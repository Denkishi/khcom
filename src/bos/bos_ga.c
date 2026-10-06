/**
 * bos_ga.c
 * Guard Armor Boss
 */

#include "bos_ga.h"
#include "anim.h"
#include "sprites_worldinspect.h"
#include "sprites_room.h"
#include "chara_types.h"
#include "chara_api.h"
#include "btl_api.h"
#include "songs.h"
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "boss_background_types.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "card_api.h"
#include "engine_math.h"
#include "ga_types.h"
#include "gba/defines.h"
#include "m4a_song.h"
#include "obj.h"
#include "obj_api.h"
#include "room_data.h"
#include "task_descriptors.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "sprite_palettes.h"

static const EmyKind sBosGaEmyKind =
{32, 100, 16, 16, 0, 100, EMY_KIND_FLAG_NO_COLLIDER}
;

static const GaEntryDef sGaEntryDefs[6] = {
    {256, 0, 0, -15872, 0, 0, gBosGaTorsoTiles, gBosGaTorsoAnims, gBosGaTorsoFrames, 8},
    {256, -2560, 2048, -25088, 0, 0, gBosGaHeadTiles, gBosGaHeadAnims, gBosGaHeadFrames, 6},
    {256, 2560, 5632, -14848, 0, 0, gBosGaNearHandTiles, gBosGaNearHandAnims, gBosGaNearHandFrames, 7},
    {256, -11264, -3328, -12288, 0, 0, gBosGaFarHandTiles, gBosGaFarHandAnims, gBosGaFarHandFrames, 7},
    {256, 3840, 512, -2048, 0, 0, gBosGaNearFootTiles, gBosGaNearFootAnims, gBosGaNearFootFrames, 1},
    {256, -3328, -1792, -2048, 0, 0, gBosGaFarFootTiles, gBosGaFarFootAnims, gBosGaFarFootFrames, 1},
};

static const BosMapConfig sBosMapConfig =
{gBosGaBgTiles, 16352, gBosGaBgPalette, 320, {gBosGaBgTopLeftMap, gBosGaBgTopRightMap, gBosGaBgBottomLeftMap, gBosGaBgBottomRightMap}}
;

static const s32 sBosGaTanTable[32] = {
    6,
    12,
    18,
    25,
    31,
    37,
    44,
    50,
    57,
    64,
    70,
    77,
    84,
    91,
    98,
    106,
    113,
    121,
    128,
    136,
    145,
    153,
    162,
    171,
    180,
    189,
    199,
    210,
    220,
    232,
    243,
    256,
};

TaskDesc gTaskDescBosGa = {
    "task_bos_ga",
    (TaskInitFunc)task_bos_ga_0,
    (TaskUpdateFunc)task_bos_ga_1,
    (TaskDrawFunc)task_bos_ga_2,
    (TaskDestroyFunc)task_bos_ga_3,
    sizeof(GaWork),
};

static GaWork* sGaWork;

u16 BosGaAtan(s32 ratio) {
    u16 i;

    if (ratio == 0x100) {
        return 0x20;
    }

    i = 0;

    if (ratio >= sBosGaTanTable[0]) {
        do {
            i++;

            if (i > 0x3F) {
                break;
            }
        } while (ratio >= sBosGaTanTable[i]);
    }

    return i;
}

s32 BosGaGetAngle(s32 x0, s32 y0, s32 x1, s32 y1) {
    s32 dx;
    s32 dy;
    s32 tmp;
    s32 q;
    u16 t;

    dx = x1 - x0;
    dy = y1 - y0;

    if (dx >= 0) {
        q = 0;

        if (dy < 0) {
            q = 3;
            tmp = dx;
            dx = -dy;
            dy = tmp;
        }
    } else if (dy >= 0) {
        q = 1;
        tmp = dx;
        dx = dy;
        dy = -tmp;
    } else {
        q = 2;
        dx = -dx;
        dy = -dy;
    }

    if (dy > dx) {
        if (dy == 0) {
            return 0;
        }

        dx <<= 8;
        t = 0x40 - BosGaAtan(dx / dy);
    } else {
        if (dx == 0) {
            return 0;
        }

        dy <<= 8;
        t = BosGaAtan(dy / dx);
    }

    return (t + (q << 6) + 0x40) & 0xFF;
}

void BosGaEntryUpdateFall(GaEntryWork* work) {
    work->vz += 0x4C;
    work->actor.z += work->vz;

    if (work->actor.z > 0) {
        if (work->vz > 0x500) {
            m4aSongNumStart(SONG_BTL_IRON_GIMICBREAK);
        }

        work->actor.z = 0;
        work->vz = -work->vz / 2;
    }

    if (work->vx > 0) {
        work->actor.x += work->vx;
        work->vx -= 0x11;

        if (work->vx < 0) {
            work->vx = 0;
        }
    } else if (work->vx < 0) {
        work->actor.x += work->vx;
        work->vx += 0x11;

        if (work->vx > 0) {
            work->vx = 0;
        }
    }

    if (work->vy > 0) {
        work->actor.y += work->vy / 2;
        work->vy -= 0x11;

        if (work->vy < 0) {
            work->vy = 0;
        }
    } else if (work->vy < 0) {
        work->actor.y += work->vy / 2;
        work->vy += 0x11;

        if (work->vy > 0) {
            work->vy = 0;
        }
    }

    ClampBattlePosition(&work->actor.x, &work->actor.y, -0x18, -0x0C);
}

void BosGaRequestState(GaWork* work, s32 state) {
    if (work->nextState != 11 && work->state != 11) {
        work->nextState = state;
        work->flags |= GA_FLAG_STATE_REQUESTED;
    }
}

s32 BosGaEntryOffsetX(GaWork* work, s16 i) {
    s32 v;

    v = sGaEntryDefs[i].offsetX;

    if (work->flipped) {
        v = -v;
    }

    return v;
}

s32 BosGaEntryOffsetY(GaWork* work, s16 i) {
    return sGaEntryDefs[i].offsetY;
}

s32 BosGaEntryHomeX(GaWork* work, s16 i) {
    return BosGaEntryOffsetX(work, i) + gBtlWork->bossX;
}

s32 BosGaEntryHomeY(GaWork* work, s16 i) {
    return BosGaEntryOffsetY(work, i) + gBtlWork->bossY;
}

s32 BosGaEntryHomeZ(GaWork* work, s16 i) {
    return sGaEntryDefs[i].offsetZ + gBtlWork->bossZ;
}

void BosGaEntryResetHome(GaWork* work, s32 i) {
    GaEntryWork* e;
    s32 v;

    e = &work->entries[i];

    if (!work->flipped) {
        e->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;
    } else {
        e->actor.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
    }

    e->offsetX = BosGaEntryOffsetX(work, i);
    e->offsetY = BosGaEntryOffsetY(work, i);
    e->baseX = BosGaEntryHomeX(work, i);
    e->baseY = BosGaEntryHomeY(work, i);
    e->baseZ = BosGaEntryHomeZ(work, i);
    v = sGaEntryDefs[i].x2;

    if (work->flipped) {
        v = -v;
    }

    e->x2 = v;
    e->y2 = sGaEntryDefs[i].y2;
}

void BosGaUpdateFacing(GaWork* work) {
    s32 flip;
    u32 i;

    flip = 0;

    if (gBtlWork->bossX <= gBtlWork->actor->x) {
        flip = 1;
    }

    if (work->flipped != flip) {
        work->flipped = flip;

        for (i = 0; i <= 5; i++) {
            BosGaEntryResetHome(work, i);
        }
    }
}

void BosGaEntryInit(GaWork* work, u32 i, s32 assemble) {
    GaEntryWork* e;
    void* p;

    e = &work->entries[i];
    e->index = i;
    e->bobZ = 0;
    e->bobAngle = GetRandom();
    e->mode = 0;
    e->vz = 0;
    e->rotation = 0;
    e->flags = 0;
    e->counter = 0;
    e->vx = e->vy = 0;
    BosGaEntryResetHome(work, i);
    e->unk_130 = 0;
    e->unk_134 = 0;
    e->unk_138 = 0;
    e->orbitAngle = 0;

    if (assemble != 0) {
        if (i != 1) {
            e->baseX -= (GetRandom() & 0x1F) << 8;
            e->baseY -= (GetRandom() & 0x1F) << 8;
        }

        e->baseZ -= 0xA000;
    }

    InitEnemyBtlObj(&e->actor, &sBosGaEmyKind, e->baseX, e->baseY, e->baseZ);
    SetEnemyHpFromStats(&e->actor, sBosGaEmyKind.id, sGaEntryDefs[i].hpScale);
    e->actor.radiusY = 0x10;

    if (i == 0) {
        e->actor.flags |= 0x400;
    } else {
        e->actor.flags |= BTLOBJ_FLAG_NEVER_USES_CARDS;
    }

    e->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;

    switch (i) {
    case 4:
    case 5:
        e->flags |= GA_ENTRY_FLAG_NO_BOB;
        break;
    }

    TaskPoolInit(&e->tasks, 1);
    TaskCreate(&e->tasks, &gTaskDescBtlShadow, &e->actor);
    p = sGaEntryDefs[i].gfxTable;
    e->tiles = AllocObjTiles(GetMaxSpriteTileBytes(p, sGaEntryDefs[i].spriteCount), sGaEntryDefs[i].owner);
    AnimInit(&e->anim, sGaEntryDefs[i].anims, p);
    AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
    e->gfx = AnimGetGfx(&e->anim);

    if (i == 0) {
        work->tiles = AllocObjTiles(GetMaxSpriteTileBytes(gBosGaCollarFrames, 4), gBosGaCollarTiles);
        AnimInit(&work->anim, gBosGaCollarAnims, gBosGaCollarFrames);
        AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
        work->gfx = AnimGetGfx(&work->anim);
    }

    ColliderInit(&e->actor.collider, 8, 8, 0x10);
}

void BosGaEntryRelease(GaEntryWork* work) {
    if (!(work->flags & GA_ENTRY_FLAG_RELEASED)) {
        ColliderUnregister(&work->actor.collider);
        ReleaseObjTiles(work->tiles);
        ReleaseEnemyBtlObj(&work->actor);
        TaskPoolDestroy(&work->tasks);
        work->flags |= GA_ENTRY_FLAG_RELEASED;
    }
}

void BosGaReleaseBody() {
    BosGaEntryRelease(&sGaWork->entries[1]);
    BosGaEntryRelease(&sGaWork->entries[0]);
}

void BosGaEntryDraw(GaWork* work, GaEntryWork* entry) {
    ObjAffine* f;
    u16 g;
    void* pal;
    u16 sx;
    u16 sy;
    GaEntryWork* q;

    if (entry->flags & GA_ENTRY_FLAG_RELEASED) {
        return;
    }

    f = AllocObjAffineAngle(entry->rotation, 1);
    q = entry;
    g = GetBattleSpritePriorityFlags(entry->actor.y);

    if (work->flipped == 1) {
        g |= 1;
    }

    if (StepHitFlash(&entry->actor)) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    WorldToScreen(&sx, &sy, q->actor.x, q->actor.y, q->actor.z);
    DrawSprite(sx + entry->x2, sy + entry->y2, entry->gfx, entry->tiles, pal, f, g,
               0xEFFC - ((q->actor.y >> 8) << 2));

    if (entry->index == 0 && work->state != 7 && work->state != 8 && work->state != 9) {
        DrawSprite(sx + entry->x2, sy + entry->y2, work->gfx, work->tiles, pal, f, g,
                   0xEFFC - ((q->actor.y >> 8) << 2));
    }

    TaskPoolDraw(&entry->tasks);
}

u8 BosGaUpdateAssemble(GaWork* work) {
    u32 i = 0;
    GaEntryWork* e;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        work->timer = 60;
        work->step = i;
        work->statePhase = 1;
        break;
    case 1:
        switch (work->step) {
        case 0:
            work->timer--;

            if (work->timer <= 0) {
                work->step = 1;
            }

            break;
        case 1:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];
                e->baseVx = 0;
                e->baseVy = 0;
                e->baseVz = 1;
                e->counter = i * 8;

                if (i == 1) {
                    e->rotation = 0;
                } else {
                    e->rotation = GetRandom() % 100;
                }
            }

            gBtlWork->bossZ = -0x2000;
            work->timer = 5;
            work->step = 2;
            break;
        case 2:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i != 1) {
                    if (e->counter > 0) {
                        e->counter--;
                    } else if (e->counter == 0) {
                        e->baseX += e->baseVx;
                        e->baseY += e->baseVy;
                        e->baseZ += e->baseVz;

                        if (e->baseVz > 0) {
                            e->baseVz += 76;

                            if (e->baseZ > -0x800) {
                                s32 t = BosGaEntryHomeZ(work, i);
                                e->baseVz = (t - e->baseZ) / 15;
                                e->baseAccelZ = -((t - e->baseZ) * 2) / 900;
                                e->baseVx = (BosGaEntryHomeX(work, i) - e->baseX) / 30;
                                e->baseVy = (BosGaEntryHomeY(work, i) - e->baseY) / 30;
                                e->rotationFixed = e->rotation << 8;
                                e->landSteps = 30;
                                m4aSongNumStart(SONG_SND_388);
                            }
                        } else {
                            ApproachValue(&e->rotationFixed, 0x10000, e->landSteps);
                            e->rotation = e->rotationFixed >> 8;
                            e->baseVz += e->baseAccelZ;
                            e->landSteps--;

                            if ((s16)e->landSteps <= 0) {
                                BosGaEntryResetHome(work, i);
                                e->rotation = 0;
                                e->baseVz = 0;
                                e->counter = -1;
                                work->timer--;

                                if (work->timer <= 0) {
                                    work->timer = 60;
                                    work->step = 3;
                                }
                            }
                        }
                    }
                }
            }

            break;
        case 3:
            ApproachValue(&gBtlWork->bossZ, 0, work->timer);

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i != 1) {
                    ApproachValue(&e->baseZ, BosGaEntryHomeZ(work, i), work->timer);
                }
            }

            work->timer--;

            if (work->timer <= 0) {
                work->timer = 0;
                work->vz = 256;
                work->step = 4;
            }

            break;
        case 4:
            for (i = 0; i <= 5; i++) {
                switch (i) {
                case 0:
                case 2:
                case 3:
                    work->entries[i].baseZ += work->vz;
                    break;
                }
            }

            work->vz -= 10;

            if (work->vz > 0) {
                work->timer++;
            } else {
                work->timer--;

                if (work->timer <= 0) {
                    work->timer = 60;
                    work->step = 5;
                }
            }

            break;
        case 5:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i == 1) {
                    ApproachValue(&e->baseZ, BosGaEntryHomeZ(work, i), work->timer);
                }
            }

            work->timer--;

            if (work->timer <= 0) {
                work->step = 6;
            }

            break;
        }

        break;
    case 2:
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateIdle(GaWork* work) {
    s32 d;
    s32 dx;
    s32 dy;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        work->timer = 15;
        break;
    case 1:
        if (gBtlWork->phase == 0) {
            break;
        }

        work->timer--;

        if (work->timer > 0) {
            break;
        }

        dx = gBtlWork->actor->x - gBtlWork->bossX;
        dx = (dx * dx) >> 8;
        dy = gBtlWork->actor->y - gBtlWork->bossY;
        dy = (dy * dy) >> 8;
        d = (dx + dy) >> 8;

        if (d <= 0xE0F) {
            if (!work->attackToggle) {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                } else {
                    BosGaRequestState(work, 2);
                }
            } else {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 2);
                } else {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                }
            }
        } else if (d <= 0x270F) {
            if (!work->attackToggle) {
                if (GetRandom() & 1) {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                } else {
                    BosGaRequestState(work, 2);
                }
            } else {
                if (GetRandom() & 1) {
                    BosGaRequestState(work, 2);
                } else {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                }
            }
        } else {
            if (!work->attackToggle) {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 2);
                } else {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                }
            } else {
                if (GetRandom() % 3 != 0) {
                    BosGaRequestState(work, 1);
                    RequestEnemyCardUse(&work->entries[0].actor);
                } else {
                    BosGaRequestState(work, 2);
                }
            }
        }

        break;
    case 2:
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateWalk(GaWork* work) {
    u32 i;
    GaEntryWork* e;
    s32 x, y;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    for (i = 0; i <= 5; i++) {
        e = &work->entries[i];

        switch (work->statePhase) {
        case 0: {
            s32 d;

            if (e->index != 0) {
                break;
            }

            x = gBtlWork->actor->x;
            y = gBtlWork->actor->y;

            if (!work->attackToggle) {
                if (x > e->baseX) {
                    x -= 0x2800;

                    if (x < 0) {
                        x += 0x5000;
                    }
                } else {
                    x += 0x2800;

                    if (x > 0x10000) {
                        x -= 0x5000;
                    }
                }
            } else {
                if (x > e->baseX) {
                    x -= 0x6400;

                    if (x < 0) {
                        x += 0xC800;
                    }
                } else {
                    x += 0x6400;

                    if (x > 0x10000) {
                        x -= 0xC800;
                    }
                }

                y = ((GetRandom() & 80) + 296) << 8;
            }

            work->vx = ((x - e->baseX) * (x - e->baseX)) >> 8;
            work->vy = ((y - e->baseY) * (y - e->baseY)) >> 8;
            d = (work->vx + work->vy) >> 8;
            work->timer = 15;
            work->stepsLeft = d / 4900 + 2;
            work->vz = 768;
            work->vzDelta = work->vz * 2 / work->timer;
            work->angle = BosGaGetAngle(e->baseX, e->baseY, x, y);
            work->vx = (x - e->baseX) / ((work->stepsLeft - 1) * work->timer * 2);

            if (work->vx > 640) {
                work->vx = 640;
            } else if (work->vx < -640) {
                work->vx = -640;
            }

            work->vy = (y - e->baseY) / ((work->stepsLeft - 1) * work->timer * 2);

            if (work->vy > 640) {
                work->vy = 640;
            } else if (work->vy < -640) {
                work->vy = -640;
            }

            if (work->vy >= 0) {
                work->entries[4].flags |= GA_ENTRY_FLAG_STEPPING;
                work->entries[5].flags &= ~GA_ENTRY_FLAG_STEPPING;
            } else {
                work->entries[4].flags &= ~GA_ENTRY_FLAG_STEPPING;
                work->entries[5].flags |= GA_ENTRY_FLAG_STEPPING;
            }

            BosGaUpdateFacing(work);
            break;
        }
        case 1:
            switch (e->index) {
            case 4:
            case 5: {
                s32 velocity;

                if (!(e->flags & GA_ENTRY_FLAG_STEPPING)) {
                    break;
                }

                velocity = work->vx;
                e->baseX += velocity;

                if (velocity < 0) {
                    if (e->baseX < 0) {
                        e->baseX = 0;
                    }
                } else if (velocity > 0) {
                    if (e->baseX > 0x10000) {
                        e->baseX = 0x10000;
                    }
                }

                velocity = work->vy;
                e->baseY += velocity;

                if (velocity < 0) {
                    if (e->baseY < 0x12800) {
                        e->baseY = 0x12800;
                    }
                } else if (velocity > 0) {
                    if (e->baseY > 0x17800) {
                        e->baseY = 0x17800;
                    }
                }

                e->baseZ -= work->vz;
                work->vz -= work->vzDelta;
                work->timer--;

                if (work->timer <= 0) {
                    if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                        if (e->index == 4) {
                            m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                        } else if (e->index == 5) {
                            m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                        }
                    }

                    work->stepsLeft--;
                    e->baseZ = BosGaEntryHomeZ(work, i);

                    if (work->stepsLeft > 0) {
                        if (work->stepsLeft == 1) {
                            work->timer = 15;
                        } else {
                            work->timer = 30;
                        }

                        work->vz = 768;
                        work->vzDelta = work->vz * 2 / work->timer;
                        work->entries[5].flags ^= GA_ENTRY_FLAG_STEPPING;
                        work->entries[4].flags ^= GA_ENTRY_FLAG_STEPPING;
                    } else {
                        BosGaRequestState(work, 1);
                    }
                }

                break;
            }
            case 0: {
                s32 a, b, d;
                a = work->entries[4].baseX - work->entries[4].offsetX;
                b = work->entries[5].baseX - work->entries[5].offsetX;
                d = a - b >= 0 ? a - b : b - a;
                e->baseX = (a < b ? d + 1 : d) ? a : b;
                gBtlWork->bossX = e->baseX;
                a = work->entries[4].baseY - work->entries[4].offsetY;
                b = work->entries[5].baseY - work->entries[5].offsetY;
                d = a - b >= 0 ? a - b : b - a;
                e->baseY = (a < b ? d + 1 : d) ? a : b;
                gBtlWork->bossY = e->baseY;
                break;
            }
            default:
                BosGaEntryResetHome(work, i);
                break;
            }

            break;
        case 2:
            switch (e->index) {
            case 4:
            case 5:
                e->flags &= ~GA_ENTRY_FLAG_STEPPING;
                break;
            }

            BosGaEntryResetHome(work, i);
            break;
        }
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateStomp(GaWork* work) {
    u32 i = 0;
    GaEntryWork* e;
    s32 velocity;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
            for (; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 4:
                    e->flags |= GA_ENTRY_FLAG_STEPPING;
                    break;
                case 5:
                    e->flags &= ~GA_ENTRY_FLAG_STEPPING;
                    break;
                case 0:
                    work->timer = 10;
                    work->stepsLeft = 5;
                    work->vz = 1024;
                    work->vzDelta = work->vz * 2 / work->timer;
                    work->step = 0;
                    BosGaUpdateFacing(work);
                    break;
                }
            }

            break;
    case 1:
        switch (work->step) {
        case 0:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 4:
                case 5:
                    if (!(e->flags & GA_ENTRY_FLAG_STEPPING)) {
                        break;
                    }

                    e->baseZ -= work->vz;
                    work->vz -= work->vzDelta;
                    work->timer--;

                    if (work->timer <= 0) {
                        if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                            if (e->index == 4) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                            } else if (e->index == 5) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                            }
                        }

                        work->stepsLeft--;
                        e->baseZ = BosGaEntryHomeZ(work, i);

                        if (work->stepsLeft > 0) {
                            if (work->stepsLeft == 1) {
                                work->timer = 10;
                            } else {
                                work->timer = 20;
                            }

                            work->vz = 896;
                            work->vzDelta = work->vz * 2 / work->timer;
                            work->entries[5].flags ^= GA_ENTRY_FLAG_STEPPING;
                            work->entries[4].flags ^= GA_ENTRY_FLAG_STEPPING;
                        } else {
                            work->step = 1;
                        }
                    }

                    break;
                default:
                    BosGaEntryResetHome(work, i);
                    break;
                }
            }

            break;
        case 1:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 0:
                    work->step = 2;
                    break;
                case 4:
                case 5:
                    e->flags &= ~GA_ENTRY_FLAG_STEPPING;
                    break;
                }

                BosGaEntryResetHome(work, i);
            }

            break;
        case 2:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 4:
                    e->flags |= GA_ENTRY_FLAG_STEPPING;
                    break;
                case 5:
                    e->flags &= ~GA_ENTRY_FLAG_STEPPING;
                    break;
                case 0:
                    work->timer = 10;
                    work->stepsLeft = 5;
                    work->vz = 1024;
                    work->vzDelta = work->vz * 2 / work->timer;
                    work->angle = BosGaGetAngle(e->baseX, e->baseY, gBtlWork->actor->x, gBtlWork->actor->y);
                    work->step = 3;
                    break;
                }
            }

            break;
        case 3:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 4:
                case 5:
                    if (!(e->flags & GA_ENTRY_FLAG_STEPPING)) {
                        break;
                    }

                    velocity = gSineTable[work->angle] * 972 >> 8;
                    e->baseX += velocity;

                    if (velocity < 0) {
                        if (e->baseX < 0) {
                            e->baseX = 0;
                        }
                    } else if (velocity > 0) {
                        if (e->baseX > 0x10000) {
                            e->baseX = 0x10000;
                        }
                    }

                    velocity = -gSineTable[work->angle + 64] * 972 >> 8;
                    e->baseY += velocity;

                    if (velocity < 0) {
                        if (e->baseY < 0x12800) {
                            e->baseY = 0x12800;
                        }
                    } else if (velocity > 0) {
                        if (e->baseY > 0x17800) {
                            e->baseY = 0x17800;
                        }
                    }

                    e->baseZ -= work->vz;
                    work->vz -= work->vzDelta;
                    work->timer--;

                    if (work->timer <= 0) {
                        if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                            if (ApplyAttackBox(226, e->actor.x, e->actor.y, e->actor.z, 16, 16, 16)) {
                                m4aSongNumStart(SONG_BTL_IRON_HIT00);
                            } else if (e->index == 4) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                            } else if (e->index == 5) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                            }
                        }

                        work->stepsLeft--;
                        e->baseZ = BosGaEntryHomeZ(work, i);

                        if (work->stepsLeft > 0) {
                            if (work->stepsLeft == 1) {
                                work->timer = 10;
                            } else {
                                work->timer = 20;
                            }

                            work->vz = 896;
                            work->vzDelta = work->vz * 2 / work->timer;
                            work->entries[5].flags ^= GA_ENTRY_FLAG_STEPPING;
                            work->entries[4].flags ^= GA_ENTRY_FLAG_STEPPING;
                        } else {
                            work->step = 4;
                        }
                    }

                    break;
                }
            }

            break;
        case 4:
            work->timer = 20;
            work->stepsLeft = 6;
            work->vz = 1024;
            work->vzDelta = work->vz * 2 / work->timer;
            work->step = 5;

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 4:
                    e->flags |= GA_ENTRY_FLAG_STEPPING;
                    e->baseVx = (BosGaEntryHomeX(work, i) - e->baseX) / (work->stepsLeft * work->timer / 2);
                    e->baseVy = (BosGaEntryHomeY(work, i) - e->baseY) / (work->stepsLeft * work->timer / 2);
                    break;
                case 5:
                    e->flags &= ~GA_ENTRY_FLAG_STEPPING;
                    e->baseVx = (BosGaEntryHomeX(work, i) - e->baseX) / (work->stepsLeft * work->timer / 2);
                    e->baseVy = (BosGaEntryHomeY(work, i) - e->baseY) / (work->stepsLeft * work->timer / 2);
                    break;
                }
            }

            break;
        case 5:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (e->index) {
                case 4:
                case 5:
                    if (!(e->flags & GA_ENTRY_FLAG_STEPPING)) {
                        break;
                    }

                    e->baseX += e->baseVx;

                    if (e->baseVx < 0) {
                        if (e->baseX < 0) {
                            e->baseX = 0;
                        }
                    } else if (e->baseVx > 0) {
                        if (e->baseX > 0x10000) {
                            e->baseX = 0x10000;
                        }
                    }

                    e->baseY += e->baseVy;

                    if (e->baseVy < 0) {
                        if (e->baseY < 0x12800) {
                            e->baseY = 0x12800;
                        }
                    } else if (e->baseVy > 0) {
                        if (e->baseY > 0x17800) {
                            e->baseY = 0x17800;
                        }
                    }

                    e->baseZ -= work->vz;
                    work->vz -= work->vzDelta;
                    work->timer--;

                    if (work->timer <= 0) {
                        if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                            if (e->index == 4) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTL);
                            } else if (e->index == 5) {
                                m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                            }
                        }

                        work->stepsLeft--;
                        e->baseZ = BosGaEntryHomeZ(work, i);

                        if (work->stepsLeft > 0) {
                            work->timer = 20;
                            work->vz = 896;
                            work->vzDelta = work->vz * 2 / work->timer;
                            work->entries[5].flags ^= GA_ENTRY_FLAG_STEPPING;
                            work->entries[4].flags ^= GA_ENTRY_FLAG_STEPPING;
                        } else {
                            BosGaRequestState(work, 1);
                        }
                    }

                    break;
                }
            }

            break;
        }

        break;
    case 2:
        for (; i <= 5; i++) {
            e = &work->entries[i];

            switch (e->index) {
            case 0:
                ClearBtlObjActionFlags(&e->actor);
                break;
            case 4:
            case 5:
                e->flags &= ~GA_ENTRY_FLAG_STEPPING;
                break;
            }

            BosGaEntryResetHome(work, i);
        }

        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateThrust(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    for (i = 0; i <= 5; i++) {
        e = &work->entries[i];

        switch (work->statePhase) {
        case 0:
            switch (e->index) {
            case 0:
                work->timer = 0;
                work->step = 0;
                break;
            case 2:
            case 3:
                e->flags |= GA_ENTRY_FLAG_NO_BOB;
                break;
            }

            break;
        case 1:
            switch (work->step) {
            case 0:
                if (e->index == 3) {
                    e->baseX = e->baseX + (!work->flipped ? 0x80 : -0x80);
                    work->timer++;

                    if (work->timer > 30) {
                        work->timer = 0;
                        work->step = 1;
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }

                break;
            case 1:
                if (e->index == 3) {
                    e->baseX = e->baseX + (!work->flipped ? -0x300 : 0x300);
                    e->baseY += 0x133;

                    if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                        if (ApplyAttackBox(0xE3, e->actor.x, e->actor.y, e->actor.z, 0x10, 0x10, 0x20)) {
                            m4aSongNumStart(SONG_BTL_IRON_HIT00);
                        }
                    }

                    work->timer++;

                    if (work->timer > 15) {
                        work->timer = 0;
                        work->step = 2;
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }

                break;
            case 2:
                if (e->index == 2) {
                    e->baseX = e->baseX + (!work->flipped ? 0x80 : -0x80);
                    work->timer++;

                    if (work->timer > 30) {
                        work->timer = 0;
                        work->step = 3;
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }

                break;
            case 3:
                if (e->index == 2) {
                    e->baseX = e->baseX + (!work->flipped ? -0x300 : 0x300);
                    e->baseY -= 0x133;

                    if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                        if (ApplyAttackBox(0xE3, e->actor.x, e->actor.y, e->actor.z, 0x10, 0x10, 0x20)) {
                            m4aSongNumStart(SONG_BTL_IRON_HIT00);
                        }
                    }

                    work->timer++;

                    if (work->timer > 15) {
                        BosGaRequestState(work, 1);
                    }
                } else {
                    BosGaEntryResetHome(work, i);
                }

                break;
            }

            break;
        case 2:
            switch (e->index) {
            case 0:
                ClearBtlObjActionFlags(&e->actor);
                break;
            case 2:
            case 3:
                e->flags &= ~GA_ENTRY_FLAG_NO_BOB;
                break;
            }

            BosGaEntryResetHome(work, i);
            break;
        }
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateOrbit(GaWork* work) {
    GaEntryWork* e;
    u32 i;
    s32 t;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    for (i = 0; i <= 5; i++) {
        e = &work->entries[i];

        switch (work->statePhase) {
        case 0:
            switch (e->index) {
            case 0:
                work->step = 0;
                work->timer = 0;
                work->orbitRadius = 0x1E00;
                break;
            case 2:
                e->orbitAngle = 0x80;
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 3:
                e->orbitAngle = !work->flipped ? 0xC0 : 0x40;
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            }

            break;
        case 1:
            switch (work->step) {
            case 0:
                switch (e->index) {
                case 0:
                    work->timer++;

                    if (work->timer > 31) {
                        work->timer = 0;
                        work->step = 1;
                    }

                    break;
                case 2:
                    t = e->orbitAngle;
                    e->orbitAngle = !work->flipped ? t - 1 : t + 1;
                    e->baseX = (gSineTable[e->orbitAngle] * work->orbitRadius >> 8) + work->entries[0].baseX;
                    e->baseY = (-gSineTable[e->orbitAngle + 0x40] * work->orbitRadius >> 8) + work->entries[0].baseY;
                    break;
                case 3:
                    t = e->orbitAngle;
                    e->orbitAngle = !work->flipped ? t + 1 : t - 1;
                    e->baseX = (gSineTable[e->orbitAngle] * work->orbitRadius >> 8) + work->entries[0].baseX;
                    e->baseY = (-gSineTable[e->orbitAngle + 0x40] * work->orbitRadius >> 8) + work->entries[0].baseY;
                    break;
                default:
                    BosGaEntryResetHome(work, i);
                    break;
                }

                break;
            case 1:
                switch (e->index) {
                case 0:
                    work->orbitRadius += 0x59;
                    work->timer++;

                    if (work->timer > 0x7F) {
                        BosGaRequestState(work, 1);
                    }

                    break;
                case 2:
                case 3:
                    e->orbitAngle = e->orbitAngle + 4;

                    if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                        if (ApplyAttackBox(0xE4, e->actor.x, e->actor.y, e->actor.z, 0x10, 0x10, 0x20)) {
                            m4aSongNumStart(SONG_BTL_IRON_HIT00);
                        }
                    }

                    e->baseX = (gSineTable[e->orbitAngle] * work->orbitRadius >> 8) + work->entries[0].baseX;
                    e->baseY = (-gSineTable[e->orbitAngle + 0x40] * work->orbitRadius >> 8) + work->entries[0].baseY;
                    break;
                default:
                    BosGaEntryResetHome(work, i);
                    break;
                }

                break;
            }

            break;
        case 2:
            switch (e->index) {
            case 0:
                ClearBtlObjActionFlags(&e->actor);
                break;
            case 2:
            case 3:
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                break;
            }

            BosGaEntryResetHome(work, i);
            break;
        }
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateJump(GaWork* work) {
    GaEntryWork* e;
    u32 i;
    s32 t;

    e = NULL;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= GA_ENTRY_FLAG_NO_BOB;

            if (i == 0) {
                AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 2, ANIM_FLAG_LOOP);
            }
        }

        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x33;

            if (gBtlWork->bossZ > 0x1800) {
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                if (i <= 3) {
                    BosGaEntryResetHome(work, i);
                }
            }

            break;
        case 1:
            gBtlWork->bossZ = 0;
            work->vx = (gBtlWork->actor->x - gBtlWork->bossX) / 60;
            work->vy = (gBtlWork->actor->y - gBtlWork->bossY) / 60;
            work->vz = 0x600;
            work->step = 2;
            break;
        case 2:
            gBtlWork->bossX += work->vx;
            gBtlWork->bossY += work->vy;
            gBtlWork->bossZ -= work->vz;
            work->vz -= 0x33;

            if (gBtlWork->bossZ > 0) {
                BtlMapStartShake();
                m4aSongNumStart(SONG_BTL_IRON_RUMB);
                ApplyAttackBox(0xE5, gBtlWork->viewX, gBtlWork->viewY, 0, 0x140, 0xF0, 1);
                work->step = 3;
            }

            for (i = 0; i <= 5; i++) {
                BosGaEntryResetHome(work, i);
            }

            break;
        case 3:
            gBtlWork->bossZ = 0;
            work->vz = 0x100;
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ += work->vz;
            t = work->vz - 7;
            work->vz = t;

            if (gBtlWork->bossZ <= 0 && t < 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                if (i <= 3) {
                    BosGaEntryResetHome(work, i);
                }
            }

            break;
        }

        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= ~GA_ENTRY_FLAG_NO_BOB;
                break;
            case 4:
            case 5:
                break;
            }

            BosGaEntryResetHome(work, i);
        }

        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateBodyChase(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    e = NULL;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= GA_ENTRY_FLAG_NO_BOB;

            switch (i) {
            case 0:
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 1:
                e->baseX = gBtlWork->bossX;
                e->baseY = gBtlWork->bossY + 0x100;
                break;
            }
        }

        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x66;

            if (gBtlWork->bossZ > 0x25FF) {
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }

            break;
        case 1:
            work->vx = 0;
            work->vy = 0;
            work->timer = 0x12C;
            work->step = 2;
            BosGaUpdateFacing(work);
            break;
        case 2:
            work->angle = BosGaGetAngle(gBtlWork->bossX, gBtlWork->bossY, gBtlWork->actor->x, gBtlWork->actor->y);
            work->vx += gSineTable[work->angle] * 5 >> 8;

            if (work->vx > 0x200) {
                work->vx = 0x200;
            } else if (work->vx < -0x200) {
                work->vx = -0x200;
            }

            gBtlWork->bossX += work->vx;

            if (work->vx < 0) {
                if (gBtlWork->bossX < 0) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vx > 0) {
                if (gBtlWork->bossX > 0x10000) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0x10000;
                    BosGaUpdateFacing(work);
                }
            }

            work->vy += -gSineTable[work->angle + 0x40] * 5 >> 8;

            if (work->vy > 0x200) {
                work->vy = 0x200;
            } else if (work->vy < -0x200) {
                work->vy = -0x200;
            }

            gBtlWork->bossY += work->vy;

            if (work->vy < 0) {
                if (gBtlWork->bossY <= 0x127FF) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x12800;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vy > 0) {
                if (gBtlWork->bossY > 0x17800) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x17800;
                    BosGaUpdateFacing(work);
                }
            }

            if (ApplyAttackBox(0xE6, work->entries[0].actor.x, work->entries[0].actor.y, work->entries[0].actor.z, 0x10, 0x10, 0x18)) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
                work->step = 3;
            }

            work->timer--;

            if (work->timer < 0) {
                work->step = 3;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY;
                    break;
                case 1:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY + 0x100;
                    break;
                }
            }

            break;
        case 3:
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ -= 0x33;

            if (gBtlWork->bossZ <= 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }

            break;
        }

        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= ~GA_ENTRY_FLAG_NO_BOB;
                break;
            case 4:
            case 5:
                break;
            }

            BosGaEntryResetHome(work, i);
        }

        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateBodyDash(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    e = NULL;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= GA_ENTRY_FLAG_NO_BOB;

            switch (i) {
            case 0:
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 1:
                e->baseX = gBtlWork->bossX;
                e->baseY = gBtlWork->bossY + 0x100;
                break;
            }
        }

        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x66;

            if (gBtlWork->bossZ > 0x25FF) {
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }

            break;
        case 1:
            work->angle = BosGaGetAngle(gBtlWork->bossX, gBtlWork->bossY, gBtlWork->actor->x, gBtlWork->actor->y);
            work->vx = gSineTable[work->angle] * 4;
            work->vy = -gSineTable[work->angle + 0x40] * 4;
            work->timer = 0x12C;
            work->step = 2;
            BosGaUpdateFacing(work);
            break;
        case 2:
            gBtlWork->bossX += work->vx;

            if (work->vx < 0) {
                if (gBtlWork->bossX < 0) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vx > 0) {
                if (gBtlWork->bossX > 0x10000) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0x10000;
                    BosGaUpdateFacing(work);
                }
            }

            gBtlWork->bossY += work->vy;

            if (work->vy < 0) {
                if (gBtlWork->bossY <= 0x127FF) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x12800;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vy > 0) {
                if (gBtlWork->bossY > 0x17800) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x17800;
                    BosGaUpdateFacing(work);
                }
            }

            if (ApplyAttackBox(0xE6, work->entries[0].actor.x, work->entries[0].actor.y, work->entries[0].actor.z, 0x10, 0x10, 0x18)) {
                m4aSongNumStart(SONG_BTL_MON_HIT03);
                work->step = 3;
            }

            work->timer--;

            if (work->timer < 0) {
                work->step = 3;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY;
                    break;
                case 1:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY + 0x100;
                    break;
                }
            }

            break;
        case 3:
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ -= 0x33;

            if (gBtlWork->bossZ <= 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }

            break;
        }

        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= ~GA_ENTRY_FLAG_NO_BOB;
                break;
            case 4:
            case 5:
                break;
            }

            BosGaEntryResetHome(work, i);
        }

        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateBodyJump(GaWork* work) {
    GaEntryWork* e;
    u32 i;

    e = NULL;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= GA_ENTRY_FLAG_NO_BOB;

            switch (i) {
            case 0:
                AnimStart(&e->anim, 1, ANIM_FLAG_LOOP);
                break;
            case 1:
                e->baseX = gBtlWork->bossX;
                e->baseY = gBtlWork->bossY + 0x100;
                break;
            }
        }

        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            gBtlWork->bossZ += 0x66;

            if (gBtlWork->bossZ > 0x25FF) {
                gBtlWork->bossZ = 0x2600;
                work->timer = 3;
                work->step = 1;
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }

            break;
        case 1:
            work->vx = (gBtlWork->actor->x - gBtlWork->bossX) / 60;
            work->vy = (gBtlWork->actor->y - gBtlWork->bossY) / 60;
            work->vz = -0x400;
            work->vzDelta = 0x22;
            work->step = 2;
            BosGaUpdateFacing(work);
            break;
        case 2:
            gBtlWork->bossX += work->vx;

            if (work->vx < 0) {
                if (gBtlWork->bossX < 0) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vx > 0) {
                if (gBtlWork->bossX > 0x10000) {
                    work->vx = -work->vx;
                    gBtlWork->bossX = 0x10000;
                    BosGaUpdateFacing(work);
                }
            }

            gBtlWork->bossY += work->vy;

            if (work->vy < 0) {
                if (gBtlWork->bossY <= 0x127FF) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x12800;
                    BosGaUpdateFacing(work);
                }
            } else if (work->vy > 0) {
                if (gBtlWork->bossY > 0x17800) {
                    work->vy = -work->vy;
                    gBtlWork->bossY = 0x17800;
                    BosGaUpdateFacing(work);
                }
            }

            gBtlWork->bossZ += work->vz;
            work->vz += work->vzDelta;

            if (gBtlWork->bossZ > 0x2600) {
                gBtlWork->bossZ = 0x2600;
                BtlMapStartShake();
                m4aSongNumStart(SONG_BTL_IRON_RUMB);
                ApplyAttackBox(0xE5, gBtlWork->viewX, gBtlWork->viewY, 0, 0x140, 0xF0, 1);
                work->timer--;

                if (work->timer > 0) {
                    work->step = 1;
                } else {
                    work->step = 3;
                }
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    BosGaEntryResetHome(work, 0);
                    break;
                case 1:
                    e->baseX = gBtlWork->bossX;
                    e->baseY = gBtlWork->bossY + 0x100;
                    e->baseZ = BosGaEntryHomeZ(work, 1);
                    break;
                }
            }

            break;
        case 3:
            work->step = 4;
            break;
        case 4:
            gBtlWork->bossZ -= 0x33;

            if (gBtlWork->bossZ <= 0) {
                BosGaRequestState(work, 1);
            }

            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i <= 1) {
                    e->baseZ = BosGaEntryHomeZ(work, i);
                }
            }

            break;
        }

        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            switch (i) {
            case 0:
                AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                ClearBtlObjActionFlags(&e->actor);
            default:
                e->flags &= ~GA_ENTRY_FLAG_NO_BOB;
                break;
            case 4:
            case 5:
                break;
            }

            BosGaEntryResetHome(work, i);
        }

        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateGimmick(GaWork* work) {
    GaEntryWork* e;
    u32 i;
    s32 t;

    e = NULL;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        work->timer = 0x12C;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];

            if (!(e->flags & GA_ENTRY_FLAG_DESTROYED)) {
                e->vz = -COS(GetRandom() % 0x20) * -3;
                e->vx = SIN(GetRandom() % 0x100) * 0x233 >> 8;
                e->vy = -COS(GetRandom() % 0x100) * 0x233 >> 8;
                e->mode = 1;

                if (i == 0) {
                    AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
                    AnimStart(&e->anim, 2, ANIM_FLAG_LOOP);
                }
            }
        }

        m4aSongNumStart(SONG_BTL_IRON_GIMICBREAK);
        BtlMapStartShake();
        break;
    case 1:
        work->timer--;

        if (work->timer > 0) {
            break;
        }

        BosGaRequestState(work, 1);
        break;
    case 2:
        gBtlWork->bossZ = 0;

        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            t = e->flags & GA_ENTRY_FLAG_DESTROYED;

            if (t == 0) {
                if (i == 0) {
                    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
                    AnimStart(&e->anim, 0, ANIM_FLAG_LOOP);
                }

                e->mode = t;
                BosGaEntryResetHome(work, i);
            }
        }

        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return 1;
}

u8 BosGaUpdateDefeat(GaWork* work) {
    CharaObjParam param;
    u32 i;
    GaEntryWork* e;
    u8 result = 1;

    if (work->flags & GA_FLAG_STATE_REQUESTED) {
        work->statePhase = 2;
    }

    switch (work->statePhase) {
    case 0:
        for (i = 0; i <= 5; i++) {
            e = &work->entries[i];
            e->flags |= GA_ENTRY_FLAG_NO_BOB;

            switch (i) {
            case 0:
                AnimStart(&work->anim, 1, 0);
                AnimStart(&e->anim, 2, 0);
                e->baseVz = 0;
                break;
            case 1:
                e->baseVz = 0;
                break;
            }
        }

        work->timer = 3;
        work->step = 0;
        break;
    case 1:
        switch (work->step) {
        case 0:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    e->baseZ += e->baseVz;
                    e->baseVz += 128;

                    if (e->baseZ > -0x1800) {
                        m4aSongNumStart(SONG_SND_389);
                        e->baseZ = -0x1800;
                        e->baseVz = -(e->baseVz / 2);
                        work->entries[1].baseVz = -(work->entries[1].baseVz / 2);
                        work->timer--;

                        if (work->timer <= 0) {
                            work->step = 1;
                        }
                    }

                    break;
                case 1:
                    e->baseZ += e->baseVz;
                    e->baseVz += 128;
                    break;
                }
            }

            break;
        case 1:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i == 1) {
                    work->timer = 20;
                    e->baseVx = (!work->flipped ? -0xA00 : 0xA00) / work->timer;
                    e->baseVy = 0x600 / work->timer;
                    work->step = 2;
                }
            }

            break;
        case 2:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i == 1) {
                    e->baseX += e->baseVx;
                    e->baseY += e->baseVy;
                    work->timer--;

                    if (work->timer <= 0) {
                        work->step = 3;
                    }
                }
            }

            break;
        case 3:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i == 1) {
                    e->baseVz = 0;
                    work->timer = 3;
                    work->step = 4;
                }
            }

            break;
        case 4:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                if (i == 1) {
                    e->baseZ += e->baseVz;
                    e->baseVz += 128;

                    if (e->baseZ > -0x800) {
                        m4aSongNumStart(SONG_BTL_IRON_FOOTR);
                        e->baseZ = -0x800;
                        e->baseVz = -(e->baseVz / 2);
                        work->timer--;

                        if (work->timer <= 0) {
                            work->step = 5;
                        }
                    }
                }
            }

            break;
        case 5:
            for (i = 0; i <= 5; i++) {
                e = &work->entries[i];

                switch (i) {
                case 0:
                    param.tilesAddr = OBJ_VRAM0 + (e->tiles->index << 5);
                    param.tileCount = e->tiles->count;
                    param.tilesAddr2 = OBJ_VRAM0 + (work->tiles->index << 5);
                    param.tileCount2 = work->tiles->count;
                    param.x = e->baseX + (!work->flipped ? -0x700 : 0x700);
                    param.y = e->baseY;
                    param.z = e->baseZ + 0x1000;
                    param.prizeObj = &e->actor;
                    break;
                case 1:
                    param.tilesAddr3 = OBJ_VRAM0 + (e->tiles->index << 5);
                    param.tileCount3 = e->tiles->count;
                    break;
                }
            }

            param.paletteAddr = OBJ_PLTT + (work->palette->index << 5);
            param.paletteSize = work->palette->count << 5;
            param.tilesAddr4 = 0;
            param.tileCount4 = 0;
            param.paletteAddr2 = 0;
            param.paletteSize2 = 0;
            param.callback = BosGaReleaseBody;
            CharaObjInitDefeat(&param);
            work->step = 6;
            break;
        case 6:
            if (!CharaObjUpdateDefeat()) {
                EndBossDefeat();
                result = 0;
            }

            break;
        }

        break;
    case 2:
        break;
    }

    if (work->statePhase == 0) {
        work->statePhase = 1;
    }

    if (work->statePhase == 2) {
        work->state = work->nextState;
        work->statePhase = 0;
        work->flags &= ~GA_FLAG_STATE_REQUESTED;
    }

    return result;
}

void BosGaEntryUpdate(GaWork* work, GaEntryWork* entry) {
    s32 d1;
    s32 d2;
    s32 flag;
    s32 v;
    u16 t;

    if (entry->flags & GA_ENTRY_FLAG_RELEASED) {
        return;
    }

    switch (UpdateBtlObjReaction(&entry->actor)) {
    case BTL_REACTION_CARD_ACTION:
        work->cardActionSeen = 1;

        if (work->state == 10 || work->nextState == 10) {
            ClearBtlObjActionFlags(&entry->actor);
        } else {
            d1 = gBtlWork->actor->x - entry->baseX;
            d1 = (d1 * d1) >> 8;
            d2 = gBtlWork->actor->y - entry->baseY;
            d2 = (d2 * d2) >> 8;

            if (work->entries[2].flags & work->entries[3].flags & work->entries[4].flags & work->entries[5].flags & GA_ENTRY_FLAG_DESTROYED) {
                switch (GetRandom() % 3) {
                case 0:
                    BosGaRequestState(work, 7);
                    break;
                case 1:
                    BosGaRequestState(work, 8);
                    break;
                case 2:
                    BosGaRequestState(work, 9);
                    break;
                }
            } else if (d1 + d2 <= 0xE0FFF) {
                if (GetRandom() % 100 < 70) {
                    if ((work->entries[2].flags & work->entries[3].flags & GA_ENTRY_FLAG_DESTROYED) == 0) {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    } else {
                        if (!work->attackToggle) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    }
                } else {
                    if ((work->entries[4].flags & work->entries[5].flags & GA_ENTRY_FLAG_DESTROYED) == 0) {
                        if (!work->attackToggle) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    } else {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    }
                }
            } else if (d1 + d2 <= 0x270FFF) {
                if (GetRandom() % 100 < 50) {
                    if ((work->entries[2].flags & work->entries[3].flags & GA_ENTRY_FLAG_DESTROYED) == 0) {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    } else {
                        if (!work->attackToggle) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    }
                } else {
                    if ((work->entries[4].flags & work->entries[5].flags & GA_ENTRY_FLAG_DESTROYED) == 0) {
                        if (!work->attackToggle) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    } else {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    }
                }
            } else {
                if (GetRandom() % 100 < 30) {
                    if ((work->entries[2].flags & work->entries[3].flags & GA_ENTRY_FLAG_DESTROYED) == 0) {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    } else {
                        if (!work->attackToggle) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    }
                } else {
                    if ((work->entries[4].flags & work->entries[5].flags & GA_ENTRY_FLAG_DESTROYED) == 0) {
                        if (!work->attackToggle) {
                            BosGaRequestState(work, 6);
                        } else {
                            BosGaRequestState(work, 3);
                        }
                    } else {
                        flag = 0;

                        if (gBtlWork->bossX <= gBtlWork->actor->x) {
                            flag = 1;
                        }

                        if (work->flipped == flag) {
                            BosGaRequestState(work, 4);
                        } else {
                            BosGaRequestState(work, 5);
                        }
                    }
                }
            }
        }

        if (GetRandom() % 3 != 0) {
            if (!work->attackToggle) {
                work->attackToggle = 1;
            } else {
                work->attackToggle = 0;
            }
        }

        break;
    case BTL_REACTION_HURT:
    case BTL_REACTION_STUNNED:
    case BTL_REACTION_GRAVITY:
        entry->flags |= GA_ENTRY_FLAG_HURT;
        entry->flashTimer = 0;

        if (entry->index == 0) {
            work->entries[1].flags |= GA_ENTRY_FLAG_HURT;
            work->entries[1].flashTimer = 0;
        }

        break;
    case BTL_REACTION_DEFEATED:
    case BTL_REACTION_GRAVITY_DEFEATED:
        SetBtlObjUnhittable(&entry->actor, 1);
        entry->flags |= GA_ENTRY_FLAG_DESTROYED;

        if (entry->index == 0) {
            BeginBossDefeat(&entry->actor);
            entry->mode = 0;
            entry->counter = 0;
            work->entries[1].mode = 0;
            work->entries[1].counter = 0;
            BosGaRequestState(work, 11);
        } else {
            entry->mode = 3;
            entry->counter = 0;

            if (work->state != 10 && work->nextState != 10) {
                if (work->cardActionSeen) {
                    ClearBtlObjActionFlags(&work->entries[0].actor);
                }

                BosGaRequestState(work, 1);
            }
        }

        break;
    case BTL_REACTION_CARD_BROKEN:
        if (work->state != 10 && work->nextState != 10) {
            if (GetRandom() % 100 < 30) {
                DropGimmickCard(0, entry->baseX, entry->baseY, entry->baseZ);
            }

            BosGaRequestState(work, 1);
        }

        ClearBtlObjActionFlags(&entry->actor);
        break;
    }

    switch ((u32)entry->mode) {
    case 0:
        v = (entry->baseX - entry->actor.x) >> 1;

        if (v > 0x600) {
            v = 0x600;
        } else if (v < -0x600) {
            v = -0x600;
        }

        entry->actor.x += v;
        v = (entry->baseY - entry->actor.y) >> 1;

        if (v > 0x600) {
            v = 0x600;
        } else if (v < -0x600) {
            v = -0x600;
        }

        entry->actor.y += v;
        v = ((entry->baseZ + entry->bobZ) - entry->actor.z) >> 1;

        if (v > 0x600) {
            v = 0x600;
        } else if (v < -0x600) {
            v = -0x600;
        }

        entry->actor.z += v;
        t = entry->rotation;
        ApproachAngle(&t, 0, 3);
        entry->rotation = t;

        if (entry->flags & GA_ENTRY_FLAG_NO_BOB) {
            break;
        }

        entry->bobZ = gSineTable[entry->bobAngle] << 2;
        entry->bobAngle += 4;
        break;
    case 1:
        BosGaEntryUpdateFall(entry);
        break;
    case 3:
        if (entry->counter == 0) {
            entry->flags |= GA_ENTRY_FLAG_HURT;
            entry->flashTimer = 0;

            if (!BgFxIsActive()) {
                BgFxStartEnemyDeath(entry->actor.x, entry->actor.y + entry->actor.z, 0, 0x100);
                entry->counter++;
            }
        } else if (entry->counter > 0) {
            if (work->entries[2].flags & work->entries[3].flags & work->entries[4].flags & work->entries[5].flags & GA_ENTRY_FLAG_DESTROYED) {
                SetBtlObjUnhittable(&work->entries[0].actor, 0);
            }

            ClearBtlObjActionFlags(&entry->actor);
            BosGaEntryRelease(entry);
            return;
        }

        BosGaEntryUpdateFall(entry);
        break;
    }

    if (entry->flags & GA_ENTRY_FLAG_HURT) {
        entry->flashTimer++;

        if (entry->flashTimer > 30) {
            ClearBtlObjActionFlags(&entry->actor);
            entry->flags &= ~GA_ENTRY_FLAG_HURT;
            entry->flashTimer = 0;
        }
    }

    entry->gfx = AnimUpdate(&entry->anim);

    if (entry->index == 0) {
        work->gfx = AnimUpdate(&work->anim);
    }

    if (entry->actor.collider.colliding) {
        entry->actor.x += entry->actor.collider.pushX;
        entry->actor.y += entry->actor.collider.pushY;
    }

    ColliderSetPosition(&entry->actor.collider, entry->actor.x, entry->actor.y, entry->actor.z + entry->bobZ);
    TaskPoolUpdate(&entry->tasks);
}

void task_bos_ga_0(GaWork* work, s32 arg) {
    u32 i;
    GaEntryWork* p;

    sGaWork = work;

    if (arg == 0) {
        work->state = 1;
    } else {
        work->state = 0;
    }

    work->nextState = work->state;
    work->flags = 0;
    work->statePhase = 0;
    work->timer = 0;
    work->stepsLeft = 0;
    work->hurtTimer = 0;
    work->flipped = 0;
    work->angle = 0;
    work->attackToggle = 0;
    work->cardTimer = 60;
    TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosMap, &sBosMapConfig);
    gBtlWork->bossX = 0xE200;
    gBtlWork->bossY = 0x15E00;
    gBtlWork->bossZ = 0;
    SetBattleActorPosition(0x8200, 0x15E00, 0);
    p = work->entries;

    for (i = 0; i <= 5; i++) {
        BosGaEntryInit(work, i, arg);
    }

    SetBtlObjUnhittable(&p->actor, 1);
    SetBtlObjUnhittable(&work->entries[1].actor, 1);
    work->palette = LoadObjPalette(gBoss01objPalette, 32);
    work->palette2 = LoadObjPalette(gHitFlashPalette, 32);
    SetBtlPaletteFadeExcluded(work->palette->index + 16, 1);
    SetBtlPaletteFadeExcluded(work->palette2->index + 16, 1);
    RequestBossCardValue(GetRandom() % 4 + 1);
}

u8 task_bos_ga_1(GaWork* work) {
    u8 result;
    GaEntryWork* p;
    AnimState* anim;
    u32 i;

    result = 1;
    work->cardTimer--;

    if (work->cardTimer <= 0) {
        RequestBossCardValue(GetRandom() % 7 + 1);
        work->cardTimer = 60;
    }

    work->cardActionSeen = 0;
    i = 0;
    p = work->entries;

    do {
        BosGaEntryUpdate(work, p);
        p++;
        i++;
    } while (i <= 5);

    switch (work->state) {
    case 0:
        result = BosGaUpdateAssemble(work);
        break;
    case 1:
        result = BosGaUpdateIdle(work);
        break;
    case 2:
        result = BosGaUpdateWalk(work);
        break;
    case 3:
        result = BosGaUpdateStomp(work);
        break;
    case 4:
        result = BosGaUpdateThrust(work);
        break;
    case 5:
        result = BosGaUpdateOrbit(work);
        break;
    case 6:
        result = BosGaUpdateJump(work);
        break;
    case 7:
        result = BosGaUpdateBodyChase(work);
        break;
    case 8:
        result = BosGaUpdateBodyDash(work);
        break;
    case 9:
        result = BosGaUpdateBodyJump(work);
        break;
    case 10:
        result = BosGaUpdateGimmick(work);
        break;
    case 11:
        result = BosGaUpdateDefeat(work);
        break;
    }

    if (ConsumeGimmickFlag(0)) {
        BosGaRequestState(work, 10);
    }

    anim = &work->entries[1].anim;

    if (AnimIsFinished(anim) && GetRandom() % 100 == 0 && work->state != 11) {
        AnimStart(anim, 1, 0);
    }

    return result;
}

void task_bos_ga_2(GaWork* work) {
    GaEntryWork* p;
    u32 i;

    i = 0;
    p = work->entries;

    do {
        BosGaEntryDraw(work, p);
        p++;
        i++;
    } while (i <= 5);
}

void task_bos_ga_3(GaWork* work) {
    GaEntryWork* p;
    u32 i;

    i = 0;
    p = work->entries;

    do {
        BosGaEntryRelease(p);
        p++;
        i++;
    } while (i <= 5);

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}
