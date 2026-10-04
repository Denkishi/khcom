#include "macros.h"
#include "poo.h"
#include "background_actor_assets.h"
#include "sprites_btl.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_map.h"
#include "sprites_pooh.h"
#include "sprites_sora.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "btl_api.h"
#include "malloc.h"
#include "mode_pooh_api.h"
#include "fade.h"
#include "songs.h"
#include "player_progression.h"
#include <stdlib.h>
#include "mode_allmap_api.h"
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
#include "mode_battle_data.h"
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

void SetPoohPalette(PoohWork* w, u32 b) {
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

    if (w->palette->src != pal) {
        ReleaseObjPalette(w->palette);
        w->palette = LoadObjPalette(pal, 32);
    }
}

void SetPoohAction(PoohWork* w, u32 b) {
    sPoohAction = b;

    if (b == 0) {
        gPoohRequest = 0;
    }

    if (b >= 38 && b <= 39) {
        w->balloonTimer = 0;

        if (!IsTaskActive(w->task)) {
            w->task = TaskCreate(&w->tasks, &gTaskDescPooBalloon, &w->pos);
        }
    }

    if (b == 30 || b == 24 || b == 4 || b == 11) {
        w->actionTimer = 0;
    }

    if (b == 15) {
        w->vz = -0x130;
    }

    if (b >= 36 && b <= 37) {
        m4aSongNumStart(SONG_SND_329);
    } else if (b == 16) {
        m4aSongNumStart(SONG_SYS_PO_FALL);
    } else if (b == 39 || b == 22 || (b >= 32 && b <= 35)) {
        // fakematch
        do {
            w->angle = 0xAD;
            w->lookAngle = 0xAD;
            w->lookColumn = w->angle;
        } while (0);
    }

    if (b > 35) {
        w->angle = 0x53;
        w->lookAngle = 0x53;
        w->lookColumn = w->angle;
    }

    SetPoohPalette(w, b);
}

void task_poo_pooh_0(PoohWork* w) {
    PooShadowArgs args;

    sPooWork = w;
    w->unk_CC = 0;
    GetPooStateGauge(&gPoohGauge, &gPoohGaugeTimer);
    w->targetNode = NULL;
    w->lookTimer = 0;
    gPoohRequest = 0;
    w->callTimer = 0;
    w->callCount = 0;
    w->angle = 45;
    w->lookAngle = 45;
    w->lookColumn = w->angle;
    SetPoohDir5Right(w);
    w->speed = 0;
    w->flipped = 0;
    w->animAction = 0xFFFF;
    GetPooStatePooh(&w->pos, &sPoohAction);
    w->pos.ground = 0;
    w->targetX = w->pos.x;
    w->targetY = w->pos.y;
    gPoohPos = &w->pos;
    w->tiles = AllocObjTiles(gPoohHitBox.tileCount * 32, NULL);
    w->palette = LoadObjPalette(gPoohHitBox.palette, 32);
    AnimInit(&w->anim, NULL, NULL);
    SetPoohAction(w, sPoohAction);
    w->hideShadow = 0;
    SetPoohAnimation(w, sPoohAction);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 9, gPoohHitBox.radius, gPoohHitBox.height);
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    TaskPoolInit(&w->tasks, 10);
    args.pos = &w->pos;
    args.shadowInfo = &w->shadowInfo;
    TaskCreate(&w->tasks, &gTaskDescPooShadowdodai, &args);
    w->task = NULL;
    w->zzzTask = NULL;
    w->groundZ = GetPooGroundZ(&w->collider, &w->pos, &w->onCollider);
}

u8 HandlePoohRequest(PoohWork* w) {
    if (gPoohRequest == 1) {
        SetPoohAction(w, 16);
        w->pos.x = gPoohRequestX;
        w->pos.y = gPoohRequestY;
    } else if (gPoohRequest == 2) {
        w->pos.x = gPoohRequestX;
        w->pos.y = gPoohRequestY;
        SetPoohAction(w, 38);
    } else if (gPoohRequest == 7) {
        w->pos.x = gPoohRequestX;
        w->pos.y = gPoohRequestY;
        SetPoohAction(w, 39);
    } else if (gPoohRequest == 8) {
        w->angle = GetAngle(w->pos.x, w->pos.y, gPoohRequestX, gPoohRequestY);
        w->lookAngle = w->angle;
        w->lookColumn = w->angle;
        SetPoohAction(w, 20);
    } else if (gPoohRequest == 11) {
        w->angle = GetAngle(w->pos.x, w->pos.y, gPoohRequestX, gPoohRequestY);
        w->lookAngle = w->angle;
        w->lookColumn = w->angle;
        w->leavingWagon = 0;
        SetPoohAction(w, 21);
    } else if (gPoohRequest == 3) {
        SetPoohAction(w, 32);
    } else if (gPoohRequest == 4 || gPoohRequest == 6) {
        SetPoohAction(w, 0);
    } else if (gPoohRequest == 5) {
        SetPoohAction(w, 10);
    } else if (gPoohRequest == 9) {
        SetPoohAction(w, 12);
    } else if (gPoohRequest == 10) {
        SetPoohAction(w, 11);
    } else if (gPoohRequest == 12) {
        gPoohRequest = 0;
        return 0;
    } else {
        SetPoohAction(w, 10);
    }

    gPoohRequest = 0;
    return 1;
}

u8 CheckPoohInterrupts(PoohWork* w, PooNode* n) {
    if (ColliderIsTouchingType(&w->collider, 1) != 0) {
        if (IsPooSoraOverWagon() == 0) {
            SetPoohAction(w, 10);
            return 1;
        }
    }

    if (gPoohRequest != 0) {
        return HandlePoohRequest(w);
    }

    return 0;
}

void ChoosePoohTarget(PoohWork* w, PooNode* n) {
    if (n != NULL) {
        if (IsPooSoraCallStarting() != 0) {
            if (w->callTimer != 0 || w->targetNode == gPooSoraNode) {
                w->callCount++;

                if (w->callCount > 10) {
                    w->callTimer = 0;
                    w->callCount = 0;
                    SetPoohAction(w, 29);
                }

                return;
            }

            w->callTimer = 90;
        }

        if (w->callTimer != 0) {
            w->callTimer--;
            n = gPooSoraNode;
        }

        if (w->targetNode != n && w->lookTimer <= 59) {
            w->lookAngle = w->angle;
            w->lookColumn = w->angle;
            w->lookTarget = GetAngle(w->pos.x, w->pos.y, ((PooPos*)n->pos)->x, ((PooPos*)n->pos)->y);
            w->targetX = w->pos.x;
            w->targetY = w->pos.y;
            SetPoohAction(w, 9);
        } else {
            w->targetNode = n;
            w->lookTimer = 0;
            w->targetX = ((PooPos*)w->targetNode->pos)->x;
            w->targetY = ((PooPos*)w->targetNode->pos)->y;
            SetPoohAction(w, 3);
        }
    } else {
        w->targetX = w->pos.x;
        w->targetY = w->pos.y;
        SetPoohAction(w, 23);
    }
}

void ApplyPoohFrameOffset(PoohWork* w, const PooSpot* b, u16 c) {
    u16 f;
    s32 v;
    s32 i;

    f = AnimGetFrame(&w->anim) + 1;

    if (w->collider.colliding == 0) {
        i = w->dirIndex * c + f;
        v = b[i].x;

        if (w->flipped != 0) {
            v = -v;
        }

        w->pos.x += v;
        v = b[i].y;
        w->pos.y += v;
    }

    w->pos.z += b[w->dirIndex * c + f].z;
}

void ApplyPooh04FrameOffset(PoohWork* w) {
    ApplyPoohFrameOffset(w, sPooh04FrameOffsets, 11);
}

void ApplyPooh04aFrameOffset(PoohWork* w) {
    ApplyPoohFrameOffset(w, sPooh04aFrameOffsets, 0x10);
}

s32 GetPoohStumpIndex(PoohWork* w) {
    PooPoint t[4];
    u32 i;

    memcpy(t, sPoohStumpCircle, sizeof(t));

    for (i = 0; i < 4; i++) {
        if (w->collider.platformX == t[i].x && w->collider.platformY == t[i].y) {
            break;
        }
    }

    return i;
}

void ResetPoohStumpCount(PoohWork* w) {
    w->stumpCount = 0;
    w->stumpIndex = GetPoohStumpIndex(w);
}

u32 NextPoohStumpIndex(u32 a) {
    a++;

    if (a > 3) {
        a = 0;
    }

    return a;
}

void UpdatePoohStumpCircle(PoohWork* w) {
    s32 t;

    t = GetPoohStumpIndex(w);

    if (t == NextPoohStumpIndex(w->stumpIndex)) {
        w->stumpIndex = t;
        w->stumpCount++;

        if (w->stumpCount > 3) {
            if (IsPooEventDone(1) == 0) {
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
        ResetPoohStumpCount(w);
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

void MovePooh(PoohWork* w, s32 b, u8 c) {
    w->speed += 6;

    if (w->speed > b) {
        w->speed = b;
    }

    if (c != 0) {
        w->lookAngle = w->angle = GetAngle(w->pos.x, w->pos.y, w->targetX, w->targetY);
        w->lookColumn = w->angle;
    }

    w->pos.x += gSineTable[w->angle] * w->speed >> 8;
    w->pos.y += -gSineTable[w->angle + 0x40] * w->speed >> 8;
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

void UpdatePoohAction(PoohWork* w, PooNode* n) {
    u16 a0;
    u16 a1;
    u16 a2;
    u16 v;
    u16 c;
    s32 b;

    switch (sPoohAction) {
    case 3:
        if (AnimGetGfxIndex(&w->anim) == 8 && gPoohPos->y > 0x1BD00 && (GetKeysPressed() & A_BUTTON) != 0) {
            v = 128;

            if (func_080D1738() != 0) {
                v = 2;
            }

            if (GetRandom() % v == 0) {
                SetPoohAction(w, 17);
            }

            break;
        }

        b = 0x4C;

        if (IsPooSoraCalling() != 0 && w->targetNode == n && n == gPooSoraNode) {
            b = 152;
            w->speed = 152;
        } else if (w->speed > 82) {
            b = w->speed - 6;
        }

        MovePooh(w, b, 1);

        if (CheckPoohInterrupts(w, n) != 0) {
            w->speed = 0;
        } else {
            ChoosePoohTarget(w, n);
        }

        break;
    case 10:
        if (w->collider.colliding != 0) {
            if (ColliderIsTouchingType(&w->collider, 1) != 0) {
                break;
            }

            if (IsPooSoraCallStarting() == 0) {
                break;
            }

            w->pos.x += w->collider.pushX;
            w->pos.y += w->collider.pushY;
            w->targetNode = NULL;
            ChoosePoohTarget(w, n);
            break;
        }

        if (GetPooManhattanDistance(&w->pos, &gPooActor.pos) > 0x1B00) {
            SetPoohAction(w, 0);
        }

        break;
    case 12:
        a0 = w->lookAngle;
        w->lookTarget = GetAngle(w->pos.x, w->pos.y, 0x8DE00, 0x45C00);
        ApproachAngle(&a0, w->lookTarget, 4);
        w->lookAngle = a0;
        w->lookTimer++;

        if (AreAllPooBeesOut() == 0) {
            break;
        }

        SetPoohAction(w, 15);
        w->angle = 64;
        w->lookAngle = 64;
        w->lookColumn = w->angle;
        break;
    case 15:
        w->pos.z += w->vz;
        w->vz += 71;

        if (w->pos.z < 0) {
            break;
        }

        w->pos.z = 0;
        SetPoohAction(w, 5);
        w->speed = 228;
        break;
    case 5:
        w->targetX = 0x87F00;
        w->targetY = 0x4B700;
        MovePooh(w, 456, 1);

        if (IsWithinPoohRadius(w->targetX >> 8, w->targetY >> 8, w->pos.x >> 8, w->pos.y >> 8) == 0) {
            break;
        }

        SetPoohAction(w, 6);
        break;
    case 6:
        w->targetX = 0x75D00;
        w->targetY = 0x49E00;
        MovePooh(w, 456, 1);

        if (IsWithinPoohRadius(w->targetX >> 8, w->targetY >> 8, w->pos.x >> 8, w->pos.y >> 8) == 0) {
            break;
        }

        SetPoohAction(w, 14);
        BtlMapStartShake();
        m4aSongNumStart(SONG_SND_372);
        break;
    case 0:
        if (w->pos.z < 0) {
            SetPoohAction(w, 1);
            break;
        }

        ChoosePoohTarget(w, n);

        if (sPoohAction != 0) {
            break;
        }

        if (w->targetNode == NULL) {
            break;
        }

        c = GetPooNodeWeight(w->targetNode);

        if (c <= 1) {
            break;
        }

        c >>= 1;
        SetPooNodeWeight(w->targetNode, c);
        break;
    case 29:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 30);
        break;
    case 30:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        if (w->actionTimer <= 1) {
            w->actionTimer++;
            AnimReset(&w->anim);
            break;
        }

        if (AnimIsFrameEnding(&w->anim) == 0) {
            break;
        }

        if (AnimGetFrame(&w->anim) != 0) {
            break;
        }

        SetPoohAction(w, 31);
        break;
    case 31:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 9);
        break;
    case 9:
        if (w->lookTimer <= 59) {
            a1 = w->lookAngle;
            w->lookTarget = GetAngle(w->pos.x, w->pos.y, ((s32*)n->pos)[0], ((s32*)n->pos)[1]);
            ApproachAngle(&a1, w->lookTarget, 4);
            w->lookAngle = a1;
            w->lookTimer++;
        } else {
            ChoosePoohTarget(w, n);
        }

        break;
    case 16:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        if (w->pos.x == 0x4A700 && w->pos.y == 0x28E00 && IsPooEventDone(5) == 0) {
            SetPoohAction(w, 37);
            TaskCreate(&w->tasks, &gTaskDescPooRoo, &w->pos);
            break;
        }

        SetPoohAction(w, 36);
        break;
    case 37:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 38);
        w->pos.z -= 0x1700;
        StartPooCameraFollowPooh();
        break;
    case 36:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 38);
        break;
    case 38:
        if (w->balloonTimer <= 59) {
            w->pos.z -= 204;
        } else if (w->balloonTimer <= 79) {
            w->pos.z -= 204;
        } else {
            w->pos.z += 204;
        }

        if (w->balloonTimer > 60) {
            w->pos.x += 128;
            w->pos.y += 64;
        }

        w->balloonTimer++;

        if (w->balloonTimer > 80 && w->pos.z >= -0x800 && IsTaskActive(w->task) != 0) {
            TaskKill(&w->tasks, w->task);
            TaskCreate(&w->tasks, &gTaskDescPooFreeballoon, &w->pos);
            gPoohRequest = 0;
        }

        if (w->pos.z < 0) {
            break;
        }

        w->pos.z = 0;

        if (ColliderIsTouchingType(&w->collider, 1) != 0) {
            SetPoohAction(w, 0);
            break;
        }

        if (gPoohRequest == 0) {
            SetPoohAction(w, 0);
            break;
        }

        HandlePoohRequest(w);
        break;
    case 39:
        w->pos.z -= 204;

        if (w->pos.z > -0xD500) {
            break;
        }

        if (IsTaskActive(w->task) != 0) {
            TaskKill(&w->tasks, w->task);
        }

        SetPoohAction(w, 22);
        break;
    case 22:
        if (w->pos.z < -0x1000) {
            w->pos.z += 204;
            break;
        }

        if (IsPooEventDone(3) == 0) {
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
        if (AnimIsFinished(&w->anim) != 0) {
            if (w->actionTimer > 40) {
                SetPoohAction(w, 18);
                ApplyPooh04aFrameOffset(w);
                w->pos.z = 0;
            }

            w->actionTimer++;
            break;
        }

        if (AnimIsFrameEnding(&w->anim) != 0) {
            ApplyPooh04FrameOffset(w);
        }

        w->actionTimer = 0;
        break;
    case 18:
        if (AnimIsFinished(&w->anim) != 0) {
            SetPoohAction(w, 0);
            break;
        }

        if (AnimIsFrameEnding(&w->anim) == 0) {
            break;
        }

        ApplyPooh04aFrameOffset(w);
        break;
    case 21:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        if (w->dirIndex == 0) {
            if (w->flipped != 0) {
                w->angle = 19;
            } else {
                w->angle = 224;
            }
        } else {
            if (w->flipped != 0) {
                w->angle = 83;
            } else {
                w->angle = 147;
            }
        }

        w->lookAngle = w->angle;
        w->lookColumn = w->angle;
        w->hopAngle = w->angle;
        SetPoohAction(w, 2);
        w->vz = 0;
        w->pos.z = -0xD00;

        if (w->flipped == 0) {
            w->pos.x -= 0x900;
        } else {
            w->pos.x += 0x900;
        }

        if (w->leavingWagon == 0) {
            ClampToPooWagonArea((u32*)&w->pos.x, (u32*)&w->pos.y, 1);
            break;
        }

        while ((u8)IsInPooWagonAreaForPooh(&w->pos) != 0) {
            w->pos.x += gSineTable[w->angle] * 2;
            w->pos.y -= gSineTable[w->angle + 0x40] * 2;
        }

        break;
    case 2:
        w->pos.z += w->vz;
        w->vz += 17;

        if (w->pos.z < 0) {
            break;
        }

        w->pos.z = 0;

        if (w->leavingWagon == 0) {
            SetPoohAction(w, 13);
            break;
        }

        SetPoohAction(w, 0);
        gPoohRequest = 0;
        break;
    case 13:
        if (IsPooSoraCallStarting() == 0) {
            break;
        }

        if ((u8)IsInPooWagonArea(&gPooActor.pos) != 0) {
            break;
        }

        w->angle = w->hopAngle + 128;
        w->lookAngle = w->angle;
        w->lookColumn = w->angle;
        SetPoohAction(w, 21);
        w->leavingWagon = 1;
        break;
    case 20:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 8);
        ResetPoohStumpCount(w);
        w->pos.z -= 0xE00;
        w->lookAngle = w->angle;
        w->lookColumn = w->angle;

        if (w->flipped == 0) {
            w->pos.x -= 0x900;
        } else {
            w->pos.x += 0x900;
        }

        break;
    case 8:
        w->onCollider = 1;

        if (IsPooSoraCallStarting() == 0) {
            break;
        }

        if (IsPoohNearScreenEdge() != 0) {
            break;
        }

        SetPoohAction(w, 7);
        break;
    case 11:
        if (w->actionTimer <= 179) {
            a2 = w->lookAngle;
            w->lookTarget = GetAngle(w->pos.x, w->pos.y, 0x8DE00, 0x45C00);
            ApproachAngle(&a2, w->lookTarget, 4);
            w->lookAngle = a2;
            w->actionTimer++;
        } else {
            w->angle += 128;
            w->lookAngle = w->angle;
            w->lookColumn = w->angle;
            SetPoohAction(w, 4);
        }

        break;
    case 4:
        if (w->actionTimer > 119) {
            SetPoohAction(w, 0);
            break;
        }

        w->actionTimer++;
        MovePooh(w, 76, 0);
        break;
    case 7:
        if (w->onCollider != 0) {
            w->targetX = gPooActor.pos.x;
            w->targetY = gPooActor.pos.y;
            MovePooh(w, 76, 1);
            break;
        }

        w->targetX = gPooActor.pos.x;
        w->targetY = gPooActor.pos.y;
        w->angle = GetAngle(w->pos.x, w->pos.y, w->targetX, w->targetY);
        w->vz = -0x130;
        w->speed = 237;
        SetPoohAction(w, 19);
        break;
    case 19:
        if (AnimIsFinished(&w->anim) != 0 && w->onCollider != 0 && w->pos.z < -0x100) {
            SetPoohAction(w, 8);
            UpdatePoohStumpCircle(w);
            break;
        }

        if (AnimGetFrame(&w->anim) == 2 && w->anim.timer == 0) {
            m4aSongNumStart(SONG_SND_960);
        }

        if ((AnimGetFrame(&w->anim) > 1 && AnimGetFrame(&w->anim) <= 4) ||
            (AnimGetFrame(&w->anim) > 4 && w->onCollider == 0 && w->pos.z < w->groundZ)) {
            w->pos.x += gSineTable[w->angle] * w->speed >> 8;
            w->pos.y += -gSineTable[w->angle + 0x40] * w->speed >> 8;
        }

        if (AnimGetFrame(&w->anim) <= 1) {
            break;
        }
    case 1:
        w->pos.z += w->vz;
        w->vz += 17;

        if (w->pos.z >= w->groundZ) {
            w->pos.z = w->groundZ;
        }

        if (AnimIsFinished(&w->anim) != 0) {
            SetPoohAction(w, 0);
        }

        break;
    case 23:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 24);
        break;
    case 24:
        if (w->actionTimer <= 119) {
            w->actionTimer++;

            if (IsPooSoraCallStarting() == 0) {
                break;
            }

            if (IsPoohNearScreenEdge() != 0) {
                break;
            }

            if (gPoohGauge != 0) {
                SetPoohAction(w, 28);
            }
        } else {
            SetPoohAction(w, 25);
        }

        break;
    case 25:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 26);
        w->sleepTimer = gPoohGaugeTimer * 1800 / 1851;
        break;
    case 26:
        if (IsPooSoraCallStarting() != 0 && IsPoohNearScreenEdge() == 0 && gPoohGauge != 0) {
            SetPoohAction(w, 27);

            if (IsTaskActive(w->zzzTask) == 0) {
                break;
            }

            TaskKill(&w->tasks, w->zzzTask);
            break;
        }

        if (IsTaskActive(w->zzzTask) == 0) {
            w->zzzTask = TaskCreate(&w->tasks, &gTaskDescPooZzz, &w->flipped);
        }

        if (gPoohGauge == 0) {
            w->sleepTimer++;

            if (w->sleepTimer > 1800) {
                gPoohGauge++;
                gPoohGaugeTimer = 1851;
                w->sleepTimer = 0;
            }

            if (gPoohGauge > 3) {
                gPoohGauge = 3;
            }
        }

        break;
    case 27:
        if (AnimIsFinished(&w->anim) != 0) {
            SetPoohAction(w, 28);
        }

        break;
    case 28:
        if (AnimIsFinished(&w->anim) != 0) {
            SetPoohAction(w, 0);
        }

        break;
    case 32:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        if (gPoohGauge == 1) {
            SetPoohAction(w, 33);
        } else if (gPoohGauge == 2) {
            SetPoohAction(w, 34);
        } else {
            SetPoohAction(w, 35);
        }

        break;
    case 33:
    case 34:
    case 35:
        if (AnimIsFinished(&w->anim) == 0) {
            break;
        }

        SetPoohAction(w, 28);
        w->pos.x -= 0x400;
        w->pos.y += 0x300;
        break;
    }
}

void UpdatePoohGauge(PoohWork* w) {
    if (sPoohAction == 3) {
        if (gPoohGauge != 0) {
            gPoohGaugeTimer--;
        }

        if (gPoohGaugeTimer == 0) {
            if (gPoohGauge == 0) {
                SetPoohAction(w, 0x17);
            } else {
                gPoohGauge--;

                if (gPoohGauge == 0) {
                    SetPoohAction(w, 0x17);
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

    if (IsRectOutsideScreen(x, y, gPoohHitBox.height, 0, gPoohHitBox.radius, gPoohHitBox.radius) != 0) {
        return 1;
    }

    return 0;
}

u8 task_poo_pooh_1(PoohWork* w) {
    PooNode* n;

    w->groundZ = GetPooGroundZ(&w->collider, &w->pos, &w->onCollider);

    if (IsPoohNearScreenEdge() != 0) {
        n = NULL;
    } else {
        n = FindPoohTargetNode();
    }

    w->hideShadow = 0;
    UpdatePoohAction(w, n);
    UpdatePoohGauge(w);
    SetPoohAnimation(w, sPoohAction);
    w->gfx = AnimUpdate(&w->anim);

    if (sPoohAction == 3 || sPoohAction == 7) {
        if (w->anim.timer == 0) {
            switch (AnimGetFrame(&w->anim)) {
            case 9:
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                break;
            case 3:
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                break;
            }
        }
    }

    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_pooh_2(PoohWork* w) {
    s16 x;
    s16 y;
    s32 f;
    u16 p;

    x = (w->pos.x >> 8) - gPooScrollX;
    y = (w->pos.y >> 8) + (w->pos.z >> 8) - gPooScrollY;

    if (w->flipped != 0) {
        f = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    } else {
        f = SPRITE_PRIORITY(2);
    }

    if (sPoohAction == 20 && w->dirIndex == 1) {
        if (AnimGetFrame(&w->anim) <= 4) {
            p = -0x1003 - ((gPoohRequestY - 0x500) >> 8) * 4;
            w->shadowInfo.z = 0;
        } else {
            p = -0x1005 - ((gPoohRequestY - 0x500) >> 8) * 4;
            w->shadowInfo.priority = 0;
        }
    } else if (IsPoohOnWagon() != 0) {
        p = GetPooWagonPriority() - 4;
        w->shadowInfo.priority = p + 1;
        w->shadowInfo.z = 0;
    } else if ((u8)GetPooWagonSide(gPoohPos->x, gPoohPos->y) != 0) {
        if (sPoohAction == 21 && w->dirIndex == 1 && w->leavingWagon != 0) {
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

        w->shadowInfo.priority = p + 1;
        w->shadowInfo.z = 0;
    } else if (w->onCollider != 0) {
        p = -0x1008 - (w->collider.platformY >> 8) * 4;

        if (w->pos.y >= gPooActor.pos.y) {
            p -= 2;
        } else {
            p += 2;
        }

        if (w->collider.penetration <= w->collider.radius || w->collider.other->radius == 0x400) {
            if (w->collider.platformZ != 0) {
                w->shadowInfo.priority = 0;
            } else {
                w->shadowInfo.priority = p + 1;
            }

            w->shadowInfo.z = 0;
        } else {
            w->shadowInfo.z = w->collider.platformZ;
            w->shadowInfo.priority = p + 1;
        }
    } else {
        p = -0x1004 - (w->pos.y >> 8) * 4;
        w->shadowInfo.z = 0;

        if (w->shadowInfo.z != w->pos.ground) {
            w->shadowInfo.priority = 0;
        } else {
            w->shadowInfo.priority = 0xFFF0;
        }
    }

    if (w->hideShadow != 0) {
        w->shadowInfo.priority = 0;
    }

    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, f, p);
    TaskPoolDraw(&w->tasks);
}

void task_poo_pooh_3(PoohWork* w) {
    if (sPoohAction == 22) {
        sPoohAction = 0;
        w->pos.z = 0;
        w->pos.y += 0x2000;
    } else if (sPoohAction == 14) {
        sPoohAction = 0;
        w->pos.x = 0x7F700;
        w->pos.y = 0x47E00;
        w->pos.z = 0;
    }

    SetPooStatePooh(&w->pos, sPoohAction);
    SetPooStateGauge(gPoohGauge, gPoohGaugeTimer);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
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
        if (sPooWork->leavingWagon != 0) {
            return 0;
        }

        return 1;
    }

    if (sPoohAction != 21) {
        return 0;
    }

    w = sPooWork;

    if (w->leavingWagon != 0) {
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

    if (sPooCameraFrozen != 0) {
        return;
    }

    if (sPooCameraFollowPooh != 0) {
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

void task_poo_map_0(PooMapWork* w) {
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
    w->mapWidth = gPooMapBgDesc.mapWidth;
    w->mapHeight = gPooMapBgDesc.mapHeight;
    TaskPoolInit(&w->tasks, 178);
    CreatePooMapobjhitTasks(&w->tasks, CreatePooSpawnTasks(&w->tasks, 0));
    CreatePooPileTasks(&w->tasks);
    TaskCreate(&w->tasks, &gTaskDescPooMapanime, NULL);
    LoadBgTiles(3, gPooMapBgDesc.tiles, gPooMapBgDesc.tilesSize);
    LoadBgTiles(2, gPooMapBgDesc.tiles2, gPooMapBgDesc.tilesSize2);
    LoadBgPalette(3, gPooMapBgDesc.palette, gPooMapBgDesc.paletteSize);
    SetBgMapBlocks(3, gPooBg3MapBlocks, w->mapWidth, w->mapHeight);
    RedrawBgMapAt(3, gPooScrollX, gPooScrollY);
    func_080CA35C();
    SetBgMapBlocks(1, gPooBg1MapBlocks, w->mapWidth, w->mapHeight);
    RedrawBgMapAt(1, gPooScrollX, gPooScrollY);
    SetBgMapBlocks(2, gPooBg2MapBlocks, w->mapWidth, w->mapHeight);
    RedrawBgMapAt(2, gPooScrollX, gPooScrollY);
    BtlMapResetShake();
}

u8 task_poo_map_1(PooMapWork* w) {
    UpdatePooCameraCenter();
    ScrollPooCamera(w);
    ScrollBgMapTo(3, gPooScrollX, gPooScrollY);
    ScrollBgMapTo(1, gPooScrollX, gPooScrollY);
    ScrollBgMapTo(2, gPooScrollX, gPooScrollY);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_map_2(PooMapWork* w) {
    TaskPoolDraw(&w->tasks);
}

void task_poo_map_3(PooMapWork* w) {
    TaskPoolDestroy(&w->tasks);
}

void ScrollPooCamera(PooMapWork* w) {
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

    if (IsPooPosBlocked(&p->pos) != 0) {
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

        if (IsPooPosBlocked(&t) == 0) {
            *ox = s * m >> 8;
            *oy = c * m >> 8;
            return 1;
        } else {
            a = p->angle - 0x40;
            s = gSineTable[a];
            c = -gSineTable[a + 0x40];
            t.x = s * 4 + x;
            t.y = c * 4 + y;

            if (IsPooPosBlocked(&t) == 0) {
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

    if (GetPooWallSlide(a, x, y, &sPooMoveAdjustX, &sPooMoveAdjustY) != 0) {
        a->pos.x = x + sPooMoveAdjustX;
        a->pos.y = y + sPooMoveAdjustY;
    }

    sx = (x >> 8) - gPooScrollX;
    sy = (y >> 8) - gPooScrollY;

    if (GetPooScreenOverflow(sx, sy, 48, 0, 18, 18, &sPooMoveAdjustX, &sPooMoveAdjustY) == 0) {
        sx = (a->pos.x >> 8) - gPooScrollX;
        sy = (a->pos.y >> 8) - gPooScrollY;

        if (GetPooScreenOverflow(sx, sy, 48, 0, 18, 18, &sPooMoveAdjustX, &sPooMoveAdjustY) != 0) {
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
    if (IsPooExitTile(p) != 0) {
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

u8 ApplyPooSoraPushOut(PooSoraWork* w, PooPos* p) {
    if (w->collider.colliding != 0 && ColliderIsTouchingType(&w->collider, 5) == 0 && ColliderIsTouchingType(&w->collider, 3) == 0 && ColliderIsTouchingType(&w->collider, 5) == 0 && ColliderIsTouchingType(&w->collider, 11) == 0) {
        if (IsPooSoraOverWagon() != 0) {
            p->x += w->collider.pushX;
            p->y += w->collider.pushY;
            SnapToPooWagonLine((u32*)&p->x, (u32*)&p->y, 1);
        } else {
            p->x += w->collider.pushX;
            p->y += w->collider.pushY;
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

s32 GetPooSoraGroundZ(PooSoraWork* w) {
    PooPos* p;
    s32 v;

    p = &gPooActor.pos;

    if ((w->collider.standFlags & COLLIDER_STAND_OVER_PLATFORM) != 0) {
        if (p->ground < w->collider.platformZ) {
            v = p->ground;
        } else {
            v = w->collider.platformZ;
        }

        w->onCollider = 1;
    } else {
        w->onCollider = 0;
        v = p->ground;
    }

    return v;
}

void SetPooSoraAnimation(PooSoraWork* w, s32 b, u16 c) {
    const PooAnimDesc* e;
    s32 d;

    switch (gPooActor.angle) {
    case 0x2D:
        d = 4;
        w->flags |= POO_SORA_FLAG_FLIP_X;
        break;
    case 0x40:
        d = 3;
        w->flags |= POO_SORA_FLAG_FLIP_X;
        break;
    case 0x53:
        d = 2;
        w->flags |= POO_SORA_FLAG_FLIP_X;
        break;
    case 0x80:
        d = 1;
        w->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0xAD:
        d = 2;
        w->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0xC0:
        d = 3;
        w->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0xD3:
        d = 4;
        w->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    case 0x00:
    default:
        d = 0;
        w->flags &= ~POO_SORA_FLAG_FLIP_X;
        break;
    }

    if (w->animAction == b) {
        c |= 4;
    }

    w->animAction = b;
    e = &gPooSoraAnimDescs[b][d];
    AnimChangeWithTables(&w->anim, (u8)e->animId, c, e->unk_04, e->unk_00);
    SetObjTileSource(w->tiles, e->tiles);
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

void task_poo_sora_0(PooSoraWork* w) {
    PooActor* a = &gPooActor;

    gPooSoraCollider = &w->collider;
    gPooSoraNode = &w->node;
    sPooSoraWork = w;
    w->tiles = AllocObjTiles(0xA00, NULL);
    w->palette = LoadObjPalette(gSoraPalette, 32);
    a->height = 16;
    w->onCollider = 0;
    w->timer = 0;
    w->flags = 0;
    w->animAction = 12;
    a->unk_32 = 0;
    a->kind = 0;
    GetPooStatePos2(&a->pos);
    a->angle = 0xAD;
    a->pos.ground = 0;
    a->speed = 0;
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    AnimInit(&w->anim, NULL, NULL);
    SetPooSoraAnimation(w, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    w->sounds = gPooSoraSounds;
    TaskPoolInit(&w->tasks, 2);
    gFieldState = EwramAlloc(sizeof(FieldState));
    TaskCreate(&w->tasks, &gTaskDescFldShadow, a);
    AddPooNode(&w->node, 1, a);
    ColliderInit(&w->collider, 1, 18, 48);
    ColliderSetPosition(&w->collider, a->pos.x, a->pos.y, a->pos.z);
}

u8 PooSoraUpdateJump(PooSoraWork* w, Task* t) {
    PooActor* a = &gPooActor;
    PooPos p;
    s32 z;
    s32 sx;
    s32 sy;
    u16 k;
    u16 v;

    z = GetPooSoraGroundZ(w);
    sx = a->pos.x;
    sy = a->pos.y;
    UpdatePooActorAngle(a);

    switch (w->state) {
    case 7:
        if (w->timer == 0) {
            SetPooSoraAnimation(w, 10, 0);
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;

        if (AnimGetFrame(&w->anim) > 3) {
            a->pos.z += w->vz;
            w->vz += 66;

            if (a->pos.z > z) {
                a->pos.z = z;
                w->vz = 0;
            }
        } else {
            w->vz = 0;
        }

        a->speed -= 38;

        if (a->speed < 0) {
            a->speed = 0;
        }

        switch (AnimGetFrame(&w->anim)) {
        case 3:
        case 4:
            SetPooSoraAttackPoint(a);
            break;
        }

        if (AnimIsFinished(&w->anim) != 0) {
            if (w->vz < 0) {
                w->state = 3;
            } else {
                w->state = 4;
            }
        } else {
            w->timer++;
        }

        break;
    case 2:
        if (w->timer == 0) {
            SetPooSoraAnimation(w, 3, 0);
            a->speed >>= 1;
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;

        if (w->timer > 3) {
            if (GetRandom() % 2 != 0) {
                m4aSongNumStart(SONG_SYS_SR_I_VO00);
            } else {
                m4aSongNumStart(SONG_SYS_SR_I_VO01);
            }

            w->state = 3;
            w->vz = -0x533;
            a->speed <<= 1;
            w->timer = 0;
        } else {
            w->timer++;
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

        if (w->vz > -0x200) {
            SetPooSoraAnimation(w, 5, 0);
        } else {
            SetPooSoraAnimation(w, 4, 0);
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;
        a->pos.z += w->vz;
        w->vz += 66;

        if (w->vz < 0) {
            if ((GetKeysHeld() & B_BUTTON) == 0) {
                w->vz += 64;
            }
        }

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            w->timer = 0;
            w->state = 7;
        } else if (w->vz > 0) {
            w->timer = 0;
            w->state = 4;
        } else {
            w->timer++;
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

        if (w->vz < 0x200) {
            SetPooSoraAnimation(w, 5, 0);
        } else {
            SetPooSoraAnimation(w, 6, 0);
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;
        a->pos.z += w->vz;
        w->vz += 66;

        if ((GetKeysPressed() & A_BUTTON) != 0) {
            w->timer = 0;
            w->state = 7;
        } else if (a->pos.z > z) {
            a->pos.z = z;
            w->vz = 0;

            if (w->state != 5) {
                w->state = 5;
                w->timer = 0;
            }
        }

        break;
    case 5:
        if (w->timer == 0) {
            SetPooSoraAnimation(w, 7, 0);
            m4aSongNumStart(w->sounds[3]);
        }

        a->speed = 0;
        k = GetKeysPressed() & B_BUTTON;

        if (k != 0) {
            w->timer = 0;
            w->state = 2;
        } else if (w->timer > 6) {
            w->state = 0;
            w->timer = 0;
            SetTaskUpdate(t, (TaskUpdateFunc)task_poo_sora_1);
        } else {
            w->timer++;
        }

        break;
    }

    if (ApplyPooSoraPushOut(w, &a->pos) != 0) {
        a->speed = a->speed * 230 >> 8;
    }

    ConstrainPooActorMove(a, sx, sy);

    if ((u8)IsInPooWagonArea(&a->pos) != 0) {
        if (a->pos.z > -0xA00) {
            p.x = sx;
            p.y = sy;

            if ((u8)IsInPooWagonArea(&p) == 0) {
                a->pos.x = sx;
                a->pos.y = sy;
                a->speed = 0;
            } else if (w->vz >= 0) {
                a->speed = 0;
                v = (-a->pos.z >> 8) + 1;
                SnapToPooWagonLine((u32*)&a->pos, (u32*)&a->pos.y, v);
            }
        }
    }

    ColliderSetPosition(&w->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    w->gfx = AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 PooSoraUpdateAttack(PooSoraWork* w, Task* t) {
    PooActor* a = &gPooActor;
    s32 sx;
    s32 sy;

    sx = a->pos.x;
    sy = a->pos.y;

    if (w->state == 6) {
        if (w->timer == 0) {
            SetPooSoraAnimation(w, 9, 0);
            a->speed = 0;
            m4aSongNumStart(SONG_SYS_SR_AT_VO00);
        }

        if (w->anim.timer == 0) {
            switch (a->angle) {
            case 0xAD:
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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
                switch (AnimGetFrame(&w->anim)) {
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

        if (w->timer > 14) {
            SetPooSoraAttackPoint(a);
        }

        if (AnimIsFinished(&w->anim) != 0) {
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

            SetPooSoraAnimation(w, 0, 0);
            w->state = 0;
            SetTaskUpdate(t, (TaskUpdateFunc)task_poo_sora_1);
        } else {
            w->timer++;
        }
    }

    ApplyPooSoraPushOut(w, &a->pos);
    ConstrainPooActorMove(a, sx, sy);

    if ((u8)IsInPooWagonArea(&a->pos) != 0) {
        a->pos.x = sx;
        a->pos.y = sy;
        a->speed = 0;
    }

    ColliderSetPosition(&w->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    w->gfx = AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 PooSoraUpdateCall(PooSoraWork* w, Task* t) {
    PooActor* a = &gPooActor;
    s32 x;
    s32 y;
    u16 keys;

    x = a->pos.x;
    y = a->pos.y;

    if (w->state == 8) {
        if (w->timer == 0) {
            SetPooSoraAnimation(w, 8, 1);
            a->speed = 0;
        }

        if (w->timer > 29) {
            keys = GetKeysHeld() & R_BUTTON;

            if (keys != 0) {
                w->timer = 0;
            } else {
                w->timer = 0;
                w->state = 0;
                SetTaskUpdate(t, (TaskUpdateFunc)task_poo_sora_1);
            }
        } else {
            w->timer++;
        }
    }

    ApplyPooSoraPushOut(w, &a->pos);
    ConstrainPooActorMove(a, x, y);

    if ((u8)IsInPooWagonArea(&a->pos) != 0) {
        a->pos.x = x;
        a->pos.y = y;
        a->speed = 0;
    }

    ColliderSetPosition(&w->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    w->gfx = AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

u8 task_poo_sora_1(PooSoraWork* w, Task* t) {
    PooActor* a = &gPooActor;
    s32 z;
    s32 sx;
    s32 sy;
    u16 v;

    z = GetPooSoraGroundZ(w);
    sx = a->pos.x;
    sy = a->pos.y;

    if (w->state <= 1) {
        UpdatePooActorAngle(a);

        if ((GetKeysHeld() & DPAD_ANY) != 0) {
            a->speed += 128;
            SetPooSoraAnimation(w, 2, 1);

            if (a->speed > 0x266) {
                a->speed = 0x266;
            }

            if (w->anim.timer == 0) {
                switch (w->anim.frame) {
                case 3:
                    m4aSongNumStart(w->sounds[0]);
                    break;
                case 7:
                    m4aSongNumStart(w->sounds[1]);
                    break;
                }
            }
        } else {
            SetPooSoraAnimation(w, 0, 1);
            a->speed -= 128;

            if (a->speed < 0) {
                a->speed = 0;
            }
        }

        a->pos.x += gSineTable[a->angle] * a->speed >> 8;
        a->pos.y += -gSineTable[a->angle + 0x40] * a->speed >> 8;

        if ((GetKeysPressed() & B_BUTTON) != 0) {
            w->timer = 0;
            w->state = 2;
            SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateJump);
            m4aSongNumStart(w->sounds[2]);
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
                w->timer = 0;
                w->state = 6;
                SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateAttack);
            }
        } else if ((GetKeysPressed() & R_BUTTON) != 0) {
            w->timer = 0;
            w->state = 8;
            SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateCall);
            a->angle = GetPooAngleToPooh(&a->pos);
        }
    } else if (AnimIsFinished(&w->anim) != 0) {
        w->state = 0;
    }

    if (CheckPooSoraExit(&a->pos) != 0) {
        a->speed = 0;
    }

    if (ApplyPooSoraPushOut(w, &a->pos) != 0) {
        a->speed = a->speed * 230 >> 8;
    }

    ConstrainPooActorMove(a, sx, sy);

    if ((u8)IsInPooWagonArea(&a->pos) != 0) {
        a->pos.x = sx;
        a->pos.y = sy;
        a->speed = 0;
    }

    if (z != a->pos.z) {
        a->speed >>= 2;
        w->vz = 0;
        w->timer = 0;
        w->state = 4;
        SetTaskUpdate(t, (TaskUpdateFunc)PooSoraUpdateJump);
    }

    ColliderSetPosition(&w->collider, a->pos.x, a->pos.y, a->pos.z);
    SetPooCameraFocus(a->pos.x, a->pos.y + a->pos.z);
    w->gfx = AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_sora_2(PooSoraWork* w) {
    PooActor* a = &gPooActor;
    s32 prio;
    s32 c;
    s32 ac;
    s16 x;
    s16 y;

    c = w->flags & POO_SORA_FLAG_FLIP_X;
    prio = SPRITE_PRIORITY(2);

    if (c != 0) {
        prio = SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
    }

    ac = w->onCollider;

    if (ac != 0) {
        sPooSoraPriority = -0x1008 - (w->collider.platformY >> 8) * 4;

        if (w->collider.penetration <= w->collider.radius || w->collider.other->radius == 0x400) {
            if (w->collider.platformZ != 0) {
                a->shadowPriority = 0;
            } else {
                a->shadowPriority = sPooSoraPriority + 1;
            }

            a->shadowZ = 0;
        } else {
            a->shadowZ = w->collider.platformZ;
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
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, prio, sPooSoraPriority - 1);
    TaskPoolDraw(&w->tasks);
}

void task_poo_sora_3(PooSoraWork* w) {
    SetPooStatePos2(&gPooActor.pos);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    EwramFree(gFieldState);
    RemovePooNode(&w->node);
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
        if (IsPooEventDone(i) == 0) {
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

        if (IsPoohOffScreen() == 0) {
            SetPooFlag(3);

            if (AreAllPooEventsDone() != 0) {
                if (IsPooFlagSet(1) != 0) {
#ifdef VERSION_EU
                    ExitPoohMode(0x91);
#else
                    ExitPoohMode(0x93);
#endif
                } else if (IsPooFlagSet(0) == 0) {
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
            } else if (IsPooFlagSet(0) == 0) {
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

void task_poo_trap_0(PooTrapWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y;
    w->z = 0;
    w->tiles = LoadObjTiles(gUnk_0972BD8C, 0x100);
    w->palette = LoadObjPalette(gUnk_09849AB8, 0x20);
    w->gfx = gUnk_0972BD78;
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    w->colliderActive = 0;
}

u8 task_poo_trap_1(PooTrapWork* w) {
    if (w->colliderActive != 0) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequestX = w->x;
            gPoohRequestY = w->y;
            gPoohRequest = 1;
        }
    }

    return 1;
}

void task_poo_trap_2(PooTrapWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (x < -16 || x > 256 || y < -16 || y > 176) {
        if (w->colliderActive != 0) {
            ColliderUnregister(&w->collider);
            w->colliderActive = 0;
        }
    } else {
        if (w->colliderActive == 0) {
            ColliderInit(&w->collider, 10, 8, 16);
            w->colliderActive = 1;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0xFFEF);
    }
}

void task_poo_trap_3(PooTrapWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);

    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
    }
}

void task_poo_pitAndButterfly_0(PooTrapWork* w, PooPos* p) {
    task_poo_trap_0(w, p);
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescPooButterfly, &w->x);
    AddPooNode(&w->node, 0xE10, &w->x);
}

u8 task_poo_pitAndButterfly_1(PooTrapWork* w) {
    task_poo_trap_1(w);

    if (w->colliderActive != 0) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            SetPooNodeWeight(&w->node, 0);
        }
    }

    return 1;
}

void task_poo_pitAndButterfly_2(PooTrapWork* w) {
    task_poo_trap_2(w);

    if (w->colliderActive != 0) {
        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_pitAndButterfly_3(PooTrapWork* w) {
    task_poo_trap_3(w);
    TaskPoolDestroy(&w->tasks);
    RemovePooNode(&w->node);
}

void task_poo_balloon_0(PooBalloonObjWork* w, PooPos* p) {
    w->pos = p;

    if (p->x == 0x3FD00 && p->y == 0x21B00) {
        w->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF5E38, 3), gUnk_0974B4D8);
        w->palette = LoadObjPalette(gUnk_09849C98, 0x20);
        AnimInit(&w->anim, gUnk_09EF5E44, gUnk_09EF5E38);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    } else {
        w->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gTrap0006Frames, 4), gTrap0006Tiles);
        w->palette = LoadObjPalette(gUnk_09849B78, 0x20);
        AnimInit(&w->anim, gTrap0006Anims, gTrap0006Frames);
        AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    }

    w->gfx = AnimGetGfx(&w->anim);
}

u8 task_poo_balloon_1(void* w) {
    return 1;
}

void task_poo_balloon_2(PooBalloonObjWork* w) {
    s16 x;
    s16 y;

    x = (w->pos->x >> 8) - gPooScrollX;
    y = (w->pos->y >> 8) + (w->pos->z >> 8) - gPooScrollY;

    if (x >= -16 && x <= 256 && y >= -16 && y <= 176) {
        w->gfx = AnimUpdate(&w->anim);
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->pos->y >> 8) * 4);
    }
}

void task_poo_balloon_3(PooBalloonObjWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
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

void task_poo_shadowdodai_0(PooShadowWork* w, PooShadowArgs* a) {
    w->pos = a->pos;
    w->shadowInfo = a->shadowInfo;
    w->x = w->pos->x;
    w->y = w->pos->y;
    w->tiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    AnimInit(&w->anim, gUnk_09EE1384, gUnk_09EE1380);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimUpdate(&w->anim);
}

u8 task_poo_shadowdodai_1(PooShadowWork* w) {
    w->x = w->pos->x;
    w->y = w->pos->y;
    return 1;
}

void task_poo_shadowdodai_2(PooShadowWork* w) {
    s32 s;
    ObjAffine* aff;
    s32 h;
    s16 x;
    s16 y;

    if (w->shadowInfo->priority != 0) {
        h = w->shadowInfo->z;

        if (w->pos->z >= h) {
            s = 0xA6;
        } else {
            s = 0xA6 - (h - w->pos->z) / 128;

            if (s <= 0x18) {
                s = 0x19;
            }
        }

        aff = AllocObjAffine(0, s, s, 0);
        x = (w->x >> 8) - gPooScrollX;
        y = (w->y >> 8) + (h >> 8) - gPooScrollY;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, aff, SPRITE_PRIORITY(2), w->shadowInfo->priority);
    }
}

void task_poo_shadowdodai_3(PooShadowWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void task_poo_shadowscale_0(PooScaleWork* w, PooShadowArgs* a) {
    w->pos = a->pos;
    w->x = w->pos->x;
    w->y = w->pos->y;
    w->scale = a->scale;
    w->tiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    AnimInit(&w->anim, gUnk_09EE1384, gUnk_09EE1380);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimUpdate(&w->anim);
}

u8 task_poo_shadowscale_1(PooScaleWork* w) {
    w->x = w->pos->x;
    w->y = w->pos->y;
    return 1;
}

void task_poo_shadowscale_2(PooScaleWork* w) {
    s32 s;
    ObjAffine* affine;
    u16 x;
    u16 y;

    if (w->pos->z >= 0) {
        s = w->scale;
    } else {
        s = w->scale + w->pos->z / 128;

        if (s <= 0x18) {
            s = 0x19;
        }
    }

    affine = AllocObjAffine(0, s, s, 0);
    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, affine, SPRITE_PRIORITY(2), 0xFFF0);
}

void task_poo_shadowscale_3(PooScaleWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void CreatePooShadowscaleTask(void* pool, void* a, s32 b) {
    PooShadowArgs args;

    args.pos = a;
    args.scale = b;
    TaskCreate(pool, &gTaskDescPooShadowscale, &args);
}

void task_poo_freeballoon_0(PooFreeBalloonWork* w, PooPos* p) {
    w->pos2 = *p;
    w->pos4 = *p;
    w->pos3 = *p;
    w->pos5 = *p;
    w->pos = p;
    w->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gTrap0004Frames, 4), gTrap0004Tiles);
    w->palette = LoadObjPalette(gTrap0004Palette, 0x20);
    AnimInit(&w->anim, gTrap0004Anims, gTrap0004Frames);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->tiles2 = AllocObjTiles(GetMaxSpriteTileBytes(gTrap0005Frames, 4), gTrap0005Tiles);
    w->palette2 = LoadObjPalette(gUnk_09849B58, 0x20);
    AnimInit(&w->anim2, gTrap0005Anims, gTrap0005Frames);
    AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    w->gfx2 = AnimGetGfx(&w->anim2);
    w->timer = 0;
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

u8 task_poo_freeballoon_1(PooFreeBalloonWork* w) {
    u16 t;

    w->timer++;

    if (w->timer > 5) {
        t = w->timer - 5;
        w->pos4.x = w->pos5.x - t * 256;
        w->pos4.y = w->pos5.y - ((t * t) << 8) / 32;
    } else {
        w->pos4 = *w->pos;
        w->pos5 = *w->pos;
    }

    w->pos2.x = w->pos3.x + w->timer * 256;
    w->pos2.y = w->pos3.y - ((w->timer * w->timer) << 8) / 32;
    w->x2 = (w->pos4.x >> 8) - gPooScrollX;
    w->y2 = (w->pos4.y >> 8) + (w->pos4.z >> 8) - gPooScrollY;
    w->x = (w->pos2.x >> 8) - gPooScrollX;
    w->y = (w->pos2.y >> 8) + (w->pos2.z >> 8) - gPooScrollY;

    if (IsPooNearScreen(w->x2, w->y2) != 0) {
        w->gfx2 = AnimUpdate(&w->anim2);
    } else {
        w->gfx2 = NULL;
    }

    if (IsPooNearScreen(w->x, w->y) != 0) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        w->gfx = NULL;
    }

    if (w->gfx == NULL && w->gfx2 == NULL) {
        return 0;
    }

    return 1;
}

void task_poo_freeballoon_2(PooFreeBalloonWork* w) {
    if (w->gfx2 != NULL) {
        DrawSprite(w->x2, w->y2, w->gfx2, w->tiles2, w->palette2, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->pos4.y >> 8) * 4);
    }

    if (w->gfx != NULL) {
        DrawSprite(w->x, w->y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->pos2.y >> 8) * 4);
    }
}

void task_poo_freeballoon_3(PooFreeBalloonWork* w) {
    ReleaseObjTiles(w->tiles2);
    ReleaseObjPalette(w->palette2);
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
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

void task_poo_gauge_0(PooGaugeWork* w) {
    w->blinkTimer = 0;
    w->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF5B2C, 4), gUnk_097356F4);
    w->palette = LoadObjPalette(gPoohGaugePalette, 0x20);
    w->paletteSrc = gPoohGaugePalette;
    w->gfx = gUnk_09EF5B2C[GetPooGaugeFrame(w->blinkTimer)];
    w->warning = 0;
}

u8 task_poo_gauge_1(PooGaugeWork* w) {
    w->blinkTimer++;
    w->gfx = gUnk_09EF5B2C[GetPooGaugeFrame(w->blinkTimer)];

    if (gPoohGauge <= 1 && gPoohGaugeTimer <= 0x1CD) {
        w->warning = 1;
    } else {
        w->warning = 0;
    }

    if (w->warning != 0) {
        if (w->paletteSrc != gUnk_09849BB8) {
            LoadObjPaletteBank(w->palette->index, gUnk_09849BB8);
            w->paletteSrc = gUnk_09849BB8;
        }
    }

    if (w->warning == 0) {
        if (w->paletteSrc != gPoohGaugePalette) {
            LoadObjPaletteBank(w->palette->index, gPoohGaugePalette);
            w->paletteSrc = gPoohGaugePalette;
        }
    }

    return 1;
}

void task_poo_gauge_2(PooGaugeWork* w) {
    DrawSprite(0xDC, 0x18, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(1), 0);
}

void task_poo_gauge_3(PooGaugeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void task_poo_trapballoon_0(PooBalloonWork* w, PooPos* p) {
    w->pos = *p;
    w->pos.z = 0;
    w->pos.ground = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gTrap0006Frames, 4);
    w->palette = NULL;
    AnimInit(&w->anim, gTrap0006Anims, gTrap0006Frames);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 3);
    w->task = TaskCreate(&w->tasks, &gTaskDescPooShadow, &w->pos);
    w->freeBalloonTask = NULL;
    w->angle = GetRandom();
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
}

u8 task_poo_trapballoon_1(PooBalloonWork* w) {
    PooPos t;

    if (w->palette == NULL) {
        return 1;
    }

    if (IsTaskActive(w->freeBalloonTask) != 0) {
        return 1;
    }

    if (IsTaskActive(w->task) == 0 && IsTaskActive(w->freeBalloonTask) == 0) {
        return 0;
    }

    if (ColliderIsTouchingType(&w->collider, 9) != 0 && IsPoohWalkingToTarget() != 0) {
        gPoohRequestX = w->pos.x;
        gPoohRequestY = w->pos.y;
        gPoohRequest = 2;
        SetPooNodeWeight(&w->node, 0);
        return 0;
    }

    if (gPooAttackActive == 0) {
        if (ColliderIsTouchingType(&w->collider, 9) == 0) {
            return 1;
        }

        if (IsPoohWalkingToTarget() != 0) {
            return 1;
        }
    }

    if (PooAttackHitsCollider(&w->collider) == 0) {
        return 1;
    }

    t = w->pos;
    t.z -= 0x1000;
    TaskCreate(&w->tasks, &gTaskDescPooSpark, &t);
    SetPooNodeWeight(&w->node, 0);
    ColliderSetDisabled(&w->collider, 1);
    TaskKill(&w->tasks, w->task);
    w->pos.x -= 0x800;
    w->pos.y += 0x1000;
    w->freeBalloonTask = TaskCreate(&w->tasks, &gTaskDescPooFreeballoon, &w->pos);
    m4aSongNumStart(SONG_SYS_PO_BLOON);
    return 1;
}

void task_poo_trapballoon_2(PooBalloonWork* w) {
    s32 d;
    s16 x;
    s16 y;

    if (IsTaskActive(w->freeBalloonTask) != 0) {
        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    } else {
        w->gfx = AnimUpdate(&w->anim);
        w->angle += 2;
        d = gSineTable[w->angle & 0xFF] * 2;
        x = ((w->pos.x - 0x800) >> 8) - gPooScrollX;
        d += 0x1200;
        y = ((w->pos.y + d) >> 8) + (w->pos.z >> 8) - gPooScrollY;

        if (IsRectOutsideScreen(x, y, 64, 8, 24, 24) != 0) {
            if (w->palette != NULL) {
                ReleaseObjTiles(w->tiles);
                ReleaseObjPalette(w->palette);
                w->palette = NULL;
                ColliderUnregister(&w->collider);
                RemovePooNode(&w->node);
            }
        } else {
            if (w->palette == NULL) {
                w->tiles = AllocObjTiles(w->tileBytes, gTrap0006Tiles);
                w->palette = LoadObjPalette(gUnk_09849B78, 0x20);
                ColliderInit(&w->collider, 10, 8, 16);
                AddPooNode(&w->node, 0x400, &w->pos);
            }

            DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->pos.y >> 8) * 4);
            TaskPoolUpdate(&w->tasks);
            TaskPoolDraw(&w->tasks);
        }
    }
}

void task_poo_trapballoon_3(PooBalloonWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
        RemovePooNode(&w->node);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_owlballoon_0(PooOwlBalloonWork* w, PooPos* p) {
    w->pos = *p;
    w->pos.z = 0;
    w->pos.ground = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gUnk_09EF5E38, 3);
    w->palette = NULL;
    AnimInit(&w->anim, gUnk_09EF5E44, gUnk_09EF5E38);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 2);
    w->task = TaskCreate(&w->tasks, &gTaskDescPooShadow, &w->pos);
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    AddPooNode(&w->node, 0x240, &w->pos);
}

u8 task_poo_owlballoon_1(PooOwlBalloonWork* w) {
    if (w->palette != NULL && ColliderIsTouchingType(&w->collider, 9) != 0 && IsPoohWalkingToTarget() != 0) {
        gPoohRequestX = w->pos.x;
        gPoohRequestY = w->pos.y;
        gPoohRequest = 7;
        SetPooNodeWeight(&w->node, 0);
        m4aSongNumStart(SONG_SND_385);
        return 0;
    }

    return 1;
}

void task_poo_owlballoon_2(PooOwlBalloonWork* w) {
    s16 x;
    s16 y;

    w->gfx = AnimUpdate(&w->anim);
    x = ((w->pos.x - 0x800) >> 8) - gPooScrollX;
    y = ((w->pos.y + 0x1000) >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 64, 8, 24, 24) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gUnk_0974B4D8);
            w->palette = LoadObjPalette(gUnk_09849C98, 0x20);
            ColliderInit(&w->collider, 10, 8, 16);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1003 - (w->pos.y >> 8) * 4);
        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_owlballoon_3(PooOwlBalloonWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
    RemovePooNode(&w->node);
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

void task_poo_honey_0(PooHoneyWork* w, PooPos* p) {
    w->pos.x = p->x;
    w->pos.y = p->y;
    w->pos.z = 0;
    w->palette = NULL;
    w->tileBytes = GetMaxSpriteTileBytes(gPoohHoneyFrames, 14);
    AnimInit(&w->anim, gPoohHoneyAnims, gPoohHoneyFrames);
    AnimStart(&w->anim, 3, ANIM_FLAG_LOOP);
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    w->pos2 = w->pos;
    w->pos2.x += 0xB00;
    w->pos2.y -= 0xA00;
    w->minPos = w->pos2;
    w->minPos.x -= 0x100;
    w->minPos.y -= 0x100;
    w->maxPos = w->pos2;
    w->maxPos.x += 0x100;
    w->maxPos.y += 0x100;
    TaskPoolInit(&w->tasks, 1);
    CreatePooShadowscaleTask(&w->tasks, &w->pos, 0xCC);
    w->state = 0;
    w->timer = 0;
}

u8 task_poo_honey_1(PooHoneyWork* w) {
    switch (w->state) {
    case 0:
        if (w->minPos.x <= gPoohPos->x && gPoohPos->x <= w->maxPos.x && w->minPos.y <= gPoohPos->y && gPoohPos->y <= w->maxPos.y) {
            gPoohRequest = 3;
            SetPooNodeWeight(&w->node, 0);
            w->state++;
        }

        break;
    case 1:
        if (GetPoohHoneyAnim() <= 2) {
            AnimStart(&w->anim, GetPoohHoneyAnim(), 0);
            AnimUpdate(&w->anim);
            w->state++;
        }

        break;
    case 2:
        AnimUpdate(&w->anim);

        if (AnimIsFinished(&w->anim) != 0) {
            return 0;
        }

        switch (AnimGetGfxIndex(&w->anim)) {
        case 1:
            w->pos = *gPoohPos;
            w->pos.x -= 0xB00;
            w->pos.y += 0xA00;
            w->pos.z = 0;
            w->pos3 = w->pos;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            w->pos.x = w->pos3.x + 0x200;
            w->pos.y = w->pos3.y;
            w->pos.z = w->pos3.z - 0x200;
            break;
        case 7:
            w->pos.x = w->pos3.x - 0x200;
            w->pos.y = w->pos3.y - 0x500;
            w->pos.z = w->pos3.z - 0xB00;
            break;
        case 8:
            gPoohGauge = 3;
            gPoohGaugeTimer = 0x73B;
            w->pos.x = w->pos3.x + 0xA00;
            w->pos.y = w->pos3.y - 0x900;
            w->pos.z = w->pos3.z - 0x1000;
            break;
        case 9:
            w->pos.x = w->pos3.x + 0x200;
            w->pos.y = w->pos3.y;
            w->pos.z = w->pos3.z - 0x300;
            break;
        case 10:
            w->pos.x = w->pos3.x + 0x200;
            w->pos.y = w->pos3.y;
            w->pos.z = w->pos3.z - 0x100;
            break;
        case 11:
        case 12:
        case 13:
            w->pos.x = w->pos3.x;
            w->pos.y = w->pos3.y;
            w->pos.z = w->pos3.z;
            w->timer++;
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

void task_poo_honey_2(PooHoneyWork* w) {
    s16 x;
    s16 y;

    if (w->timer > 29 && (w->timer & 1) != 0) {
        return;
    }

    x = (w->pos.x >> 8) - gPooScrollX;
    y = (w->pos.y >> 8) + (w->pos.z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 8, 16, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
            RemovePooNode(&w->node);
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gPoohHoneyTiles);
            w->palette = LoadObjPalette(gPoohGaugePalette, 0x20);
            ColliderInit(&w->collider, 10, 8, 16);
            AddPooNode(&w->node, 0x1FA4, &w->pos2);
        }

        DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->pos.y >> 8) * 4);
        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_honey_3(PooHoneyWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
        RemovePooNode(&w->node);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_mapanime_0(PooMapAnimeWork* w) {
    BosMapanimeInit(&w->anims[0], &gPooMapanimeDef0);
    BosMapanimeInit(&w->anims[1], &gPooMapanimeDef1);
}

u8 task_poo_mapanime_1(PooMapAnimeWork* w) {
    u8 r;
    u32 i;

    r = 0;

    for (i = 0; i < 2; i++) {
        r = BosMapanimeUpdate(&w->anims[i], w->anims[i].def, r);
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

void task_poo_pile_0(PooPileWork* w, PooPileArgs* a) {
    w->pos.x = a->x;
    w->pos.y = a->y;
    w->pos.z = 0;
    w->palette = NULL;
    AnimInit(&w->anim, gUnk_09EF5C8C, gUnk_09EF5C6C);

    if (a->stage == 8) {
        w->stage = GetRandomPooPileStage();
    } else {
        w->stage = a->stage;
    }

    AnimStart(&w->anim, w->stage, 0);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    w->colliderActive = 0;
    TaskPoolInit(&w->tasks, 1);
    w->task = NULL;
}

u8 task_poo_pile_1(PooPileWork* w) {
    PooPos t;

    if (w->stage == 7) {
        return 1;
    }

    if (w->colliderActive == 0) {
        return 1;
    }

    if (ColliderIsTouchingType(&w->collider, 9) != 0) {
        gPoohRequest = 5;
    }

    if (gPooAttackActive == 0) {
        return 1;
    }

    if (PooAttackHitsCollider(&w->collider) == 0) {
        return 1;
    }

    if (AnimIsFinished(&w->anim) == 0) {
        return 1;
    }

    t = w->pos;
    t.z -= (u16)GetPooPileHeight(w->stage) * 256;

    if (IsTaskActive(w->task) != 0) {
        TaskKill(&w->tasks, w->task);
    }

    w->task = TaskCreate(&w->tasks, &gTaskDescPooSpark, &t);
    w->stage = NextPooPileStage(w->stage);
    AnimStart(&w->anim, w->stage, 0);
    m4aSongNumStart(SONG_SYS_PO_WOOD);

    if (w->stage == 7) {
        ColliderUnregister(&w->collider);
        w->colliderActive = 0;
        RemovePooNode(&w->node);
    } else {
        ColliderSetHeight(&w->collider, GetPooPileHeight(w->stage));
    }

    return 1;
}

void task_poo_pile_2(PooPileWork* w) {
    u16 z;
    s16 x;
    s16 y;

    x = (w->pos.x >> 8) - gPooScrollX;
    y = (w->pos.y >> 8) - gPooScrollY;

    if (x < -16 || x > 256 || y < -36 || y > 196) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }

        if (w->colliderActive != 0) {
            ColliderUnregister(&w->collider);
            RemovePooNode(&w->node);
            w->colliderActive = 0;
        }

        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    } else {
        w->gfx = AnimUpdate(&w->anim);

        if (w->palette == NULL) {
            w->tiles = LoadObjTiles(gUnk_09742CC2, 0x300);
            w->palette = LoadObjPalette(gUnk_09849BF8, 0x20);
        }

        if (w->stage != 7) {
            z = -0x1004 - (w->pos.y >> 8) * 4;

            if (w->colliderActive == 0) {
                ColliderInit(&w->collider, 7, 4, GetPooPileHeight(w->stage));
                AddPooNode(&w->node, 0x240, &w->pos);
                w->colliderActive = 1;
            }
        } else {
            z = 0xFFF1;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), z);
        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_pile_3(PooPileWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
        RemovePooNode(&w->node);
    }

    TaskPoolDestroy(&w->tasks);
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

void task_poo_tigerstump_0(PooStumpWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y + 0x800;
    w->unk_2C = 0;
    w->palette = NULL;
    w->gfx = gUnk_097561D4;
    ColliderSetPosition(&w->collider, w->x, w->y, 0);
}

u8 task_poo_tigerstump_1(PooStumpWork* w) {
    if (w->palette != NULL) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_tigerstump_2(PooStumpWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = ((w->y - 0x800) >> 8) - gPooScrollY;

    if (x < -96 || x > 336 || y < -64 || y > 224) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = LoadObjTiles(gUnk_097561E8, 0x400);
            w->palette = LoadObjPalette(gUnk_09849D38, 0x20);
            ColliderInit(&w->collider, 7, 15, 24);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - ((w->y - 0x700) >> 8) * 4);
    }
}

void task_poo_tigerstump_3(PooStumpWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }
}

void task_poo_poohstump_0(PooStumpWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y;
    w->unk_2C = 0;
    w->palette = NULL;
    w->gfx = gUnk_09755F34;
    ColliderSetPosition(&w->collider, w->x, w->y, 0);
}

u8 task_poo_poohstump_1(PooStumpWork* w) {
    if (w->palette != NULL) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequestX = w->x;
            gPoohRequestY = w->y;
            gPoohRequest = 8;
        }
    }

    return 1;
}

void task_poo_poohstump_2(PooStumpWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (x < -80 || x > 320 || y < -24 || y > 184) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = LoadObjTiles(gUnk_09755F54, 0x280);
            w->palette = LoadObjPalette(gUnk_09849D38, 0x20);
            ColliderInit(&w->collider, 7, 7, 14);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - ((w->y - 0x500) >> 8) * 4);
    }
}

void task_poo_poohstump_3(PooStumpWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }
}

void SetPooPigletAnimation(PooPigletWork* w, s32 b, u16 c) {
    if (w->animIndex != b) {
        w->animIndex = b;
        AnimChangeWithTables(&w->anim, gPooPigletAnimDescs[b].animId, c, gPooPigletAnimDescs[b].unk_00, gPooPigletAnimDescs[b].unk_04);
        SetObjTileSource(w->tiles, gPooPigletAnimDescs[b].tiles);
    }
}

void task_poo_piglet_0(PooPigletWork* w) {
    u16 m;
    u16 n;
    u8 i;

    w->x = 0x2A500;
    w->y = 0x21100;
    w->z = 0;
    w->state = 0;
    w->timer = 0;
    w->palette = NULL;
    m = 0;

    for (i = 0; i < 4; i++) {
        n = GetMaxSpriteTileBytes(gPooPigletGfxDescs[i].gfxTable, gPooPigletGfxDescs[i].gfxCount);

        if (m < n) {
            m = n;
        }
    }

    w->tiles = AllocObjTiles(m, NULL);
    AnimInit(&w->anim, NULL, NULL);
    w->animIndex = 4;
    SetPooPigletAnimation(w, 0, 1);
    w->flipped = 0;
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescPooShadow, &w->x);

    if (IsPooEventDone(0) != 0) {
        w->interactionId = AddPoohInteraction(&w->collider, 0x36);
        SetPoohInteractionEnabled(w->interactionId, 0);
    }
}

u8 task_poo_piglet_1(PooPigletWork* w) {
    if (w->palette != NULL && w->collider.colliding != 0) {
        if (ColliderIsTouchingType(&w->collider, 9) == 0) {
            return 1;
        }

        if (IsPooEventDone(0) != 0) {
            return 1;
        }

        gPoohRequestX = w->x;
        gPoohRequestY = w->y;
        gPoohRequest = 4;
#ifdef VERSION_EU
        ExitPoohMode(134);
#else
        ExitPoohMode(136);
#endif
        SetPooEventDone(0);
        SetJiminyFlag(78);
    }

    switch (w->state) {
    case 0:
        SetPooPigletAnimation(w, 0, 1);
        w->flipped = 0;

        if (w->timer > 209) {
            w->state = 1;
            w->speed = 0;
        } else {
            w->timer++;
        }

        break;
    case 1:
        SetPooPigletAnimation(w, 3, 1);
        w->flipped = 1;
        w->speed += 0x600;

        if (w->speed > 128) {
            w->speed = 128;
        }

        w->x += gSineTable[0x20] * w->speed >> 8;
        w->y += -gSineTable[0x60] * w->speed >> 8;

        if (w->x > 0x2C8FF) {
            w->state = 2;
            w->timer = 0;
        }

        break;
    case 2:
        SetPooPigletAnimation(w, 1, 1);
        w->flipped = 1;

        if (w->timer > 39) {
            w->state = 3;
            w->timer = 0;
        } else {
            w->timer++;
        }

        break;
    case 3:
        SetPooPigletAnimation(w, 0, 1);
        w->flipped = 1;

        if (w->timer > 29) {
            w->state = 4;
            w->timer = 0;
        } else {
            w->timer++;
        }

        break;
    case 4:
        SetPooPigletAnimation(w, 1, 1);
        w->flipped = 1;

        if (w->timer > 29) {
            w->state = 5;
            w->timer = 0;
        } else {
            w->timer++;
        }

        break;
    case 5:
        SetPooPigletAnimation(w, 0, 1);
        w->flipped = 1;

        if (w->timer <= 59) {
            w->timer++;
        } else {
            w->state = 6;
            w->speed = 0;
        }

        break;
    case 6:
        SetPooPigletAnimation(w, 2, 1);
        w->flipped = 0;
        w->speed += 0x600;

        if (w->speed > 128) {
            w->speed = 128;
        }

        w->x += gSineTable[0xA0] * w->speed >> 8;
        w->y += -gSineTable[0xE0] * w->speed >> 8;

        if (w->x <= 0x2A500) {
            w->x = 0x2A500;
            w->y = 0x21100;
            w->state = 0;
            w->timer = 0;
        }

        break;
    default:
        break;
    }

    w->gfx = AnimUpdate(&w->anim);
    return 1;
}

void task_poo_piglet_2(PooPigletWork* w) {
    u16 pr;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 8, 8, 8) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            ColliderUnregister(&w->collider);
            SetPoohInteractionEnabled(w->interactionId, 0);
            w->palette = NULL;
        }
    } else {
        TaskPoolUpdate(&w->tasks);

        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gUnk_09849C18, 0x20);

            if (IsPooEventDone(0) != 0) {
                ColliderInit(&w->collider, 10, 4, 16);
            } else {
                ColliderInit(&w->collider, 10, 16, 16);
            }

            SetPoohInteractionEnabled(w->interactionId, 1);
        }

        ColliderSetPosition(&w->collider, w->x, w->y, w->z);
        pr = w->flipped != 0 ? 0x801 : 0x800;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, pr, -0x1004 - (w->y >> 8) * 4);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_piglet_3(PooPigletWork* w) {
    ReleaseObjTiles(w->tiles);

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_eeyore_0(PooEeyoreWork* w) {
    w->x = 0x82700;
    w->y = 0x47E00;
    w->z = 0;
    w->unk_30 = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gEeyoreFl00Frames, 0x10);
    w->tiles = NULL;
    w->palette = NULL;

    if (IsPooEventDone(2) != 0) {
        w->animId = 0;
    } else {
        w->animId = 4;
    }

    AnimInit(&w->anim, gEeyoreFl00Anims, gEeyoreFl00Frames);
    AnimStart(&w->anim, w->animId, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescPooShadow, &w->x);
    ColliderInit(&w->collider, 10, 16, 16);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    w->colliderActive = 1;

    if (IsPooEventDone(2) == 0) {
        w->interactionId = AddPoohInteraction(&w->collider, 0x38);
    } else {
        w->interactionId = AddPoohInteraction(&w->collider, 0x39);
    }

    SetPoohInteractionEnabled(w->interactionId, 1);
    w->moveTimer = 0;
}

u8 task_poo_eeyore_1(PooEeyoreWork* w) {
    if (w->colliderActive != 0) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequest = 5;
        }
    }

    if (IsPooEeyoreTailLanded() != 0 && w->animId == 4) {
        w->animId = 5;
        AnimStart(&w->anim, 5, ANIM_FLAG_LOOP);
        w->moveTimer = 180;
    }

    if (w->moveTimer != 0) {
        ApproachValue((u32*)&w->x, 0x80B00, w->moveTimer);
        ApproachValue((u32*)&w->y, 0x48C00, w->moveTimer);
        SetPooCameraFocus(w->x, w->y + w->z);
        w->moveTimer--;

        if (w->moveTimer == 0) {
#ifdef VERSION_EU
            ExitPoohMode(0x8A);
#else
            ExitPoohMode(0x8C);
#endif
            SetPooEventDone(2);
            SetJiminyFlag(0x51);
            w->animId = 1;
            AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
        }
    }

    return 1;
}

void task_poo_eeyore_2(PooEeyoreWork* w) {
    u8* p;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 10, 24, 24) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ReleaseObjTiles(w->tiles);
        }

        p = &w->colliderActive;

        if (*p != 0) {
            ColliderUnregister(&w->collider);
            SetPoohInteractionEnabled(w->interactionId, 0);
            *p = 0;
        }
    } else {
        p = &w->colliderActive;

        if (*p == 0) {
            ColliderInit(&w->collider, 10, 16, 16);
            SetPoohInteractionEnabled(w->interactionId, 1);
            *p = 1;
        }

        ColliderSetPosition(&w->collider, w->x, w->y, w->z);
        w->gfx = AnimUpdate(&w->anim);

        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gEeyorePalette, 0x20);
            w->tiles = AllocObjTiles(w->tileBytes, gEeyoreFl00Tiles);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);
        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_eeyore_3(PooEeyoreWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_owl_0(PooOwlWork* w) {
    w->pos.x = 0x41500;
    w->pos.y = 0x20700;
    w->pos.z = -0x3000;
    w->pos.ground = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gOwlFl00Frames, 18);
    w->palette = NULL;
    w->gfx = gOwlFl00Frame0;
    AnimInit(&w->anim, gOwlFl00Anims, gOwlFl00Frames);
    w->flying = 0;
    w->descending = 0;
    sPooOwlBalloonPos.x = 0x3FD00;
    sPooOwlBalloonPos.y = 0x21B00;
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescPooOwlballoon, &sPooOwlBalloonPos);
}

u8 task_poo_owl_1(PooOwlWork* w) {
    if (IsPoohOnOwlBalloon() != 0) {
        SetPooCameraFocus(gPoohPos->x, gPoohPos->y + gPoohPos->z);

        if (gPoohPos->z <= -0x3800) {
            FreezePooCamera();
        }

        if (IsPoohOffScreen() != 0) {
            if (w->flying == 0) {
                w->flying = 1;
                AnimStart(&w->anim, 1, 0);
                w->flyTimer = 60;
                m4aSongNumStart(SONG_SND_351);
            }

            if (AnimGetFrame(&w->anim) > 3) {
                if (w->flyTimer != 0) {
                    ApproachValueHalfSteps(&w->pos.z, -0x9000, w->flyTimer);
                    w->flyTimer--;
                    w->pos.x -= 204;
                } else {
                    w->pos.z -= 0x100;
                }
            }

            w->gfx = AnimUpdate(&w->anim);
        }
    }

    if (IsPoohDescendingWithOwl() != 0) {
        if (w->descending == 0) {
            w->descending = 1;
            AnimStart(&w->anim, 4, ANIM_FLAG_LOOP);
        }

        if (AnimGetFrame(&w->anim) == 0 && w->anim.timer == 0) {
            m4aSongNumStart(SONG_EV_HUKUROUJUMP);
        }

        w->pos = *gPoohPos;
        w->gfx = AnimUpdate(&w->anim);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_owl_2(PooOwlWork* w) {
    s16 x;
    s16 y;

    TaskPoolDraw(&w->tasks);
    x = (w->pos.x >> 8) - gPooScrollX;
    y = (w->pos.y >> 8) + (w->pos.z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 24, 8, 8, 8) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gOwlFl00Tiles);
            w->palette = LoadObjPalette(gOwlPalette, 0x20);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - ((w->pos.y + w->pos.z) >> 8) * 4);
    }
}

void task_poo_owl_3(PooOwlWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    TaskPoolDestroy(&w->tasks);
}

void SetPooRabbitAnimation(PooRabbitWork* w, s32 b, u16 c) {
    if (w->animIndex != b) {
        w->animIndex = b;
        AnimChangeWithTables(&w->anim, gPooRabbitAnimDescs[b].animId, c, gPooRabbitAnimDescs[b].unk_00, gPooRabbitAnimDescs[b].unk_04);
        SetObjTileSource(w->tiles, gPooRabbitAnimDescs[b].tiles);
    }
}

void task_poo_rabbit_0(PooRabbitWork* w) {
    u16 m;
    u16 n;
    u8 i;

    w->x = 0x1B700;
    w->y = 0x16E00;
    w->z = 0;
    w->unk_34 = 0;
    w->palette = NULL;
    m = 0;

    for (i = 0; i < 2; i++) {
        n = GetMaxSpriteTileBytes(gPooRabbitGfxDescs[i].gfxTable, gPooRabbitGfxDescs[i].gfxCount);

        if (m < n) {
            m = n;
        }
    }

    w->tiles = AllocObjTiles(m, NULL);
    AnimInit(&w->anim, NULL, NULL);
    w->animIndex = 7;
    SetPooRabbitAnimation(w, 1, 0);
    w->flipped = 0;
    w->timer = 0;
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    CreatePooShadowscaleTask(&w->tasks, &w->x, 0x100);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    w->interactionId = AddPoohInteraction(&w->collider, 0x3B);
    SetPoohInteractionEnabled(w->interactionId, 0);
}

u8 task_poo_rabbit_1(PooRabbitWork* w) {
    switch (w->animIndex) {
    case 1:
        if (AnimIsFinished(&w->anim) != 0) {
            w->timer++;

            if (w->timer <= 3) {
                AnimReset(&w->anim);
            } else {
                SetPooRabbitAnimation(w, 4, 1);
                w->flipped = 1;
                w->timer = 312;
            }
        }

        break;
    case 4:
        if (w->palette != NULL && w->collider.colliding != 0 && ColliderIsTouchingType(&w->collider, 9) != 0) {
            SetPooRabbitAnimation(w, 6, 0);
            w->waitTimer = 20;
        } else {
            ApproachValue(&w->x, 0x23000, w->timer);
            ApproachValue(&w->y, 0x12400, w->timer);
            w->timer--;

            if (w->timer == 0) {
                SetPooRabbitAnimation(w, 5, 0);
                w->flipped = 1;
            }
        }

        break;
    case 5:
        if (AnimIsFinished(&w->anim) != 0) {
            SetPooRabbitAnimation(w, 2, 1);
            w->flipped = 0;
            w->timer = 260;
        }

        break;
    case 2:
        if (w->palette != NULL && w->collider.colliding != 0 && ColliderIsTouchingType(&w->collider, 9) != 0) {
            w->waitTimer = 20;
            SetPooRabbitAnimation(w, 0, 0);
        } else {
            ApproachValue(&w->x, 0x1B700, w->timer);
            ApproachValue(&w->y, 0x16E00, w->timer);
            w->timer--;

            if (w->timer == 0) {
                SetPooRabbitAnimation(w, 1, 0);
                w->flipped = 0;
                w->timer = 0;
            }
        }

        break;
    case 6:
        if (w->waitTimer == 0) {
            if (w->palette != NULL && ColliderIsTouchingType(&w->collider, 9) == 0) {
                SetPooRabbitAnimation(w, 4, 1);
            }
        } else {
            w->waitTimer--;
        }

        break;
    case 0:
        if (w->waitTimer != 0) {
            w->waitTimer--;
        } else if (w->palette != NULL && ColliderIsTouchingType(&w->collider, 9) == 0) {
            SetPooRabbitAnimation(w, 2, 1);
        }

        break;
    default:
        break;
    }

    w->gfx = AnimUpdate(&w->anim);
    return 1;
}

void task_poo_rabbit_2(PooRabbitWork* w) {
    TaskPool* pool;
    s32 pr;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 48, 8, 16, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            ColliderUnregister(&w->collider);
            SetPoohInteractionEnabled(w->interactionId, 0);
            w->palette = NULL;
        }
    } else {
        pool = &w->tasks;
        TaskPoolUpdate(pool);

        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gRabbitPalette, 0x40);
            ColliderInit(&w->collider, 10, 4, 48);
            SetPoohInteractionEnabled(w->interactionId, 1);
        }

        ColliderSetPosition(&w->collider, w->x, w->y, w->z);
        pr = w->flipped != 0 ? 0x801 : 0x800;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, pr, -0x1004 - (w->y >> 8) * 4);
        TaskPoolDraw(pool);
    }
}

void task_poo_rabbit_3(PooRabbitWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void SetPooTiggerrooAnimation(PooTiggerWork* w, u16 b) {
    s32 a;

    AnimReset(&w->anim);

    if (w->mode == 2) {
        switch (w->heading) {
        case 0xAD:
            a = 2;
            w->flipped = 0;
            break;
        case 0x53:
            a = 2;
            w->flipped = 1;
            break;
        case 0xD3:
            a = 3;
            w->flipped = 0;
            break;
        case 0x00:
        default:
            a = 3;
            w->flipped = 1;
            break;
        }
    } else {
        a = 0;
    }

    if (w->animIndex != a) {
        w->animIndex = a;
        AnimStart(&w->anim, a, b);
    }
}

void SetPooTiggerAnimation(PooTiggerWork* w, u16 b) {
    u16 r;

    AnimReset(&w->anim);

    if (w->mode == 0) {
        r = 0;
    } else if (w->mode == 1) {
        r = 1;
    } else if (w->mode == 2) {
        switch (w->heading) {
        case 0xAD:
            r = 2;
            w->flipped = 0;
            break;
        case 0x53:
            r = 2;
            w->flipped = 1;
            break;
        case 0xD3:
            r = 3;
            w->flipped = 0;
            break;
        case 0x2D:
        default:
            r = 3;
            w->flipped = 1;
            break;
        }
    } else {
        r = 0;
    }

    if (w->animIndex != r) {
        w->animIndex = r;
        AnimChangeWithTables(&w->anim, gPooTiggerAnimDescs[r].animId, b, gPooTiggerAnimDescs[r].unk_00, gPooTiggerAnimDescs[r].unk_04);
        SetObjTileSource(w->tiles, gPooTiggerAnimDescs[r].tiles);
    }
}

void StartPooTiggerHopStep(PooTiggerWork* w) {
    PooAnimData* d;
    s32 t[8];

    memcpy(t, gPooTiggerHopHeights, sizeof(t));
    d = ((PooAnimData**)gPooTiggerAnimDescs[w->animIndex].unk_00)[gPooTiggerAnimDescs[w->animIndex].animId];
    w->stepTimer = (&d->frames[w->step])->duration;
    w->targetZ = t[w->step] - 0x1800;
    w->step++;
}

u16 GetPooTiggerAnimDuration(PooTiggerWork* w) {
    PooAnimData* d;
    u16 t;
    s32 i;

    d = ((PooAnimData**)gPooTiggerAnimDescs[w->animIndex].unk_00)[gPooTiggerAnimDescs[w->animIndex].animId];
    t = 0;

    for (i = 0; i < d->frameCount; i++) {
        t += d->frames[i].duration;
    }

    return t;
}

void StartPooTiggerHop(PooTiggerWork* w) {
    w->hopTimer = GetPooTiggerAnimDuration(w);

    if (w->heading == 0xAD) {
        w->x = gPooTiggerHopCorners[0];
        w->y = gPooTiggerHopCorners[1];
        w->targetX = gPooTiggerHopCorners[2];
        w->targetY = gPooTiggerHopCorners[3];
    } else if (w->heading == 0x53) {
        w->x = gPooTiggerHopCorners[2];
        w->y = gPooTiggerHopCorners[3];
        w->targetX = gPooTiggerHopCorners[4];
        w->targetY = gPooTiggerHopCorners[5];
    } else if (w->heading == 0x2D) {
        w->x = gPooTiggerHopCorners[4];
        w->y = gPooTiggerHopCorners[5];
        w->targetX = gPooTiggerHopCorners[6];
        w->targetY = gPooTiggerHopCorners[7];
    } else {
        w->x = gPooTiggerHopCorners[6];
        w->y = gPooTiggerHopCorners[7];
        w->targetX = gPooTiggerHopCorners[0];
        w->targetY = gPooTiggerHopCorners[1];
    }

    w->z = -0x1800;
    w->step = 0;
    StartPooTiggerHopStep(w);
}

void PlayPooTiggerHopSound(s32 x, s32 y, s32 z, u8 c) {
    s16 sx;
    s16 sy;

    sx = (x >> 8) - gPooScrollX;
    sy = (y >> 8) + (z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(sx, sy, 120, 8, 24, 24) == 0) {
        if (c != 0) {
            m4aSongNumStart(SONG_SND_961);
        } else {
            m4aSongNumStart(SONG_SYS_LU_JP);
        }
    }
}

void task_poo_tigger_0(PooTiggerWork* w) {
    PooShadowArgs args;
    u16 m;
    u16 t;
    u8 i;

    w->mode = 2;
    w->heading = 0xAD;
    w->isTigger = 1;
    w->palette = NULL;
    m = 0;

    for (i = 0; i < 4; i++) {
        t = GetMaxSpriteTileBytes(gPooTiggerGfxDescs[i].gfxTable, gPooTiggerGfxDescs[i].gfxCount);

        if (m < t) {
            m = t;
        }
    }

    w->tiles = AllocObjTiles(m, NULL);
    AnimInit(&w->anim, NULL, NULL);
    w->animIndex = 4;
    SetPooTiggerAnimation(w, 0);
    StartPooTiggerHop(w);
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    args.pos = (PooPos*)&w->x;
    args.shadowInfo = &w->shadowInfo;
    TaskCreate(&w->tasks, &gTaskDescPooShadowdodai, &args);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
}

u8 task_poo_tiggerroo_1(PooTiggerWork* w) {
    GetPooGroundZ(&w->collider, (PooPos*)&w->x, &w->onCollider);

    if (w->mode == 2) {
        if (w->hopTimer > 0) {
            ApproachValueHalfSteps(&w->x, w->targetX, w->hopTimer);
            ApproachValueHalfSteps(&w->y, w->targetY, w->hopTimer);
            w->hopTimer--;
            ApproachValue((u32*)&w->z, w->targetZ, w->stepTimer);
            w->stepTimer--;

            if (w->stepTimer == 0) {
                StartPooTiggerHopStep(w);
            }
        } else {
            switch (w->heading) {
            case 0xAD:
                w->heading = 0x53;
                break;
            case 0x53:
                w->heading = 0x2D;
                break;
            case 0x2D:
                w->heading = 0xD3;
                break;
            case 0xD3:
                w->heading = 0xAD;
                break;
            }

            if (w->isTigger != 0) {
                SetPooTiggerAnimation(w, 0);
            } else {
                SetPooTiggerrooAnimation(w, 0);
            }

            StartPooTiggerHop(w);
            PlayPooTiggerHopSound(w->x, w->y, w->z, w->isTigger);
        }
    }

    w->gfx = AnimUpdate(&w->anim);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_tiggerroo_2(PooTiggerWork* w) {
    u16 z;
    s32 pr;
    s32 d;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 56, 8, 24, 24) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);

            if (w->isTigger == 0) {
                if (w->tiles != NULL) {
                    ReleaseObjTiles(w->tiles);
                    w->tiles = NULL;
                }
            }
        }
    } else {
        if (w->palette == NULL) {
            if (w->isTigger != 0) {
                w->palette = LoadObjPalette(gTiggerPalette, 0x20);
                ColliderInit(&w->collider, 4, 8, 8);
            } else {
                w->palette = LoadObjPalette(gRooPalette, 0x20);
                w->tiles = AllocObjTiles(w->tileBytes, gRooFl00Tiles);
                ColliderInit(&w->collider, 4, 8, 8);
            }
        }

        ColliderSetPosition(&w->collider, w->x, w->y, w->z);
        pr = w->flipped != 0 ? 0x801 : 0x800;
        d = w->onCollider;

        if (d != 0) {
            z = -0x1008 - (w->collider.platformY >> 8) * 4;

            if (w->y >= gPooActor.pos.y) {
                z -= 2;
            } else {
                z += 2;
            }

            if (w->collider.penetration <= w->collider.radius) {
                w->shadowInfo.z = 0;
                w->shadowInfo.priority = 0;
            } else {
                w->shadowInfo.z = w->collider.platformZ;
                w->shadowInfo.priority = z + 1;
            }
        } else {
            z = -0x1004 - (w->y >> 8) * 4;
            w->shadowInfo.z = d;

            if (d != w->ground) {
                w->shadowInfo.priority = 0;
            } else {
                w->shadowInfo.priority = z + 1;
            }
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, pr, z);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_tiggerroo_3(PooTiggerWork* w) {
    if (w->tiles != NULL) {
        ReleaseObjTiles(w->tiles);
    }

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_tiggerroo_0(PooTiggerWork* w) {
    PooShadowArgs args;

    w->mode = 2;
    w->heading = 0x2D;
    w->isTigger = 0;
    w->palette = NULL;
    w->tiles = NULL;
    w->tileBytes = GetMaxSpriteTileBytes(gRooFl00Frames, 18);
    AnimInit(&w->anim, gRooFl00Anims, gRooFl00Frames);
    w->animIndex = 4;
    SetPooTiggerrooAnimation(w, 0);
    StartPooTiggerHop(w);
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    args.pos = (PooPos*)&w->x;
    args.shadowInfo = &w->shadowInfo;
    TaskCreate(&w->tasks, &gTaskDescPooShadowdodai, &args);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
}

void task_poo_roo_0(PooRooWork* w, PooPos* p) {
    gStockMesDispWork = w;
    w->srcPos = p;
    w->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gRooFl00Frames, 8), gRooFl00Tiles);
    w->palette = LoadObjPalette(gRooPalette, 0x20);
    AnimInit(&w->anim, gRooFl00Anims, gRooFl00Frames);

    if (IsPooEventDone(5) != 0) {
        w->pos.x = 0x95F00;
        w->pos.y = 0x4EE00;
        w->pos.z = 0;
        AnimStart(&w->anim, 0, 0);
        w->flipped = 0;
        w->state = 3;
    } else {
        w->pos = *w->srcPos;
        AnimStart(&w->anim, 4, 0);
        w->flipped = 0;
        w->state = 0;
    }

    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescPooShadow, &w->pos);
    ColliderInit(&w->collider, 10, 4, 32);
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);

    if (IsPooEventDone(5) != 0) {
        w->interactionId = AddPoohInteraction(&w->collider, 58);
    }
}

u8 task_poo_roo_1(PooRooWork* w) {
    s32 t;

    switch (w->state) {
    case 0:
        if (AnimIsFinished(&w->anim) != 0) {
            AnimStart(&w->anim, 5, 0);
            w->state = 1;
            w->pos = *w->srcPos;
            w->pos.x -= 0x600;
            w->pos.z += 0x1F00;
        }

        break;
    case 1:
        w->lastZ = w->pos.z;
        w->pos = *w->srcPos;
        w->pos.x -= 0x600;
        t = w->pos.z + 0x1F00;
        w->pos.z = t;

        if (w->lastZ - t < 0 && t >= -0x2100) {
            AnimStart(&w->anim, 6, 0);
            w->state = 2;
            w->vz = 0;
        }

        break;
    case 2:
        w->pos.z += w->vz;
        w->vz += 7;

        if (w->pos.z >= 0) {
            w->pos.z = 0;
        } else {
            w->pos.x -= 0x40;
            w->pos.y += 0x40;
        }

        if (w->srcPos->z >= 0) {
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
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequest = 5;
        }

        break;
    }

    w->gfx = AnimUpdate(&w->anim);
    ColliderSetPosition(&w->collider, w->pos.x, w->pos.y, w->pos.z);
    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_roo_2(PooRooWork* w) {
    s16 x;
    s16 y;
    s32 pr;
    s32 t;

    x = (w->pos.x >> 8) - gPooScrollX;
    t = w->pos.y >> 8;
    y = t + (w->pos.z >> 8) - gPooScrollY;
    pr = w->flipped != 0 ? 0x801 : 0x800;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, pr, -0x1006 - t * 4);

    if (w->state != 0) {
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_roo_3(PooRooWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
}

u8 IsPooRooAnimFrameEnding() {
    return AnimIsFrameEnding(&((PooRooWork*)gStockMesDispWork)->anim);
}

u8 IsPooRooAnimFinished() {
    return AnimIsFinished(&((PooRooWork*)gStockMesDispWork)->anim);
}

void task_poo_roo_footmark_0(PooFootmarkWork* w) {
    w->x = 0x4A700;
    w->y = 0x28E00;
    w->unk_14 = 0;
    w->tiles = LoadObjTiles(gRoFootmarkTiles, 0x500);
    w->palette = NULL;

    if (IsPooEventDone(5) == 0) {
        w->gfx = gRoFootmarkFrame0;
    } else {
        w->gfx = gRoFootmarkFrame1;
    }
}

u8 task_poo_roo_footmark_1(void* w) {
    return 1;
}

void task_poo_roo_footmark_2(PooFootmarkWork* w) {
    PooNode* n;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 48, 0, 48) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            RemovePooNode(&w->node);
            w->palette = NULL;
        }
    } else {
        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gRoFootmarkPalette, 0x20);
            n = &w->node;
            AddPooNode(n, 0x240, &w->x);

            if (IsPooEventDone(5) != 0) {
                SetPooNodeWeight(n, 0);
            }
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0xFFF1);
    }
}

void task_poo_roo_footmark_3(PooFootmarkWork* w) {
    ReleaseObjTiles(w->tiles);

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
        RemovePooNode(&w->node);
    }
}

void task_poo_leaf_0(PooLeafWork* w, PooSpawnArgs* a) {
    w->x = a->pos.x;
    w->y = a->pos.y;
    w->z = 0;
    w->prizeId = a->prizeId;
    w->tileBytes = GetMaxSpriteTileBytes(gUnk_09EF610C, 5);
    w->palette = NULL;
    AnimInit(&w->anim, gUnk_09EF612C, gUnk_09EF610C);
    AnimStart(&w->anim, 0, 0);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderSetPosition(&w->collider, w->x + 0x1C00, w->y + 0x1000, w->z);
    w->playing = 0;
}

u8 task_poo_leaf_1(PooLeafWork* w) {
    if (w->palette != NULL && (w->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0 && w->playing == 0) {
        w->playing = 1;
        AnimReset(&w->anim);
        m4aSongNumStart(SONG_SND_224);

        if (IsPooPrizeDropped(w->prizeId) == 0) {
            if (SpawnPooPrizes(2, 3, w->x + 0x1C00, w->y + 0x2000, w->z) != 0) {
                SetPooPrizeDropped(w->prizeId);
            }
        }
    }

    return 1;
}

void task_poo_leaf_2(PooLeafWork* w) {
    u8* p;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 32, 0, 56) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
            w->playing = 0;
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gUnk_0975C3E2);
            w->palette = LoadObjPalette(gUnk_09849DF8, 0x20);
            ColliderInit(&w->collider, 6, 28, 0);
        }

        p = &w->playing;

        if (*p != 0) {
            w->gfx = AnimUpdate(&w->anim);

            if (AnimIsFinished(&w->anim) == 0) {
                DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0xFFF1);
            } else if ((w->collider.standFlags & COLLIDER_STAND_STOOD_ON) == 0) {
                *p = 0;
            }
        }
    }
}

void task_poo_leaf_3(PooLeafWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }
}

void task_poo_tanpopo_0(PooTanpopoWork* w, PooSpawnArgs* a) {
    w->x = a->pos.x;
    w->y = a->pos.y;
    w->z = 0;
    w->prizeId = a->prizeId;
    w->tileBytes = GetMaxSpriteTileBytes(gUnk_09EF6130, 2);
    w->tileBytes2 = GetMaxSpriteTileBytes(gUnk_09EF613C, 6);
    w->palette = NULL;
    AnimInit(&w->anim, gUnk_09EF6138, gUnk_09EF6130);
    AnimStart(&w->anim, 0, 0);
    w->gfx = AnimGetGfx(&w->anim);
    AnimInit(&w->anim2, gUnk_09EF6154, gUnk_09EF613C);
    AnimStart(&w->anim2, 0, 0);
    w->gfx2 = AnimGetGfx(&w->anim2);
    ColliderSetPosition(&w->collider, w->x + 0x1800, w->y + 0x1000, w->z);
    w->playing = 0;
}

u8 task_poo_tanpopo_1(PooTanpopoWork* w) {
    if (w->palette != NULL && (w->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0 && w->playing == 0) {
        w->playing = 1;
        AnimReset(&w->anim);
        AnimReset(&w->anim2);

        if (IsPooPrizeDropped(w->prizeId) == 0) {
            if (SpawnPooPrizes(2, 1, w->x + 0x1800, w->y + 0x2000, w->z) != 0) {
                SetPooPrizeDropped(w->prizeId);
            }
        }
    }

    return 1;
}

void task_poo_tanpopo_2(PooTanpopoWork* w) {
    u8* p;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 32, 0, 48) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjTiles(w->tiles2);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
            w->playing = 0;
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = LoadObjTiles(gUnk_0975E40E, 0x800);
            w->tiles2 = LoadObjTiles(gUnk_0975EC8E, 0x1800);
            w->palette = LoadObjPalette(gUnk_09849E18, 0x20);
            ColliderInit(&w->collider, 6, 24, 0);
        }

        p = &w->playing;

        if (*p != 0) {
            w->gfx = AnimUpdate(&w->anim);
            w->gfx2 = AnimUpdate(&w->anim2);
            DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), 0xFFF1);

            if (AnimIsFinished(&w->anim2) == 0) {
                DrawSprite(x, y, w->gfx2, w->tiles2, w->palette, NULL, SPRITE_PRIORITY(2), 100);
            } else if ((w->collider.standFlags & COLLIDER_STAND_STOOD_ON) == 0) {
                *p = 0;
            }
        }
    }
}

void task_poo_tanpopo_3(PooTanpopoWork* w) {
    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
        ReleaseObjTiles(w->tiles);
        ReleaseObjTiles(w->tiles2);
        ColliderUnregister(&w->collider);
    }
}

void task_poo_ti_board_0(PooBoardWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y;
    w->z = 0;
    w->tiles = LoadObjTiles(gUnk_097565FC, 0x200);
    w->palette = NULL;
    w->gfx = gUnk_097565E8;
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
}

u8 task_poo_ti_board_1(PooBoardWork* w) {
    if (w->palette != NULL) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_ti_board_2(PooBoardWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 16, 1, 8, 8) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
        }
    } else {
        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gUnk_09849D58, 0x20);
            ColliderInit(&w->collider, 7, 8, 16);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);
    }
}

void task_poo_ti_board_3(PooBoardWork* w) {
    ReleaseObjTiles(w->tiles);

    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }
}

void task_poo_eeyoretail_0(PooEeyoreTailWork* w) {
    w->x = 0x7CD00;
    w->y = 0x49E00;
    w->z = -0x2000;
    w->unk_18 = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gEeyoreFl00Frames, 0x10);
    w->palette = NULL;
    w->gfx = gEeyoreFl00Frame15;
    TaskPoolInit(&w->tasks, 1);
    CreatePooShadowscaleTask(&w->tasks, &w->x, 0x66);
    sPooEeyoreTailTimer = 0x1E;
    w->height = -w->z;
}

u8 task_poo_eeyoretail_1(PooEeyoreTailWork* w) {
    if (IsPoohBeeChaseOver() != 0) {
        if (sPooEeyoreTailTimer != 0) {
            ApproachValue(&w->x, 0x7FD00, sPooEeyoreTailTimer);
            ApproachValue(&w->y, 0x49300, sPooEeyoreTailTimer);
            ApproachValue(&w->height, 0, sPooEeyoreTailTimer);
            w->z = -w->height;
            sPooEeyoreTailTimer--;
            SetPooCameraFocus(w->x, w->y + w->z);
        }

        TaskPoolUpdate(&w->tasks);
    }

    return 1;
}

void task_poo_eeyoretail_2(PooEeyoreTailWork* w) {
    s16 x;
    s16 y;
    u16 pr;
    s32 z;

    x = ((s32)w->x >> 8) - gPooScrollX;
    y = ((s32)w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gEeyoreFl00Tiles);
            w->palette = LoadObjPalette(gEeyorePalette, 0x20);
        }

        if (IsPooEeyoreTailLanded() != 0) {
            pr = 0x800;
            z = 0xFFEF;
        } else {
            pr = 0x400;
            z = 10;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, pr, z);

        if (IsPoohBeeChaseOver() != 0) {
            TaskPoolDraw(&w->tasks);
        }
    }
}

void task_poo_eeyoretail_3(PooEeyoreTailWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    TaskPoolDestroy(&w->tasks);
}

u8 IsPooEeyoreTailLanded() {
    if (sPooEeyoreTailTimer == 0) {
        return 1;
    }

    return 0;
}

void task_poo_honeycomb_0(PooHoneycombWork* w) {
    w->x = 0x8DE00;
    w->y = 0x46600;
    w->z = -0xA00;
    w->unk_30 = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gEeHoneycombFrames, 1);
    w->palette = NULL;
    w->gfx = gEeHoneycombFrame0;
    ColliderSetPosition(&w->collider, w->x, w->y, 0);
    w->colliderActive = 0;
    sPooHoneycombState = 0;
    w->shakeX = 0;
    w->angle = 0;
}

u8 task_poo_honeycomb_1(PooHoneycombWork* w) {
    u8 c;

    if (w->colliderActive != 0) {
        switch (sPooHoneycombState) {
        case 2:
            break;
        case 0:
            if (ColliderIsTouchingType(&w->collider, 9) != 0) {
                c = IsPooEventDone(2);

                if (c == 0) {
                    gPoohRequest = 9;

                    if (IsPoohLookingAtHoneycomb() != 0) {
                        sPooHoneycombState = 1;
                        w->shakeTimer = c;
                    }
                } else {
                    gPoohRequest = 10;
                }
            }

            break;
        case 1:
            w->shakeX = gSineTable[(u8)w->angle];
            w->angle += 16;
            w->shakeTimer++;

            if (w->shakeTimer > 60) {
                w->shakeX = 0;
                sPooHoneycombState = 2;
                m4aSongNumStart(SONG_SND_371);
            }

            break;
        }
    }

    return 1;
}

void task_poo_honeycomb_2(PooHoneycombWork* w) {
    u8* p;
    s16 x;
    s16 y;

    x = ((w->x + w->shakeX) >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 16, 16, 16, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            ReleaseObjTiles(w->tiles);
            w->palette = NULL;
        }

        p = &w->colliderActive;

        if (*p != 0) {
            ColliderUnregister(&w->collider);
            *p = 0;
        }
    } else {
        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gEeHoneycombPalette, 0x20);
            w->tiles = AllocObjTiles(w->tileBytes, gEeHoneycombTiles);
        }

        p = &w->colliderActive;

        if (*p == 0) {
            ColliderInit(&w->collider, 6, 64, 0);
            *p = 1;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(3), 0xFFF0);
    }
}

void task_poo_honeycomb_3(PooHoneycombWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
    }
}

u8 IsPooHoneycombShaken() {
    if (sPooHoneycombState == 2) {
        return 1;
    }

    return 0;
}

void task_poo_vegetable_0(PooVegetableWork* w) {
    w->x = 0x1AC00;
    w->y = 0x18000;
    w->z = 0;
    w->unk_30 = 0;
    w->tileBytes = GetMaxSpriteTileBytes(gRaVegetablesFrames, 1);
    w->palette = NULL;
    w->gfx = gRaVegetablesFrame0;
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
}

u8 task_poo_vegetable_1(PooVegetableWork* w) {
    if (w->palette != NULL) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_vegetable_2(PooVegetableWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 32, 40, 48, 48) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
            ColliderUnregister(&w->collider);
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gRaVegetablesTiles);
            w->palette = LoadObjPalette(gRaVegetablesPalette, 0x20);
            ColliderInit(&w->collider, 7, 0x26, 12);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);
    }
}

void task_poo_vegetable_3(PooVegetableWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }
}

s32 IsInPooWagonArea(PooPos* p) {
    s32 k;
    s32 x;
    s32 y;

    k = 0x2500;

    if (IsPooEventDone(6) != 0) {
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

    if (IsPooEventDone(6) != 0) {
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

void task_poo_wagon_0(PooWagonWork* w) {
    sPooWagon = w;
    w->pos.x = 0x2AE00;
    w->pos.y = 0x17700;
    w->pos.z = 0;
    w->pos.ground = 0;
    w->pos2 = w->pos;

    if (IsPooEventDone(6) != 0) {
        w->pos.y += 0xC00;
    }

    w->palette = NULL;
    w->gfx = gRaWagonFrame11;
    w->gfx2 = gRaWagonFrame1;
    w->gfx3 = gRaWagonFrame12;
    w->poohAboard = 0;
    w->timer = 0;
    w->angle = 0;
}

u8 task_poo_wagon_1(PooWagonWork* w) {
    u8 c;
    s32 t;
    s32 d;

    if (IsPooSoraOnWagon() != 0) {
        if (w->pos.y == w->pos2.y) {
            w->pos.y += 0x100;
            gPooActor.pos.y += 0x100;

            if (w->poohAboard != 0) {
                gPoohPos->y += 0x100;
            }
        }
    } else if (IsPooEventDone(6) == 0) {
        if (w->pos.y != w->pos2.y) {
            w->pos.y -= 0x100;
            gPooActor.pos.y -= 0x100;

            if (w->poohAboard != 0) {
                gPoohPos->y -= 0x100;
            }
        }
    }

    c = IsInPooWagonAreaForPooh(gPoohPos);

    if (c != 0) {
        if (w->poohAboard == 0) {
            gPoohRequestX = w->pos.x;
            gPoohRequestY = w->pos.y;
            gPoohRequest = 11;
            w->poohAboard = 1;
        }
    } else {
        w->poohAboard = 0;
    }

    if (IsPooSoraOnWagon() != 0 && IsPoohWaitingOnWagon() != 0 && IsPooEventDone(6) == 0) {
        w->timer++;

        if (w->timer > 100) {
            if (w->pos.y != w->pos2.y + 0xC00) {
                t = w->pos.y - 0xC00;
                d = w->pos2.y - t;
                w->pos.y += d;
                gPooActor.pos.y += d;
                gPoohPos->y += d;
                SetPooEventDone(6);
                m4aSongNumStart(SONG_SYS_OBJ_BREAK);
                w->timer = 0;
            }
        }
    } else {
        w->timer = 0;
    }

    return 1;
}

void task_poo_wagon_2(PooWagonWork* w) {
    s32 t;
    s16 x;
    s16 y;
    u16 n;
    u16 p;
    s32 d;
    s32 k;

    d = 0;

    if (w->timer != 0) {
        t = gSineTable[(u8)w->angle];
        w->angle += 16;
    } else {
        t = 0;
    }

    x = ((w->pos.x + t) >> 8) - gPooScrollX;
    y = (w->pos.y >> 8) + (w->pos.z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 32, 40, 48, 48) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjTiles(w->tiles2);
            ReleaseObjTiles(w->tiles3);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }

        return;
    }

    if (w->palette == NULL) {
        w->tiles = AllocObjTiles(0x560, gRaWagonTiles);
        w->tiles2 = AllocObjTiles(0x4C0, gRaWagonTiles);
        w->tiles3 = AllocObjTiles(160, gRaWagonTiles);
        w->palette = LoadObjPalette(gRaWagonPalette, 32);
    }

    n = GetPooSoraPriority();

    if (IsPooSoraOverWagon() != 0) {
        sPooWagonPriority = n + 3;
        sPooWagonPriority2 = n - 1;

        if (IsPoohOnWagon() != 0) {
            if (gPooActor.pos.y >= gPoohPos->y) {
                sPooWagonPriority += 6;
            } else {
                sPooWagonPriority2 += 0xFFFC;
            }
        }
    } else {
        d = (u8)GetPooWagonSide(gPooActor.pos.x, gPooActor.pos.y);

        if (d == 0) {
            k = w->pos.y + 0x300;
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

    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), sPooWagonPriority);
    DrawSprite(x, y, w->gfx2, w->tiles2, w->palette, NULL, SPRITE_PRIORITY(2), sPooWagonPriority2);
    p = -0x1002 - ((w->pos.y - 0xE00) >> 8) * 4;

    if (IsPooSoraOverWagon() == 0 && n > p && (d == 83 || d == 173)) {
        p = n - 1;
    }

    DrawSprite(x, y, w->gfx3, w->tiles3, w->palette, NULL, SPRITE_PRIORITY(2), p);
}

void task_poo_wagon_3(PooWagonWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjTiles(w->tiles2);
        ReleaseObjTiles(w->tiles3);
        ReleaseObjPalette(w->palette);
    }
}

u16 GetPooWagonPriority2() {
    return sPooWagonPriority2;
}

u16 GetPooWagonPriority() {
    return sPooWagonPriority;
}

void task_poo_wagonwheel_0(PooWheelWork* w) {
    s16 x;
    s16 y;

    if (IsPooEventDone(6) == 0) {
        w->x = 0x2A800;
        w->y = 0x18D00;
        w->animId = 2;
        w->gfx = gRaWagonFrame3;
    } else {
        GetPooStateWheelPos(&x, &y);
        w->x = x << 8;
        w->y = y << 8;
        w->animId = 4;
        w->gfx = gRaWagonFrame10;
    }

    w->startX = w->x;
    w->z = 0;
    w->unk_30 = 0;
    w->tileBytes = 0x180;
    w->palette = NULL;
    AnimInit(&w->anim, gRaWagonAnims, gRaWagonFrames);
    AnimStart(&w->anim, w->animId, ANIM_FLAG_LOOP);
    w->speed = 0;
    w->removeWhenOffscreen = 0;
}

u8 task_poo_wagonwheel_1(PooWheelWork* w) {
    if (w->animId == 2 && IsPooEventDone(6) != 0) {
        w->animId = 3;
        AnimStart(&w->anim, 3, ANIM_FLAG_LOOP);
    }

    if (w->animId == 3) {
        w->gfx = AnimUpdate(&w->anim);

        if (w->speed <= 0x4FF) {
            w->speed += 6;
        }

        w->y += w->speed;
        w->x += w->speed;

        if (w->x > w->startX + 0x4800) {
            w->x = w->startX + 0x4800;
        }
    }

    if (w->removeWhenOffscreen != 0 && w->palette == NULL) {
        return 0;
    }

    return 1;
}

void task_poo_wagonwheel_2(PooWheelWork* w) {
    u16* p;
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 32, 0, 16, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;

            if (w->animId == 3) {
                w->animId = 4;
                w->gfx = gRaWagonFrame10;
            }
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, gRaWagonTiles);
            w->palette = LoadObjPalette(gRaWagonPalette, 0x20);
        }

        if (IsPooEventDone(6) == 0) {
            p = &sPooWagonWheelPriority;
            *p = GetPooWagonPriority2() - 1;
        } else {
            sPooWagonWheelPriority = -0x1004 - (w->y >> 8) * 4;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), sPooWagonWheelPriority);
    }
}

void task_poo_wagonwheel_3(PooWheelWork* w) {
    if (IsPooEventDone(6) != 0) {
        SetPooStateWheelPos(w->x >> 8, w->y >> 8);
    }

    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }
}

void task_poo_spark_0(PooSparkWork* w, PooPos* p) {
    w->pos = *p;
    w->tiles = AllocObjTiles(0x200, gUnk_098A4B68);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 0x20);
    AnimInit(&w->anim, gUnk_09EF8CC0, gUnk_09EF8CA0);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
}

u8 task_poo_spark_1(PooSparkWork* w) {
    AnimUpdate(&w->anim);

    if (AnimIsFinished(&w->anim) != 0) {
        return 0;
    }

    return 1;
}

void task_poo_spark_2(PooSparkWork* w) {
    u16 x;
    u16 y;

    x = (w->pos.x >> 8) - gPooScrollX;
    y = (w->pos.y >> 8) + (w->pos.z >> 8) - gPooScrollY;
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, NULL, SPRITE_PRIORITY(1), 0x50);
}

void task_poo_spark_3(PooSparkWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void task_poo_bee_0(PooBeeWork* w) {
    void* a;
    void* b;
    s32 i;

    w->x = 0x8DE00;
    w->y = 0x46600;
    w->z = -0xA00;
    w->unk_B0 = 0;
    i = 0;
    a = gEeBeeAnims;
    b = gEeBeeFrames;

    for (; i < 4; i++) {
        w->sub[i].x = -0x500;
        w->sub[i].y = 0x500;
        w->sub[i].targetX = gPooBeePoints[i].x;
        w->sub[i].targetY = gPooBeePoints[i].y;
    }

    AnimInit(&w->anim, a, b);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->palette = NULL;
    sPooBeeCount = 0;
    w->releaseTimer = 8;
    w->setupPending = 1;
}

u8 task_poo_bee_1(PooBeeWork* w) {
    s32 i;

    if (IsPooHoneycombShaken() != 0) {
        if (w->setupPending != 0) {
            w->setupPending = 0;

            for (i = 0; i < 4; i++) {
                w->sub[i].x = w->x - 0x500;
                w->sub[i].y = w->y + 0x500;
                w->sub[i].z = w->z;
                w->sub[i].targetX = 0x2000 + gPoohPos->x + gPooBeePoints[i].x;
                w->sub[i].targetY = -0x2000 + gPoohPos->y + gPooBeePoints[i].y;
            }
        }

        if (sPooBeeCount <= 3) {
            ApproachValue(&w->sub[sPooBeeCount].x, w->sub[sPooBeeCount].targetX, w->releaseTimer);
            ApproachValue(&w->sub[sPooBeeCount].y, w->sub[sPooBeeCount].targetY, w->releaseTimer);
            w->releaseTimer--;

            if (w->releaseTimer == 0) {
                w->releaseTimer = 8;
                sPooBeeCount++;

                if (sPooBeeCount > 3) {
                    w->x = gPoohPos->x + 0x2000;
                    w->y = gPoohPos->y - 0x2000;
                    w->dx = w->dy = 0;
                }
            }

            SetPooCameraFocus(w->x, w->y + w->z);
        } else {
            w->dx = w->x - (gPoohPos->x + 0x2000);
            w->dy = w->y - (gPoohPos->y - 0x2000);
            w->x -= w->dx;
            w->y -= w->dy;

            for (i = 0; i < 4; i++) {
                w->sub[i].x -= w->dx;
                w->sub[i].y -= w->dy;
            }

            if (IsPoohBeeChaseOver() == 0) {
                SetPooCameraFocus(w->x, w->y + w->z);
            }
        }

        w->gfx = AnimUpdate(&w->anim);
    }

    return 1;
}

void task_poo_bee_2(PooBeeWork* w) {
    s32 x;
    s32 y;
    s32 u;
    s32 v;
    s32 i;

    if (IsPooHoneycombShaken() == 0) {
        return;
    }

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 19, 17, 46, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            ReleaseObjTiles(w->tiles);
            w->palette = NULL;
        }

        return;
    }

    if (w->palette == NULL) {
        w->palette = LoadObjPalette(gEeBeePalette, 32);
        w->tiles = LoadObjTiles(gEeBeeTiles, 0x180);
    }

    for (i = 0; i < sPooBeeCount + 1 && i <= 3; i++) {
        u = (w->sub[i].x >> 8) - gPooScrollX;
        v = (w->sub[i].y >> 8) + (w->sub[i].z >> 8) - gPooScrollY;
        DrawSprite(u, v, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), i - ((w->y >> 8) * 4 + 0x1003));
    }
}

void task_poo_bee_3(PooBeeWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }
}

u8 AreAllPooBeesOut() {
    if (sPooBeeCount <= 3) {
        return 0;
    }

    return 1;
}

void task_poo_beeAfterEvent_0(PooBeeAfterEventWork* w) {
    sPooBeeAfterEventWork = w;
    w->x = 0x8DE00;
    w->y = 0x46600;
    w->z = -0xA00;
    w->unk_50 = 0;
    AnimInit(&w->anim, gEeBeeAnims, gEeBeeFrames);
    AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    AnimInit(&w->anim2, gEeBeeAnims, gEeBeeFrames);
    AnimStart(&w->anim2, 0, ANIM_FLAG_LOOP);
    w->gfx2 = AnimGetGfx(&w->anim2);
    w->palette = NULL;
}

u8 task_poo_beeAfterEvent_1(PooBeeAfterEventWork* w) {
    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    return 1;
}

void task_poo_beeAfterEvent_2(PooBeeAfterEventWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 19, 17, 46, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjPalette(w->palette);
            ReleaseObjTiles(w->tiles);
            ReleaseObjTiles(w->tiles2);
            w->palette = NULL;

            if (IsPooMapBeeVisible() == 0) {
                m4aSongNumStop(SONG_SND_386);
            }
        }
    } else {
        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gEeBeePalette, 0x20);
            w->tiles = LoadObjTiles(gEeBeeTiles, 0x180);
            w->tiles2 = LoadObjTiles(gEeBeeTiles, 0x180);
            m4aSongNumStart(SONG_SND_386);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1002 - (w->y >> 8) * 4);
        DrawSprite(x - 5, y + 5, w->gfx2, w->tiles2, w->palette, NULL, SPRITE_PRIORITY(2), -0x1003 - (w->y >> 8) * 4);
    }
}

void task_poo_beeAfterEvent_3(PooBeeAfterEventWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjTiles(w->tiles2);
        ReleaseObjPalette(w->palette);
    }
}

u8 IsPooBeeAfterEventVisible() {
    if (IsPooEventDone(2) != 0) {
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

void task_poo_cabbage_0(PooCabbageWork* w) {
    u16 r;

    w->x = 0x98300;
    w->y = 0x4D100;
    w->z = 0;
    w->vz = 0x4CC;
    r = GetRandom();
    w->angle = (r & 15) + 88;
    w->speed = 0x1CC;
    w->palette = NULL;
    AnimInit(&w->anim, gRaVegetablesAnims, gRaVegetablesFrames);
    w->state = 2;
    AnimStart(&w->anim, 2, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 10, 8, 16);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    w->colliderActive = 1;
    TaskPoolInit(&w->tasks, 2);
    CreatePooShadowscaleTask(&w->tasks, &w->x, 0x80);
    w->task = NULL;
    w->age = 0;
    w->wasOnScreen = 0;
    w->animating = 1;
}

u8 task_poo_cabbage_1(PooCabbageWork* w) {
    u16 t[15];
    u16 sx;
    s16 sy;
    s32 v;

    memcpy(t, gPooCabbageRemoveCounts, sizeof(t));
    w->age++;

    switch (w->state) {
    case 2:
        if (gPooAttackActive != 0 && PooAttackHitsCollider(&w->collider) != 0) {
            if (IsTaskActive(w->task) != 0) {
                TaskKill(&w->tasks, w->task);
            }

            w->task = TaskCreate(&w->tasks, &gTaskDescPooSpark, &w->x);
            w->state = 3;
            AnimStart(&w->anim, 3, 0);
            m4aSongNumStart(SONG_SND_222);
            w->moveTimer = 30;
            w->zTimer = 20;
            w->hopHeight = -0x2000;
            GetPooCabbageStackSpot((PooSpot*)&w->targetX);
            w->stackIndex = GetPooCabbageCount();
            IncPooCabbageCount();

            if (w->colliderActive != 0) {
                ColliderUnregister(&w->collider);
                w->colliderActive = 0;
            }
        } else {
            w->x += gSineTable[w->angle] * w->speed >> 8;
            w->y += -gSineTable[w->angle + 0x40] * w->speed >> 8;
            w->vz += 51;
            w->z += w->vz;

            if (w->z > 0) {
                w->z = 0;
                w->vz = -(w->vz * 179 >> 8);
            }

            if (w->wasOnScreen != 0) {
                v = (w->x >> 8) - gPooScrollX;
                sy = (w->y >> 8) + (w->z >> 8) - gPooScrollY;
                sx = v;

                if ((u16)(sx + 16) > 272 || sy < -36 || sy > 196) {
                    return 0;
                }
            }
        }

        break;
    case 3:
        if (w->zTimer != 0) {
            ApproachValue(&w->z, w->targetZ + w->hopHeight, w->zTimer);
            w->zTimer--;

            if (w->zTimer == 0 && w->hopHeight < 0) {
                w->zTimer = 10;
                w->hopHeight = 0;
            }
        }

        ApproachValue(&w->x, w->targetX, w->moveTimer);
        ApproachValue(&w->y, w->targetY, w->moveTimer);
        w->moveTimer--;

        if (w->moveTimer == 0) {
            w->state = 4;
            AnimStart(&w->anim, 4, 0);
        }

        break;
    case 4:
        if (IsPooEventDone(4) == 0 && w->stackIndex == 13) {
#ifdef VERSION_EU
            ExitPoohMode(140);
#else
            ExitPoohMode(142);
#endif
            SetPooEventDone(4);
            SetJiminyFlag(83);
        }

        if (AnimIsFinished(&w->anim) != 0) {
            w->state = 1;
            AnimStart(&w->anim, 1, 0);
            IncPooCabbageLandedCount();
            w->animating = 0;

            if (w->stackIndex == 5) {
                w->x = 0xAB300;
                w->y = 0x57100;
                w->z = 0;
                w->gfx = gRaVegetablesFrame10;
            } else if (w->stackIndex == 8) {
                w->x = 0xAB300;
                w->y = 0x57100;
                w->z = 0;
                w->gfx = gRaVegetablesFrame11;
            } else {
                w->gfx = gRaVegetablesFrame1;
            }
        }

        break;
    case 1:
        if (t[w->stackIndex] < GetPooCabbageLandedCount()) {
            return 0;
        }

        break;
    }

    return 1;
}

void task_poo_cabbage_2(PooCabbageWork* w) {
    u16 t[5];
    u16 z;
    s16 x;
    s16 y;

    memcpy(t, gPooCabbageStackPriorities, sizeof(t));
    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (x < -16 || x > 256 || y < -36 || y > 196) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = LoadObjTiles(gRaVegetablesTiles, 0x1D20);
            w->palette = LoadObjPalette(gRaVegetablesPalette, 32);
        }

        if (w->animating != 0) {
            w->gfx = AnimUpdate(&w->anim);
        }

        w->wasOnScreen = 1;

        if (w->colliderActive != 0) {
            ColliderSetPosition(&w->collider, w->x, w->y, w->z);
        }

        if (w->stackIndex < 9 || w->stackIndex > 13) {
            z = -0x1004 - (w->y >> 8) * 4;
        } else {
            z = 0xDA38 - t[w->stackIndex - 9];
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), z);

        if (w->state != 4 && w->state != 1) {
            TaskPoolUpdate(&w->tasks);
            TaskPoolDraw(&w->tasks);
        }
    }
}

void task_poo_cabbage_3(PooCabbageWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
    }

    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_cabbageborn_0(PooCabbageBornWork* w) {
    TaskPoolInit(&w->tasks, 0x20);
    w->unk_14 = 0;
    w->timer = 0;
    sPooCabbageCount = 0;
    sPooCabbageLandedCount = 0;
}

u8 CanSpawnPooCabbage() {
    if (IsPooEventDone(6) != 0 && IsPoohOffScreen() == 0 && gPooScrollX > 0x9EB && gPooScrollX <= 0xA8A && gPooScrollY <= 0x548 && gPooScrollY > 0x4F9) {
        return 1;
    }

    return 0;
}

u8 task_poo_cabbageborn_1(PooCabbageBornWork* w) {
    if (CanSpawnPooCabbage() != 0 && w->timer == 0) {
        TaskCreate(&w->tasks, &gTaskDescPooCabbage, NULL);
        w->timer = 40;
    }

    if (w->timer != 0) {
        w->timer--;
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void task_poo_cabbageborn_2(PooCabbageBornWork* w) {
    TaskPoolDraw(&w->tasks);
}

void task_poo_cabbageborn_3(PooCabbageBornWork* w) {
    TaskPoolDestroy(&w->tasks);
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

u8 func_080D1738() {
    if (IsPooEventDone(4) == 0) {
        if (IsPooEventDone(6) != 0) {
            if (gPooScrollY > 0x4F9) {
                return 1;
            }
        }
    }

    return 0;
}

void task_poo_mapobjhit_0(PooMapObjHitWork* w, PooMapObjHitArgs* a) {
    w->x = a->x;
    w->y = a->y;
    w->z = 0;
    w->kind = a->kind;
    w->prizeId = a->prizeId;
    w->desc = a->desc;
    w->tileBytes = GetMaxSpriteTileBytes(w->desc->gfxTable, w->desc->gfxCount);
    w->palette = NULL;
    AnimInit(&w->anim, w->desc->anims, w->desc->gfxTable);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->collider.radius = 0x1000;
    w->collider.height = 0x1800;
    ColliderSetPosition(&w->collider, w->x + 0x1000, w->y + 0xC00, w->z);
    w->playing = 0;
}

u8 task_poo_mapobjhit_1(PooMapObjHitWork* w) {
    SetPooRabbitTalkBlocked(0);

    if (gPooAttackActive != 0) {
        if (PooAttackHitsCollider(&w->collider) != 0) {
            if (w->playing == 0) {
                w->playing = 1;
                AnimReset(&w->anim);

                if (IsPooPrizeDropped(w->prizeId) == 0) {
                    if (SpawnPooPrizes(2, 1, w->x + 0x1000, w->y + 0x1800, w->z) != 0) {
                        SetPooPrizeDropped(w->prizeId);
                    }
                }

                if (w->kind == 4) {
                    m4aSongNumStart(SONG_SYS_PO_WOOD);
                } else {
                    m4aSongNumStart(SONG_SND_224);
                }
            }
        }
    }

    if (w->playing != 0) {
        w->gfx = AnimUpdate(&w->anim);

        if (AnimIsFinished(&w->anim) != 0) {
            w->playing = 0;
        }
    }

    return 1;
}

void task_poo_mapobjhit_2(PooMapObjHitWork* w) {
    s16 x;
    s16 y;
    s32 pr;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (w->playing == 0 || IsRectOutsideScreen(x, y, 0, 24, 0, 32) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }
    } else {
        if (w->palette == NULL) {
            w->tiles = AllocObjTiles(w->tileBytes, w->desc->tiles);
            w->palette = LoadObjPalette(w->desc->palette, 0x20);
        }

        pr = 0x800;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, pr, 0xFFF1);
        SetPooRabbitTalkBlocked(1);
    }
}

void task_poo_mapobjhit_3(PooMapObjHitWork* w) {
    if (w->palette != NULL) {
        ReleaseObjPalette(w->palette);
        ReleaseObjTiles(w->tiles);
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

void PooPrizeUpdateBounce(PooPrizeWork* w) {
    u8 v;

    w->vz += 56;
    w->z += w->vz;
    w->x += gSineTable[w->angle] * w->speed >> 8;
    w->y += -gSineTable[w->angle + 0x40] * w->speed >> 8;

    if (IsPooPosBlocked((PooPos*)w) != 0) {
        w->angle = (u8)(w->angle + 100) + GetRandom() % 57;
    } else {
        w->ground = 0;
    }

    if (w->z > w->ground) {
        w->z = w->ground;
        w->vz = -(w->vz * 179 >> 8);
        w->speed = w->speed * 212 >> 8;
    }

    if (w->collider.colliding != 0 && ColliderIsTouchingType(&w->collider, 1) != 0) {
        switch (w->kind) {
        case 2:
        case 3:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.progression.mooglePoints += w->amount;

            if (gGameState.progression.mooglePoints > 99999) {
                gGameState.progression.mooglePoints = 99999;
            }

            break;
        case 0:
        case 1:
        default:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.hp += w->amount;

            if (gGameState.hp > gGameState.progression.maxHp) {
                gGameState.hp = gGameState.progression.maxHp;
            }

            break;
        }

        w->update = PooPrizeUpdateCollect;
        w->timer = 0;
        w->angle = GetAngle(gPooActor.pos.x, gPooActor.pos.y, w->x, w->y);
        w->collected = 1;
        w->visible = 1;
        w->spin = GetRandom() % 6 + 5;
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetPosition(&w->collider, w->x, w->y, w->z);

        if (w->timer == 20) {
            ColliderSetDisabled(&w->collider, 0);
        }

        if (w->timer > 420) {
            v = 0;

            if (w->visible == 0) {
                v = 1;
            }

            w->visible = v;
        }

        if (w->timer++ > 480) {
            w->update = NULL;
        }
    }
}

void PooPrizeUpdateCollect(PooPrizeWork* w) {
    PooPos* g;
    const s16* t;
    s32 tx;
    s32 ty;
    s32 tz;
    s32 s;
    u8 a;

    g = &gPooActor.pos;
    t = gSineTable;
    a = w->angle;
    tx = g->x + ((t[a] << 5) * w->scale >> 8);
    s = -gSineTable[a + 0x40] * 22;
    ty = g->y + (s * w->scale >> 8);
    tz = g->z - ((w->timer >> 1) << 8);
    w->angle = a + w->spin;
    w->x += (tx - w->x) >> 2;
    w->y += (ty - w->y) >> 2;
    w->z += (tz - w->z) >> 2;
    w->ground = 0;
    w->scale -= 2;

    if (w->timer > 60) {
        w->update = NULL;
    } else {
        w->timer++;
    }
}

void task_poo_prize_0(PooPrizeWork* w, PoohPrizeArgs* a) {
    w->x = a->x;
    w->y = a->y;
    w->z = a->z;
    w->ground = 0;
    w->vz = -(GetRandom() % 0x301 + 0x200);
    w->speed = GetRandom() % 155 + 153;
    w->angle = GetRandom();
    w->tiles = LoadObjTiles(gUnk_098A5CF4, 0x160);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    w->kind = a->kind;

    switch (w->kind) {
    case 3:
        w->gfx = gUnk_098A5CAE;
        w->amount = 10;
        break;
    case 2:
        w->gfx = gUnk_098A5CA4;
        w->amount = 4;
        break;
    case 1:
        w->gfx = gUnk_098A5C9A;
        w->amount = 10;
        break;
    case 0:
    default:
        w->gfx = gUnk_098A5C90;
        w->amount = 3;
        break;
    }

    w->gfx2 = gUnk_098A5CB8;
    w->collected = 0;
    w->visible = 1;
    w->timer = 0;
    w->update = PooPrizeUpdateBounce;
    w->scale = 0x100;
    ColliderInit(&w->collider, 5, 16, 50);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    ColliderSetDisabled(&w->collider, 1);
}

u8 task_poo_prize_1(PooPrizeWork* w) {
    if (w->update != NULL) {
        w->update(w);

        if (w->update != NULL) {
            return 1;
        }
    }

    return 0;
}

void task_poo_prize_2(PooPrizeWork* w) {
    ObjAffine* aff;
    s32 s;
    s16 x;
    s16 y;

    if (w->visible == 0) {
        return;
    }

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8) != 0) {
        return;
    }

    s = w->scale;

    if (s != 256) {
        aff = AllocObjAffine(0, s, s, 0);
    } else {
        aff = NULL;
    }

    DrawSprite(x, y, w->gfx, w->tiles, w->palette, aff, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);

    if (w->collected == 0) {
        y = (w->y >> 8) + (w->ground >> 8) - gPooScrollY;
        DrawSprite(x, y, w->gfx2, w->tiles, w->palette, aff, SPRITE_PRIORITY(2), 0xFFF0);
    }
}

void task_poo_prize_3(PooPrizeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void task_poo_zzz_0(PooZzzWork* w, u8* arg) {
    w->pos = gPoohPos;
    w->tiles = AllocObjTiles(0x100, gPoohFl05Tiles);
    w->palette = LoadObjPalette(gPoohPalette, 0x20);
    AnimInit(&w->anim, gPoohFl05Anims, gPoohFl05Frames);

    if (*arg != 0) {
        AnimStart(&w->anim, 8, ANIM_FLAG_LOOP);
    } else {
        AnimStart(&w->anim, 7, ANIM_FLAG_LOOP);
    }

    w->gfx = AnimGetGfx(&w->anim);
}

u8 task_poo_zzz_1(void* w) {
    return 1;
}

void task_poo_zzz_2(PooZzzWork* w) {
    PooPos* p;
    s16 x;
    s16 y;
    void* g;

    p = w->pos;
    x = (p->x >> 8) - gPooScrollX;
    y = (p->y >> 8) + (p->z >> 8) - gPooScrollY;

    if (x >= -0x20 && x <= 0x110 && y >= -0x20 && y <= 0xC0) {
        g = AnimUpdate(&w->anim);
        w->gfx = g;
        DrawSprite(x, y, g, w->tiles, w->palette, NULL, SPRITE_PRIORITY(1), 0x0B);
    }
}

void task_poo_zzz_3(PooZzzWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
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

void task_poo_butterfly_0(PooButterflyWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y;
    w->z = p->z - 0xE00;
    w->palette = LoadObjPalette(gTrap0100Palette, 0x20);
    w->parts[0].x = w->x - 0x1000;
    w->parts[0].y = w->y;
    w->parts[0].z = w->z;
    w->parts[0].pointAX = w->x - 0x1000;
    w->parts[0].pointAY = w->y;
    w->parts[0].pointBX = w->x + 0x600;
    w->parts[0].pointBY = w->y + 0x700;
    w->parts[0].angle = 0x60;
    w->parts[0].timer = 0x60;
    w->parts[1].x = w->x + 0x1200;
    w->parts[1].y = w->y;
    w->parts[1].z = w->z;
    w->parts[1].pointBX = w->x + 0x1200;
    w->parts[1].pointBY = w->y;
    w->parts[1].pointAX = w->x - 0x100;
    w->parts[1].pointAY = w->y - 0x700;
    w->parts[1].angle = 0xE0;
    w->parts[1].timer = 0x60;
    PooBflyPartInit(&w->parts[0]);
    PooBflyPartInit(&w->parts[1]);
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

u8 task_poo_butterfly_1(PooButterflyWork* w) {
    PooBflyPartUpdate(&w->parts[0]);
    PooBflyPartUpdate(&w->parts[1]);
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

    pr = p->flipped != 0 ? 0x801 : 0x800;
    PooBflyPartSetAnimation(p);
    DrawSprite(x, y, p->gfx, p->tiles, pal, NULL, pr, -0x1004 - (p->y >> 8) * 4);
    return 1;
}

void task_poo_butterfly_2(PooButterflyWork* w) {
    PooBflyPartDraw(&w->parts[0], w->palette);
    PooBflyPartDraw(&w->parts[1], w->palette);
}

void task_poo_butterfly_3(PooButterflyWork* w) {
    ReleaseObjTiles(w->parts[0].tiles);
    ReleaseObjTiles(w->parts[1].tiles);
    ReleaseObjPalette(w->palette);
}

u8 task_poo_butterflyRight_1(PooButterflyWork* w) {
    PooBflyPartUpdate(&w->parts[1]);
    return 1;
}

void task_poo_butterflyRight_2(PooButterflyWork* w) {
    PooBflyPartDraw(&w->parts[1], w->palette);
}

u8 task_poo_butterflyLeft_1(PooButterflyWork* w) {
    PooBflyPartUpdate(&w->parts[0]);
    return 1;
}

void task_poo_butterflyLeft_2(PooButterflyWork* w) {
    PooBflyPartDraw(&w->parts[0], w->palette);
}

void task_poo_mapbee_0(PooMapBeeWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y;
    w->z = 0;
    w->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gUnk_09EF6158, 1), gUnk_097606E8);
    w->palette = LoadObjPalette(gUnk_09849E38, 0x20);
    AnimInit(&w->anim, gUnk_09EF6200, gUnk_09EF6158);
    AnimStart(&w->anim, 0, 0);
    w->gfx = AnimGetGfx(&w->anim);
    w->onScreen = 1;
    w->state = 0;
    m4aSongNumStart(SONG_SND_386);
}

u8 task_poo_mapbee_1(PooMapBeeWork* w) {
    if (w->onScreen == 0) {
        return 0;
    }

    switch (w->state) {
    case 0:
        if (AnimIsFinished(&w->anim) != 0) {
            AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
            w->state = 1;
        }

        break;
    case 1:
        w->z -= 0xCC;
        break;
    }

    w->gfx = AnimUpdate(&w->anim);
    return 1;
}

void task_poo_mapbee_2(PooMapBeeWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8) != 0) {
        w->onScreen = 0;
    } else {
        SetPooMapBeeVisible(1);
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);
    }
}

void task_poo_mapbee_3(PooMapBeeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);

    if (IsPooBeeAfterEventVisible() == 0) {
        m4aSongNumStop(SONG_SND_386);
    }
}

void task_poo_mapbeeborn_0(PooMapBornWork* w, PooPos* p) {
    w->pos = *p;
    w->pos.z = 0;
    w->x = p->x + 0x400;
    w->y = p->y + 0x1800;
    w->unk_08 = 0;
    ColliderSetPosition(&w->collider, w->x, w->y, 0);
    w->colliderActive = 0;
    w->unk_7C = 0;
    w->armed = 0;
    TaskPoolInit(&w->tasks, 1);
    w->task = NULL;
}

u8 task_poo_mapbeeborn_1(PooMapBornWork* w) {
    if (w->colliderActive != 0) {
        if ((w->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0) {
            if (IsTaskActive(w->task) == 0 && w->armed != 0) {
                w->armed = 0;
                w->task = TaskCreate(&w->tasks, &gTaskDescPooMapbee, &w->pos);
            }
        } else {
            w->armed = 1;
        }
    }

    return 1;
}

void task_poo_mapbeeborn_2(PooMapBornWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 24, 0, 32) != 0) {
        if (w->colliderActive != 0) {
            w->colliderActive = 0;
            ColliderUnregister(&w->collider);
            w->armed = 0;

#ifdef VERSION_EU
            if (IsTaskActive(w->task)) {
                TaskKill(&w->tasks, w->task);
            }
#endif
        }
    } else {
        if (w->colliderActive == 0) {
            ColliderInit(&w->collider, 6, 28, 0);
            w->colliderActive = 1;
            w->armed = 1;
        }

        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_mapbeeborn_3(PooMapBornWork* w) {
    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_mapbutterfly_0(PooMapButterflyWork* w, PooPos* p) {
    w->x = p->x;
    w->y = p->y;
    w->z = 0;
    w->tiles = AllocObjTiles(0x40, gUnk_09760986);
    w->palette = LoadObjPalette(gUnk_09849E58, 0x20);
    AnimInit(&w->anim, gUnk_09EF6298, gUnk_09EF6208);
    AnimStart(&w->anim, 0, 0);
    w->gfx = AnimGetGfx(&w->anim);
    w->onScreen = 1;
}

u8 task_poo_mapbutterfly_1(PooMapButterflyWork* w) {
    if (w->onScreen == 0) {
        return 0;
    }

    w->z -= 0x80;
    w->gfx = AnimUpdate(&w->anim);
    return 1;
}

void task_poo_mapbutterfly_2(PooMapButterflyWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) + (w->z >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 8, 8, 8, 8) != 0) {
        w->onScreen = 0;
    } else {
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);
    }
}

void task_poo_mapbutterfly_3(PooMapButterflyWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void task_poo_mapbutterflyborn_0(PooMapBornWork* w, PooPos* p) {
    w->pos = *p;
    w->pos.z = 0;
    w->x = p->x + 0x1000;
    w->y = p->y + 0x1800;
    w->unk_08 = 0;
    ColliderSetPosition(&w->collider, w->x, w->y, 0);
    w->colliderActive = 0;
    w->unk_7C = 0;
    w->armed = 0;
    TaskPoolInit(&w->tasks, 1);
    w->task = NULL;
}

u8 task_poo_mapbutterflyborn_1(PooMapBornWork* w) {
    if (w->colliderActive != 0) {
        if ((w->collider.standFlags & COLLIDER_STAND_STOOD_ON) != 0) {
            if (IsTaskActive(w->task) == 0 && w->armed != 0) {
                w->armed = 0;
                w->task = TaskCreate(&w->tasks, &gTaskDescPooMapbutterfly, &w->pos);
            }
        } else {
            w->armed = 1;
        }
    }

    return 1;
}

void task_poo_mapbutterflyborn_2(PooMapBornWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 0, 24, 0, 32) != 0) {
        if (w->colliderActive != 0) {
            w->colliderActive = 0;
            ColliderUnregister(&w->collider);
            w->armed = 0;
        }
    } else {
        if (w->colliderActive == 0) {
            ColliderInit(&w->collider, 6, 40, 0);
            w->colliderActive = 1;
            w->armed = 1;
        }

        TaskPoolUpdate(&w->tasks);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_mapbutterflyborn_3(PooMapBornWork* w) {
    if (w->colliderActive != 0) {
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_rabbitAfterEvent_0(PooRabbitAfterEventWork* w) {
    w->x = 0xA9B00;
    w->y = 0x57200;
    w->z = 0;
    w->unk_30 = 0;
    w->palette = NULL;
    w->tileBytes = GetMaxSpriteTileBytes(gRabbitBl00Frames, 15);
    AnimInit(&w->anim, gRabbitBl00Anims, gRabbitBl00Frames);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    TaskPoolInit(&w->tasks, 1);
    CreatePooShadowscaleTask(&w->tasks, &w->x, 0x100);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    w->interactionId = AddPoohInteraction(&w->collider, 60);
    SetPoohInteractionEnabled(w->interactionId, 0);
}

u8 task_poo_rabbitAfterEvent_1(PooRabbitAfterEventWork* w) {
    if (w->palette != NULL) {
        if (ColliderIsTouchingType(&w->collider, 9) != 0) {
            gPoohRequest = 5;
        }
    }

    return 1;
}

void task_poo_rabbitAfterEvent_2(PooRabbitAfterEventWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 48, 8, 16, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            ColliderUnregister(&w->collider);
            SetPoohInteractionEnabled(w->interactionId, 0);
            w->palette = NULL;
        }
    } else {
        w->gfx = AnimUpdate(&w->anim);
        TaskPoolUpdate(&w->tasks);

        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gRabbitPalette, 0x40);
            w->tiles = AllocObjTiles(w->tileBytes, gRabbitBl00Tiles);
            ColliderInit(&w->collider, 10, 4, 48);
            SetPoohInteractionEnabled(w->interactionId, 1);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP, -0x1004 - (w->y >> 8) * 4);
        TaskPoolDraw(&w->tasks);
    }
}

void task_poo_rabbitAfterEvent_3(PooRabbitAfterEventWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
        ColliderUnregister(&w->collider);
    }

    TaskPoolDestroy(&w->tasks);
}

void task_poo_cabbageAfterEvent_0(PooCabbageAfterEventWork* w) {
    w->x = 0xAB300;
    w->y = 0x57100;
    w->unk_14 = 0;
    w->unk_18 = 0;
    w->palette = NULL;
    w->tileBytes = GetMaxSpriteTileBytes(gRaVegetablesFrames, 13);
    w->gfx = gRaVegetablesFrame9;
}

u8 task_poo_cabbageAfterEvent_1(PooCabbageAfterEventWork* w) {
    *(void* volatile*)&w->palette;
    return 1;
}

void task_poo_cabbageAfterEvent_2(PooCabbageAfterEventWork* w) {
    s16 x;
    s16 y;

    x = (w->x >> 8) - gPooScrollX;
    y = (w->y >> 8) - gPooScrollY;

    if (IsRectOutsideScreen(x, y, 48, 8, 16, 16) != 0) {
        if (w->palette != NULL) {
            ReleaseObjTiles(w->tiles);
            ReleaseObjPalette(w->palette);
            w->palette = NULL;
        }
    } else {
        if (w->palette == NULL) {
            w->palette = LoadObjPalette(gRaVegetablesPalette, 0x20);
            w->tiles = AllocObjTiles(w->tileBytes, gRaVegetablesTiles);
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - (w->y >> 8) * 4);
    }
}

void task_poo_cabbageAfterEvent_3(PooCabbageAfterEventWork* w) {
    if (w->palette != NULL) {
        ReleaseObjTiles(w->tiles);
        ReleaseObjPalette(w->palette);
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

    if (IsPooFlagSet(1) != 0) {
        return 1;
    }

    n = 0;

    for (i = 0; i < 6; i++) {
        if (IsPooEventDone(v[i]) != 0) {
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
        if (sPoohInteractions->entries[i].message == 0x3B && sPoohInteractions->rabbitTalkBlocked != 0) {
            continue;
        }

        if (sPoohInteractions->entries[i].enabled == 0) {
            continue;
        }

        if (PooAttackHitsCollider(sPoohInteractions->entries[i].collider) == 0) {
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

void AllmapVCountCallback() {
    while ((REG_DISPSTAT & DISPSTAT_HBLANK) == 0) {
    }

    REG_BG2CNT &= ~BGCNT_PRIORITY_MASK;
    REG_BG2CNT |= BGCNT_PRIORITY(2);
    REG_BG2HOFS = 0;
}

void AllmapAllocBgMaps() {
    u32 i;
    u16 j;
    u16 k;

    gAllmapBg0Map = EwramAlloc(0x4000);
    gAllmapBg1Map = EwramAlloc(0x4000);

    for (i = 0; i < 0x2000; i++) {
        gAllmapBg0Map[i] = 0;
        gAllmapBg1Map[i] = 0;
    }

    for (j = 0; j < 4; j++) {
        for (k = 0; k < 2; k++) {
            gAllmapBg0MapBlocks[j * 2 + k] = gAllmapBg0Map + (j * 2 + k) * 0x400;
            gAllmapBg1MapBlocks[j * 2 + k] = gAllmapBg1Map + (j * 2 + k) * 0x400;
        }
    }
}

void AllmapDimPalette10() {
    s32 i;

    for (i = 0; i < 32; i++) {
        FadeSetPaletteExcluded(i, 1);
    }

    FadeSetPaletteExcluded(10, 0);
    FadeToAmount(FADE_MODE_BLACK, 16, 16);
}

void AllmapSetBlend(s16 a) {
    SetBlendAlpha(a, 16 - a);
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
    gUnk_097A2ED8, 32768, 0, gUnk_09849898, 512, 0, gUnk_097AAED8, 16032, 16, 9
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
    { 611584, 339200, 4, 0 },
    { 619264, 343296, 3, 0 },
    { 626944, 347392, 2, 0 },
    { 634624, 351488, 1, 0 },
    { 642304, 355584, 2, 0 },
    { 649984, 359680, 3, 0 },
    { 657664, 363776, 4, 0 },
    { 763904, 389632, 0, 0 },
    { 759552, 398336, 0, 0 },
    { 754688, 405760, 0, 0 },
    { 747264, 411904, 0, 0 },
    { 739072, 416768, 0, 0 },
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
        { gSor1bb00Frames, gSor1bb00Anims, gSor1bb00Tiles, 0, 0 },
        { gSor1ff00Frames, gSor1ff00Anims, gSor1ff00Tiles, 0, 0 },
        { gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0, 0 },
        { gSor1ll00Frames, gSor1ll00Anims, gSor1ll00Tiles, 0, 0 },
        { gSor1bl00Frames, gSor1bl00Anims, gSor1bl00Tiles, 0, 0 },
    },
    {
        { gSor1bb01Frames, gSor1bb01Anims, gSor1bb01Tiles, 0, 0 },
        { gSor1ff01Frames, gSor1ff01Anims, gSor1ff01Tiles, 0, 0 },
        { gSor1fl01Frames, gSor1fl01Anims, gSor1fl01Tiles, 0, 0 },
        { gSor1ll01Frames, gSor1ll01Anims, gSor1ll01Tiles, 0, 0 },
        { gSor1bl01Frames, gSor1bl01Anims, gSor1bl01Tiles, 0, 0 },
    },
    {
        { gSor1bb02Frames, gSor1bb02Anims, gSor1bb02Tiles, 0, 0 },
        { gSor1ff02Frames, gSor1ff02Anims, gSor1ff02Tiles, 0, 0 },
        { gSor1fl02Frames, gSor1fl02Anims, gSor1fl02Tiles, 0, 0 },
        { gSor1ll02Frames, gSor1ll02Anims, gSor1ll02Tiles, 0, 0 },
        { gSor1bl02Frames, gSor1bl02Anims, gSor1bl02Tiles, 0, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 0, 0 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 0, 0 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 0, 0 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 0, 0 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 0, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 1, 0 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 1, 0 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 1, 0 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 1, 0 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 1, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 2, 0 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 2, 0 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 2, 0 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 2, 0 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 2, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 3, 0 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 3, 0 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 3, 0 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 3, 0 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 3, 0 },
    },
    {
        { gSor1bb03Frames, gSor1bb03Anims, gSor1bb03Tiles, 4, 0 },
        { gSor1ff03Frames, gSor1ff03Anims, gSor1ff03Tiles, 4, 0 },
        { gSor1fl03Frames, gSor1fl03Anims, gSor1fl03Tiles, 4, 0 },
        { gSor1ll03Frames, gSor1ll03Anims, gSor1ll03Tiles, 4, 0 },
        { gSor1bl03Frames, gSor1bl03Anims, gSor1bl03Tiles, 4, 0 },
    },
    {
        { gSor1bb15Frames, gSor1bb15Anims, gSor1bb15Tiles, 2, 0 },
        { gSor1ff15Frames, gSor1ff15Anims, gSor1ff15Tiles, 2, 0 },
        { gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 2, 0 },
        { gSor1ll15Frames, gSor1ll15Anims, gSor1ll15Tiles, 2, 0 },
        { gSor1bl15Frames, gSor1bl15Anims, gSor1bl15Tiles, 2, 0 },
    },
    {
        { gSor1bb10Frames, gSor1bb10Anims, gSor1bb10Tiles, 0, 0 },
        { gSor1ff10Frames, gSor1ff10Anims, gSor1ff10Tiles, 0, 0 },
        { gSor1fl10Frames, gSor1fl10Anims, gSor1fl10Tiles, 0, 0 },
        { gSor1ll10Frames, gSor1ll10Anims, gSor1ll10Tiles, 0, 0 },
        { gSor1bl10Frames, gSor1bl10Anims, gSor1bl10Tiles, 0, 0 },
    },
    {
        { gSor1bb61Frames, gSor1bb61Anims, gSor1bb61Tiles, 0, 0 },
        { gSor1ff61Frames, gSor1ff61Anims, gSor1ff61Tiles, 0, 0 },
        { gSor1fl61Frames, gSor1fl61Anims, gSor1fl61Tiles, 0, 0 },
        { gSor1ll61Frames, gSor1ll61Anims, gSor1ll61Tiles, 0, 0 },
        { gSor1bl61Frames, gSor1bl61Anims, gSor1bl61Tiles, 0, 0 },
    },
};

const u16 gPooSoraSounds[8] = { SONG_SYS_SR_FOOTL, SONG_SYS_SR_FOOTR, SONG_SYS_SR_JUMP, SONG_SYS_SR_LAND, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSUP, SONG_SYS_SR_GRASSJP, 0 };

const u16* gPooBg3MapBlocks[144] = {
    gUnk_09806D98,
    gUnk_09807598,
    gUnk_09808D98,
    gUnk_09809598,
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
    gUnk_09807D98,
    gUnk_09808598,
    gUnk_09809D98,
    gUnk_0980A598,
    gUnk_0980BD98,
    gUnk_0980C598,
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
    gUnk_0980AD98,
    gUnk_0980B598,
    gUnk_0980CD98,
    gUnk_0980D598,
    gUnk_0980ED98,
    gUnk_0980F598,
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
    gUnk_0980DD98,
    gUnk_0980E598,
    gUnk_0980FD98,
    gUnk_09810598,
    gUnk_09811D98,
    gUnk_09812598,
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
    gUnk_09810D98,
    gUnk_09811598,
    gUnk_09812D98,
    gUnk_09813598,
    gUnk_09814D98,
    gUnk_09815598,
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
    gUnk_09813D98,
    gUnk_09814598,
    gUnk_09815D98,
    gUnk_09816598,
    gUnk_09817D98,
    gUnk_09818598,
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
    gUnk_09816D98,
    gUnk_09817598,
    gUnk_09818D98,
    gUnk_09819598,
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
    gUnk_09819D98,
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
    gUnk_0981A598,
    gUnk_0981AD98,
    gUnk_0981CD98,
    gUnk_0981D598,
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
    gUnk_0981B598,
    gUnk_0981BD98,
    gUnk_0981DD98,
    gUnk_0981E598,
    gUnk_0981FD98,
    gUnk_09820598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_0981ED98,
    gUnk_0981F598,
    gUnk_09820D98,
    gUnk_09821598,
    gUnk_09822D98,
    gUnk_09823598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_09821D98,
    gUnk_09822598,
    gUnk_09823D98,
    gUnk_09824598,
    gUnk_09825D98,
    gUnk_09826598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_09824D98,
    gUnk_09825598,
    gUnk_09826D98,
    gUnk_09827598,
    gUnk_09828D98,
    gUnk_09829598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_09827D98,
    gUnk_09828598,
    gUnk_09829D98,
    gUnk_0982A598,
    gUnk_0982BD98,
    gUnk_0982C598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_0982AD98,
    gUnk_0982B598,
    gUnk_0982CD98,
    gUnk_0982D598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_0982DD98,
    gUnk_0982E598,
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
    gUnk_0981C598,
    gUnk_0981C598,
    gUnk_08125E24,
    gUnk_08125E24,
};

const u16* gPooBg2MapBlocks[144] = {
    gUnk_08125E24,
    gUnk_0982ED98,
    gUnk_0982F598,
    gUnk_0982FD98,
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
    gUnk_09830598,
    gUnk_09830D98,
    gUnk_09831598,
    gUnk_09831D98,
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
    gUnk_09832598,
    gUnk_09832D98,
    gUnk_09833598,
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
    gUnk_09833D98,
    gUnk_09834598,
    gUnk_09834D98,
    gUnk_09835598,
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
    gUnk_09835D98,
    gUnk_09836598,
    gUnk_09836D98,
    gUnk_09837598,
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
    gUnk_09837D98,
    gUnk_09838598,
    gUnk_09838D98,
    gUnk_09839598,
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
    gUnk_09839D98,
    gUnk_0983A598,
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

const BosMapanimeDef gPooMapanimeDef0 = { sPooMapanimeFrames0, 4, 0, gUnk_097B4578, 0x2080, 0x0240, 0x0400, 0, 3 };

const BosMapanimeDef gPooMapanimeDef1 = { sPooMapanimeFrames1, 4, 0, gUnk_097B5418, 0x3880, 0x0240, 0x0400, 0, 3 };

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
    { gUnk_09EF5CB0, gUnk_09EF5CAC, gUnk_09742FD8, 0, 0 },
    { gUnk_09EF5CB8, gUnk_09EF5CB4, gUnk_097430EC, 0, 0 },
    { gUnk_09EF5CDC, gUnk_09EF5CBC, gUnk_09743262, 0, 0 },
    { gUnk_09EF5D00, gUnk_09EF5CE0, gUnk_09743ADA, 0, 0 },
};

const PooGfxDesc gPooPigletGfxDescs[4] = {
    { gUnk_09EF5CAC, 1, 0 },
    { gUnk_09EF5CB4, 1, 0 },
    { gUnk_09EF5CBC, 8, 0 },
    { gUnk_09EF5CE0, 8, 0 },
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
    { gRabbitFl00Anims, gRabbitFl00Frames, gRabbitFl00Tiles, 0, 0 },
    { gRabbitFl00Anims, gRabbitFl00Frames, gRabbitFl00Tiles, 1, 0 },
    { gRabbitFl00Anims, gRabbitFl00Frames, gRabbitFl00Tiles, 2, 0 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 0, 0 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 2, 0 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 3, 0 },
    { gRabbitBl00Anims, gRabbitBl00Frames, gRabbitBl00Tiles, 4, 0 },
};

const PooGfxDesc gPooRabbitGfxDescs[2] = {
    { gRabbitFl00Frames, 14, 0 },
    { gRabbitBl00Frames, 15, 0 },
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
    { gTiggerFl00Anims, gTiggerFl00Frames, gTiggerFl00Tiles, 0, 0 },
    { gTiggerFl01Anims, gTiggerFl01Frames, gTiggerFl01Tiles, 0, 0 },
    { gTiggerFl02Anims, gTiggerFl02Frames, gTiggerFl02Tiles, 0, 0 },
    { gTiggerBl02Anims, gTiggerBl02Frames, gTiggerBl02Tiles, 0, 0 },
};

const PooGfxDesc gPooTiggerGfxDescs[4] = {
    { gTiggerFl00Frames, 1, 0 },
    { gTiggerFl01Frames, 9, 0 },
    { gTiggerFl02Frames, 8, 0 },
    { gTiggerBl02Frames, 8, 0 },
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
#if defined(VERSION_US)
    { gUnk_09760D00, 5, 0, gUnkUs_09EF62B4, gUnkUs_09EF629C, gUnk_09849E78 },
    { gUnk_09761824, 11, 0, gUnkUs_09EF62E4, gUnkUs_09EF62B8, gUnk_09849E98 },
    { gUnk_09762542, 24, 0, gUnkUs_09EF6348, gUnkUs_09EF62E8, gUnk_09849EB8 },
    { gUnk_097634D0, 3, 0, gUnkUs_09EF6358, gUnkUs_09EF634C, gUnk_09849ED8 },
    { gUnk_09763B54, 9, 0, gUnkUs_09EF6380, gUnkUs_09EF635C, gUnk_09849EF8 },
    { gUnk_09764BB8, 2, 0, gUnkUs_09EF638C, gUnkUs_09EF6384, gUnk_09849F18 },
    { gUnk_09765012, 6, 0, gUnkUs_09EF63AC, gUnkUs_09EF6394, gUnk_09849F38 },
    { gUnk_0976626E, 6, 0, gUnkUs_09EF63C8, gUnkUs_09EF63B0, gUnk_09849F38 },
    { gUnk_09767562, 10, 0, gUnkUs_09EF63F4, gUnkUs_09EF63CC, gUnk_09849F58 },
    { gUnk_09769416, 10, 0, gUnkUs_09EF6420, gUnkUs_09EF63F8, gUnk_09849F58 },
#elif defined(VERSION_JP)
    { gUnk_09760D00, 5, 0, gUnkJp_09ECD6A0, gUnkJp_09ECD688, gUnk_09849E78 },
    { gUnk_09761824, 11, 0, gUnkJp_09ECD6D0, gUnkJp_09ECD6A4, gUnk_09849E98 },
    { gUnk_09762542, 24, 0, gUnkJp_09ECD734, gUnkJp_09ECD6D4, gUnk_09849EB8 },
    { gUnk_097634D0, 3, 0, gUnkJp_09ECD744, gUnkJp_09ECD738, gUnk_09849ED8 },
    { gUnk_09763B54, 9, 0, gUnkJp_09ECD76C, gUnkJp_09ECD748, gUnk_09849EF8 },
    { gUnk_09764BB8, 2, 0, gUnkJp_09ECD778, gUnkJp_09ECD770, gUnk_09849F18 },
    { gUnk_09765012, 6, 0, gUnkJp_09ECD798, gUnkJp_09ECD780, gUnk_09849F38 },
    { gUnk_0976626E, 6, 0, gUnkJp_09ECD7B4, gUnkJp_09ECD79C, gUnk_09849F38 },
    { gUnk_09767562, 10, 0, gUnkJp_09ECD7E0, gUnkJp_09ECD7B8, gUnk_09849F58 },
    { gUnk_09769416, 10, 0, gUnkJp_09ECD80C, gUnkJp_09ECD7E4, gUnk_09849F58 },
#else
    { gUnk_09760D00, 5, 0, gUnkEu_09F816AC, gUnkEu_09F81694, gUnk_09849E78 },
    { gUnk_09761824, 11, 0, gUnkEu_09F816DC, gUnkEu_09F816B0, gUnk_09849E98 },
    { gUnk_09762542, 24, 0, gUnkEu_09F81740, gUnkEu_09F816E0, gUnk_09849EB8 },
    { gUnk_097634D0, 3, 0, gUnkEu_09F81750, gUnkEu_09F81744, gUnk_09849ED8 },
    { gUnk_09763B54, 9, 0, gUnkEu_09F81778, gUnkEu_09F81754, gUnk_09849EF8 },
    { gUnk_09764BB8, 2, 0, gUnkEu_09F81784, gUnkEu_09F8177C, gUnk_09849F18 },
    { gUnk_09765012, 6, 0, gUnkEu_09F817A4, gUnkEu_09F8178C, gUnk_09849F38 },
    { gUnk_0976626E, 6, 0, gUnkEu_09F817C0, gUnkEu_09F817A8, gUnk_09849F38 },
    { gUnk_09767562, 10, 0, gUnkEu_09F817EC, gUnkEu_09F817C4, gUnk_09849F58 },
    { gUnk_09769416, 10, 0, gUnkEu_09F81818, gUnkEu_09F817F0, gUnk_09849F58 },
#endif
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
    { gTrap01Bb00Frames, gTrap01Bb00Anims, gTrap01Bb00Tiles, 0, { 0, 0, 0 } },
    { gTrap01Ff00Frames, gTrap01Ff00Anims, gTrap01Ff00Tiles, 0, { 0, 0, 0 } },
    { gTrap01Fl00Frames, gTrap01Fl00Anims, gTrap01Fl00Tiles, 0, { 0, 0, 0 } },
    { gTrap01Ll00Frames, gTrap01Ll00Anims, gTrap01Ll00Tiles, 0, { 0, 0, 0 } },
    { gTrap01Bl00Frames, gTrap01Bl00Anims, gTrap01Bl00Tiles, 0, { 0, 0, 0 } },
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

#ifdef VERSION_EU
u8* gAllmapFloorTilesByLanguage[5] = {
    gUnk_097B7218,
    gUnkEu_097966A0,
    gUnkEu_09799760,
    gUnkEu_09798720,
    gUnkEu_097976E0,
};

u8* gAllmapRikuFloorTilesByLanguage[5] = {
    gUnkEu_0979A7A0,
    gUnkEu_0979B7E0,
    gUnkEu_0979E8A0,
    gUnkEu_0979D860,
    gUnkEu_0979C820,
};
#endif
