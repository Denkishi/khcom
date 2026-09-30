#include "task_descriptors.h"
#include "system_state.h"
#include "display.h"
#include "frd.h"
#include "task_animation_assets.h"
#include "sprites_evt.h"
#include "sprites_frd.h"
#include "world_types.h"
#include "btl_api.h"
#include "fade.h"
#include "smn_api.h"
#include "songs.h"
#include "frd_tasks.h"

static const AnimDef sFrdDonaldAnimDefs[6] = {
    { gDonaBtLl00Frames, gDonaBtLl00Anims, gDonaBtLl00Tiles, 0, { 0, 0, 0 } },
    { gDonaBtLl00Frames, gDonaBtLl00Anims, gDonaBtLl00Tiles, 1, { 0, 0, 0 } },
    { gDonaBtLl00Frames, gDonaBtLl00Anims, gDonaBtLl00Tiles, 2, { 0, 0, 0 } },
    { gDonaBtLl00Frames, gDonaBtLl00Anims, gDonaBtLl00Tiles, 3, { 0, 0, 0 } },
    { gDonaFl00Frames, gDonaFl00Anims, gDonaFl00Tiles, 5, { 0, 0, 0 } },
    { gDonaBl00Frames, gDonaBl00Anims, gDonaBl00Tiles, 2, { 0, 0, 0 } },
};

TaskDesc gTaskDescFrdDonald = {
    "task_frd_donald",
    (TaskInitFunc)task_frd_donald_0,
    (TaskUpdateFunc)task_frd_donald_1,
    (TaskDrawFunc)task_frd_donald_2,
    (TaskDestroyFunc)task_frd_donald_3,
    sizeof(FrdDonaldWork),
};

static const AnimDef sFrdGoofyAnimDefs[5] = {
    { gGoofy16Frames, gGoofy16Anims, gGoofy16Tiles, 0, { 0, 0, 0 } },
    { gGoofy16Frames, gGoofy16Anims, gGoofy16Tiles, 1, { 0, 0, 0 } },
    { gGoofy14Frames, gGoofy14Anims, gGoofy14Tiles, 0, { 0, 0, 0 } },
    { gGoofy05Frames, gGoofy05Anims, gGoofy05Tiles, 1, { 0, 0, 0 } },
    { gGoofy05Frames, gGoofy05Anims, gGoofy05Tiles, 2, { 0, 0, 0 } },
};

TaskDesc gTaskDescFrdGoofy = {
    "task_frd_goofy",
    (TaskInitFunc)task_frd_goofy_0,
    (TaskUpdateFunc)task_frd_goofy_1,
    (TaskDrawFunc)task_frd_goofy_2,
    (TaskDestroyFunc)task_frd_goofy_3,
    sizeof(FrdGoofyWork),
};

static const AnimDef sFrdArielAnimDefs[3] = {
    { gUnk_09EDE5C8, gUnk_09EDE5F0, gUnk_088777F6, 0, { 0, 0, 0 } },
    { gUnk_09EDE5C8, gUnk_09EDE5F0, gUnk_088777F6, 1, { 0, 0, 0 } },
    { gUnk_09EDE5C8, gUnk_09EDE5F0, gUnk_088777F6, 2, { 0, 0, 0 } },
};

TaskDesc gTaskDescFrdAriel = {
    "task_frd_ariel",
    (TaskInitFunc)task_frd_ariel_0,
    (TaskUpdateFunc)task_frd_ariel_1,
    (TaskDrawFunc)task_frd_ariel_2,
    (TaskDestroyFunc)task_frd_ariel_3,
    sizeof(FrdArielWork),
};

static const AnimDef sFrdJackAnimDefs[5] = {
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 0, { 0, 0, 0 } },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 1, { 0, 0, 0 } },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 2, { 0, 0, 0 } },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 3, { 0, 0, 0 } },
    { gUnk_09EDE594, gUnk_09EDE5B4, gUnk_08875122, 4, { 0, 0, 0 } },
};

TaskDesc gTaskDescFrdJack = {
    "task_frd_jack",
    (TaskInitFunc)task_frd_jack_0,
    (TaskUpdateFunc)task_frd_jack_1,
    (TaskDrawFunc)task_frd_jack_2,
    (TaskDestroyFunc)task_frd_jack_3,
    sizeof(FrdJackWork),
};

static const AnimDef sFrdPanAnimDefs[4] = {
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 0, { 0, 0, 0 } },
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 1, { 0, 0, 0 } },
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 2, { 0, 0, 0 } },
    { gPeterTukiFrames, gPeterTukiAnims, gPeterTukiTiles, 3, { 0, 0, 0 } },
};

TaskDesc gTaskDescFrdPan = {
    "task_frd_pan",
    (TaskInitFunc)task_frd_pan_0,
    (TaskUpdateFunc)task_frd_pan_1,
    (TaskDrawFunc)task_frd_pan_2,
    (TaskDestroyFunc)task_frd_pan_3,
    sizeof(FrdPanWork),
};

static const AnimDef sFrdAladdinAnimDefs[3] = {
    { gAladdin10Frames, gAladdin10Anims, gAladdin10Tiles, 2, { 0, 0, 0 } },
    { gAladdin10Frames, gAladdin10Anims, gAladdin10Tiles, 0, { 0, 0, 0 } },
    { gAladdin10Frames, gAladdin10Anims, gAladdin10Tiles, 1, { 0, 0, 0 } },
};

TaskDesc gTaskDescFrdAladdin = {
    "task_frd_aladdin",
    (TaskInitFunc)task_frd_aladdin_0,
    (TaskUpdateFunc)task_frd_aladdin_1,
    (TaskDrawFunc)task_frd_aladdin_2,
    (TaskDestroyFunc)task_frd_aladdin_3,
    sizeof(FrdAladdinWork),
};

static const AnimDef sFrdBeastAnimDefs[2] = {
    { gFelosiaslangeFrames, gFelosiaslangeAnims, gFelosiaslangeTiles, 0, { 0, 0, 0 } },
    { gFelosiaslangeFrames, gFelosiaslangeAnims, gFelosiaslangeTiles, 1, { 0, 0, 0 } },
};

void task_frd_donald_0(FrdDonaldWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->vz = 0;

    if (work->actor->flags & 4) {
        work->unk_158 = work->actor->x - 0x3000;
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 4;
    } else {
        work->unk_158 = work->actor->x + 0x3000;
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->z = -0x5000;
    body->groundZ = 0;
    work->palette = LoadObjPalette(gDonaldPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 0, 0, work->tiles);

    switch (args->variant) {
    case 0:
        work->repeatsLeft = 1;
#ifdef VERSION_EU
        if (gLanguage == 3) {
            m4aSongNumStart(SONG_VO_SR_SUMMON00);
        } else {
            m4aSongNumStart(SONG_VO_SR_SUMMON04);
        }
#else
        m4aSongNumStart(SONG_VO_SR_SUMMON04);
#endif
        break;
    case 1:
        work->repeatsLeft = 1;
#ifdef VERSION_EU
        if (gLanguage == 3) {
            m4aSongNumStart(SONG_VO_SR_SUMMON00);
        } else {
            m4aSongNumStart(SONG_VO_SR_SUMMON04);
        }
#else
        m4aSongNumStart(SONG_VO_SR_SUMMON04);
#endif
        break;
    case 2:
        work->repeatsLeft = 1;
#ifdef VERSION_EU
        if (gLanguage == 3) {
            m4aSongNumStart(SONG_VO_SR_SUMMON00);
        } else {
            m4aSongNumStart(SONG_VO_SR_SUMMON04);
        }
#else
        m4aSongNumStart(SONG_VO_SR_SUMMON04);
#endif
        break;
    default:
        m4aSongNumStart(SONG_VO_DL_ATTACK00);
        BgFxStartFlame(0, 0, 0, 0x180);
        UpdateDonaldFlame(body, 0, 8, 8);
        break;
    }

    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_frd_donald_1(FrdDonaldWork* work) {
    BtlObj* body = &work->body;
    BtlWork* owner;
    BtlObj* target;
    s32 angle;
    if (work->mainSide != 0) {
        owner = gBtlWork;
        target = owner->actor2;
    } else {
        owner = gRikuBtlWork;
        target = owner->actor2;
    }
    if (owner->flags & 0x40000000) return 0;
    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 2, 0, work->tiles);
            work->stateTimer++;
        }
        body->x += (work->unk_158 - body->x) >> 4;
        ClampBattlePosition(&body->x, &body->y, -16, 0);
        if (work->variant == 3) UpdateDonaldFlame(body, 0, 8, 8);
        if (FrdDonaldApplyGravity(work)) {
            work->stateTimer = 0;
            if (work->variant == 3) work->state = 8;
            else {
                work->state = 1;
                m4aSongNumStart(SONG_VO_DL_ATTACK00);
            }
        }
        break;
    case 1:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 3, 0, work->tiles);
        if (AnimIsFinished(&work->anim)) {
            SelectLockonTarget();
            if (gBtlWork->flags & 0x800000000ULL) work->state = 4;
            else {
                u16 spell = GetRandom();
                spell &= 3;
                switch (spell) {
                case 0:
                    work->state = 4;
                    break;
                case 1:
                    work->state = 5;
                    break;
                case 2:
                    work->state = 6;
                    break;
                case 3:
                    work->state = 7;
                    break;
                }
            }
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    case 2:
        if (work->repeatsLeft > 0) {
            SelectLockonTarget();
            if (gBtlWork->flags & 0x800000000ULL) work->state = 4;
            else {
                u16 spell = GetRandom();
                spell &= 3;
                switch (spell) {
                case 0:
                    work->state = 4;
                    break;
                case 1:
                    work->state = 5;
                    break;
                case 2:
                    work->state = 6;
                    break;
                case 3:
                    work->state = 7;
                    break;
                }
            }
            work->stateTimer = 0;
            work->repeatsLeft--;
        } else {
            if (work->stateTimer == 0) AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 3, 0, work->tiles);
            if (AnimIsFinished(&work->anim)) {
                work->state = 3;
                work->stateTimer = 0;
            } else work->stateTimer++;
        }
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 2, 0, work->tiles);
            if (!(body->flags & 4)) work->unk_158 = (gBtlWork->xMin - 64) * 256;
            else work->unk_158 = (gBtlWork->xMax + 64) * 256;
            work->vz = -0x500;
            work->steps = 30;
        }
        ApproachValue(&body->x, work->unk_158, work->steps);
        if (work->variant == 3) UpdateDonaldFlame(body, 0, 8, 8);
        FrdDonaldApplyGravity(work);
        if (work->steps <= 0) {
            if (work->variant == 3) BgAnimStop();
            return 0;
        }
        work->stateTimer++;
        work->steps--;
        break;
    case 8:
        if (work->stateTimer == 0) {
            if (body->flags & 4) angle = GetRandom() % 2 ? 0xAD : 0xD3;
            else angle = GetRandom() % 2 ? 0x53 : 0x2D;
            work->unk_158 = gSineTable[angle] * 3;
            work->unk_15C = -gSineTable[angle + 64] * 3;
        }
        if (work->unk_15C > 0) AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 4, ANIM_FLAG_LOOP, work->tiles);
        else AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 5, ANIM_FLAG_LOOP, work->tiles);
        if (work->unk_158 < 0) body->flags |= 4;
        else body->flags &= ~4ULL;
        body->x += work->unk_158;
        body->y += work->unk_15C;
        FrdDonaldApplyGravity(work);
        UpdateDonaldFlame(body, 1, 2, 8);
        switch (ClampBattlePosition(&body->x, &body->y, 0, 0)) {
        case 1:
        case 2:
            work->unk_158 = -work->unk_158;
            break;
        case 3:
        case 4:
            work->unk_15C = -work->unk_15C;
            break;
        }
        if (work->stateTimer > 179) {
            work->stateTimer = 0;
            work->state = 3;
        } else work->stateTimer++;
        break;
    case 4:
        {
            s32 x,y,z;
            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);
                if (target != NULL) {
                    if (target->x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                }
            }
            if (work->stateTimer == 40) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->z - target->centerHeight * 256;
                    if (x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                } else {
                    if (body->flags & 4) x = body->x - 0xC800;
                    else x = body->x + 0xC800;
                    y = body->y;
                    z = body->z - 0x800;
                }
                switch (work->variant) {
                case 0:
                    if (body->flags & 4) BgFxStartFire(0, body->x - 0x5000, body->y, body->z - 0x800, x, y, z, 1, 123);
                    else BgFxStartFire(0, body->x + 0x5000, body->y, body->z - 0x800, x, y, z, 0, 123);
                    break;
                case 1:
                    if (body->flags & 4) BgFxStartFire(1, body->x - 0x5000, body->y, body->z - 0x800, x, y, z, 1, 124);
                    else BgFxStartFire(1, body->x + 0x5000, body->y, body->z - 0x800, x, y, z, 0, 124);
                    break;
                case 2:
                default:
                    if (body->flags & 4) BgFxStartFire(2, body->x - 0x5000, body->y, body->z - 0x800, x, y, z, 1, 125);
                    else BgFxStartFire(2, body->x + 0x5000, body->y, body->z - 0x800, x, y, z, 0, 125);
                    break;
                }
            }
            if (work->stateTimer > 40) {
                if (!BgFxIsActive()) {
                    work->state = 2;
                    work->stateTimer = 0;
                    break;
                }
                if (target != NULL) BgFxSetTarget(target->x, target->y, target->z - target->centerHeight * 256);
            }
            work->stateTimer++;
            break;
        }
    case 5:
        {
            s32 x,y,z;
            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);
                if (target != NULL) {
                    if (target->x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                }
            }
            if (work->stateTimer == 40) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->z - target->centerHeight * 256;
                    if (x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                } else {
                    if (body->flags & 4) x = body->x - 0x6400;
                    else x = body->x + 0x6400;
                    y = body->y;
                    z = body->z - 0x800;
                }
                switch (work->variant) {
                case 0:
                    if (body->flags & 4) BgFxStartBlizzard(0, body->x - 0x5000, body->y, body->z - 0x800, x, y, z, 1, 126);
                    else BgFxStartBlizzard(0, body->x + 0x5000, body->y, body->z - 0x800, x, y, z, 0, 126);
                    break;
                case 1:
                    if (body->flags & 4) BgFxStartBlizzard(1, body->x - 0x5000, body->y, body->z - 0x800, x, y, z, 1, 127);
                    else BgFxStartBlizzard(1, body->x + 0x5000, body->y, body->z - 0x800, x, y, z, 0, 127);
                    break;
                case 2:
                default:
                    if (body->flags & 4) BgFxStartBlizzard(2, body->x - 0x5000, body->y, body->z - 0x800, x, y, z, 1, 128);
                    else BgFxStartBlizzard(2, body->x + 0x5000, body->y, body->z - 0x800, x, y, z, 0, 128);
                    break;
                }
            }
            if (work->stateTimer > 40) {
                if (!BgFxIsActive()) {
                    work->state = 2;
                    work->stateTimer = 0;
                    break;
                }
                if (target != NULL) BgFxSetTarget(target->x, target->y, target->z - target->centerHeight * 256);
            }
            work->stateTimer++;
            break;
        }
    case 6:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdDonaldAnimDefs, &work->anim, 1, 0, work->tiles);
            AnimReset(&work->anim);
            if (target != NULL) {
                if (target->x < body->x) body->flags |= 4;
                else body->flags &= ~4ULL;
            }
        }
        if (work->stateTimer == 40) {
            switch (work->variant) {
            case 0:
                {
                    s32 x,y,z;
                    if (target != NULL) {
                        x=target->x;
                        y=target->y;
                        z=target->groundZ;
                    } else {
                        if (body->flags & 4) x=body->x-0x5000;
                        else x=body->x+0x5000;
                        y=body->y;
                        z=0;
                    }
                    BgFxStartThunder(0, body->x, body->y, body->z-0x4000, x,y,z,129);
                    break;
                }
            case 1:
                BgFxStartWideThunder(1,body->x,body->y,body->z-0x4000,body->groundZ,130);
                break;
            case 2:
            default:
                BgFxStartWideThunder(2,body->x,body->y,body->z-0x4000,body->groundZ,131);
                break;
            }
        }
        if (work->stateTimer == 60) SetBattleZoom(15,148,0x10000,0x12C00);
        if (work->stateTimer > 40 && !BgFxIsActive()) {
            work->state=2;
            SetBattleZoom(15,256,gBtlWork->x2,gBtlWork->y2);
            work->stateTimer=0;
        } else work->stateTimer++;
        break;
    case 7:
        {
            BtlObj* ally=work->mainSide != 0 ? gBtlWork->actor : gRikuBtlWork->actor;
            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdDonaldAnimDefs,&work->anim,1,0,work->tiles);
                AnimReset(&work->anim);
                if (ally->x < body->x) body->flags |= 4;
                else body->flags &= ~4ULL;
            }
            if (work->stateTimer == 40) {
                switch (work->variant) {
                case 0:
                    BgFxStartCure(0,ally->x,ally->y,ally->z-0x2C00);
                    break;
                case 1:
                    BgFxStartCure(1,ally->x,ally->y,ally->z-0x2C00);
                    break;
                case 2:
                    BgFxStartCure(2,ally->x,ally->y,ally->z-0x2C00);
                    break;
                default:
                    BgFxStartCure(0,ally->x,ally->y,ally->z-0x2C00);
                    break;
                }
            }
            if (work->stateTimer > 40) {
                if (BgFxIsActive()) {
                    BgFxSetPosition(ally->x,ally->y,ally->z-0x2C00);
                } else {
                    if (ally->btl->hcEffect == 13) {
                        switch (work->variant) {
                        case 0:
                            ally->hp+=75;
                            break;
                        case 1:
                            ally->hp+=225;
                            break;
                        case 2:
                            ally->hp+=450;
                            break;
                        }
                    } else {
                        switch (work->variant) {
                        case 0:
                            ally->hp+=50;
                            break;
                        case 1:
                            ally->hp+=150;
                            break;
                        case 2:
                            ally->hp+=300;
                            break;
                        }
                    }
                    if (ally->hp > ally->maxHp) ally->hp=ally->maxHp;
                    CreateBtlPopTask(ally,10);
                    work->state=2;
                    SetBattleZoom(15,256,gBtlWork->x2,gBtlWork->y2);
                    work->stateTimer=0;
                    break;
                }
            }
            work->stateTimer++;
            break;
        }
    }
    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_donald_2(FrdDonaldWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_donald_3(FrdDonaldWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

u8 FrdGoofyApplyGravity(FrdGoofyWork* work) {
    BtlObj* body;

    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

void task_frd_goofy_0(FrdGoofyWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
#ifdef VERSION_EU
    if (gLanguage == 1 || gLanguage == 3) {
        m4aSongNumStart(SONG_VO_SR_SUMMON00);
    } else {
        m4aSongNumStart(SONG_VO_SR_SUMMON03);
    }
#else
    m4aSongNumStart(SONG_VO_SR_SUMMON03);
#endif

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->vz = 0;

    if (work->actor->flags & 4) {
        work->targetX = work->actor->x - 0x3000;
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 4;
    } else {
        work->targetX = work->actor->x + 0x3000;
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->z = -0x5000;
    body->groundZ = 0;
    work->palette = LoadObjPalette(gGoofyPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 0, 0, work->tiles);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_frd_goofy_1(FrdGoofyWork* work) {
    BtlObj* body;
    BtlWork* obj;
    s32 t;

    body = &work->body;
    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        return 0;
    }

    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 0, 0, work->tiles);
            work->stateTimer++;
        }

        body->x += (work->targetX - body->x) >> 4;
        ClampBattlePosition(&body->x, &body->y, -16, 0);

        if (FrdGoofyApplyGravity(work)) {
            work->state = 1;
            work->stateTimer = 0;
            m4aSongNumStart(SONG_VO_GF_ATTACK00);
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            switch (work->variant) {
            case 0:
            case 1:
                work->state = 4;
                break;
            case 2:
                work->state = 5;
                break;
            }

            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 1, 0, work->tiles);
        }

        if (AnimIsFinished(&work->anim)) {
            work->state = 3;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 0, 0, work->tiles);

            if (body->flags & 4) {
                work->targetX = (gBtlWork->xMin - 0x40) << 8;
            } else {
                work->targetX = (gBtlWork->xMax + 0x40) << 8;
            }

            work->vz = -0x500;
            work->steps = 30;
        }

        ApproachValue(&body->x, work->targetX, work->steps);
        FrdGoofyApplyGravity(work);

        if (work->steps <= 0) {
            return 0;
        }

        work->stateTimer++;
        work->steps--;
        break;
    case 4:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 2, 0, work->tiles);

            if (body->flags & 4) {
                work->targetX = body->x - 0x8500;
            } else {
                work->targetX = body->x + 0x8500;
            }
        }

        if (work->stateTimer == 40) {
            work->targetY = work->actor->y;
        }

        if (work->stateTimer > 39) {
            body->x += (work->targetX - body->x) >> 4;
            body->y += (work->targetY - body->y) >> 4;

            if (body->flags & 4
                    ? ApplyAttackBox(work->variant + 120, body->x - 0xF00, body->y, body->z, 0x1E, 0x0C, 0x30)
                    : ApplyAttackBox(work->variant + 120, body->x + 0xF00, body->y, body->z, 0x1E, 0x0C, 0x30)) {
                m4aSongNumStart(SONG_EF_GFHIT);
            }

            ClampBattlePosition(&body->x, &body->y, -16, 0);
        }

        FrdGoofyApplyGravity(work);

        if (AnimIsFinished(&work->anim)) {
            work->state = 2;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 5:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 3, 0, work->tiles);
        }

        FrdGoofyApplyGravity(work);

        if (AnimIsFinished(&work->anim)) {
            work->state = 6;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 6:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdGoofyAnimDefs, &work->anim, 4, ANIM_FLAG_LOOP, work->tiles);
            work->angle = GetRandom();
        }

        work->targetX = work->actor->x + (gSineTable[work->angle] << 6);
        work->targetY = work->actor->y - (gSineTable[work->angle + 0x40] << 5);
        body->x += (work->targetX - body->x) >> 3;
        body->y += (work->targetY - body->y) >> 3;
        ClampBattlePosition(&body->x, &body->y, -16, 0);
        work->angle += 4;

        if (ApplyAttackBox(0x7A, body->x, body->y, body->z, 0x23, 0x1C, 0x30)) {
            m4aSongNumStart(SONG_EF_GFHIT);
        }

        FrdGoofyApplyGravity(work);

        if (work->stateTimer > 179) {
            work->state = 2;
            work->stateTimer = 0;
        }

        work->stateTimer++;
        break;
    }

    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_goofy_2(FrdGoofyWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_goofy_3(FrdGoofyWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_frd_ariel_0(FrdArielWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
    m4aSongNumStart(SONG_VO_SR_SUMMON10);

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;

    if (work->actor->flags & 4) {
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 4;
    } else {
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->groundZ = 0;
    work->hoverZ = -0x1000;
    body->z = -0x1000;
    work->palette = LoadObjPalette(gArielPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdArielAnimDefs, &work->anim, 1, 0, work->tiles);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);

    switch (args->variant) {
    case 0:
        work->passSpeed = 0x500;
        work->passesLeft = 0;
        break;
    case 1:
        work->passSpeed = 0x800;
        work->passesLeft = 1;
        break;
    case 2:
    default:
        work->passSpeed = 0xC00;
        work->passesLeft = 4;
        break;
    }
}

u8 task_frd_ariel_1(FrdArielWork* work) {
    BtlObj* body;
    BtlWork* obj;
    s32 t;

    body = &work->body;

    if (gGameState.world != WORLD_ATLANTICA) {
        return 0;
    }

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        return 0;
    }

    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);

    switch (work->state) {
    case 0:
        if (body->flags & 4) {
            t = gBtlWork->xMax - 0x30;
        } else {
            t = gBtlWork->xMin + 0x30;
        }

        body->x += ((t << 8) - body->x) >> 3;

        if (work->stateTimer > 20) {
            work->stateTimer = 0;
            work->state = 1;
        } else {
            work->stateTimer++;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            work->speed = 0;
            work->steps = 12;
            AnimChangeWithDef(sFrdArielAnimDefs, &work->anim, 2, 0, work->tiles);
        }

        switch (AnimGetFrame(&work->anim)) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
        default:
            if (work->steps > 0) {
                ApproachValue(&work->speed, work->passSpeed, work->steps);
                work->steps--;
            }

            if (body->flags & 4) {
                body->x -= work->speed;
            } else {
                body->x += work->speed;
            }
            break;
        }

        if (work->steps <= 0 && AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 2;
        } else {
            work->stateTimer++;
        }
        break;
    case 2:
        AnimChangeWithDef(sFrdArielAnimDefs, &work->anim, 0, ANIM_FLAG_LOOP, work->tiles);

        if (body->flags & 4
                ? ApplyAttackBox(0x77, body->x, body->y, body->z, 0x10, 0x10, 0x10)
                : ApplyAttackBox(0x77, body->x, body->y, body->z, 0x10, 0x10, 0x10)) {
            m4aSongNumStart(SONG_BTL_AR_PUNCHHIT);
        }

        if (body->flags & 4) {
            body->x -= work->passSpeed;

            if (body->x < (gBtlWork->xMin - 0x30) << 8) {
                if (work->passesLeft == 0) {
                    return 0;
                }

                work->passesLeft--;
                body->flags &= 0xFFFFFFFFFFFFFFFB;
                work->stateTimer = 0;
                body->y = work->actor->y;
                MakeOpponentsHittable();
            }
        } else {
            body->x += work->passSpeed;

            if (body->x > (gBtlWork->xMax + 0x30) << 8) {
                if (work->passesLeft == 0) {
                    return 0;
                }

                work->passesLeft--;
                body->flags |= 4;
                work->stateTimer = 0;
                body->y = work->actor->y;
                MakeOpponentsHittable();
            }
        }

        body->z = work->hoverZ + (gSineTable[((u16)work->stateTimer * 8) & 0xFF] << 3);
        body->y += (work->actor->y - body->y) >> 4;

        if (work->stateTimer == 20) {
            m4aSongNumStart(SONG_VO_AR_ATTACK00);
        }

        work->stateTimer++;
        break;
    }

    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_ariel_2(FrdArielWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_ariel_3(FrdArielWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

u8 FrdJackApplyGravity(FrdJackWork* work) {
    BtlObj* body;

    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

void task_frd_jack_0(FrdJackWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
    m4aSongNumStart(SONG_VO_SR_SUMMON07);

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->vz = 0;

    if (work->actor->flags & 4) {
        work->targetX = work->actor->x - 0x3000;
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 4;
    } else {
        work->targetX = work->actor->x + 0x3000;
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->z = -0x5000;
    body->groundZ = 0;
    work->rotation = 0;
    work->palette = LoadObjPalette(gJackPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);

    switch (args->variant) {
    case 0:
        work->repeatsLeft = 0;
        break;
    case 1:
        work->repeatsLeft = 1;
        break;
    case 2:
    default:
        work->repeatsLeft = 2;
        break;
    }

    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_frd_jack_1(FrdJackWork* work) {
    BtlObj* body = &work->body;
    BtlWork* owner;
    BtlObj* target;
    if (gGameState.world != WORLD_HALLOWEEN_TOWN) return 0;
    if (work->mainSide != 0) {
        owner = gBtlWork;
        target = owner->actor2;
    } else {
        owner = gRikuBtlWork;
        target = owner->actor2;
    }
    if (owner->flags & 0x40000000) return 0;
    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 1, 0, work->tiles);
            work->stateTimer++;
        }
        body->x += (work->targetX - body->x) >> 4;
        ClampBattlePosition(&body->x, &body->y, -16, 0);
        if (FrdJackApplyGravity(work)) {
            work->state = 1;
            work->stateTimer = 0;
            m4aSongNumStart(SONG_VO_JC_ATTACK00);
        }
        break;
    case 1:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 2, 0, work->tiles);
        if (AnimIsFinished(&work->anim)) {
            u16 spell;
            SelectLockonTarget();
            spell = GetRandom();
            spell &= 3;
            switch (spell) {
            case 0:
                work->state = 4;
                break;
            case 1:
                work->state = 5;
                break;
            case 2:
                work->state = 6;
                break;
            case 3:
                work->state = 7;
                break;
            }
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    case 2:
        if (work->repeatsLeft > 0) {
            work->state = 8;
            work->stateTimer = 0;
            work->repeatsLeft--;
        } else {
            if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 4, 0, work->tiles);
            if (AnimIsFinished(&work->anim)) {
                work->state = 3;
                work->stateTimer = 0;
            } else work->stateTimer++;
        }
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 3, 0, work->tiles);
            if (!(body->flags & 4)) work->targetX = (gBtlWork->xMin - 64) * 256;
            else work->targetX = (gBtlWork->xMax + 64) * 256;
            work->vz = -0x500;
            work->steps = 30;
        }
        ApproachValue(&body->x, work->targetX, work->steps);
        FrdJackApplyGravity(work);
        if (work->steps <= 0) return 0;
        work->stateTimer++;
        work->steps--;
        break;
    case 8:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 4, 0, work->tiles);
        if (AnimIsFinished(&work->anim)) {
            work->state = 9;
            GetRandom();
            m4aSongNumStart(SONG_VO_JC_ATTACK00);
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    case 9:
        if (work->stateTimer == 0) {
            if (work->actor->flags & 4) work->targetX = work->actor->x - 0x2D00;
            else work->targetX = work->actor->x + 0x2D00;
            work->targetY = work->actor->y;
            work->vz = -0x500;
            work->steps = 45;
            if (work->targetX > body->x) {
                if (body->flags & 4) {
                    work->rotationTarget = 256;
                } else {
                    work->rotationTarget = -256;
                }
            } else {
                if (body->flags & 4) {
                    work->rotationTarget = -256;
                } else {
                    work->rotationTarget = 256;
                }
            }
            work->stateTimer++;
        }
        FrdJackApplyGravity(work);
        if (work->vz > 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 1, 0, work->tiles);
        else AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 3, 0, work->tiles);
        if (work->steps > 0) {
            ApproachValueHalfSteps(&body->x, work->targetX, work->steps);
            ApproachValueHalfSteps(&body->y, work->targetY, work->steps);
            if (work->steps <= 39) ApproachValueHalfSteps(&work->rotation, work->rotationTarget, work->steps);
            work->steps--;
        }
        if (body->z >= body->groundZ && work->steps <= 0) {
            work->stateTimer = 0;
            work->rotation = 0;
            work->state = 10;
        }
        break;
    case 10:
        if (work->stateTimer == 0) AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 2, 0, work->tiles);
        if (AnimIsFinished(&work->anim)) {
            u16 spell;
            SelectLockonTarget();
            spell = GetRandom();
            spell &= 3;
            switch (spell) {
            case 0:
                work->state = 4;
                break;
            case 1:
                work->state = 5;
                break;
            case 2:
                work->state = 6;
                break;
            case 3:
                work->state = 7;
                break;
            }
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    case 4:
        {
            s32 x, y, z;
            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);
                if (target != NULL) {
                    if (target->x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                }
            }
            if (work->stateTimer == 44) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->z - target->centerHeight * 256;
                    if (x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                } else {
                    if (body->flags & 4) x = body->x - 0xC800;
                    else x = body->x + 0xC800;
                    y = body->y;
                    z = body->z - 0x1800;
                }
                switch (work->variant) {
                case 0:
                    if (body->flags & 4) BgFxStartFire(0, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 133);
                    else BgFxStartFire(0, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 133);
                    break;
                case 1:
                    if (body->flags & 4) BgFxStartFire(1, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 134);
                    else BgFxStartFire(1, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 134);
                    break;
                case 2:
                default:
                    if (body->flags & 4) BgFxStartFire(2, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 135);
                    else BgFxStartFire(2, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 135);
                    break;
                }
            }
            if (work->stateTimer > 44) {
                if (!BgFxIsActive()) {
                    work->state = 2;
                    work->stateTimer = 0;
                    break;
                }
                if (target != NULL) BgFxSetTarget(target->x, target->y, target->z - target->centerHeight * 256);
            }
            work->stateTimer++;
            break;
        }
    case 7:
        {
            s32 x, y, z;
            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);
                if (target != NULL) {
                    if (target->x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                }
                FadeToAmount(2, 13, 60);
            }
            if (work->stateTimer == 44) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->groundZ;
                    if (x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                } else {
                    if (body->flags & 4) x = body->x - 0x4000;
                    else x = body->x + 0x4000;
                    y = body->y;
                    z = body->groundZ;
                }
                switch (work->variant) {
                case 0:
                    if (body->flags & 4) BgFxStartGravity(0, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 1, 142);
                    else BgFxStartGravity(0, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 0, 142);
                    break;
                case 1:
                    if (body->flags & 4) BgFxStartGravity(1, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 1, 143);
                    else BgFxStartGravity(1, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 0, 143);
                    break;
                case 2:
                default:
                    if (body->flags & 4) BgFxStartGravity(2, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 1, 144);
                    else BgFxStartGravity(2, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 0, 144);
                    break;
                }
            }
            if (work->stateTimer > 44 && !BgFxIsActive()) {
                FadeToOriginal(2, 20);
                work->state = 2;
                work->stateTimer = 0;
            } else work->stateTimer++;
            break;
        }
    case 5:
        {
            s32 x, y, z;
            if (work->stateTimer == 0) {
                AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
                AnimReset(&work->anim);
                if (target != NULL) {
                    if (target->x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                }
            }
            if (work->stateTimer == 44) {
                if (target != NULL) {
                    x = target->x;
                    y = target->y;
                    z = target->z - target->centerHeight * 256;
                    if (x < body->x) body->flags |= 4;
                    else body->flags &= ~4ULL;
                } else {
                    if (body->flags & 4) x = body->x - 0x6400;
                    else x = body->x + 0x6400;
                    y = body->y;
                    z = body->z - 0x1800;
                }
                switch (work->variant) {
                case 0:
                    if (body->flags & 4) BgFxStartBlizzard(0, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 136);
                    else BgFxStartBlizzard(0, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 136);
                    break;
                case 1:
                    if (body->flags & 4) BgFxStartBlizzard(1, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 137);
                    else BgFxStartBlizzard(1, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 137);
                    break;
                case 2:
                default:
                    if (body->flags & 4) BgFxStartBlizzard(2, body->x - 0x4A00, body->y, body->z - 0x1800, x, y, z, 1, 138);
                    else BgFxStartBlizzard(2, body->x + 0x4A00, body->y, body->z - 0x1800, x, y, z, 0, 138);
                    break;
                }
            }
            if (work->stateTimer > 44) {
                if (!BgFxIsActive()) {
                    work->state = 2;
                    work->stateTimer = 0;
                    break;
                }
                if (target != NULL) BgFxSetTarget(target->x, target->y, target->z - target->centerHeight * 256);
            }
            work->stateTimer++;
            break;
        }
    case 6:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdJackAnimDefs, &work->anim, 0, 0, work->tiles);
            AnimReset(&work->anim);
            if (target != NULL) {
                if (target->x < body->x) body->flags |= 4;
                else body->flags &= ~4ULL;
            }
        }
        if (work->stateTimer == 44) {
            switch (work->variant) {
            case 0:
                {
                    s32 x, y, z;
                    if (target != NULL) {
                        x = target->x;
                        y = target->y;
                        z = target->groundZ;
                    } else {
                        if (body->flags & 4) x = body->x - 0x5000;
                        else x = body->x + 0x5000;
                        y = body->y;
                        z = 0;
                    }
                    if (body->flags & 4) BgFxStartThunder(0, body->x - 0x2800, body->y, body->z - 0x1800, x, y, z, 139);
                    else BgFxStartThunder(0, body->x + 0x2800, body->y, body->z - 0x1800, x, y, z, 139);
                    break;
                }
            case 1:
                if (body->flags & 4) BgFxStartWideThunder(1, body->x - 0x2800, body->y, body->z - 0x1800, body->groundZ, 140);
                else BgFxStartWideThunder(1, body->x + 0x2800, body->y, body->z - 0x1800, body->groundZ, 140);
                break;
            case 2:
            default:
                if (body->flags & 4) BgFxStartWideThunder(2, body->x - 0x2800, body->y, body->z - 0x1800, body->groundZ, 141);
                else BgFxStartWideThunder(2, body->x + 0x2800, body->y, body->z - 0x1800, body->groundZ, 141);
                break;
            }
        }
        if (work->stateTimer == 64) SetBattleZoom(15, 148, 0x10000, 0x12C00);
        if (work->stateTimer > 44 && !BgFxIsActive()) {
            work->state = 2;
            SetBattleZoom(15, 256, gBtlWork->x2, gBtlWork->y2);
            work->stateTimer = 0;
        } else work->stateTimer++;
        break;
    }
    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_jack_2(FrdJackWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;
    u8 angle;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);
    angle = work->rotation;

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (angle == 0 && gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (angle != 0) {
        affine = AllocObjAffine(angle, sclX, sclY, 1);
    } else if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    if (body->flags & 4) {
        sx = sx + (gSineTable[(u16)(angle + 128) & 0xFF] * 5 >> 5);
    } else {
        sx = sx - (gSineTable[(u16)(angle + 128) & 0xFF] * 5 >> 5);
    }

    sy = sy + (-gSineTable[((u16)(angle + 128) & 0xFF) + 64] * 5 >> 5) - 40;
    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags, -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_jack_3(FrdJackWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

void task_frd_pan_0(FrdPanWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
    m4aSongNumStart(SONG_VO_SR_SUMMON08);

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->unk_158 = 0;

    if (work->actor->flags & 4) {
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 0x20004;
        work->vx = -0x800;
        work->flyLeft = 0;
    } else {
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0x20000;
        work->vx = 0x800;
        work->flyLeft = 1;
    }

    work->targetX = 0x10000;
    body->y = work->actor->y;
    body->groundZ = 0;
    work->hoverZ = -0x2000;
    body->z = -0x2000;
    work->palette = LoadObjPalette(gPeterPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
    TaskPoolInit(&work->tasks, 15);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);

    switch (work->variant) {
    case 0:
        work->duration = 0x78;
        break;
    case 1:
        work->duration = 0xF0;
        break;
    case 2:
    default:
        work->duration = 0x1E0;
        break;
    }
}

void FrdPanSpawnSparkle(FrdPanWork* work) {
    BtlObj sub;

    if (work->stateTimer % 3 == 0) {
        sub.x = work->body.x;
        sub.y = work->body.y;
        sub.z = work->body.z;

        switch (AnimGetGfxIndex(&work->anim)) {
        case 1:
        case 2:
            sub.z -= 0x800;
            break;
        case 3:
        case 4:
            sub.z -= 0x1800;

            if (work->body.flags & 4) {
                sub.x += 0x2000;
            } else {
                sub.x -= 0x2000;
            }
            break;
        case 5:
        default:
            sub.z -= 0x1000;

            if (work->body.flags & 4) {
                sub.x += 0x1000;
            } else {
                sub.x -= 0x1000;
            }
            break;
        }

        TaskCreate(&work->tasks, &gTaskDescSmnTinkeff, &sub);
    }
}

void FrdPanHover(FrdPanWork* work) {
    BtlObj* body;

    body = &work->body;
    body->z += ((work->hoverZ + (gSineTable[((u16)work->stateTimer * 2) & 0xFF] << 4)) - body->z) >> 2;
}

u8 task_frd_pan_1(FrdPanWork* work) {
    BtlObj* body = &work->body;
    BtlWork* owner;
    BtlObj* target;
    s32 ground;
    s32 y;
    s32 z;
    if (gGameState.world != WORLD_NEVER_LAND) {
        return 0;
    }
    owner = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    target = owner->actor2;
    if (owner->flags & 0x40000000) {
        return 0;
    }
    if (gBtlWork->boundsCallback != NULL) {
        ground = body->groundZ;
        gBtlWork->boundsCallback(&body->x, &body->y, &body->z, &ground);
        if (ground != body->groundZ) {
            work->hoverZ = body->groundZ - 0x1000;
            body->groundZ = ground;
        }
    }
    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
            work->steps = 30;
        }
        ApproachValueHalfSteps(&body->x, work->targetX, work->steps);
        FrdPanHover(work);
        if (work->steps <= 0) {
            work->state = 3;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
            work->steps--;
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
        }
        FrdPanHover(work);
        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 2;
        } else {
            work->stateTimer++;
        }
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 0, 0, work->tiles);
            if (!(body->flags & 4)) {
                work->targetX = (gBtlWork->xMin - 64) * 256;
            } else {
                work->targetX = (gBtlWork->xMax + 64) * 256;
            }
            work->steps = 30;
        }
        work->hoverZ -= 0x400;
        ApproachValue(&body->x, work->targetX, work->steps);
        FrdPanHover(work);
        if (work->steps <= 0) {
            return 0;
        }
        work->stateTimer++;
        work->steps--;
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 1, 0, work->tiles);
        }
        FrdPanHover(work);
        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 4;
            m4aSongNumStart(SONG_VO_PP_ATTACK00);
        } else {
            work->stateTimer++;
        }
        break;
    case 4:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
            work->steps = 70;
            FadeToAmount(0, gBtlWork->fadeAmount, 8);
        }
        SelectLockonTarget();
        if (gBtlWork->flags & 0x4000) {
            BtlObj* other = work->mainSide != 0 ? gRikuBtlWork->actor : gBtlWork->actor;
            y = other->y;
            z = other->z;
        } else if (target != NULL) {
            y = target->y;
            z = target->z;
        } else {
            y = work->actor->y;
            z = work->actor->z;
        }
        body->y += (y - body->y) >> 5;
        work->hoverZ += (z - work->hoverZ) >> 5;
        FrdPanHover(work);
        if (work->flyLeft != 0) {
            ApproachValue(&work->vx, -0x800, work->steps);
        } else {
            ApproachValue(&work->vx, 0x800, work->steps);
        }
        body->x += work->vx;
        if (--work->steps <= 0) {
            work->steps = 70;
            work->flyLeft = !work->flyLeft;
        }
        if (work->vx < 0) {
            body->flags |= 4;
        } else {
            body->flags &= ~4ULL;
        }
        if (body->flags & 4) {
            if (ApplyAttackBox(150, body->x - 0x1C00, body->y, body->z - 0x1400, 20, 20, 20)) {
                m4aSongNumStart(SONG_BTL_PP_SWORDHIT);
            }
        } else {
            if (ApplyAttackBox(150, body->x + 0x1C00, body->y, body->z - 0x1400, 20, 20, 20)) {
                m4aSongNumStart(SONG_BTL_PP_SWORDHIT);
            }
        }
        if (work->stateTimer > work->duration) {
            work->stateTimer = 0;
            work->state = 5;
        } else {
            work->stateTimer++;
        }
        break;
    case 5:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdPanAnimDefs, &work->anim, 3, 0, work->tiles);
        }
        FrdPanHover(work);
        if (AnimIsFinished(&work->anim)) {
            work->stateTimer = 0;
            work->state = 1;
            FadeToOriginal(0, 8);
        } else {
            work->stateTimer++;
        }
        break;
    }
    FrdPanSpawnSparkle(work);
    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_pan_2(FrdPanWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_pan_3(FrdPanWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

u8 FrdAladdinApplyGravity(FrdAladdinWork* work) {
    BtlObj* body;

    body = &work->body;

    if (ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ)) {
        body->z += work->vz;
        work->vz = -0x200;
    } else {
        body->z += work->vz;
        work->vz += 0x33;
    }

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

void task_frd_aladdin_0(FrdAladdinWork* work, FrdArgs* args) {
    BtlObj* body;

    body = &work->body;
    m4aSongNumStart(SONG_VO_SR_SUMMON11);

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
    }

    work->variant = args->variant;
    work->state = 0;
    work->stateTimer = 0;
    work->steps = 0;
    work->vz = 0;

    if (work->actor->flags & 4) {
        work->targetX = work->actor->x - 0x3000;
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 4;
    } else {
        work->targetX = work->actor->x + 0x3000;
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0;
    }

    body->y = work->actor->y;
    body->z = -0x5000;
    body->groundZ = 0;
    work->palette = LoadObjPalette(gAladdinPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdAladdinAnimDefs, &work->anim, 0, 0, work->tiles);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);

    switch (work->variant) {
    case 0:
        work->duration = 0x78;
        break;
    case 1:
        work->duration = 0xF0;
        break;
    case 2:
    default:
        work->duration = 0x1E0;
        break;
    }
}

u8 task_frd_aladdin_1(FrdAladdinWork* work) {
    BtlObj* body;
    s32 x;
    s32 y;
    s32 delta;

    body = &work->body;
    if (gGameState.world != WORLD_AGRABAH) {
        return 0;
    }
    if ((work->mainSide ? gBtlWork->flags : gRikuBtlWork->flags) & 0x40000000) return 0;
    switch (work->state) {
    case 0:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdAladdinAnimDefs, &work->anim, 0, 0, work->tiles);
            work->stateTimer++;
        }
        body->x += (work->targetX - body->x) >> 4;
        ClampBattlePosition(&body->x, &body->y, -16, 0);
        if (FrdAladdinApplyGravity(work)) {
            work->state = 1;
            work->stateTimer = 0;
            m4aSongNumStart(SONG_VO_AD_ATTACK00);
        }
        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdAladdinAnimDefs, &work->anim, 1, 0, work->tiles);
        }
        if (AnimIsFinished(&work->anim)) {
            work->state = 3;
            work->stateTimer = 0;
        } else {
            work->stateTimer++;
        }
        break;
    case 2:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdAladdinAnimDefs, &work->anim, 0, 0, work->tiles);
            if (!(body->flags & 4)) {
                work->targetX = (gBtlWork->xMin - 64) << 8;
            } else {
                work->targetX = (gBtlWork->xMax + 64) << 8;
            }
            work->vz = -0x500;
            work->steps = 30;
        }
        ApproachValue(&body->x, work->targetX, work->steps);
        FrdAladdinApplyGravity(work);
        if (work->steps <= 0) {
            return 0;
        }
        work->stateTimer++;
        work->steps--;
        break;
    case 3:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdAladdinAnimDefs, &work->anim, 2, ANIM_FLAG_LOOP, work->tiles);
        }
        SelectLockonTarget();
        if (work->actor->flags & 4) {
            body->flags |= 4;
            x = work->actor->x - 0x2800;
        } else {
            body->flags &= ~4ULL;
            x = work->actor->x + 0x2800;
        }
        y = work->actor->y;
        delta = (x - body->x) >> 3;
        if (delta < -0x400) {
            delta = -0x400;
        } else if (delta > 0x400) {
            delta = 0x400;
        }
        body->x += delta;
        delta = (y - body->y) >> 5;
        if (delta < -0x200) {
            delta = -0x200;
        } else if (delta > 0x200) {
            delta = 0x200;
        }
        body->y += delta;
        if (work->anim.timer == 0) {
            switch (AnimGetFrame(&work->anim)) {
            case 0:
            case 1:
            case 5:
            case 6:
                if ((body->flags & 4) ? ApplyAttackBox(0x95, body->x - 0x1E00, body->y, body->z, 20, 20, 50) : ApplyAttackBox(0x95, body->x + 0x1E00, body->y, body->z, 20, 20, 50)) {
                    m4aSongNumStart(SONG_BTL_AD_SWORDHIT);
                }
                break;
            }
        }
        FrdAladdinApplyGravity(work);
        ClampBattlePosition(&body->x, &body->y, -16, 0);
        if (work->stateTimer > work->duration) {
            work->stateTimer = 0;
            work->state = 2;
        } else {
            work->stateTimer++;
        }
        break;
    }
    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_aladdin_2(FrdAladdinWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_aladdin_3(FrdAladdinWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

u8 FrdBeastApplyGravity(FrdBeastWork* work) {
    BtlObj* body;

    body = &work->body;
    ApplyBattleBounds(&body->x, &body->y, &body->z, &body->groundZ);
    body->z += work->vz;
    work->vz += 0x33;

    if (body->z > body->groundZ) {
        body->z = body->groundZ;
        work->vz = 0;
        return 1;
    }

    return 0;
}

void task_frd_beast_0(FrdBeastWork* work, FrdArgs* args) {
    BtlObj* body;
    BtlObj* obj;

    body = &work->body;
#ifdef VERSION_EU
    if (gLanguage == 0) {
        m4aSongNumStart(SONG_VO_SR_SUMMON09);
    } else {
        m4aSongNumStart(SONG_VO_SR_SUMMON00);
    }
#else
    m4aSongNumStart(SONG_VO_SR_SUMMON09);
#endif

    if (args->mainSide != 0) {
        work->mainSide = 1;
        gBtlWork->flags |= 0x200000;
        work->actor = gBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
        obj = gBtlWork->actor2;
    } else {
        work->mainSide = args->mainSide;
        gRikuBtlWork->flags |= 0x200000;
        work->actor = gRikuBtlWork->actor;
        work->tiles = gBtlWork->tiles2;
        obj = gRikuBtlWork->actor2;
    }

    work->variant = args->variant;
    work->stateTimer = 0;
    work->vz = 0;

    if (obj != NULL) {
        work->targetX = obj->x;
        work->targetY = obj->y;
    } else {
        work->targetX = 0x10000;
        work->targetY = work->actor->y;
    }

    if (work->actor->flags & 4) {
        body->x = (gBtlWork->xMax + 0x30) << 8;
        body->flags = 0x20004;
    } else {
        body->x = (gBtlWork->xMin - 0x30) << 8;
        body->flags = 0x20000;
    }

    body->y = work->targetY;
    body->z = 0;
    body->groundZ = 0;

    switch (work->variant) {
    case 0:
        work->state = 1;
        work->attack = 0xA0;
        break;
    case 1:
        work->state = 1;
        work->attack = 0xA1;
        break;
    case 2:
    default:
        work->state = 2;
        work->attack = 0xA1;
        break;
    }

    work->palette = LoadObjPalette(gBeastPalette, 32);
    AnimInit(&work->anim, 0, 0);
    AnimChangeWithDef(sFrdBeastAnimDefs, &work->anim, 0, 0, work->tiles);
    TaskPoolInit(&work->tasks, 1);
    TaskCreate(&work->tasks, &gTaskDescBtlShadow, body);
}

u8 task_frd_beast_1(FrdBeastWork* work) {
    BtlObj* body;
    BtlWork* obj;

    body = &work->body;

    if (gGameState.world != WORLD_HOLLOW_BASTION) {
        return 0;
    }

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;

    if (obj->flags & 0x40000000) {
        return 0;
    }

    switch (work->state) {
    case 2:
        if (work->stateTimer == 0) {
            m4aSongNumStart(SONG_VO_BE_ATTACK00);
        }

        if (work->anim.timer == 0 && AnimGetFrame(&work->anim) == 2) {
            work->vz = -0x400;
            m4aSongNumStart(SONG_BTL_BE_ATT02);
        }

        if (body->z < body->groundZ) {
            body->x += (work->targetX - body->x) >> 4;
            body->y += (work->targetY - body->y) >> 4;
        }

        if (work->vz > 0) {
            if (gBtlWork->battleId == 0x99) {
                ApplyAttackBox(0xA3, body->x, body->y, body->z - 0x1800, 0x28, 0x14, 0x10);
            } else {
                ApplyAttackBox(0xA2, body->x, body->y, body->z - 0x1800, 0x28, 0x14, 0x10);
            }
        }

        if (FrdBeastApplyGravity(work) && AnimIsFinished(&work->anim)) {
            work->state = 1;
            work->attack = 0xA1;
            work->stateTimer = 0;
            BtlMapStartShake();
            break;
        }

        work->stateTimer++;
        break;
    case 1:
        if (work->stateTimer == 0) {
            AnimChangeWithDef(sFrdBeastAnimDefs, &work->anim, 1, ANIM_FLAG_LOOP, work->tiles);

            if (work->variant != 2) {
                m4aSongNumStart(SONG_VO_BE_ATTACK00);
            }
        }

        if (body->flags & 4) {
            body->x -= 0x380;

            if (body->x < (gBtlWork->xMin - 0x28) << 8) {
                return 0;
            }
        } else {
            body->x += 0x380;

            if (body->x > (gBtlWork->xMax + 0x28) << 8) {
                return 0;
            }
        }

        if (ApplyAttackBox(work->attack, body->x, body->y, body->z - 0x1800, 0x28, 0x14, 0x10)) {
            m4aSongNumStart(SONG_BTL_BE_ATT01);
        }

        FrdBeastApplyGravity(work);
        work->stateTimer++;
        break;
    }

    AnimUpdate(&work->anim);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

void task_frd_beast_2(FrdBeastWork* work) {
    BtlObj* body;
    void* gfx;
    u16 flags;
    s16 sx;
    s16 sy;
    ObjAffine* affine;
    s32 sclX;
    s32 sclY;

    body = &work->body;
    gfx = AnimGetGfx(&work->anim);
    flags = GetBattleSpritePriorityFlags(body->y);

    if (body->flags & 4) {
        sclY = gBtlWork->scale;
        sclX = sclY;
    } else if (gBtlWork->scale == 256) {
        sclY = gBtlWork->scale;
        sclX = sclY;
        flags |= 1;
    } else {
        sclX = -gBtlWork->scale;
        sclY = gBtlWork->scale;
    }

    WorldToScreen(&sx, &sy, body->x, body->y, body->z);

    if (gBtlWork->scale == 256) {
        affine = 0;
    } else if (gBtlWork->scale <= 255) {
        affine = AllocObjAffine(0, sclX, sclY, 0);
    } else {
        affine = AllocObjAffine(0, sclX, sclY, 1);
    }

    DrawSprite(sx, sy, gfx, work->tiles, work->palette, affine, flags,
               -4100 - ((body->y >> 8) * 4));
    body->shadowPriority = (-4100 - ((body->y >> 8) * 4)) | 2;
    TaskPoolDraw(&work->tasks);
}

void task_frd_beast_3(FrdBeastWork* work) {
    BtlWork* obj;

    obj = work->mainSide != 0 ? gBtlWork : gRikuBtlWork;
    obj->flags &= 0xFFFFFFFFFFDFFFFF;
    ReleaseObjPalette(work->palette);
    TaskPoolDestroy(&work->tasks);
}

TaskDesc gTaskDescFrdBeast = {
    "task_frd_beast",
    (TaskInitFunc)task_frd_beast_0,
    (TaskUpdateFunc)task_frd_beast_1,
    (TaskDrawFunc)task_frd_beast_2,
    (TaskDestroyFunc)task_frd_beast_3,
    sizeof(FrdBeastWork),
};
