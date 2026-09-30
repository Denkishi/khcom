#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_sio_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include <string.h>
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "card_reload_assets.h"
#include "map_card_assets.h"
#include "card_localized_assets.h"
#include "card_help_assets.h"
#include "card_message_assets.h"
#include "card_description_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_level_up.h"
#include "evt_types.h"

#ifdef VERSION_EU
extern u8 gUnkEu_0916F992[];
extern u8 gUnkEu_0917063A[];
extern u8 gUnkEu_09170202[];
extern u8 gUnkEu_0916FDCA[];
#endif
extern EventState* gEventState;
void TrackLevelUpEffectTarget(LevelUpEffectWork* w);

void Lvup_Logo_0(LevelUpEffectWork* w, LevelUpEffectArgs* a) {
    w->x[0] = a->x;
    w->targetX = a->x;
    w->y[0] = a->y;
    w->targetY = a->y;
    w->target = a->target;
#ifdef VERSION_EU
    switch (gLanguage) {
    case 0:
        w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
        break;
    case 1:
        w->tiles = LoadObjTiles(gUnkEu_0916F992, 0x3E0);
        break;
    case 2:
        w->tiles = LoadObjTiles(gUnkEu_0917063A, 0x3E0);
        break;
    case 3:
        w->tiles = LoadObjTiles(gUnkEu_09170202, 0x3E0);
        break;
    case 4:
        w->tiles = LoadObjTiles(gUnkEu_0916FDCA, 0x3E0);
        break;
    default:
        w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
        break;
    }
#else
    w->tiles = LoadObjTiles(gUnk_0908C686, 0x3E0);
#endif
    LoadObjPalette(gCard00Palette, 32);
    w->tiles = a->tiles;
    w->palette = a->palette;
    FadeSetPaletteExcluded(a->palette->index + 16, 1);
    w->frame = 0;
    w->timer = 0;
    w->vy[0] = -0x280;
    m4aSongNumStart(SONG_BTL_LVUP);
}

s32 Lvup_Logo_1(LevelUpEffectWork* w) {
    w->y[0] += w->vy[0];
    w->vy[0] += 25;
    TrackLevelUpEffectTarget(w);
    w->x[0] = w->targetX << 8;
    w->timer++;

    if ((s8)w->timer == 60) {
        return 0;
    }

    return 1;
}
void Lvup_Logo_2(LevelUpEffectWork* w) {
    DrawSprite(w->x[0] >> 8, w->y[0] >> 8, gUnk_09EEA19C[w->frame], w->tiles, w->palette, 0, 0, 10);
}
void Lvup_Logo_3(LevelUpEffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gLvupLogoActive = 0;
}

u8 CreateLevelUpEffectTask(BtlObj* p, TaskPool* pool) {
    LevelUpEffectArgs args;

    gLvupLogoActive = 0;

    if (gBtlWork->flags & 0x20000) {
        return 0;
    }

    args.x = p->x;
    args.y = p->y;
    args.unk_08 = 0;
    args.target = p;
    TaskCreate(pool, &gTaskDescLVUPEFFECT, &args);
    gBtlWork->flags |= 0x20000;
    return 1;
}

void LoadEventMapObjectGfx(EventMapObjectWork* w, EventBackgroundDef* t) {
    EventMapObjectDef* q;
    EventMapObjectPlacement* entries;
    u8 i;

    q = t->mapObjects;
    entries = q->placements;

    for (i = 0; i < 10; i++) {
        w->tiles[i] = 0;
        w->palettes[i] = 0;
    }

    for (i = 0; i < q->placementCount; i++) {
        if (w->tiles[entries[i].spriteIndex] == 0) {
            w->tiles[entries[i].spriteIndex] = LoadObjTiles(q->tileResources[entries[i].spriteIndex].data, q->tileResources[entries[i].spriteIndex].size);
            w->palettes[entries[i].spriteIndex] = LoadObjPalette(q->paletteResources[entries[i].spriteIndex].data, q->paletteResources[entries[i].spriteIndex].size);
        }
    }
}

void ReleaseEventMapObjectGfx(EventMapObjectWork* w) {
    u8 i;

    for (i = 0; i <= 9; i++) {
        if (w->tiles[i] != 0) {
            ReleaseObjTiles(w->tiles[i]);
            ReleaseObjPalette(w->palettes[i]);
        }
    }
}
void Ev_mapObj_0(EventMapObjectWork* w, u8* a) {
    EventBackgroundDef* t;

    w->background = a[0];
    t = gEventBackgroundDefs[w->background];

    if (t->mapObjects != 0) {
        LoadEventMapObjectGfx(w, t);
        w->definition = t->mapObjects;
    }
}

u8 Ev_mapObj_1(EventMapObjectWork* w) {
    EventMapObjectDef* p;
    EventMapObjectPlacement* q;
    u8 i;

    p = w->definition;
    q = p->placements;

    for (i = 0; i < p->placementCount; i++) {
        FadeSetPaletteExcluded(w->palettes[q[i].spriteIndex]->index + 16, 0);
    }

    return 1;
}

void Ev_mapObj_2(EventMapObjectWork* w) {
    EventMapObjectDef* q;
    EventMapObjectPlacement* entries;
    EventMapObjectPlacement* e;
    u8 i;

    q = w->definition;
    entries = q->placements;

    for (i = 0; i < q->placementCount; i++) {
        e = &entries[i];
        DrawSprite(e->x - (gEventState->x >> 8), e->y - (gEventState->y >> 8), q->sprites[e->spriteIndex], w->tiles[e->spriteIndex], w->palettes[e->spriteIndex], 0, 0x800, (u16)(-0x1004 - e->y * 4));
    }
}

void Ev_mapObj_3(EventMapObjectWork* w) {
    ReleaseEventMapObjectGfx(w);
}

TaskDesc gTaskDescLvupLogo = {
    "Lvup_Logo",
    (TaskInitFunc)Lvup_Logo_0,
    (TaskUpdateFunc)Lvup_Logo_1,
    (TaskDrawFunc)Lvup_Logo_2,
    (TaskDestroyFunc)Lvup_Logo_3,
    sizeof(LevelUpEffectWork),
};

TaskDesc gTaskDescEvMapObj = {
    "Ev_mapObj",
    (TaskInitFunc)Ev_mapObj_0,
    (TaskUpdateFunc)Ev_mapObj_1,
    (TaskDrawFunc)Ev_mapObj_2,
    (TaskDestroyFunc)Ev_mapObj_3,
    sizeof(EventMapObjectWork),
};

void* gEventBgEffectMaps[7] = { gUnk_0951F2B8, gUnk_0951FAB8, gUnk_095202B8, gUnk_095212B8, gUnk_09520AB8, gUnk_09521AB8, gUnk_095222B8 };
