#include "mode_ms_top.h"
#include "registration_data.h"
#include "system_state.h"
#include "mode_ms.h"
#include "mode_ms_top_api.h"
#include "jiminy_data.h"
#include "jiminy_text_assets.h"
#include "mode_chkobj_assets.h"
#include "localized_resource_assets.h"
#include "anim.h"
#include "bos5.h"
#include "ms_charge.h"
#include "mode_mapinspect.h"
#include "mode_worldwarp.h"
#include "worldinspect_assets.h"
#include "sprites_btl.h"
#include "sprites_evt.h"
#include "sprites_moogle_shop.h"
#include "sprites_sora.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "mode_ms_api.h"
#include "fade.h"
#include "songs.h"
#include "player_progression.h"

static s16 sMsTopCursor;
static void* sMsTopNextMode;
static struct ObjTiles* sMsTopBarTiles;
static struct ObjPalette* sMsTopBarPalette;
static struct ObjTiles* gUnk_020357D0;
static struct ObjPalette* gUnk_020357D4;
static AnimState gWorldwarpAnim;
static struct ObjTiles* sMsTopSoraTiles;
static struct ObjPalette* sMsTopSoraPalette;
static AnimState sMsTopSoraAnim;
static struct ObjTiles* sMsTopShadowTiles;
static struct ObjPalette* sMsTopShadowPalette;
static void* sMsTopWarpTiles[2];
static void* sMsTopWarpPalettes[2];
static AnimState sMsTopWarpAnims[2];
static struct ObjTiles* sMsTopMoogleTiles;
static struct ObjPalette* sMsTopMooglePalette;
static AnimState sMsTopMoogleAnim;
static s16 sMsTopScrollDir;
static s16 sMsTopScrollSteps;
static s16 sMsTopMoogleWalkDir;
static s32 sMsTopBg1ScrollX;
static s32 sMsTopBg0ScrollX;
static s32 gUnk_02035888;
static s32 sMsTopMoogleX;
static s16 sMsTopState;
static s16 sMsTopSteps;
static s32 sMsTopBarY[2];
static s32 sMsTopBarX;
static u8 sMsTopBarVisible;
static TaskPool gMsTopTaskPool;
static s16 sMsTopPendingMessage;
static s16 sMsTopPendingOptionMessage;
static u8 sMsTopMessageStarted;
static s16 sMsTopIntroIndex;

static const WarpDef sWarpDefs[2] = {
#if defined(VERSION_US)
    {&gModeMsShop, gUnk_09A36EDC, 1280, 104, 48, 1, 136, 80, 0, 48, 66, {0, 0}, {{64, 64, gWorldwarpAssetUs_09A3D81C, 32, {0, 0}, gWorldwarpAssetUs_099A2F84, 832, {0, 0}, gUnk_09EF999C, gUnk_09EF9998, 0, {0, 0}}, {192, 84, gMoguPalette, 32, {0, 0}, gUnk_099A2194, 2368, {0, 0}, gUnk_09EF9978, gUnk_09EF9928, 1, {0, 0}}}},
    {&gModeMsCharge, gUnk_09A373DC, 1280, 76, 48, 0, 112, 80, 1, 32, 32, {0, 0}, {{32, 64, gWorldwarpAssetUs_09A3D83C, 32, {0, 0}, gWorldwarpAssetUs_099A32E4, 832, {0, 0}, gUnk_09EF99A4, gUnk_09EF99A0, 0, {0, 0}}, {160, 84, gUnk_09A3D77C, 32, {0, 0}, gUnk_099A2194, 2368, {0, 0}, gUnk_09EF9978, gUnk_09EF9928, 0, {0, 0}}}},
#elif defined(VERSION_JP)
    {&gModeMsShop, gUnk_09A36EDC, 1280, 104, 48, 1, 136, 80, 0, 48, 66, {0, 0}, {{64, 64, gWorldwarpAssetJp_099F22A4, 32, {0, 0}, gWorldwarpAssetJp_09957A0C, 832, {0, 0}, gUnk_09EF999C, gUnk_09EF9998, 0, {0, 0}}, {192, 84, gMoguPalette, 32, {0, 0}, gUnk_099A2194, 2368, {0, 0}, gUnk_09EF9978, gUnk_09EF9928, 1, {0, 0}}}},
    {&gModeMsCharge, gUnk_09A373DC, 1280, 76, 48, 0, 112, 80, 1, 32, 32, {0, 0}, {{32, 64, gWorldwarpAssetJp_099F22C4, 32, {0, 0}, gWorldwarpAssetJp_09957D6C, 832, {0, 0}, gUnk_09EF99A4, gUnk_09EF99A0, 0, {0, 0}}, {160, 84, gUnk_09A3D77C, 32, {0, 0}, gUnk_099A2194, 2368, {0, 0}, gUnk_09EF9978, gUnk_09EF9928, 0, {0, 0}}}},
#elif defined(VERSION_EU)
    {&gModeMsShop, gUnk_09A36EDC, 1280, 104, 48, 1, 136, 80, 0, 48, 66, {0, 0}, {{64, 64, gWorldwarpAssetEu_09A9B2E0, 32, {0, 0}, gWorldwarpAssetEu_099B0F08, 832, {0, 0}, gUnk_09EF999C, gUnk_09EF9998, 0, {0, 0}}, {192, 84, gMoguPalette, 32, {0, 0}, gUnk_099A2194, 2368, {0, 0}, gUnk_09EF9978, gUnk_09EF9928, 1, {0, 0}}}},
    {&gModeMsCharge, gUnk_09A373DC, 1280, 76, 48, 0, 112, 80, 1, 32, 32, {0, 0}, {{32, 64, gWorldwarpAssetEu_09A9B300, 32, {0, 0}, gWorldwarpAssetEu_099B1268, 832, {0, 0}, gUnk_09EF99A4, gUnk_09EF99A0, 0, {0, 0}}, {160, 84, gUnk_09A3D77C, 32, {0, 0}, gUnk_099A2194, 2368, {0, 0}, gUnk_09EF9978, gUnk_09EF9928, 0, {0, 0}}}},
#endif
};

static const u16 sMsTopIntroMessages[3] = {
    129,
    130,
    131,
};

#ifdef VERSION_EU
static void* sUnkEu_09F84EE8[5] = {
    gUnk_09A378DC,
    gUnk_09A382DC,
    gUnkEu_09A8C1A0,
    gUnkEu_09A8BCA0,
    gUnkEu_09A8B7A0,
};

static void* sUnkEu_09F84EFC[5] = {
    gUnk_09A37DDC,
    gUnkEu_09A8C6A0,
    gUnkEu_09A8D5A0,
    gUnkEu_09A8D0A0,
    gUnkEu_09A8CBA0,
};

static void* sUnkEu_09F84F10[5] = {
    gUnk_099A2AD4,
    gUnkEu_099AFC68,
    gUnkEu_099B0A58,
    gUnkEu_099B0588,
    gUnkEu_099B00F8,
};

static void* sUnkEu_09F84F24[5] = {
    gUnk_099A2AF0,
    gUnkEu_099AFC84,
    gUnkEu_099B0A74,
    gUnkEu_099B05A4,
    gUnkEu_099B0114,
};

static void* sUnkEu_09F84F38[5] = {
    gUnk_099A2B24,
    gUnkEu_099AFCB8,
    gUnkEu_099B0AA8,
    gUnkEu_099B05D8,
    gUnkEu_099B0148,
};
#endif

Mode gModeMsTop = {
    "mode_ms_top",
    (ModeInitFunc)mode_ms_top_0,
    mode_ms_top_1,
    mode_ms_top_2,
};

u32 GetMooglePoints(void) {
    return gGameState.progression.mooglePoints;
}

void SetMooglePoints(u32 a) {
    gGameState.progression.mooglePoints = a;
}

u8 SpendMooglePoints(u32 a) {
    u8 ok = 0;

    if (GetMooglePoints() >= a) {
        SetMooglePoints(GetMooglePoints() - a);
        ok = 1;
    }
    return ok;
}

u8 AddMooglePoints(u32 a) {
    a += GetMooglePoints();
    if (a > 99999) {
        SetMooglePoints(99999);
        return 0;
    }
    SetMooglePoints(a);
    return 1;
}

void LoadDecimalDigitTiles(u32 value, u8* glyphs, u8* dst, u16 stride, u16 count) {
    s32 i;
    u32 digit;

    for (i = 0; i < count; i++) {
        digit = value % 10;
        value /= 10;
        RequestDma3Copy(&glyphs[digit * stride], &dst[(count - 1 - i) * stride], stride);
    }
}

void UpdateMsTopMooglePalette(void) {
    s32 flag;
    s16 x;
    s32 v;
    s32 base;

    x = sWarpDefs[0].x3 + ((sMsTopMoogleX - sMsTopBg0ScrollX) >> 8);
    flag = 0;
    v = x;
    base = (-sMsTopBg1ScrollX) >> 8;
    if (v <= base + 0x1C || v >= base + 0x1C + 0x62) {
        flag = 1;
    }
    ReleaseObjPalette(sMsTopMooglePalette);
    sMsTopMooglePalette = LoadObjPalette(flag == 0 ? gMoguPalette : gUnk_09A3D77C, 0x20);
}

void UpdateMsTopWarpGfx(void) {
    s16 i;
    s32 flag;
    s16 x;
    s32 v;
    s32 base;

    for (i = 0; i <= 1; i++) {
        x = sWarpDefs[0].gfx[i].x - (sMsTopBg0ScrollX >> 8);
        flag = 0;
        v = x;
        base = (-sMsTopBg1ScrollX) >> 8;
        if (v <= base + 0x18 || v >= base + 0x18 + 0x6A) {
            flag = 1;
        }

        if (sMsTopWarpPalettes[i] != NULL) {
            ReleaseObjPalette(sMsTopWarpPalettes[i]);
        }

        if (sMsTopWarpTiles[i] != NULL) {
            ReleaseObjTiles(sMsTopWarpTiles[i]);
        }
        sMsTopWarpPalettes[i] = LoadObjPalette(sWarpDefs[flag].gfx[i].palette, sWarpDefs[flag].gfx[i].paletteSize);
        sMsTopWarpTiles[i] = LoadObjTiles(sWarpDefs[flag].gfx[i].tiles, sWarpDefs[flag].gfx[i].tilesSize);
        AnimInit(&sMsTopWarpAnims[i], sWarpDefs[flag].gfx[i].anims, sWarpDefs[flag].gfx[i].gfxTable);
        AnimStart(&sMsTopWarpAnims[i], sWarpDefs[flag].gfx[i].animId, ANIM_FLAG_LOOP);
    }
}

void SetMsTopWarpAnim(s16 a) {
    AnimStart(&gWorldwarpAnim, sWarpDefs[a].animId, ANIM_FLAG_LOOP);
}

void QueueMsTopIntroMessage(void) {
    if (sMsTopPendingMessage < 0) {
        if (sMsTopIntroIndex <= 2) {
            sMsTopPendingMessage = sMsTopIntroMessages[sMsTopIntroIndex];
            sMsTopIntroIndex++;
        }
    }
}

void MsTopHandleInput(void) {
    s16 prev;
    u16 keys;

    prev = sMsTopCursor;
    keys = GetKeysPressed();
    if (keys & A_BUTTON) {
        if (sMsTopCursor == 1) {
            AnimStart(&sMsTopWarpAnims[sMsTopCursor], 2, ANIM_FLAG_LOOP);
        }
        sMsTopNextMode = sWarpDefs[sMsTopCursor].mode;
        m4aSongNumStart(SONG_SYS_KETTEI);
        FadeStartOut(0, 16);
        FadeLock();
        sMsTopState = 11;
    } else if (keys & B_BUTTON) {
        sMsTopNextMode = 0;
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsTopBarVisible = 1;
#ifdef VERSION_EU
        LoadBgMap(2, sUnkEu_09F84EE8[gLanguage], 0x500);
#else
        LoadBgMap(2, gUnk_09A378DC, 0x500);
#endif
        sMsTopSteps = 16;
        sMsTopState = 9;
    } else if (keys & START_BUTTON) {
        sMsTopNextMode = 0;
        m4aSongNumStart(SONG_SYS_CLOSE);
        sMsTopBarVisible = 1;
#ifdef VERSION_EU
        LoadBgMap(2, sUnkEu_09F84EE8[gLanguage], 0x500);
#else
        LoadBgMap(2, gUnk_09A378DC, 0x500);
#endif
        FadeStartOut(0, 16);
        FadeLock();
        sMsTopState = 11;
    } else if ((keys & DPAD_LEFT) && sMsTopScrollDir != 1 && sMsTopCursor != 0) {
        sMsTopCursor = 0;
        sMsTopScrollDir = 1;
        sMsTopScrollSteps = 30 - sMsTopScrollSteps;
        sMsTopMoogleWalkDir = 1;
        AnimStart(&sMsTopMoogleAnim, 1, ANIM_FLAG_LOOP);
    } else if ((keys & DPAD_RIGHT) && sMsTopScrollDir != 2 && sMsTopCursor != 1) {
        sMsTopCursor = 1;
        sMsTopScrollDir = 2;
        sMsTopScrollSteps = 30 - sMsTopScrollSteps;
        sMsTopMoogleWalkDir = 2;
        AnimStart(&sMsTopMoogleAnim, 1, ANIM_FLAG_LOOP);
    }

    if (sMsTopCursor != prev) {
        if (IsMessageWindowOpen()) {
            CloseMessageWindow();
        }
        sMsTopPendingOptionMessage = sMsTopCursor == 0 ? 0x40 : 0x41;
        SetMsTopWarpAnim(sMsTopCursor);
        m4aSongNumStart(SONG_SYS_CLICK);
    }
}

void MsTopDraw(void) {
    s32 i;
    u16 flags;

    if (sMsTopBarVisible != 0) {
#ifdef VERSION_EU
        DrawSprite(sMsTopBarX >> 8, 0, sUnkEu_09F84F10[gLanguage], sMsTopBarTiles, sMsTopBarPalette, 0, SPRITE_PRIORITY(2), 0x7D0);
        DrawSprite(0x80, sMsTopBarY[0] >> 8, sUnkEu_09F84F24[gLanguage], sMsTopBarTiles, sMsTopBarPalette, 0, SPRITE_PRIORITY(2), 0x7D1);
        DrawSprite(0x80, sMsTopBarY[1] >> 8, sUnkEu_09F84F38[gLanguage], sMsTopBarTiles, sMsTopBarPalette, 0, SPRITE_PRIORITY(2), 0x7D1);
#else
        DrawSprite(sMsTopBarX >> 8, 0, gUnk_099A2AD4, sMsTopBarTiles, sMsTopBarPalette, 0, SPRITE_PRIORITY(2), 0x7D0);
        DrawSprite(0x80, sMsTopBarY[0] >> 8, gUnk_099A2AF0, sMsTopBarTiles, sMsTopBarPalette, 0, SPRITE_PRIORITY(2), 0x7D1);
        DrawSprite(0x80, sMsTopBarY[1] >> 8, gUnk_099A2B24, sMsTopBarTiles, sMsTopBarPalette, 0, SPRITE_PRIORITY(2), 0x7D1);
#endif
    }

    flags = 0x800;

    switch (sMsTopMoogleWalkDir) {
    case 0:
        if (sMsTopCursor == 0) {
            flags |= 1;
        }
        break;
    case 1:
        break;
    case 2:
        flags |= 1;
        break;
    }
    DrawSprite(sWarpDefs[0].x3 + ((sMsTopMoogleX - sMsTopBg0ScrollX) >> 8), sWarpDefs[0].y3,
        AnimUpdate(&sMsTopMoogleAnim), sMsTopMoogleTiles, sMsTopMooglePalette, 0, flags, 0x834);
    DrawSprite((gUnk_02035888 >> 8) + sWarpDefs[0].x, sWarpDefs[0].y,
        AnimUpdate(&gWorldwarpAnim), gUnk_020357D0, gUnk_020357D4, 0, SPRITE_PRIORITY(2), 0x7D0);

    DrawSprite(sWarpDefs[0].x2 + (gUnk_02035888 >> 8), sWarpDefs[0].y2,
        AnimUpdate(&sMsTopSoraAnim), sMsTopSoraTiles, sMsTopSoraPalette, 0,
        0x800 | sWarpDefs[sMsTopCursor].flags, 0x7D0);
    DrawSprite(sWarpDefs[0].x2 + (gUnk_02035888 >> 8), sWarpDefs[0].y2,
        gUnk_08B22BA8, sMsTopShadowTiles, sMsTopShadowPalette, 0,
        0x800 | sWarpDefs[sMsTopCursor].flags, 0x7D1);

    for (i = 0; i <= 1; i++) {
        DrawSprite(sWarpDefs[0].gfx[i].x - (sMsTopBg0ScrollX >> 8), sWarpDefs[0].gfx[i].y,
            AnimUpdate(&sMsTopWarpAnims[i]), sMsTopWarpTiles[i], sMsTopWarpPalettes[i], 0, SPRITE_PRIORITY(2), 0x7D0);
    }

    if (sMsTopState == 6) {
        DrawMooglePackOpening();
    }
    TaskPoolDraw(&gMsTopTaskPool);
    SetBgScroll(0, (u16)(sMsTopBg0ScrollX >> 8), 0);
    SetBgScroll(1, (u16)(sMsTopBg1ScrollX >> 8), 0);
}

void mode_ms_top_0(u32 a) {
    s32 i;

    SpriteReset();
    FadeStartIn(0, 16);
    SetBgMode0();
    gBldCnt = (BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0);
    gBldAlpha = 0x1010;
    SetupBg(0, 0, 28, 0);
    SetupBg(1, 0, 29, 0);
    SetupBg(2, 0, 30, 0);
    SetupBg(3, 3, 31, 14);
    SetBgPriority(0, 3);
    SetBgPriority(1, 2);
    SetBgPriority(2, 1);
    SetBgPriority(3, 0);

    if (a & 1) {
        ClearMoogleRoomFlags();
    }

    if (a & 2) {
        sMsTopBarVisible = 0;
        sMsTopState = 7;
    } else {
        sMsTopBarVisible = 1;
        sMsTopState = 0;
        sMsTopSteps = 16;
        sMsTopBarY[0] = -0x800;
        sMsTopBarY[1] = 0xA800;
        sMsTopBarX = -0x8000;
        sMsTopCursor = 0;
    }

    sMsTopScrollDir = 0;
    sMsTopScrollSteps = 0;
    sMsTopMoogleWalkDir = 0;

    if (sMsTopCursor == 0) {
        sMsTopBg1ScrollX = 0;
        sMsTopBg0ScrollX = 0;
        gUnk_02035888 = 0;
        sMsTopMoogleX = 0;
    } else {
        sMsTopBg1ScrollX = -0x6100;
        sMsTopBg0ScrollX = 0x2100;
        gUnk_02035888 = -0x1C00;
        sMsTopMoogleX = 0xBC00;
    }

    sMsTopPendingMessage = -1;
    sMsTopPendingOptionMessage = -1;
    sMsTopMessageStarted = 0;
    LoadBgPalette(0, gUnk_09A3D79C, 0x60);
#ifdef VERSION_EU
    LoadBgTiles(0, gUnk_09A10A3C, 0x24C0);
#else
    LoadBgTiles(0, gUnk_09A10A3C, 0x19A0);
#endif
    LoadDecimalDigitTiles(GetMooglePoints(), gUnk_09A123DC, (u8*)GetBgCharBase(0) + 0x20, 0x20, 5);
    LoadBgMap(0, gUnk_09A36EDC, 0x500);
    LoadBgMap(1, gUnk_09A373DC, 0x500);

    if (sMsTopBarVisible != 0) {
#ifdef VERSION_EU
        LoadBgMap(2, sUnkEu_09F84EE8[gLanguage], 0x500);
#else
        LoadBgMap(2, gUnk_09A378DC, 0x500);
#endif
    } else {
#ifdef VERSION_EU
        LoadBgMap(2, sUnkEu_09F84EFC[gLanguage], 0x500);
#else
        LoadBgMap(2, gUnk_09A37DDC, 0x500);
#endif
    }

    for (i = 0; i < 2; i++) {
        sMsTopWarpPalettes[i] = 0;
        sMsTopWarpTiles[i] = 0;
    }

    sMsTopBarPalette = LoadObjPalette(gUnk_09A3D7FC, 0x20);
    sMsTopBarTiles = LoadObjTiles(gUnk_099A2B62, 0x400);
    gUnk_020357D4 = LoadObjPalette(gUnk_09A3D85C, 0x20);
    gUnk_020357D0 = LoadObjTiles(gUnk_099A36F8, 0x500);
    AnimInit(&gWorldwarpAnim, gUnk_09EF99D0, gUnk_09EF99A8);
    sMsTopSoraPalette = LoadObjPalette(gSoraPalette, 0x20);
    sMsTopSoraTiles = LoadObjTiles(gSor1ll00Tiles, 0x300);
    AnimInit(&sMsTopSoraAnim, gSor1ll00Anims, gSor1ll00Frames);
    AnimStart(&sMsTopSoraAnim, 0, ANIM_FLAG_LOOP);
    sMsTopShadowPalette = LoadObjPalette(gBStatesPalette, 0x20);
    sMsTopShadowTiles = LoadObjTiles(gUnk_08B22BBC, 0x100);
    sMsTopMooglePalette = LoadObjPalette(gMoguPalette, 0x20);
    sMsTopMoogleTiles = LoadObjTiles(gMoguFl00Tiles, 0xC00);
    AnimInit(&sMsTopMoogleAnim, gMoguFl00Anims, gMoguFl00Frames);
    AnimStart(&sMsTopMoogleAnim, 0, ANIM_FLAG_LOOP);
    SetMsTopWarpAnim(sMsTopCursor);
    UpdateMsTopWarpGfx();
    UpdateMsTopMooglePalette();
    TaskPoolInit(&gMsTopTaskPool, 1);
    EnableBg(0);
    EnableBg(1);
    EnableBg(2);
    DisableBg(3);
}

void mode_ms_top_1(void) {
    UpdatePlayTime();

    switch (sMsTopState) {
    case 0:
        ApproachValue(&sMsTopBarY[0], 0, sMsTopSteps);
        ApproachValue(&sMsTopBarY[1], 0x9800, sMsTopSteps);

        if (--sMsTopSteps <= 0) {
            sMsTopSteps = 16;
            sMsTopState = 1;
        }

        break;
    case 1:
        ApproachValue(&sMsTopBarX, 0, sMsTopSteps);

        if (--sMsTopSteps <= 0) {
            sMsTopBarVisible = 0;
#ifdef VERSION_EU
            LoadBgMap(2, sUnkEu_09F84EFC[gLanguage], 0x500);
#else
            LoadBgMap(2, gUnk_09A37DDC, 0x500);
#endif
            sMsTopState = 2;
        }
        break;
    case 2:
        if ((gGameState.progression.unk_82 & 0x80) == 0) {
            sMsTopIntroIndex = 0;
            sMsTopState = 3;
        } else {
            sMsTopState = 4;
        }
        break;
    case 3:
        QueueMsTopIntroMessage();

        if (sMsTopIntroIndex > 2 && sMsTopPendingMessage < 0 && IsMessageWindowOpen() == 0) {
            SetJiminyFlag(27);
            gGameState.progression.unk_82 |= 0x80;
            sMsTopState = 4;
        }
        break;
    case 4:
        if (GetMoogleFreePackFlag(gMapFloorState.room) == 0) {
            sMsTopPendingMessage = 0x42;
            sMsTopState = 5;
        } else {
            sMsTopState = 7;
        }
        break;
    case 5:
        if (IsMessageWindowOpen() == 0) {
            if (gGameState.floor <= 5) {
                RollMooglePackCards(0, 0);
            } else if (gGameState.floor <= 9) {
                RollMooglePackCards(0, 1);
            } else {
                RollMooglePackCards(0, 2);
            }

            InitMooglePackOpening(120, 80);
            FadeSetPaletteExcluded(13, 1);
            FadeToAmount(0, 16, 8);
            sMsTopState = 6;
        }
        break;
    case 6:
        if (UpdateMooglePackOpening(1) == 0) {
            ReleaseMooglePackOpening();
            SetMoogleFreePackFlag(gMapFloorState.room);
            SetupBg(3, 3, 31, 14);
            DisableBg(3);
            LoadDecimalDigitTiles(GetMooglePoints(), gUnk_09A123DC, (u8*)GetBgCharBase(0) + 0x20, 0x20, 5);
            FadeToOriginal(0, 8);
            sMsTopState = 7;
        }
        break;
    case 7:
        sMsTopPendingOptionMessage = sMsTopCursor == 0 ? 0x40 : 0x41;
        sMsTopState = 8;
        break;
    case 8:
        MsTopHandleInput();
        break;
    case 9:
        ApproachValue(&sMsTopBarX, -0x8000, sMsTopSteps);

        if (--sMsTopSteps <= 0) {
            sMsTopSteps = 16;
            sMsTopState = 10;
        }

        break;
    case 10:
        ApproachValue(&sMsTopBarY[0], -0x800, sMsTopSteps);
        ApproachValue(&sMsTopBarY[1], 0xA800, sMsTopSteps);

        if (--sMsTopSteps <= 0) {
            FadeStartOut(0, 16);
            FadeLock();
            sMsTopState = 11;
        }

        break;
    case 11:
        if (FadeIsActive() == 0) {
            if (sMsTopNextMode != NULL) {
                ModeRequest(sMsTopNextMode, 0);
            } else {
                RequestMapMode();
            }
        }

        break;
    }

    switch (sMsTopScrollDir) {
    case 0:
        break;
    case 1:
        UpdateMsTopWarpGfx();
        ApproachValue(&sMsTopBg1ScrollX, 0, sMsTopScrollSteps);
        ApproachValue(&sMsTopBg0ScrollX, 0, sMsTopScrollSteps);
        ApproachValue(&gUnk_02035888, 0, sMsTopScrollSteps);

        if (--sMsTopScrollSteps <= 0) {
            sMsTopScrollDir = 0;
        }

        break;
    case 2:
        UpdateMsTopWarpGfx();
        ApproachValue(&sMsTopBg1ScrollX, -0x6100, sMsTopScrollSteps);
        ApproachValue(&sMsTopBg0ScrollX, 0x2100, sMsTopScrollSteps);
        ApproachValue(&gUnk_02035888, -0x1C00, sMsTopScrollSteps);

        if (--sMsTopScrollSteps <= 0) {
            sMsTopScrollDir = 0;
        }

        break;
    }

    switch (sMsTopMoogleWalkDir) {
    case 0:
        break;
    case 1:
        UpdateMsTopMooglePalette();
        sMsTopMoogleX -= 0x180;

        if (sMsTopMoogleX <= 0) {
            AnimStart(&sMsTopMoogleAnim, 0, ANIM_FLAG_LOOP);
            sMsTopMoogleX = 0;
            sMsTopMoogleWalkDir = 0;
        }
        break;
    case 2:
        UpdateMsTopMooglePalette();
        sMsTopMoogleX += 0x180;
        if (sMsTopMoogleX >= 0xBC00) {
            AnimStart(&sMsTopMoogleAnim, 0, ANIM_FLAG_LOOP);
            sMsTopMoogleX = 0xBC00;
            sMsTopMoogleWalkDir = 0;
        }
        break;
    }

    if (sMsTopPendingOptionMessage >= 0) {
        if (sMsTopMessageStarted != 0) {
            if (IsMessageWindowOpen() == 0) {
                ShowPersistentCardMessage(&gMsTopTaskPool, 3, sMsTopPendingOptionMessage);
                sMsTopPendingOptionMessage = -1;
            }
        } else {
            ShowPersistentCardMessage(&gMsTopTaskPool, 3, sMsTopPendingOptionMessage);
            sMsTopPendingOptionMessage = -1;
            sMsTopMessageStarted = 1;
        }
    }

    if (sMsTopPendingMessage >= 0) {
        if (sMsTopMessageStarted != 0) {
            if (IsMessageWindowOpen() == 0) {
                CreateCardMessageTask(&gMsTopTaskPool, 3, sMsTopPendingMessage);
                sMsTopPendingMessage = -1;
            }
        } else {
            CreateCardMessageTask(&gMsTopTaskPool, 3, sMsTopPendingMessage);
            sMsTopPendingMessage = -1;
            sMsTopMessageStarted = 1;
        }
    }

    TaskPoolUpdate(&gMsTopTaskPool);
    MsTopDraw();
}

void mode_ms_top_2(void) {
    s32 i;

    ReleaseObjPalette(sMsTopBarPalette);
    ReleaseObjTiles(sMsTopBarTiles);
    ReleaseObjPalette(gUnk_020357D4);
    ReleaseObjTiles(gUnk_020357D0);
    ReleaseObjPalette(sMsTopSoraPalette);
    ReleaseObjTiles(sMsTopSoraTiles);
    ReleaseObjPalette(sMsTopShadowPalette);
    ReleaseObjTiles(sMsTopShadowTiles);

    for (i = 0; i < 2; i++) {
        ReleaseObjPalette(sMsTopWarpPalettes[i]);
        ReleaseObjTiles(sMsTopWarpTiles[i]);
    }

    ReleaseObjPalette(sMsTopMooglePalette);
    ReleaseObjTiles(sMsTopMoogleTiles);
    TaskPoolDestroy(&gMsTopTaskPool);
}
