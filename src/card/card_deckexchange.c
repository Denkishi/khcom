#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "mode_sio_api.h"
#include "card_battle.h"
#include "mode_test_api.h"
#include "player_progression.h"
#include "m4a_song.h"
#include "game_state.h"
#include <string.h>
#include "text.h"
#include "monsgage.h"
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "text_types.h"
#include "taskpool.h"
#include "key.h"
#include "gba/syscall.h"
#include "malloc.h"
#include "card.h"
#include "card_reload_assets.h"
#include "map_card_assets.h"
#include "card_localized_assets.h"
#include "card_help_assets.h"
#include "card_message_assets.h"
#include "card_description_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_deck_menu.h"

#ifndef VERSION_EU
u16 gUnk_0203A9DC EWRAM_COMMON(4);
#endif

u16 func_080857D4(u8 slot);
u8 func_080A8C20(DeckExchangeWork* w);
u8 func_080A86F4(DeckExchangeWork* w, void* a);
u8 func_080A7C80(DeckExchangeWork* w, void* a);
u8 func_080A8BD8(DeckExchangeWork* w, void* a);
void func_0808CC58(u16 a, u8 b);
u8 func_080A8430(DeckExchangeWork* w, void* a);
void func_08090170(DeckCard2Work* node);
void func_080A9968(DeckExchangeWork* w);
void func_080AA6D4(u8 a);
void func_080AAEB0(DeckExchangeWork* w, u16 index);
void func_080AAEEC(DeckExchangeWork* w, s16 n);
u8 func_080A7914(DeckExchangeWork* w, void* a);
void func_0808DD20(u8 a, u16 b);
s32 func_080AAB08(DeckExchangeWork* w);
void func_0808CBB4(u8 a, u8 b);
void func_080A9F08(u8 a);
void func_080AA1F8(void);
u8 func_080A82E0(DeckExchangeWork* w, void* a);
u16 CountCollectionCards(void);
u16 CountCardsInDecks(void);
void func_08084D78(UnkStruct_08084D78* out, u8 deck, u8 mode, u16 n, void* p);
u16 func_08084E50(UnkStruct_08084D78* out, u8 deck, u8 mode, u16 n, void* p);
void func_0808500C(u8 mode, u16* out);
void ClearCardCollectionSlot(u16* p);
Deck* GetDeck(u8 index);
u16 GetDeckCpCost(u8 index);
u8* GetDeckName(u8 index);
u16 func_080857D4(u8 slot);
u16 GetDeckCardCount(u8 index);
u8 GetActiveDeckIndex(void);
void func_0808CBB4(u8 a, u8 b);
void func_0808CC58(u16 a, u8 b);
void func_0808DD20(u8 a, u16 b);
void func_08090170(DeckCard2Work* node);
#ifndef VERSION_EU
const s16 gUnk_09041F04[3] = { 116, 116, 116 };

const s16 gUnk_09041F0A[3] = { 56, 104, 148 };

const s16 gUnk_09041F10[5] = { 12, 28, 42, 56, 70 };

const s16 gUnk_09041F1A[6] = { 172, 172, 188, 202, 216, 230 };

const s16 gUnk_09041F26[5] = { 64, 82, 100, 118, 136 };

const s16 gUnk_09041F30[2] = { 80, 128 };

const s16 gUnk_09041F34[5] = { 80, 88, 96, 104, 112 };

const u16 gUnk_09041F3E[4] = { 45, 93, 141, 30 };

void deckexchange_0(DeckExchangeWork* w, void* a) {
    s32 zero;
    u16 n;

    zero = 0;
    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(DeckExchangeWork) / 4);
    w->tiles7 = 0;
    w->tiles4 = 0;
    w->tiles5 = 0;
    w->tiles6 = 0;
    w->palette2 = 0;
    w->palette3 = 0;
    w->tiles8 = 0;
    w->palette6 = 0;
    w->palette7 = 0;
    w->palette4 = 0;
    w->unk_4C0 = 0;
    w->unk_4C4 = 0;
    w->unk_4CC = 0;
    w->unk_6FC = a;
    SetBgMode0();
    SetBackdropColor(0, 0, 0);
    SetupBg(0, 3, 31, 0);
    SetupBg(1, 2, 23, 0);
    SetupBg(2, 1, 15, 0);
    SetupBg(3, 0, 30, 0);
    SetBgPriority(0, 0);
    SetBgPriority(1, 1);
    SetBgPriority(2, 2);
    FadeStartIn(0, 16);
    ListPoolInit(&w->pool);
    TaskPoolInit(&w->tasks, 99);
    TaskPoolInit(&w->tasks2, 1);
    w->unk_700 = GetActiveDeckIndex();
    func_080A968C(w, 0);
    w->tiles = AllocObjTiles(0x120, 0);
    SetObjTileSource(w->tiles, gUnk_090A4664);
    AnimInit(&w->anim, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    w->x2 = gUnk_09041F04[0] << 8;
    w->y2 = gUnk_09041F0A[0] << 8;
    w->unk_6CE = 0;
    w->tiles3 = LoadObjTiles(gUnk_090A44C4, 32);
    w->palette = LoadObjPalette(gUnk_09614418, 32);
    w->tiles2 = AllocObjTiles(0x280, 0);
    func_080AAA8C(w, 0);
    w->palette4 = LoadObjPalette(gUnk_09614438, 32);
    w->unk_715 = 0;
    w->unk_6D0 = 0;
    w->unk_6D2 = 0;
    w->unk_6F2 = 0;
    w->unk_6F3 = 0;
    w->unk_6F6 = 4;
    w->unk_707 = 0;
    w->unk_706 = 0;
    w->unk_6F0 = 0;
    w->unk_6F7 = func_080857D4(0);
    w->unk_6F8 = func_080857D4(1);
    w->unk_6F9 = func_080857D4(2);
    w->unk_6FA = func_080857D4(3);
    w->unk_701 = 0;
    w->unk_6E0 = 0;
    w->unk_70D = 0;
    w->unk_710 = 0;
    w->unk_711 = 16;
    w->unk_712 = 16;
    w->unk_6A4 = 0;
    w->unk_6AC = -0x800;
    w->unk_6A8 = 0;
    w->unk_6B0 = 0xA000;
    w->unk_6B4 = -0x8000;
    w->unk_714 = 0;
    w->x7 = 8;
    w->y7 = 113;
    w->textSlotCount5 = 0;
    w->unk_6C4 = 79;
    n = gUnk_09041F3E[w->unk_700];
    w->unk_6C6 = n;
    w->unk_6C8 = 225;
    n = gUnk_09041F3E[w->unk_700];
    w->unk_6CA = n;
    w->unk_70F = 0;
    w->unk_713 = 0;
    w->textSlotCount = 0;
    w->textSlotCount2 = 0;
    w->textSlotCount3 = 0;
    w->textSlotCount4 = 0;
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    InitTextSlots(w->textSlots4, 30);
    InitTextSlots(w->textSlots5, 90);
}
u8 deckexchange_1(DeckExchangeWork* w, void* a) {
    FadeStartIn(0, 16);

    switch (w->unk_715) {
    case 0:
        RequestDma3Clear(GetBgCharBase(0), 0x1000);
        break;
    case 1:
        RequestDma3Clear(GetBgCharBase(0) + 0x1000, 0x1000);
        break;
    case 2:
        RequestDma3Clear(GetBgCharBase(0) + 0x2000, 0x1000);
        break;
    case 3:
        RequestDma3Clear(GetBgCharBase(0) + 0x3000, 0x1000);
        break;
    case 4:
        RequestDma3Clear(GetBgCharBase(1), 0x1000);
        break;
    case 5:
        RequestDma3Clear(GetBgCharBase(1) + 0x1000, 0x1000);
        break;
    case 6:
        RequestDma3Clear(GetBgCharBase(1) + 0x2000, 0x1000);
        break;
    case 7:
        RequestDma3Clear(GetBgCharBase(1) + 0x3000, 0x1000);
        break;
    case 8:
        RequestDma3Clear(GetBgCharBase(2), 0x1000);
        break;
    case 9:
        RequestDma3Clear(GetBgCharBase(2) + 0x1000, 0x1000);
        break;
    case 10:
        RequestDma3Clear(GetBgCharBase(2) + 0x2000, 0x1000);
        break;
    case 11:
        RequestDma3Clear(GetBgCharBase(2) + 0x3000, 0x1000);
        break;
    case 12:
        RequestDma3Clear(GetBgCharBase(3), 0x1000);
        break;
    case 13:
        RequestDma3Clear(GetBgCharBase(3) + 0x1000, 0x1000);
        break;
    case 14:
        RequestDma3Clear(GetBgCharBase(3) + 0x2000, 0x1000);
        break;
    case 15:
        RequestDma3Clear(GetBgCharBase(3) + 0x3000, 0x1000);
        w->unk_715 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A7914);
        return 1;
    }

    w->unk_715++;
}

u8 func_080A7914(DeckExchangeWork* w, void* a) {
    FadeStartIn(0, 16);

    switch (w->unk_715) {
    case 0:
        LoadBgTiles(3, gUnk_09402F78, 0x2000);
        break;
    case 1:
        RequestDma3Copy(&gUnk_09402F78[0x2000],
                        (u8*)GetBgCharBase(3) + 0x2000, 0x2000);
        break;
    case 2:
        LoadBgPalette(3, gUnk_09614118, 0x1E0);
        break;
    case 3:
        LoadBgTiles(0, gUnk_09406F78, 0xC00);
        break;
    case 4:
        LoadBgMap(0, gUnk_08125E24, 0x800);
        break;
    case 5:
        LoadBgTiles(1, &gUnk_09406F78[0xC00], 0x2000);
        break;
    case 6:
        RequestDma3Copy(&gUnk_09406F78[0x2C00],
                        (u8*)GetBgCharBase(1) + 0x2000, 0x1E20);
        break;
    case 7:
        LoadBgMap(1, gUnk_08125E24, 0x800);
        break;
    case 8:
        LoadBgTiles(2, &gUnk_09406F78[0x4A20], 0x2000);
        break;
    case 9:
        RequestDma3Copy(&gUnk_09406F78[0x6A20],
                        (u8*)GetBgCharBase(2) + 0x2000, 0x1E20);
        break;
    case 10:
        LoadBgMap(2, gUnk_08125E24, 0x800);
        break;
    case 12:
        w->unk_715 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A7ABC);
        return 1;
    }

    w->unk_715++;
    SetBgScroll(0, (u16)-88, (u16)-16);
    SetBgScroll(1, (u16)-88, (u16)-64);
    SetBgScroll(2, (u16)-88, (u16)-112);
    return 1;
}
u8 func_080A7ABC(DeckExchangeWork* w, void* a) {
    s32 v;

    FadeStartIn(0, 16);

    switch (w->unk_715) {
    case 1:
        LoadBgMap(0, &gUnk_095192B8[0x800], 0x180);
        break;
    case 2:
        LoadBgMap(1, &gUnk_095192B8[0x1000], 0x180);
        break;
    case 3:
        LoadBgMap(2, &gUnk_095192B8[0x1800], 0x180);
        break;
    case 4:
        func_0808CBB4(w->unk_6F7, 0);
        break;
    case 5:
        func_0808CBB4(w->unk_6F8, 1);
        break;
    case 6:
        func_0808CBB4(w->unk_6F9, 2);
        break;
    case 7:
        func_0808CBB4(w->unk_6FA, 3);
        break;
    case 8:
        func_080A9B84(w, w->unk_700);
        break;
    case 9:
        func_080A9E40(0);
        func_080A9E40(1);
        func_080A9E40(2);
        break;
    case 10:
        func_080A9F08(GetActiveDeckIndex());
        func_080AA1F8();
        w->x = 0x4800;
        w->y = 0x2800;
        v = w->unk_700;
        w->unk_6D2 = v;
        ApproachValue(&w->x2, gUnk_09041F04[w->unk_6D0] << 8, w->unk_6F6);
        ApproachValue(&w->y2, gUnk_09041F0A[w->unk_6D2] << 8, w->unk_6F6);
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A82E0);
        w->unk_6F0 = 1;
        func_080A9AE8(w);
        func_080AA328(w);
        break;
    }

    w->unk_715++;
    return 1;
}

u8 func_080A7C80(DeckExchangeWork* w, void* a) {
    u8 n;
    s32 m;

    if (w->unk_70D != 0) {
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);

        if (GetKeysPressed() & START_BUTTON) {
            w->unk_710 = 1;
        }

        return 1;
    }

    if (w->unk_710 != 0) {
        if ((u8)func_080AAC40(w) != 0 && (u8)func_080AAC8C(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A8C20);
            FadeStartOut(0, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }

        w->unk_710 = 0;
    }

    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);

    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->unk_6D0 > 0) {
            w->unk_6D0--;
            w->unk_6F6 = 4;

            if ((u8)func_080AA77C(w, 32) != 0) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        func_080AA680(w);
        break;
    case DPAD_RIGHT:
        if (w->unk_6D0 <= 0) {
            w->unk_6D0++;
            w->unk_6F6 = 4;

            if ((u8)func_080AA77C(w, 16) != 0) {
                m4aSongNumStart(SONG_SYS_CLICK);
            }
        }

        func_080AA680(w);
        break;
    case DPAD_UP:
        n = w->unk_6D2;

        if (w->unk_6D2 > 0) {
            w->unk_6D2--;
        }

        w->unk_6F6 = 4;
        func_080AA77C(w, 64);

        if ((s8)n != w->unk_6D2) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        func_080AA680(w);
        break;
    case DPAD_DOWN:
        n = w->unk_6D2;

        if (w->unk_6D2 <= 3) {
            w->unk_6D2++;
        }

        w->unk_6F6 = 4;
        func_080AA77C(w, 128);

        if ((s8)n != w->unk_6D2) {
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        func_080AA680(w);
        break;
    }

    switch (GetKeysPressed()) {
    case B_BUTTON:
        func_080AAA8C(w, 0);
        m = (s8)w->unk_6F4;
        w->unk_6D0 = m;
        m = (s8)w->unk_6F5;
        w->unk_6D2 = m;
        w->x2 = gUnk_0903595E[w->unk_6D0] << 8;
        w->y2 = gUnk_09035964[w->unk_6D2] << 8;
        func_080AA450(w);
        w->unk_6F0 = 9;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A86F4);
        return 1;
    case A_BUTTON:
        if ((u8)func_080AAB08(w) == 0) {
            return 1;
        }

        func_080AA1F8();
        func_0808500C(3, w->unk_6E2);
        func_0808CC58(w->unk_6E2[0], 0);
        func_0808CC58(w->unk_6E2[1], 1);
        func_0808CC58(w->unk_6E2[2], 2);
        func_0808CC58(w->unk_6E2[3], 3);
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A8BD8);
        func_080AA680(w);
        w->unk_6F6 = 4;
        break;
    case START_BUTTON:
        if ((u8)func_080AAC40(w) != 0 && (u8)func_080AAC8C(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A8C20);
            FadeStartOut(0, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }

        return 1;
    }

    if (w->unk_6F6 != 0) {
        ApproachValue(&w->x2, gUnk_09041F30[w->unk_6D0] << 8, w->unk_6F6);
        ApproachValue(&w->y2, (gUnk_09041F34[w->unk_6D2] - 16) << 8, w->unk_6F6);
        w->unk_6F6--;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

u8 func_080A8020(DeckExchangeWork* w, void* a) {
    s32 i;

    w->gfx = AnimUpdate(&w->anim);
    switch (GetKeysRepeat()) {
    case DPAD_LEFT:
        if (w->unk_6D0 > 1) {
            w->unk_6D0--;
            w->unk_6F6 = 4;
            m4aSongNumStart(SONG_SYS_CLICK);
            w->unk_701 = w->unk_6D0;
            func_080AA148(w->unk_701, w->unk_706);
            func_080A9968(w);
            w->unk_716 = func_080A97D4(w, w->unk_701, 1);
        }
        for (i = 0; i < 10; i++) {
            func_0808DD20(0, i);
        }
        break;
    case DPAD_RIGHT:
        if (w->unk_6D0 < 5) {
            w->unk_6D0++;
            w->unk_6F6 = 4;
            m4aSongNumStart(SONG_SYS_CLICK);
            w->unk_701 = w->unk_6D0;
            func_080AA148(w->unk_701, w->unk_706);
            func_080A9968(w);
            w->unk_716 = func_080A97D4(w, w->unk_701, 1);
        }
        for (i = 0; i < 10; i++) {
            func_0808DD20(0, i);
        }
        break;
    case DPAD_DOWN:
        if (w->unk_716 != 0) {
            w->unk_6D0 = 0;
            w->unk_6D2 = 0;
            w->unk_6F6 = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            func_080AA450(w);
            w->unk_6F0 = 9;
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A86F4);
            w->x = 0xA000;
            w->y = 0x2800;
            w->unk_6EC = 4;
            return 1;
        }
        m4aSongNumStart(SONG_SYS_BEEP);
        break;
    case B_BUTTON:
        if (w->unk_716 != 0) {
            w->unk_6D0 = 0;
            w->unk_6D2 = 0;
            w->unk_6F6 = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
            func_080AA450(w);
            w->unk_6F0 = 9;
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A86F4);
            w->x = 0xA000;
            w->y = 0x2800;
            w->unk_6EC = 4;
            return 1;
        }
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A8BD8);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case START_BUTTON:
        if ((u8)func_080AAC40(w) != 0 && (u8)func_080AAC8C(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A8C20);
            FadeStartOut(0, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }
        return 1;
    }
    if (w->unk_6F6 != 0) {
        ApproachValue(&w->x2, gUnk_09041F1A[w->unk_6D0] << 8, w->unk_6F6);
        ApproachValue(&w->y2, 0x1E00, w->unk_6F6);
        w->unk_6F6--;
    }
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}
u8 func_080A82E0(DeckExchangeWork* w, void* a) {
    FadeStartIn(0, 4);
    SetupBg(3, 0, 30, 0);
    SetupBg(2, 0, 15, 0);
    SetupBg(1, 0, 23, 0);
    SetupBg(0, 0, 31, 0);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);
    SetBgScroll(2, 0, 16);
    LoadBgMap(3, gUnk_09515AB8, 0x800);
    LoadBgMap(2, gUnk_095182B8, 0x800);
    LoadBgMap(1, gUnk_09514AB8, 0x800);
    DisableBg(0);
    func_0808500C(3, w->unk_6E2);
    func_0808CC58(w->unk_6E2[0], 0);
    func_0808CC58(w->unk_6E2[1], 1);
    func_0808CC58(w->unk_6E2[2], 2);
    func_0808CC58(w->unk_6E2[3], 3);
    w->unk_6F0 = 9;
    func_080AAA8C(w, 0);
    func_080A9968(w);
    w->unk_715 = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)func_080A8430);
    w->unk_6C4 = 0xFFFE;
    w->unk_6C6 = 142;
    w->unk_6C8 = 142;
    w->unk_6CA = 142;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}
u8 func_080A8430(DeckExchangeWork* w, void* a) {
    u32 zero;
    u16 i;
    u16 j;
    u16 n;

    FadeStartIn(0, 16);
    switch (w->unk_715) {
    case 0:
        w->unk_6E0 = 286;
        w->unk_4D0 = EwramAlloc(w->unk_6E0 * sizeof(UnkStruct_08084D78));
        zero = 0;
        CpuSet(&zero, w->unk_4D0, CPU_SET_SRC_FIXED | CPU_SET_32BIT | w->unk_6E0 * (sizeof(UnkStruct_08084D78) / 4));
        break;
    case 1:
        func_08084D78(w->unk_4D0, w->unk_700, 0, w->unk_6E0, w->unk_4F4);
        break;
    case 2:
        w->unk_6E0 = func_08084E50(w->unk_4D0, w->unk_700, 0, w->unk_6E0, w->unk_4F4);
        break;
    case 3:
        w->unk_4CC = EwramAlloc(w->unk_6E0 * sizeof(UnkStruct_08084D78));
        for (i = 0, n = 0; i < 286; i++) {
            if (w->unk_4D0[i].unk_16 != 0) {
                w->unk_4CC[n] = w->unk_4D0[i];
                w->unk_4CC[n].unk_1C = EwramAlloc(w->unk_4D0[i].unk_18 * 2);
                for (j = 0; j < w->unk_4D0[i].unk_18; j++) {
                    w->unk_4CC[n].unk_1C[j] = w->unk_4D0[i].unk_1C[j];
                }
                n++;
            }
        }
        break;
    case 4:
        for (i = 0; i < 286; i++) {
            if (w->unk_4D0[i].unk_16 != 0) {
                EwramFree(w->unk_4D0[i].unk_1C);
            }
        }
        EwramFree(w->unk_4D0);
        break;
    case 5:
        w->unk_701 = 5;
        w->unk_716 = func_080A97D4(w, 5, 1);
        func_080A9AE8(w);
        w->x2 = gUnk_0903595E[0] << 8;
        w->y2 = gUnk_09035964[0] << 8;
        w->unk_706 = 2;
        w->unk_6D0 = 0;
        w->unk_6D2 = 0;
        func_080AA450(w);
        if (w->unk_716 != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A86F4);
        } else {
            w->unk_6D0 = w->unk_701;
            w->unk_6F6 = 4;
            w->unk_6F0 = 10;
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A8020);
        }
        break;
    }
    w->unk_715++;
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}
u8 func_080A86F4(DeckExchangeWork* w, void* a) {
    s32 i;

    w->gfx = AnimUpdate(&w->anim);
    w->gfx2 = AnimUpdate(&w->anim2);
    if (w->unk_70D != 0) {
        TaskPoolUpdate(&w->tasks);
        TaskPoolUpdate(&w->tasks2);
        if (GetKeysPressed() & START_BUTTON) {
            w->unk_710 = 1;
        }
        return 1;
    }
    if (w->unk_710 != 0) {
        if ((u8)func_080AAC40(w) != 0 && (u8)func_080AAC8C(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A8C20);
            FadeStartOut(0, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
            return 1;
        }
        w->unk_710 = 0;
    }
    switch (GetKeysRepeat()) {
    case DPAD_UP:
        if (w->unk_6D2 > 0) {
            if ((u8)func_080AAD84(w, w->unk_6D0, (s16)(w->unk_6D2 - 1)) != 0) {
                w->unk_6D2--;
                w->unk_6F6 = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else {
            if (func_080A9A38(w) == 0) {
                func_080AAF20(w);
                w->unk_6D0 = w->unk_701;
                w->unk_6F6 = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
                w->unk_6F0 = 10;
                for (i = 0; i < 10; i++) {
                    func_0808DD20(0, i);
                }
                SetTaskUpdate(a, (TaskUpdateFunc)func_080A8020);
                return 1;
            }
            func_080AAF20(w);
        }
        func_080AA450(w);
        break;
    case DPAD_DOWN:
        if (w->unk_6D2 < 3) {
            if ((u8)func_080AAD84(w, w->unk_6D0, (s16)(w->unk_6D2 + 1)) != 0) {
                w->unk_6D2++;
                w->unk_6F6 = 4;
                m4aSongNumStart(SONG_SYS_CLICKI04B);
            }
        } else if ((u8)func_080AAD84(w, w->unk_6D0, (s16)(w->unk_6D2 + 1)) != 0) {
            func_080A99A0(w);
            func_080AAF20(w);
        }
        func_080AA450(w);
        break;
    case DPAD_LEFT:
        if (w->unk_6D0 > 0 && (u8)func_080AAD84(w, (s16)(w->unk_6D0 - 1), w->unk_6D2) != 0) {
            w->unk_6D0--;
            w->unk_6F6 = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }
        func_080AA450(w);
        break;
    case DPAD_RIGHT:
        if (w->unk_6D0 > 1) {
            w->unk_6F6 = 4;
            return 1;
        }
        if ((u8)func_080AAD84(w, (s16)(w->unk_6D0 + 1), w->unk_6D2) != 0) {
            w->unk_6D0++;
            w->unk_6F6 = 4;
            m4aSongNumStart(SONG_SYS_CLICKI04B);
        }
        func_080AA450(w);
        break;
    }
    switch (GetKeysPressed()) {
    case A_BUTTON:
        if ((u8)func_080AAD2C(w) != 0) {
            w->unk_6F4 = w->unk_6D0;
            w->unk_6F5 = w->unk_6D2;
            w->unk_6D0 = 0;
            w->unk_6D2 = 0;
            func_080AAA8C(w, 1);
            w->unk_6F0 = 11;
            m4aSongNumStart(SONG_SYS_KETTEI);
            if ((u8)func_080AA77C(w, 0) != 0) {
                func_080AA680(w);
                w->x2 = gUnk_09041F30[w->unk_6D0] << 8;
                w->y2 = (gUnk_09041F34[w->unk_6D2] - 16) << 8;
                SetTaskUpdate(a, (TaskUpdateFunc)func_080A7C80);
                return 1;
            }
            w->unk_6D0 = (s8)w->unk_6F4;
            w->unk_6D2 = (s8)w->unk_6F5;
            func_080AAA8C(w, 0);
            w->unk_6F0 = 9;
            m4aSongNumStart(SONG_SYS_BEEP);
            return 1;
        }
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    case B_BUTTON:
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A8BD8);
        m4aSongNumStart(SONG_SYS_CLOSE);
        return 1;
    case START_BUTTON:
        if ((u8)func_080AAC40(w) != 0 && (u8)func_080AAC8C(w) != 0) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_080A8C20);
            FadeStartOut(0, 4);
            m4aSongNumStart(SONG_SYS_CANSEL);
        }
        return 1;
    }
    if (GetKeysPressed() & SELECT_BUTTON) {
        func_080AACC8(w);
        w->unk_6D0 = w->unk_701;
        w->unk_6F6 = 4;
        w->x = 0xA000;
        w->y = 0x2800;
        w->unk_6EC = 4;
        m4aSongNumStart(SONG_SYS_CLICKI04B);
        w->unk_6F0 = 10;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080A8020);
        return 1;
    }
    if (w->unk_6F6 != 0) {
        ApproachValue(&w->x2, gUnk_0903595E[w->unk_6D0] << 8, w->unk_6F6);
        ApproachValue(&w->y2, gUnk_09035964[w->unk_6D2] << 8, w->unk_6F6);
        w->unk_6F6--;
    }
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}
u8 func_080A8BD8(DeckExchangeWork* w, void* a) {
    FadeStartOut(0, 16);
    w->unk_701 = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)func_080A8C20);
    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}
u8 func_080A8C20(DeckExchangeWork* w) {
    if (FadeIsActive() == 0) {
        func_080A9968(w);
        return 0;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    return 1;
}

void func_080A8C58(DeckExchangeWork* w, u8 b) {
    if (b == 0) {
        switch (w->unk_700) {
        case 0:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette, 20, w->textSlotCount);
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette4, 20, w->textSlotCount2);
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette4, 20, w->textSlotCount3);
            break;
        case 1:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette4, 20, w->textSlotCount);
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette, 20, w->textSlotCount2);
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette4, 20, w->textSlotCount3);
            break;
        case 2:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette4, 20, w->textSlotCount);
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette4, 20, w->textSlotCount2);
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette, 20, w->textSlotCount3);
            break;
        }
    } else {
        switch (w->unk_700) {
        case 0:
            DrawTextSlots(w->x4, w->y4, w->textSlots, w->palette, 20, w->textSlotCount);
            break;
        case 1:
            DrawTextSlots(w->x5, w->y5, w->textSlots2, w->palette, 20, w->textSlotCount2);
            break;
        case 2:
            DrawTextSlots(w->x6, w->y6, w->textSlots3, w->palette, 20, w->textSlotCount3);
            break;
        }
    }
}

void func_080A8EE4(DeckExchangeWork* w) {
    DrawTextSlots(w->x7, w->y7, w->textSlots5, w->palette, 20, w->textSlotCount5);
}
void deckexchange_2(DeckExchangeWork* w) {
    if (w->unk_70D == 0) {
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 30, w->gfx, w->tiles, w->palette, 0, w->unk_6CE, 3);
    }
    DrawSprite(w->x >> 8, w->y >> 8, gUnk_09EEB000, w->tiles3, w->palette, 0, 0x800, 10);
    switch (w->unk_6F0) {
    case 0:
        if (w->unk_714 != 0) {
            DrawSprite((w->x3 >> 8) - 16, (w->y3 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
        }
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
    case 1:
    case 2:
    case 3:
        func_080A8C58(w, 0);
        break;
    case 4:
        func_080A8C58(w, 1);
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
        if (w->tiles4 != 0) {
            if (w->unk_70D == 0) {
                DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
            }
            DrawSprite(24, 82, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(24, 82, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    case 7:
        func_080A8C58(w, 1);
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
        if (w->tiles4 != 0) {
            DrawSprite(164, 82, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(164, 82, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            if (w->tiles6 != 0) {
                DrawSprite(164, 82, w->gfx5, w->tiles6, w->palette2, 0, 0, 19);
            }
            DrawTextSlots(100, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    case 5:
        DrawSprite((w->x2 >> 8) - 26, (w->y2 >> 8) - 13, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
        func_080A8C58(w, 1);
        if (w->tiles4 != 0) {
            DrawSprite(24, 82, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(24, 82, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    case 6:
        func_080A8C58(w, 1);
        if (w->tiles4 != 0) {
            DrawSprite(24, 82, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(24, 82, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            DrawTextSlots(10, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    case 8:
        func_080A8C58(w, 1);
        if (w->tiles4 != 0) {
            DrawSprite(164, 82, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(164, 82, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            if (w->tiles6 != 0) {
                DrawSprite(164, 82, w->gfx5, w->tiles6, w->palette2, 0, 0, 19);
            }
            DrawTextSlots(100, 116, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    case 9:
        DrawSprite((w->x2 >> 8) - 16, (w->y2 >> 8) - 20, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
        func_080A8EE4(w);
        if (w->tiles4 != 0) {
            DrawSprite(24, 66, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(24, 66, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    case 11:
        DrawSprite((w->x2 >> 8) - 26, (w->y2 >> 8) - 13, w->gfx2, w->tiles2, w->palette4, 0, 0, 8);
        func_080A8EE4(w);
        if (w->tiles4 != 0) {
            DrawSprite(24, 66, w->gfx3, w->tiles4, w->palette2, 0, 0, 20);
            DrawSprite(24, 66, w->gfx4, w->tiles5, w->palette3, 0, 0, 21);
            DrawTextSlots(10, 100, w->textSlots4, w->palette4, 20, w->textSlotCount4);
        }
        break;
    }
    TaskPoolDraw(&w->tasks);
    TaskPoolDraw(&w->tasks2);
}
void deckexchange_3(DeckExchangeWork* w) {
    ObjPalette** p;

    if (w->tiles8 != 0) {
        ReleaseObjTiles(w->tiles8);
    }

    if (w->palette5 != 0) {
        ReleaseObjPalette(w->palette5);
    }

    if (w->tiles9 != 0) {
        ReleaseObjTiles(w->tiles9);
    }

    if (w->palette6 != 0) {
        ReleaseObjPalette(w->palette6);
    }

    if (w->palette7 != 0) {
        ReleaseObjPalette(w->palette7);
    }

    p = &w->palette4;

    if (*p != 0) {
        ReleaseObjPalette(*p);
    }

    func_080AA634(w);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjPalette(w->palette);
    FreeTextSlots(w->textSlots, 8);
    FreeTextSlots(w->textSlots2, 8);
    FreeTextSlots(w->textSlots3, 8);
    FreeTextSlots(w->textSlots4, 30);
    FreeTextSlots(w->textSlots5, 90);
    ReleaseObjPalette(*p);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
    func_080AAA38(w);
    *w->unk_6FC = 6;
}
void func_080A968C(DeckExchangeWork* w, u8 kind) {
    DeckCard2Args args;
    u16* cards;
    u8 i;
    s8 x;
    s8 y;

    cards = GetDeck(w->unk_700)->cards;
    x = 0;
    y = 0;
    for (i = 0; i < DECK_SIZE; i++) {
        if (cards[i] != 0xFFFF) {
            if (kind == 0) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.unk_0A = 0;
                args.slot = &cards[i];
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            } else if (gCardDefs[gCardCollection[cards[i]] & CARD_ID_MASK].unk_2A == kind - 1) {
                args.pool = &w->pool;
                args.cardId = gCardCollection[cards[i]] & 0x8FFF;
                args.col = x;
                args.row = y;
                args.unk_0A = 0;
                args.slot = &cards[i];
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
            if (x > 2) {
                x = 0;
                y++;
            }
        }
    }
    w->x = 0x4800;
    w->y = 0x2800;
    w->unk_6EC = 4;
    func_080AAEEC(w, y * 3 + x);
}

s32 func_080A97D4(DeckExchangeWork* w, u8 kind) {
    DeckCard2Args args;
    u16 i;
    s8 x;
    s8 y;

    x = 0;
    y = 0;

    for (i = 0; i < w->unk_6E0; i++) {
        if (kind == 5) {
            if (w->unk_4CC[i].unk_14 <= 77) {
                args.pool = &w->pool;
                args.cardId = func_080A993C(w->unk_4CC[i].unk_14);
                args.col = x;
                args.row = y;
                args.unk_0A = 1;
                args.slot = 0;
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
        } else {
            args.pool = &w->pool;
            args.cardId = func_080A993C(w->unk_4CC[i].unk_14);

            if (gCardDefs[args.cardId].unk_2A == kind - 1 && w->unk_4CC[i].unk_14 <= 77) {
                args.col = x;
                args.row = y;
                args.unk_0A = 1;
                args.slot = 0;
                TaskCreate(&w->tasks, &gTaskDescDeckCard2, &args);
                x++;
            }
        }

        if (x > 2) {
            x = 0;
            y++;
        }
    }

    w->x = 0xA000;
    w->y = 0x2800;
    w->unk_6EC = 4;
    func_080AAEEC(w, y * 3 + x);
}

s32 func_080A993C(s32 a) {
    u32 i;

    for (i = 0; i < 950; i++) {
        if (gCardDefs[i].unk_1C == a) {
            return i;
        }
    }
}

void func_080A9968(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        node->unk_4A = 1;
        node = ListPoolNext(&node->node);
    }

    TaskPoolUpdate(&w->tasks);
}

void func_080A99A0(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if (w->unk_6EC == 33) {
        return;
    }

    while (node != 0) {
        node->args.row--;

        if (node->args.row < 0) {
            node->y = 0x20000;
            func_08090170(node);
        }

        node = ListPoolNext(&node->node);
    }

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    w->unk_6EC++;
    w->y += 0x300;

    if (w->y > 0x7C00) {
        w->y = 0x7C00;
    }

    if (w->unk_714 != 0) {
        w->unk_6C2--;
    }
}

u8 func_080A9A38(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    if (node == 0) {
        w->y -= 0x300;

        if (w->y < 0x2800) {
            w->y = 0x2800;
            return 0;
        }

        return 1;
    }

    if (node->args.row == 0) {
        return 0;
    }

    do {
        node->args.row++;

        if (node->args.row > 3) {
            node->y = 0x20000;
            func_08090170(node);
        }

        node = ListPoolNext(&node->node);
    } while (node != 0);

    m4aSongNumStart(SONG_SYS_CLICKI04B);
    w->unk_6EC--;
    w->y -= 0x300;

    if (w->y < 0x2800) {
        w->y = 0x2800;
    }

    return 1;
}

void func_080A9AE8(DeckExchangeWork* w) {
    u16 t;

    switch (w->unk_6F0) {
    case 0:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        AnimStart(&w->anim, 0, 1);
        w->unk_6CE &= ~1;
        break;
    case 1:
    case 3:
        AnimStart(&w->anim, 2, 1);
        t = w->unk_6CE | 1;
        w->unk_6CE = t;
        break;
    }
}

void func_080A9B84(DeckExchangeWork* w, u8 b) {
    u16* pal;

    switch (b) {
    case 0:
        pal = (u16*)0x05000100;
        LoadPalette(gUnk_096142F8, pal, 32);
        pal = (u16*)0x05000120;
        LoadPalette(gUnk_09614118 + 0x120, pal, 32);
        pal = (u16*)0x05000140;
        LoadPalette(gUnk_09614118 + 0x140, pal, 32);
        LoadBgMap(0, gUnk_09519AB8 + 0x180, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, (u16)-76, (u16)-14);
        SetBgScroll(1, (u16)-88, (u16)-64);
        SetBgScroll(2, (u16)-88, (u16)-112);
        w->x4 = 100;
        w->y4 = 25;
        w->x5 = 102;
        w->y5 = 75;
        w->x6 = 102;
        w->y6 = 122;
        break;
    case 1:
        pal = (u16*)0x05000120;
        LoadPalette(gUnk_096142F8, pal, 32);
        pal = (u16*)0x05000100;
        LoadPalette(gUnk_09614118 + 0x100, pal, 32);
        pal = (u16*)0x05000140;
        LoadPalette(gUnk_09614118 + 0x140, pal, 32);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8 + 0x180, 0x180);
        LoadBgMap(2, gUnk_0951AAB8, 0x180);
        SetBgScroll(0, (u16)-88, (u16)-16);
        SetBgScroll(1, (u16)-76, (u16)-62);
        SetBgScroll(2, (u16)-88, (u16)-112);
        w->x4 = 102;
        w->y4 = 27;
        w->x5 = 100;
        w->y5 = 73;
        w->x6 = 102;
        w->y6 = 122;
        break;
    case 2:
        pal = (u16*)0x05000140;
        LoadPalette(gUnk_096142F8, pal, 32);
        pal = (u16*)0x05000100;
        LoadPalette(gUnk_09614118 + 0x100, pal, 32);
        pal = (u16*)0x05000120;
        LoadPalette(gUnk_09614118 + 0x120, pal, 32);
        LoadBgMap(0, gUnk_09519AB8, 0x180);
        LoadBgMap(1, gUnk_0951A2B8, 0x180);
        LoadBgMap(2, gUnk_0951AAB8 + 0x180, 0x180);
        SetBgScroll(0, (u16)-88, (u16)-16);
        SetBgScroll(1, (u16)-88, (u16)-64);
        SetBgScroll(2, (u16)-76, (u16)-110);
        w->x4 = 102;
        w->y4 = 27;
        w->x5 = 102;
        w->y5 = 75;
        w->x6 = 100;
        w->y6 = 121;
        break;
    }
}

void func_080A9E40(u8 deck) {
    u8 d[2];
    u8 e[2];
    u32 base;
    u16 n;

    base = 0;
    n = GetDeckCardCount(deck);
    d[0] = n / 10;
    d[1] = n - (u16)(n / 10) * 10;
    e[0] = 9;
    e[1] = 9;

    switch (deck) {
    case 0:
        base = GetBgCharBase(0);
        break;
    case 1:
        base = GetBgCharBase(1);
        break;
    case 2:
        base = GetBgCharBase(2);
        break;
    }

    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], (u8*)base + 0x20, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], (u8*)base + 0x40, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], (u8*)base + 0x60, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], (u8*)base + 0x80, 32);
}

void func_080A9F08(u8 mode) {
    u32 bg0;
    u32 bg1;
    u32 bg2;

    bg0 = GetBgCharBase(0);
    bg1 = GetBgCharBase(1);
    bg2 = GetBgCharBase(2);

    switch (mode) {
    case 0:
        RequestDma3Copy(gUnk_0940FC58, (u8*)bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_0940FC58 + 0x400, (u8*)bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_0940FC58 + 0x400, (u8*)bg2 + 0x1A0, 0x1E0);
        break;
    case 1:
        RequestDma3Copy(gUnk_09410058, (u8*)bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058 - 0x400, (u8*)bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058, (u8*)bg2 + 0x1A0, 0x1E0);
        break;
    case 2:
        RequestDma3Copy(gUnk_09410058, (u8*)bg0 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058, (u8*)bg1 + 0x1A0, 0x1E0);
        RequestDma3Copy(gUnk_09410058 - 0x400, (u8*)bg2 + 0x1A0, 0x1E0);
        break;
    }
}
void func_080A9FF4(u8 kind) {
    u8 d[3];
    u8 e[3];
    u32 base;
    u16 n;
    u8* p;
    u8* ep;

    base = 0;
    n = GetDeckCpCost(kind);
    d[0] = n / 100;
    d[1] = n / 10 - d[0] * 10;
    d[2] = n - d[0] * 100 - d[1] * 10;
    ep = e;
    p = (u8*)&gGameState;
    ep[0] = *(s16*)(p + 0xFA) / 100;
    ep[1] = *(s16*)(p + 0xFA) / 10 - ep[0] * 10;
    ep[2] = *(s16*)(p + 0xFA) - ep[0] * 100 - ep[1] * 10;

    switch (kind) {
    case 0:
        base = GetBgCharBase(0);
        break;
    case 1:
        base = GetBgCharBase(1);
        break;
    case 2:
        base = GetBgCharBase(2);
        break;
    }

    RequestDma3Copy(&gUnk_0940F938[(d[0] + 1) * 32], (u8*)base + 0xA0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[1] + 1) * 32], (u8*)base + 0xC0, 32);
    RequestDma3Copy(&gUnk_0940F938[(d[2] + 1) * 32], (u8*)base + 0xE0, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[0] + 1) * 32], (u8*)base + 0x100, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[1] + 1) * 32], (u8*)base + 0x120, 32);
    RequestDma3Copy(&gUnk_0940F938[(e[2] + 1) * 32], (u8*)base + 0x140, 32);
}

void func_080AA148(u8 kind, u8 slot) {
    u8* dst;

    dst = (u8*)GetBgScreenBase(3) + 0xA8;

    switch (kind) {
    case 5:
        RequestDma3Copy(gUnk_095152B8 + slot * 256, dst, 20);
        RequestDma3Copy(gUnk_095152B8 + 0x40 + slot * 256, dst + 0x40, 20);
        break;
    case 4:
        RequestDma3Copy(gUnk_095152CC + slot * 256, dst, 20);
        RequestDma3Copy(gUnk_095152CC + 0x40 + slot * 256, dst + 0x40, 20);
        break;
    case 3:
        RequestDma3Copy(gUnk_095152E0 + slot * 256, dst, 20);
        RequestDma3Copy(gUnk_095152E0 + 0x40 + slot * 256, dst + 0x40, 20);
        break;
    case 2:
        RequestDma3Copy(gUnk_09515338 + slot * 256, dst, 20);
        RequestDma3Copy(gUnk_09515338 + 0x40 + slot * 256, dst + 0x40, 20);
        break;
    case 1:
        RequestDma3Copy(gUnk_0951534C + slot * 256, dst, 20);
        RequestDma3Copy(gUnk_0951534C + 0x40 + slot * 256, dst + 0x40, 20);
        break;
    }
}

void func_080AA1F8(void) {
    u8 d1[3];
    u8 d2[3];
    u16 a;
    u16 b;

    u32 base;

    a = CountCardsInDecks();
    b = CountCollectionCards();

    d1[0] = a / 100;
    d1[1] = a / 10 - d1[0] * 10;
    d1[2] = a - d1[0] * 100 - d1[1] * 10;
    d2[0] = b / 100;
    d2[1] = b / 10 - d2[0] * 10;
    d2[2] = b - d2[0] * 100 - d2[1] * 10;
    base = GetBgCharBase(3);
    RequestDma3Copy(&gUnk_0940F938[(d1[0] + 1) * 32], (void*)(base + 0x2A0), 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[1] + 1) * 32], (void*)(base + 0x2C0), 32);
    RequestDma3Copy(&gUnk_0940F938[(d1[2] + 1) * 32], (void*)(base + 0x2E0), 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[0] + 1) * 32], (void*)(base + 0x300), 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[1] + 1) * 32], (void*)(base + 0x320), 32);
    RequestDma3Copy(&gUnk_0940F938[(d2[2] + 1) * 32], (void*)(base + 0x340), 32);
}

void func_080AA328(DeckExchangeWork* w) {
    InitTextSlots(w->textSlots, 8);
    InitTextSlots(w->textSlots2, 8);
    InitTextSlots(w->textSlots3, 8);
    w->textSlotCount = LoadTextSlots(GetDeckName(0), w->textSlots);
    w->textSlotCount2 = LoadTextSlots(GetDeckName(1), w->textSlots2);
    w->textSlotCount3 = LoadTextSlots(GetDeckName(2), w->textSlots3);
}

void func_080AA3A0(DeckExchangeWork* w, s32 id) {
    CardDef* def;

    def = &gCardDefs[id];
    w->textSlotCount4 = LoadTextSlots(def->name, w->textSlots4);

    switch (def->unk_2A) {
    case 0:
        LoadPalette(gUnk_09614458, (void*)(w->palette4->index * 32 + 0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    case 1:
        LoadPalette(gUnk_09614478, (void*)(w->palette4->index * 32 + 0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    case 2:
        LoadPalette(gUnk_09614498, (void*)(w->palette4->index * 32 + 0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    case 3:
        LoadPalette(gUnk_096144B8, (void*)(w->palette4->index * 32 + 0x05000200),
                    (u16)(w->palette4->count << 5));
        break;
    }
}

void func_080AA450(DeckExchangeWork* w) {
    DeckCard2Work* node;
    CardDef* def;
    s32 id;
    u8 i;
    u8 j;
    void* dst;

    id = 0xFFFF;
    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        if (node->args.row == w->unk_6D2 && node->args.col == w->unk_6D0) {
            id = node->args.cardId;
            break;
        }

        node = ListPoolNext(&node->node);
    }

    func_080AA634(w);

    if (id != 0xFFFF) {
        def = &gCardDefs[id & CARD_ID_MASK];
        w->tiles4 = LoadObjTiles(gUnk_08F709B0[def->unk_2A].tiles, 0x300);
        w->tiles5 = LoadObjTiles(def->tiles, 0x200);
        w->palette3 = LoadObjPalette(def->palette, 32);
        w->palette2 = LoadObjPalette(gCard00Palette, 32);
        w->gfx3 = gUnk_08F709B0[def->unk_2A].gfx;
        w->gfx4 = def->gfx;

        for (i = 0; i < w->unk_6E0; i++) {
            if (w->unk_4CC[i].unk_14 == def->unk_1C) {
                break;
            }
        }

        w->unk_6CC = i;
        dst = gUnk_05000160;
        LoadPalette(&gUnk_09614118[def->unk_2A * 32 + 0x200], dst, 32);

        for (j = 0; j < 10; j++) {
            func_0808DD20(w->unk_4CC[i].unk_00[j], j);
        }

        func_080AA3A0(w, id);
        func_080AAEB0(w, id);

        if (def->unk_1C > 46) {
            LoadBgMap(2, gUnk_09518AB8, 0x800);
            func_080AA6D4(0);
        } else {
            LoadBgMap(2, gUnk_095182B8, 0x800);
            func_080AA6D4(0);
        }
    } else {
        for (j = 0; j < 10; j++) {
            func_0808DD20(0, j);
        }

        func_080AA6D4(0);
    }
}

void func_080AA634(DeckExchangeWork* w) {
    if (w->tiles7 != 0) {
        ReleaseObjTiles(w->tiles7);
        w->tiles7 = 0;
    }

    if (w->tiles4 != 0) {
        ReleaseObjTiles(w->tiles4);
        ReleaseObjPalette(w->palette2);
        ReleaseObjTiles(w->tiles5);
        ReleaseObjPalette(w->palette3);

        if (w->tiles6 != 0) {
            ReleaseObjTiles(w->tiles6);
            w->tiles6 = 0;
        }

        w->tiles4 = 0;
        w->palette2 = 0;
        w->tiles5 = 0;
        w->palette3 = 0;
    }
}

void func_080AA680(DeckExchangeWork* w) {
    func_080AA6D4(GetCardCpCost(
        func_080A993C(w->unk_4CC[w->unk_6CC].unk_14) +
        w->unk_6D0 * 5 + (u16)w->unk_6D2));
}

void func_080AA6D4(u8 a) {
    u8 d[2];
    u32 base;

    base = GetBgCharBase(3);

    if (a != 0) {
        d[0] = a / 10;
        d[1] = a - d[0] * 10;
        RequestDma3Copy(&gUnk_0940FA98[(d[0] + 3) * 32], (void*)(base + 0xCE0), 32);
        RequestDma3Copy(&gUnk_0940FA98[(d[1] + 3) * 32], (void*)(base + 0xD00), 32);
    } else {
        RequestDma3Copy(gUnk_0940FAD8, (void*)(base + 0xCE0), 32);
        RequestDma3Copy(gUnk_0940FAD8, (void*)(base + 0xD00), 32);
    }
}

u32 func_080AA764(u16* data) {
    u32 sum;
    u16* p;
    s32 i;

    sum = 0;
    p = data;
    i = 9;

    do {
        sum += *p++;
    } while (--i >= 0);

    return sum;
}

s32 func_080AA77C(DeckExchangeWork* w, u16 key) {
    u8* tbl;
    u8 idx;
    u8 r0;
    u8 c0;
    u16 row0;
    s32 sum;
    s32 i;
    s8 d;
    s8 n;
    s32 ofs;
    s32 k;
    u8* p;

    idx = w->unk_6D0 * 5 + (u8)w->unk_6D2;
    tbl = (u8*)&w->unk_4CC[w->unk_6CC];
    row0 = w->unk_6D0;
    r0 = w->unk_6D0;
    c0 = w->unk_6D2;

    if (*(u16*)&tbl[idx << 1] != 0) {
        return 1;
    }

    switch (key) {
    case 0x40:
        do {
            if (w->unk_6D2 > 0) {
                w->unk_6D2 = w->unk_6D2 - 1;
            } else {
                w->unk_6D2 = 4;
            }

            idx = w->unk_6D0 * 5 + (u8)w->unk_6D2;

            if (w->unk_6D0 == r0 && w->unk_6D2 == c0) {
                return 0;
            }
        } while (*(u16*)&tbl[idx << 1] == 0);
        break;
    case 0x80:
        do {
            if (w->unk_6D2 <= 3) {
                w->unk_6D2 = w->unk_6D2 + 1;
            } else {
                w->unk_6D2 = 0;
            }

            idx = w->unk_6D0 * 5 + (u8)w->unk_6D2;

            if (w->unk_6D0 == r0 && w->unk_6D2 == c0) {
                return 0;
            }
        } while (*(u16*)&tbl[idx << 1] == 0);
        break;
    case 0x20:
        if (*(u16*)&tbl[w->unk_6D2 << 1] != 0) {
            if ((s16)row0 > 0) {
                w->unk_6D0 = row0 - 1;
            }

            return 1;
        }

        sum = 0;

        for (i = 0; i < 5; i++) {
            sum += *(u16*)&tbl[i * 2];
        }

        if (sum == 0) {
            w->unk_6D0 = 1;
            return 0;
        }

        p = (u8*)&w->unk_6D2;
        d = -1;
        k = *p + d;

        for (;;) {
            n = k;

            if (n < 0) {
                n = 0;
            }

            if (n > 4) {
                n = 4;
            }

            ofs = n;

            if (*(u16*)&tbl[ofs *= 2] != 0) {
                break;
            }

            if (d < 0) {
                d = -d;
            } else {
                d++;
                d = -d;
            }

            k = *p + d;
        }

        w->unk_6D2 = n;
        break;
    case 0x10:
        if (*(u16*)&tbl[(w->unk_6D2 + 5) << 1] != 0) {
            if ((s16)row0 <= 0) {
                w->unk_6D0 = row0 + 1;
            }

            return 1;
        }

        sum = 0;

        for (i = 5; i < 10; i++) {
            sum += *(u16*)&tbl[i * 2];
        }

        if (sum == 0) {
            w->unk_6D0 = 0;
            return 0;
        }

        p = (u8*)&w->unk_6D2;
        d = -1;
        k = *p + d;

        for (;;) {
            n = k;

            if (n < 0) {
                n = 0;
            }

            if (n > 4) {
                n = 4;
            }

            ofs = n;
            ofs *= 2;

            if (*(u16*)&tbl[ofs += 10] != 0) {
                break;
            }

            if (d < 0) {
                d = -d;
            } else {
                d++;
                d = -d;
            }

            k = *p + d;
        }

        w->unk_6D2 = n;
        break;
    case 0:
        do {
            if (w->unk_6D2 <= 3) {
                w->unk_6D2 = w->unk_6D2 + 1;
            } else {
                w->unk_6D2 = 0;
            }

            idx = w->unk_6D0 * 5 + (u8)w->unk_6D2;

            if (w->unk_6D0 == r0 && w->unk_6D2 == c0) {
                if (w->unk_6D0 <= 0) {
                    w->unk_6D0 = w->unk_6D0 + 1;
                } else {
                    w->unk_6D0 = 0;
                }

                if (func_080AA764((u16*)tbl) == 0) {
                    return 0;
                }
            }
        } while (*(u16*)&tbl[idx << 1] == 0);
        break;
    }

    return 1;
}

void func_080AAA38(DeckExchangeWork* w) {
    u16 i;

    if (w->unk_4CC != 0) {
        for (i = 0; i < w->unk_6E0; i++) {
            EwramFree(w->unk_4CC[i].unk_1C);
        }

        EwramFree(w->unk_4CC);
        w->unk_4CC = 0;
    }
}

void func_080AAA8C(DeckExchangeWork* w, u8 kind) {
    switch (kind) {
    case 0:
        SetObjTileSource(w->tiles2, gUnk_090A4A0C);
        AnimInit(&w->anim2, gUnk_09EEB064, gUnk_09EEB050);
        AnimStart(&w->anim2, 0, 1);
        w->gfx2 = AnimGetGfx(&w->anim2);
        break;
    case 1:
        SetObjTileSource(w->tiles2, gUnk_090A51F6);
        AnimInit(&w->anim2, gUnk_09EEB07C, gUnk_09EEB068);
        AnimStart(&w->anim2, 0, 1);
        w->gfx2 = AnimGetGfx(&w->anim2);
        break;
    }
}

s32 func_080AAB08(DeckExchangeWork* w) {
    u16 idx;
    UnkStruct_08084D78* e;
    u16 i;
    s32 card;
    u16 id;
    CardDef* def;
    u16 kind;

    idx = w->unk_6D0 * 5 + w->unk_6D2;
    e = &w->unk_4CC[w->unk_6CC];
    if (e->unk_00[idx] == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        return 1;
    }
    for (i = 0; i < e->unk_16; i++) {
        card = e->unk_1C[i];
        if (card != 0xFFFF) {
            id = gCardCollection[card] & CARD_ID_MASK;
            def = &gCardDefs[id];
            if (id > 0x1C1) {
                if (idx == 0) {
                    gUnk_0203A9DC = gCardCollection[card] & CARD_ID_MASK;
                    ClearCardCollectionSlot(&gCardCollection[card]);
                    e->unk_1C[i] = 0xFFFF;
                    e->unk_00[0]--;
                    func_0808DD20(e->unk_00[0], 0);
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    return 1;
                }
            } else {
                kind = def->unk_20;
                if (kind == idx) {
                    gUnk_0203A9DC = gCardCollection[card] & CARD_ID_MASK;
                    ClearCardCollectionSlot(&gCardCollection[card]);
                    e->unk_1C[i] = 0xFFFF;
                    e->unk_00[kind]--;
                    func_0808DD20(e->unk_00[kind], kind);
                    m4aSongNumStart(SONG_SYS_KETTEI);
                    return 1;
                }
            }
        }
    }
    m4aSongNumStart(SONG_SYS_BEEP);
    return 1;
}

s32 func_080AAC40(DeckExchangeWork* w) {
    if (GetDeckCpCost(GetActiveDeckIndex()) > gGameState.progression.cp) {
        TaskCreate(&w->tasks2, &gUnk_09EE7FA8, &w->unk_70D);
        m4aSongNumStart(SONG_SYS_BEEP);

        return 0;
    }

    return 1;
}

u8 func_080AAC8C(DeckExchangeWork* w) {
    if (func_080857D4(0) == 0) {
        m4aSongNumStart(SONG_SYS_BEEP);
        TaskCreate(&w->tasks2, &gUnk_09EE7FC0, &w->unk_70D);
        return 0;
    }

    return 1;
}

void func_080AACC8(DeckExchangeWork* w) {
    DeckCard2Work* node;
    s16 x;
    s16 y;

    node = ListPoolFirst(&w->pool);
    x = 0;
    y = 0;

    while (node != 0) {
        node->args.col = x;
        node->args.row = y;
        x++;

        if (x > 2) {
            x = 0;
            y++;
        }

        node = ListPoolNext(&node->node);
    }

    w->y = 0x2800;
    w->unk_6EC = 4;
}

u8 func_080AAD2C(DeckExchangeWork* w) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        if (node->args.col == w->unk_6D0 &&
            node->args.row == w->unk_6D2) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 func_080AAD84(DeckExchangeWork* w, u16 x, u16 y) {
    DeckCard2Work* node;

    node = ListPoolFirst(&w->pool);

    while (node != 0) {
        if (node->args.col == (s16)x && node->args.row == (s16)y) {
            return 1;
        }

        node = ListPoolNext(&node->node);
    }

    return 0;
}

u8 func_080AADD4(DeckExchangeWork* w, s16 x, s16 y, u16 dir) {
    DeckCard2Work* n;

    for (n = ListPoolFirst(&w->pool); n != 0; n = ListPoolNext(&n->node)) {
        if (n->args.col == x && n->args.row == y) {
            return 1;
        }
    }

    switch (dir) {
    case 0x40:
        return func_080AADD4(w, x, y - 1, 0x40);
    case 0x80:
        return func_080AADD4(w, x, y + 1, 0x80);
    case 0x20:
        return func_080AADD4(w, x - 1, y, 0x20);
    case 0x10:
        return func_080AADD4(w, x + 1, y, 0x10);
    }

    return 0;
}

void func_080AAEB0(DeckExchangeWork* w, u16 index) {
    CardDef* d;

    d = &gCardDefs[index];
    w->textSlotCount5 = LoadTextSlots((void*)gUnk_09EE8F48[d->unk_1C], w->textSlots5);
}

void func_080AAEEC(DeckExchangeWork* w, s16 n) {
    w->unk_6EE = n / 3;

    if (n % 3 != 0) {
        w->unk_6EE = n / 3 + 1;
    }
}

void func_080AAF20(DeckExchangeWork* w) {
    s32 t;

    t = 0x5400 / (w->unk_6EE - 4);
    w->y = t * (w->unk_6EC - 4) + 0x2800;

    if (w->y > 0x7C00) {
        w->y = 0x7C00;
    }

    if (w->y < 0x2800) {
        w->y = 0x2800;
    }
}
#endif

#ifndef VERSION_EU
TaskDesc gTaskDescDeckexchange = {
    "deckexchange",
    (TaskInitFunc)deckexchange_0,
    (TaskUpdateFunc)deckexchange_1,
    (TaskFunc)deckexchange_2,
    (TaskFunc)deckexchange_3,
    sizeof(DeckExchangeWork),
};
#endif
