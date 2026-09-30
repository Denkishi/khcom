#include "macros.h"
#include "bos2.h"
#include "sprites_bos2.h"
#include "system_state.h"
#include "btl_api.h"
#include "fade.h"
#include "songs.h"

s16 gBosJfActorX EWRAM_COMMON(8);
JfMapArg gJfMapArg EWRAM_COMMON(16);
s16 gBosJfActorY EWRAM_COMMON(4);
s16 gBosJfActorZ EWRAM_COMMON(4);
s16 gBosJfRightPillarLevel EWRAM_COMMON(16);
s16 gBosJfLeftPillarLevel EWRAM_COMMON(4);
s16 gBosJfShakeTimer EWRAM_COMMON(4);
s16 gBosJfShakeDuration EWRAM_COMMON(4);
s8 gBosJfShakeActive EWRAM_COMMON(4);
s16 gBosJfMiddlePillarLevel EWRAM_COMMON(4);
void* gBosJfMapBlocks EWRAM_COMMON(4);
u32 gUnk_0203ACDC EWRAM_COMMON(4);
u8 gBosJfMapBuffer[0x800] EWRAM_COMMON(16);
s16 gBosJfShakeStep EWRAM_COMMON(4);
s16 gBosJfPillarShape EWRAM_COMMON(4);
s32 gBosJfShakeOffset EWRAM_COMMON(4);
u32 gUnk_0203B4EC EWRAM_COMMON(4);

void task_bos_jf_0(JfWork* work, s32 a) {
    BtlObj* sub;
    BtlWork* q;
    s32 v1;
    s32 v2;

    gBosJfActorX = 0;
    gBosJfActorY = 0;
    gBosJfActorZ = 0;
    work->flags = 0;

    if (a != 0) {
        work->flags = 8;
    }

    gBosJfLeftPillarLevel = 7;
    gBosJfMiddlePillarLevel = 0;
    gBosJfRightPillarLevel = 0;
    gJfMapArg.tiles = gUnk_0965DC04;
    gJfMapArg.tilesSize = 0x8000;
    gJfMapArg.palette = gUnk_096FB404;
    gJfMapArg.paletteSize = 128;
    gJfMapArg.maps[0] = gUnk_096C4C64;
    gJfMapArg.maps[1] = gUnk_096C5464;
    gJfMapArg.maps[2] = gBosJfMapBuffer;
    gJfMapArg.maps[3] = gUnk_096C6464;
    TaskPoolInit(&work->tasks, 4);

    if (work->flags & 8) {
        TaskCreate(&work->tasks, &gTaskDescBosJfMap, &gJfMapArg);
    } else {
        TaskCreate(&gBtlWork->taskPools[1], &gTaskDescBosJfMap, &gJfMapArg);
    }

    work->unk_268 = 0;
    work->unk_26A = 0;
    v1 = work->flags & 8;

    if (v1 != 0) {
        work->state = 10;
        work->attackState = 10;
    } else {
        work->state = 0;
        work->attackState = 0;
    }

    work->unk_240 = 0;
    work->hurtTimer = 0;
    work->stateStep = 0;
    work->unk_246 = 0;
    work->bgFrame = 8;
    work->bgFrameTimer = 12;
    work->pillarPhase = 0;
    work->gimmickTimer = 0;
    v2 = work->flags & 8;

    if (v2 != 0) {
        work->bodyX = 0x2A200;
        work->bodyY = 0x15E00;
        work->bodyZ = -0x3800;
        InitEnemyBtlObj(&work->body, &gBosJfEmyKind, work->bodyX, work->bodyY, work->bodyZ);
        work->body.flags |= 4;
        TaskCreate(&work->tasks, &gTaskDescBosJfMajin, work);
    } else {
        work->subX = 0x29600;
        work->subY = 0x15400;
        work->subZ = -0xB400;
        sub = &work->sub;
        InitEnemyBtlObj(sub, &gBosJfEmyKind, work->subX, work->subY, work->subZ);
        sub->flags |= 0x400;
        sub->flags |= 0x200000000000;
        sub->flags &= ~4;
        sub->hitFlags = v2;
        work->sub.centerHeight = 4;
        work->bodyX = 0x2A200;
        work->bodyY = 0x15E00;
        work->bodyZ = -0x3800;
        InitEnemyBtlObj(&work->body, &gBosJfEmyKind, work->bodyX, work->bodyY, work->bodyZ);
        work->body.flags |= 4;
        work->body.flags |= 0x8000;
        work->body.flags |= 0x100000000;
        work->body.radiusX = 32;
        work->body.radiusY = 40;
        work->body.height = 28;
        SetBtlObjParent(&work->body, sub);
        gBtlWork->bossPriorityOffset = 0xFF00;
        SetBtlPaletteFadeExcluded(0, 1);
        SetBattleActorPosition(0x23E00, 0x16800, -0x4000);
        SetGimmickTarget(0x20600, 0x16800, -0x800);
        TaskCreate(&work->tasks, &gTaskDescBosJfLamp, work);
        TaskCreate(&work->tasks, &gTaskDescBosJfMajin, work);
        q = gBtlWork;
        q->bossX = sub->x;
        q->bossY = sub->y;
        q->bossZ = sub->z;
    }
}
u8 task_bos_jf_1(JfWork* work) {
    BtlObj* sub = &work->sub;
    BtlWork* q;
    u16 t;

    if (work->flags & 8) {
        TaskPoolUpdate(&work->tasks);
        return 1;
    }

    switch (UpdateBtlObjReaction(sub)) {
    case 5:
        work->state = work->attackState;
        work->stateStep = 0;
        break;
    case 1:
    case 6:
    case 7:
        work->flags |= 1;
        work->hurtTimer = 20;
        break;
    case 3:
    case 8:
        work->state = 9;
        work->stateStep = 0;
        break;
    case 4:
        if (gGameState.flags & GAME_FLAG_RIKU) {
            if (work->gimmickTimer == 0) {
                if (GetRandom() % 100 <= 19) {
                    _0801C1F8(0, sub->x, sub->y, sub->z);
                }
            }
        }

        work->state = 7;
        work->stateStep = 0;
        break;
    }

    if (work->flags & 1) {
        if (--work->hurtTimer <= 0) {
            work->unk_240 = 0;
            work->flags &= ~1;
            LoadPaletteWithEffect(gUnk_096FB584, (void*)0x05000000, 32);
            ClearBtlObjActionFlags(sub);

            if (sub->hp > 0) {
                if (work->state != 1 && work->state != 6 && work->state != 7 &&
                    work->state != 11) {
                    work->state = 0;
                    work->stateStep = 0;
                }
            }
        }
    }

    if ((gGameState.flags & GAME_FLAG_RIKU) == 0) {
        if (sub->hitFlags & 0x20000000) {
            sub->hitFlags &= ~0x20000000;

            if ((work->flags & 1) == 0) {
                if (work->gimmickTimer == 0) {
                    _0801C1F8(0, sub->x, sub->y, sub->z);
                }
            }
        }
    }

    if (ConsumeGimmickFlag(0)) {
        work->stateStep = 0;
        work->state = 11;
        work->flags |= 4;

        if (gBtlWork->flags & 0x40) {
            gBtlWork->flags |= 0x400000;
        }
    }

    t = work->gimmickTimer;

    if ((s16)t > 0) {
        work->gimmickTimer = t - 1;
    }

    TaskPoolUpdate(&work->tasks);
    q = gBtlWork;
    q->bossX = sub->x;
    q->bossY = sub->y;
    q->bossZ = sub->z;

    if (work->flags & 2) {
        return 0;
    }

    gBosJfActorX = q->actor->x >> 8;
    gBosJfActorY = q->actor->y >> 8;
    gBosJfActorZ = q->actor->z >> 8;
    return 1;
}

void task_bos_jf_2(JfWork* work) {
    TaskPoolDraw(&work->tasks);
}

void task_bos_jf_3(JfWork* work) {
    if ((work->flags & 8) == 0) {
        ReleaseEnemyBtlObj(&work->sub);
        ReleaseEnemyBtlObj(&work->body);
    }

    TaskPoolDestroy(&work->tasks);
}

u8 ClampBosJfBounds(s32* p, s32* b, s32* a, s32* out) {
    s32 v1;
    s32 v2;
    s32 v3;
    s32 lo;
    s32 hi;
    s32 x;

    v1 = -((gBosJfLeftPillarLevel + 1) << 11);
    v2 = -((gBosJfMiddlePillarLevel + 1) << 11);
    v3 = -((gBosJfRightPillarLevel + 1) << 11);
    gBtlWork->actor->flags &= ~0x2000000;

    if (gBosJfLeftPillarLevel > gBosJfMiddlePillarLevel) {
        lo = 0x1F600;

        if (gBosJfMiddlePillarLevel > gBosJfRightPillarLevel) {
            hi = 0x22E00;
            gBosJfPillarShape = 0;
            x = *p;

            if (x > hi) {
                *out = v3;
                return 0;
            }

            if (x > lo) {
                if (*a <= v2) {
                    *out = v2;
                    if (x > hi - 0x1000)
                        gBtlWork->actor->flags |= 0x2000000;
                } else {
                    *out = v3;
                    *p = hi;
                    return 1;
                }
            } else {
                if (*a <= v1) {
                    *out = v1;
                    if (x > lo - 0x1000)
                        gBtlWork->actor->flags |= 0x2000000;
                } else {
                    *out = v2;
                    *p = lo;
                    return 1;
                }
            }
        } else if (gBosJfMiddlePillarLevel < gBosJfRightPillarLevel) {
            hi = 0x21200;
            gBosJfPillarShape = 1;
            x = *p;

            if (x <= lo) {
                if (*a <= v1) {
                    *out = v1;
                    if (x > lo - 0x1000)
                        gBtlWork->actor->flags |= 0x2000000;
                } else {
                    *out = v2;
                    *p = lo;
                    return 1;
                }
            } else {
                if (x < hi) {
                    *out = v2;
                    return 0;
                }

                if (*a <= v3) {
                    *out = v3;
                    if (x < hi + 0x1000)
                        gBtlWork->actor->flags |= 0x2000000;
                } else {
                    *out = v2;
                    *p = hi;
                    return 1;
                }
            }
        } else {
            gBosJfPillarShape = 2;
            x = *p;

            if (x > lo) {
                *out = v2;
                return 0;
            }

            if (*a <= v1) {
                *out = v1;
                if (x > lo - 0x1000)
                    gBtlWork->actor->flags |= 0x2000000;
            } else {
                *out = v2;
                *p = lo;
                return 1;
            }
        }
    } else if (gBosJfLeftPillarLevel < gBosJfMiddlePillarLevel) {
        lo = 0x1DA00;

        if (gBosJfMiddlePillarLevel > gBosJfRightPillarLevel) {
            hi = 0x22E00;
            gBosJfPillarShape = 3;
            x = *p;

            if (x < lo) {
                *out = v1;
                return 0;
            }

            if (x > hi) {
                *out = v3;
                return 0;
            }

            if (*a <= v2) {
                *out = v2;
                if ((x < lo + 0x1000) || (x > hi - 0x1000))
                    gBtlWork->actor->flags |= 0x2000000;
            } else {
                if (x <= 0x205FF) {
                    *out = v1;
                    *p = lo;
                    return 1;
                }

                *out = v3;
                *p = hi;
                return 1;
            }
        } else if (gBosJfMiddlePillarLevel < gBosJfRightPillarLevel) {
            hi = 0x21200;
            gBosJfPillarShape = 4;
            x = *p;

            if (x < lo) {
                *out = v1;
                return 0;
            }

            if (x < hi) {
                if (*a <= v2) {
                    *out = v2;
                    if (x < lo + 0x1000)
                        gBtlWork->actor->flags |= 0x2000000;
                } else {
                    *out = v1;
                    *p = lo;
                    return 1;
                }
            } else {
                if (*a <= v3) {
                    *out = v3;
                    if (x < hi + 0x1000)
                        gBtlWork->actor->flags |= 0x2000000;
                } else {
                    *out = v2;
                    *p = hi;
                    return 1;
                }
            }
        } else {
            gBosJfPillarShape = 5;
            x = *p;

            if (x < lo) {
                *out = v1;
                return 0;
            }

            if (*a <= v2) {
                *out = v2;
                if (x < lo + 0x1000)
                    gBtlWork->actor->flags |= 0x2000000;
            } else {
                *out = v1;
                *p = lo;
                return 1;
            }
        }
    } else {
        if (gBosJfMiddlePillarLevel > gBosJfRightPillarLevel) {
            hi = 0x22E00;
            gBosJfPillarShape = 6;
            x = *p;

            if (x > hi) {
                *out = v3;
                return 0;
            }

            if (*a <= v2) {
                *out = v2;
                if (x > hi - 0x1000)
                    gBtlWork->actor->flags |= 0x2000000;
            } else {
                *out = v3;
                *p = hi;
                return 1;
            }
        } else if (gBosJfMiddlePillarLevel < gBosJfRightPillarLevel) {
            hi = 0x21200;
            gBosJfPillarShape = 7;
            x = *p;

            if (x < hi) {
                *out = v2;
                return 0;
            }

            if (*a <= v3) {
                *out = v3;
                if (x < hi + 0x1000)
                    gBtlWork->actor->flags |= 0x2000000;
            } else {
                *out = v2;
                *p = hi;
                return 1;
            }
        } else {
            gBosJfPillarShape = 8;
            v1 = v2;
            *out = v1;
            return 0;
        }
    }

    return 0;
}

u8 BosJfGetGroundZ(s32* p, s32* a, s32* b, s32* out) {
    s32 v1;
    s32 v2;
    s32 v3;

    v1 = -((gBosJfLeftPillarLevel + 1) << 11);
    v2 = -((gBosJfMiddlePillarLevel + 1) << 11);
    v3 = -((gBosJfRightPillarLevel + 1) << 11);

    if (*p <= 0x259FF) {
        if (*p <= 0x221FF) {
            if (*p <= 0x1E9FF) {
                if (*p <= 0x1B1FF) {
                    *out = 0;

                    if (*p > 0x1AE00) {
                        return 0;
                    }
                } else {
                    *out = v1;

                    if (*p <= 0x1B5FF) {
                        return 0;
                    }

                    if (*p > 0x1E600 && v1 != v2) {
                        return 0;
                    }
                }
            } else {
                *out = v2;

                if (*p <= 0x1EDFF && v1 != v2) {
                    return 0;
                }

                if (*p > 0x21E00 && v2 != v3) {
                    return 0;
                }
            }
        } else {
            *out = v3;

            if (*p <= 0x225FF && v2 != v3) {
                return 0;
            }

            if (*p > 0x25600) {
                return 0;
            }
        }
    } else {
        *out = 0;

        if (*p <= 0x25DFF) {
            return 0;
        }
    }

    return 1;
}

void task_bos_jf_map_0(JfMapWork* work, JfMapArg* arg) {
    RequestDma3Copy(gUnk_096C5C64, gBosJfMapBuffer, 0x800);
    gBosJfMapBlocks = arg->maps;
    BosJfDrawPillars();
    LoadBgTiles(0, arg->tiles, arg->tilesSize);
    LoadBgPalette(0, arg->palette, arg->paletteSize);
    gBtlWork->scale = 0x100;
    gBtlWork->zoomScale = 0x100;
    gBtlWork->x = 0x23E00;
    gBtlWork->y = 0x12800;
    gBtlWork->viewX = 0x23E00;
    gBtlWork->viewY = 0x12800;
    gBtlWork->x2 = 0x23E00;
    gBtlWork->y2 = 0x12800;
    gBtlWork->zoomX = 0x23E00;
    gBtlWork->zoomY = 0x12800;
    gBtlWork->zoomSteps = 0xF;
    gBtlWork->rotation = 0;
    BtlMapResetShake();
    ScrollBgMapTo(0, gBtlWork->viewX >> 8, gBtlWork->viewY >> 8);
    work->paletteTimer = 0;
    work->paletteFrame = 0;
    gBosJfShakeActive = 0;
    gBosJfShakeStep = 0;
    gBosJfShakeTimer = 0;
    gBosJfShakeDuration = 0;
    gBosJfShakeOffset = 0;
}

u8 task_bos_jf_map_1(JfMapWork* work) {
    s32 dx;
    s32 dy;

    work->paletteTimer++;

    if (work->paletteTimer > 14) {
        work->paletteTimer = 0;
        work->paletteFrame++;

        if (work->paletteFrame > 7) {
            work->paletteFrame = 0;
        }

        LoadPalette(gUnk_096FB484 + work->paletteFrame * 32, (void*)0x05000020, 0x20);
    }

    BtlMapUpdateShake();
    dx = (gBtlWork->x2 - gBtlWork->x) >> 3;
    dy = (gBtlWork->y2 - gBtlWork->y) >> 3;

    if (dx > 0x500) {
        dx = 0x500;
    } else if (dx < -0x500) {
        dx = -0x500;
    }

    gBtlWork->x += dx;
    gBtlWork->y += dy;
    gBtlWork->viewX = gBtlWork->x;
    gBtlWork->viewY = gBtlWork->y;

    if (gBtlWork->viewX < (gBtlWork->xMin + 0x14) << 8) {
        gBtlWork->viewX = (gBtlWork->xMin + 0x14) << 8;
    } else if (gBtlWork->viewX > (gBtlWork->xMax - 0x1C) << 8) {
        gBtlWork->viewX = (gBtlWork->xMax - 0x1C) << 8;
    }

    if (gBtlWork->viewY < (gBtlWork->yMin - 0x90) << 8) {
        gBtlWork->viewY = (gBtlWork->yMin - 0x90) << 8;
    } else if (gBtlWork->viewY > (gBtlWork->yMax - 0x48) << 8) {
        gBtlWork->viewY = (gBtlWork->yMax - 0x48) << 8;
    }

    gBtlWork->viewY += BtlMapGetShake() + BosJfUpdateShake();
    ScrollBgMapTo(0, (gBtlWork->viewX >> 8) + 8, (gBtlWork->viewY >> 8) + 0x28);

    return 1;
}

void BosJfDrawPillars(void) {
    RequestMapRowsCopy(gBosJfPillarMaps[0][gBosJfLeftPillarLevel], gBosJfMapBuffer + 0x24c, 7, 0x17);
    RequestMapRowsCopy(gBosJfPillarMaps[1][gBosJfMiddlePillarLevel], gBosJfMapBuffer + 0x25a, 7, 0x17);
    RequestMapRowsCopy(gBosJfPillarMaps[0][gBosJfRightPillarLevel], gBosJfMapBuffer + 0x268, 7, 0x17);
    SetBgMapBlocks(0, gBosJfMapBlocks, 2, 2);
}
void BosJfStartShake(s16 a) {
    gBosJfShakeActive = 1;
    gBosJfShakeStep = 0;
    gBosJfShakeTimer = 0;
    gBosJfShakeDuration = a;
    gBosJfShakeOffset = 0;
}

s32 BosJfUpdateShake(void) {
    if (gBosJfShakeActive == 1) {
        gBosJfShakeTimer++;

        if (gBosJfShakeTimer < gBosJfShakeDuration) {
            if (gBosJfShakeStep % 4 == 0) {
                gBosJfShakeOffset = 0x200;
            } else if (gBosJfShakeStep % 4 == 2) {
                gBosJfShakeOffset = -0x200;
            }

            gBosJfShakeStep++;
        } else {
            gBosJfShakeActive = 0;
        }
    }

    return gBosJfShakeOffset;
}

void task_bos_jf_lamp_0(JfLampWork* work, JfWork* arg) {
    JfLampSpeed speed;

    speed.integer = 0;
    speed.fraction = 0x80;
    work->jf = arg;
    work->vx = speed.integer * 256 + speed.fraction;
    work->tiles = LoadObjTiles(gUnk_09682AA4, 0x2800);
    work->gfx = gUnk_09EF3A48[12];
    work->tiles2 = LoadObjTiles(gUnk_09682AA4, 0x2800);
    work->gfx2 = gUnk_09EF3A48[14];
    work->palette = LoadObjPalette(gUnk_096FB5A4, 0x60);
    work->palette2 = LoadObjPalette(gUnk_08F69BC4, 32);
    FadeSetPaletteExcluded(work->palette->index + 16, 1);
    work->moveSteps = 0;
    work->tiles2Frame = 0;
    work->tiles2Timer = 0;
    work->voiceInterval = GetRandom() % 0x79 + 0x1E0;
    work->voiceTimer = 0;
    work->unk_24 = 1;
    work->onFlatGround = 1;
    work->state = 0;
    work->stateTimer = 0;
    work->targetX = 0;
    work->angle = 0;
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, &(arg = work->jf)->sub);
}
u8 task_bos_jf_lamp_1(JfLampWork* work) {
    BtlObj* sub = &work->jf->sub;
    JfWork* jf = work->jf;
    ObjTiles* p;
    s32 d;

    if (jf->state <= 3) {
        if (++work->voiceTimer > work->voiceInterval) {
            work->voiceTimer = 0;
            m4aSongNumStart(SONG_VO_EG_DAMAGE00);
            work->voiceInterval = GetRandom() % 121 + 480;
        }
    }

    if (work->jf->state == 9) {
        work->state = 5;
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            work->targetX = BosJfLampChooseTargetX(work);
            d = (s16)((work->targetX >> 8) - (sub->x >> 8));

            if (d > 0) {
                sub->flags &= ~4;
            } else if (d < 0) {
                sub->flags |= 4;
            }

            work->moveSteps = 200;
            work->stateTimer++;
        } else if (work->moveSteps > 0) {
            ApproachValue(&sub->x, work->targetX, work->moveSteps);
            work->moveSteps--;
        } else {
            work->stateTimer = 0;
            work->state = 1;
        }

        sub->z = gSineTable[(u8)work->angle] * 20 - 0xB400;
        work->angle += 2;
        break;
    case 1:
        if (work->stateTimer == 0) {
            d = (s16)((gBtlWork->actor->x >> 8) - (sub->x >> 8));

            if (d > 0) {
                sub->flags &= ~4;
            } else if (d < 0) {
                sub->flags |= 4;
            }

            work->stateTimer++;
        } else if (work->stateTimer > 60) {
            work->stateTimer = 0;
            work->state = 2;
        } else {
            work->stateTimer++;
        }

        sub->z = gSineTable[(u8)work->angle] * 20 - 0xB400;
        work->angle += 2;
        break;
    case 2:
        if (work->stateTimer == 0) {
            if (jf->body.flags & 4) {
                work->targetX = 0x27800;
            } else {
                work->targetX = 0x19400;
            }

            d = (s16)((work->targetX >> 8) - (sub->x >> 8));

            if (d > 0) {
                sub->flags &= ~4;
            } else if (d < 0) {
                sub->flags |= 4;
            }

            work->moveSteps = 200;
            work->stateTimer++;
        } else if (work->moveSteps > 0) {
            ApproachValue(&sub->x, work->targetX, work->moveSteps);
            ApproachValue(&sub->z, -0xB400, work->moveSteps);
            work->moveSteps--;
        } else {
            work->stateTimer = 0;
            work->state = 3;
        }

        sub->z = gSineTable[(u8)work->angle] * 20 - 0xB400;
        work->angle += 2;
        break;
    case 3:
        if (work->stateTimer == 0) {
            d = (s16)((gBtlWork->actor->x >> 8) - (sub->x >> 8));

            if (d > 0) {
                sub->flags &= ~4;
            } else if (d < 0) {
                sub->flags |= 4;
            }

            work->stateTimer++;
        } else if (work->stateTimer > 60) {
            work->stateTimer = 0;
            work->state = 0;
        } else {
            work->stateTimer++;
        }

        sub->z = gSineTable[(u8)work->angle] * 20 - 0xB400;
        work->angle += 2;
        break;
    case 4:
        if (work->stateTimer == 0) {
            work->moveSteps = 20;
            sub->flags |= 4;
            work->vx = -204;
            work->stateTimer++;
        } else {
            if (work->moveSteps > 0) {
                ApproachValue(&sub->z, -0xA000, work->moveSteps);
                work->moveSteps--;
            } else {
                if (sub->x <= 0x19400) {
                    sub->flags &= ~4;
                    work->vx = 204;
                }

                if (sub->x > 0x277FF) {
                    sub->flags |= 4;
                    work->vx = -204;
                }

                sub->x += work->vx;
            }

            if (work->jf->gimmickTimer == 0) {
                work->stateTimer = 0;
                work->state = 2;
            }
        }
        break;
    case 5:
        break;
    }

    if (work->jf->pillarPhase == 2) {
        work->stateTimer = 0;
        work->state = 4;
    }

    if (work->tiles2Timer > 3) {
        work->tiles2Timer = 0;
        work->tiles2Frame++;

        if (work->tiles2Frame > 5) {
            work->tiles2Frame = 0;
        }

        p = work->tiles2;
        RequestDma3Copy(gUnk_09685DA4 + (work->tiles2Frame << 9), gUnk_06010000 + (p->index << 5), 512);
    }

    work->tiles2Timer++;
    work->onFlatGround = BosJfGetGroundZ(&sub->x, &sub->y, &sub->z, &sub->groundZ);
    ColliderSetPosition(&sub->collider, sub->x, sub->y, sub->z);
    TaskPoolUpdate(&work->tasks);

    return 1;
}

void task_bos_jf_lamp_2(JfLampWork* work) {
    BtlObj* sub = &work->jf->sub;
    void* pal;
    u16 mode;
    s16 x;
    s16 y;

    mode = GetBattleSpritePriorityFlags(sub->y);

    if (sub->flags & 4) {
        mode &= 0xFFFE;
    } else {
        mode |= 1;
    }

    if (gBtlWork->paused == 0 && (work->jf->flags & 1) && (gFrameCounter & 1)) {
        pal = work->palette2;
    } else {
        pal = work->palette;
    }

    WorldToScreen(&x, &y, sub->x, sub->y, sub->z);
    DrawSprite(x, y, work->gfx, work->tiles, pal, 0, mode, (u16)(-4100 - (sub->y >> 8) * 4));
    DrawSprite(x, y - 14, work->gfx2, work->tiles2, work->palette, 0, mode,
               (u16)(-4101 - (sub->y >> 8) * 4));

    if (work->onFlatGround == 1) {
        TaskPoolDraw(&work->tasks);
    }
}

void task_bos_jf_lamp_3(JfLampWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    ReleaseObjPalette(work->palette2);
    TaskPoolDestroy(&work->tasks);
}

s32 BosJfLampChooseTargetX(JfLampWork* work) {
    s16 v;
    s32 r;

    if (work->jf->body.flags & 4) {
        switch (gBosJfPillarShape) {
        case 5:
        case 6:
            r = 0x27800;
            break;
        case 1:
        case 4:
        case 7:
            r = 0x21800;
            break;
        case 8:
            v = GetRandom() % 3;

            if (v == 0) {
                r = 0x27800;
            } else if (v == 1) {
                r = 0x24600;
            } else {
                r = 0x21800;
            }
            break;
        case 0:
        case 2:
        case 3:
            r = 0x24600;
            break;
        default:
            r = 0;
            break;
        }

        return r;
    }

    switch (gBosJfPillarShape) {
    case 0:
    case 2:
        r = 0x1F400;
        break;
    case 3:
    case 5:
    case 7:
        r = 0x19400;
        break;
    case 8:
        v = GetRandom() % 3;

        if (v == 0) {
            r = 0x19400;
        } else if (v == 1) {
            r = 0x1CE00;
        } else {
            r = 0x1F400;
        }
        break;
    case 1:
    case 4:
    case 6:
        r = 0x1CE00;
        break;
    default:
        r = 0;
        break;
    }

    return r;
}

const EmyKind gBosJfEmyKind = { 33, 1000, 16, 16, 24, 60, 0 };

TaskDesc gTaskDescBosJf = {
    "task_bos_jf",
    (TaskInitFunc)task_bos_jf_0,
    (TaskUpdateFunc)task_bos_jf_1,
    (TaskDrawFunc)task_bos_jf_2,
    (TaskDestroyFunc)task_bos_jf_3,
    sizeof(JfWork),
};

void* gBosJfPillarMaps[2][15] = {
    {
        gUnk_096C6C64,
        gUnk_096C6C64 + 14,
        gUnk_096C6C64 + 28,
        gUnk_096C6C64 + 42,
        gUnk_096C7464,
        gUnk_096C7464 + 14,
        gUnk_096C7464 + 28,
        gUnk_096C7464 + 42,
        gUnk_096C7C64,
        gUnk_096C7C64 + 14,
        gUnk_096C7C64 + 28,
        gUnk_096C7C64 + 42,
        gUnk_096C8464,
        gUnk_096C8464 + 14,
        gUnk_096C8464 + 28,
    },
    {
        gUnk_096C8C64,
        gUnk_096C8C64 + 14,
        gUnk_096C8C64 + 28,
        gUnk_096C8C64 + 42,
        gUnk_096C9464,
        gUnk_096C9464 + 14,
        gUnk_096C9464 + 28,
        gUnk_096C9464 + 42,
        gUnk_096C9C64,
        gUnk_096C9C64 + 14,
        gUnk_096C9C64 + 28,
        gUnk_096C9C64 + 42,
        gUnk_096CA464,
        gUnk_096CA464 + 14,
        gUnk_096CA464 + 28,
    },
};

TaskDesc gTaskDescBosJfMap = {
    "task_bos_jf_map",
    (TaskInitFunc)task_bos_jf_map_0,
    (TaskUpdateFunc)task_bos_jf_map_1,
    NULL,
    NULL,
    sizeof(JfMapWork),
};

u8 gUnk_09EF27EC[8] = { 0, 1, 1, 0, 0, 0, 0, 0 };

TaskDesc gTaskDescBosJfLamp = {
    "task_bos_jf_lamp",
    (TaskInitFunc)task_bos_jf_lamp_0,
    (TaskUpdateFunc)task_bos_jf_lamp_1,
    (TaskDrawFunc)task_bos_jf_lamp_2,
    (TaskDestroyFunc)task_bos_jf_lamp_3,
    sizeof(JfLampWork),
};
