#include "rogue.h"
#include "rogue_actor_art.h"
#include "anim.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl_collision.h"
#include "engine_math.h"
#include "fade.h"
#include "hum.h"
#include "m4a_song.h"
#include "system_state.h"

// Bosses with a fight of their own, drawn from their own sheets. They take
// the place of Leon in his battle, as the friends do, but nothing of his is
// left: the pictures come from tools/rogue_actors.py, one for each pose, and
// what the boss does is decided here. A move is a clip: poses in turn, each
// with how far it carries the boss and what it sets off. Between moves the
// boss rests, walking up to Sora; hit, it loses the move it was making.

typedef struct RogueActorMove {
    u8 clip;
    u8 near; // made when Sora is this far, in pixels, at least
    u8 far; // and this far at most
    u8 weight;
    u8 flags;
} RogueActorMove;

#define MOVE_ENRAGED 1 // only below half HP
#define MOVE_ALIGNED 2 // only level with Sora

typedef struct RogueActor {
    const AnimDef* poses;
    const RogueClipStep* const* clips;
    HumDef def;
    u8 idle;
    u8 run;
    u8 hurt;
    u8 enrage; // the clip played once at half HP, 0xFF for none
    u8 escape; // the move made after three hits taken in a row
    u8 moveCount;
    const RogueActorMove* moves;
    u16 speed; // a frame, walking up to Sora
    u8 rest; // frames between moves on the first floor
    u8 keep; // how near Sora it walks, in pixels
    void (*special)(BtlObj* boss, u8 which);
} RogueActor;

static u8 sClip;
static u8 sStep;
static u8 sTime;
static u8 sPose; // the pose shown, 0xFF when the picture is not one of the clips'
static u8 sActing; // in the middle of a move
static u8 sEnraged;
static u8 sStagger; // moves lost to hits in a row
static u8 sLast; // the move made last, not made twice running
static u8 sSide; // which side of Sora the next blink comes out on
static s16 sRest;
static u32 sFrame; // the frame of the last tick: a gap means the boss was hit
static s32 sDriftX; // carried this far a frame, for sDrift frames
static s32 sDriftY;
static u8 sDrift;

// tall: one of the numbers of Leon's own definition, kept as he has it.
#define ACTOR_DEF(tiles, palette, tall) { tiles, 0, (void*)palette, 0, { 41, 99, tall, 14, 40, 99, 0 } }

// Sephiroth.

static void SephirothSpecial(BtlObj* boss, u8 which) {
    BtlObj* sora = gBtlWork->actor;
    s32 left = (boss->flags & 4) != 0;

    switch (which) {
    case 3:
        // He has landed: the ground bursts on both sides of him.
        RogueFoeMove(boss, ROGUE_MOVE_FIRE_BURST, boss->x - 0x3000, boss->y, boss->z, ROGUE_MOVE_PLAIN, 0, 4, 1);
        RogueFoeMove(boss, ROGUE_MOVE_FIRE_BURST, boss->x + 0x3000, boss->y, boss->z, ROGUE_MOVE_PLAIN, 0, 4, 0);
        break;
    case 5:
        // The wave; with the wing out, three abreast.
        RogueFoeMove(boss, ROGUE_MOVE_WAVE, boss->x + (left ? -0x2000 : 0x2000), boss->y, boss->z - 0x1A00, ROGUE_MOVE_PLAIN, 0, 0, left);

        if (sEnraged) {
            RogueFoeMove(boss, ROGUE_MOVE_WAVE, boss->x + (left ? -0x2000 : 0x2000), boss->y - 0x1400, boss->z - 0x1A00, ROGUE_MOVE_PLAIN, 0,
                         8, left);
            RogueFoeMove(boss, ROGUE_MOVE_WAVE, boss->x + (left ? -0x2000 : 0x2000), boss->y + 0x1400, boss->z - 0x1A00, ROGUE_MOVE_PLAIN, 0,
                         16, left);
        }
        break;
    case 6:
        m4aSongNumStart(SONG_EF_SUMMON_UP);
        break;
    case 7:
        // Heartless Angel, left to finish: all Sora has but one.
        if (sora->unk_02C > 1 && !gRogueDebug.god) {
            sora->unk_02C = 1;
        }

        FadeFromAmount(2, 16, 16);
        m4aSongNumStart(SONG_EF_SUMMON_UP);
        break;
    }
}

static const RogueActorMove sSephirothMoves[] = {
    { ROGUE_SEPHIROTH_CLIP_SLASH, 0, 70, 3, MOVE_ALIGNED },
    { ROGUE_SEPHIROTH_CLIP_SWEEP, 0, 80, 2, MOVE_ALIGNED },
    { ROGUE_SEPHIROTH_CLIP_RISE, 0, 64, 2, MOVE_ALIGNED },
    { ROGUE_SEPHIROTH_CLIP_THRUST, 50, 140, 3, MOVE_ALIGNED },
    { ROGUE_SEPHIROTH_CLIP_FLASH, 70, 255, 2, 0 },
    { ROGUE_SEPHIROTH_CLIP_PLUNGE, 50, 255, 2, 0 },
    { ROGUE_SEPHIROTH_CLIP_FLARE, 80, 255, 2, 0 },
    { ROGUE_SEPHIROTH_CLIP_WAVE, 60, 255, 3, MOVE_ALIGNED },
    { ROGUE_SEPHIROTH_CLIP_ANGEL, 90, 255, 1, MOVE_ENRAGED },
    { ROGUE_SEPHIROTH_CLIP_OCTA, 0, 255, 2, MOVE_ENRAGED },
};

static const RogueActor sSephiroth = {
    gRogueSephirothPoses,
    gRogueSephirothClips,
    ACTOR_DEF(ROGUE_SEPHIROTH_TILES + 1, gRogueSephirothActorPalette, 64),
    ROGUE_SEPHIROTH_CLIP_IDLE,
    ROGUE_SEPHIROTH_CLIP_RUN,
    ROGUE_SEPHIROTH_CLIP_HURT,
    ROGUE_SEPHIROTH_CLIP_WING,
    ROGUE_SEPHIROTH_CLIP_FLASH,
    sizeof(sSephirothMoves) / sizeof(sSephirothMoves[0]),
    sSephirothMoves,
    0x1A0,
    46,
    56,
    SephirothSpecial,
};

// Sora as he is on his second journey: quick, with the Keyblade thrown and
// two spells, and a Cure at half his HP.

static const RogueActorMove sSoraKh2Moves[] = {
    { ROGUE_SORA_KH2_CLIP_COMBO, 0, 56, 3, MOVE_ALIGNED },
    { ROGUE_SORA_KH2_CLIP_ARCS, 0, 60, 3, MOVE_ALIGNED },
    { ROGUE_SORA_KH2_CLIP_RISING, 0, 52, 2, MOVE_ALIGNED },
    { ROGUE_SORA_KH2_CLIP_RAID, 50, 255, 4, MOVE_ALIGNED },
    { ROGUE_SORA_KH2_CLIP_FIRE, 60, 255, 2, 0 },
    { ROGUE_SORA_KH2_CLIP_ICE, 60, 255, 2, MOVE_ALIGNED },
    { ROGUE_SORA_KH2_CLIP_SONIC, 60, 255, 2, 0 },
    { ROGUE_SORA_KH2_CLIP_ARS, 0, 255, 2, MOVE_ENRAGED },
};

static const RogueActor sSoraKh2 = {
    gRogueSoraKh2Poses,
    gRogueSoraKh2Clips,
    ACTOR_DEF(ROGUE_SORA_KH2_TILES + 1, gRogueSoraKh2ActorPalette, 64),
    ROGUE_SORA_KH2_CLIP_IDLE,
    ROGUE_SORA_KH2_CLIP_RUN,
    ROGUE_SORA_KH2_CLIP_HURT,
    ROGUE_SORA_KH2_CLIP_CURE,
    ROGUE_SORA_KH2_CLIP_SONIC,
    sizeof(sSoraKh2Moves) / sizeof(sSoraKh2Moves[0]),
    sSoraKh2Moves,
    0x200,
    40,
    44,
    0,
};

// Roxas, three times over.

static const RogueActorMove sRoxasMoves[] = {
    { ROGUE_ROXAS_CLIP_SLASH, 0, 54, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_CLIP_SPIN, 0, 58, 2, MOVE_ALIGNED },
    { ROGUE_ROXAS_CLIP_UPPER, 0, 50, 2, MOVE_ALIGNED },
    { ROGUE_ROXAS_CLIP_RAID, 50, 255, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_CLIP_DASH, 50, 130, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_CLIP_FLURRY, 0, 255, 3, MOVE_ENRAGED },
};

static const RogueActor sRoxas = {
    gRogueRoxasPoses,
    gRogueRoxasClips,
    ACTOR_DEF(ROGUE_ROXAS_TILES + 1, gRogueRoxasActorPalette, 64),
    ROGUE_ROXAS_CLIP_IDLE,
    ROGUE_ROXAS_CLIP_RUN,
    ROGUE_ROXAS_CLIP_HURT,
    ROGUE_ROXAS_CLIP_DUAL,
    ROGUE_ROXAS_CLIP_DASH,
    sizeof(sRoxasMoves) / sizeof(sRoxasMoves[0]),
    sRoxasMoves,
    0x1E0,
    44,
    44,
    0,
};

static const RogueActorMove sRoxasCoatMoves[] = {
    { ROGUE_ROXAS_COAT_CLIP_COMBO, 0, 58, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_COAT_CLIP_WIDE, 0, 68, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_COAT_CLIP_LIGHT, 30, 80, 2, MOVE_ALIGNED },
    { ROGUE_ROXAS_COAT_CLIP_DARK, 0, 74, 2, MOVE_ALIGNED },
    { ROGUE_ROXAS_COAT_CLIP_RAID, 60, 255, 2, MOVE_ALIGNED },
    { ROGUE_ROXAS_COAT_CLIP_STEP, 60, 255, 3, 0 },
    { ROGUE_ROXAS_COAT_CLIP_LIGHTS, 70, 255, 2, 0 },
    { ROGUE_ROXAS_COAT_CLIP_FLURRY, 0, 255, 3, MOVE_ENRAGED },
};

static const RogueActor sRoxasCoat = {
    gRogueRoxasCoatPoses,
    gRogueRoxasCoatClips,
    ACTOR_DEF(ROGUE_ROXAS_COAT_TILES + 1, gRogueRoxasCoatActorPalette, 64),
    ROGUE_ROXAS_COAT_CLIP_IDLE,
    ROGUE_ROXAS_COAT_CLIP_RUN,
    ROGUE_ROXAS_COAT_CLIP_HURT,
    ROGUE_ROXAS_COAT_CLIP_RAGE,
    ROGUE_ROXAS_COAT_CLIP_STEP,
    sizeof(sRoxasCoatMoves) / sizeof(sRoxasCoatMoves[0]),
    sRoxasCoatMoves,
    0x200,
    38,
    46,
    0,
};

static const RogueActorMove sRoxasHoodMoves[] = {
    { ROGUE_ROXAS_HOOD_CLIP_COMBO, 0, 58, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_HOOD_CLIP_ARCS, 0, 72, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_HOOD_CLIP_WIDE, 0, 68, 2, MOVE_ALIGNED },
    { ROGUE_ROXAS_HOOD_CLIP_CYCLONE, 40, 160, 3, MOVE_ALIGNED },
    { ROGUE_ROXAS_HOOD_CLIP_PILLARS, 0, 70, 2, 0 },
    { ROGUE_ROXAS_HOOD_CLIP_LIGHTS, 70, 255, 2, 0 },
    { ROGUE_ROXAS_HOOD_CLIP_STEP, 60, 255, 3, 0 },
    { ROGUE_ROXAS_HOOD_CLIP_FLURRY, 0, 255, 3, MOVE_ENRAGED },
};

static const RogueActor sRoxasHood = {
    gRogueRoxasHoodPoses,
    gRogueRoxasHoodClips,
    ACTOR_DEF(ROGUE_ROXAS_HOOD_TILES + 1, gRogueRoxasHoodActorPalette, 64),
    ROGUE_ROXAS_HOOD_CLIP_IDLE,
    ROGUE_ROXAS_HOOD_CLIP_RUN,
    ROGUE_ROXAS_HOOD_CLIP_HURT,
    ROGUE_ROXAS_HOOD_CLIP_RAGE,
    ROGUE_ROXAS_HOOD_CLIP_STEP,
    sizeof(sRoxasHoodMoves) / sizeof(sRoxasHoodMoves[0]),
    sRoxasHoodMoves,
    0x220,
    34,
    46,
    0,
};

static const RogueActor* const sActors[ROGUE_SKIN_ACTORS_END - ROGUE_SKINS] = {
    &sSephiroth, &sSoraKh2, &sRoxas, &sRoxasCoat, &sRoxasHood,
};

static const RogueActor* RogueActorNow(void) {
    if (gRogue.bossSkin >= ROGUE_SKINS && gRogue.bossSkin < ROGUE_SKIN_ACTORS_END) {
        return sActors[gRogue.bossSkin - ROGUE_SKINS];
    }

    return 0;
}

u8 RogueActorIs(void) {
    return RogueActorNow() != 0;
}

// What the game's own code shows of the boss while it is not the AI's: Leon's
// standing (0) and his other four, of which 3 and 4 are for when he is hit.
const AnimDef* RogueActorAnim(u16 slot) {
    const RogueActor* actor = RogueActorNow();
    const RogueClipStep* clip = actor->clips[slot >= 3 ? actor->hurt : actor->idle];

    sPose = 0xFF;
    return &actor->poses[clip[slot == 4 ? 1 : 0].pose];
}

const HumDef* RogueActorDef(void) {
    return &RogueActorNow()->def;
}

void RogueActorReset(void) {
    sClip = 0;
    sStep = 0;
    sTime = 0;
    sPose = 0xFF;
    sActing = 0;
    sEnraged = 0;
    sStagger = 0;
    sLast = 0xFF;
    sSide = 0;
    sRest = 60;
    sFrame = 0;
    sDrift = 0;
}

// A hit of a boss's, or of something a boss threw: whose card is in play
// decides whom a hit box hurts, so the enemy's turn is claimed for the test.
s32 RogueFoeHit(BtlObj* foe, s32 x, s32 y, s32 z, s16 width, s16 depth, s16 height, u16 scale) {
    u64 flags = gBtlWork->flags;
    BtlObj* source = gBtlWork->actor3;
    s32 old = gBtlWork->unk_124;
    s32 hit;

    gBtlWork->flags &= ~0x20000000ULL;
    gBtlWork->actor3 = foe;
    gBtlWork->unk_124 = scale;
    hit = func_08011F78(ROGUE_BOSS_AI_ATTACK, x, y, z, width, depth, height);
    gBtlWork->unk_124 = old;
    gBtlWork->actor3 = source;
    gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);

    if (hit) {
        gRogueDebug.bossHits++;
    }

    return hit;
}

static void RogueActorFace(BtlObj* boss, BtlObj* sora) {
    if (sora->x < boss->x) {
        boss->flags |= 4;
    } else {
        boss->flags &= ~4;
    }
}

// What a step sets off as it starts.
static void RogueActorEvent(const RogueActor* actor, BtlObj* boss) {
    const RogueClipStep* step = &actor->clips[sClip][sStep];
    BtlObj* sora = gBtlWork->actor;
    s32 reach = step->arg;
    s32 left = (boss->flags & 4) != 0;
    s32 dir;
    s32 i;

    switch (step->event) {
    case ROGUE_CLIP_BLINK:
        sSide ^= 1;
        boss->x = sora->x + (sSide ? 0x2600 : -0x2600);
        boss->y = sora->y;
        RogueActorFace(boss, sora);
        // Fall through.
    case ROGUE_CLIP_HIT:
    case ROGUE_CLIP_HEAVY:
        dir = (boss->flags & 4) ? -1 : 1;
        RogueFoeHit(boss, boss->x + dir * reach * 0x80, boss->y, boss->z, reach / 2 + 4, 18, 44, step->event == ROGUE_CLIP_HEAVY ? 384 : 256);
        gRogueDebug.bossSwings++;
        break;
    case ROGUE_CLIP_SPECIAL:
        if (actor->special != 0) {
            actor->special(boss, step->arg);
        }
        break;
    case ROGUE_CLIP_THROW:
        RogueFoeMove(boss, step->arg, boss->x + (left ? -0x2000 : 0x2000), boss->y, boss->z - 0x1400, ROGUE_MOVE_PLAIN, 0, 0, left);
        break;
    case ROGUE_CLIP_SEEK:
        // Four, or with the boss enraged six, each a moment after the other.
        for (i = 0; i < (sEnraged ? 6 : 4); i++) {
            static const s8 where[6][2] = { { -48, -14 }, { 48, -14 }, { -48, 14 }, { 48, 14 }, { 0, -24 }, { 0, 24 } };

            RogueFoeMove(boss, step->arg, sora->x + where[i][0] * 0x100, sora->y + where[i][1] * 0x100, sora->z - 0x2800, ROGUE_MOVE_SHARD,
                         40 + i * 9, i * 3, where[i][0] > 0);
        }
        break;
    case ROGUE_CLIP_CAST:
        RogueFoeMove(boss, step->arg, boss->x + (left ? -0x2800 : 0x2800), boss->y, boss->z, ROGUE_MOVE_PLAIN, 0, 0, left);
        break;
    case ROGUE_CLIP_BEHIND:
        boss->x = sora->x + (left ? -0x2800 : 0x2800);
        boss->y = sora->y;
        boss->flags ^= 4;
        m4aSongNumStart(SONG_EF_RAC_3TR);
        break;
    case ROGUE_CLIP_OVER:
        sDrift = 18;
        sDriftX = (sora->x - boss->x) / 18;
        sDriftY = (sora->y - boss->y) / 18;
        break;
    case ROGUE_CLIP_LAND:
        boss->z = boss->unk_010;
        FadeFromAmount(2, 10, 16);
        m4aSongNumStart(SONG_EF_SUMMON_UP);
        RogueFoeHit(boss, boss->x, boss->y, boss->z, reach, 26, 48, 384);
        gRogueDebug.bossSwings++;
        break;
    case ROGUE_CLIP_FLASH:
        FadeFromAmount(2, 16, 16);
        m4aSongNumStart(SONG_EF_SUMMON_UP);
        break;
    case ROGUE_CLIP_HEAL:
        boss->unk_02C += boss->unk_02E / 6;

        if (boss->unk_02C > boss->unk_02E) {
            boss->unk_02C = boss->unk_02E;
        }
        break;
    }
}

static void RogueActorStart(const RogueActor* actor, BtlObj* boss, u8 clip) {
    sClip = clip;
    sStep = 0;
    sTime = 0;
    RogueActorEvent(actor, boss);
}

// One frame of the clip being played. Returns 0 when it has ended; one that
// loops starts again instead.
static s32 RogueActorPlay(const RogueActor* actor, BtlObj* boss, AnimState* anim, void* tiles, u8 loops) {
    const RogueClipStep* step = &actor->clips[sClip][sStep];
    s32 dir = (boss->flags & 4) ? -1 : 1;

    if (step->pose != sPose) {
        sPose = step->pose;
        AnimChangeWithDef(&actor->poses[sPose], anim, 0, 1, tiles);
    }

    boss->x += dir * step->move * 0x100;
    boss->z -= step->lift * 0x100;

    if (sDrift != 0) {
        sDrift--;
        boss->x += sDriftX;
        boss->y += sDriftY;
    }

    if (++sTime < step->frames) {
        return 1;
    }

    sTime = 0;
    sStep++;

    if (actor->clips[sClip][sStep].frames == 0) {
        if (!loops) {
            return 0;
        }

        sStep = 0;
    }

    RogueActorEvent(actor, boss);
    return 1;
}

// The move to make with Sora this far off, 0xFF if none suits.
static u8 RogueActorChoose(const RogueActor* actor, s32 distance, s32 level) {
    s32 total = 0;
    s32 roll;
    s32 i;
    s32 pass;

    for (pass = 0; pass < 2; pass++) {
        for (i = 0; i < actor->moveCount; i++) {
            const RogueActorMove* move = &actor->moves[i];

            if (distance < move->near || distance > move->far || move->clip == sLast) {
                continue;
            }

            if (((move->flags & MOVE_ENRAGED) && !sEnraged) || ((move->flags & MOVE_ALIGNED) && !level)) {
                continue;
            }

            if (pass == 0) {
                total += move->weight;
            } else {
                roll -= move->weight;

                if (roll < 0) {
                    return move->clip;
                }
            }
        }

        if (total == 0) {
            return 0xFF;
        }

        if (pass == 0) {
            roll = GetRandom() % total;
        }
    }

    return 0xFF;
}

// Called every frame the boss is free to act.
u8 RogueActorTick(BtlObj* boss, AnimState* anim, void* tiles) {
    const RogueActor* actor = RogueActorNow();
    BtlObj* sora = gBtlWork->actor;
    s32 dx;
    s32 dy;
    s32 distance;
    s32 rest;
    u8 clip;

    // Hit since the last frame: the move is lost. Three lost in a row and he
    // is done taking it.
    if (sFrame != 0 && gFrameCounter - sFrame > 2) {
        if (sActing) {
            sStagger++;
        }

        sActing = 0;
        sDrift = 0;
        boss->z = boss->unk_010;
        sRest = 14;
        sClip = 0xFF;

        if (sStagger >= 3) {
            sStagger = 0;
            sActing = 1;
            RogueActorFace(boss, sora);
            RogueActorStart(actor, boss, actor->escape);
        }
    }

    sFrame = gFrameCounter;

    if (sora == 0 || sora->unk_02C <= 0) {
        if (sClip != actor->idle || sActing) {
            sActing = 0;
            boss->z = boss->unk_010;
            RogueActorStart(actor, boss, actor->idle);
        }

        RogueActorPlay(actor, boss, anim, tiles, 1);
        return 1;
    }

    if (sActing) {
        if (!RogueActorPlay(actor, boss, anim, tiles, 0)) {
            sActing = 0;
            sStagger = 0;
            sDrift = 0;
            boss->z = boss->unk_010;
            rest = actor->rest - gRogue.floor * 3;

            if (sEnraged) {
                rest /= 2;
            }

            sRest = rest < 12 ? 12 : rest;
            sClip = 0xFF;
        }

        return 1;
    }

    RogueActorFace(boss, sora);
    dx = sora->x - boss->x;
    dy = sora->y - boss->y;
    distance = (dx < 0 ? -dx : dx) >> 8;

    if (distance > 255) {
        distance = 255;
    }

    // At half HP, once, whatever he was about to do.
    if (!sEnraged && actor->enrage != 0xFF && boss->unk_02C * 2 < boss->unk_02E) {
        sEnraged = 1;
        sActing = 1;
        RogueActorStart(actor, boss, actor->enrage);
        gRogueDebug.bossClip = actor->enrage;
        return 1;
    }

    if (sRest > 0) {
        sRest--;
    } else {
        clip = RogueActorChoose(actor, distance, dy <= 0xC00 && dy >= -0xC00);

        if (gRogueDebug.bossForce != 0) {
            clip = gRogueDebug.bossForce - 1;
            gRogueDebug.bossForce = 0;
        }

        if (clip != 0xFF) {
            sActing = 1;
            sLast = clip;
            gRogueDebug.bossClip = clip;
            gRogueDebug.bossClips++;
            RogueActorStart(actor, boss, clip);
            return 1;
        }
    }

    // Resting: he walks up to Sora, or stands.
    clip = actor->idle;

    if (distance > actor->keep) {
        boss->x += dx > 0 ? actor->speed : -actor->speed;
        clip = actor->run;
    }

    if (dy > 0x600) {
        boss->y += actor->speed / 2;
        clip = actor->run;
    } else if (dy < -0x600) {
        boss->y -= actor->speed / 2;
        clip = actor->run;
    }

    if (sClip != clip) {
        RogueActorStart(actor, boss, clip);
    }

    RogueActorPlay(actor, boss, anim, tiles, 1);
    return 1;
}
