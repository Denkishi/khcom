#include "rogue.h"
#include "card_ids.h"
#include "map.h"
#include "map_runtime.h"
#include "map_tasks.h"
#include "sprites_evt.h"
#include "sprite_palettes.h"

// Event rooms: someone Sora knows waits there, says a couple of lines and
// offers three things to choose from, in the reward screen.

typedef struct RogueEventNpc {
    void* tiles;
    u16 tilesSize;
    void* palette;
    AnimHeader** anims;
    void** frames;
} RogueEventNpc;

typedef struct RogueEventDef {
    RogueEventNpc npc;
    RogueEventOffer offers[ROGUE_EVENT_OFFERS];
} RogueEventDef;

#define NPC(name) { g##name##Fl00Tiles, sizeof(g##name##Fl00Tiles), g##name##Palette, g##name##Fl00Anims, g##name##Fl00Frames }

// In the order of the ROGUE_EVENT_ ids, which is also the order of their
// messages in rogue_text.c.
static const RogueEventDef sEvents[ROGUE_EVENTS] = {
    // Belle looks after him.
    { NPC(Bell), { { ROGUE_OFFER_HEAL, 0 }, { ROGUE_OFFER_MAX_HP, 0 }, { ROGUE_OFFER_CARD, CARD_ID(CARD_CURE, 7) } } },
    // Leon: strength at a price.
    { NPC(Reon), { { ROGUE_OFFER_ATTACK_FOR_HP, 0 }, { ROGUE_OFFER_CARD, CARD_ID(CARD_LIONHEART, 5) }, { ROGUE_OFFER_SHARDS, 5 } } },
    // Yuffie shares what she "found".
    { NPC(Yuffie), { { ROGUE_OFFER_RANDOM_CARD, 0 }, { ROGUE_OFFER_SHARDS, 15 }, { ROGUE_OFFER_REROLL, 0 } } },
    // The moogle's synthesis.
    { NPC(Mogu), { { ROGUE_OFFER_UPGRADE, 0 }, { ROGUE_OFFER_CP, 0 }, { ROGUE_OFFER_RANDOM_CARD, 0 } } },
    // Jack's experiment: a gamble.
    { NPC(Jack), { { ROGUE_OFFER_GAMBLE, 0 }, { ROGUE_OFFER_CARD, CARD_ID(CARD_PUMPKINHEAD, 6) }, { ROGUE_OFFER_SHARDS, 5 } } },
    // Hercules trains him.
    { NPC(Heracles), { { ROGUE_OFFER_COMBO, 0 }, { ROGUE_OFFER_MAX_HP, 0 }, { ROGUE_OFFER_HEAL, 0 } } },
    // Tigger teaches bouncing.
    { NPC(Tigger), { { ROGUE_OFFER_AIR_JUMP, 0 }, { ROGUE_OFFER_SHARDS, 10 }, { ROGUE_OFFER_HEAL, 0 } } },
};

const RogueEventOffer* RogueEventOffers(void) {
    return sEvents[gRogue.event].offers;
}

// Stands a character next to where Sora enters the room: on the first spot
// around it that is floor at Sora's own height, so that he can be reached.
void RoguePlaceNpc(FldObj* obj) {
    static const s16 offsets[][2] = {
        { -0x2800, 0 }, { 0x2800, 0 }, { -0x2000, -0x1400 }, { 0x2000, -0x1400 },
        { -0x2000, 0x1400 }, { 0x2000, 0x1400 }, { 0, -0x2000 }, { 0, 0x2000 },
    };
    FldPos spawn;
    FldPos* p = &obj->fieldPosition;
    s32 height;
    u32 i;

    spawn.x = gFieldState->unk_DC;
    spawn.y = gFieldState->unk_E0;
    spawn.z = 0;
    height = func_080DFF30(&spawn);

    for (i = 0; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        p->x = spawn.x + offsets[i][0];
        p->y = spawn.y + offsets[i][1];
        p->z = 0;

        if (func_080DFB8C(p->x, p->y)->unk_0C != 0x100000 && func_080DFF30(p) == height) {
            break;
        }
    }

    if (i == sizeof(offsets) / sizeof(offsets[0])) {
        p->x = spawn.x + offsets[0][0];
        p->y = spawn.y;
    }

    p->z = 0;
    p->unk_0C = func_080DFF30(p);
    p->z = p->unk_0C;
    p->y -= p->unk_0C;
}

typedef struct RogueEventWork {
    FldObj obj;
    Collider collider;
    AnimState anim;
    void* tiles;
    ObjPalette* palette;
    void (*update)(struct RogueEventWork*);
    u8 inRange;
    u8 visible;
    u8 page;
    TaskPool tasks;
    TaskPool talkTasks;
} RogueEventWork;

static void RogueEvent_Wait(RogueEventWork* w) {
}

static void RogueEvent_Talk(RogueEventWork* w) {
    if (func_080A42C8() != 0) {
        return;
    }

    w->page++;

    if (w->page < ROGUE_EVENT_PAGES) {
        CreateCardMessageTask(&w->tasks, 0, ROGUE_MSG_EVENT_FIRST + gRogue.event * ROGUE_EVENT_PAGES + w->page);
        return;
    }

    gFieldState->flags &= ~0x1000;
    gRogue.eventDone = 1;
    w->update = RogueEvent_Wait;
    RogueLeaveRoomFor(&gModeRogueReward, ROGUE_REWARD_EVENT);
}

static void RogueEvent_Idle(RogueEventWork* w) {
    if (w->inRange != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;
        w->page = 0;
        CreateCardMessageTask(&w->tasks, 0, ROGUE_MSG_EVENT_FIRST + gRogue.event * ROGUE_EVENT_PAGES);
        w->update = RogueEvent_Talk;
    }
}

static void RogueEvent_Init(RogueEventWork* w) {
    const RogueEventNpc* npc = &sEvents[gRogue.event].npc;
    FldObj* e = &w->obj;

    RoguePlaceNpc(e);
    e->angle = 0x80;
    e->unk_1A = 0x30;
    e->unk_30 = 2;
    w->visible = 1;
    // Whoever has already made their offer just stands there.
    w->update = gRogue.eventDone ? RogueEvent_Wait : RogueEvent_Idle;
    w->tiles = AllocObjTiles(npc->tilesSize, npc->tiles);
    w->palette = LoadObjPalette(npc->palette, 32);
    AnimInit(&w->anim, npc->anims, npc->frames);
    AnimStart(&w->anim, 0, 1);
    ColliderInit(&w->collider, 4, 16, 48);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 2);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, &w->obj);
    w->inRange = 0;
    TaskPoolInit(&w->talkTasks, 1);
    TaskCreate(&w->talkTasks, &gTaskDescMapTalk, &w->obj);
}

static s32 RogueEvent_Update(RogueEventWork* w) {
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

static void RogueEvent_Draw(RogueEventWork* w) {
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

        if (w->inRange != 0 && w->update == RogueEvent_Idle) {
            TaskPoolDraw(&w->talkTasks);
        }
    }
}

static void RogueEvent_Destroy(RogueEventWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->talkTasks);
}

TaskDesc gTaskDescRogueEvent = {
    "task_rogue_event",
    (TaskInitFunc)RogueEvent_Init,
    (TaskUpdateFunc)RogueEvent_Update,
    (TaskDrawFunc)RogueEvent_Draw,
    (TaskDestroyFunc)RogueEvent_Destroy,
    sizeof(RogueEventWork),
};
