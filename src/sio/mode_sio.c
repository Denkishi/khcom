#include "macros.h"
#include "mode_sio_dbg.h"
#include "mode_chkobj_assets.h"
#include "registration_data.h"
#include "system_state.h"
#include "chara_api.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_sio_api.h"
#include "m4a_song.h"
#include "pallet.h"
#include "sio_api.h"
#include "display.h"
#include "text.h"
#include "monsgage.h"
#include "mode_sio.h"
#include "gba/keys.h"
#include "btl.h"
#include "event_background_assets.h"
#include "jiminy_data.h"
#include "jiminy_text_assets.h"
#include "map.h"
#include "mode_dummy.h"
#include "sprites_boss_tm.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_sora.h"
#include "battle_backgrounds.h"
#include "sprites_msg.h"
#include "link_menus.h"
#include "sprites_card_pictures.h"
#include "sprites_card.h"
#include "card_ids.h"
#include "malloc.h"
#include "fade.h"
#include "card_deck.h"
#include "mode_test_api.h"
#include "songs.h"
#include "common_text.h"

u16 gSioWinCount EWRAM_COMMON(4);
u16 gSioLoseCount EWRAM_COMMON(4);
s8 gSioWorldCursor EWRAM_COMMON(16);
CharaLinkData gCharaLinkRecv EWRAM_COMMON(16);
u8 gSioDeckNames[2][20] EWRAM_COMMON(16);
u8 gSioHandicaps[2] EWRAM_COMMON(4);
u8 gSioDeckNameRecv[2][20] EWRAM_COMMON(16);
u8 gSioWorldCount EWRAM_COMMON(4);
s8 gSioDeckNameChunk EWRAM_COMMON(4);
s8 gSioPrevWorldCursor EWRAM_COMMON(4);
s8 gSioWorldList[14] EWRAM_COMMON(16);
u8 gSioSavedWorld EWRAM_COMMON(4);
CharaLinkData gCharaLinkSend EWRAM_COMMON(16);
u8 gSioDeckNameRecvBuf[2][20] EWRAM_COMMON(16);
#ifdef VERSION_EU
s8 gSioDebugReady[2] EWRAM_COMMON(4);
#endif
#ifndef VERSION_EU
s8 gSioChgCardCursor EWRAM_COMMON(16);
u16 gSioChgCardSlots[10] EWRAM_COMMON(16);
s8 gSioChgCardReady[2] EWRAM_COMMON(4);
#endif

Mode gModeSioBattle = {
    "mode_sio_battle",
    mode_sio_battle_0,
    mode_sio_battle_1,
    mode_sio_battle_2,
};

Mode gModeSioBtlConnect = {
    "mode_sio_btl_connect",
    mode_sio_btl_connect_0,
    mode_sio_btl_connect_1,
    mode_sio_btl_connect_2,
};

static const SioAnimDef sSioBtlOptionAnimDefs[2] = {
    {gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0},
    {gSor1ll51Frames, gSor1ll51Anims, gSor1ll51Tiles, 0},
};

#ifndef VERSION_EU
extern const SioAnimDef gSioChgCardAnimDefs[3];
#endif

#ifdef VERSION_EU
#include "link_deck_names.inc"
#endif

#ifdef VERSION_EU

#endif

extern SioWorldEntry gSioWorldEntries[];
extern s8 gSioHandicapMarkerX[];
extern u16 gSioHandicapAp[];
#ifndef VERSION_EU
extern SioChgCardPos gSioChgCardSlotPos[];
#endif

static SioBtlConnectWork* gSioBtlConnectWork;
static SioBtlOptionWork* gSioBtlOptionWork;
static SioBtlCardgetWork* gSioBtlCardgetWork;
#ifndef VERSION_EU
static SioBtlConnectWork* gSioChgConnectWork;
static SioChgCardWork* gSioChgCardWork;
#endif
static SioErrorWork* gSioErrorWork;

void mode_sio_btl_connect_0(s32 arg) {
    gSioBtlConnectWork = EwramAlloc(sizeof(SioBtlConnectWork));
    FadeStartIn(0, 16);
    SetBgMode0();
    SetupBg(0, 0, 7, 15);
    SetupBg(1, 1, 31, 0);
    EnableBg(0);
    EnableBg(1);
    LoadBgTiles(0, gUnk_096AD604, 0x140);
    LoadBgMap(0, gUnk_096F6464, 0x800);
    LoadBgPalette(0, gCard00Palette, 0x20);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5C64, 0x800);
    gSioBtlConnectWork->unk_00 = 0;
    gSioBtlConnectWork->timer = 0;
    gSioBtlConnectWork->state = 0;
    gSioBtlConnectWork->textSlotCount = 0;
    InitTextSlots(gSioBtlConnectWork->textSlots, SIO_CONNECT_TEXT_SLOTS);
#ifdef VERSION_EU
    gSioBtlConnectWork->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_08891508), gSioBtlConnectWork->textSlots);
#else
    gSioBtlConnectWork->textSlotCount = LoadTextSlots(gUnk_08159E4A, gSioBtlConnectWork->textSlots);
#endif
    gSioBtlConnectWork->palette = LoadObjPalette(gUnk_096FBAA4, 32);
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
        SioReset();
        SioConnectInit(SioBtlConnectOnConnect, SioBtlConnectOnCancel, 0);
    }
#else
    SioReset();
    SioConnectInit(SioBtlConnectOnConnect, SioBtlConnectOnCancel, 0);
#endif
}

void mode_sio_btl_connect_1(void) {
    s32 i;
    s32 j;

#ifdef VERSION_EU
    s16 width;
    s16 x;
    if (gSioDebugMode == 0) {
#endif
    switch (gSioBtlConnectWork->state) {
    case 0:
        SioConnectUpdate();
        break;
    case 1:
        SioConnectUpdate();
        gSioBtlConnectWork->timer++;
        if (gSioBtlConnectWork->timer > 4) {
            SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
            SioPrepareCharaLinkExchange();
            gSystemFlags |= SYSTEM_FLAG_LINK_ACTIVE;
            gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
            gSioBtlConnectWork->state++;
        }
        break;
    case 2:
        if (gSioLinkResult == 2) {
            gSioBtlConnectWork->timer = 0;
            SioInitWorldList();
            gSioBtlConnectWork->state++;
        }
        break;
    case 3:
        gSioBtlConnectWork->timer++;
        if (gSioBtlConnectWork->timer > 4) {
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
            gSioWorldCursor = 1;
            gSioPrevWorldCursor = 1;
            gSioDeckNameChunk = 1;
            gSioHandicaps[0] = 6;
            gSioHandicaps[1] = 6;

            for (i = 0; i < 2; i++) {
                for (j = 0; j < 20; j++) {
                    gSioDeckNameRecv[i][j] = 0;
                    gSioDeckNameRecvBuf[i][j] = 0;
                    gSioDeckNames[i][j] = 0;
                }
            }
            gSioWinCount = 0;
            gSioLoseCount = 0;
            ModeRequest(&gModeSioBtlOption, 0);
            return;
        }
        break;
    }
#ifdef VERSION_EU
    } else if (GetKeysPressed() & (A_BUTTON | START_BUTTON)) {
        gSioWorldCursor = 1;
        gSioPrevWorldCursor = 1;
        gSioDeckNameChunk = 1;
        gSioHandicaps[0] = 6;
        gSioHandicaps[1] = 6;

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 20; j++) {
                gSioDeckNameRecv[i][j] = 0;
                gSioDeckNameRecvBuf[i][j] = 0;
                gSioDeckNames[i][j] = 0;
            }
        }
        SioDbgApplySettings();
        SioInitWorldList();
        ModeRequest(&gModeSioBtlOption, 0);
    }
    width = eu_0806629C(gSioBtlConnectWork->textSlots, gSioBtlConnectWork->textSlotCount);
    if (gLanguage == 1) {
        x = 120 - (width >> 1);
        DrawTextSlots(x, 68, gSioBtlConnectWork->textSlots, gSioBtlConnectWork->palette, 20, gSioBtlConnectWork->textSlotCount);
    } else {
        x = 120 - (width >> 1);
        DrawTextSlots(x, 63, gSioBtlConnectWork->textSlots, gSioBtlConnectWork->palette, 20, gSioBtlConnectWork->textSlotCount);
    }
#elif defined(VERSION_JP)
    DrawTextSlots(0x3D, 0x3F, gSioBtlConnectWork->textSlots, gSioBtlConnectWork->palette, 20, gSioBtlConnectWork->textSlotCount);
#else
    DrawTextSlots(0x42, 0x3F, gSioBtlConnectWork->textSlots, gSioBtlConnectWork->palette, 20, gSioBtlConnectWork->textSlotCount);
#endif
}

void mode_sio_btl_connect_2(void) {
    ReleaseObjPalette(gSioBtlConnectWork->palette);
    FreeTextSlots(gSioBtlConnectWork->textSlots, SIO_CONNECT_TEXT_SLOTS);
    EwramFree(gSioBtlConnectWork);
}

void SioBtlConnectOnConnect(void) {
    m4aSongNumStart(SONG_SYS_ITEMGET);
    gSioBtlConnectWork->state++;
}

void SioBtlConnectOnCancel(void) {
    m4aSongNumStart(SONG_SYS_CLOSE);
    ModeRequest(&gModeSioBattle, 2);
}

void SioInitWorldList(void) {
    s32 i;
    s32 flags;
    gSioWorldCount = 0;

    for (i = 0; i < 13; i++) {
        gSioWorldList[i] = 0;
    }
    flags = 0x1FFE;

    for (i = 1; i < 14; i++) {
        if ((flags >> i) & 1) {
            gSioWorldList[gSioWorldCount + 1] = i;
            gSioWorldCount++;
        }
    }
}

void SetSioBtlOptionAnimation(u16 a, u16 b, u16 c) {
    const SioAnimDef* def = &sSioBtlOptionAnimDefs[b];
    AnimChangeWithTables(&gSioBtlOptionWork->anim2[a], def->animId, c, def->anims, def->gfxTable);
    SetObjTileSource(gSioBtlOptionWork->unk_008[a], def->tiles);
}

void mode_sio_btl_option_0(s32 arg) {
    gSioBtlOptionWork = EwramAlloc(sizeof(SioBtlOptionWork));
    SetBgMode1();
    SetupBg(0, 0, 7, 10);
    SetBgPriority(0, 0);
    SetBgOverflow(0, 1);
    SetBgSize(0, 0);
    SetupBg(1, 0, 15, 10);
    SetBgPriority(1, 1);
    SetBgOverflow(1, 1);
    SetBgSize(1, 0);
    SetupBg(2, 2, 24, 0);
    SetBgPriority(2, 2);
    SetBgOverflow(2, 1);
    SetBgSize(2, 0x8000);
    RequestDma3Copy(gUnk_096AD744, GetBgCharBase(0), 0x2000);
#ifdef VERSION_EU
    InitTextSlots(gSioBtlOptionWork->textSlots, 40);
    InitTextSlots(gSioBtlOptionWork->textSlots2, 20);
    InitTextSlots(gSioBtlOptionWork->textSlots3, 20);
    if (gSioDebugMode == 0) {
        gSioBtlOptionWork->textSlotCount2 = LoadTextSlots(gSioDeckNames[0], gSioBtlOptionWork->textSlots2);
        gSioBtlOptionWork->textSlotCount3 = LoadTextSlots(gSioDeckNames[1], gSioBtlOptionWork->textSlots3);
    } else {
        gSioBtlOptionWork->textSlotCount2 = LoadTextSlots((u16*)gUnkEu_095DA860, gSioBtlOptionWork->textSlots2);
        gSioBtlOptionWork->textSlotCount3 = LoadTextSlots((u16*)gUnkEu_095DA867, gSioBtlOptionWork->textSlots3);
    }
#else
    InitTextSlots(gSioBtlOptionWork->textSlots, 20);
    InitTextSlots(gSioBtlOptionWork->textSlots2, 10);
    InitTextSlots(gSioBtlOptionWork->textSlots3, 10);
    gSioBtlOptionWork->textSlotCount2 = LoadTextSlots(gSioDeckNames[0], gSioBtlOptionWork->textSlots2);
    gSioBtlOptionWork->textSlotCount3 = LoadTextSlots(gSioDeckNames[1], gSioBtlOptionWork->textSlots3);
#endif
    gSioBtlOptionWork->palette7 = LoadObjPalette(gUnk_096FBCC4, 32);
    gSioBtlOptionWork->palette8 = LoadObjPalette(gUnk_096FBCC4 + 64, 32);
    gSioBtlOptionWork->palette9 = LoadObjPalette(gUnk_096FBCC4 + 32, 32);
    gSioBtlOptionWork->worldEntry = gSioWorldList[gSioWorldCursor];
    DisableBg(0);
    DisableBg(1);
    gSioBtlOptionWork->modeArg = arg;
    gSioBtlOptionWork->state = 0;
}

void SioBtlOptionLoadBg(void) {
    RequestDma3Copy(gUnk_096AF744, (u8*)GetBgCharBase(0) + 0x2000, 0x800);
#ifdef VERSION_EU
    switch (gLanguage) {
    case 0:
        LoadBgMap(0, gUnk_096F6C64, 0x800);
        LoadBgMap(1, gUnk_096F7464, 0x800);
        break;
    case 3:
        LoadBgMap(0, gUnkEu_096C298C, 0x800);
        LoadBgMap(1, gUnkEu_096C498C, 0x800);
        break;
    case 1:
        LoadBgMap(0, gUnkEu_096C198C, 0x800);
        LoadBgMap(1, gUnkEu_096C398C, 0x800);
        break;
    case 4:
        LoadBgMap(0, gUnkEu_096C218C, 0x800);
        LoadBgMap(1, gUnkEu_096C418C, 0x800);
        break;
    case 2:
    default:
        LoadBgMap(0, gUnkEu_096C318C, 0x800);
        LoadBgMap(1, gUnkEu_096C518C, 0x800);
        break;
    }
#else
    LoadBgMap(0, gUnk_096F6C64, 0x800);
#endif
    LoadBgPalette(0, gUnk_096FBC04, 0xC0);
#ifndef VERSION_EU
    LoadBgMap(1, gUnk_096F7464, 0x800);
#endif
    DisableBg(0);
    DisableBg(1);
    gSioBtlOptionWork->state = 1;
}

void SioBtlOptionInitObjs(void) {
    s32 i;

#ifdef VERSION_EU
    RequestDma3Copy(gUnkEu_0967CB6C, (u8*)GetBgCharBase(0) + 0x49E0, 0x1620);
#endif

    if (gSioBtlOptionWork->modeArg == 1) {
        gSioBtlOptionWork->menuOpen = 1;
        gSioBtlOptionWork->cursor = 1;
        gSioBtlOptionWork->y = gSioBtlOptionWork->cursor * 4608 + 10752;
    } else {
        gSioBtlOptionWork->menuOpen = 0;
        gSioBtlOptionWork->cursor = 0;
        gSioBtlOptionWork->y = 10752;
    }
    gSioBtlOptionWork->fadeLevel = 0;
    gSioBtlOptionWork->timer = 0;
    gSioBtlOptionWork->player1Ready = 0;
    gSioBtlOptionWork->player2Ready = 0;
    gSioBtlOptionWork->worldChangeState = 0;
    gSioBtlOptionWork->frameCount = 0;
    gSioBtlOptionWork->leaveDelay = 0;
    gSioBtlOptionWork->unk_418 = 0;
    SetBgAffine(2, 0, 256, 256, 0x10000, 0x16800);

    for (i = 0; i < 2; i++) {
        gSioBtlOptionWork->unk_008[i] = AllocObjTiles(0xC80, 0);
        AnimInit(&gSioBtlOptionWork->anim2[i], 0, 0);
        SetSioBtlOptionAnimation(i, 0, 0);
        gSioBtlOptionWork->gfx6[i] = AnimGetGfx(&gSioBtlOptionWork->anim2[i]);
    }

    if (gSioPlayerId == 0) {
        gSioBtlOptionWork->unk_008[2] = LoadObjPalette(gSoraPalette, 32);
        gSioBtlOptionWork->unk_008[3] = LoadObjPalette(gUnk_096FAC64, 32);
    } else {
        gSioBtlOptionWork->unk_008[2] = LoadObjPalette(gUnk_096FAC64, 32);
        gSioBtlOptionWork->unk_008[3] = LoadObjPalette(gSoraPalette, 32);
    }
#ifdef VERSION_EU
    gSioBtlOptionWork->palette = LoadObjPalette(gUnk_096FBD24, 32);
    switch (gLanguage) {
    case 0:
        gSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F18BE, 0xC00);
        gSioBtlOptionWork->gfx = gUnkEu_09F7EBB0[0];
        break;
    case 3:
        gSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F3D12, 0xC00);
        gSioBtlOptionWork->gfx = gUnkEu_09F7EBC8[0];
        break;
    case 1:
        gSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F24DA, 0xC00);
        gSioBtlOptionWork->gfx = gUnkEu_09F7EBB8[0];
        break;
    case 4:
        gSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F30F6, 0xC00);
        gSioBtlOptionWork->gfx = gUnkEu_09F7EBC0[0];
        break;
    case 2:
    default:
        gSioBtlOptionWork->tiles = LoadObjTiles(gUnkEu_095F492E, 0xC00);
        gSioBtlOptionWork->gfx = gUnkEu_09F7EBD0[0];
        break;
    }
#else
    gSioBtlOptionWork->tiles = LoadObjTiles(gUnk_0962BEDA, 0xC00);
    gSioBtlOptionWork->palette = LoadObjPalette(gUnk_096FBD24, 32);
    gSioBtlOptionWork->gfx = gUnk_09EF38D4[0];
#endif
    gSioBtlOptionWork->tiles2 = LoadObjTiles(gUnk_0962B090, 0x1C0);
    gSioBtlOptionWork->palette2 = LoadObjPalette(gUnk_096FBAA4, 32);
    AnimInit(&gSioBtlOptionWork->anim, gUnk_09EF38B4, gUnk_09EF3894);
    AnimStart(&gSioBtlOptionWork->anim, 1, 1);
    gSioBtlOptionWork->gfx2 = AnimGetGfx(&gSioBtlOptionWork->anim);
    gSioBtlOptionWork->cursorVisible = 1;
    gSioBtlOptionWork->tiles3 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    gSioBtlOptionWork->palette3 = LoadObjPalette(gCard00Palette, 32);
    gSioBtlOptionWork->gfx3 = gUnk_09EF1278[0];
    gSioBtlOptionWork->messageVisible = 0;
#ifdef VERSION_EU
    InitTextSlots(gSioBtlOptionWork->textSlots4, 120);
    gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891580), gSioBtlOptionWork->textSlots4);
#else
    InitTextSlots(gSioBtlOptionWork->textSlots4, 60);
    gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815A20C, gSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
    gSioBtlOptionWork->x = 68;
#else
    gSioBtlOptionWork->x = 65;
#endif
    gSioBtlOptionWork->y2 = 124;
    gSioBtlOptionWork->palette6 = LoadObjPalette(gUnk_096FBAA4, 32);
#ifdef VERSION_EU
    gSioBtlOptionWork->tiles4 = LoadObjTiles(gUnkEu_095EC758, 0x120);
#else
    gSioBtlOptionWork->tiles4 = LoadObjTiles(gUnk_0962D7C0, 0x120);
#endif
    gSioBtlOptionWork->palette4 = LoadObjPalette(gUnk_096FBD44, 32);
#ifdef VERSION_EU
    gSioBtlOptionWork->gfx4 = gUnkEu_09F7EB08[0];
    gSioBtlOptionWork->gfx7 = gUnkEu_09F7EB08[1];
    gSioBtlOptionWork->gfx8 = gUnkEu_09F7EB08[2];
#else
    gSioBtlOptionWork->gfx4 = gUnk_09EF38EC[0];
    gSioBtlOptionWork->gfx7 = gUnk_09EF38EC[1];
    gSioBtlOptionWork->gfx8 = gUnk_09EF38EC[2];
#endif
    gSioBtlOptionWork->handicapMarkerVisible = 0;
#ifdef VERSION_EU
    gSioBtlOptionWork->tiles5[0] = LoadObjTiles(gUnkEu_095EC898, 0x280);
#else
    gSioBtlOptionWork->tiles5[0] = LoadObjTiles(gUnk_0962D900, 0x280);
#endif
    gSioBtlOptionWork->palette5[0] = LoadObjPalette(gUnk_096FBD64, 32);
#ifdef VERSION_EU
    gSioBtlOptionWork->gfx5[0] = gUnkEu_09F7EB18[0];
#else
    gSioBtlOptionWork->gfx5[0] = gUnk_09EF38FC[0];
#endif
    gSioBtlOptionWork->handicaps[0] = gSioHandicaps[0];
#ifdef VERSION_EU
    gSioBtlOptionWork->tiles5[1] = LoadObjTiles(gUnkEu_095ECB38, 0x280);
#else
    gSioBtlOptionWork->tiles5[1] = LoadObjTiles(gUnk_0962DBA0, 0x280);
#endif
    gSioBtlOptionWork->palette5[1] = LoadObjPalette(gUnk_096FBDA4, 32);
#ifdef VERSION_EU
    gSioBtlOptionWork->gfx5[1] = gUnkEu_09F7EB20[0];
#else
    gSioBtlOptionWork->gfx5[1] = gUnk_09EF3904[0];
#endif
    gSioBtlOptionWork->handicaps[1] = gSioHandicaps[1];

    if (gSioPlayerId == 0) {
        gSioBtlOptionWork->handicap = gSioHandicaps[0];
    } else {
        gSioBtlOptionWork->handicap = gSioHandicaps[1];
    }
    SioBtlOptionDrawStats();
    gSioBtlOptionWork->state = 2;
}

void SioBtlOptionLoadWorld(void) {
    s8 i = gSioWorldList[gSioWorldCursor];
    RequestDma3Copy(gSioWorldEntries[i].tiles, GetBgCharBase(2), 0x2000);
    LoadBgPalette(2, gSioWorldEntries[i].palette, gSioWorldEntries[i].paletteSize);
#ifdef VERSION_EU
    eu_080059F4(2, gSioWorldEntries[i].map);
    gSioBtlOptionWork->textSlotCount = LoadTextSlots(eu_0805E924(gSioWorldEntries[i].text), gSioBtlOptionWork->textSlots);
#else
    LoadBgMap(2, gSioWorldEntries[i].map, gSioWorldEntries[i].mapSize);
    gSioBtlOptionWork->textSlotCount = LoadTextSlots(gSioWorldEntries[i].text, gSioBtlOptionWork->textSlots);
#endif
    DisableBg(2);
    gSioBtlOptionWork->state++;
}

void SioBtlOptionFadeIn(void) {
    s8 i = gSioWorldList[gSioWorldCursor];
    FadeStartIn(0, 16);
    RequestDma3Copy((u8*)gSioWorldEntries[i].tiles + 0x2000, (u8*)GetBgCharBase(2) + 0x2000, gSioWorldEntries[i].tilesSize - 0x2000);
    EnableBg(0);
    EnableBg(1);
    EnableBg(2);
    SioBtlOptionPlayWorldBgm();
    gSioBtlOptionWork->returnState = 4;
    gSioBtlOptionWork->state = 4;
}

void mode_sio_btl_option_1(void) {
    switch (gSioBtlOptionWork->state) {
    case 0:
        SioBtlOptionLoadBg();
        break;
    case 1:
        SioBtlOptionInitObjs();
        break;
    case 2:
        SioBtlOptionLoadWorld();
        break;
    case 3:
        SioBtlOptionFadeIn();
        break;
    case 4:
        SioBtlOptionWaitStart();
        break;
    case 5:
        SioBtlOptionHandleIdle();
        SioBtlOptionDraw();
        break;
    case 6:
        SioBtlOptionHandleMenu();
        SioBtlOptionDraw();
        break;
    case 7:
        SioBtlOptionSetHandicap();
        SioBtlOptionDraw();
        break;
    case 8:
        SioBtlOptionChangeWorld();
        SioBtlOptionDraw();
        break;
    case 9:
        SioBtlOptionWaitReady();
        SioBtlOptionDraw();
        break;
    case 10:
        SioBtlOptionConfirm();
        SioBtlOptionDraw();
        break;
    case 11:
        SioBtlOptionStartDeckExchange();
        SioBtlOptionDraw();
        break;
    case 12:
        SioBtlOptionWaitDeckExchange();
        SioBtlOptionDraw();
        break;
    case 13:
        SioBtlOptionResumeCommands();
        SioBtlOptionDraw();
        break;
    case 14:
        func_080B041C();
        SioBtlOptionDraw();
        break;
    case 15:
        SioBtlOptionSyncStart();
        SioBtlOptionDraw();
        break;
    case 16:
        SioBtlOptionStartBattle();
        SioBtlOptionDraw();
        break;
    }
}

void SioBtlOptionDraw(void) {
#ifdef VERSION_EU
    s16 width;
    s32 multiline;
    s32 i;
#endif
    gSioBtlOptionWork->gfx6[0] = AnimUpdate(&gSioBtlOptionWork->anim2[0]);
    gSioBtlOptionWork->gfx6[1] = AnimUpdate(&gSioBtlOptionWork->anim2[1]);
    gSioBtlOptionWork->gfx2 = AnimUpdate(&gSioBtlOptionWork->anim);
    DrawSprite(60, 88, gSioBtlOptionWork->gfx6[0], gSioBtlOptionWork->unk_008[0], gSioBtlOptionWork->unk_008[2], 0, 1, 0xFFF0);
    DrawSprite(180, 88, gSioBtlOptionWork->gfx6[1], gSioBtlOptionWork->unk_008[1], gSioBtlOptionWork->unk_008[3], 0, 0, 0xFFF0);
#ifdef VERSION_EU
    width = GetTextSlotsWidth(gSioBtlOptionWork->textSlots, gSioBtlOptionWork->textSlotCount);
    DrawTextSlots(162 - width / 2, 4, gSioBtlOptionWork->textSlots, gSioBtlOptionWork->palette7, 20, gSioBtlOptionWork->textSlotCount);
#else
    DrawTextSlots(gSioWorldEntries[gSioBtlOptionWork->worldEntry].textX + 108, 4, gSioBtlOptionWork->textSlots, gSioBtlOptionWork->palette7, 20, gSioBtlOptionWork->textSlotCount);
#endif
    DrawTextSlots(16, 144, gSioBtlOptionWork->textSlots2, gSioBtlOptionWork->palette8, 0xF200, gSioBtlOptionWork->textSlotCount2);
    DrawTextSlots(136, 144, gSioBtlOptionWork->textSlots3, gSioBtlOptionWork->palette9, 0xF200, gSioBtlOptionWork->textSlotCount3);
    DrawSprite(-((gSioBtlOptionWork->frameCount >> 3) % 4) + 88, 2, gSioBtlOptionWork->gfx4, gSioBtlOptionWork->tiles4, gSioBtlOptionWork->palette4, 0, 0, 0xFF00);
    DrawSprite(224 + ((gSioBtlOptionWork->frameCount >> 3) % 4), 2, gSioBtlOptionWork->gfx7, gSioBtlOptionWork->tiles4, gSioBtlOptionWork->palette4, 0, 0, 0xFF00);

    if (gSioBtlOptionWork->menuOpen == 1) {
        DrawSprite(72, 38, gSioBtlOptionWork->gfx, gSioBtlOptionWork->tiles, gSioBtlOptionWork->palette, 0, 0, 0x200);

        if (gSioBtlOptionWork->cursorVisible == 1) {
            ApproachValueHalf(&gSioBtlOptionWork->y, gSioBtlOptionWork->cursor * 4608 + 10752);
            DrawSprite(64, gSioBtlOptionWork->y >> 8, gSioBtlOptionWork->gfx2, gSioBtlOptionWork->tiles2, gSioBtlOptionWork->palette2, 0, 0, 0x100);
        }
    }

    if (gSioBtlOptionWork->messageVisible == 1) {
        DrawSprite(120, 131, gSioBtlOptionWork->gfx3, gSioBtlOptionWork->tiles3, gSioBtlOptionWork->palette3, 0, 0, 0xF000);
#ifdef VERSION_EU
        width = eu_0806629C(gSioBtlOptionWork->textSlots4, gSioBtlOptionWork->textSlotCount4);
        multiline = 0;
        for (i = 0; i < gSioBtlOptionWork->textSlotCount4; i++) {
            if (gSioBtlOptionWork->textSlots4[i].tiles == NULL) {
                multiline = 1;
                break;
            }
        }
        if (multiline != 0) {
            DrawTextSlots(120 - (width >> 1), 119, gSioBtlOptionWork->textSlots4, gSioBtlOptionWork->palette6, 20, gSioBtlOptionWork->textSlotCount4);
        } else {
            DrawTextSlots(120 - (width >> 1), 124, gSioBtlOptionWork->textSlots4, gSioBtlOptionWork->palette6, 20, gSioBtlOptionWork->textSlotCount4);
        }
#else
        DrawTextSlots(gSioBtlOptionWork->x, gSioBtlOptionWork->y2, gSioBtlOptionWork->textSlots4, gSioBtlOptionWork->palette6, 20, gSioBtlOptionWork->textSlotCount4);
#endif
    }
    DrawSprite(32, 24, gSioBtlOptionWork->gfx5[0], gSioBtlOptionWork->tiles5[0], gSioBtlOptionWork->palette5[0], 0, 0, 0xF100);
    DrawSprite(132, 24, gSioBtlOptionWork->gfx5[1], gSioBtlOptionWork->tiles5[1], gSioBtlOptionWork->palette5[1], 0, 0, 0xF100);

    if (gSioBtlOptionWork->handicapMarkerVisible == 1) {
        DrawSprite(gSioPlayerId * 101 + 44 + gSioHandicapMarkerX[gSioBtlOptionWork->handicap], -((gSioBtlOptionWork->frameCount >> 3) % 4) / 2 + 22, gSioBtlOptionWork->gfx8, gSioBtlOptionWork->tiles4, gSioBtlOptionWork->palette4, 0, 0, 0xF000);
    }
    gSioBtlOptionWork->frameCount++;
}

void SioBtlOptionWaitStart(void) {
    if (gSioBtlOptionWork->timer > 4) {
        gSioBtlOptionWork->timer = 0;

        if (gSioBtlOptionWork->modeArg == 1) {
            gSioBtlOptionWork->state = 6;
        } else {
            gSioBtlOptionWork->state = 5;
        }
    } else {
        gSioBtlOptionWork->timer++;
    }
    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
}

void SioBtlOptionHandleIdle(void) {
    s8 v = 0;
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
    gSioCommandSend[1] |= 5;

    if (GetKeysPressed() & A_BUTTON) {
        gSioCommandSend[1] |= 0x1F20;
    } else if (GetKeysPressed() & B_BUTTON) {
        gSioCommandSend[1] |= 0xC2F0;
    }

    if (GetKeysPressed() & L_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v--;
            if (v <= 0) {
                v = gSioWorldCount;
            }
            gSioCommandSend[2] |= v & 15;
        }
    } else if (GetKeysPressed() & R_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v++;
            if (v > gSioWorldCount) {
                v = 1;
            }
            gSioCommandSend[2] |= v & 15;
        }
    } else {
        gSioCommandSend[2] &= 0xFFF0;
    }

    if ((gSioCommandRecv[1][0] & 0xFFF0) == 0xC2F0 || (gSioCommandRecv[1][1] & 0xFFF0) == 0xC2F0) {
        if ((gSioCommandRecv[1][0] & 15) == 5 && (gSioCommandRecv[1][1] & 15) == 5 && gSioBtlOptionWork->leaveDelay == 0) {
            SioLinkClose();
            m4aMPlayAllStop();
            gSioWinCount = 0;
            gSioLoseCount = 0;
            ModeRequest(&gModeSioBtlConnect, 0);
        }
    } else if ((gSioCommandRecv[1][0] & 0xFFF0) == 0x1F20) {
        gSioBtlOptionWork->leaveDelay = 10;

        if (gSioPlayerId == 0) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            gSioBtlOptionWork->menuOpen = 1;
            gSioBtlOptionWork->state = 6;
        }
    } else if ((gSioCommandRecv[1][1] & 0xFFF0) == 0x1F20) {
        gSioBtlOptionWork->leaveDelay = 10;

        if (gSioPlayerId == 1) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            gSioBtlOptionWork->menuOpen = 1;
            gSioBtlOptionWork->state = 6;
        }
    }
    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();

    if (gSioBtlOptionWork->leaveDelay > 0) {
        gSioBtlOptionWork->leaveDelay--;
    }
#ifdef VERSION_EU
    } else {
        if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_CANSEL);
            gSioBtlOptionWork->menuOpen = 1;
            gSioBtlOptionWork->state = 6;
        }
        if (GetKeysPressed() & L_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v--;
                if (v <= 0) {
                    v = gSioWorldCount;
                }
                gSioBtlOptionWork->timer = 0;
                gSioBtlOptionWork->fadeLevel = 0;
                gSioBtlOptionWork->worldChangeState = 0;
                gSioBtlOptionWork->returnState = gSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                gSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else if (GetKeysPressed() & R_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v++;
                if (v > gSioWorldCount) {
                    v = 1;
                }
                gSioBtlOptionWork->timer = 0;
                gSioBtlOptionWork->fadeLevel = 0;
                gSioBtlOptionWork->worldChangeState = 0;
                gSioBtlOptionWork->returnState = gSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                gSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else {
            gSioCommandSend[2] &= 0xFFF0;
        }

        SioBtlOptionCheckReady();
        SioBtlOptionSyncHandicaps();
        SioBtlOptionRecvWorld();
        SioBtlOptionSyncDeckNames();
    }
#endif
}

void SioBtlOptionHandleMenu(void) {
    s8 v;
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
    gSioCommandSend[1] = 6;

    if (GetKeysPressed() & DPAD_UP) {
        m4aSongNumStart(SONG_SYS_CLICK);
        gSioBtlOptionWork->cursor--;
        if (gSioBtlOptionWork->cursor < 0) {
            gSioBtlOptionWork->cursor = 2;
        }
    } else if (GetKeysPressed() & DPAD_DOWN) {
        m4aSongNumStart(SONG_SYS_CLICK);
        gSioBtlOptionWork->cursor++;
        if (gSioBtlOptionWork->cursor > 2) {
            gSioBtlOptionWork->cursor = 0;
        }
    }

    if (GetKeysPressed() & L_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v--;
            if (v <= 0) {
                v = gSioWorldCount;
            }
            gSioCommandSend[2] |= v & 15;
        }
    } else if (GetKeysPressed() & R_BUTTON) {
        if (gSioWorldCount == 1) {
            m4aSongNumStart(SONG_SYS_BEEP);
        } else {
            v = gSioWorldCursor;
            v++;
            if (v > gSioWorldCount) {
                v = 1;
            }
            gSioCommandSend[2] |= v & 15;
        }
    } else {
        gSioCommandSend[2] &= 0xFFF0;
    }

    if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_KETTEI);

        switch (gSioBtlOptionWork->cursor) {
        case 0:
            if (gSioPlayerId == 0) {
                gSioCommandSend[1] = 0x2FCF;
            } else {
                gSioCommandSend[1] = 0x6AD6;
            }
            gSioBtlOptionWork->menuOpen = 0;
            gSioBtlOptionWork->messageVisible = 1;
#ifdef VERSION_EU
            gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891580), gSioBtlOptionWork->textSlots4);
#else
            gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815A20C, gSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
            gSioBtlOptionWork->x = 68;
#else
            gSioBtlOptionWork->x = 65;
#endif
            gSioBtlOptionWork->y2 = 124;
            gSioBtlOptionWork->state = 9;
            break;
        case 1:
            ModeRequest(&gModeDeck, 0);
            break;
        case 2:
            gSioBtlOptionWork->cursorVisible = 0;
            gSioBtlOptionWork->handicapMarkerVisible = 1;
            gSioBtlOptionWork->state = 7;
            break;
        }
    } else if (GetKeysPressed() & B_BUTTON) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        gSioBtlOptionWork->menuOpen = 0;
        gSioBtlOptionWork->state = 5;
    }
    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
#ifdef VERSION_EU
    } else {
        if (GetKeysPressed() & DPAD_UP) {
            m4aSongNumStart(SONG_SYS_CLICK);
            gSioBtlOptionWork->cursor--;
            if (gSioBtlOptionWork->cursor < 0) {
                gSioBtlOptionWork->cursor = 2;
            }
        } else if (GetKeysPressed() & DPAD_DOWN) {
            m4aSongNumStart(SONG_SYS_CLICK);
            gSioBtlOptionWork->cursor++;
            if (gSioBtlOptionWork->cursor > 2) {
                gSioBtlOptionWork->cursor = 0;
            }
        }

        if (GetKeysPressed() & L_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v--;
                if (v <= 0) {
                    v = gSioWorldCount;
                }
                gSioBtlOptionWork->timer = 0;
                gSioBtlOptionWork->fadeLevel = 0;
                gSioBtlOptionWork->worldChangeState = 0;
                gSioBtlOptionWork->returnState = gSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                gSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        } else if (GetKeysPressed() & R_BUTTON) {
            if (gSioWorldCount == 1) {
                m4aSongNumStart(SONG_SYS_BEEP);
            } else {
                v = gSioWorldCursor;
                v++;
                if (v > gSioWorldCount) {
                    v = 1;
                }
                gSioBtlOptionWork->timer = 0;
                gSioBtlOptionWork->fadeLevel = 0;
                gSioBtlOptionWork->worldChangeState = 0;
                gSioBtlOptionWork->returnState = gSioBtlOptionWork->state;
                gSioPrevWorldCursor = gSioWorldCursor;
                gSioWorldCursor = v;
                gSioBtlOptionWork->state = 8;
                m4aSongNumStart(SONG_SYS_CANSEL);
            }
        }

        if (GetKeysPressed() & A_BUTTON) {
            m4aSongNumStart(SONG_SYS_KETTEI);

            switch (gSioBtlOptionWork->cursor) {
            case 0:
                gSioDebugReady[0] = 1;
                gSioBtlOptionWork->menuOpen = 0;
                gSioBtlOptionWork->messageVisible = 1;
                gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891580), gSioBtlOptionWork->textSlots4);
#ifdef VERSION_JP
                gSioBtlOptionWork->x = 68;
#else
                gSioBtlOptionWork->x = 65;
#endif
                gSioBtlOptionWork->y2 = 124;
                gSioBtlOptionWork->state = 9;
                break;
            case 1:
                ModeRequest(&gModeDeck, 0);
                break;
            case 2:
                gSioBtlOptionWork->cursorVisible = 0;
                gSioBtlOptionWork->handicapMarkerVisible = 1;
                gSioBtlOptionWork->state = 7;
                break;
            }
        } else if (GetKeysPressed() & B_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            gSioBtlOptionWork->menuOpen = 0;
            gSioBtlOptionWork->state = 5;
        }
        SioBtlOptionCheckReady();
        SioBtlOptionSyncHandicaps();
        SioBtlOptionRecvWorld();
        SioBtlOptionSyncDeckNames();
    }
#endif
}

void SioBtlOptionSetHandicap(void) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
    if (GetKeysPressed() & DPAD_LEFT) {
        if (gSioBtlOptionWork->handicap > 1) {
            m4aSongNumStart(SONG_SYS_CLICK);
            gSioBtlOptionWork->handicap--;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    } else if (GetKeysPressed() & DPAD_RIGHT) {
        if (gSioBtlOptionWork->handicap <= 10) {
            m4aSongNumStart(SONG_SYS_CLICK);
            gSioBtlOptionWork->handicap++;
        } else {
            m4aSongNumStart(SONG_SYS_BEEP);
        }
    }

    if (gSioPlayerId == 0) {
        gSioHandicaps[0] = gSioBtlOptionWork->handicap;
    } else {
        gSioHandicaps[1] = gSioBtlOptionWork->handicap;
    }

    if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        gSioBtlOptionWork->cursorVisible = 1;
        gSioBtlOptionWork->handicapMarkerVisible = 0;
        gSioBtlOptionWork->state = 6;
    }
    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
#ifdef VERSION_EU
    } else {
        if (GetKeysPressed() & DPAD_LEFT) {
            if (gSioBtlOptionWork->handicap > 1) {
                m4aSongNumStart(SONG_SYS_CLICK);
                gSioBtlOptionWork->handicap--;
                gSioHandicaps[0] = gSioBtlOptionWork->handicap;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (GetKeysPressed() & DPAD_RIGHT) {
            if (gSioBtlOptionWork->handicap <= 10) {
                m4aSongNumStart(SONG_SYS_CLICK);
                gSioBtlOptionWork->handicap++;
                gSioHandicaps[0] = gSioBtlOptionWork->handicap;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }
        if (GetKeysPressed() & L_BUTTON) {
            if ((s8)gSioHandicaps[1] > 1) {
                m4aSongNumStart(SONG_SYS_CLICK);
                gSioHandicaps[1]--;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        } else if (GetKeysPressed() & R_BUTTON) {
            if ((s8)gSioHandicaps[1] <= 10) {
                m4aSongNumStart(SONG_SYS_CLICK);
                gSioHandicaps[1]++;
            } else {
                m4aSongNumStart(SONG_SYS_BEEP);
            }
        }
        if (GetKeysPressed() & (A_BUTTON | B_BUTTON)) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            gSioBtlOptionWork->cursorVisible = 1;
            gSioBtlOptionWork->handicapMarkerVisible = 0;
            gSioBtlOptionWork->state = 6;
        }
        SioBtlOptionCheckReady();
        SioBtlOptionSyncHandicaps();
        SioBtlOptionRecvWorld();
        SioBtlOptionSyncDeckNames();
    }
#endif
}

void SioBtlOptionChangeWorld(void) {
    s8 a = gSioWorldList[gSioPrevWorldCursor];
    s8 b = gSioWorldList[gSioWorldCursor];

    switch (gSioBtlOptionWork->worldChangeState) {
    case 0:
        gSioBtlOptionWork->timer++;
        if (gSioBtlOptionWork->timer > 1) {
            gSioBtlOptionWork->timer = 0;

            if (gSioBtlOptionWork->fadeLevel > 31) {
                gSioBtlOptionWork->fadeLevel = 32;
                gSioBtlOptionWork->worldChangeState++;
            } else {
                gSioBtlOptionWork->fadeLevel += 8;
                FadePaletteToBlack(gSioWorldEntries[a].palette, (u16*)0x05000000, gSioWorldEntries[a].paletteSize, gSioBtlOptionWork->fadeLevel);
            }
        }
        break;
    case 1:
        FadePaletteToBlack(gSioWorldEntries[b].palette, (u16*)0x05000000, gSioWorldEntries[b].paletteSize, 32);
#ifdef VERSION_EU
        eu_080059F4(2, gSioWorldEntries[b].map);
#else
        LoadBgMap(2, gSioWorldEntries[b].map, gSioWorldEntries[b].mapSize);
#endif
        RequestDma3Copy(gSioWorldEntries[b].tiles, GetBgCharBase(2), 0x2000);
        gSioBtlOptionWork->worldChangeState++;
        break;
    case 2:
        RequestDma3Copy((u8*)gSioWorldEntries[b].tiles + 0x2000, (u8*)GetBgCharBase(2) + 0x2000, gSioWorldEntries[b].tilesSize - 0x2000);
#ifdef VERSION_EU
        gSioBtlOptionWork->textSlotCount = LoadTextSlots(eu_0805E924(gSioWorldEntries[b].text), gSioBtlOptionWork->textSlots);
#else
        gSioBtlOptionWork->textSlotCount = LoadTextSlots(gSioWorldEntries[b].text, gSioBtlOptionWork->textSlots);
#endif
        gSioBtlOptionWork->worldEntry = b;
        gSioBtlOptionWork->worldChangeState++;
        break;
    case 3:
        gSioBtlOptionWork->timer++;
        if (gSioBtlOptionWork->timer > 1) {
            gSioBtlOptionWork->timer = 0;

            if (gSioBtlOptionWork->fadeLevel <= 0) {
                gSioBtlOptionWork->fadeLevel = 0;
                SioBtlOptionPlayWorldBgm();
                gSioBtlOptionWork->worldChangeState++;
            } else {
                gSioBtlOptionWork->fadeLevel -= 8;
                if (gSioBtlOptionWork->fadeLevel == 0) {
                    LoadPaletteWithEffect(gSioWorldEntries[b].palette, (u16*)0x05000000, gSioWorldEntries[b].paletteSize);
                } else {
                    FadePaletteToBlack(gSioWorldEntries[b].palette, (u16*)0x05000000, gSioWorldEntries[b].paletteSize, gSioBtlOptionWork->fadeLevel);
                }
            }
        }
        break;
    default:
        gSioBtlOptionWork->state = gSioBtlOptionWork->returnState;
        break;
    }
    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionSyncDeckNames();
}

void SioBtlOptionWaitReady(void) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
        if (gSioPlayerId == 0) {
            gSioCommandSend[1] = 0x2FCF;
        } else {
            gSioCommandSend[1] = 0x6AD6;
        }
#ifdef VERSION_EU
    } else if (GetKeysPressed() & A_BUTTON) {
        gSioDebugReady[1] = 1;
    }
#endif

    if (gSioBtlOptionWork->player1Ready == 1 && gSioBtlOptionWork->player2Ready == 1) {
        gSioBtlOptionWork->timer = 0;
#ifdef VERSION_EU
        gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891670), gSioBtlOptionWork->textSlots4);
#else
        gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815A23C, gSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
        gSioBtlOptionWork->x = 61;
#else
        gSioBtlOptionWork->x = 68;
#endif
        gSioBtlOptionWork->y2 = 119;
        gSioBtlOptionWork->state++;
    }
    SioBtlOptionCheckReady();
    SioBtlOptionSyncHandicaps();
    SioBtlOptionRecvWorld();
    SioBtlOptionSyncDeckNames();
}

void SioBtlOptionConfirm(void) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
    if (GetKeysPressed() & A_BUTTON) {
        gSioCommandSend[1] = 0xA926;
    } else if (GetKeysPressed() & B_BUTTON) {
        gSioCommandSend[1] = 0xDD42;
    }

    if (gSioCommandRecv[1][0] == 0xA926 || gSioCommandRecv[1][1] == 0xA926) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
        gSioBtlOptionWork->timer = 0;
#ifdef VERSION_EU
        gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891714), gSioBtlOptionWork->textSlots4);
#else
        gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(gUnk_0815B3D4, gSioBtlOptionWork->textSlots4);
#endif
#ifdef VERSION_JP
        gSioBtlOptionWork->x = 74;
#else
        gSioBtlOptionWork->x = 72;
#endif
        gSioBtlOptionWork->y2 = 124;
        gSioBtlOptionWork->state++;
    } else if (gSioCommandRecv[1][0] == 0xDD42 || gSioCommandRecv[1][1] == 0xDD42) {
        gSioBtlOptionWork->leaveDelay = 10;
        m4aSongNumStart(SONG_SYS_CLOSE);
        gSioBtlOptionWork->timer = 0;
        SioBtlOptionCancelReady();
        gSioBtlOptionWork->state = 5;
    }
#ifdef VERSION_EU
    } else if (GetKeysPressed() & A_BUTTON) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
        gSioBtlOptionWork->timer = 0;
        gSioBtlOptionWork->textSlotCount4 = LoadTextSlots(eu_0805E924(&gUnkEu_08891714), gSioBtlOptionWork->textSlots4);
        gSioBtlOptionWork->x = 72;
        gSioBtlOptionWork->y2 = 124;
        gSioBtlOptionWork->state++;
    }
#endif
}

void SioBtlOptionStartDeckExchange(void) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
        gSioBtlOptionWork->timer++;
        if (gSioBtlOptionWork->timer > 9) {
            SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
            SioPrepareDeckExchange();
            gSioBtlOptionWork->state++;
        }
    } else {
        gSioBtlOptionWork->timer++;
        if (gSioBtlOptionWork->timer > 9) {
            SioPrepareDeckExchange();
            eu_080C24D8();
            gSioBtlOptionWork->timer = 0;
            gSioBtlOptionWork->state++;
        }
    }
#else
    gSioBtlOptionWork->timer++;
    if (gSioBtlOptionWork->timer > 9) {
        SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
        SioPrepareDeckExchange();
        gSioBtlOptionWork->state++;
    }
#endif
}

void SioBtlOptionWaitDeckExchange(void) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
        if (gSioLinkResult == 2) {
            gSioBtlOptionWork->timer = 0;
            gSioBtlOptionWork->state++;
        }
    } else {
        gSioBtlOptionWork->timer++;
        if (gSioBtlOptionWork->timer > 59) {
            gSioBtlOptionWork->timer = 0;
            gSystemFlags |= SYSTEM_FLAG_LINK_ACTIVE;
            SioSetLinkCallbacks(eu_080C273C, eu_080C2740);
            SioApplyBattleSettings();
            gRandomPartnerDpadTimer = 180;
            gRandomPartnerDpad = 0;
            gRandomPartnerATimer = 120;
            ModeRequest(&gModeVsbattle, 0);
        }
    }
#else
    if (gSioLinkResult == 2) {
        gSioBtlOptionWork->timer = 0;
        gSioBtlOptionWork->state++;
    }
#endif
}

void SioBtlOptionResumeCommands(void) {
    gSioBtlOptionWork->timer++;
    if (gSioBtlOptionWork->timer > 4) {
        gSioBtlOptionWork->timer = 0;
        SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
        SioCommandReset();
        gSioBtlOptionWork->state++;
    }
}

void func_080B041C(void) {
    gSioBtlOptionWork->timer++;
    if (gSioBtlOptionWork->timer > 30) {
        gSioBtlOptionWork->timer = 0;
        gSioBtlOptionWork->state++;
    }
}

void SioBtlOptionSyncStart(void) {
    gSioBtlOptionWork->timer++;
    if (gSioBtlOptionWork->timer > 20) {
        gSioCommandSend[1] = 0x7CD2;

        if (gSioCommandRecv[1][0] == 0x7CD2 && gSioCommandRecv[1][1] == 0x7CD2) {
            gSioBtlOptionWork->timer = 0;
            gSystemFlags &= ~SYSTEM_FLAG_DMA3_FLUSH_CPU;
            gSioBtlOptionWork->state++;
        }
    }
}

void SioBtlOptionStartBattle(void) {
    gSioBtlOptionWork->timer++;
    if (gSioBtlOptionWork->timer > 4) {
        gSioBtlOptionWork->timer = 0;
        SioSetLinkCallbacks(SioKeySyncSend, SioKeySyncRecv);
        SioApplyBattleSettings();

        if (gSioPlayerId == 0) {
            ModeRequest(&gModeVsbattle, 0);
        } else {
            ModeRequest(&gModeVsbattle, 1);
        }
    }
}

void mode_sio_btl_option_2(void) {
    ReleaseObjTiles(gSioBtlOptionWork->unk_008[0]);
    ReleaseObjPalette(gSioBtlOptionWork->unk_008[2]);
    ReleaseObjTiles(gSioBtlOptionWork->unk_008[1]);
    ReleaseObjPalette(gSioBtlOptionWork->unk_008[3]);
    ReleaseObjPalette(gSioBtlOptionWork->palette7);
    ReleaseObjPalette(gSioBtlOptionWork->palette8);
    ReleaseObjPalette(gSioBtlOptionWork->palette9);
    ReleaseObjPalette(gSioBtlOptionWork->palette6);
#ifdef VERSION_EU
    FreeTextSlots(gSioBtlOptionWork->textSlots, 40);
    FreeTextSlots(gSioBtlOptionWork->textSlots2, 20);
    FreeTextSlots(gSioBtlOptionWork->textSlots3, 20);
    FreeTextSlots(gSioBtlOptionWork->textSlots4, 120);
#else
    FreeTextSlots(gSioBtlOptionWork->textSlots, 20);
    FreeTextSlots(gSioBtlOptionWork->textSlots2, 10);
    FreeTextSlots(gSioBtlOptionWork->textSlots3, 10);
    FreeTextSlots(gSioBtlOptionWork->textSlots4, 60);
#endif
    ReleaseObjTiles(gSioBtlOptionWork->tiles);
    ReleaseObjPalette(gSioBtlOptionWork->palette);
    ReleaseObjTiles(gSioBtlOptionWork->tiles2);
    ReleaseObjPalette(gSioBtlOptionWork->palette2);
    ReleaseObjTiles(gSioBtlOptionWork->tiles3);
    ReleaseObjPalette(gSioBtlOptionWork->palette3);
    ReleaseObjTiles(gSioBtlOptionWork->tiles4);
    ReleaseObjPalette(gSioBtlOptionWork->palette4);
    ReleaseObjTiles(gSioBtlOptionWork->tiles5[0]);
    ReleaseObjPalette(gSioBtlOptionWork->palette5[0]);
    ReleaseObjTiles(gSioBtlOptionWork->tiles5[1]);
    ReleaseObjPalette(gSioBtlOptionWork->palette5[1]);
    EwramFree(gSioBtlOptionWork);
}

void SioBtlOptionCheckReady(void) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
    if (gSioCommandRecv[1][0] == 0x2FCF) {
        RequestDma3Copy(gUnk_096B2724, (void*)0x06000020, 0xC0);

        if (gSioBtlOptionWork->player1Ready == 0) {
            SetSioBtlOptionAnimation(0, 1, 1);
        }
        gSioBtlOptionWork->player1Ready = 1;
    }

    if (gSioCommandRecv[1][1] == 0x6AD6) {
        RequestDma3Copy(gUnk_096B2B24, (void*)0x06000300, 0xC0);

        if (gSioBtlOptionWork->player2Ready == 0) {
            SetSioBtlOptionAnimation(1, 1, 1);
        }
        gSioBtlOptionWork->player2Ready = 1;
    }
#ifdef VERSION_EU
    } else {
    if (gSioDebugReady[0] == 1) {
        RequestDma3Copy(gUnk_096B2724, (void*)0x06000020, 0xC0);

        if (gSioBtlOptionWork->player1Ready == 0) {
            SetSioBtlOptionAnimation(0, 1, 1);
        }
        gSioBtlOptionWork->player1Ready = 1;
    }

    if (gSioDebugReady[1] == 1) {
        RequestDma3Copy(gUnk_096B2B24, (void*)0x06000300, 0xC0);

        if (gSioBtlOptionWork->player2Ready == 0) {
            SetSioBtlOptionAnimation(1, 1, 1);
        }
        gSioBtlOptionWork->player2Ready = 1;
    }
    }
#endif
}

void SioBtlOptionRecvWorld(void) {
    s8 x;
    s8 y;
#ifdef VERSION_EU
    if (gSioDebugMode != 0) {
        return;
    }
#endif
    x = gSioCommandRecv[2][0] & 15;
    y = gSioCommandRecv[2][1] & 15;
    if (x != 0 || y != 0) {
        if (x <= 12 && y <= 12) {
            gSioPrevWorldCursor = gSioWorldCursor;

            if (x > y) {
                gSioWorldCursor = x;
            } else if (x < y) {
                gSioWorldCursor = y;
            } else {
                gSioWorldCursor = x;
            }
            gSioBtlOptionWork->timer = 0;
            gSioBtlOptionWork->fadeLevel = 0;
            gSioBtlOptionWork->worldChangeState = 0;
            gSioBtlOptionWork->returnState = gSioBtlOptionWork->state;
            gSioBtlOptionWork->state = 8;
            m4aSongNumStart(SONG_SYS_CANSEL);
        }
    }
}

void SioBtlOptionRecvSettings(void) {
    u8 buf[2];
    s8 x;
    s8 y;
    s32 i;
#ifdef VERSION_EU
    if (gSioDebugMode != 0) {
        return;
    }
#endif
    buf[0] = (gSioCommandRecv[2][0] & 0xF0) >> 4;
    buf[1] = (gSioCommandRecv[2][1] & 0xF0) >> 4;

    if (buf[0] >= 1 && buf[0] <= 11) {
        gSioHandicaps[0] = buf[0];
    }

    if (buf[1] >= 1 && buf[1] <= 11) {
        gSioHandicaps[1] = buf[1];
    }

    if ((gSioCommandRecv[2][0] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][0] >> 12) - 1;
        gSioDeckNameRecvBuf[0][n * 2] = gSioCommandRecv[3][0];
        gSioDeckNameRecvBuf[0][n * 2 + 1] = gSioCommandRecv[3][0] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[0][i] = gSioDeckNameRecvBuf[0][i];
            }
        }
    }

    if ((gSioCommandRecv[2][1] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][1] >> 12) - 1;
        gSioDeckNameRecvBuf[1][n * 2] = gSioCommandRecv[3][1];
        gSioDeckNameRecvBuf[1][n * 2 + 1] = gSioCommandRecv[3][1] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[1][i] = gSioDeckNameRecvBuf[1][i];
            }
        }
    }
    x = gSioCommandRecv[2][0] & 15;
    y = gSioCommandRecv[2][1] & 15;
    if (x != 0 || y != 0) {
        if (x <= 12 && y <= 12) {
            if (x > y) {
                gSioWorldCursor = x;
            } else if (x < y) {
                gSioWorldCursor = y;
            } else {
                gSioWorldCursor = x;
            }
        }
    }
}

void SioBtlOptionSyncDeckNames(void) {
    s32 deck;
    s32 i;
#ifdef VERSION_EU
    if (gSioDebugMode != 0) {
        return;
    }
#endif
    deck = GetActiveDeckIndex();
    gSioCommandSend[2] |= (gSioDeckNameChunk & 15) << 12;
    gSioCommandSend[3] = gDecks[deck].name[(gSioDeckNameChunk - 1) * 2] | (gDecks[deck].name[(gSioDeckNameChunk - 1) * 2 + 1] << 8);
    gSioDeckNameChunk++;
    if (gSioDeckNameChunk > 10) {
        gSioDeckNameChunk = 1;
    }

    if ((gSioCommandRecv[2][0] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][0] >> 12) - 1;
        gSioDeckNameRecvBuf[0][n * 2] = gSioCommandRecv[3][0];
        gSioDeckNameRecvBuf[0][n * 2 + 1] = gSioCommandRecv[3][0] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[0][i] = gSioDeckNameRecvBuf[0][i];
                gSioDeckNames[0][i] = gSioDeckNameRecv[0][i];
            }
            gSioBtlOptionWork->textSlotCount2 = LoadTextSlots(gSioDeckNames[0], gSioBtlOptionWork->textSlots2);
        }
    }

    if ((gSioCommandRecv[2][1] >> 12) != 0) {
        u16 n = (gSioCommandRecv[2][1] >> 12) - 1;
        gSioDeckNameRecvBuf[1][n * 2] = gSioCommandRecv[3][1];
        gSioDeckNameRecvBuf[1][n * 2 + 1] = gSioCommandRecv[3][1] >> 8;

        if (n == 9) {
            for (i = 0; i < 20; i++) {
                gSioDeckNameRecv[1][i] = gSioDeckNameRecvBuf[1][i];
                gSioDeckNames[1][i] = gSioDeckNameRecv[1][i];
            }
            gSioBtlOptionWork->textSlotCount3 = LoadTextSlots(gSioDeckNames[1], gSioBtlOptionWork->textSlots3);
        }
    }
}

void SioBtlOptionDrawStats(void) {
    s16 digits[4];
    s16 a, b, c, d, e, f, g, h;

#ifdef VERSION_EU
    if ((gSioDebugMode == 0 ? gSioPlayerId : 0) != 0) {
        a = gCharaLinkRecv.level;
        b = gCharaLinkSend.level;
        c = gCharaLinkRecv.maxHp;
        d = gCharaLinkSend.maxHp;
        e = gCharaLinkRecv.winCount;
        f = gCharaLinkSend.winCount;
        g = gCharaLinkRecv.loseCount;
        h = gCharaLinkSend.loseCount;
    } else {
        a = gCharaLinkSend.level;
        b = gCharaLinkRecv.level;
        c = gCharaLinkSend.maxHp;
        d = gCharaLinkRecv.maxHp;
        e = gCharaLinkSend.winCount;
        f = gCharaLinkRecv.winCount;
        g = gCharaLinkSend.loseCount;
        h = gCharaLinkRecv.loseCount;
    }
#else
    if (gSioPlayerId == 0) {
        a = gCharaLinkSend.level;
        b = gCharaLinkRecv.level;
        c = gCharaLinkSend.maxHp;
        d = gCharaLinkRecv.maxHp;
        e = gCharaLinkSend.winCount;
        f = gCharaLinkRecv.winCount;
        g = gCharaLinkSend.loseCount;
        h = gCharaLinkRecv.loseCount;
    } else {
        a = gCharaLinkRecv.level;
        b = gCharaLinkSend.level;
        c = gCharaLinkRecv.maxHp;
        d = gCharaLinkSend.maxHp;
        e = gCharaLinkRecv.winCount;
        f = gCharaLinkSend.winCount;
        g = gCharaLinkRecv.loseCount;
        h = gCharaLinkSend.loseCount;
    }
#endif

    digits[0] = a / 100;
    a %= 100;
    digits[1] = a / 10;
    a %= 10;
    digits[2] = a;
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)0x06000100, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)0x06000120, 32);

    digits[0] = c / 100;
    c %= 100;
    digits[1] = c / 10;
    c %= 10;
    digits[2] = c;
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)0x06000140, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)0x06000160, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)0x06000180, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)0x060001A0, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)0x060001C0, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)0x060001E0, 32);

    digits[0] = e / 1000;
    e %= 1000;
    digits[1] = e / 100;
    e %= 100;
    digits[2] = e / 10;
    e %= 10;
    digits[3] = e;
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)0x06000200, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)0x06000220, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)0x06000240, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[3] * 32, (void*)0x06000260, 32);

    digits[0] = g / 1000;
    g %= 1000;
    digits[1] = g / 100;
    g %= 100;
    digits[2] = g / 10;
    g %= 10;
    digits[3] = g;
    RequestDma3Copy(gUnk_096B2124 + digits[0] * 32, (void*)0x06000280, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[1] * 32, (void*)0x060002A0, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[2] * 32, (void*)0x060002C0, 32);
    RequestDma3Copy(gUnk_096B2124 + digits[3] * 32, (void*)0x060002E0, 32);

    digits[0] = b / 100;
    b %= 100;
    digits[1] = b / 10;
    b %= 10;
    digits[2] = b;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)0x060003E0, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)0x06000400, 32);

    digits[0] = d / 100;
    d %= 100;
    digits[1] = d / 10;
    d %= 10;
    digits[2] = d;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)0x06000420, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)0x06000440, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)0x06000460, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)0x06000480, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)0x060004A0, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)0x060004C0, 32);

    digits[0] = f / 1000;
    f %= 1000;
    digits[1] = f / 100;
    f %= 100;
    digits[2] = f / 10;
    f %= 10;
    digits[3] = f;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)0x060004E0, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)0x06000500, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)0x06000520, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[3] * 32, (void*)0x06000540, 32);

    digits[0] = h / 1000;
    h %= 1000;
    digits[1] = h / 100;
    h %= 100;
    digits[2] = h / 10;
    h %= 10;
    digits[3] = h;
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[0] * 32, (void*)0x06000560, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[1] * 32, (void*)0x06000580, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[2] * 32, (void*)0x060005A0, 32);
    RequestDma3Copy(gUnk_096B2124 + 0x400 + digits[3] * 32, (void*)0x060005C0, 32);
}
void SioApplyBattleSettings(void) {
    s8* base;
    s8* p;
    GameState* gs;
    SioWorldEntry* table;
    SioWorldEntry* entry;

    base = gSioWorldList;
    p = base + gSioWorldCursor;
    gs = &gGameState;
    table = gSioWorldEntries;
    entry = &table[*p];

    gs->battleStage = entry->world;
    gSioSavedWorld = gs->world;
    gs->world = entry->world;

    if (gSioPlayerId == 0) {
        gCharaLinkSend.ap += gSioHandicapAp[gSioBtlOptionWork->handicaps[0]];
        gCharaLinkRecv.ap += gSioHandicapAp[gSioBtlOptionWork->handicaps[1]];
    } else {
        gCharaLinkSend.ap += gSioHandicapAp[gSioBtlOptionWork->handicaps[1]];
        gCharaLinkRecv.ap += gSioHandicapAp[gSioBtlOptionWork->handicaps[0]];
    }

    gGameState.linkMaxHp = gCharaLinkSend.maxHp;
    gGameState.linkAp = gCharaLinkSend.ap;
    gGameState.linkLevel = gCharaLinkSend.level;
    gGameState.linkLearnedStocks = gCharaLinkSend.learnedStocks;
    gGameState.linkLearnedStocks2 = gCharaLinkSend.learnedStocks2;
    gGameState.linkPartnerMaxHp = gCharaLinkRecv.maxHp;
    gGameState.linkPartnerAp = gCharaLinkRecv.ap;
    gGameState.linkPartnerLevel = gCharaLinkRecv.level;
    gGameState.linkPartnerLearnedStocks = gCharaLinkRecv.learnedStocks;
    gGameState.linkPartnerLearnedStocks2 = gCharaLinkRecv.learnedStocks2;
}

void SioBtlOptionSyncHandicaps(void) {
    u8 buf[2];

#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
#endif
    if (gSioPlayerId == 0) {
        gSioCommandSend[2] |= (gSioHandicaps[0] & 15) << 4;
    } else {
        gSioCommandSend[2] |= (gSioHandicaps[1] & 15) << 4;
    }
    buf[0] = (gSioCommandRecv[2][0] & 0xF0) >> 4;
    buf[1] = (gSioCommandRecv[2][1] & 0xF0) >> 4;

    if (buf[0] >= 1 && buf[0] <= 11) {
        gSioBtlOptionWork->handicaps[0] = buf[0];
        gSioHandicaps[0] = gSioBtlOptionWork->handicaps[0];
    }

    if (buf[1] >= 1 && buf[1] <= 11) {
        gSioBtlOptionWork->handicaps[1] = buf[1];
        gSioHandicaps[1] = gSioBtlOptionWork->handicaps[1];
    }
    SioBtlOptionUpdateHandicapGauges(gSioBtlOptionWork->handicaps[0], gSioBtlOptionWork->handicaps[1]);
#ifdef VERSION_EU
    } else {
    buf[0] = gSioHandicaps[0];
    buf[1] = gSioHandicaps[1];

    if (buf[0] >= 1 && buf[0] <= 11) {
        gSioBtlOptionWork->handicaps[0] = buf[0];
    }

    if (buf[1] >= 1 && buf[1] <= 11) {
        gSioBtlOptionWork->handicaps[1] = buf[1];
    }
    SioBtlOptionUpdateHandicapGauges(gSioBtlOptionWork->handicaps[0], gSioBtlOptionWork->handicaps[1]);
    }
#endif
}

void SioBtlOptionUpdateHandicapGauges(u16 a, u16 b) {
    switch (a) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        LoadPalette(gUnk_096FBD64, (void*)(gSioBtlOptionWork->palette5[0]->index * 32 + 0x05000200), 32);
        LoadPalette(gUnk_096FBD64 + 0x22, (void*)(gSioBtlOptionWork->palette5[0]->index * 32 + 0x05000202), (6 - a) * 2);
        break;
    case 6:
        LoadPalette(gUnk_096FBD64, (void*)(gSioBtlOptionWork->palette5[0]->index * 32 + 0x05000200), 32);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        LoadPalette(gUnk_096FBD64, (void*)(gSioBtlOptionWork->palette5[0]->index * 32 + 0x05000200), 32);
        LoadPalette(gUnk_096FBD64 + 0x2C, (void*)(gSioBtlOptionWork->palette5[0]->index * 32 + 0x0500020C), (a - 6) * 2);
        break;
    }

    switch (b) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        LoadPalette(gUnk_096FBDA4, (void*)(gSioBtlOptionWork->palette5[1]->index * 32 + 0x05000200), 32);
        LoadPalette(gUnk_096FBDA4 + 0x22, (void*)(gSioBtlOptionWork->palette5[1]->index * 32 + 0x05000202), (6 - b) * 2);
        break;
    case 6:
        LoadPalette(gUnk_096FBDA4, (void*)(gSioBtlOptionWork->palette5[1]->index * 32 + 0x05000200), 32);
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        LoadPalette(gUnk_096FBDA4, (void*)(gSioBtlOptionWork->palette5[1]->index * 32 + 0x05000200), 32);
        LoadPalette(gUnk_096FBDA4 + 0x2C, (void*)(gSioBtlOptionWork->palette5[1]->index * 32 + 0x0500020C), (b - 6) * 2);
        break;
    }
}

void SioBtlOptionCancelReady(void) {
    gSioBtlOptionWork->messageVisible = 0;
    RequestDma3Copy(gUnk_096B2664, (void*)0x06000020, 0xC0);
    RequestDma3Copy(gUnk_096B2664 + 0x400, (void*)0x06000300, 0xC0);
    gSioBtlOptionWork->player1Ready = 0;
    gSioBtlOptionWork->player2Ready = 0;
    SetSioBtlOptionAnimation(0, 0, 0);
    SetSioBtlOptionAnimation(1, 0, 0);
}

void SioBtlOptionPlayWorldBgm(void) {
    s8 i = gSioWorldList[gSioWorldCursor];
    switch (i) {
    case 1:
        m4aSongNumStart(SONG_BGM_ALADDIN_BATTLE);
        break;
    case 2:
        m4aSongNumStart(SONG_BGM_MARMAID_BATTLE);
        break;
    case 3:
        m4aSongNumStart(SONG_BGM_HERCULES_BATTLE);
        break;
    case 4:
        m4aSongNumStart(SONG_BGM_ALICE_BTL);
        break;
    case 5:
        m4aSongNumStart(SONG_BGM_PINOCCHIO_BTL);
        break;
    case 6:
        m4aSongNumStart(SONG_BGM_HALLOWEEN_BTL);
        break;
    case 7:
        m4aSongNumStart(SONG_BGM_PETERPAN_BTL);
        break;
    case 8:
        m4aSongNumStart(SONG_BGM_HOLLOW_BATTLE);
        break;
    case 9:
        m4aSongNumStart(SONG_BGM_DESTINY_BATTLE);
        break;
    case 10:
        m4aSongNumStart(SONG_BGM_TOWN_BTL);
        break;
    case 11:
        m4aSongNumStart(SONG_BGM_TWILIGHT_BATTLE);
        break;
    case 12:
        m4aSongNumStart(SONG_BGM_F13F_FORGET_BATTLE);
        break;
    }
}

void mode_sio_btl_cardget_0(s32 arg) {
#ifdef VERSION_EU
    if (gSioDebugMode == 0) {
        gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
    }
#else
    gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
#endif

    if (gLinkDecksAllocated == 1) {
        FreeLinkDecks();
        gLinkDecksAllocated = 0;
    }
    gSioBtlCardgetWork = EwramAlloc(sizeof(SioBtlCardgetWork));

    if (arg == 0) {
        gSioBtlCardgetWork->lost = 0;
    } else {
        gSioBtlCardgetWork->lost = 1;
    }
    SetBgMode0();
    SetupBg(1, 0, 16, 0);
    SetBgPriority(1, 1);
    SetupBg(2, 0, 24, 0);
    SetBgPriority(2, 2);
    RequestDma3Copy(gUnk_096AD744, GetBgCharBase(1), 0x2000);
    gSioBtlCardgetWork->state = 0;
}

void SioBtlCardgetLoadBgTiles(void) {
    RequestDma3Copy(gUnk_096AF744, (u8*)GetBgCharBase(1) + 0x2000, 0x2000);
}

void SioBtlCardgetLoadBg(void) {
#ifdef VERSION_EU
    RequestDma3Copy(gUnk_096B1744, (u8*)GetBgCharBase(1) + 0x4000, 0x2000);
#else
    RequestDma3Copy(gUnk_096B1744, (u8*)GetBgCharBase(1) + 0x4000, 0x9E0);
#endif
    LoadBgPalette(1, gUnk_096FBAC4, 0x200);
#ifdef VERSION_EU
    switch (gLanguage) {
    case 0:
        LoadBgMap(1, gUnk_096F7C64, 0x800);
        break;
    case 3:
        LoadBgMap(1, gUnkEu_096C698C, 0x800);
        break;
    case 1:
        LoadBgMap(1, gUnkEu_096C598C, 0x800);
        break;
    case 4:
        LoadBgMap(1, gUnkEu_096C618C, 0x800);
        break;
    case 2:
    default:
        LoadBgMap(1, gUnkEu_096C718C, 0x800);
        break;
    }
#else
    LoadBgMap(1, gUnk_096F7C64, 0x800);
#endif
    DisableBg(1);
}

void SioBtlCardgetShowResult(void) {
    FadeStartIn(0, 16);
    DisableBg(0);
    EnableBg(1);
    EnableBg(2);
    DisableBg(3);

    if (gSioBtlCardgetWork->lost == 0) {
        gSioWinCount++;
        if (gSioWinCount > 0x270F) {
            gSioWinCount = 0x270F;
        }

        if (gSioPlayerId == 0) {
            SioBtlCardgetLoad1PWin();
            gSioBtlCardgetWork->palette = LoadObjPalette(gSoraPalette, 32);
            gSioBtlCardgetWork->palette2 = LoadObjPalette(gUnk_096FAC64, 32);
        } else {
            SioBtlCardgetLoad2PWin();
            gSioBtlCardgetWork->palette = LoadObjPalette(gUnk_096FAC64, 32);
            gSioBtlCardgetWork->palette2 = LoadObjPalette(gSoraPalette, 32);
        }
    } else {
        gSioLoseCount++;
        if (gSioLoseCount > 0x270F) {
            gSioLoseCount = 0x270F;
        }

        if (gSioPlayerId == 0) {
            SioBtlCardgetLoad2PWin();
            gSioBtlCardgetWork->palette = LoadObjPalette(gSoraPalette, 32);
            gSioBtlCardgetWork->palette2 = LoadObjPalette(gUnk_096FAC64, 32);
        } else {
            SioBtlCardgetLoad1PWin();
            gSioBtlCardgetWork->palette = LoadObjPalette(gUnk_096FAC64, 32);
            gSioBtlCardgetWork->palette2 = LoadObjPalette(gSoraPalette, 32);
        }
    }

    if (gSioPlayerId == 0) {
        gSioBtlCardgetWork->unk_20 = 0x3C00;
        gSioBtlCardgetWork->unk_24 = 0x6000;
    } else {
        gSioBtlCardgetWork->unk_20 = 0xB400;
        gSioBtlCardgetWork->unk_24 = 0x6000;
    }
    gSioBtlCardgetWork->unk_02 = 0;
    gSioBtlCardgetWork->timer = 0;
    gGameState.hp = gCharaLinkSend.hp;
    gGameState.world = gSioSavedWorld;
}

void mode_sio_btl_cardget_1(void) {
#ifdef VERSION_EU
    SioBtlCardgetWork* work;
#endif
    switch (gSioBtlCardgetWork->state) {
    case 0:
        SioBtlCardgetLoadBgTiles();
        gSioBtlCardgetWork->state++;
        break;
    case 1:
        SioBtlCardgetLoadBg();
        gSioBtlCardgetWork->state++;
        break;
    case 2:
        SioBtlCardgetShowResult();
        gSioBtlCardgetWork->state++;
        break;
    case 3:
        gSioBtlCardgetWork->timer++;
        if (gSioBtlCardgetWork->timer > 4) {
            gSioBtlCardgetWork->timer = 0;
#ifdef VERSION_EU
            if (gSioDebugMode == 0) {
#endif
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
#ifdef VERSION_EU
            }
#endif
            gSioBtlCardgetWork->state++;
        }
        SioBtlCardgetDraw();
        break;
    case 4:
        gSioBtlCardgetWork->timer++;
        if (gSioBtlCardgetWork->timer > 4) {
            gSioBtlCardgetWork->timer = 0;
            gSioBtlCardgetWork->state++;
        }
        SioBtlCardgetDraw();
        break;
    case 5:
#ifdef VERSION_EU
        if (gSioDebugMode == 0) {
#endif
        if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
            gSioCommandSend[1] = 0x45FC;
        }

        if (gSioCommandRecv[1][0] == 0x45FC || gSioCommandRecv[1][1] == 0x45FC) {
            m4aSongNumStart(SONG_SYS_ITEMGET);
            gSioBtlCardgetWork->timer = 0;
            gSioBtlCardgetWork->state++;
        }
#ifdef VERSION_EU
        } else if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
            m4aSongNumStart(SONG_SYS_ITEMGET);
            gSioBtlCardgetWork->timer = 0;
            gSioBtlCardgetWork->state++;
        }
#endif
        SioBtlCardgetDraw();
        break;
    case 6:
        gSioBtlCardgetWork->timer++;
        if (gSioBtlCardgetWork->timer > 4) {
#ifdef VERSION_EU
            work = gSioBtlCardgetWork;
            if (gSioDebugMode == 0) {
#endif
            SioSetLinkCallbacks(SioExchangeSend, SioExchangeRecv);
            SioPrepareCharaLinkExchange();
#ifdef VERSION_EU
                work = gSioBtlCardgetWork;
            }
            work->state++;
#else
            gSioBtlCardgetWork->state++;
#endif
        }
        SioBtlCardgetDraw();
        break;
    case 7:
#ifdef VERSION_EU
        if (gSioDebugMode == 0) {
#endif
        if (gSioLinkResult == 2) {
            gSioBtlCardgetWork->timer = 0;
            gSioBtlCardgetWork->state++;
        }
#ifdef VERSION_EU
        } else {
            gSioBtlCardgetWork->timer = 0;
            gSioBtlCardgetWork->state++;
        }
#endif
        SioBtlCardgetDraw();
        break;
    case 8:
        gSioBtlCardgetWork->timer++;
        if (gSioBtlCardgetWork->timer > 4) {
#ifdef VERSION_EU
            work = gSioBtlCardgetWork;
            if (gSioDebugMode == 0) {
#endif
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
#ifdef VERSION_EU
                work = gSioBtlCardgetWork;
            }
            work->state++;
#else
            gSioBtlCardgetWork->state++;
#endif
        }
        SioBtlCardgetDraw();
        break;
    case 9:
        ModeRequestHeapReset(&gModeSioBtlOption, 0);
        gSioBtlCardgetWork->state++;
        break;
    }
}

void mode_sio_btl_cardget_2(void) {
}

void SioBtlCardgetDraw(void) {
    DrawSprite(60, 116, gSioBtlCardgetWork->gfx, gSioBtlCardgetWork->tiles, gSioBtlCardgetWork->palette, 0, 0, 0xFFF0);
    DrawSprite(180, 116, gSioBtlCardgetWork->gfx2, gSioBtlCardgetWork->tiles2, gSioBtlCardgetWork->palette2, 0, 0, 0xFFF0);
#ifdef VERSION_JP
    DrawSprite(28, 36, gSioBtlCardgetWork->gfx3, gSioBtlCardgetWork->tiles3, gSioBtlCardgetWork->palette3, 0, 0, 0xFF00);
#else
    DrawSprite(13, 36, gSioBtlCardgetWork->gfx3, gSioBtlCardgetWork->tiles3, gSioBtlCardgetWork->palette3, 0, 0, 0xFF00);
#endif
#ifdef VERSION_JP
    DrawSprite(148, 36, gSioBtlCardgetWork->gfx4, gSioBtlCardgetWork->tiles4, gSioBtlCardgetWork->palette4, 0, 0, 0xFF00);
#else
    DrawSprite(135, 36, gSioBtlCardgetWork->gfx4, gSioBtlCardgetWork->tiles4, gSioBtlCardgetWork->palette4, 0, 0, 0xFF00);
#endif
}

void SioBtlCardgetLoad1PWin(void) {
    LoadBgMap(2, gUnk_096F8C64, 0x800);
    gSioBtlCardgetWork->tiles = AllocObjTiles(0xC80, gSor1ff00Tiles);
    gSioBtlCardgetWork->gfx = gSor1ff00Frames[18];
    gSioBtlCardgetWork->tiles2 = AllocObjTiles(0xC80, gSor1fl26Tiles);
    gSioBtlCardgetWork->gfx2 = gSor1fl26Frames[6];
#ifdef VERSION_EU
    gSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBDE4, 32);
    gSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBE04, 32);
    switch (gLanguage) {
    case 0:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095ECDD8, 0x680);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EB28[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095ED472, 0x600);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EB30[0];
        break;
    case 1:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F5550, 0x640);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBD8[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F5BB0, 0x580);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBE0[0];
        break;
    case 4:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F6150, 0x640);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBE8[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F67B0, 0x580);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBF0[0];
        break;
    case 3:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F6D50, 0x640);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBF8[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F73AA, 0x600);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EC00[0];
        break;
    case 2:
    default:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F79D2, 0x5C0);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EC08[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F7FAE, 0x600);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EC10[0];
        break;
    }
#else
#ifdef VERSION_JP
    gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962CAFC, 0x500);
#else
    gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962CAFC, 0x680);
#endif
    gSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBDE4, 32);
    gSioBtlCardgetWork->gfx3 = gUnk_09EF38DC[0];
#ifdef VERSION_JP
    gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962D196, 0x480);
#else
    gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962D196, 0x600);
#endif
    gSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBE04, 32);
    gSioBtlCardgetWork->gfx4 = gUnk_09EF38E4[0];
#endif
}

void SioBtlCardgetLoad2PWin(void) {
    LoadBgMap(2, gUnk_096F8464, 0x800);
    gSioBtlCardgetWork->tiles = AllocObjTiles(0xC80, gSor1fl26Tiles);
    gSioBtlCardgetWork->gfx = gSor1fl26Frames[6];
    gSioBtlCardgetWork->tiles2 = AllocObjTiles(0xC80, gSor1ff00Tiles);
    gSioBtlCardgetWork->gfx2 = gSor1ff00Frames[18];
#ifdef VERSION_EU
    gSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBE04, 32);
    gSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBDE4, 32);
    switch (gLanguage) {
    case 0:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095ED472, 0x600);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EB30[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095ECDD8, 0x680);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EB28[0];
        break;
    case 1:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F5BB0, 0x580);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBE0[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F5550, 0x640);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBD8[0];
        break;
    case 4:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F67B0, 0x580);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EBF0[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F6150, 0x640);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBE8[0];
        break;
    case 3:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F73AA, 0x600);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EC00[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F6D50, 0x640);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EBF8[0];
        break;
    case 2:
    default:
        gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnkEu_095F7FAE, 0x600);
        gSioBtlCardgetWork->gfx3 = gUnkEu_09F7EC10[0];
        gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnkEu_095F79D2, 0x5C0);
        gSioBtlCardgetWork->gfx4 = gUnkEu_09F7EC08[0];
        break;
    }
#else
#ifdef VERSION_JP
    gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962D196, 0x480);
#else
    gSioBtlCardgetWork->tiles3 = LoadObjTiles(gUnk_0962D196, 0x600);
#endif
    gSioBtlCardgetWork->palette3 = LoadObjPalette(gUnk_096FBE04, 32);
    gSioBtlCardgetWork->gfx3 = gUnk_09EF38E4[0];
#ifdef VERSION_JP
    gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962CAFC, 0x500);
#else
    gSioBtlCardgetWork->tiles4 = LoadObjTiles(gUnk_0962CAFC, 0x680);
#endif
    gSioBtlCardgetWork->palette4 = LoadObjPalette(gUnk_096FBDE4, 32);
    gSioBtlCardgetWork->gfx4 = gUnk_09EF38DC[0];
#endif
}

#ifndef VERSION_EU
void mode_sio_chg_connect_0(s32 arg) {
    gSioChgConnectWork = EwramAlloc(sizeof(SioBtlConnectWork));
    FadeStartIn(0, 16);
    SetBgMode0();
    SetupBg(0, 0, 7, 15);
    SetupBg(1, 1, 31, 0);
    EnableBg(0);
    EnableBg(1);
    LoadBgTiles(0, gUnk_096AD604, 0x140);
    LoadBgMap(0, gUnk_096F6464, 0x800);
    LoadBgPalette(0, gCard00Palette, 0x20);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5C64, 0x800);
    gSioChgConnectWork->unk_00 = 0;
    gSioChgConnectWork->timer = 0;
    gSioChgConnectWork->state = 0;
    gSioChgConnectWork->textSlotCount = 0;
    InitTextSlots(gSioChgConnectWork->textSlots, 0x5A);
    gSioChgConnectWork->textSlotCount = LoadTextSlots(gUnk_08159EC4, gSioChgConnectWork->textSlots);
    gSioChgConnectWork->palette = LoadObjPalette(gUnk_096FBAA4, 32);
    SioReset();
    SioConnectInit(SioChgConnectOnConnect, SioChgConnectOnCancel, 1);
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_connect_1(void) {
    switch (gSioChgConnectWork->state) {
    case 0:
        SioConnectUpdate();
        break;
    case 1:
        SioConnectUpdate();
        gSioChgConnectWork->timer++;
        if (gSioChgConnectWork->timer > 4) {
            SioSetLinkCallbacks(SioCommandSend, SioCommandRecv);
            SioCommandReset();
            gSystemFlags |= SYSTEM_FLAG_LINK_ACTIVE;
            gSystemFlags |= SYSTEM_FLAG_DMA3_FLUSH_CPU;
            SioChgConnectStartTrade();
            return;
        }
        break;
    }
    DrawTextSlots(61, 68, gSioChgConnectWork->textSlots, gSioChgConnectWork->palette, 20, gSioChgConnectWork->textSlotCount);
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_connect_2(void) {
    ReleaseObjPalette(gSioChgConnectWork->palette);
    FreeTextSlots(gSioChgConnectWork->textSlots, 0x5A);
    EwramFree(gSioChgConnectWork);
}
#endif

#ifndef VERSION_EU
void SioChgConnectOnConnect(void) {
    m4aSongNumStart(SONG_SYS_ITEMGET);
    gSioChgConnectWork->state++;
}
#endif

#ifndef VERSION_EU
void SioChgConnectOnCancel(void) {
    m4aSongNumStart(SONG_SYS_CLOSE);
    ModeRequest(&gModeSioBattle, 3);
}
#endif

#ifndef VERSION_EU
void SioChgConnectStartTrade(void) {
    s32 i;

    if (gSioPlayerId == 0) {
        gSioChgCardCursor = 0;
    } else {
        gSioChgCardCursor = 5;
    }

    for (i = 0; i < 10; i++) {
        gSioChgCardSlots[i] = 0x800;
    }

    for (i = 0; i < 2; i++) {
        gSioChgCardReady[i] = 0;
    }
    ModeRequest(&gModeSioChgCard, 0x800);
}
#endif

#ifndef VERSION_EU
void SetSioChgCardAnimation(u16 a, u16 b, u16 c) {
    const SioAnimDef* def = &gSioChgCardAnimDefs[b];
    AnimChangeWithTables(&gSioChgCardWork->anim[a], def->animId, c, def->anims, def->gfxTable);
    SetObjTileSource(gSioChgCardWork->unk_008[a], def->tiles);
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_card_0(s32 arg) {
    gSioChgCardWork = EwramAlloc(sizeof(SioChgCardWork));
    SetBgMode0();
    SetupBg(0, 0, 7, 0);
    SetBgPriority(0, 0);
    SetBgOverflow(0, 1);
    SetBgSize(0, 0);
    SetupBg(1, 0, 15, 0);
    SetBgPriority(1, 1);
    SetBgOverflow(1, 1);
    SetBgSize(1, 0);
    SetupBg(2, 0, 24, 0);
    SetBgPriority(2, 2);
    SetBgOverflow(2, 1);
    SetBgSize(2, 0);
    RequestDma3Copy(gUnk_096B2BE4, GetBgCharBase(0), 0x2000);
    DisableBg(0);
    DisableBg(1);
    DisableBg(2);
    gSioChgCardWork->blinkPhase = 0;
    gSioChgCardWork->timer = 0;
    gSioChgCardWork->ready = 0;
    gSioChgCardWork->state = 0;
    gSioChgCardWork->receiveOk = 0;
    gSioChgCardWork->leaveDelay = 0;
    gSioChgCardWork->offeredCard = arg;
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((arg + 1) & 0x0FFF);
}
#endif

#ifndef VERSION_EU
void SioChgCardLoadBg(void) {
    RequestDma3Copy(gUnk_096B4BE4, (u8*)GetBgCharBase(0) + 0x2000, 0x11C0);
    LoadBgPalette(0, gUnk_096FBE24, 0xE0);
    LoadBgMap(0, gUnk_096FA464, 0x800);
    DisableBg(0);
    DisableBg(1);
    DisableBg(2);
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((gSioChgCardWork->offeredCard + 1) & 0x0FFF);
    gSioChgCardWork->state++;
}
#endif

#ifndef VERSION_EU
void SioChgCardInitObjs(void) {
    s32 i;
    s16 n;
    FadeStartIn(0, 16);
    LoadBgMap(1, gUnk_096F9C64, 0x800);
    LoadBgMap(2, gUnk_096F9464, 0x800);
    DisableBg(0);
    EnableBg(1);
    EnableBg(2);
    gSioChgCardWork->cursor = gSioChgCardCursor;
    gSioChgCardWork->x = gSioChgCardSlotPos[gSioChgCardWork->cursor].x;
    gSioChgCardWork->y = gSioChgCardSlotPos[gSioChgCardWork->cursor].y;
    gSioChgCardWork->nextCursor = gSioChgCardWork->cursor;
    gSioChgCardWork->cursorVisible = 1;

    for (i = 0; i < 2; i++) {
        gSioChgCardWork->unk_008[i] = AllocObjTiles(0xC80, 0);
        AnimInit(&gSioChgCardWork->anim[i], 0, 0);

        if (gSioChgCardReady[i] == 0) {
            SetSioChgCardAnimation(i, 0, 0);
        } else {
            SetSioChgCardAnimation(i, 2, 0);
        }
        gSioChgCardWork->gfx[i] = AnimGetGfx(&gSioChgCardWork->anim[i]);
    }

    if (gSioPlayerId == 0) {
        gSioChgCardWork->unk_008[2] = LoadObjPalette(gSoraPalette, 32);
        gSioChgCardWork->unk_008[3] = LoadObjPalette(gUnk_096FAC64, 32);
    } else {
        gSioChgCardWork->unk_008[2] = LoadObjPalette(gUnk_096FAC64, 32);
        gSioChgCardWork->unk_008[3] = LoadObjPalette(gSoraPalette, 32);
    }
    gSioChgCardWork->tiles = LoadObjTiles(gUnk_0962DEA8, 0x780);
    gSioChgCardWork->palette = LoadObjPalette(gUnk_096FBF04, 32);
    AnimInit(&gSioChgCardWork->anim2, gUnk_09EF3920, gUnk_09EF390C);
    AnimStart(&gSioChgCardWork->anim2, 0, 1);
    gSioChgCardWork->gfx2 = AnimGetGfx(&gSioChgCardWork->anim2);
    gSioChgCardWork->tiles2 = LoadObjTiles(gUnk_0962B090, 0x1C0);
    gSioChgCardWork->palette2 = LoadObjPalette(gUnk_096FBAA4, 32);
    AnimInit(&gSioChgCardWork->anim3, gUnk_09EF38B4, gUnk_09EF3894);
    AnimStart(&gSioChgCardWork->anim3, 0, 1);
    gSioChgCardWork->gfx3 = AnimGetGfx(&gSioChgCardWork->anim3);

    for (i = 0; i < 10; i++) {
        if (gSioChgCardSlots[i] == 0x800) {
            gSioChgCardWork->cardVisible[i] = 0;
            gSioChgCardWork->x2[i] = gSioChgCardSlotPos[i].x << 8;
            gSioChgCardWork->y2[i] = gSioChgCardSlotPos[i].y << 8;
            gSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].tiles2, 0x200);
            gSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].palette2, 32);
            gSioChgCardWork->gfx4[i] = gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].gfx2;
            gSioChgCardWork->gfx5[i] = gUnk_09EE981C[0];
            gSioChgCardWork->scaleX[i] = 0x100;
            gSioChgCardWork->scaleY[i] = 0x100;
            gSioChgCardWork->angle[i] = 0;
        } else {
            gSioChgCardWork->cardVisible[i] = 1;
            gSioChgCardWork->x2[i] = gSioChgCardSlotPos[i].x << 8;
            gSioChgCardWork->y2[i] = gSioChgCardSlotPos[i].y << 8;
            n = gSioChgCardSlots[i];
            gSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[n].tiles2, 0x200);
            gSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[n].palette2, 32);
            gSioChgCardWork->gfx4[i] = gCardDefs[n].gfx2;
            gSioChgCardWork->gfx5[i] = gUnk_09EE981C[gCardDefs[n].value];
            gSioChgCardWork->scaleX[i] = 0x100;
            gSioChgCardWork->scaleY[i] = 0x100;
            gSioChgCardWork->angle[i] = 0;
        }
    }
    gSioChgCardWork->tiles4 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    gSioChgCardWork->palette4 = LoadObjPalette(gCard00Palette, 32);
    gSioChgCardWork->tiles5 = LoadObjTiles(gUnk_093F8C8E, 0xC00);
    gSioChgCardWork->gfx6 = gUnk_09EF1278[0];
    gSioChgCardWork->messageVisible = 0;
    InitTextSlots(gSioChgCardWork->textSlots, 42);
    gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A394, gSioChgCardWork->textSlots);
    gSioChgCardWork->x3 = 68;
    gSioChgCardWork->y3 = 124;
    InitTextSlots(gSioChgCardWork->textSlots2, 20);
    gSioChgCardWork->textSlotCount2 = LoadTextSlots(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].name, gSioChgCardWork->textSlots2);
    gSioChgCardWork->cardInfoVisible = 0;
    TaskPoolInit(&gSioChgCardWork->tasks, 11);
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((gSioChgCardWork->offeredCard + 1) & 0x0FFF);
    gSioChgCardWork->state++;
}
#endif

#ifndef VERSION_EU
void mode_sio_chg_card_1(void) {
    switch (gSioChgCardWork->state) {
    case 0:
        SioChgCardLoadBg();
        break;
    case 1:
        SioChgCardInitObjs();
        break;
    case 2:
        SioChgCardWaitStart();
        SioChgCardDraw();
        break;
    case 3:
        SioChgCardSelect();
        SioChgCardDraw();
        break;
    case 4:
        SioChgCardConfirm();
        SioChgCardDraw();
        break;
    case 5:
        SioChgCardTryTrade();
        SioChgCardDraw();
        break;
    case 6:
        SioChgCardWaitTradeResult();
        SioChgCardDraw();
        break;
    case 7:
        SioChgCardTradeFailed();
        SioChgCardDraw();
        break;
    case 8:
        SioChgCardStartMove();
        SioChgCardDraw();
        break;
    case 9:
        SioChgCardSave();
        SioChgCardDraw();
        break;
    case 10:
        SioChgCardWaitMove();
        SioChgCardDraw();
        break;
    case 11:
        func_080B2AE8();
        SioChgCardDraw();
        break;
    case 12:
        func_080B2B48();
        SioChgCardDraw();
        break;
    case 13:
        SioChgCardRestart();
        SioChgCardDraw();
        break;
    }
}

void SioChgCardWaitStart(void) {
    gSioChgCardWork->timer++;
    if (gSioChgCardWork->timer > 5) {
        SioChgCardRecvSlots();
        SioChgCardDrawPointTotals();
        gSioChgCardWork->state++;
    }
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((gSioChgCardWork->offeredCard + 1) & 0x0FFF);
}

void SioChgCardSelect(void) {
    gSioCommandSend[2] = (GetKeysPressed() & 0x0FFF) | 0x5000;
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((gSioChgCardWork->offeredCard + 1) & 0x0FFF);

    if (gSioChgCardWork->ready == 0) {
        SioChgCardHandleInput();
    } else {
        func_080B3DF8();
        gSioCommandSend[1] = 0x1AC7;
    }

    if (gSioCommandRecv[1][0] == 0x1AC7) {
        if (gSioChgCardReady[0] == 0) {
            SetSioChgCardAnimation(0, 1, 0);
            m4aSongNumStart(SONG_SYS_KETTEI);
        }
        RequestDma3Copy(gUnk_096B5FA4, (void*)0x06000020, 0xC0);
        gSioChgCardReady[0] = 1;
    } else if (gSioCommandRecv[1][0] == 0x2B9A) {
        if (gSioChgCardReady[0] == 1) {
            SetSioChgCardAnimation(0, 0, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            gSioChgCardWork->messageVisible = 0;
        }
        RequestDma3Copy(gUnk_096B5EE4, (void*)0x06000020, 0xC0);
        gSioChgCardReady[0] = 0;
    }

    if (gSioCommandRecv[1][1] == 0x1AC7) {
        if (gSioChgCardReady[1] == 0) {
            SetSioChgCardAnimation(1, 1, 0);
            m4aSongNumStart(SONG_SYS_KETTEI);
        }
        RequestDma3Copy(gUnk_096B63A4, (void*)0x060000E0, 0xC0);
        gSioChgCardReady[1] = 1;
    } else if (gSioCommandRecv[1][1] == 0x2B9A) {
        if (gSioChgCardReady[1] == 1) {
            SetSioChgCardAnimation(1, 0, 0);
            m4aSongNumStart(SONG_SYS_CLOSE);
            gSioChgCardWork->messageVisible = 0;
        }
        RequestDma3Copy(gUnk_096B62E4, (void*)0x060000E0, 0xC0);
        gSioChgCardReady[1] = 0;
    }

    if (gSioChgCardReady[0] == 1 && gSioChgCardReady[1] == 1) {
        gSioChgCardWork->timer = 0;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A3C0, gSioChgCardWork->textSlots);
        gSioChgCardWork->x3 = 64;
        gSioChgCardWork->y3 = 114;
        gSioChgCardWork->state++;
    }

    if (gSioCommandRecv[1][0] == 0xA4CA || gSioCommandRecv[1][1] == 0xA4CA) {
        if ((gSioCommandRecv[2][0] & 0xF000) == 0x5000 && (gSioCommandRecv[2][1] & 0xF000) == 0x5000 && gSioChgCardWork->leaveDelay == 0) {
            m4aSongNumStart(SONG_SYS_CLOSE);
            SioChgCardReturnOwnCards();
            SioLinkClose();
            ModeRequest(&gModeSioChgConnect, 3);
        }
    } else if (gSioCommandRecv[1][0] == 0x1D58) {
        gSioChgCardWork->leaveDelay = 10;

        if (gSioPlayerId == 0) {
            m4aSongNumStart(SONG_SYS_KETTEI);
            gSioChgCardCursor = gSioChgCardWork->cursor;
            ModeRequest(&gModeDeckExchange, 0);
        }
    } else if (gSioCommandRecv[1][1] == 0x1D58) {
        gSioChgCardWork->leaveDelay = 10;

        if (gSioPlayerId == 1) {
            m4aSongNumStart(SONG_SYS_KETTEI);
            gSioChgCardCursor = gSioChgCardWork->cursor;
            ModeRequest(&gModeDeckExchange, 0);
        }
    }
    SioChgCardRecvSlots();
    SioChgCardDrawPointTotals();

    if (gSioChgCardWork->leaveDelay > 0) {
        gSioChgCardWork->leaveDelay--;
    }
}

void SioChgCardConfirm(void) {
    if (GetKeysPressed() & A_BUTTON) {
        gSioCommandSend[1] = 0xEF01;
    } else if (GetKeysPressed() & B_BUTTON) {
        gSioCommandSend[1] = 0x58FA;
    }

    if (gSioCommandRecv[1][0] == 0xEF01 || gSioCommandRecv[1][1] == 0xEF01) {
        gSioChgCardWork->timer = 0;
        gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A404, gSioChgCardWork->textSlots);
        gSioChgCardWork->x3 = 71;
        gSioChgCardWork->y3 = 124;
        gSioChgCardWork->state++;
    }

    if (gSioCommandRecv[1][0] == 0x58FA || gSioCommandRecv[1][1] == 0x58FA) {
        m4aSongNumStart(SONG_SYS_CLOSE);
        gSioChgCardWork->timer = 0;
        SioChgCardCancelReady();
        gSioChgCardWork->state = 3;
    }
    SioChgCardRecvSlots();
    SioChgCardDrawPointTotals();
}

void SioChgCardTryTrade(void) {
    SioChgCardBackupCollection();
    gSioChgCardWork->receiveOk = SioChgCardReceiveCards();
    if (gSioChgCardWork->receiveOk == 1) {
        gSioCommandSend[1] = 0xEF23;
    } else {
        gSioCommandSend[1] = 0x1269;
    }
    gSioChgCardWork->state++;
}

void SioChgCardWaitTradeResult(void) {
    if (gSioChgCardWork->receiveOk == 1) {
        gSioCommandSend[1] = 0xEF23;
    } else {
        gSioCommandSend[1] = 0x1269;
    }

    if (gSioCommandRecv[1][0] == 0xEF23 && gSioCommandRecv[1][1] == 0xEF23) {
        m4aSongNumStart(SONG_SYS_ITEMGET);
        gSioChgCardWork->timer = 0;
        gGameState.progression.obtainedCardKinds = gSioChgCardWork->obtainedCardKindsBackup;
        gSioChgCardWork->state = 8;
    }

    if (gSioCommandRecv[1][0] == 0x1269 || gSioCommandRecv[1][1] == 0x1269) {
        m4aSongNumStart(SONG_SYS_BEEP);
        gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A4B6, gSioChgCardWork->textSlots);
        gSioChgCardWork->x3 = 63;
        gSioChgCardWork->y3 = 118;
        SioChgCardRestoreCollection();
        gSioChgCardWork->timer = 0;
        gSioChgCardWork->state = 7;
    }
}

void SioChgCardTradeFailed(void) {
    if (gSioChgCardWork->timer > 179) {
        gSioChgCardWork->timer = 0;
        SioChgCardCancelReady();
        gSioChgCardWork->state = 3;
    } else {
        gSioChgCardWork->timer++;
    }
}

void SioChgCardStartMove(void) {
    SioChgCardCreateMoveTasks();
    gSioChgCardWork->timer = 0;
    gSioChgCardWork->state++;
}

void SioChgCardSave(void) {
    TaskPoolUpdate(&gSioChgCardWork->tasks);

    if (SioHasError() == 0) {
        if (gSioDebugMode == 0) {
            if (gGameState.flags & GAME_FLAG_SECOND_FILE) {
                SaveWriteFileLarge(1);
            } else {
                SaveWriteFileLarge(0);
            }
        }
    } else {
        gSystemFlags &= ~SYSTEM_FLAG_LINK_ACTIVE;
        ModeRequest(&gModeSioError, 0);
    }
    gSioChgCardWork->timer = 0;
    gSioChgCardWork->state++;
}

void SioChgCardWaitMove(void) {
    TaskPoolUpdate(&gSioChgCardWork->tasks);

    if (gSioChgCardWork->timer == 80) {
        gSioChgCardWork->messageVisible = 0;
    }
    gSioChgCardWork->timer++;
    if (gSioChgCardWork->timer > 199) {
        gSioChgCardWork->timer = 0;
        gSioChgCardWork->messageVisible = 1;
        gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A428, gSioChgCardWork->textSlots);
        gSioChgCardWork->x3 = 70;
        gSioChgCardWork->y3 = 119;
        gSioChgCardWork->state++;
    }
}

void func_080B2AE8(void) {
    gSioChgCardWork->timer++;
    if (gSioChgCardWork->timer > 119) {
        gSioChgCardWork->timer = 0;
        gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815B3FA, gSioChgCardWork->textSlots);
        gSioChgCardWork->x3 = 83;
        gSioChgCardWork->y3 = 124;
        gSioChgCardWork->state++;
    }
}

void func_080B2B48(void) {
    gSioChgCardWork->timer++;
    if (gSioChgCardWork->timer > 119) {
        gSioChgCardWork->timer = 0;
        gSioChgCardWork->messageVisible = 0;
        gSioChgCardWork->state++;
    }
}

void SioChgCardRestart(void) {
    s32 i;
    gSioCommandSend[1] = 0x25FD;

    if (gSioCommandRecv[1][0] == 0x25FD || gSioCommandRecv[1][1] == 0x25FD) {
        if (gSioPlayerId == 0) {
            gSioChgCardCursor = 0;
        } else {
            gSioChgCardCursor = 5;
        }

        for (i = 0; i < 10; i++) {
            gSioChgCardSlots[i] = 0x800;
        }
        gSioChgCardReady[0] = 0;
        gSioChgCardReady[1] = 0;
        ModeRequest(&gModeSioChgCard, 0x800);
    }
}

void mode_sio_chg_card_2(void) {
    s32 i;
    ReleaseObjTiles(gSioChgCardWork->unk_008[0]);
    ReleaseObjTiles(gSioChgCardWork->unk_008[1]);
    ReleaseObjPalette(gSioChgCardWork->unk_008[2]);
    ReleaseObjPalette(gSioChgCardWork->unk_008[3]);
    ReleaseObjTiles(gSioChgCardWork->tiles);
    ReleaseObjPalette(gSioChgCardWork->palette);
    ReleaseObjTiles(gSioChgCardWork->tiles2);
    ReleaseObjPalette(gSioChgCardWork->palette2);

    for (i = 0; i < 10; i++) {
        ReleaseObjTiles(gSioChgCardWork->tiles3[i]);
        ReleaseObjPalette(gSioChgCardWork->palette3[i]);
    }
    ReleaseObjTiles(gSioChgCardWork->tiles4);
    ReleaseObjPalette(gSioChgCardWork->palette4);
    ReleaseObjTiles(gSioChgCardWork->tiles5);
    FreeTextSlots(gSioChgCardWork->textSlots, 42);
    FreeTextSlots(gSioChgCardWork->textSlots2, 20);
    TaskPoolDestroy(&gSioChgCardWork->tasks);
    EwramFree(gSioChgCardWork);
}

void SioChgCardDraw(void) {
    s32 i;
    ObjAffine* aff;
    gSioChgCardWork->gfx[0] = AnimUpdate(&gSioChgCardWork->anim[0]);
    gSioChgCardWork->gfx[1] = AnimUpdate(&gSioChgCardWork->anim[1]);
    gSioChgCardWork->gfx2 = AnimUpdate(&gSioChgCardWork->anim2);
    gSioChgCardWork->gfx3 = AnimUpdate(&gSioChgCardWork->anim3);
    DrawSprite(72, 72, gSioChgCardWork->gfx[0], gSioChgCardWork->unk_008[0], gSioChgCardWork->unk_008[2], 0, 0x401, 0xFFFF);
    DrawSprite(168, 72, gSioChgCardWork->gfx[1], gSioChgCardWork->unk_008[1], gSioChgCardWork->unk_008[3], 0, 0x400, 0xFFFF);

    if (gSioChgCardWork->cursorVisible == 1) {
        DrawSprite(gSioChgCardWork->x, gSioChgCardWork->y, gSioChgCardWork->gfx2, gSioChgCardWork->tiles, gSioChgCardWork->palette, 0, 0x400, 0xFFC0);
        DrawSprite(gSioChgCardWork->x + 2, gSioChgCardWork->y - 8, gSioChgCardWork->gfx3, gSioChgCardWork->tiles2, gSioChgCardWork->palette2, 0, 0x400, 0xFFA0);
    }

    for (i = 0; i < 10; i++) {
        if (gSioChgCardWork->cardVisible[i] == 1) {
            aff = AllocObjAffine(gSioChgCardWork->angle[i], gSioChgCardWork->scaleX[i], gSioChgCardWork->scaleY[i], 1);
            DrawSprite((gSioChgCardWork->x2[i] >> 8) + 16, (gSioChgCardWork->y2[i] >> 8) + 20, gSioChgCardWork->gfx4[i], gSioChgCardWork->tiles3[i], gSioChgCardWork->palette3[i], aff, 0x400, 0xFFF0);

            if (gCardDefs[gSioChgCardSlots[i]].category != 3) {
                DrawSprite((gSioChgCardWork->x2[i] >> 8) + 13, (gSioChgCardWork->y2[i] >> 8) + 16, gSioChgCardWork->gfx5[i], gSioChgCardWork->tiles4, gSioChgCardWork->palette4, aff, 0x400, 0xFFE0);
            }
        }
    }

    if (gSioChgCardWork->messageVisible == 1) {
        DrawSprite(120, 131, gSioChgCardWork->gfx6, gSioChgCardWork->tiles5, gSioChgCardWork->palette4, 0, 0, 0xFF00);
        DrawTextSlots(gSioChgCardWork->x3, gSioChgCardWork->y3, gSioChgCardWork->textSlots, gSioChgCardWork->palette2, 20, gSioChgCardWork->textSlotCount);
    }

    if (gSioChgCardWork->cardInfoVisible == 1) {
        DrawTextSlots(58, 27, gSioChgCardWork->textSlots2, gSioChgCardWork->palette, 18, gSioChgCardWork->textSlotCount2);
        DrawTextSlots(52, 42, gSioChgCardWork->textSlots, gSioChgCardWork->palette2, 18, gSioChgCardWork->textSlotCount);
    }
}

void SioChgCardRecvSlots(void) {
    if (gSioCommandRecv[0][0] == 0xACD) {
        SioChgCardSetSlot(gSioCommandRecv[3][0]);
    }

    if (gSioCommandRecv[0][1] == 0xACD) {
        SioChgCardSetSlot(gSioCommandRecv[3][1]);
    }
}

void SioChgCardSetSlot(u16 a) {
    u16 slot;
    s32 i;

    if (a != 0) {
        i = a;
        i = i >> 12;
        slot = (a & 0x0FFF) - 1;
        if (slot == 0x800) {
            gSioChgCardWork->cardVisible[i] = 0;
            ReleaseObjTiles(gSioChgCardWork->tiles3[i]);
            ReleaseObjPalette(gSioChgCardWork->palette3[i]);
            gSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].tiles2, 0x200);
            gSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].palette2, 32);
            gSioChgCardWork->gfx4[i] = gCardDefs[CARD_ID(CARD_KINGDOM_KEY, 0)].gfx2;
            gSioChgCardWork->gfx5[i] = gUnk_09EE981C[0];
            gSioChgCardSlots[i] = slot;

            if (gSioChgCardWork->cardInfoVisible == 1) {
                if (i == gSioChgCardWork->cursor) {
                    SioChgCardHideInfo();
                }
            }
        } else {
            gSioChgCardWork->cardVisible[i] = 1;
            ReleaseObjTiles(gSioChgCardWork->tiles3[i]);
            ReleaseObjPalette(gSioChgCardWork->palette3[i]);
            gSioChgCardWork->tiles3[i] = LoadObjTiles(gCardDefs[slot].tiles2, 0x200);
            gSioChgCardWork->palette3[i] = LoadObjPalette(gCardDefs[slot].palette2, 32);
            gSioChgCardWork->gfx4[i] = gCardDefs[slot].gfx2;
            gSioChgCardWork->gfx5[i] = gUnk_09EE981C[gCardDefs[slot].value];
            gSioChgCardSlots[i] = slot;
        }
    }
}

void SioChgCardRecvSlotIds(void) {
    gSioCommandSend[2] = 0x6000;

    if (gSioCommandRecv[0][0] == 0xACD) {
        SioChgCardSetSlotId(gSioCommandRecv[3][0]);
    }

    if (gSioCommandRecv[0][1] == 0xACD) {
        SioChgCardSetSlotId(gSioCommandRecv[3][1]);
    }
}

void SioChgCardSetSlotId(u16 a) {
    u16 slot;
    s32 i;

    if (a != 0) {
        i = a;
        i = i >> 12;
        slot = (a & 0x0FFF) - 1;
        if (slot == 0x800) {
            gSioChgCardSlots[i] = 0x800;
        } else {
            gSioChgCardSlots[i] = slot;
        }
    }
}

void SioChgCardDrawPointTotals(void) {
    u16 sum;
    s32 lim;
    s32 x;
    s32 i;
    s32 j;
    s16 digits[3];
    s32 v;

    sum = 0;
    lim = 0x800;
    for (i = 0; i < 5; i++) {
        x = gSioChgCardSlots[i];
        if ((s16)x != lim) {
            sum = GetCardMooglePointValue(x) - (0 - sum);
        }
    }
    v = (s16)sum;
    digits[0] = v / 100;
    v = v % 100;
    digits[1] = v / 10;
    v = v % 10;
    digits[2] = v;
    RequestDma3Copy(&gUnk_096B5DA4[digits[0] * 32], (void*)0x060001A0, 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[1] * 32], (void*)0x060001C0, 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[2] * 32], (void*)0x060001E0, 32);

    sum = 0;
    for (j = 5; j < 10; j++) {
        x = gSioChgCardSlots[j];
        if ((s16)x != 0x800) {
            sum = GetCardMooglePointValue(x) - (0 - sum);
        }
    }
    v = (s16)sum;
    digits[0] = v / 100;
    v = v % 100;
    digits[1] = v / 10;
    v = v % 10;
    digits[2] = v;
    RequestDma3Copy(&gUnk_096B5DA4[digits[0] * 32], (void*)0x06000200, 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[1] * 32], (void*)0x06000220, 32);
    RequestDma3Copy(&gUnk_096B5DA4[digits[2] * 32], (void*)0x06000240, 32);
}

void SioChgCardHandleInput(void) {
    u16 k1;
    u16 k2;
    s16 v;
    k1 = GetKeysPressed();
    k2 = GetKeysPressed();

    if (gSioChgCardWork->cardInfoVisible == 1) {
        if (GetKeysPressed() & B_BUTTON) {
            if (gSioChgCardWork->cardInfoVisible == 1) {
                SioChgCardHideInfo();
            }
        }
    } else if (gSioPlayerId == 0) {
        if (k1 & DPAD_ANY) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (k1 & DPAD_UP) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].up;
        } else if (k1 & DPAD_DOWN) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].down;
        }

        if (k1 & DPAD_LEFT) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].left;
        } else if (k1 & DPAD_RIGHT) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].right;
        }

        if (gSioChgCardWork->nextCursor != 11) {
            gSioChgCardWork->cursor = gSioChgCardWork->nextCursor;
        }

        if (k1 & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLICK);
            gSioChgCardWork->nextCursor = 10;
            gSioChgCardWork->cursor = 10;
        }
        gSioChgCardWork->x = gSioChgCardSlotPos[gSioChgCardWork->cursor].x;
        gSioChgCardWork->y = gSioChgCardSlotPos[gSioChgCardWork->cursor].y;
        v = gSioChgCardSlotPos[gSioChgCardWork->cursor].owner;

        if (k1 & A_BUTTON) {
            if (v == 2) {
                if (SioChgCardHasOwnCards() == 1) {
                    gSioChgCardWork->ready = 1;
                    gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A394, gSioChgCardWork->textSlots);
                    gSioChgCardWork->x3 = 68;
                    gSioChgCardWork->y3 = 124;
                    gSioChgCardWork->messageVisible = 1;
                } else {
                    m4aSongNumStart(SONG_SYS_BEEP);
                }
            } else if (gSioChgCardSlots[gSioChgCardWork->cursor] == 0x800) {
                if (v == 0) {
                    gSioCommandSend[1] = 0x1D58;
                }
            } else if (gSioChgCardWork->cardInfoVisible == 0) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                SioChgCardShowInfo();
            }
        } else if (k1 & B_BUTTON) {
            if (SioChgCardSlotsEmpty() == 1) {
                gSioCommandSend[1] = 0xA4CA;
            } else if (v == 0) {
                if (gSioChgCardSlots[gSioChgCardWork->cursor] != 0x800) {
                    m4aSongNumStart(SONG_SYS_CLOSE);
                    SioChgCardReturnCard();
                }
            }
        }
    } else {
        if (k2 & DPAD_ANY) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        if (k2 & DPAD_UP) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].up;
        } else if (k2 & DPAD_DOWN) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].down;
        }

        if (k2 & DPAD_LEFT) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].left;
        } else if (k2 & DPAD_RIGHT) {
            gSioChgCardWork->nextCursor = gSioChgCardSlotPos[gSioChgCardWork->cursor].right;
        }

        if (gSioChgCardWork->nextCursor != 10) {
            gSioChgCardWork->cursor = gSioChgCardWork->nextCursor;
        }

        if (k2 & START_BUTTON) {
            m4aSongNumStart(SONG_SYS_CLICK);
            gSioChgCardWork->nextCursor = 11;
            gSioChgCardWork->cursor = 11;
        }
        gSioChgCardWork->x = gSioChgCardSlotPos[gSioChgCardWork->cursor].x;
        gSioChgCardWork->y = gSioChgCardSlotPos[gSioChgCardWork->cursor].y;
        v = gSioChgCardSlotPos[gSioChgCardWork->cursor].owner;

        if (k2 & A_BUTTON) {
            if (v == 2) {
                if (SioChgCardHasOwnCards() == 1) {
                    gSioChgCardWork->ready = 1;
                    gSioChgCardWork->textSlotCount = LoadTextSlots(gUnk_0815A394, gSioChgCardWork->textSlots);
                    gSioChgCardWork->x3 = 68;
                    gSioChgCardWork->y3 = 124;
                    gSioChgCardWork->messageVisible = 1;
                } else {
                    m4aSongNumStart(SONG_SYS_BEEP);
                }
            } else if (gSioChgCardSlots[gSioChgCardWork->cursor] == 0x800) {
                if (v == 1) {
                    gSioCommandSend[1] = 0x1D58;
                }
            } else if (gSioChgCardWork->cardInfoVisible == 0) {
                m4aSongNumStart(SONG_SYS_KETTEI);
                SioChgCardShowInfo();
            }
        } else if (k2 & B_BUTTON) {
            if (SioChgCardSlotsEmpty() == 1) {
                gSioCommandSend[1] = 0xA4CA;
            } else if (v == 1) {
                if (gSioChgCardSlots[gSioChgCardWork->cursor] != 0x800) {
                    m4aSongNumStart(SONG_SYS_CLOSE);
                    SioChgCardReturnCard();
                }
            }
        }
    }

    if (gSioChgCardWork->cursor == 10) {
        gSioChgCardWork->cursorVisible = 0;

        if (gFrameCounter % 10 == 0) {
            RequestDma3Copy(&gUnk_096B5EE4[gSioChgCardWork->blinkPhase * 192], (void*)0x06000020, 0xC0);
            gSioChgCardWork->blinkPhase = 1 - gSioChgCardWork->blinkPhase;
        }
    } else if (gSioChgCardWork->cursor == 11) {
        gSioChgCardWork->cursorVisible = 0;

        if (gFrameCounter % 10 == 0) {
            RequestDma3Copy(&gUnk_096B62E4[gSioChgCardWork->blinkPhase * 192], (void*)0x060000E0, 0xC0);
            gSioChgCardWork->blinkPhase = 1 - gSioChgCardWork->blinkPhase;
        }
    } else {
        gSioChgCardWork->cursorVisible = 1;
        RequestDma3Copy(gUnk_096B5EE4, (void*)0x06000020, 0xC0);
        RequestDma3Copy(gUnk_096B5EE4 + 0x400, (void*)0x060000E0, 0xC0);
    }
}

void SioChgCardReturnCard(void) {
    AddCardToCollection(gSioChgCardSlots[gSioChgCardWork->cursor]);
    gSioChgCardSlots[gSioChgCardWork->cursor] = 0x800;
    gSioChgCardCursor = gSioChgCardWork->cursor;
    gSioChgCardWork->offeredCard = 0x800;
    gSioCommandSend[3] = ((gSioChgCardCursor & 15) << 12) | ((gSioChgCardWork->offeredCard + 1) & 0x0FFF);
}

s8 SioChgCardHasOwnCards(void) {
    s32 i;

    if (gSioPlayerId == 0) {
        for (i = 0; i < 5; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                return 1;
            }
        }
    } else {
        for (i = 5; i < 10; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                return 1;
            }
        }
    }
    return 0;
}

s8 SioChgCardSlotsEmpty(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gSioChgCardSlots[i] != 0x800) {
            return 0;
        }
    }
    return 1;
}

void SioChgCardShowInfo(void) {
    s16 n;
    u32 off;
    u16 nameId;
    CardDef* defs;
    CardDef* def;

    n = gSioChgCardSlots[gSioChgCardWork->cursor];
    defs = gCardDefs;
    def = &defs[n];
    off = def->category << 5;
    LoadPalette(gUnk_096FBF84 + off, (void*)0x050000A0, 32);
    LoadObjPaletteBank(gSioChgCardWork->palette->index, gUnk_096FBF04 + off);
    nameId = def->kind;
    defs = (CardDef*)&defs->name;
    gSioChgCardWork->textSlotCount2 = LoadTextSlots(defs[n].gfx, gSioChgCardWork->textSlots2);
    gSioChgCardWork->textSlotCount = LoadTextSlots((void*)gCardKindDescriptions[nameId], gSioChgCardWork->textSlots);
    EnableBg(0);
    gSioChgCardWork->cardInfoVisible = 1;
}

void SioChgCardHideInfo(void) {
    DisableBg(0);
    gSioChgCardWork->cardInfoVisible = 0;
}

void SioChgCardCancelReady(void) {
    s8 v;

    gSioChgCardWork->ready = 0;

    if (gSioPlayerId == 0) {
        gSioChgCardCursor = 0;
    } else {
        gSioChgCardCursor = 5;
    }

    v = gSioChgCardCursor;
    gSioChgCardWork->cursor = v;
    gSioChgCardWork->nextCursor = v;
    gSioChgCardWork->x = gSioChgCardSlotPos[gSioChgCardWork->cursor].x;
    gSioChgCardWork->y = gSioChgCardSlotPos[gSioChgCardWork->cursor].y;
    gSioChgCardWork->cursorVisible = 1;
    gSioChgCardWork->offeredCard = gSioChgCardSlots[gSioChgCardWork->cursor];
    SetSioChgCardAnimation(0, 0, 0);
    SetSioChgCardAnimation(1, 0, 0);
    RequestDma3Copy(gUnk_096B5EE4, (void*)0x06000020, 0xC0);
    RequestDma3Copy(gUnk_096B5EE4 + 0x400, (void*)0x060000E0, 0xC0);
    gSioChgCardReady[0] = 0;
    gSioChgCardReady[1] = 0;
    gSioChgCardWork->messageVisible = 0;
}

void SioChgCardCreateMoveTasks(void) {
    SioCardTaskArg arg;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (gSioChgCardSlots[i] != 0x800) {
            arg.x = &gSioChgCardWork->x2[i];
            arg.y = &gSioChgCardWork->y2[i];
            arg.scaleX = &gSioChgCardWork->scaleX[i];
            arg.scaleY = &gSioChgCardWork->scaleY[i];
            arg.angle = &gSioChgCardWork->angle[i];
            arg.visible = &gSioChgCardWork->cardVisible[i];
            arg.targetX = 0xA000;
            arg.targetY = 0x800;
            arg.delay = (5 - i) * 20;
            TaskCreate(&gSioChgCardWork->tasks, &gTaskDescChgCardObj, &arg);
        }
    }

    for (i = 5; i < 10; i++) {
        if (gSioChgCardSlots[i] != 0x800) {
            arg.x = &gSioChgCardWork->x2[i];
            arg.y = &gSioChgCardWork->y2[i];
            arg.scaleX = &gSioChgCardWork->scaleX[i];
            arg.scaleY = &gSioChgCardWork->scaleY[i];
            arg.angle = &gSioChgCardWork->angle[i];
            arg.visible = &gSioChgCardWork->cardVisible[i];
            arg.targetX = 0x4000;
            arg.targetY = 0x800;
            arg.delay = (10 - i) * 20 + 10;
            TaskCreate(&gSioChgCardWork->tasks, &gTaskDescChgCardObj, &arg);
        }
    }
}

void SioChgCardBackupCollection(void) {
    u16 i;

    for (i = 0; i <= 0x3E6; i++) {
        gSioChgCardWork->collectionBackup[i] = gCardCollection[i];
    }
    gSioChgCardWork->obtainedCardKindsBackup = gGameState.progression.obtainedCardKinds;
}

void SioChgCardRestoreCollection(void) {
    u16 i;

    for (i = 0; i <= 0x3E6; i++) {
        gCardCollection[i] = gSioChgCardWork->collectionBackup[i];
    }
    gGameState.progression.obtainedCardKinds = gSioChgCardWork->obtainedCardKindsBackup;
}

s16 SioChgCardReceiveCards(void) {
    s32 i;
    s32 t;

    if (gSioPlayerId == 0) {
        for (i = 5; i < 10; i++) {
            t = gSioChgCardSlots[i] != 0x800;
            if (t) {
                if (AddCardToCollection(gSioChgCardSlots[i]) == -1) {
                    return 0;
                }
            }
        }
    } else {
        for (i = 0; i < 5; i++) {
            t = gSioChgCardSlots[i] != 0x800;
            if (t) {
                if (AddCardToCollection(gSioChgCardSlots[i]) == -1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void SioChgCardReturnOwnCards(void) {
    s32 i;

    if (gSioPlayerId == 0) {
        for (i = 0; i < 5; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                AddCardToCollection(gSioChgCardSlots[i]);
            }
        }
    } else {
        for (i = 5; i < 10; i++) {
            if (gSioChgCardSlots[i] != 0x800) {
                AddCardToCollection(gSioChgCardSlots[i]);
            }
        }
    }
}

void func_080B3DF8(void) {
}
#endif

void mode_sioError_0(s32 arg) {
    gSystemFlags |= SYSTEM_FLAG_NO_SOFT_RESET;
    gSioErrorWork = EwramAlloc(sizeof(SioErrorWork));
    m4aMPlayAllStop();
    FadeStartIn(0, 16);
    SioLinkClose();
    SetBgMode0();
    SetupBg(0, 0, 7, 15);
    SetupBg(1, 1, 31, 0);
    SetBgSize(1, 0);
    LoadBgTiles(1, gUnk_096ACA44, 0xBC0);
    LoadBgPalette(1, gUnk_096FBA04, 0x40);
    LoadBgMap(1, gUnk_096F5C64, 0x800);
    EnableBg(0);
    EnableBg(1);
    DisableBg(2);
    DisableBg(3);
    gSioErrorWork->unk_00 = 0;
    gSioErrorWork->unk_02 = 0;
    gSioErrorWork->unk_04 = 0;
#ifdef VERSION_EU
    LoadBgPalette(0, gCard00Palette, 32);
    LoadBgTiles(0, gUnk_0950E2F8, 0x140);
    if (gLanguage == 1 || gLanguage == 4) {
        LoadBgMap(0, gUnkEu_096C798C, 0x800);
        SetBgScroll(0, 0xFFE9, 0xFFCD);
    } else {
        LoadBgMap(0, gUnk_096112B8, 0x800);
        SetBgScroll(0, 0xFFE9, 0xFFD0);
    }
#elif defined(VERSION_JP)
    LoadBgTiles(0, gUnk_096AD604, 0x140);
    LoadBgMap(0, gUnk_096F6464, 0x800);
    LoadBgPalette(0, gCard00Palette, 32);
#else
    LoadBgTiles(0, gUnk_0950E2F8, 0x140);
    LoadBgMap(0, gUnk_096112B8, 0x800);
    LoadBgPalette(0, gCard00Palette, 32);
    SetBgScroll(0, 0xFFE9, 0xFFD0);
#endif
    InitTextSlots(gSioErrorWork->textSlots, SIO_ERROR_TEXT_SLOTS);
#ifdef VERSION_EU
    gSioErrorWork->textSlotCount = LoadTextSlots(eu_0805E924(&gUnkEu_088920BC), gSioErrorWork->textSlots);
#elif defined(VERSION_JP)
    gSioErrorWork->textSlotCount = LoadTextSlots(gUnk_0814F180, gSioErrorWork->textSlots);
#else
    gSioErrorWork->textSlotCount = LoadTextSlots(gUnk_0815A2BE, gSioErrorWork->textSlots);
#endif
    gSioErrorWork->palette = LoadObjPalette(gUnk_096FBAA4, 32);
}

void mode_sioError_1(void) {
    SioErrorDraw();
}

void SioErrorDraw(void) {
#ifdef VERSION_JP
    DrawTextSlots(58, 62, gSioErrorWork->textSlots, gSioErrorWork->palette, 20, gSioErrorWork->textSlotCount);
#else
    DrawTextSlots(36, 57, gSioErrorWork->textSlots, gSioErrorWork->palette, 20, gSioErrorWork->textSlotCount);
#endif
}

void mode_sioError_2(void) {
    ReleaseObjPalette(gSioErrorWork->palette);
    FreeTextSlots(gSioErrorWork->textSlots, SIO_ERROR_TEXT_SLOTS);
    EwramFree(gSioErrorWork);
}

SioWorldEntry gSioWorldEntries[13] = {
#if defined(VERSION_US)
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnk_0815A57C, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 0},
    {gUnk_08C90824, 16384, 0, gUnk_08EF5384, 4096, 0, gUnk_08F68B84, 256, 0, gUnk_0815A56C, BATTLE_STAGE_AGRABAH, 0, 36},
    {gUnk_08C88824, 16384, 0, gUnk_08EF3384, 4096, 0, gUnk_08F689C4, 192, 0, gUnk_0815A5AA, BATTLE_STAGE_ATLANTICA, 0, 32},
    {gUnk_08C7C824, 16384, 0, gUnk_08EF0384, 4096, 0, gUnk_08F686E4, 224, 0, gUnk_0815A54A, BATTLE_STAGE_OLYMPUS_COLISEUM, 0, 16},
    {gUnk_08C84824, 16384, 0, gUnk_08EF2384, 4096, 0, gUnk_08F68904, 192, 0, gUnk_0815A534, BATTLE_STAGE_WONDERLAND, 0, 28},
    {gUnk_08C8C824, 16384, 0, gUnk_08EF4384, 4096, 0, gUnk_08F68A84, 256, 0, gUnk_0815A59A, BATTLE_STAGE_MONSTRO, 0, 36},
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnk_0815A57C, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 18},
    {gUnk_08C98824, 16064, 0, gUnk_08EF7384, 4096, 0, gUnk_08F68D64, 320, 0, gUnk_0815A5BE, BATTLE_STAGE_NEVER_LAND, 0, 26},
    {gUnk_08CA06E4, 16384, 0, gUnk_08EF9384, 4096, 0, gUnk_08F68FC4, 224, 0, gUnk_0815A5D4, BATTLE_STAGE_HOLLOW_BASTION, 0, 20},
    {gUnk_08C9C6E4, 16384, 0, gUnk_08EF8384, 4096, 0, gUnk_08F68EA4, 288, 0, gUnk_0815A62A, BATTLE_STAGE_DESTINY_ISLANDS, 0, 18},
    {gUnk_08C78824, 16384, 0, gUnk_08EEF384, 4096, 0, gUnk_08F68624, 192, 0, gUnk_0815A518, BATTLE_STAGE_TRAVERSE_TOWN, 0, 20},
    {gUnk_08CA46E4, 16384, 0, gUnk_08EFA384, 4096, 0, gUnk_08F690A4, 320, 0, gUnk_0815A60E, BATTLE_STAGE_TWILIGHT_TOWN, 0, 22},
    {gUnk_08CA86E4, 16384, 0, gUnk_08EFB384, 4096, 0, gUnk_08F691E4, 224, 0, gUnk_0815A64A, BATTLE_STAGE_CASTLE_OBLIVION, 0, 22},
#elif defined(VERSION_JP)
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnkJp_0814E5B8, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 0},
    {gUnk_08C90824, 16384, 0, gUnk_08EF5384, 4096, 0, gUnk_08F68B84, 256, 0, gUnkJp_0814E590, BATTLE_STAGE_AGRABAH, 0, 28},
    {gUnk_08C88824, 16384, 0, gUnk_08EF3384, 4096, 0, gUnk_08F689C4, 192, 0, gUnkJp_0814E5E4, BATTLE_STAGE_ATLANTICA, 0, 20},
    {gUnk_08C7C824, 16384, 0, gUnk_08EF0384, 4096, 0, gUnk_08F686E4, 224, 0, gUnkJp_0814E5CC, BATTLE_STAGE_OLYMPUS_COLISEUM, 0, 8},
    {gUnk_08C84824, 16384, 0, gUnk_08EF2384, 4096, 0, gUnk_08F68904, 192, 0, gUnkJp_0814E59C, BATTLE_STAGE_WONDERLAND, 0, 20},
    {gUnk_08C8C824, 16384, 0, gUnk_08EF4384, 4096, 0, gUnk_08F68A84, 256, 0, gUnkJp_0814E5AC, BATTLE_STAGE_MONSTRO, 0, 28},
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 4096, 0, gUnk_08F68C84, 224, 0, gUnkJp_0814E5B8, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 16},
    {gUnk_08C98824, 16064, 0, gUnk_08EF7384, 4096, 0, gUnk_08F68D64, 320, 0, gUnkJp_0814E5F4, BATTLE_STAGE_NEVER_LAND, 0, 26},
    {gUnk_08CA06E4, 16384, 0, gUnk_08EF9384, 4096, 0, gUnk_08F68FC4, 224, 0, gUnkJp_0814E618, BATTLE_STAGE_HOLLOW_BASTION, 0, 12},
    {gUnk_08C9C6E4, 16384, 0, gUnk_08EF8384, 4096, 0, gUnk_08F68EA4, 288, 0, gUnkJp_0814E62C, BATTLE_STAGE_DESTINY_ISLANDS, 0, 2},
    {gUnk_08C78824, 16384, 0, gUnk_08EEF384, 4096, 0, gUnk_08F68624, 192, 0, gUnkJp_0814E57C, BATTLE_STAGE_TRAVERSE_TOWN, 0, 12},
    {gUnk_08CA46E4, 16384, 0, gUnk_08EFA384, 4096, 0, gUnk_08F690A4, 320, 0, gUnkJp_0814E644, BATTLE_STAGE_TWILIGHT_TOWN, 0, 12},
    {gUnk_08CA86E4, 16384, 0, gUnk_08EFB384, 4096, 0, gUnk_08F691E4, 224, 0, gUnkJp_0814E658, BATTLE_STAGE_CASTLE_OBLIVION, 0, 34},
#elif defined(VERSION_EU)
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 1312, 0, gUnk_08F68C84, 224, 0, &gUnkEu_0888E4C0, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 0},
    {gUnk_08C90824, 16384, 0, gUnk_08EF5384, 1216, 0, gUnk_08F68B84, 256, 0, &gUnkEu_0888E3A0, BATTLE_STAGE_AGRABAH, 0, 36},
    {gUnk_08C88824, 16384, 0, gUnk_08EF3384, 1620, 0, gUnk_08F689C4, 192, 0, &gUnkEu_0888E578, BATTLE_STAGE_ATLANTICA, 0, 32},
    {gUnk_08C7C824, 16384, 0, gUnk_08EF0384, 1164, 0, gUnk_08F686E4, 224, 0, &gUnkEu_0888E530, BATTLE_STAGE_OLYMPUS_COLISEUM, 0, 16},
    {gUnk_08C84824, 16384, 0, gUnk_08EF2384, 1412, 0, gUnk_08F68904, 192, 0, &gUnkEu_0888E410, BATTLE_STAGE_WONDERLAND, 0, 28},
    {gUnk_08C8C824, 16384, 0, gUnk_08EF4384, 1692, 0, gUnk_08F68A84, 256, 0, &gUnkEu_0888E450, BATTLE_STAGE_MONSTRO, 0, 36},
    {gUnk_08C94824, 16384, 0, gUnk_08EF6384, 1312, 0, gUnk_08F68C84, 224, 0, &gUnkEu_0888E4C0, BATTLE_STAGE_HALLOWEEN_TOWN, 0, 18},
    {gUnk_08C98824, 16064, 0, gUnk_08EF7384, 1020, 0, gUnk_08F68D64, 320, 0, &gUnkEu_0888E5DC, BATTLE_STAGE_NEVER_LAND, 0, 26},
    {gUnk_08CA06E4, 16384, 0, gUnk_08EF9384, 1084, 0, gUnk_08F68FC4, 224, 0, &gUnkEu_0888E6BC, BATTLE_STAGE_HOLLOW_BASTION, 0, 20},
    {gUnk_08C9C6E4, 16384, 0, gUnk_08EF8384, 1112, 0, gUnk_08F68EA4, 288, 0, &gUnkEu_0888E72C, BATTLE_STAGE_DESTINY_ISLANDS, 0, 18},
    {gUnk_08C78824, 16384, 0, gUnk_08EEF384, 1088, 0, gUnk_08F68624, 192, 0, &gUnkEu_0888E364, BATTLE_STAGE_TRAVERSE_TOWN, 0, 20},
    {gUnk_08CA46E4, 16384, 0, gUnk_08EFA384, 1196, 0, gUnk_08F690A4, 320, 0, &gUnkEu_0888E78C, BATTLE_STAGE_TWILIGHT_TOWN, 0, 22},
    {gUnk_08CA86E4, 16384, 0, gUnk_08EFB384, 868, 0, gUnk_08F691E4, 224, 0, &gUnkEu_0888E804, BATTLE_STAGE_CASTLE_OBLIVION, 0, 22},
#endif
};

s8 gSioHandicapMarkerX[12] = {
    0,
    0,
    4,
    8,
    12,
    16,
    21,
    26,
    30,
    34,
    38,
    42,
};

u16 gSioHandicapAp[12] = {
    0,
    65527,
    65528,
    65529,
    65530,
    65531,
    65532,
    65533,
    65534,
    65535,
    0,
    1,
};

Mode gModeSioBtlOption = {
    "mode_sio_btl_option",
    mode_sio_btl_option_0,
    mode_sio_btl_option_1,
    mode_sio_btl_option_2,
};

Mode gModeSioBtlCardget = {
    "mode_sio_btl_cardget",
    mode_sio_btl_cardget_0,
    mode_sio_btl_cardget_1,
    mode_sio_btl_cardget_2,
};

#ifndef VERSION_EU
Mode gModeSioChgConnect = {
    "mode_sio_chg_connect",
    mode_sio_chg_connect_0,
    mode_sio_chg_connect_1,
    mode_sio_chg_connect_2,
};

SioChgCardPos gSioChgCardSlotPos[13] = {
    {16, 76, 0, 10, 1, 9, 2, {0, 0, 0}},
    {30, 105, 0, 0, 10, 8, 3, {0, 0, 0}},
    {43, 76, 0, 10, 3, 0, 4, {0, 0, 0}},
    {57, 105, 0, 2, 10, 1, 6, {0, 0, 0}},
    {70, 76, 0, 10, 3, 2, 5, {0, 0, 0}},
    {139, 76, 1, 11, 6, 4, 7, {0, 0, 0}},
    {153, 105, 1, 7, 11, 3, 8, {0, 0, 0}},
    {166, 76, 1, 11, 6, 5, 9, {0, 0, 0}},
    {180, 105, 1, 9, 11, 6, 1, {0, 0, 0}},
    {193, 76, 1, 11, 8, 7, 0, {0, 0, 0}},
    {0, 0, 2, 1, 0, 10, 10, {0, 0, 0}},
    {0, 0, 2, 8, 9, 11, 11, {0, 0, 0}},
    {0, 0, 0, 0, 0, 0, 0, {0, 0, 0}},
};
#endif

#ifndef VERSION_EU
const SioAnimDef gSioChgCardAnimDefs[3] = {
    {gSor1fl00Frames, gSor1fl00Anims, gSor1fl00Tiles, 0},
    {gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 0},
    {gSor1fl15Frames, gSor1fl15Anims, gSor1fl15Tiles, 1},
};
#endif

#ifndef VERSION_EU
Mode gModeSioChgCard = {
    "mode_sio_chg_card",
    mode_sio_chg_card_0,
    mode_sio_chg_card_1,
    mode_sio_chg_card_2,
};
#endif

Mode gModeSioError = {
    "mode_sioError",
    mode_sioError_0,
    mode_sioError_1,
    mode_sioError_2,
};
