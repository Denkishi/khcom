#include "task_descriptors.h"
#include "display.h"
#include "obj_api.h"
#include "util.h"
#include "btl3.h"
#include "btl3_api.h"
#include "smn.h"
#include "task_animation_assets.h"
#include "sprites_btl.h"
#include "sprites_fld.h"

TaskDesc gTaskDescBtlForm = {
    "task_btl_form",
    (TaskInitFunc)task_btl_form_0,
    (TaskUpdateFunc)task_btl_form_1,
    NULL,
    (TaskDestroyFunc)task_btl_form_3,
    sizeof(BtlFormWork),
};

TaskDesc gTaskDescBtlBorn = {
    "task_btl_born",
    (TaskInitFunc)task_btl_born_0,
    (TaskUpdateFunc)task_btl_born_1,
    NULL,
    NULL,
    sizeof(BtlBornWork),
};

TaskDesc gTaskDescBtlRaid = {
    "task_btl_raid",
    (TaskInitFunc)task_btl_raid_0,
    (TaskUpdateFunc)task_btl_raid_1,
    (TaskDrawFunc)task_btl_raid_2,
    (TaskDestroyFunc)task_btl_raid_3,
    sizeof(BtlRaidWork),
};

const AnimDef gBtlBadstatusAnimDefs[5] = {
    { gUnk_09EE12E8, gUnk_09EE130C, gUnk_08B21CFC, 0, { 0, 0, 0 } },
    { gUnk_09EE12D4, gUnk_09EE12E4, gUnk_08B21ACE, 0, { 0, 0, 0 } },
    { gUnk_09EE1318, gUnk_09EE132C, gUnk_08B2213C, 0, { 0, 0, 0 } },
    { gUnk_09EE1330, gUnk_09EE1360, gUnk_08B223E8, 0, { 0, 0, 0 } },
    { gUnk_09EE1368, gUnk_09EE137C, gUnk_08B229A8, 0, { 0, 0, 0 } },
};

void task_btl_form_0(BtlFormWork* work, const BtlFormList* list) {
    s32 i;

    gBtlWork->flags |= 0x2000000;
    work->flags = 0;
    work->list = list;
    work->entry = list->entries[0];
    work->timer = work->entry->delay;
    work->entryIndex = 1;
    work->stepTimer = 0;
    work->stepIndex = 0;
    work->nextTileCount = 0;
    work->waitTimer = 100;
    gBtlWork->pendingEnemies = 0;

    for (i = 0; i < list->count; i++) {
        gBtlWork->pendingEnemies += list->entries[i]->count;
    }
}

u8 task_btl_form_1(BtlFormWork* work) {
    const BtlFormList* list;
    const BtlFormStep* step;
    BtlObj* obj;
    s32 x;
    s32 y;
    s32 z;

    if (gBtlWork->flags & 0x0100000000000000) {
        return 0;
    }

    if (work->flags & 2) {
        list = work->list;
        if (list->threshold >= work->nextTileCount + gBtlWork->enemyTileCount) {
            if (work->nextTileCount == 0) {
                return 0;
            }
            work->entry = list->entries[work->entryIndex];
            work->timer = work->entry->delay;
            work->stepTimer = 0;
            work->stepIndex = 0;
            work->flags &= ~2;
            work->entryIndex++;
            work->waitTimer = 100;
        }
    } else if (work->entry->count <= work->stepIndex) {
        if (work->waitTimer-- <= 0) {
            work->flags |= 2;

            if (gGameState.roomEffect != 4) {
                gGameState.flags &= ~4;
            }

            if (work->entryIndex >= work->list->count) {
                work->nextTileCount = 0;
                return 0;
            }
            work->nextTileCount = GetBtlFormEntryTileCount(work->list->entries[work->entryIndex]);
        }
    } else {
        if (work->timer > 0) {
            work->timer--;
        } else {
            if (work->timer == 0) {
                obj = gBtlWork->actor;
                work->x = (obj->x + 0x10000) >> 1;
                work->y = obj->y;
                work->z = 0;

                if (obj->flags & 4) {
                    if (GetRandom() % 5 != 0) {
                        work->flags |= 1;
                    } else {
                        work->flags &= ~1;
                    }
                } else {
                    if (GetRandom() % 5 == 0) {
                        work->flags |= 1;
                    } else {
                        work->flags &= ~1;
                    }
                }
                work->timer = 0xFFFF;
            }
            step = &work->entry->steps[work->stepIndex];
            if (work->stepTimer >= step->delay) {
                if (work->flags & 1) {
                    x = work->x - (step->x << 8);
                } else {
                    x = work->x + (step->x << 8);
                }
                y = work->y + (step->y << 8);
                z = work->z + (step->z << 8);
                SpawnEnemy(step->id, x, y, z);
                work->stepIndex++;
            } else {
                work->stepTimer++;
            }
        }
    }

    return 1;
}

void task_btl_form_3(void) {
    gBtlWork->flags &= ~0x2000000;
}

void task_btl_born_0(BtlBornWork* work, BtlBornArgs* args) {
    work->pos = args->pos;
    work->desc = args->desc;
    work->flags = args->flags;
    work->tileCount = args->tileCount;
}

u8 task_btl_born_1(BtlBornWork* work) {
    if (BgFxIsActive() == 0) {
        ClampBattlePosition(&work->pos.x, &work->pos.y, -24, -12);

        if (IsSongPlaying(SONG_EF_MON_UP) == 0) {
            m4aSongNumStart(SONG_EF_MON_UP);
        }

        if (CanAllocObjTiles(work->tileCount) == 0) {
            gBtlWork->pendingEnemies--;
            return 0;
        }

        if (CanAllocObjPalette(1) == 0) {
            gBtlWork->pendingEnemies--;
            return 0;
        }

        if (work->flags & 1) {
            BgFxStartEnemySpawn(work->pos.x, work->pos.y,
                          work->pos.z - 0x1000, 0x200);
        } else {
            BgFxStartEnemySpawn(work->pos.x, work->pos.y,
                          work->pos.z - 0x800, 0x100);
        }

        TaskCreate(&gBtlWork->taskPools[0], work->desc, work);
        return 0;
    }

    return 1;
}

void BtlRaidGetEffectPosition(BtlRaidWork* work, s32* outX, s32* outY, s32* outZ) {
    s16 dx;
    s16 dz;

    switch (AnimGetFrame(&work->anim)) {
    case 0:
    case 1:
        dx = -15;
        dz = -6;
        break;
    case 2:
    case 3:
        dx = -15;
        dz = 6;
        break;
    case 4:
    case 5:
        dx = 0;
        dz = 8;
        break;
    case 6:
    case 7:
        dx = 15;
        dz = 6;
        break;
    case 8:
    case 9:
        dx = 15;
        dz = -6;
        break;
    case 10:
    case 11:
    default:
        dx = 0;
        dz = -8;
        break;
    }

    if (work->facingLeft == 0) {
        dx = -dx;
    }

    *outX = work->x + (dx << 8);
    *outY = work->y;
    *outZ = work->z + (dz << 8);
}

void task_btl_raid_0(BtlRaidWork* work, BtlRaidArgs* args) {
    s32 x;
    s32 y;
    s32 z;

    work->variant = args->variant;

    if (args->facingLeft != 0) {
        work->facingLeft = 1;
    } else {
        work->facingLeft = 0;
    }

    if (args->mainSide != 0) {
        work->mainSide = 1;
        work->tiles2 = gBtlWork->tiles2;
        work->actor = gBtlWork->actor;
        work->palette = LoadObjPalette(gSoraPalette, 32);
    } else {
        work->mainSide = 0;
        work->tiles2 = gBtlWork->tiles2;
        work->actor = gRikuBtlWork->actor;
        work->palette = LoadObjPalette(gUnk_096FAC64, 32);
    }

    AnimInit(&work->anim, 0, 0);
    AnimChangeWithTables(&work->anim, 0, 1, gSor1ll68wAnims, gSor1ll68wFrames);
    SetObjTileSource(work->tiles2, gSor1ll68wTiles);
    work->x = args->x;
    work->y = args->y;
    work->z = args->z;
    work->timer = 100;
    work->state = 0;
    work->scale = 256;
    work->vx = 0x800;
    work->hitHalfSize = 10;
    work->flags = 2;
    work->song = 568;

    switch (work->variant) {
    case 0:
        work->attack = 86;
        break;
    case 1:
        work->attack = 100;
        break;
    case 2:
        work->attack = 101;
        BtlRaidGetEffectPosition(work, &x, &y, &z);
        BgFxStartFlame(x, y, z, 332);
        work->hitHalfSize = 16;
        work->song = 505;
        break;
    case 3:
        work->attack = 102;
        BtlRaidGetEffectPosition(work, &x, &y, &z);
        BgFxStartFrost(x, y, z, 332);
        work->hitHalfSize = 16;
        work->song = 509;
        break;
    case 4:
        work->attack = 103;
        work->flags |= 1;
        work->hitHalfSize = 8;
        break;
    case 5:
        work->attack = 104;
        work->flags |= 1;
        work->hitHalfSize = 8;
        break;
    case 6:
        work->attack = 105;
        work->state = 3;

        if (work->facingLeft != 0) {
            work->angle = 192;
        } else {
            work->angle = 64;
        }
        work->timer = 0;
        work->unk_5A = GetRandom() % 5 + 0xFFFE;
        break;
    case 7:
        work->attack = 111;
        work->state = 4;

        if (work->facingLeft != 0) {
            work->angle = 192;
        } else {
            work->angle = 64;
        }
        work->timer = 0;
        work->steps = 0;
        break;
    }

    work->tiles = LoadObjTiles(gUnk_08B22CE4, 0x200);
    work->palette2 = LoadObjPalette(gBStatesPalette, 32);
    m4aSongNumStart(SONG_BTL_LT2_SW);
}

BtlObj* BtlRaidGetTarget(BtlRaidWork* work) {
    BtlObj* obj;

    if (gBtlWork->flags & 0x4000) {
        if (work->mainSide != 0) {
            obj = gRikuBtlWork->actor;
        } else {
            obj = gBtlWork->actor;
        }

        if (obj->hp <= 0) {
            return 0;
        }

        return obj;
    }

    if (gBtlWork->actor2 == 0) {
        return ListPoolFirst(&gBtlWork->pool);
    }

    return gBtlWork->actor2;
}

u8 task_btl_raid_1(BtlRaidWork* work) {
    BtlObj* obj;
    u16 hit;
    s32 x;
    s32 y;
    s32 z;

    if ((work->mainSide != 0 ? gBtlWork : gRikuBtlWork)->flags & 0x40000000) {
        return 0;
    }

    BtlMapFollowPosition(work->x, work->y, work->z + 0x1800);

    switch (work->state) {
    case 4:
        work->x += gSineTable[(u8)work->angle] * 5;
        work->z += -gSineTable[(u8)work->angle + 64] * 5;
        if (work->z > 0) {
            work->z = 0;
        }

        obj = BtlRaidGetTarget(work);

        if (obj != 0) {
            if (work->steps <= 0) {
                ApproachAngle(&work->angle,
                              (u8)GetAngle(work->x, work->z, obj->x,
                                            obj->z - (obj->centerHeight << 8)),
                              2);
            } else {
                work->steps--;
            }

            work->y += (obj->y - work->y) >> 3;

            if (ApplyAttackBox(work->attack, work->x, work->y, work->z, 8, 8, 8) != 0) {
                m4aSongNumStart(work->song);

                if (obj->flags & 2) {
                    work->steps = 20;
                }
            }
        }

        if (obj == 0 || work->timer > 180) {
            work->state = 5;
            work->timer = 0;
        } else {
            work->timer++;
        }
        break;
    case 3:
        work->x += gSineTable[(u8)work->angle] * 8;
        work->y -= gSineTable[(u8)work->angle + 64] * 4;
        hit = ClampBattlePosition(&work->x, &work->y, 0, 0);

        switch (hit) {
        case 1:
            work->angle = GetRandom() % 65 + 32;
            break;
        case 2:
            work->angle = GetRandom() % 65 + 160;
            break;
        case 4:
            work->angle = GetRandom() % 65 + 0xFFE0;
            break;
        case 3:
            work->angle = GetRandom() % 65 + 96;
            break;
        }

        if (ApplyAttackBox(work->attack, work->x, work->y, work->z, 8, 8, 32) != 0) {
            m4aSongNumStart(work->song);
        }

        if (hit != 0) {
            if (work->timer > 180) {
                work->state = 5;
                work->timer = 0;
                break;
            }
            work->unk_5A = GetRandom() % 5 + 0xFFFE;
        }

        work->timer++;
        break;
    case 5:
        if (work->timer == 0) {
            work->steps = 16;
        }
        ApproachValue(&work->x, work->actor->x, work->steps);
        ApproachValue(&work->y, work->actor->y, work->steps);
        ApproachValue(&work->z, work->actor->z - 0x1000, work->steps);
        work->steps--;
        if (work->steps <= 3) {
            return 0;
        }
        work->timer++;
        break;
    case 0:
        ApproachValue(&work->vx, -0x800, work->timer);

        if (work->facingLeft != 0) {
            work->x = work->x - work->vx;
        } else {
            work->x = work->x + work->vx;
        }

        if (work->flags & 1) {
            if (TestAttackBox(work->x, work->y, work->z, work->hitHalfSize, work->hitHalfSize, 32) != 0) {
                work->state = 2;
                work->timer = 0;
                break;
            }
        } else {
            if (ApplyAttackBox(work->attack, work->x, work->y, work->z,
                              work->hitHalfSize, work->hitHalfSize, 32) != 0) {
                m4aSongNumStart(work->song);
            }
        }

        if (work->timer <= 0) {
            switch (work->variant) {
            case 2:
            case 3:
                BgAnimStop();
                break;
            }
            return 0;
        }

        switch (ClampBattlePosition(&work->x, &work->y, -20, 0)) {
        case 1:
        case 2:
            work->state = 1;
            work->steps = work->timer >> 2;
            work->bounceVx = work->vx;
            break;
        }
        work->timer--;
        break;
    case 1:
        ApproachValue(&work->vx, -work->bounceVx, work->steps);

        if (work->facingLeft != 0) {
            work->x = work->x - work->vx;
        } else {
            work->x = work->x + work->vx;
        }

        if (ApplyAttackBox(work->attack, work->x, work->y, work->z,
                          work->hitHalfSize, work->hitHalfSize, 32) != 0) {
            m4aSongNumStart(work->song);
        }

        if (work->steps <= 0) {
            work->timer = 100 - work->timer;
            MakeOpponentsHittable();
            work->state = 0;
        } else {
            work->steps--;
        }
        break;
    case 2:
        if (work->timer == 0) {
            work->steps = 30;

            switch (work->variant) {
            case 4:
                BgFxStartThunderStrike(work->x, work->y, 0, work->attack);
                break;
            case 5:
                BgFxStartGravityStrike(work->x, work->y, 0, work->attack);
                break;
            }
        }

        if (work->steps > 0) {
            ApproachValue(&work->scale, 25, work->steps);
            work->steps--;
            if (work->steps <= 0) {
                work->flags &= ~2;
            }
        }

        if (!(work->flags & 2) && BgFxIsActive() == 0) {
            return 0;
        }

        work->timer++;
        break;
    }

    switch (work->variant) {
    case 2:
    case 3:
        BtlRaidGetEffectPosition(work, &x, &y, &z);
        BgFxSetPosition(x, y, z);
        break;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_btl_raid_2(BtlRaidWork* work) {
    s16 sx;
    s16 sy;
    u16 flags;
    ObjAffine* affine;
    s32 scale;

    if (work->flags & 2) {
        flags = GetBattleSpritePriorityFlags(work->y);
        WorldToScreen(&sx, &sy, work->x, work->y, work->z);
        scale = gBtlWork->scale * work->scale >> 8;

        if (scale == 256) {
            affine = 0;

            if (work->facingLeft == 0) {
                flags |= 1;
            }
        } else {
            if (work->facingLeft == 0) {
                affine = AllocObjAffine(0, -scale, scale, 1);
            } else {
                affine = AllocObjAffine(0, scale, scale, 1);
            }
        }

        DrawSprite(sx, sy, work->gfx, work->tiles2, work->palette, affine, flags,
                   -4100 - (((work->y + 0x1000) >> 8) * 4));
        WorldToScreen(&sx, &sy, work->x, work->y, 0);
        DrawSprite(sx, sy, gUnk_08B22CBC, work->tiles, work->palette2, 0, flags, 0xFFFE);
    }
}

void task_btl_raid_3(BtlRaidWork* work) {
    ReleaseObjPalette(work->palette);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette2);
}

void task_btl_badstatus_0(BtlBadStatusWork* work, BtlObj* obj) {
    work->status = 0;
    work->actor = obj;
    work->tiles = AllocObjTiles(128, 0);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    work->palette2 = LoadObjPalette(gCard00Palette, 32);
    work->palette3 = work->palette;
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(gBtlBadstatusAnimDefs, &work->anim, 0, 1, work->tiles);
}

u8 task_btl_badstatus_1(BtlBadStatusWork* work) {
    BtlObj* obj;
    u32 state;

    obj = work->actor;
    state = obj->badStatus;

    if (state == 0) {
        return 1;
    }

    if (state != work->status) {
        work->status = state;

        switch (state) {
        case 2:
            AnimChangeWithDef(gBtlBadstatusAnimDefs, &work->anim, 0, 1, work->tiles);
            work->palette3 = work->palette;
            break;
        case 5:
            AnimChangeWithDef(gBtlBadstatusAnimDefs, &work->anim, 2, 1, work->tiles);
            work->palette3 = work->palette2;
            break;
        case 3:
            AnimChangeWithDef(gBtlBadstatusAnimDefs, &work->anim, 3, 1, work->tiles);
            work->palette3 = work->palette;
            break;
        case 4:
            AnimChangeWithDef(gBtlBadstatusAnimDefs, &work->anim, 4, 1, work->tiles);
            work->palette3 = work->palette2;
            break;
        case 1:
        default:
            AnimChangeWithDef(gBtlBadstatusAnimDefs, &work->anim, 1, 1, work->tiles);
            work->palette3 = work->palette;
            break;
        }
    }

    obj->badStatusTimer--;

    if (obj->badStatusTimer <= 0) {
        obj->badStatus = 0;
        work->status = 0;
    }

    return 1;
}

void task_btl_badstatus_2(BtlBadStatusWork* work) {
    BtlObj* obj;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;

    obj = work->actor;

    if (obj->badStatus != 0) {
        flags = GetBattleSpritePriorityFlags(obj->y);

        if (gBtlWork->paused != 0) {
            gfx = AnimGetGfx(&work->anim);
        } else {
            gfx = AnimUpdate(&work->anim);
        }

        WorldToScreen(&sx, &sy, obj->x, obj->y,
                      obj->z - ((obj->height + 8) << 8));
        DrawSprite(sx, sy, gfx, work->tiles, work->palette3, 0, flags,
                   -4101 - ((obj->y >> 8) * 4));
    }
}

void task_btl_badstatus_3(BtlBadStatusWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
}

BtlObj* SmnCloudNextTarget(SmnCloudWork* work) {
    BtlObj* list[10];
    BtlObj* p;
    s16 count;

    if (gBtlWork->flags & 0x4000) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return 0;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != 0) {
        if (!(p->flags & 0x01000000)) {
            list[count] = p;
            count++;
            if (count > 9) {
                break;
            }
        }
        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return 0;
    }

    p = list[work->targetIndex % count];
    work->targetIndex++;
    return p;
}

BtlObj* SmnCloudPickTeleportTarget(SmnCloudWork* work) {
    BtlObj* list[10];
    BtlObj* p;
    s16 count;
    s32 d;

    if (gBtlWork->flags & 0x4000) {
        if (work->mainSide != 0) {
            p = gRikuBtlWork->actor;
        } else {
            p = gBtlWork->actor;
        }

        if (p->hp <= 0) {
            return 0;
        }

        return p;
    }

    count = 0;
    p = ListPoolFirst(&gBtlWork->pool);

    while (p != 0) {
        if (!(p->flags & 0x01000000)) {
            d = work->body.z - p->z;
            if (d >= 0 ? d <= 0x3000 : p->z - work->body.z <= 0x3000) {
                list[count] = p;
                count++;
                if (count > 9) {
                    break;
                }
            }
        }
        p = ListPoolNext(&p->node);
    }

    if (count == 0) {
        return 0;
    }

    p = list[GetRandom() % count];
    return p;
}

TaskDesc gTaskDescBtlBadstatus = {
    "task_btl_badstatus",
    (TaskInitFunc)task_btl_badstatus_0,
    (TaskUpdateFunc)task_btl_badstatus_1,
    (TaskDrawFunc)task_btl_badstatus_2,
    (TaskDestroyFunc)task_btl_badstatus_3,
    sizeof(BtlBadStatusWork),
};
