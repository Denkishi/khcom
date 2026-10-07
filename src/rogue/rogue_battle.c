#include "rogue.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl_collision.h"
#include "card_def_data.h"
#include "engine_math.h"
#include "hum.h"
#include "m4a_song.h"
#include "sprite_palettes.h"
#include "sprites_hum.h"
#include "gba/keys.h"
#include "msg_api.h"
#include "obj_api.h"
#include "sprite.h"
#include "system_state.h"
#include "taskpool.h"
#include "text.h"

// What the mod adds on top of a battle: the hit counter and its damage
// bonus, hitstop, and the jump buffer.

// The enemy Sora hit last, for the tests to follow after the lock-on drops it.

static BtlObj* sLastHit;

// Runs a pending test command and refreshes what the tests read back.
void RogueDebugBattle(void) {
    BtlObj* sora = gBtlWork->actor;
    BtlObj* target = gBtlWork->actor2;
    u64 flags;

    if (sora != 0) {
        gRogueDebug.soraHp = sora->unk_02C;
        gRogueDebug.soraZ = sora->z;
    }

    gRogueDebug.targetHp = target != 0 ? target->unk_02C : -1;
    gRogueDebug.targetZ = sLastHit != 0 ? sLastHit->z : 0;

    switch (gRogueDebug.command) {
    case ROGUE_DEBUG_WIN:
        gBtlWork->flags |= 0x200000000ULL;
        break;
    case ROGUE_DEBUG_HURT:
        if (sora != 0) {
            sora->unk_020 = gRogueDebug.arg;
            sora->flags |= 2;
        }
        break;
    case ROGUE_DEBUG_HIT:
        if (target != 0) {
            target->unk_020 = gRogueDebug.arg;
            target->flags |= 2;
        }
        break;
    case ROGUE_DEBUG_RELIC:
        gRogue.relics |= 1 << gRogueDebug.arg;
        break;
    case ROGUE_DEBUG_ENEMY_TAG:
        RogueOnEnemyCard(&gCardDefs[450 + gRogueDebug.arg]);
        break;
    case ROGUE_DEBUG_TAG:
        RogueTagIn(gRogueDebug.arg);
        break;
    case ROGUE_DEBUG_MOVE:
        if (sora != 0) {
            RogueDoMove(gRogueDebug.arg, sora);
        }
        break;
    case ROGUE_DEBUG_FINISHER:
        if (sora != 0) {
            RogueOnFinisher(sora);
        }
        break;
    case ROGUE_DEBUG_ATTACK:
        // Goes through the whole damage calculation, as a hit of Sora's.
        if (target != 0) {
            flags = gBtlWork->flags;
            gBtlWork->flags |= 0x20000000;
            func_08011F78(gRogueDebug.arg, target->x, target->y, target->z, 24, 16, 32);
            gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
        }
        break;
    default:
        return;
    }

    gRogueDebug.command = ROGUE_DEBUG_NONE;
}

// The damage of Sora's last hits, shown where they landed.
typedef struct RogueDamageNumber {
    s32 x;
    s32 y;
    s32 z;
    u16 value;
    u8 timer; // frames left on the screen, 0 when not shown
} RogueDamageNumber;

static RogueDamageNumber sNumbers[ROGUE_DAMAGE_NUMBERS];
static u8 sNextNumber;

// Called when an actor is about to take the damage in unk_020.
void RogueOnDamage(BtlObj* p) {
    BtlObj* sora = gBtlWork->actor;
    s32 bonus;
    s32 cap;

    if (p == sora) {
        if (gRogueDebug.god) {
            p->unk_020 = 0;
        }

        if (RogueHasRelic(ROGUE_RELIC_GLASS_CANNON)) {
            p->unk_020 += p->unk_020 / 2;
        }

        if (RogueHasRelic(ROGUE_RELIC_SECOND_WIND) && !gRogue.secondWindUsed && p->unk_020 >= p->unk_02C && p->unk_02C > 1) {
            p->unk_020 = p->unk_02C - 1;
            gRogue.secondWindUsed = 1;
        }

        gRogue.combo = 0;
        gRogue.comboTimer = 0;
        return;
    }

    // Each hit of an unbroken string adds 2% damage, up to 30%.
    cap = RogueHasRelic(ROGUE_RELIC_MOMENTUM) ? ROGUE_COMBO_BONUS_HITS * 2 : ROGUE_COMBO_BONUS_HITS;
    bonus = gRogue.combo < cap ? gRogue.combo : cap;
    p->unk_020 += p->unk_020 * bonus / 50;

    if (RogueHasRelic(ROGUE_RELIC_CRITICAL) && RogueRandBelow(7) == 0) {
        p->unk_020 *= 2;
    }

    if (RogueHasRelic(ROGUE_RELIC_GLASS_CANNON)) {
        p->unk_020 += p->unk_020 / 2;
    }

    if (RogueHasRelic(ROGUE_RELIC_VAMPIRE) && sora->unk_02C > 0 && sora->unk_02C < sora->unk_02E) {
        sora->unk_02C++;
    }

    if (gRogue.combo < 999) {
        gRogue.combo++;
    }

    gRogue.comboTimer = ROGUE_COMBO_TIME;
    gRogueDebug.lastDamage = p->unk_020;
    gRogueDebug.hits++;
    sLastHit = p;

    // The damage rises from the enemy as a number; the oldest makes room.
    if (p->unk_020 > 0) {
        RogueDamageNumber* number = &sNumbers[sNextNumber];

        sNextNumber = (sNextNumber + 1) % ROGUE_DAMAGE_NUMBERS;
        number->x = p->x;
        number->y = p->y;
        number->z = p->z;
        number->value = p->unk_020 > 9999 ? 9999 : p->unk_020;
        number->timer = ROGUE_DAMAGE_NUMBER_TIME;
    }
}

// Called once the knockback of one of Sora's hits is set: a combo finisher
// sends the enemy up, so that the combo can go on in the air.
void RogueOnKnockback(BtlObj* target) {
    if (gRogue.finisher && target->unk_0AC < ROGUE_LAUNCH) {
        target->unk_0AC = ROGUE_LAUNCH;
    }
}

u8 RogueReloadRate(u8 slowed) {
    u8 rate = slowed ? ROGUE_RELOAD_RATE_SLOWED : ROGUE_RELOAD_RATE;

    if (RogueHasRelic(ROGUE_RELIC_RELOAD)) {
        rate += rate / 2;
    }

    return rate;
}

// A press of the jump button counts for a few frames, so that one made just
// before Sora can jump still does.
u16 RogueBufferJump(u16 pressed) {
    // Once a frame, before Sora acts: the pose of a move runs out.
    if (gRogue.pose != 0) {
        gRogue.pose--;
    }

    if (pressed & B_BUTTON) {
        gRogue.jumpBuffer = ROGUE_JUMP_BUFFER;
    } else if (gRogue.jumpBuffer != 0) {
        gRogue.jumpBuffer--;
        pressed |= B_BUTTON;
    }

    return pressed;
}

// Larxene's knife thrown by Sora: her projectile with the sides swapped. The
// game decides whom a hitbox hurts from whose card is in play, so the knife
// claims the player's turn for the instant of its own hit test.

#define KNIFE_ATTACK 0x133
#define KNIFE_COUNT 3
#define KNIFE_TILES 0x2C0

typedef struct RogueKnifeArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 left;
} RogueKnifeArgs;

typedef struct RogueKnifeWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    u8 left;
    u8 onScreen;
    u8 stuck;
    u8 timer;
} RogueKnifeWork;

static void RogueKnife_Init(RogueKnifeWork* w, RogueKnifeArgs* args) {
    w->palette = LoadObjPalette(gLaxinePalette, 0x20);
    w->tiles = LoadObjTiles(gLaxineKnifeTiles, KNIFE_TILES);
    AnimInit(&w->anim, gLaxineKnifeAnims, gLaxineKnifeFrames);
    AnimStart(&w->anim, 0, 0);
    w->x = args->x;
    w->y = args->y;
    w->z = args->z;
    w->left = args->left;
    w->vx = GetRandom() % 897 + 0x800;
    w->onScreen = 1;
    w->stuck = 0;
    w->timer = 0;
}

static s32 RogueKnife_Update(RogueKnifeWork* w) {
    u64 flags;
    s32 hit;

    if (!w->onScreen) {
        return 0;
    }

    if (w->stuck) {
        if (++w->timer > 30) {
            return 0;
        }
    } else {
        flags = gBtlWork->flags;
        gBtlWork->flags |= 0x20000000;
        gRogue.projectile = 1;
        hit = func_08011F78(KNIFE_ATTACK, w->x, w->y, w->z, 1, 6, 2);
        gRogue.projectile = 0;
        gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);

        if (hit) {
            m4aSongNumStart(SONG_BTL_RAC_HIT);
            AnimStart(&w->anim, 1, 0);
            w->stuck = 1;
        } else if (w->left) {
            w->x -= w->vx;
        } else {
            w->x += w->vx;
        }
    }

    AnimUpdate(&w->anim);
    return 1;
}

static void RogueKnife_Draw(RogueKnifeWork* w) {
    u16 attr = GetBattleSpritePriorityFlags(w->y);
    s16 x;
    s16 y;

    // Her sprite faces left; Sora's knives fly the way he faces.
    if (w->left) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, w->x, w->y, w->z);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, attr, -0x1004 - (w->y >> 8) * 4);

    if (IsRectOutsideScreen(x, y, 2, 2, 32, 32)) {
        w->onScreen = 0;
    }
}

static void RogueKnife_Destroy(RogueKnifeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

static TaskDesc sTaskDescRogueKnife = {
    "task_rogue_knife",
    (TaskInitFunc)RogueKnife_Init,
    (TaskUpdateFunc)RogueKnife_Update,
    (TaskDrawFunc)RogueKnife_Draw,
    (TaskDestroyFunc)RogueKnife_Destroy,
    sizeof(RogueKnifeWork),
};

// Vexen's ice, raised by Sora: a block of it comes up where the finisher
// lands and hits what stands there, as one of his own ice attacks cut down
// to about a swing and a half.

#define PILLAR_ATTACK 313
#define PILLAR_TILES 0x800
#define PILLAR_HIT_FRAME 6
#define PILLAR_FRAMES 44

typedef struct RoguePillarArgs {
    s32 x;
    s32 y;
} RoguePillarArgs;

typedef struct RoguePillarWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    u8 timer;
} RoguePillarWork;

static void RoguePillar_Init(RoguePillarWork* w, RoguePillarArgs* args) {
    w->palette = LoadObjPalette(gVixEPalette, 0x20);
    w->tiles = LoadObjTiles(gVixenE2Tiles, PILLAR_TILES);
    AnimInit(&w->anim, gVixenE2Anims, gVixenE2Frames);
    AnimStart(&w->anim, 0, 0);
    w->x = args->x;
    w->y = args->y;
    w->timer = 0;
}

static s32 RoguePillar_Update(RoguePillarWork* w) {
    u64 flags;
    s32 scale;

    if (w->timer == PILLAR_HIT_FRAME) {
        flags = gBtlWork->flags;
        scale = gBtlWork->unk_124;
        gBtlWork->flags |= 0x20000000;
        gBtlWork->unk_124 = ROGUE_PILLAR_SCALE;
        gRogue.projectile = 1;
        gRogue.echoing = 1;
        func_08011F78(PILLAR_ATTACK, w->x, w->y, 0, 28, 20, 48);
        gRogue.echoing = 0;
        gRogue.projectile = 0;
        gBtlWork->unk_124 = scale;
        gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
    }

    if (w->timer == PILLAR_FRAMES / 2) {
        AnimStart(&w->anim, 1, 0);
    }

    AnimUpdate(&w->anim);
    return ++w->timer < PILLAR_FRAMES;
}

static void RoguePillar_Draw(RoguePillarWork* w) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, w->x, w->y, 0);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, GetBattleSpritePriorityFlags(w->y),
               -0x1004 - (w->y >> 8) * 4);
}

static void RoguePillar_Destroy(RoguePillarWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

static TaskDesc sTaskDescRoguePillar = {
    "task_rogue_pillar",
    (TaskInitFunc)RoguePillar_Init,
    (TaskUpdateFunc)RoguePillar_Update,
    (TaskDrawFunc)RoguePillar_Draw,
    (TaskDestroyFunc)RoguePillar_Destroy,
    sizeof(RoguePillarWork),
};

void RogueRaisePillar(BtlObj* sora) {
    RoguePillarArgs args;

    if (!CanAllocObjTiles(PILLAR_TILES / 32)) {
        return;
    }

    args.x = sora->x + ((sora->flags & 4) ? -0x2400 : 0x2400);
    args.y = sora->y;
    TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRoguePillar, &args);
    gRogueDebug.pillars++;
}

void RogueThrowKnives(BtlObj* sora) {
    RogueKnifeArgs args;
    s32 count;
    s32 i;

    m4aSongNumStart(SONG_EF_RAC_3TR);

    // A projectile build throws five knives instead of three.
    count = RogueBuildBonus(ROGUE_BUILD_PROJECTILE) != 0 ? KNIFE_COUNT + 2 : KNIFE_COUNT;

    for (i = 0; i < count; i++) {
        // The check counts 8x8 tiles, the size above is in bytes.
        if (!CanAllocObjTiles(KNIFE_TILES / 32)) {
            return;
        }

        args.left = (sora->flags & 4) != 0;
        args.x = sora->x + (args.left ? -0x1800 : 0x1800);
        args.y = sora->y + (i - count / 2) * 0x0A00;
        args.z = sora->z - 0x1400;
        TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueKnife, &args);
        gRogueDebug.knives++;
    }
}

// Called on the hit frame of a combo finisher.
void RogueOnFinisher(BtlObj* sora) {
    u8 move;

    if (RogueHasRelic(ROGUE_RELIC_ICE_PILLAR)) {
        RogueRaisePillar(sora);
    }

    if (RogueHasRelic(ROGUE_RELIC_KNIVES)) {
        RogueThrowKnives(sora);
    }

    for (move = 0; move < ROGUE_MOVES; move++) {
        if (RogueHasRelic(ROGUE_RELIC_CHAKRAM + move)) {
            RogueDoMove(move, sora);
        }
    }
}

// The same for the card button: the request to play a card is repeated for a
// few frames, so that one made just before Sora is free still counts. It
// stops as soon as a card is played, see RogueOnStockPlayed.
u16 RogueBufferCard(u16 pressed) {
    if (pressed & A_BUTTON) {
        gRogue.cardBuffer = ROGUE_CARD_BUFFER;
    } else if (gRogue.cardBuffer != 0) {
        gRogue.cardBuffer--;
        pressed |= A_BUTTON;
    }

    return pressed;
}

typedef struct RogueHudWork {
    void* tiles;
    void* palette;
} RogueHudWork;

static const u8 sHits[] = "HIT";

static void RogueHud_Init(RogueHudWork* w) {
    u32 i;

    w->tiles = LoadSmallFontTiles();
    w->palette = LoadSmallFontPalette();
    gRogue.combo = 0;
    gRogue.comboTimer = 0;
    gRogue.jumpBuffer = 0;
    gRogue.cardBuffer = 0;
    gRogue.secondWindUsed = 0;
    gRogue.playedKind = ROGUE_NO_KIND;
    gRogue.projectile = 0;
    gRogue.echoing = 0;
    gRogue.finisher = 0;
    gRogue.artsUsed = 0;
    RogueCountBuild();
    gRogueDebug.hits = 0;
    sLastHit = 0;
    gRogueDebug.knives = 0;
    gRogueDebug.pillars = 0;
    gRogueDebug.tagHits = 0;
    gRogueDebug.moves = 0;
    gRogueDebug.moveHits = 0;
    gRogue.tagTimer = 0;
    gRogue.pose = 0;
    gRogueDebug.echoes = 0;
    sNextNumber = 0;

    for (i = 0; i < ROGUE_DAMAGE_NUMBERS; i++) {
        sNumbers[i].timer = 0;
    }
}

static s32 RogueHud_Update(RogueHudWork* w) {
    u32 i;

    RogueDebugBattle();

    for (i = 0; i < ROGUE_DAMAGE_NUMBERS; i++) {
        if (sNumbers[i].timer != 0) {
            sNumbers[i].timer--;
        }
    }

    if (gRogue.comboTimer != 0) {
        gRogue.comboTimer--;

        if (gRogue.comboTimer == 0) {
            gRogue.combo = 0;
        }
    }

    return 1;
}

static void RogueHud_Draw(RogueHudWork* w) {
    u16 text[8];
    u16 digits;
    s16 x;
    s16 y;
    u32 i;

    // The numbers rise as they age, from above the enemy's head.
    for (i = 0; i < ROGUE_DAMAGE_NUMBERS; i++) {
        const RogueDamageNumber* number = &sNumbers[i];

        if (number->timer == 0) {
            continue;
        }

        WorldToScreen(&x, &y, number->x, number->y, number->z);
        digits = FormatSmallFontDecimal(number->value, text);
        y -= 40 + (ROGUE_DAMAGE_NUMBER_TIME - number->timer) / 2;

        if (y >= 8 && x >= digits * 4 && x <= 240 - digits * 4) {
            DrawSmallFontString(x - digits * 4, y, text, w->tiles, w->palette, 0, digits);
        }
    }

    if (gRogue.combo < 2) {
        return;
    }

    // The small font has no space: the two words are drawn apart.
    digits = FormatSmallFontDecimal(gRogue.combo, text);
    x = 120 - (digits * 8 + 4 + 24) / 2;
    DrawSmallFontString(x, 30, text, w->tiles, w->palette, 0, digits);
    DrawSmallFontString(x + digits * 8 + 4, 30, text, w->tiles, w->palette, 0, EncodeSmallFontString((u8*)sHits, text));
}

static void RogueHud_Destroy(RogueHudWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

TaskDesc gTaskDescRogueHud = {
    "task_rogue_hud",
    (TaskInitFunc)RogueHud_Init,
    (TaskUpdateFunc)RogueHud_Update,
    (TaskDrawFunc)RogueHud_Draw,
    (TaskDestroyFunc)RogueHud_Destroy,
    sizeof(RogueHudWork),
};
