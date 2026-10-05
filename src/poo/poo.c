/**
 * poo.c
 * 100 Acre Wood Minigame Objects
 */

#include "macros.h"
#include "poo.h"
#include "sprites_btl.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_map.h"
#include "sprites_pooh.h"
#include "sprites_sora.h"
#include "gba/keys.h"
#include "btl_api.h"
#include "malloc.h"
#include "mode_pooh_api.h"
#include "songs.h"
#include "player_progression.h"
#include <stdlib.h>
#include "poo_background_data.h"
#include <string.h>
#include "anim.h"
#include "battle_actor_types.h"
#include "bos4_api.h"
#include "btl_collision.h"
#include "display.h"
#include "engine_math.h"
#include "field_state.h"
#include "game_state.h"
#include "key.h"
#include "listpool.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "player_progression_types.h"
#include "poo_api.h"
#include "poo_data.h"
#include "pooh_actor_types.h"
#include "prize_types.h"
#include "registration_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "default_bg_map.h"
#include "event_backgrounds.h"
#include "sprite_palettes.h"

u8 gPooAttackActive EWRAM_COMMON(4);
s32 gPoohRequestX EWRAM_COMMON(4);
u16 gPoohGaugeTimer EWRAM_COMMON(4);
u16 gPoohGauge EWRAM_COMMON(4);
s32 gPoohRequestY EWRAM_COMMON(4);
struct PooPos* gPoohPos EWRAM_COMMON(4);
u32 gPoohRequest EWRAM_COMMON(4);
u32 gUnk_0203C3F4 EWRAM_COMMON(4);
u16 gPooScrollY EWRAM_COMMON(4);
s32 gPooCameraX EWRAM_COMMON(4);
s32 gPooCameraFocusY EWRAM_COMMON(4);
s32 gPooCameraFocusX EWRAM_COMMON(4);
s32 gPooCameraY EWRAM_COMMON(4);
u16 gPooScrollX EWRAM_COMMON(4);
struct PooNode* gPooSoraNode EWRAM_COMMON(4);
void* gPooSoraCollider EWRAM_COMMON(4);
PooActor gPooActor EWRAM_COMMON(16);
void* gStockMesDispWork EWRAM_COMMON(4);
PooState gPooState EWRAM_COMMON(16);
void* gSharedModeWork EWRAM_COMMON(4);

#define sPoohInteractions ((PoohInteractionRegistry*)gSharedModeWork)

extern AnimDef gTrap01AnimDefs[5];

static const PooSpot sPooh04FrameOffsets[55] = {
    { 0, 0, 0 },
    { 0, -512, 0 },
    { 0, -512, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, -1024, 0 },
    { 0, -256, 0 },
    { 0, -256, 0 },
    { 0, -256, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 512, 0 },
    { 0, 512, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 1024, 0 },
    { 0, 256, 0 },
    { 0, -256, 0 },
    { 0, 256, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { -768, 0, 0 },
    { -1280, 0, 0 },
    { -1024, 1280, 0 },
    { -512, -768, 0 },
    { -768, 1280, 0 },
    { -256, -1024, 0 },
    { -256, 0, 0 },
    { -256, 256, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { -512, 0, 0 },
    { -1280, 0, 0 },
    { -1536, 0, 256 },
    { -768, 0, 512 },
    { -1280, 0, -768 },
    { -512, 0, 0 },
    { -256, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { -768, 0, 0 },
    { -1280, 0, 0 },
    { -1024, -1280, 0 },
    { -512, 768, 0 },
    { -768, -1280, 0 },
    { -256, 1024, 0 },
    { -256, 0, 0 },
    { -256, -256, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};

static const PooSpot sPooh04aFrameOffsets[80] = {
    { 0, 0, 0 },
    { 0, 512, 0 },
    { 0, 256, 0 },
    { 0, 256, 0 },
    { 0, 512, 0 },
    { -256, 0, 0 },
    { 0, 0, 0 },
    { 0, -512, 0 },
    { 0, 256, 0 },
    { 0, -256, 0 },
    { 0, -512, 0 },
    { 0, 512, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, -512, 0 },
    { 0, -256, 0 },
    { 0, -256, 0 },
    { 0, -512, 0 },
    { -256, 0, 0 },
    { 0, 0, 0 },
    { 0, 512, 0 },
    { 0, -256, 0 },
    { 0, 256, 0 },
    { 0, 512, 0 },
    { 0, -512, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { -256, -256, 0 },
    { 0, 0, 0 },
    { 0, 512, 0 },
    { 256, -256, 0 },
    { 0, 0, 0 },
    { -256, 0, 0 },
    { 768, 0, 0 },
    { 0, 0, 0 },
    { 256, 0, 0 },
    { 512, 0, 0 },
    { 512, 0, 0 },
    { 256, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 256, 0, 0 },
    { 0, 0, 0 },
    { 256, 0, 0 },
    { -256, 0, 0 },
    { -256, 0, 0 },
    { -256, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 768, 0, 0 },
    { 256, 0, 0 },
    { 0, 0, 0 },
    { 256, 0, 0 },
    { 256, 0, 0 },
    { 768, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { -256, 256, 0 },
    { 0, 0, 0 },
    { 0, 512, 0 },
    { 256, 256, 0 },
    { 0, 0, 0 },
    { -256, 0, 0 },
    { 768, 0, 0 },
    { 0, 0, 0 },
    { 256, 0, 0 },
    { 512, 0, 0 },
    { 512, 0, 0 },
    { 256, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};

static const PooPoint sPoohStumpCircle[4] = {
    { 593408, 315648 },
    { 584192, 320256 },
    { 593408, 324864 },
    { 602624, 320256 },
};

static PoohWork* sPooWork;
static u32 sPoohAction;
static PooSpawnArgs sPooSpawnArgs;
static PooPos sPooSpawnPos;
static s32 sPooMoveAdjustX;
static s32 sPooMoveAdjustY;
static u8 sPooCameraFrozen;
static u8 sPooCameraFollowPooh;
static s32 sPooCameraMaxY;
static PooSoraWork* sPooSoraWork;
static u16 sPooSoraPriority;
static s32 sPooBestNodeScore;
static s32 sPooNodeScore;
static ListPool sPooNodes;
static PooPos sPooOwlBalloonPos;
static u16 sPooEeyoreTailTimer;
static u32 sPooHoneycombState;
static PooWagonWork* sPooWagon;
static u16 sPooWagonPriority2;
static u16 sPooWagonPriority;
static u16 sPooWagonWheelPriority;
static u32 sPooBeeCount;
static PooBeeAfterEventWork* sPooBeeAfterEventWork;
static u16 sPooCabbageCount;
static u16 sPooCabbageLandedCount;

s32 GetPooManhattanDistance(PooPos* a, PooPos* b) {
    s32 dx;
    s32 dy;

    dx = a->x - b->x;

    if (dx < 0) {
        dx = b->x - a->x;
    }

    dy = a->y - b->y;

    if (dy < 0) {
        dy = b->y - a->y;
    }

    return dx + dy;
}

void SetPoohPalette(PoohWork* work, u32 b) {
    u16* pal;

    switch (b) {
    case 16:
        pal = gTrap0001Palette;
        break;
    case 36:
    case 37:
        pal = gTrap0002Palette;
        break;
    case 38:
    case 39:
        pal = gTrap0003Palette;
        break;
    default:
        pal = gPoohPalette;
        break;
    }

    if (work->palette->src != pal) {
        ReleaseObjPalette(work->palette);
        work->palette = LoadObjPalette(pal, 32);
    }
}

void SetPoohAction(PoohWork* work, u32 b) {
    sPoohAction = b;

    if (b == 0) {
        gPoohRequest = 0;
    }

    if (b >= 38 && b <= 39) {
        work->balloonTimer = 0;

        if (!IsTaskActive(work->task)) {
            work->task = TaskCreate(&work->tasks, &gTaskDescPooBalloon, &work->pos);
        }
    }

    if (b == 30 || b == 24 || b == 4 || b == 11) {
        work->actionTimer = 0;
    }

    if (b == 15) {
        work->vz = -0x130;
    }

    if (b >= 36 && b <= 37) {
        m4aSongNumStart(SONG_SND_329);
    } else if (b == 16) {
        m4aSongNumStart(SONG_SYS_PO_FALL);
    } else if (b == 39 || b == 22 || (b >= 32 && b <= 35)) {
        // fakematch
        do {
            work->angle = 0xAD;
            work->lookAngle = 0xAD;
            work->lookColumn = work->angle;
        } while (0);
    }

    if (b > 35) {
        work->angle = 0x53;
        work->lookAngle = 0x53;
        work->lookColumn = work->angle;
    }

    SetPoohPalette(work, b);
}

void task_poo_pooh_0(PoohWork* work) {
    PooShadowArgs args;

    sPooWork = work;
    work->unk_CC = 0;
    GetPooStateGauge(&gPoohGauge, &gPoohGaugeTimer);
    work->targetNode = NULL;
    work->lookTimer = 0;
    gPoohRequest = 0;
    work->callTimer = 0;
    work->callCount = 0;
    work->angle = 45;
    work->lookAngle = 45;
    work->lookColumn = work->angle;
    SetPoohDir5Right(work);
    work->speed = 0;
    work->flipped = 0;
    work->animAction = 0xFFFF;
    GetPooStatePooh(&work->pos, &sPoohAction);
    work->pos.ground = 0;
    work->targetX = work->pos.x;
    work->targetY = work->pos.y;
    gPoohPos = &work->pos;
    work->tiles = AllocObjTiles(gPoohHitBox.tileCount * 32, NULL);
    work->palette = LoadObjPalette(gPoohHitBox.palette, 32);
    AnimInit(&work->anim, NULL, NULL);
    SetPoohAction(work, sPoohAction);
    work->hideShadow = 0;
    SetPoohAnimation(work, sPoohAction);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 9, gPoohHitBox.radius, gPoohHitBox.height);
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
    TaskPoolInit(&work->tasks, 10);
    args.pos = &work->pos;
    args.shadowInfo = &work->shadowInfo;
    TaskCreate(&work->tasks, &gTaskDescPooShadowdodai, &args);
    work->task = NULL;
    work->zzzTask = NULL;
    work->groundZ = GetPooGroundZ(&work->collider, &work->pos, &work->onCollider);
}

u8 HandlePoohRequest(PoohWork* work) {
    if (gPoohRequest == 1) {
        SetPoohAction(work, 16);
        work->pos.x = gPoohRequestX;
        work->pos.y = gPoohRequestY;
    } else if (gPoohRequest == 2) {
        work->pos.x = gPoohRequestX;
        work->pos.y = gPoohRequestY;
        SetPoohAction(work, 38);
    } else if (gPoohRequest == 7) {
        work->pos.x = gPoohRequestX;
        work->pos.y = gPoohRequestY;
        SetPoohAction(work, 39);
    } else if (gPoohRequest == 8) {
        work->angle = GetAngle(work->pos.x, work->pos.y, gPoohRequestX, gPoohRequestY);
        work->lookAngle = work->angle;
        work->lookColumn = work->angle;
        SetPoohAction(work, 20);
    } else if (gPoohRequest == 11) {
        work->angle = GetAngle(work->pos.x, work->pos.y, gPoohRequestX, gPoohRequestY);
        work->lookAngle = work->angle;
        work->lookColumn = work->angle;
        work->leavingWagon = 0;
        SetPoohAction(work, 21);
    } else if (gPoohRequest == 3) {
        SetPoohAction(work, 32);
    } else if (gPoohRequest == 4 || gPoohRequest == 6) {
        SetPoohAction(work, 0);
    } else if (gPoohRequest == 5) {
        SetPoohAction(work, 10);
    } else if (gPoohRequest == 9) {
        SetPoohAction(work, 12);
    } else if (gPoohRequest == 10) {
        SetPoohAction(work, 11);
    } else if (gPoohRequest == 12) {
        gPoohRequest = 0;
        return 0;
    } else {
        SetPoohAction(work, 10);
    }

    gPoohRequest = 0;
    return 1;
}

u8 CheckPoohInterrupts(PoohWork* work, PooNode* n) {
    if (ColliderIsTouchingType(&work->collider, 1)) {
        if (!IsPooSoraOverWagon()) {
            SetPoohAction(work, 10);
            return 1;
        }
    }

    if (gPoohRequest != 0) {
        return HandlePoohRequest(work);
    }

    return 0;
}

void ChoosePoohTarget(PoohWork* work, PooNode* n) {
    if (n != NULL) {
        if (IsPooSoraCallStarting()) {
            if (work->callTimer != 0 || work->targetNode == gPooSoraNode) {
                work->callCount++;

                if (work->callCount > 10) {
                    work->callTimer = 0;
                    work->callCount = 0;
                    SetPoohAction(work, 29);
                }

                return;
            }

            work->callTimer = 90;
        }

        if (work->callTimer != 0) {
            work->callTimer--;
            n = gPooSoraNode;
        }

        if (work->targetNode != n && work->lookTimer <= 59) {
            work->lookAngle = work->angle;
            work->lookColumn = work->angle;
            work->lookTarget = GetAngle(work->pos.x, work->pos.y, ((PooPos*)n->pos)->x, ((PooPos*)n->pos)->y);
            work->targetX = work->pos.x;
            work->targetY = work->pos.y;
            SetPoohAction(work, 9);
        } else {
            work->targetNode = n;
            work->lookTimer = 0;
            work->targetX = ((PooPos*)work->targetNode->pos)->x;
            work->targetY = ((PooPos*)work->targetNode->pos)->y;
            SetPoohAction(work, 3);
        }
    } else {
        work->targetX = work->pos.x;
        work->targetY = work->pos.y;
        SetPoohAction(work, 23);
    }
}

void ApplyPoohFrameOffset(PoohWork* work, const PooSpot* b, u16 c) {
    u16 f;
    s32 v;
    s32 i;

    f = AnimGetFrame(&work->anim) + 1;

    if (!work->collider.colliding) {
        i = work->dirIndex * c + f;
        v = b[i].x;

        if (work->flipped != 0) {
            v = -v;
        }

        work->pos.x += v;
        v = b[i].y;
        work->pos.y += v;
    }

    work->pos.z += b[work->dirIndex * c + f].z;
}

void ApplyPooh04FrameOffset(PoohWork* work) {
    ApplyPoohFrameOffset(work, sPooh04FrameOffsets, 11);
}

void ApplyPooh04aFrameOffset(PoohWork* work) {
    ApplyPoohFrameOffset(work, sPooh04aFrameOffsets, 0x10);
}

s32 GetPoohStumpIndex(PoohWork* work) {
    PooPoint t[4];
    u32 i;

    memcpy(t, sPoohStumpCircle, sizeof(t));

    for (i = 0; i < 4; i++) {
        if (work->collider.platformX == t[i].x && work->collider.platformY == t[i].y) {
            break;
        }
    }

    return i;
}

void ResetPoohStumpCount(PoohWork* work) {
    work->stumpCount = 0;
    work->stumpIndex = GetPoohStumpIndex(work);
}

u32 NextPoohStumpIndex(u32 a) {
    a++;

    if (a > 3) {
        a = 0;
    }

    return a;
}

void UpdatePoohStumpCircle(PoohWork* work) {
    s32 t;

    t = GetPoohStumpIndex(work);

    if (t == NextPoohStumpIndex(work->stumpIndex)) {
        work->stumpIndex = t;
        work->stumpCount++;

        if (work->stumpCount > 3) {
            if (!IsPooEventDone(1)) {
#ifdef VERSION_EU
                ExitPoohMode(0x8B);
#else
                ExitPoohMode(0x8D);
#endif
                SetPooEventDone(1);
                SetJiminyFlag(0x52);
            }
        }
    } else {
        ResetPoohStumpCount(work);
    }
}

s32 GetPooGroundZ(Collider* w, PooPos* p, u8* c) {
    s32 v;

    if ((w->standFlags & COLLIDER_STAND_OVER_PLATFORM) != 0) {
        if (p->ground < w->platformZ) {
            v = p->ground;
        } else {
            v = w->platformZ;
        }

        *c = 1;
    } else {
        *c = 0;
        v = p->ground;
    }

    return v;
}

void MovePooh(PoohWork* work, s32 b, u8 c) {
    work->speed += 6;

    if (work->speed > b) {
        work->speed = b;
    }

    if (c) {
        work->lookAngle = work->angle = GetAngle(work->pos.x, work->pos.y, work->targetX, work->targetY);
        work->lookColumn = work->angle;
    }

    work->pos.x += gSineTable[work->angle] * work->speed >> 8;
    work->pos.y += -gSineTable[work->angle + 0x40] * work->speed >> 8;
}

u8 IsPoohNearScreenEdge() {
    s16 x;
    s16 y;

    x = (gPoohPos->x >> 8) - gPooScrollX;
    y = (gPoohPos->y >> 8) + (gPoohPos->z >> 8) - gPooScrollY;

    if (x < gPoohHitBox.radius * 2 || 240 - gPoohHitBox.radius * 2 < x || y < gPoohHitBox.height * 2 || y > 152) {
        return 1;
    }

    return 0;
}

void UpdatePoohAction(PoohWork* work, PooNode* n) {
    u16 a0;
    u16 a1;
    u16 a2;
    u16 v;
    u16 c;
    s32 b;

    switch (sPoohAction) {
    case 3:
        if (AnimGetGfxIndex(&work->anim) == 8 && gPoohPos->y > 0x1BD00 && (GetKeysPressed() & A_BUTTON) != 0) {
            v = 128;

            if (IsPooCabbageGameActive()) {
                v = 2;
            }

            if (GetRandom() % v == 0) {
                SetPoohAction(work, 17);
            }

            break;
        }

        b = 0x4C;

        if (IsPooSoraCalling() && work->targetNode == n && n == gPooSoraNode) {
            b = 152;
            work->speed = 152;
        } else if (work->speed > 82) {
            b = work->speed - 6;
        }

        MovePooh(work, b, 1);

        if (CheckPoohInterrupts(work, n)) {
            work->speed = 0;
        } else {
            ChoosePoohTarget(work, n);
        }

        break;
    case 10:
        if (work->collider.colliding) {
            if (ColliderIsTouchingType(&work->collider, 1)) {
                break;
            }

            if (!IsPooSoraCallStarting()) {
                break;
            }

            work->pos.x += work->collider.pushX;
            work->pos.y += work->collider.pushY;
            work->targetNode = NULL;
            ChoosePoohTarget(work, n);
            break;
        }

        if (GetPooManhattanDistance(&work->pos, &gPooActor.pos) > 0x1B00) {
            SetPoohAction(work, 0);
        }

        break;
    case 12:
        a0 = work->lookAngle;
        work->lookTarget = GetAngle(work->pos.x, work->pos.y, 0x8DE00, 0x45C00);
        ApproachAngle(&a0, work->lookTarget, 4);
        work->lookAngle = a0;
        work->lookTimer++;

        if (!AreAllPooBeesOut()) {
            break;
        }

        SetPoohAction(work, 15);
        work->angle = 64;
        work->lookAngle = 64;
        work->lookColumn = work->angle;
        break;
    case 15:
        work->pos.z += work->vz;
        work->vz += 71;

        if (work->pos.z < 0) {
            break;
        }

        work->pos.z = 0;
        SetPoohAction(work, 5);
        work->speed = 228;
        break;
    case 5:
        work->targetX = 0x87F00;
        work->targetY = 0x4B700;
        MovePooh(work, 456, 1);

        if (!IsWithinPoohRadius(work->targetX >> 8, work->targetY >> 8, work->pos.x >> 8, work->pos.y >> 8)) {
            break;
        }

        SetPoohAction(work, 6);
        break;
    case 6:
        work->targetX = 0x75D00;
        work->targetY = 0x49E00;
        MovePooh(work, 456, 1);

        if (!IsWithinPoohRadius(work->targetX >> 8, work->targetY >> 8, work->pos.x >> 8, work->pos.y >> 8)) {
            break;
        }

        SetPoohAction(work, 14);
        BtlMapStartShake();
        m4aSongNumStart(SONG_SND_372);
        break;
    case 0:
        if (work->pos.z < 0) {
            SetPoohAction(work, 1);
            break;
        }

        ChoosePoohTarget(work, n);

        if (sPoohAction != 0) {
            break;
        }

        if (work->targetNode == NULL) {
            break;
        }

        c = GetPooNodeWeight(work->targetNode);

        if (c <= 1) {
            break;
        }

        c >>= 1;
        SetPooNodeWeight(work->targetNode, c);
        break;
    case 29:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 30);
        break;
    case 30:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        if (work->actionTimer <= 1) {
            work->actionTimer++;
            AnimReset(&work->anim);
            break;
        }

        if (!AnimIsFrameEnding(&work->anim)) {
            break;
        }

        if (AnimGetFrame(&work->anim) != 0) {
            break;
        }

        SetPoohAction(work, 31);
        break;
    case 31:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 9);
        break;
    case 9:
        if (work->lookTimer <= 59) {
            a1 = work->lookAngle;
            work->lookTarget = GetAngle(work->pos.x, work->pos.y, ((s32*)n->pos)[0], ((s32*)n->pos)[1]);
            ApproachAngle(&a1, work->lookTarget, 4);
            work->lookAngle = a1;
            work->lookTimer++;
        } else {
            ChoosePoohTarget(work, n);
        }

        break;
    case 16:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        if (work->pos.x == 0x4A700 && work->pos.y == 0x28E00 && !IsPooEventDone(5)) {
            SetPoohAction(work, 37);
            TaskCreate(&work->tasks, &gTaskDescPooRoo, &work->pos);
            break;
        }

        SetPoohAction(work, 36);
        break;
    case 37:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 38);
        work->pos.z -= 0x1700;
        StartPooCameraFollowPooh();
        break;
    case 36:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 38);
        break;
    case 38:
        if (work->balloonTimer <= 59) {
            work->pos.z -= 204;
        } else if (work->balloonTimer <= 79) {
            work->pos.z -= 204;
        } else {
            work->pos.z += 204;
        }

        if (work->balloonTimer > 60) {
            work->pos.x += 128;
            work->pos.y += 64;
        }

        work->balloonTimer++;

        if (work->balloonTimer > 80 && work->pos.z >= -0x800 && IsTaskActive(work->task)) {
            TaskKill(&work->tasks, work->task);
            TaskCreate(&work->tasks, &gTaskDescPooFreeballoon, &work->pos);
            gPoohRequest = 0;
        }

        if (work->pos.z < 0) {
            break;
        }

        work->pos.z = 0;

        if (ColliderIsTouchingType(&work->collider, 1)) {
            SetPoohAction(work, 0);
            break;
        }

        if (gPoohRequest == 0) {
            SetPoohAction(work, 0);
            break;
        }

        HandlePoohRequest(work);
        break;
    case 39:
        work->pos.z -= 204;

        if (work->pos.z > -0xD500) {
            break;
        }

        if (IsTaskActive(work->task)) {
            TaskKill(&work->tasks, work->task);
        }

        SetPoohAction(work, 22);
        break;
    case 22:
        if (work->pos.z < -0x1000) {
            work->pos.z += 204;
            break;
        }

        if (!IsPooEventDone(3)) {
#ifdef VERSION_EU
            ExitPoohMode(135);
#else
            ExitPoohMode(137);
#endif
            SetPooEventDone(3);
            SetJiminyFlag(79);
        } else {
#ifdef VERSION_EU
            ExitPoohMode(136);
#else
            ExitPoohMode(138);
#endif
        }

        break;
    case 17:
        if (AnimIsFinished(&work->anim)) {
            if (work->actionTimer > 40) {
                SetPoohAction(work, 18);
                ApplyPooh04aFrameOffset(work);
                work->pos.z = 0;
            }

            work->actionTimer++;
            break;
        }

        if (AnimIsFrameEnding(&work->anim)) {
            ApplyPooh04FrameOffset(work);
        }

        work->actionTimer = 0;
        break;
    case 18:
        if (AnimIsFinished(&work->anim)) {
            SetPoohAction(work, 0);
            break;
        }

        if (!AnimIsFrameEnding(&work->anim)) {
            break;
        }

        ApplyPooh04aFrameOffset(work);
        break;
    case 21:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        if (work->dirIndex == 0) {
            if (work->flipped != 0) {
                work->angle = 19;
            } else {
                work->angle = 224;
            }
        } else {
            if (work->flipped != 0) {
                work->angle = 83;
            } else {
                work->angle = 147;
            }
        }

        work->lookAngle = work->angle;
        work->lookColumn = work->angle;
        work->hopAngle = work->angle;
        SetPoohAction(work, 2);
        work->vz = 0;
        work->pos.z = -0xD00;

        if (work->flipped == 0) {
            work->pos.x -= 0x900;
        } else {
            work->pos.x += 0x900;
        }

        if (!work->leavingWagon) {
            ClampToPooWagonArea((u32*)&work->pos.x, (u32*)&work->pos.y, 1);
            break;
        }

        while ((u8)IsInPooWagonAreaForPooh(&work->pos)) {
            work->pos.x += gSineTable[work->angle] * 2;
            work->pos.y -= gSineTable[work->angle + 0x40] * 2;
        }

        break;
    case 2:
        work->pos.z += work->vz;
        work->vz += 17;

        if (work->pos.z < 0) {
            break;
        }

        work->pos.z = 0;

        if (!work->leavingWagon) {
            SetPoohAction(work, 13);
            break;
        }

        SetPoohAction(work, 0);
        gPoohRequest = 0;
        break;
    case 13:
        if (!IsPooSoraCallStarting()) {
            break;
        }

        if ((u8)IsInPooWagonArea(&gPooActor.pos)) {
            break;
        }

        work->angle = work->hopAngle + 128;
        work->lookAngle = work->angle;
        work->lookColumn = work->angle;
        SetPoohAction(work, 21);
        work->leavingWagon = 1;
        break;
    case 20:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 8);
        ResetPoohStumpCount(work);
        work->pos.z -= 0xE00;
        work->lookAngle = work->angle;
        work->lookColumn = work->angle;

        if (work->flipped == 0) {
            work->pos.x -= 0x900;
        } else {
            work->pos.x += 0x900;
        }

        break;
    case 8:
        work->onCollider = 1;

        if (!IsPooSoraCallStarting()) {
            break;
        }

        if (IsPoohNearScreenEdge()) {
            break;
        }

        SetPoohAction(work, 7);
        break;
    case 11:
        if (work->actionTimer <= 179) {
            a2 = work->lookAngle;
            work->lookTarget = GetAngle(work->pos.x, work->pos.y, 0x8DE00, 0x45C00);
            ApproachAngle(&a2, work->lookTarget, 4);
            work->lookAngle = a2;
            work->actionTimer++;
        } else {
            work->angle += 128;
            work->lookAngle = work->angle;
            work->lookColumn = work->angle;
            SetPoohAction(work, 4);
        }

        break;
    case 4:
        if (work->actionTimer > 119) {
            SetPoohAction(work, 0);
            break;
        }

        work->actionTimer++;
        MovePooh(work, 76, 0);
        break;
    case 7:
        if (work->onCollider != 0) {
            work->targetX = gPooActor.pos.x;
            work->targetY = gPooActor.pos.y;
            MovePooh(work, 76, 1);
            break;
        }

        work->targetX = gPooActor.pos.x;
        work->targetY = gPooActor.pos.y;
        work->angle = GetAngle(work->pos.x, work->pos.y, work->targetX, work->targetY);
        work->vz = -0x130;
        work->speed = 237;
        SetPoohAction(work, 19);
        break;
    case 19:
        if (AnimIsFinished(&work->anim) && work->onCollider != 0 && work->pos.z < -0x100) {
            SetPoohAction(work, 8);
            UpdatePoohStumpCircle(work);
            break;
        }

        if (AnimGetFrame(&work->anim) == 2 && work->anim.timer == 0) {
            m4aSongNumStart(SONG_SND_960);
        }

        if ((AnimGetFrame(&work->anim) > 1 && AnimGetFrame(&work->anim) <= 4) ||
            (AnimGetFrame(&work->anim) > 4 && work->onCollider == 0 && work->pos.z < work->groundZ)) {
            work->pos.x += gSineTable[work->angle] * work->speed >> 8;
            work->pos.y += -gSineTable[work->angle + 0x40] * work->speed >> 8;
        }

        if (AnimGetFrame(&work->anim) <= 1) {
            break;
        }
    case 1:
        work->pos.z += work->vz;
        work->vz += 17;

        if (work->pos.z >= work->groundZ) {
            work->pos.z = work->groundZ;
        }

        if (AnimIsFinished(&work->anim)) {
            SetPoohAction(work, 0);
        }

        break;
    case 23:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 24);
        break;
    case 24:
        if (work->actionTimer <= 119) {
            work->actionTimer++;

            if (!IsPooSoraCallStarting()) {
                break;
            }

            if (IsPoohNearScreenEdge()) {
                break;
            }

            if (gPoohGauge != 0) {
                SetPoohAction(work, 28);
            }
        } else {
            SetPoohAction(work, 25);
        }

        break;
    case 25:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 26);
        work->sleepTimer = gPoohGaugeTimer * 1800 / 1851;
        break;
    case 26:
        if (IsPooSoraCallStarting() && !IsPoohNearScreenEdge() && gPoohGauge != 0) {
            SetPoohAction(work, 27);

            if (!IsTaskActive(work->zzzTask)) {
                break;
            }

            TaskKill(&work->tasks, work->zzzTask);
            break;
        }

        if (!IsTaskActive(work->zzzTask)) {
            work->zzzTask = TaskCreate(&work->tasks, &gTaskDescPooZzz, &work->flipped);
        }

        if (gPoohGauge == 0) {
            work->sleepTimer++;

            if (work->sleepTimer > 1800) {
                gPoohGauge++;
                gPoohGaugeTimer = 1851;
                work->sleepTimer = 0;
            }

            if (gPoohGauge > 3) {
                gPoohGauge = 3;
            }
        }

        break;
    case 27:
        if (AnimIsFinished(&work->anim)) {
            SetPoohAction(work, 28);
        }

        break;
    case 28:
        if (AnimIsFinished(&work->anim)) {
            SetPoohAction(work, 0);
        }

        break;
    case 32:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        if (gPoohGauge == 1) {
            SetPoohAction(work, 33);
        } else if (gPoohGauge == 2) {
            SetPoohAction(work, 34);
        } else {
            SetPoohAction(work, 35);
        }

        break;
    case 33:
    case 34:
    case 35:
        if (!AnimIsFinished(&work->anim)) {
            break;
        }

        SetPoohAction(work, 28);
        work->pos.x -= 0x400;
        work->pos.y += 0x300;
        break;
    }
}

void UpdatePoohGauge(PoohWork* work) {
    if (sPoohAction == 3) {
        if (gPoohGauge != 0) {
            gPoohGaugeTimer--;
        }

        if (gPoohGaugeTimer == 0) {
            if (gPoohGauge == 0) {
                SetPoohAction(work, 0x17);
            } else {
                gPoohGauge--;

                if (gPoohGauge == 0) {
                    SetPoohAction(work, 0x17);
                } else {
                    gPoohGaugeTimer = 0x73B;
                }
            }
        }
    }
}

u8 IsPoohOffScreen() {
    s32 x;
    s32 y;

    x = (gPoohPos->x >> 8) - gPooScrollX;
    y = (gPoohPos->y >> 8) + (gPoohPos->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, gPoohHitBox.height, 0, gPoohHitBox.radius, gPoohHitBox.radius)) {
        return 1;
    }

    return 0;
}

u8 task_poo_pooh_1(PoohWork* work) {
    PooNode* n;

    work->groundZ = GetPooGroundZ(&work->collider, &work->pos, &work->onCollider);

    if (IsPoohNearScreenEdge()) {
        n = NULL;
    } else {
        n = FindPoohTargetNode();
    }

    work->hideShadow = 0;
    UpdatePoohAction(work, n);
    UpdatePoohGauge(work);
    SetPoohAnimation(work, sPoohAction);
    work->gfx = AnimUpdate(&work->anim);

    if (sPoohAction == 3 || sPoohAction == 7) {
        if (work->anim.timer == 0) {
            switch (AnimGetFrame(&work->anim)) {
            case 9:
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                break;
            case 3:
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                break;
            }
        }
    }

    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_pooh_2(PoohWork* work) {
    s16 x;
    s16 y;
    s32 f;
    u16 p;

    x = (work->pos.x >> 8) - gPooScrollX;
    y = (work->pos.y >> 8) + (work->pos.z >> 8) - gPooScrollY;

    if (work->flipped != 0) {
        f = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    } else {
        f = SPRITE_PRIORITY(2);
    }

    if (sPoohAction == 20 && work->dirIndex == 1) {
        if (AnimGetFrame(&work->anim) <= 4) {
            p = -0x1003 - ((gPoohRequestY - 0x500) >> 8) * 4;
            work->shadowInfo.z = 0;
        } else {
            p = -0x1005 - ((gPoohRequestY - 0x500) >> 8) * 4;
            work->shadowInfo.priority = 0;
        }
    } else if (IsPoohOnWagon()) {
        p = GetPooWagonPriority() - 4;
        work->shadowInfo.priority = p + 1;
        work->shadowInfo.z = 0;
    } else if ((u8)GetPooWagonSide(gPoohPos->x, gPoohPos->y) != 0) {
        if (sPoohAction == 21 && work->dirIndex == 1 && work->leavingWagon) {
            p = GetPooWagonPriority2() - 3;
        } else if ((u8)GetPooWagonSide(gPoohPos->x, gPoohPos->y) == 83 || (u8)GetPooWagonSide(gPoohPos->x, gPoohPos->y) == 173) {
            if (gPoohPos->y < gPooActor.pos.y) {
                p = GetPooWagonPriority() + 5;
            } else {
                p = GetPooWagonPriority() + 1;
            }
        } else {
            if (gPoohPos->y < gPooActor.pos.y) {
                p = GetPooWagonPriority2() - 2;
            } else {
                p = GetPooWagonPriority2() - 6;
            }
        }

        work->shadowInfo.priority = p + 1;
        work->shadowInfo.z = 0;
    } else if (work->onCollider != 0) {
        p = -0x1008 - (work->collider.platformY >> 8) * 4;

        if (work->pos.y >= gPooActor.pos.y) {
            p -= 2;
        } else {
            p += 2;
        }

        if (work->collider.penetration <= work->collider.radius || work->collider.other->radius == 0x400) {
            if (work->collider.platformZ != 0) {
                work->shadowInfo.priority = 0;
            } else {
                work->shadowInfo.priority = p + 1;
            }

            work->shadowInfo.z = 0;
        } else {
            work->shadowInfo.z = work->collider.platformZ;
            work->shadowInfo.priority = p + 1;
        }
    } else {
        p = -0x1004 - (work->pos.y >> 8) * 4;
        work->shadowInfo.z = 0;

        if (work->shadowInfo.z != work->pos.ground) {
            work->shadowInfo.priority = 0;
        } else {
            work->shadowInfo.priority = 0xFFF0;
        }
    }

    if (work->hideShadow) {
        work->shadowInfo.priority = 0;
    }

    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, f, p);
    TaskPoolDraw(&work->tasks);
}

void task_poo_pooh_3(PoohWork* work) {
    if (sPoohAction == 22) {
        sPoohAction = 0;
        work->pos.z = 0;
        work->pos.y += 0x2000;
    } else if (sPoohAction == 14) {
        sPoohAction = 0;
        work->pos.x = 0x7F700;
        work->pos.y = 0x47E00;
        work->pos.z = 0;
    }

    SetPooStatePooh(&work->pos, sPoohAction);
    SetPooStateGauge(gPoohGauge, gPoohGaugeTimer);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
}

u8 IsPoohDescendingWithOwl() {
    if (sPoohAction == 22) {
        return 1;
    }

    return 0;
}

u8 IsPoohOnOwlBalloon() {
    if (sPoohAction == 39) {
        return 1;
    }

    return 0;
}

u8 IsPoohWalkingToTarget() {
    if (sPoohAction == 3) {
        return 1;
    }

    return 0;
}

u8 IsPoohBeeChaseOver() {
    if (sPoohAction == 14) {
        return 1;
    }

    return 0;
}

u8 IsPoohWaitingOnWagon() {
    if (sPoohAction == 13) {
        return 1;
    }

    return 0;
}

u8 IsPoohOnWagon() {
    PoohWork* w;

    if (sPoohAction == 13) {
        return 1;
    }

    if (sPoohAction == 2) {
        if (sPooWork->leavingWagon) {
            return 0;
        }

        return 1;
    }

    if (sPoohAction != 21) {
        return 0;
    }

    w = sPooWork;

    if (w->leavingWagon) {
        if (w->dirIndex != 1) {
            return 1;
        }

        if (AnimGetFrame(&w->anim) > 4) {
            return 0;
        }

        return 1;
    }

    if (w->dirIndex == 0) {
        return 0;
    }

    if (AnimGetFrame(&w->anim) <= 4) {
        return 0;
    }

    return 1;
}

u8 IsPoohAtLowerExit() {
    if (GetPooExitAt(gPoohPos) == 2) {
        return 1;
    }

    return 0;
}

u16 GetPoohHoneyAnim() {
    if (sPoohAction == 0x21) {
        return 0;
    }

    if (sPoohAction == 0x22) {
        return 1;
    }

    if (sPoohAction == 0x23) {
        return 2;
    }

    return 3;
}

u8 IsPoohLookingAtHoneycomb() {
    if (sPoohAction == 12) {
        return 1;
    }

    return 0;
}

void CreatePooPileTasks(void* pool) {
    u32 i;

    for (i = 0; i < 12; i++) {
        CreatePooPileTask(pool, gPooPileDescs[i].kind, gPooPileDescs[i].x, gPooPileDescs[i].y);
    }
}

u16 CreatePooMapobjhitTasks(void* pool, u16 b) {
    u32 i;

    for (i = 0; i < 80; i++) {
        CreatePooMapobjhitTask(pool, gPooTileDescs[i].kind, gPooTileDescs[i].x, gPooTileDescs[i].y, b);
        b++;
    }

    return b;
}

u16 CreatePooSpawnTasks(void* pool, u16 b) {
    u32 i;

    for (i = 0; i < 85; i++) {
        sPooSpawnPos.x = gPooSpawns[i].x;
        sPooSpawnPos.y = gPooSpawns[i].y;
        sPooSpawnPos.z = 0;

        if (gPooSpawns[i].desc == &gTaskDescPooTanpopo || gPooSpawns[i].desc == &gTaskDescPooLeaf) {
            sPooSpawnArgs.pos = sPooSpawnPos;
            sPooSpawnArgs.prizeId = b;
            TaskCreate(pool, gPooSpawns[i].desc, &sPooSpawnArgs);
            b++;
        } else {
            TaskCreate(pool, gPooSpawns[i].desc, &sPooSpawnPos);
        }
    }

    return b;
}

void SetPooCameraFocus(s32 a, s32 b) {
    gPooCameraFocusX = a;
    gPooCameraFocusY = b;
}

void UpdatePooCameraCenter() {
    s32 y;

    if (sPooCameraFrozen) {
        return;
    }

    if (sPooCameraFollowPooh) {
        SetPooCameraFocus(gPoohPos->x, gPoohPos->y + gPoohPos->z);
    }

    y = gPoohPos->y + gPoohPos->z;

    if ((gPooCameraFocusX - gPoohPos->x >= 0 ? gPooCameraFocusX - gPoohPos->x < 0xF000
                                                    : gPoohPos->x - gPooCameraFocusX < 0xF000) &&
        (gPooCameraFocusY - y >= 0 ? gPooCameraFocusY - y < 0xA000 : y - gPooCameraFocusY < 0xA000)) {
        gPooCameraX = (gPooCameraFocusX + gPoohPos->x) / 2;
        gPooCameraY = (gPooCameraFocusY + y) / 2;
    } else {
        gPooCameraX = gPooCameraFocusX;
        gPooCameraY = gPooCameraFocusY;
    }
}

void FreezePooCamera() {
    sPooCameraFrozen = 1;
}

void UnfreezePooCamera() {
    sPooCameraFrozen = 0;
}

void StartPooCameraFollowPooh() {
    sPooCameraFollowPooh = 1;
}

void StopPooCameraFollowPooh() {
    sPooCameraFollowPooh = 0;
}

void task_poo_map_0(PooMapWork* work) {
    PooPos p;
    s32 n;

    UnfreezePooCamera();
    StopPooCameraFollowPooh();
    GetPooStatePooh(&p, &n);
    gPoohPos = &p;
    UpdatePooCameraCenter();
    sPooCameraMaxY = gPooCameraY;
    gPooScrollX = (gPooCameraX >> 8) - 120;
    gPooScrollY = (gPooCameraY >> 8) - 80;
    gFieldState->x = gPooScrollX << 8;
    gFieldState->y = gPooScrollY << 8;
    work->mapWidth = gPooMapBgDesc.mapWidth;
    work->mapHeight = gPooMapBgDesc.mapHeight;
    TaskPoolInit(&work->tasks, 178);
    CreatePooMapobjhitTasks(&work->tasks, CreatePooSpawnTasks(&work->tasks, 0));
    CreatePooPileTasks(&work->tasks);
    TaskCreate(&work->tasks, &gTaskDescPooMapanime, NULL);
    LoadBgTiles(3, gPooMapBgDesc.tiles, gPooMapBgDesc.tilesSize);
    LoadBgTiles(2, gPooMapBgDesc.tiles2, gPooMapBgDesc.tilesSize2);
    LoadBgPalette(3, gPooMapBgDesc.palette, gPooMapBgDesc.paletteSize);
    SetBgMapBlocks(3, gPooBg3MapBlocks, work->mapWidth, work->mapHeight);
    RedrawBgMapAt(3, gPooScrollX, gPooScrollY);
    func_080CA35C();
    SetBgMapBlocks(1, gPooBg1MapBlocks, work->mapWidth, work->mapHeight);
    RedrawBgMapAt(1, gPooScrollX, gPooScrollY);
    SetBgMapBlocks(2, gPooBg2MapBlocks, work->mapWidth, work->mapHeight);
    RedrawBgMapAt(2, gPooScrollX, gPooScrollY);
    BtlMapResetShake();
}

u8 task_poo_map_1(PooMapWork* work) {
    UpdatePooCameraCenter();
    ScrollPooCamera(work);
    ScrollBgMapTo(3, gPooScrollX, gPooScrollY);
    ScrollBgMapTo(1, gPooScrollX, gPooScrollY);
    ScrollBgMapTo(2, gPooScrollX, gPooScrollY);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_map_2(PooMapWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_poo_map_3(PooMapWork* work) {
    TaskPoolDestroy(&work->tasks);
}

void ScrollPooCamera(PooMapWork* work) {
    s32 tx;
    s32 ty;

    BtlMapUpdateShake();
    tx = gPooCameraX - 0x7800;
    ty = gPooCameraY - 0x5000;

    if (ty < 0) {
        ty = 0;
    }

    if (gPooCameraX + 0x7800 > 0xEDF00) {
        tx = 0xDEF00;
    }

    if (ty + 0xA000 > 0x83000) {
        ty = 0x79000;
    }

    tx = (tx - (gPooScrollX << 8)) >> 3;
    ty = (ty - (gPooScrollY << 8)) >> 3;

    if (tx > 0x300) {
        tx = 0x300;
    } else if (tx < -0x300) {
        tx = -0x300;
    }

    if (ty > 0x300) {
        ty = 0x300;
    } else if (ty < -0x300) {
        ty = -0x300;
    }

    if (abs(tx) <= 50) {
        tx = 0;
    }

    if (abs(ty) <= 50) {
        ty = 0;
    }

    gPooScrollX += tx >> 8;
    gPooScrollY += ty >> 8;
    gPooScrollY += BtlMapGetShake() >> 8;
    gFieldState->x = gPooScrollX << 8;
    gFieldState->y = gPooScrollY << 8;
}

void func_080CA35C() {
    gUnk_0203C3F4 = 0;
}

void func_080CA368(s32 a, u16 b, u16 c) {
}

u16 GetPooMapTile(u16 x, u16 y) {
    const u16** t;
    u32 bx;
    u32 by;
    u32 tx;
    u32 ty;

    t = gPooBg3MapBlocks;
    bx = x >> 8;
    by = y >> 8;
    tx = (x >> 3) & 0x1F;
    ty = (y >> 3) & 0x1F;
    return t[by * 16 + bx][ty * 32 + tx];
}

u8 IsPooPosBlocked(PooPos* p) {
    u32 v;

    v = GetPooMapTile(p->x >> 8, p->y >> 8) & 0x3FF;

    if ((u16)(v - 1) <= 8) {
        return 0;
    }

    if ((u16)(v - 0x20) <= 9) {
        return 0;
    }

    if ((u16)(v - 0x40) <= 9) {
        return 0;
    }

    if ((u16)(v - 0x1E0) > 0x5F) {
        return 1;
    }

    return 0;
}

u8 GetPooWallSlide(PooActor* p, s32 x, s32 y, s32* ox, s32* oy) {
    PooPos t;
    s32 s;
    s32 c;
    s32 m;
    s32 v;
    u8 a;

    if (IsPooPosBlocked(&p->pos)) {
        a = p->angle + 0x40;
        s = gSineTable[a];
        c = -gSineTable[a + 0x40];
        t.x = s * 4 + x;
        t.y = c * 4 + y;
        t.z = p->pos.z;
        t.ground = p->pos.ground;
        m = p->speed;

        if (m > 0x200) {
            m = 0x200;
        }

        if (!IsPooPosBlocked(&t)) {
            *ox = s * m >> 8;
            *oy = c * m >> 8;
            return 1;
        } else {
            a = p->angle - 0x40;
            s = gSineTable[a];
            c = -gSineTable[a + 0x40];
            t.x = s * 4 + x;
            t.y = c * 4 + y;

            if (!IsPooPosBlocked(&t)) {
                *ox = s * m >> 8;
                *oy = c * m >> 8;
                return 1;
            } else {
                v = 0;
                *ox = v;
                *oy = v;
                return 1;
            }
        }
    }

    return 0;
}

u8 GetPooScreenOverflow(s16 x, s16 y, s16 h, s16 vy, s16 w, s16 vx, s32* ox, s32* oy) {
    s32 t;
    s32 r;

    r = 0;
    *oy = 0;
    *ox = 0;
    t = x + vx;

    if (t >= 0) {
        t = x - w;

        if (t > 0xF0) {
            t -= 0xF0;
            *ox = t << 8;
            r = 1;
        }
    } else {
        *ox = t << 8;
        r = 1;
    }

    t = y + vy;

    if (t >= 0) {
        t = y - h;

        if (t > 0xA0) {
            t -= 0xA0;
            *oy = t << 8;
            r = 1;
        }
    } else {
        *oy = t << 8;
        r = 1;
    }

    return r;
}

u8 ConstrainPooActorMove(PooActor* a, s32 x, s32 y) {
    s16 sx;
    s16 sy;

    if (GetPooWallSlide(a, x, y, &sPooMoveAdjustX, &sPooMoveAdjustY)) {
        a->pos.x = x + sPooMoveAdjustX;
        a->pos.y = y + sPooMoveAdjustY;
    }

    sx = (x >> 8) - gPooScrollX;
    sy = (y >> 8) - gPooScrollY;

    if (!GetPooScreenOverflow(sx, sy, 48, 0, 18, 18, &sPooMoveAdjustX, &sPooMoveAdjustY)) {
        sx = (a->pos.x >> 8) - gPooScrollX;
        sy = (a->pos.y >> 8) - gPooScrollY;

        if (GetPooScreenOverflow(sx, sy, 48, 0, 18, 18, &sPooMoveAdjustX, &sPooMoveAdjustY)) {
            a->pos.x -= sPooMoveAdjustX;
            a->pos.y -= sPooMoveAdjustY;
        }
    } else {
        a->pos.x = x;
        a->pos.y = y;
    }

    return 1;
}

u8 IsPooExitTile(PooPos* p) {
    if ((GetPooMapTile(p->x >> 8, p->y >> 8) & 0x3FF) > 0x3BA) {
        return 1;
    }

    return 0;
}

u16 GetPooExitAt(PooPos* p) {
    if (IsPooExitTile(p)) {
        if (p->y <= 0x1FFFF) {
            return 1;
        }

        return 2;
    }

    return 0;
}

void MovePooCamera(s32 a, s32 b) {
    gPooCameraX += a;
    gPooCameraY += b;

    if (sPooCameraMaxY < gPooCameraY) {
        gPooCameraY = sPooCameraMaxY;
    }

    gPooScrollX = (gPooCameraX >> 8) - 120;
    gPooScrollY = (gPooCameraY >> 8) - 80;
    gFieldState->x = gPooScrollX << 8;
    gFieldState->y = gPooScrollY << 8;
    ScrollBgMapTo(3, gPooScrollX, gPooScrollY);
    ScrollBgMapTo(1, gPooScrollX, gPooScrollY);
    ScrollBgMapTo(2, gPooScrollX, gPooScrollY);
}

void SetPooActorAngleFromDpad(PooActor* p) {
    if ((GetKeysHeld() & DPAD_LEFT) != 0 && (GetKeysHeld() & DPAD_DOWN) != 0) {
        p->angle = 0xAD;
    } else if ((GetKeysHeld() & DPAD_UP) != 0 && (GetKeysHeld() & DPAD_LEFT) != 0) {
        p->angle = 0xD3;
    } else if ((GetKeysHeld() & DPAD_UP) != 0 && (GetKeysHeld() & DPAD_RIGHT) != 0) {
        p->angle = 0x2D;
    } else if ((GetKeysHeld() & DPAD_RIGHT) != 0 && (GetKeysHeld() & DPAD_DOWN) != 0) {
        p->angle = 0x53;
    } else if ((GetKeysHeld() & DPAD_DOWN) != 0 && GetKeyReleaseTime(DPAD_LEFT) <= 4) {
        p->angle = 0xAD;
    } else if ((GetKeysHeld() & DPAD_DOWN) != 0 && GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
        p->angle = 0x53;
    } else if ((GetKeysHeld() & DPAD_UP) != 0 && GetKeyReleaseTime(DPAD_LEFT) <= 4) {
        p->angle = 0xD3;
    } else if ((GetKeysHeld() & DPAD_UP) != 0 && GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
        p->angle = 0x2D;
    } else if ((GetKeysHeld() & DPAD_LEFT) != 0 && GetKeyReleaseTime(DPAD_UP) <= 4) {
        p->angle = 0xD3;
    } else if ((GetKeysHeld() & DPAD_LEFT) != 0 && GetKeyReleaseTime(DPAD_DOWN) <= 4) {
        p->angle = 0xAD;
    } else if ((GetKeysHeld() & DPAD_RIGHT) != 0 && GetKeyReleaseTime(DPAD_UP) <= 4) {
        p->angle = 0x2D;
    } else if ((GetKeysHeld() & DPAD_RIGHT) != 0 && GetKeyReleaseTime(DPAD_DOWN) <= 4) {
        p->angle = 0x53;
    } else if ((GetKeysHeld() & DPAD_DOWN) != 0) {
        p->angle = 0x80;
    } else if ((GetKeysHeld() & DPAD_UP) != 0) {
        p->angle = 0;
    } else if ((GetKeysHeld() & DPAD_LEFT) != 0) {
        p->angle = 0xC0;
    } else if ((GetKeysHeld() & DPAD_RIGHT) != 0) {
        p->angle = 0x40;
    }
}

u8 ApplyPooSoraPushOut(PooSoraWork* work, PooPos* p) {
    if (work->collider.colliding && !ColliderIsTouchingType(&work->collider, 5) && !ColliderIsTouchingType(&work->collider, 3) && !ColliderIsTouchingType(&work->collider, 5) && !ColliderIsTouchingType(&work->collider, 11)) {
        if (IsPooSoraOverWagon()) {
            p->x += work->collider.pushX;
            p->y += work->collider.pushY;
            SnapToPooWagonLine((u32*)&p->x, (u32*)&p->y, 1);
        } else {
            p->x += work->collider.pushX;
            p->y += work->collider.pushY;
        }

        return 1;
    }

    return 0;
}

u8 GetPooAngleToPooh(PooPos* p) {
    u8 a;

    a = GetAngle(p->x, p->y, gPoohPos->x, gPoohPos->y);

    switch (((a + 16) & 0xFF) >> 5) {
    case 1:
        return 0x2D;
    case 2:
        return 0x40;
    case 3:
        return 0x53;
    case 4:
        return 0x80;
    case 5:
        return 0xAD;
    case 6:
        return 0xC0;
    case 7:
        return 0xD3;
    case 0:
    default:
        return 0;
    }
}

void UpdatePooActorAngle(PooActor* p) {
    u8 old;

    old = p->angle;
    SetPooActorAngleFromDpad(p);

    if (old != p->angle) {
        if (abs((s8)GetAngleDiff(old, p->angle)) > 100) {
            p->speed = 0;
        } else {
            p->speed >>= 1;
        }
    }
}

s32 GetPooSoraGroundZ(PooSoraWork* work) {
    PooPos* p;
    s32 v;

    p = &gPooActor.pos;

    if ((work->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) != 0) {
        if (p->ground < work->collider.platformZ) {
            v = p->ground;
        } else {
            v = work->collider.platformZ;
        }

        work->onCollider = 1;
    } else {
        work->onCollider = 0;
        v = p->ground;
    }

    return v;
}

void SetPooSoraAnimation(PooSoraWork* work, s32 b, u16 c) {
    const PooAnimDesc* e;
    s32 d;

    switch (gPooActor.angle) {
    case 0x2D:
        d = 4;
        work->flags |= POO_SORA_FLAG_FLIP_X;
        break;
    case 0x40:
        d = 3;
        work->flags |= POO_SORA_FLAG_FLIP_X;
        break;
    case 0x53:
        d = 2;
        work->flags |= POO_SORA_FLAG_FLIP_X;
        break;
    case 0x80:
        d = 1;
        work->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0xAD:
        d = 2;
        work->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0xC0:
        d = 3;
        work->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0xD3:
        d = 4;
        work->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0x00:
    default:
        d = 0;
        work->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    }

    if (work->animAction == b) {
        c |= 4;
    }

    work->animAction = b;
    e = &gPooSoraAnimDescs[b][d];
    AnimChangeWithTables(&work->anim, (u8)e->animId, c, e->unk_04, e->unk_00);
    SetObjTileSource(work->tiles, e->tiles);
}

void SetPooSoraAttackPoint(PooActor* p) {
    s32 x;
    s32 y;

    switch (p->angle) {
    case 0x2D:
    case 0xD3:
        x = p->pos.x + gSineTable[p->angle] * 12;
        y = p->pos.y + -gSineTable[p->angle + 0x40] * 12;
        break;
    case 0x40:
    case 0xC0:
        x = p->pos.x + gSineTable[p->angle] * 27;
        y = p->pos.y + -gSineTable[p->angle + 0x40] * 27;
        break;
    case 0x00:
    case 0x53:
    case 0x80:
    case 0xAD:
    default:
        x = p->pos.x + gSineTable[p->angle] * 20;
        y = p->pos.y + -gSineTable[p->angle + 0x40] * 20;
        break;
    }

    SetPooAttackPoint(x, y, p->pos.z - 0x800);
}

void task_poo_sora_0(PooSoraWork* work) {
    PooActor* a = &gPooActor;

    gPooSoraCollider = &work->collider;
    gPooSoraNode = &work->node;
    sPooSoraWork = work;
    work->tiles = AllocObjTiles(0xA00, NULL);
    work->palette = LoadObjPalette(gSoraPalette, 32);
    a->height = 16;
    work->onCollider = 0;
    work->timer = 0;
    work->flags = 0;
    work->animAction = 12;
    a->unk_32 = 0;
    a->kind = 0;
    GetPooStatePos2(&a->pos);
    a->angle = 0xAD;
    a->pos.ground = 0;
    a->speed = 0;
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    AnimInit(&work->anim, NULL, NULL);
    SetPooSoraAnimation(work, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);
    work->sounds = gPooSoraSounds;
    TaskPoolInit(&work->tasks, 2);
    gFieldState = EwramAlloc(sizeof(FieldState));
    TaskCreate(&work->tasks, &gTaskDescFldShadow, a);
    AddPooNode(&work->node, 1, a);
    ColliderInit(&work->collider, 1, 18, 48);
    ColliderSetPosition(&work->collider, a->pos.x, a->pos.y, a->pos.z);
}

u8 PooSoraUpdateJump(PooSoraWork* work, Task* t) {
    PooActor* a = &gPooActor;
    PooPos p;
    s32 z;
    s32 sx;
    s32 sy;
    u16 k;
    u16 v;

    z = GetPooSoraGroundZ(work);
    sx = a->pos.x;
    sy = a->pos.y;
    UpdatePooActorAngle(a);

    switch (work->state) {
    case 7:
        if (work->timer == 0) {
            SetPooSoraAnimation(work, 10, 0);
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;

        if (AnimGetFrame(&work->anim) > 3) {
            a->pos.z += work->vz;
            work->vz += 66;

            if (a->pos.z > z) {
                a->pos.z = z;
                work->vz = 0;
            }
        } else {
            work->vz = 0;
        }

        a->speed -= 38;

        if (a->speed < 0) {
            a->speed = 0;
        }

        switch (AnimGetFrame(&work->anim)) {
        case 3:
        case 4:
            SetPooSoraAttackPoint(a);
            break;
        }

        if (AnimIsFinished(&work->anim)) {
            if (work->vz < 0) {
                work->state = 3;
            } else {
                work->state = 4;
            }
        } else {
            work->timer++;
        }

        break;
    case 2:
        if (work->timer == 0) {
            SetPooSoraAnimation(work, 3, 0);
            a->speed >>= 1;
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;

        if (work->timer > 3) {
            if (GetRandom() % 2 != 0) {
                m4aSongNumStart(SONG_SYS_SR_I_VO00);
            } else {
                m4aSongNumStart(SONG_SYS_SR_I_VO01);
            }

            work->state = 3;
            work->vz = -0x533;
            a->speed <<= 1;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 3:
        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            a->speed += 17;

            if (a->speed > 0x200) {
                a->speed = 0x200;
            }
        } else {
            a->speed -= 38;

            if (a->speed < 0) {
                a->speed = 0;
            }
        }

        if (work->vz > -0x200) {
            SetPooSoraAnimation(work, 5, 0);
        } else {
            SetPooSoraAnimation(work, 4, 0);
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;
        a->pos.z += work->vz;
        work->vz += 66;

        if (work->vz < 0) {
            if ((GetKeysHeld() & B_BUTTON) == 0) {
                work->vz += 64;
            }
        }

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            work->timer = 0;
            work->state = 7;
        } else if (work->vz > 0) {
            work->timer = 0;
            work->state = 4;
        } else {
            work->timer++;
        }

        break;
    case 4:
        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            a->speed += 17;

            if (a->speed > 0x200) {
                a->speed = 0x200;
            }
        } else {
            a->speed -= 38;

            if (a->speed < 0) {
                a->speed = 0;
            }
        }

        if (work->vz < 0x200) {
            SetPooSoraAnimation(work, 5, 0);
        } else {
            SetPooSoraAnimation(work, 6, 0);
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;
        a->pos.z += work->vz;
        work->vz += 66;

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            work->timer = 0;
            work->state = 7;
        } else if (a->pos.z > z) {
            a->pos.z = z;
            work->vz = 0;

            if (work->state != 5) {
                work->state = 5;
                work->timer = 0;
            }
        }

        break;
    case 5:
        if (work->timer == 0) {
            SetPooSoraAnimation(work, 7, 0);
            m4aSongNumStart(work->sounds[3]);
        }

        a->speed = 0;
        k = GetKeysPressed() & B_BUTTON;

        if (k != 0) {
            work->timer = 0;
            work->state = 2;
        } else if (work->timer > 6) {
            work->state = 0;
            work->timer = 0;
            SetTaskUpdate(t, (TaskUpdateFunc)task_poo_sora_1);
        } else {
            work->timer++;
        }

        break;
    }

    if (ApplyPooSoraPushOut(work, &a->pos)) {
        a->speed = a->speed * 230 >> 8;
    }

    ConstrainPooActorMove(a, sx, sy);

    if ((u8)IsInPooWagonArea(&a->pos)) {
        if (a->pos.z > -0xA00) {
            p.x = sx;
            p.y = sy;

            if (!(u8)IsInPooWagonArea(&p)) {
                a->pos.x = sx;
                a->pos.y = sy;
                a->speed = 0;
            } else if (work->vz >= 0) {
                a->speed = 0;
                v = (-a->pos.z >> 8) + 1;
                SnapToPooWagonLine((u32*)&a->pos, (u32*)&a->pos.y, v);
            }
        }
    }

    ColliderSetPosition(&work->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 PooSoraUpdateAttack(PooSoraWork* work, Task* t) {
    PooActor* a = &gPooActor;
    s32 sx;
    s32 sy;

    sx = a->pos.x;
    sy = a->pos.y;

    if (work->state == 6) {
        if (work->timer == 0) {
            SetPooSoraAnimation(work, 9, 0);
            a->speed = 0;
            m4aSongNumStart(SONG_SYS_SR_AT_VO00);
        }

        if (work->anim.timer == 0) {
            switch (a->angle) {
            case 0xAD:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x -= 0x500;
                    a->pos.y += 0x400;
                    break;
                case 1:
                    a->pos.x -= 0x200;
                    break;
                case 2:
                    a->pos.x -= 0x300;
                    break;
                }

                break;
            case 0x53:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x += 0x500;
                    a->pos.y += 0x400;
                    break;
                case 1:
                    a->pos.x += 0x200;
                    break;
                case 2:
                    a->pos.x += 0x300;
                    break;
                }

                break;
            case 0xD3:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x -= 0x500;
                    a->pos.y -= 0x200;
                    break;
                case 1:
                    a->pos.x -= 0x500;
                    break;
                case 2:
                    a->pos.x -= 0x200;
                    break;
                }

                break;
            case 0x2D:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x += 0x500;
                    a->pos.y -= 0x200;
                    break;
                case 1:
                    a->pos.x += 0x500;
                    break;
                case 2:
                    a->pos.x += 0x200;
                    break;
                }

                break;
            case 0x80:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x -= 0x300;
                    a->pos.y += 0x400;
                    break;
                case 1:
                    a->pos.x += 0x100;
                    a->pos.y += 0x100;
                    break;
                case 2:
                    a->pos.y += 0x200;
                    break;
                case 3:
                    a->pos.y += 0x100;
                    break;
                }

                break;
            case 0x40:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x += 0x700;
                    a->pos.y += 0x100;
                    break;
                case 1:
                    a->pos.x += 0x300;
                    break;
                case 2:
                    a->pos.x += 0x200;
                    break;
                }

                break;
            case 0xC0:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.x -= 0x700;
                    a->pos.y += 0x100;
                    break;
                case 1:
                    a->pos.x -= 0x300;
                    break;
                case 2:
                    a->pos.x -= 0x200;
                    break;
                }

                break;
            case 0:
                switch (AnimGetFrame(&work->anim)) {
                case 0:
                    a->pos.y -= 0x400;
                    break;
                case 1:
                    a->pos.y -= 0x400;
                    break;
                case 2:
                    a->pos.x -= 0x100;
                    a->pos.y += 0x100;
                    break;
                case 3:
                    a->pos.y -= 0x100;
                    break;
                }

                break;
            }
        }

        if (work->timer > 14) {
            SetPooSoraAttackPoint(a);
        }

        if (AnimIsFinished(&work->anim)) {
            switch (a->angle) {
            case 0xAD:
                a->pos.x -= 0x200;
                a->pos.y += 0x200;
                break;
            case 0x53:
                a->pos.x += 0x200;
                a->pos.y += 0x200;
                break;
            case 0xD3:
            case 0x2D:
                a->pos.y -= 0x400;
                break;
            case 0x80:
                a->pos.y += 0x200;
                break;
            case 0:
                a->pos.y -= 0x200;
                break;
            }

            SetPooSoraAnimation(work, 0, 0);
            work->state = 0;
            SetTaskUpdate(t, (TaskUpdateFunc)task_poo_sora_1);
        } else {
            work->timer++;
        }
    }

    ApplyPooSoraPushOut(work, &a->pos);
    ConstrainPooActorMove(a, sx, sy);

    if ((u8)IsInPooWagonArea(&a->pos)) {
        a->pos.x = sx;
        a->pos.y = sy;
        a->speed = 0;
    }

    ColliderSetPosition(&work->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 PooSoraUpdateCall(PooSoraWork* work, Task* t) {
    PooActor* a = &gPooActor;
    s32 x;
    s32 y;
    u16 keys;

    x = a->pos.x;
    y = a->pos.y;

    if (work->state == 8) {
        if (work->timer == 0) {
            SetPooSoraAnimation(work, 8, 1);
            a->speed = 0;
        }

        if (work->timer > 29) {
            keys = GetKeysHeld() & R_BUTTON;

            if (keys != 0) {
                work->timer = 0;
            } else {
                work->timer = 0;
                work->state = 0;
                SetTaskUpdate(t, (TaskUpdateFunc)task_poo_sora_1);
            }
        } else {
            work->timer++;
        }
    }

    ApplyPooSoraPushOut(work, &a->pos);
    ConstrainPooActorMove(a, x, y);

    if ((u8)IsInPooWagonArea(&a->pos)) {
        a->pos.x = x;
        a->pos.y = y;
        a->speed = 0;
    }

    ColliderSetPosition(&work->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 task_poo_sora_1(PooSoraWork* work, Task* t) {
    PooActor* a = &gPooActor;
    s32 z;
    s32 sx;
    s32 sy;
    u16 v;

    z = GetPooSoraGroundZ(work);
    sx = a->pos.x;
    sy = a->pos.y;

    if (work->state <= 1) {
        UpdatePooActorAngle(a);

        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            a->speed += 128;
            SetPooSoraAnimation(work, 2, 1);

            if (a->speed > 0x266) {
                a->speed = 0x266;
            }

            if (work->anim.timer == 0) {
                switch (work->anim.frame) {
                case 3:
                    m4aSongNumStart(work->sounds[0]);
                    break;
                case 7:
                    m4aSongNumStart(work->sounds[1]);
                    break;
                }
            }
        } else {
            SetPooSoraAnimation(work, 0, 1);
            a->speed -= 128;

            if (a->speed < 0) {
                a->speed = 0;
            }
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;

        if ((GetKeysPressed() & B_BUTTON) != 0) {
            work->timer = 0;
            work->state = 2;
            SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateJump);
            m4aSongNumStart(work->sounds[2]);
        } else if ((GetKeysPressed() & A_BUTTON) != 0) {
            SetPooSoraAttackPoint(a);
            gPooAttackActive = 0;
            v = FindPoohInteractionMessage();

#ifdef VERSION_EU
            if (v != 179) {
#else
            if (v != 180) {
#endif
                OpenPoohModeMessage(v);
            } else {
                work->timer = 0;
                work->state = 6;
                SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateAttack);
            }
        } else if ((GetKeysPressed() & R_BUTTON) != 0) {
            work->timer = 0;
            work->state = 8;
            SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateCall);
            a->angle = GetPooAngleToPooh(&a->pos);
        }
    } else if (AnimIsFinished(&work->anim)) {
        work->state = 0;
    }

    if (CheckPooSoraExit(&a->pos) != 0) {
        a->speed = 0;
    }

    if (ApplyPooSoraPushOut(work, &a->pos)) {
        a->speed = a->speed * 230 >> 8;
    }

    ConstrainPooActorMove(a, sx, sy);

    if ((u8)IsInPooWagonArea(&a->pos)) {
        a->pos.x = sx;
        a->pos.y = sy;
        a->speed = 0;
    }

    if (z != a->pos.z) {
        a->speed >>= 2;
        work->vz = 0;
        work->timer = 0;
        work->state = 4;
        SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateJump);
    }

    ColliderSetPosition(&work->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_sora_2(PooSoraWork* work) {
    PooActor* a = &gPooActor;
    s32 prio;
    s32 c;
    s32 ac;
    s16 x;
    s16 y;

    c = work->flags & POO_SORA_FLAG_FLIP_X;
    prio = SPRITE_PRIORITY(2);

    if (c != 0) {
        prio = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    ac = work->onCollider;

    if (ac != 0) {
        sPooSoraPriority = -0x1008 - (work->collider.platformY >> 8) * 4;

        if (work->collider.penetration <= work->collider.radius || work->collider.other->radius == 0x400) {
            if (work->collider.platformZ != 0) {
                a->shadowPriority = 0;
            } else {
                a->shadowPriority = sPooSoraPriority + 1;
            }

            a->shadowZ = 0;
        } else {
            a->shadowZ = work->collider.platformZ;
            a->shadowPriority = sPooSoraPriority + 1;
        }
    } else {
        sPooSoraPriority = -0x1008 - (a->pos.y >> 8) * 4;
        a->shadowZ = 0;

        if (ac != a->pos.ground) {
            a->shadowPriority = 0;
        } else {
            a->shadowPriority = sPooSoraPriority + 1;
        }
    }

    x = (a->pos.x >> 8) - gPooScrollX;
    y = (a->pos.y >> 8) + (a->pos.z >> 8) - gPooScrollY;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, prio, sPooSoraPriority - 1);
    TaskPoolDraw(&work->tasks);
}

void task_poo_sora_3(PooSoraWork* work) {
    SetPooStatePos2(&gPooActor.pos);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
    EwramFree(gFieldState);
    RemovePooNode(&work->node);
}

u8 IsPooSoraCallStarting() {
    if (sPooSoraWork->state == 8 && sPooSoraWork->timer == 0) {
        return 1;
    }

    return 0;
}

u8 IsPooSoraCalling() {
    if (sPooSoraWork->state == 8) {
        return 1;
    }

    return 0;
}

u8 AreAllPooEventsDone() {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (!IsPooEventDone(i)) {
            return 0;
        }
    }

    return 1;
}

u16 CheckPooSoraExit(PooPos* p) {
    u16 r;

    r = GetPooExitAt(p);
    ClearPooFlag(3);

    if (r == 1) {
        OpenPoohModeMessage(0xFFFE);
    } else if (r == 2) {
        SetJiminyFlag(13);

        if (!IsPoohOffScreen()) {
            SetPooFlag(3);

            if (AreAllPooEventsDone()) {
                if (IsPooFlagSet(1)) {
#ifdef VERSION_EU
                    ExitPoohMode(0x91);
#else
                    ExitPoohMode(0x93);
#endif
                } else if (!IsPooFlagSet(0)) {
                    SetPooFlag(0);
                    SetPooFlag(1);
                    SetJiminyFlag(77);
#ifdef VERSION_EU
                    ExitPoohMode(0x8D);
#else
                    ExitPoohMode(0x8F);
#endif
                } else {
                    SetPooFlag(1);
                    SetJiminyFlag(77);
#ifdef VERSION_EU
                    ExitPoohMode(0x8F);
#else
                    ExitPoohMode(0x91);
#endif
                }
            } else if (!IsPooFlagSet(0)) {
                SetPooFlag(0);
                SetJiminyFlag(77);
#ifdef VERSION_EU
                ExitPoohMode(0x8E);
#else
                ExitPoohMode(0x90);
#endif
            } else {
#ifdef VERSION_EU
                ExitPoohMode(0x90);
#else
                ExitPoohMode(0x92);
#endif
            }
        } else {
            OpenPoohModeMessage(0xFFFD);
        }
    }

    return r;
}

u16 GetPooSoraPriority() {
    return sPooSoraPriority - 1;
}

void task_poo_trap_0(PooTrapWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y;
    work->z = 0;
    work->tiles = LoadObjTiles(gPooTrapTiles, 0x100);
    work->palette = LoadObjPalette(gPooTrapPalette, 0x20);
    work->gfx = gPooTrapFrame0;
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    work->colliderActive = 0;
}

u8 task_poo_trap_1(PooTrapWork* work) {
    if (work->colliderActive) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequestX = work->x;
            gPoohRequestY = work->y;
            gPoohRequest = 1;
        }
    }

    return 1;
}

void task_poo_trap_2(PooTrapWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (x < -16 || x > 256 || y < -16 || y > 176) {
        if (work->colliderActive) {
            ColliderUnregister(&work->collider);
            work->colliderActive = 0;
        }
    } else {
        if (!work->colliderActive) {
            ColliderInit(&work->collider, 10, 8, 16);
            work->colliderActive = 1;
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 0xFFEF);
    }
}

void task_poo_trap_3(PooTrapWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    if (work->colliderActive) {
        ColliderUnregister(&work->collider);
    }
}

void task_poo_pitAndButterfly_0(PooTrapWork* work, PooPos* p) {
    task_poo_trap_0(work, p);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescPooButterfly, &work->x);
    AddPooNode(&work->node, 0xE10, &work->x);
}

u8 task_poo_pitAndButterfly_1(PooTrapWork* work) {
    task_poo_trap_1(work);

    if (work->colliderActive) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            SetPooNodeWeight(&work->node, 0);
        }
    }

    return 1;
}

void task_poo_pitAndButterfly_2(PooTrapWork* work) {
    task_poo_trap_2(work);

    if (work->colliderActive) {
        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_pitAndButterfly_3(PooTrapWork* work) {
    task_poo_trap_3(work);
    TaskPoolDestroy(&work->tasks);
    RemovePooNode(&work->node);
}

void task_poo_balloon_0(PooBalloonObjWork* work, PooPos* p) {
    work->pos = p;

    if (p->x == 0x3FD00 && p->y == 0x21B00) {
        work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gPooBalloonFrames, 3), gPooBalloonTiles);
        work->palette = LoadObjPalette(gPooBalloonPalette, 0x20);
        AnimInit(&work->anim, gPooBalloonAnims, gPooBalloonFrames);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    } else {
        work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gTrap0006Frames, 4), gTrap0006Tiles);
        work->palette = LoadObjPalette(gPooTrapBalloonPalette, 0x20);
        AnimInit(&work->anim, gTrap0006Anims, gTrap0006Frames);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    }

    work->gfx = AnimGetGfx(&work->anim);
}

u8 task_poo_balloon_1(void* w) {
    return 1;
}

void task_poo_balloon_2(PooBalloonObjWork* work) {
    s16 x;
    s16 y;

    x = (work->pos->x >> 8) - gPooScrollX;
    y = (work->pos->y >> 8) + (work->pos->z >> 8) - gPooScrollY;

    if (x >= -16 && x <= 256 && y >= -16 && y <= 176) {
        work->gfx = AnimUpdate(&work->anim);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->pos->y >> 8) * 4);
    }
}

void task_poo_balloon_3(PooBalloonObjWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_poo_shadow_0(TaskPool* w, void* arg) {
    PooShadowArgs args;

    args.pos = arg;
    args.scale = 0xA6;
    TaskPoolInit(w, 1);
    TaskCreate(w, &gTaskDescPooShadowscale, &args);
}

u8 task_poo_shadow_1(TaskPool* w) {
    TaskPoolUpdate(w);
    return 1;
}

void task_poo_shadow_2(TaskPool* w) {
    TaskPoolDraw(w);
}

void task_poo_shadow_3(TaskPool* w) {
    TaskPoolDestroy(w);
}

void task_poo_shadowdodai_0(PooShadowWork* work, PooShadowArgs* a) {
    work->pos = a->pos;
    work->shadowInfo = a->shadowInfo;
    work->x = work->pos->x;
    work->y = work->pos->y;
    work->tiles = LoadObjTiles(gBtlShadowTiles, 0x100);
    work->palette = LoadObjPalette(gCommonObjPalette, 0x20);
    AnimInit(&work->anim, gBtlShadowAnims, gBtlShadowFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimUpdate(&work->anim);
}

u8 task_poo_shadowdodai_1(PooShadowWork* work) {
    work->x = work->pos->x;
    work->y = work->pos->y;
    return 1;
}

void task_poo_shadowdodai_2(PooShadowWork* work) {
    s32 s;
    ObjAffine* aff;
    s32 h;
    s16 x;
    s16 y;

    if (work->shadowInfo->priority != 0) {
        h = work->shadowInfo->z;

        if (work->pos->z >= h) {
            s = 0xA6;
        } else {
            s = 0xA6 - (h - work->pos->z) / 128;

            if (s <= 0x18) {
                s = 0x19;
            }
        }

        aff = AllocObjAffine(0, s, s, 0);
        x = (work->x >> 8) - gPooScrollX;
        y = (work->y >> 8) + (h >> 8) - gPooScrollY;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, SPRITE_PRIORITY(2), work->shadowInfo->priority);
    }
}

void task_poo_shadowdodai_3(PooShadowWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_poo_shadowscale_0(PooScaleWork* work, PooShadowArgs* a) {
    work->pos = a->pos;
    work->x = work->pos->x;
    work->y = work->pos->y;
    work->scale = a->scale;
    work->tiles = LoadObjTiles(gBtlShadowTiles, 0x100);
    work->palette = LoadObjPalette(gCommonObjPalette, 0x20);
    AnimInit(&work->anim, gBtlShadowAnims, gBtlShadowFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimUpdate(&work->anim);
}

u8 task_poo_shadowscale_1(PooScaleWork* work) {
    work->x = work->pos->x;
    work->y = work->pos->y;
    return 1;
}

void task_poo_shadowscale_2(PooScaleWork* work) {
    s32 s;
    ObjAffine* affine;
    u16 x;
    u16 y;

    if (work->pos->z >= 0) {
        s = work->scale;
    } else {
        s = work->scale + work->pos->z / 128;

        if (s <= 0x18) {
            s = 0x19;
        }
    }

    affine = AllocObjAffine(0, s, s, 0);
    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, SPRITE_PRIORITY(2), 0xFFF0);
}

void task_poo_shadowscale_3(PooScaleWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void CreatePooShadowscaleTask(void* pool, void* a, s32 b) {
    PooShadowArgs args;

    args.pos = a;
    args.scale = b;
    TaskCreate(pool, &gTaskDescPooShadowscale, &args);
}

void task_poo_freeballoon_0(PooFreeBalloonWork* work, PooPos* p) {
    work->pos2 = *p;
    work->pos4 = *p;
    work->pos3 = *p;
    work->pos5 = *p;
    work->pos = p;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gTrap0004Frames, 4), gTrap0004Tiles);
    work->palette = LoadObjPalette(gTrap0004Palette, 0x20);
    AnimInit(&work->anim, gTrap0004Anims, gTrap0004Frames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->tiles2 = AllocObjTiles(GetMaxSpriteTileBytes(gTrap0005Frames, 4), gTrap0005Tiles);
    work->palette2 = LoadObjPalette(gPooFreeBalloonPalette, 0x20);
    AnimInit(&work->anim2, gTrap0005Anims, gTrap0005Frames);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    work->timer = 0;
}

u8 IsPooNearScreen(s16 x, s16 y) {
    if (x < -64 || x > 304) {
        return 0;
    }

    if (y < -64) {
        return 0;
    }

    if (y <= 224) {
        return 1;
    }

    return 0;
}

u8 task_poo_freeballoon_1(PooFreeBalloonWork* work) {
    u16 t;

    work->timer++;

    if (work->timer > 5) {
        t = work->timer - 5;
        work->pos4.x = work->pos5.x - t * 256;
        work->pos4.y = work->pos5.y - ((t * t) << 8) / 32;
    } else {
        work->pos4 = *work->pos;
        work->pos5 = *work->pos;
    }

    work->pos2.x = work->pos3.x + work->timer * 256;
    work->pos2.y = work->pos3.y - ((work->timer * work->timer) << 8) / 32;
    work->x2 = (work->pos4.x >> 8) - gPooScrollX;
    work->y2 = (work->pos4.y >> 8) + (work->pos4.z >> 8) - gPooScrollY;
    work->x = (work->pos2.x >> 8) - gPooScrollX;
    work->y = (work->pos2.y >> 8) + (work->pos2.z >> 8) - gPooScrollY;

    if (IsPooNearScreen(work->x2, work->y2)) {
        work->gfx2 = AnimUpdate(&work->anim2);
    } else {
        work->gfx2 = NULL;
    }

    if (IsPooNearScreen(work->x, work->y)) {
        work->gfx = AnimUpdate(&work->anim);
    } else {
        work->gfx = NULL;
    }

    if (work->gfx == NULL && work->gfx2 == NULL) {
        return 0;
    }

    return 1;
}

void task_poo_freeballoon_2(PooFreeBalloonWork* work) {
    if (work->gfx2 != NULL) {
        DrawSprite(work->x2, work->y2, work->gfx2, work->tiles2, work->palette2, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->pos4.y >> 8) * 4);
    }

    if (work->gfx != NULL) {
        DrawSprite(work->x, work->y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->pos2.y >> 8) * 4);
    }
}

void task_poo_freeballoon_3(PooFreeBalloonWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjPalette(work->palette2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

s32 GetPooGaugeFrame(u16 x) {
    s32 v;
    u32 a;
    u8 c;

    a = x;
    v = 3 - gPoohGauge;

    if (gPoohGaugeTimer <= 0x1CD) {
        c = (a / 20) & 1;

        if (c != 0) {
            if (v <= 2) {
                v++;
            }
        }
    }

    return v;
}

void task_poo_gauge_0(PooGaugeWork* work) {
    work->blinkTimer = 0;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gPooGaugeFrames, 4), gPooGaugeTiles);
    work->palette = LoadObjPalette(gPoohGaugePalette, 0x20);
    work->paletteSrc = gPoohGaugePalette;
    work->gfx = gPooGaugeFrames[GetPooGaugeFrame(work->blinkTimer)];
    work->warning = 0;
}

u8 task_poo_gauge_1(PooGaugeWork* work) {
    work->blinkTimer++;
    work->gfx = gPooGaugeFrames[GetPooGaugeFrame(work->blinkTimer)];

    if (gPoohGauge <= 1 && gPoohGaugeTimer <= 0x1CD) {
        work->warning = 1;
    } else {
        work->warning = 0;
    }

    if (work->warning) {
        if (work->paletteSrc != gPooGaugePalette) {
            LoadObjPaletteBank(work->palette->index, gPooGaugePalette);
            work->paletteSrc = gPooGaugePalette;
        }
    }

    if (!work->warning) {
        if (work->paletteSrc != gPoohGaugePalette) {
            LoadObjPaletteBank(work->palette->index, gPoohGaugePalette);
            work->paletteSrc = gPoohGaugePalette;
        }
    }

    return 1;
}

void task_poo_gauge_2(PooGaugeWork* work) {
    DrawSprite(0xDC, 0x18, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 0);
}

void task_poo_gauge_3(PooGaugeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_poo_trapballoon_0(PooBalloonWork* work, PooPos* p) {
    work->pos = *p;
    work->pos.z = 0;
    work->pos.ground = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gTrap0006Frames, 4);
    work->palette = NULL;
    AnimInit(&work->anim, gTrap0006Anims, gTrap0006Frames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 3);
    work->task = TaskCreate(&work->tasks, &gTaskDescPooShadow, &work->pos);
    work->freeBalloonTask = NULL;
    work->angle = GetRandom();
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
}

u8 task_poo_trapballoon_1(PooBalloonWork* work) {
    PooPos t;

    if (work->palette == NULL) {
        return 1;
    }

    if (IsTaskActive(work->freeBalloonTask)) {
        return 1;
    }

    if (!IsTaskActive(work->task) && !IsTaskActive(work->freeBalloonTask)) {
        return 0;
    }

    if (ColliderIsTouchingType(&work->collider, 9) && IsPoohWalkingToTarget()) {
        gPoohRequestX = work->pos.x;
        gPoohRequestY = work->pos.y;
        gPoohRequest = 2;
        SetPooNodeWeight(&work->node, 0);
        return 0;
    }

    if (!gPooAttackActive) {
        if (!ColliderIsTouchingType(&work->collider, 9)) {
            return 1;
        }

        if (IsPoohWalkingToTarget()) {
            return 1;
        }
    }

    if (!PooAttackHitsCollider(&work->collider)) {
        return 1;
    }

    t = work->pos;
    t.z -= 0x1000;
    TaskCreate(&work->tasks, &gTaskDescPooSpark, &t);
    SetPooNodeWeight(&work->node, 0);
    ColliderSetDisabled(&work->collider, 1);
    TaskKill(&work->tasks, work->task);
    work->pos.x -= 0x800;
    work->pos.y += 0x1000;
    work->freeBalloonTask = TaskCreate(&work->tasks, &gTaskDescPooFreeballoon, &work->pos);
    m4aSongNumStart(SONG_SYS_PO_BLOON);
    return 1;
}

void task_poo_trapballoon_2(PooBalloonWork* work) {
    s32 d;
    s16 x;
    s16 y;

    if (IsTaskActive(work->freeBalloonTask)) {
        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    } else {
        work->gfx = AnimUpdate(&work->anim);
        work->angle += 2;
        d = SIN(work->angle) * 2;
        x = ((work->pos.x - 0x800) >> 8) - gPooScrollX;
        d += 0x1200;
        y = ((work->pos.y + d) >> 8) + (work->pos.z >> 8) - gPooScrollY;

        if (IsRectOutsideScreen(x, y, 64, 8, 24, 24)) {
            if (work->palette != NULL) {
                ReleaseObjTiles(work->tiles);
                ReleaseObjPalette(work->palette);
                work->palette = NULL;
                ColliderUnregister(&work->collider);
                RemovePooNode(&work->node);
            }
        } else {
            if (work->palette == NULL) {
                work->tiles = AllocObjTiles(work->tileBytes, gTrap0006Tiles);
                work->palette = LoadObjPalette(gPooTrapBalloonPalette, 0x20);
                ColliderInit(&work->collider, 10, 8, 16);
                AddPooNode(&work->node, 0x400, &work->pos);
            }

            DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->pos.y >> 8) * 4);
            TaskPoolUpdate(&work->tasks);
            TaskPoolDraw(&work->tasks);
        }
    }
}

void task_poo_trapballoon_3(PooBalloonWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
        RemovePooNode(&work->node);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_owlballoon_0(PooOwlBalloonWork* work, PooPos* p) {
    work->pos = *p;
    work->pos.z = 0;
    work->pos.ground = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gPooBalloonFrames, 3);
    work->palette = NULL;
    AnimInit(&work->anim, gPooBalloonAnims, gPooBalloonFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 2);
    work->task = TaskCreate(&work->tasks, &gTaskDescPooShadow, &work->pos);
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
    AddPooNode(&work->node, 0x240, &work->pos);
}

u8 task_poo_owlballoon_1(PooOwlBalloonWork* work) {
    if (work->palette != NULL && ColliderIsTouchingType(&work->collider, 9) && IsPoohWalkingToTarget()) {
        gPoohRequestX = work->pos.x;
        gPoohRequestY = work->pos.y;
        gPoohRequest = 7;
        SetPooNodeWeight(&work->node, 0);
        m4aSongNumStart(SONG_SND_385);
        return 0;
    }

    return 1;
}

void task_poo_owlballoon_2(PooOwlBalloonWork* work) {
    s16 x;
    s16 y;

    work->gfx = AnimUpdate(&work->anim);
    x = ((work->pos.x - 0x800) >> 8) - gPooScrollX;
    y = ((work->pos.y + 0x1000) >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 64, 8, 24, 24)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gPooBalloonTiles);
            work->palette = LoadObjPalette(gPooBalloonPalette, 0x20);
            ColliderInit(&work->collider, 10, 8, 16);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1003 - (work->pos.y >> 8) * 4);
        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_owlballoon_3(PooOwlBalloonWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
    RemovePooNode(&work->node);
}

u16 GetPooNodeWeight(PooNode* n) {
    return n->weight;
}

void SetPooNodeWeight(PooNode* n, u16 v) {
    n->weight = v;
}

u16 GetPooNodeBaseWeight(PooNode* n) {
    return n->baseWeight;
}

void SetPooNodeBaseWeight(PooNode* n, u16 v) {
    n->baseWeight = v;
}

void AddPooNode(PooNode* n, u16 v, void* p) {
    SetPooNodeWeight(n, v);
    SetPooNodeBaseWeight(n, v);
    n->pos = p;
    n->unk_04 = 0;
    ListNodeInit(&n->node, &sPooNodes, n);
    ListPoolAppend(&n->node, &sPooNodes);
}

void RemovePooNode(PooNode* p) {
    ListPoolRemove(&p->node, &sPooNodes);
}

void InitPooNodes() {
    ListPoolInit(&sPooNodes);
}

s32 GetPooNodeScore(PooNode* n) {
    PooPos* q;
    PooPos* p;
    s16 dx;
    s16 dy;
    u16 r;
    s32 d;

    q = gPoohPos;
    p = n->pos;
    dx = (q->x - p->x) >> 8;
    dy = (q->y - p->y) >> 8;
    r = GetPooNodeWeight(n);

    if (dx * dx > 0x3840 && dy * dy > 0x1900) {
        return 0;
    }

    d = dx * dx + dy * dy;

    if (d == 0) {
        return r << 8;
    }

    if (r != 0 && (r << 8) / (d << 8) == 0) {
        return 1;
    }

    return (r << 8) / ((dx * dx + dy * dy) << 8);
}

PooNode* FindPoohTargetNode() {
    PooNode* best;
    PooNode* n;

    best = ListPoolFirst(&sPooNodes);
    n = best;
    sPooBestNodeScore = 0;

    while (n != NULL) {
        sPooNodeScore = GetPooNodeScore(n);

        if (sPooNodeScore > sPooBestNodeScore) {
            sPooBestNodeScore = sPooNodeScore;
            best = n;
        }

        n = ListPoolNext(&n->node);
    }

    if (sPooBestNodeScore == 0 && best == (PooNode*)ListPoolFirst(&sPooNodes)) {
        return NULL;
    }

    return best;
}

void task_poo_honey_0(PooHoneyWork* work, PooPos* p) {
    work->pos.x = p->x;
    work->pos.y = p->y;
    work->pos.z = 0;
    work->palette = NULL;
    work->tileBytes = GetMaxSpriteTileBytes(gPoohHoneyFrames, 14);
    AnimInit(&work->anim, gPoohHoneyAnims, gPoohHoneyFrames);
    AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
    work->pos2 = work->pos;
    work->pos2.x += 0xB00;
    work->pos2.y -= 0xA00;
    work->minPos = work->pos2;
    work->minPos.x -= 0x100;
    work->minPos.y -= 0x100;
    work->maxPos = work->pos2;
    work->maxPos.x += 0x100;
    work->maxPos.y += 0x100;
    TaskPoolInit(&work->tasks, 1);
    CreatePooShadowscaleTask(&work->tasks, &work->pos, 0xCC);
    work->state = 0;
    work->timer = 0;
}

u8 task_poo_honey_1(PooHoneyWork* work) {
    switch (work->state) {
    case 0:
        if (work->minPos.x <= gPoohPos->x && gPoohPos->x <= work->maxPos.x && work->minPos.y <= gPoohPos->y && gPoohPos->y <= work->maxPos.y) {
            gPoohRequest = 3;
            SetPooNodeWeight(&work->node, 0);
            work->state++;
        }

        break;
    case 1:
        if (GetPoohHoneyAnim() <= 2) {
            AnimStart(&work->anim, GetPoohHoneyAnim(), 0);
            AnimUpdate(&work->anim);
            work->state++;
        }

        break;
    case 2:
        AnimUpdate(&work->anim);

        if (AnimIsFinished(&work->anim)) {
            return 0;
        }

        switch (AnimGetGfxIndex(&work->anim)) {
        case 1:
            work->pos = *gPoohPos;
            work->pos.x -= 0xB00;
            work->pos.y += 0xA00;
            work->pos.z = 0;
            work->pos3 = work->pos;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            work->pos.x = work->pos3.x + 0x200;
            work->pos.y = work->pos3.y;
            work->pos.z = work->pos3.z - 0x200;
            break;
        case 7:
            work->pos.x = work->pos3.x - 0x200;
            work->pos.y = work->pos3.y - 0x500;
            work->pos.z = work->pos3.z - 0xB00;
            break;
        case 8:
            gPoohGauge = 3;
            gPoohGaugeTimer = 0x73B;
            work->pos.x = work->pos3.x + 0xA00;
            work->pos.y = work->pos3.y - 0x900;
            work->pos.z = work->pos3.z - 0x1000;
            break;
        case 9:
            work->pos.x = work->pos3.x + 0x200;
            work->pos.y = work->pos3.y;
            work->pos.z = work->pos3.z - 0x300;
            break;
        case 10:
            work->pos.x = work->pos3.x + 0x200;
            work->pos.y = work->pos3.y;
            work->pos.z = work->pos3.z - 0x100;
            break;
        case 11:
        case 12:
        case 13:
            work->pos.x = work->pos3.x;
            work->pos.y = work->pos3.y;
            work->pos.z = work->pos3.z;
            work->timer++;
            break;
        case 0:
        default:
            break;
        }

        break;
    default:
        break;
    }

    return 1;
}

void task_poo_honey_2(PooHoneyWork* work) {
    s16 x;
    s16 y;

    if (work->timer > 29 && (work->timer & 1) != 0) {
        return;
    }

    x = (work->pos.x >> 8) - gPooScrollX;
    y = (work->pos.y >> 8) + (work->pos.z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 8, 16, 16)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
            RemovePooNode(&work->node);
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gPoohHoneyTiles);
            work->palette = LoadObjPalette(gPoohGaugePalette, 0x20);
            ColliderInit(&work->collider, 10, 8, 16);
            AddPooNode(&work->node, 0x1FA4, &work->pos2);
        }

        DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->pos.y >> 8) * 4);
        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_honey_3(PooHoneyWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
        RemovePooNode(&work->node);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_mapanime_0(PooMapAnimeWork* work) {
    BosMapanimeInit(&work->anims[0], &gPooMapanimeDef0);
    BosMapanimeInit(&work->anims[1], &gPooMapanimeDef1);
}

u8 task_poo_mapanime_1(PooMapAnimeWork* work) {
    u8 r;
    u32 i;

    r = 0;

    for (i = 0; i < 2; i++) {
        r = BosMapanimeUpdate(&work->anims[i], work->anims[i].def, r);
    }

    return 1;
}

void task_poo_mapanime_2(void* w) {
}

void task_poo_mapanime_3(void* w) {
}

s32 GetRandomPooPileStage() {
    switch (GetRandom() % 40 / 10) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 4;
    }

    return 6;
}

s32 NextPooPileStage(u32 a) {
    if (a == 0) {
        return 1;
    }

    if (a <= 2) {
        return 3;
    }

    if (a <= 4) {
        return 5;
    }

    return 7;
}

s32 GetPooPileHeight(u32 a) {
    if (a == 0) {
        return 32;
    }

    if (a <= 2) {
        return 24;
    }

    if (a <= 4) {
        return 16;
    }

    return 9;
}

void task_poo_pile_0(PooPileWork* work, PooPileArgs* a) {
    work->pos.x = a->x;
    work->pos.y = a->y;
    work->pos.z = 0;
    work->palette = NULL;
    AnimInit(&work->anim, gPooPileAnims, gPooPileFrames);

    if (a->stage == 8) {
        work->stage = GetRandomPooPileStage();
    } else {
        work->stage = a->stage;
    }

    AnimStart(&work->anim, work->stage, 0);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
    work->colliderActive = 0;
    TaskPoolInit(&work->tasks, 1);
    work->task = NULL;
}

u8 task_poo_pile_1(PooPileWork* work) {
    PooPos t;

    if (work->stage == 7) {
        return 1;
    }

    if (!work->colliderActive) {
        return 1;
    }

    if (ColliderIsTouchingType(&work->collider, 9)) {
        gPoohRequest = 5;
    }

    if (!gPooAttackActive) {
        return 1;
    }

    if (!PooAttackHitsCollider(&work->collider)) {
        return 1;
    }

    if (!AnimIsFinished(&work->anim)) {
        return 1;
    }

    t = work->pos;
    t.z -= (u16)GetPooPileHeight(work->stage) * 256;

    if (IsTaskActive(work->task)) {
        TaskKill(&work->tasks, work->task);
    }

    work->task = TaskCreate(&work->tasks, &gTaskDescPooSpark, &t);
    work->stage = NextPooPileStage(work->stage);
    AnimStart(&work->anim, work->stage, 0);
    m4aSongNumStart(SONG_SYS_PO_WOOD);

    if (work->stage == 7) {
        ColliderUnregister(&work->collider);
        work->colliderActive = 0;
        RemovePooNode(&work->node);
    } else {
        ColliderSetHeight(&work->collider, GetPooPileHeight(work->stage));
    }

    return 1;
}

void task_poo_pile_2(PooPileWork* work) {
    u16 z;
    s16 x;
    s16 y;

    x = (work->pos.x >> 8) - gPooScrollX;
    y = (work->pos.y >> 8) - gPooScrollY;

    if (x < -16 || x > 256 || y < -36 || y > 196) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }

        if (work->colliderActive) {
            ColliderUnregister(&work->collider);
            RemovePooNode(&work->node);
            work->colliderActive = 0;
        }

        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    } else {
        work->gfx = AnimUpdate(&work->anim);

        if (work->palette == NULL) {
            work->tiles = LoadObjTiles(gPooPileTiles, 0x300);
            work->palette = LoadObjPalette(gPooPilePalette, 0x20);
        }

        if (work->stage != 7) {
            z = -0x1004 - (work->pos.y >> 8) * 4;

            if (!work->colliderActive) {
                ColliderInit(&work->collider, 7, 4, GetPooPileHeight(work->stage));
                AddPooNode(&work->node, 0x240, &work->pos);
                work->colliderActive = 1;
            }
        } else {
            z = 0xFFF1;
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), z);
        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_pile_3(PooPileWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }

    if (work->colliderActive) {
        ColliderUnregister(&work->collider);
        RemovePooNode(&work->node);
    }

    TaskPoolDestroy(&work->tasks);
}

void CreatePooPileTask(void* pool, u16 b, s32 x, s32 y) {
    s32 t[6];
    PooPileArgs args;

    memcpy(t, gPooPileKindStages, sizeof(t));
    args.x = x;
    args.y = y;
    args.stage = t[b];
    TaskCreate(pool, &gTaskDescPooPile, &args);
}

void task_poo_tigerstump_0(PooStumpWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y + 0x800;
    work->unk_2C = 0;
    work->palette = NULL;
    work->gfx = gPooTigerStumpFrame0;
    ColliderSetPosition(&work->collider, work->x, work->y, 0);
}

u8 task_poo_tigerstump_1(PooStumpWork* work) {
    if (work->palette != NULL) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_tigerstump_2(PooStumpWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = ((work->y - 0x800) >> 8) - gPooScrollY;

    if (x < -96 || x > 336 || y < -64 || y > 224) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = LoadObjTiles(gPooTigerStumpTiles, 0x400);
            work->palette = LoadObjPalette(gPooStumpPalette, 0x20);
            ColliderInit(&work->collider, 7, 15, 24);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - ((work->y - 0x700) >> 8) * 4);
    }
}

void task_poo_tigerstump_3(PooStumpWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }
}

void task_poo_poohstump_0(PooStumpWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y;
    work->unk_2C = 0;
    work->palette = NULL;
    work->gfx = gPooPoohStumpFrame0;
    ColliderSetPosition(&work->collider, work->x, work->y, 0);
}

u8 task_poo_poohstump_1(PooStumpWork* work) {
    if (work->palette != NULL) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequestX = work->x;
            gPoohRequestY = work->y;
            gPoohRequest = 8;
        }
    }

    return 1;
}

void task_poo_poohstump_2(PooStumpWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (x < -80 || x > 320 || y < -24 || y > 184) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = LoadObjTiles(gPooPoohStumpTiles, 0x280);
            work->palette = LoadObjPalette(gPooStumpPalette, 0x20);
            ColliderInit(&work->collider, 7, 7, 14);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - ((work->y - 0x500) >> 8) * 4);
    }
}

void task_poo_poohstump_3(PooStumpWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }
}

void SetPooPigletAnimation(PooPigletWork* work, s32 b, u16 c) {
    if (work->animIndex != b) {
        work->animIndex = b;
        AnimChangeWithTables(&work->anim, gPooPigletAnimDescs[b].animId, c, gPooPigletAnimDescs[b].unk_00, gPooPigletAnimDescs[b].unk_04);
        SetObjTileSource(work->tiles, gPooPigletAnimDescs[b].tiles);
    }
}

void task_poo_piglet_0(PooPigletWork* work) {
    u16 m;
    u16 n;
    u8 i;

    work->x = 0x2A500;
    work->y = 0x21100;
    work->z = 0;
    work->state = 0;
    work->timer = 0;
    work->palette = NULL;
    m = 0;

    for (i = 0; i < 4; i++) {
        n = GetMaxSpriteTileBytes(gPooPigletGfxDescs[i].gfxTable, gPooPigletGfxDescs[i].gfxCount);

        if (m < n) {
            m = n;
        }
    }

    work->tiles = AllocObjTiles(m, NULL);
    AnimInit(&work->anim, NULL, NULL);
    work->animIndex = 4;
    SetPooPigletAnimation(work, 0, 1);
    work->flipped = 0;
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescPooShadow, &work->x);

    if (IsPooEventDone(0)) {
        work->interactionId = AddPoohInteraction(&work->collider, 0x36);
        SetPoohInteractionEnabled(work->interactionId, 0);
    }
}

u8 task_poo_piglet_1(PooPigletWork* work) {
    if (work->palette != NULL && work->collider.colliding) {
        if (!ColliderIsTouchingType(&work->collider, 9)) {
            return 1;
        }

        if (IsPooEventDone(0)) {
            return 1;
        }

        gPoohRequestX = work->x;
        gPoohRequestY = work->y;
        gPoohRequest = 4;
#ifdef VERSION_EU
        ExitPoohMode(134);
#else
        ExitPoohMode(136);
#endif
        SetPooEventDone(0);
        SetJiminyFlag(78);
    }

    switch (work->state) {
    case 0:
        SetPooPigletAnimation(work, 0, 1);
        work->flipped = 0;

        if (work->timer > 209) {
            work->state = 1;
            work->speed = 0;
        } else {
            work->timer++;
        }

        break;
    case 1:
        SetPooPigletAnimation(work, 3, 1);
        work->flipped = 1;
        work->speed += 0x600;

        if (work->speed > 128) {
            work->speed = 128;
        }

        work->x += gSineTable[0x20] * work->speed >> 8;
        work->y += -gSineTable[0x60] * work->speed >> 8;

        if (work->x > 0x2C8FF) {
            work->state = 2;
            work->timer = 0;
        }

        break;
    case 2:
        SetPooPigletAnimation(work, 1, 1);
        work->flipped = 1;

        if (work->timer > 39) {
            work->state = 3;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 3:
        SetPooPigletAnimation(work, 0, 1);
        work->flipped = 1;

        if (work->timer > 29) {
            work->state = 4;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 4:
        SetPooPigletAnimation(work, 1, 1);
        work->flipped = 1;

        if (work->timer > 29) {
            work->state = 5;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 5:
        SetPooPigletAnimation(work, 0, 1);
        work->flipped = 1;

        if (work->timer <= 59) {
            work->timer++;
        } else {
            work->state = 6;
            work->speed = 0;
        }

        break;
    case 6:
        SetPooPigletAnimation(work, 2, 1);
        work->flipped = 0;
        work->speed += 0x600;

        if (work->speed > 128) {
            work->speed = 128;
        }

        work->x += gSineTable[0xA0] * work->speed >> 8;
        work->y += -gSineTable[0xE0] * work->speed >> 8;

        if (work->x <= 0x2A500) {
            work->x = 0x2A500;
            work->y = 0x21100;
            work->state = 0;
            work->timer = 0;
        }

        break;
    default:
        break;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_poo_piglet_2(PooPigletWork* work) {
    u16 pr;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 8, 8, 8)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            ColliderUnregister(&work->collider);
            SetPoohInteractionEnabled(work->interactionId, 0);
            work->palette = NULL;
        }
    } else {
        TaskPoolUpdate(&work->tasks);

        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gPigletPalette, 0x20);

            if (IsPooEventDone(0)) {
                ColliderInit(&work->collider, 10, 4, 16);
            } else {
                ColliderInit(&work->collider, 10, 16, 16);
            }

            SetPoohInteractionEnabled(work->interactionId, 1);
        }

        ColliderSetPosition(&work->collider, work->x, work->y, work->z);
        pr = work->flipped ? 0x801 : 0x800;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pr, -0x1004 - (work->y >> 8) * 4);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_piglet_3(PooPigletWork* work) {
    ReleaseObjTiles(work->tiles);

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_eeyore_0(PooEeyoreWork* work) {
    work->x = 0x82700;
    work->y = 0x47E00;
    work->z = 0;
    work->unk_30 = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gEeyoreFl00Frames, 0x10);
    work->tiles = NULL;
    work->palette = NULL;

    if (IsPooEventDone(2)) {
        work->animId = 0;
    } else {
        work->animId = 4;
    }

    AnimInit(&work->anim, gEeyoreFl00Anims, gEeyoreFl00Frames);
    AnimStart(&work->anim, work->animId, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescPooShadow, &work->x);
    ColliderInit(&work->collider, 10, 16, 16);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    work->colliderActive = 1;

    if (!IsPooEventDone(2)) {
        work->interactionId = AddPoohInteraction(&work->collider, 0x38);
    } else {
        work->interactionId = AddPoohInteraction(&work->collider, 0x39);
    }

    SetPoohInteractionEnabled(work->interactionId, 1);
    work->moveTimer = 0;
}

u8 task_poo_eeyore_1(PooEeyoreWork* work) {
    if (work->colliderActive != 0) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequest = 5;
        }
    }

    if (IsPooEeyoreTailLanded() && work->animId == 4) {
        work->animId = 5;
        AnimStart(&work->anim, 5, ANIM_FLAG_LOOP);
        work->moveTimer = 180;
    }

    if (work->moveTimer != 0) {
        ApproachValue((u32*)&work->x, 0x80B00, work->moveTimer);
        ApproachValue((u32*)&work->y, 0x48C00, work->moveTimer);
        SetPooCameraFocus(work->x, work->y + work->z);
        work->moveTimer--;

        if (work->moveTimer == 0) {
#ifdef VERSION_EU
            ExitPoohMode(0x8A);
#else
            ExitPoohMode(0x8C);
#endif
            SetPooEventDone(2);
            SetJiminyFlag(0x51);
            work->animId = 1;
            AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
        }
    }

    return 1;
}

void task_poo_eeyore_2(PooEeyoreWork* work) {
    u8* p;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 10, 24, 24)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ReleaseObjTiles(work->tiles);
        }

        p = &work->colliderActive;

        if (*p != 0) {
            ColliderUnregister(&work->collider);
            SetPoohInteractionEnabled(work->interactionId, 0);
            *p = 0;
        }
    } else {
        p = &work->colliderActive;

        if (*p == 0) {
            ColliderInit(&work->collider, 10, 16, 16);
            SetPoohInteractionEnabled(work->interactionId, 1);
            *p = 1;
        }

        ColliderSetPosition(&work->collider, work->x, work->y, work->z);
        work->gfx = AnimUpdate(&work->anim);

        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gEeyorePalette, 0x20);
            work->tiles = AllocObjTiles(work->tileBytes, gEeyoreFl00Tiles);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);
        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_eeyore_3(PooEeyoreWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }

    if (work->colliderActive != 0) {
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_owl_0(PooOwlWork* work) {
    work->pos.x = 0x41500;
    work->pos.y = 0x20700;
    work->pos.z = -0x3000;
    work->pos.ground = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gOwlFl00Frames, 18);
    work->palette = NULL;
    work->gfx = gOwlFl00Frame0;
    AnimInit(&work->anim, gOwlFl00Anims, gOwlFl00Frames);
    work->flying = 0;
    work->descending = 0;
    sPooOwlBalloonPos.x = 0x3FD00;
    sPooOwlBalloonPos.y = 0x21B00;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescPooOwlballoon, &sPooOwlBalloonPos);
}

u8 task_poo_owl_1(PooOwlWork* work) {
    if (IsPoohOnOwlBalloon()) {
        SetPooCameraFocus(gPoohPos->x, gPoohPos->y + gPoohPos->z);

        if (gPoohPos->z <= -0x3800) {
            FreezePooCamera();
        }

        if (IsPoohOffScreen()) {
            if (!work->flying) {
                work->flying = 1;
                AnimStart(&work->anim, 1, 0);
                work->flyTimer = 60;
                m4aSongNumStart(SONG_SND_351);
            }

            if (AnimGetFrame(&work->anim) > 3) {
                if (work->flyTimer != 0) {
                    ApproachValueHalfSteps(&work->pos.z, -0x9000, work->flyTimer);
                    work->flyTimer--;
                    work->pos.x -= 204;
                } else {
                    work->pos.z -= 0x100;
                }
            }

            work->gfx = AnimUpdate(&work->anim);
        }
    }

    if (IsPoohDescendingWithOwl()) {
        if (!work->descending) {
            work->descending = 1;
            AnimStart(&work->anim, 4, ANIM_FLAG_LOOP);
        }

        if (AnimGetFrame(&work->anim) == 0 && work->anim.timer == 0) {
            m4aSongNumStart(SONG_EV_HUKUROUJUMP);
        }

        work->pos = *gPoohPos;
        work->gfx = AnimUpdate(&work->anim);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_owl_2(PooOwlWork* work) {
    s16 x;
    s16 y;

    TaskPoolDraw(&work->tasks);
    x = (work->pos.x >> 8) - gPooScrollX;
    y = (work->pos.y >> 8) + (work->pos.z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 8, 8, 8)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gOwlFl00Tiles);
            work->palette = LoadObjPalette(gOwlPalette, 0x20);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - ((work->pos.y + work->pos.z) >> 8) * 4);
    }
}

void task_poo_owl_3(PooOwlWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }

    TaskPoolDestroy(&work->tasks);
}

void SetPooRabbitAnimation(PooRabbitWork* work, s32 b, u16 c) {
    if (work->animIndex != b) {
        work->animIndex = b;
        AnimChangeWithTables(&work->anim, gPooRabbitAnimDescs[b].animId, c, gPooRabbitAnimDescs[b].unk_00, gPooRabbitAnimDescs[b].unk_04);
        SetObjTileSource(work->tiles, gPooRabbitAnimDescs[b].tiles);
    }
}

void task_poo_rabbit_0(PooRabbitWork* work) {
    u16 m;
    u16 n;
    u8 i;

    work->x = 0x1B700;
    work->y = 0x16E00;
    work->z = 0;
    work->unk_34 = 0;
    work->palette = NULL;
    m = 0;

    for (i = 0; i < 2; i++) {
        n = GetMaxSpriteTileBytes(gPooRabbitGfxDescs[i].gfxTable, gPooRabbitGfxDescs[i].gfxCount);

        if (m < n) {
            m = n;
        }
    }

    work->tiles = AllocObjTiles(m, NULL);
    AnimInit(&work->anim, NULL, NULL);
    work->animIndex = 7;
    SetPooRabbitAnimation(work, 1, 0);
    work->flipped = 0;
    work->timer = 0;
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    CreatePooShadowscaleTask(&work->tasks, &work->x, 0x100);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    work->interactionId = AddPoohInteraction(&work->collider, 0x3B);
    SetPoohInteractionEnabled(work->interactionId, 0);
}

u8 task_poo_rabbit_1(PooRabbitWork* work) {
    switch (work->animIndex) {
    case 1:
        if (AnimIsFinished(&work->anim)) {
            work->timer++;

            if (work->timer <= 3) {
                AnimReset(&work->anim);
            } else {
                SetPooRabbitAnimation(work, 4, 1);
                work->flipped = 1;
                work->timer = 312;
            }
        }

        break;
    case 4:
        if (work->palette != NULL && work->collider.colliding && ColliderIsTouchingType(&work->collider, 9)) {
            SetPooRabbitAnimation(work, 6, 0);
            work->waitTimer = 20;
        } else {
            ApproachValue(&work->x, 0x23000, work->timer);
            ApproachValue(&work->y, 0x12400, work->timer);
            work->timer--;

            if (work->timer == 0) {
                SetPooRabbitAnimation(work, 5, 0);
                work->flipped = 1;
            }
        }

        break;
    case 5:
        if (AnimIsFinished(&work->anim)) {
            SetPooRabbitAnimation(work, 2, 1);
            work->flipped = 0;
            work->timer = 260;
        }

        break;
    case 2:
        if (work->palette != NULL && work->collider.colliding && ColliderIsTouchingType(&work->collider, 9)) {
            work->waitTimer = 20;
            SetPooRabbitAnimation(work, 0, 0);
        } else {
            ApproachValue(&work->x, 0x1B700, work->timer);
            ApproachValue(&work->y, 0x16E00, work->timer);
            work->timer--;

            if (work->timer == 0) {
                SetPooRabbitAnimation(work, 1, 0);
                work->flipped = 0;
                work->timer = 0;
            }
        }

        break;
    case 6:
        if (work->waitTimer == 0) {
            if (work->palette != NULL && !ColliderIsTouchingType(&work->collider, 9)) {
                SetPooRabbitAnimation(work, 4, 1);
            }
        } else {
            work->waitTimer--;
        }

        break;
    case 0:
        if (work->waitTimer != 0) {
            work->waitTimer--;
        } else if (work->palette != NULL && !ColliderIsTouchingType(&work->collider, 9)) {
            SetPooRabbitAnimation(work, 2, 1);
        }

        break;
    default:
        break;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_poo_rabbit_2(PooRabbitWork* work) {
    TaskPool* pool;
    s32 pr;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 48, 8, 16, 16)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            ColliderUnregister(&work->collider);
            SetPoohInteractionEnabled(work->interactionId, 0);
            work->palette = NULL;
        }
    } else {
        pool = &work->tasks;
        TaskPoolUpdate(pool);

        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gRabbitPalette, 0x40);
            ColliderInit(&work->collider, 10, 4, 48);
            SetPoohInteractionEnabled(work->interactionId, 1);
        }

        ColliderSetPosition(&work->collider, work->x, work->y, work->z);
        pr = work->flipped ? 0x801 : 0x800;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pr, -0x1004 - (work->y >> 8) * 4);
        TaskPoolDraw(pool);
    }
}

void task_poo_rabbit_3(PooRabbitWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void SetPooTiggerrooAnimation(PooTiggerWork* work, u16 b) {
    s32 a;

    AnimReset(&work->anim);

    if (work->mode == 2) {
        switch (work->heading) {
        case 0xAD:
            a = 2;
            work->flipped = 0;
            break;
        case 0x53:
            a = 2;
            work->flipped = 1;
            break;
        case 0xD3:
            a = 3;
            work->flipped = 0;
            break;
        case 0x00:
        default:
            a = 3;
            work->flipped = 1;
            break;
        }
    } else {
        a = 0;
    }

    if (work->animIndex != a) {
        work->animIndex = a;
        AnimStart(&work->anim, a, b);
    }
}

void SetPooTiggerAnimation(PooTiggerWork* work, u16 b) {
    u16 r;

    AnimReset(&work->anim);

    if (work->mode == 0) {
        r = 0;
    } else if (work->mode == 1) {
        r = 1;
    } else if (work->mode == 2) {
        switch (work->heading) {
        case 0xAD:
            r = 2;
            work->flipped = 0;
            break;
        case 0x53:
            r = 2;
            work->flipped = 1;
            break;
        case 0xD3:
            r = 3;
            work->flipped = 0;
            break;
        case 0x2D:
        default:
            r = 3;
            work->flipped = 1;
            break;
        }
    } else {
        r = 0;
    }

    if (work->animIndex != r) {
        work->animIndex = r;
        AnimChangeWithTables(&work->anim, gPooTiggerAnimDescs[r].animId, b, gPooTiggerAnimDescs[r].unk_00, gPooTiggerAnimDescs[r].unk_04);
        SetObjTileSource(work->tiles, gPooTiggerAnimDescs[r].tiles);
    }
}

void StartPooTiggerHopStep(PooTiggerWork* work) {
    PooAnimData* d;
    s32 t[8];

    memcpy(t, gPooTiggerHopHeights, sizeof(t));
    d = ((PooAnimData**)gPooTiggerAnimDescs[work->animIndex].unk_00)[gPooTiggerAnimDescs[work->animIndex].animId];
    work->stepTimer = (&d->frames[work->step])->duration;
    work->targetZ = t[work->step] - 0x1800;
    work->step++;
}

u16 GetPooTiggerAnimDuration(PooTiggerWork* work) {
    PooAnimData* d;
    u16 t;
    s32 i;

    d = ((PooAnimData**)gPooTiggerAnimDescs[work->animIndex].unk_00)[gPooTiggerAnimDescs[work->animIndex].animId];
    t = 0;

    for (i = 0; i < d->frameCount; i++) {
        t += d->frames[i].duration;
    }

    return t;
}

void StartPooTiggerHop(PooTiggerWork* work) {
    work->hopTimer = GetPooTiggerAnimDuration(work);

    if (work->heading == 0xAD) {
        work->x = gPooTiggerHopCorners[0];
        work->y = gPooTiggerHopCorners[1];
        work->targetX = gPooTiggerHopCorners[2];
        work->targetY = gPooTiggerHopCorners[3];
    } else if (work->heading == 0x53) {
        work->x = gPooTiggerHopCorners[2];
        work->y = gPooTiggerHopCorners[3];
        work->targetX = gPooTiggerHopCorners[4];
        work->targetY = gPooTiggerHopCorners[5];
    } else if (work->heading == 0x2D) {
        work->x = gPooTiggerHopCorners[4];
        work->y = gPooTiggerHopCorners[5];
        work->targetX = gPooTiggerHopCorners[6];
        work->targetY = gPooTiggerHopCorners[7];
    } else {
        work->x = gPooTiggerHopCorners[6];
        work->y = gPooTiggerHopCorners[7];
        work->targetX = gPooTiggerHopCorners[0];
        work->targetY = gPooTiggerHopCorners[1];
    }

    work->z = -0x1800;
    work->step = 0;
    StartPooTiggerHopStep(work);
}

void PlayPooTiggerHopSound(s32 x, s32 y, s32 z, u8 c) {
    s16 sx;
    s16 sy;

    sx = (x >> 8) - gPooScrollX;
    sy = (y >> 8) + (z >> 8) - gPooScrollY;

    if (!IsRectOutsideScreen(sx, sy, 120, 8, 24, 24)) {
        if (c) {
            m4aSongNumStart(SONG_SND_961);
        } else {
            m4aSongNumStart(SONG_SYS_LU_JP);
        }
    }
}

void task_poo_tigger_0(PooTiggerWork* work) {
    PooShadowArgs args;
    u16 m;
    u16 t;
    u8 i;

    work->mode = 2;
    work->heading = 0xAD;
    work->isTigger = 1;
    work->palette = NULL;
    m = 0;

    for (i = 0; i < 4; i++) {
        t = GetMaxSpriteTileBytes(gPooTiggerGfxDescs[i].gfxTable, gPooTiggerGfxDescs[i].gfxCount);

        if (m < t) {
            m = t;
        }
    }

    work->tiles = AllocObjTiles(m, NULL);
    AnimInit(&work->anim, NULL, NULL);
    work->animIndex = 4;
    SetPooTiggerAnimation(work, 0);
    StartPooTiggerHop(work);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    args.pos = (PooPos*)&work->x;
    args.shadowInfo = &work->shadowInfo;
    TaskCreate(&work->tasks, &gTaskDescPooShadowdodai, &args);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
}

u8 task_poo_tiggerroo_1(PooTiggerWork* work) {
    GetPooGroundZ(&work->collider, (PooPos*)&work->x, &work->onCollider);

    if (work->mode == 2) {
        if (work->hopTimer > 0) {
            ApproachValueHalfSteps(&work->x, work->targetX, work->hopTimer);
            ApproachValueHalfSteps(&work->y, work->targetY, work->hopTimer);
            work->hopTimer--;
            ApproachValue((u32*)&work->z, work->targetZ, work->stepTimer);
            work->stepTimer--;

            if (work->stepTimer == 0) {
                StartPooTiggerHopStep(work);
            }
        } else {
            switch (work->heading) {
            case 0xAD:
                work->heading = 0x53;
                break;
            case 0x53:
                work->heading = 0x2D;
                break;
            case 0x2D:
                work->heading = 0xD3;
                break;
            case 0xD3:
                work->heading = 0xAD;
                break;
            }

            if (work->isTigger) {
                SetPooTiggerAnimation(work, 0);
            } else {
                SetPooTiggerrooAnimation(work, 0);
            }

            StartPooTiggerHop(work);
            PlayPooTiggerHopSound(work->x, work->y, work->z, work->isTigger);
        }
    }

    work->gfx = AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_tiggerroo_2(PooTiggerWork* work) {
    u16 z;
    s32 pr;
    s32 d;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 56, 8, 24, 24)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);

            if (!work->isTigger) {
                if (work->tiles != NULL) {
                    ReleaseObjTiles(work->tiles);
                    work->tiles = NULL;
                }
            }
        }
    } else {
        if (work->palette == NULL) {
            if (work->isTigger) {
                work->palette = LoadObjPalette(gTiggerPalette, 0x20);
                ColliderInit(&work->collider, 4, 8, 8);
            } else {
                work->palette = LoadObjPalette(gRooPalette, 0x20);
                work->tiles = AllocObjTiles(work->tileBytes, gRooFl00Tiles);
                ColliderInit(&work->collider, 4, 8, 8);
            }
        }

        ColliderSetPosition(&work->collider, work->x, work->y, work->z);
        pr = work->flipped ? 0x801 : 0x800;
        d = work->onCollider;

        if (d != 0) {
            z = -0x1008 - (work->collider.platformY >> 8) * 4;

            if (work->y >= gPooActor.pos.y) {
                z -= 2;
            } else {
                z += 2;
            }

            if (work->collider.penetration <= work->collider.radius) {
                work->shadowInfo.z = 0;
                work->shadowInfo.priority = 0;
            } else {
                work->shadowInfo.z = work->collider.platformZ;
                work->shadowInfo.priority = z + 1;
            }
        } else {
            z = -0x1004 - (work->y >> 8) * 4;
            work->shadowInfo.z = d;

            if (d != work->ground) {
                work->shadowInfo.priority = 0;
            } else {
                work->shadowInfo.priority = z + 1;
            }
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pr, z);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_tiggerroo_3(PooTiggerWork* work) {
    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_tiggerroo_0(PooTiggerWork* work) {
    PooShadowArgs args;

    work->mode = 2;
    work->heading = 0x2D;
    work->isTigger = 0;
    work->palette = NULL;
    work->tiles = NULL;
    work->tileBytes = GetMaxSpriteTileBytes(gRooFl00Frames, 18);
    AnimInit(&work->anim, gRooFl00Anims, gRooFl00Frames);
    work->animIndex = 4;
    SetPooTiggerrooAnimation(work, 0);
    StartPooTiggerHop(work);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    args.pos = (PooPos*)&work->x;
    args.shadowInfo = &work->shadowInfo;
    TaskCreate(&work->tasks, &gTaskDescPooShadowdodai, &args);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
}

void task_poo_roo_0(PooRooWork* work, PooPos* p) {
    gStockMesDispWork = work;
    work->srcPos = p;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gRooFl00Frames, 8), gRooFl00Tiles);
    work->palette = LoadObjPalette(gRooPalette, 0x20);
    AnimInit(&work->anim, gRooFl00Anims, gRooFl00Frames);

    if (IsPooEventDone(5)) {
        work->pos.x = 0x95F00;
        work->pos.y = 0x4EE00;
        work->pos.z = 0;
        AnimStart(&work->anim, 0, 0);
        work->flipped = 0;
        work->state = 3;
    } else {
        work->pos = *work->srcPos;
        AnimStart(&work->anim, 4, 0);
        work->flipped = 0;
        work->state = 0;
    }

    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescPooShadow, &work->pos);
    ColliderInit(&work->collider, 10, 4, 32);
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);

    if (IsPooEventDone(5)) {
        work->interactionId = AddPoohInteraction(&work->collider, 58);
    }
}

u8 task_poo_roo_1(PooRooWork* work) {
    s32 t;

    switch (work->state) {
    case 0:
        if (AnimIsFinished(&work->anim)) {
            AnimStart(&work->anim, 5, 0);
            work->state = 1;
            work->pos = *work->srcPos;
            work->pos.x -= 0x600;
            work->pos.z += 0x1F00;
        }

        break;
    case 1:
        work->lastZ = work->pos.z;
        work->pos = *work->srcPos;
        work->pos.x -= 0x600;
        t = work->pos.z + 0x1F00;
        work->pos.z = t;

        if (work->lastZ - t < 0 && t >= -0x2100) {
            AnimStart(&work->anim, 6, 0);
            work->state = 2;
            work->vz = 0;
        }

        break;
    case 2:
        work->pos.z += work->vz;
        work->vz += 7;

        if (work->pos.z >= 0) {
            work->pos.z = 0;
        } else {
            work->pos.x -= 0x40;
            work->pos.y += 0x40;
        }

        if (work->srcPos->z >= 0) {
#ifdef VERSION_EU
            ExitPoohMode(0x89);
#else
            ExitPoohMode(0x8B);
#endif
            SetPooEventDone(5);
            SetJiminyFlag(80);
        }

        break;
    case 3:
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequest = 5;
        }

        break;
    }

    work->gfx = AnimUpdate(&work->anim);
    ColliderSetPosition(&work->collider, work->pos.x, work->pos.y, work->pos.z);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_roo_2(PooRooWork* work) {
    s16 x;
    s16 y;
    s32 pr;
    s32 t;

    x = (work->pos.x >> 8) - gPooScrollX;
    t = work->pos.y >> 8;
    y = t + (work->pos.z >> 8) - gPooScrollY;
    pr = work->flipped != 0 ? 0x801 : 0x800;
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pr, -0x1006 - t * 4);

    if (work->state != 0) {
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_roo_3(PooRooWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
    TaskPoolDestroy(&work->tasks);
}

u8 IsPooRooAnimFrameEnding() {
    return AnimIsFrameEnding(&((PooRooWork*)gStockMesDispWork)->anim);
}

u8 IsPooRooAnimFinished() {
    return AnimIsFinished(&((PooRooWork*)gStockMesDispWork)->anim);
}

void task_poo_roo_footmark_0(PooFootmarkWork* work) {
    work->x = 0x4A700;
    work->y = 0x28E00;
    work->unk_14 = 0;
    work->tiles = LoadObjTiles(gRoFootmarkTiles, 0x500);
    work->palette = NULL;

    if (!IsPooEventDone(5)) {
        work->gfx = gRoFootmarkFrame0;
    } else {
        work->gfx = gRoFootmarkFrame1;
    }
}

u8 task_poo_roo_footmark_1(void* w) {
    return 1;
}

void task_poo_roo_footmark_2(PooFootmarkWork* work) {
    PooNode* n;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 48, 0, 48)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            RemovePooNode(&work->node);
            work->palette = NULL;
        }
    } else {
        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gRoFootmarkPalette, 0x20);
            n = &work->node;
            AddPooNode(n, 0x240, &work->x);

            if (IsPooEventDone(5)) {
                SetPooNodeWeight(n, 0);
            }
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 0xFFF1);
    }
}

void task_poo_roo_footmark_3(PooFootmarkWork* work) {
    ReleaseObjTiles(work->tiles);

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
        RemovePooNode(&work->node);
    }
}

void task_poo_leaf_0(PooLeafWork* work, PooSpawnArgs* a) {
    work->x = a->pos.x;
    work->y = a->pos.y;
    work->z = 0;
    work->prizeId = a->prizeId;
    work->tileBytes = GetMaxSpriteTileBytes(gPooLeafFrames, 5);
    work->palette = NULL;
    AnimInit(&work->anim, gPooLeafAnims, gPooLeafFrames);
    AnimStart(&work->anim, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderSetPosition(&work->collider, work->x + 0x1C00, work->y + 0x1000, work->z);
    work->playing = 0;
}

u8 task_poo_leaf_1(PooLeafWork* work) {
    if (work->palette != NULL && (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0 && work->playing == 0) {
        work->playing = 1;
        AnimReset(&work->anim);
        m4aSongNumStart(SONG_SND_224);

        if (!IsPooPrizeDropped(work->prizeId)) {
            if (SpawnPooPrizes(2, 3, work->x + 0x1C00, work->y + 0x2000, work->z) != 0) {
                SetPooPrizeDropped(work->prizeId);
            }
        }
    }

    return 1;
}

void task_poo_leaf_2(PooLeafWork* work) {
    u8* p;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 32, 0, 56)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
            work->playing = 0;
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gPooLeafTiles);
            work->palette = LoadObjPalette(gPooLeafPalette, 0x20);
            ColliderInit(&work->collider, 6, 28, 0);
        }

        p = &work->playing;

        if (*p != 0) {
            work->gfx = AnimUpdate(&work->anim);

            if (!AnimIsFinished(&work->anim)) {
                DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 0xFFF1);
            } else if ((work->collider.standFlags & COLLIDER_STAND_STOOD_ON) == 0) {
                *p = 0;
            }
        }
    }
}

void task_poo_leaf_3(PooLeafWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }
}

void task_poo_tanpopo_0(PooTanpopoWork* work, PooSpawnArgs* a) {
    work->x = a->pos.x;
    work->y = a->pos.y;
    work->z = 0;
    work->prizeId = a->prizeId;
    work->tileBytes = GetMaxSpriteTileBytes(gPooTanpopoFrames, 2);
    work->tileBytes2 = GetMaxSpriteTileBytes(gPooTanpopoSeedFrames, 6);
    work->palette = NULL;
    AnimInit(&work->anim, gPooTanpopoAnims, gPooTanpopoFrames);
    AnimStart(&work->anim, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    AnimInit(&work->anim2, gPooTanpopoSeedAnims, gPooTanpopoSeedFrames);
    AnimStart(&work->anim2, 0, 0);
    work->gfx2 = AnimGetGfx(&work->anim2);
    ColliderSetPosition(&work->collider, work->x + 0x1800, work->y + 0x1000, work->z);
    work->playing = 0;
}

u8 task_poo_tanpopo_1(PooTanpopoWork* work) {
    if (work->palette != NULL && (work->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0 && work->playing == 0) {
        work->playing = 1;
        AnimReset(&work->anim);
        AnimReset(&work->anim2);

        if (!IsPooPrizeDropped(work->prizeId)) {
            if (SpawnPooPrizes(2, 1, work->x + 0x1800, work->y + 0x2000, work->z) != 0) {
                SetPooPrizeDropped(work->prizeId);
            }
        }
    }

    return 1;
}

void task_poo_tanpopo_2(PooTanpopoWork* work) {
    u8* p;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 32, 0, 48)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjTiles(work->tiles2);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
            work->playing = 0;
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = LoadObjTiles(gPooTanpopoTiles, 0x800);
            work->tiles2 = LoadObjTiles(gPooTanpopoSeedTiles, 0x1800);
            work->palette = LoadObjPalette(gPooTanpopoPalette, 0x20);
            ColliderInit(&work->collider, 6, 24, 0);
        }

        p = &work->playing;

        if (*p != 0) {
            work->gfx = AnimUpdate(&work->anim);
            work->gfx2 = AnimUpdate(&work->anim2);
            DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), 0xFFF1);

            if (!AnimIsFinished(&work->anim2)) {
                DrawSprite(x, y, work->gfx2, work->tiles2, work->palette, NULL, SPRITE_PRIORITY(2), 100);
            } else if ((work->collider.standFlags & COLLIDER_STAND_STOOD_ON) == 0) {
                *p = 0;
            }
        }
    }
}

void task_poo_tanpopo_3(PooTanpopoWork* work) {
    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
        ReleaseObjTiles(work->tiles);
        ReleaseObjTiles(work->tiles2);
        ColliderUnregister(&work->collider);
    }
}

void task_poo_ti_board_0(PooBoardWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y;
    work->z = 0;
    work->tiles = LoadObjTiles(gPooTiBoardTiles, 0x200);
    work->palette = NULL;
    work->gfx = gPooTiBoardFrame0;
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
}

u8 task_poo_ti_board_1(PooBoardWork* work) {
    if (work->palette != NULL) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_ti_board_2(PooBoardWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 16, 1, 8, 8)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
        }
    } else {
        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gPooTiBoardPalette, 0x20);
            ColliderInit(&work->collider, 7, 8, 16);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);
    }
}

void task_poo_ti_board_3(PooBoardWork* work) {
    ReleaseObjTiles(work->tiles);

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }
}

void task_poo_eeyoretail_0(PooEeyoreTailWork* work) {
    work->x = 0x7CD00;
    work->y = 0x49E00;
    work->z = -0x2000;
    work->unk_18 = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gEeyoreFl00Frames, 0x10);
    work->palette = NULL;
    work->gfx = gEeyoreFl00Frame15;
    TaskPoolInit(&work->tasks, 1);
    CreatePooShadowscaleTask(&work->tasks, &work->x, 0x66);
    sPooEeyoreTailTimer = 0x1E;
    work->height = -work->z;
}

u8 task_poo_eeyoretail_1(PooEeyoreTailWork* work) {
    if (IsPoohBeeChaseOver()) {
        if (sPooEeyoreTailTimer != 0) {
            ApproachValue(&work->x, 0x7FD00, sPooEeyoreTailTimer);
            ApproachValue(&work->y, 0x49300, sPooEeyoreTailTimer);
            ApproachValue(&work->height, 0, sPooEeyoreTailTimer);
            work->z = -work->height;
            sPooEeyoreTailTimer--;
            SetPooCameraFocus(work->x, work->y + work->z);
        }

        TaskPoolUpdate(&work->tasks);
    }

    return 1;
}

void task_poo_eeyoretail_2(PooEeyoreTailWork* work) {
    s16 x;
    s16 y;
    u16 pr;
    s32 z;

    x = ((s32)work->x >> 8) - gPooScrollX;
    y = ((s32)work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gEeyoreFl00Tiles);
            work->palette = LoadObjPalette(gEeyorePalette, 0x20);
        }

        if (IsPooEeyoreTailLanded()) {
            pr = 0x800;
            z = 0xFFEF;
        } else {
            pr = 0x400;
            z = 10;
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pr, z);

        if (IsPoohBeeChaseOver()) {
            TaskPoolDraw(&work->tasks);
        }
    }
}

void task_poo_eeyoretail_3(PooEeyoreTailWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }

    TaskPoolDestroy(&work->tasks);
}

u8 IsPooEeyoreTailLanded() {
    if (sPooEeyoreTailTimer == 0) {
        return 1;
    }

    return 0;
}

void task_poo_honeycomb_0(PooHoneycombWork* work) {
    work->x = 0x8DE00;
    work->y = 0x46600;
    work->z = -0xA00;
    work->unk_30 = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gEeHoneycombFrames, 1);
    work->palette = NULL;
    work->gfx = gEeHoneycombFrame0;
    ColliderSetPosition(&work->collider, work->x, work->y, 0);
    work->colliderActive = 0;
    sPooHoneycombState = 0;
    work->shakeX = 0;
    work->angle = 0;
}

u8 task_poo_honeycomb_1(PooHoneycombWork* work) {
    u8 c;

    if (work->colliderActive != 0) {
        switch (sPooHoneycombState) {
        case 2:
            break;
        case 0:
            if (ColliderIsTouchingType(&work->collider, 9)) {
                c = IsPooEventDone(2);

                if (!c) {
                    gPoohRequest = 9;

                    if (IsPoohLookingAtHoneycomb()) {
                        sPooHoneycombState = 1;
                        work->shakeTimer = c;
                    }
                } else {
                    gPoohRequest = 10;
                }
            }

            break;
        case 1:
            work->shakeX = gSineTable[(u8)work->angle];
            work->angle += 16;
            work->shakeTimer++;

            if (work->shakeTimer > 60) {
                work->shakeX = 0;
                sPooHoneycombState = 2;
                m4aSongNumStart(SONG_SND_371);
            }

            break;
        }
    }

    return 1;
}

void task_poo_honeycomb_2(PooHoneycombWork* work) {
    u8* p;
    s16 x;
    s16 y;

    x = ((work->x + work->shakeX) >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 16, 16, 16, 16)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            ReleaseObjTiles(work->tiles);
            work->palette = NULL;
        }

        p = &work->colliderActive;

        if (*p != 0) {
            ColliderUnregister(&work->collider);
            *p = 0;
        }
    } else {
        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gEeHoneycombPalette, 0x20);
            work->tiles = AllocObjTiles(work->tileBytes, gEeHoneycombTiles);
        }

        p = &work->colliderActive;

        if (*p == 0) {
            ColliderInit(&work->collider, 6, 64, 0);
            *p = 1;
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(3), 0xFFF0);
    }
}

void task_poo_honeycomb_3(PooHoneycombWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }

    if (work->colliderActive != 0) {
        ColliderUnregister(&work->collider);
    }
}

u8 IsPooHoneycombShaken() {
    if (sPooHoneycombState == 2) {
        return 1;
    }

    return 0;
}

void task_poo_vegetable_0(PooVegetableWork* work) {
    work->x = 0x1AC00;
    work->y = 0x18000;
    work->z = 0;
    work->unk_30 = 0;
    work->tileBytes = GetMaxSpriteTileBytes(gRaVegetablesFrames, 1);
    work->palette = NULL;
    work->gfx = gRaVegetablesFrame0;
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
}

u8 task_poo_vegetable_1(PooVegetableWork* work) {
    if (work->palette != NULL) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_vegetable_2(PooVegetableWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 32, 40, 48, 48)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
            ColliderUnregister(&work->collider);
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gRaVegetablesTiles);
            work->palette = LoadObjPalette(gRaVegetablesPalette, 0x20);
            ColliderInit(&work->collider, 7, 0x26, 12);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);
    }
}

void task_poo_vegetable_3(PooVegetableWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }
}

s32 IsInPooWagonArea(PooPos* p) {
    s32 k;
    s32 x;
    s32 y;

    k = 0x2500;

    if (IsPooEventDone(6)) {
        k = 0x2100;
    }

    x = p->x - sPooWagon->pos.x;
    y = p->y - sPooWagon->pos.y;

    if (y + x < -0x1A00) {
        return 0;
    }

    if (y - x / 2 > k - 0xB80) {
        return 0;
    }

    if (y + x > k + 0x1700) {
        return 0;
    }

    if (y - x / 2 < -0x1180) {
        return 0;
    }

    return 1;
}

s32 IsInPooWagonAreaForPooh(PooPos* p) {
    s32 k;
    s32 x;
    s32 y;

    k = 0x2500;

    if (IsPooEventDone(6)) {
        k = 0x2100;
    }

    x = p->x - sPooWagon->pos.x;
    y = p->y - sPooWagon->pos.y;

    if (y + x < -0x1A00) {
        return 0;
    }

    if (y - x / 2 > k - 0xB80) {
        return 0;
    }

    if (y + x > 0x3100) {
        return 0;
    }

    if (y - x / 2 < -0x1180) {
        return 0;
    }

    return 1;
}

u8 IsPooSoraOnWagon() {
    if (gPooActor.pos.z < 0) {
        return 0;
    }

    return IsInPooWagonArea(&gPooActor.pos);
}

u8 IsPooSoraOverWagon() {
    if (gPooActor.pos.z < -0x2000) {
        return 0;
    }

    return IsInPooWagonArea(&gPooActor.pos);
}

void SnapToPooWagonLine(u32* a, u32* b, u16 c) {
    s32 d;
    s32 e;

    d = *a - sPooWagon->pos.x;

    if (d < -0x600) {
        d = -0x600;
    } else if (d > 0xA00) {
        d = 0xA00;
    }

    e = d / 2 - 0x300;
    ApproachValue(a, d + sPooWagon->pos.x, c);
    ApproachValue(b, e + sPooWagon->pos.y, c);
}

void ProjectToPooWagonEdgeUL(s32* a, s32* b) {
    s32 t;
    s32 y;

    t = *a;
    y = *b;
    t -= 0x4600;
    *a = (t - y * 2) / 5;
    *b = -0x2300 - *a * 2;
}

void ProjectToPooWagonEdgeLR(s32* a, s32* b) {
    s32 t;
    s32 y;

    t = *a;
    y = *b;
    t += 0x5000;
    *a = (t - y * 2) / 5;
    *b = 0x2800 - *a * 2;
}

void ProjectToPooWagonEdgeUR(s32* a, s32* b) {
    s32 t;
    s32 y;

    t = *a;
    y = *b;
    *a = (y * 2 + t * 4 + 0xF00) / 5;
    *b = *a / 2 - 0x800;
}

void ProjectToPooWagonEdgeLL(s32* a, s32* b) {
    s32 x;
    s32 y;

    x = *a;
    y = *b;
    *a = (y * 2 + x * 4 - 1280) / 5;
    *b = *a / 2 + 768;
}

void ClampToPooWagonArea(u32* a, u32* b, u16 c) {
    s32 x;
    s32 y;

    x = *a - sPooWagon->pos.x;
    y = *b - sPooWagon->pos.y;

    if (x < -0xB00 && y < -0xD00) {
        ProjectToPooWagonEdgeUL(&x, &y);

        if (y < -0xD00) {
            ProjectToPooWagonEdgeUR(&x, &y);
        } else if (y > -0xD00) {
            ProjectToPooWagonEdgeLL(&x, &y);
        }
    } else if (x > 0xF00 && y > 0x600) {
        ProjectToPooWagonEdgeLR(&x, &y);

        if (y < 0x600) {
            ProjectToPooWagonEdgeUR(&x, &y);
        } else if (y > 0xA00) {
            ProjectToPooWagonEdgeLL(&x, &y);
        }
    } else if (-x / 2 + y > 0) {
        ProjectToPooWagonEdgeLL(&x, &y);

        if (x < -0x1700) {
            ProjectToPooWagonEdgeUL(&x, &y);
        } else if (x > 0xF00) {
            ProjectToPooWagonEdgeLR(&x, &y);
        }
    } else {
        ProjectToPooWagonEdgeUR(&x, &y);

        if (x < -0xB00) {
            ProjectToPooWagonEdgeUL(&x, &y);
        } else if (x > 0x1800) {
            ProjectToPooWagonEdgeLR(&x, &y);
        }
    }

    ApproachValue(a, x + sPooWagon->pos.x, c);
    ApproachValue(b, y + sPooWagon->pos.y, c);
}

s32 GetPooWagonNearestSide(s32 x, s32 y) {
    s32 dx;
    s32 dy;

    dx = x - sPooWagon->pos.x;
    dy = y - sPooWagon->pos.y;

    if (dx < -0xB00 && dy < -0xD00) {
        return 0x53;
    }

    if (dx > 0xF00 && dy > 0x600) {
        return 0xD3;
    }

    if (-dx / 2 + dy > 0) {
        return 0x2D;
    }

    return 0xAD;
}

s32 GetPooWagonSide(s32 a, s32 b) {
    s32 x;
    s32 y;

    x = a - sPooWagon->pos.x;
    y = b - sPooWagon->pos.y;

    if (x < -0x3D00 || x > 0x4300 || y < -0x1F00 || y > 0x3800) {
        return 0;
    }

    if (x < -0x1100 && y <= 0x2FF) {
        return 0x53;
    }

    if (x > 0x1700 && y > 0x500) {
        return 0xD3;
    }

    if (-x / 2 + y > 0) {
        return 0x2D;
    }

    return 0xAD;
}

void task_poo_wagon_0(PooWagonWork* work) {
    sPooWagon = work;
    work->pos.x = 0x2AE00;
    work->pos.y = 0x17700;
    work->pos.z = 0;
    work->pos.ground = 0;
    work->pos2 = work->pos;

    if (IsPooEventDone(6)) {
        work->pos.y += 0xC00;
    }

    work->palette = NULL;
    work->gfx = gRaWagonFrame11;
    work->gfx2 = gRaWagonFrame1;
    work->gfx3 = gRaWagonFrame12;
    work->poohAboard = 0;
    work->timer = 0;
    work->angle = 0;
}

u8 task_poo_wagon_1(PooWagonWork* work) {
    u8 c;
    s32 t;
    s32 d;

    if (IsPooSoraOnWagon()) {
        if (work->pos.y == work->pos2.y) {
            work->pos.y += 0x100;
            gPooActor.pos.y += 0x100;

            if (work->poohAboard) {
                gPoohPos->y += 0x100;
            }
        }
    } else if (!IsPooEventDone(6)) {
        if (work->pos.y != work->pos2.y) {
            work->pos.y -= 0x100;
            gPooActor.pos.y -= 0x100;

            if (work->poohAboard) {
                gPoohPos->y -= 0x100;
            }
        }
    }

    c = IsInPooWagonAreaForPooh(gPoohPos);

    if (c) {
        if (!work->poohAboard) {
            gPoohRequestX = work->pos.x;
            gPoohRequestY = work->pos.y;
            gPoohRequest = 11;
            work->poohAboard = 1;
        }
    } else {
        work->poohAboard = 0;
    }

    if (IsPooSoraOnWagon() && IsPoohWaitingOnWagon() && !IsPooEventDone(6)) {
        work->timer++;

        if (work->timer > 100) {
            if (work->pos.y != work->pos2.y + 0xC00) {
                t = work->pos.y - 0xC00;
                d = work->pos2.y - t;
                work->pos.y += d;
                gPooActor.pos.y += d;
                gPoohPos->y += d;
                SetPooEventDone(6);
                m4aSongNumStart(SONG_SYS_OBJ_BREAK);
                work->timer = 0;
            }
        }
    } else {
        work->timer = 0;
    }

    return 1;
}

void task_poo_wagon_2(PooWagonWork* work) {
    s32 t;
    s16 x;
    s16 y;
    u16 n;
    u16 p;
    s32 d;
    s32 k;

    d = 0;

    if (work->timer != 0) {
        t = gSineTable[(u8)work->angle];
        work->angle += 16;
    } else {
        t = 0;
    }

    x = ((work->pos.x + t) >> 8) - gPooScrollX;
    y = (work->pos.y >> 8) + (work->pos.z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 32, 40, 48, 48)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjTiles(work->tiles2);
            ReleaseObjTiles(work->tiles3);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }

        return;
    }

    if (work->palette == NULL) {
        work->tiles = AllocObjTiles(0x560, gRaWagonTiles);
        work->tiles2 = AllocObjTiles(0x4C0, gRaWagonTiles);
        work->tiles3 = AllocObjTiles(160, gRaWagonTiles);
        work->palette = LoadObjPalette(gRaWagonPalette, 32);
    }

    n = GetPooSoraPriority();

    if (IsPooSoraOverWagon()) {
        sPooWagonPriority = n + 3;
        sPooWagonPriority2 = n - 1;

        if (IsPoohOnWagon()) {
            if (gPooActor.pos.y >= gPoohPos->y) {
                sPooWagonPriority += 6;
            } else {
                sPooWagonPriority2 += 0xFFFC;
            }
        }
    } else {
        d = (u8)GetPooWagonSide(gPooActor.pos.x, gPooActor.pos.y);

        if (d == 0) {
            k = work->pos.y + 0x300;
            sPooWagonPriority = -0x1004 - (k >> 8) * 4;
            sPooWagonPriority2 = -0x1009 - (k >> 8) * 4;
        } else if (d == 83 || d == 173) {
            sPooWagonPriority = n - 3;
            sPooWagonPriority2 = n - 8;
        } else {
            sPooWagonPriority2 = n + 4;
            sPooWagonPriority = n + 9;
        }
    }

    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), sPooWagonPriority);
    DrawSprite(x, y, work->gfx2, work->tiles2, work->palette, NULL, SPRITE_PRIORITY(2), sPooWagonPriority2);
    p = -0x1002 - ((work->pos.y - 0xE00) >> 8) * 4;

    if (!IsPooSoraOverWagon() && n > p && (d == 83 || d == 173)) {
        p = n - 1;
    }

    DrawSprite(x, y, work->gfx3, work->tiles3, work->palette, NULL, SPRITE_PRIORITY(2), p);
}

void task_poo_wagon_3(PooWagonWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjTiles(work->tiles2);
        ReleaseObjTiles(work->tiles3);
        ReleaseObjPalette(work->palette);
    }
}

u16 GetPooWagonPriority2() {
    return sPooWagonPriority2;
}

u16 GetPooWagonPriority() {
    return sPooWagonPriority;
}

void task_poo_wagonwheel_0(PooWheelWork* work) {
    s16 x;
    s16 y;

    if (!IsPooEventDone(6)) {
        work->x = 0x2A800;
        work->y = 0x18D00;
        work->animId = 2;
        work->gfx = gRaWagonFrame3;
    } else {
        GetPooStateWheelPos(&x, &y);
        work->x = x << 8;
        work->y = y << 8;
        work->animId = 4;
        work->gfx = gRaWagonFrame10;
    }

    work->startX = work->x;
    work->z = 0;
    work->unk_30 = 0;
    work->tileBytes = 0x180;
    work->palette = NULL;
    AnimInit(&work->anim, gRaWagonAnims, gRaWagonFrames);
    AnimStart(&work->anim, work->animId, ANIM_FLAG_LOOP);
    work->speed = 0;
    work->removeWhenOffscreen = 0;
}

u8 task_poo_wagonwheel_1(PooWheelWork* work) {
    if (work->animId == 2 && IsPooEventDone(6)) {
        work->animId = 3;
        AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);
    }

    if (work->animId == 3) {
        work->gfx = AnimUpdate(&work->anim);

        if (work->speed <= 0x4FF) {
            work->speed += 6;
        }

        work->y += work->speed;
        work->x += work->speed;

        if (work->x > work->startX + 0x4800) {
            work->x = work->startX + 0x4800;
        }
    }

    if (work->removeWhenOffscreen != 0 && work->palette == NULL) {
        return 0;
    }

    return 1;
}

void task_poo_wagonwheel_2(PooWheelWork* work) {
    u16* p;
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 32, 0, 16, 16)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;

            if (work->animId == 3) {
                work->animId = 4;
                work->gfx = gRaWagonFrame10;
            }
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, gRaWagonTiles);
            work->palette = LoadObjPalette(gRaWagonPalette, 0x20);
        }

        if (!IsPooEventDone(6)) {
            p = &sPooWagonWheelPriority;
            *p = GetPooWagonPriority2() - 1;
        } else {
            sPooWagonWheelPriority = -0x1004 - (work->y >> 8) * 4;
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), sPooWagonWheelPriority);
    }
}

void task_poo_wagonwheel_3(PooWheelWork* work) {
    if (IsPooEventDone(6)) {
        SetPooStateWheelPos(work->x >> 8, work->y >> 8);
    }

    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }
}

void task_poo_spark_0(PooSparkWork* work, PooPos* p) {
    work->pos = *p;
    work->tiles = AllocObjTiles(0x200, gUnk_098A4B68);
    work->palette = LoadObjPalette(gCommonObjPalette, 0x20);
    AnimInit(&work->anim, gUnk_09EF8CC0, gUnk_09EF8CA0);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
}

u8 task_poo_spark_1(PooSparkWork* work) {
    AnimUpdate(&work->anim);

    if (AnimIsFinished(&work->anim)) {
        return 0;
    }

    return 1;
}

void task_poo_spark_2(PooSparkWork* work) {
    u16 x;
    u16 y;

    x = (work->pos.x >> 8) - gPooScrollX;
    y = (work->pos.y >> 8) + (work->pos.z >> 8) - gPooScrollY;
    DrawSprite(x, y, AnimGetGfx(&work->anim), work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 0x50);
}

void task_poo_spark_3(PooSparkWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_poo_bee_0(PooBeeWork* work) {
    void* a;
    void* b;
    s32 i;

    work->x = 0x8DE00;
    work->y = 0x46600;
    work->z = -0xA00;
    work->unk_B0 = 0;
    i = 0;
    a = gEeBeeAnims;
    b = gEeBeeFrames;

    for (; i < 4; i++) {
        work->sub[i].x = -0x500;
        work->sub[i].y = 0x500;
        work->sub[i].targetX = gPooBeePoints[i].x;
        work->sub[i].targetY = gPooBeePoints[i].y;
    }

    AnimInit(&work->anim, a, b);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->palette = NULL;
    sPooBeeCount = 0;
    work->releaseTimer = 8;
    work->setupPending = 1;
}

u8 task_poo_bee_1(PooBeeWork* work) {
    s32 i;

    if (IsPooHoneycombShaken()) {
        if (work->setupPending) {
            work->setupPending = 0;

            for (i = 0; i < 4; i++) {
                work->sub[i].x = work->x - 0x500;
                work->sub[i].y = work->y + 0x500;
                work->sub[i].z = work->z;
                work->sub[i].targetX = 0x2000 + gPoohPos->x + gPooBeePoints[i].x;
                work->sub[i].targetY = -0x2000 + gPoohPos->y + gPooBeePoints[i].y;
            }
        }

        if (sPooBeeCount <= 3) {
            ApproachValue(&work->sub[sPooBeeCount].x, work->sub[sPooBeeCount].targetX, work->releaseTimer);
            ApproachValue(&work->sub[sPooBeeCount].y, work->sub[sPooBeeCount].targetY, work->releaseTimer);
            work->releaseTimer--;

            if (work->releaseTimer == 0) {
                work->releaseTimer = 8;
                sPooBeeCount++;

                if (sPooBeeCount > 3) {
                    work->x = gPoohPos->x + 0x2000;
                    work->y = gPoohPos->y - 0x2000;
                    work->dx = work->dy = 0;
                }
            }

            SetPooCameraFocus(work->x, work->y + work->z);
        } else {
            work->dx = work->x - (gPoohPos->x + 0x2000);
            work->dy = work->y - (gPoohPos->y - 0x2000);
            work->x -= work->dx;
            work->y -= work->dy;

            for (i = 0; i < 4; i++) {
                work->sub[i].x -= work->dx;
                work->sub[i].y -= work->dy;
            }

            if (!IsPoohBeeChaseOver()) {
                SetPooCameraFocus(work->x, work->y + work->z);
            }
        }

        work->gfx = AnimUpdate(&work->anim);
    }

    return 1;
}

void task_poo_bee_2(PooBeeWork* work) {
    s32 x;
    s32 y;
    s32 u;
    s32 v;
    s32 i;

    if (!IsPooHoneycombShaken()) {
        return;
    }

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 19, 17, 46, 16)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            ReleaseObjTiles(work->tiles);
            work->palette = NULL;
        }

        return;
    }

    if (work->palette == NULL) {
        work->palette = LoadObjPalette(gEeBeePalette, 32);
        work->tiles = LoadObjTiles(gEeBeeTiles, 0x180);
    }

    for (i = 0; i < sPooBeeCount + 1 && i <= 3; i++) {
        u = (work->sub[i].x >> 8) - gPooScrollX;
        v = (work->sub[i].y >> 8) + (work->sub[i].z >> 8) - gPooScrollY;
        DrawSprite(u, v, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), i - ((work->y >> 8) * 4 + 0x1003));
    }
}

void task_poo_bee_3(PooBeeWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }
}

u8 AreAllPooBeesOut() {
    if (sPooBeeCount <= 3) {
        return 0;
    }

    return 1;
}

void task_poo_beeAfterEvent_0(PooBeeAfterEventWork* work) {
    sPooBeeAfterEventWork = work;
    work->x = 0x8DE00;
    work->y = 0x46600;
    work->z = -0xA00;
    work->unk_50 = 0;
    AnimInit(&work->anim, gEeBeeAnims, gEeBeeFrames);
    AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    AnimInit(&work->anim2, gEeBeeAnims, gEeBeeFrames);
    AnimStart(&work->anim2, 0, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    work->palette = NULL;
}

u8 task_poo_beeAfterEvent_1(PooBeeAfterEventWork* work) {
    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    return 1;
}

void task_poo_beeAfterEvent_2(PooBeeAfterEventWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 19, 17, 46, 16)) {
        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
            ReleaseObjTiles(work->tiles);
            ReleaseObjTiles(work->tiles2);
            work->palette = NULL;

            if (!IsPooMapBeeVisible()) {
                m4aSongNumStop(SONG_SND_386);
            }
        }
    } else {
        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gEeBeePalette, 0x20);
            work->tiles = LoadObjTiles(gEeBeeTiles, 0x180);
            work->tiles2 = LoadObjTiles(gEeBeeTiles, 0x180);
            m4aSongNumStart(SONG_SND_386);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1002 - (work->y >> 8) * 4);
        DrawSprite(x - 5, y + 5, work->gfx2, work->tiles2, work->palette, NULL, SPRITE_PRIORITY(2), -0x1003 - (work->y >> 8) * 4);
    }
}

void task_poo_beeAfterEvent_3(PooBeeAfterEventWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjTiles(work->tiles2);
        ReleaseObjPalette(work->palette);
    }
}

u8 IsPooBeeAfterEventVisible() {
    if (IsPooEventDone(2)) {
        if (sPooBeeAfterEventWork->palette != NULL) {
            return 1;
        }
    }

    return 0;
}

void GetPooCabbageStackSpot(PooSpot* p) {
    PooSpot t[18];
    u16 i;

    memcpy(t, gPooCabbageStackOffsets, sizeof(t));
    i = GetPooCabbageCount();

    if (i > 13) {
        i += GetRandom() % 4;
    }

    p->x = t[i].x + 0xAB300;
    p->y = t[i].y + 0x57100;
    p->z = t[i].z;
}

void task_poo_cabbage_0(PooCabbageWork* work) {
    u16 r;

    work->x = 0x98300;
    work->y = 0x4D100;
    work->z = 0;
    work->vz = 0x4CC;
    r = GetRandom();
    work->angle = (r & 15) + 88;
    work->speed = 0x1CC;
    work->palette = NULL;
    AnimInit(&work->anim, gRaVegetablesAnims, gRaVegetablesFrames);
    work->state = 2;
    AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    ColliderInit(&work->collider, 10, 8, 16);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    work->colliderActive = 1;
    TaskPoolInit(&work->tasks, 2);
    CreatePooShadowscaleTask(&work->tasks, &work->x, 0x80);
    work->task = NULL;
    work->age = 0;
    work->wasOnScreen = 0;
    work->animating = 1;
}

u8 task_poo_cabbage_1(PooCabbageWork* work) {
    u16 t[15];
    u16 sx;
    s16 sy;
    s32 v;

    memcpy(t, gPooCabbageRemoveCounts, sizeof(t));
    work->age++;

    switch (work->state) {
    case 2:
        if (gPooAttackActive && PooAttackHitsCollider(&work->collider)) {
            if (IsTaskActive(work->task)) {
                TaskKill(&work->tasks, work->task);
            }

            work->task = TaskCreate(&work->tasks, &gTaskDescPooSpark, &work->x);
            work->state = 3;
            AnimStart(&work->anim, 3, 0);
            m4aSongNumStart(SONG_SND_222);
            work->moveTimer = 30;
            work->zTimer = 20;
            work->hopHeight = -0x2000;
            GetPooCabbageStackSpot((PooSpot*)&work->targetX);
            work->stackIndex = GetPooCabbageCount();
            IncPooCabbageCount();

            if (work->colliderActive) {
                ColliderUnregister(&work->collider);
                work->colliderActive = 0;
            }
        } else {
            work->x += gSineTable[work->angle] * work->speed >> 8;
            work->y += -gSineTable[work->angle + 0x40] * work->speed >> 8;
            work->vz += 51;
            work->z += work->vz;

            if (work->z > 0) {
                work->z = 0;
                work->vz = -(work->vz * 179 >> 8);
            }

            if (work->wasOnScreen) {
                v = (work->x >> 8) - gPooScrollX;
                sy = (work->y >> 8) + (work->z >> 8) - gPooScrollY;
                sx = v;

                if ((u16)(sx + 16) > 272 || sy < -36 || sy > 196) {
                    return 0;
                }
            }
        }

        break;
    case 3:
        if (work->zTimer != 0) {
            ApproachValue(&work->z, work->targetZ + work->hopHeight, work->zTimer);
            work->zTimer--;

            if (work->zTimer == 0 && work->hopHeight < 0) {
                work->zTimer = 10;
                work->hopHeight = 0;
            }
        }

        ApproachValue(&work->x, work->targetX, work->moveTimer);
        ApproachValue(&work->y, work->targetY, work->moveTimer);
        work->moveTimer--;

        if (work->moveTimer == 0) {
            work->state = 4;
            AnimStart(&work->anim, 4, 0);
        }

        break;
    case 4:
        if (!IsPooEventDone(4) && work->stackIndex == 13) {
#ifdef VERSION_EU
            ExitPoohMode(140);
#else
            ExitPoohMode(142);
#endif
            SetPooEventDone(4);
            SetJiminyFlag(83);
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 1;
            AnimStart(&work->anim, 1, 0);
            IncPooCabbageLandedCount();
            work->animating = 0;

            if (work->stackIndex == 5) {
                work->x = 0xAB300;
                work->y = 0x57100;
                work->z = 0;
                work->gfx = gRaVegetablesFrame10;
            } else if (work->stackIndex == 8) {
                work->x = 0xAB300;
                work->y = 0x57100;
                work->z = 0;
                work->gfx = gRaVegetablesFrame11;
            } else {
                work->gfx = gRaVegetablesFrame1;
            }
        }

        break;
    case 1:
        if (t[work->stackIndex] < GetPooCabbageLandedCount()) {
            return 0;
        }

        break;
    }

    return 1;
}

void task_poo_cabbage_2(PooCabbageWork* work) {
    u16 t[5];
    u16 z;
    s16 x;
    s16 y;

    memcpy(t, gPooCabbageStackPriorities, sizeof(t));
    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (x < -16 || x > 256 || y < -36 || y > 196) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = LoadObjTiles(gRaVegetablesTiles, 0x1D20);
            work->palette = LoadObjPalette(gRaVegetablesPalette, 32);
        }

        if (work->animating) {
            work->gfx = AnimUpdate(&work->anim);
        }

        work->wasOnScreen = 1;

        if (work->colliderActive) {
            ColliderSetPosition(&work->collider, work->x, work->y, work->z);
        }

        if (work->stackIndex < 9 || work->stackIndex > 13) {
            z = -0x1004 - (work->y >> 8) * 4;
        } else {
            z = 0xDA38 - t[work->stackIndex - 9];
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), z);

        if (work->state != 4 && work->state != 1) {
            TaskPoolUpdate(&work->tasks);
            TaskPoolDraw(&work->tasks);
        }
    }
}

void task_poo_cabbage_3(PooCabbageWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }

    if (work->colliderActive) {
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_cabbageborn_0(PooCabbageBornWork* work) {
    TaskPoolInit(&work->tasks, 0x20);
    work->unk_14 = 0;
    work->timer = 0;
    sPooCabbageCount = 0;
    sPooCabbageLandedCount = 0;
}

u8 CanSpawnPooCabbage() {
    if (IsPooEventDone(6) && !IsPoohOffScreen() && gPooScrollX > 0x9EB && gPooScrollX <= 0xA8A && gPooScrollY <= 0x548 && gPooScrollY > 0x4F9) {
        return 1;
    }

    return 0;
}

u8 task_poo_cabbageborn_1(PooCabbageBornWork* work) {
    if (CanSpawnPooCabbage() && work->timer == 0) {
        TaskCreate(&work->tasks, &gTaskDescPooCabbage, NULL);
        work->timer = 40;
    }

    if (work->timer != 0) {
        work->timer--;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_poo_cabbageborn_2(PooCabbageBornWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_poo_cabbageborn_3(PooCabbageBornWork* work) {
    TaskPoolDestroy(&work->tasks);
}

void IncPooCabbageCount() {
    if (sPooCabbageCount <= 13) {
        sPooCabbageCount++;
    }
}

u16 GetPooCabbageCount() {
    return sPooCabbageCount;
}

void IncPooCabbageLandedCount() {
    sPooCabbageLandedCount++;
}

u16 GetPooCabbageLandedCount() {
    return sPooCabbageLandedCount;
}

u8 IsPooCabbageGameActive() {
    if (!IsPooEventDone(4)) {
        if (IsPooEventDone(6)) {
            if (gPooScrollY > 0x4F9) {
                return 1;
            }
        }
    }

    return 0;
}

void task_poo_mapobjhit_0(PooMapObjHitWork* work, PooMapObjHitArgs* a) {
    work->x = a->x;
    work->y = a->y;
    work->z = 0;
    work->kind = a->kind;
    work->prizeId = a->prizeId;
    work->desc = a->desc;
    work->tileBytes = GetMaxSpriteTileBytes(work->desc->gfxTable, work->desc->gfxCount);
    work->palette = NULL;
    AnimInit(&work->anim, work->desc->anims, work->desc->gfxTable);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->collider.radius = 0x1000;
    work->collider.height = 0x1800;
    ColliderSetPosition(&work->collider, work->x + 0x1000, work->y + 0xC00, work->z);
    work->playing = 0;
}

u8 task_poo_mapobjhit_1(PooMapObjHitWork* work) {
    SetPooRabbitTalkBlocked(0);

    if (gPooAttackActive) {
        if (PooAttackHitsCollider(&work->collider)) {
            if (!work->playing) {
                work->playing = 1;
                AnimReset(&work->anim);

                if (!IsPooPrizeDropped(work->prizeId)) {
                    if (SpawnPooPrizes(2, 1, work->x + 0x1000, work->y + 0x1800, work->z) != 0) {
                        SetPooPrizeDropped(work->prizeId);
                    }
                }

                if (work->kind == 4) {
                    m4aSongNumStart(SONG_SYS_PO_WOOD);
                } else {
                    m4aSongNumStart(SONG_SND_224);
                }
            }
        }
    }

    if (work->playing) {
        work->gfx = AnimUpdate(&work->anim);

        if (AnimIsFinished(&work->anim)) {
            work->playing = 0;
        }
    }

    return 1;
}

void task_poo_mapobjhit_2(PooMapObjHitWork* work) {
    s16 x;
    s16 y;
    s32 pr;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (!work->playing || IsRectOutsideScreen(x, y, 0, 24, 0, 32)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }
    } else {
        if (work->palette == NULL) {
            work->tiles = AllocObjTiles(work->tileBytes, work->desc->tiles);
            work->palette = LoadObjPalette(work->desc->palette, 0x20);
        }

        pr = 0x800;
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, pr, 0xFFF1);
        SetPooRabbitTalkBlocked(1);
    }
}

void task_poo_mapobjhit_3(PooMapObjHitWork* work) {
    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
        ReleaseObjTiles(work->tiles);
    }
}

void CreatePooMapobjhitTask(void* pool, u32 a, s32 x, s32 y, u16 e) {
    PooMapObjHitArgs args;

    args.x = x;
    args.y = y;
    args.desc = &gPooMapObjHitDescs[a];
    args.kind = a;
    args.prizeId = e;
    TaskCreate(pool, &gTaskDescPooMapobjhit, &args);
}

void PooPrizeUpdateBounce(PooPrizeWork* work) {
    u8 v;

    work->vz += 56;
    work->z += work->vz;
    work->x += gSineTable[work->angle] * work->speed >> 8;
    work->y += -gSineTable[work->angle + 0x40] * work->speed >> 8;

    if (IsPooPosBlocked((PooPos*)work)) {
        work->angle = (u8)(work->angle + 100) + GetRandom() % 57;
    } else {
        work->ground = 0;
    }

    if (work->z > work->ground) {
        work->z = work->ground;
        work->vz = -(work->vz * 179 >> 8);
        work->speed = work->speed * 212 >> 8;
    }

    if (work->collider.colliding && ColliderIsTouchingType(&work->collider, 1)) {
        switch (work->kind) {
        case 2:
        case 3:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.progression.mooglePoints += work->amount;

            if (gGameState.progression.mooglePoints > 99999) {
                gGameState.progression.mooglePoints = 99999;
            }

            break;
        case 0:
        case 1:
        default:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.hp += work->amount;

            if (gGameState.hp > gGameState.progression.maxHp) {
                gGameState.hp = gGameState.progression.maxHp;
            }

            break;
        }

        work->update = PooPrizeUpdateCollect;
        work->timer = 0;
        work->angle = GetAngle(gPooActor.pos.x, gPooActor.pos.y, work->x, work->y);
        work->collected = 1;
        work->visible = 1;
        work->spin = GetRandom() % 6 + 5;
        ColliderSetDisabled(&work->collider, 1);
    } else {
        ColliderSetPosition(&work->collider, work->x, work->y, work->z);

        if (work->timer == 20) {
            ColliderSetDisabled(&work->collider, 0);
        }

        if (work->timer > 420) {
            v = 0;

            if (!work->visible) {
                v = 1;
            }

            work->visible = v;
        }

        if (work->timer++ > 480) {
            work->update = NULL;
        }
    }
}

void PooPrizeUpdateCollect(PooPrizeWork* work) {
    PooPos* g;
    const s16* t;
    s32 tx;
    s32 ty;
    s32 tz;
    s32 s;
    u8 a;

    g = &gPooActor.pos;
    t = gSineTable;
    a = work->angle;
    tx = g->x + ((t[a] << 5) * work->scale >> 8);
    s = -gSineTable[a + 0x40] * 22;
    ty = g->y + (s * work->scale >> 8);
    tz = g->z - ((work->timer >> 1) << 8);
    work->angle = a + work->spin;
    work->x += (tx - work->x) >> 2;
    work->y += (ty - work->y) >> 2;
    work->z += (tz - work->z) >> 2;
    work->ground = 0;
    work->scale -= 2;

    if (work->timer > 60) {
        work->update = NULL;
    } else {
        work->timer++;
    }
}

void task_poo_prize_0(PooPrizeWork* work, PoohPrizeArgs* a) {
    work->x = a->x;
    work->y = a->y;
    work->z = a->z;
    work->ground = 0;
    work->vz = -(GetRandom() % 0x301 + 0x200);
    work->speed = GetRandom() % 155 + 153;
    work->angle = GetRandom();
    work->tiles = LoadObjTiles(gUnk_098A5CF4, 0x160);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    work->kind = a->kind;

    switch (work->kind) {
    case 3:
        work->gfx = gUnk_098A5CAE;
        work->amount = 10;
        break;
    case 2:
        work->gfx = gUnk_098A5CA4;
        work->amount = 4;
        break;
    case 1:
        work->gfx = gUnk_098A5C9A;
        work->amount = 10;
        break;
    case 0:
    default:
        work->gfx = gUnk_098A5C90;
        work->amount = 3;
        break;
    }

    work->gfx2 = gUnk_098A5CB8;
    work->collected = 0;
    work->visible = 1;
    work->timer = 0;
    work->update = PooPrizeUpdateBounce;
    work->scale = 0x100;
    ColliderInit(&work->collider, 5, 16, 50);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    ColliderSetDisabled(&work->collider, 1);
}

u8 task_poo_prize_1(PooPrizeWork* work) {
    if (work->update != NULL) {
        work->update(work);

        if (work->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void task_poo_prize_2(PooPrizeWork* work) {
    ObjAffine* aff;
    s32 s;
    s16 x;
    s16 y;

    if (!work->visible) {
        return;
    }

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8)) {
        return;
    }

    s = work->scale;

    if (s != 256) {
        aff = AllocObjAffine(0, s, s, 0);
    } else {
        aff = NULL;
    }

    DrawSprite(x, y, work->gfx, work->tiles, work->palette, aff, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);

    if (!work->collected) {
        y = (work->y >> 8) + (work->ground >> 8) - gPooScrollY;
        DrawSprite(x, y, work->gfx2, work->tiles, work->palette, aff, SPRITE_PRIORITY(2), 0xFFF0);
    }
}

void task_poo_prize_3(PooPrizeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ColliderUnregister(&work->collider);
}

void task_poo_zzz_0(PooZzzWork* work, u8* arg) {
    work->pos = gPoohPos;
    work->tiles = AllocObjTiles(0x100, gPoohFl05Tiles);
    work->palette = LoadObjPalette(gPoohPalette, 0x20);
    AnimInit(&work->anim, gPoohFl05Anims, gPoohFl05Frames);

    if (*arg != 0) {
        AnimStart(&work->anim, 8, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&work->anim, 7, ANIM_FLAG_LOOP);
    }

    work->gfx = AnimGetGfx(&work->anim);
}

u8 task_poo_zzz_1(void* w) {
    return 1;
}

void task_poo_zzz_2(PooZzzWork* work) {
    PooPos* p;
    s16 x;
    s16 y;
    void* g;

    p = work->pos;
    x = (p->x >> 8) - gPooScrollX;
    y = (p->y >> 8) + (p->z >> 8) - gPooScrollY;

    if (x >= -0x20 && x <= 0x110 && y >= -0x20 && y <= 0xC0) {
        g = AnimUpdate(&work->anim);
        work->gfx = g;
        DrawSprite(x, y, g, work->tiles, work->palette, NULL, SPRITE_PRIORITY(1), 0x0B);
    }
}

void task_poo_zzz_3(PooZzzWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void PooBflyPartSetDir(PooBflyPart* p) {
    switch (((p->angle + 16) & 0xFF) >> 5) {
    case 1:
        p->dirIndex = 4;
        p->flipped = 1;
        break;
    case 2:
        p->dirIndex = 3;
        p->flipped = 1;
        break;
    case 3:
        p->dirIndex = 2;
        p->flipped = 1;
        break;
    case 4:
        p->dirIndex = 1;
        p->flipped = 0;
        break;
    case 5:
        p->dirIndex = 2;
        p->flipped = 0;
        break;
    case 6:
        p->dirIndex = 3;
        p->flipped = 0;
        break;
    case 7:
        p->dirIndex = 4;
        p->flipped = 0;
        break;
    case 0:
    default:
        p->dirIndex = 0;
        p->flipped = 0;
        break;
    }
}

void PooBflyPartSetAnimation(PooBflyPart* p) {
    const AnimDef* d;

    PooBflyPartSetDir(p);
    d = &gTrap01AnimDefs[p->dirIndex];
    AnimChangeWithTables(&p->anim, d->animId, ANIM_FLAG_LOOP, d->anims, d->gfxTable);
    SetObjTileSource(p->tiles, d->tiles);
}

void PooBflyPartInit(PooBflyPart* p) {
    if ((s8)p->angle >= 0) {
        p->targetX = p->pointBX;
        p->targetY = p->pointBY;
    } else {
        p->targetX = p->pointAX;
        p->targetY = p->pointAY;
    }

    p->tiles = AllocObjTiles(0x40, NULL);
    AnimInit(&p->anim, NULL, NULL);
    PooBflyPartSetAnimation(p);
    p->gfx = AnimGetGfx(&p->anim);
}

void task_poo_butterfly_0(PooButterflyWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y;
    work->z = p->z - 0xE00;
    work->palette = LoadObjPalette(gTrap0100Palette, 0x20);
    work->parts[0].x = work->x - 0x1000;
    work->parts[0].y = work->y;
    work->parts[0].z = work->z;
    work->parts[0].pointAX = work->x - 0x1000;
    work->parts[0].pointAY = work->y;
    work->parts[0].pointBX = work->x + 0x600;
    work->parts[0].pointBY = work->y + 0x700;
    work->parts[0].angle = 0x60;
    work->parts[0].timer = 0x60;
    work->parts[1].x = work->x + 0x1200;
    work->parts[1].y = work->y;
    work->parts[1].z = work->z;
    work->parts[1].pointBX = work->x + 0x1200;
    work->parts[1].pointBY = work->y;
    work->parts[1].pointAX = work->x - 0x100;
    work->parts[1].pointAY = work->y - 0x700;
    work->parts[1].angle = 0xE0;
    work->parts[1].timer = 0x60;
    PooBflyPartInit(&work->parts[0]);
    PooBflyPartInit(&work->parts[1]);
}

void PooBflyPartUpdate(PooBflyPart* p) {
    if (p->timer != 0) {
        ApproachValue(&p->x, p->targetX, p->timer);
        ApproachValue(&p->y, p->targetY, p->timer);
        p->timer--;
    } else {
        p->timer = 0x60;
        p->angle += 0x80;

        if ((s8)p->angle >= 0) {
            p->targetX = p->pointBX;
            p->targetY = p->pointBY;
        } else {
            p->targetX = p->pointAX;
            p->targetY = p->pointAY;
        }
    }

    p->gfx = AnimUpdate(&p->anim);
}

u8 task_poo_butterfly_1(PooButterflyWork* work) {
    PooBflyPartUpdate(&work->parts[0]);
    PooBflyPartUpdate(&work->parts[1]);
    return 1;
}

u8 PooBflyPartDraw(PooBflyPart* p, void* pal) {
    s16 x;
    s16 y;
    s32 pr;

    x = (p->x >> 8) - gPooScrollX;
    y = (p->y >> 8) + (p->z >> 8) - gPooScrollY;

    if (x < -8 || x > 248 || y < -8 || y > 168) {
        return 0;
    }

    pr = p->flipped ? 0x801 : 0x800;
    PooBflyPartSetAnimation(p);
    DrawSprite(x, y, p->gfx, p->tiles, pal, NULL, pr, -0x1004 - (p->y >> 8) * 4);
    return 1;
}

void task_poo_butterfly_2(PooButterflyWork* work) {
    PooBflyPartDraw(&work->parts[0], work->palette);
    PooBflyPartDraw(&work->parts[1], work->palette);
}

void task_poo_butterfly_3(PooButterflyWork* work) {
    ReleaseObjTiles(work->parts[0].tiles);
    ReleaseObjTiles(work->parts[1].tiles);
    ReleaseObjPalette(work->palette);
}

u8 task_poo_butterflyRight_1(PooButterflyWork* work) {
    PooBflyPartUpdate(&work->parts[1]);
    return 1;
}

void task_poo_butterflyRight_2(PooButterflyWork* work) {
    PooBflyPartDraw(&work->parts[1], work->palette);
}

u8 task_poo_butterflyLeft_1(PooButterflyWork* work) {
    PooBflyPartUpdate(&work->parts[0]);
    return 1;
}

void task_poo_butterflyLeft_2(PooButterflyWork* work) {
    PooBflyPartDraw(&work->parts[0], work->palette);
}

void task_poo_mapbee_0(PooMapBeeWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y;
    work->z = 0;
    work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gPooMapbeeFrames, 1), gPooMapbeeTiles);
    work->palette = LoadObjPalette(gPooMapbeePalette, 0x20);
    AnimInit(&work->anim, gPooMapbeeAnims, gPooMapbeeFrames);
    AnimStart(&work->anim, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    work->onScreen = 1;
    work->state = 0;
    m4aSongNumStart(SONG_SND_386);
}

u8 task_poo_mapbee_1(PooMapBeeWork* work) {
    if (!work->onScreen) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (AnimIsFinished(&work->anim)) {
            AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
            work->state = 1;
        }

        break;
    case 1:
        work->z -= 0xCC;
        break;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_poo_mapbee_2(PooMapBeeWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8)) {
        work->onScreen = 0;
    } else {
        SetPooMapBeeVisible(1);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);
    }
}

void task_poo_mapbee_3(PooMapBeeWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);

    if (!IsPooBeeAfterEventVisible()) {
        m4aSongNumStop(SONG_SND_386);
    }
}

void task_poo_mapbeeborn_0(PooMapBornWork* work, PooPos* p) {
    work->pos = *p;
    work->pos.z = 0;
    work->x = p->x + 0x400;
    work->y = p->y + 0x1800;
    work->unk_08 = 0;
    ColliderSetPosition(&work->collider, work->x, work->y, 0);
    work->colliderActive = 0;
    work->unk_7C = 0;
    work->armed = 0;
    TaskPoolInit(&work->tasks, 1);
    work->task = NULL;
}

u8 task_poo_mapbeeborn_1(PooMapBornWork* work) {
    if (work->colliderActive) {
        if ((work->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0) {
            if (!IsTaskActive(work->task) && work->armed) {
                work->armed = 0;
                work->task = TaskCreate(&work->tasks, &gTaskDescPooMapbee, &work->pos);
            }
        } else {
            work->armed = 1;
        }
    }

    return 1;
}

void task_poo_mapbeeborn_2(PooMapBornWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 24, 0, 32)) {
        if (work->colliderActive) {
            work->colliderActive = 0;
            ColliderUnregister(&work->collider);
            work->armed = 0;

#ifdef VERSION_EU
            if (IsTaskActive(work->task)) {
                TaskKill(&work->tasks, work->task);
            }
#endif
        }
    } else {
        if (!work->colliderActive) {
            ColliderInit(&work->collider, 6, 28, 0);
            work->colliderActive = 1;
            work->armed = 1;
        }

        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_mapbeeborn_3(PooMapBornWork* work) {
    if (work->colliderActive) {
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_mapbutterfly_0(PooMapButterflyWork* work, PooPos* p) {
    work->x = p->x;
    work->y = p->y;
    work->z = 0;
    work->tiles = AllocObjTiles(0x40, gPooMapbutterflyTiles);
    work->palette = LoadObjPalette(gPooMapbutterflyPalette, 0x20);
    AnimInit(&work->anim, gPooMapbutterflyAnims, gPooMapbutterflyFrames);
    AnimStart(&work->anim, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    work->onScreen = 1;
}

u8 task_poo_mapbutterfly_1(PooMapButterflyWork* work) {
    if (!work->onScreen) {
        return 0;
    }

    work->z -= 0x80;
    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_poo_mapbutterfly_2(PooMapButterflyWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) + (work->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8)) {
        work->onScreen = 0;
    } else {
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);
    }
}

void task_poo_mapbutterfly_3(PooMapButterflyWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_poo_mapbutterflyborn_0(PooMapBornWork* work, PooPos* p) {
    work->pos = *p;
    work->pos.z = 0;
    work->x = p->x + 0x1000;
    work->y = p->y + 0x1800;
    work->unk_08 = 0;
    ColliderSetPosition(&work->collider, work->x, work->y, 0);
    work->colliderActive = 0;
    work->unk_7C = 0;
    work->armed = 0;
    TaskPoolInit(&work->tasks, 1);
    work->task = NULL;
}

u8 task_poo_mapbutterflyborn_1(PooMapBornWork* work) {
    if (work->colliderActive) {
        if ((work->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0) {
            if (!IsTaskActive(work->task) && work->armed) {
                work->armed = 0;
                work->task = TaskCreate(&work->tasks, &gTaskDescPooMapbutterfly, &work->pos);
            }
        } else {
            work->armed = 1;
        }
    }

    return 1;
}

void task_poo_mapbutterflyborn_2(PooMapBornWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 24, 0, 32)) {
        if (work->colliderActive) {
            work->colliderActive = 0;
            ColliderUnregister(&work->collider);
            work->armed = 0;
        }
    } else {
        if (!work->colliderActive) {
            ColliderInit(&work->collider, 6, 40, 0);
            work->colliderActive = 1;
            work->armed = 1;
        }

        TaskPoolUpdate(&work->tasks);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_mapbutterflyborn_3(PooMapBornWork* work) {
    if (work->colliderActive) {
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_rabbitAfterEvent_0(PooRabbitAfterEventWork* work) {
    work->x = 0xA9B00;
    work->y = 0x57200;
    work->z = 0;
    work->unk_30 = 0;
    work->palette = NULL;
    work->tileBytes = GetMaxSpriteTileBytes(gRabbitBl00Frames, 15);
    AnimInit(&work->anim, gRabbitBl00Anims, gRabbitBl00Frames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    TaskPoolInit(&work->tasks, 1);
    CreatePooShadowscaleTask(&work->tasks, &work->x, 0x100);
    ColliderSetPosition(&work->collider, work->x, work->y, work->z);
    work->interactionId = AddPoohInteraction(&work->collider, 60);
    SetPoohInteractionEnabled(work->interactionId, 0);
}

u8 task_poo_rabbitAfterEvent_1(PooRabbitAfterEventWork* work) {
    if (work->palette != NULL) {
        if (ColliderIsTouchingType(&work->collider, 9)) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_rabbitAfterEvent_2(PooRabbitAfterEventWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 48, 8, 16, 16)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            ColliderUnregister(&work->collider);
            SetPoohInteractionEnabled(work->interactionId, 0);
            work->palette = NULL;
        }
    } else {
        work->gfx = AnimUpdate(&work->anim);
        TaskPoolUpdate(&work->tasks);

        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gRabbitPalette, 0x40);
            work->tiles = AllocObjTiles(work->tileBytes, gRabbitBl00Tiles);
            ColliderInit(&work->collider, 10, 4, 48);
            SetPoohInteractionEnabled(work->interactionId, 1);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP, -0x1004 - (work->y >> 8) * 4);
        TaskPoolDraw(&work->tasks);
    }
}

void task_poo_rabbitAfterEvent_3(PooRabbitAfterEventWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
        ColliderUnregister(&work->collider);
    }

    TaskPoolDestroy(&work->tasks);
}

void task_poo_cabbageAfterEvent_0(PooCabbageAfterEventWork* work) {
    work->x = 0xAB300;
    work->y = 0x57100;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->palette = NULL;
    work->tileBytes = GetMaxSpriteTileBytes(gRaVegetablesFrames, 13);
    work->gfx = gRaVegetablesFrame9;
}

u8 task_poo_cabbageAfterEvent_1(PooCabbageAfterEventWork* work) {
    *(void* volatile*)&work->palette;
    return 1;
}

void task_poo_cabbageAfterEvent_2(PooCabbageAfterEventWork* work) {
    s16 x;
    s16 y;

    x = (work->x >> 8) - gPooScrollX;
    y = (work->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 48, 8, 16, 16)) {
        if (work->palette != NULL) {
            ReleaseObjTiles(work->tiles);
            ReleaseObjPalette(work->palette);
            work->palette = NULL;
        }
    } else {
        if (work->palette == NULL) {
            work->palette = LoadObjPalette(gRaVegetablesPalette, 0x20);
            work->tiles = AllocObjTiles(work->tileBytes, gRaVegetablesTiles);
        }

        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (work->y >> 8) * 4);
    }
}

void task_poo_cabbageAfterEvent_3(PooCabbageAfterEventWork* work) {
    if (work->palette != NULL) {
        ReleaseObjTiles(work->tiles);
        ReleaseObjPalette(work->palette);
    }
}

void ClearPooPrizesDropped() {
    s32 i;

    for (i = 0; i < 4; i++) {
        gPooState.droppedPrizes[i] = 0;
    }
}

void SetPooPrizeDropped(u16 a) {
    u32 i;
    u32 s;

    i = a / 32;
    s = a % 32;
    gPooState.droppedPrizes[i] |= 1 << s;
}

u8 IsPooPrizeDropped(u16 a) {
    u32 i;
    u32 s;

    i = a / 32;
    s = a % 32;

    if ((gPooState.droppedPrizes[i] & (1 << s)) != 0) {
        return 1;
    }

    return 0;
}

void ResetPooProgress() {
    ClearPooPrizesDropped();
    gPooState.eventsDone = 0;
    gPooState.gauge = 3;
    gPooState.gaugeTimer = 0x73B;
    gPoohGauge = 3;
    gPoohGaugeTimer = 0x73B;
}

void InitPooState() {
    gPooState.flags = 0;
    ResetPooProgress();
}

void SetPooStatePooh(PooPos* p, s32 b) {
    gPooState.pos = *p;
    gPooState.poohAction = b;
}

void GetPooStatePooh(PooPos* p, s32* b) {
    *p = gPooState.pos;
    *b = gPooState.poohAction;
}

void SetPooStateGauge(u16 a, u16 b) {
    gPooState.gauge = a;
    gPooState.gaugeTimer = b;
}

void GetPooStateGauge(u16* a, u16* b) {
    *a = gPooState.gauge;
    *b = gPooState.gaugeTimer;
}

void SetPooStateWheelPos(s16 a, s16 b) {
    gPooState.wheelX = a;
    gPooState.wheelY = b;
}

void GetPooStateWheelPos(u16* a, u16* b) {
    *a = gPooState.wheelX;
    *b = gPooState.wheelY;
}

void SetPooStatePos2(PooPos* p) {
    gPooState.pos2 = *p;
}

void GetPooStatePos2(PooPos* p) {
    *p = gPooState.pos2;
}

void SetPooEventDone(s32 a) {
    gPooState.eventsDone |= 1 << a;
}

u8 IsPooEventDone(s32 a) {
    if (((gPooState.eventsDone >> a) & 1) != 0) {
        return 1;
    }

    return 0;
}

void SetPooFlag(s32 a) {
    gPooState.flags |= 1 << a;
}

void ClearPooFlag(s32 a) {
    gPooState.flags &= ~(1 << a);
}

u8 IsPooFlagSet(s32 a) {
    if ((gPooState.flags & (1 << a)) != 0) {
        return 1;
    }

    return 0;
}

void GetPooState(void* p) {
    memcpy(p, &gPooState, sizeof(gPooState));
}

void SetPooState(const void* p) {
    memcpy(&gPooState, p, sizeof(gPooState));
}

u8 IsPooAltImageActive() {
    s32 v[6];
    u32 i;
    s32 n;

    memcpy(v, gPooMainEventIds, sizeof(v));

    if (IsPooFlagSet(1)) {
        return 1;
    }

    n = 0;

    for (i = 0; i < 6; i++) {
        if (IsPooEventDone(v[i])) {
            n++;
        }
    }

    if (n <= 4) {
        return 0;
    }

    return 1;
}

u16 AddPoohInteraction(Collider* a, u16 b) {
    if (sPoohInteractions->count > 5) {
        return 0xFFFF;
    }

    sPoohInteractions->entries[sPoohInteractions->count].collider = a;
    sPoohInteractions->entries[sPoohInteractions->count].message = b;
    sPoohInteractions->entries[sPoohInteractions->count].enabled = 1;
    return sPoohInteractions->count++;
}

void SetPoohInteractionEnabled(u16 a, u8 b) {
    sPoohInteractions->entries[a].enabled = b;
}

void FreePoohInteractions() {
    EwramFree(gSharedModeWork);
}

void InitPoohInteractions() {
    void** state = &gSharedModeWork;

    *state = EwramAlloc(sizeof(PoohInteractionRegistry));
    ((PoohInteractionRegistry*)*state)->count = 0;
    SetPooRabbitTalkBlocked(0);
}

u16 FindPoohInteractionMessage() {
    s32 i;

    for (i = 0; i < sPoohInteractions->count; i++) {
        if (sPoohInteractions->entries[i].message == 0x3B && sPoohInteractions->rabbitTalkBlocked) {
            continue;
        }

        if (!sPoohInteractions->entries[i].enabled) {
            continue;
        }

        if (!PooAttackHitsCollider(sPoohInteractions->entries[i].collider)) {
            continue;
        }

        return sPoohInteractions->entries[i].message;
    }

#ifdef VERSION_EU
    return 0xB3;
#else
    return 0xB4;
#endif
}

void SetPooRabbitTalkBlocked(u8 a) {
    sPoohInteractions->rabbitTalkBlocked = a;
}

TaskDesc gTaskDescPooPooh = {
    "task_poo_pooh",
    (TaskInitFunc)task_poo_pooh_0,
    (TaskUpdateFunc)task_poo_pooh_1,
    (TaskDrawFunc)task_poo_pooh_2,
    (TaskDestroyFunc)task_poo_pooh_3,
    sizeof(PoohWork),
};

const PooMapBgDesc gPooMapBgDesc = {
    gPooMapBgTiles, 32768, gPooMapBgPalette, 512, gPooMapBgTiles2, 16032, 16, 9
};

const PooSpawn gPooSpawns[85] = {
    { 130816, 99328, &gTaskDescPooHoney },
    { 223232, 130304, &gTaskDescPooTrapballoon },
    { 229888, 153088, &gTaskDescPooTrapballoon },
    { 251392, 143104, &gTaskDescPooPitAndButterfly },
    { 242688, 159488, &gTaskDescPooTrap },
    { 263936, 162816, &gTaskDescPooHoney },
    { 279040, 175104, &gTaskDescPooTrap },
    { 304896, 167424, &gTaskDescPooTrap },
    { 301824, 182784, &gTaskDescPooTrapballoon },
    { 444672, 238848, &gTaskDescPooTigerstump },
    { 411904, 238848, &gTaskDescPooTigerstump },
    { 428288, 247040, &gTaskDescPooTigerstump },
    { 428288, 230656, &gTaskDescPooTigerstump },
    { 440576, 231680, &gTaskDescPooTiBoard },
    { 407040, 218624, &gTaskDescPooHoney },
    { 463104, 266496, &gTaskDescPooTrap },
    { 476672, 251136, &gTaskDescPooPitAndButterfly },
    { 502272, 262912, &gTaskDescPooTrap },
    { 489216, 277504, &gTaskDescPooPitAndButterfly },
    { 484096, 265472, &gTaskDescPooTrapballoon },
    { 518400, 271616, &gTaskDescPooHoney },
    { 648960, 335616, &gTaskDescPooHoney },
    { 602624, 320256, &gTaskDescPooPoohstump },
    { 584192, 320256, &gTaskDescPooPoohstump },
    { 593408, 315648, &gTaskDescPooPoohstump },
    { 593408, 324864, &gTaskDescPooPoohstump },
    { 602624, 315136, &gTaskDescPooTiBoard },
    { 585984, 305920, &gTaskDescPooPoohstump },
    { 573440, 329472, &gTaskDescPooPoohstump },
    { 566016, 325376, &gTaskDescPooPoohstump },
    { 617728, 319488, &gTaskDescPooPoohstump },
    { 282624, 150272, &gTaskDescPooLeaf },
    { 512000, 285440, &gTaskDescPooLeaf },
    { 159744, 102400, &gTaskDescPooTanpopo },
    { 194560, 114688, &gTaskDescPooTanpopo },
    { 200704, 118784, &gTaskDescPooButterfly },
    { 167936, 120832, &gTaskDescPooTanpopo },
    { 174080, 124928, &gTaskDescPooButterflyRight },
    { 198656, 133120, &gTaskDescPooTanpopo },
    { 323584, 167936, &gTaskDescPooTanpopo },
    { 313344, 180224, &gTaskDescPooTanpopo },
    { 323584, 192512, &gTaskDescPooTanpopo },
    { 333824, 182272, &gTaskDescPooTanpopo },
    { 339968, 186368, &gTaskDescPooButterflyRight },
    { 350208, 182272, &gTaskDescPooTanpopo },
    { 337920, 190464, &gTaskDescPooTanpopo },
    { 358400, 190464, &gTaskDescPooTanpopo },
    { 301056, 196608, &gTaskDescPooTanpopo },
    { 325632, 212992, &gTaskDescPooTanpopo },
    { 350208, 198656, &gTaskDescPooTanpopo },
    { 374784, 200704, &gTaskDescPooTanpopo },
    { 362496, 204800, &gTaskDescPooTanpopo },
    { 382976, 210944, &gTaskDescPooTanpopo },
    { 370688, 212992, &gTaskDescPooTanpopo },
    { 391168, 219136, &gTaskDescPooTanpopo },
    { 374784, 221184, &gTaskDescPooTanpopo },
    { 358400, 225280, &gTaskDescPooTanpopo },
    { 387072, 229376, &gTaskDescPooTanpopo },
    { 374784, 233472, &gTaskDescPooTanpopo },
    { 391168, 241664, &gTaskDescPooTanpopo },
    { 395264, 204800, &gTaskDescPooTanpopo },
    { 405504, 221184, &gTaskDescPooTanpopo },
    { 403456, 247808, &gTaskDescPooTanpopo },
    { 313344, 200704, &gTaskDescPooTanpopo },
    { 325632, 202752, &gTaskDescPooTanpopo },
    { 337920, 198656, &gTaskDescPooTanpopo },
    { 344064, 206848, &gTaskDescPooTanpopo },
    { 350208, 210944, &gTaskDescPooButterflyLeft },
    { 356352, 212992, &gTaskDescPooTanpopo },
    { 342016, 215040, &gTaskDescPooTanpopo },
    { 79872, 38912, &gTaskDescPooMapbeeborn },
    { 153600, 75776, &gTaskDescPooMapbeeborn },
    { 559104, 278528, &gTaskDescPooMapbeeborn },
    { 632832, 315392, &gTaskDescPooMapbeeborn },
    { 706560, 352256, &gTaskDescPooMapbeeborn },
    { 780288, 389120, &gTaskDescPooMapbeeborn },
    { 131072, 63488, &gTaskDescPooMapbutterflyborn },
    { 278528, 137216, &gTaskDescPooMapbutterflyborn },
    { 352256, 174080, &gTaskDescPooMapbutterflyborn },
    { 536576, 266240, &gTaskDescPooMapbutterflyborn },
    { 610304, 303104, &gTaskDescPooMapbutterflyborn },
    { 684032, 339968, &gTaskDescPooMapbutterflyborn },
    { 757760, 376832, &gTaskDescPooMapbutterflyborn },
    { 794624, 395264, &gTaskDescPooMapbutterflyborn },
    { 831488, 413696, &gTaskDescPooMapbutterflyborn },
};

const PooPileDesc gPooPileDescs[12] = {
    { 611584, 339200, 4 },
    { 619264, 343296, 3 },
    { 626944, 347392, 2 },
    { 634624, 351488, 1 },
    { 642304, 355584, 2 },
    { 649984, 359680, 3 },
    { 657664, 363776, 4 },
    { 763904, 389632, 0 },
    { 759552, 398336, 0 },
    { 754688, 405760, 0 },
    { 747264, 411904, 0 },
    { 739072, 416768, 0 },
};

const PooTileDesc gPooTileDescs[80] = {
    { 106496, 49152, 0x3 },
    { 180224, 86016, 0x3 },
    { 327680, 159744, 0x3 },
    { 512000, 251904, 0x3 },
    { 585728, 288768, 0x3 },
    { 659456, 325632, 0x3 },
    { 770048, 380928, 0x3 },
    { 217088, 104448, 0x5 },
    { 253952, 122880, 0x5 },
    { 290816, 141312, 0x5 },
    { 364544, 178176, 0x5 },
    { 401408, 196608, 0x5 },
    { 438272, 215040, 0x5 },
    { 475136, 233472, 0x5 },
    { 548864, 270336, 0x5 },
    { 622592, 307200, 0x5 },
    { 696320, 344064, 0x5 },
    { 806912, 399360, 0x5 },
    { 131072, 63488, 0x8 },
    { 204800, 100352, 0x8 },
    { 278528, 137216, 0x8 },
    { 389120, 192512, 0x8 },
    { 352256, 174080, 0x8 },
    { 462848, 229376, 0x8 },
    { 536576, 266240, 0x8 },
    { 610304, 303104, 0x8 },
    { 684032, 339968, 0x8 },
    { 757760, 376832, 0x8 },
    { 794624, 395264, 0x8 },
    { 831488, 413696, 0x9 },
    { 94208, 45056, 0x4 },
    { 167936, 81920, 0x4 },
    { 241664, 118784, 0x4 },
    { 315392, 155648, 0x4 },
    { 425984, 210944, 0x4 },
    { 499712, 247808, 0x4 },
    { 647168, 321536, 0x4 },
    { 720896, 358400, 0x4 },
    { 116736, 57344, 0x1 },
    { 227328, 112640, 0x1 },
    { 301056, 149504, 0x1 },
    { 337920, 167936, 0x1 },
    { 374784, 186368, 0x1 },
    { 485376, 241664, 0x1 },
    { 522240, 260096, 0x1 },
    { 595968, 296960, 0x1 },
    { 669696, 333824, 0x1 },
    { 743424, 370688, 0x1 },
    { 817152, 407552, 0x1 },
    { 120832, 63488, 0x0 },
    { 194560, 100352, 0x0 },
    { 305152, 155648, 0x0 },
    { 342016, 174080, 0x0 },
    { 378880, 192512, 0x0 },
    { 526336, 266240, 0x0 },
    { 600064, 303104, 0x0 },
    { 673792, 339968, 0x0 },
    { 747520, 376832, 0x0 },
    { 153600, 75776, 0x6 },
    { 190464, 94208, 0x6 },
    { 264192, 131072, 0x6 },
    { 411648, 204800, 0x6 },
    { 448512, 223232, 0x6 },
    { 559104, 278528, 0x6 },
    { 632832, 315392, 0x6 },
    { 706560, 352256, 0x6 },
    { 780288, 389120, 0x6 },
    { 79872, 38912, 0x7 },
    { 83968, 45056, 0x2 },
    { 157696, 81920, 0x2 },
    { 231424, 118784, 0x2 },
    { 268288, 137216, 0x2 },
    { 415744, 210944, 0x2 },
    { 452608, 229376, 0x2 },
    { 489472, 247808, 0x2 },
    { 563200, 284672, 0x2 },
    { 636928, 321536, 0x2 },
    { 710656, 358400, 0x2 },
    { 784384, 395264, 0x2 },
    { 821248, 413696, 0x2 },
};

TaskDesc gTaskDescPooMap = {
    "task_poo_map",
    (TaskInitFunc)task_poo_map_0,
    (TaskUpdateFunc)task_poo_map_1,
    (TaskDrawFunc)task_poo_map_2,
    (TaskDestroyFunc)task_poo_map_3,
    sizeof(PooMapWork),
};

const PooAnimDesc gPooSoraAnimDescs[11][5] = {
    {
        { gSor1bb00Frames, gSor1bb00Anims, gSor1bb00Tiles, 0 },
        { gSor1ff00Frames, gSor1ff00Anims, gSor1ff00Tiles, 0 },
        { gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0 },
        { gSor1ll00Frames, gSor1ll00Anims, gSor1ll00Tiles, 0 },
        { gSor1bl00Frames, gSor1bl00Anims, gSor1bl00Tiles, 0 },
    },
    {
        { gSor1bb01Frames, gSor1bb01Anims, gSor1bb01Tiles, 0 },
        { gSor1ff01Frames, gSor1ff01Anims, gSor1ff01Tiles, 0 },
        { gSor1fl01Frames, gSor1fl01Anims, gSor1fl01Tiles, 0 },
        { gSor1ll01Frames, gSor1ll01Anims, gSor1ll01Tiles, 0 },
        { gSor1bl01Frames, gSor1bl01Anims, gSor1bl01Tiles, 0 },
    },
    {
        { gSor1bb02Frames, gSor1bb02Anims, gSor1bb02Tiles, 0 },
        { gSor1ff02Frames, gSor1ff02Anims, gSor1ff02Tiles, 0 },
        { gSor1fl02Frames, gSor1fl02Anims, gSor1fl02Tiles, 0 },
        { gSor1ll02Frames, gSor1ll02Anims, gSor1ll02Tiles, 0 },
        { gSor1bl02Frames, gSor1bl02Anims, gSor1bl02Tiles, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 0 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 0 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 0 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 0 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 1 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 1 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 1 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 1 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 1 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 2 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 2 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 2 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 2 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 2 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 3 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 3 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 3 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 3 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 3 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 4 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 4 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 4 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 4 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 4 },
    },
    {
        { gSor1bb15Frames, gSor1bb15Anims, gSor1bb15Tiles, 2 },
        { gSor1ff15Frames, gSor1ff15Anims, gSor1ff15Tiles, 2 },
        { gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 2 },
        { gSor1ll15Frames, gSor1ll15Anims, gSor1ll15Tiles, 2 },
        { gSor1bl15Frames, gSor1bl15Anims, gSor1bl15Tiles, 2 },
    },
    {
        { gSor1bb10Frames, gSor1bb10Anims, gSor1bb10Tiles, 0 },
        { gSor1ff10Frames, gSor1ff10Anims, gSor1ff10Tiles, 0 },
        { gSor1fl10Frames, gSor1fl10Anims, gSor1fl10Tiles, 0 },
        { gSor1ll10Frames, gSor1ll10Anims, gSor1ll10Tiles, 0 },
        { gSor1bl10Frames, gSor1bl10Anims, gSor1bl10Tiles, 0 },
    },
    {
        { gSor1bb61Frames, gSor1bb61Anims, gSor1bb61Tiles, 0 },
        { gSor1ff61Frames, gSor1ff61Anims, gSor1ff61Tiles, 0 },
        { gSor1fl61Frames, gSor1fl61Anims, gSor1fl61Tiles, 0 },
        { gSor1ll61Frames, gSor1ll61Anims, gSor1ll61Tiles, 0 },
        { gSor1bl61Frames, gSor1bl61Anims, gSor1bl61Tiles, 0 },
    },
};

const u16 gPooSoraSounds[8] = { SONG_SYS_SR_FOOTL, SONG_SYS_SR_FOOTR, SONG_SYS_SR_JUMP, SONG_SYS_SR_LAND, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSJP, 0 };

const u16* gPooBg3MapBlocks[144] = {
    gPooBg3Map0,
    gPooBg3Map1,
    gPooBg3Map2,
    gPooBg3Map3,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map16,
    gPooBg3Map17,
    gPooBg3Map18,
    gPooBg3Map19,
    gPooBg3Map20,
    gPooBg3Map21,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map34,
    gPooBg3Map35,
    gPooBg3Map36,
    gPooBg3Map37,
    gPooBg3Map38,
    gPooBg3Map39,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map52,
    gPooBg3Map53,
    gPooBg3Map54,
    gPooBg3Map55,
    gPooBg3Map56,
    gPooBg3Map57,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map70,
    gPooBg3Map71,
    gPooBg3Map72,
    gPooBg3Map73,
    gPooBg3Map74,
    gPooBg3Map75,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map88,
    gPooBg3Map89,
    gPooBg3Map90,
    gPooBg3Map91,
    gPooBg3Map92,
    gPooBg3Map93,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map106,
    gPooBg3Map107,
    gPooBg3Map108,
    gPooBg3Map109,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg3Map124,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
};

const u16* gPooBg1MapBlocks[144] = {
    gPooBg1Map0,
    gPooBg1Map1,
    gPooBg1Map2,
    gPooBg1Map3,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map16,
    gPooBg1Map17,
    gPooBg1Map18,
    gPooBg1Map19,
    gPooBg1Map20,
    gPooBg1Map21,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gPooBg1Map34,
    gPooBg1Map35,
    gPooBg1Map36,
    gPooBg1Map37,
    gPooBg1Map38,
    gPooBg1Map39,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gPooBg1Map52,
    gPooBg1Map53,
    gPooBg1Map54,
    gPooBg1Map55,
    gPooBg1Map56,
    gPooBg1Map57,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gPooBg1Map70,
    gPooBg1Map71,
    gPooBg1Map72,
    gPooBg1Map73,
    gPooBg1Map74,
    gPooBg1Map75,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gPooBg1Map88,
    gPooBg1Map89,
    gPooBg1Map90,
    gPooBg1Map91,
    gPooBg1Map92,
    gPooBg1Map93,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gPooBg1Map106,
    gPooBg1Map107,
    gPooBg1Map108,
    gPooBg1Map109,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gPooBg1Map124,
    gPooBg1Map125,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg1Map32,
    gPooBg1Map32,
    gUnk_08125E24,
    gUnk_08125E24,
};

const u16* gPooBg2MapBlocks[144] = {
    gUnk_08125E24,
    gPooBg2Map1,
    gPooBg2Map2,
    gPooBg2Map3,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg2Map18,
    gPooBg2Map19,
    gPooBg2Map20,
    gPooBg2Map21,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg2Map36,
    gPooBg2Map37,
    gPooBg2Map38,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg2Map54,
    gPooBg2Map55,
    gPooBg2Map56,
    gPooBg2Map57,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg2Map72,
    gPooBg2Map73,
    gPooBg2Map74,
    gPooBg2Map75,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg2Map90,
    gPooBg2Map91,
    gPooBg2Map92,
    gPooBg2Map93,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gPooBg2Map108,
    gPooBg2Map109,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
    gUnk_08125E24,
};

TaskDesc gTaskDescPooSora = {
    "task_poo_sora",
    (TaskInitFunc)task_poo_sora_0,
    (TaskUpdateFunc)task_poo_sora_1,
    (TaskDrawFunc)task_poo_sora_2,
    (TaskDestroyFunc)task_poo_sora_3,
    sizeof(PooSoraWork),
};

TaskDesc gTaskDescPooTrap = {
    "task_poo_trap",
    (TaskInitFunc)task_poo_trap_0,
    (TaskUpdateFunc)task_poo_trap_1,
    (TaskDrawFunc)task_poo_trap_2,
    (TaskDestroyFunc)task_poo_trap_3,
    sizeof(PooTrapWork),
};

TaskDesc gTaskDescPooPitAndButterfly = {
    "task_poo_pitAndButterfly",
    (TaskInitFunc)task_poo_pitAndButterfly_0,
    (TaskUpdateFunc)task_poo_pitAndButterfly_1,
    (TaskDrawFunc)task_poo_pitAndButterfly_2,
    (TaskDestroyFunc)task_poo_pitAndButterfly_3,
    sizeof(PooTrapWork),
};

TaskDesc gTaskDescPooBalloon = {
    "task_poo_balloon",
    (TaskInitFunc)task_poo_balloon_0,
    (TaskUpdateFunc)task_poo_balloon_1,
    (TaskDrawFunc)task_poo_balloon_2,
    (TaskDestroyFunc)task_poo_balloon_3,
    sizeof(PooBalloonObjWork),
};

TaskDesc gTaskDescPooShadow = {
    "task_poo_shadow",
    (TaskInitFunc)task_poo_shadow_0,
    (TaskUpdateFunc)task_poo_shadow_1,
    (TaskDrawFunc)task_poo_shadow_2,
    (TaskDestroyFunc)task_poo_shadow_3,
    sizeof(TaskPool),
};

TaskDesc gTaskDescPooShadowdodai = {
    "task_poo_shadowdodai",
    (TaskInitFunc)task_poo_shadowdodai_0,
    (TaskUpdateFunc)task_poo_shadowdodai_1,
    (TaskDrawFunc)task_poo_shadowdodai_2,
    (TaskDestroyFunc)task_poo_shadowdodai_3,
    sizeof(PooShadowWork),
};

TaskDesc gTaskDescPooShadowscale = {
    "task_poo_shadowscale",
    (TaskInitFunc)task_poo_shadowscale_0,
    (TaskUpdateFunc)task_poo_shadowscale_1,
    (TaskDrawFunc)task_poo_shadowscale_2,
    (TaskDestroyFunc)task_poo_shadowscale_3,
    sizeof(PooScaleWork),
};

TaskDesc gTaskDescPooFreeballoon = {
    "task_poo_freeballoon",
    (TaskInitFunc)task_poo_freeballoon_0,
    (TaskUpdateFunc)task_poo_freeballoon_1,
    (TaskDrawFunc)task_poo_freeballoon_2,
    (TaskDestroyFunc)task_poo_freeballoon_3,
    sizeof(PooFreeBalloonWork),
};

TaskDesc gTaskDescPooGauge = {
    "task_poo_gauge",
    (TaskInitFunc)task_poo_gauge_0,
    (TaskUpdateFunc)task_poo_gauge_1,
    (TaskDrawFunc)task_poo_gauge_2,
    (TaskDestroyFunc)task_poo_gauge_3,
    sizeof(PooGaugeWork),
};

TaskDesc gTaskDescPooTrapballoon = {
    "task_poo_trapballoon",
    (TaskInitFunc)task_poo_trapballoon_0,
    (TaskUpdateFunc)task_poo_trapballoon_1,
    (TaskDrawFunc)task_poo_trapballoon_2,
    (TaskDestroyFunc)task_poo_trapballoon_3,
    sizeof(PooBalloonWork),
};

TaskDesc gTaskDescPooOwlballoon = {
    "task_poo_owlballoon",
    (TaskInitFunc)task_poo_owlballoon_0,
    (TaskUpdateFunc)task_poo_owlballoon_1,
    (TaskDrawFunc)task_poo_owlballoon_2,
    (TaskDestroyFunc)task_poo_owlballoon_3,
    sizeof(PooOwlBalloonWork),
};

TaskDesc gTaskDescPooHoney = {
    "task_poo_honey",
    (TaskInitFunc)task_poo_honey_0,
    (TaskUpdateFunc)task_poo_honey_1,
    (TaskDrawFunc)task_poo_honey_2,
    (TaskDestroyFunc)task_poo_honey_3,
    sizeof(PooHoneyWork),
};

static const BosMapanimeFrame sPooMapanimeFrames0[4] = { { 18, 0 }, { 18, 1 }, { 18, 2 }, { 18, 3 } };

static const BosMapanimeFrame sPooMapanimeFrames1[4] = { { 18, 0 }, { 18, 1 }, { 18, 2 }, { 18, 3 } };

const BosMapanimeDef gPooMapanimeDef0 = { sPooMapanimeFrames0, 4, gPooMapanime0Tiles, 0x2080, 0x0240, 0x0400, 3 };

const BosMapanimeDef gPooMapanimeDef1 = { sPooMapanimeFrames1, 4, gPooMapanime1Tiles, 0x3880, 0x0240, 0x0400, 3 };

TaskDesc gTaskDescPooMapanime = {
    "task_poo_mapanime",
    (TaskInitFunc)task_poo_mapanime_0,
    (TaskUpdateFunc)task_poo_mapanime_1,
    task_poo_mapanime_2,
    task_poo_mapanime_3,
    sizeof(PooMapAnimeWork),
};

TaskDesc gTaskDescPooPile = {
    "task_poo_pile",
    (TaskInitFunc)task_poo_pile_0,
    (TaskUpdateFunc)task_poo_pile_1,
    (TaskDrawFunc)task_poo_pile_2,
    (TaskDestroyFunc)task_poo_pile_3,
    sizeof(PooPileWork),
};

const s32 gPooPileKindStages[6] = { 8, 0, 2, 4, 6, 7 };

TaskDesc gTaskDescPooTigerstump = {
    "task_poo_tigerstump",
    (TaskInitFunc)task_poo_tigerstump_0,
    (TaskUpdateFunc)task_poo_tigerstump_1,
    (TaskDrawFunc)task_poo_tigerstump_2,
    (TaskDestroyFunc)task_poo_tigerstump_3,
    sizeof(PooStumpWork),
};

TaskDesc gTaskDescPooPoohstump = {
    "task_poo_poohstump",
    (TaskInitFunc)task_poo_poohstump_0,
    (TaskUpdateFunc)task_poo_poohstump_1,
    (TaskDrawFunc)task_poo_poohstump_2,
    (TaskDestroyFunc)task_poo_poohstump_3,
    sizeof(PooStumpWork),
};

const PooAnimDesc gPooPigletAnimDescs[4] = {
    { gPigletStandFrontAnims, gPigletStandFrontFrames, gPigletStandFrontTiles, 0 },
    { gPigletStandBackAnims, gPigletStandBackFrames, gPigletStandBackTiles, 0 },
    { gPigletWalkFrontAnims, gPigletWalkFrontFrames, gPigletWalkFrontTiles, 0 },
    { gPigletWalkBackAnims, gPigletWalkBackFrames, gPigletWalkBackTiles, 0 },
};

const PooGfxDesc gPooPigletGfxDescs[4] = {
    { gPigletStandFrontFrames, 1 },
    { gPigletStandBackFrames, 1 },
    { gPigletWalkFrontFrames, 8 },
    { gPigletWalkBackFrames, 8 },
};

TaskDesc gTaskDescPooPiglet = {
    "task_poo_piglet",
    (TaskInitFunc)task_poo_piglet_0,
    (TaskUpdateFunc)task_poo_piglet_1,
    (TaskDrawFunc)task_poo_piglet_2,
    (TaskDestroyFunc)task_poo_piglet_3,
    sizeof(PooPigletWork),
};

TaskDesc gTaskDescPooEeyore = {
    "task_poo_eeyore",
    (TaskInitFunc)task_poo_eeyore_0,
    (TaskUpdateFunc)task_poo_eeyore_1,
    (TaskDrawFunc)task_poo_eeyore_2,
    (TaskDestroyFunc)task_poo_eeyore_3,
    sizeof(PooEeyoreWork),
};

TaskDesc gTaskDescPooOwl = {
    "task_poo_owl",
    (TaskInitFunc)task_poo_owl_0,
    (TaskUpdateFunc)task_poo_owl_1,
    (TaskDrawFunc)task_poo_owl_2,
    (TaskDestroyFunc)task_poo_owl_3,
    sizeof(PooOwlWork),
};

const PooAnimDesc gPooRabbitAnimDescs[7] = {
    { gRabbitFl00Anims, gRabbitFl00Frames, gRabbitFl00Tiles, 0 },
    { gRabbitFl00Anims, gRabbitFl00Frames, gRabbitFl00Tiles, 1 },
    { gRabbitFl00Anims, gRabbitFl00Frames, gRabbitFl00Tiles, 2 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 0 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 2 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 3 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 4 },
};

const PooGfxDesc gPooRabbitGfxDescs[2] = {
    { gRabbitFl00Frames, 14 },
    { gRabbitBl00Frames, 15 },
};

TaskDesc gTaskDescPooRabbit = {
    "task_poo_rabbit",
    (TaskInitFunc)task_poo_rabbit_0,
    (TaskUpdateFunc)task_poo_rabbit_1,
    (TaskDrawFunc)task_poo_rabbit_2,
    (TaskDestroyFunc)task_poo_rabbit_3,
    sizeof(PooRabbitWork),
};

const PooAnimDesc gPooTiggerAnimDescs[4] = {
    { gTiggerFl00Anims, gTiggerFl00Frames, gTiggerFl00Tiles, 0 },
    { gTiggerFl01Anims, gTiggerFl01Frames, gTiggerFl01Tiles, 0 },
    { gTiggerFl02Anims, gTiggerFl02Frames, gTiggerFl02Tiles, 0 },
    { gTiggerBl02Anims, gTiggerBl02Frames, gTiggerBl02Tiles, 0 },
};

const PooGfxDesc gPooTiggerGfxDescs[4] = {
    { gTiggerFl00Frames, 1 },
    { gTiggerFl01Frames, 9 },
    { gTiggerFl02Frames, 8 },
    { gTiggerBl02Frames, 8 },
};

const s32 gPooTiggerHopCorners[8] = { 428288, 232704, 411904, 240896, 428288, 249088, 444672, 240896 };

const s32 gPooTiggerHopHeights[8] = { -512, -2560, -4096, -5120, -5120, -4096, -2560, -512 };

TaskDesc gTaskDescPooTigger = {
    "task_poo_tigger",
    (TaskInitFunc)task_poo_tigger_0,
    (TaskUpdateFunc)task_poo_tiggerroo_1,
    (TaskDrawFunc)task_poo_tiggerroo_2,
    (TaskDestroyFunc)task_poo_tiggerroo_3,
    sizeof(PooTiggerWork),
};

TaskDesc gTaskDescPooTiggerroo = {
    "task_poo_tiggerroo",
    (TaskInitFunc)task_poo_tiggerroo_0,
    (TaskUpdateFunc)task_poo_tiggerroo_1,
    (TaskDrawFunc)task_poo_tiggerroo_2,
    (TaskDestroyFunc)task_poo_tiggerroo_3,
    sizeof(PooTiggerWork),
};

TaskDesc gTaskDescPooRoo = {
    "task_poo_roo",
    (TaskInitFunc)task_poo_roo_0,
    (TaskUpdateFunc)task_poo_roo_1,
    (TaskDrawFunc)task_poo_roo_2,
    (TaskDestroyFunc)task_poo_roo_3,
    sizeof(PooRooWork),
};

TaskDesc gTaskDescPooRooFootmark = {
    "task_poo_roo_footmark",
    (TaskInitFunc)task_poo_roo_footmark_0,
    (TaskUpdateFunc)task_poo_roo_footmark_1,
    (TaskDrawFunc)task_poo_roo_footmark_2,
    (TaskDestroyFunc)task_poo_roo_footmark_3,
    sizeof(PooFootmarkWork),
};

TaskDesc gTaskDescPooLeaf = {
    "task_poo_leaf",
    (TaskInitFunc)task_poo_leaf_0,
    (TaskUpdateFunc)task_poo_leaf_1,
    (TaskDrawFunc)task_poo_leaf_2,
    (TaskDestroyFunc)task_poo_leaf_3,
    sizeof(PooLeafWork),
};

TaskDesc gTaskDescPooTanpopo = {
    "task_poo_tanpopo",
    (TaskInitFunc)task_poo_tanpopo_0,
    (TaskUpdateFunc)task_poo_tanpopo_1,
    (TaskDrawFunc)task_poo_tanpopo_2,
    (TaskDestroyFunc)task_poo_tanpopo_3,
    sizeof(PooTanpopoWork),
};

TaskDesc gTaskDescPooTiBoard = {
    "task_poo_ti_board",
    (TaskInitFunc)task_poo_ti_board_0,
    (TaskUpdateFunc)task_poo_ti_board_1,
    (TaskDrawFunc)task_poo_ti_board_2,
    (TaskDestroyFunc)task_poo_ti_board_3,
    sizeof(PooBoardWork),
};

TaskDesc gTaskDescPooEeyoretail = {
    "task_poo_eeyoretail",
    (TaskInitFunc)task_poo_eeyoretail_0,
    (TaskUpdateFunc)task_poo_eeyoretail_1,
    (TaskDrawFunc)task_poo_eeyoretail_2,
    (TaskDestroyFunc)task_poo_eeyoretail_3,
    sizeof(PooEeyoreTailWork),
};

TaskDesc gTaskDescPooHoneycomb = {
    "task_poo_honeycomb",
    (TaskInitFunc)task_poo_honeycomb_0,
    (TaskUpdateFunc)task_poo_honeycomb_1,
    (TaskDrawFunc)task_poo_honeycomb_2,
    (TaskDestroyFunc)task_poo_honeycomb_3,
    sizeof(PooHoneycombWork),
};

TaskDesc gTaskDescPooVegetable = {
    "task_poo_vegetable",
    (TaskInitFunc)task_poo_vegetable_0,
    (TaskUpdateFunc)task_poo_vegetable_1,
    (TaskDrawFunc)task_poo_vegetable_2,
    (TaskDestroyFunc)task_poo_vegetable_3,
    sizeof(PooVegetableWork),
};

TaskDesc gTaskDescPooWagon = {
    "task_poo_wagon",
    (TaskInitFunc)task_poo_wagon_0,
    (TaskUpdateFunc)task_poo_wagon_1,
    (TaskDrawFunc)task_poo_wagon_2,
    (TaskDestroyFunc)task_poo_wagon_3,
    sizeof(PooWagonWork),
};

TaskDesc gTaskDescPooWagonwheel = {
    "task_poo_wagonwheel",
    (TaskInitFunc)task_poo_wagonwheel_0,
    (TaskUpdateFunc)task_poo_wagonwheel_1,
    (TaskDrawFunc)task_poo_wagonwheel_2,
    (TaskDestroyFunc)task_poo_wagonwheel_3,
    sizeof(PooWheelWork),
};

TaskDesc gTaskDescPooSpark = {
    "task_poo_spark",
    (TaskInitFunc)task_poo_spark_0,
    (TaskUpdateFunc)task_poo_spark_1,
    (TaskDrawFunc)task_poo_spark_2,
    (TaskDestroyFunc)task_poo_spark_3,
    sizeof(PooSparkWork),
};

const PooPoint gPooBeePoints[4] = { { -512, -1792 }, { -2304, 512 }, { 2304, -768 }, { 768, 1792 } };

TaskDesc gTaskDescPooBee = {
    "task_poo_bee",
    (TaskInitFunc)task_poo_bee_0,
    (TaskUpdateFunc)task_poo_bee_1,
    (TaskDrawFunc)task_poo_bee_2,
    (TaskDestroyFunc)task_poo_bee_3,
    sizeof(PooBeeWork),
};

TaskDesc gTaskDescPooBeeAfterEvent = {
    "task_poo_beeAfterEvent",
    (TaskInitFunc)task_poo_beeAfterEvent_0,
    (TaskUpdateFunc)task_poo_beeAfterEvent_1,
    (TaskDrawFunc)task_poo_beeAfterEvent_2,
    (TaskDestroyFunc)task_poo_beeAfterEvent_3,
    sizeof(PooBeeAfterEventWork),
};

const PooSpot gPooCabbageStackOffsets[18] = {
    { 0, 0, 0 },
    { -2560, -1280, 0 },
    { -5120, -2560, 0 },
    { -2560, -3840, 0 },
    { 0, -2560, 0 },
    { 2560, -1280, 0 },
    { 5120, -2560, 0 },
    { 2560, -3840, 0 },
    { 0, -5120, 0 },
    { 0, -640, -3200 },
    { -2560, -1920, -3200 },
    { 0, -3200, -3200 },
    { 2560, -1920, -3200 },
    { 0, -1280, -5888 },
    { 61440, 40960, 0 },
    { 0, 40960, 0 },
    { 61440, 0, 0 },
    { 0, 0, 0 },
};

const u16 gPooCabbageRemoveCounts[15] = { 6, 6, 6, 6, 6, 9, 9, 9, 65535, 65535, 65535, 65535, 65535, 65535, 65535 };

const u16 gPooCabbageStackPriorities[5] = { 3, 2, 1, 2, 4 };

TaskDesc gTaskDescPooCabbage = {
    "task_poo_cabbage",
    (TaskInitFunc)task_poo_cabbage_0,
    (TaskUpdateFunc)task_poo_cabbage_1,
    (TaskDrawFunc)task_poo_cabbage_2,
    (TaskDestroyFunc)task_poo_cabbage_3,
    sizeof(PooCabbageWork),
};

TaskDesc gTaskDescPooCabbageborn = {
    "task_poo_cabbageborn",
    (TaskInitFunc)task_poo_cabbageborn_0,
    (TaskUpdateFunc)task_poo_cabbageborn_1,
    (TaskDrawFunc)task_poo_cabbageborn_2,
    (TaskDestroyFunc)task_poo_cabbageborn_3,
    sizeof(PooCabbageBornWork),
};

const PooMapObjHitDesc gPooMapObjHitDescs[10] = {
    { gPooMapObjHit0Tiles, 5, gPooMapObjHit0Anims, gPooMapObjHit0Frames, gPooMapObjHit0Palette },
    { gPooMapObjHit1Tiles, 11, gPooMapObjHit1Anims, gPooMapObjHit1Frames, gPooMapObjHit1Palette },
    { gPooMapObjHit2Tiles, 24, gPooMapObjHit2Anims, gPooMapObjHit2Frames, gPooMapObjHit2Palette },
    { gPooMapObjHit3Tiles, 3, gPooMapObjHit3Anims, gPooMapObjHit3Frames, gPooMapObjHit3Palette },
    { gPooMapObjHit4Tiles, 9, gPooMapObjHit4Anims, gPooMapObjHit4Frames, gPooMapObjHit4Palette },
    { gPooMapObjHit5Tiles, 2, gPooMapObjHit5Anims, gPooMapObjHit5Frames, gPooMapObjHit5Palette },
    { gPooMapObjHit6Tiles, 6, gPooMapObjHit6Anims, gPooMapObjHit6Frames, gPooMapObjHit6Palette },
    { gPooMapObjHit7Tiles, 6, gPooMapObjHit7Anims, gPooMapObjHit7Frames, gPooMapObjHit6Palette },
    { gPooMapObjHit8Tiles, 10, gPooMapObjHit8Anims, gPooMapObjHit8Frames, gPooMapObjHit8Palette },
    { gPooMapObjHit9Tiles, 10, gPooMapObjHit9Anims, gPooMapObjHit9Frames, gPooMapObjHit8Palette },
};

TaskDesc gTaskDescPooMapobjhit = {
    "task_poo_mapobjhit",
    (TaskInitFunc)task_poo_mapobjhit_0,
    (TaskUpdateFunc)task_poo_mapobjhit_1,
    (TaskDrawFunc)task_poo_mapobjhit_2,
    (TaskDestroyFunc)task_poo_mapobjhit_3,
    sizeof(PooMapObjHitWork),
};

TaskDesc gTaskDescPooPrize = {
    "task_poo_prize",
    (TaskInitFunc)task_poo_prize_0,
    (TaskUpdateFunc)task_poo_prize_1,
    (TaskDrawFunc)task_poo_prize_2,
    (TaskDestroyFunc)task_poo_prize_3,
    sizeof(PooPrizeWork),
};

TaskDesc gTaskDescPooZzz = {
    "task_poo_zzz",
    (TaskInitFunc)task_poo_zzz_0,
    (TaskUpdateFunc)task_poo_zzz_1,
    (TaskDrawFunc)task_poo_zzz_2,
    (TaskDestroyFunc)task_poo_zzz_3,
    sizeof(PooZzzWork),
};

AnimDef gTrap01AnimDefs[5] = {
    { gTrap01Bb00Frames, gTrap01Bb00Anims, gTrap01Bb00Tiles, 0 },
    { gTrap01Ff00Frames, gTrap01Ff00Anims, gTrap01Ff00Tiles, 0 },
    { gTrap01Fl00Frames, gTrap01Fl00Anims, gTrap01Fl00Tiles, 0 },
    { gTrap01Ll00Frames, gTrap01Ll00Anims, gTrap01Ll00Tiles, 0 },
    { gTrap01Bl00Frames, gTrap01Bl00Anims, gTrap01Bl00Tiles, 0 },
};

TaskDesc gTaskDescPooButterfly = {
    "task_poo_butterfly",
    (TaskInitFunc)task_poo_butterfly_0,
    (TaskUpdateFunc)task_poo_butterfly_1,
    (TaskDrawFunc)task_poo_butterfly_2,
    (TaskDestroyFunc)task_poo_butterfly_3,
    sizeof(PooButterflyWork),
};

TaskDesc gTaskDescPooButterflyRight = {
    "task_poo_butterflyRight",
    (TaskInitFunc)task_poo_butterfly_0,
    (TaskUpdateFunc)task_poo_butterflyRight_1,
    (TaskDrawFunc)task_poo_butterflyRight_2,
    (TaskDestroyFunc)task_poo_butterfly_3,
    sizeof(PooButterflyWork),
};

TaskDesc gTaskDescPooButterflyLeft = {
    "task_poo_butterflyLeft",
    (TaskInitFunc)task_poo_butterfly_0,
    (TaskUpdateFunc)task_poo_butterflyLeft_1,
    (TaskDrawFunc)task_poo_butterflyLeft_2,
    (TaskDestroyFunc)task_poo_butterfly_3,
    sizeof(PooButterflyWork),
};

TaskDesc gTaskDescPooMapbee = {
    "task_poo_mapbee",
    (TaskInitFunc)task_poo_mapbee_0,
    (TaskUpdateFunc)task_poo_mapbee_1,
    (TaskDrawFunc)task_poo_mapbee_2,
    (TaskDestroyFunc)task_poo_mapbee_3,
    sizeof(PooMapBeeWork),
};

TaskDesc gTaskDescPooMapbeeborn = {
    "task_poo_mapbeeborn",
    (TaskInitFunc)task_poo_mapbeeborn_0,
    (TaskUpdateFunc)task_poo_mapbeeborn_1,
    (TaskDrawFunc)task_poo_mapbeeborn_2,
    (TaskDestroyFunc)task_poo_mapbeeborn_3,
    sizeof(PooMapBornWork),
};

TaskDesc gTaskDescPooMapbutterfly = {
    "task_poo_mapbutterfly",
    (TaskInitFunc)task_poo_mapbutterfly_0,
    (TaskUpdateFunc)task_poo_mapbutterfly_1,
    (TaskDrawFunc)task_poo_mapbutterfly_2,
    (TaskDestroyFunc)task_poo_mapbutterfly_3,
    sizeof(PooMapButterflyWork),
};

TaskDesc gTaskDescPooMapbutterflyborn = {
    "task_poo_mapbutterflyborn",
    (TaskInitFunc)task_poo_mapbutterflyborn_0,
    (TaskUpdateFunc)task_poo_mapbutterflyborn_1,
    (TaskDrawFunc)task_poo_mapbutterflyborn_2,
    (TaskDestroyFunc)task_poo_mapbutterflyborn_3,
    sizeof(PooMapBornWork),
};

TaskDesc gTaskDescPooRabbitAfterEvent = {
    "task_poo_rabbitAfterEvent",
    (TaskInitFunc)task_poo_rabbitAfterEvent_0,
    (TaskUpdateFunc)task_poo_rabbitAfterEvent_1,
    (TaskDrawFunc)task_poo_rabbitAfterEvent_2,
    (TaskDestroyFunc)task_poo_rabbitAfterEvent_3,
    sizeof(PooRabbitAfterEventWork),
};

TaskDesc gTaskDescPooCabbageAfterEvent = {
    "task_poo_cabbageAfterEvent",
    (TaskInitFunc)task_poo_cabbageAfterEvent_0,
    (TaskUpdateFunc)task_poo_cabbageAfterEvent_1,
    (TaskDrawFunc)task_poo_cabbageAfterEvent_2,
    (TaskDestroyFunc)task_poo_cabbageAfterEvent_3,
    sizeof(PooCabbageAfterEventWork),
};

const s32 gPooMainEventIds[6] = { 0, 1, 2, 3, 4, 5 };

