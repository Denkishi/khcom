#include "rogue.h"
#include "anim.h"
#include "battle.h"
#include "battle_actor.h"
#include "btl_collision.h"
#include "card_def_data.h"
#include "card_ids.h"
#include "fade.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "sprite.h"
#include "sprite_palettes.h"
#include "system_state.h"
#include "taskpool.h"

// Tag attacks: a character card played in a combo swaps Sora out for an
// instant. The character does one move where Sora stands, Sora is not drawn
// meanwhile, and the combo goes on with the next card as if the move had
// been one of his swings.

extern const AnimDef gSmnCloudAnimDefs[], gSmnTinkAnimDefs[], gSmnMushuAnimDefs[], gSmnDumboAnimDefs[], gSmnGenieAnimDefs[],
    gSmnKingAnimDefs[], gSmnBambiAnimDef, gSmnSimbaAnimDef;
extern const AnimDef gFrdDonaldAnimDefs[], gFrdGoofyAnimDefs[], gFrdArielAnimDefs[], gFrdJackAnimDefs[], gFrdPanAnimDefs[],
    gFrdAladdinAnimDefs[], gFrdBeastAnimDefs[];

typedef struct RogueTagDef {
    u8 kind; // card kind that calls the character
    const AnimDef* anims;
    u8* palette;
    u8 smallTiles; // the character's sprite goes in the battle's second tile block
    u8 anim; // index in anims of the move
    u8 hitFrame; // frame of the move its hit lands on
    u8 frames; // frames until Sora is back
    u16 attack; // attack definition of the hit, 0 for a character who heals instead
    u16 scale; // 8.8, of that attack's damage; or the share of max HP healed
    // For the enemies and bosses, called by their enemy cards:
    u16 firstCard; // the card ids that call it
    u16 lastCard;
    u8 tiles; // size of its tile block in tiles, 0 for one that fits Sora's
    u8 fast; // its move plays at twice its speed
} RogueTagDef;

#define ROGUE_TAG_BLOCK 100 // tiles in Sora's block

#include "rogue_tag_enemies.inc"

// The attacks used: 14 is a keyblade finisher (256 a swing), 66 Fire, 69
// Blizzard and 72 Thunder (five, four and three swings at full scale).
static const RogueTagDef sTags[] = {
    // Summons.
    { CARD_SIMBA, &gSmnSimbaAnimDef, gShinbaPalette, 0, 0, 10, 30, 14, 512 },
    { CARD_GENIE, gSmnGenieAnimDefs, gGeniePalette, 0, 1, 10, 30, 72, 160 },
    { CARD_BAMBI, &gSmnBambiAnimDef, gBanbPalette, 1, 0, 10, 26, 0, 26 },
    { CARD_DUMBO, gSmnDumboAnimDefs, gDamboPalette, 0, 0, 10, 30, 69, 120 },
    { CARD_TINKER_BELL, gSmnTinkAnimDefs, gTinkPalette, 1, 0, 10, 26, 0, 51 },
    { CARD_MUSHU, gSmnMushuAnimDefs, gMushuPalette, 1, 2, 10, 30, 66, 100 },
    { CARD_CLOUD, gSmnCloudAnimDefs, gCroudPalette, 0, 1, 8, 28, 14, 640 },
    { CARD_THE_KING, gSmnKingAnimDefs, gMickeyPalette, 0, 1, 10, 30, 14, 768 },
    // The friends whose cards drop in battle.
    { CARD_DONALD_DUCK, gFrdDonaldAnimDefs, gDonaldPalette, 1, 2, 10, 30, 72, 140 },
    { CARD_GOOFY, gFrdGoofyAnimDefs, gGoofyPalette, 1, 4, 10, 30, 14, 512 },
    { CARD_ALADDIN, gFrdAladdinAnimDefs, gAladdinPalette, 1, 2, 10, 30, 14, 512 },
    { CARD_ARIEL, gFrdArielAnimDefs, gArielPalette, 1, 1, 10, 30, 69, 120 },
    { CARD_JACK, gFrdJackAnimDefs, gJackPalette, 1, 3, 10, 30, 66, 100 },
    { CARD_PETER_PAN, gFrdPanAnimDefs, gPeterPalette, 1, 2, 10, 30, 14, 512 },
    { CARD_THE_BEAST, gFrdBeastAnimDefs, gBeastPalette, 1, 1, 10, 30, 14, 768 },
};

typedef struct RogueTagWork {
    const RogueTagDef* def;
    void* palette;
    ObjTiles* tiles;
    void* sheet; // the character's tiles
    void* soraSheet; // what the tile block pointed at before, to give back
    AnimState anim;
    u8 timer;
    u8 own; // the tile block is the character's own, too big for Sora's
    u8 bare; // nobody is drawn: a giant, or no room for the tiles
} RogueTagWork;

static void RogueTag_Init(RogueTagWork* w, const RogueTagDef* def) {
    w->def = def;
    w->timer = 0;
    w->own = 0;
    w->bare = def->anims == 0;

    if (!w->bare && def->tiles > ROGUE_TAG_BLOCK) {
        // A body too big for Sora's block gets one of its own, if there is room.
        if (CanAllocObjTiles(def->tiles) && CanAllocObjPalette(1)) {
            w->own = 1;
        } else {
            w->bare = 1;
        }
    }

    if (w->bare) {
        // Sora stays, in his casting pose, and the ground shakes around him.
        w->palette = 0;
        w->tiles = 0;
        RogueSoraPose(gBtlWork->actor);
        m4aSongNumStart(SONG_EF_SUMMON_UP);
        return;
    }

    w->palette = LoadObjPalette(def->palette, 32);
    AnimInit(&w->anim, 0, 0);

    if (w->own) {
        w->tiles = AllocObjTiles(def->tiles * 32, 0);
        w->soraSheet = 0;
        AnimChangeWithDef(def->anims, &w->anim, def->anim, 0, w->tiles);
        w->sheet = w->tiles->src;
        m4aSongNumStart(SONG_EF_SUMMON_UP);
        gRogue.tagTimer = def->frames;
        return;
    }

    // The summons draw from the very tile block Sora's sprite uses, which is
    // why he cannot be on screen with them. Sora keeps pointing the block at
    // his own sheet whenever his animation changes, so the block is pointed
    // back at the character's every frame and at Sora's when the move ends.
    w->tiles = def->smallTiles ? gBtlWork->tiles2 : gBtlWork->tiles;
    w->soraSheet = w->tiles->src;
    AnimChangeWithDef(def->anims, &w->anim, gRogueDebug.tagAnim != 0 ? gRogueDebug.tagAnim - 1 : def->anim, 0, w->tiles);
    w->sheet = w->tiles->src;
    m4aSongNumStart(SONG_EF_SUMMON_UP);
    gRogue.tagTimer = def->frames;
}

static s32 RogueTag_Update(RogueTagWork* w) {
    BtlObj* sora = gBtlWork->actor;
    u64 flags;
    s32 scale;

    if (w->timer == w->def->hitFrame && w->def->attack == 0) {
        // A character who heals: the scale is the share of max HP, in 1/256.
        sora->unk_02C += (sora->unk_02E * w->def->scale) >> 8;

        if (sora->unk_02C > sora->unk_02E) {
            sora->unk_02C = sora->unk_02E;
        }

        gRogueDebug.tagHits++;
    } else if (w->timer == w->def->hitFrame) {
        // The hit is Sora's, a strong one that launches like a finisher.
        flags = gBtlWork->flags;
        scale = gBtlWork->unk_124;
        gBtlWork->flags |= 0x20000000;
        gBtlWork->unk_124 = w->def->scale;
        gRogue.finisher = 1;
        gRogue.echoing = 1;

        if (w->def->anims == 0) {
            // A giant's card: everything around Sora is hit.
            FadeFromAmount(2, 12, 16);

            if (func_08011F78(w->def->attack, sora->x, sora->y, sora->z, 120, 60, 80)) {
                gRogueDebug.tagHits++;
            }
        } else if (func_08011F78(w->def->attack, (sora->flags & 4) ? sora->x - 9216 : sora->x + 9216, sora->y, sora->z, 28, 16,
                                 40)) {
            gRogueDebug.tagHits++;
        }

        gRogue.echoing = 0;
        gRogue.finisher = 0;
        gBtlWork->unk_124 = scale;
        gBtlWork->flags = (gBtlWork->flags & ~0x20000000ULL) | (flags & 0x20000000);
    }

    w->timer++;

    if (w->bare) {
        return w->timer < w->def->frames;
    }

    if (!w->own && w->tiles->src != w->sheet) {
        w->soraSheet = w->tiles->src;
        SetObjTileSource(w->tiles, w->sheet);
    }

    AnimUpdate(&w->anim);

    if (w->def->fast) {
        AnimUpdate(&w->anim);
    }

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

    if (w->bare) {
        return;
    }

    // The sheets face left: flipped when Sora faces right.
    if (!(sora->flags & 4)) {
        attr |= 1;
    }

    WorldToScreen(&x, &y, sora->x, sora->y, sora->z);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, attr, -0x1004 - (sora->y >> 8) * 4);
}

static void RogueTag_Destroy(RogueTagWork* w) {
    if (w->bare) {
        return;
    }

    if (w->own) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        gRogue.tagTimer = 0;
        return;
    }

    SetObjTileSource(w->tiles, w->soraSheet);
    w->tiles->sprite = 0;
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

// Called when an enemy card is played: its enemy or boss comes in and does
// its attack, on top of what the card does on its own.
void RogueOnEnemyCard(const CardDef* def) {
    u16 id = def - gCardDefs;
    u32 i;

    if (gRogue.tagTimer != 0) {
        return;
    }

    for (i = 0; i < sizeof(sEnemyTags) / sizeof(sEnemyTags[0]); i++) {
        if (id >= sEnemyTags[i].firstCard && id <= sEnemyTags[i].lastCard) {
            TaskCreate(&gBtlWork->taskPools[0], &sTaskDescRogueTag, (void*)&sEnemyTags[i]);
            gRogueDebug.enemyTags++;
            return;
        }
    }
}
