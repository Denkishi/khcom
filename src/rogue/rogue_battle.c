#include "rogue.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl_collision.h"
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

// Called when an actor is about to take the damage in unk_020.
void RogueOnDamage(BtlObj* p) {
    BtlObj* sora = gBtlWork->actor;
    s32 bonus;
    s32 cap;

    if (p == sora) {
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
        hit = func_08011F78(KNIFE_ATTACK, w->x, w->y, w->z, 1, 6, 2);
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

// Called on the hit frame of a combo finisher.

void RogueOnFinisher(BtlObj* sora) {
    RogueKnifeArgs args;
    s32 i;

    if (!RogueHasRelic(ROGUE_RELIC_KNIVES)) {
        return;
    }

    m4aSongNumStart(SONG_EF_RAC_3TR);

    for (i = 0; i < KNIFE_COUNT; i++) {
        // The check counts 8x8 tiles, the size above is in bytes.
        if (!CanAllocObjTiles(KNIFE_TILES / 32)) {
            return;
        }

        args.left = (sora->flags & 4) != 0;
        args.x = sora->x + (args.left ? -0x1800 : 0x1800);
        args.y = sora->y + (i - 1) * 0x0A00;
        args.z = sora->z - 0x1400;
        TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueKnife, &args);
    }
}

typedef struct RogueHudWork {
    void* tiles;
    void* palette;
} RogueHudWork;

static const u8 sHits[] = "HIT";

static void RogueHud_Init(RogueHudWork* w) {
    w->tiles = LoadSmallFontTiles();
    w->palette = LoadSmallFontPalette();
    gRogue.combo = 0;
    gRogue.comboTimer = 0;
    gRogue.jumpBuffer = 0;
    gRogue.secondWindUsed = 0;
}

static s32 RogueHud_Update(RogueHudWork* w) {
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
