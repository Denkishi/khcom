#include "rogue.h"
#include "anim.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl_collision.h"
#include "card_ids.h"
#include "m4a_song.h"
#include "obj_api.h"
#include "sprite.h"
#include "sprite_palettes.h"
#include "sprites_cloud.h"
#include "system_state.h"
#include "taskpool.h"

// Tag attacks: a character card played in a combo swaps Sora out for an
// instant. The character does one move where Sora stands, Sora is not drawn
// meanwhile, and the combo goes on with the next card as if the move had
// been one of his swings.

extern const AnimDef gSmnCloudAnimDefs[8];

typedef struct RogueTagDef {
    u8 kind; // card kind that calls the character
    const AnimDef* anims;
    u8* palette;
    u8 anim; // index in anims of the move
    u8 hitFrame; // frame of the move its hit lands on
    u8 frames; // frames until Sora is back
    u16 attack; // attack definition of the hit
    u16 scale; // 8.8, of that attack's damage
    u16 voice; // sound played when the character comes in
} RogueTagDef;

static const RogueTagDef sTags[] = {
    // Cloud: a rising slash that launches.
    { CARD_CLOUD, gSmnCloudAnimDefs, gCroudPalette, ROGUE_TAG_CLOUD_ANIM, 8, 28, 14, 640, SONG_EF_SUMMON_UP },
};

typedef struct RogueTagWork {
    const RogueTagDef* def;
    void* palette;
    AnimState anim;
    u8 timer;
} RogueTagWork;

static void RogueTag_Init(RogueTagWork* w, const RogueTagDef* def) {
    w->def = def;
    w->timer = 0;
    w->palette = LoadObjPalette(def->palette, 32);
    AnimInit(&w->anim, 0, 0);
    AnimChangeWithDef(def->anims, &w->anim, gRogueDebug.tagAnim != 0 ? gRogueDebug.tagAnim - 1 : def->anim, 0, gBtlWork->tiles);
    m4aSongNumStart(def->voice);
    gRogue.tagTimer = def->frames;
}

static s32 RogueTag_Update(RogueTagWork* w) {
    BtlObj* sora = gBtlWork->actor;
    u64 flags;
    s32 scale;

    if (w->timer == w->def->hitFrame) {
        // The hit is Sora's, a strong one that launches like a finisher.
        flags = gBtlWork->flags;
        scale = gBtlWork->unk_124;
        gBtlWork->flags |= 0x20000000;
        gBtlWork->unk_124 = w->def->scale;
        gRogue.finisher = 1;
        gRogue.echoing = 1;

        if (func_08011F78(w->def->attack, (sora->flags & 4) ? sora->x - 9216 : sora->x + 9216, sora->y, sora->z, 28, 16, 40)) {
            gRogueDebug.tagHits++;
        }

        gRogue.echoing = 0;
        gRogue.finisher = 0;
        gBtlWork->unk_124 = scale;
        gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
    }

    AnimUpdate(&w->anim);
    w->timer++;

    if (gRogue.tagTimer != 0) {
        gRogue.tagTimer--;
    }

    return gRogue.tagTimer != 0;
}

static void RogueTag_Draw(RogueTagWork* w) {
    BtlObj* sora = gBtlWork->actor;
    u16 attr = GetBattleSpritePriorityFlags(sora->y);
    s16 x;
    s16 y;

    // The sheets face left: flipped when Sora faces right.
    if (!(sora->flags & 4)) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, sora->x, sora->y, sora->z);
    DrawSprite(x, y, AnimGetGfx(&w->anim), gBtlWork->tiles, w->palette, 0, attr, -0x1004 - (sora->y >> 8) * 4);
}

static void RogueTag_Destroy(RogueTagWork* w) {
    ReleaseObjPalette(w->palette);
    gRogue.tagTimer = 0;
}

static TaskDesc sTaskDescRogueTag = {
    "task_rogue_tag",
    (TaskInitFunc)RogueTag_Init,
    (TaskUpdateFunc)RogueTag_Update,
    (TaskDrawFunc)RogueTag_Draw,
    (TaskDestroyFunc)RogueTag_Destroy,
    sizeof(RogueTagWork),
};

// Called when a card of this kind is played alone. Returns 1 if it is a tag
// card: the character comes in, and the caller plays the card as a swing.
u8 RogueTagIn(u16 kind) {
    u32 i;

    if (gRogue.tagTimer != 0) {
        return 0;
    }

    for (i = 0; i < sizeof(sTags) / sizeof(sTags[0]); i++) {
        if (sTags[i].kind == kind) {
            TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueTag, (void*)&sTags[i]);
            return 1;
        }
    }

    return 0;
}
