/**
 * mode_eventselect.c
 * Debug Event Select and Event Effects
 */

#include "macros.h"
#include "registration_data.h"
#include "msg_api.h"
#include "card_api.h"
#include "m4a_song.h"
#include "fade.h"
#include "engine_math.h"
#include "mode_event.h"
#include "mode_eventselect.h"
#include "gba/keys.h"
#include "sprites_evt.h"
#include "sprites_hum.h"
#include "sprites_level_up.h"
#include "sprites_smn.h"
#include "obj_resource_types.h"
#include "malloc.h"
#include "anim.h"
#include "display.h"
#include "event_chara_types.h"
#include "event_index_data.h"
#include "evt_object_types.h"
#include "evt_types.h"
#include "key.h"
#include "m4a.h"
#include "mode.h"
#include "msg_types.h"
#include "obj.h"
#include "obj_api.h"
#include "taskpool.h"
#include "text.h"
#include "types.h"
#include <stddef.h>
#include "debug_text.h"
#include "sprite_palettes.h"
#include "debug_font.h"

static const s16 sSoraEventIds[147] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
    72, 73, 74, 75, 76, 77, 78, 80, 81, 82, 83, 84,
    85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
    97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
    109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
    121, 122, 123, 124, 125, 126,
#ifdef VERSION_EU
    127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138,
    139, 140, 141, 142, 143, 144, 145, 146,
#else
    129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
    141, 142, 143, 144, 145, 146, 147, 148,
#endif
    -1,
};

static const s16 sRikuEventIds[49] = {
#ifdef VERSION_EU
    147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
    159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
    171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182,
    183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
#else
    149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
    161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
    173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184,
    185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196,
#endif
    -1,
};

static const char sEventSelectCursorText[] = "\x81\xa8";

static const char sEventSelectBlankText[] = "\x81\x40";

static const char sEventSelectSoraLabel[] = "\x82\x64\x82\x75\x82\x64\x82\x6d\x82\x73\x81\x40\x82\x72\x82\x6e\x82\x71\x82\x60";

static const char sEventSelectRikuLabel[] = "\x82\x64\x82\x75\x82\x64\x82\x6d\x82\x73\x81\x40\x82\x71\x82\x68\x82\x6a\x82\x74";

static const char sEventSelectNoLabel[] = "\x82\x6d\x82\x8f\x81\x40\x81\x81";

static u16 sUnk_02034A92;
static s16 sEventSelectIndex;
static u8 sEventSelectList;
EventSoundMix* gEventSoundMix EWRAM_COMMON(4);

enum EventSelectList {
    EVENT_SELECT_LIST_SORA,
    EVENT_SELECT_LIST_RIKU
};

s16 GetEventListLength(u8 list) {
    s16 n = 0;

    switch (list) {
    case EVENT_SELECT_LIST_SORA:
        while (sSoraEventIds[n] != -1) {
            n++;
        }

        break;
    case EVENT_SELECT_LIST_RIKU:
        while (sRikuEventIds[n] != -1) {
            n++;
        }

        break;
    }

    return n;
}

void mode_eventselect_0() {
    SetBgMode0();
    func_08085FB0();
    InitSoraDecks();
    InitMapCardInventory();
    SetupBg(0, 0, 30, 0);
    EnableBg(0);
    DebugTextInit(0, 0x8000, 0x800);
    DebugTextLoadPalette(0, gDebugFontPalette, 0x20, 0);
}

void mode_eventselect_1() {
    if (GetKeysRepeat() & DPAD_UP) {
        if (sEventSelectList != EVENT_SELECT_LIST_SORA) {
            sEventSelectList--;
        } else {
            sEventSelectList = EVENT_SELECT_LIST_RIKU;
        }
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        if (sEventSelectList == EVENT_SELECT_LIST_SORA) {
            sEventSelectList++;
        } else {
            sEventSelectList = EVENT_SELECT_LIST_SORA;
        }
    }

    switch (sEventSelectList) {
    case EVENT_SELECT_LIST_SORA:
        DebugTextPrint(0, 0, 2, sEventSelectCursorText);
        DebugTextPrint(0, 10, 2, sEventSelectBlankText);
        DebugTextPrint(0, 20, 2, sEventSelectBlankText);
        break;
    case EVENT_SELECT_LIST_RIKU:
        DebugTextPrint(0, 0, 2, sEventSelectBlankText);
        DebugTextPrint(0, 10, 2, sEventSelectCursorText);
        DebugTextPrint(0, 20, 2, sEventSelectBlankText);
        break;
    }

    if (GetKeysRepeat() & DPAD_RIGHT) {
        sEventSelectIndex++;
    }

    if (GetKeysRepeat() & DPAD_LEFT) {
        sEventSelectIndex--;
    }

    if (GetEventListLength(sEventSelectList) - 1 < sEventSelectIndex) {
        sEventSelectIndex = 0;
    }

    if (sEventSelectIndex < 0) {
        sEventSelectIndex = GetEventListLength(sEventSelectList) - 1;
    }

    DebugTextPrint(10, 0, 2, sEventSelectSoraLabel);
    DebugTextPrint(10, 10, 2, sEventSelectRikuLabel);
    DebugTextPrint(20, 40, 2, sEventSelectNoLabel);
    DebugTextPrintNumber(100, 40, 2, sEventSelectIndex + 1);

    switch (sEventSelectList) {
    case EVENT_SELECT_LIST_SORA:
        DebugTextPrint(20, 80, 2, gEventNames[sSoraEventIds[sEventSelectIndex]]);
        break;
    case EVENT_SELECT_LIST_RIKU:
        DebugTextPrint(20, 80, 2, gEventNames[sRikuEventIds[sEventSelectIndex]]);
        break;
    }

    if (GetKeysPressed() & A_BUTTON) {
        switch (sEventSelectList) {
        case EVENT_SELECT_LIST_SORA:
#ifdef VERSION_EU
            ModeRequest(&gModeEventDebug, sSoraEventIds[sEventSelectIndex] | 0x8000);
#else
            RequestEventMode(sSoraEventIds[sEventSelectIndex]);
#endif
            break;
        case EVENT_SELECT_LIST_RIKU:
#ifdef VERSION_EU
            ModeRequest(&gModeEventDebug, sRikuEventIds[sEventSelectIndex] | 0x8000);
#else
            RequestEventMode(sRikuEventIds[sEventSelectIndex]);
#endif
            break;
        }
    }

    if (GetKeysPressed() & B_BUTTON) {
        ModeRequest(&gModeDebug, 0);
    }

    DebugTextDraw(0);
    DebugTextClear();
}

void mode_eventselect_2() {
    DebugTextDestroy();
}

void Hanabira_0(EffectWork* work, EventCharaWork* chara) {
    s32 i;

    TaskPoolInit(&work->tasks, 16);

    for (i = 15; i >= 0; i--) {
        TaskCreate(&work->tasks, &gTaskDescHanabiraC, chara);
    }
}

s32 Hanabira_1(EffectWork* work) {
    TaskPoolUpdate(&work->tasks);

    return 1;
}

void Hanabira_2(EffectWork* work) {
    TaskPoolDraw(&work->tasks);
}

void Hanabira_3(EffectWork* work) {
    TaskPoolDestroy(&work->tasks);
}

enum HanabiraCState {
    HANABIRA_C_STATE_RISE,
    HANABIRA_C_STATE_FLUTTER
};

void Hanabira_c_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;
    work->palette = LoadObjPalette(gMaruxhaBtEffPalette, 32);
    work->tiles = LoadObjTiles(gMaruxhaBtEff2Tiles, 256);
    work->x = b->x;
    work->y = b->y;
    work->z = b->z - 0x3000;
    work->vx = GetRandom() % 717 - 358;
    work->vz = -(GetRandom() % 539 + 102);
    AnimInit(&work->anim, gMaruxhaBtEff2Anims, gMaruxhaBtEff2Frames);
    AnimStart(&work->anim, GetRandom() & 1, ANIM_FLAG_LOOP);
    work->state = HANABIRA_C_STATE_RISE;
}

s32 Hanabira_c_1(EffectWork* work) {
    s32 v;
    s32 r;

    switch (work->state) {
    case HANABIRA_C_STATE_RISE:
        work->x += work->vx;
        work->z += work->vz;
        work->vz += 17;

        if (work->vz > 256) {
            work->state = HANABIRA_C_STATE_FLUTTER;
        }

        break;
    case HANABIRA_C_STATE_FLUTTER:
        work->x += work->vx;
        work->z += work->vz;
        work->vz = (v = work->vz - 12) - (r = GetRandom()) % 9;

        if (work->vz < 0) {
            work->vz = GetRandom() % 181 + 204;

            if (work->vx > 0) {
                work->vx = -(GetRandom() % 257 + 128);
            } else {
                work->vx = GetRandom() % 257 + 128;
            }
        }

        if (work->z >= 0) {
            return 0;
        }

        break;
    }

    work->gfx = AnimUpdate(&work->anim);

    return 1;
}

void Hanabira_c_2(EffectWork* work) {
    s32 x;
    s32 y;
    s32 t;

    x = (work->x >> 8) - (gEventState->x >> 8);
    t = work->y >> 8;
    y = t + (work->z >> 8) - (gEventState->y >> 8);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - t * 4);
}

void Hanabira_c_3(EffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void smoke_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;
    work->x = b->x;
    work->y = b->y - 0x800;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    SetObjTileSource(work->tiles, gEventSmokeTiles);
    AnimInit(&work->anim, gEventSmokeAnims, gEventSmokeFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 1;
    work->age = 0;
}

void Exclamation_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;
    work->x = b->x;
    work->y = b->y;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);

    if (!FadeIsActive()) {
        FadeSetPaletteExcluded(((ObjPaletteHeader*)work->palette)->index + 16, 1);
    }

    SetObjTileSource(work->tiles, gFEventTiles);
    AnimInit(&work->anim, gFEventAnims, gFEventFrames);
    AnimStart(&work->anim, 0, 0);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 1;
    work->age = 0;
}

void balloon_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;
    work->x = b->x;
    work->y = b->y;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    SetObjTileSource(work->tiles, gFEventTiles);
    AnimInit(&work->anim, gFEventAnims, gFEventFrames);
    AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 0;
    work->age = 0;
}

s32 EffectUpdateObj(EffectWork* work) {
    work->gfx = AnimUpdate(&work->anim);

    if (!work->actor->callbackActive) {
        return 0;
    }

    return 1;
}

s32 Exclamation_1(EffectWork* work) {
    work->age++;
    work->gfx = AnimUpdate(&work->anim);

    if (!work->actor->callbackActive || work->age == 50) {
        return 0;
    }

    return 1;
}

void EffectDrawObj(EffectWork* work) {
    u16 pr;
    s32 y;

    pr = work->actor->obj.drawFlags;

    if (!work->followFlip) {
        pr &= 0xFFFE;
    }

    DrawSprite((work->x >> 8) - (gEventState->x >> 8),
               (y = (work->y >> 8) + gEventCharaParams[work->actor->arg.chara].spriteYOffset) -
                   (gEventState->y >> 8),
               work->gfx, work->tiles, work->palette, NULL, pr, 50);
}

void EffectReleaseObj(EffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void Question_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;
    work->x = b->x;
    work->y = b->y;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    SetObjTileSource(work->tiles, gFEventTiles);
    AnimInit(&work->anim, gFEventAnims, gFEventFrames);
    AnimStart(&work->anim, 5, 0);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 0;
    work->timer = 0;
    work->age = 0;
}

s32 Question_1(EffectWork* work) {
    work->gfx = AnimUpdate(&work->anim);
    work->timer++;

    if (work->timer == 12) {
        AnimStart(&work->anim, 6, ANIM_FLAG_LOOP);
    }

    if (!work->actor->callbackActive) {
        return 0;
    }

    work->age = 0;

    return 1;
}

void TinkerbellParticleInit(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;
    s32 d1;
    s32 d2;
    s32 k;

    work->actor = chara;
    b = &chara->obj;
    k = 0x400;
    d1 = (GetRandom() % 9 << 8) - k;
    work->x = b->x + d1;
    d2 = (GetRandom() % 9 << 8) - k;
    work->y = b->y + d2;
    work->z2 = b->z;
    work->vx = GetRandom() % 232 + 76;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    SetObjTileSource(work->tiles, gSmnTinkEffTiles);
    AnimInit(&work->anim, gSmnTinkEffAnims, gSmnTinkEffFrames);
    AnimStart(&work->anim, GetRandom() % 3, 0);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 0;
    work->age = 0;
    gEventState->particleCount++;
}

s32 TinkerbellParticleUpdate(EffectWork* work) {
    work->gfx = AnimUpdate(&work->anim);
    work->age++;
    work->z2 += 256;

    if (work->z2 > 0) {
        return 0;
    }

    return 1;
}

void TinkerbellParticleDraw(EffectWork* work) {
    u16 pr;

    pr = work->actor->obj.drawFlags;

    if (!work->followFlip) {
        pr &= 0xFFFE;
    }

    DrawSprite((work->x >> 8) - (gEventState->x >> 8),
               ((work->y + work->z2) >> 8) - (gEventState->y >> 8),
               work->gfx, work->tiles, work->palette, NULL, pr,
               -0x1004 - (work->y >> 8) * 4);
}

void TinkerbellParticleDestroy(EffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    gEventState->particleCount--;
}

void GlowNose_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;
    work->x = b->x - 1536;
    work->y = b->y + 3072;
    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    SetObjTileSource(work->tiles, gGlowNoseTiles);
    AnimInit(&work->anim, gGlowNoseAnims, gGlowNoseFrames);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 1;
    work->age = 0;
}

s32 GlowNose_1(EffectWork* work) {
    work->gfx = AnimUpdate(&work->anim);
    work->age++;

    if (work->age > 44) {
        return 0;
    }

    return 1;
}

void GlowNose2_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;

    work->actor = chara;
    b = &chara->obj;

    switch (chara->arg.chara) {
    case 3:
        work->x = b->x - 6144;
        work->y = b->y + 8192;
        break;
    case 43:
        work->x = b->x + 2048;
        work->y = b->y + 2048;
        break;
    }

    work->tiles = AllocObjTiles(128, NULL);
    work->palette = LoadObjPalette(gCommonObjPalette, 32);
    SetObjTileSource(work->tiles, gGlowNoseTiles);
    AnimInit(&work->anim, gGlowNoseAnims, gGlowNoseFrames);
    AnimStart(&work->anim, 1, ANIM_FLAG_LOOP);
    work->gfx = AnimGetGfx(&work->anim);
    work->followFlip = 1;
    work->age = 0;
}

s32 GlowNose2_1(EffectWork* work) {
    work->gfx = AnimUpdate(&work->anim);
    work->age++;

    if (work->age > 8) {
        return 0;
    }

    return 1;
}

void down_0(EffectWork* work, EventCharaWork* chara) {
    EvtObj* b;
    DownWork* s;
    u8 i;

    work->actor = chara;
    b = &chara->obj;

    switch (chara->arg.chara) {
    case 0:
        work->x = b->x + 4096;
        work->y = b->y - 6144;
        break;
    case 2:
        work->x = b->x - 2048;
        work->y = b->y - 6144;
        break;
    case 1:
        work->x = b->x + 3584;
        work->y = b->y - 1024;
        break;
    }

    work->tiles = AllocSpriteFrameTiles(32);
    UpdateSpriteFrameTiles(work->tiles, gLvupLogoFrames[3], gLvupLogoTiles);
    work->palette = LoadObjPalette(gCard00Palette, 32);
    work->down = EwramAlloc(sizeof(DownWork));
    s = work->down;

    for (i = 0; i < 8; i++) {
        s->angle[i] = i * 32;
        s->wobble[i] = 0;
    }
}

s32 down_1(EffectWork* work) {
    DownWork* s;
    u8 i;

    s = work->down;

    for (i = 0; i < 8; i++) {
        s->x[i] = SIN(s->angle[i]) * 8 + work->x;
        s->y[i] = -COS(s->angle[i]) * (s->wobble[i] + 4) +
                       work->y;
        s->angle[i] += 4;

        if (s->wobble[i] == 0) {
            s->wobble[i]++;
        } else {
            s->wobble[i] = 0;
        }
    }

    if (!work->actor->callbackActive) {
        return 0;
    }

    return 1;
}

s32 down_2(EffectWork* work) {
    DownWork* s;
    u16 pr;
    u8 i;

    pr = work->actor->obj.drawFlags;
    s = work->down;

    for (i = 0; i < 8; i++) {
        DrawSprite((s->x[i] >> 8) - (gEventState->x >> 8),
                   (s->y[i] >> 8) - (gEventState->y >> 8), NULL,
                   work->tiles, work->palette, NULL, pr, 50);
    }
}

void down_3(EffectWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    EwramFree(work->down);
}

void Tinkerbell_0(EffectWork* work, EventCharaWork* chara) {
    work->actor = chara;
    gEventState->particleCount = 0;
    work->timer = 0;
    TaskPoolInit(&work->tasks, 8);
}

s32 Tinkerbell_1(EffectWork* work) {
    work->timer++;

    if (work->timer == 5) {
        if (gEventState->particleCount <= 3) {
            TaskCreate(&work->tasks, &gTaskDescTinkerbellParticle, work->actor);
        }

        work->timer = 0;
    }

    TaskPoolUpdate(&work->tasks);

    return 1;
}

void Tinkerbell_2(EffectWork* work) {
    TaskPoolDraw(&work->tasks);
}

void Tinkerbell_3(EffectWork* work) {
    TaskPoolDestroy(&work->tasks);
}

void CreateTinkerbellTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescTinkerbell, work);
}

void CreateDownTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescDown, work);
}

void CreateSmokeTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescSmoke, work);
}

void CreateExclamationTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescExclamation, work);
}

void CreateBalloonTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescBalloon, work);
}

void CreateQuestionTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescQuestion, work);
}

void CreateGlowNoseTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescGlowNose, work);
}

void CreateGlowNose2Task(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescGlowNose2, work);
}

void CreateHanabiraTask(EventCharaWork* work) {
    TaskCreate(&work->tasks, &gTaskDescHanabira, work);
}

enum EvSoundFadeMode {
    EV_SOUND_FADE_MODE_NONE,
    EV_SOUND_FADE_MODE_IN,
    EV_SOUND_FADE_MODE_OUT
};

void EV_SOUND_0(EvSoundWork* work, u8* arg) {
    u8 i;

    work->eventId = arg[0];
    work->cue = 0;
    work->unk_06 = 0;
    work->fadeMode = EV_SOUND_FADE_MODE_NONE;
    work->volume = 256;
    work->soundCues = gEventSequenceDefs[work->eventId]->soundCues;
    gEventSoundMix = EwramAlloc(256);

    for (i = 0; i < 64; i++) {
        gEventSoundMix[i].pan = 0;
        gEventSoundMix[i].volume = 256;
    }
}

s32 EV_SOUND_1(EvSoundWork* work) {
    const EvSoundCue* p;
    MusicPlayerInfo* mp;
    u8 idx;
    u8 n;
    u8 i;

    if (work->soundCues == NULL) {
        return 0;
    }

    p = &work->soundCues[work->cue];

    if (gEventState->frame == p->frame) {
        if (p->song != 0xFFFF) {
            if ((p->flags & EV_SOUND_FLAG_STOP) == 0) {
                m4aSongNumStartOrContinue(p->song);
                idx = gSongTable[p->song].ms;
                m4aMPlayImmInit(gMPlayTable[idx].info);
                gEventSoundMix[idx].pan = 0;
                gEventSoundMix[idx].volume = 256;
            } else {
                m4aSongNumStop(p->song);
            }
        } else {
            m4aMPlayAllStop();
        }

        if (p->flags & EV_SOUND_FLAG_FADE_OUT) {
            m4aMPlayFadeOut(gMPlayTable[gSongTable[p->song].ms].info, 5);
            work->fadeMode = EV_SOUND_FADE_MODE_OUT;
        }

        if (p->flags & EV_SOUND_FLAG_FADE_IN) {
            n = gSongTable[p->song].ms;
            mp = gMPlayTable[n].info;
            work->volume = 3;
            m4aMPlayVolumeControl(mp, 255, 3);
            work->fadeMode = EV_SOUND_FADE_MODE_IN;
        }

        if ((p->flags & EV_SOUND_FLAG_END) == 0) {
            work->cue++;
        }
    }

    EvSoundUpdateFadeIn(work);

    for (i = 16; i <= 24; i++) {
        m4aMPlayPanpotControl(gMPlayTable[i].info, 255,
                              gEventSoundMix[i].pan);
        m4aMPlayVolumeControl(gMPlayTable[i].info, 255,
                              gEventSoundMix[i].volume);
    }

    return 1;
}

void EV_SOUND_2() {
}

void EV_SOUND_3() {
    EwramFree(gEventSoundMix);
}

void EvSoundUpdateFadeIn(EvSoundWork* work) {
    MusicPlayerInfo* mp;

    mp = gMPlayTable[0].info;

    if (work->fadeMode == EV_SOUND_FADE_MODE_IN) {
        work->volume += 2;

        if (work->volume > 255) {
            work->volume = 256;
        }

        m4aMPlayImmInit(mp);
        m4aMPlayVolumeControl(mp, 255, work->volume);
    }
}

void SetEventSoundPosition(u16 song, s16 x, s16 y) {
    u8 idx;
    s32 sx;
    s16 dx;
    s16 pan;
    s16 dist;
    s16 t;
    s16 v;
    u32 d;

    v = 0;

    if (gEventSoundMix == NULL) {
        return;
    }

    idx = gSongTable[song].ms;
    m4aMPlayImmInit(gMPlayTable[idx].info);

    if ((u16)x > 240) {
        gEventSoundMix[idx].pan = v;
        gEventSoundMix[idx].volume = v;
    }

    if ((u16)y > 160) {
        gEventSoundMix[idx].pan = v;
        gEventSoundMix[idx].volume = v;
    }

    sx = x;
    dx = sx;
    dx -= 120;
    pan = dx;

    if (pan > 127) {
        pan = 127;
    }

    if (pan < -128) {
        pan = -128;
    }

    gEventSoundMix[idx].pan = pan;

    if (120 - sx >= 0) {
        t = 120 - sx;
    } else {
        t = dx;
    }

    dist = t;

    if (80 - y * 2 < 0) {
        d = y * 2 - 80;
        t = d / 2;
    } else {
        d = 80 - y * 2;
        t = d / 2;
    }

    v = dist + t;

    if (v > 256) {
        v = 256;
    }

    gEventSoundMix[idx].volume = 256 - v;

    if (gEventSoundMix[idx].volume < 12) {
        gEventSoundMix[idx].volume = 12;
    }
}

void Event_Debug_0(EventDebugWork* work) {
    work->tiles = LoadSmallFontTiles();
    work->palette = LoadSmallFontPalette();
}

s32 Event_Debug_1(EventDebugWork* work) {
    work->digitCount = FormatSmallFontDecimal(gEventState->frame, work->digits);
    return 1;
}

void Event_Debug_2(EventDebugWork* work) {
    DrawSmallFontString(0, 0, work->digits, work->tiles, work->palette, 0, work->digitCount);
}

void Event_Debug_3(EventDebugWork* work) {
    FreeSmallFontResources(work->tiles, work->palette);
}

Mode gModeEventselect = {
    "mode_eventselect",
    (ModeInitFunc)mode_eventselect_0,
    mode_eventselect_1,
    mode_eventselect_2,
};

TaskDesc gTaskDescHanabira = {
    "Hanabira",
    (TaskInitFunc)Hanabira_0,
    (TaskUpdateFunc)Hanabira_1,
    (TaskDrawFunc)Hanabira_2,
    (TaskDestroyFunc)Hanabira_3,
    sizeof(EffectWork),
};

TaskDesc gTaskDescHanabiraC = {
    "Hanabira_c",
    (TaskInitFunc)Hanabira_c_0,
    (TaskUpdateFunc)Hanabira_c_1,
    (TaskDrawFunc)Hanabira_c_2,
    (TaskDestroyFunc)Hanabira_c_3,
    sizeof(EffectWork),
};

TaskDesc gTaskDescSmoke = {
    "smoke",
    (TaskInitFunc)smoke_0,
    (TaskUpdateFunc)EffectUpdateObj,
    (TaskDrawFunc)EffectDrawObj,
    (TaskDestroyFunc)EffectReleaseObj,
    sizeof(EffectWork),
};

TaskDesc gTaskDescExclamation = {
    "Exclamation",
    (TaskInitFunc)Exclamation_0,
    (TaskUpdateFunc)Exclamation_1,
    (TaskDrawFunc)EffectDrawObj,
    (TaskDestroyFunc)EffectReleaseObj,
    sizeof(EffectWork),
};

TaskDesc gTaskDescBalloon = {
    "balloon",
    (TaskInitFunc)balloon_0,
    (TaskUpdateFunc)EffectUpdateObj,
    (TaskDrawFunc)EffectDrawObj,
    (TaskDestroyFunc)EffectReleaseObj,
    sizeof(EffectWork),
};

TaskDesc gTaskDescQuestion = {
    "Question",
    (TaskInitFunc)Question_0,
    (TaskUpdateFunc)Question_1,
    (TaskDrawFunc)EffectDrawObj,
    (TaskDestroyFunc)EffectReleaseObj,
    sizeof(EffectWork),
};

TaskDesc gTaskDescTinkerbellParticle = {
    "GlowNose",
    (TaskInitFunc)TinkerbellParticleInit,
    (TaskUpdateFunc)TinkerbellParticleUpdate,
    (TaskDrawFunc)TinkerbellParticleDraw,
    (TaskDestroyFunc)TinkerbellParticleDestroy,
    sizeof(EffectWork),
};

TaskDesc gTaskDescGlowNose = {
    "GlowNose",
    (TaskInitFunc)GlowNose_0,
    (TaskUpdateFunc)GlowNose_1,
    (TaskDrawFunc)EffectDrawObj,
    (TaskDestroyFunc)EffectReleaseObj,
    sizeof(EffectWork),
};

TaskDesc gTaskDescGlowNose2 = {
    "GlowNose",
    (TaskInitFunc)GlowNose2_0,
    (TaskUpdateFunc)GlowNose2_1,
    (TaskDrawFunc)EffectDrawObj,
    (TaskDestroyFunc)EffectReleaseObj,
    sizeof(EffectWork),
};

TaskDesc gTaskDescDown = {
    "down",
    (TaskInitFunc)down_0,
    (TaskUpdateFunc)down_1,
    (TaskDrawFunc)down_2,
    (TaskDestroyFunc)down_3,
    sizeof(EffectWork),
};

TaskDesc gTaskDescTinkerbell = {
    "Tinkerbell",
    (TaskInitFunc)Tinkerbell_0,
    (TaskUpdateFunc)Tinkerbell_1,
    (TaskDrawFunc)Tinkerbell_2,
    (TaskDestroyFunc)Tinkerbell_3,
    sizeof(EffectWork),
};

TaskDesc gTaskDescEvSound = {
    "EV_SOUND",
    (TaskInitFunc)EV_SOUND_0,
    (TaskUpdateFunc)EV_SOUND_1,
    (TaskDrawFunc)EV_SOUND_2,
    (TaskDestroyFunc)EV_SOUND_3,
    sizeof(EvSoundWork),
};

TaskDesc gTaskDescEventDebug = {
    "Event_Debug",
    (TaskInitFunc)Event_Debug_0,
    (TaskUpdateFunc)Event_Debug_1,
    (TaskDrawFunc)Event_Debug_2,
    (TaskDestroyFunc)Event_Debug_3,
    sizeof(EventDebugWork),
};
