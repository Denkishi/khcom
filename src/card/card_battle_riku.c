/**
 * card_battle_riku.c
 * Riku Card Battle Interface
 */

#include "macros.h"
#include "registration_data.h"
#include "card_battle.h"
#include "m4a_song.h"
#include <string.h>
#include "fade.h"
#include "obj_api.h"
#include "engine_math.h"
#include "listpool.h"
#include "anim.h"
#include "obj.h"
#include "taskpool.h"
#include "malloc.h"
#include "card.h"
#include "sprites_card.h"
#include "sprites_card_pictures.h"
#include "songs.h"
#include "card_deck_data.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "boss_card_data.h"
#include "card_api.h"
#include "card_def_data.h"
#include "card_label_data.h"
#include "card_types.h"
#include "types.h"
#include "gba/macro.h"
#include <stddef.h>
#include "card_battle_riku.h"
#include "card_map_anim.h"
#include "card_enemy.h"
#include "sprite_palettes.h"
#include "battle_ids.h"

u8 gBossCardRequestValue EWRAM_COMMON(4);

u8 gBossCardRequest EWRAM_COMMON(4);

static u32 sRikuCardRequest;

static u32 sRikuCardReloadRequest;

static CardDisplayWork* sRikuSelectedCard;

#include "riku_deck_names.inc"
static const Deck sRikuDecks[21] = {
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

static const s32 sRikuCardSwingAngles[4] = {
    0xE000, 0x2000, 0x6000, 0xA000,
};

static const s16 sRikuStockValueX[4] = {
    184, 172, 160, 0,
};

static const StockKeys sRikuEmptyKeys = {
    { -1, -1, -1, -1, -1, -1 },
};

void RequestRikuPotion() {
    sRikuCardReloadRequest = CARD_REQUEST_POTION;
}

void RequestRikuHiPotion() {
    sRikuCardReloadRequest = CARD_REQUEST_HI_POTION;
}

void RequestRikuMegaPotion() {
    sRikuCardReloadRequest = CARD_REQUEST_MEGA_POTION;
}

void RequestRikuEther() {
    sRikuCardReloadRequest = CARD_REQUEST_ETHER;
}

void RequestRikuMegaEther() {
    sRikuCardReloadRequest = CARD_REQUEST_MEGA_ETHER;
}

void RequestRikuElixir() {
    sRikuCardReloadRequest = CARD_REQUEST_ELIXIR;
}

void RequestRikuMegalixir() {
    sRikuCardReloadRequest = CARD_REQUEST_MEGALIXIR;
}

void RequestRikuNextCard() {
    sRikuCardRequest = CARD_REQUEST_NEXT_CARD;
}

void RequestRikuPrevCard() {
    sRikuCardRequest = CARD_REQUEST_PREV_CARD;
}

void RequestRikuCardUse() {
    sRikuCardRequest = CARD_REQUEST_USE_CARD;
}

void RequestRikuCardStock() {
    sRikuCardRequest = CARD_REQUEST_STOCK_CARD;
}

void RequestRikuStockUse() {
    sRikuCardRequest = CARD_REQUEST_USE_STOCK;
}

void func_0807E230() {
    sRikuCardRequest = CARD_REQUEST_NOP;
}

void RequestOpenRikuCards() {
    sRikuCardRequest = CARD_REQUEST_OPEN_CARDS;
}

void RequestCloseRikuCards() {
    sRikuCardRequest = CARD_REQUEST_CLOSE_CARDS;
}

void RequestCycleRikuCardList() {
    sRikuCardRequest = CARD_REQUEST_CYCLE_LIST;
}

void RequestSwitchRikuCardList() {
    sRikuCardRequest = CARD_REQUEST_SWITCH_LIST;
}

void RequestRikuAutoCycle60() {
    sRikuCardRequest = CARD_REQUEST_AUTO_CYCLE_60;
}

void RequestRikuAutoCycle180() {
    sRikuCardRequest = CARD_REQUEST_AUTO_CYCLE_180;
}

void RequestRikuAutoCycle300() {
    sRikuCardRequest = CARD_REQUEST_AUTO_CYCLE_300;
}

void ClearRikuCardRequest() {
    sRikuCardRequest = CARD_REQUEST_NONE;
}

u8 IsRikuReloadCardSelected() {
    if (sRikuSelectedCard != NULL) {
        if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            return 1;
        }
    }

    return 0;
}

s32 GetRikuSelectedMove() {
    const CardDef* def;

    if (sRikuSelectedCard != NULL) {
        if (!(sRikuSelectedCard->flags & (CARD_DISP_FLAG_RELOAD_CARD | CARD_DISP_FLAG_RELOAD_GAUGE))) {
            // @bug The opponent's empty slot has no cardDef (NULL read).
            def = sRikuSelectedCard->cardDef;

            if (def->category == 3) {
                return def->move + 0xFFFF;
            }

            return def->move;
        }
    }

    return 145;
}

void SetRikuReloadCharging() {
    // @bug Called before the card battle state exists (NULL write).
    if (sRikuSelectedCard != NULL) {
        if ((sRikuSelectedCard->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_RELOAD_GAUGE)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_RELOAD_GAUGE)) {
            gCardBattleState->rikuReloadCharging = 1;
        } else {
            gCardBattleState->rikuReloadCharging = 0;
        }
    } else {
        gCardBattleState->rikuReloadCharging = 0;
    }
}

u8 GetRikuCardsLeft() {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->rikuCardsLeft;
}

u8 IsRikuSelectionEmpty() {
    if (sRikuSelectedCard != NULL) {
        return sRikuSelectedCard->flags & CARD_DISP_FLAG_NO_CARD;
    }

    return 0;
}

void CreateRikuCardDisplay(CardBattleWork* work, u8 listIndex) {
    CardDisplayArgs args;
    u16 id;
    CardSlot* slot;
    CardDisplayWork* node;
    s16 count;

    count = 0;

    if (work->cursors[listIndex] != 0xFFFF && work->slotCounts[listIndex] > 0) {
        id = work->cursors[listIndex];
        slot = FindNextAvailableSlot(work, listIndex, &id);

        if (slot != NULL) {
            args.pool = &work->cardDisplays[listIndex];
            args.index = id;
            args.listIndex = listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                sRikuSelectedCard = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                sRikuSelectedCard = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
            }

            count++;
        }
    }

    switch (count) {
    case 0:
        args.pool = &work->cardDisplays[listIndex];
        args.index = 0xFFFF;
        args.slot = work->slots[listIndex];
        args.listIndex = listIndex;
        node = TaskCreate(&work->tasks, &gTaskDescNOCard, &args)->work;
        node->swingAngleTarget = node->swingAngle = sRikuCardSwingAngles[0];
        node->ringIndex = 0;
        node->priority = 50;
        node->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_VISIBLE);
        sRikuSelectedCard = node;
        break;
    case 1:
        sRikuSelectedCard->swingAngleTarget = sRikuSelectedCard->swingAngle = sRikuCardSwingAngles[0];
        sRikuSelectedCard->priority = 50;
        sRikuSelectedCard->flags |= CARD_DISP_FLAG_VISIBLE;
        break;
    }
}

void LoadRikuDeckCardSlots(CardBattleWork* work, CardSlot* slots, s8 listIndex, s32 cardCount) {
    const Deck* deck;
    u32 count;

    switch (gBtlWork->battleId) {
    case BATTLE_LEON:
    case BATTLE_TUTORIAL_1:
        deck = &sRikuDecks[20];
        cardCount = deck->cardCount;
        break;
    case BATTLE_HOOK:
        deck = &sRikuDecks[4];
        cardCount = deck->cardCount;
        break;
    case BATTLE_CLOUD:
        deck = &sRikuDecks[1];
        cardCount = deck->cardCount;
        break;
    case BATTLE_HADES:
        deck = &sRikuDecks[2];
        cardCount = deck->cardCount;
        break;
    case BATTLE_RIKU_1:
        deck = &sRikuDecks[5];
        cardCount = deck->cardCount;
        break;
    case BATTLE_AXEL_1:
        deck = &sRikuDecks[0];
        cardCount = deck->cardCount;
        break;
    case BATTLE_LARXENE_1:
        deck = &sRikuDecks[3];
        cardCount = deck->cardCount;
        break;
    case BATTLE_VEXEN_1:
        deck = &sRikuDecks[7];
        cardCount = deck->cardCount;
        break;
    case BATTLE_MARLUXIA:
        deck = &sRikuDecks[13];
        cardCount = deck->cardCount;
        break;
    case BATTLE_ANSEM_1:
        deck = &sRikuDecks[14];
        cardCount = deck->cardCount;
        break;
    case BATTLE_ANSEM_2:
        deck = &sRikuDecks[19];
        cardCount = deck->cardCount;
        break;
    case BATTLE_LEXAEUS:
        deck = &sRikuDecks[17];
        cardCount = deck->cardCount;
        break;
    case BATTLE_RIKU_2:
        deck = &sRikuDecks[6];
        cardCount = deck->cardCount;
        break;
    case BATTLE_RIKU_3:
        deck = &sRikuDecks[9];
        cardCount = deck->cardCount;
        break;
    case BATTLE_RIKU_4:
        deck = &sRikuDecks[10];
        cardCount = deck->cardCount;
        break;
    case BATTLE_RIKU_5:
        deck = &sRikuDecks[16];
        cardCount = deck->cardCount;
        break;
    case BATTLE_RIKU_6:
        deck = &sRikuDecks[18];
        cardCount = deck->cardCount;
        break;
    case BATTLE_AXEL_2:
        deck = &sRikuDecks[12];
        cardCount = deck->cardCount;
        break;
    case BATTLE_LARXENE_2:
        deck = &sRikuDecks[11];
        cardCount = deck->cardCount;
        break;
    case BATTLE_VEXEN_2:
        deck = &sRikuDecks[8];
        cardCount = deck->cardCount;
        break;
    case BATTLE_VEXEN_3:
        deck = &sRikuDecks[15];
        cardCount = deck->cardCount;
        break;
    default:
        deck = GetLinkPartnerDeck();
        cardCount = 99;
        break;
    }

    count = FillCardSlotsFromIds(slots, deck->cards, cardCount, listIndex);

    if (gBtlWork->flags & BTL_FLAG_HUM_BATTLE) {
        ShuffleCardSlots(work->slots[listIndex], count);
    }

    if (listIndex == 0) {
        slots[count].unk_06 = 0;
        slots[count].stocked = 0;
        slots[count].removed = 0;
        slots[count].cardId = CARD_ID_RELOAD;
        slots[count].index = count;
    }
}

u16 FillCardSlotsFromIds(CardSlot* out, const u16* ids, u16 idCount, u8 listIndex) {
    u16 count = 0;
    s32 i;

    for (i = 0; i < idCount; i++) {
        if (ids[i] != 0xFFFF) {
            switch (listIndex) {
            case 0:
                if (gCardDefs[ids[i] & CARD_ID_MASK].category <= 2) {
                    out[count].unk_06 = listIndex;
                    out[count].stocked = listIndex;
                    out[count].removed = listIndex;
                    out[count].cardId = ids[i];
                    out[count].index = count;
                    count++;
                }

                break;
            case 3:
                if (gCardDefs[ids[i] & CARD_ID_MASK].category == 3) {
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

void InitRikuCardList(CardBattleWork* work, s8 idx) {
    u16 n = work->slotCounts[idx];

    if (n != 0) {
        if (idx == 0) {
            CardSlot* slots;
            u8 i;

            slots = EwramAlloc((n + 15) * sizeof(CardSlot));
            work->slots[idx] = slots;
            CpuFill32(0, slots, (n + 15) * sizeof(CardSlot));

            for (i = 0; i < n; i++) {
                work->slots[idx][i].unk_06 = 0;
                work->slots[idx][i].cardId = CARD_ID_NONE;
                work->slots[idx][i].stocked = 0;
                work->slots[idx][i].removed = 0;
                work->slots[idx][i].used = 0;
                work->slots[idx][i].restoreOnReload = 0;
            }

            for (i = n; i < n + 15; i++) {
                work->slots[idx][i].unk_06 = 1;
                work->slots[idx][i].cardId = CARD_ID_NONE;
                work->slots[idx][i].stocked = 1;
                work->slots[idx][i].removed = 1;
                work->slots[idx][i].used = 1;
                work->slots[idx][i].restoreOnReload = 0;
            }
        } else {
            CardSlot* slots;
            u8 i;

            slots = EwramAlloc(n * sizeof(CardSlot));
            work->slots[idx] = slots;
            CpuFill32(0, slots, n * sizeof(CardSlot));

            for (i = 0; i < n; i++) {
                work->slots[idx][i].unk_06 = 0;
                work->slots[idx][i].cardId = CARD_ID_NONE;
                work->slots[idx][i].stocked = 0;
                work->slots[idx][i].removed = 0;
                work->slots[idx][i].used = 0;
                work->slots[idx][i].restoreOnReload = 0;
            }
        }

        LoadRikuDeckCardSlots(work, work->slots[idx], idx, (u16)work->slotCounts[idx]);
        work->cursors[idx] = 0;
    } else {
        CardSlot* slot;
        u16* cursor;
        s32 k;

        slot = EwramAlloc(sizeof(CardSlot));
        work->slots[idx] = slot;
        CpuFill32(0, slot, sizeof(CardSlot));
        work->slots[idx]->cardId = (idx << 12) | 0xFF;
        work->slots[idx]->restoreOnReload = 0;
        cursor = work->cursors;
        cursor += idx;
        k = 0xFFFF;
        *cursor = k;
    }
}

static void cardbattle_0(CardBattleWork* work) {
    u8 i;

    CpuFill32(0, work, sizeof(CardBattleWork));
    gCardBattleState->rikuWork = work;
    work->tiles = AllocSpriteFrameTiles(0x80);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    UpdateSpriteFrameTiles(work->tiles, gStockValueFrames[0], gStockValueTiles);
    TaskPoolInit(&work->tasks, 30);
    work->stockCount = 0;
    work->listIndex = 0;
    work->reloadPending[0] = 0;
    work->reloadPending[1] = 0;
    work->reloadPending[2] = 0;
    work->reloadPending[3] = 0;
    work->revCountShown[0] = 1;
    work->revCountShown[1] = 0;
    work->revCountShown[2] = 0;
    work->revCountShown[3] = 0;
    work->stockValue = 0;
    work->xSteps = 0;
    work->x = sRikuStockValueX[0];

    for (i = 0; i <= 2; i++) {
        work->playedCards[i] = NULL;
        work->stock[i] = NULL;
    }

    for (i = 0; i <= 3; i++) {
        work->selectedCards[i] = NULL;
        work->slots[i] = NULL;
    }

    work->stockNameChecked = 0;
    ListPoolInit(&work->cardDisplays[0]);
    ListPoolInit(&work->cardDisplays[1]);
    ListPoolInit(&work->cardDisplays[2]);
    ListPoolInit(&work->cardDisplays[3]);

    switch (gBtlWork->battleId) {
    case BATTLE_LEON:
    case BATTLE_TUTORIAL_1:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[20]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[20]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_HOOK:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[4]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[4]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_CLOUD:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[1]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[1]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_HADES:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[2]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[2]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_RIKU_1:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[5]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[5]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_AXEL_1:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[0]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[0]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_LARXENE_1:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[3]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[3]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_VEXEN_1:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[7]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[7]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_MARLUXIA:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[13]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[13]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_ANSEM_1:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[14]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[14]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_ANSEM_2:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[19]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[19]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_LEXAEUS:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[17]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[17]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_RIKU_2:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[6]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[6]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_RIKU_3:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[9]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[9]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_RIKU_4:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[10]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[10]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_RIKU_5:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[16]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[16]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_RIKU_6:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[18]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[18]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_AXEL_2:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[12]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[12]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_LARXENE_2:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[11]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[11]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_VEXEN_2:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[8]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[8]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    case BATTLE_VEXEN_3:
        work->slotCounts[0] = work->cardsLeft[0] = CountDeckCards(0, &sRikuDecks[15]) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountDeckCards(1, &sRikuDecks[15]);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    default:
        work->slotCounts[0] = work->cardsLeft[0] = CountLinkPartnerDeckCards(0) + 1;
        work->slotCounts[3] = work->cardsLeft[3] = CountLinkPartnerDeckCards(3);
        InitRikuCardList(work, 0);
        InitRikuCardList(work, 3);
        break;
    }

    work->reloadCounts[0] = 0;
    work->reloadCounts[1] = 0;
    work->reloadCounts[2] = 0;
    work->cursors[0] = 0;
    work->cursors[1] = 0;
    work->cursors[2] = 0;
    work->cursors[3] = 0;
    sRikuSelectedCard = NULL;
    CreateRikuCardDisplay(work, work->listIndex);
    sRikuCardRequest = CARD_REQUEST_NONE;
    gCardBattleState->rikuListIndex = work->listIndex;
}

static u8 cardbattle_1(CardBattleWork* work, void* task) {
    StockKeys stockKeys;
    u8 flag[4];
    StockKeys cards;
    u8 output[6];
    s32 hold;
    ReloadArgs args;
    s32 done;
    u32 stockName;
    u32 flags;
    CardDisplayWork* selected;
    u16 result;
    u8 i;
    u8 slot;

    if (gBtlWork->phase == BTL_PHASE_END) {
        if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        return 0;
    }

    if (work->xSteps != 0) {
        hold = work->x << 8;
        ApproachValue(&hold, sRikuStockValueX[work->stockCount - 1] << 8, work->xSteps);
        work->x = hold >> 8;
        work->xSteps--;
    }

    if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
        if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_DONE) {
            if (gRikuBtlWork->hcEffect == HC_EFFECT_QUICKLOAD) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
                sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;

                if (gRikuBtlWork->hcEffect != HC_EFFECT_DRAW_2) {
                    IncrementReloadCount(work);

                    if (gRikuBtlWork->hcEffect == HC_EFFECT_COMBO_PLUS_2) {
                        work->reloadCounts[work->listIndex] -= 2;

                        if (work->reloadCounts[work->listIndex] < 0) {
                            work->reloadCounts[work->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->rikuReloadCounter = work->reloadCounts[work->listIndex];
                gCardBattleState->rikuReloadGauge = 0;
                gCardBattleState->rikuGaugeFullFrame = 4;
                TaskPoolUpdate(&work->tasks);
                ResetCardSlotsForReload(work, 0);
                work->cursors[0] = 0;
                work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
                CreateRikuCardDisplay(work, 0);
                TickRikuHcEffectOnReload();
            } else {
                sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;

                if (gRikuBtlWork->hcEffect != HC_EFFECT_DRAW_2) {
                    IncrementReloadCount(work);

                    if (gRikuBtlWork->hcEffect == HC_EFFECT_COMBO_PLUS_2) {
                        work->reloadCounts[work->listIndex] -= 2;

                        if (work->reloadCounts[work->listIndex] < 0) {
                            work->reloadCounts[work->listIndex] = 0;
                        }
                    }
                }

                gCardBattleState->rikuReloadCounter = work->reloadCounts[work->listIndex];
                gCardBattleState->rikuReloadGauge = 0;
                gCardBattleState->rikuGaugeFullFrame = 4;
                ClearUsedCardSlots(work, 0);
                work->cursors[work->listIndex] = 0;
                work->cardsLeft[work->listIndex] = 0;
                work->reloadPending[work->listIndex] = 1;
                sRikuSelectedCard = NULL;
                sRikuCardRequest = CARD_REQUEST_NONE;
                work->revCountShown[work->listIndex] = 0;
            }
        }
    }

    switch (sRikuCardRequest) {
    case CARD_REQUEST_NONE:
        break;
    case CARD_REQUEST_NEXT_CARD:
        sRikuCardRequest = CARD_REQUEST_NONE;

        if (sRikuSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
            SelectNextRikuCard(work, work->listIndex);
        }

        break;
    case CARD_REQUEST_PREV_CARD:
        sRikuCardRequest = CARD_REQUEST_NONE;

        if (sRikuSelectedCard->flags & CARD_DISP_FLAG_SETTLED) {
            SelectPrevRikuCard(work, work->listIndex);
        }

        break;
    case CARD_REQUEST_STOCK_CARD:
        sRikuCardRequest = CARD_REQUEST_NONE;
        selected = sRikuSelectedCard;
        flags = selected->flags;

        if (!(flags & CARD_DISP_FLAG_RELOAD_CARD)) {
            if (work->stockCount == 3) {
                UseRikuStock(work);
            } else if (selected->cardDef->category == 3) {
#ifndef VERSION_EU
                m4aSongNumStart(SONG_SYS_BEEP);
#endif
            } else if (work->reloadPending[work->listIndex] == 0) {
                if (!(flags & CARD_DISP_FLAG_NO_CARD)) {
                    if (CanUseRikuSelectedCard()) {
                        if (work->stockCount <= 2 && !gCardBattleState->rikuStockActive) {
                            StockRikuCard(work);
                        }
                    } else if (sRikuSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_BEEP);
#endif
                    }
                } else if (flags & CARD_DISP_FLAG_OPEN) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_BEEP);
#endif
                }
            }
        } else if (work->stockCount != 0) {
            UseRikuStock(work);
        } else {
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_BEEP);
#endif
        }

        break;
    case CARD_REQUEST_USE_CARD:
        sRikuCardRequest = CARD_REQUEST_NONE;

        if (sRikuSelectedCard->cardDef->category != 3) {
            if (!(sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) && work->reloadPending[work->listIndex] == 0) {
                if (!(sRikuSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
                    if (CanUseRikuSelectedCard()) {
                        UseRikuCard(work);
                    } else if (sRikuSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_BEEP);
#endif
                    }
                } else if (sRikuSelectedCard->flags & CARD_DISP_FLAG_OPEN) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_BEEP);
#endif
                }
            }
        } else if (!(sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD)) {
            UseRikuHeartlessCard(work);
        }

        break;
    case CARD_REQUEST_USE_STOCK:
        sRikuCardRequest = CARD_REQUEST_NONE;

        if (work->stockCount != 0) {
            UseRikuStock(work);
        } else if (!(gBtlWork->flags & BTL_FLAG_CARD_ACTIVE)) {
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_BEEP);
#endif
        }

        break;
    case CARD_REQUEST_OPEN_CARDS:
        sRikuCardRequest = CARD_REQUEST_NONE;
        OpenRikuCards(work);
        break;
    case CARD_REQUEST_CLOSE_CARDS:
        work->revCountShown[work->listIndex] = 0;
        work->reloadShown = 0;
        CloseRikuCards(work);
        break;
    case CARD_REQUEST_NOP:
        sRikuCardRequest = CARD_REQUEST_NONE;
        break;
    case CARD_REQUEST_CYCLE_LIST:
        sRikuCardRequest = CARD_REQUEST_NONE;
        CycleRikuCardList(work);
        break;
    case CARD_REQUEST_SWITCH_LIST:
        sRikuCardRequest = CARD_REQUEST_NONE;
        SwitchRikuCardList(work);
        break;
    default:
        sRikuCardRequest = CARD_REQUEST_NONE;
        break;
    }

    switch (sRikuCardReloadRequest) {
    case CARD_REQUEST_POTION:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForPotion(work);

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    case CARD_REQUEST_HI_POTION:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForHiPotion(work);

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    case CARD_REQUEST_MEGA_POTION:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForMegaPotion(work);
        ResetRikuReloadGauge(work);
        work->reloadCounts[0] = 0;

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    case CARD_REQUEST_ETHER:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForEther(work);

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    case CARD_REQUEST_MEGA_ETHER:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForMegaEther(work);
        ResetRikuReloadGauge(work);
        work->reloadCounts[0] = 0;

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    case CARD_REQUEST_ELIXIR:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForElixir(work);

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    case CARD_REQUEST_MEGALIXIR:
        sRikuCardReloadRequest = CARD_REQUEST_NONE;
        RestoreCardsForElixir(work);
        ResetRikuReloadGauge(work);
        work->reloadCounts[0] = 0;

        if (work->listIndex == 0) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        } else {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_GAUGE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
            }

            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            work->listIndex = 0;
#ifdef VERSION_EU
            gCardBattleState->rikuListIndex = 0;
#endif
        }

        TaskPoolUpdate(&work->tasks);
        ClearUsedCardSlots(work, 0);
        work->cursors[0] = 0;
        work->cardsLeft[0] = CountAvailableCardSlots(work, 0);
        CreateRikuCardDisplay(work, 0);
        TickRikuHcEffectOnReload();
        break;
    }

    if (work->reloadPending[work->listIndex] != 0) {
        if (sRikuSelectedCard != NULL) {
            if (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_DONE) {
                sRikuSelectedCard->flags |= CARD_DISP_FLAG_REMOVE;
                BeginRikuReloadDeal(work);
                work->reloadPending[work->listIndex] = 0;
                work->reloadShown = 1;
                gRikuBtlWork->flags |= BTL_FLAG_RELOADING;
                SetTaskUpdate(task, (TaskUpdateFunc)UpdateRikuReloadDeal);
                sRikuSelectedCard->flags = (sRikuSelectedCard->flags | (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_VISIBLE)) & ~CARD_DISP_FLAG_FROZEN;
                TaskPoolUpdate(&work->tasks);
#ifndef VERSION_EU
                m4aSongNumStart(SONG_SYS_RELOAD);
#endif
                slot = work->listIndex;
                args.slot = slot;
                args.state = &work->reloadShown;
                args.mode = 2;
                TaskCreate(&work->tasks, &gTaskDescRELOAD, &args);
                return 1;
            }
        } else {
            BeginRikuReloadDeal(work);
            work->reloadPending[work->listIndex] = 0;
            gRikuBtlWork->flags |= BTL_FLAG_RELOADING;
            SetTaskUpdate(task, (TaskUpdateFunc)UpdateRikuReloadDeal);
            sRikuSelectedCard->flags = (sRikuSelectedCard->flags | (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_VISIBLE)) & ~CARD_DISP_FLAG_FROZEN;
            TaskPoolUpdate(&work->tasks);
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_RELOAD);
#endif
            return 1;
        }
    } else if (sRikuSelectedCard != NULL && (sRikuSelectedCard->flags & (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SETTLED) &&
               CountAvailableCardSlots(work, work->listIndex) != 0) {
        work->reloadPending[work->listIndex] = 1;
        work->cardsLeft[0] = 0;
        sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;

        if (gRikuBtlWork->hcEffect != HC_EFFECT_AUTO_RELOAD) {
            if (gRikuBtlWork->actor->hp > 3) {
                gRikuBtlWork->actor->hp -= 2;
            }

            work->selectedCards[work->listIndex] = NULL;
            sRikuSelectedCard = NULL;

            if (gRikuBtlWork->hcEffect != HC_EFFECT_DRAW_2) {
                IncrementReloadCount(work);

                if (gRikuBtlWork->hcEffect == HC_EFFECT_COMBO_PLUS_2) {
                    work->reloadCounts[work->listIndex] -= 2;

                    if (work->reloadCounts[work->listIndex] < 0) {
                        work->reloadCounts[work->listIndex] = 0;
                    }
                }
            }

#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

            if (FadeGetAmount() == 0) {
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
            }
        } else {
            work->selectedCards[work->listIndex] = NULL;
            sRikuSelectedCard = NULL;
            work->reloadPending[work->listIndex] = 1;
            work->cardsLeft[0] = 0;
        }
    }

    if (work->stockNameChecked == 0 && AreCardsSettled(work->stock, work->stockCount)) {
        stockKeys = sRikuEmptyKeys;

        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            result = LookupStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, flag);
        } else {
            result = LookupLinkStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, flag, 1);
        }

        gCardBattleState->rikuStockName = result;

        if (result <= 105) {
            for (i = 0; i < work->stockCount; i++) {
                work->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
            }

            if (!gCardBattleState->rikuStockNameShown) {
                TaskCreate(&work->tasks, &gTaskDescStockNameRiku, NULL);
                gCardBattleState->rikuStockNameShown = 1;
            }
        } else {
            if (work->stockCount == 3) {
                cards = sRikuEmptyKeys;
                memset(output, 0, 6);
                done = 0;

                for (i = 0; i < work->stockCount; i++) {
                    cards.keys[i] = work->stock[i]->cardDef->catalogNumber;
                }

                stockName = LookupStockPairName(&cards, output, work->stockCount);

                switch (stockName) {
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
                    gCardBattleState->rikuStockName = stockName;
                    done = 1;
                    break;
                }

                if (!done) {
                    for (i = 0; i < work->stockCount; i++) {
                        work->stock[i]->flags &= ~CARD_DISP_FLAG_STOCK_NAMED;
                    }

                    if (gCardBattleState->rikuStockNameShown) {
                        gCardBattleState->rikuStockNameShown = 0;
                    }
                } else {
                    for (i = 0; i < work->stockCount; i++) {
                        work->stock[i]->flags |= CARD_DISP_FLAG_STOCK_NAMED;
                    }

                    if (!gCardBattleState->rikuStockNameShown) {
                        TaskCreate(&work->tasks, &gTaskDescStockNameRiku, NULL);
                        gCardBattleState->rikuStockNameShown = 1;
                    }
                }
            }
        }

        work->stockNameChecked = 1;
    }

    gCardBattleState->rikuCardsLeft = work->cardsLeft[work->listIndex];
    TaskPoolUpdate(&work->tasks);
    gCardBattleState->rikuStockCount = work->stockCount;
    return 1;
}

static void cardbattle_2(CardBattleWork* work) {
    if (gCardBattleState->cardsOpen && gRikuBtlWork->hcEffect != HC_EFFECT_SLEIGHTBLIND && work->stockCount != 0 && work->stockValue != 0) {
        DrawSprite(work->x, 4, gStockValueFrames[0], work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC, 12);
    }

    TaskPoolDraw(&work->tasks);
}

static void cardbattle_3(CardBattleWork* work) {
    u8 i;

    TaskPoolDestroy(&work->tasks);

    for (i = 0; i <= 3; i++) {
        if (work->slots[i] != NULL) {
            EwramFree(work->slots[i]);
        }
    }

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void CloseRikuCards(CardBattleWork* work) {
    u8 i;

    for (i = 0; i < work->stockCount; i++) {
        work->stock[i]->flags &= ~CARD_DISP_FLAG_OPEN;
    }

    if (sRikuSelectedCard != NULL) {
        sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_OPEN;
    }

    gCardBattleState->soraHcEffect = HC_EFFECT_NONE;
    gBtlWork->flags |= BTL_FLAG_CARD_PLAY_ENDED;
    gCardBattleState->cardsOpen = 0;
    gCardBattleState->rikuStockNameShown = 0;
    work->cardsClosed = 1;
}

void OpenRikuCards(CardBattleWork* work) {
    u8 i;

    for (i = 0; i < work->stockCount; i++) {
        work->stock[i]->flags |= CARD_DISP_FLAG_OPEN;
    }

    if (sRikuSelectedCard != NULL) {
        sRikuSelectedCard->flags |= CARD_DISP_FLAG_OPEN;
    }

    gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
    gCardBattleState->cardsOpen = 1;
    work->cardsClosed = 0;
}

u8 UpdateRikuReloadDeal(CardBattleWork* work, void* task) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardSlot* slot;
    u16 index;

    if (gBtlWork->phase == BTL_PHASE_END) {
        if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        m4aSongNumStop(SONG_SYS_RELOAD);
        return 0;
    }

    if ((s16)sRikuSelectedCard->timer == 0) {
        if (CountAvailableCardSlots(work, work->listIndex) > work->dealtCount) {
            sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
            index = sRikuSelectedCard->args.index - 1;
            slot = FindPrevAvailableSlot(work, work->listIndex, &index);

            if (slot != NULL) {
                args.pool = &work->cardDisplays[work->listIndex];
                args.index = index;
                args.listIndex = work->listIndex;
                args.slot = slot;
                card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
                card->ringAngleTarget = card->ringAngle = 0;
                card->priority = 50;
                card->timer = 8;
                card->x = card->ringCenterX;
                card->y = card->ringCenterY;
                card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_VISIBLE);
                sRikuSelectedCard = card;
                work->dealtCount++;
                work->cardsLeft[work->listIndex]++;
            }
        } else {
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOADING;
            gRikuBtlWork->flags &= ~0x100;
            work->reloadShown = 0;
            m4aSongNumStop(SONG_SYS_RELOAD);
            sRikuCardRequest = CARD_REQUEST_NONE;
            SetTaskUpdate(task, (TaskUpdateFunc)cardbattle_1);
        }
    }

    if (sRikuCardRequest == CARD_REQUEST_CLOSE_CARDS) {
        work->revCountShown[work->listIndex] = 0;
        work->reloadShown = 0;
        CloseRikuCards(work);
        m4aSongNumStop(SONG_SYS_RELOAD);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void SelectNextRikuCard(CardBattleWork* work, u8 listIndex) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardSlot* slot;
    u16 index;

    if (!(sRikuSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
        if (work->cardsLeft[work->listIndex] != 1) {
            sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
            sRikuSelectedCard->timer = 4;
            index = sRikuSelectedCard->args.index + 1;

            if ((s16)index >= work->slotCounts[listIndex]) {
                index = 0;
            }

            slot = FindNextAvailableSlot(work, listIndex, &index);

            if (slot != NULL) {
                args.pool = &work->cardDisplays[listIndex];
                args.index = index;
                args.listIndex = listIndex;
                args.slot = slot;
                args.reloadCount = work->reloadCounts[listIndex];

                if (slot->cardId == CARD_ID_RELOAD) {
                    card = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
                } else {
                    card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
                }

                card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
                card->ringIndex = 0;
                card->priority = 60;
                card->timer = 4;
                card->x = card->ringCenterX;
                card->y = card->ringCenterY;
                card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
                sRikuSelectedCard = card;
            }
        }
    }
}

void SelectPrevRikuCard(CardBattleWork* work, u8 listIndex) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardSlot* slot;
    u16 index;

    if (!(sRikuSelectedCard->flags & CARD_DISP_FLAG_NO_CARD)) {
        if (work->cardsLeft[work->listIndex] != 1) {
            sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
            sRikuSelectedCard->scaleX = 0;
            sRikuSelectedCard->timer = 4;
            index = sRikuSelectedCard->args.index - 1;

            if ((s16)index < 0) {
                index = work->slotCounts[listIndex] - 1;
            }

            slot = FindPrevAvailableSlot(work, listIndex, &index);

            if (slot != NULL) {
                args.pool = &work->cardDisplays[listIndex];
                args.index = index;
                args.listIndex = listIndex;
                args.slot = slot;
                args.reloadCount = work->reloadCounts[listIndex];

                if (slot->cardId == CARD_ID_RELOAD) {
                    card = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
                } else {
                    card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
                }

                card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
                card->ringIndex = 0;
                card->priority = 60;
                card->timer = 4;
                card->x = card->ringCenterX;
                card->y = card->ringCenterY;
                card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
                sRikuSelectedCard = card;
            }
        }
    }
}

void SwitchRikuCardList(CardBattleWork* work) {
    if ((sRikuSelectedCard->flags & CARD_DISP_FLAG_SETTLED) != 0) {
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CANSEL);
#endif

        if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }

        work->revCountShown[work->listIndex] = 0;

        if (work->reloadPending[work->listIndex] == 0) {
            work->cursors[work->listIndex] = sRikuSelectedCard->args.index;
            sRikuSelectedCard->ringCenterX = 0x10400;
            sRikuSelectedCard->ringCenterY = 0x8C00;
            sRikuSelectedCard->timer = 4;
            sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
            sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
        } else {
            work->selectedCards[work->listIndex] = sRikuSelectedCard;
            sRikuSelectedCard->swingAngleTarget = sRikuCardSwingAngles[3];
            sRikuSelectedCard->swingSteps = 4;
            sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
        }

        switch (work->listIndex) {
        case 0:
            work->listIndex = 3;
            break;
        case 3:
            work->listIndex = 0;
            break;
        }

        if (work->reloadPending[work->listIndex] == 0) {
            CreateRikuCardDisplay(work, work->listIndex);
            sRikuSelectedCard->x = gRikuCardLayout[5][0];
            sRikuSelectedCard->y = gRikuCardLayout[5][1];
            sRikuSelectedCard->swingSteps = 1;
            sRikuSelectedCard->timer = 1;
        } else {
            sRikuSelectedCard = work->selectedCards[work->listIndex];
            sRikuSelectedCard->swingAngleTarget = sRikuCardSwingAngles[0];
            sRikuSelectedCard->swingAngle = sRikuSelectedCard->swingAngleTarget;
            sRikuSelectedCard->swingSteps = 1;
            sRikuSelectedCard->timer = 1;
            sRikuSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
        }

        gCardBattleState->rikuListIndex = work->listIndex;
    }
}

void CycleRikuCardList(CardBattleWork* work) {
#ifndef VERSION_EU
    m4aSongNumStart(SONG_SYS_CANSEL);
#endif

    if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    work->revCountShown[work->listIndex] = 0;

    if (work->reloadPending[work->listIndex] == 0) {
        work->cursors[work->listIndex] = sRikuSelectedCard->args.index;
        sRikuSelectedCard->ringCenterX = 0xC800;
        sRikuSelectedCard->ringCenterY = 0xB400;
        sRikuSelectedCard->timer = 12;
        sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    } else {
        work->selectedCards[work->listIndex] = sRikuSelectedCard;
        sRikuSelectedCard->swingAngleTarget = sRikuCardSwingAngles[3];
        sRikuSelectedCard->swingSteps = 12;
        sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SELECTED;
    }

    switch (work->listIndex) {
    case 0:
        work->listIndex = 3;
        break;
    case 1:
        work->listIndex = 0;
        break;
    case 2:
        work->listIndex = 3;
        break;
    case 3:
        work->listIndex = 0;
        break;
    }

    if (work->reloadPending[work->listIndex] == 0) {
        CreateRikuCardDisplay(work, work->listIndex);
        sRikuSelectedCard->x = 0x10400;
        sRikuSelectedCard->y = 0x8C00;
        sRikuSelectedCard->timer = 12;
    } else {
        sRikuSelectedCard = work->selectedCards[work->listIndex];
        sRikuSelectedCard->swingAngleTarget = sRikuCardSwingAngles[0];
        sRikuSelectedCard->swingAngle = sRikuCardSwingAngles[1];
        sRikuSelectedCard->swingSteps = 12;
        sRikuSelectedCard->timer = 12;
        sRikuSelectedCard->flags |= CARD_DISP_FLAG_SELECTED;
    }

    gCardBattleState->rikuListIndex = work->listIndex;
}

void ApplyTrickmasterToRikuCard(CardBattleWork* work) {
    if (gBtlWork->hcEffect == HC_EFFECT_VALUE_BREAK) {
        if (sRikuSelectedCard->value != 0) {
            sRikuSelectedCard->value -= gCardBattleState->activeValue;
        }

        gBtlWork->hcEffectCount--;
    }
}

void ApplyTrickmasterToRikuStock(CardBattleWork* work) {
    CardDisplayWork* card;
    u8 dmg;
    u8 i;
    u16 remaining;

    dmg = gCardBattleState->activeValue;

    if (gBtlWork->hcEffect == HC_EFFECT_VALUE_BREAK) {
        if (work->stockValue != 0) {
            for (i = 0; i < 3; i++) {
                card = work->stock[i];

                if (card->value > dmg) {
                    card->value -= dmg;
                    break;
                }

                remaining = dmg - card->value;
                card->value = 0;
                dmg = remaining;
            }
        }

        gBtlWork->hcEffectCount--;
    }
}

void TryRikuCardBreak(CardBattleWork* work) {
#ifdef VERSION_EU
    s32 i;
#endif
    s32 hcEffect;
    s32 j;
    u32 valueToRaise;
    s32 valueToLower;
    u8 n;
    u8 flag;

    hcEffect = gRikuBtlWork->hcEffect;

    if (hcEffect == 1) {
        valueToRaise = sRikuSelectedCard->value;
        n = valueToRaise + 1;

        if (n > 9) {
            n = 9;
        }

        if (valueToRaise <= 8) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &sRikuSelectedCard->cardDef);
        }

        sRikuSelectedCard->value = n;
        sRikuSelectedCard->valueModified = 1;
    } else if (hcEffect == 21) {
        valueToLower = sRikuSelectedCard->value;

        if (valueToLower != 0) {
            n = valueToLower - 1;
            sRikuSelectedCard->value = valueToLower - 1;
            sRikuSelectedCard->valueModified = 1;
        } else {
            n = 0;
            sRikuSelectedCard->valueModified = 1;
        }
    } else {
        n = sRikuSelectedCard->value;
    }

    if (gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    flag = 0;

    if (gBtlWork->hcEffect == HC_EFFECT_ATTACK_BRACER && gCardBattleState->activeCards[0]->cardDef->category == 0 && !gCardBattleState->soraStockActive) {
        flag = 1;
    }

#ifdef VERSION_EU
    if (gBtlWork->hcEffect == HC_EFFECT_LEAF_BRACER) {
        for (i = 0; i < gCardBattleState->activeCardCount; i++) {
            if (gCardBattleState->activeCards[i]->cardDef->move == 22) {
                flag = 1;
            }
        }
    }

    if (gBtlWork->hcEffect == HC_EFFECT_ITEM_BRACER) {
        for (j = 0; j < gCardBattleState->activeCardCount; j++) {
            if (gCardBattleState->activeCards[j]->cardDef->category == 2 && !(gCardBattleState->activeCards[j]->cardDef->flags & CARD_DEF_FLAG_FRIEND)) {
                flag = 1;
            }
        }
    }
#else
    if (gBtlWork->hcEffect == HC_EFFECT_LEAF_BRACER && gCardBattleState->activeCards[0]->cardDef->move == 22 && !gCardBattleState->soraStockActive) {
        flag = 1;
    }

    if (gBtlWork->hcEffect == HC_EFFECT_ITEM_BRACER && gCardBattleState->activeCards[0]->cardDef->category == 2 && !gCardBattleState->soraStockActive) {
        flag = 1;
    }
#endif

    if (flag) {
        return;
    }

    for (j = 0; j < gCardBattleState->activeCardCount; j++) {
        gCardBattleState->activeCards[j]->flags |= CARD_DISP_FLAG_BROKEN;
    }

    gBtlWork->flags |= BTL_FLAG_CARD_BREAK;

    if (gCardBattleState->activeValue != n) {
        if (n == 0) {
            if (gCardBattleState->activeValue > 9) {
                gBtlWork->breakDifference = 9;
            } else {
                gBtlWork->breakDifference = gCardBattleState->activeValue;
            }
        } else {
            gBtlWork->breakDifference = (u8)gCardBattleState->activeValue - n;

            if (gBtlWork->breakDifference < -9) {
                gBtlWork->breakDifference = -9;
            }
        }

        m4aSongNumStart(SONG_BTL_GARD);
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        sRikuSelectedCard->flags |= CARD_DISP_FLAG_IN_PLAY;
        ApplyTrickmasterToRikuCard(work);
        gCardBattleState->activeCards[0] = sRikuSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = sRikuSelectedCard->value;
        gBtlWork->soraOwnsPlay = 0;
        AddBreakDarkPoints();
    } else {
        ApplyTrickmasterToRikuCard(work);
        gBtlWork->breakDifference = 0;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->soraOwnsPlay = 0;
        gCardBattleState->activeCards[0] = sRikuSelectedCard;
        gCardBattleState->activeCardCount = 1;
        gCardBattleState->activeValue = sRikuSelectedCard->value;
    }
}

u8 UseRikuCard(CardBattleWork* work) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardSlot* slot;
    u16 index;
    u16 hcEffect;

    if ((gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) == 0) {
        gCardBattleState->activeCards[0] = sRikuSelectedCard;

        if (gRikuBtlWork->hcEffect == HC_EFFECT_INCREMENTOR) {
            gCardBattleState->activeValue = sRikuSelectedCard->value + 1;
            sRikuSelectedCard->value++;
            sRikuSelectedCard->valueModified = 1;

            if (sRikuSelectedCard->value > 9) {
                sRikuSelectedCard->value = 9;
            }

            if (gCardBattleState->activeValue > 9) {
                gCardBattleState->activeValue = 9;
            }

            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &sRikuSelectedCard->cardDef);
        } else if (gRikuBtlWork->hcEffect == HC_EFFECT_DECREMENTOR) {
            if (sRikuSelectedCard->value != 0) {
                gCardBattleState->activeValue = sRikuSelectedCard->value - 1;
                sRikuSelectedCard->value--;
                sRikuSelectedCard->valueModified = 1;
            } else {
                gCardBattleState->activeValue = 0;
                sRikuSelectedCard->valueModified = 1;
            }
        } else {
            gCardBattleState->activeValue = sRikuSelectedCard->value;
        }

        gCardBattleState->activeCardCount = 1;
        sRikuSelectedCard->flags |= CARD_DISP_FLAG_IN_PLAY;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_BUSY;
    } else {
        if (!gBtlWork->soraOwnsPlay) {
            sRikuSelectedCard->command = CARD_DISP_COMMAND_NONE;
            return 1;
        }

        if ((gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) == 0) {
            TryRikuCardBreak(work);
        } else {
            TryRikuCardBreak(work);
        }

        gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_BUSY;
    }

    work->cardsLeft[work->listIndex]--;

    if ((sRikuSelectedCard->cardDef->flags & CARD_DEF_FLAG_ITEM) && (sRikuSelectedCard->flags & CARD_DISP_FLAG_IN_PLAY)) {
        sRikuSelectedCard->args.slot->removed = 1;
    }

    if (sRikuSelectedCard->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        sRikuSelectedCard->args.slot->removed = 1;
    }

    if (sRikuSelectedCard->premium == 1) {
        sRikuSelectedCard->args.slot->removed = 1;

        if (CountRemainingAttackCards(work, 0) == 0) {
            sRikuSelectedCard->args.slot->removed = 0;
        }
    }

    work->playedCards[0] = sRikuSelectedCard;
    sRikuSelectedCard->command = CARD_DISP_COMMAND_PLAY;
    sRikuSelectedCard->priority = 50;
    sRikuSelectedCard->args.slot->used = 1;
    index = sRikuSelectedCard->args.index + 1;

    if ((s16)index >= work->slotCounts[work->listIndex]) {
        index = 0;
    }

    // fakematch
    do {
        TickRikuHcEffectOnCardUse();
    } while (0);

    if (gRikuBtlWork->hcEffect == HC_EFFECT_RANDOM_FLUSH) {
        hcEffect = GetRandomHcEffect();
        SyncRikuHcEffect(work);
        gCardBattleState->rikuHcEffect = hcEffect;
        func_08081740(work, gCardBattleState->rikuHcEffect);
        ApplyRikuHcEffect(work);
        gRikuBtlWork->hcEffectCount = gHcEffectDefs[gRikuBtlWork->hcEffect].count;
    }

    sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    sRikuSelectedCard = NULL;
    slot = FindNextAvailableSlot(work, work->listIndex, &index);

    if (slot != NULL) {
        args.pool = &work->cardDisplays[work->listIndex];
        args.index = index;
        args.listIndex = work->listIndex;
        args.slot = slot;
        args.reloadCount = work->reloadCounts[work->listIndex];

        if (slot->cardId == CARD_ID_RELOAD) {
            card = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
        } else {
            card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
        }

        card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
        card->ringIndex = 0;
        card->priority = 60;
        card->timer = 4;
        card->x = card->ringCenterX;
        card->y = card->ringCenterY;
        card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        sRikuSelectedCard = card;
    }

    if (gRikuBtlWork->hcEffect == HC_EFFECT_AUTO_RELOAD && (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) &&
        work->cardsLeft[work->listIndex] == 1) {
        work->cardsLeft[work->listIndex] = 0;
        sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        work->selectedCards[work->listIndex] = NULL;
        sRikuSelectedCard = NULL;
        work->reloadPending[0] = 1;

#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }
    }

    return 1;
}

void BeginRikuReloadDeal(CardBattleWork* work) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardDisplayWork* noCard;
    CardSlot* slot = NULL;
    u16 index;

    work->dealtCount = 0;
    ResetCardSlotsForReload(work, work->listIndex);

    if (CountAvailableCardSlots(work, work->listIndex) != 0) {
        index = work->slotCounts[work->listIndex] - 1;
        slot = FindPrevAvailableSlot(work, work->listIndex, &index);

        if (slot != NULL) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = index;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
            }

            card->ringAngleTarget = card->ringAngle = 0;
            card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
            card->ringIndex = 0;
            card->priority = 50;
            card->x = card->ringCenterX;
            card->y = card->ringCenterY;
            card->timer = 8;
            card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_DEALING | CARD_DISP_FLAG_VISIBLE);
            sRikuSelectedCard = card;
            work->dealtCount++;
            work->cardsLeft[work->listIndex]++;
        }
    } else {
        args.pool = &work->cardDisplays[work->listIndex];
        args.index = 0xFFFF;
        args.slot = work->slots[work->listIndex];
        args.listIndex = work->listIndex;
        noCard = TaskCreate(&work->tasks, &gTaskDescNOCard, &args)->work;
        noCard->ringAngleTarget = noCard->ringAngle = 0;
        noCard->swingAngleTarget = noCard->swingAngle = sRikuCardSwingAngles[0];
        noCard->x = noCard->ringCenterX;
        noCard->y = noCard->ringCenterY;
        noCard->priority = 50;
        noCard->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        sRikuSelectedCard = noCard;
    }

    TickRikuHcEffectOnReload();
}

u8 StockRikuCard(CardBattleWork* work) {
    CardDisplayArgs args;
    u16 hcEffect;
    u8 n;
    CardSlot* slot;
    CardDisplayWork* card;
    u16 index;

    if (!(sRikuSelectedCard->flags & CARD_DISP_FLAG_SETTLED)) {
        return 1;
    }

    if (sRikuSelectedCard->flags & CARD_DISP_FLAG_NO_CARD) {
        return 1;
    }

    if (gCardBattleState->unk_0B0 == 112) {
        return 1;
    }

    if (gCardBattleState->unk_0B0 == 109) {
        return 1;
    }

    work->stockNameChecked = 0;
    gCardBattleState->rikuStockNameShown = 0;
#ifndef VERSION_EU
    m4aSongNumStart(SONG_SYS_KETEI2);
#endif
    sRikuSelectedCard->flags = (sRikuSelectedCard->flags & ~CARD_DISP_FLAG_SETTLED) | CARD_DISP_FLAG_STOCKED;
    sRikuSelectedCard->command = CARD_DISP_COMMAND_STOCK;
    sRikuSelectedCard->stockIndex = work->stockCount;
    sRikuSelectedCard->priority = (3 - work->stockCount) * 4 + 50;
    work->stock[work->stockCount] = sRikuSelectedCard;
    gCardBattleState->rikuStockedCards[gCardBattleState->rikuStockedCount] = sRikuSelectedCard;
    sRikuSelectedCard->args.slot->stocked = 1;

    if (gRikuBtlWork->hcEffect == HC_EFFECT_INCREMENTOR) {
        n = sRikuSelectedCard->value + 1;

        if (n > 9) {
            n = 9;
        }

        sRikuSelectedCard->value = n;
        sRikuSelectedCard->valueModified = 1;
        TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &sRikuSelectedCard->cardDef);
    } else if (gRikuBtlWork->hcEffect == HC_EFFECT_DECREMENTOR) {
        if (sRikuSelectedCard->value != 0) {
            n = sRikuSelectedCard->value - 1;
            sRikuSelectedCard->value--;
            sRikuSelectedCard->valueModified = 1;
        } else {
            n = 0;
            sRikuSelectedCard->valueModified = 1;
        }
    } else {
        n = sRikuSelectedCard->value;
    }

    work->stockValue += n;
    work->stockCount++;
    gCardBattleState->rikuStockedCount++;

    if (work->stockValue != 0) {
        UpdateSpriteFrameTiles(work->tiles, gStockValueFrames[0], gStockValueTiles + ((work->stockValue - 1) << 7));
        work->xSteps = 8;
    }

    work->cardsLeft[work->listIndex]--;

    if (sRikuSelectedCard->cardDef->flags & CARD_DEF_FLAG_FRIEND) {
        sRikuSelectedCard->args.slot->removed = 1;
    }

    sRikuSelectedCard->args.slot->used = 1;
    index = sRikuSelectedCard->args.index + 1;

    if ((s16)index >= work->slotCounts[work->listIndex]) {
        index = 0;
    }

    sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;
    sRikuSelectedCard = NULL;

    if (gRikuBtlWork->hcEffect == HC_EFFECT_RANDOM_FLUSH) {
        hcEffect = GetRandomHcEffect();
        SyncRikuHcEffect(work);
        gCardBattleState->rikuHcEffect = hcEffect;
        func_08081740(work, gCardBattleState->rikuHcEffect);
        ApplyRikuHcEffect(work);
        gRikuBtlWork->hcEffectCount = gHcEffectDefs[gRikuBtlWork->hcEffect].count;
    }

    slot = FindNextAvailableSlot(work, work->listIndex, &index);

    if (slot != NULL) {
        args.pool = &work->cardDisplays[work->listIndex];
        args.index = index;
        args.listIndex = work->listIndex;
        args.slot = slot;
        args.reloadCount = work->reloadCounts[work->listIndex];

        if (slot->cardId == CARD_ID_RELOAD) {
            card = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
        } else {
            card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
        }

        card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
        card->ringIndex = 0;
        card->priority = 60;
        card->timer = 4;
        card->x = card->ringCenterX;
        card->y = card->ringCenterY;
        card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_VISIBLE);
        sRikuSelectedCard = card;
    }

    if (gRikuBtlWork->hcEffect == HC_EFFECT_AUTO_RELOAD && (sRikuSelectedCard->flags & CARD_DISP_FLAG_RELOAD_CARD) &&
        work->cardsLeft[work->listIndex] == 1) {
        work->cardsLeft[work->listIndex] = 0;
        sRikuSelectedCard->command = CARD_DISP_COMMAND_REMOVE;
        work->selectedCards[work->listIndex] = NULL;
        sRikuSelectedCard = NULL;
        work->reloadPending[0] = 1;

#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }
    }

    return 1;
}

void TryRikuStockBreak(CardBattleWork* work) {
    CardDisplayWork** activeCard;
    u8 n = work->stockValue;
    u16 total = 0;
#ifdef VERSION_EU
    CardDisplayWork* previous[3];
#endif
    StockKeys stockKeys = sRikuEmptyKeys;
    u8 flag;
    u8 skip;
    u8 i;
    u16 result;

#ifdef VERSION_EU
    u8 previousCount;
    s32 j;
    s32 k;
#endif

    if (gCardBattleState->activeValue > n && n != 0) {
        return;
    }

    skip = 0;

    if (gBtlWork->hcEffect == HC_EFFECT_ATTACK_BRACER && gCardBattleState->activeCards[0]->cardDef->category == 0 &&
        !gCardBattleState->soraStockActive) {
        skip = 1;
    }

#ifdef VERSION_EU
    if (gBtlWork->hcEffect == HC_EFFECT_LEAF_BRACER) {
        for (j = 0; j < gCardBattleState->activeCardCount; j++) {
            if (gCardBattleState->activeCards[j]->cardDef->move == 22) {
                skip = 1;
            }
        }
    }

    if (gBtlWork->hcEffect == HC_EFFECT_ITEM_BRACER) {
        for (k = 0; k < gCardBattleState->activeCardCount; k++) {
            if (gCardBattleState->activeCards[k]->cardDef->category == 2 &&
                !(gCardBattleState->activeCards[k]->cardDef->flags & CARD_DEF_FLAG_FRIEND)) {
                skip = 1;
            }
        }
    }
#else
    if (gBtlWork->hcEffect == HC_EFFECT_LEAF_BRACER && gCardBattleState->activeCards[0]->cardDef->move == 22 &&
        !gCardBattleState->soraStockActive) {
        skip = 1;
    }

    if (gBtlWork->hcEffect == HC_EFFECT_ITEM_BRACER && gCardBattleState->activeCards[0]->cardDef->category == 2 &&
        !gCardBattleState->soraStockActive) {
        skip = 1;
    }
#endif

    if (skip) {
        return;
    }

    for (i = 0; i < gCardBattleState->activeCardCount; i++) {
        gCardBattleState->activeCards[i]->flags |= CARD_DISP_FLAG_BROKEN;
    }

    gBtlWork->flags |= BTL_FLAG_CARD_BREAK;

    if (gCardBattleState->activeValue != n) {
        if (n == 0) {
            gBtlWork->breakDifference = -(u8)gCardBattleState->activeValue;

            if (gBtlWork->breakDifference < -9) {
                gBtlWork->breakDifference = -9;
            }
        } else {
            gBtlWork->breakDifference = (u8)gCardBattleState->activeValue - n;

            if (gBtlWork->breakDifference < -9) {
                gBtlWork->breakDifference = -9;
            }
        }

        AddBreakDarkPoints();
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_BUSY;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        ApplyTrickmasterToRikuStock(work);

#ifndef VERSION_EU
        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            result = LookupStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag);
        } else {
            result = LookupLinkStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag, 1);
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

        for (i = 0; i < work->stockCount; i++) {
            total += work->stock[i]->value;
        }

        gCardBattleState->activeValue = total;
#ifdef VERSION_EU
        previousCount = gCardBattleState->activeCardCount;
#endif
        gCardBattleState->activeCardCount = work->stockCount;

        for (i = 0; i < work->stockCount; i++) {
#ifdef VERSION_EU
            previous[i] = gCardBattleState->activeCards[i];
#endif
            activeCard = gCardBattleState->activeCards;
            activeCard += i;
            *activeCard = work->stock[i];
            work->stock[i]->flags |= CARD_DISP_FLAG_IN_PLAY;

            if (work->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                work->stock[i]->args.slot->removed = 1;
            }
        }

        gBtlWork->soraOwnsPlay = 0;
        gCardBattleState->rikuStockActive = 1;
        m4aSongNumStart(SONG_BTL_GARD);

#ifdef VERSION_EU
        if (!(gBtlWork->flags & BTL_FLAG_VS_BATTLE)) {
            result = LookupStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag);
        } else {
            result = LookupLinkStockName(work->stock, work->stockCount, work->stockValue, &stockKeys, &flag, 1);
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
        ApplyTrickmasterToRikuStock(work);
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gCardBattleState->rikuStockActive = 0;
        gBtlWork->soraOwnsPlay = 0;
    }
}

void UseRikuStock(CardBattleWork* work) {
    CardDisplayWork** activeCard;
    CardDisplayWork* empty;
    u64 flags;
    u8 i;
    u8 n;

    for (i = 0, n = 0; i < work->stockCount; i++) {
        if (work->stock[i]->flags & CARD_DISP_FLAG_SETTLED) {
            n++;
        }
    }

    if (n < work->stockCount) {
        return;
    }

    gCardBattleState->unk_0C0 = 0;
    gCardBattleState->rikuStockNameShown = 0;
    work->stockNameChecked = 0;
    flags = gBtlWork->flags;

    if ((flags & BTL_FLAG_CARD_ACTIVE) == 0) {
        gCardBattleState->activeCardCount = work->stockCount;

        for (i = 0; i < work->stockCount; i++) {
            activeCard = gCardBattleState->activeCards;
            activeCard += i;
            *activeCard = work->stock[i];
            work->stock[i]->priority = i * 4 + 50;

            if (work->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                work->stock[i]->args.slot->removed = 1;
            }

            work->stock[i]->flags |= (CARD_DISP_FLAG_IN_PLAY | CARD_DISP_FLAG_UNOPPOSED);
        }

        gCardBattleState->activeValue = work->stockValue;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags |= BTL_FLAG_CARD_PLAY_START;
        gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_BUSY;
        gCardBattleState->rikuStockActive = 1;
    } else {
        if (!gBtlWork->soraOwnsPlay) {
            return;
        }

        if ((flags & BTL_FLAG_CARD_PLAY_ENDED) == 0) {
            TryRikuStockBreak(work);
            gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_BUSY;
        } else {
            TryRikuStockBreak(work);
            gBtlWork->flags |= BTL_FLAG_OPPONENT_CARD_BUSY;
        }
    }

    for (i = 0; i < work->stockCount; i++) {
        work->stock[i]->args.slot->stocked = 0;

        if (work->stock[i]->cardDef->flags & CARD_DEF_FLAG_ITEM) {
            work->stock[i]->args.slot->removed = 1;
        } else if (i == 0 && gRikuBtlWork->hcEffect != HC_EFFECT_SLEIGHT_LOCK) {
            work->stock[0]->args.slot->removed = 1;
        }
    }

    if (CountRemainingAttackCards(work, 0) == 0) {
        for (i = 0; i < work->stockCount; i++) {
            if (work->stock[i]->args.listIndex == 0) {
                work->stock[i]->args.slot->removed = 0;
                break;
            }
        }
    }

    i = 0;

    if (i < work->stockCount) {
        do {
            empty = NULL;
            n = i;
            work->playedCards[n] = work->stock[n];
            work->stock[n]->command = CARD_DISP_COMMAND_PLAY;
            work->stock[n] = empty;
            i = ++n;
        } while (i < work->stockCount);
    }

    TickRikuHcEffectOnCardUse();
    work->stockCount = 0;
    gCardBattleState->rikuStockedCount = 0;
    work->stockValue = 0;
    ClearStockedCardSlots(work);
    work->stockNameChecked = 0;
}

u8 UseRikuHeartlessCard(CardBattleWork* work) {
    CardDisplayArgs args;
    CardDisplayWork* card;
    CardDisplayWork* selected;
    CardSlot* slot;
    u16 index;
    CardDisplayWork** active;

    if ((sRikuSelectedCard->flags & CARD_DISP_FLAG_NO_CARD) == 0) {
        if (gCardBattleState->rikuHcEffect == HC_EFFECT_NONE) {
            gCardBattleState->rikuHcEffect = sRikuSelectedCard->cardDef->move;
            func_08081740(work, gCardBattleState->rikuHcEffect);
            ApplyRikuHcEffect(work);
            active = &sRikuSelectedCard;
        } else {
            SyncRikuHcEffect(work);
            gCardBattleState->rikuHcEffect = sRikuSelectedCard->cardDef->move;
            func_08081740(work, gCardBattleState->rikuHcEffect);
            ApplyRikuHcEffect(work);
            gCardBattleState->rikuHcEffectReplaced = 1;
            active = &sRikuSelectedCard;
        }

        sRikuSelectedCard->args.slot->removed = 1;
        sRikuSelectedCard->command = CARD_DISP_COMMAND_HEARTLESS;
        sRikuSelectedCard->priority = 50;
        sRikuSelectedCard->flags &= ~CARD_DISP_FLAG_SETTLED;

        if (work->stockValue > 1) {
            UpdateSpriteFrameTiles(work->tiles, gStockValueFrames[0], gStockValueTiles + ((work->stockValue - 1) << 7));
            work->xSteps = 8;
        }

        sRikuSelectedCard->args.slot->used = 1;
        selected = sRikuSelectedCard;
        index = selected->args.index + 1;

        if ((s16)index >= work->slotCounts[work->listIndex]) {
            index = 0;
        }

        selected->flags &= ~CARD_DISP_FLAG_SETTLED;
        sRikuSelectedCard = NULL;
        work->cardsLeft[work->listIndex]--;
        slot = FindNextAvailableSlot(work, work->listIndex, &index);

        if (slot != NULL) {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = index;
            args.listIndex = work->listIndex;
            args.slot = slot;
            args.reloadCount = work->reloadCounts[work->listIndex];

            if (slot->cardId == CARD_ID_RELOAD) {
                card = TaskCreate(&work->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                card = TaskCreate(&work->tasks, &gTaskDescCardRiku, &args)->work;
            }

            card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
            card->ringIndex = 0;
            card->priority = 60;
            card->timer = 4;
            card->x = card->ringCenterX;
            card->y = card->ringCenterY;
            card->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_VISIBLE);
            sRikuSelectedCard = card;
        } else {
            args.pool = &work->cardDisplays[work->listIndex];
            args.index = 0xFFFF;
            args.slot = work->slots[work->listIndex];
            args.listIndex = work->listIndex;
            card = TaskCreate(&work->tasks, &gTaskDescNOCard, &args)->work;
            card->swingAngleTarget = card->swingAngle = sRikuCardSwingAngles[0];
            card->ringIndex = 0;
            card->priority = 50;
            card->timer = 4;
            card->flags |= (CARD_DISP_FLAG_NO_CARD | CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED | CARD_DISP_FLAG_VISIBLE);
            sRikuSelectedCard = card;
        }

        if (*active == NULL) {
            work->reloadPending[work->listIndex] = 1;
        }
    }

    return 1;
}

void func_08081740(CardBattleWork* work, u16 hcEffect) {
}

void SyncRikuHcEffect(CardBattleWork* work) {
    gRikuBtlWork->hcEffect = gCardBattleState->rikuHcEffect;
}

void ApplyRikuHcEffect(CardBattleWork* work) {
    if (gBtlWork->hcEffect != HC_EFFECT_DISPEL) {
        gRikuBtlWork->hcEffect = gCardBattleState->rikuHcEffect;
    } else {
        gRikuBtlWork->hcEffect = HC_EFFECT_NONE;
        gCardBattleState->rikuHcEffect = HC_EFFECT_NONE;
    }

#ifdef VERSION_EU
    if (gRikuBtlWork->hcEffect == HC_EFFECT_DISPEL) {
        if (gBtlWork->hcEffect == HC_EFFECT_DOUBLE_SLEIGHT && (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
            gBtlWork->flags &= ~BTL_FLAG_STOCK_SEQUENCE;
        }

        gCardBattleState->soraHcEffect = HC_EFFECT_NONE;
        gBtlWork->hcEffect = HC_EFFECT_NONE;
        gBtlWork->hcEffectCount = 0;
        gRikuBtlWork->hcEffect = HC_EFFECT_NONE;
        gRikuBtlWork->hcEffectCount = 0;
    }
#endif

    if (gCardBattleState->rikuHcEffect == HC_EFFECT_MIMIC) {
        if (gBtlWork->hcEffect != HC_EFFECT_NONE) {
            gCardBattleState->rikuHcEffect = gCardBattleState->soraHcEffect;
            gRikuBtlWork->hcEffect = gBtlWork->hcEffect;
        } else {
            gBtlWork->hcEffect = HC_EFFECT_NONE;
            gCardBattleState->rikuHcEffect = HC_EFFECT_NONE;
        }
    }

    if (gRikuBtlWork->hcEffect == HC_EFFECT_DOUBLE_SLEIGHT) {
        work->reloadCounts[0] = 2;
        work->reloadCounts[1] = 2;
    }

#ifndef VERSION_EU
    if (gRikuBtlWork->hcEffect == HC_EFFECT_DISPEL) {
        gCardBattleState->soraHcEffect = HC_EFFECT_NONE;
        gBtlWork->hcEffect = HC_EFFECT_NONE;
        gBtlWork->hcEffectCount = 0;
        gRikuBtlWork->hcEffect = HC_EFFECT_NONE;
        gRikuBtlWork->hcEffectCount = 0;
    }
#endif
}

u8 func_08081828() {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->unk_0ED;
}

u8 GetRikuCardListIndex() {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->rikuListIndex;
}

u8 GetActiveCardValue() {
    // @bug Polled before the card battle state exists (NULL read).
    return gCardBattleState->activeValue;
}

s32 GetRikuSelectedCardMoveRaw() {
    if (sRikuSelectedCard != NULL) {
        return sRikuSelectedCard->cardDef->move;
    }

    return 145;
}

u8 GetRikuSelectedCardValue() {
    if (sRikuSelectedCard != NULL) {
        return sRikuSelectedCard->value;
    }

    return 0xFF;
}

u8 CanUseRikuSelectedCard() {
    if (gRikuBtlWork->hcEffect == HC_EFFECT_MAGIC_BOOST) {
        if (sRikuSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (!(sRikuSelectedCard->cardDef->flags & CARD_DEF_FLAG_SUMMON)) {
            return 1;
        }

        return 0;
    } else if (gRikuBtlWork->hcEffect == HC_EFFECT_SUMMON_BOOST) {
        if (sRikuSelectedCard->cardDef->category != 1) {
            return 1;
        }

        if (sRikuSelectedCard->cardDef->flags & CARD_DEF_FLAG_SUMMON) {
            return 1;
        }

        return 0;
    }

    return 1;
}

void TickRikuHcEffectOnReload() {
    switch (gRikuBtlWork->hcEffect) {
    case HC_EFFECT_INCREMENTOR:
    case HC_EFFECT_COMBO_PLUS:
    case HC_EFFECT_FIRE_BOOST:
    case HC_EFFECT_COMBO_FINISH:
    case HC_EFFECT_DRAW:
    case HC_EFFECT_CARDBLIND:
    case HC_EFFECT_QUICKLOAD:
    case HC_EFFECT_COMBO_PLUS_2:
    case HC_EFFECT_BLIZZARD_BOOST:
    case HC_EFFECT_THUNDER_BOOST:
    case HC_EFFECT_CURE_BOOST:
    case HC_EFFECT_PROTECT:
    case HC_EFFECT_RANDOM_VALUES:
    case HC_EFFECT_ALL_ZEROS:
    case HC_EFFECT_VANISH:
    case HC_EFFECT_LEAF_BRACER:
    case HC_EFFECT_DECREMENTOR:
    case HC_EFFECT_BIO:
    case HC_EFFECT_DRAW_2:
    case HC_EFFECT_ITEM_BRACER:
    case HC_EFFECT_RELOAD_KINESIS:
    case HC_EFFECT_RETROGRADE:
    case HC_EFFECT_DRAIN:
    case HC_EFFECT_BACK_ATTACK:
    case HC_EFFECT_RANDOM_FLUSH:
    case HC_EFFECT_MAGIC_BOOST:
    case HC_EFFECT_SUMMON_BOOST:
    case HC_EFFECT_AUTO_RELOAD:
    case HC_EFFECT_HYPER_HEALING:
    case HC_EFFECT_GUARD:
    case HC_EFFECT_FLOAT:
        gRikuBtlWork->hcEffectCount--;
        break;
    }
}

void TickRikuHcEffectOnCardUse() {
    if (gRikuBtlWork->hcEffect == HC_EFFECT_DASH) {
        gRikuBtlWork->hcEffectCount--;
    }
}

void ResetRikuReloadGauge(CardBattleWork* work) {
    gCardBattleState->rikuReloadGauge = 0;
    gCardBattleState->rikuReloadCounter = 0;
    gCardBattleState->rikuGaugeFullFrame = 4;
    gCardBattleState->rikuGaugeAnim = 2;
    gCardBattleState->reloadGaugeFull[1] = 0;
}

void RikuCardInit(CardDisplayWork* work, CardDisplayArgs* args) {
    u16 index;

    CpuFill32(0, work, sizeof(CardDisplayWork));
    work->tiles = NULL;
    work->tiles2 = NULL;
    work->tiles3 = NULL;
    work->tiles4 = NULL;
    work->tiles5 = NULL;
    work->palette2 = NULL;
    work->palette = NULL;
    work->children = NULL;
    work->reloadGauge = NULL;
    work->args = *args;
    work->flags = 0;
    index = work->args.index;

    if ((s16)index != -1) {
        LookupRikuCardDef(&work->args, &work->cardDef, index);

        if (work->args.slot->cardId == CARD_ID_RELOAD) {
            work->flags |= CARD_DISP_FLAG_RELOAD_CARD;
        }
    } else {
        work->flags = CARD_DISP_FLAG_NO_CARD;
    }

    if (work->args.slot->cardId & 0x8000) {
        work->premium = 1;
    } else {
        work->premium = 0;
    }

    work->scaleX = 0;
    work->scaleY = 0x100;
    work->bobAngle = 0;
    work->angle = 0;
    work->ringAngle = 0;
    work->ringAngleTarget = 0;
    work->swingAngle = 0;
    work->swingAngleTarget = 0;
    work->command = CARD_DISP_COMMAND_NONE;
    work->priority = 80;
    work->timer = 4;
    work->phase = CARD_STOCK_PHASE_RISE;
    work->ringRadius = 0x2400;
    work->ringRadiusTarget = 0x2400;
    work->swingSteps = 0;
    work->ringCenterX = gRikuCardLayout[5][0];
    work->ringCenterY = gRikuCardLayout[5][1];
    work->x = gRikuCardLayout[4][0];
    work->y = gRikuCardLayout[4][1];

    if (work->cardDef != NULL) {
        work->value = work->cardDef->value;
    } else {
        work->value = 0;
    }

    work->valueModified = 0;
    work->flags |= (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_OPEN);
    work->flags &= ~CARD_DISP_FLAG_SETTLED;
}

u8 RikuCardUpdate(CardDisplayWork* work, void* task) {
    if ((work->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_GFX_LOADED)) == CARD_DISP_FLAG_SELECTED) {
        LoadCardDisplayGfx(work);
        work->flags |= CARD_DISP_FLAG_GFX_LOADED;
    }

    if (work->flags & CARD_DISP_FLAG_DEALING) {
        work->timer = 4;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardDeal);
        return 1;
    }

    if (work->flags & CARD_DISP_FLAG_SELECTED) {
        if ((s16)work->timer > 0) {
            work->flags &= ~CARD_DISP_FLAG_SETTLED;
            ApproachValue(&work->scaleX, 0x100, work->timer);
            work->timer--;
        } else {
            work->flags |= CARD_DISP_FLAG_SETTLED;
        }
    } else if ((s16)work->timer > 0) {
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        ApproachValue(&work->scaleX, 0, work->timer);

        if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
            ReleaseCardDisplayGfx(work);
            work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        }

        work->timer--;
    } else {
        return 0;
    }

    if (work->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    ApproachValue(&work->x, work->ringCenterX, work->timer);
    ApproachValue(&work->y, work->ringCenterY, work->timer);
    work->bobAngle += 4;

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardClosed);
    }

    return DispatchRikuCardCommand(work, task);
}

static void card_2(CardDisplayWork* work) {
    void* gfx;
    ObjAffine* affine;
    u16 y;
    s16 sy;
    u16 flags;
    u8 j;

    gfx = work->cardDef->gfx;

    if (IsMessageWindowOpen() == 1) {
        y = work->y >> 8;
    } else {
        y = (work->y >> 8) + (gSineTable[work->bobAngle] >> 8);
    }

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        return;
    }

    if (!(work->flags & CARD_DISP_FLAG_GFX_LOADED)) {
        return;
    }

    if (work->scaleX == 0) {
        return;
    }

    if (!(work->flags & CARD_DISP_FLAG_STOCKED)) {
        u8 j;

        if (gRikuBtlWork->hcEffect == HC_EFFECT_CARDBLIND) {
            return;
        }

        affine = AllocObjAffine(work->angle, work->scaleX, work->scaleY, 0);
        flags = SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC;
        DrawSprite(work->x >> 8, y, gCardBacks[work->cardDef->category].gfx, gCardBattleState->tiles[work->cardDef->category], gCardBattleState->palette, affine, flags, work->priority - 1);
        DrawSprite(work->x >> 8, y, gfx, work->tiles, work->palette, affine, flags, work->priority);
        j = work->value;

        if (work->cardDef->category == 3) {
            return;
        }

        if (work->valueModified) {
            DrawSprite(work->x >> 8, y, gCardModifiedValueDigitFrames[j], gCardBattleState->tiles7, gCardBattleState->palette2, affine, flags, work->priority - 2);
        } else if (work->premium) {
            DrawSprite(work->x >> 8, y, gCardPremiumValueDigitFrames[j], gCardBattleState->tiles6, gCardBattleState->palette2, affine, flags, work->priority - 2);
        } else {
            DrawSprite(work->x >> 8, y, gCardValueDigitFrames[j], gCardBattleState->tiles5, gCardBattleState->palette, affine, flags, work->priority - 2);
        }

        if (work->premium) {
            DrawSprite(work->x >> 8, y, gCardBattleState->gfx, gCardBattleState->premiumTiles, gCardBattleState->palette, affine, flags, work->priority - 3);
        }

        return;
    }

    if (gRikuBtlWork->hcEffect == HC_EFFECT_SLEIGHTBLIND) {
        return;
    }

    affine = AllocObjAffine(0, work->scaleX, work->scaleY, 0);
    flags = SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC;
    sy = y;
    DrawSprite(work->x >> 8, sy, work->cardDef->gfx2, work->tiles, work->palette, affine, flags, work->priority);
    j = work->value;

    if (work->cardDef->category == 3) {
        return;
    }

    if (work->valueModified) {
        DrawSprite((work->x >> 8) - 3, sy - 4, gCardValueDigitFrames[j], gCardBattleState->tiles7, gCardBattleState->palette2, affine, flags, work->priority - 10);

        if (work->premium) {
            DrawSprite(work->x >> 8, sy, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, affine, flags, work->priority - 11);
        }
    } else if (work->premium) {
        DrawSprite((work->x >> 8) - 3, sy - 4, gCardValueDigitFrames[j], gCardBattleState->tiles6, gCardBattleState->palette2, affine, flags, work->priority - 10);
        DrawSprite(work->x >> 8, sy, gCardBattleState->gfx2, gCardBattleState->premiumTiles2, gCardBattleState->palette, affine, flags, work->priority - 11);
    } else {
        DrawSprite((work->x >> 8) - 3, sy - 4, gCardValueDigitFrames[j], gCardBattleState->tiles5, gCardBattleState->palette, affine, flags, work->priority - 10);
    }
}

void NO_Card_2(CardDisplayWork* work) {
    void* gfx;
    u16 y;

    gfx = gCardBacks[0].gfx2;

    if (IsMessageWindowOpen() == 1) {
        y = work->y >> 8;
    } else {
        y = (work->y >> 8) + (gSineTable[work->bobAngle] >> 8);
    }

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
            if (work->scaleX != 0) {
                if (gRikuBtlWork->hcEffect != HC_EFFECT_CARDBLIND) {
                    DrawSprite(work->x >> 8, y, gfx, work->tiles2, gCardBattleState->palette, NULL, SPRITE_PRIORITY(1) | SPRITE_FLAG_NO_MOSAIC, work->priority - 1);
                }
            }
        }
    }
}

void RikuCardDestroy(CardDisplayWork* work) {
    ReleaseCardDisplayGfx(work);

    if (work->reloadGauge != NULL) {
        EwramFree(work->reloadGauge);
    }
}

void SyncRikuCardDisplayGfx(CardDisplayWork* work) {
    if (work->command == CARD_DISP_COMMAND_STOCK) {
        return;
    }

    if (work->scaleX == 0) {
        if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
            ReleaseCardDisplayGfx(work);
            work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        }
    } else {
        if ((work->flags & CARD_DISP_FLAG_GFX_LOADED) == 0) {
            LoadCardDisplayGfx(work);
            work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        }
    }
}

u8 RikuCardWaitPlayEnd(CardDisplayWork* work, void* task) {
    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) {
        work->timer = 8;
        work->spinSpeed = 8;
        gCardBattleState->activeCardCount = 0;
        gCardBattleState->activeValue = 0;
        gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
        gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
        gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_BUSY;

        if (work->cardDef->category == 0) {
            TickRikuHcEffectOnAttackEnd();
        }

        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardShrinkAway);
    } else if (work->flags & CARD_DISP_FLAG_BROKEN) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = 16;
        work->spinSpeed = 1;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardBreakFall);
    }

    return 1;
}

u8 RikuCardMoveToPlay(CardDisplayWork* work, void* task) {
    ApproachValue(&work->x, 0x7800, work->timer);
    ApproachValue(&work->y, 0x8400, work->timer);
    work->priority = 80;

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer |= 0xFFFF;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) {
        if (work->flags & CARD_DISP_FLAG_IN_PLAY) {
            if ((s16)work->timer == 0) {
                SetTaskUpdate(task, (TaskUpdateFunc)RikuCardWaitPlayEnd);
            }
        } else if ((s16)work->timer <= 2) {
            work->priority -= 4;
            work->ringRadius = 0x500;
            work->timer = 0x100;
            work->ringAngle = 16;
            work->spinSpeed = 1;
            work->flags |= CARD_DISP_FLAG_IN_PLAY;
            SetTaskUpdate(task, (TaskUpdateFunc)RikuCardFlyOff);

            if (work->cardDef->flags & CARD_DEF_FLAG_ITEM) {
                work->args.slot->unk_06 = 0;
            }

            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)work->timer <= 2) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = 16;
        work->spinSpeed = 1;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardFlyOff);
    }

    return 1;
}

u8 RikuStockWaitPlayEnd(CardDisplayWork* work, void* task) {
    ApproachValue(&work->ringCenterX, gPlayedCardCenter[0], work->timer);
    ApproachValue(&work->ringCenterY, gPlayedCardCenter[1], work->timer);
    ApproachValue(&work->ringRadius, work->ringRadiusTarget, work->timer);
    ApproachValue(&work->scaleX, 0x100, work->timer);
    ApproachValue(&work->scaleY, 0x100, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer = 0;
    }

    UpdateRikuPlayedCardPosition(work);

    switch (work->stockIndex) {
    case 0:
        work->priority = 50;
        break;
    case 1:
        work->priority = 40;
        break;
    case 2:
        work->priority = 60;
        break;
    }

    if (work->flags & CARD_DISP_FLAG_BROKEN) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = 16;
        work->spinSpeed = 1;
        gCardBattleState->rikuStockActive = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardBreakFall);
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_PLAY_ENDED) {
        work->timer = 8;
        work->spinSpeed = 8;
        gCardBattleState->activeCardCount--;
        gCardBattleState->activeValue = 0;

        if (gCardBattleState->activeCardCount == 0) {
            gBtlWork->flags &= ~BTL_FLAG_CARD_PLAY_ENDED;
            gBtlWork->flags &= ~BTL_FLAG_CARD_ACTIVE;
            TickRikuHcEffectOnPlayEnd();
        }

        gCardBattleState->rikuStockActive = 0;
        gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_BUSY;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardShrinkAway);
    }

    return 1;
}

u8 RikuStockMoveToPlay(CardDisplayWork* work, void* task) {
    ApproachValue(&work->ringCenterX, gPlayedCardCenter[0], work->timer);
    ApproachValue(&work->ringCenterY, gPlayedCardCenter[1], work->timer);
    ApproachValue(&work->ringRadius, work->ringRadiusTarget, work->timer);
    ApproachValue(&work->scaleX, 0x100, work->timer);
    ApproachValue(&work->scaleY, 0x100, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer = 0;
    }

    UpdateRikuPlayedCardPosition(work);

    if (gBtlWork->flags & BTL_FLAG_CARD_ACTIVE) {
        if (work->flags & CARD_DISP_FLAG_IN_PLAY) {
            if ((s16)work->timer == 0) {
                SetTaskUpdate(task, (TaskUpdateFunc)RikuStockWaitPlayEnd);
            }
        } else if ((s16)work->timer <= 2) {
            work->priority -= 4;
            work->ringRadius = 0x500;
            work->timer = 0x100;
            work->ringAngle = 16;
            work->spinSpeed = 1;
            gCardBattleState->unk_0C0 = 0;
            gCardBattleState->rikuStockActive = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)RikuCardFlyOff);
            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)work->timer <= 2) {
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = 16;
        work->spinSpeed = 1;
        gCardBattleState->rikuStockActive = 0;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardFlyOff);
    }

    return 1;
}

u8 RikuStockHold(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);
    s32 targetY;

    SyncCardDisplayGfx(work);

    if (!(work->flags & CARD_DISP_FLAG_STOCK_NAMED)) {
        fn = RikuStockMoveToSlot;
        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        return fn(work, task);
    }

    if (work->flags & 0x40000000) {
        SetTaskUpdate(task, (TaskUpdateFunc)RikuStockVanish);
        return 1;
    }

    if (work->command == CARD_DISP_COMMAND_PLAY) {
        if (work->flags & CARD_DISP_FLAG_UNOPPOSED) {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = RikuStockWaitPlayEnd;
        } else {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = RikuStockMoveToPlay;
        }

        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        work->flags &= ~CARD_DISP_FLAG_STOCKED;
        RefreshRikuCardDisplayGfx(work);
        return fn(work, task);
    }

    if ((s16)work->timer > 0) {
        work->timer--;
        return 1;
    }

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        switch (work->phase) {
        case CARD_STOCK_PHASE_RISE:
            work->y -= 0x80;
            targetY = gRikuCardLayout[3 - work->stockIndex][1] - 0x200;

            if (work->y <= targetY) {
                work->y = targetY;
                work->phase = CARD_STOCK_PHASE_DROP;
            }

            break;
        case CARD_STOCK_PHASE_DROP:
            work->y += 0x200;
            targetY = gRikuCardLayout[3 - work->stockIndex][1];

            if (work->y >= targetY) {
                work->y = targetY;
                work->phase = CARD_STOCK_PHASE_RISE;
                work->timer = 16;
            }

            break;
        }
    } else {
        ApproachValue(&work->x, gRikuCardLayout[4][0], work->timer);
        ApproachValue(&work->y, gRikuCardLayout[4][1], work->timer);
    }

    work->bobAngle += 4;
    return 1;
}

u8 RikuStockMoveToSlot(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);
    u16 timer;

    if (gBtlWork->paused == 1) {
        return 1;
    }

    SyncCardDisplayGfx(work);

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        ApproachValue(&work->x, gRikuCardLayout[3 - work->stockIndex][0], work->timer);
        ApproachValue(&work->scaleY, 179, work->timer);
        ApproachValue(&work->y, gRikuCardLayout[3 - work->stockIndex][1], work->timer);
        ApproachValue(&work->scaleX, 179, work->timer);
    } else {
        ApproachValue(&work->x, gRikuCardLayout[4][0], work->timer);
        ApproachValue(&work->y, gRikuCardLayout[4][1], work->timer);
    }

    timer = work->timer;

    if ((s16)timer > 0) {
        work->timer = timer - 1;
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
    } else {
        work->timer = 0;
        work->scaleX = 0x100;
        work->scaleY = 0x100;
        work->flags |= CARD_DISP_FLAG_SETTLED;

        if (work->flags & CARD_DISP_FLAG_STOCK_NAMED) {
            work->timer = work->stockIndex * 8;
            fn = RikuStockHold;
            SetTaskUpdate(task, (TaskUpdateFunc)fn);
            return fn(work, task);
        }
    }

    if (work->flags & 0x40000000) {
        SetTaskUpdate(task, (TaskUpdateFunc)RikuStockVanish);
        return 1;
    }

    if (work->command == CARD_DISP_COMMAND_PLAY) {
        if (work->flags & CARD_DISP_FLAG_UNOPPOSED) {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = RikuStockWaitPlayEnd;
        } else {
            work->timer = 15;
            work->ringRadiusTarget = 0x800;
            work->ringRadius = 0;
            work->ringAngleTarget = gPlayedCardAngles[work->stockIndex] * 2;
            work->ringAngle = 0;
            work->ringCenterX = work->x;
            work->ringCenterY = work->y;
            fn = RikuStockMoveToPlay;
        }

        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        work->flags &= ~CARD_DISP_FLAG_STOCKED;
        RefreshRikuCardDisplayGfx(work);
        return fn(work, task);
    }

    work->bobAngle += 4;
    return 1;
}

u8 RikuCardDeal(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        fn = RikuCardClosed;
        SetTaskUpdate(task, (TaskUpdateFunc)fn);
        return fn(work, task);
    }

    ApproachValue(&work->scaleX, 0x100, work->timer);
    work->timer--;

    if (work->timer == 0) {
        work->flags &= ~CARD_DISP_FLAG_DEALING;
        work->scaleX = 0x100;

        if (work->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            gCardBattleState->rikuReloadCharging = 0;
            SetTaskUpdate(task, (TaskUpdateFunc)Reload_Card_1);
        } else {
            SetTaskUpdate(task, (TaskUpdateFunc)RikuCardUpdate);
        }
    }

    return 1;
}

u8 RikuCardClosed(CardDisplayWork* work, void* task) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (work->command == CARD_DISP_COMMAND_REMOVE) {
        return 0;
    }

    work->ringRadius += -work->ringRadius >> 1;
    work->x += (gRikuCardLayout[4][0] - work->x) >> 1;
    work->y += (gRikuCardLayout[4][1] - work->y) >> 1;

    if (work->flags & CARD_DISP_FLAG_OPEN) {
        if (work->flags & CARD_DISP_FLAG_RELOAD_CARD) {
            fn = Reload_Card_1;
            SetTaskUpdate(task, (TaskUpdateFunc)fn);
            return fn(work, task);
        } else {
            SetTaskUpdate(task, (TaskUpdateFunc)RikuCardUpdate);
            fn = RikuCardUpdate;
            return fn(work, task);
        }
    }

    return 1;
}

u8 RikuCardShrinkAway(CardDisplayWork* work) {
    ApproachValue(&work->y, 0x8200, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
    } else {
        work->timer = 0;
    }

    if ((s16)work->timer == 0) {
        work->timer = 0;
        work->angle += work->spinSpeed;
        work->spinSpeed++;

        if (work->scaleX <= 25) {
            return 0;
        }

        work->scaleX -= 25;
        work->scaleY -= 25;
    }

    return 1;
}

u8 RikuCardFlyOff(CardDisplayWork* work) {
    work->command = CARD_DISP_COMMAND_NONE;
    work->y -= work->ringRadius;
    work->ringRadius -= (s16)work->timer;
    work->timer++;
    work->x -= COS(work->ringAngle);
    work->angle += work->spinSpeed;
    work->scaleX -= 5;
    work->scaleY -= 5;

    if (IsCardDisplayOffScreen(work)) {
        work->flags &= ~CARD_DISP_FLAG_VISIBLE;
        ReleaseCardDisplayGfx(work);
        gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_BUSY;
        work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        return 0;
    }

    return 1;
}

void UpdateRikuPlayedCardPosition(CardDisplayWork* work) {
    s32 wrappedAngle;

    if (work->ringAngleTarget - work->ringAngle > 0x7F00) {
        work->ringAngle += 0x10000;
    }

    if (work->ringAngleTarget - work->ringAngle <= 255) {
        wrappedAngle = work->ringAngle - 0x10000;

        if (work->ringAngleTarget - wrappedAngle < work->ringAngle - work->ringAngleTarget) {
            work->ringAngle = wrappedAngle;
        }
    }

    work->ringAngle += (work->ringAngleTarget - work->ringAngle) >> 2;
    work->x = SIN(work->ringAngle >> 8) * (work->ringRadius >> 8) + work->ringCenterX;
    work->y = -COS(work->ringAngle >> 8) * (work->ringRadius >> 8) + work->ringCenterY;
}

u8 DispatchRikuCardCommand(CardDisplayWork* work, void* task) {
    switch (work->command) {
    case CARD_DISP_COMMAND_PLAY:
        work->timer = 10;
        work->priority -= 4;
        work->scaleX = 0x100;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardMoveToPlay);
        return 1;
    case CARD_DISP_COMMAND_STOCK:
        work->timer = 8;
        work->priority -= 4;
        LoadRikuCardDisplayGfx2(work);
        work->flags |= CARD_DISP_FLAG_STOCKED;
        work->flags |= CARD_DISP_FLAG_GFX_LOADED;
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuStockMoveToSlot);
        return 1;
    case CARD_DISP_COMMAND_FLY_OFF:
        work->priority -= 4;
        work->ringRadius = 0x500;
        work->timer = 0x100;
        work->ringAngle = 16;
        work->spinSpeed = 1;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardFlyOff);
        return 1;
    case CARD_DISP_COMMAND_REMOVE:
        work->ringRadius = 0x500;
        work->timer = 0x100;
        return 0;
    case CARD_DISP_COMMAND_HEARTLESS:
        work->timer = 10;
        work->priority -= 4;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuHeartlessCardShow);
        return 1;
    case CARD_DISP_COMMAND_SLIDE_OUT:
    default:
        UpdateRikuCardValue(work);
        break;
    }

    return 1;
}

void LookupRikuCardDef(CardDisplayArgs* args, const CardDef** out, u8 index) {
    u32* pickedFriendCardId;

    if (args->slot != NULL) {
        if (args->slot->cardId != CARD_ID_NONE) {
            if (args->slot->cardId != CARD_ID_RELOAD) {
                *out = &gCardDefs[args->slot->cardId & CARD_ID_MASK];
            } else {
                *out = NULL;
            }
        } else {
            *out = NULL;
        }
    } else {
        pickedFriendCardId = &gCardBattleState->pickedFriendCardId;
        *out = &gCardDefs[*pickedFriendCardId & CARD_ID_MASK];
        *pickedFriendCardId = 0x3B6;
    }
}

u8 RikuCardBreakFall(CardDisplayWork* work, void* task) {
    work->command = CARD_DISP_COMMAND_NONE;
    work->y -= work->ringRadius;
    work->ringRadius -= (s16)work->timer >> 1;
    work->timer++;
    work->x -= 0x200;
    work->angle += 16;

    if (!(work->flags & CARD_DISP_FLAG_SPIN_MIRRORED)) {
        work->scaleX -= 10;

        if (work->scaleX >= -2 && work->scaleX <= 2) {
            work->scaleX = -10;
        }

        if (work->scaleX <= -0x100) {
            work->scaleX = -0x100;
            work->flags |= CARD_DISP_FLAG_SPIN_MIRRORED;
        }
    } else {
        work->scaleX -= 10;

        if (work->scaleX >= -2 && work->scaleX <= 2) {
            work->scaleX = 10;
        }

        if (work->scaleX >= 0x100) {
            work->scaleX = 0x100;
            work->flags &= ~CARD_DISP_FLAG_SPIN_MIRRORED;
        }
    }

    if (IsCardDisplayOffScreen(work)) {
        work->flags &= ~CARD_DISP_FLAG_VISIBLE;
        ReleaseCardDisplayGfx(work);
        work->flags &= ~CARD_DISP_FLAG_GFX_LOADED;
        gBtlWork->flags &= ~BTL_FLAG_OPPONENT_CARD_BUSY;
        return 0;
    }

    return 1;
}

void LoadRikuCardDisplayGfx2(CardDisplayWork* work) {
    void* tiles;
    void* pal;

    ReleaseCardDisplayGfx(work);
    tiles = work->cardDef->tiles2;
    pal = work->cardDef->palette2;
    work->tiles = LoadObjTiles(tiles, 256);
    work->palette = LoadObjPalette(pal, 32);
}

void RefreshRikuCardDisplayGfx(CardDisplayWork* work) {
    if (work->tiles != NULL) {
        ReleaseObjTiles(work->tiles);
    }

    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    work->tiles = NULL;
    work->palette = NULL;
    LoadCardDisplayGfx(work);
}

u8 RikuHeartlessCardShow(CardDisplayWork* work) {
    u8 arg;

    work->command = CARD_DISP_COMMAND_NONE;
    ApproachValue(&work->x, 0xD800, work->timer);
    ApproachValue(&work->scaleY, 0x99, work->timer);
    ApproachValue(&work->y, 0x6400, work->timer);
    ApproachValue(&work->scaleX, 0x99, work->timer);

    if ((s16)work->timer > 0) {
        work->timer--;
        return 1;
    }

    arg = 2;
    gRikuBtlWork->hcEffectCount = gHcEffectDefs[gRikuBtlWork->hcEffect].count;
    TaskCreate(&gCardBattleState->tasks, &gTaskDescHCEffectName, &arg);
    return 0;
}

u8 RikuStockVanish(CardDisplayWork* work) {
    s32 result;

    if (work->scaleX <= 24) {
        work->args.slot->stocked = result = 0;
        return result;
    }

    work->scaleX -= 12;
    work->scaleY += 12;

    if (work->scaleY > 0x1FF) {
        work->scaleY = 0x200;
    }

    return 1;
}

void Reload_Card_0(CardDisplayWork* work, CardDisplayArgs* args) {
    CpuFill32(0, work, sizeof(CardDisplayWork));
    work->tiles = NULL;
    work->tiles2 = NULL;
    work->tiles3 = NULL;
    work->tiles4 = NULL;
    work->tiles5 = NULL;
    work->palette2 = NULL;
    work->palette = NULL;
    work->children = NULL;
    work->reloadGauge = EwramAlloc(sizeof(ReloadGauge));
    CpuFill32(0, work->reloadGauge, sizeof(ReloadGauge));
    work->args = *args;
    work->reloadGauge->chargeTick = 0;
    work->flags = (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_OPEN | CARD_DISP_FLAG_RELOAD_CARD | CARD_DISP_FLAG_RELOAD_GAUGE);
    work->cardDef = NULL;
    work->scaleX = 0;
    work->scaleY = 0x100;
    work->bobAngle = 0;
    work->angle = 0;
    work->stockIndex = 0;
    work->ringAngle = 0;
    work->ringAngleTarget = 0;
    work->swingAngle = 0;
    work->swingAngleTarget = 0;
    work->command = CARD_DISP_COMMAND_NONE;
    work->priority = 80;
    work->timer = 4;
    work->phase = 0;
    work->ringRadius = 0x2400;
    work->ringRadiusTarget = 0x2400;
    work->swingSteps = 0;
    work->ringCenterX = gRikuCardLayout[5][0];
    work->ringCenterY = gRikuCardLayout[5][1];
    work->x = gRikuCardLayout[4][0];
    work->y = gRikuCardLayout[4][1];
    work->flags &= ~CARD_DISP_FLAG_SETTLED;
    gCardBattleState->rikuReloadCharging = 0;
    LoadRikuReloadCardGfx(work);
    work->flags |= CARD_DISP_FLAG_GFX_LOADED;
}

u8 Reload_Card_1(CardDisplayWork* work, void* task) {
    if (work->flags & CARD_DISP_FLAG_DEALING) {
        work->timer = 4;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardDeal);
        return 1;
    }

    UpdateRikuReloadGauge(work);

    if (work->flags & CARD_DISP_FLAG_SELECTED) {
        if ((s16)work->timer > 0) {
            work->flags &= ~CARD_DISP_FLAG_SETTLED;
            ApproachValue(&work->scaleX, 0x100, work->timer);
            gCardBattleState->rikuReloadCharging = 0;
            work->timer--;
        } else {
            work->flags |= CARD_DISP_FLAG_SETTLED;
        }
    } else {
        if ((s16)work->timer <= 0) {
            return 0;
        }

        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        ApproachValue(&work->scaleX, 0, work->timer);
        gCardBattleState->rikuReloadCharging = 0;
        work->timer--;
    }

    if (work->flags & CARD_DISP_FLAG_FROZEN) {
        return 1;
    }

    ApproachValue(&work->x, work->ringCenterX, work->timer);
    ApproachValue(&work->y, work->ringCenterY, work->timer);
    work->bobAngle += 4;

    if (!(work->flags & CARD_DISP_FLAG_OPEN)) {
        work->flags &= ~CARD_DISP_FLAG_SETTLED;
        SetTaskUpdate(task, (TaskUpdateFunc)RikuCardClosed);
    }

    return DispatchRikuCardCommand(work, task);
}

void Reload_Card_3(CardDisplayWork* work) {
    ReleaseCardDisplayGfx(work);

    if (work->reloadGauge != NULL) {
        EwramFree(work->reloadGauge);
    }

    if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }
}

void AdvanceRikuReloadGaugeAnim(ReloadGauge* gauge, CardDisplayWork* work) {
    if (gCardBattleState->rikuGaugeAnim <= 7) {
        gCardBattleState->rikuGaugeAnim++;
    }

    AnimStart(&gauge->anim3, gCardBattleState->rikuGaugeAnim, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void ResetRikuReloadGaugeAnim(ReloadGauge* gauge) {
    gCardBattleState->rikuGaugeAnim = 2;
    AnimStart(&gauge->anim3, 2, ANIM_FLAG_LOOP | ANIM_FLAG_KEEP_FRAME);
}

void SetRikuReloadGaugeIdleFrames(ReloadGauge* gauge, CardDisplayWork* work) {
    gauge->gfx = gRiCardF0RedFrames[3];
    gauge->gfx2 = gRiCardF0RedFrames[gCardBattleState->rikuGaugeFullFrame + 2];
}

void UpdateRikuReloadGaugeAnims(ReloadGauge* gauge, CardDisplayWork* work) {
    gauge->gfx = AnimUpdate(&gauge->anim2);
    gauge->gfx2 = AnimUpdate(&gauge->anim3);
}

void SetRikuReloadCounterAnim(ReloadGauge* gauge, s16 count) {
    void* gfx;

    if ((u16)count <= 18) {
        AnimStart(&gauge->anim, count, 0);
        gfx = AnimGetGfx(&gauge->anim);
    } else {
        gfx = NULL;
    }

    gauge->gfx3 = gfx;
}

void UpdateRikuReloadGauge(CardDisplayWork* work) {
    ReloadGauge* gauge = work->reloadGauge;
    u8 reloadCharging = 0;

    if ((work->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        reloadCharging = gCardBattleState->rikuReloadCharging;
        gCardBattleState->rikuReloadCharging = 0;
    } else {
        gCardBattleState->rikuReloadCharging = 0;
    }

    if ((work->flags & (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) == (CARD_DISP_FLAG_SELECTED | CARD_DISP_FLAG_SETTLED)) {
        if (reloadCharging == 1) {
            if ((s8)gauge->chargeTick == 2) {
                if (!(gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING)) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_CHAGE);
#endif
                    gRikuBtlWork->flags |= BTL_FLAG_RELOAD_CHARGING;
                }

                if (gCardBattleState->reloadGaugeFull[1] == 0) {
                    if (gRikuBtlWork->hcEffect == HC_EFFECT_OVERDRIVE) {
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
                    AdvanceRikuReloadGaugeAnim(work->reloadGauge, work);

                    if (gCardBattleState->rikuGaugeFullFrame == 22) {
                        gCardBattleState->rikuGaugeFullFrame = 4;
                        gCardBattleState->rikuReloadGauge = 0;
                        gCardBattleState->reloadGaugeFull[1] = 0;
                        gCardBattleState->rikuReloadCounter--;
                        work->phase = reloadCharging;
                        ResetRikuReloadGaugeAnim(work->reloadGauge);
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
#endif
                        SetRikuReloadCounterAnim(work->reloadGauge, gCardBattleState->rikuReloadCounter);
                    }
                }

                gauge->chargeTick = 0;
            }

            UpdateRikuReloadGaugeAnims(work->reloadGauge, work);
            gauge->chargeTick++;
        } else {
            SetRikuReloadGaugeIdleFrames(work->reloadGauge, work);
            gauge->chargeTick = 0;
            m4aSongNumStop(SONG_SYS_CHAGE);
            gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
        }
    } else {
        gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }

    if ((s16)gCardBattleState->rikuReloadCounter < 0) {
        gCardBattleState->rikuReloadGauge = 0;
        gCardBattleState->rikuGaugeFullFrame = 4;
        gCardBattleState->rikuGaugeAnim = 2;
        gCardBattleState->reloadGaugeFull[1] = 0;

        if (!(work->flags & CARD_DISP_FLAG_RELOAD_DONE)) {
            work->flags |= CARD_DISP_FLAG_RELOAD_DONE;
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif
        }

        if (FadeGetAmount() == 0) {
            FadeFromAmount(FADE_MODE_ADD_WHITE, 16, 20);
        }

        gRikuBtlWork->flags &= ~BTL_FLAG_RELOAD_CHARGING;
    }
}

void Reload_Card_2(CardDisplayWork* work) {
    ObjAffine* affine;
    ObjAffine* affine2;
    ReloadGauge* gauge;
    s16 y;
    u16 attr;

    attr = 0x410;
    affine = AllocObjAffine(0, work->scaleX, 0x100, 0);

    if (work->flags & CARD_DISP_FLAG_GFX_LOADED) {
        gauge = work->reloadGauge;

        if (IsMessageWindowOpen() == 1) {
            y = work->y >> 8;
        } else {
            y = (work->y >> 8) + (gSineTable[work->bobAngle] >> 8);
        }

        if (work->scaleX > 0) {
            DrawSprite(work->x >> 8, y, gCardBacks[3].gfx2, work->tiles2,
                       gCardBattleState->palette, affine, attr, work->priority);

            if (gauge->gfx3 != NULL) {
                DrawSprite(work->x >> 8, y, gauge->gfx3, work->tiles,
                           gCardBattleState->palette, affine, attr,
                           work->priority - 2);
            }

            if ((s32)gCardBattleState->rikuReloadGauge > 0) {
                affine2 = AllocObjAffine(0, work->scaleX, gCardBattleState->rikuReloadGauge, 0);

                if (gauge->gfx != NULL) {
                    DrawSprite(work->x >> 8, y + 17, gauge->gfx,
                               work->tiles3, gCardBattleState->palette, affine2, SPRITE_PRIORITY(1),
                               work->priority - 1);
                }

                if (gCardBattleState->reloadGaugeFull[1] == 1 && gauge->gfx2 != NULL) {
                    DrawSprite(work->x >> 8, y, gauge->gfx2, work->tiles4,
                               gCardBattleState->palette, affine, SPRITE_PRIORITY(1),
                               work->priority - 1);
                }
            }
        }
    }
}

void InitRikuReloadCounterAnim(ReloadGauge* gauge, void* tiles, u8 listIndex, s8 count) {
    AnimInit(&gauge->anim, gReloadCounterWhiteAnims, gReloadCounterWhiteFrames);

    if (count >= 0) {
        AnimStart(&gauge->anim, count, 0);
    } else {
        AnimStart(&gauge->anim, 0, 0);
    }

    gauge->gfx3 = AnimGetGfx(&gauge->anim);
}

void LoadRikuReloadCardGfx(CardDisplayWork* work) {
    ReloadGauge* gauge;

    gauge = work->reloadGauge;
    work->tiles = AllocObjTiles(128, NULL);
    SetObjTileSource(work->tiles, gReloadCounterWhiteTiles);
    InitRikuReloadCounterAnim(work->reloadGauge, work->tiles, work->args.listIndex, gCardBattleState->rikuReloadCounter);
    work->palette = NULL;
    work->tiles2 = LoadObjTiles(gReloadCardGreenTiles, 0x280);
    work->palette2 = NULL;
    work->tiles3 = AllocObjTiles(0x200, NULL);
    SetObjTileSource(work->tiles3, gRiCardF0RedTiles);
    work->tiles4 = AllocObjTiles(128, NULL);
    SetObjTileSource(work->tiles4, gRiCardF0RedTiles);
    AnimInit(&gauge->anim2, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&gauge->anim2, 1, ANIM_FLAG_LOOP);
    gauge->gfx = gRiCardF0RedFrames[3];
    AnimInit(&gauge->anim3, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&gauge->anim3, gCardBattleState->rikuGaugeAnim, ANIM_FLAG_LOOP);
    gauge->gfx2 = gRiCardF0RedFrames[gCardBattleState->rikuGaugeFullFrame + 2];
}

void UpdateRikuCardValue(CardDisplayWork* work) {
    // @bug The reload card and the empty slot have no cardDef (NULL read).
    if (gRikuBtlWork->hcEffect == HC_EFFECT_RANDOM_VALUES) {
        if (work->flags & CARD_DISP_FLAG_SELECTED) {
            work->valueModified = 1;
            work->value = GetRandom() % 10;
        } else {
            work->valueModified = 0;
            work->value = work->cardDef->value;
        }
    } else if (gRikuBtlWork->hcEffect == HC_EFFECT_RETROGRADE) {
        work->valueModified = 1;
        work->value = 10 - work->cardDef->value;

        if (work->value == 10) {
            work->value = 0;
        }
    } else if (gRikuBtlWork->hcEffect == HC_EFFECT_ALL_ZEROS) {
        work->valueModified = 1;
        work->value = 0;
    } else {
        work->value = work->cardDef->value;
        work->valueModified = 0;
    }
}

void TickRikuHcEffectOnPlayEnd() {
    BtlWork* btl;

    btl = gRikuBtlWork;

    switch ((u32)btl->hcEffect) {
    case HC_EFFECT_SLEIGHT_LOCK:
    case HC_EFFECT_SLEIGHTBLIND:
    case HC_EFFECT_DOUBLE_SLEIGHT:
        btl->hcEffectCount--;
        break;
    }
}

void TickRikuHcEffectOnAttackEnd() {
    if (gRikuBtlWork->hcEffect == HC_EFFECT_ATTACK_BRACER) {
        gRikuBtlWork->hcEffectCount--;
    }
}

void RequestBossCardOpen() {
}

void RequestBossCardClose() {
    gBossCardRequest = 7;
}

void func_080838F8() {
}

void func_080838FC() {
}

void RequestBossCardValue(u8 value) {
    gBossCardRequest = 1;
    gBossCardRequestValue = value;
}

void RequestBossCardRandom() {
    gBossCardRequest = 2;
}

u8 GetBossCardShownValue() {
    return GetBossCardValue();
}

void Bosscard_0(BossCardWork* work, u32* arg) {
    u8 cardCount;

    work->enemyKind = arg[0];
    gBossCardRequest = 2;
    gBossCardRequestValue = GetRandom() % 9;
    work->x = 0x100;
    work->y = 0x84;
    work->flipScale = 0x100;
    work->unk_2F = 1;
    work->unk_30 = 1;
    work->bobAngle = 0;
    work->slideSteps = 8;
    work->flipShrinking = 1;
    work->flipTimer = 0;
    work->flipDelay = GetRandom() % 100;
    work->cardIds = gEnemyCardIds[work->enemyKind];
    work->cardDef = &gCardDefs[work->cardIds[0]];
    work->cardBack = &gEnemyCardBacks[work->cardDef->kind >> 12];
    cardCount = gEnemyCardCounts[work->enemyKind];
    gCardBattleState->nextEnemyCardIndex = GetRandom() % cardCount;
}

u8 Bosscard_1(BossCardWork* work, void* task) {
    s32 x;
    u8 z;

    work->bobAngle += 4;

    if (gCardBattleState->enemyCardUsed == 1) {
        z = 0;
        work->x = 0x100;
        work->slideSteps = 8;
        gCardBattleState->enemyCardUsed = z;
    }

    if (work->slideSteps != 0) {
        x = work->x << 8;
        ApproachValue(&x, 0xDC00, work->slideSteps);
        work->x = x >> 8;
        work->slideSteps--;
    }

    if (gBossCardRequest == 7) {
        work->slideSteps = 8;
        SetTaskUpdate(task, (TaskUpdateFunc)BosscardSlideOut);
    }

    if (gBossCardRequest == 1) {
        if (FlipBossCard(work, 1)) {
            gBossCardRequest = 0;
        }
    }

    if (gBossCardRequest == 2) {
        if (work->flipTimer == work->flipDelay) {
            if (FlipBossCard(work, 0)) {
                work->flipTimer = 0;
                work->flipDelay = GetRandom() % 100;
            }
        } else {
            work->flipTimer++;
        }
    }

    return 1;
}

s32 BosscardSlideOut(BossCardWork* work) {
    s32 x;

    if (work->slideSteps != 0) {
        x = work->x << 8;
        ApproachValue(&x, 0x10000, work->slideSteps);
        work->x = x >> 8;
        work->slideSteps--;
    }

    return 1;
}

void Bosscard_2() {
}

void Bosscard_3() {
}

u8 FlipBossCard(BossCardWork* work, u8 requested) {
    if (work->flipShrinking == 1) {
        work->flipScale -= 51;

        if (work->flipScale <= 2) {
            work->flipScale = 2;
            work->flipShrinking = 0;

            if (!requested) {
                gBossCardRequestValue = GetRandom() % 9 + 1;
            }

            SetBossCardValue(gBossCardRequestValue);
        }
    } else {
        work->flipScale += 51;

        if (work->flipScale > 255) {
            work->flipScale = 256;
            work->flipShrinking = 1;
            return 1;
        }
    }

    return 0;
}

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
