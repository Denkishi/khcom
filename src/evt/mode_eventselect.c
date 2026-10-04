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
#include "mode_test_api.h"
#include "malloc.h"
#include "anim.h"
#include "card.h"
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

s16 GetEventListLength(u8 a) {
    s16 n = 0;

    switch (a) {
    case 0:
        while (sSoraEventIds[n] != -1) {
            n++;
        }

        break;
    case 1:
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
    DebugTextLoadPalette(0, gUnk_08F70990, 0x20, 0);
}

void mode_eventselect_1() {
    if (GetKeysRepeat() & DPAD_UP) {
        if (sEventSelectList != 0) {
            sEventSelectList--;
        } else {
            sEventSelectList = 1;
        }
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        if (sEventSelectList == 0) {
            sEventSelectList++;
        } else {
            sEventSelectList = 0;
        }
    }

    switch (sEventSelectList) {
    case 0:
        DebugTextPrint(0, 0, 2, sEventSelectCursorText);
        DebugTextPrint(0, 10, 2, sEventSelectBlankText);
        DebugTextPrint(0, 20, 2, sEventSelectBlankText);
        break;
    case 1:
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
    case 0:
        DebugTextPrint(20, 80, 2, gEventNames[sSoraEventIds[sEventSelectIndex]]);
        break;
    case 1:
        DebugTextPrint(20, 80, 2, gEventNames[sRikuEventIds[sEventSelectIndex]]);
        break;
    }

    if (GetKeysPressed() & A_BUTTON) {
        switch (sEventSelectList) {
        case 0:
#ifdef VERSION_EU
            ModeRequest(&gModeEventDebug, sSoraEventIds[sEventSelectIndex] | 0x8000);
#else
            RequestEventMode(sSoraEventIds[sEventSelectIndex]);
#endif
            break;
        case 1:
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

void Hanabira_0(EffectWork* w, EventCharaWork* chara) {
    s32 i;

    TaskPoolInit(&w->tasks, 16);

    for (i = 15; i >= 0; i--) {
        TaskCreate(&w->tasks, &gTaskDescHanabiraC, chara);
    }
}

s32 Hanabira_1(EffectWork* w) {
    TaskPoolUpdate(&w->tasks);

    return 1;
}

void Hanabira_2(EffectWork* w) {
    TaskPoolDraw(&w->tasks);
}

void Hanabira_3(EffectWork* w) {
    TaskPoolDestroy(&w->tasks);
}

void Hanabira_c_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;
    w->palette = LoadObjPalette(gMaruxhaBtEffPalette, 32);
    w->tiles = LoadObjTiles(gMaruxhaBtEff2Tiles, 256);
    w->x = b->x;
    w->y = b->y;
    w->z = b->z - 0x3000;
    w->vx = GetRandom() % 717 - 358;
    w->vz = -(GetRandom() % 539 + 102);
    AnimInit(&w->anim, gMaruxhaBtEff2Anims, gMaruxhaBtEff2Frames);
    AnimStart(&w->anim, GetRandom() & 1, ANIM_FLAG_LOOP);
    w->state = 0;
}

s32 Hanabira_c_1(EffectWork* w) {
    s32 v;
    s32 r;

    switch (w->state) {
    case 0:
        w->x += w->vx;
        w->z += w->vz;
        w->vz += 17;

        if (w->vz > 256) {
            w->state = 1;
        }

        break;
    case 1:
        w->x += w->vx;
        w->z += w->vz;
        w->vz = (v = w->vz - 12) - (r = GetRandom()) % 9;

        if (w->vz < 0) {
            w->vz = GetRandom() % 181 + 204;

            if (w->vx > 0) {
                w->vx = -(GetRandom() % 257 + 128);
            } else {
                w->vx = GetRandom() % 257 + 128;
            }
        }

        if (w->z >= 0) {
            return 0;
        }

        break;
    }

    w->gfx = AnimUpdate(&w->anim);

    return 1;
}

void Hanabira_c_2(EffectWork* w) {
    s32 x;
    s32 y;
    s32 t;

    x = (w->x >> 8) - (gEventState->x >> 8);
    t = w->y >> 8;
    y = t + (w->z >> 8) - (gEventState->y >> 8);
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, NULL, SPRITE_PRIORITY(2), -0x1004 - t * 4);
}

void Hanabira_c_3(EffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void smoke_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;
    w->x = b->x;
    w->y = b->y - 0x800;
    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    SetObjTileSource(w->tiles, gUnk_093215CA);
    AnimInit(&w->anim, gUnk_09EEFD78, gUnk_09EEFD60);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 1;
    w->age = 0;
}

void Exclamation_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;
    w->x = b->x;
    w->y = b->y;
    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);

    if (!FadeIsActive()) {
        FadeSetPaletteExcluded(((ObjPaletteHeader*)w->palette)->index + 16, 1);
    }

    SetObjTileSource(w->tiles, gFEventTiles);
    AnimInit(&w->anim, gFEventAnims, gFEventFrames);
    AnimStart(&w->anim, 0, 0);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 1;
    w->age = 0;
}

void balloon_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;
    w->x = b->x;
    w->y = b->y;
    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    SetObjTileSource(w->tiles, gFEventTiles);
    AnimInit(&w->anim, gFEventAnims, gFEventFrames);
    AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 0;
    w->age = 0;
}

s32 EffectUpdateObj(EffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (!w->actor->callbackActive) {
        return 0;
    }

    return 1;
}

s32 Exclamation_1(EffectWork* w) {
    w->age++;
    w->gfx = AnimUpdate(&w->anim);

    if (!w->actor->callbackActive || w->age == 50) {
        return 0;
    }

    return 1;
}

void EffectDrawObj(EffectWork* w) {
    u16 pr;
    s32 y;

    pr = w->actor->obj.drawFlags;

    if (!w->followFlip) {
        pr &= 0xFFFE;
    }

    DrawSprite((w->x >> 8) - (gEventState->x >> 8),
               (y = (w->y >> 8) + gEventCharaParams[w->actor->arg.chara].spriteYOffset) -
                   (gEventState->y >> 8),
               w->gfx, w->tiles, w->palette, NULL, pr, 50);
}

void EffectReleaseObj(EffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void Question_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;
    w->x = b->x;
    w->y = b->y;
    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    SetObjTileSource(w->tiles, gFEventTiles);
    AnimInit(&w->anim, gFEventAnims, gFEventFrames);
    AnimStart(&w->anim, 5, 0);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 0;
    w->timer = 0;
    w->age = 0;
}

s32 Question_1(EffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);
    w->timer++;

    if (w->timer == 12) {
        AnimStart(&w->anim, 6, ANIM_FLAG_LOOP);
    }

    if (!w->actor->callbackActive) {
        return 0;
    }

    w->age = 0;

    return 1;
}

void TinkerbellParticleInit(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;
    s32 d1;
    s32 d2;
    s32 k;

    w->actor = chara;
    b = &chara->obj;
    k = 0x400;
    d1 = (GetRandom() % 9 << 8) - k;
    w->x = b->x + d1;
    d2 = (GetRandom() % 9 << 8) - k;
    w->y = b->y + d2;
    w->z2 = b->z;
    w->vx = GetRandom() % 232 + 76;
    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    SetObjTileSource(w->tiles, gUnk_088A5D7A);
    AnimInit(&w->anim, gUnk_09EDE7E4, gUnk_09EDE7B4);
    AnimStart(&w->anim, GetRandom() % 3, 0);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 0;
    w->age = 0;
    gEventState->particleCount++;
}

s32 TinkerbellParticleUpdate(EffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);
    w->age++;
    w->z2 += 256;

    if (w->z2 > 0) {
        return 0;
    }

    return 1;
}

void TinkerbellParticleDraw(EffectWork* w) {
    u16 pr;

    pr = w->actor->obj.drawFlags;

    if (!w->followFlip) {
        pr &= 0xFFFE;
    }

    DrawSprite((w->x >> 8) - (gEventState->x >> 8),
               ((w->y + w->z2) >> 8) - (gEventState->y >> 8),
               w->gfx, w->tiles, w->palette, NULL, pr,
               -0x1004 - (w->y >> 8) * 4);
}

void TinkerbellParticleDestroy(EffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    gEventState->particleCount--;
}

void GlowNose_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;
    w->x = b->x - 1536;
    w->y = b->y + 3072;
    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    SetObjTileSource(w->tiles, gUnk_09321804);
    AnimInit(&w->anim, gUnk_09EEFD9C, gUnk_09EEFD7C);
    AnimStart(&w->anim, 0, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 1;
    w->age = 0;
}

s32 GlowNose_1(EffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);
    w->age++;

    if (w->age > 44) {
        return 0;
    }

    return 1;
}

void GlowNose2_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;

    w->actor = chara;
    b = &chara->obj;

    switch (chara->arg.chara) {
    case 3:
        w->x = b->x - 6144;
        w->y = b->y + 8192;
        break;
    case 43:
        w->x = b->x + 2048;
        w->y = b->y + 2048;
        break;
    }

    w->tiles = AllocObjTiles(128, NULL);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    SetObjTileSource(w->tiles, gUnk_09321804);
    AnimInit(&w->anim, gUnk_09EEFD9C, gUnk_09EEFD7C);
    AnimStart(&w->anim, 1, ANIM_FLAG_LOOP);
    w->gfx = AnimGetGfx(&w->anim);
    w->followFlip = 1;
    w->age = 0;
}

s32 GlowNose2_1(EffectWork* w) {
    w->gfx = AnimUpdate(&w->anim);
    w->age++;

    if (w->age > 8) {
        return 0;
    }

    return 1;
}

void down_0(EffectWork* w, EventCharaWork* chara) {
    EvtObj* b;
    DownWork* s;
    u8 i;

    w->actor = chara;
    b = &chara->obj;

    switch (chara->arg.chara) {
    case 0:
        w->x = b->x + 4096;
        w->y = b->y - 6144;
        break;
    case 2:
        w->x = b->x - 2048;
        w->y = b->y - 6144;
        break;
    case 1:
        w->x = b->x + 3584;
        w->y = b->y - 1024;
        break;
    }

    w->tiles = AllocSpriteFrameTiles(32);
    UpdateSpriteFrameTiles(w->tiles, gUnk_09EEA19C[3], gUnk_0908C686);
    w->palette = LoadObjPalette(gCard00Palette, 32);
    w->down = EwramAlloc(sizeof(DownWork));
    s = w->down;

    for (i = 0; i < 8; i++) {
        s->angle[i] = i * 32;
        s->wobble[i] = 0;
    }
}

s32 down_1(EffectWork* w) {
    DownWork* s;
    u8 i;

    s = w->down;

    for (i = 0; i < 8; i++) {
        s->x[i] = gSineTable[s->angle[i] & 0xFF] * 8 + w->x;
        s->y[i] = -gSineTable[(s->angle[i] & 0xFF) + 64] * (s->wobble[i] + 4) +
                       w->y;
        s->angle[i] += 4;

        if (s->wobble[i] == 0) {
            s->wobble[i]++;
        } else {
            s->wobble[i] = 0;
        }
    }

    if (!w->actor->callbackActive) {
        return 0;
    }

    return 1;
}

s32 down_2(EffectWork* w) {
    DownWork* s;
    u16 pr;
    u8 i;

    pr = w->actor->obj.drawFlags;
    s = w->down;

    for (i = 0; i < 8; i++) {
        DrawSprite((s->x[i] >> 8) - (gEventState->x >> 8),
                   (s->y[i] >> 8) - (gEventState->y >> 8), NULL,
                   w->tiles, w->palette, NULL, pr, 50);
    }
}

void down_3(EffectWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    EwramFree(w->down);
}

void Tinkerbell_0(EffectWork* w, EventCharaWork* chara) {
    w->actor = chara;
    gEventState->particleCount = 0;
    w->timer = 0;
    TaskPoolInit(&w->tasks, 8);
}

s32 Tinkerbell_1(EffectWork* w) {
    w->timer++;

    if (w->timer == 5) {
        if (gEventState->particleCount <= 3) {
            TaskCreate(&w->tasks, &gTaskDescTinkerbellParticle, w->actor);
        }

        w->timer = 0;
    }

    TaskPoolUpdate(&w->tasks);

    return 1;
}

void Tinkerbell_2(EffectWork* w) {
    TaskPoolDraw(&w->tasks);
}

void Tinkerbell_3(EffectWork* w) {
    TaskPoolDestroy(&w->tasks);
}

void CreateTinkerbellTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescTinkerbell, p);
}

void CreateDownTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescDown, p);
}

void CreateSmokeTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescSmoke, p);
}

void CreateExclamationTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescExclamation, p);
}

void CreateBalloonTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescBalloon, p);
}

void CreateQuestionTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescQuestion, p);
}

void CreateGlowNoseTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescGlowNose, p);
}

void CreateGlowNose2Task(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescGlowNose2, p);
}

void CreateHanabiraTask(EventCharaWork* p) {
    TaskCreate(&p->tasks, &gTaskDescHanabira, p);
}

void EV_SOUND_0(EvSoundWork* w, u8* arg) {
    u8 i;

    w->eventId = arg[0];
    w->cue = 0;
    w->unk_06 = 0;
    w->fadeMode = 0;
    w->volume = 256;
    w->soundCues = gEventSequenceDefs[w->eventId]->soundCues;
    gEventSoundMix = EwramAlloc(256);

    for (i = 0; i < 64; i++) {
        gEventSoundMix[i].pan = 0;
        gEventSoundMix[i].volume = 256;
    }
}

s32 EV_SOUND_1(EvSoundWork* w) {
    const EvSoundCue* p;
    MusicPlayerInfo* mp;
    u8 idx;
    u8 n;
    u8 i;

    if (w->soundCues == NULL) {
        return 0;
    }

    p = &w->soundCues[w->cue];

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
            w->fadeMode = 2;
        }

        if (p->flags & EV_SOUND_FLAG_FADE_IN) {
            n = gSongTable[p->song].ms;
            mp = gMPlayTable[n].info;
            w->volume = 3;
            m4aMPlayVolumeControl(mp, 255, 3);
            w->fadeMode = 1;
        }

        if ((p->flags & EV_SOUND_FLAG_END) == 0) {
            w->cue++;
        }
    }

    EvSoundUpdateFadeIn(w);

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

void EvSoundUpdateFadeIn(EvSoundWork* w) {
    MusicPlayerInfo* mp;

    mp = gMPlayTable[0].info;

    if (w->fadeMode == 1) {
        w->volume += 2;

        if (w->volume > 255) {
            w->volume = 256;
        }

        m4aMPlayImmInit(mp);
        m4aMPlayVolumeControl(mp, 255, w->volume);
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
