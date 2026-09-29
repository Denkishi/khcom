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
#include "sprites_card.h"
#include "sprites_card_pictures.h"

u8 gUnk_02039DD8 EWRAM_COMMON(4);

u8 gUnk_02039DDC EWRAM_COMMON(4);

#include "riku_deck_names.inc"

const Deck gUnk_09034084[21] = {
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

const s32 gUnk_090352E4[4] = {
    0xE000, 0x2000, 0x6000, 0xA000,
};

const s16 gUnk_090352F4[4] = {
    184, 172, 160, 0,
};

const UnkStruct_080ABA80 gUnk_090352FC = {
    { -1, -1, -1, -1, -1, -1 },
};

u8 func_0807CE68(CardDisplayWork* p);
void func_0807C39C(CardDisplayWork* p);
void func_0807C33C(CardDisplayWork* p);
static u8 cardbattle_1(CardBattleWork* w, void* a);
u8 func_0807FB5C(CardBattleWork* w, void* a);
void func_0807FD10(CardBattleWork* w, u8 n);
void func_0807FE30(CardBattleWork* w, u8 n);
void sub_0807E4C8(CardBattleWork* w, CardSlot* slots, s8 kind, s32 n);
u16 sub_0807E66C(CardSlot* out, u16* ids, u16 n, u8 kind);
Deck* sub_08083EFC(void);
void func_08081740(CardBattleWork* w, u16 n);
void func_08081744(CardBattleWork* w);
void func_08080228(CardBattleWork* w);
void func_0807FF48(CardBattleWork* w);
void func_080800B4(CardBattleWork* w);
u8 func_08080594(CardBattleWork* w);
void func_08080994(CardBattleWork* w);
u8 func_08080B44(CardBattleWork* w);
void func_08081210(CardBattleWork* w);
u8 func_080814BC(CardBattleWork* w);
void func_080819E8(void);
void func_08081A04(CardBattleWork* w);
void func_08082EFC(CardDisplayWork* p);
void func_080838A0(void);
u8 func_080827E0(CardDisplayWork* p, void* a);
void func_08083340(CardDisplayWork* p);
void func_08082DA4(CardDisplayArgs* a, CardDef** out, u8 index);
void func_080838CC(void);
u8 func_08082AE4(CardDisplayWork* p);
u8 func_08082FF0(CardDisplayWork* p);
void func_08082F24(CardDisplayWork* p);
s32 func_08083ADC(BossCardWork* w);
void func_08082BF8(CardDisplayWork* p);
u8 func_080782AC(CardDisplayWork** p, u8 n);
void sub_0807842C(CardSlot* slots, u8 n);
u16 func_08078754(CardBattleWork* w, u8 n);
u16 func_0807885C(CardBattleWork* w, u8 b);
void func_080788CC(CardBattleWork* w, u8 b);
void func_08078914(CardBattleWork* w, u8 n);
u16 func_080792AC(void);
void func_0807AE78(CardBattleWork* w);
void func_0807B378(CardBattleWork* w);
void func_0807B728(CardBattleWork* w);
void func_0807B7A4(CardBattleWork* w);
void func_0807B81C(CardBattleWork* w);
void func_0807B894(CardBattleWork* w);
void func_0807B910(CardBattleWork* w);
void func_0807B98C(CardBattleWork* w);
u8 func_0807BA54(void);
void func_0807C2EC(CardDisplayWork* p);
void func_0807C33C(CardDisplayWork* p);
void func_0807C39C(CardDisplayWork* p);
u8 func_0807CE68(CardDisplayWork* p);

void func_0807E368(CardBattleWork* w, u8 slot) {
    CardDisplayArgs args;
    u16 id;
    CardSlot* card;
    CardDisplayWork* node;
    s16 count;

    count = 0;
    if (w->unk_94[slot] != 0xFFFF && (s16)w->unk_A8[slot] > 0) {
        id = w->unk_94[slot];
        card = func_08076674(w, slot, &id);
        if (card != 0) {
            args.pool = &w->unk_54[slot];
            args.index = id;
            args.unk_0E = slot;
            args.slot = card;
            args.unk_0F = w->unk_9C[slot];
            if (card->cardId == 0xFFFE) {
                gRikuSelectedCard = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                gRikuSelectedCard = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
            }
            count++;
        }
    }

    switch (count) {
    case 0:
        args.pool = &w->unk_54[slot];
        args.index = 0xFFFF;
        args.slot = w->slots[slot];
        args.unk_0E = slot;
        node = TaskCreate(&w->tasks, &gTaskDescNOCard, &args)->work;
        node->unk_98 = node->unk_94 = gUnk_090352E4[0];
        node->unk_A4 = 0;
        node->unk_A0 = 50;
        node->unk_78 |= 0x802;
        gRikuSelectedCard = node;
        break;
    case 1:
        gRikuSelectedCard->unk_98 = gRikuSelectedCard->unk_94 = gUnk_090352E4[0];
        gRikuSelectedCard->unk_A0 = 50;
        gRikuSelectedCard->unk_78 |= 0x800;
        break;
    }
}

void sub_0807E4C8(CardBattleWork* w, CardSlot* slots, s8 kind, s32 n) {
    Deck* deck;
    u32 count;

    switch (gBtlWork->unk_10C) {
    case 157:
    case 179:
        deck = &gUnk_09034084[20];
        n = deck->unk_DC;
        break;
    case 158:
        deck = &gUnk_09034084[4];
        n = deck->unk_DC;
        break;
    case 159:
        deck = &gUnk_09034084[1];
        n = deck->unk_DC;
        break;
    case 160:
        deck = &gUnk_09034084[2];
        n = deck->unk_DC;
        break;
    case 161:
        deck = &gUnk_09034084[5];
        n = deck->unk_DC;
        break;
    case 162:
        deck = &gUnk_09034084[0];
        n = deck->unk_DC;
        break;
    case 163:
        deck = &gUnk_09034084[3];
        n = deck->unk_DC;
        break;
    case 164:
        deck = &gUnk_09034084[7];
        n = deck->unk_DC;
        break;
    case 165:
        deck = &gUnk_09034084[13];
        n = deck->unk_DC;
        break;
    case 166:
        deck = &gUnk_09034084[14];
        n = deck->unk_DC;
        break;
    case 177:
        deck = &gUnk_09034084[19];
        n = deck->unk_DC;
        break;
    case 167:
        deck = &gUnk_09034084[17];
        n = deck->unk_DC;
        break;
    case 168:
        deck = &gUnk_09034084[6];
        n = deck->unk_DC;
        break;
    case 169:
        deck = &gUnk_09034084[9];
        n = deck->unk_DC;
        break;
    case 170:
        deck = &gUnk_09034084[10];
        n = deck->unk_DC;
        break;
    case 171:
        deck = &gUnk_09034084[16];
        n = deck->unk_DC;
        break;
    case 172:
        deck = &gUnk_09034084[18];
        n = deck->unk_DC;
        break;
    case 173:
        deck = &gUnk_09034084[12];
        n = deck->unk_DC;
        break;
    case 174:
        deck = &gUnk_09034084[11];
        n = deck->unk_DC;
        break;
    case 175:
        deck = &gUnk_09034084[8];
        n = deck->unk_DC;
        break;
    case 176:
        deck = &gUnk_09034084[15];
        n = deck->unk_DC;
        break;
    default:
        deck = sub_08083EFC();
        n = 99;
        break;
    }

    count = sub_0807E66C(slots, deck->cards, n, (u8)kind);

    if (gBtlWork->flags & 0x800) {
        sub_0807842C(w->slots[kind], count);
    }

    if (kind == 0) {
        slots[count].unk_06 = 0;
        slots[count].unk_07 = 0;
        slots[count].unk_0A = 0;
        slots[count].cardId = 0xFFFE;
        slots[count].unk_04 = count;
    }
}

u16 sub_0807E66C(CardSlot* out, u16* ids, u16 n, u8 kind) {
    u16 count = 0;
    s32 i;

    for (i = 0; i < n; i++) {
        if (ids[i] != 0xFFFF) {
            switch (kind) {
            case 0:
                if ((u8)gCardDefs[ids[i] & CARD_ID_MASK].unk_2A <= 2) {
                    out[count].unk_06 = kind;
                    out[count].unk_07 = kind;
                    out[count].unk_0A = kind;
                    out[count].cardId = ids[i];
                    out[count].unk_04 = count;
                    count++;
                }
                break;
            case 3:
                if ((u8)gCardDefs[ids[i] & CARD_ID_MASK].unk_2A == 3) {
                    out[count].unk_06 = 0;
                    out[count].unk_07 = 0;
                    out[count].unk_0A = 0;
                    out[count].cardId = ids[i];
                    out[count].unk_04 = count;
                    count++;
                }
                break;
            }
        }
    }

    return count;
}

void func_0807E724(CardBattleWork* w, s8 idx) {
    u16 n = w->unk_A8[idx];

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
                w->slots[idx][i].unk_07 = 0;
                w->slots[idx][i].unk_0A = 0;
                w->slots[idx][i].unk_08 = 0;
                w->slots[idx][i].unk_09 = 0;
            }

            for (i = n; i < n + 15; i++) {
                w->slots[idx][i].unk_06 = 1;
                w->slots[idx][i].cardId = 0xFFFF;
                w->slots[idx][i].unk_07 = 1;
                w->slots[idx][i].unk_0A = 1;
                w->slots[idx][i].unk_08 = 1;
                w->slots[idx][i].unk_09 = 0;
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
                w->slots[idx][i].unk_07 = 0;
                w->slots[idx][i].unk_0A = 0;
                w->slots[idx][i].unk_08 = 0;
                w->slots[idx][i].unk_09 = 0;
            }
        }

        sub_0807E4C8(w, w->slots[idx], idx, (u16)w->unk_A8[idx]);
        w->unk_94[idx] = 0;
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
        w->slots[idx]->unk_09 = 0;
        q = w->unk_94;
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
    gCardBattleState->unk_060 = w;
    w->tiles = AllocSpriteFrameTiles(0x80);
    w->palette = LoadObjPalette(gBStatesPalette, 32);
    UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8);
    TaskPoolInit(&w->tasks, 30);
    w->unk_B9 = 0;
    w->unk_B8 = 0;
    w->unk_C0[0] = 0;
    w->unk_C0[1] = 0;
    w->unk_C0[2] = 0;
    w->unk_C0[3] = 0;
    w->unk_BC[0] = 1;
    w->unk_BC[1] = 0;
    w->unk_BC[2] = 0;
    w->unk_BC[3] = 0;
    w->unk_BA = 0;
    w->unk_C4[3] = 0;
    w->x = *(u16*)&gUnk_090352E4[4];

    for (i = 0; i <= 2; i++) {
        w->unk_1C[i] = 0;
        w->unk_28[i] = 0;
    }

    for (i = 0; i <= 3; i++) {
        w->unk_34[i] = 0;
        w->slots[i] = 0;
    }

    w->unk_C4[1] = 0;
    ListPoolInit(&w->unk_54[0]);
    ListPoolInit(&w->unk_54[1]);
    ListPoolInit(&w->unk_54[2]);
    ListPoolInit(&w->unk_54[3]);

    switch (gBtlWork->unk_10C) {
    case 157:
    case 179:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[20]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[20]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 158:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[4]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[4]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 159:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[1]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[1]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 160:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[2]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[2]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 161:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[5]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[5]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 162:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[0]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[0]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 163:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[3]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[3]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 164:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[7]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[7]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 165:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[13]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[13]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 166:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[14]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[14]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 177:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[19]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[19]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 167:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[17]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[17]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 168:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[6]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[6]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 169:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[9]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[9]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 170:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[10]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[10]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 171:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[16]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[16]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 172:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[18]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[18]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 173:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[12]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[12]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 174:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[11]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[11]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 175:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[8]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[8]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    case 176:
        w->unk_A8[0] = w->unk_B0[0] = func_080859A0(0, &gUnk_09034084[15]) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_080859A0(1, &gUnk_09034084[15]);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    default:
        w->unk_A8[0] = w->unk_B0[0] = func_08083E54(0) + 1;
        w->unk_A8[3] = w->unk_B0[3] = func_08083E54(3);
        func_0807E724(w, 0);
        func_0807E724(w, 3);
        break;
    }

    w->unk_9C[0] = 0;
    w->unk_9C[1] = 0;
    w->unk_9C[2] = 0;
    w->unk_94[0] = 0;
    w->unk_94[1] = 0;
    w->unk_94[2] = 0;
    w->unk_94[3] = 0;
    gRikuSelectedCard = 0;
    func_0807E368(w, w->unk_B8);
    gUnk_02034AA4 = 0;
    gCardBattleState->unk_0D4 = w->unk_B8;
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

    if (gBtlWork->unk_0A0 == 4) {
        if (gRikuBtlWork->flags & 0x1000000) {
            gRikuBtlWork->flags &= ~0x1000000;
        }

        return 0;
    }

    if (w->unk_C4[3] != 0) {
        hold = w->x << 8;
        ApproachValue(&hold, gUnk_090352F4[w->unk_B9 - 1] << 8, w->unk_C4[3]);
        w->x = hold >> 8;
        w->unk_C4[3]--;
    }

    if (gRikuSelectedCard->unk_78 & 0x1000000) {
        if (gRikuSelectedCard->unk_78 & 0x4000000) {
            if (gRikuBtlWork->unk_0F4 == 9) {
                gRikuSelectedCard->unk_78 |= 0x4000;
                gRikuSelectedCard->unk_A1 = 7;

                if (gRikuBtlWork->unk_0F4 != 25) {
                    func_0807B378(w);

                    if (gRikuBtlWork->unk_0F4 == 10) {
                        w->unk_9C[w->unk_B8] -= 2;

                        if ((s16)w->unk_9C[w->unk_B8] < 0) {
                            w->unk_9C[w->unk_B8] = 0;
                        }
                    }
                }

                gCardBattleState->unk_0FE = w->unk_9C[w->unk_B8];
                gCardBattleState->unk_0F8 = 0;
                gCardBattleState->unk_102 = 4;
                TaskPoolUpdate(&w->tasks);
                func_08078914(w, 0);
                w->unk_94[0] = 0;
                w->unk_B0[0] = func_08078754(w, 0);
                func_0807E368(w, 0);
                func_080818E4();
            } else {
                gRikuSelectedCard->unk_A1 = 7;

                if (gRikuBtlWork->unk_0F4 != 25) {
                    func_0807B378(w);

                    if (gRikuBtlWork->unk_0F4 == 10) {
                        w->unk_9C[w->unk_B8] -= 2;

                        if ((s16)w->unk_9C[w->unk_B8] < 0) {
                            w->unk_9C[w->unk_B8] = 0;
                        }
                    }
                }

                gCardBattleState->unk_0FE = w->unk_9C[w->unk_B8];
                gCardBattleState->unk_0F8 = 0;
                gCardBattleState->unk_102 = 4;
                func_080788CC(w, 0);
                w->unk_94[w->unk_B8] = 0;
                w->unk_B0[w->unk_B8] = 0;
                w->unk_C0[w->unk_B8] = 1;
                gRikuSelectedCard = 0;
                gUnk_02034AA4 = 0;
                w->unk_BC[w->unk_B8] = 0;
            }
        }
    }

    switch (gUnk_02034AA4) {
    case 0:
        break;
    case 1:
        gUnk_02034AA4 = 0;

        if (gRikuSelectedCard->unk_78 & 0x40) {
            func_0807FD10(w, w->unk_B8);
        }
        break;
    case 2:
        gUnk_02034AA4 = 0;

        if (gRikuSelectedCard->unk_78 & 0x40) {
            func_0807FE30(w, w->unk_B8);
        }
        break;
    case 4:
        gUnk_02034AA4 = 0;
        p = gRikuSelectedCard;
        flags = p->unk_78;

        if (!(flags & 0x100000)) {
            if (w->unk_B9 == 3) {
                func_08081210(w);
            } else if (p->cardDef->unk_2A == 3) {
#ifndef VERSION_EU
                m4aSongNumStart(SONG_SYS_BEEP);
#endif
            } else if (w->unk_C0[w->unk_B8] == 0) {
                if (!(flags & 2)) {
                    if (func_08081888() != 0) {
                        if (w->unk_B9 <= 2 && gCardBattleState->unk_0E2 == 0) {
                            func_08080B44(w);
                        }
                    } else if (gRikuSelectedCard->unk_78 & 0x20) {
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
        } else if (w->unk_B9 != 0) {
            func_08081210(w);
        } else {
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_BEEP);
#endif
        }
        break;
    case 3:
        gUnk_02034AA4 = 0;

        if (gRikuSelectedCard->cardDef->unk_2A != 3) {
            if (!(gRikuSelectedCard->unk_78 & 0x100000) && w->unk_C0[w->unk_B8] == 0) {
                if (!(gRikuSelectedCard->unk_78 & 2)) {
                    if (func_08081888() != 0) {
                        func_08080594(w);
                    } else if (gRikuSelectedCard->unk_78 & 0x20) {
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_BEEP);
#endif
                    }
                } else if (gRikuSelectedCard->unk_78 & 0x20) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_BEEP);
#endif
                }
            }
        } else if (!(gRikuSelectedCard->unk_78 & 0x100000)) {
            func_080814BC(w);
        }
        break;
    case 5:
        gUnk_02034AA4 = 0;

        if (w->unk_B9 != 0) {
            func_08081210(w);
        } else if (!(gBtlWork->flags & 0x80)) {
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_BEEP);
#endif
        }
        break;
    case 6:
        gUnk_02034AA4 = 0;
        func_0807FAD8(w);
        break;
    case 7:
        w->unk_BC[w->unk_B8] = 0;
        w->unk_C4[0] = 0;
        func_0807FA44(w);
        break;
    case 8:
        gUnk_02034AA4 = 0;
        break;
    case 9:
        gUnk_02034AA4 = 0;
        func_080800B4(w);
        break;
    case 10:
        gUnk_02034AA4 = 0;
        func_0807FF48(w);
        break;
    default:
        gUnk_02034AA4 = 0;
        break;
    }

    switch (gUnk_02034AA8) {
    case 17:
        gUnk_02034AA8 = 0;
        func_0807B728(w);

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    case 18:
        gUnk_02034AA8 = 0;
        func_0807B7A4(w);

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    case 19:
        gUnk_02034AA8 = 0;
        func_0807B81C(w);
        func_08081A04(w);
        w->unk_9C[0] = 0;

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    case 21:
        gUnk_02034AA8 = 0;
        func_0807B894(w);

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    case 22:
        gUnk_02034AA8 = 0;
        func_0807B910(w);
        func_08081A04(w);
        w->unk_9C[0] = 0;

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    case 23:
        gUnk_02034AA8 = 0;
        func_0807B98C(w);

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    case 24:
        gUnk_02034AA8 = 0;
        func_0807B98C(w);
        func_08081A04(w);
        w->unk_9C[0] = 0;

        if (w->unk_B8 == 0) {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
        } else {
            if (gRikuSelectedCard->unk_78 & 0x1000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
            }

            gRikuSelectedCard->unk_A1 = 7;
            w->unk_B8 = 0;
#ifdef VERSION_EU
            gCardBattleState->unk_0D4 = 0;
#endif
        }

        TaskPoolUpdate(&w->tasks);
        func_080788CC(w, 0);
        w->unk_94[0] = 0;
        w->unk_B0[0] = func_08078754(w, 0);
        func_0807E368(w, 0);
        func_080818E4();
        break;
    }

    if (w->unk_C0[w->unk_B8] != 0) {
        if (gRikuSelectedCard != 0) {
            if (gRikuSelectedCard->unk_78 & 0x4000000) {
                gRikuSelectedCard->unk_78 |= 0x4000;
                func_08080994(w);
                w->unk_C0[w->unk_B8] = 0;
                w->unk_C4[0] = 1;
                gRikuBtlWork->flags |= 0x80000000;
                SetTaskUpdate(a, (TaskUpdateFunc)func_0807FB5C);
                gRikuSelectedCard->unk_78 = (gRikuSelectedCard->unk_78 | 0x834) & ~0x1000;
                TaskPoolUpdate(&w->tasks);
#ifndef VERSION_EU
                m4aSongNumStart(SONG_SYS_RELOAD);
#endif
                slot = w->unk_B8;
                args.slot = slot;
                args.state = &w->unk_C4[0];
                args.mode = 2;
                TaskCreate(&w->tasks, &gTaskDescRELOAD, &args);
                return 1;
            }
        } else {
            func_08080994(w);
            w->unk_C0[w->unk_B8] = 0;
            gRikuBtlWork->flags |= 0x80000000;
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807FB5C);
            gRikuSelectedCard->unk_78 = (gRikuSelectedCard->unk_78 | 0x834) & ~0x1000;
            TaskPoolUpdate(&w->tasks);
#ifndef VERSION_EU
            m4aSongNumStart(SONG_SYS_RELOAD);
#endif
            return 1;
        }
    } else if (gRikuSelectedCard != 0 && (gRikuSelectedCard->unk_78 & 0x42) == 0x42 &&
               func_08078754(w, w->unk_B8) != 0) {
        w->unk_C0[w->unk_B8] = 1;
        w->unk_B0[0] = 0;
        gRikuSelectedCard->unk_A1 = 7;

        if (gRikuBtlWork->unk_0F4 != 40) {
            if (gRikuBtlWork->actor->unk_02C > 3) {
                gRikuBtlWork->actor->unk_02C -= 2;
            }

            w->unk_34[w->unk_B8] = 0;
            gRikuSelectedCard = 0;

            if (gRikuBtlWork->unk_0F4 != 25) {
                func_0807B378(w);

                if (gRikuBtlWork->unk_0F4 == 10) {
                    w->unk_9C[w->unk_B8] -= 2;

                    if ((s16)w->unk_9C[w->unk_B8] < 0) {
                        w->unk_9C[w->unk_B8] = 0;
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
            w->unk_34[w->unk_B8] = 0;
            gRikuSelectedCard = 0;
            w->unk_C0[w->unk_B8] = 1;
            w->unk_B0[0] = 0;
        }
    }

    if (w->unk_C4[1] == 0 && (u8)func_080782AC(w->unk_28, w->unk_B9) != 0) {
        arr = gUnk_090352FC;

        if (!(gBtlWork->flags & 0x4000)) {
            r = func_080AC5E8(w->unk_28, w->unk_B9, w->unk_BA, &arr, flag);
        } else {
            r = func_080AD144(w->unk_28, w->unk_B9, w->unk_BA, &arr, flag, 1);
        }

        gCardBattleState->unk_0C6 = r;

        if (r <= 105) {
            for (i = 0; i < w->unk_B9; i++) {
                w->unk_28[i]->unk_78 |= 0x10000000;
            }

            if (gCardBattleState->unk_0E4 == 0) {
                TaskCreate(&w->tasks, &gUnk_09EE77EC, 0);
                gCardBattleState->unk_0E4 = 1;
            }
        } else {
            if (w->unk_B9 == 3) {
                arr2 = gUnk_090352FC;
                memset(buf, 0, 6);
                done = 0;

                for (i = 0; i < w->unk_B9; i++) {
                    arr2.unk_00[i] = w->unk_28[i]->cardDef->unk_28;
                }

                kind = func_080AE28C(&arr2, buf, w->unk_B9);

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
                    gCardBattleState->unk_0C6 = kind;
                    done = 1;
                    break;
                }

                if (done == 0) {
                    for (i = 0; i < w->unk_B9; i++) {
                        w->unk_28[i]->unk_78 &= ~0x10000000;
                    }

                    if (gCardBattleState->unk_0E4 != 0) {
                        gCardBattleState->unk_0E4 = 0;
                    }
                } else {
                    for (i = 0; i < w->unk_B9; i++) {
                        w->unk_28[i]->unk_78 |= 0x10000000;
                    }

                    if (gCardBattleState->unk_0E4 == 0) {
                        TaskCreate(&w->tasks, &gUnk_09EE77EC, 0);
                        gCardBattleState->unk_0E4 = 1;
                    }
                }
            }
        }

        w->unk_C4[1] = 1;
    }

    gCardBattleState->unk_0F0 = w->unk_B0[w->unk_B8];
    TaskPoolUpdate(&w->tasks);
    gCardBattleState->unk_0D5 = w->unk_B9;
    return 1;
}

static void cardbattle_2(CardBattleWork* w) {
    if (gCardBattleState->unk_0EA != 0 && gRikuBtlWork->unk_0F4 != 28 && w->unk_B9 != 0 && w->unk_BA != 0) {
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

void func_0807FA44(CardBattleWork* w) {
    u8 i;

    for (i = 0; i < w->unk_B9; i++) {
        w->unk_28[i]->unk_78 &= ~0x20;
    }

    if (gRikuSelectedCard != 0) {
        gRikuSelectedCard->unk_78 &= ~0x20;
    }

    gCardBattleState->unk_0CC = 0;
    gBtlWork->flags |= 0x20;
    gCardBattleState->unk_0EA = 0;
    gCardBattleState->unk_0E4 = 0;
    w->unk_C9 = 1;
}

void func_0807FAD8(CardBattleWork* w) {
    u8 i;

    for (i = 0; i < w->unk_B9; i++) {
        w->unk_28[i]->unk_78 |= 0x20;
    }

    if (gRikuSelectedCard != 0) {
        gRikuSelectedCard->unk_78 |= 0x20;
    }

    gBtlWork->flags &= ~0x20;
    gCardBattleState->unk_0EA = 1;
    w->unk_C9 = 0;
}

u8 func_0807FB5C(CardBattleWork* w, void* a) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;

    if (gBtlWork->unk_0A0 == 4) {
        if (gRikuBtlWork->flags & 0x1000000) {
            gRikuBtlWork->flags &= ~0x1000000;
        }

        m4aSongNumStop(SONG_SYS_RELOAD);
        return 0;
    }

    if ((s16)gRikuSelectedCard->unk_9C == 0) {
        if (func_08078754(w, w->unk_B8) > w->unk_C4[2]) {
            gRikuSelectedCard->unk_78 &= ~4;
            v = gRikuSelectedCard->args.index - 1;
            c = func_08076750(w, w->unk_B8, &v);

            if (c != 0) {
                args.pool = &w->unk_54[w->unk_B8];
                args.index = v;
                args.unk_0E = w->unk_B8;
                args.slot = c;
                p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
                p->unk_80 = p->unk_7C = 0;
                p->unk_A0 = 50;
                p->unk_9C = 8;
                p->x = p->unk_8C;
                p->y = p->unk_90;
                p->unk_78 |= 0x814;
                gRikuSelectedCard = p;
                w->unk_C4[2]++;
                w->unk_B0[w->unk_B8]++;
            }
        } else {
            gRikuBtlWork->flags &= ~0x80000000LL;
            gRikuBtlWork->flags &= ~0x100;
            w->unk_C4[0] = 0;
            m4aSongNumStop(SONG_SYS_RELOAD);
            gUnk_02034AA4 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)cardbattle_1);
        }
    }

    if (gUnk_02034AA4 == 7) {
        w->unk_BC[w->unk_B8] = 0;
        w->unk_C4[0] = 0;
        func_0807FA44(w);
        m4aSongNumStop(SONG_SYS_RELOAD);
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}
void func_0807FD10(CardBattleWork* w, u8 n) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;

    if (!(gRikuSelectedCard->unk_78 & 2)) {
        if (w->unk_B0[w->unk_B8] != 1) {
            gRikuSelectedCard->unk_78 &= ~4;
            gRikuSelectedCard->unk_9C = 4;
            v = gRikuSelectedCard->args.index + 1;

            if ((s16)v >= (s16)w->unk_A8[n]) {
                v = 0;
            }

            c = func_08076674(w, n, &v);

            if (c != 0) {
                args.pool = &w->unk_54[n];
                args.index = v;
                args.unk_0E = n;
                args.slot = c;
                args.unk_0F = w->unk_9C[n];

                if (c->cardId == 0xFFFE) {
                    p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
                } else {
                    p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
                }

                p->unk_98 = p->unk_94 = gUnk_090352E4[0];
                p->unk_A4 = 0;
                p->unk_A0 = 60;
                p->unk_9C = 4;
                p->x = p->unk_8C;
                p->y = p->unk_90;
                p->unk_78 |= 0x804;
                gRikuSelectedCard = p;
            }
        }
    }
}

void func_0807FE30(CardBattleWork* w, u8 n) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;

    if (!(gRikuSelectedCard->unk_78 & 2)) {
        if (w->unk_B0[w->unk_B8] != 1) {
            gRikuSelectedCard->unk_78 &= ~4;
            gRikuSelectedCard->unk_54 = 0;
            gRikuSelectedCard->unk_9C = 4;
            v = gRikuSelectedCard->args.index - 1;

            if ((s16)v < 0) {
                v = w->unk_A8[n] - 1;
            }

            c = func_08076750(w, n, &v);

            if (c != 0) {
                args.pool = &w->unk_54[n];
                args.index = v;
                args.unk_0E = n;
                args.slot = c;
                args.unk_0F = w->unk_9C[n];

                if (c->cardId == 0xFFFE) {
                    p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
                } else {
                    p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
                }

                p->unk_98 = p->unk_94 = gUnk_090352E4[0];
                p->unk_A4 = 0;
                p->unk_A0 = 60;
                p->unk_9C = 4;
                p->x = p->unk_8C;
                p->y = p->unk_90;
                p->unk_78 |= 0x804;
                gRikuSelectedCard = p;
            }
        }
    }
}

void func_0807FF48(CardBattleWork* w) {
    if ((gRikuSelectedCard->unk_78 & 0x40) != 0) {
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CANSEL);
#endif

        if (gRikuBtlWork->flags & 0x1000000) {
            gRikuBtlWork->flags &= ~0x1000000;
        }

        w->unk_BC[w->unk_B8] = 0;

        if (w->unk_C0[w->unk_B8] == 0) {
            w->unk_94[w->unk_B8] = gRikuSelectedCard->args.index;
            gRikuSelectedCard->unk_8C = 0x10400;
            gRikuSelectedCard->unk_90 = 0x8C00;
            gRikuSelectedCard->unk_9C = 4;
            gRikuSelectedCard->unk_A1 = 7;
            gRikuSelectedCard->unk_78 &= ~4;
        } else {
            w->unk_34[w->unk_B8] = gRikuSelectedCard;
            gRikuSelectedCard->unk_98 = gUnk_090352E4[3];
            gRikuSelectedCard->unk_A3 = 4;
            gRikuSelectedCard->unk_78 &= ~4;
        }

        switch (w->unk_B8) {
        case 0:
            w->unk_B8 = 3;
            break;
        case 3:
            w->unk_B8 = 0;
            break;
        }

        if (w->unk_C0[w->unk_B8] == 0) {
            func_0807E368(w, (u8)w->unk_B8);
            gRikuSelectedCard->x = gUnk_0903401C[5][0];
            gRikuSelectedCard->y = gUnk_0903401C[5][1];
            gRikuSelectedCard->unk_A3 = 1;
            gRikuSelectedCard->unk_9C = 1;
        } else {
            gRikuSelectedCard = w->unk_34[w->unk_B8];
            gRikuSelectedCard->unk_98 = gUnk_090352E4[0];
            gRikuSelectedCard->unk_94 = gRikuSelectedCard->unk_98;
            gRikuSelectedCard->unk_A3 = 1;
            gRikuSelectedCard->unk_9C = 1;
            gRikuSelectedCard->unk_78 |= 4;
        }

        gCardBattleState->unk_0D4 = w->unk_B8;
    }
}
void func_080800B4(CardBattleWork* w) {
#ifndef VERSION_EU
    m4aSongNumStart(SONG_SYS_CANSEL);
#endif

    if (gRikuBtlWork->flags & 0x1000000) {
        gRikuBtlWork->flags &= ~0x1000000;
    }

    w->unk_BC[w->unk_B8] = 0;

    if (w->unk_C0[w->unk_B8] == 0) {
        w->unk_94[w->unk_B8] = gRikuSelectedCard->args.index;
        gRikuSelectedCard->unk_8C = 0xC800;
        gRikuSelectedCard->unk_90 = 0xB400;
        gRikuSelectedCard->unk_9C = 12;
        gRikuSelectedCard->unk_78 &= ~4;
    } else {
        w->unk_34[w->unk_B8] = gRikuSelectedCard;
        gRikuSelectedCard->unk_98 = gUnk_090352E4[3];
        gRikuSelectedCard->unk_A3 = 12;
        gRikuSelectedCard->unk_78 &= ~4;
    }

    switch (w->unk_B8) {
    case 0:
        w->unk_B8 = 3;
        break;
    case 1:
        w->unk_B8 = 0;
        break;
    case 2:
        w->unk_B8 = 3;
        break;
    case 3:
        w->unk_B8 = 0;
        break;
    }

    if (w->unk_C0[w->unk_B8] == 0) {
        func_0807E368(w, (u8)w->unk_B8);
        gRikuSelectedCard->x = 0x10400;
        gRikuSelectedCard->y = 0x8C00;
        gRikuSelectedCard->unk_9C = 12;
    } else {
        gRikuSelectedCard = w->unk_34[w->unk_B8];
        gRikuSelectedCard->unk_98 = gUnk_090352E4[0];
        gRikuSelectedCard->unk_94 = gUnk_090352E4[1];
        gRikuSelectedCard->unk_A3 = 12;
        gRikuSelectedCard->unk_9C = 12;
        gRikuSelectedCard->unk_78 |= 4;
    }

    gCardBattleState->unk_0D4 = w->unk_B8;
}

void func_08080228(CardBattleWork* w) {
    if (gBtlWork->unk_0F4 == 0x30) {
        if (gRikuSelectedCard->unk_A5 != 0) {
            gRikuSelectedCard->unk_A5 -= gCardBattleState->unk_0C2;
        }

        gBtlWork->unk_0F8--;
    }
}

void func_08080268(CardBattleWork* w) {
    CardDisplayWork* q;
    u8 d;
    u8 i;
    u16 remaining;

    d = gCardBattleState->unk_0C2;

    if (gBtlWork->unk_0F4 == 0x30) {
        if (w->unk_BA != 0) {
            for (i = 0; i < 3; i++) {
                q = w->unk_28[i];

                if (q->unk_A5 > d) {
                    q->unk_A5 -= d;
                    break;
                }

                remaining = d - q->unk_A5;
                q->unk_A5 = 0;
                d = remaining;
            }
        }

        gBtlWork->unk_0F8--;
    }
}

void func_080802D8(CardBattleWork* w) {
#ifdef VERSION_EU
    s32 i;
#endif
    s32 f;
    s32 j;
    u32 t;
    s32 u;
    u8 n;
    u8 flag;

    f = gRikuBtlWork->unk_0F4;

    if (f == 1) {
        t = gRikuSelectedCard->unk_A5;
        n = t + 1;

        if (n > 9) {
            n = 9;
        }

        if (t <= 8) {
            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gRikuSelectedCard->cardDef);
        }

        gRikuSelectedCard->unk_A5 = n;
        gRikuSelectedCard->unk_A7 = 1;
    } else if (f == 21) {
        u = gRikuSelectedCard->unk_A5;

        if (u != 0) {
            n = u - 1;
            gRikuSelectedCard->unk_A5 = u - 1;
            gRikuSelectedCard->unk_A7 = 1;
        } else {
            n = 0;
            gRikuSelectedCard->unk_A7 = 1;
        }
    } else {
        n = gRikuSelectedCard->unk_A5;
    }

    if ((s16)gCardBattleState->unk_0C2 > n && n != 0) {
        return;
    }

    flag = 0;

    if (gBtlWork->unk_0F4 == 2 && gCardBattleState->unk_000[0]->cardDef->unk_2A == 0 && gCardBattleState->unk_0E1 == 0) {
        flag = 1;
    }

#ifdef VERSION_EU
    if (gBtlWork->unk_0F4 == 20) {
        for (i = 0; i < gCardBattleState->unk_0D0; i++) {
            if (gCardBattleState->unk_000[i]->cardDef->unk_24 == 22) {
                flag = 1;
            }
        }
    }

    if (gBtlWork->unk_0F4 == 29) {
        for (j = 0; j < gCardBattleState->unk_0D0; j++) {
            if (gCardBattleState->unk_000[j]->cardDef->unk_2A == 2 && !(gCardBattleState->unk_000[j]->cardDef->flags & 8)) {
                flag = 1;
            }
        }
    }
#else
    if (gBtlWork->unk_0F4 == 20 && gCardBattleState->unk_000[0]->cardDef->unk_24 == 22 && gCardBattleState->unk_0E1 == 0) {
        flag = 1;
    }

    if (gBtlWork->unk_0F4 == 29 && gCardBattleState->unk_000[0]->cardDef->unk_2A == 2 && gCardBattleState->unk_0E1 == 0) {
        flag = 1;
    }
#endif

    if (flag) {
        return;
    }

    for (j = 0; j < gCardBattleState->unk_0D0; j++) {
        gCardBattleState->unk_000[j]->unk_78 |= 0x200000;
    }

    gBtlWork->flags |= 0x800000;

    if ((s16)gCardBattleState->unk_0C2 != n) {
        if (n == 0) {
            if ((s16)gCardBattleState->unk_0C2 > 9) {
                gBtlWork->unk_1CA = 9;
            } else {
                gBtlWork->unk_1CA = gCardBattleState->unk_0C2;
            }
        } else {
            gBtlWork->unk_1CA = (u8)gCardBattleState->unk_0C2 - n;

            if ((s8)gBtlWork->unk_1CA < -9) {
                gBtlWork->unk_1CA = -9;
            }
        }

        m4aSongNumStart(SONG_BTL_GARD);
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags &= ~0x20;
        gRikuSelectedCard->unk_78 |= 0x2000;
        func_08080228(w);
        gCardBattleState->unk_000[0] = gRikuSelectedCard;
        gCardBattleState->unk_0D0 = 1;
        gCardBattleState->unk_0C2 = gRikuSelectedCard->unk_A5;
        gBtlWork->unk_0A4 = 0;
        func_0807BA54();
    } else {
        func_08080228(w);
        gBtlWork->unk_1CA = 0;
        gBtlWork->flags &= ~0x80;
        gBtlWork->flags &= ~0x20;
        gBtlWork->flags &= ~0x400;
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->unk_0A4 = 0;
        gCardBattleState->unk_000[0] = gRikuSelectedCard;
        gCardBattleState->unk_0D0 = 1;
        gCardBattleState->unk_0C2 = gRikuSelectedCard->unk_A5;
    }
}

u8 func_08080594(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardSlot* c;
    u16 v;
    u16 t;

    if ((gBtlWork->flags & 0x80) == 0) {
        gCardBattleState->unk_000[0] = gRikuSelectedCard;

        if (gRikuBtlWork->unk_0F4 == 1) {
            gCardBattleState->unk_0C2 = gRikuSelectedCard->unk_A5 + 1;
            gRikuSelectedCard->unk_A5++;
            gRikuSelectedCard->unk_A7 = 1;

            if (gRikuSelectedCard->unk_A5 > 9) {
                gRikuSelectedCard->unk_A5 = 9;
            }

            if ((s16)gCardBattleState->unk_0C2 > 9) {
                gCardBattleState->unk_0C2 = 9;
            }

            TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gRikuSelectedCard->cardDef);
        } else if (gRikuBtlWork->unk_0F4 == 21) {
            if (gRikuSelectedCard->unk_A5 != 0) {
                gCardBattleState->unk_0C2 = gRikuSelectedCard->unk_A5 - 1;
                gRikuSelectedCard->unk_A5--;
                gRikuSelectedCard->unk_A7 = 1;
            } else {
                gCardBattleState->unk_0C2 = 0;
                gRikuSelectedCard->unk_A7 = 1;
            }
        } else {
            gCardBattleState->unk_0C2 = gRikuSelectedCard->unk_A5;
        }

        gCardBattleState->unk_0D0 = 1;
        gRikuSelectedCard->unk_78 |= 0x2000;
        gBtlWork->unk_0A4 = 0;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags |= 0x10000000;
    } else {
        if (gBtlWork->unk_0A4 == 0) {
            gRikuSelectedCard->unk_A1 = 0;
            return 1;
        }

        if ((gBtlWork->flags & 0x20) == 0) {
            func_080802D8(w);
        } else {
            func_080802D8(w);
        }

        gBtlWork->flags |= 0x10000000;
    }

    w->unk_B0[w->unk_B8]--;

    if ((gRikuSelectedCard->cardDef->flags & 2) && (gRikuSelectedCard->unk_78 & 0x2000)) {
        gRikuSelectedCard->args.slot->unk_0A = 1;
    }

    if (gRikuSelectedCard->cardDef->flags & 8) {
        gRikuSelectedCard->args.slot->unk_0A = 1;
    }

    if (gRikuSelectedCard->unk_A6 == 1) {
        gRikuSelectedCard->args.slot->unk_0A = 1;

        if ((u16)func_0807885C(w, 0) == 0) {
            gRikuSelectedCard->args.slot->unk_0A = 0;
        }
    }

    w->unk_1C[0] = gRikuSelectedCard;
    gRikuSelectedCard->unk_A1 = 5;
    gRikuSelectedCard->unk_A0 = 50;
    gRikuSelectedCard->args.slot->unk_08 = 1;
    v = gRikuSelectedCard->args.index + 1;

    if ((s16)v >= (s16)w->unk_A8[w->unk_B8]) {
        v = 0;
    }

    do {
        func_080819E8();
    } while (0);

    if (gRikuBtlWork->unk_0F4 == 37) {
        t = func_080792AC();
        func_08081744(w);
        gCardBattleState->unk_0CE = t;
        func_08081740(w, gCardBattleState->unk_0CE);
        func_08081760(w);
        gRikuBtlWork->unk_0F8 = gUnk_08F7CBA8[gRikuBtlWork->unk_0F4].unk_0E;
    }

    gRikuSelectedCard->unk_78 &= ~0x40;
    gRikuSelectedCard = 0;
    c = func_08076674(w, w->unk_B8, &v);

    if (c != 0) {
        args.pool = &w->unk_54[w->unk_B8];
        args.index = v;
        args.unk_0E = w->unk_B8;
        args.slot = c;
        args.unk_0F = w->unk_9C[w->unk_B8];

        if (c->cardId == 0xFFFE) {
            p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
        } else {
            p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
        }

        p->unk_98 = p->unk_94 = gUnk_090352E4[0];
        p->unk_A4 = 0;
        p->unk_A0 = 60;
        p->unk_9C = 4;
        p->x = p->unk_8C;
        p->y = p->unk_90;
        p->unk_78 |= 0x804;
        gRikuSelectedCard = p;
    }

    if (gRikuBtlWork->unk_0F4 == 40 && (gRikuSelectedCard->unk_78 & 0x100000) &&
        w->unk_B0[w->unk_B8] == 1) {
        w->unk_B0[w->unk_B8] = 0;
        gRikuSelectedCard->unk_A1 = 7;
        w->unk_34[w->unk_B8] = 0;
        gRikuSelectedCard = 0;
        w->unk_C0[0] = 1;
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

        if (FadeGetAmount() == 0) {
            FadeFromAmount(2, 16, 20);
        }
    }

    return 1;
}

void func_08080994(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardDisplayWork* q;
    CardSlot* c = 0;
    u16 v;

    w->unk_C4[2] = 0;
    func_08078914(w, w->unk_B8);

    if (func_08078754(w, w->unk_B8) != 0) {
        v = w->unk_A8[w->unk_B8] - 1;
        c = func_08076750(w, w->unk_B8, &v);

        if (c != 0) {
            args.pool = &w->unk_54[w->unk_B8];
            args.index = v;
            args.unk_0E = w->unk_B8;
            args.slot = c;
            args.unk_0F = w->unk_9C[w->unk_B8];

            if (c->cardId == 0xFFFE) {
                p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
            }

            p->unk_80 = p->unk_7C = 0;
            p->unk_98 = p->unk_94 = gUnk_090352E4[0];
            p->unk_A4 = 0;
            p->unk_A0 = 50;
            p->x = p->unk_8C;
            p->y = p->unk_90;
            p->unk_9C = 8;
            p->unk_78 |= 0x814;
            gRikuSelectedCard = p;
            w->unk_C4[2]++;
            w->unk_B0[w->unk_B8]++;
        }
    } else {
        args.pool = &w->unk_54[w->unk_B8];
        args.index = 0xFFFF;
        args.slot = w->slots[w->unk_B8];
        args.unk_0E = w->unk_B8;
        q = TaskCreate(&w->tasks, &gTaskDescNOCard, &args)->work;
        q->unk_80 = q->unk_7C = 0;
        q->unk_98 = q->unk_94 = gUnk_090352E4[0];
        q->x = q->unk_8C;
        q->y = q->unk_90;
        q->unk_A0 = 50;
        q->unk_78 |= 0x806;
        gRikuSelectedCard = q;
    }

    func_080818E4();
}
u8 func_08080B44(CardBattleWork* w) {
    CardDisplayArgs args;
    u16 t;
    u8 n;
    CardSlot* c;
    CardDisplayWork* p;
    u16 v;

    if (!(gRikuSelectedCard->unk_78 & 0x40)) {
        return 1;
    }

    if (gRikuSelectedCard->unk_78 & 2) {
        return 1;
    }

    if (gCardBattleState->unk_0B0 == 112) {
        return 1;
    }

    if (gCardBattleState->unk_0B0 == 109) {
        return 1;
    }

    w->unk_C4[1] = 0;
    gCardBattleState->unk_0E4 = 0;
#ifndef VERSION_EU
    m4aSongNumStart(SONG_SYS_KETEI2);
#endif
    gRikuSelectedCard->unk_78 = (gRikuSelectedCard->unk_78 & ~0x40) | 0x200;
    gRikuSelectedCard->unk_A1 = 6;
    gRikuSelectedCard->unk_9F = w->unk_B9;
    gRikuSelectedCard->unk_A0 = (3 - w->unk_B9) * 4 + 50;
    w->unk_28[w->unk_B9] = gRikuSelectedCard;
    gCardBattleState->unk_024[gCardBattleState->unk_0DF] = gRikuSelectedCard;
    gRikuSelectedCard->args.slot->unk_07 = 1;

    if (gRikuBtlWork->unk_0F4 == 1) {
        n = gRikuSelectedCard->unk_A5 + 1;

        if (n > 9) {
            n = 9;
        }

        gRikuSelectedCard->unk_A5 = n;
        gRikuSelectedCard->unk_A7 = 1;
        TaskCreate(&gCardBattleState->tasks, &gTaskDescNumberPlus, &gRikuSelectedCard->cardDef);
    } else if (gRikuBtlWork->unk_0F4 == 21) {
        if (gRikuSelectedCard->unk_A5 != 0) {
            n = gRikuSelectedCard->unk_A5 - 1;
            gRikuSelectedCard->unk_A5--;
            gRikuSelectedCard->unk_A7 = 1;
        } else {
            n = 0;
            gRikuSelectedCard->unk_A7 = 1;
        }
    } else {
        n = gRikuSelectedCard->unk_A5;
    }

    w->unk_BA += n;
    w->unk_B9++;
    gCardBattleState->unk_0DF++;

    if (w->unk_BA != 0) {
        UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8 + ((w->unk_BA - 1) << 7));
        w->unk_C4[3] = 8;
    }

    w->unk_B0[w->unk_B8]--;

    if (gRikuSelectedCard->cardDef->flags & 8) {
        gRikuSelectedCard->args.slot->unk_0A = 1;
    }

    gRikuSelectedCard->args.slot->unk_08 = 1;
    v = gRikuSelectedCard->args.index + 1;

    if ((s16)v >= (s16)w->unk_A8[w->unk_B8]) {
        v = 0;
    }

    gRikuSelectedCard->unk_78 &= ~0x40;
    gRikuSelectedCard = 0;

    if (gRikuBtlWork->unk_0F4 == 37) {
        t = func_080792AC();
        func_08081744(w);
        gCardBattleState->unk_0CE = t;
        func_08081740(w, gCardBattleState->unk_0CE);
        func_08081760(w);
        gRikuBtlWork->unk_0F8 = gUnk_08F7CBA8[gRikuBtlWork->unk_0F4].unk_0E;
    }

    c = func_08076674(w, w->unk_B8, &v);

    if (c != 0) {
        args.pool = &w->unk_54[w->unk_B8];
        args.index = v;
        args.unk_0E = w->unk_B8;
        args.slot = c;
        args.unk_0F = w->unk_9C[w->unk_B8];

        if (c->cardId == 0xFFFE) {
            p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
        } else {
            p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
        }

        p->unk_98 = p->unk_94 = gUnk_090352E4[0];
        p->unk_A4 = 0;
        p->unk_A0 = 60;
        p->unk_9C = 4;
        p->x = p->unk_8C;
        p->y = p->unk_90;
        p->unk_78 |= 0x804;
        gRikuSelectedCard = p;
    }

    if (gRikuBtlWork->unk_0F4 == 40 && (gRikuSelectedCard->unk_78 & 0x100000) &&
        w->unk_B0[w->unk_B8] == 1) {
        w->unk_B0[w->unk_B8] = 0;
        gRikuSelectedCard->unk_A1 = 7;
        w->unk_34[w->unk_B8] = 0;
        gRikuSelectedCard = 0;
        w->unk_C0[0] = 1;
#ifndef VERSION_EU
        m4aSongNumStart(SONG_SYS_CHAGEF2);
#endif

        if (FadeGetAmount() == 0) {
            FadeFromAmount(2, 16, 20);
        }
    }

    return 1;
}

void func_08080EB4(CardBattleWork* w) {
    CardDisplayWork** q;
    u8 n = w->unk_BA;
    u16 total = 0;
#ifdef VERSION_EU
    CardDisplayWork* previous[3];
#endif
    UnkStruct_080ABA80 arr = *(UnkStruct_080ABA80*)&gUnk_090352E4[6];
    u8 flag;
    u8 skip;
    u8 i;
    u16 result;
#ifdef VERSION_EU
    u8 previousCount;
    s32 j;
    s32 k;
#endif

    if ((s16)gCardBattleState->unk_0C2 > n && n != 0) {
        return;
    }
    skip = 0;
    if (gBtlWork->unk_0F4 == 2 && gCardBattleState->unk_000[0]->cardDef->unk_2A == 0 &&
        gCardBattleState->unk_0E1 == 0) {
        skip = 1;
    }
#ifdef VERSION_EU
    if (gBtlWork->unk_0F4 == 20) {
        for (j = 0; j < gCardBattleState->unk_0D0; j++) {
            if (gCardBattleState->unk_000[j]->cardDef->unk_24 == 22) {
                skip = 1;
            }
        }
    }
    if (gBtlWork->unk_0F4 == 29) {
        for (k = 0; k < gCardBattleState->unk_0D0; k++) {
            if (gCardBattleState->unk_000[k]->cardDef->unk_2A == 2 &&
                !(gCardBattleState->unk_000[k]->cardDef->flags & 8)) {
                skip = 1;
            }
        }
    }
#else
    if (gBtlWork->unk_0F4 == 20 && gCardBattleState->unk_000[0]->cardDef->unk_24 == 22 &&
        gCardBattleState->unk_0E1 == 0) {
        skip = 1;
    }
    if (gBtlWork->unk_0F4 == 29 && gCardBattleState->unk_000[0]->cardDef->unk_2A == 2 &&
        gCardBattleState->unk_0E1 == 0) {
        skip = 1;
    }
#endif
    if (skip != 0) {
        return;
    }
    for (i = 0; i < gCardBattleState->unk_0D0; i++) {
        gCardBattleState->unk_000[i]->unk_78 |= 0x200000;
    }
    gBtlWork->flags |= 0x800000;
    if ((s16)gCardBattleState->unk_0C2 != n) {
        if (n == 0) {
            gBtlWork->unk_1CA = -(u8)gCardBattleState->unk_0C2;
            if ((s8)gBtlWork->unk_1CA < -9) {
                gBtlWork->unk_1CA = -9;
            }
        } else {
            gBtlWork->unk_1CA = (u8)gCardBattleState->unk_0C2 - n;
            if ((s8)gBtlWork->unk_1CA < -9) {
                gBtlWork->unk_1CA = -9;
            }
        }
        func_0807BA54();
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x10000000;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags &= ~0x20ULL;
        func_08080268(w);
#ifndef VERSION_EU
        if (!(gBtlWork->flags & 0x4000)) {
            result = func_080AC5E8(w->unk_28, w->unk_B9, w->unk_BA, &arr, &flag);
        } else {
            result = func_080AD144(w->unk_28, w->unk_B9, w->unk_BA, &arr, &flag, 1);
        }
        if (result == 52) {
            for (i = 0; i < gCardBattleState->unk_0D0; i++) {
                if (gCardBattleState->unk_000[i]->args.slot->unk_08 == 1) {
                    gCardBattleState->unk_000[i]->args.slot->unk_0A = 1;
                    gCardBattleState->unk_000[i]->unk_78 |= 0x80000000;
                }
            }
        }
#endif
        for (i = 0; i < w->unk_B9; i++) {
            total += w->unk_28[i]->unk_A5;
        }
        gCardBattleState->unk_0C2 = total;
#ifdef VERSION_EU
        previousCount = gCardBattleState->unk_0D0;
#endif
        gCardBattleState->unk_0D0 = w->unk_B9;
        for (i = 0; i < w->unk_B9; i++) {
#ifdef VERSION_EU
            previous[i] = gCardBattleState->unk_000[i];
#endif
            q = gCardBattleState->unk_000;
            q += i;
            *q = w->unk_28[i];
            w->unk_28[i]->unk_78 |= 0x2000;
            if (w->unk_28[i]->cardDef->flags & 2) {
                w->unk_28[i]->args.slot->unk_0A = 1;
            }
        }
        *(u8*)&gBtlWork->unk_0A4 = 0;
        gCardBattleState->unk_0E2 = 1;
        m4aSongNumStart(SONG_BTL_GARD);
#ifdef VERSION_EU
        if (!(gBtlWork->flags & 0x4000)) {
            result = func_080AC5E8(w->unk_28, w->unk_B9, w->unk_BA, &arr, &flag);
        } else {
            result = func_080AD144(w->unk_28, w->unk_B9, w->unk_BA, &arr, &flag, 1);
        }
        if (result == 52) {
            for (i = 0; i < previousCount; i++) {
                if (previous[i]->args.slot->unk_08 == 1) {
                    previous[i]->args.slot->unk_0A = 1;
                    previous[i]->unk_78 |= 0x80000000;
                }
            }
        }
#endif
    } else {
        gBtlWork->unk_1CA = 0;
        func_08080268(w);
        m4aSongNumStart(SONG_SYS_DROW);
        gBtlWork->flags &= ~0x400ULL;
        gBtlWork->flags &= ~0x20ULL;
        gBtlWork->flags &= ~0x80ULL;
        gCardBattleState->unk_0E2 = 0;
        *(u8*)&gBtlWork->unk_0A4 = 0;
    }
}

void func_08081210(CardBattleWork* w) {
    CardDisplayWork** q;
    CardDisplayWork* p;
    u64 flags;
    u8 i;
    u8 n;

    for (i = 0, n = 0; i < w->unk_B9; i++) {
        if (w->unk_28[i]->unk_78 & 0x40) {
            n++;
        }
    }

    if (n < w->unk_B9) {
        return;
    }

    gCardBattleState->unk_0C0 = 0;
    gCardBattleState->unk_0E4 = 0;
    w->unk_C4[1] = 0;
    flags = gBtlWork->flags;

    if ((flags & 0x80) == 0) {
        gCardBattleState->unk_0D0 = w->unk_B9;

        for (i = 0; i < w->unk_B9; i++) {
            q = gCardBattleState->unk_000;
            q += i;
            *q = w->unk_28[i];
            w->unk_28[i]->unk_A0 = i * 4 + 50;

            if (w->unk_28[i]->cardDef->flags & 2) {
                w->unk_28[i]->args.slot->unk_0A = 1;
            }

            w->unk_28[i]->unk_78 |= 0xA000;
        }

        gCardBattleState->unk_0C2 = w->unk_BA;
        gBtlWork->unk_0A4 = 0;
        gBtlWork->flags |= 0x80;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x10000000;
        gCardBattleState->unk_0E2 = 1;
    } else {
        if (gBtlWork->unk_0A4 == 0) {
            return;
        }

        if ((flags & 0x20) == 0) {
            func_08080EB4(w);
            gBtlWork->flags |= 0x10000000;
        } else {
            func_08080EB4(w);
            gBtlWork->flags |= 0x10000000;
        }
    }

    for (i = 0; i < w->unk_B9; i++) {
        w->unk_28[i]->args.slot->unk_07 = 0;

        if (w->unk_28[i]->cardDef->flags & 2) {
            w->unk_28[i]->args.slot->unk_0A = 1;
        } else if (i == 0 && gRikuBtlWork->unk_0F4 != 15) {
            w->unk_28[0]->args.slot->unk_0A = 1;
        }
    }

    if (func_0807885C(w, 0) == 0) {
        for (i = 0; i < w->unk_B9; i++) {
            if (w->unk_28[i]->args.unk_0E == 0) {
                w->unk_28[i]->args.slot->unk_0A = 0;
                break;
            }
        }
    }

    i = 0;

    if (i < w->unk_B9) {
        do {
            p = 0;
            n = i;
            w->unk_1C[n] = w->unk_28[n];
            w->unk_28[n]->unk_A1 = 5;
            w->unk_28[n] = p;
            i = ++n;
        } while (i < w->unk_B9);
    }

    func_080819E8();
    w->unk_B9 = 0;
    gCardBattleState->unk_0DF = 0;
    w->unk_BA = 0;
    func_0807AE78(w);
    w->unk_C4[1] = 0;
}

u8 func_080814BC(CardBattleWork* w) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    CardDisplayWork* q;
    CardSlot* c;
    u16 v;
    CardDisplayWork** pp;

    if ((gRikuSelectedCard->unk_78 & 2) == 0) {
        if (gCardBattleState->unk_0CE == 0) {
            gCardBattleState->unk_0CE = gRikuSelectedCard->cardDef->unk_24;
            func_08081740(w, gCardBattleState->unk_0CE);
            func_08081760(w);
            pp = &gRikuSelectedCard;
        } else {
            func_08081744(w);
            gCardBattleState->unk_0CE = gRikuSelectedCard->cardDef->unk_24;
            func_08081740(w, gCardBattleState->unk_0CE);
            func_08081760(w);
            gCardBattleState->unk_0EC = 1;
            pp = &gRikuSelectedCard;
        }

        gRikuSelectedCard->args.slot->unk_0A = 1;
        gRikuSelectedCard->unk_A1 = 10;
        gRikuSelectedCard->unk_A0 = 50;
        gRikuSelectedCard->unk_78 &= ~0x40;

        if (w->unk_BA > 1) {
            UpdateSpriteFrameTiles(w->tiles, gUnk_09EF12E8[0], gUnk_093FBAB8 + ((w->unk_BA - 1) << 7));
            w->unk_C4[3] = 8;
        }

        gRikuSelectedCard->args.slot->unk_08 = 1;
        q = gRikuSelectedCard;
        v = q->args.index + 1;

        if ((s16)v >= (s16)w->unk_A8[w->unk_B8]) {
            v = 0;
        }

        q->unk_78 &= ~0x40;
        gRikuSelectedCard = 0;
        w->unk_B0[w->unk_B8]--;
        c = func_08076674(w, w->unk_B8, &v);

        if (c != 0) {
            args.pool = &w->unk_54[w->unk_B8];
            args.index = v;
            args.unk_0E = w->unk_B8;
            args.slot = c;
            args.unk_0F = w->unk_9C[w->unk_B8];

            if (c->cardId == 0xFFFE) {
                p = TaskCreate(&w->tasks, &gTaskDescReloadCard, &args)->work;
            } else {
                p = TaskCreate(&w->tasks, &gUnk_09EE49CC, &args)->work;
            }

            p->unk_98 = p->unk_94 = gUnk_090352E4[0];
            p->unk_A4 = 0;
            p->unk_A0 = 60;
            p->unk_9C = 4;
            p->x = p->unk_8C;
            p->y = p->unk_90;
            p->unk_78 |= 0x844;
            gRikuSelectedCard = p;
        } else {
            args.pool = &w->unk_54[w->unk_B8];
            args.index = 0xFFFF;
            args.slot = w->slots[w->unk_B8];
            args.unk_0E = w->unk_B8;
            p = TaskCreate(&w->tasks, &gTaskDescNOCard, &args)->work;
            p->unk_98 = p->unk_94 = gUnk_090352E4[0];
            p->unk_A4 = 0;
            p->unk_A0 = 50;
            p->unk_9C = 4;
            p->unk_78 |= 0x846;
            gRikuSelectedCard = p;
        }

        if (*pp == 0) {
            w->unk_C0[w->unk_B8] = 1;
        }
    }

    return 1;
}

void func_08081740(CardBattleWork* w, u16 n) {
}
void func_08081744(CardBattleWork* w) {
    gRikuBtlWork->unk_0F4 = gCardBattleState->unk_0CE;
}

void func_08081760(CardBattleWork* w) {
    if (gBtlWork->unk_0F4 != 41) {
        gRikuBtlWork->unk_0F4 = gCardBattleState->unk_0CE;
    } else {
        gRikuBtlWork->unk_0F4 = 0;
        gCardBattleState->unk_0CE = 0;
    }

#ifdef VERSION_EU
    if (gRikuBtlWork->unk_0F4 == 41) {
        if (gBtlWork->unk_0F4 == 47 && (gBtlWork->flags & 0x20000000)) {
            gBtlWork->flags &= ~2;
        }

        gCardBattleState->unk_0CC = 0;
        gBtlWork->unk_0F4 = 0;
        gBtlWork->unk_0F8 = 0;
        gRikuBtlWork->unk_0F4 = 0;
        gRikuBtlWork->unk_0F8 = 0;
    }
#endif

    if (gCardBattleState->unk_0CE == 45) {
        if (gBtlWork->unk_0F4 != 0) {
            gCardBattleState->unk_0CE = gCardBattleState->unk_0CC;
            gRikuBtlWork->unk_0F4 = gBtlWork->unk_0F4;
        } else {
            gBtlWork->unk_0F4 = 0;
            gCardBattleState->unk_0CE = 0;
        }
    }

    if (gRikuBtlWork->unk_0F4 == 47) {
        w->unk_9C[0] = 2;
        w->unk_9C[1] = 2;
    }

#ifndef VERSION_EU
    if (gRikuBtlWork->unk_0F4 == 41) {
        gCardBattleState->unk_0CC = 0;
        gBtlWork->unk_0F4 = 0;
        gBtlWork->unk_0F8 = 0;
        gRikuBtlWork->unk_0F4 = 0;
        gRikuBtlWork->unk_0F8 = 0;
    }
#endif
}

u8 func_08081828(void) {
    return gCardBattleState->unk_0ED;
}

u8 func_08081838(void) {
    return gCardBattleState->unk_0D4;
}

u8 func_08081848(void) {
    return gCardBattleState->unk_0C2;
}

s32 func_08081858(void) {
    if (gRikuSelectedCard != 0) {
        return gRikuSelectedCard->cardDef->unk_24;
    }

    return 145;
}

u8 func_08081870(void) {
    if (gRikuSelectedCard != 0) {
        return gRikuSelectedCard->unk_A5;
    }

    return 0xFF;
}

u8 func_08081888(void) {
    if (gRikuBtlWork->unk_0F4 == 38) {
        if (gRikuSelectedCard->cardDef->unk_2A != 1) {
            return 1;
        }

        if (!(gRikuSelectedCard->cardDef->flags & 4)) {
            return 1;
        }

        return 0;
    } else if (gRikuBtlWork->unk_0F4 == 39) {
        if (gRikuSelectedCard->cardDef->unk_2A != 1) {
            return 1;
        }

        if (gRikuSelectedCard->cardDef->flags & 4) {
            return 1;
        }

        return 0;
    }

    return 1;
}

void func_080818E4(void) {
    switch (gRikuBtlWork->unk_0F4) {
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
        gRikuBtlWork->unk_0F8--;
        break;
    }
}

void func_080819E8(void) {
    if (gRikuBtlWork->unk_0F4 == 50) {
        gRikuBtlWork->unk_0F8--;
    }
}

void func_08081A04(CardBattleWork* w) {
    gCardBattleState->unk_0F8 = 0;
    gCardBattleState->unk_0FE = 0;
    gCardBattleState->unk_102 = 4;
    gCardBattleState->unk_106 = 2;
    gCardBattleState->unk_108[1] = 0;
}

void func_08081A3C(CardDisplayWork* p, CardDisplayArgs* a) {
    vu32 zero;
    u16 v;

    zero = 0;
    CpuSet((void*)&zero, p, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(CardDisplayWork) / 4);
    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->tiles4 = 0;
    p->tiles5 = 0;
    p->unk_18 = 0;
    p->palette = 0;
    p->unk_1C = 0;
    p->unk_20 = 0;
    p->args = *a;
    p->unk_78 = 0;
    v = p->args.index;

    if ((s16)v != -1) {
        func_08082DA4(&p->args, &p->cardDef, (u8)v);

        if (p->args.slot->cardId == 0xFFFE) {
            p->unk_78 |= 0x100000;
        }
    } else {
        p->unk_78 = 2;
    }

    if (p->args.slot->cardId & 0x8000) {
        p->unk_A6 = 1;
    } else {
        p->unk_A6 = 0;
    }

    p->unk_54 = 0;
    p->unk_58 = 0x100;
    p->unk_5F = 0;
    p->unk_5E = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
    p->unk_94 = 0;
    p->unk_98 = 0;
    p->unk_A1 = 0;
    p->unk_A0 = 80;
    p->unk_9C = 4;
    p->unk_A2 = 0;
    p->unk_84 = 0x2400;
    p->unk_88 = 0x2400;
    p->unk_A3 = 0;
    p->unk_8C = gUnk_0903401C[5][0];
    p->unk_90 = gUnk_0903401C[5][1];
    p->x = gUnk_0903401C[4][0];
    p->y = gUnk_0903401C[4][1];

    if (p->cardDef != 0) {
        p->unk_A5 = p->cardDef->unk_20;
    } else {
        p->unk_A5 = 0;
    }

    p->unk_A7 = 0;
    p->unk_78 |= 0x24;
    p->unk_78 &= ~0x40;
}
u8 func_08081B70(CardDisplayWork* p, void* a) {
    if ((p->unk_78 & 0x84) == 4) {
        func_0807C33C(p);
        p->unk_78 |= 0x80;
    }

    if (p->unk_78 & 0x10) {
        p->unk_9C = 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080829D0);
        return 1;
    }

    if (p->unk_78 & 4) {
        if ((s16)p->unk_9C > 0) {
            p->unk_78 &= ~0x40;
            ApproachValue(&p->unk_54, 0x100, p->unk_9C);
            p->unk_9C--;
        } else {
            p->unk_78 |= 0x40;
        }
    } else if ((s16)p->unk_9C > 0) {
        p->unk_78 &= ~0x40;
        ApproachValue(&p->unk_54, 0, p->unk_9C);

        if (p->unk_78 & 0x80) {
            func_0807C39C(p);
            p->unk_78 &= ~0x80;
        }

        p->unk_9C--;
    } else {
        return 0;
    }

    if (p->unk_78 & 0x1000) {
        return 1;
    }

    ApproachValue(&p->x, p->unk_8C, p->unk_9C);
    ApproachValue(&p->y, p->unk_90, p->unk_9C);
    p->unk_5F += 4;

    if (!(p->unk_78 & 0x20)) {
        p->unk_78 &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082A64);
    }

    return func_08082C98(p, a);
}

static void card_2(CardDisplayWork* p) {
    void* gfx;
    ObjAffine* aff;
    u16 y;
    s16 sy;
    u16 flags;
    u8 j;

    gfx = p->cardDef->gfx;

    if (func_080A42C8() == 1) {
        y = p->y >> 8;
    } else {
        y = (p->y >> 8) + (gSineTable[p->unk_5F] >> 8);
    }

    if (!(p->unk_78 & 0x20)) {
        return;
    }

    if (!(p->unk_78 & 0x80)) {
        return;
    }

    if (p->unk_54 == 0) {
        return;
    }

    if (!(p->unk_78 & 0x200)) {
        u8 j;

        if (gRikuBtlWork->unk_0F4 == 7) {
            return;
        }

        aff = AllocObjAffine(p->unk_5E, p->unk_54, p->unk_58, 0);
        flags = 0x410;
        DrawSprite(p->x >> 8, y, gUnk_08F709B0[p->cardDef->unk_2A].gfx, gCardBattleState->tiles[p->cardDef->unk_2A], gCardBattleState->palette, aff, flags, (u16)(p->unk_A0 - 1));
        DrawSprite(p->x >> 8, y, gfx, p->tiles, p->palette, aff, flags, p->unk_A0);
        j = p->unk_A5;

        if (p->cardDef->unk_2A == 3) {
            return;
        }

        if (p->unk_A7 != 0) {
            DrawSprite(p->x >> 8, y, gUnk_09EE98C0[j], gCardBattleState->tiles7, gCardBattleState->palette2, aff, flags, (u16)(p->unk_A0 - 2));
        } else if (p->unk_A6 != 0) {
            DrawSprite(p->x >> 8, y, gUnk_09EE9894[j], gCardBattleState->tiles6, gCardBattleState->palette2, aff, flags, (u16)(p->unk_A0 - 2));
        } else {
            DrawSprite(p->x >> 8, y, gUnk_09EE981C[j], gCardBattleState->tiles5, gCardBattleState->palette, aff, flags, (u16)(p->unk_A0 - 2));
        }

        if (p->unk_A6 != 0) {
            DrawSprite(p->x >> 8, y, gCardBattleState->gfx, gCardBattleState->unk_040, gCardBattleState->palette, aff, flags, (u16)(p->unk_A0 - 3));
        }

        return;
    }

    if (gRikuBtlWork->unk_0F4 == 28) {
        return;
    }

    aff = AllocObjAffine(0, p->unk_54, p->unk_58, 0);
    flags = 0x410;
    sy = y;
    DrawSprite(p->x >> 8, sy, p->cardDef->gfx2, p->tiles, p->palette, aff, flags, p->unk_A0);
    j = p->unk_A5;

    if (p->cardDef->unk_2A == 3) {
        return;
    }

    if (p->unk_A7 != 0) {
        DrawSprite((p->x >> 8) - 3, sy - 4, gUnk_09EE981C[j], gCardBattleState->tiles7, gCardBattleState->palette2, aff, flags, (u16)(p->unk_A0 - 10));

        if (p->unk_A6 != 0) {
            DrawSprite(p->x >> 8, sy, gCardBattleState->gfx2, gCardBattleState->unk_050, gCardBattleState->palette, aff, flags, (u16)(p->unk_A0 - 11));
        }
    } else if (p->unk_A6 != 0) {
        DrawSprite((p->x >> 8) - 3, sy - 4, gUnk_09EE981C[j], gCardBattleState->tiles6, gCardBattleState->palette2, aff, flags, (u16)(p->unk_A0 - 10));
        DrawSprite(p->x >> 8, sy, gCardBattleState->gfx2, gCardBattleState->unk_050, gCardBattleState->palette, aff, flags, (u16)(p->unk_A0 - 11));
    } else {
        DrawSprite((p->x >> 8) - 3, sy - 4, gUnk_09EE981C[j], gCardBattleState->tiles5, gCardBattleState->palette, aff, flags, (u16)(p->unk_A0 - 10));
    }
}

void NO_Card_2(CardDisplayWork* p) {
    void* gfx;
    u16 y;

    gfx = gUnk_08F709B0[0].gfx2;

    if (func_080A42C8() == 1) {
        y = p->y >> 8;
    } else {
        y = (p->y >> 8) + (gSineTable[p->unk_5F] >> 8);
    }

    if (p->unk_78 & 0x20) {
        if (p->unk_78 & 0x80) {
            if (p->unk_54 != 0) {
                if (gRikuBtlWork->unk_0F4 != 7) {
                    DrawSprite(p->x >> 8, y, gfx, p->tiles2, gCardBattleState->palette, 0, 0x410, (u16)(p->unk_A0 - 1));
                }
            }
        }
    }
}

void func_080820F4(CardDisplayWork* p) {
    func_0807C39C(p);

    if (p->unk_20 != 0) {
        EwramFree(p->unk_20);
    }
}

void func_0808210C(CardDisplayWork* p) {
    if (p->unk_A1 == 6) {
        return;
    }

    if (p->unk_54 == 0) {
        if (p->unk_78 & 0x80) {
            func_0807C39C(p);
            p->unk_78 &= ~0x80;
        }
    } else {
        if ((p->unk_78 & 0x80) == 0) {
            func_0807C33C(p);
            p->unk_78 |= 0x80;
        }
    }
}

u8 func_08082154(CardDisplayWork* p, void* a) {
    if (gBtlWork->flags & 0x20) {
        p->unk_9C = 8;
        p->unk_9E = 8;
        gCardBattleState->unk_0D0 = 0;
        gCardBattleState->unk_0C2 = 0;
        gBtlWork->flags &= ~0x80;
        gBtlWork->flags &= ~0x20;
        gBtlWork->flags &= ~0x10000000;

        if (p->cardDef->unk_2A == 0) {
            func_080838CC();
        }

        SetTaskUpdate(a, (TaskUpdateFunc)func_08082AE4);
    } else if (p->unk_78 & 0x200000) {
        p->unk_A0 -= 4;
        p->unk_84 = 0x500;
        p->unk_9C = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082E0C);
    }

    return 1;
}

u8 func_08082224(CardDisplayWork* p, void* a) {
    ApproachValue(&p->x, 0x7800, p->unk_9C);
    ApproachValue(&p->y, 0x8400, p->unk_9C);
    p->unk_A0 = 80;

    if ((s16)p->unk_9C > 0) {
        p->unk_9C--;
    } else {
        p->unk_9C |= 0xFFFF;
    }

    if (gBtlWork->flags & 0x80) {
        if (p->unk_78 & 0x2000) {
            if ((s16)p->unk_9C == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_08082154);
            }
        } else if ((s16)p->unk_9C <= 2) {
            p->unk_A0 -= 4;
            p->unk_84 = 0x500;
            p->unk_9C = 0x100;
            p->unk_7C = 16;
            p->unk_9E = 1;
            p->unk_78 |= 0x2000;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);

            if (p->cardDef->flags & 2) {
                p->args.slot->unk_06 = 0;
            }

            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)p->unk_9C <= 2) {
        p->unk_A0 -= 4;
        p->unk_84 = 0x500;
        p->unk_9C = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
    }

    return 1;
}
u8 func_08082348(CardDisplayWork* p, void* a) {
    ApproachValue(&p->unk_8C, gUnk_0903404C[0], p->unk_9C);
    ApproachValue(&p->unk_90, gUnk_0903404C[1], p->unk_9C);
    ApproachValue(&p->unk_84, p->unk_88, p->unk_9C);
    ApproachValue(&p->unk_54, 0x100, p->unk_9C);
    ApproachValue(&p->unk_58, 0x100, p->unk_9C);

    if ((s16)p->unk_9C > 0) {
        p->unk_9C--;
    } else {
        p->unk_9C = 0;
    }

    func_08082BF8(p);

    switch (p->unk_9F) {
    case 0:
        p->unk_A0 = 50;
        break;
    case 1:
        p->unk_A0 = 40;
        break;
    case 2:
        p->unk_A0 = 60;
        break;
    }

    if (p->unk_78 & 0x200000) {
        p->unk_A0 -= 4;
        p->unk_84 = 0x500;
        p->unk_9C = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        gCardBattleState->unk_0E2 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082E0C);
    }

    if (gBtlWork->flags & 0x20) {
        p->unk_9C = 8;
        p->unk_9E = 8;
        gCardBattleState->unk_0D0--;
        gCardBattleState->unk_0C2 = 0;

        if (gCardBattleState->unk_0D0 == 0) {
            gBtlWork->flags &= ~0x20;
            gBtlWork->flags &= ~0x80;
            func_080838A0();
        }

        gCardBattleState->unk_0E2 = 0;
        gBtlWork->flags &= ~0x10000000;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082AE4);
    }

    return 1;
}
u8 func_080824C8(CardDisplayWork* p, void* a) {
    ApproachValue(&p->unk_8C, gUnk_0903404C[0], p->unk_9C);
    ApproachValue(&p->unk_90, gUnk_0903404C[1], p->unk_9C);
    ApproachValue(&p->unk_84, p->unk_88, p->unk_9C);
    ApproachValue(&p->unk_54, 0x100, p->unk_9C);
    ApproachValue(&p->unk_58, 0x100, p->unk_9C);

    if ((s16)p->unk_9C > 0) {
        p->unk_9C--;
    } else {
        p->unk_9C = 0;
    }

    func_08082BF8(p);

    if (gBtlWork->flags & 0x80) {
        if (p->unk_78 & 0x2000) {
            if ((s16)p->unk_9C == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_08082348);
            }
        } else if ((s16)p->unk_9C <= 2) {
            p->unk_A0 -= 4;
            p->unk_84 = 0x500;
            p->unk_9C = 0x100;
            p->unk_7C = 16;
            p->unk_9E = 1;
            gCardBattleState->unk_0C0 = 0;
            gCardBattleState->unk_0E2 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
            m4aSongNumStart(SONG_SYS_DROW);
        }
    } else if ((s16)p->unk_9C <= 2) {
        p->unk_A0 -= 4;
        p->unk_84 = 0x500;
        p->unk_9C = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        gCardBattleState->unk_0E2 = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
    }

    return 1;
}
u8 func_08082618(CardDisplayWork* p, void* a) {
    u8 (*f)(CardDisplayWork*, void*);
    s32 v;

    func_0807C2EC(p);

    if (!(p->unk_78 & 0x10000000)) {
        f = func_080827E0;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(p, a);
    }

    if (p->unk_78 & 0x40000000) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082FF0);
        return 1;
    }

    if (p->unk_A1 == 5) {
        if (p->unk_78 & 0x8000) {
            p->unk_9C = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gUnk_09034054[p->unk_9F] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            f = func_08082348;
        } else {
            p->unk_9C = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gUnk_09034054[p->unk_9F] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            f = func_080824C8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)f);
        p->unk_78 &= ~0x200;
        func_08082F24(p);
        return f(p, a);
    }

    if ((s16)p->unk_9C > 0) {
        p->unk_9C--;
        return 1;
    }

    if (p->unk_78 & 0x20) {
        switch (p->unk_A2) {
        case 0:
            p->y -= 0x80;
            v = gUnk_0903401C[3 - p->unk_9F][1] - 0x200;

            if (p->y <= v) {
                p->y = v;
                p->unk_A2 = 1;
            }
            break;
        case 1:
            p->y += 0x200;
            v = gUnk_0903401C[3 - p->unk_9F][1];

            if (p->y >= v) {
                p->y = v;
                p->unk_A2 = 0;
                p->unk_9C = 16;
            }
            break;
        }
    } else {
        ApproachValue(&p->x, gUnk_0903401C[4][0], p->unk_9C);
        ApproachValue(&p->y, gUnk_0903401C[4][1], p->unk_9C);
    }

    p->unk_5F += 4;
    return 1;
}
u8 func_080827E0(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);
    u16 t;

    if (gBtlWork->unk_070 == 1) {
        return 1;
    }

    func_0807C2EC(p);

    if (p->unk_78 & 0x20) {
        ApproachValue(&p->x, gUnk_0903401C[3 - p->unk_9F][0], p->unk_9C);
        ApproachValue(&p->unk_58, 179, p->unk_9C);
        ApproachValue(&p->y, gUnk_0903401C[3 - p->unk_9F][1], p->unk_9C);
        ApproachValue(&p->unk_54, 179, p->unk_9C);
    } else {
        ApproachValue(&p->x, gUnk_0903401C[4][0], p->unk_9C);
        ApproachValue(&p->y, gUnk_0903401C[4][1], p->unk_9C);
    }

    t = p->unk_9C;

    if ((s16)t > 0) {
        p->unk_9C = t - 1;
        p->unk_78 &= ~0x40;
    } else {
        p->unk_9C = 0;
        p->unk_54 = 0x100;
        p->unk_58 = 0x100;
        p->unk_78 |= 0x40;

        if (p->unk_78 & 0x10000000) {
            p->unk_9C = p->unk_9F * 8;
            fn = func_08082618;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(p, a);
        }
    }

    if (p->unk_78 & 0x40000000) {
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082FF0);
        return 1;
    }

    if (p->unk_A1 == 5) {
        if (p->unk_78 & 0x8000) {
            p->unk_9C = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gUnk_09034054[p->unk_9F] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_08082348;
        } else {
            p->unk_9C = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gUnk_09034054[p->unk_9F] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            fn = func_080824C8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)fn);
        p->unk_78 &= ~0x200;
        func_08082F24(p);
        return fn(p, a);
    }

    p->unk_5F += 4;
    return 1;
}

u8 func_080829D0(CardDisplayWork* p, void* a) {
    u8 (*f)(CardDisplayWork*, void*);

    if (!(p->unk_78 & 0x20)) {
        f = func_08082A64;
        SetTaskUpdate(a, (TaskUpdateFunc)f);
        return f(p, a);
    }

    ApproachValue(&p->unk_54, 0x100, p->unk_9C);
    p->unk_9C--;

    if (p->unk_9C == 0) {
        p->unk_78 &= ~0x10;
        p->unk_54 = 0x100;

        if (p->unk_78 & 0x100000) {
            gCardBattleState->unk_0E8 = 0;
            SetTaskUpdate(a, (TaskUpdateFunc)Reload_Card_1);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)func_08081B70);
        }
    }

    return 1;
}

u8 func_08082A64(CardDisplayWork* p, void* a) {
    u8 (*fn)(CardDisplayWork*, void*);

    if (p->unk_A1 == 7) {
        return 0;
    }

    p->unk_84 += -p->unk_84 >> 1;
    p->x += (gUnk_0903401C[4][0] - p->x) >> 1;
    p->y += (gUnk_0903401C[4][1] - p->y) >> 1;

    if (p->unk_78 & 0x20) {
        if (p->unk_78 & 0x100000) {
            fn = Reload_Card_1;
            SetTaskUpdate(a, (TaskUpdateFunc)fn);
            return fn(p, a);
        } else {
            do {
                fn = func_08081B70;
                SetTaskUpdate(a, (TaskUpdateFunc)fn);
            } while (0);

            return fn(p, a);
        }
    }

    return 1;
}

u8 func_08082AE4(CardDisplayWork* p) {
    ApproachValue(&p->y, 0x8200, p->unk_9C);
    *(u16*)&p->unk_9C =
        *(s16*)&p->unk_9C > 0 ? p->unk_9C - 1 : 0;

    if (*(s16*)&p->unk_9C == 0) {
        *(u16*)&p->unk_9C = 0;
        p->unk_5E += p->unk_9E;
        p->unk_9E++;

        if (p->unk_54 <= 25) {
            return 0;
        }

        p->unk_54 -= 25;
        p->unk_58 -= 25;
    }

    return 1;
}

u8 func_08082B48(CardDisplayWork* p) {
    p->unk_A1 = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->unk_9C;
    p->unk_9C++;
    p->x -= gSineTable[(p->unk_7C & 0xFF) + 0x40];
    p->unk_5E += p->unk_9E;
    p->unk_54 -= 5;
    p->unk_58 -= 5;

    if (func_0807CE68(p)) {
        p->unk_78 &= ~0x800;
        func_0807C39C(p);
        gBtlWork->flags &= ~0x10000000;
        p->unk_78 &= ~0x80;
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
u8 func_08082C98(CardDisplayWork* p, void* a) {
    switch (p->unk_A1) {
    case 5:
        p->unk_9C = 10;
        p->unk_A0 -= 4;
        p->unk_54 = 0x100;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082224);
        return 1;
    case 6:
        p->unk_9C = 8;
        p->unk_A0 -= 4;
        func_08082EFC(p);
        p->unk_78 |= 0x200;
        p->unk_78 |= 0x80;
        p->unk_78 &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080827E0);
        return 1;
    case 8:
        p->unk_A0 -= 4;
        p->unk_84 = 0x500;
        p->unk_9C = 0x100;
        p->unk_7C = 16;
        p->unk_9E = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082B48);
        return 1;
    case 7:
        p->unk_84 = 0x500;
        p->unk_9C = 0x100;
        return 0;
    case 10:
        p->unk_9C = 10;
        p->unk_A0 -= 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082F50);
        return 1;
    case 9:
    default:
        UpdateRikuCardValue(p);
        break;
    }

    return 1;
}

void func_08082DA4(CardDisplayArgs* a, CardDef** out, u8 index) {
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
        q = &gCardBattleState->unk_0B8;
        *out = &gCardDefs[*q & CARD_ID_MASK];
        *q = 0x3B6;
    }
}

u8 func_08082E0C(CardDisplayWork* p, void* a) {
    p->unk_A1 = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->unk_9C >> 1;
    p->unk_9C++;
    p->x -= 0x200;
    p->unk_5E += 16;

    if (!(p->unk_78 & 0x400000)) {
        p->unk_54 -= 10;

        if (p->unk_54 >= -2 && p->unk_54 <= 2) {
            p->unk_54 = -10;
        }

        if (p->unk_54 <= -0x100) {
            p->unk_54 = -0x100;
            p->unk_78 |= 0x400000;
        }
    } else {
        p->unk_54 -= 10;

        if (p->unk_54 >= -2 && p->unk_54 <= 2) {
            p->unk_54 = 10;
        }

        if (p->unk_54 >= 0x100) {
            p->unk_54 = 0x100;
            p->unk_78 &= ~0x400000;
        }
    }

    if (func_0807CE68(p)) {
        p->unk_78 &= ~0x800;
        func_0807C39C(p);
        p->unk_78 &= ~0x80;
        gBtlWork->flags &= ~0x10000000;
        return 0;
    }

    return 1;
}
void func_08082EFC(CardDisplayWork* p) {
    void* tiles;
    void* pal;

    func_0807C39C(p);
    tiles = p->cardDef->tiles2;
    pal = p->cardDef->palette2;
    p->tiles = LoadObjTiles(tiles, 256);
    p->palette = LoadObjPalette(pal, 32);
}

void func_08082F24(CardDisplayWork* p) {
    if (p->tiles != 0) {
        ReleaseObjTiles(p->tiles);
    }

    if (p->palette != 0) {
        ReleaseObjPalette(p->palette);
    }

    p->tiles = 0;
    p->palette = 0;
    func_0807C33C(p);
}

u8 func_08082F50(CardDisplayWork* p) {
    u8 arg;

    p->unk_A1 = 0;
    ApproachValue(&p->x, 0xD800, p->unk_9C);
    ApproachValue(&p->unk_58, 0x99, p->unk_9C);
    ApproachValue(&p->y, 0x6400, p->unk_9C);
    ApproachValue(&p->unk_54, 0x99, p->unk_9C);

    if ((s16)p->unk_9C > 0) {
        p->unk_9C--;
        return 1;
    }

    arg = 2;
    gRikuBtlWork->unk_0F8 = gUnk_08F7CBA8[gRikuBtlWork->unk_0F4].unk_0E;
    TaskCreate(&gCardBattleState->tasks, &gTaskDescHCEffectName, &arg);
    return 0;
}

u8 func_08082FF0(CardDisplayWork* p) {
    s32 r;

    if (p->unk_54 <= 24) {
        p->args.slot->unk_07 = r = 0;
        return r;
    }

    p->unk_54 -= 12;
    p->unk_58 += 12;

    if (p->unk_58 > 0x1FF) {
        p->unk_58 = 0x200;
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
    p->unk_18 = 0;
    p->palette = 0;
    p->unk_1C = 0;
    p->unk_20 = EwramAlloc(sizeof(UnkStruct_08095A5C));
    zero2 = 0;
    CpuSet((void*)&zero2, p->unk_20, CPU_SET_SRC_FIXED | CPU_SET_32BIT | sizeof(UnkStruct_08095A5C) / 4);
    p->args = *a;
    p->unk_20->unk_65 = 0;
    p->unk_78 = 0x01100024;
    p->cardDef = 0;
    p->unk_54 = 0;
    p->unk_58 = 0x100;
    p->unk_5F = 0;
    p->unk_5E = 0;
    p->unk_9F = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
    p->unk_94 = 0;
    p->unk_98 = 0;
    p->unk_A1 = 0;
    p->unk_A0 = 80;
    p->unk_9C = 4;
    p->unk_A2 = 0;
    p->unk_84 = 0x2400;
    p->unk_88 = 0x2400;
    p->unk_A3 = 0;
    p->unk_8C = gUnk_0903401C[5][0];
    p->unk_90 = gUnk_0903401C[5][1];
    p->x = gUnk_0903401C[4][0];
    p->y = gUnk_0903401C[4][1];
    p->unk_78 &= ~0x40;
    gCardBattleState->unk_0E8 = 0;
    func_08083714(p);
    p->unk_78 |= 0x80;
}
u8 Reload_Card_1(CardDisplayWork* p, void* a) {
    if (p->unk_78 & 0x10) {
        p->unk_9C = 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080829D0);
        return 1;
    }

    func_08083340(p);

    if (p->unk_78 & 4) {
        if ((s16)p->unk_9C > 0) {
            p->unk_78 &= ~0x40;
            ApproachValue(&p->unk_54, 0x100, p->unk_9C);
            gCardBattleState->unk_0E8 = 0;
            p->unk_9C--;
        } else {
            p->unk_78 |= 0x40;
        }
    } else {
        if ((s16)p->unk_9C <= 0) {
            return 0;
        }

        p->unk_78 &= ~0x40;
        ApproachValue(&p->unk_54, 0, p->unk_9C);
        gCardBattleState->unk_0E8 = 0;
        p->unk_9C--;
    }

    if (p->unk_78 & 0x1000) {
        return 1;
    }

    ApproachValue(&p->x, p->unk_8C, p->unk_9C);
    ApproachValue(&p->y, p->unk_90, p->unk_9C);
    p->unk_5F += 4;

    if (!(p->unk_78 & 0x20)) {
        p->unk_78 &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08082A64);
    }

    return func_08082C98(p, a);
}
void Reload_Card_3(CardDisplayWork* p) {
    func_0807C39C(p);

    if (p->unk_20 != 0) {
        EwramFree(p->unk_20);
    }

    if (gRikuBtlWork->flags & 0x1000000) {
        gRikuBtlWork->flags &= ~0x1000000;
    }
}
void func_08083278(UnkStruct_08095A5C* p, CardDisplayWork* w) {
    if (gCardBattleState->unk_106 <= 7) {
        gCardBattleState->unk_106++;
    }

    AnimStart(&p->anim3, (u16)gCardBattleState->unk_106, 5);
}
void func_080832B0(UnkStruct_08095A5C* p) {
    gCardBattleState->unk_106 = 2;
    AnimStart(&p->anim3, 2, 5);
}
void func_080832D0(UnkStruct_08095A5C* p, CardDisplayWork* w) {
    p->gfx = gRiCardF0RedFrames[3];
    p->gfx2 = gRiCardF0RedFrames[gCardBattleState->unk_102 + 2];
}
void func_080832F8(UnkStruct_08095A5C* p, CardDisplayWork* w) {
    p->gfx = AnimUpdate(&p->anim2);
    p->gfx2 = AnimUpdate(&p->anim3);
}
void func_08083314(UnkStruct_08095A5C* p, s16 a) {
    void* gfx;

    if ((u16)a <= 18) {
        AnimStart(&p->anim, a, 0);
        gfx = AnimGetGfx(&p->anim);
    } else {
        gfx = 0;
    }

    p->gfx3 = gfx;
}
void func_08083340(CardDisplayWork* p) {
    UnkStruct_08095A5C* w = p->unk_20;
    u8 v = 0;

    if ((p->unk_78 & 0x44) == 0x44) {
        v = gCardBattleState->unk_0E8;
        gCardBattleState->unk_0E8 = 0;
    } else {
        gCardBattleState->unk_0E8 = 0;
    }

    if ((p->unk_78 & 0x44) == 0x44) {
        if (v == 1) {
            if ((s8)w->unk_65 == 2) {
                if (!(gRikuBtlWork->flags & 0x1000000)) {
#ifndef VERSION_EU
                    m4aSongNumStart(SONG_SYS_CHAGE);
#endif
                    gRikuBtlWork->flags |= 0x1000000;
                }

                if (gCardBattleState->unk_108[1] == 0) {
                    if (gRikuBtlWork->unk_0F4 == 43) {
                        gCardBattleState->unk_0F8 += 12;
                    } else {
                        gCardBattleState->unk_0F8 += 25;
                    }

                    if ((s32)gCardBattleState->unk_0F8 > 0x100) {
                        gCardBattleState->unk_0F8 = 0x100;
                        gCardBattleState->unk_108[1] = 1;
                    }
                } else {
                    gCardBattleState->unk_102 += 3;
                    func_08083278(p->unk_20, p);

                    if (gCardBattleState->unk_102 == 22) {
                        gCardBattleState->unk_102 = 4;
                        gCardBattleState->unk_0F8 = 0;
                        gCardBattleState->unk_108[1] = 0;
                        gCardBattleState->unk_0FE--;
                        p->unk_A2 = v;
                        func_080832B0(p->unk_20);
#ifndef VERSION_EU
                        m4aSongNumStart(SONG_SYS_CHAGEF1);
#endif
                        func_08083314(p->unk_20, (s16)gCardBattleState->unk_0FE);
                    }
                }

                w->unk_65 = 0;
            }

            func_080832F8(p->unk_20, p);
            w->unk_65++;
        } else {
            func_080832D0(p->unk_20, p);
            w->unk_65 = 0;
            m4aSongNumStop(SONG_SYS_CHAGE);
            gRikuBtlWork->flags &= ~0x1000000;
        }
    } else {
        gRikuBtlWork->flags &= ~0x1000000;
    }

    if ((s16)gCardBattleState->unk_0FE < 0) {
        gCardBattleState->unk_0F8 = 0;
        gCardBattleState->unk_102 = 4;
        gCardBattleState->unk_106 = 2;
        gCardBattleState->unk_108[1] = 0;

        if (!(p->unk_78 & 0x4000000)) {
            p->unk_78 |= 0x4000000;
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
    UnkStruct_08095A5C* w;
    s16 y;
    u16 attr;

    attr = 0x410;
    affine = AllocObjAffine(0, p->unk_54, 0x100, 0);

    if (p->unk_78 & 0x80) {
        w = p->unk_20;

        if (func_080A42C8() == 1) {
            y = p->y >> 8;
        } else {
            y = (p->y >> 8) + (gSineTable[p->unk_5F] >> 8);
        }

        if (p->unk_54 > 0) {
            DrawSprite(p->x >> 8, y, gUnk_08F709B0[3].gfx2, p->tiles2,
                       gCardBattleState->palette, affine, attr, p->unk_A0);

            if (w->gfx3 != 0) {
                DrawSprite(p->x >> 8, y, w->gfx3, p->tiles,
                           gCardBattleState->palette, affine, attr,
                           (u16)(p->unk_A0 - 2));
            }

            if ((s32)gCardBattleState->unk_0F8 > 0) {
                affine2 = AllocObjAffine(0, p->unk_54, gCardBattleState->unk_0F8, 0);

                if (w->gfx != 0) {
                    DrawSprite(p->x >> 8, y + 17, w->gfx,
                               p->tiles3, gCardBattleState->palette, affine2, 0x400,
                               (u16)(p->unk_A0 - 1));
                }

                if (gCardBattleState->unk_108[1] == 1 && w->gfx2 != 0) {
                    DrawSprite(p->x >> 8, y, w->gfx2, p->tiles4,
                               gCardBattleState->palette, affine, 0x400,
                               (u16)(p->unk_A0 - 1));
                }
            }
        }
    }
}

void func_080836C4(UnkStruct_08095A5C* p, void* a, u8 b, s8 c) {
    AnimInit(&p->anim, gUnk_09EEA4E0, gUnk_09EEA494);

    if (c >= 0) {
        AnimStart(&p->anim, c, 0);
    } else {
        AnimStart(&p->anim, 0, 0);
    }

    p->gfx3 = AnimGetGfx(&p->anim);
}

void func_08083714(CardDisplayWork* w) {
    UnkStruct_08095A5C* q;

    q = w->unk_20;
    w->tiles = AllocObjTiles(128, 0);
    SetObjTileSource(w->tiles, gUnk_0909A4E0);
    func_080836C4(w->unk_20, w->tiles, w->args.unk_0E, gCardBattleState->unk_0FE);
    w->palette = 0;
    w->tiles2 = LoadObjTiles(gUnk_0909FDCA, 0x280);
    w->unk_18 = 0;
    w->tiles3 = AllocObjTiles(0x200, 0);
    SetObjTileSource(w->tiles3, gRiCardF0RedTiles);
    w->tiles4 = AllocObjTiles(128, 0);
    SetObjTileSource(w->tiles4, gRiCardF0RedTiles);
    AnimInit(&q->anim2, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&q->anim2, 1, 1);
    q->gfx = gRiCardF0RedFrames[3];
    AnimInit(&q->anim3, gRiCardF0RedAnims, gRiCardF0RedFrames);
    AnimStart(&q->anim3, gCardBattleState->unk_106, 1);
    q->gfx2 = gRiCardF0RedFrames[gCardBattleState->unk_102 + 2];
}

void UpdateRikuCardValue(CardDisplayWork* p) {
    if (gRikuBtlWork->unk_0F4 == 16) {
        if (p->unk_78 & 4) {
            p->unk_A7 = 1;
            p->unk_A5 = GetRandom() % 10;
        } else {
            p->unk_A7 = 0;
            p->unk_A5 = p->cardDef->unk_20;
        }
    } else if (gRikuBtlWork->unk_0F4 == 31) {
        p->unk_A7 = 1;
        p->unk_A5 = 10 - p->cardDef->unk_20;

        if (p->unk_A5 == 10) {
            p->unk_A5 = 0;
        }
    } else if (gRikuBtlWork->unk_0F4 == 17) {
        p->unk_A7 = 1;
        p->unk_A5 = 0;
    } else {
        p->unk_A5 = p->cardDef->unk_20;
        p->unk_A7 = 0;
    }
}

void func_080838A0(void) {
    BtlWork* p;

    p = gRikuBtlWork;

    switch ((u32)p->unk_0F4) {
    case 15:
    case 28:
    case 47:
        p->unk_0F8--;
        break;
    }
}
void func_080838CC(void) {
    if (gRikuBtlWork->unk_0F4 == 2) {
        gRikuBtlWork->unk_0F8--;
    }
}

void func_080838E8(void) {
}

void func_080838EC(void) {
    gUnk_02039DDC = 7;
}

void func_080838F8(void) {
}

void func_080838FC(void) {
}

void func_08083900(u8 a) {
    gUnk_02039DDC = 1;
    gUnk_02039DD8 = a;
}

void func_08083914(void) {
    gUnk_02039DDC = 2;
}

u8 func_08083920(void) {
    return func_08091B44();
}

void Bosscard_0(BossCardWork* w, u32* a) {
    u8 m;

    w->unk_24 = a[0];
    gUnk_02039DDC = 2;
    gUnk_02039DD8 = GetRandom() % 9;
    w->unk_28 = 0x100;
    w->unk_2A = 0x84;
    w->unk_2C = 0x100;
    w->unk_2F = 1;
    w->unk_30 = 1;
    w->unk_2E = 0;
    w->unk_31 = 8;
    w->unk_32 = 1;
    w->unk_33 = 0;
    w->unk_34 = GetRandom() % 100;
    w->unk_08 = gUnk_09EE275C[w->unk_24];
    w->cardDef = &gCardDefs[w->unk_08[0]];
    w->cardBack = &gUnk_08F70A28[w->cardDef->unk_1C >> 12];
    m = gUnk_08F7DAC4[w->unk_24];
    gCardBattleState->unk_0D7 = GetRandom() % m;
}

u8 Bosscard_1(BossCardWork* w, void* a) {
    s32 v;
    u8 z;

    w->unk_2E += 4;

    if (gCardBattleState->unk_0E0 == 1) {
        z = 0;
        w->unk_28 = 0x100;
        w->unk_31 = 8;
        gCardBattleState->unk_0E0 = z;
    }

    if (w->unk_31 != 0) {
        v = w->unk_28 << 8;
        ApproachValue(&v, 0xDC00, w->unk_31);
        w->unk_28 = v >> 8;
        w->unk_31--;
    }

    if (gUnk_02039DDC == 7) {
        w->unk_31 = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08083ADC);
    }

    if (gUnk_02039DDC == 1) {
        if (func_08083B20(w, 1) != 0) {
            gUnk_02039DDC = 0;
        }
    }

    if (gUnk_02039DDC == 2) {
        if (w->unk_33 == w->unk_34) {
            if (func_08083B20(w, 0) != 0) {
                w->unk_33 = 0;
                w->unk_34 = GetRandom() % 100;
            }
        } else {
            w->unk_33++;
        }
    }

    return 1;
}

s32 func_08083ADC(BossCardWork* w) {
    s32 v;

    if (w->unk_31 != 0) {
        v = w->unk_28 << 8;
        ApproachValue(&v, 0x10000, w->unk_31);
        w->unk_28 = v >> 8;
        w->unk_31--;
    }

    return 1;
}
void Bosscard_2(void) {
}
void Bosscard_3(void) {
}

u8 func_08083B20(BossCardWork* w, u8 b) {
    if (w->unk_32 == 1) {
        w->unk_2C -= 51;

        if (w->unk_2C <= 2) {
            w->unk_2C = 2;
            w->unk_32 = 0;

            if (b == 0) {
                gUnk_02039DD8 = GetRandom() % 9 + 1;
            }

            func_08091B38(gUnk_02039DD8);
        }
    } else {
        w->unk_2C += 51;

        if (w->unk_2C > 255) {
            w->unk_2C = 256;
            w->unk_32 = 1;
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

TaskDesc gUnk_09EE49CC = {
    "card",
    (TaskInitFunc)func_08081A3C,
    (TaskUpdateFunc)func_08081B70,
    (TaskDrawFunc)card_2,
    (TaskDestroyFunc)func_080820F4,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescNOCard = {
    "NO_Card",
    (TaskInitFunc)func_08081A3C,
    (TaskUpdateFunc)func_08081B70,
    (TaskDrawFunc)NO_Card_2,
    (TaskDestroyFunc)func_080820F4,
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
