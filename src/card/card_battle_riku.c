#include "macros.h"
#include "card_localized_data.h"
#include "msg_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "map_api.h"
#include "msg_api.h"
#include "card_battle.h"
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
#include "card_message_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_card.h"
#include "sprites_card_pictures.h"
#include "songs.h"

u8 gBossCardRequestValue EWRAM_COMMON(4);

u8 gBossCardRequest EWRAM_COMMON(4);

#include "riku_deck_names.inc"

const Deck gRikuDecks[21] = {
    {
        { 800, 802, 802, 803, 804, 804, 806, 811, 811, 813, 813, 814, 815, 815 },
        RIKU_DECK_NAME_00,
        999, 14, 0,
    },
    {
        {
            680, 681, 682, 682, 683, 683, 684, 684, 685, 686, 687, 688, 690, 691, 692, 692,
            693, 693, 694, 694, 695, 696, 697, 698, 397,
        },
        RIKU_DECK_NAME_01,
        999, 25, 0,
    },
    {
        {
            740, 741, 742, 743, 743, 744, 744, 745, 745, 746, 746, 747, 748, 751, 752, 753,
            753, 754, 754, 755, 755, 746, 746, 757, 758, 759, 430, 434, 551, 459,
        },
        RIKU_DECK_NAME_02,
        999, 30, 0,
    },
    {
        {
            820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 831, 832, 833, 834, 835, 846,
            837, 838, 839, 830, 841, 842, 843, 844, 845, 846, 847, 848, 849, 840, 432, 436,
            465,
        },
        RIKU_DECK_NAME_03,
        999, 33, 0,
    },
    {
        {
            700, 701, 702, 703, 704, 705, 706, 707, 708, 709, 710, 711, 712, 713, 714, 715,
            716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 726, 727, 728, 729, 730, 731,
            732, 733, 734, 735, 736, 737, 738, 739, 555, 507, 492,
        },
        RIKU_DECK_NAME_04,
        999, 43, 0,
    },
    {
        {
            760, 762, 763, 763, 764, 764, 765, 765, 766, 766, 767, 769, 770, 772, 773, 773,
            774, 774, 775, 775, 776, 776, 777, 779, 781, 781, 784, 785, 785, 785, 786, 788,
            788, 435, 436, 450,
        },
        RIKU_DECK_NAME_05,
        999, 36, 0,
    },
    {
        {
            760, 760, 761, 762, 762, 763, 763, 764, 764, 764, 765, 765, 765, 766, 766, 767,
            767, 768, 769, 769, 770, 770, 772, 773, 774, 775, 776, 777, 779, 779, 781, 781,
            784, 784, 785, 785, 785, 786, 786, 788, 788, 434, 435, 436, 450,
        },
        RIKU_DECK_NAME_06,
        999, 45, 0,
    },
    {
        {
            850, 850, 850, 851, 852, 852, 852, 853, 857, 857, 857, 858, 859, 859, 860, 860,
            861, 861, 861, 862, 863, 863, 863, 867, 868, 869, 869, 869, 423, 424, 425, 426,
            430, 431, 438, 439, 462,
        },
        RIKU_DECK_NAME_07,
        999, 37, 0,
    },
    {
        {
            850, 850, 850, 851, 851, 852, 852, 852, 853, 857, 857, 857, 858, 858, 859, 859,
            859, 860, 860, 860, 861, 861, 861, 862, 863, 863, 863, 867, 868, 868, 869, 869,
            869, 422, 423, 424, 425, 426, 437, 430, 431, 438, 439, 435, 560, 462, 510,
        },
        RIKU_DECK_NAME_08,
        999, 47, 0,
    },
    {
        {
            760, 760, 761, 762, 763, 763, 764, 764, 764, 765, 765, 765, 766, 766, 767, 768,
            769, 769, 770, 770, 774, 774, 774, 775, 775, 775, 779, 779, 781, 781, 784, 784,
            784, 785, 785, 785, 788, 788, 791, 792, 792, 793, 794, 795, 796, 797, 797, 798,
            434, 435, 436, 435, 450,
        },
        RIKU_DECK_NAME_09,
        999, 53, 0,
    },
    {
        {
            760, 760, 761, 761, 763, 763, 764, 764, 764, 765, 765, 765, 766, 766, 768, 768,
            769, 769, 770, 770, 771, 771, 772, 773, 773, 774, 774, 774, 775, 775, 775, 776,
            776, 777, 778, 778, 779, 779, 781, 782, 783, 784, 784, 785, 785, 786, 786, 787,
            788, 790, 791, 791, 792, 792, 797, 797, 798, 798, 799, 434, 435, 436, 439, 435,
            557, 450,
        },
        RIKU_DECK_NAME_10,
        999, 66, 0,
    },
    {
        {
            820, 820, 821, 821, 822, 822, 823, 823, 824, 824, 825, 825, 826, 826, 827, 827,
            828, 828, 829, 829, 831, 831, 833, 833, 835, 835, 837, 837, 839, 839, 840, 840,
            841, 841, 842, 842, 843, 843, 844, 844, 845, 845, 846, 846, 847, 847, 848, 848,
            849, 849, 432, 436, 559, 465,
        },
        RIKU_DECK_NAME_11,
        999, 54, 0,
    },
    {
        {
            800, 800, 800, 801, 801, 802, 802, 803, 803, 804, 804, 804, 805, 805, 805, 806,
            806, 806, 807, 807, 808, 808, 808, 809, 809, 809, 810, 810, 810, 811, 811, 811,
            812, 812, 813, 813, 813, 814, 814, 814, 815, 815, 815, 816, 816, 817, 817, 817,
            818, 818, 819, 819, 819, 430, 439, 558, 459,
        },
        RIKU_DECK_NAME_12,
        999, 57, 0,
    },
    {
        {
            870, 870, 871, 872, 873, 874, 874, 875, 875, 876, 876, 877, 877, 877, 878, 878,
            878, 879, 879, 879, 880, 880, 881, 882, 883, 884, 884, 885, 885, 886, 886, 887,
            887, 887, 888, 888, 888, 889, 889, 889, 890, 890, 891, 892, 893, 894, 894, 895,
            895, 896, 896, 897, 897, 897, 898, 898, 898, 899, 899, 899, 439, 439, 561,
        },
        RIKU_DECK_NAME_13,
        999, 63, 0,
    },
    {
        {
            930, 931, 932, 933, 934, 935, 936, 937, 938, 939, 940, 941, 942, 943, 944, 945,
            946, 947, 948, 949, 435,
        },
        RIKU_DECK_NAME_14,
        999, 21, 0,
    },
    {
        {
            850, 850, 850, 851, 851, 852, 857, 858, 858, 859, 859, 859, 860, 860, 860, 861,
            861, 862, 867, 868, 868, 869, 869, 869, 424, 425, 430, 431, 438, 439, 560, 462,
            510,
        },
        RIKU_DECK_NAME_15,
        999, 33, 0,
    },
    {
        {
            760, 760, 761, 762, 762, 763, 763, 764, 764, 764, 765, 765, 765, 766, 766, 767,
            767, 768, 769, 769, 770, 770, 772, 773, 774, 775, 776, 777, 779, 779, 781, 781,
            784, 784, 785, 785, 785, 786, 786, 788, 788, 434, 435, 436, 450,
        },
        RIKU_DECK_NAME_16,
        999, 45, 0,
    },
    {
        {
            900, 900, 901, 901, 902, 902, 903, 903, 904, 904, 905, 905, 906, 906, 907, 907,
            908, 908, 909, 909, 913, 913, 913, 914, 914, 914, 915, 915, 915, 916, 916, 916,
            917, 917, 917, 918, 918, 918, 920, 921, 922, 923, 924, 925, 926, 927, 928, 929,
            563,
        },
        RIKU_DECK_NAME_17,
        999, 49, 0,
    },
    {
        {
            760, 760, 761, 761, 763, 763, 764, 764, 764, 765, 765, 765, 766, 766, 768, 768,
            769, 769, 770, 770, 771, 771, 772, 773, 773, 774, 774, 774, 775, 775, 775, 776,
            776, 777, 778, 778, 779, 779, 781, 782, 783, 784, 784, 785, 785, 786, 786, 787,
            788, 790, 791, 791, 792, 792, 797, 797, 798, 798, 799, 434, 435, 436, 439, 435,
            557, 450,
        },
        RIKU_DECK_NAME_18,
        999, 66, 0,
    },
    {
        {
            930, 930, 930, 930, 930, 931, 931, 931, 931, 932, 932, 932, 932, 933, 933, 933,
            933, 934, 934, 934, 934, 935, 935, 935, 935, 936, 936, 936, 936, 937, 937, 937,
            937, 938, 938, 938, 938, 939, 939, 939, 939, 939, 940, 940, 940, 940, 940, 941,
            941, 941, 941, 942, 942, 942, 942, 943, 943, 943, 943, 944, 944, 944, 944, 945,
            945, 945, 945, 946, 946, 946, 946, 947, 947, 947, 947, 948, 948, 948, 948, 949,
            949, 949, 949, 949, 439, 439, 564,
        },
        RIKU_DECK_NAME_19,
        999, 87, 0,
    },
    {
        { 9, 2, 8, 1, 0, 5, 1, 7, 9 },
        RIKU_DECK_NAME_20,
        999, 9, 0,
    },
};

const s32 gRikuCardSwingAngles[4] = {
    0xE000, 0x2000, 0x6000, 0xA000,
};

const s16 gRikuStockValueX[4] = {
    184, 172, 160, 0,
};

const UnkStruct_080ABA80 gUnk_090352FC = {
    { -1, -1, -1, -1, -1, -1 },
};

u8 IsCardDisplayOffScreen(CardDisplayWork* p);
void ReleaseCardDisplayGfx(CardDisplayWork* p);
void LoadCardDisplayGfx(CardDisplayWork* p);
static u8 cardbattle_1(CardBattleWork* w, void* a);
u8 UpdateRikuReloadDeal(CardBattleWork* w, void* a);
void SelectNextRikuCard(CardBattleWork* w, u8 n);
void SelectPrevRikuCard(CardBattleWork* w, u8 n);
void LoadRikuDeckCardSlots(CardBattleWork* w, CardSlot* slots, s8 kind, s32 n);
u16 FillCardSlotsFromIds(CardSlot* out, u16* ids, u16 n, u8 kind);
Deck* GetLinkPartnerDeck(void);
void func_08081740(CardBattleWork* w, u16 n);
void func_08081744(CardBattleWork* w);
void func_08080228(CardBattleWork* w);
void SwitchRikuCardList(CardBattleWork* w);
void CycleRikuCardList(CardBattleWork* w);
u8 UseRikuCard(CardBattleWork* w);
void BeginRikuReloadDeal(CardBattleWork* w);
u8 StockRikuCard(CardBattleWork* w);
void UseRikuStock(CardBattleWork* w);
u8 UseRikuHeartlessCard(CardBattleWork* w);
void TickRikuHcEffectOnCardUse(void);
void ResetRikuReloadGauge(CardBattleWork* w);
void LoadRikuCardDisplayGfx2(CardDisplayWork* p);
void TickRikuHcEffectOnPlayEnd(void);
u8 func_080827E0(CardDisplayWork* p, void* a);
void UpdateRikuReloadGauge(CardDisplayWork* p);
void LookupRikuCardDef(CardDisplayArgs* a, CardDef** out, u8 index);
void TickRikuHcEffectOnAttackEnd(void);
u8 func_08082AE4(CardDisplayWork* p);
u8 func_08082FF0(CardDisplayWork* p);
void RefreshRikuCardDisplayGfx(CardDisplayWork* p);
s32 func_08083ADC(BossCardWork* w);
void func_08082BF8(CardDisplayWork* p);
u8 AreCardsSettled(CardDisplayWork** p, u8 n);
void ShuffleCardSlots(CardSlot* slots, u8 n);
u16 CountAvailableCardSlots(CardBattleWork* w, u8 n);
u16 CountRemainingAttackCards(CardBattleWork* w, u8 b);
void ClearUsedCardSlots(CardBattleWork* w, u8 b);
void ResetCardSlotsForReload(CardBattleWork* w, u8 n);
u16 GetRandomHcEffect(void);
void ClearStockedCardSlots(CardBattleWork* w);
void IncrementReloadCount(CardBattleWork* w);
void RestoreCardsForPotion(CardBattleWork* w);
void RestoreCardsForHiPotion(CardBattleWork* w);
void RestoreCardsForMegaPotion(CardBattleWork* w);
void RestoreCardsForEther(CardBattleWork* w);
void RestoreCardsForMegaEther(CardBattleWork* w);
void RestoreCardsForElixir(CardBattleWork* w);
u8 AddBreakDarkPoints(void);
void SyncCardDisplayGfx(CardDisplayWork* p);
void LoadCardDisplayGfx(CardDisplayWork* p);
void ReleaseCardDisplayGfx(CardDisplayWork* p);
u8 IsCardDisplayOffScreen(CardDisplayWork* p);

void CreateRikuCardDisplay(CardBattleWork* w, u8 slot) {
    CardDisplayArgs args;
    u16 id;
    CardSlot* card;
    CardDisplayWork* node;
    s16 count;

    count = 0;
    if (w->cursors[slot] != 0xFFFF && (s16)w->slotCounts[slot] > 0) {
        id = w->cursors[slot];
        card = FindNextAvailableSlot(w, slot, &id);
        if (card != 0) {
            args.pool = &w->cardDisplays[slot];
            args.index = id;
            args.listIndex = slot;
            args.slot = card;
            args.reloadCount = w->reloadCounts[slot];
            if (card->cardId == 0xFFFE) {
                gRikuSelectedCard = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                gRikuSelectedCard = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
            }
            count++;
        }
    }

    switch (count) {
    case 0:
        args.pool = &w->cardDisplays[slot];
        args.index = 0xFFFF;
        args.slot = w->slots[slot];
        args.listIndex = slot;
        node = TaskCreate(&w->tasks, &gTaskDescNOCard, &args)->work;
        node->swingAngleTarget = node->swingAngle = gRikuCardSwingAngles[0];
        node->ringIndex = 0;
        node->priority = 50;
        node->flags |= 0x802;
        gRikuSelectedCard = node;
        break;
    case 1:
        gRikuSelectedCard->swingAngleTarget = gRikuSelectedCard->swingAngle = gRikuCardSwingAngles[0];
        gRikuSelectedCard->priority = 50;
        gRikuSelectedCard->flags |= 0x800;
        break;
    }
}

void LoadRikuDeckCardSlots(CardBattleWork* w, CardSlot* slots, s8 kind, s32 n) {
    Deck* deck;
    u32 count;

    switch (gBtlWork->battleId) {
    case 157:
    case 179:
        deck = &gRikuDecks[20];
        n = deck->cardCount;
        break;
    case 158:
        deck = &gRikuDecks[4];
        n = deck->cardCount;
        break;
    case 159:
        deck = &gRikuDecks[1];
        n = deck->cardCount;
        break;
    case 160:
        deck = &gRikuDecks[2];
        n = deck->cardCount;
        break;
    case 161:
        deck = &gRikuDecks[5];
        n = deck->cardCount;
        break;
    case 162:
        deck = &gRikuDecks[0];
        n = deck->cardCount;
        break;
    case 163:
        deck = &gRikuDecks[3];
        n = deck->cardCount;
        break;
    case 164:
        deck = &gRikuDecks[7];
        n = deck->cardCount;
        break;
    case 165:
        deck = &gRikuDecks[13];
        n = deck->cardCount;
        break;
    case 166:
        deck = &gRikuDecks[14];
        n = deck->cardCount;
        break;
    case 177:
        deck = &gRikuDecks[19];
        n = deck->cardCount;
        break;
    case 167:
        deck = &gRikuDecks[17];
        n = deck->cardCount;
        break;
    case 168:
        deck = &gRikuDecks[6];
        n = deck->cardCount;
        break;
    case 169:
        deck = &gRikuDecks[9];
        n = deck->cardCount;
        break;
    case 170:
        deck = &gRikuDecks[10];
        n = deck->cardCount;
        break;
    case 171:
        deck = &gRikuDecks[16];
        n = deck->cardCount;
        break;
    case 172:
        deck = &gRikuDecks[18];
        n = deck->cardCount;
        break;
    case 173:
        deck = &gRikuDecks[12];
        n = deck->cardCount;
        break;
    case 174:
        deck = &gRikuDecks[11];
        n = deck->cardCount;
        break;
    case 175:
        deck = &gRikuDecks[8];
        n = deck->cardCount;
        break;
    case 176:
        deck = &gRikuDecks[15];
        n = deck->cardCount;
        break;
    default:
        deck = GetLinkPartnerDeck();
        n = 99;
        break;
    }

    count = FillCardSlotsFromIds(slots, deck->cards, n, (u8)kind);

    if (gBtlWork->flags & 0x800) {
        ShuffleCardSlots(w->slots[kind], count);
    }

    if (kind == 0) {
        slots[count].unk_06 = 0;
        slots[count].stocked = 0;
        slots[count].removed = 0;
        slots[count].cardId = 0xFFFE;
        slots[count].index = count;
    }
}

u16 FillCardSlotsFromIds(CardSlot* out, u16* ids, u16 n, u8 kind) {
    u16 count = 0;
    s32 i;

    for (i = 0; i < n; i++) {
        if (ids[i] != 0xFFFF) {
            switch (kind) {
            case 0:
                if ((u8)gCardDefs[ids[i] & CARD_ID_MASK].category <= 2) {
                    out[count].unk_06 = kind;
                    out[count].stocked = kind;
                    out[count].removed = kind;
                    out[count].cardId = ids[i];
                    out[count].index = count;
                    count++;
                }
                break;
            case 3:
                if ((u8)gCardDefs[ids[i] & CARD_ID_MASK].category == 3) {
                    out[count].unk_06 = 0;
                    out[count].stocked = 0;
                    out[count].removed = 0;
                    out[count].cardId = ids[i];
                    out[count].index = count;
                    count++;
                }
                break;
            }
        }
    }

    return count;
}

void InitRikuCardList(CardBattleWork* w, s8 idx) {
    u16 n = w->slotCounts[idx];

    if (n != 0) {
        if (idx == 0) {
            CardSlot* slots;
            vu32 zero;
            u8 i;

            slots = EwramAlloc((n + 15) * sizeof(CardSlot));
            w->slots[idx] = slots;
            zero = 0;
            CpuSet((void*)&zero, slots, (n + 15) * (sizeof(CardSlot) / 4) | CPU_SET_SRC_FIXED | CPU_SET_32BIT);

            for (i = 0; i < n; i++) {
                w->slots[idx][i].unk_06 = 0;
                w->slots[idx][i].cardId = 0xFFFF;
                w->slots[idx][i].stocked = 0;
                w->slots[idx][i].removed = 0;
                w->slots[idx][i].used = 0;
                w->slots[idx][i].restoreOnReload = 0;
            }

            for (i = n; i < n + 15; i++) {
                w->slots[idx][i].unk_06 = 1;
                w->slots[idx][i].cardId = 0xFFFF;
                w->slots[idx][i].stocked = 1;
                w->slots[idx][i].removed = 1;
                w->slots[idx][i].used = 1;
                w->slots[idx][i].restoreOnReload = 0;
            }
        } else {
            CardSlot* slots;
            vu32 zero;
            u8 i;

            slots = EwramAlloc(n * sizeof(CardSlot));
            w->slots[idx] = slots;
            zero = 0;
            CpuSet((void*)&zero, slots, n * (sizeof(CardSlot) / 4) | CPU_SET_SRC_FIXED | CPU_SET_32BIT);

            for (i = 0; i < n; i++) {
                w->slots[idx][i].unk_06 = 0;
                w->slots[idx][i].cardId = 0xFFFF;
                w->slots[idx][i].stocked = 0;
                w->slots[idx][i].removed = 0;
                w->slots[idx][i].used = 0;
                w->slots[idx][i].restoreOnReload = 0;
            }
        }

        LoadRikuDeckCardSlots(w, w->slots[idx], idx, (u16)w->slotCounts[idx]);
        w->cursors[idx] = 0;
    } else {
        CardSlot* slot;
        vu32 zero;
        u16* q;
        s32 k;

        slot = EwramAlloc(sizeof(CardSlot));
        w->slots[idx] = slot;
        zero = 0;
        CpuSet((void*)&zero, slot, sizeof(CardSlot) / 4 | CPU_SET_SRC_FIXED | CPU_SET_32BIT);
        w->slots[idx]->cardId = (idx << 12) | 0xFF;
        w->slots[idx]->restoreOnReload = 0;
        q = w->cursors;
        q += idx;
        k = 0xFFFF;
        *q = k;
    }
}

static void cardbattle_0(CardBattleWork* w) {
    s32 zero;
    u8 i;

    zero = 0;
    CpuSet((void*)&zero, w, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardBattleWork) / 4);
    gCardBattleState->rikuWork = w;
    w->tiles = AllocSpriteFrameTiles(0x80);
    w->palette = LoadObjPalette(gBStatesPalette, 32);
    UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8);
    TaskPoolInit(&w->tasks, 30);
    w->stockCount = 0;
    w->listIndex = 0;
    w->reloadPending[0] = 0;
    w->reloadPending[1] = 0;
    w->reloadPending[2] = 0;
    w->reloadPending[3] = 0;
    w->revCountShown[0] = 1;
    w->revCountShown[1] = 0;
    w->revCountShown[2] = 0;
    w->revCountShown[3] = 0;
    w->stockValue = 0;
    w->unk_C4[3] = 0;
    // @bug? Reads past the end of the array.
    w->x = *(u16*)&gRikuCardSwingAngles[4];

    for (i = 0; i <= 2; i++) {
        w->playedCards[i] = 0;
        w->stock[i] = 0;
    }

    for (i = 0; i <= 3; i++) {
        w->selectedCards[i] = 0;
        w->slots[i] = 0;
    }

    w->unk_C4[1] = 0;
    ListPoolInit(&w->cardDisplays[0]);
    ListPoolInit(&w->cardDisplays[1]);
    ListPoolInit(&w->cardDisplays[2]);
    ListPoolInit(&w->cardDisplays[3]);

    switch (gBtlWork->battleId) {
    case 157:
    case 179:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[20]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[20]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 158:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[4]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[4]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 159:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[1]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[1]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 160:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[2]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[2]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 161:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[5]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[5]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 162:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[0]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[0]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 163:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[3]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[3]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 164:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[7]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[7]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 165:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[13]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[13]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 166:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[14]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[14]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 177:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[19]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[19]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 167:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[17]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[17]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 168:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[6]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[6]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 169:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[9]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[9]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 170:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[10]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[10]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 171:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[16]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[16]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 172:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[18]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[18]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 173:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[12]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[12]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 174:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[11]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[11]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 175:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[8]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[8]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    case 176:
        w->slotCounts[0] = w->cardsLeft[0] = CountDeckCards(0, &gRikuDecks[15]) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountDeckCards(1, &gRikuDecks[15]);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    default:
        w->slotCounts[0] = w->cardsLeft[0] = CountLinkPartnerDeckCards(0) + 1;
        w->slotCounts[3] = w->cardsLeft[3] = CountLinkPartnerDeckCards(3);
        InitRikuCardList(w, 0);
        InitRikuCardList(w, 3);
        break;
    }

    w->reloadCounts[0] = 0;
    w->reloadCounts[1] = 0;
    w->reloadCounts[2] = 0;
    w->cursors[0] = 0;
    w->cursors[1] = 0;
    w->cursors[2] = 0;
    w->cursors[3] = 0;
    gRikuSelectedCard = 0;
    CreateRikuCardDisplay(w, w->listIndex);
    gRikuCardRequest = 0;
    gCardBattleState->rikuListIndex = w->listIndex;
}

static u8 cardbattle_1(CardBattleWork* w, void* a) {
    UnkStruct_080ABA80 arr;
    u8 flag[4];
    UnkStruct_080ABA80 arr2;
    u8 buf[6];
    s32 hold;
    ReloadArgs args;
    s32 done;
    u32 kind;
    u32 flags;
    CardDisplayWork* p;
    u16 r;
    u8 i;
    u8 slot;

    if (gBtlWork->phase == 4) {
        if (gRikuBtlWork->flags & 0x1000000) {
            gRikuBtlWork->flags &= ~0x1000000;
        }

        return 0;
    }

    if (w->unk_C4[3] != 0) {
        hold = w->x << 8;
        ApproachValue(&hold, gRikuStockValueX[w->stockCount - 1] << 8, w->unk_C4[3]);
        w->x = hold >> 8;
        w->unk_C4[3]--;
    }

    if (gRikuSelectedCard->flags & 0x1000000) {
        if (gRikuSelectedCard->flags & 0x4000000) {
            if (gRikuBtlWork->hcEffect == 9) {
                gRikuSelectedCard->flags |= 0x4000;
                gRikuSelectedCard->command = 7;

                if (gRikuBtlWork->hcEffect != 25) {
                    IncrementReloadCount(w);

                    if (gRikuBtlWork->hcEffect == 10) {
                        w->reloadCounts[w->listIndex] -= 2;

                        if ((s16)w->reloadCounts[w->listIndex] < 0) {
                            w->reloadCounts[w->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->rikuReloadCounter = w->reloadCounts[w->listIndex];
                gCardBattleState->rikuReloadGauge = 0;
                gCardBattleState->rikuGaugeFullFrame = 4;
                TaskPoolUpdate(&w->tasks);
                ResetCardSlotsForReload(w, 0);
                w->cursors[0] = 0;
                w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
                CreateRikuCardDisplay(w, 0);
                TickRikuHcEffectOnReload();
            } else {
                gRikuSelectedCard->command = 7;

                if (gRikuBtlWork->hcEffect != 25) {
                    IncrementReloadCount(w);

                    if (gRikuBtlWork->hcEffect == 10) {
                        w->reloadCounts[w->listIndex] -= 2;

                        if ((s16)w->reloadCounts[w->listIndex] < 0) {
                            w->reloadCounts[w->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->rikuReloadCounter = w->reloadCounts[w->listIndex];
                gCardBattleState->rikuReloadGauge = 0;
                gCardBattleState->rikuGaugeFullFrame = 4;
                ClearUsedCardSlots(w, 0);
                w->cursors[w->listIndex] = 0;
                w->cardsLeft[w->listIndex] = 0;
                w->reloadPending[w->listIndex] = 1;
                gRikuSelectedCard = 0;
                gRikuCardRequest = 0;
                w->revCountShown[w->listIndex] = 0;
            }
        }
    }

    switch (gRikuCardRequest) {
    case 0:
        break;
    case 1:
        gRikuCardRequest = 0;

        if (gRikuSelectedCard->flags & 0x40) {
            SelectNextRikuCard(w, w->listIndex);
        }
        break;
    case 2:
        gRikuCardRequest = 0;

        if (gRikuSelectedCard->flags & 0x40) {
            SelectPrevRikuCard(w, w->listIndex);
        }
        break;
    case 4:
        gRikuCardRequest = 0;
        p = gRikuSelectedCard;
        flags = p->flags;

        if (!(flags & 0x100000)) {
            if (w->stockCount == 3) {
                UseRikuStock(w);
            } else if (p->cardDef->category == 3) {
#ifndef VERSION_EU
                m4aSongNumStart(SONG_SYS_BEEP);
#endif
            } else if (w->reloadPending[w->listIndex] == 0) {
                if (!(flags & 2)) {
                    if (CanUseRikuSelectedCard() != 0) {
                        if (w->stockCount <= 2 && gCardBattleState->rikuStockActive == 0) {
                            StockRikuCard(w);
                        }
                    } else if (gRikuSelectedCard->flags & 0x20) {
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_BEEP);
#endif
                    }
                } else if (flags & 0x20) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_BEEP);
#endif
                }
            }
        } else if (w->stockCount != 0) {
            UseRikuStock(w);
        } else {
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_BEEP);
#endif
        }
        break;
    case 3:
        gRikuCardRequest = 0;

        if (gRikuSelectedCard->cardDef->category != 3) {
            if (!(gRikuSelectedCard->flags & 0x100000) && w->reloadPending[w->listIndex] == 0) {
                if (!(gRikuSelectedCard->flags & 2)) {
                    if (CanUseRikuSelectedCard() != 0) {
                        UseRikuCard(w);
                    } else if (gRikuSelectedCard->flags & 0x20) {
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_BEEP);
#endif
                    }
                } else if (gRikuSelectedCard->flags & 0x20) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_BEEP);
#endif
                }
            }
        } else if (!(gRikuSelectedCard->flags & 0x100000)) {
            UseRikuHeartlessCard(w);
        }
        break;
    case 5:
        gRikuCardRequest = 0;

        if (w->stockCount != 0) {
            UseRikuStock(w);
        } else if (!(gBtlWork->flags & 0x80)) {
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_BEEP);
#endif
        }
        break;
    case 6:
        gRikuCardRequest = 0;
        OpenRikuCards(w);
        break;
    case 7:
        w->revCountShown[w->listIndex] = 0;
        w->unk_C4[0] = 0;
        CloseRikuCards(w);
        break;
    case 8:
        gRikuCardRequest = 0;
        break;
    case 9:
        gRikuCardRequest = 0;
        CycleRikuCardList(w);
        break;
    case 10:
        gRikuCardRequest = 0;
        SwitchRikuCardList(w);
        break;
    default:
        gRikuCardRequest = 0;
        break;
    }

    switch (gRikuCardReloadRequest) {
    case 17:
        gRikuCardReloadRequest = 0;
        RestoreCardsForPotion(w);

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    case 18:
        gRikuCardReloadRequest = 0;
        RestoreCardsForHiPotion(w);

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    case 19:
        gRikuCardReloadRequest = 0;
        RestoreCardsForMegaPotion(w);
        ResetRikuReloadGauge(w);
        w->reloadCounts[0] = 0;

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    case 21:
        gRikuCardReloadRequest = 0;
        RestoreCardsForEther(w);

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    case 22:
        gRikuCardReloadRequest = 0;
        RestoreCardsForMegaEther(w);
        ResetRikuReloadGauge(w);
        w->reloadCounts[0] = 0;

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    case 23:
        gRikuCardReloadRequest = 0;
        RestoreCardsForElixir(w);

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    case 24:
        gRikuCardReloadRequest = 0;
        RestoreCardsForElixir(w);
        ResetRikuReloadGauge(w);
        w->reloadCounts[0] = 0;

        if (w->listIndex == 0) {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
        } else {
            if (gRikuSelectedCard->flags & 0x1000000) {
                gRikuSelectedCard->flags |= 0x4000;
            }

            gRikuSelectedCard->command = 7;
            w->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        ClearUsedCardSlots(w, 0);
        w->cursors[0] = 0;
        w->cardsLeft[0] = CountAvailableCardSlots(w, 0);
        CreateRikuCardDisplay(w, 0);
        TickRikuHcEffectOnReload();
        break;
    }

    if (w->reloadPending[w->listIndex] != 0) {
        if (gRikuSelectedCard != 0) {
            if (gRikuSelectedCard->flags & 0x4000000) {
                gRikuSelectedCard->flags |= 0x4000;
                BeginRikuReloadDeal(w);
                w->reloadPending[w->listIndex] = 0;
                w->unk_C4[0] = 1;
                gRikuBtlWork->flags |= 0x80000000;
                SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuReloadDeal);
                gRikuSelectedCard->flags = (gRikuSelectedCard->flags | 0x834) & ~0x1000;
                TaskPoolUpdate(&w->tasks);
#ifndef VERSION_EU
                m4aSongNumStart(SONG_SYS_RELOAD);
#endif
                slot = w->listIndex;
                args.slot = slot;
                args.state = &w->unk_C4[0];
                args.mode = 2;
                TaskCreate(&w->tasks, &gTaskDescRELOAD, &args);
                return 1;
            }
        } else {
            BeginRikuReloadDeal(w);
            w->reloadPending[w->listIndex] = 0;
            gRikuBtlWork->flags |= 0x80000000;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateRikuReloadDeal);
            gRikuSelectedCard->flags = (gRikuSelectedCard->flags | 0x834) & ~0x1000;
            TaskPoolUpdate(&w->tasks);
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_RELOAD);
#endif
            return 1;
        }
    } else if (gRikuSelectedCard != 0 && (gRikuSelectedCard->flags & 0x42) == 0x42 &&
               CountAvailableCardSlots(w, w->listIndex) != 0) {
        w->reloadPending[w->listIndex] = 1;
        w->cardsLeft[0] = 0;
        gRikuSelectedCard->command = 7;

        if (gRikuBtlWork->hcEffect != 40) {
            if (gRikuBtlWork->actor->hp > 3) {
                gRikuBtlWork->actor->hp -= 2;
            }

            w->selectedCards[w->listIndex] = 0;
            gRikuSelectedCard = 0;

            if (gRikuBtlWork->hcEffect != 25) {
                IncrementReloadCount(w);

                if (gRikuBtlWork->hcEffect == 10) {
                    w->reloadCounts[w->listIndex] -= 2;

                    if ((s16)w->reloadCounts[w->listIndex] < 0) {
                        w->reloadCounts[w->listIndex] = 0;
                    }
                }
            }

#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

            if (FadeGetAmount() == 0) {
                FadeFromAmount(2, 16, 20);
            }
        } else {
            w->selectedCards[w->listIndex] = 0;
            gRikuSelectedCard = 0;
            w->reloadPending[w->listIndex] = 1;
            w->cardsLeft[0] = 0;
        }
    }

    if (w->unk_C4[1] == 0 && (u8)AreCardsSettled(w->stock, w->stockCount) != 0) {
        arr = gUnk_090352FC;

        if (!(gBtlWork->flags & 0x4000)) {
            r = LookupStockName(w->stock, w->stockCount, w->stockValue, &arr, flag);
        } else {
            r = LookupLinkStockName(w->stock, w->stockCount, w->stockValue, &arr, flag, 1);
        }

        gCardBattleState->rikuStockName = r;

        if (r <= 105) {
            for (i = 0; i < w->stockCount; i++) {
                w->stock[i]->flags |= 0x10000000;
            }

            if (gCardBattleState->rikuStockNameShown == 0) {
                TaskCreate(&w->tasks, &gTaskDescStockNameRiku, 0);
                gCardBattleState->rikuStockNameShown = 1;
            }
        } else {
            if (w->stockCount == 3) {
                arr2 = gUnk_090352FC;
                memset(buf, 0, 6);
                done = 0;

                for (i = 0; i < w->stockCount; i++) {
                    arr2.unk_00[i] = w->stock[i]->cardDef->unk_28;
                }

                kind = LookupStockPairName(&arr2, buf, w->stockCount);

                switch (kind) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 11:
                case 15:
                case 17:
                case 19:
                case 21:
                case 23:
                case 25:
                case 27:
                case 29:
                case 31:
                case 33:
                case 35:
                case 37:
                case 39:
                case 41:
                case 43:
                case 44:
                    gCardBattleState->rikuStockName = kind;
                    done = 1;
                    break;
                }

                if (done == 0) {
                    for (i = 0; i < w->stockCount; i++) {
                        w->stock[i]->flags &= ~0x10000000;
                    }

                    if (gCardBattleState->rikuStockNameShown != 0) {
                        gCardBattleState->rikuStockNameShown = 0;
                    }
                } else {
                    for (i = 0; i < w->stockCount; i++) {
                        w->stock[i]->flags |= 0x10000000;
                    }

                    if (gCardBattleState->rikuStockNameShown == 0) {
                        TaskCreate(&w->tasks, &gTaskDescStockNameRiku, 0);
                        gCardBattleState->rikuStockNameShown = 1;
                    }
                }
            }
        }

        w->unk_C4[1] = 1;
    }

    gCardBattleState->rikuCardsLeft = w->cardsLeft[w->listIndex];
    TaskPoolUpdate(&w->tasks);
    gCardBattleState->rikuStockCount = w->stockCount;
    return 1;
}

static void cardbattle_2(CardBattleWork* w) {
    if (gCardBattleState->cardsOpen != 0 && gRikuBtlWork->hcEffect != 28 && w->stockCount != 0 && w->stockValue != 0) {
        DrawSprite(w->x, 4, gUnk_09EF12E8[0], w->tiles, w->palette, 0, 16, 12);
    }

    TaskPoolDraw(&w->tasks);
}

static void cardbattle_3(CardBattleWork* w) {
    u8 i;

    TaskPoolDestroy(&w->tasks);

    for (i = 0; i <= 3; i++) {
        if (w->slots[i] != 0) {
            EwramFree(w->slots[i]);
        }
    }

    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void CloseRikuCards(CardBattleWork* w) {
    u8 i;

    for (i = 0; i < w->stockCount; i++) {
        w->stock[i]->flags &= ~0x20;
    }

    if (gRikuSelectedCard != 0) {
        gRikuSelectedCard->flags &= ~0x20;
    }

    gCardBattleState->soraHcEffect = 0;
    gBtlWork->flags |= 0x20;
    gCardBattleState->cardsOpen = 0;
    gCardBattleState->rikuStockNameShown = 0;
    w->cardsClosed = 1;
}

void OpenRikuCards(CardBattleWork* w) {
    u8 i;

    for (i = 0; i < w->stockCount; i++) {
        w->stock[i]->flags |= 0x20;
    }

    if (gRikuSelectedCard != 0) {
        gRikuSelectedCard->flags |= 0x20;
    }

    gBtlWork->flags &= ~0x20;
    gCardBattleState->cardsOpen = 1;
    w->cardsClosed = 0;
}

u8 UpdateRikuReloadDeal(CardBattleWork* w, void* a) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;

    if (gBtlWork->phase == 4) {
        if (gRikuBtlWork->flags & 0x1000000) {
            gRikuBtlWork->flags &= ~0x1000000;
        }

        m4aSongNumStop(SONG_SYS_RELOAD);
        return 0;
    }

    if ((s16)gRikuSelectedCard->timer == 0) {
        if (CountAvailableCardSlots(w, w->listIndex) > w->unk_C4[2]) {
            gRikuSelectedCard->flags &= ~4;
            v = gRikuSelectedCard->args.index - 1;
            c = FindPrevAvailableSlot(w, w->listIndex, &v);

            if (c != 0) {
                args.pool = &w->cardDisplays[w->listIndex];
                args.index = v;
                args.listIndex = w->listIndex;
                args.slot = c;
                p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
                p->unk_80 = p->unk_7C = 0;
                p->priority = 50;
                p->timer = 8;
                p->x = p->unk_8C;
                p->y = p->unk_90;
                p->flags |= 0x814;
                gRikuSelectedCard = p;
                w->unk_C4[2]++;
                w->cardsLeft[w->listIndex]++;
            }
        } else {
            gRikuBtlWork->flags &= ~0x80000000LL;
            gRikuBtlWork->flags &= ~0x100;
            w->unk_C4[0] = 0;
            m4aSongNumStop(SONG_SYS_RELOAD);
            gRikuCardRequest = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)cardbattle_1);
        }
    }

    if (gRikuCardRequest == 7) {
        w->revCountShown[w->listIndex] = 0;
        w->unk_C4[0] = 0;
        CloseRikuCards(w);
        m4aSongNumStop(SONG_SYS_RELOAD);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}
void SelectNextRikuCard(CardBattleWork* w, u8 n) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;

    if (!(gRikuSelectedCard->flags & 2)) {
        if (w->cardsLeft[w->listIndex] != 1) {
            gRikuSelectedCard->flags &= ~4;
            gRikuSelectedCard->timer = 4;
            v = gRikuSelectedCard->args.index + 1;

            if ((s16)v >= (s16)w->slotCounts[n]) {
                v = 0;
            }

            c = FindNextAvailableSlot(w, n, &v);

            if (c != 0) {
                args.pool = &w->cardDisplays[n];
                args.index = v;
                args.listIndex = n;
                args.slot = c;
                args.reloadCount = w->reloadCounts[n];

                if (c->cardId == 0xFFFE) {
                    p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
                } else {
                    p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
                }

                p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
                p->ringIndex = 0;
                p->priority = 60;
                p->timer = 4;
                p->x = p->unk_8C;
                p->y = p->unk_90;
                p->flags |= 0x804;
                gRikuSelectedCard = p;
            }
        }
    }
}

void SelectPrevRikuCard(CardBattleWork* w, u8 n) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;

    if (!(gRikuSelectedCard->flags & 2)) {
        if (w->cardsLeft[w->listIndex] != 1) {
            gRikuSelectedCard->flags &= ~4;
            gRikuSelectedCard->scaleX = 0;
            gRikuSelectedCard->timer = 4;
            v = gRikuSelectedCard->args.index - 1;

            if ((s16)v < 0) {
                v = w->slotCounts[n] - 1;
            }

            c = FindPrevAvailableSlot(w, n, &v);

            if (c != 0) {
                args.pool = &w->cardDisplays[n];
                args.index = v;
                args.listIndex = n;
                args.slot = c;
                args.reloadCount = w->reloadCounts[n];

                if (c->cardId == 0xFFFE) {
                    p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
                } else {
                    p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
                }

                p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
                p->ringIndex = 0;
                p->priority = 60;
                p->timer = 4;
                p->x = p->unk_8C;
                p->y = p->unk_90;
                p->flags |= 0x804;
                gRikuSelectedCard = p;
            }
        }
    }
}

void SwitchRikuCardList(CardBattleWork* w) {
    if ((gRikuSelectedCard->flags & 0x40) != 0) {
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CANSEL);
#endif

        if (gRikuBtlWork->flags & 0x1000000) {
            gRikuBtlWork->flags &= ~0x1000000;
        }

        w->revCountShown[w->listIndex] = 0;

        if (w->reloadPending[w->listIndex] == 0) {
            w->cursors[w->listIndex] = gRikuSelectedCard->args.index;
            gRikuSelectedCard->unk_8C = 0x10400;
            gRikuSelectedCard->unk_90 = 0x8C00;
            gRikuSelectedCard->timer = 4;
            gRikuSelectedCard->command = 7;
            gRikuSelectedCard->flags &= ~4;
        } else {
            w->selectedCards[w->listIndex] = gRikuSelectedCard;
            gRikuSelectedCard->swingAngleTarget = gRikuCardSwingAngles[3];
            gRikuSelectedCard->swingSteps = 4;
            gRikuSelectedCard->flags &= ~4;
        }

        switch (w->listIndex) {
        case 0:
            w->listIndex = 3;
            break;
        case 3:
            w->listIndex = 0;
            break;
        }

        if (w->reloadPending[w->listIndex] == 0) {
            CreateRikuCardDisplay(w, (u8)w->listIndex);
            gRikuSelectedCard->x = gRikuCardLayout[5][0];
            gRikuSelectedCard->y = gRikuCardLayout[5][1];
            gRikuSelectedCard->swingSteps = 1;
            gRikuSelectedCard->timer = 1;
        } else {
            gRikuSelectedCard = w->selectedCards[w->listIndex];
            gRikuSelectedCard->swingAngleTarget = gRikuCardSwingAngles[0];
            gRikuSelectedCard->swingAngle = gRikuSelectedCard->swingAngleTarget;
            gRikuSelectedCard->swingSteps = 1;
            gRikuSelectedCard->timer = 1;
            gRikuSelectedCard->flags |= 4;
        }

        gCardBattleState->rikuListIndex = w->listIndex;
    }
}
void CycleRikuCardList(CardBattleWork* w) {
#ifndef VERSION_EU
    m4aSongNumStart(SONG_SYS_CANSEL);
#endif

    if (gRikuBtlWork->flags & 0x1000000) {
        gRikuBtlWork->flags &= ~0x1000000;
    }

    w->revCountShown[w->listIndex] = 0;

    if (w->reloadPending[w->listIndex] == 0) {
        w->cursors[w->listIndex] = gRikuSelectedCard->args.index;
        gRikuSelectedCard->unk_8C = 0xC800;
        gRikuSelectedCard->unk_90 = 0xB400;
        gRikuSelectedCard->timer = 12;
        gRikuSelectedCard->flags &= ~4;
    } else {
        w->selectedCards[w->listIndex] = gRikuSelectedCard;
        gRikuSelectedCard->swingAngleTarget = gRikuCardSwingAngles[3];
        gRikuSelectedCard->swingSteps = 12;
        gRikuSelectedCard->flags &= ~4;
    }

    switch (w->listIndex) {
    case 0:
        w->listIndex = 3;
        break;
    case 1:
        w->listIndex = 0;
        break;
    case 2:
        w->listIndex = 3;
        break;
    case 3:
        w->listIndex = 0;
        break;
    }

    if (w->reloadPending[w->listIndex] == 0) {
        CreateRikuCardDisplay(w, (u8)w->listIndex);
        gRikuSelectedCard->x = 0x10400;
        gRikuSelectedCard->y = 0x8C00;
        gRikuSelectedCard->timer = 12;
    } else {
        gRikuSelectedCard = w->selectedCards[w->listIndex];
        gRikuSelectedCard->swingAngleTarget = gRikuCardSwingAngles[0];
        gRikuSelectedCard->swingAngle = gRikuCardSwingAngles[1];
        gRikuSelectedCard->swingSteps = 12;
        gRikuSelectedCard->timer = 12;
        gRikuSelectedCard->flags |= 4;
    }

    gCardBattleState->rikuListIndex = w->listIndex;
}

void func_08080228(CardBattleWork* w) {
    if (gBtlWork->hcEffect == 0x30) {
        if (gRikuSelectedCard->value != 0) {
            gRikuSelectedCard->value -= gCardBattleState->activeValue;
        }

        gBtlWork->hcEffectCount--;
    }
}

void func_08080268(CardBattleWork* w) {
    CardDisplayWork* q;
    u8 d;
    u8 i;
    u16 remaining;

    d = gCardBattleState->activeValue;

    if (gBtlWork->hcEffect == 0x30) {
        if (w->stockValue != 0) {
            for (i = 0; i < 3; i++) {
                q = w->stock[i];

                if (q->value > d) {
                    q->value -= d;
                    break;
                }

                remaining = d - q->value;
                q->value = 0;
                d = remaining;
            }
        }

        gBtlWork->hcEffectCount--;
    }
}

void TryRikuCardBreak(CardBattleWork* w) {
#ifdef VERSION_EU
    s32 i;
#endif
    s32 f;
    s32 j;
    u32 t;
    s32 u;
    u8 n;
    u8 flag;

    f = gRikuBtlWork->hcEffect;

    if (f == 1) {
        t = gRikuSelectedCard->value;
        n = t + 1;

        if (n > 9) {
            n = 9;
        }

        if (t <= 8) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gRikuSelectedCard->cardDef);
        }

        gRikuSelectedCard->value = n;
        gRikuSelectedCard->valueModified = 1;
    } else if (f == 21) {
        u = gRikuSelectedCard->value;

        if (u != 0) {
            n = u - 1;
            gRikuSelectedCard->value = u - 1;
            gRikuSelectedCard->valueModified = 1;
        } else {
            n = 0;
            gRikuSelectedCard->valueModified = 1;
        }
    } else {
        n = gRikuSelectedCard->value;
    }

    if ((s16)gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    flag = 0;

    if (gBtlWork->hcEffect == 2 && gCardBattleState->activeCards[0]->cardDef->category == 0 && gCardBattleState->soraStockActive == 0) {
        flag = 1;
    }

#ifdef VERSION_EU
    if (gBtlWork->hcEffect == 20) {
        for (i = 0; i < gCardBattleState->activeCardCount; i++) {
            if (gCardBattleState->activeCards[i]->cardDef->move == 22) {
                flag = 1;
            }
        }
    }

    if (gBtlWork->hcEffect == 29) {
        for (j = 0; j < gCardBattleState->activeCardCount; j++) {
            if (gCardBattleState->activeCards[j]->cardDef->category == 2 && !(gCardBattleState->activeCards[j]->cardDef->flags & 8)) {
                flag = 1;
            }
        }
    }
#else
    if (gBtlWork->hcEffect == 20 && gCardBattleState->activeCards[0]->cardDef->move == 22 && gCardBattleState->soraStockActive == 0) {
        flag = 1;
    }

    if (gBtlWork->hcEffect == 29 && gCardBattleState->activeCards[0]->cardDef->category == 2 && gCardBattleState->soraStockActive == 0) {
        flag = 1;
    }
#endif

    if (flag) {
        return;
    }

    for (j = 0; j < gCardBattleState->activeCardCount; j++) {
        gCardBattleState->activeCards[j]->flags |= 0x200000;
    }

    gBtlWork->flags |= 0x800000;

    if ((s16)gCardBattleState->activeValue != n) {
        if (n == 0) {
            if ((s16)gCardBattleState->activeValue > 9) {
                gBtlWork->breakDifference = 9;
            } else {
                gBtlWork->breakDifference = gCardBattleState->activeValue;
            }
        } else {
            gBtlWork->breakDifference = (u8)gCardBattleState->activeValue - n;

            if ((s8)gBtlWork->breakDifference < -9) {
                gBtlWork->breakDifference = -9;
            }
        }

        m4aSongNumStart(SONG_BTL_GARD);
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags &= ~0x20;
        gRikuSelectedCard->flags |= 0x2000;
        func_08080228(w);
        gCardBattleState->activeCards[0] = gRikuSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = gRikuSelectedCard->value;
        gBtlWork->soraOwnsPlay = 0;
        AddBreakDarkPoints();
    } else {
        func_08080228(w);
        gBtlWork->breakDifference = 0;
        gBtlWork->flags &= ~0x80;
        gBtlWork->flags &= ~0x20;
        gBtlWork->flags &= ~0x400;
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->soraOwnsPlay = 0;
        gCardBattleState->activeCards[0] = gRikuSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = gRikuSelectedCard->value;
    }
}

u8 UseRikuCard(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;
    u16 t;

    if ((gBtlWork->flags & 0x80) == 0) {
        gCardBattleState->activeCards[0] = gRikuSelectedCard;

        if (gRikuBtlWork->hcEffect == 1) {
            gCardBattleState->activeValue = gRikuSelectedCard->value + 1;
            gRikuSelectedCard->value++;
            gRikuSelectedCard->valueModified = 1;

            if (gRikuSelectedCard->value > 9) {
                gRikuSelectedCard->value = 9;
            }

            if ((s16)gCardBattleState->activeValue > 9) {
                gCardBattleState->activeValue = 9;
            }

            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gRikuSelectedCard->cardDef);
        } else if (gRikuBtlWork->hcEffect == 21) {
            if (gRikuSelectedCard->value != 0) {
                gCardBattleState->activeValue = gRikuSelectedCard->value - 1;
                gRikuSelectedCard->value--;
                gRikuSelectedCard->valueModified = 1;
            } else {
                gCardBattleState->activeValue = 0;
                gRikuSelectedCard->valueModified = 1;
            }
        } else {
            gCardBattleState->activeValue = gRikuSelectedCard->value;
        }

        gCardBattleState->activeCardCount = 1;
        gRikuSelectedCard->flags |= 0x2000;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags |= 0x10000000;
    } else {
        if (gBtlWork->soraOwnsPlay == 0) {
            gRikuSelectedCard->command = 0;
            return 1;
        }

        if ((gBtlWork->flags & 0x20) == 0) {
            TryRikuCardBreak(w);
        } else {
            TryRikuCardBreak(w);
        }

        gBtlWork->flags |= 0x10000000;
    }

    w->cardsLeft[w->listIndex]--;

    if ((gRikuSelectedCard->cardDef->flags & 2) && (gRikuSelectedCard->flags & 0x2000)) {
        gRikuSelectedCard->args.slot->removed = 1;
    }

    if (gRikuSelectedCard->cardDef->flags & 8) {
        gRikuSelectedCard->args.slot->removed = 1;
    }

    if (gRikuSelectedCard->premium == 1) {
        gRikuSelectedCard->args.slot->removed = 1;

        if ((u16)CountRemainingAttackCards(w, 0) == 0) {
            gRikuSelectedCard->args.slot->removed = 0;
        }
    }

    w->playedCards[0] = gRikuSelectedCard;
    gRikuSelectedCard->command = 5;
    gRikuSelectedCard->priority = 50;
    gRikuSelectedCard->args.slot->used = 1;
    v = gRikuSelectedCard->args.index + 1;

    if ((s16)v >= (s16)w->slotCounts[w->listIndex]) {
        v = 0;
    }

    do {
        TickRikuHcEffectOnCardUse();
    } while (0);

    if (gRikuBtlWork->hcEffect == 37) {
        t = GetRandomHcEffect();
        func_08081744(w);
        gCardBattleState->rikuHcEffect = t;
        func_08081740(w, gCardBattleState->rikuHcEffect);
        ApplyRikuHcEffect(w);
        gRikuBtlWork->hcEffectCount = gHcEffectDefs[gRikuBtlWork->hcEffect].count;
    }

    gRikuSelectedCard->flags &= ~0x40;
    gRikuSelectedCard = 0;
    c = FindNextAvailableSlot(w, w->listIndex, &v);

    if (c != 0) {
        args.pool = &w->cardDisplays[w->listIndex];
        args.index = v;
        args.listIndex = w->listIndex;
        args.slot = c;
        args.reloadCount = w->reloadCounts[w->listIndex];

        if (c->cardId == 0xFFFE) {
            p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
        } else {
            p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
        }

        p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
        p->ringIndex = 0;
        p->priority = 60;
        p->timer = 4;
        p->x = p->unk_8C;
        p->y = p->unk_90;
        p->flags |= 0x804;
        gRikuSelectedCard = p;
    }

    if (gRikuBtlWork->hcEffect == 40 && (gRikuSelectedCard->flags & 0x100000) &&
        w->cardsLeft[w->listIndex] == 1) {
        w->cardsLeft[w->listIndex] = 0;
        gRikuSelectedCard->command = 7;
        w->selectedCards[w->listIndex] = 0;
        gRikuSelectedCard = 0;
        w->reloadPending[0] = 1;
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

        if (FadeGetAmount() == 0) {
            FadeFromAmount(2, 16, 20);
        }
    }

    return 1;
}

void BeginRikuReloadDeal(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardDisplayWork* q;
    CardSlot* c = 0;
    u16 v;

    w->unk_C4[2] = 0;
    ResetCardSlotsForReload(w, w->listIndex);

    if (CountAvailableCardSlots(w, w->listIndex) != 0) {
        v = w->slotCounts[w->listIndex] - 1;
        c = FindPrevAvailableSlot(w, w->listIndex, &v);

        if (c != 0) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = v;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == 0xFFFE) {
                p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
            }

            p->unk_80 = p->unk_7C = 0;
            p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
            p->ringIndex = 0;
            p->priority = 50;
            p->x = p->unk_8C;
            p->y = p->unk_90;
            p->timer = 8;
            p->flags |= 0x814;
            gRikuSelectedCard = p;
            w->unk_C4[2]++;
            w->cardsLeft[w->listIndex]++;
        }
    } else {
        args.pool = &w->cardDisplays[w->listIndex];
        args.index = 0xFFFF;
        args.slot = w->slots[w->listIndex];
        args.listIndex = w->listIndex;
        q = TaskCreate(&w->tasks, &gTaskDescNOCard, &args)->work;
        q->unk_80 = q->unk_7C = 0;
        q->swingAngleTarget = q->swingAngle = gRikuCardSwingAngles[0];
        q->x = q->unk_8C;
        q->y = q->unk_90;
        q->priority = 50;
        q->flags |= 0x806;
        gRikuSelectedCard = q;
    }

    TickRikuHcEffectOnReload();
}
u8 StockRikuCard(CardBattleWork* w) {
    CardDisplayArgs args;
    u16 t;
    u8 n;
    CardSlot* c;
    CardDisplayWork* p;
    u16 v;

    if (!(gRikuSelectedCard->flags & 0x40)) {
        return 1;
    }

    if (gRikuSelectedCard->flags & 2) {
        return 1;
    }

    if (gCardBattleState->unk_0B0 == 112) {
        return 1;
    }

    if (gCardBattleState->unk_0B0 == 109) {
        return 1;
    }

    w->unk_C4[1] = 0;
    gCardBattleState->rikuStockNameShown = 0;
#ifndef VERSION_EU
    m4aSongNumStart(SONG_SYS_KETEI2);
#endif
    gRikuSelectedCard->flags = (gRikuSelectedCard->flags & ~0x40) | 0x200;
    gRikuSelectedCard->command = 6;
    gRikuSelectedCard->stockIndex = w->stockCount;
    gRikuSelectedCard->priority = (3 - w->stockCount) * 4 + 50;
    w->stock[w->stockCount] = gRikuSelectedCard;
    gCardBattleState->unk_024[gCardBattleState->unk_0DF] = gRikuSelectedCard;
    gRikuSelectedCard->args.slot->stocked = 1;

    if (gRikuBtlWork->hcEffect == 1) {
        n = gRikuSelectedCard->value + 1;

        if (n > 9) {
            n = 9;
        }

        gRikuSelectedCard->value = n;
        gRikuSelectedCard->valueModified = 1;
        TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gRikuSelectedCard->cardDef);
    } else if (gRikuBtlWork->hcEffect == 21) {
        if (gRikuSelectedCard->value != 0) {
            n = gRikuSelectedCard->value - 1;
            gRikuSelectedCard->value--;
            gRikuSelectedCard->valueModified = 1;
        } else {
            n = 0;
            gRikuSelectedCard->valueModified = 1;
        }
    } else {
        n = gRikuSelectedCard->value;
    }

    w->stockValue += n;
    w->stockCount++;
    gCardBattleState->unk_0DF++;

    if (w->stockValue != 0) {
        UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8 + ((w->stockValue - 1) << 7));
        w->unk_C4[3] = 8;
    }

    w->cardsLeft[w->listIndex]--;

    if (gRikuSelectedCard->cardDef->flags & 8) {
        gRikuSelectedCard->args.slot->removed = 1;
    }

    gRikuSelectedCard->args.slot->used = 1;
    v = gRikuSelectedCard->args.index + 1;

    if ((s16)v >= (s16)w->slotCounts[w->listIndex]) {
        v = 0;
    }

    gRikuSelectedCard->flags &= ~0x40;
    gRikuSelectedCard = 0;

    if (gRikuBtlWork->hcEffect == 37) {
        t = GetRandomHcEffect();
        func_08081744(w);
        gCardBattleState->rikuHcEffect = t;
        func_08081740(w, gCardBattleState->rikuHcEffect);
        ApplyRikuHcEffect(w);
        gRikuBtlWork->hcEffectCount = gHcEffectDefs[gRikuBtlWork->hcEffect].count;
    }

    c = FindNextAvailableSlot(w, w->listIndex, &v);

    if (c != 0) {
        args.pool = &w->cardDisplays[w->listIndex];
        args.index = v;
        args.listIndex = w->listIndex;
        args.slot = c;
        args.reloadCount = w->reloadCounts[w->listIndex];

        if (c->cardId == 0xFFFE) {
            p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
        } else {
            p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
        }

        p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
        p->ringIndex = 0;
        p->priority = 60;
        p->timer = 4;
        p->x = p->unk_8C;
        p->y = p->unk_90;
        p->flags |= 0x804;
        gRikuSelectedCard = p;
    }

    if (gRikuBtlWork->hcEffect == 40 && (gRikuSelectedCard->flags & 0x100000) &&
        w->cardsLeft[w->listIndex] == 1) {
        w->cardsLeft[w->listIndex] = 0;
        gRikuSelectedCard->command = 7;
        w->selectedCards[w->listIndex] = 0;
        gRikuSelectedCard = 0;
        w->reloadPending[0] = 1;
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

        if (FadeGetAmount() == 0) {
            FadeFromAmount(2, 16, 20);
        }
    }

    return 1;
}

void TryRikuStockBreak(CardBattleWork* w) {
    CardDisplayWork** q;
    u8 n = w->stockValue;
    u16 total = 0;
#ifdef VERSION_EU
    CardDisplayWork* previous[3];
#endif
    UnkStruct_080ABA80 arr = *(UnkStruct_080ABA80*)&gRikuCardSwingAngles[6];
    u8 flag;
    u8 skip;
    u8 i;
    u16 result;
#ifdef VERSION_EU
    u8 previousCount;
    s32 j;
    s32 k;
#endif

    if ((s16)gCardBattleState->activeValue > n && n != 0) {
        return;
    }
    skip = 0;
    if (gBtlWork->hcEffect == 2 && gCardBattleState->activeCards[0]->cardDef->category == 0 &&
        gCardBattleState->soraStockActive == 0) {
        skip = 1;
    }
#ifdef VERSION_EU
    if (gBtlWork->hcEffect == 20) {
        for (j = 0; j < gCardBattleState->activeCardCount; j++) {
            if (gCardBattleState->activeCards[j]->cardDef->move == 22) {
                skip = 1;
            }
        }
    }
    if (gBtlWork->hcEffect == 29) {
        for (k = 0; k < gCardBattleState->activeCardCount; k++) {
            if (gCardBattleState->activeCards[k]->cardDef->category == 2 &&
                !(gCardBattleState->activeCards[k]->cardDef->flags & 8)) {
                skip = 1;
            }
        }
    }
#else
    if (gBtlWork->hcEffect == 20 && gCardBattleState->activeCards[0]->cardDef->move == 22 &&
        gCardBattleState->soraStockActive == 0) {
        skip = 1;
    }
    if (gBtlWork->hcEffect == 29 && gCardBattleState->activeCards[0]->cardDef->category == 2 &&
        gCardBattleState->soraStockActive == 0) {
        skip = 1;
    }
#endif
    if (skip != 0) {
        return;
    }
    for (i = 0; i < gCardBattleState->activeCardCount; i++) {
        gCardBattleState->activeCards[i]->flags |= 0x200000;
    }
    gBtlWork->flags |= 0x800000;
    if ((s16)gCardBattleState->activeValue != n) {
        if (n == 0) {
            gBtlWork->breakDifference = -(u8)gCardBattleState->activeValue;
            if ((s8)gBtlWork->breakDifference < -9) {
                gBtlWork->breakDifference = -9;
            }
        } else {
            gBtlWork->breakDifference = (u8)gCardBattleState->activeValue - n;
            if ((s8)gBtlWork->breakDifference < -9) {
                gBtlWork->breakDifference = -9;
            }
        }
        AddBreakDarkPoints();
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x10000000;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags &= ~0x20ULL;
        func_08080268(w);
#ifndef VERSION_EU
        if (!(gBtlWork->flags & 0x4000)) {
            result = LookupStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag);
        } else {
            result = LookupLinkStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag, 1);
        }
        if (result == 52) {
            for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                if (gCardBattleState->activeCards[i]->args.slot->used == 1) {
                    gCardBattleState->activeCards[i]->args.slot->removed = 1;
                    gCardBattleState->activeCards[i]->flags |= 0x80000000;
                }
            }
        }
#endif
        for (i = 0; i < w->stockCount; i++) {
            total += w->stock[i]->value;
        }
        gCardBattleState->activeValue = total;
#ifdef VERSION_EU
        previousCount = gCardBattleState->activeCardCount;
#endif
        gCardBattleState->activeCardCount = w->stockCount;
        for (i = 0; i < w->stockCount; i++) {
#ifdef VERSION_EU
            previous[i] = gCardBattleState->activeCards[i];
#endif
            q = gCardBattleState->activeCards;
            q += i;
            *q = w->stock[i];
            w->stock[i]->flags |= 0x2000;
            if (w->stock[i]->cardDef->flags & 2) {
                w->stock[i]->args.slot->removed = 1;
            }
        }
        *(u8*)&gBtlWork->soraOwnsPlay = 0;
        gCardBattleState->rikuStockActive = 1;
        m4aSongNumStart(SONG_BTL_GARD);
#ifdef VERSION_EU
        if (!(gBtlWork->flags & 0x4000)) {
            result = LookupStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag);
        } else {
            result = LookupLinkStockName(w->stock, w->stockCount, w->stockValue, &arr, &flag, 1);
        }
        if (result == 52) {
            for (i = 0; i < previousCount; i++) {
                if (previous[i]->args.slot->used == 1) {
                    previous[i]->args.slot->removed = 1;
                    previous[i]->flags |= 0x80000000;
                }
            }
        }
#endif
    } else {
        gBtlWork->breakDifference = 0;
        func_08080268(w);
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->flags &= ~0x400ULL;
        gBtlWork->flags &= ~0x20ULL;
        gBtlWork->flags &= ~0x80ULL;
        gCardBattleState->rikuStockActive = 0;
        *(u8*)&gBtlWork->soraOwnsPlay = 0;
    }
}

void UseRikuStock(CardBattleWork* w) {
    CardDisplayWork** q;
    CardDisplayWork* p;
    u64 flags;
    u8 i;
    u8 n;

    for (i = 0, n = 0; i < w->stockCount; i++) {
        if (w->stock[i]->flags & 0x40) {
            n++;
        }
    }

    if (n < w->stockCount) {
        return;
    }

    gCardBattleState->unk_0C0 = 0;
    gCardBattleState->rikuStockNameShown = 0;
    w->unk_C4[1] = 0;
    flags = gBtlWork->flags;

    if ((flags & 0x80) == 0) {
        gCardBattleState->activeCardCount = w->stockCount;

        for (i = 0; i < w->stockCount; i++) {
            q = gCardBattleState->activeCards;
            q += i;
            *q = w->stock[i];
            w->stock[i]->priority = i * 4 + 50;

            if (w->stock[i]->cardDef->flags & 2) {
                w->stock[i]->args.slot->removed = 1;
            }

            w->stock[i]->flags |= 0xA000;
        }

        gCardBattleState->activeValue = w->stockValue;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x10000000;
        gCardBattleState->rikuStockActive = 1;
    } else {
        if (gBtlWork->soraOwnsPlay == 0) {
            return;
        }

        if ((flags & 0x20) == 0) {
            TryRikuStockBreak(w);
            gBtlWork->flags |= 0x10000000;
        } else {
            TryRikuStockBreak(w);
            gBtlWork->flags |= 0x10000000;
        }
    }

    for (i = 0; i < w->stockCount; i++) {
        w->stock[i]->args.slot->stocked = 0;

        if (w->stock[i]->cardDef->flags & 2) {
            w->stock[i]->args.slot->removed = 1;
        } else if (i == 0 && gRikuBtlWork->hcEffect != 15) {
            w->stock[0]->args.slot->removed = 1;
        }
    }

    if (CountRemainingAttackCards(w, 0) == 0) {
        for (i = 0; i < w->stockCount; i++) {
            if (w->stock[i]->args.listIndex == 0) {
                w->stock[i]->args.slot->removed = 0;
                break;
            }
        }
    }

    i = 0;

    if (i < w->stockCount) {
        do {
            p = 0;
            n = i;
            w->playedCards[n] = w->stock[n];
            w->stock[n]->command = 5;
            w->stock[n] = p;
            i = ++n;
        } while (i < w->stockCount);
    }

    TickRikuHcEffectOnCardUse();
    w->stockCount = 0;
    gCardBattleState->unk_0DF = 0;
    w->stockValue = 0;
    ClearStockedCardSlots(w);
    w->unk_C4[1] = 0;
}

u8 UseRikuHeartlessCard(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardDisplayWork* q;
    CardSlot* c;
    u16 v;
    CardDisplayWork** pp;

    if ((gRikuSelectedCard->flags & 2) == 0) {
        if (gCardBattleState->rikuHcEffect == 0) {
            gCardBattleState->rikuHcEffect = gRikuSelectedCard->cardDef->move;
            func_08081740(w, gCardBattleState->rikuHcEffect);
            ApplyRikuHcEffect(w);
            pp = &gRikuSelectedCard;
        } else {
            func_08081744(w);
            gCardBattleState->rikuHcEffect = gRikuSelectedCard->cardDef->move;
            func_08081740(w, gCardBattleState->rikuHcEffect);
            ApplyRikuHcEffect(w);
            gCardBattleState->rikuHcEffectReplaced = 1;
            pp = &gRikuSelectedCard;
        }

        gRikuSelectedCard->args.slot->removed = 1;
        gRikuSelectedCard->command = 10;
        gRikuSelectedCard->priority = 50;
        gRikuSelectedCard->flags &= ~0x40;

        if (w->stockValue > 1) {
            UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8 + ((w->stockValue - 1) << 7));
            w->unk_C4[3] = 8;
        }

        gRikuSelectedCard->args.slot->used = 1;
        q = gRikuSelectedCard;
        v = q->args.index + 1;

        if ((s16)v >= (s16)w->slotCounts[w->listIndex]) {
            v = 0;
        }

        q->flags &= ~0x40;
        gRikuSelectedCard = 0;
        w->cardsLeft[w->listIndex]--;
        c = FindNextAvailableSlot(w, w->listIndex, &v);

        if (c != 0) {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = v;
            args.listIndex = w->listIndex;
            args.slot = c;
            args.reloadCount = w->reloadCounts[w->listIndex];

            if (c->cardId == 0xFFFE) {
                p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                p = TaskCreate(&w->tasks, &gTaskDescCardRiku, &args)->work;
            }

            p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
            p->ringIndex = 0;
            p->priority = 60;
            p->timer = 4;
            p->x = p->unk_8C;
            p->y = p->unk_90;
            p->flags |= 0x844;
            gRikuSelectedCard = p;
        } else {
            args.pool = &w->cardDisplays[w->listIndex];
            args.index = 0xFFFF;
            args.slot = w->slots[w->listIndex];
            args.listIndex = w->listIndex;
            p = TaskCreate(&w->tasks, &gTaskDescNOCard, &args)->work;
            p->swingAngleTarget = p->swingAngle = gRikuCardSwingAngles[0];
            p->ringIndex = 0;
            p->priority = 50;
            p->timer = 4;
            p->flags |= 0x846;
            gRikuSelectedCard = p;
        }

        if (*pp == 0) {
            w->reloadPending[w->listIndex] = 1;
        }
    }

    return 1;
}

void func_08081740(CardBattleWork* w, u16 n) {
}
void func_08081744(CardBattleWork* w) {
    gRikuBtlWork->hcEffect = gCardBattleState->rikuHcEffect;
}

void ApplyRikuHcEffect(CardBattleWork* w) {
    if (gBtlWork->hcEffect != 41) {
        gRikuBtlWork->hcEffect = gCardBattleState->rikuHcEffect;
    } else {
        gRikuBtlWork->hcEffect = 0;
        gCardBattleState->rikuHcEffect = 0;
    }

#ifdef VERSION_EU
    if (gRikuBtlWork->hcEffect == 41) {
        if (gBtlWork->hcEffect == 47 && (gBtlWork->flags & 0x20000000)) {
            gBtlWork->flags &= ~2;
        }

        gCardBattleState->soraHcEffect = 0;
        gBtlWork->hcEffect = 0;
        gBtlWork->hcEffectCount = 0;
        gRikuBtlWork->hcEffect = 0;
        gRikuBtlWork->hcEffectCount = 0;
    }
#endif

    if (gCardBattleState->rikuHcEffect == 45) {
        if (gBtlWork->hcEffect != 0) {
            gCardBattleState->rikuHcEffect = gCardBattleState->soraHcEffect;
            gRikuBtlWork->hcEffect = gBtlWork->hcEffect;
        } else {
            gBtlWork->hcEffect = 0;
            gCardBattleState->rikuHcEffect = 0;
        }
    }

    if (gRikuBtlWork->hcEffect == 47) {
        w->reloadCounts[0] = 2;
        w->reloadCounts[1] = 2;
    }

#ifndef VERSION_EU
    if (gRikuBtlWork->hcEffect == 41) {
        gCardBattleState->soraHcEffect = 0;
        gBtlWork->hcEffect = 0;
        gBtlWork->hcEffectCount = 0;
        gRikuBtlWork->hcEffect = 0;
        gRikuBtlWork->hcEffectCount = 0;
    }
#endif
}

u8 func_08081828(void) {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->unk_0ED;
}

u8 GetRikuCardListIndex(void) {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->rikuListIndex;
}

u8 GetActiveCardValue(void) {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->activeValue;
}

s32 func_08081858(void) {
    if (gRikuSelectedCard != 0) {
        return gRikuSelectedCard->cardDef->move;
    }

    return 145;
}

u8 GetRikuSelectedCardValue(void) {
    if (gRikuSelectedCard != 0) {
        return gRikuSelectedCard->value;
    }

    return 0xFF;
}

u8 CanUseRikuSelectedCard(void) {
    if (gRikuBtlWork->hcEffect == 38) {
        if (gRikuSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (!(gRikuSelectedCard->cardDef->flags & 4)) {
            return 1;
        }

        return 0;
    } else if (gRikuBtlWork->hcEffect == 39) {
        if (gRikuSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (gRikuSelectedCard->cardDef->flags & 4) {
            return 1;
        }

        return 0;
    }

    return 1;
}

void TickRikuHcEffectOnReload(void) {
    switch (gRikuBtlWork->hcEffect) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 17:
    case 19:
    case 20:
    case 21:
    case 24:
    case 25:
    case 29:
    case 30:
    case 31:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 42:
    case 51:
    case 53:
        gRikuBtlWork->hcEffectCount--;
        break;
    }
}

void TickRikuHcEffectOnCardUse(void) {
    if (gRikuBtlWork->hcEffect == 50) {
        gRikuBtlWork->hcEffectCount--;
    }
}

void ResetRikuReloadGauge(CardBattleWork* w) {
    gCardBattleState->rikuReloadGauge = 0;
    gCardBattleState->rikuReloadCounter = 0;
    gCardBattleState->rikuGaugeFullFrame = 4;
    gCardBattleState->rikuGaugeAnim = 2;
    gCardBattleState->reloadGaugeFull[1] = 0;
}

void RikuCardInit(CardDisplayWork* p, CardDisplayArgs* a) {
    vu32 zero;
    u16 v;

    zero = 0;
    CpuSet((void*)&zero, p, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardDisplayWork) / 4);
    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->tiles4 = 0;
    p->tiles5 = 0;
    p->palette2 = 0;
    p->palette = 0;
    p->children = 0;
    p->reloadGauge = 0;
    p->args = *a;
    p->flags = 0;
    v = p->args.index;

    if ((s16)v != -1) {
        LookupRikuCardDef(&p->args, &p->cardDef, (u8)v);

        if (p->args.slot->cardId == 0xFFFE) {
            p->flags |= 0x100000;
        }
    } else {
        p->flags = 2;
    }

    if (p->args.slot->cardId & 0x8000) {
        p->premium = 1;
    } else {
        p->premium = 0;
    }

    p->scaleX = 0;
    p->scaleY = 0x100;
    p->bobAngle = 0;
    p->angle = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
    p->swingAngle = 0;
    p->swingAngleTarget = 0;
    p->command = 0;
    p->priority = 80;
    p->timer = 4;
    p->unk_A2 = 0;
    p->unk_84 = 0x2400;
    p->unk_88 = 0x2400;
    p->swingSteps = 0;
    p->unk_8C = gRikuCardLayout[5][0];
    p->unk_90 = gRikuCardLayout[5][1];
    p->x = gRikuCardLayout[4][0];
    p->y = gRikuCardLayout[4][1];

    if (p->cardDef != 0) {
        p->value = p->cardDef->value;
    } else {
        p->value = 0;
    }

    p->valueModified = 0;
    p->flags |= 0x24;
    p->flags &= ~0x40;
}
u8 RikuCardUpdate(CardDisplayWork* p, void* a) {
    if ((p->flags & 0x84) == 4) {
        LoadCardDisplayGfx(p);
        p->flags |= 0x80;
    }

    if (p->flags & 0x10) {
        p->timer = 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080829D0);
        return 1;
    }

    if (p->flags & 4) {
        if ((s16)p->timer > 0) {
            p->flags &= ~0x40;
            ApproachValue(&p->scaleX, 0x100, p->timer);
            p->timer--;
        } else {
            p->flags |= 0x40;
        }
    } else if ((s16)p->timer > 0) {
        p->flags &= ~0x40;
        ApproachValue(&p->scaleX, 0, p->timer);

        if (p->flags & 0x80) {
            ReleaseCardDisplayGfx(p);
            p->flags &= ~0x80;
        }

        p->timer--;
    } else {
        return 0;
    }

    if (p->flags & 0x1000) {
        return 1;
    }

    ApproachValue(&p->x, p->unk_8C, p->timer);
    ApproachValue(&p->y, p->unk_90, p->timer);
    p->bobAngle += 4;

    if (!(p->flags & 0x20)) {
        p->flags &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082A64);
    }

    return DispatchRikuCardCommand(p, a);
}

static void card_2(CardDisplayWork* p) {
    void* gfx;
    ObjAffine* aff;
    u16 y;
    s16 sy;
    u16 flags;
    u8 j;

    gfx = p->cardDef->gfx;

    if (IsMessageWindowOpen() == 1) {
        y = p->y >> 8;
    } else {
        y = (p->y >> 8) + (gSineTable[p->bobAngle] >> 8);
    }

    if (!(p->flags & 0x20)) {
        return;
    }

    if (!(p->flags & 0x80)) {
        return;
    }

    if (p->scaleX == 0) {
        return;
    }

    if (!(p->flags & 0x200)) {
        u8 j;

        if (gRikuBtlWork->hcEffect == 7) {
            return;
        }

        aff = AllocObjAffine(p->angle, p->scaleX, p->scaleY, 0);
        flags = 0x410;
        DrawSprite(p->x >> 8, y, gCardBacks[p->cardDef->category].gfx, gCardBattleState->tiles[p->cardDef->category], gCardBattleState->palette, aff, flags, (u16)(p->priority - 1));
        DrawSprite(p->x >> 8, y, gfx, p->tiles, p->palette, aff, flags, p->priority);
        j = p->value;

        if (p->cardDef->category == 3) {
            return;
        }

        if (p->valueModified != 0) {
            DrawSprite(p->x >> 8, y, gUnk_09EE98C0[j], gCardBattleState->tiles7, gCardBattleState->palette2, aff, flags, (u16)(p->priority - 2));
        } else if (p->premium != 0) {
            DrawSprite(p->x >> 8, y, gUnk_09EE9894[j], gCardBattleState->tiles6, gCardBattleState->palette2, aff, flags, (u16)(p->priority - 2));
        } else {
            DrawSprite(p->x >> 8, y, gUnk_09EE981C[j], gCardBattleState->tiles5, gCardBattleState->palette, aff, flags, (u16)(p->priority - 2));
        }

        if (p->premium != 0) {
            DrawSprite(p->x >> 8, y, gCardBattleState->gfx, gCardBattleState->premiumTiles, gCardBattleState->palette, aff, flags, (u16)(p->priority - 3));
        }

        return;
    }

    if (gRikuBtlWork->hcEffect == 28) {
        return;
    }

    aff = AllocObjAffine(0, p->scaleX, p->scaleY, 0);
    flags = 0x410;
    sy = y;
    DrawSprite(p->x >> 8, sy, p->cardDef->gfx2, p->tiles, p->palette, aff, flags, p->priority);
    j = p->value;

    if (p->cardDef->category == 3) {
        return;
    }

    if (p->valueModified != 0) {
        DrawSprite((p->x >> 8) - 3, sy - 4, gUnk_09EE981C[j], gCardBattleState->tiles7, gCardBattleState->palette2, aff, flags, (u16)(p->priority - 10));

        if (p->premium != 0) {
            DrawSprite(p->x >> 8, sy, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, aff, flags, (u16)(p->priority - 11));
        }
    } else if (p->premium != 0) {
        DrawSprite((p->x >> 8) - 3, sy - 4, gUnk_09EE981C[j], gCardBattleState->tiles6, gCardBattleState->palette2, aff, flags, (u16)(p->priority - 10));
        DrawSprite(p->x >> 8, sy, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, aff, flags, (u16)(p->priority - 11));
    } else {
        DrawSprite((p->x >> 8) - 3, sy - 4, gUnk_09EE981C[j], gCardBattleState->tiles5, gCardBattleState->palette, aff, flags, (u16)(p->priority - 10));
    }
}

void NO_Card_2(CardDisplayWork* p) {
    void* gfx;
    u16 y;

    gfx = gCardBacks[0].gfx2;

    if (IsMessageWindowOpen() == 1) {
        y = p->y >> 8;
    } else {
        y = (p->y >> 8) + (gSineTable[p->bobAngle] >> 8);
    }

    if (p->flags & 0x20) {
        if (p->flags & 0x80) {
            if (p->scaleX != 0) {
                if (gRikuBtlWork->hcEffect != 7) {
                    DrawSprite(p->x >> 8, y, gfx, p->tiles2, gCardBattleState->palette, 0, 0x410, (u16)(p->priority - 1));
                }
            }
        }
    }
}

void RikuCardDestroy(CardDisplayWork* p) {
    ReleaseCardDisplayGfx(p);

    if (p->reloadGauge != 0) {
        EwramFree(p->reloadGauge);
    }
}

void func_0808210C(CardDisplayWork* p) {
    if (p->command == 6) {
        return;
    }

    if (p->scaleX == 0) {
        if (p->flags & 0x80) {
            ReleaseCardDisplayGfx(p);
            p->flags &= ~0x80;
        }
    } else {
        if ((p->flags & 0x80) == 0) {
            LoadCardDisplayGfx(p);
            p->flags |= 0x80;
        }
    }
}

u8 func_08082154(CardDisplayWork* p, void* a) {
    if (gBtlWork->flags & 0x20) {
        p->timer = 8;
        p->unk_9E = 8;
        gCardBattleState->activeCardCount = 0;
        gCardBattleState->activeValue = 0;
        gBtlWork->flags &= ~0x80;
        gBtlWork->flags &= ~0x20;
        gBtlWork->flags &= ~0x10000000;

        if (p->cardDef->category == 0) {
            TickRikuHcEffectOnAttackEnd();
        }

        SetTaskUpdate(a, (TaskUpdateFunc)func_08082AE4);
    } else if (p->flags & 0x200000) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082E0C);
    }

    return 1;
}

u8 func_08082224(CardDisplayWork* p, void* a) {
    ApproachValue(&p->x, 0x7800, p->timer);
    ApproachValue(&p->y, 0x8400, p->timer);
    p->priority = 80;

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        p->timer |= 0xFFFF;
    }

    if (gBtlWork->flags & 0x80) {
        if (p->flags & 0x2000) {
            if ((s16)p->timer == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_08082154);
            }
        } else if ((s16)p->timer <= 2) {
            p->priority -= 4;
            p->unk_84 = 0x500;
            p->timer = 0x100;
            p->unk_7C = 16;
            p->unk_9E = 1;
            p->flags |= 0x2000;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);

            if (p->cardDef->flags & 2) {
                p->args.slot->unk_06 = 0;
            }

            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)p->timer <= 2) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
    }

    return 1;
}
u8 func_08082348(CardDisplayWork* p, void* a) {
    ApproachValue(&p->unk_8C, gPlayedCardCenter[0], p->timer);
    ApproachValue(&p->unk_90, gPlayedCardCenter[1], p->timer);
    ApproachValue(&p->unk_84, p->unk_88, p->timer);
    ApproachValue(&p->scaleX, 0x100, p->timer);
    ApproachValue(&p->scaleY, 0x100, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        p->timer = 0;
    }

    func_08082BF8(p);

    switch (p->stockIndex) {
    case 0:
        p->priority = 50;
        break;
    case 1:
        p->priority = 40;
        break;
    case 2:
        p->priority = 60;
        break;
    }

    if (p->flags & 0x200000) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        gCardBattleState->rikuStockActive = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082E0C);
    }

    if (gBtlWork->flags & 0x20) {
        p->timer = 8;
        p->unk_9E = 8;
        gCardBattleState->activeCardCount--;
        gCardBattleState->activeValue = 0;

        if (gCardBattleState->activeCardCount == 0) {
            gBtlWork->flags &= ~0x20;
            gBtlWork->flags &= ~0x80;
            TickRikuHcEffectOnPlayEnd();
        }

        gCardBattleState->rikuStockActive = 0;
        gBtlWork->flags &= ~0x10000000;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082AE4);
    }

    return 1;
}
u8 func_080824C8(CardDisplayWork* p, void* a) {
    ApproachValue(&p->unk_8C, gPlayedCardCenter[0], p->timer);
    ApproachValue(&p->unk_90, gPlayedCardCenter[1], p->timer);
    ApproachValue(&p->unk_84, p->unk_88, p->timer);
    ApproachValue(&p->scaleX, 0x100, p->timer);
    ApproachValue(&p->scaleY, 0x100, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    } else {
        p->timer = 0;
    }

    func_08082BF8(p);

    if (gBtlWork->flags & 0x80) {
        if (p->flags & 0x2000) {
            if ((s16)p->timer == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_08082348);
            }
        } else if ((s16)p->timer <= 2) {
            p->priority -= 4;
            p->unk_84 = 0x500;
            p->timer = 0x100;
            p->unk_7C = 16;
            p->unk_9E = 1;
            gCardBattleState->unk_0C0 = 0;
            gCardBattleState->rikuStockActive = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)p->timer <= 2) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        gCardBattleState->rikuStockActive = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
    }

    return 1;
}
u8 func_08082618(CardDisplayWork* p, void* a) {
    u8 (*f)(CardDisplayWork*, void*);
    s32 v;

    SyncCardDisplayGfx(p);

    if (!(p->flags & 0x10000000)) {
        f = func_080827E0;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(p, a);
    }

    if (p->flags & 0x40000000) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082FF0);
        return 1;
    }

    if (p->command == 5) {
        if (p->flags & 0x8000) {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            f = func_08082348;
        } else {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            f = func_080824C8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)f);
        p->flags &= ~0x200;
        RefreshRikuCardDisplayGfx(p);
        return f(p, a);
    }

    if ((s16)p->timer > 0) {
        p->timer--;
        return 1;
    }

    if (p->flags & 0x20) {
        switch (p->unk_A2) {
        case 0:
            p->y -= 0x80;
            v = gRikuCardLayout[3 - p->stockIndex][1] - 0x200;

            if (p->y <= v) {
                p->y = v;
                p->unk_A2 = 1;
            }
            break;
        case 1:
            p->y += 0x200;
            v = gRikuCardLayout[3 - p->stockIndex][1];

            if (p->y >= v) {
                p->y = v;
                p->unk_A2 = 0;
                p->timer = 16;
            }
            break;
        }
    } else {
        ApproachValue(&p->x, gRikuCardLayout[4][0], p->timer);
        ApproachValue(&p->y, gRikuCardLayout[4][1], p->timer);
    }

    p->bobAngle += 4;
    return 1;
}
u8 func_080827E0(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);
    u16 t;

    if (gBtlWork->paused == 1) {
        return 1;
    }

    SyncCardDisplayGfx(p);

    if (p->flags & 0x20) {
        ApproachValue(&p->x, gRikuCardLayout[3 - p->stockIndex][0], p->timer);
        ApproachValue(&p->scaleY, 179, p->timer);
        ApproachValue(&p->y, gRikuCardLayout[3 - p->stockIndex][1], p->timer);
        ApproachValue(&p->scaleX, 179, p->timer);
    } else {
        ApproachValue(&p->x, gRikuCardLayout[4][0], p->timer);
        ApproachValue(&p->y, gRikuCardLayout[4][1], p->timer);
    }

    t = p->timer;

    if ((s16)t > 0) {
        p->timer = t - 1;
        p->flags &= ~0x40;
    } else {
        p->timer = 0;
        p->scaleX = 0x100;
        p->scaleY = 0x100;
        p->flags |= 0x40;

        if (p->flags & 0x10000000) {
            p->timer = p->stockIndex * 8;
            fn = func_08082618;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(p, a);
        }
    }

    if (p->flags & 0x40000000) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082FF0);
        return 1;
    }

    if (p->command == 5) {
        if (p->flags & 0x8000) {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_08082348;
        } else {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_080824C8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        p->flags &= ~0x200;
        RefreshRikuCardDisplayGfx(p);
        return fn(p, a);
    }

    p->bobAngle += 4;
    return 1;
}

u8 func_080829D0(CardDisplayWork* p, void* a) {
    u8 (*f)(CardDisplayWork*, void*);

    if (!(p->flags & 0x20)) {
        f = func_08082A64;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(p, a);
    }

    ApproachValue(&p->scaleX, 0x100, p->timer);
    p->timer--;

    if (p->timer == 0) {
        p->flags &= ~0x10;
        p->scaleX = 0x100;

        if (p->flags & 0x100000) {
            gCardBattleState->rikuReloadCharging = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)Reload_Card_1);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)RikuCardUpdate);
        }
    }

    return 1;
}

u8 func_08082A64(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (p->command == 7) {
        return 0;
    }

    p->unk_84 += -p->unk_84 >> 1;
    p->x += (gRikuCardLayout[4][0] - p->x) >> 1;
    p->y += (gRikuCardLayout[4][1] - p->y) >> 1;

    if (p->flags & 0x20) {
        if (p->flags & 0x100000) {
            fn = Reload_Card_1;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(p, a);
        } else {
            do {
                fn = RikuCardUpdate;
                SetTaskUpdate(a, (TaskUpdateFunc)fn);
            } while (0);

            return fn(p, a);
        }
    }

    return 1;
}

u8 func_08082AE4(CardDisplayWork* p) {
    ApproachValue(&p->y, 0x8200, p->timer);
    *(u16*)&p->timer =
        *(s16*)&p->timer > 0 ? p->timer - 1 : 0;

    if (*(s16*)&p->timer == 0) {
        *(u16*)&p->timer = 0;
        p->angle += p->unk_9E;
        p->unk_9E++;

        if (p->scaleX <= 25) {
            return 0;
        }

        p->scaleX -= 25;
        p->scaleY -= 25;
    }

    return 1;
}

u8 func_08082B48(CardDisplayWork* p) {
    p->command = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->timer;
    p->timer++;
    p->x -= gSineTable[(p->unk_7C & 0xFF) + 0x40];
    p->angle += p->unk_9E;
    p->scaleX -= 5;
    p->scaleY -= 5;

    if (IsCardDisplayOffScreen(p)) {
        p->flags &= ~0x800;
        ReleaseCardDisplayGfx(p);
        gBtlWork->flags &= ~0x10000000;
        p->flags &= ~0x80;
        return 0;
    }

    return 1;
}

void func_08082BF8(CardDisplayWork* p) {
    s32 t;

    if (p->unk_80 - p->unk_7C > 0x7F00) {
        p->unk_7C += 0x10000;
    }

    if (p->unk_80 - p->unk_7C <= 255) {
        t = p->unk_7C - 0x10000;

        if (p->unk_80 - t < p->unk_7C - p->unk_80) {
            p->unk_7C = t;
        }
    }

    p->unk_7C += (p->unk_80 - p->unk_7C) >> 2;
    p->x = gSineTable[(p->unk_7C >> 8) & 0xFF] * (p->unk_84 >> 8) + p->unk_8C;
    p->y = -gSineTable[((p->unk_7C >> 8) & 0xFF) + 64] * (p->unk_84 >> 8) + p->unk_90;
}
u8 DispatchRikuCardCommand(CardDisplayWork* p, void* a) {
    switch (p->command) {
    case 5:
        p->timer = 10;
        p->priority -= 4;
        p->scaleX = 0x100;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082224);
        return 1;
    case 6:
        p->timer = 8;
        p->priority -= 4;
        LoadRikuCardDisplayGfx2(p);
        p->flags |= 0x200;
        p->flags |= 0x80;
        p->flags &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080827E0);
        return 1;
    case 8:
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
        return 1;
    case 7:
        p->unk_84 = 0x500;
        p->timer = 0x100;
        return 0;
    case 10:
        p->timer = 10;
        p->priority -= 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082F50);
        return 1;
    case 9:
    default:
        UpdateRikuCardValue(p);
        break;
    }

    return 1;
}

void LookupRikuCardDef(CardDisplayArgs* a, CardDef** out, u8 index) {
    u32* q;

    if (a->slot != 0) {
        if (a->slot->cardId != 0xFFFF) {
            if (a->slot->cardId != 0xFFFE) {
                *out = &gCardDefs[a->slot->cardId & CARD_ID_MASK];
            } else {
                *out = 0;
            }
        } else {
            *out = 0;
        }
    } else {
        q = &gCardBattleState->pickedFriendCardId;
        *out = &gCardDefs[*q & CARD_ID_MASK];
        *q = 0x3B6;
    }
}

u8 func_08082E0C(CardDisplayWork* p, void* a) {
    p->command = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->timer >> 1;
    p->timer++;
    p->x -= 0x200;
    p->angle += 16;

    if (!(p->flags & 0x400000)) {
        p->scaleX -= 10;

        if (p->scaleX >= -2 && p->scaleX <= 2) {
            p->scaleX = -10;
        }

        if (p->scaleX <= -0x100) {
            p->scaleX = -0x100;
            p->flags |= 0x400000;
        }
    } else {
        p->scaleX -= 10;

        if (p->scaleX >= -2 && p->scaleX <= 2) {
            p->scaleX = 10;
        }

        if (p->scaleX >= 0x100) {
            p->scaleX = 0x100;
            p->flags &= ~0x400000;
        }
    }

    if (IsCardDisplayOffScreen(p)) {
        p->flags &= ~0x800;
        ReleaseCardDisplayGfx(p);
        p->flags &= ~0x80;
        gBtlWork->flags &= ~0x10000000;
        return 0;
    }

    return 1;
}
void LoadRikuCardDisplayGfx2(CardDisplayWork* p) {
    void* tiles;
    void* pal;

    ReleaseCardDisplayGfx(p);
    tiles = p->cardDef->tiles2;
    pal = p->cardDef->palette2;
    p->tiles = LoadObjTiles(tiles, 256);
    p->palette = LoadObjPalette(pal, 32);
}

void RefreshRikuCardDisplayGfx(CardDisplayWork* p) {
    if (p->tiles != 0) {
        ReleaseObjTiles(p->tiles);
    }

    if (p->palette != 0) {
        ReleaseObjPalette(p->palette);
    }

    p->tiles = 0;
    p->palette = 0;
    LoadCardDisplayGfx(p);
}

u8 func_08082F50(CardDisplayWork* p) {
    u8 arg;

    p->command = 0;
    ApproachValue(&p->x, 0xD800, p->timer);
    ApproachValue(&p->scaleY, 0x99, p->timer);
    ApproachValue(&p->y, 0x6400, p->timer);
    ApproachValue(&p->scaleX, 0x99, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
        return 1;
    }

    arg = 2;
    gRikuBtlWork->hcEffectCount = gHcEffectDefs[gRikuBtlWork->hcEffect].count;
    TaskCreate(&gCardBattleState->tasks, &gTaskDescHCEffectName, &arg);
    return 0;
}

u8 func_08082FF0(CardDisplayWork* p) {
    s32 r;

    if (p->scaleX <= 24) {
        p->args.slot->stocked = r = 0;
        return r;
    }

    p->scaleX -= 12;
    p->scaleY += 12;

    if (p->scaleY > 0x1FF) {
        p->scaleY = 0x200;
    }

    return 1;
}
void Reload_Card_0(CardDisplayWork* p, CardDisplayArgs* a) {
    vu32 zero;
    vu32 zero2;

    zero = 0;
    CpuSet((void*)&zero, p, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardDisplayWork) / 4);
    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->tiles4 = 0;
    p->tiles5 = 0;
    p->palette2 = 0;
    p->palette = 0;
    p->children = 0;
    p->reloadGauge = EwramAlloc(sizeof(ReloadGauge));
    zero2 = 0;
    CpuSet((void*)&zero2, p->reloadGauge, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(ReloadGauge) / 4);
    p->args = *a;
    p->reloadGauge->chargeTick = 0;
    p->flags = 0x01100024;
    p->cardDef = 0;
    p->scaleX = 0;
    p->scaleY = 0x100;
    p->bobAngle = 0;
    p->angle = 0;
    p->stockIndex = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
    p->swingAngle = 0;
    p->swingAngleTarget = 0;
    p->command = 0;
    p->priority = 80;
    p->timer = 4;
    p->unk_A2 = 0;
    p->unk_84 = 0x2400;
    p->unk_88 = 0x2400;
    p->swingSteps = 0;
    p->unk_8C = gRikuCardLayout[5][0];
    p->unk_90 = gRikuCardLayout[5][1];
    p->x = gRikuCardLayout[4][0];
    p->y = gRikuCardLayout[4][1];
    p->flags &= ~0x40;
    gCardBattleState->rikuReloadCharging = 0;
    LoadRikuReloadCardGfx(p);
    p->flags |= 0x80;
}
u8 Reload_Card_1(CardDisplayWork* p, void* a) {
    if (p->flags & 0x10) {
        p->timer = 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080829D0);
        return 1;
    }

    UpdateRikuReloadGauge(p);

    if (p->flags & 4) {
        if ((s16)p->timer > 0) {
            p->flags &= ~0x40;
            ApproachValue(&p->scaleX, 0x100, p->timer);
            gCardBattleState->rikuReloadCharging = 0;
            p->timer--;
        } else {
            p->flags |= 0x40;
        }
    } else {
        if ((s16)p->timer <= 0) {
            return 0;
        }

        p->flags &= ~0x40;
        ApproachValue(&p->scaleX, 0, p->timer);
        gCardBattleState->rikuReloadCharging = 0;
        p->timer--;
    }

    if (p->flags & 0x1000) {
        return 1;
    }

    ApproachValue(&p->x, p->unk_8C, p->timer);
    ApproachValue(&p->y, p->unk_90, p->timer);
    p->bobAngle += 4;

    if (!(p->flags & 0x20)) {
        p->flags &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082A64);
    }

    return DispatchRikuCardCommand(p, a);
}
void Reload_Card_3(CardDisplayWork* p) {
    ReleaseCardDisplayGfx(p);

    if (p->reloadGauge != 0) {
        EwramFree(p->reloadGauge);
    }

    if (gRikuBtlWork->flags & 0x1000000) {
        gRikuBtlWork->flags &= ~0x1000000;
    }
}
void AdvanceRikuReloadGaugeAnim(ReloadGauge* p, CardDisplayWork* w) {
    if (gCardBattleState->rikuGaugeAnim <= 7) {
        gCardBattleState->rikuGaugeAnim++;
    }

    AnimStart(&p->anim3, (u16)gCardBattleState->rikuGaugeAnim, 5);
}
void ResetRikuReloadGaugeAnim(ReloadGauge* p) {
    gCardBattleState->rikuGaugeAnim = 2;
    AnimStart(&p->anim3, 2, 5);
}
void func_080832D0(ReloadGauge* p, CardDisplayWork* w) {
    p->gfx = gRiCardF0RedFrames[3];
    p->gfx2 = gRiCardF0RedFrames[gCardBattleState->rikuGaugeFullFrame + 2];
}
void func_080832F8(ReloadGauge* p, CardDisplayWork* w) {
    p->gfx = AnimUpdate(&p->anim2);
    p->gfx2 = AnimUpdate(&p->anim3);
}
void SetRikuReloadCounterAnim(ReloadGauge* p, s16 a) {
    void* gfx;

    if ((u16)a <= 18) {
        AnimStart(&p->anim, a, 0);
        gfx = AnimGetGfx(&p->anim);
    } else {
        gfx = 0;
    }

    p->gfx3 = gfx;
}
void UpdateRikuReloadGauge(CardDisplayWork* p) {
    ReloadGauge* w = p->reloadGauge;
    u8 v = 0;

    if ((p->flags & 0x44) == 0x44) {
        v = gCardBattleState->rikuReloadCharging;
        gCardBattleState->rikuReloadCharging = 0;
    } else {
        gCardBattleState->rikuReloadCharging = 0;
    }

    if ((p->flags & 0x44) == 0x44) {
        if (v == 1) {
            if ((s8)w->chargeTick == 2) {
                if (!(gRikuBtlWork->flags & 0x1000000)) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_CHAGE);
#endif
                    gRikuBtlWork->flags |= 0x1000000;
                }

                if (gCardBattleState->reloadGaugeFull[1] == 0) {
                    if (gRikuBtlWork->hcEffect == 43) {
                        gCardBattleState->rikuReloadGauge += 12;
                    } else {
                        gCardBattleState->rikuReloadGauge += 25;
                    }

                    if ((s32)gCardBattleState->rikuReloadGauge > 0x100) {
                        gCardBattleState->rikuReloadGauge = 0x100;
                        gCardBattleState->reloadGaugeFull[1] = 1;
                    }
                } else {
                    gCardBattleState->rikuGaugeFullFrame += 3;
                    AdvanceRikuReloadGaugeAnim(p->reloadGauge, p);

                    if (gCardBattleState->rikuGaugeFullFrame == 22) {
                        gCardBattleState->rikuGaugeFullFrame = 4;
                        gCardBattleState->rikuReloadGauge = 0;
                        gCardBattleState->reloadGaugeFull[1] = 0;
                        gCardBattleState->rikuReloadCounter--;
                        p->unk_A2 = v;
                        ResetRikuReloadGaugeAnim(p->reloadGauge);
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
#endif
                        SetRikuReloadCounterAnim(p->reloadGauge, (s16)gCardBattleState->rikuReloadCounter);
                    }
                }

                w->chargeTick = 0;
            }

            func_080832F8(p->reloadGauge, p);
            w->chargeTick++;
        } else {
            func_080832D0(p->reloadGauge, p);
            w->chargeTick = 0;
            m4aSongNumStop(SONG_SYS_CHAGE);
            gRikuBtlWork->flags &= ~0x1000000;
        }
    } else {
        gRikuBtlWork->flags &= ~0x1000000;
    }

    if ((s16)gCardBattleState->rikuReloadCounter < 0) {
        gCardBattleState->rikuReloadGauge = 0;
        gCardBattleState->rikuGaugeFullFrame = 4;
        gCardBattleState->rikuGaugeAnim = 2;
        gCardBattleState->reloadGaugeFull[1] = 0;

        if (!(p->flags & 0x4000000)) {
            p->flags |= 0x4000000;
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif
        }

        if (FadeGetAmount() == 0) {
            FadeFromAmount(2, 16, 20);
        }

        gRikuBtlWork->flags &= ~0x1000000;
    }
}
void Reload_Card_2(CardDisplayWork* p) {
    ObjAffine* affine;
    ObjAffine* affine2;
    ReloadGauge* w;
    s16 y;
    u16 attr;

    attr = 0x410;
    affine = AllocObjAffine(0, p->scaleX, 0x100, 0);

    if (p->flags & 0x80) {
        w = p->reloadGauge;

        if (IsMessageWindowOpen() == 1) {
            y = p->y >> 8;
        } else {
            y = (p->y >> 8) + (gSineTable[p->bobAngle] >> 8);
        }

        if (p->scaleX > 0) {
            DrawSprite(p->x >> 8, y, gCardBacks[3].gfx2, p->tiles2,
                       gCardBattleState->palette, affine, attr, p->priority);

            if (w->gfx3 != 0) {
                DrawSprite(p->x >> 8, y, w->gfx3, p->tiles,
                           gCardBattleState->palette, affine, attr,
                           (u16)(p->priority - 2));
            }

            if ((s32)gCardBattleState->rikuReloadGauge > 0) {
                affine2 = AllocObjAffine(0, p->scaleX, gCardBattleState->rikuReloadGauge, 0);

                if (w->gfx != 0) {
                    DrawSprite(p->x >> 8, y + 17, w->gfx,
                               p->tiles3, gCardBattleState->palette, affine2, 0x400,
                               (u16)(p->priority - 1));
                }

                if (gCardBattleState->reloadGaugeFull[1] == 1 && w->gfx2 != 0) {
                    DrawSprite(p->x >> 8, y, w->gfx2, p->tiles4,
                               gCardBattleState->palette, affine, 0x400,
                               (u16)(p->priority - 1));
                }
            }
        }
    }
}

void InitRikuReloadCounterAnim(ReloadGauge* p, void* a, u8 b, s8 c) {
    AnimInit(&p->anim, gUnk_09EEA4E0, gUnk_09EEA494);

    if (c >= 0) {
        AnimStart(&p->anim, c, 0);
    } else {
        AnimStart(&p->anim, 0, 0);
    }

    p->gfx3 = AnimGetGfx(&p->anim);
}

void LoadRikuReloadCardGfx(CardDisplayWork* w) {
    ReloadGauge* q;

    q = w->reloadGauge;
    w->tiles = AllocObjTiles(128, 0);
    SetObjTileSource(w->tiles, gUnk_0909A4E0);
    InitRikuReloadCounterAnim(w->reloadGauge, w->tiles, w->args.listIndex, gCardBattleState->rikuReloadCounter);
    w->palette = 0;
    w->tiles2 = LoadObjTiles(gUnk_0909FDCA, 0x280);
    w->palette2 = 0;
    w->tiles3 = AllocObjTiles(0x200, 0);
    SetObjTileSource(w->tiles3, gRiCardF0RedTiles);
    w->tiles4 = AllocObjTiles(128, 0);
    SetObjTileSource(w->tiles4, gRiCardF0RedTiles);
    AnimInit(&q->anim2, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&q->anim2, 1, 1);
    q->gfx = gRiCardF0RedFrames[3];
    AnimInit(&q->anim3, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&q->anim3, gCardBattleState->rikuGaugeAnim, 1);
    q->gfx2 = gRiCardF0RedFrames[gCardBattleState->rikuGaugeFullFrame + 2];
}

void UpdateRikuCardValue(CardDisplayWork* p) {
    // @bug The reload card and the empty slot have no cardDef (NULL read).
    if (gRikuBtlWork->hcEffect == 16) {
        if (p->flags & 4) {
            p->valueModified = 1;
            p->value = GetRandom() % 10;
        } else {
            p->valueModified = 0;
            p->value = p->cardDef->value;
        }
    } else if (gRikuBtlWork->hcEffect == 31) {
        p->valueModified = 1;
        p->value = 10 - p->cardDef->value;

        if (p->value == 10) {
            p->value = 0;
        }
    } else if (gRikuBtlWork->hcEffect == 17) {
        p->valueModified = 1;
        p->value = 0;
    } else {
        p->value = p->cardDef->value;
        p->valueModified = 0;
    }
}

void TickRikuHcEffectOnPlayEnd(void) {
    BtlWork* p;

    p = gRikuBtlWork;

    switch ((u32)p->hcEffect) {
    case 15:
    case 28:
    case 47:
        p->hcEffectCount--;
        break;
    }
}
void TickRikuHcEffectOnAttackEnd(void) {
    if (gRikuBtlWork->hcEffect == 2) {
        gRikuBtlWork->hcEffectCount--;
    }
}

void func_080838E8(void) {
}

void RequestBossCardClose(void) {
    gBossCardRequest = 7;
}

void func_080838F8(void) {
}

void func_080838FC(void) {
}

void RequestBossCardValue(u8 a) {
    gBossCardRequest = 1;
    gBossCardRequestValue = a;
}

void RequestBossCardRandom(void) {
    gBossCardRequest = 2;
}

u8 func_08083920(void) {
    return GetBossCardValue();
}

void Bosscard_0(BossCardWork* w, u32* a) {
    u8 m;

    w->enemyKind = a[0];
    gBossCardRequest = 2;
    gBossCardRequestValue = GetRandom() % 9;
    w->x = 0x100;
    w->y = 0x84;
    w->flipScale = 0x100;
    w->unk_2F = 1;
    w->unk_30 = 1;
    w->unk_2E = 0;
    w->slideSteps = 8;
    w->flipShrinking = 1;
    w->flipTimer = 0;
    w->flipDelay = GetRandom() % 100;
    w->cardIds = gEnemyCardIds[w->enemyKind];
    w->cardDef = &gCardDefs[w->cardIds[0]];
    w->cardBack = &gEnemyCardBacks[w->cardDef->kind >> 12];
    m = gEnemyCardCounts[w->enemyKind];
    gCardBattleState->nextEnemyCardIndex = GetRandom() % m;
}

u8 Bosscard_1(BossCardWork* w, void* a) {
    s32 v;
    u8 z;

    w->unk_2E += 4;

    if (gCardBattleState->enemyCardUsed == 1) {
        z = 0;
        w->x = 0x100;
        w->slideSteps = 8;
        gCardBattleState->enemyCardUsed = z;
    }

    if (w->slideSteps != 0) {
        v = w->x << 8;
        ApproachValue(&v, 0xDC00, w->slideSteps);
        w->x = v >> 8;
        w->slideSteps--;
    }

    if (gBossCardRequest == 7) {
        w->slideSteps = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08083ADC);
    }

    if (gBossCardRequest == 1) {
        if (FlipBossCard(w, 1) != 0) {
            gBossCardRequest = 0;
        }
    }

    if (gBossCardRequest == 2) {
        if (w->flipTimer == w->flipDelay) {
            if (FlipBossCard(w, 0) != 0) {
                w->flipTimer = 0;
                w->flipDelay = GetRandom() % 100;
            }
        } else {
            w->flipTimer++;
        }
    }

    return 1;
}

s32 func_08083ADC(BossCardWork* w) {
    s32 v;

    if (w->slideSteps != 0) {
        v = w->x << 8;
        ApproachValue(&v, 0x10000, w->slideSteps);
        w->x = v >> 8;
        w->slideSteps--;
    }

    return 1;
}
void Bosscard_2(void) {
}
void Bosscard_3(void) {
}

u8 FlipBossCard(BossCardWork* w, u8 b) {
    if (w->flipShrinking == 1) {
        w->flipScale -= 51;

        if (w->flipScale <= 2) {
            w->flipScale = 2;
            w->flipShrinking = 0;

            if (b == 0) {
                gBossCardRequestValue = GetRandom() % 9 + 1;
            }

            SetBossCardValue(gBossCardRequestValue);
        }
    } else {
        w->flipScale += 51;

        if (w->flipScale > 255) {
            w->flipScale = 256;
            w->flipShrinking = 1;
            return 1;
        }
    }

    return 0;
}

static void card_2(CardDisplayWork* p);

TaskDesc gTaskDescCardBattleRiku = {
    "cardbattle",
    (TaskInitFunc)cardbattle_0,
    (TaskUpdateFunc)cardbattle_1,
    (TaskDrawFunc)cardbattle_2,
    (TaskDestroyFunc)cardbattle_3,
    sizeof(CardBattleWork),
};

TaskDesc gTaskDescCardRiku = {
    "card",
    (TaskInitFunc)RikuCardInit,
    (TaskUpdateFunc)RikuCardUpdate,
    (TaskDrawFunc)card_2,
    (TaskDestroyFunc)RikuCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescNOCard = {
    "NO_Card",
    (TaskInitFunc)RikuCardInit,
    (TaskUpdateFunc)RikuCardUpdate,
    (TaskDrawFunc)NO_Card_2,
    (TaskDestroyFunc)RikuCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescReloadCard = {
    "Reload_Card",
    (TaskInitFunc)Reload_Card_0,
    (TaskUpdateFunc)Reload_Card_1,
    (TaskDrawFunc)Reload_Card_2,
    (TaskDestroyFunc)Reload_Card_3,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescBosscard = {
    "Bosscard",
    (TaskInitFunc)Bosscard_0,
    (TaskUpdateFunc)Bosscard_1,
    (TaskDrawFunc)Bosscard_2,
    (TaskDestroyFunc)Bosscard_3,
    sizeof(BossCardWork),
};
