#include "rogue.h"
#include "map.h"
#include "map_tasks.h"
#include "sprites_evt.h"
#include "sprite_palettes.h"

// Axel waits in the first room of every run and explains what changed.
typedef struct RogueAxelWork {
    FldObj obj;
    Collider collider;
    AnimState anim;
    void* tiles;
    ObjPalette* palette;
    void (*update)(struct RogueAxelWork*);
    u8 inRange;
    u8 visible;
    u8 page;
    u8 flat; // pages on the flat battle still to say, before the rest
    u8 rest; // the pages on everything else follow
    TaskPool tasks;
    TaskPool talkTasks;
} RogueAxelWork;

#define AXEL_ANIM_IDLE 0
#define AXEL_ANIM_MEMORIZED 2

static void RogueAxel_Idle(RogueAxelWork* w);

static void RogueAxel_Gesture(RogueAxelWork* w) {
    if (AnimIsFinished(&w->anim)) {
        AnimStart(&w->anim, AXEL_ANIM_IDLE, 1);
        gFieldState->flags &= ~0x1000;
        w->update = RogueAxel_Idle;

        if (!(gRogueMeta.flags & ROGUE_META_TUTORIAL_SEEN)) {
            gRogueMeta.flags |= ROGUE_META_TUTORIAL_SEEN;
            RogueMetaSave();
        }
    }
}

static void RogueAxel_Talk(RogueAxelWork* w) {
    if (func_080A42C8() != 0) {
        return;
    }

    // The flat battle first, when it is on.
    if (w->flat != 0) {
        w->flat--;

        if (w->flat != 0) {
            CreateCardMessageTask(&w->tasks, 0, ROGUE_MSG_FLAT_FIRST + ROGUE_FLAT_PAGES - w->flat);
            return;
        }

        if (!(gRogueMeta.flags & ROGUE_META_2D_SEEN)) {
            gRogueMeta.flags |= ROGUE_META_2D_SEEN;
            RogueMetaSave();
        }

        if (w->rest) {
            w->page = 0;
            CreateCardMessageTask(&w->tasks, 0, ROGUE_MSG_AXEL_FIRST);
            return;
        }

        w->page = ROGUE_MSG_AXEL_LAST - ROGUE_MSG_AXEL_FIRST;
    }

    w->page++;

    if (w->page <= ROGUE_MSG_AXEL_LAST - ROGUE_MSG_AXEL_FIRST) {
        CreateCardMessageTask(&w->tasks, 0, ROGUE_MSG_AXEL_FIRST + w->page);
        return;
    }

    AnimStart(&w->anim, AXEL_ANIM_MEMORIZED, 0);
    w->update = RogueAxel_Gesture;
}

static void RogueAxel_Idle(RogueAxelWork* w) {
    if (w->inRange != 0 && (GetKeysPressed() & A_BUTTON)) {
        // Once the explanation has been heard, talking to him opens the shop.
        // Holding L asks for the explanation again.
        // With the flat battle on he explains it once, and again whenever L is held.
        u8 flat = (gRogueMeta.flags & ROGUE_META_2D) && (!(gRogueMeta.flags & ROGUE_META_2D_SEEN) || (GetKeysHeld() & L_BUTTON));
        u8 rest = !(gRogueMeta.flags & ROGUE_META_TUTORIAL_SEEN) || (GetKeysHeld() & L_BUTTON);

        if (!flat && !rest) {
            RogueLeaveRoomFor(&gModeRogueShop, ROGUE_SHOP_FROM_ROOM);
            return;
        }

        gFieldState->flags |= 0x1000;
        w->page = 0;
        w->flat = flat ? ROGUE_FLAT_PAGES : 0;
        w->rest = rest;
        CreateCardMessageTask(&w->tasks, 0, flat ? ROGUE_MSG_FLAT_FIRST : ROGUE_MSG_AXEL_FIRST);
        w->update = RogueAxel_Talk;
    }
}

static void RogueAxel_Init(RogueAxelWork* w) {
    FldObj* e = &w->obj;

    RoguePlaceNpc(e);
    e->angle = 0x80;
    e->unk_1A = 0x30;
    e->unk_30 = 2;
    w->visible = 1;
    w->update = RogueAxel_Idle;
    w->tiles = AllocObjTiles(sizeof(gAcceleFl00Tiles), gAcceleFl00Tiles);
    w->palette = LoadObjPalette(gAccelePalette, 32);
    AnimInit(&w->anim, gAcceleFl00Anims, gAcceleFl00Frames);
    AnimStart(&w->anim, AXEL_ANIM_IDLE, 1);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->inRange = 0;
    TaskPoolInit(&w->talkTasks, 1);
    TaskCreate(&w->talkTasks, &gTaskDescMapTalk, &w->obj);
}

static s32 RogueAxel_Update(RogueAxelWork* w) {
    if ((u8)func_080E0390() != 0) {
        w->visible = 0;
    } else {
        w->visible = 1;
        w->inRange = func_080E03C0(&w->obj);
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->talkTasks);
        AnimUpdate(&w->anim);
        w->update(w);
    }

    return 1;
}

static void RogueAxel_Draw(RogueAxelWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 priority;
    s32 row;
    s16 x;
    s16 y;

    if (w->visible != 0) {
        x = (p->x >> 8) - (gFieldState->x >> 8);
        row = p->y >> 8;
        y = row + (p->z >> 8) - (gFieldState->y >> 8);
        priority = -0x1004 - row * 4;
        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, priority);
        w->obj.unk_3C = p->unk_0C;
        w->obj.unk_3A = priority + 1;
        TaskPoolDraw(&w->tasks);

        if (w->inRange != 0 && w->update == RogueAxel_Idle) {
            TaskPoolDraw(&w->talkTasks);
        }
    }
}

static void RogueAxel_Destroy(RogueAxelWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->talkTasks);
}

TaskDesc gTaskDescRogueAxel = {
    "task_rogue_axel",
    (TaskInitFunc)RogueAxel_Init,
    (TaskUpdateFunc)RogueAxel_Update,
    (TaskDrawFunc)RogueAxel_Draw,
    (TaskDestroyFunc)RogueAxel_Destroy,
    sizeof(RogueAxelWork),
};

// Called once the room and the player exist.
void RogueSpawnRoomActors(void) {
    // The ring that marks the nearest enemy, in every room.
    TaskCreate(&gFieldState->tasks, &gTaskDescRogueRing, 0);

    if (gRogue.kind == ROGUE_ROOM_START) {
        TaskCreate(&gFieldState->tasks, &gTaskDescRogueAxel, 0);
    }

    if (gRogue.kind == ROGUE_ROOM_EVENT) {
        TaskCreate(&gFieldState->tasks, &gTaskDescRogueEvent, 0);
    }
}
