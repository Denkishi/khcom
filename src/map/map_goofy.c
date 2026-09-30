#include "map_text_assets.h"
#include "monsgage.h"
#include "map_resource_assets.h"
#include "map_tasks.h"
#include "sprites_btl.h"
#include "sprites_emy.h"
#include "sprites_evt.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "sprite_palettes.h"
#include "battle_backgrounds.h"
#include "gba/keys.h"
#include "fade.h"
#include "songs.h"
#include "engine_math.h"
#include "common_text.h"

extern MapNameText* gFloorNames[13];
extern MapNameText* gBasementFloorNames[12];

void MapGoofyCheckTalk(MapGoofyWork* w) {
    if (w->targeted != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;

        if ((s8)gGameState.floor == 12 && gMapFloorState.room == 0xFD) {
            CreateCardMessageTask(&w->tasks, 0, 49);
        } else {
            CreateCardMessageTask(&w->tasks, 0, gGoofyTalkMessages[gMapFloorState.progress]);
        }

        w->update = MapGoofyWaitMessage;
    }
}

void MapGoofyWaitMessage(MapGoofyWork* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~0x1000;
        w->update = MapGoofyCheckTalk;
    }
}

void Task_MapGoofy_0(MapGoofyWork* w) {
    FldObj* e = &w->obj;

    if (gMapFloorState.room != 0xFE) {
        if ((s8)gGameState.floor == 12) {
            w->obj.fieldPosition.x = 0x25000;
            w->obj.fieldPosition.y = 0x10A00;
        } else {
            w->obj.fieldPosition.x = 0x20000;
            w->obj.fieldPosition.y = 0xB000;
        }
    } else {
        if ((s8)gGameState.floor != 0) {
            w->obj.fieldPosition.x = 0x1E800;
            w->obj.fieldPosition.y = 0xD000;
        } else {
            w->obj.fieldPosition.x = 0x2C000;
            w->obj.fieldPosition.y = 0xE000;
        }
    }

    e->fieldPosition.z = 0;
    e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.z = e->fieldPosition.ground;
    e->fieldPosition.y -= e->fieldPosition.ground;
    e->angle = 0x80;
    e->height = 0x30;
    e->kind = 2;
    w->visible = 1;
    w->update = MapGoofyCheckTalk;
    w->tiles = AllocObjTiles(0x400, gGoofyFl00Tiles);
    w->palette = LoadObjPalette(gGoofyPalette, 32);
    AnimInit(&w->anim, gGoofyFl00Anims, gGoofyFl00Frames);
    AnimStart(&w->anim, 0, 1);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
}

s32 Task_MapGoofy_1(MapGoofyWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        w->visible = 0;
    } else {
        w->visible = 1;
        w->targeted = IsFldObjTalkTarget(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        AnimUpdate(&w->anim);

        if (w->update != NULL) {
            w->update(w);
        }
    }

    return 1;
}

void Task_MapGoofy_2(MapGoofyWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (w->visible != 0) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, v);
        w->obj.shadowZ = p->ground;
        w->obj.shadowPriority = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->targeted != 0) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapGoofy_3(MapGoofyWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

void MapNamineCheckTalk(MapNamineWork* w) {
    if (w->targeted != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;

        if (gMapFloorState.progress == 27) {
            CreateCardMessageTask(&w->tasks, 0, 0x33);
        } else {
            CreateCardMessageTask(&w->tasks, 0, 0x32);
        }
        w->update = MapNamineWaitMessage;
    }
}

void MapNamineWaitMessage(MapNamineWork* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~0x1000;
        w->update = MapNamineCheckTalk;
    }
}

void Task_MapNamine_0(MapNamineWork* w) {
    FldObj* p = &w->obj;

    switch (gMapFloorState.progress) {
    case 27:
        w->obj.fieldPosition.x = 0x20D00;
        w->obj.fieldPosition.y = 0xD500;
        w->spriteFlags = 0x800;
        break;
    case 23:
        w->obj.fieldPosition.x = 0x27C00;
        w->obj.fieldPosition.y = 0xD400;
        w->spriteFlags = 0x800;
        break;
    case 24:
    case 25:
    case 26:
    default:
        p->fieldPosition.x = 0x15200;
        p->fieldPosition.y = 0xF800;
        w->spriteFlags = 0x801;
        break;
    }

    p->fieldPosition.z = 0;
    p->fieldPosition.z = p->fieldPosition.ground = GetFldPosFloor(&p->fieldPosition);
    p->fieldPosition.y -= p->fieldPosition.ground;
    p->angle = 173;
    p->height = 48;
    p->kind = 2;
    w->registered = gMapFloorState.progress != 23;
    w->visible = 1;
    w->update = MapNamineCheckTalk;
    w->tiles = AllocObjTiles(0x300, gNamiF00Tiles);
    w->palette = LoadObjPalette(gNaminePalette, 32);
    AnimInit(&w->anim, gNamiF00Anims, gNamiF00Frames);
    AnimStart(&w->anim, 0, 1);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, p->fieldPosition.x, p->fieldPosition.y, p->fieldPosition.z);

    if (w->registered != 0) {
        FldObjRegister(p);
    }

    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
}

s32 Task_MapNamine_1(MapNamineWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        w->visible = 0;
    } else {
        w->visible = 1;
        w->targeted = IsFldObjTalkTarget(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        AnimUpdate(&w->anim);

        if (w->update != NULL) {
            w->update(w);
        }
    }

    return 1;
}

void Task_MapNamine_2(MapNamineWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (w->visible != 0) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, w->spriteFlags, v);
        w->obj.shadowZ = p->ground;
        w->obj.shadowPriority = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->targeted != 0) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapNamine_3(MapNamineWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);

    if (w->registered != 0) {
        FldObjUnregister(&w->obj);
    }

    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

void MapNiserikuCheckTalk(MapNiserikuWork* w) {
    if (w->targeted != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;
        CreateCardMessageTask(&w->tasks, 0, 0x34);
        w->update = MapNiserikuWaitMessage;
    }
}

void MapNiserikuWaitMessage(MapNiserikuWork* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~0x1000;
        w->update = MapNiserikuCheckTalk;
    }
}

void MapNiserikuWaitApproach(MapNiserikuWork* w) {
    s32 dx;
    s32 dy;

    dx = w->obj.fieldPosition.x - gFieldState->actor.fieldPosition.x;

    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - w->obj.fieldPosition.x;
    }

    dy = w->obj.fieldPosition.y - gFieldState->actor.fieldPosition.y;

    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - w->obj.fieldPosition.y;
    }

    if (dx <= 0x8000 && dy <= 0x8000) {
        if (Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < 0x3000) {
            FadeStartOut(0, 16);
            gFieldState->flags |= 0x1000;
            w->update = MapNiserikuStartEvent;
        }
    }
}

void MapNiserikuStartEvent(MapNiserikuWork* w) {
    if (FadeIsActive() == 0) {
        RequestEventMode(0x3B);
        w->update = 0;
    }
}

void Task_MapNiseriku_0(MapNiserikuWork* w) {
    FldObj* e = &w->obj;
    s32 c;

    switch (gMapFloorState.progress) {
    case 27:
        e->fieldPosition.x = 0x27C00;
        e->fieldPosition.y = 0x10700;
        break;
    case 23:
        e->fieldPosition.x = 0x24900;
        e->fieldPosition.y = 0xD500;
        break;
    case 24:
    case 25:
    case 26:
    default:
        e->fieldPosition.x = 0x17A00;
        e->fieldPosition.y = 0x11000;
        break;
    }

    e->fieldPosition.z = 0;
    e->fieldPosition.z = e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.y -= e->fieldPosition.z;
    e->angle = 173;
    e->height = 48;
    e->kind = 2;

    c = 0;

    if (gMapFloorState.progress == 27) {
        c = 1;
    }

    w->registered = c;

    w->visible = 1;
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
    TaskPoolInit(&w->tasks, 2);

    switch (gMapFloorState.progress) {
    case 27:
        w->update = MapNiserikuCheckTalk;
        w->tiles = AllocObjTiles(0x680, gNiseFl00Tiles);
        w->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&w->anim, gNiseFl00Anims, gNiseFl00Frames);
        AnimStart(&w->anim, 0, 1);
        ColliderInit(&w->collider, 4, 16, 48);
        ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
        break;
    case 23:
        w->update = MapNiserikuWaitApproach;
        w->tiles = AllocObjTiles(0x320, gNiserikuHizaFTiles);
        w->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&w->anim, gNiserikuHizaFAnims, gNiserikuHizaFFrames);
        AnimStart(&w->anim, 0, 1);
        ColliderInit(&w->collider, 4, 16, 48);
        ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
        break;
    case 24:
    case 25:
    case 26:
    default:
        w->update = 0;
        w->tiles = AllocObjTiles(0x300, gNiserikuDownFTiles);
        w->palette = LoadObjPalette(gNiserikuPalette, 32);
        AnimInit(&w->anim, gNiserikuDownFAnims, gNiserikuDownFFrames);
        AnimStart(&w->anim, 1, 1);
        ColliderInit(&w->collider, 4, 36, 48);
        ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
        break;
    }

    if (w->registered != 0) {
        FldObjRegister(e);
    }
}

s32 Task_MapNiseriku_1(MapNiserikuWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        w->visible = 0;
    } else {
        w->visible = 1;
        w->targeted = IsFldObjTalkTarget(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        AnimUpdate(&w->anim);

        if (w->update != NULL) {
            w->update(w);
        }
    }

    return 1;
}

void Task_MapNiseriku_2(MapNiserikuWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (w->visible != 0) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, v);
        w->obj.shadowZ = p->ground;
        w->obj.shadowPriority = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->targeted != 0) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapNiseriku_3(MapNiserikuWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);

    if (w->registered != 0) {
        FldObjUnregister(&w->obj);
    }

    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

void MapMickeyCheckTalk(MapMickeyWork* w) {
    if (w->targeted != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;

        switch (gMapFloorState.progress) {
        case 20:
            CreateCardMessageTask(&w->tasks, 0, 0x3F);
            break;
        case 22:
            CreateCardMessageTask(&w->tasks, 0, 0x3D);
            break;
        case 23:
        default:
            CreateCardMessageTask(&w->tasks, 0, 0x3E);
            break;
        }

        w->update = MapMickeyWaitMessage;
    }
}

void MapMickeyWaitMessage(MapMickeyWork* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~0x1000;
        w->update = MapMickeyCheckTalk;
    }
}

void Task_MapMickey_0(MapMickeyWork* w) {
    FldObj* e = &w->obj;

    e->fieldPosition.x = 0x1C800;
    e->fieldPosition.y = 0xE000;
    w->spriteFlags = 0x801;
    e->fieldPosition.z = 0;
    e->fieldPosition.ground = GetFldPosFloor(&e->fieldPosition);
    e->fieldPosition.z = e->fieldPosition.ground;
    e->fieldPosition.y -= e->fieldPosition.ground;
    e->angle = 0xAD;
    e->height = 0x30;
    e->kind = 2;
    w->visible = 1;
    w->update = MapMickeyCheckTalk;
    w->tiles = AllocObjTiles(0x300, gMickeyFl00Tiles);
    w->palette = LoadObjPalette(gMickeyPalette, 32);
    AnimInit(&w->anim, gMickeyFl00Anims, gMickeyFl00Frames);
    AnimStart(&w->anim, 0, 1);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->targeted = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, &w->obj);
}

s32 Task_MapMickey_1(MapMickeyWork* w) {
    if ((u8)IsMapInterrupted() != 0) {
        w->visible = 0;
    } else {
        w->visible = 1;
        w->targeted = IsFldObjTalkTarget(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        AnimUpdate(&w->anim);

        if (w->update != NULL) {
            w->update(w);
        }
    }

    return 1;
}

void Task_MapMickey_2(MapMickeyWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    if (w->visible != 0) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        k = p->y >> 8;
        y = k + (p->z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, w->spriteFlags, v);
        w->obj.shadowZ = p->ground;
        w->obj.shadowPriority = v + 1;
        TaskPoolDraw(&w->tasks);

        if (w->targeted != 0) {
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapMickey_3(MapMickeyWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

void MapTutorialStartBattle(void) {
    gFieldState->flags |= 0x80;
    gMapRoomState->battleId = 10;
    gMapRoomState->flags &= ~0x4000;
    gMapRoomState->flags |= 2;
}

void MapTutorialWaitStart(MapTutorialWork* w) {
    u32 flags;

    if (gFieldState->lockonTarget == NULL) {
        flags = gFieldState->flags;

        if (!(flags & 0x2000) && !(gMapRoomState->flags & 0x2000) && (gGameState.progression.unk_82 & 0x10)) {
            gMapRoomState->flags |= 0x4000;
            gFieldState->flags = flags | 0x1000;
            CreateCardMessageTask(&w->tasks, 0, 0x6A);
            w->update = MapTutorialDropBarrel;
        }
    }
}

void MapTutorialDropBarrel(MapTutorialWork* w) {
    if (IsMessageWindowOpen() == 0) {
        AnimState* a;

        MapPickFreeFloorPosInView(&w->obj.fieldPosition, &w->obj.fieldPosition.y);
        w->obj.fieldPosition.z = 0;
        w->obj.fieldPosition.ground = GetFldPosFloor(&w->obj.fieldPosition);
        w->obj.fieldPosition.y -= w->obj.fieldPosition.ground;
        w->obj.fieldPosition.z = w->obj.fieldPosition.ground - 0xA000;
        w->obj.height = 24;
        w->obj.speed = 2;
        w->tiles = AllocObjTiles(0x400, gUnk_09858B3C);
        w->palette = LoadObjPalette(gUnk_099912E4, 32);
        a = &w->anim;
        AnimInit(a, gUnk_09EF8460, gUnk_09EF8424);
        AnimStart(a, 0, 1);
        w->gfx = AnimGetGfx(a);
        ColliderInit(&w->collider, 6, 12, 24);
        ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
        w->shadowVisible = 1;
        TaskCreate(&w->tasks2, &gTaskDescFldShadow, &w->obj);
        w->visible = 1;
        w->update = MapTutorialBarrelFall;
    }
}

void MapTutorialBarrelFall(MapTutorialWork* w) {
    MapTutorialWork* p = w;

    w->obj.speed += 0x38;
    w->obj.fieldPosition.z += w->obj.speed;

    if (w->obj.fieldPosition.z > w->obj.fieldPosition.ground) {
        gFieldState->flags &= ~0x1000;
        m4aSongNumStart(SONG_SND_215);
        w->obj.fieldPosition.z = w->obj.fieldPosition.ground;
        w->obj.speed = 0;
        w->shadowVisible = 0;
        w->update = MapTutorialWaitBarrelHit;
    }
    ColliderSetPosition(&p->collider, p->obj.fieldPosition.x, p->obj.fieldPosition.y, p->obj.fieldPosition.z);
}

void MapTutorialWaitBarrelHit(MapTutorialWork* w) {
    if (IsHitByMapAttack(&w->obj.fieldPosition, 8, 8)) {
        m4aSongNumStart(SONG_SYS_OBJ_BREAK);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, &w->obj);
        gMapRoomState->flags &= ~0x20;
        TryCreateRandomPrzCard(0, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
        AnimStart(&w->anim, 1, 0);
        w->update = MapTutorialBarrelBreak;
        ColliderUnregister(&w->collider);
    }
}

void MapTutorialBarrelBreak(MapTutorialWork* w) {
    if (AnimIsFinished(&w->anim)) {
        w->update = MapTutorialWaitPrizeCard;
    } else {
        w->gfx = AnimUpdate(&w->anim);
    }
}

void MapTutorialWaitPrizeCard(MapTutorialWork* w) {
    if ((gMapRoomState->flags & 0x10) == 0) {
        gGameState.progression.unk_82 |= 0x2000;
        gFieldState->flags |= 0x1000;
        CreateCardMessageTask(&w->tasks, 0, 0x6B);
        w->update = MapTutorialSpawnEnemy;
    }
}

void MapTutorialSpawnEnemy(MapTutorialWork* w) {
    if (IsMessageWindowOpen() == 0) {
        AnimState* a;
        u8 v;

        MapPickFreeFloorPosInView(&w->obj.fieldPosition, &w->obj.fieldPosition.y);
        w->obj.fieldPosition.z = 0;
        w->obj.fieldPosition.ground = GetFldPosFloor(&w->obj.fieldPosition);
        w->obj.fieldPosition.y -= w->obj.fieldPosition.ground;
        w->obj.fieldPosition.z = w->obj.fieldPosition.ground;
        w->obj.height = 16;
        v = 0;

        if (gFieldState->actor.fieldPosition.x > w->obj.fieldPosition.x) {
            v = 1;
        }
        w->flip = v;
        w->tiles = AllocObjTiles(0x400, gEmy00L06Tiles);
        w->palette = LoadObjPalette(gEmy00Palette, 32);
        a = &w->anim;
        AnimInit(a, gEmy00L06Anims, gEmy00L06Frames);
        AnimStart(a, 0, 1);
        w->gfx = AnimGetGfx(a);
        ColliderInit(&w->collider, 3, 8, 16);
        ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
        ColliderSetDisabled(&w->collider, 1);
        w->update = MapTutorialEnemyAppear;
    }
}

void MapTutorialEnemyAppear(MapTutorialWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        AnimChangeWithTables(a, 0, 1, gEmy00L00Anims, gEmy00L00Frames);
        SetObjTileSource(w->tiles, gEmy00L00Tiles);
        CreateCardMessageTask(&w->tasks, 0, 0x6C);
        w->update = MapTutorialWaitEnemyMessage;
    } else {
        w->gfx = AnimUpdate(a);
    }
}

void MapTutorialWaitEnemyMessage(MapTutorialWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~0x1000;
        ColliderSetDisabled(&w->collider, 0);
        w->update = MapTutorialEnemyUpdate;
    }
}

void MapTutorialEnemyUpdate(MapTutorialWork* w) {
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if (IsHitByMapAttack(&w->obj.fieldPosition, 8, 16)) {
        gMapRoomState->flags |= 0x80;
        gMapRoomState->flags |= 4;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, &w->obj);
        m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        AnimChangeWithTables(a, 0, 1, gEmy00L09Anims, gEmy00L09Frames);
        SetObjTileSource(w->tiles, gEmy00L09Tiles);
        w->update = MapTutorialEnemyHit;
    } else if (w->collider.colliding != 0) {
        if (!(gMapRoomState->flags & 4) && w->collider.otherType == 1) {
            ColliderSetDisabled(&w->collider, 1);
            MapTutorialStartBattle();
        } else {
            w->obj.fieldPosition.x += w->collider.pushX;
            w->obj.fieldPosition.y += w->collider.pushY;
        }
    }
}

void MapTutorialEnemyHit(MapTutorialWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        ColliderSetDisabled(&w->collider, 1);
        gGameState.flags |= 4;
        MapTutorialStartBattle();
    } else {
        w->gfx = AnimUpdate(a);
    }
}

void Task_MapTutorial_0(MapTutorialWork* w) {
    u16 t;

    TaskPoolInit(&w->tasks, 1);
    TaskPoolInit(&w->tasks2, 1);
    gMapRoomState->flags |= 0x20;
    w->tiles = 0;
    w->palette = 0;
    w->flip = 0;
    t = gGameState.progression.unk_82 & 0x2000;

    if (t == 0) {
        w->shadowVisible = 0;
        w->visible = 0;
        w->update = MapTutorialWaitStart;
    } else {
        gFieldState->flags |= 0x1000;
        TaskCreate(&w->tasks2, &gTaskDescFldShadow, &w->obj);
        w->visible = 1;
        w->shadowVisible = 1;
        w->update = MapTutorialSpawnEnemy;
    }
}

s32 Task_MapTutorial_1(MapTutorialWork* w) {
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);

    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }
    return 0;
}

void Task_MapTutorial_2(MapTutorialWork* w) {
    u16 flags;
    u16 v;
    s32 k;
    s32 t;
    s16 x;
    s16 y;

    TaskPoolDraw(&w->tasks);

    if (w->visible != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        t = w->flip;
        flags = 0x800;

        if (t != 0) {
            flags = 0x801;
        }
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, flags, v);

        if (w->shadowVisible != 0) {
            w->obj.shadowZ = w->obj.fieldPosition.ground;
            w->obj.shadowPriority = v + 1;
            TaskPoolDraw(&w->tasks2);
        }
    }
}

void Task_MapTutorial_3(MapTutorialWork* w) {
    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

s32 IsPlayerWithin(FldPos* p, s32 lim) {
    s32 dx;
    s32 dy;

    dx = p->x - gFieldState->actor.fieldPosition.x;
    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - p->x;
    }
    dy = p->y - gFieldState->actor.fieldPosition.y;
    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - p->y;
    }

    if (dx > 0x8000 || dy > 0x8000) {
        return 0;
    }
    return Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < lim ? 1 : 0;
}

void func_080F74E8(MapStairWork* w) {
    if ((u8)IsPlayerWithin(&w->obj.fieldPosition, 0x800) != 0) {
        if (gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
            if (gMapFloorState.room == 0xFE) {
                gMapRoomState->flags |= 0x100;
            } else {
                gMapRoomState->flags |= 0x400;
            }
        }
    }
}

void func_080F753C(MapStairWork* w) {
    s32 k = 0x800;

    if ((u8)IsPlayerWithin(&w->obj.fieldPosition, k) != 0) {
        if (gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.ground) {
            if (gMapFloorState.room == 0xFE) {
                gMapRoomState->flags |= k;
            } else {
                gMapRoomState->flags |= 0x200;
            }
        }
    }
}

void MapStairWaitApproach(MapStairWork* w) {
    if ((u8)IsPlayerWithin(&w->obj.fieldPosition, 0x3000) != 0) {
        gFieldState->flags |= 0x1000;
        gMapRoomState->flags |= 0x4000;
        CreateCardMessageTask(&w->tasks, 0, 0xA7);
        w->update = MapStairWaitMessage;
    }
}

void MapStairWaitMessage(MapStairWork* w) {
    if (IsMessageWindowOpen() == 0) {
        gFieldState->flags &= ~0x1000;
        gMapRoomState->flags &= ~0x4000;
        gGameState.progression.unk_82 |= 0x400;
        w->update = func_080F74E8;
    }
}

void Task_MapStair_0(MapStairWork* w, FldObj* arg) {
    s32 y;

    w->obj.angle = arg->angle;
    w->obj.fieldPosition.x = arg->fieldPosition.x;
    y = arg->fieldPosition.y;
    w->obj.fieldPosition.ground = 0;
    w->obj.fieldPosition.z = 0;
    w->obj.fieldPosition.y = y;
    w->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    w->tiles = LoadObjTiles(gUnk_08B1EA00, 0xE0);
    w->visible = 0;

    switch (w->obj.angle) {
    case 0x2D:
        if ((gGameState.progression.unk_82 & 0x400) == 0 && gMapFloorState.room == 0xFD) {
            w->update = MapStairWaitApproach;
        } else {
            w->update = func_080F74E8;
        }
        break;
    case 0xAD:
        w->update = func_080F753C;
        break;
    }
    TaskPoolInit(&w->tasks, 1);
}

s32 Task_MapStair_1(MapStairWork* w) {
    TaskPoolUpdate(&w->tasks);

    if (w->update != NULL) {
        w->update(w);
    }
    return 1;
}

void Task_MapStair_2(MapStairWork* w) {
    s32 x;
    s32 y;

    TaskPoolDraw(&w->tasks);

    if (w->visible == 1) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        y = (w->obj.fieldPosition.y >> 8) + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        DrawSprite(x, y, gUnk_08B1E9A6, w->tiles, w->palette, 0, 0x800, 0x101);
    }
}

void Task_MapStair_3(MapStairWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    TaskPoolDestroy(&w->tasks);
}

void Task_MapFaint_0(MapFaintWork* w, FldObj* obj) {
    w->obj = obj;
    w->tiles = AllocObjTiles(0x80, gUnk_08B21ACE);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    AnimInit(&w->anim, gUnk_09EE12E4, gUnk_09EE12D4);
    AnimStart(&w->anim, 0, 1);
}

s32 Task_MapFaint_1(MapFaintWork* w) {
    AnimUpdate(&w->anim);
    return 1;
}

void Task_MapFaint_2(MapFaintWork* w) {
    FldObj* e = w->obj;
    u16 x;
    u16 y;

    x = (e->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (e->fieldPosition.y >> 8) + ((e->fieldPosition.z - ((s16)e->height + 8) * 0x100) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, -0x1005 - (e->fieldPosition.y >> 8) * 4);
}

void Task_MapFaint_3(MapFaintWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void Task_MapDmg_0(MapDmgWork* w) {
    s32 z = 0;

    w->visible = z;
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    w->tiles = LoadObjTiles(gUnk_08B1EA00, 224);
    w->timer = z;
    w->enabled = 1;
}

s32 Task_MapDmg_1(MapDmgWork* w) {
    if (w->enabled == 0) {
        w->visible = 0;
    } else {
        if (gMapRoomState->attackActive != 0 || (gMapRoomState->flags & 4)) {
            w->timer = 20;
        }

        w->visible = w->timer != 0;

        if (w->timer != 0) {
            w->timer -= 1;
        }
    }
    return 1;
}

void Task_MapDmg_2(MapDmgWork* w) {
    s16 x;
    s16 y;

    if (w->visible == 0) {
        return;
    }

    x = ((gMapRoomState->attackX - 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY - 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E974, w->tiles, w->palette, 0, 0x800, 0x101);

    x = ((gMapRoomState->attackX + 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY - 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E97E, w->tiles, w->palette, 0, 0x800, 0x101);

    x = ((gMapRoomState->attackX - 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY + 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E992, w->tiles, w->palette, 0, 0x800, 0x101);

    x = ((gMapRoomState->attackX + 0x1400) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY + 0x1400) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E988, w->tiles, w->palette, 0, 0x800, 0x101);

    x = ((gMapRoomState->attackX) >> 8) - (gFieldState->x >> 8);
    y = ((gMapRoomState->attackY) >> 8) + (gMapRoomState->attackZ >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, gUnk_08B1E9A6, w->tiles, w->palette, 0, 0x800, 0x101);
}

void Task_MapDmg_3(MapDmgWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void* GetFloorName(void) {
#ifdef VERSION_EU
    if (gGameState.flags & 8) {
        return eu_0805E924(gBasementFloorNames[(s8)gGameState.floor]);
    }
    return eu_0805E924(gFloorNames[(s8)gGameState.floor]);
#else
    if (gGameState.flags & 8) {
        return gBasementFloorNames[(s8)gGameState.floor];
    }
    return gFloorNames[(s8)gGameState.floor];
#endif
}

void Task_MapFloor_0(MapFloorWork* w) {
    gFieldState->flags |= 0x1000;
    gFieldState->flags |= 0x80;
    w->tiles = LoadObjTiles(gUnk_0993AF64, 0x800);
    w->palette = LoadObjPalette(gUnk_099910C4, 32);
    w->gfx = gUnk_09EF8DA4[0];
    w->timer = 120;
#ifdef VERSION_EU
    InitTextSlots(w->textSlots, 60);
#else
    InitTextSlots(w->textSlots, 40);
#endif
    w->palette2 = LoadTextPalette(1);
    w->textSlotCount = LoadTextSlots(GetFloorName(), w->textSlots);
    w->textX = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
}

s32 Task_MapFloor_1(MapFloorWork* w) {
    u16* p = &w->timer;

    if (*p != 0) {
        (*p)--;
        return 1;
    }
    return 0;
}

void Task_MapFloor_2(MapFloorWork* w) {
    DrawSprite(120, 138, w->gfx, w->tiles, w->palette, 0, 0, 0x3C);
    DrawTextSlots(w->textX, 0x85, w->textSlots, w->palette2, 50, w->textSlotCount);
}

void Task_MapFloor_3(MapFloorWork* w) {
    ReleaseObjPalette(w->palette);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette2);
#ifdef VERSION_EU
    FreeTextSlots(w->textSlots, 60);
#else
    FreeTextSlots(w->textSlots, 40);
#endif
    gFieldState->flags &= ~0x80;
    gFieldState->flags &= ~0x1000;
}

const u8 gGoofyTalkMessages[28] = {
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 46, 46, 47, 47, 48, 48,
};

TaskDesc gTaskDescMapGoofy = {
    "Task_MapGoofy",
    (TaskInitFunc)Task_MapGoofy_0,
    (TaskUpdateFunc)Task_MapGoofy_1,
    (TaskDrawFunc)Task_MapGoofy_2,
    (TaskDestroyFunc)Task_MapGoofy_3,
    sizeof(MapGoofyWork),
};

TaskDesc gTaskDescMapNamine = {
    "Task_MapNamine",
    (TaskInitFunc)Task_MapNamine_0,
    (TaskUpdateFunc)Task_MapNamine_1,
    (TaskDrawFunc)Task_MapNamine_2,
    (TaskDestroyFunc)Task_MapNamine_3,
    sizeof(MapNamineWork),
};

TaskDesc gTaskDescMapNiseriku = {
    "Task_MapNiseriku",
    (TaskInitFunc)Task_MapNiseriku_0,
    (TaskUpdateFunc)Task_MapNiseriku_1,
    (TaskDrawFunc)Task_MapNiseriku_2,
    (TaskDestroyFunc)Task_MapNiseriku_3,
    sizeof(MapNiserikuWork),
};

TaskDesc gTaskDescMapMickey = {
    "Task_MapMickey",
    (TaskInitFunc)Task_MapMickey_0,
    (TaskUpdateFunc)Task_MapMickey_1,
    (TaskDrawFunc)Task_MapMickey_2,
    (TaskDestroyFunc)Task_MapMickey_3,
    sizeof(MapMickeyWork),
};

TaskDesc gTaskDescMapTutorial = {
    "Task_MapTutorial",
    (TaskInitFunc)Task_MapTutorial_0,
    (TaskUpdateFunc)Task_MapTutorial_1,
    (TaskDrawFunc)Task_MapTutorial_2,
    (TaskDestroyFunc)Task_MapTutorial_3,
    sizeof(MapTutorialWork),
};

TaskDesc gTaskDescMapStair = {
    "Task_MapStair",
    (TaskInitFunc)Task_MapStair_0,
    (TaskUpdateFunc)Task_MapStair_1,
    (TaskDrawFunc)Task_MapStair_2,
    (TaskDestroyFunc)Task_MapStair_3,
    sizeof(MapStairWork),
};

TaskDesc gTaskDescMapFaint = {
    "Task_MapFaint",
    (TaskInitFunc)Task_MapFaint_0,
    (TaskUpdateFunc)Task_MapFaint_1,
    (TaskDrawFunc)Task_MapFaint_2,
    (TaskDestroyFunc)Task_MapFaint_3,
    sizeof(MapFaintWork),
};

TaskDesc gTaskDescMapDmg = {
    "Task_MapDmg",
    (TaskInitFunc)Task_MapDmg_0,
    (TaskUpdateFunc)Task_MapDmg_1,
    (TaskDrawFunc)Task_MapDmg_2,
    (TaskDestroyFunc)Task_MapDmg_3,
    sizeof(MapDmgWork),
};

MapNameText* gFloorNames[13] = {
#if defined(VERSION_US)
    gMapNameTextUs_0815B5F6,
    gMapNameTextUs_0815B630,
    gMapNameTextUs_0815B66C,
    gMapNameTextUs_0815B6A6,
    gMapNameTextUs_0815B6E2,
    gMapNameTextUs_0815B71C,
    gMapNameTextUs_0815B756,
    gMapNameTextUs_0815B794,
    gMapNameTextUs_0815B7D0,
    gMapNameTextUs_0815B80A,
    gMapNameTextUs_0815B844,
    gMapNameTextUs_0815B884,
    gMapNameTextUs_0815B8C2,
#elif defined(VERSION_JP)
    gMapNameTextJp_0814F52C,
    gMapNameTextJp_0814F53C,
    gMapNameTextJp_0814F54C,
    gMapNameTextJp_0814F55C,
    gMapNameTextJp_0814F56C,
    gMapNameTextJp_0814F57C,
    gMapNameTextJp_0814F58C,
    gMapNameTextJp_0814F59C,
    gMapNameTextJp_0814F5AC,
    gMapNameTextJp_0814F5BC,
    gMapNameTextJp_0814F5D0,
    gMapNameTextJp_0814F5E4,
    gMapNameTextJp_0814F5F8,
#elif defined(VERSION_EU)
    &gMapNameEu_08893480,
    &gMapNameEu_0889352C,
    &gMapNameEu_088935D8,
    &gMapNameEu_08893684,
    &gMapNameEu_08893730,
    &gMapNameEu_088937DC,
    &gMapNameEu_0889388C,
    &gMapNameEu_08893938,
    &gMapNameEu_088939E4,
    &gMapNameEu_08893A94,
    &gMapNameEu_08893B48,
    &gMapNameEu_08893BFC,
    &gMapNameEu_08893CB8,
#endif
};

MapNameText* gBasementFloorNames[12] = {
#if defined(VERSION_US)
    gMapNameTextUs_0815B906,
    gMapNameTextUs_0815B948,
    gMapNameTextUs_0815B98A,
    gMapNameTextUs_0815B9C6,
    gMapNameTextUs_0815BA04,
    gMapNameTextUs_0815BA44,
    gMapNameTextUs_0815BA84,
    gMapNameTextUs_0815BAC0,
    gMapNameTextUs_0815BAFE,
    gMapNameTextUs_0815BB3C,
    gMapNameTextUs_0815BB7C,
    gMapNameTextUs_0815BBB8,
#elif defined(VERSION_JP)
    gMapNameTextJp_0814F60C,
    gMapNameTextJp_0814F624,
    gMapNameTextJp_0814F63C,
    gMapNameTextJp_0814F654,
    gMapNameTextJp_0814F668,
    gMapNameTextJp_0814F67C,
    gMapNameTextJp_0814F690,
    gMapNameTextJp_0814F6A4,
    gMapNameTextJp_0814F6B8,
    gMapNameTextJp_0814F6CC,
    gMapNameTextJp_0814F6E0,
    gMapNameTextJp_0814F6F4,
#elif defined(VERSION_EU)
    &gMapNameEu_08893D78,
    &gMapNameEu_08893E38,
    &gMapNameEu_08893EF4,
    &gMapNameEu_08893FAC,
    &gMapNameEu_08894068,
    &gMapNameEu_08894124,
    &gMapNameEu_088941DC,
    &gMapNameEu_08894294,
    &gMapNameEu_0889434C,
    &gMapNameEu_08894408,
    &gMapNameEu_088944C0,
    &gMapNameEu_08894578,
#endif
};

TaskDesc gTaskDescMapFloor = {
    "Task_MapFloor",
    (TaskInitFunc)Task_MapFloor_0,
    (TaskUpdateFunc)Task_MapFloor_1,
    (TaskDrawFunc)Task_MapFloor_2,
    (TaskDestroyFunc)Task_MapFloor_3,
    sizeof(MapFloorWork),
};
