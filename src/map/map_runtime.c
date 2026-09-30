#include "map_index_assets.h"
#include "boss_map_block_assets.h"
#include "registration_data.h"
#include "map_api.h"
#include "msg_api.h"
#include "m4a_song.h"
#include "monsgage.h"
#include "bos4.h"
#include "bos4_api.h"
#include "map_runtime.h"
#include "map_text_data.h"
#include "world_types.h"
#include "system_state.h"
#include "player_progression.h"
#include "common_text.h"
#include "jiminy_inline_text_data.h"
#include "jiminy_data.h"

extern u8 gWorldBattleStages[];
extern u8 gRikuRoomTypes[];
extern const MapNameText* gMapWorldNames[];

static const u8 sSoraWorldExitEvents[13] = { 10, 13, 16, 19, 22, 25, 30, 33, 37, 40, 47, 58, 66 };

#ifdef VERSION_EU
static const u8 sRikuWorldExitEvents[13] = { 153, 255, 158, 255, 161, 255, 255, 255, 169, 255, 188, 191, 0 };
#else
static const u8 sRikuWorldExitEvents[13] = { 155, 255, 160, 255, 163, 255, 255, 255, 171, 255, 190, 193, 0 };
#endif

u8 GetOppositeDoorSide(u8 a) {
    switch (a) {
    case 0:
        a = 1;
        break;
    case 1:
        a = 0;
        break;
    case 2:
        a = 3;
        break;
    case 3:
        a = 2;
        break;
    }

    return a;
}

void MarkEventRoomDone(MapEventDoor* p) {
    MapFloorRoom* e;

    if (p->kind == 1 || p->kind == 4) {
        e = GetMapFloorRoom(p->room);
        e->cardValue = 0;
        e->nameId = 26;
        e->roomType = 0;
        e->flags |= 8;
    }
}

void SetHallDefaultSpawn(void) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        switch (gGameState.floor) {
        case 1:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
            gMapFloorState.entrySide = 5;
            break;
        }
    } else {
        if (gGameState.floor != 12) {
            gMapFloorState.entrySide = 5;
        }
    }
}

void UpdateWorldFriendFlags(void) {
    u16 t;

    if (gGameState.floor != GetProgressFloor() || gMapFloorState.room == 0xFE
            || gMapFloorState.room == 0xFD) {
        if ((gGameState.flags & GAME_FLAG_FRIENDS_SAVED) == 0) {
            gGameState.flags |= GAME_FLAG_FRIENDS_SAVED;
            gGameState.progression.savedFriendFlags = gGameState.progression.friendFlags & FRIEND_FLAGS_WORLD;
        }

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            return;
        }

        t = gGameState.progression.friendFlags & ~FRIEND_FLAGS_WORLD;
        gGameState.progression.friendFlags = t;

        if (gMapFloorState.room >= 0xFD && gMapFloorState.room <= 0xFE) {
            return;
        }

        switch (gMapFloorState.world) {
        case WORLD_AGRABAH:
            t = FRIEND_FLAG_ALADDIN | gGameState.progression.friendFlags;
            gGameState.progression.friendFlags = t;
            break;
        case WORLD_ATLANTICA:
            t = FRIEND_FLAG_ARIEL | gGameState.progression.friendFlags;
            gGameState.progression.friendFlags = t;
            break;
        case WORLD_HALLOWEEN_TOWN:
            t = FRIEND_FLAG_JACK | gGameState.progression.friendFlags;
            gGameState.progression.friendFlags = t;
            break;
        case WORLD_NEVER_LAND:
            t = FRIEND_FLAG_PETER_PAN | gGameState.progression.friendFlags;
            gGameState.progression.friendFlags = t;
            break;
        case WORLD_HOLLOW_BASTION:
            t = FRIEND_FLAG_THE_BEAST | gGameState.progression.friendFlags;
            gGameState.progression.friendFlags = t;
            break;
        case WORLD_OLYMPUS_COLISEUM:
        case WORLD_WONDERLAND:
        case WORLD_MONSTRO:
        default:
            break;
        }
    } else {
        if ((gGameState.flags & GAME_FLAG_FRIENDS_SAVED) == 0) {
            return;
        }

        gGameState.flags &= ~GAME_FLAG_FRIENDS_SAVED;
        t = (gGameState.progression.friendFlags & ~FRIEND_FLAGS_WORLD) | gGameState.progression.savedFriendFlags;
        gGameState.progression.friendFlags = t;
    }
}

MapFloorDef* GetMapFloorDef(u8 a) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return &gUnk_0984CBD0[a];
    }

    return &gUnk_0984C868[a];
}

u8* GetMapRoomLinks(u8 a) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return gUnk_0984CBD0[gGameState.floor].links + a * 4;
    }

    return gUnk_0984C868[gGameState.floor].links + a * 4;
}

MapEventDoor* GetMapEventDoor(u8 a) {
    if (gGameState.flags & GAME_FLAG_RIKU) {
        return gUnk_0984CBD0[gGameState.floor].eventDoors + a;
    }

    return gUnk_0984C868[gGameState.floor].eventDoors + a;
}

MapFloorRoom* GetMapFloorRoom(u8 index) {
    return &gMapFloorState.rooms[index];
}

u8 GetMapRoomLink(u8 a, u8 b) {
    return GetMapRoomLinks(a)[b];
}

u16 GetMapDoorFlags(u8 a, u8 b) {
    MapFloorRoom* e;
    MapEventDoor* p;
    u16 r;
    u8 c;
    u8 d;

    c = GetMapRoomLink(a, b);

    if (c == 0xFF) {
        return 0;
    }

    if (c >= 0xFD && c <= 0xFE) {
        return 3;
    }

    e = GetMapFloorRoom(c);
    r = 1;

    if ((e->flags & 1) != 0) {
        r = 3;
    }

    if ((e->flags & 8) != 0) {
        r |= 8;
    }

    if ((e->flags & 4) != 0) {
        r |= 8;
    }

    d = GetEventRoomKind(c);

    if (d == 1 || d == 4 || d == 2) {
        r |= 0x10;
        p = GetMapEventDoor(0);

        while (p->kind != 5) {
            if (p->room == c) {
                if (p->side != b) {
                    r |= 8;
                }

                break;
            }

            p++;
        }
    }

    if ((gMapFloorState.flags & 8) != 0) {
        p = GetMapEventDoor(*GetMapRoomEvent(gMapFloorState.eventStep));

        if (p->room == c && p->side == b) {
            r |= 2;
        }
    }

    return r;
}
void UpdateGameWorld(void) {
    u16 t;

    switch (gMapFloorState.room) {
    case 0xFD:
    case 0xFE:
        gGameState.world = 0;
        gGameState.battleStage = BATTLE_STAGE_CASTLE_OBLIVION;
        break;
    case 0xFC:
        gGameState.world = WORLD_TRAVERSE_TOWN;
        gGameState.battleStage = BATTLE_STAGE_TRAVERSE_TOWN;
        break;
    default:
        gGameState.world = gMapFloorState.world;
        gGameState.battleStage = gWorldBattleStages[gMapFloorState.world];
        break;
    }

    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
        InitRikuDeckForWorld(gGameState.world);

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            t = gGameState.progression.friendFlags & 0xFF80;
            gGameState.progression.friendFlags = t;
            return;
        }
    }

    switch (gGameState.world) {
    case 0:
        break;
    case WORLD_AGRABAH:
        t = gGameState.progression.friendFlags & 0xFF07;
        gGameState.progression.friendFlags = t;
        break;
    case WORLD_ATLANTICA:
        t = gGameState.progression.friendFlags & 0xFF0B;
        gGameState.progression.friendFlags = t;
        break;
    case WORLD_HALLOWEEN_TOWN:
        t = gGameState.progression.friendFlags & 0xFF13;
        gGameState.progression.friendFlags = t;
        break;
    case WORLD_NEVER_LAND:
        t = gGameState.progression.friendFlags & 0xFF23;
        gGameState.progression.friendFlags = t;
        break;
    case WORLD_HOLLOW_BASTION:
        t = gGameState.progression.friendFlags & 0xFF43;
        gGameState.progression.friendFlags = t;
        break;
    case WORLD_OLYMPUS_COLISEUM:
    case WORLD_WONDERLAND:
    case WORLD_MONSTRO:
    default:
        t = gGameState.progression.friendFlags & 0xFF03;
        gGameState.progression.friendFlags = t;
        break;
    }
}
void SetWorldJiminyFlags(void) {
    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
        switch (gGameState.world) {
        case WORLD_AGRABAH:
            SetJiminyFlag(57);
            break;
        case WORLD_ATLANTICA:
            SetJiminyFlag(67);
            break;
        case WORLD_OLYMPUS_COLISEUM:
            SetJiminyFlag(50);
            break;
        case WORLD_HALLOWEEN_TOWN:
            SetJiminyFlag(61);
            break;
        case WORLD_NEVER_LAND:
            SetJiminyFlag(72);
            break;
        case WORLD_HOLLOW_BASTION:
            SetJiminyFlag(75);
            break;
        }
    } else {
        switch (gGameState.world) {
        case WORLD_TRAVERSE_TOWN:
            SetJiminyFlag(4);
            SetJiminyFlag(28);
            SetJiminyFlag(29);
            SetJiminyFlag(30);
            SetJiminyFlag(31);
            break;
        case WORLD_WONDERLAND:
            SetJiminyFlag(5);
            SetJiminyFlag(42);
            SetJiminyFlag(43);
            SetJiminyFlag(44);
            SetJiminyFlag(45);
            SetJiminyFlag(46);
            SetJiminyFlag(47);
            break;
        case WORLD_OLYMPUS_COLISEUM:
            SetJiminyFlag(6);
            SetJiminyFlag(32);
            SetJiminyFlag(48);
            SetJiminyFlag(49);
            SetJiminyFlag(50);
            break;
        case WORLD_AGRABAH:
            SetJiminyFlag(7);
            SetJiminyFlag(51);
            SetJiminyFlag(52);
            SetJiminyFlag(53);
            SetJiminyFlag(54);
            SetJiminyFlag(55);
            SetJiminyFlag(56);
            SetJiminyFlag(57);
            break;
        case WORLD_HALLOWEEN_TOWN:
            SetJiminyFlag(8);
            SetJiminyFlag(58);
            SetJiminyFlag(59);
            SetJiminyFlag(60);
            SetJiminyFlag(61);
            break;
        case WORLD_MONSTRO:
            SetJiminyFlag(9);
            SetJiminyFlag(62);
            SetJiminyFlag(63);
            break;
        case WORLD_ATLANTICA:
            SetJiminyFlag(10);
            SetJiminyFlag(64);
            SetJiminyFlag(65);
            SetJiminyFlag(66);
            SetJiminyFlag(67);
            SetJiminyFlag(68);
            break;
        case WORLD_NEVER_LAND:
            SetJiminyFlag(11);
            SetJiminyFlag(69);
            SetJiminyFlag(70);
            SetJiminyFlag(71);
            SetJiminyFlag(72);
            break;
        case WORLD_HOLLOW_BASTION:
            SetJiminyFlag(12);
            SetJiminyFlag(73);
            SetJiminyFlag(74);
            SetJiminyFlag(75);
            SetJiminyFlag(76);
            break;
        case WORLD_TWILIGHT_TOWN:
            SetJiminyFlag(14);
            break;
        case WORLD_DESTINY_ISLANDS:
            SetJiminyFlag(15);
            SetJiminyFlag(33);
            SetJiminyFlag(34);
            SetJiminyFlag(35);
            break;
        }
    }
}
void SetFloorJiminyFlags(void) {
    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
        switch (gGameState.floor) {
        case 0:
            SetJiminyFlag(1);
            break;
        case 2:
            SetJiminyFlag(0x28);
            break;
        case 4:
            SetJiminyFlag(2);
            SetJiminyFlag(0xEE);
            break;
        case 8:
            SetJiminyFlag(3);
            SetJiminyFlag(0xF0);
            break;
        case 9:
            SetJiminyFlag(0xEB);
            SetJiminyFlag(0xF1);
            break;
        case 10:
            SetJiminyFlag(0xEC);
            SetJiminyFlag(0x24);
            SetJiminyFlag(0x26);
            SetJiminyFlag(0x29);
            SetJiminyFlag(0x27);
            SetJiminyFlag(0xF2);
            break;
        }
    } else {
        switch (gGameState.floor) {
        case 0:
            SetJiminyFlag(0);
            SetJiminyFlag(0x26);
            break;
        case 5:
            SetJiminyFlag(1);
            SetJiminyFlag(0x27);
            break;
        case 8:
            SetJiminyFlag(2);
            break;
        case 9:
            SetJiminyFlag(0x28);
            break;
        case 11:
            SetJiminyFlag(3);
            SetJiminyFlag(0x24);
            SetJiminyFlag(0x25);
            break;
        }
    }
}
void AdvanceFloorStory(void) {
    u8* e = GetMapRoomEvent(gMapFloorState.eventStep);
    MapEventDoor* p;
    MapFloorRoom* q;
    u16 t;
    u16 u;
    u16 v;

    if (gMapFloorState.room == 0xFE) {
        t = gMapFloorState.flags | 2;
        gMapFloorState.flags = t;

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            if (gGameState.floor == 0x0A) {
                gMapFloorState.progress++;
            }
        } else {
            if (gGameState.floor == 0) {
                gMapFloorState.room = 0xFC;
                gMapFloorState.entrySide = 5;
                return;
            }

            if (gGameState.floor == 0x0C) {
                gMapFloorState.progress++;
            }
        }

        EnterFloorWorld();
    } else if (gMapFloorState.room == 0xFD) {
        u = gMapFloorState.flags | 1;
        gMapFloorState.flags = u;
        SetFloorJiminyFlags();
        gMapFloorState.progress++;
        StoreMapFloorState();
        GoToNextFloor();
        SetHallDefaultSpawn();
    } else if (e[0] == 0xFF) {
        v = gMapFloorState.flags | 4;
        gMapFloorState.flags = v;
        gMapFloorState.progress++;
        SetCurrentMapRoom(0xFD, 5);
    } else {
        t = gMapFloorState.flags & ~8;
        gMapFloorState.flags = t;
        p = GetMapEventDoor(e[0]);
        MarkEventRoomDone(p);
        CreateMapRoom(p->returnRoom, 0);
        SetCurrentMapRoom(p->returnRoom, p->returnSide);
        gMapFloorState.eventStep++;

        if (e[4] == 0xFF) {
            q = GetMapFloorRoom(GetMapFloorDef(gGameState.floor)->exitRoom);
            t = q->flags & ~4;
            q->flags = t;
            gMapFloorState.flags |= 0x20;
            SetWorldJiminyFlags();
        }
    }
}

void AdvanceToExitHall(void) {
    gMapFloorState.progress++;
    SetCurrentMapRoom(0xFD, 5);
}

u8 func_080DF49C(void) {
    u8* e = GetMapRoomEvent(gMapFloorState.eventStep);
    EventKeyList* t = &gEventKeyLists[GetMapEventDoor(*e)->keyList];
    EventKey* q;

    t += *e;
    q = t->keys;

    while (q->kind == 0xFF) {
        q++;
    }

    return q->kind;
}

u8 GetCurrentEventDoorKeyKind(void) {
    if (SelectEventDoor(gMapRoomState->doorRoom, gMapRoomState->doorSide) != 0) {
        return GetEventKey(0)->kind;
    }

    return 0xFF;
}

u8 SelectCurrentEventDoor(void) {
    return SelectEventDoor(gMapRoomState->doorRoom, gMapRoomState->doorSide);
}

u8 GetEventRoomKind(u8 a) {
    MapEventDoor* p = GetMapEventDoor(0);

    while (p->kind != 5) {
        if (p->room == a) {
            return p->kind;
        }

        p++;
    }

    return 0;
}

s32 GetMapRoomCardValue(u8 a) {
    u8* p;
    u8* q;

    if ((s32)gMapRoomState->flags < 0) {
        return 0;
    }

    p = (u8*)&gMapFloorState;
    q = p + a * 0x10;

    return q[0x26];
}

void SetCardlessRoomType(u8 a) {
    MapFloorRoom* e = GetMapFloorRoom(a);
    MapEventDoor* p = GetMapEventDoor(0);

    while (p->kind != 5) {
        if (p->room == a) {
            if (p->kind == 2) {
                e->cardValue = 0;
                e->nameId = 27;
                e->roomType = 22;
                return;
            }

            gMapFloorState.flags |= 8;
            e->cardValue = 0;
            e->nameId = 26;
            e->roomType = 0;
        }

        p++;
    }

    if (GetMapFloorDef(gGameState.floor)->exitRoom != a) {
        e->cardValue = 0;
        e->nameId = 26;
        e->roomType = 0;
        return;
    }

    e->cardValue = 0;
    e->nameId = 5;
    e->roomType = 23;
}

u8 GetRandomRoomType(void) {
    if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
        return GetRandom() % 21 + 1;
    }

    return gRikuRoomTypes[GetRandom() % 13];
}

void CreateMapRoom(u8 a, UnkStruct_080DF640* p) {
    MapFloorRoom* e = GetMapFloorRoom(a);
    const u8* row;
    const u8* anim;

    if (p == NULL && (e->flags & 1) != 0) {
        return;
    }

    e->flags &= ~0x10;
    e->flags &= ~0x20;
    e->flags |= 1;
    e->seed = gFrameCounter * gFrameCounter;

    if (p != NULL) {
        row = gUnk_0984D0CC[p->kind];
        e->cardValue = p->value;
        e->nameId = row[0];

        if (row[1] != 25) {
            e->roomType = row[1];
        } else {
            e->roomType = GetRandomRoomType();
        }
    } else {
        SetCardlessRoomType(a);
    }

    anim = gUnk_0984D134[e->roomType];
    e->enemiesLeft = anim[2];
    e->przCardsLeft = anim[6];
}

void LoadMapRoomState(MapRoomState* p, u8 a) {
    MapFloorRoom* e = GetMapFloorRoom(a);
    const u8* row;
    u16 t;

    t = e->flags | 2;
    e->flags = t;
    SeedRandom(e->seed);
    gMapRoomState->nameId = e->nameId;
    gMapRoomState->roomType = e->roomType;

    if (gMapChkUseParams == 0) {
        row = gUnk_0984D134[e->roomType];
        gGameState.roomEffect = row[5];
        LoadMapForm(row[0]);
    }
}

void SetCurrentMapRoom(u8 a, u8 b) {
    gMapFloorState.room = a;
    gMapFloorState.entrySide = GetOppositeDoorSide(b);
    UpdateWorldFriendFlags();
}

u8 GetProgressFloor(void) {
    if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
        if (gMapFloorState.progress > 0x16) {
            return 11;
        }

        if (gMapFloorState.progress > 0x13) {
            return 10;
        }

        if (gMapFloorState.progress > 0x11) {
            return 9;
        }

        if (gMapFloorState.progress > 0x0F) {
            return 8;
        }

        if (gMapFloorState.progress > 0x0D) {
            return 7;
        }

        if (gMapFloorState.progress > 0x0B) {
            return 6;
        }

        if (gMapFloorState.progress > 0x09) {
            return 5;
        }

        if (gMapFloorState.progress > 0x07) {
            return 4;
        }

        if (gMapFloorState.progress > 0x05) {
            return 3;
        }

        if (gMapFloorState.progress > 0x03) {
            return 2;
        }

        if (gMapFloorState.progress <= 0x01) {
            return 0;
        }

        return 1;
    }

    if (gMapFloorState.progress > 0x18) {
        return 12;
    }

    if (gMapFloorState.progress > 0x15) {
        return 11;
    }

    if (gMapFloorState.progress > 0x13) {
        return 10;
    }

    if (gMapFloorState.progress > 0x11) {
        return 9;
    }

    if (gMapFloorState.progress > 0x0F) {
        return 8;
    }

    if (gMapFloorState.progress > 0x0D) {
        return 7;
    }

    if (gMapFloorState.progress > 0x0B) {
        return 6;
    }

    if (gMapFloorState.progress > 0x09) {
        return 5;
    }

    if (gMapFloorState.progress > 0x07) {
        return 4;
    }

    if (gMapFloorState.progress > 0x05) {
        return 3;
    }

    if (gMapFloorState.progress > 0x03) {
        return 2;
    }

    if (gMapFloorState.progress <= 0x01) {
        return 0;
    }

    return 1;
}

void* GetMapWorldName(u8 index) {
#ifdef VERSION_EU
    return eu_0805E924(gMapWorldNames[index]);
#else
    return (void*)gMapWorldNames[index];
#endif
}

void EnterEntranceHall(void) {
    SetCurrentMapRoom(0xFE, 1);
    RequestMapMode();
}

void EnterExitHall(void) {
    u8 v;
    u16 f;

    if ((gMapFloorState.flags & 4) != 0) {
        v = 0xFF;
    } else {
        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            v = sRikuWorldExitEvents[gGameState.floor];
        } else {
            v = sSoraWorldExitEvents[gGameState.floor];
        }
    }

    if (v != 0xFF) {
        gGameState.world = 0;
        gGameState.battleStage = BATTLE_STAGE_CASTLE_OBLIVION;
        gGameState.roomEffect = 0;

        if ((gGameState.flags & GAME_FLAG_RIKU) != 0) {
            InitRikuDeckForWorld(0);
        }

        RequestEventMode(v);
    } else {
        if ((gMapFloorState.flags & 4) == 0) {
            f = gMapFloorState.flags | 4;
            gMapFloorState.flags = f;
            gMapFloorState.progress++;
        }

        SetCurrentMapRoom(0xFD, 0);
        RequestMapMode();
    }
}
void InitMapFloorState(u8 a, u8 b) {
    s32 i;
    u16 t;

    gMapFloorState.flags = gGameState.floors[gGameState.floor].flags;
    gMapFloorState.world = gGameState.floors[gGameState.floor].world;
    gMapFloorState.eventStep = gGameState.floors[gGameState.floor].eventStep;
    gMapFloorState.room = a;
    gMapFloorState.entrySide = b;

    for (i = 0; i <= 3; i++) {
        gMapFloorState.unk_18[i] = 0;
        gMapFloorState.eventKeyProgress[i].paid = 0;
        gMapFloorState.eventKeyProgress[i].remaining = 0;
    }

    for (i = 0; i < 32; i++) {
        gMapFloorState.rooms[i].flags = 0;
        gMapFloorState.rooms[i].seed = 0;
        gMapFloorState.rooms[i].nameId = 0;
        gMapFloorState.rooms[i].cardValue = 0;
        gMapFloorState.rooms[i].roomType = 0;
    }

    gGameState.mapMenuCursor = 0xFF;
    t = gMapFloorState.flags | 0x100;
    gMapFloorState.flags = t;
}

void MarkPastEventRoomsDone(void) {
    s32 i;

    for (i = 0; i < gMapFloorState.eventStep; i++) {
        MarkEventRoomDone(GetMapEventDoor(*GetMapRoomEvent(i)));
    }
}

void GoToFloor(u8 a) {
    gGameState.floor = a;
    InitMapFloorState(0xFE, 0);
}

void GoToNextFloor(void) {
    gGameState.floor++;
    InitMapFloorState(0xFE, 1);
}

void GoToPreviousFloor(void) {
    gGameState.floor--;
    InitMapFloorState(0xFD, 0);
}

void WarpToFloor(u8 a) {
    u16 t;

    ClearFieldResume();
    StoreMapFloorState();
    GoToFloor(a);
    gMapFloorState.room = 0xFE;
    gMapFloorState.entrySide = 5;
    t = gMapFloorState.flags | 0x80;
    gMapFloorState.flags = t;
    RequestMapMode();
}

void SetFloorWorld(u8 a) {
    gMapFloorState.world = a;
    gGameState.floors[gGameState.floor].world = a;
}

void EnterFloorWorld(void) {
    MapFloorDef* e = GetMapFloorDef(gGameState.floor);
    MapFloorRoom* p;
    u16 t;

    if (gGameState.floor == 13) {
        gGameState.floor = 0;
    }

    if (gMapFloorState.room == 0xFD) {
        SetCurrentMapRoom(e->exitRoom, 1);
    } else {
        SetCurrentMapRoom(e->entryRoom, 0);
    }

    MarkPastEventRoomsDone();

    if ((gMapFloorState.flags & 0x20) == 0) {
        p = GetMapFloorRoom(e->exitRoom);
        t = p->flags | 4;
        p->flags = t;
    }

    CreateMapRoom(gMapFloorState.room, 0);
}

void StoreMapFloorState(void) {
    gGameState.floors[gGameState.floor].flags = gMapFloorState.flags;
    gGameState.floors[gGameState.floor].world = gMapFloorState.world;
    gGameState.floors[gGameState.floor].eventStep = gMapFloorState.eventStep;
}

void InitStartFloor(u8 a, u8 b) {
    GoToFloor(a);
    SetFloorWorld(b);

    if (a == 0) {
        gMapFloorState.progress = 0;
        gMapFloorState.flags &= 0xFEFF;
    }
}

void ResetMapFloors(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        gGameState.floors[i].flags = 0;
        gGameState.floors[i].world = 0;
        gGameState.floors[i].eventStep = 0;
    }

    gMapFloorState.progress = 0;

    if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
        InitSoraDecks();
    }

    GoToFloor(0);
}

MapDoor* GetMapDoor(u8 a) {
    return MapGetDoor(a);
}

MapCell* FieldCellAt(s32 x, s32 y) {
    s16 a = x / 0x2000;
    s16 b = y / 0x1000;

    if ((s32)gMapRoomState->flags < 0) {
        return MapFixCellAt(a, b);
    }

    return MapCellAt(a, b);
}

u8 IsFldPosBlocked(FldPos* p) {
    s32 y = p->y + p->ground;
    MapCell* q = FieldCellAt(p->x, y);

    if (q == NULL) {
        return 1;
    }

    if (q->upperZ >= p->z && q->lowerZ != 0x100000) {
        return 0;
    }

    return MapCellMaskBitAt(q, p->x, y);
}

u8 GetMapWalkOutMode(void) {
    if (gMapRoomState->flags & 0x100) {
        if (gMapFloorState.world != 0) {
            return 2;
        }

        if ((gGameState.flags & GAME_FLAG_RIKU) == 0 && gGameState.floor == 12) {
            SetFloorWorld(WORLD_CASTLE_OBLIVION);
            return 2;
        }

        return 1;
    }

    return 0;
}

void EndMapWalkOut(void) {
    gMapRoomState->flags &= ~0x100;
}

u8 FldPosRevertIfBlocked(FldPos* p, s32 x, s32 y) {
    s32 old;

    if (IsFldPosBlocked(p) != 0) {
        p->x = x;
        p->y = y;
        return 1;
    }

    old = p->ground;
    p->ground = GetFldPosGround(p);

    if (old != p->ground) {
        if (IsFldPosBlocked(p) != 0) {
            p->x = x;
            p->y = y;
            p->ground = old;
            return 1;
        }
    }

    return 0;
}

u8 MapFindOpenDoor(FldPos* p) {
    s32 i;
    u16 a;
    u16 b;
    MapDoor* e;
    u8 r = 0;

    if ((s32)gMapRoomState->flags < 0) {
        return 0;
    }

    if ((gGameState.progression.unk_82 & 0x200) == 0) {
        return 0;
    }

    if (p->z != p->ground) {
        return 0;
    }

    a = (p->x >> 8) / 32;
    b = ((p->y + p->z) >> 8) / 16;

    for (i = 0; i <= 3; i++) {
        e = GetMapDoor(i);

        if ((e->flags & 1) != 0 && (e->flags & 0xA) == 2 && e->cellX == a && e->cellY == b) {
            gMapRoomState->doorRoom = e->room;
            gMapRoomState->doorSide = e->side;
            r = 1;
            break;
        }
    }

    return r;
}
u8 IsAtTargetDoor(FldPos* p) {
    s32 i;
    u16 a;
    u16 b;
    MapDoor* e;

    if ((s32)gMapRoomState->flags < 0) {
        return gMapRoomState->flags >> 9 & 1;
    }

    if (p->z != p->ground) {
        return 0;
    }

    a = (p->x >> 8) / 32;
    b = ((p->y + p->z) >> 8) / 16;

    for (i = 0; i <= 3; i++) {
        e = GetMapDoor(i);

        if ((e->flags & 1) != 0 && (e->flags & 0xA) == 2 && e->cellX == a && e->cellY == b
                && e->room == gMapRoomState->doorRoom && e->side == gMapRoomState->doorSide) {
            return 1;
        }
    }

    return 0;
}

u8 _080DFE1C(FldPos* p) {
    MapCell* q = FieldCellAt(p->x, p->y + p->ground);

    if (q->flags & 0x20) {
        switch (q->type) {
        case 3:
        case 4:
        case 8:
            return 2;
        case 5:
        case 6:
        case 9:
            return 1;
        case 7:
            return 0;
        }
    }

    return 0;
}

s32 func_080DFE7C(s32 x, s32 y, s32 z) {
    MapCell* p;
    s32 r;

    y += z;
    p = FieldCellAt(x, y);

    if (p == NULL) {
        return 0;
    }

    if (p->type == 4 || p->type == 6) {
        if (MapCellMaskBitAt(p, x, y) != 0) {
            r = p->lowerZ;
        } else {
            r = p->upperZ;
        }
    } else {
        r = p->lowerZ;
    }

    return r;
}

u8 gWorldBattleStages[14] = {
    BATTLE_STAGE_CASTLE_OBLIVION,
    BATTLE_STAGE_AGRABAH,
    BATTLE_STAGE_ATLANTICA,
    BATTLE_STAGE_OLYMPUS_COLISEUM,
    BATTLE_STAGE_WONDERLAND,
    BATTLE_STAGE_MONSTRO,
    BATTLE_STAGE_HALLOWEEN_TOWN,
    BATTLE_STAGE_NEVER_LAND,
    BATTLE_STAGE_HOLLOW_BASTION,
    BATTLE_STAGE_DESTINY_ISLANDS,
    BATTLE_STAGE_TRAVERSE_TOWN,
    BATTLE_STAGE_TWILIGHT_TOWN,
    BATTLE_STAGE_CASTLE_OBLIVION,
};

u8 gRikuRoomTypes[14] = {
    1,
    2,
    4,
    5,
    6,
    7,
    8,
    13,
    14,
    15,
    16,
    17,
    18,
};

const MapNameText* gMapWorldNames[14] = {
#if defined(VERSION_US)
    gMapWorldNameTextUs_0815B57A,
    gUnk_0815A56C,
    gUnk_0815A5AA,
    gUnk_0815A54A,
    gUnk_0815A534,
    gUnk_0815A59A,
    gUnk_0815A57C,
    gUnk_0815A5BE,
    gUnk_0815A5D4,
    gUnk_0815A62A,
    gUnk_0815A518,
    gUnk_0815A60E,
    gUnk_0815A64A,
    gUnk_0815A5F2,
#elif defined(VERSION_JP)
    gMapWorldNameTextJp_0814F2E0,
    gUnkJp_0814E590,
    gUnkJp_0814E5E4,
    gUnkJp_0814E5CC,
    gUnkJp_0814E59C,
    gUnkJp_0814E5AC,
    gUnkJp_0814E5B8,
    gUnkJp_0814E5F4,
    gUnkJp_0814E618,
    gUnkJp_0814E62C,
    gUnkJp_0814E57C,
    gUnkJp_0814E644,
    gUnkJp_0814E658,
    gUnkJp_0814E604,
#elif defined(VERSION_EU)
    &gMapWorldNameEu_088926FC,
    &gUnkEu_0888E3A0,
    &gUnkEu_0888E578,
    &gUnkEu_0888E530,
    &gUnkEu_0888E410,
    &gUnkEu_0888E450,
    &gUnkEu_0888E4C0,
    &gUnkEu_0888E5DC,
    &gUnkEu_0888E6BC,
    &gUnkEu_0888E72C,
    &gUnkEu_0888E364,
    &gUnkEu_0888E78C,
    &gUnkEu_0888E804,
    &gUnkEu_0888E654,
#endif
};
