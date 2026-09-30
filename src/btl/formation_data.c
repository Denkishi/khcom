#include "formation_data.h"
#include "formation_types.h"

#ifdef VERSION_EU
#define FORMATION_LIST_DROP 1
#else
#define FORMATION_LIST_DROP 0
#endif

static const BtlFormStep sUnk_08130E6C[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 85, 12, 0, 2 },
    { 0, 55, 25, 0, 3 },
    { 0, -55, 25, 0, 4 },
    { 0, -85, 12, 0, 5 },
    { 0, -65, -12, 0, 6 },
    { 0, -25, -25, 0, 7 },
};

static const BtlFormEntry sUnk_08130ECC = { 8, { 0 }, sUnk_08130E6C, 60 };

static const BtlFormStep sUnk_08130ED8[] = {
    { 0, 90, 0, 0, 0 },
    { 0, 55, 25, 0, 1 },
    { 0, 40, 0, 0, 2 },
    { 0, 25, -25, 0, 3 },
    { 0, -25, -25, 0, 4 },
    { 0, -55, 25, 0, 5 },
    { 0, -64, 0, 0, 6 },
};

static const BtlFormEntry sUnk_08130F2C = { 7, { 0 }, sUnk_08130ED8, 60 };

static const BtlFormStep sUnk_08130F38[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 40, 0, 0, 1 },
    { 0, 25, 25, 0, 2 },
    { 0, -25, 25, 0, 3 },
    { 0, -40, 0, 0, 4 },
    { 0, -25, -25, 0, 5 },
};

static const BtlFormEntry sUnk_08130F80 = { 6, { 0 }, sUnk_08130F38, 60 };

static const BtlFormStep sUnk_08130F8C[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 40, 0, 0, 1 },
    { 0, 55, 25, 0, 2 },
    { 0, -55, -25, 0, 3 },
    { 0, -40, 0, 0, 4 },
    { 0, -25, 25, 0, 5 },
};

const BtlFormEntry gUnk_08130FD4 = { 6, { 0 }, sUnk_08130F8C, 60 };

static const BtlFormStep sUnk_08130FE0[] = {
    { 0, 90, 0, 0, 0 },
    { 0, 64, 0, 0, 1 },
    { 0, 40, 0, 0, 2 },
    { 0, -40, 0, 0, 3 },
    { 0, -64, 0, 0, 4 },
    { 0, -90, 0, 0, 5 },
};

const BtlFormEntry gUnk_08131028 = { 6, { 0 }, sUnk_08130FE0, 60 };

static const BtlFormStep sUnk_08131034[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 40, 0, 0, 1 },
    { 0, 55, 25, 0, 2 },
    { 0, 65, -12, 0, 3 },
    { 0, 85, 12, 0, 4 },
};

const BtlFormEntry gUnk_08131070 = { 5, { 0 }, sUnk_08131034, 60 };

static const BtlFormStep sUnk_0813107C[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 55, 25, 0, 1 },
    { 0, 90, 0, 0, 2 },
    { 0, -65, -12, 0, 3 },
    { 0, -85, 12, 0, 4 },
};

static const BtlFormEntry sUnk_081310B8 = { 5, { 0 }, sUnk_0813107C, 60 };

static const BtlFormStep sUnk_081310C4[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, -25, -25, 0, 2 },
    { 0, -40, 0, 0, 3 },
    { 0, -55, 25, 0, 4 },
};

static const BtlFormEntry sUnk_08131100 = { 5, { 0 }, sUnk_081310C4, 60 };

static const BtlFormStep sUnk_0813110C[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 90, 0, 0, 2 },
    { 0, 85, 12, 0, 3 },
    { 0, 55, 25, 0, 4 },
};

static const BtlFormEntry sUnk_08131148 = { 5, { 0 }, sUnk_0813110C, 60 };

static const BtlFormStep sUnk_08131154[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 55, 25, 0, 1 },
    { 0, 65, -12, 0, 2 },
    { 0, 85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_08131184 = { 4, { 0 }, sUnk_08131154, 60 };

static const BtlFormStep sUnk_08131190[] = {
    { 0, 40, 0, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 85, 12, 0, 2 },
    { 0, 90, 0, 0, 3 },
};

static const BtlFormEntry sUnk_081311C0 = { 4, { 0 }, sUnk_08131190, 60 };

static const BtlFormStep sUnk_081311CC[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, -65, -12, 0, 2 },
    { 0, -85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_081311FC = { 4, { 0 }, sUnk_081311CC, 60 };

static const BtlFormStep sUnk_08131208[] = {
    { 0, -55, 25, 0, 0 },
    { 0, -85, 12, 0, 1 },
    { 0, -65, -12, 0, 2 },
    { 0, -25, -25, 0, 3 },
};

static const BtlFormEntry sUnk_08131238 = { 4, { 0 }, sUnk_08131208, 60 };

static const BtlFormStep sUnk_08131244[] = {
    { 0, 40, 0, 0, 0 },
    { 0, 65, -12, 0, 1 },
    { 0, 85, 12, 0, 2 },
};

static const BtlFormEntry sUnk_08131268 = { 3, { 0 }, sUnk_08131244, 60 };

static const BtlFormStep sUnk_08131274[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, 90, 0, 0, 2 },
};

static const BtlFormEntry sUnk_08131298 = { 3, { 0 }, sUnk_08131274, 60 };

static const BtlFormStep sUnk_081312A4[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
    { 0, -40, 0, 0, 2 },
};

static const BtlFormEntry sUnk_081312C8 = { 3, { 0 }, sUnk_081312A4, 60 };

static const BtlFormStep sUnk_081312D4[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 64, 0, 0, 1 },
    { 0, 55, 25, 0, 2 },
};

static const BtlFormEntry sUnk_081312F8 = { 3, { 0 }, sUnk_081312D4, 60 };

static const BtlFormStep sUnk_08131304[] = {
    { 0, -25, 25, 0, 0 },
    { 0, -64, 0, 0, 1 },
    { 0, -55, -25, 0, 2 },
};

static const BtlFormEntry sUnk_08131328 = { 3, { 0 }, sUnk_08131304, 60 };

static const BtlFormStep sUnk_08131334[] = {
    { 0, -65, -12, 0, 0 },
    { 0, -85, 12, 0, 1 },
    { 0, 40, 0, 0, 2 },
};

static const BtlFormEntry sUnk_08131358 = { 3, { 0 }, sUnk_08131334, 60 };

static const BtlFormStep sUnk_08131364[] = {
    { 0, 65, -12, 0, 0 },
    { 0, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_0813137C = { 2, { 0 }, sUnk_08131364, 60 };

static const BtlFormStep sUnk_08131388[] = {
    { 0, 25, -25, 0, 0 },
    { 0, 55, 25, 0, 1 },
};

static const BtlFormEntry sUnk_081313A0 = { 2, { 0 }, sUnk_08131388, 60 };

static const BtlFormStep sUnk_081313AC[] = {
    { 0, 40, 0, 0, 0 },
    { 0, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_081313C4 = { 2, { 0 }, sUnk_081313AC, 60 };

static const BtlFormStep sUnk_081313D0[] = {
    { 0, 40, 0, 0, 0 },
    { 0, 90, 0, 0, 1 },
};

static const BtlFormEntry sUnk_081313E8 = { 2, { 0 }, sUnk_081313D0, 60 };

static const BtlFormStep sUnk_081313F4[] = {
    { 0, -65, -12, 0, 0 },
    { 0, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_0813140C = { 2, { 0 }, sUnk_081313F4, 60 };

static const BtlFormStep sUnk_08131418[] = {
    { 0, -55, 25, 0, 0 },
    { 0, -25, -25, 0, 1 },
};

static const BtlFormEntry sUnk_08131430 = { 2, { 0 }, sUnk_08131418, 60 };

static const BtlFormStep sUnk_0813143C[] = {
    { 0, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08131448 = { 1, { 0 }, sUnk_0813143C, 60 };

static const BtlFormStep sUnk_08131454[] = {
    { 1, 25, -25, -30, 0 },
    { 1, 40, 0, -30, 1 },
    { 1, 55, 25, -30, 2 },
    { 1, 65, -12, -40, 3 },
    { 1, 85, 12, -40, 4 },
};

const BtlFormEntry gUnk_08131490 = { 5, { 0 }, sUnk_08131454, 60 };

static const BtlFormStep sUnk_0813149C[] = {
    { 1, 25, -25, -30, 0 },
    { 1, 55, 25, -30, 1 },
    { 1, 65, -12, -40, 2 },
    { 1, 85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_081314CC = { 4, { 0 }, sUnk_0813149C, 60 };

static const BtlFormStep sUnk_081314D8[] = {
    { 1, 40, 0, -30, 0 },
    { 1, 65, -12, -40, 1 },
    { 1, 85, 12, -40, 2 },
};

const BtlFormEntry gUnk_081314FC = { 3, { 0 }, sUnk_081314D8, 60 };

static const BtlFormStep sUnk_08131508[] = {
    { 1, 65, -12, -40, 0 },
    { 1, 85, 12, -40, 1 },
    { 1, -40, 0, -30, 2 },
};

static const BtlFormEntry sUnk_0813152C = { 3, { 0 }, sUnk_08131508, 60 };

static const BtlFormStep sUnk_08131538[] = {
    { 1, 65, -12, -40, 0 },
    { 1, 85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08131550 = { 2, { 0 }, sUnk_08131538, 60 };

static const BtlFormStep sUnk_0813155C[] = {
    { 1, -65, -12, -40, 0 },
    { 1, -85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08131574 = { 2, { 0 }, sUnk_0813155C, 60 };

static const BtlFormStep sUnk_08131580[] = {
    { 1, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_0813158C = { 1, { 0 }, sUnk_08131580, 60 };

static const BtlFormStep sUnk_08131598[] = {
    { 1, 25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_081315A4 = { 1, { 0 }, sUnk_08131598, 60 };

static const BtlFormStep sUnk_081315B0[] = {
    { 1, -25, -25, -30, 0 },
};

const BtlFormEntry gUnk_081315BC = { 1, { 0 }, sUnk_081315B0, 60 };

static const BtlFormStep sUnk_081315C8[] = {
    { 1, 55, 25, -30, 0 },
};

const BtlFormEntry gUnk_081315D4 = { 1, { 0 }, sUnk_081315C8, 60 };

static const BtlFormStep sUnk_081315E0[] = {
    { 1, -55, 25, -30, 0 },
};

const BtlFormEntry gUnk_081315EC = { 1, { 0 }, sUnk_081315E0, 60 };

static const BtlFormStep sUnk_081315F8[] = {
    { 2, 25, -25, -30, 0 },
    { 2, 55, 25, -30, 1 },
    { 2, 90, 0, -50, 2 },
    { 2, -65, -12, -40, 3 },
    { 2, -85, 12, -40, 4 },
};

const BtlFormEntry gUnk_08131634 = { 5, { 0 }, sUnk_081315F8, 60 };

static const BtlFormStep sUnk_08131640[] = {
    { 2, 40, 0, -30, 0 },
    { 2, 65, -12, -40, 1 },
    { 2, 85, 12, -40, 2 },
    { 2, 90, 0, -50, 3 },
};

static const BtlFormEntry sUnk_08131670 = { 4, { 0 }, sUnk_08131640, 60 };

static const BtlFormStep sUnk_0813167C[] = {
    { 2, 65, -12, -40, 0 },
    { 2, 85, 12, -40, 1 },
    { 2, 90, 0, -50, 2 },
};

static const BtlFormEntry sUnk_081316A0 = { 3, { 0 }, sUnk_0813167C, 60 };

static const BtlFormStep sUnk_081316AC[] = {
    { 2, 25, -25, -30, 0 },
    { 2, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_081316C4 = { 2, { 0 }, sUnk_081316AC, 60 };

static const BtlFormStep sUnk_081316D0[] = {
    { 2, -65, -12, -40, 0 },
    { 2, -85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_081316E8 = { 2, { 0 }, sUnk_081316D0, 60 };

static const BtlFormStep sUnk_081316F4[] = {
    { 2, -55, 25, -30, 0 },
    { 2, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_0813170C = { 2, { 0 }, sUnk_081316F4, 60 };

static const BtlFormStep sUnk_08131718[] = {
    { 2, 64, 0, -50, 0 },
};

const BtlFormEntry gUnk_08131724 = { 1, { 0 }, sUnk_08131718, 60 };

static const BtlFormStep sUnk_08131730[] = {
    { 2, 40, 0, -30, 0 },
};

static const BtlFormEntry sUnk_0813173C = { 1, { 0 }, sUnk_08131730, 60 };

static const BtlFormStep sUnk_08131748[] = {
    { 2, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08131754 = { 1, { 0 }, sUnk_08131748, 60 };

static const BtlFormStep sUnk_08131760[] = {
    { 2, 25, -25, -30, 0 },
};

const BtlFormEntry gUnk_0813176C = { 1, { 0 }, sUnk_08131760, 60 };

static const BtlFormStep sUnk_08131778[] = {
    { 2, -25, -25, -30, 0 },
};

const BtlFormEntry gUnk_08131784 = { 1, { 0 }, sUnk_08131778, 60 };

static const BtlFormStep sUnk_08131790[] = {
    { 2, 55, 25, -30, 0 },
};

const BtlFormEntry gUnk_0813179C = { 1, { 0 }, sUnk_08131790, 60 };

static const BtlFormStep sUnk_081317A8[] = {
    { 2, -55, 25, -30, 0 },
};

static const BtlFormEntry sUnk_081317B4 = { 1, { 0 }, sUnk_081317A8, 60 };

static const BtlFormStep sUnk_081317C0[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
    { 3, -25, -25, -30, 2 },
    { 3, -40, 0, -30, 3 },
    { 3, -55, 25, -30, 4 },
};

const BtlFormEntry gUnk_081317FC = { 5, { 0 }, sUnk_081317C0, 60 };

static const BtlFormStep sUnk_08131808[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
    { 3, -65, -12, -40, 2 },
    { 3, -85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_08131838 = { 4, { 0 }, sUnk_08131808, 60 };

static const BtlFormStep sUnk_08131844[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
    { 3, -40, 0, -30, 2 },
};

static const BtlFormEntry sUnk_08131868 = { 3, { 0 }, sUnk_08131844, 60 };

static const BtlFormStep sUnk_08131874[] = {
    { 3, -25, 25, -30, 0 },
    { 3, -64, 0, -50, 1 },
    { 3, -55, -25, -30, 2 },
};

static const BtlFormEntry sUnk_08131898 = { 3, { 0 }, sUnk_08131874, 60 };

static const BtlFormStep sUnk_081318A4[] = {
    { 3, 65, -12, -40, 0 },
    { 3, 85, 12, -40, 1 },
};

const BtlFormEntry gUnk_081318BC = { 2, { 0 }, sUnk_081318A4, 60 };

static const BtlFormStep sUnk_081318C8[] = {
    { 3, 25, -25, -30, 0 },
    { 3, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_081318E0 = { 2, { 0 }, sUnk_081318C8, 60 };

static const BtlFormStep sUnk_081318EC[] = {
    { 3, 40, 0, -30, 0 },
    { 3, -40, 0, -30, 1 },
};

const BtlFormEntry gUnk_08131904 = { 2, { 0 }, sUnk_081318EC, 60 };

static const BtlFormStep sUnk_08131910[] = {
    { 3, 40, 0, -30, 0 },
    { 3, 90, 0, -50, 1 },
};

static const BtlFormEntry sUnk_08131928 = { 2, { 0 }, sUnk_08131910, 60 };

static const BtlFormStep sUnk_08131934[] = {
    { 3, -65, -12, -40, 0 },
    { 3, -85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_0813194C = { 2, { 0 }, sUnk_08131934, 60 };

static const BtlFormStep sUnk_08131958[] = {
    { 3, -55, 25, -30, 0 },
    { 3, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_08131970 = { 2, { 0 }, sUnk_08131958, 60 };

static const BtlFormStep sUnk_0813197C[] = {
    { 3, 64, 0, -50, 0 },
};

const BtlFormEntry gUnk_08131988 = { 1, { 0 }, sUnk_0813197C, 60 };

static const BtlFormStep sUnk_08131994[] = {
    { 3, 25, -25, -30, 0 },
};

const BtlFormEntry gUnk_081319A0 = { 1, { 0 }, sUnk_08131994, 60 };

static const BtlFormStep sUnk_081319AC[] = {
    { 3, -25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_081319B8 = { 1, { 0 }, sUnk_081319AC, 60 };

static const BtlFormStep sUnk_081319C4[] = {
    { 3, 55, 25, -30, 0 },
};

const BtlFormEntry gUnk_081319D0 = { 1, { 0 }, sUnk_081319C4, 60 };

static const BtlFormStep sUnk_081319DC[] = {
    { 3, -55, 25, -30, 0 },
};

const BtlFormEntry gUnk_081319E8 = { 1, { 0 }, sUnk_081319DC, 60 };

static const BtlFormStep sUnk_081319F4[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
    { 4, -25, -25, -30, 2 },
    { 4, -40, 0, -30, 3 },
    { 4, -55, 25, -30, 4 },
};

const BtlFormEntry gUnk_08131A30 = { 5, { 0 }, sUnk_081319F4, 60 };

static const BtlFormStep sUnk_08131A3C[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
    { 4, -65, -12, -40, 2 },
    { 4, -85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_08131A6C = { 4, { 0 }, sUnk_08131A3C, 60 };

static const BtlFormStep sUnk_08131A78[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
    { 4, -40, 0, -30, 2 },
};

const BtlFormEntry gUnk_08131A9C = { 3, { 0 }, sUnk_08131A78, 60 };

static const BtlFormStep sUnk_08131AA8[] = {
    { 4, -65, -12, -40, 0 },
    { 4, -85, 12, -40, 1 },
    { 4, 40, 0, -30, 2 },
};

static const BtlFormEntry sUnk_08131ACC = { 3, { 0 }, sUnk_08131AA8, 60 };

static const BtlFormStep sUnk_08131AD8[] = {
    { 4, 65, -12, -40, 0 },
    { 4, 85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08131AF0 = { 2, { 0 }, sUnk_08131AD8, 60 };

static const BtlFormStep sUnk_08131AFC[] = {
    { 4, 25, -25, -30, 0 },
    { 4, 55, 25, -30, 1 },
};

const BtlFormEntry gUnk_08131B14 = { 2, { 0 }, sUnk_08131AFC, 60 };

static const BtlFormStep sUnk_08131B20[] = {
    { 4, 40, 0, -30, 0 },
    { 4, -40, 0, -30, 1 },
};

static const BtlFormEntry sUnk_08131B38 = { 2, { 0 }, sUnk_08131B20, 60 };

static const BtlFormStep sUnk_08131B44[] = {
    { 4, -65, -12, -40, 0 },
    { 4, -85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08131B5C = { 2, { 0 }, sUnk_08131B44, 60 };

static const BtlFormStep sUnk_08131B68[] = {
    { 4, -55, 25, -30, 0 },
    { 4, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_08131B80 = { 2, { 0 }, sUnk_08131B68, 60 };

static const BtlFormStep sUnk_08131B8C[] = {
    { 4, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08131B98 = { 1, { 0 }, sUnk_08131B8C, 60 };

static const BtlFormStep sUnk_08131BA4[] = {
    { 4, 25, -25, -30, 0 },
};

const BtlFormEntry gUnk_08131BB0 = { 1, { 0 }, sUnk_08131BA4, 60 };

static const BtlFormStep sUnk_08131BBC[] = {
    { 4, -25, -25, -30, 0 },
};

const BtlFormEntry gUnk_08131BC8 = { 1, { 0 }, sUnk_08131BBC, 60 };

static const BtlFormStep sUnk_08131BD4[] = {
    { 4, 55, 25, -30, 0 },
};

static const BtlFormEntry sUnk_08131BE0 = { 1, { 0 }, sUnk_08131BD4, 60 };

static const BtlFormStep sUnk_08131BEC[] = {
    { 4, -55, 25, -30, 0 },
};

const BtlFormEntry gUnk_08131BF8 = { 1, { 0 }, sUnk_08131BEC, 60 };

static const BtlFormStep sUnk_08131C04[] = {
    { 5, 25, -25, -30, 0 },
    { 5, 40, 0, -30, 1 },
    { 5, 25, 25, -30, 2 },
    { 5, -25, 25, -30, 3 },
    { 5, -40, 0, -30, 4 },
    { 5, -25, -25, -30, 5 },
};

static const BtlFormEntry sUnk_08131C4C = { 6, { 0 }, sUnk_08131C04, 60 };

static const BtlFormStep sUnk_08131C58[] = {
    { 5, 25, -25, -30, 0 },
    { 5, 40, 0, -30, 1 },
    { 5, 55, 25, -30, 2 },
    { 5, 65, -12, -40, 3 },
    { 5, 85, 12, -40, 4 },
};

const BtlFormEntry gUnk_08131C94 = { 5, { 0 }, sUnk_08131C58, 60 };

static const BtlFormStep sUnk_08131CA0[] = {
    { 5, 25, -25, -30, 0 },
    { 5, 55, 25, -30, 1 },
    { 5, 65, -12, -40, 2 },
    { 5, 85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_08131CD0 = { 4, { 0 }, sUnk_08131CA0, 60 };

static const BtlFormStep sUnk_08131CDC[] = {
    { 5, 65, -12, -40, 0 },
    { 5, 85, 12, -40, 1 },
    { 5, -65, -12, -40, 2 },
    { 5, -85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_08131D0C = { 4, { 0 }, sUnk_08131CDC, 60 };

static const BtlFormStep sUnk_08131D18[] = {
    { 5, 40, 0, -30, 0 },
    { 5, 65, -12, -40, 1 },
    { 5, 85, 12, -40, 2 },
};

static const BtlFormEntry sUnk_08131D3C = { 3, { 0 }, sUnk_08131D18, 60 };

static const BtlFormStep sUnk_08131D48[] = {
    { 5, -25, 25, -30, 0 },
    { 5, -64, 0, -50, 1 },
    { 5, -55, -25, -30, 2 },
};

const BtlFormEntry gUnk_08131D6C = { 3, { 0 }, sUnk_08131D48, 60 };

static const BtlFormStep sUnk_08131D78[] = {
    { 5, 65, -12, -40, 0 },
    { 5, 85, 12, -40, 1 },
};

const BtlFormEntry gUnk_08131D90 = { 2, { 0 }, sUnk_08131D78, 60 };

static const BtlFormStep sUnk_08131D9C[] = {
    { 5, 64, 0, -50, 0 },
};

const BtlFormEntry gUnk_08131DA8 = { 1, { 0 }, sUnk_08131D9C, 60 };

static const BtlFormStep sUnk_08131DB4[] = {
    { 6, 65, -12, 0, 0 },
    { 6, 85, 12, 0, 1 },
    { 6, -65, -12, 0, 2 },
    { 6, -85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_08131DE4 = { 4, { 0 }, sUnk_08131DB4, 60 };

static const BtlFormStep sUnk_08131DF0[] = {
    { 6, 40, 0, 0, 0 },
    { 6, 65, -12, 0, 1 },
    { 6, 85, 12, 0, 2 },
};

const BtlFormEntry gUnk_08131E14 = { 3, { 0 }, sUnk_08131DF0, 60 };

static const BtlFormStep sUnk_08131E20[] = {
    { 6, 25, -25, 0, 0 },
    { 6, 55, 25, 0, 1 },
};

const BtlFormEntry gUnk_08131E38 = { 2, { 0 }, sUnk_08131E20, 60 };

static const BtlFormStep sUnk_08131E44[] = {
    { 6, 40, 0, 0, 0 },
    { 6, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_08131E5C = { 2, { 0 }, sUnk_08131E44, 60 };

static const BtlFormStep sUnk_08131E68[] = {
    { 6, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08131E74 = { 1, { 0 }, sUnk_08131E68, 60 };

static const BtlFormStep sUnk_08131E80[] = {
    { 7, 65, -12, 0, 0 },
    { 7, 85, 12, 0, 1 },
    { 7, -65, -12, 0, 2 },
    { 7, -85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_08131EB0 = { 4, { 0 }, sUnk_08131E80, 60 };

static const BtlFormStep sUnk_08131EBC[] = {
    { 7, 65, -12, 0, 0 },
    { 7, 85, 12, 0, 1 },
    { 7, -40, 0, 0, 2 },
};

const BtlFormEntry gUnk_08131EE0 = { 3, { 0 }, sUnk_08131EBC, 60 };

static const BtlFormStep sUnk_08131EEC[] = {
    { 7, 65, -12, 0, 0 },
    { 7, 85, 12, 0, 1 },
};

const BtlFormEntry gUnk_08131F04 = { 2, { 0 }, sUnk_08131EEC, 60 };

static const BtlFormStep sUnk_08131F10[] = {
    { 7, 40, 0, 0, 0 },
    { 7, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_08131F28 = { 2, { 0 }, sUnk_08131F10, 60 };

static const BtlFormStep sUnk_08131F34[] = {
    { 7, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08131F40 = { 1, { 0 }, sUnk_08131F34, 60 };

static const BtlFormStep sUnk_08131F4C[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 40, 0, 0, 1 },
    { 9, 55, 25, 0, 2 },
    { 9, -55, -25, 0, 3 },
    { 9, -40, 0, 0, 4 },
    { 9, -25, 25, 0, 5 },
};

static const BtlFormEntry sUnk_08131F94 = { 6, { 0 }, sUnk_08131F4C, 60 };

static const BtlFormStep sUnk_08131FA0[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 55, 25, 0, 1 },
    { 9, 90, 0, 0, 2 },
    { 9, -65, -12, 0, 3 },
    { 9, -85, 12, 0, 4 },
};

const BtlFormEntry gUnk_08131FDC = { 5, { 0 }, sUnk_08131FA0, 60 };

static const BtlFormStep sUnk_08131FE8[] = {
    { 9, 65, -12, -40, 0 },
    { 9, 85, 12, -40, 1 },
    { 9, -25, -25, -30, 2 },
    { 9, -40, 0, -30, 3 },
    { 9, -55, 25, -30, 4 },
};

const BtlFormEntry gUnk_08132024 = { 5, { 0 }, sUnk_08131FE8, 60 };

static const BtlFormStep sUnk_08132030[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 55, 25, 0, 1 },
    { 9, 65, -12, 0, 2 },
    { 9, 85, 12, 0, 3 },
};

const BtlFormEntry gUnk_08132060 = { 4, { 0 }, sUnk_08132030, 60 };

static const BtlFormStep sUnk_0813206C[] = {
    { 9, 40, 0, -30, 0 },
    { 9, 65, -12, -40, 1 },
    { 9, 85, 12, -40, 2 },
    { 9, 90, 0, -50, 3 },
};

static const BtlFormEntry sUnk_0813209C = { 4, { 0 }, sUnk_0813206C, 60 };

static const BtlFormStep sUnk_081320A8[] = {
    { 9, 65, -12, 0, 0 },
    { 9, 85, 12, 0, 1 },
    { 9, -65, -12, 0, 2 },
    { 9, -85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_081320D8 = { 4, { 0 }, sUnk_081320A8, 60 };

static const BtlFormStep sUnk_081320E4[] = {
    { 9, 40, 0, -30, 0 },
    { 9, 65, -12, -40, 1 },
    { 9, 85, 12, -40, 2 },
};

const BtlFormEntry gUnk_08132108 = { 3, { 0 }, sUnk_081320E4, 60 };

static const BtlFormStep sUnk_08132114[] = {
    { 9, 65, -12, 0, 0 },
    { 9, 85, 12, 0, 1 },
    { 9, 90, 0, 0, 2 },
};

const BtlFormEntry gUnk_08132138 = { 3, { 0 }, sUnk_08132114, 60 };

static const BtlFormStep sUnk_08132144[] = {
    { 9, 65, -12, -40, 0 },
    { 9, 85, 12, -40, 1 },
    { 9, -40, 0, -30, 2 },
};

const BtlFormEntry gUnk_08132168 = { 3, { 0 }, sUnk_08132144, 60 };

static const BtlFormStep sUnk_08132174[] = {
    { 9, 25, -25, 0, 0 },
    { 9, 64, 0, 0, 1 },
    { 9, 55, 25, 0, 2 },
};

static const BtlFormEntry sUnk_08132198 = { 3, { 0 }, sUnk_08132174, 60 };

static const BtlFormStep sUnk_081321A4[] = {
    { 9, -25, 25, 0, 0 },
    { 9, -64, 0, 0, 1 },
    { 9, -55, -25, 0, 2 },
};

static const BtlFormEntry sUnk_081321C8 = { 3, { 0 }, sUnk_081321A4, 60 };

static const BtlFormStep sUnk_081321D4[] = {
    { 9, 65, -12, 0, 0 },
    { 9, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_081321EC = { 2, { 0 }, sUnk_081321D4, 60 };

static const BtlFormStep sUnk_081321F8[] = {
    { 9, 25, -25, -30, 0 },
    { 9, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_08132210 = { 2, { 0 }, sUnk_081321F8, 60 };

static const BtlFormStep sUnk_0813221C[] = {
    { 9, 40, 0, 0, 0 },
    { 9, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_08132234 = { 2, { 0 }, sUnk_0813221C, 60 };

static const BtlFormStep sUnk_08132240[] = {
    { 9, -65, -12, 0, 0 },
    { 9, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08132258 = { 2, { 0 }, sUnk_08132240, 60 };

static const BtlFormStep sUnk_08132264[] = {
    { 9, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132270 = { 1, { 0 }, sUnk_08132264, 60 };

static const BtlFormStep sUnk_0813227C[] = {
    { 9, 40, 0, 0, 0 },
};

const BtlFormEntry gUnk_08132288 = { 1, { 0 }, sUnk_0813227C, 60 };

static const BtlFormStep sUnk_08132294[] = {
    { 9, -64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_081322A0 = { 1, { 0 }, sUnk_08132294, 60 };

static const BtlFormStep sUnk_081322AC[] = {
    { 9, -40, 0, 0, 0 },
};

const BtlFormEntry gUnk_081322B8 = { 1, { 0 }, sUnk_081322AC, 60 };

static const BtlFormStep sUnk_081322C4[] = {
    { 10, 40, 0, 0, 0 },
    { 10, 65, -12, 0, 1 },
    { 10, 85, 12, 0, 2 },
};

static const BtlFormEntry sUnk_081322E8 = { 3, { 0 }, sUnk_081322C4, 60 };

static const BtlFormStep sUnk_081322F4[] = {
    { 10, 25, -25, 0, 0 },
    { 10, 55, 25, 0, 1 },
};

static const BtlFormEntry sUnk_0813230C = { 2, { 0 }, sUnk_081322F4, 60 };

static const BtlFormStep sUnk_08132318[] = {
    { 10, -65, -12, 0, 0 },
    { 10, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08132330 = { 2, { 0 }, sUnk_08132318, 60 };

static const BtlFormStep sUnk_0813233C[] = {
    { 10, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08132348 = { 1, { 0 }, sUnk_0813233C, 60 };

static const BtlFormStep sUnk_08132354[] = {
    { 11, 65, -12, 0, 0 },
    { 11, 85, 12, 0, 1 },
    { 11, 90, 0, 0, 2 },
};

static const BtlFormEntry sUnk_08132378 = { 3, { 0 }, sUnk_08132354, 60 };

static const BtlFormStep sUnk_08132384[] = {
    { 11, 40, 0, 0, 0 },
    { 11, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_0813239C = { 2, { 0 }, sUnk_08132384, 60 };

static const BtlFormStep sUnk_081323A8[] = {
    { 11, -55, 25, 0, 0 },
    { 11, -25, -25, 0, 1 },
};

static const BtlFormEntry sUnk_081323C0 = { 2, { 0 }, sUnk_081323A8, 60 };

static const BtlFormStep sUnk_081323CC[] = {
    { 11, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_081323D8 = { 1, { 0 }, sUnk_081323CC, 60 };

static const BtlFormStep sUnk_081323E4[] = {
    { 12, 25, -25, -30, 0 },
    { 12, 55, 25, -30, 1 },
    { 12, 65, -12, -40, 2 },
    { 12, 85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_08132414 = { 4, { 0 }, sUnk_081323E4, 60 };

static const BtlFormStep sUnk_08132420[] = {
    { 12, 65, -12, -40, 0 },
    { 12, 85, 12, -40, 1 },
    { 12, -65, -12, -40, 2 },
    { 12, -85, 12, -40, 3 },
};

static const BtlFormEntry sUnk_08132450 = { 4, { 0 }, sUnk_08132420, 60 };

static const BtlFormStep sUnk_0813245C[] = {
    { 12, 65, -12, -40, 0 },
    { 12, 85, 12, -40, 1 },
    { 12, 90, 0, -50, 2 },
};

static const BtlFormEntry sUnk_08132480 = { 3, { 0 }, sUnk_0813245C, 60 };

static const BtlFormStep sUnk_0813248C[] = {
    { 12, 65, -12, -40, 0 },
    { 12, 85, 12, -40, 1 },
    { 12, -40, 0, -30, 2 },
};

static const BtlFormEntry sUnk_081324B0 = { 3, { 0 }, sUnk_0813248C, 60 };

static const BtlFormStep sUnk_081324BC[] = {
    { 12, 40, 0, -30, 0 },
    { 12, -40, 0, -30, 1 },
};

static const BtlFormEntry sUnk_081324D4 = { 2, { 0 }, sUnk_081324BC, 60 };

static const BtlFormStep sUnk_081324E0[] = {
    { 12, -55, 25, -30, 0 },
    { 12, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_081324F8 = { 2, { 0 }, sUnk_081324E0, 60 };

static const BtlFormStep sUnk_08132504[] = {
    { 12, 64, 0, -50, 0 },
};

const BtlFormEntry gUnk_08132510 = { 1, { 0 }, sUnk_08132504, 60 };

static const BtlFormStep sUnk_0813251C[] = {
    { 13, 25, -25, 0, 0 },
    { 13, 55, 25, 0, 1 },
    { 13, 90, 0, 0, 2 },
    { 13, -65, -12, 0, 3 },
    { 13, -85, 12, 0, 4 },
};

const BtlFormEntry gUnk_08132558 = { 5, { 0 }, sUnk_0813251C, 60 };

static const BtlFormStep sUnk_08132564[] = {
    { 13, 25, -25, 0, 0 },
    { 13, 55, 25, 0, 1 },
    { 13, 65, -12, 0, 2 },
    { 13, 85, 12, 0, 3 },
};

const BtlFormEntry gUnk_08132594 = { 4, { 0 }, sUnk_08132564, 60 };

static const BtlFormStep sUnk_081325A0[] = {
    { 13, 65, -12, 0, 0 },
    { 13, 85, 12, 0, 1 },
    { 13, -65, -12, 0, 2 },
    { 13, -85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_081325D0 = { 4, { 0 }, sUnk_081325A0, 60 };

static const BtlFormStep sUnk_081325DC[] = {
    { 13, 65, -12, 0, 0 },
    { 13, 85, 12, 0, 1 },
    { 13, -40, 0, 0, 2 },
};

const BtlFormEntry gUnk_08132600 = { 3, { 0 }, sUnk_081325DC, 60 };

static const BtlFormStep sUnk_0813260C[] = {
    { 13, 25, -25, 0, 0 },
    { 13, 55, 25, 0, 1 },
};

static const BtlFormEntry sUnk_08132624 = { 2, { 0 }, sUnk_0813260C, 60 };

static const BtlFormStep sUnk_08132630[] = {
    { 13, -55, 25, 0, 0 },
    { 13, -25, -25, 0, 1 },
};

static const BtlFormEntry sUnk_08132648 = { 2, { 0 }, sUnk_08132630, 60 };

static const BtlFormStep sUnk_08132654[] = {
    { 13, 64, 0, 0, 0 },
};

const BtlFormEntry gUnk_08132660 = { 1, { 0 }, sUnk_08132654, 60 };

static const BtlFormStep sUnk_0813266C[] = {
    { 13, 40, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08132678 = { 1, { 0 }, sUnk_0813266C, 60 };

static const BtlFormStep sUnk_08132684[] = {
    { 14, 40, 0, 0, 0 },
    { 14, 65, -12, 0, 1 },
    { 14, 85, 12, 0, 2 },
};

static const BtlFormEntry sUnk_081326A8 = { 3, { 0 }, sUnk_08132684, 60 };

static const BtlFormStep sUnk_081326B4[] = {
    { 14, 65, -12, 0, 0 },
    { 14, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_081326CC = { 2, { 0 }, sUnk_081326B4, 60 };

static const BtlFormStep sUnk_081326D8[] = {
    { 14, 40, 0, 0, 0 },
    { 14, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_081326F0 = { 2, { 0 }, sUnk_081326D8, 60 };

static const BtlFormStep sUnk_081326FC[] = {
    { 14, -65, -12, 0, 0 },
    { 14, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08132714 = { 2, { 0 }, sUnk_081326FC, 60 };

static const BtlFormStep sUnk_08132720[] = {
    { 14, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_0813272C = { 1, { 0 }, sUnk_08132720, 60 };

static const BtlFormStep sUnk_08132738[] = {
    { 14, -64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08132744 = { 1, { 0 }, sUnk_08132738, 60 };

static const BtlFormStep sUnk_08132750[] = {
    { 15, 65, -12, -40, 0 },
    { 15, 85, 12, -40, 1 },
    { 15, 90, 0, -50, 2 },
};

static const BtlFormEntry sUnk_08132774 = { 3, { 0 }, sUnk_08132750, 60 };

static const BtlFormStep sUnk_08132780[] = {
    { 15, 25, -25, -30, 0 },
    { 15, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_08132798 = { 2, { 0 }, sUnk_08132780, 60 };

static const BtlFormStep sUnk_081327A4[] = {
    { 15, 40, 0, -30, 0 },
    { 15, -40, 0, -30, 1 },
};

static const BtlFormEntry sUnk_081327BC = { 2, { 0 }, sUnk_081327A4, 60 };

static const BtlFormStep sUnk_081327C8[] = {
    { 15, -65, -12, -40, 0 },
    { 15, -85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_081327E0 = { 2, { 0 }, sUnk_081327C8, 60 };

static const BtlFormStep sUnk_081327EC[] = {
    { 15, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_081327F8 = { 1, { 0 }, sUnk_081327EC, 60 };

static const BtlFormStep sUnk_08132804[] = {
    { 15, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132810 = { 1, { 0 }, sUnk_08132804, 60 };

static const BtlFormStep sUnk_0813281C[] = {
    { 16, 65, -12, -40, 0 },
    { 16, 85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08132834 = { 2, { 0 }, sUnk_0813281C, 60 };

static const BtlFormStep sUnk_08132840[] = {
    { 16, -55, 25, -30, 0 },
    { 16, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_08132858 = { 2, { 0 }, sUnk_08132840, 60 };

static const BtlFormStep sUnk_08132864[] = {
    { 16, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132870 = { 1, { 0 }, sUnk_08132864, 60 };

static const BtlFormStep sUnk_0813287C[] = {
    { 16, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132888 = { 1, { 0 }, sUnk_0813287C, 60 };

static const BtlFormStep sUnk_08132894[] = {
    { 16, 25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_081328A0 = { 1, { 0 }, sUnk_08132894, 60 };

static const BtlFormStep sUnk_081328AC[] = {
    { 16, -25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_081328B8 = { 1, { 0 }, sUnk_081328AC, 60 };

static const BtlFormStep sUnk_081328C4[] = {
    { 16, 55, 25, -30, 0 },
};

static const BtlFormEntry sUnk_081328D0 = { 1, { 0 }, sUnk_081328C4, 60 };

static const BtlFormStep sUnk_081328DC[] = {
    { 16, -55, 25, -30, 0 },
};

static const BtlFormEntry sUnk_081328E8 = { 1, { 0 }, sUnk_081328DC, 60 };

static const BtlFormStep sUnk_081328F4[] = {
    { 17, 65, -12, 0, 0 },
    { 17, 85, 12, 0, 1 },
    { 17, -40, 0, 0, 2 },
};

const BtlFormEntry gUnk_08132918 = { 3, { 0 }, sUnk_081328F4, 60 };

static const BtlFormStep sUnk_08132924[] = {
    { 17, 25, -25, 0, 0 },
    { 17, 55, 25, 0, 1 },
};

static const BtlFormEntry sUnk_0813293C = { 2, { 0 }, sUnk_08132924, 60 };

static const BtlFormStep sUnk_08132948[] = {
    { 17, 40, 0, 0, 0 },
    { 17, -40, 0, 0, 1 },
};

const BtlFormEntry gUnk_08132960 = { 2, { 0 }, sUnk_08132948, 60 };

static const BtlFormStep sUnk_0813296C[] = {
    { 17, 65, -12, 0, 0 },
    { 17, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08132984 = { 2, { 0 }, sUnk_0813296C, 60 };

static const BtlFormStep sUnk_08132990[] = {
    { 17, -55, 25, 0, 0 },
    { 17, -25, -25, 0, 1 },
};

static const BtlFormEntry sUnk_081329A8 = { 2, { 0 }, sUnk_08132990, 60 };

static const BtlFormStep sUnk_081329B4[] = {
    { 17, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_081329C0 = { 1, { 0 }, sUnk_081329B4, 60 };

static const BtlFormStep sUnk_081329CC[] = {
    { 17, -64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_081329D8 = { 1, { 0 }, sUnk_081329CC, 60 };

static const BtlFormStep sUnk_081329E4[] = {
    { 18, 40, 0, -30, 0 },
    { 18, 65, -12, -40, 1 },
    { 18, 85, 12, -40, 2 },
};

static const BtlFormEntry sUnk_08132A08 = { 3, { 0 }, sUnk_081329E4, 60 };

static const BtlFormStep sUnk_08132A14[] = {
    { 18, 25, -25, -30, 0 },
    { 18, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_08132A2C = { 2, { 0 }, sUnk_08132A14, 60 };

static const BtlFormStep sUnk_08132A38[] = {
    { 18, -55, 25, -30, 0 },
    { 18, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_08132A50 = { 2, { 0 }, sUnk_08132A38, 60 };

static const BtlFormStep sUnk_08132A5C[] = {
    { 18, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132A68 = { 1, { 0 }, sUnk_08132A5C, 60 };

static const BtlFormStep sUnk_08132A74[] = {
    { 18, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132A80 = { 1, { 0 }, sUnk_08132A74, 60 };

static const BtlFormStep sUnk_08132A8C[] = {
    { 19, 25, -25, 0, 0 },
    { 19, 40, 0, 0, 1 },
    { 19, 55, 25, 0, 2 },
    { 19, 65, -12, 0, 3 },
    { 19, 85, 12, 0, 4 },
};

const BtlFormEntry gUnk_08132AC8 = { 5, { 0 }, sUnk_08132A8C, 60 };

static const BtlFormStep sUnk_08132AD4[] = {
    { 19, 65, -12, 0, 0 },
    { 19, 85, 12, 0, 1 },
    { 19, -65, -12, 0, 2 },
    { 19, -85, 12, 0, 3 },
};

const BtlFormEntry gUnk_08132B04 = { 4, { 0 }, sUnk_08132AD4, 60 };

static const BtlFormStep sUnk_08132B10[] = {
    { 19, 65, -12, 0, 0 },
    { 19, 85, 12, 0, 1 },
    { 19, 90, 0, 0, 2 },
};

static const BtlFormEntry sUnk_08132B34 = { 3, { 0 }, sUnk_08132B10, 60 };

static const BtlFormStep sUnk_08132B40[] = {
    { 19, -65, -12, 0, 0 },
    { 19, -85, 12, 0, 1 },
    { 19, 40, 0, 0, 2 },
};

static const BtlFormEntry sUnk_08132B64 = { 3, { 0 }, sUnk_08132B40, 60 };

static const BtlFormStep sUnk_08132B70[] = {
    { 19, 65, -12, 0, 0 },
    { 19, 85, 12, 0, 1 },
};

const BtlFormEntry gUnk_08132B88 = { 2, { 0 }, sUnk_08132B70, 60 };

static const BtlFormStep sUnk_08132B94[] = {
    { 19, -65, -12, 0, 0 },
    { 19, -85, 12, 0, 1 },
};

const BtlFormEntry gUnk_08132BAC = { 2, { 0 }, sUnk_08132B94, 60 };

static const BtlFormStep sUnk_08132BB8[] = {
    { 19, 40, 0, 0, 0 },
    { 19, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_08132BD0 = { 2, { 0 }, sUnk_08132BB8, 60 };

static const BtlFormStep sUnk_08132BDC[] = {
    { 19, 64, 0, 0, 0 },
};

const BtlFormEntry gUnk_08132BE8 = { 1, { 0 }, sUnk_08132BDC, 60 };

static const BtlFormStep sUnk_08132BF4[] = {
    { 20, 25, -25, -30, 0 },
    { 20, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_08132C0C = { 2, { 0 }, sUnk_08132BF4, 60 };

static const BtlFormStep sUnk_08132C18[] = {
    { 20, 40, 0, -30, 0 },
    { 20, -40, 0, -30, 1 },
};

static const BtlFormEntry sUnk_08132C30 = { 2, { 0 }, sUnk_08132C18, 60 };

static const BtlFormStep sUnk_08132C3C[] = {
    { 20, -55, 25, -30, 0 },
    { 20, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_08132C54 = { 2, { 0 }, sUnk_08132C3C, 60 };

static const BtlFormStep sUnk_08132C60[] = {
    { 20, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132C6C = { 1, { 0 }, sUnk_08132C60, 60 };

static const BtlFormStep sUnk_08132C78[] = {
    { 20, -64, 0, -50, 0 },
};

const BtlFormEntry gUnk_08132C84 = { 1, { 0 }, sUnk_08132C78, 60 };

static const BtlFormStep sUnk_08132C90[] = {
    { 20, 25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_08132C9C = { 1, { 0 }, sUnk_08132C90, 60 };

static const BtlFormStep sUnk_08132CA8[] = {
    { 21, 65, -12, -40, 0 },
    { 21, 85, 12, -40, 1 },
};

const BtlFormEntry gUnk_08132CC0 = { 2, { 0 }, sUnk_08132CA8, 60 };

static const BtlFormStep sUnk_08132CCC[] = {
    { 21, 25, -25, -30, 0 },
    { 21, 55, 25, -30, 1 },
};

static const BtlFormEntry sUnk_08132CE4 = { 2, { 0 }, sUnk_08132CCC, 60 };

static const BtlFormStep sUnk_08132CF0[] = {
    { 21, 40, 0, -30, 0 },
    { 21, -40, 0, -30, 1 },
};

static const BtlFormEntry sUnk_08132D08 = { 2, { 0 }, sUnk_08132CF0, 60 };

static const BtlFormStep sUnk_08132D14[] = {
    { 21, 40, 0, -30, 0 },
    { 21, 90, 0, -50, 1 },
};

static const BtlFormEntry sUnk_08132D2C = { 2, { 0 }, sUnk_08132D14, 60 };

static const BtlFormStep sUnk_08132D38[] = {
    { 21, -65, -12, -40, 0 },
    { 21, -85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08132D50 = { 2, { 0 }, sUnk_08132D38, 60 };

static const BtlFormStep sUnk_08132D5C[] = {
    { 21, -55, 25, -30, 0 },
    { 21, -25, -25, -30, 1 },
};

static const BtlFormEntry sUnk_08132D74 = { 2, { 0 }, sUnk_08132D5C, 60 };

static const BtlFormStep sUnk_08132D80[] = {
    { 21, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132D8C = { 1, { 0 }, sUnk_08132D80, 60 };

static const BtlFormStep sUnk_08132D98[] = {
    { 21, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132DA4 = { 1, { 0 }, sUnk_08132D98, 60 };

static const BtlFormStep sUnk_08132DB0[] = {
    { 21, 25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_08132DBC = { 1, { 0 }, sUnk_08132DB0, 60 };

static const BtlFormStep sUnk_08132DC8[] = {
    { 21, -25, -25, -30, 0 },
};

static const BtlFormEntry sUnk_08132DD4 = { 1, { 0 }, sUnk_08132DC8, 60 };

static const BtlFormStep sUnk_08132DE0[] = {
    { 21, 55, 25, -30, 0 },
};

static const BtlFormEntry sUnk_08132DEC = { 1, { 0 }, sUnk_08132DE0, 60 };

static const BtlFormStep sUnk_08132DF8[] = {
    { 21, -55, 25, -30, 0 },
};

static const BtlFormEntry sUnk_08132E04 = { 1, { 0 }, sUnk_08132DF8, 60 };

static const BtlFormStep sUnk_08132E10[] = {
    { 22, 65, -12, -40, 0 },
    { 22, 85, 12, -40, 1 },
};

static const BtlFormEntry sUnk_08132E28 = { 2, { 0 }, sUnk_08132E10, 60 };

static const BtlFormStep sUnk_08132E34[] = {
    { 22, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132E40 = { 1, { 0 }, sUnk_08132E34, 60 };

static const BtlFormStep sUnk_08132E4C[] = {
    { 22, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132E58 = { 1, { 0 }, sUnk_08132E4C, 60 };

static const BtlFormStep sUnk_08132E64[] = {
    { 23, 65, -12, -40, 0 },
    { 23, 85, 12, -40, 1 },
    { 23, 90, 0, -50, 2 },
};

const BtlFormEntry gUnk_08132E88 = { 3, { 0 }, sUnk_08132E64, 60 };

static const BtlFormStep sUnk_08132E94[] = {
    { 23, 40, 0, -30, 0 },
    { 23, -40, 0, -30, 1 },
};

static const BtlFormEntry sUnk_08132EAC = { 2, { 0 }, sUnk_08132E94, 60 };

static const BtlFormStep sUnk_08132EB8[] = {
    { 23, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132EC4 = { 1, { 0 }, sUnk_08132EB8, 60 };

static const BtlFormStep sUnk_08132ED0[] = {
    { 23, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_08132EDC = { 1, { 0 }, sUnk_08132ED0, 60 };

static const BtlFormStep sUnk_08132EE8[] = {
    { 24, 40, 0, 0, 0 },
    { 24, 65, -12, 0, 1 },
    { 24, 85, 12, 0, 2 },
};

const BtlFormEntry gUnk_08132F0C = { 3, { 0 }, sUnk_08132EE8, 60 };

static const BtlFormStep sUnk_08132F18[] = {
    { 24, 65, -12, 0, 0 },
    { 24, 85, 12, 0, 1 },
    { 24, -40, 0, 0, 2 },
};

static const BtlFormEntry sUnk_08132F3C = { 3, { 0 }, sUnk_08132F18, 60 };

static const BtlFormStep sUnk_08132F48[] = {
    { 24, 65, -12, 0, 0 },
    { 24, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08132F60 = { 2, { 0 }, sUnk_08132F48, 60 };

static const BtlFormStep sUnk_08132F6C[] = {
    { 24, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08132F78 = { 1, { 0 }, sUnk_08132F6C, 60 };

static const BtlFormStep sUnk_08132F84[] = {
    { 24, -64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08132F90 = { 1, { 0 }, sUnk_08132F84, 60 };

static const BtlFormStep sUnk_08132F9C[] = {
    { 25, 65, -12, 0, 0 },
    { 25, 85, 12, 0, 1 },
};

const BtlFormEntry gUnk_08132FB4 = { 2, { 0 }, sUnk_08132F9C, 60 };

static const BtlFormStep sUnk_08132FC0[] = {
    { 25, 40, 0, 0, 0 },
    { 25, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_08132FD8 = { 2, { 0 }, sUnk_08132FC0, 60 };

static const BtlFormStep sUnk_08132FE4[] = {
    { 25, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08132FF0 = { 1, { 0 }, sUnk_08132FE4, 60 };

static const BtlFormStep sUnk_08132FFC[] = {
    { 25, -64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133008 = { 1, { 0 }, sUnk_08132FFC, 60 };

static const BtlFormStep sUnk_08133014[] = {
    { 26, 25, -25, 0, 0 },
    { 26, 55, 25, 0, 1 },
};

const BtlFormEntry gUnk_0813302C = { 2, { 0 }, sUnk_08133014, 60 };

static const BtlFormStep sUnk_08133038[] = {
    { 26, 40, 0, 0, 0 },
    { 26, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_08133050 = { 2, { 0 }, sUnk_08133038, 60 };

static const BtlFormStep sUnk_0813305C[] = {
    { 26, -64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133068 = { 1, { 0 }, sUnk_0813305C, 60 };

static const BtlFormStep sUnk_08133074[] = {
    { 26, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133080 = { 1, { 0 }, sUnk_08133074, 60 };

static const BtlFormStep sUnk_0813308C[] = {
    { 27, 65, -12, -40, 0 },
    { 27, 85, 12, -40, 1 },
};

const BtlFormEntry gUnk_081330A4 = { 2, { 0 }, sUnk_0813308C, 60 };

static const BtlFormStep sUnk_081330B0[] = {
    { 27, 64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_081330BC = { 1, { 0 }, sUnk_081330B0, 60 };

static const BtlFormStep sUnk_081330C8[] = {
    { 27, -64, 0, -50, 0 },
};

static const BtlFormEntry sUnk_081330D4 = { 1, { 0 }, sUnk_081330C8, 60 };

static const BtlFormStep sUnk_081330E0[] = {
    { 28, 25, -25, 0, 0 },
    { 28, 55, 25, 0, 1 },
};

static const BtlFormEntry sUnk_081330F8 = { 2, { 0 }, sUnk_081330E0, 60 };

static const BtlFormStep sUnk_08133104[] = {
    { 28, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133110 = { 1, { 0 }, sUnk_08133104, 60 };

static const BtlFormStep sUnk_0813311C[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 40, 0, 0, 1 },
    { 29, 55, 25, 0, 2 },
    { 29, 65, -12, 0, 3 },
    { 29, 85, 12, 0, 4 },
};

const BtlFormEntry gUnk_08133158 = { 5, { 0 }, sUnk_0813311C, 60 };

static const BtlFormStep sUnk_08133164[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 55, 25, 0, 1 },
    { 29, 90, 0, 0, 2 },
    { 29, -65, -12, 0, 3 },
    { 29, -85, 12, 0, 4 },
};

static const BtlFormEntry sUnk_081331A0 = { 5, { 0 }, sUnk_08133164, 60 };

static const BtlFormStep sUnk_081331AC[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 55, 25, 0, 1 },
    { 29, 65, -12, 0, 2 },
    { 29, 85, 12, 0, 3 },
};

const BtlFormEntry gUnk_081331DC = { 4, { 0 }, sUnk_081331AC, 60 };

static const BtlFormStep sUnk_081331E8[] = {
    { 29, 40, 0, 0, 0 },
    { 29, 65, -12, 0, 1 },
    { 29, 85, 12, 0, 2 },
};

static const BtlFormEntry sUnk_0813320C = { 3, { 0 }, sUnk_081331E8, 60 };

static const BtlFormStep sUnk_08133218[] = {
    { 29, 25, -25, 0, 0 },
    { 29, 64, 0, 0, 1 },
    { 29, 55, 25, 0, 2 },
};

static const BtlFormEntry sUnk_0813323C = { 3, { 0 }, sUnk_08133218, 60 };

static const BtlFormStep sUnk_08133248[] = {
    { 29, -25, 25, 0, 0 },
    { 29, -64, 0, 0, 1 },
    { 29, -55, -25, 0, 2 },
};

static const BtlFormEntry sUnk_0813326C = { 3, { 0 }, sUnk_08133248, 60 };

static const BtlFormStep sUnk_08133278[] = {
    { 29, 65, -12, 0, 0 },
    { 29, 85, 12, 0, 1 },
};

const BtlFormEntry gUnk_08133290 = { 2, { 0 }, sUnk_08133278, 60 };

static const BtlFormStep sUnk_0813329C[] = {
    { 29, 40, 0, 0, 0 },
    { 29, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_081332B4 = { 2, { 0 }, sUnk_0813329C, 60 };

static const BtlFormStep sUnk_081332C0[] = {
    { 29, -65, -12, 0, 0 },
    { 29, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_081332D8 = { 2, { 0 }, sUnk_081332C0, 60 };

static const BtlFormStep sUnk_081332E4[] = {
    { 29, -55, 25, 0, 0 },
    { 29, -25, -25, 0, 1 },
};

const BtlFormEntry gUnk_081332FC = { 2, { 0 }, sUnk_081332E4, 60 };

static const BtlFormStep sUnk_08133308[] = {
    { 29, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133314 = { 1, { 0 }, sUnk_08133308, 60 };

static const BtlFormStep sUnk_08133320[] = {
    { 30, 25, -25, 0, 0 },
    { 30, 40, 0, 0, 1 },
    { 30, 55, 25, 0, 2 },
    { 30, 65, -12, 0, 3 },
    { 30, 85, 12, 0, 4 },
};

static const BtlFormEntry sUnk_0813335C = { 5, { 0 }, sUnk_08133320, 60 };

static const BtlFormStep sUnk_08133368[] = {
    { 30, 25, -25, 0, 0 },
    { 30, 55, 25, 0, 1 },
    { 30, 65, -12, 0, 2 },
    { 30, 85, 12, 0, 3 },
};

const BtlFormEntry gUnk_08133398 = { 4, { 0 }, sUnk_08133368, 60 };

static const BtlFormStep sUnk_081333A4[] = {
    { 30, 40, 0, 0, 0 },
    { 30, 65, -12, 0, 1 },
    { 30, 85, 12, 0, 2 },
};

const BtlFormEntry gUnk_081333C8 = { 3, { 0 }, sUnk_081333A4, 60 };

static const BtlFormStep sUnk_081333D4[] = {
    { 30, 25, -25, 0, 0 },
    { 30, 64, 0, 0, 1 },
    { 30, 55, 25, 0, 2 },
};

static const BtlFormEntry sUnk_081333F8 = { 3, { 0 }, sUnk_081333D4, 60 };

static const BtlFormStep sUnk_08133404[] = {
    { 30, -25, 25, 0, 0 },
    { 30, -64, 0, 0, 1 },
    { 30, -55, -25, 0, 2 },
};

static const BtlFormEntry sUnk_08133428 = { 3, { 0 }, sUnk_08133404, 60 };

static const BtlFormStep sUnk_08133434[] = {
    { 30, 65, -12, 0, 0 },
    { 30, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_0813344C = { 2, { 0 }, sUnk_08133434, 60 };

static const BtlFormStep sUnk_08133458[] = {
    { 30, -65, -12, 0, 0 },
    { 30, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08133470 = { 2, { 0 }, sUnk_08133458, 60 };

static const BtlFormStep sUnk_0813347C[] = {
    { 30, -55, 25, 0, 0 },
    { 30, -25, -25, 0, 1 },
};

static const BtlFormEntry sUnk_08133494 = { 2, { 0 }, sUnk_0813347C, 60 };

static const BtlFormStep sUnk_081334A0[] = {
    { 30, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_081334AC = { 1, { 0 }, sUnk_081334A0, 60 };

static const BtlFormStep sUnk_081334B8[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 40, 0, 0, 1 },
    { 31, 25, 25, 0, 2 },
    { 31, -25, 25, 0, 3 },
    { 31, -40, 0, 0, 4 },
    { 31, -25, -25, 0, 5 },
};

static const BtlFormEntry sUnk_08133500 = { 6, { 0 }, sUnk_081334B8, 60 };

static const BtlFormStep sUnk_0813350C[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 40, 0, 0, 1 },
    { 31, 55, 25, 0, 2 },
    { 31, 65, -12, 0, 3 },
    { 31, 85, 12, 0, 4 },
};

const BtlFormEntry gUnk_08133548 = { 5, { 0 }, sUnk_0813350C, 60 };

static const BtlFormStep sUnk_08133554[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 55, 25, 0, 1 },
    { 31, 90, 0, 0, 2 },
    { 31, -65, -12, 0, 3 },
    { 31, -85, 12, 0, 4 },
};

static const BtlFormEntry sUnk_08133590 = { 5, { 0 }, sUnk_08133554, 60 };

static const BtlFormStep sUnk_0813359C[] = {
    { 31, 25, -25, 0, 0 },
    { 31, 55, 25, 0, 1 },
    { 31, 65, -12, 0, 2 },
    { 31, 85, 12, 0, 3 },
};

static const BtlFormEntry sUnk_081335CC = { 4, { 0 }, sUnk_0813359C, 60 };

static const BtlFormStep sUnk_081335D8[] = {
    { 31, 40, 0, 0, 0 },
    { 31, 65, -12, 0, 1 },
    { 31, 85, 12, 0, 2 },
};

const BtlFormEntry gUnk_081335FC = { 3, { 0 }, sUnk_081335D8, 60 };

static const BtlFormStep sUnk_08133608[] = {
    { 31, -65, -12, 0, 0 },
    { 31, -85, 12, 0, 1 },
    { 31, 40, 0, 0, 2 },
};

static const BtlFormEntry sUnk_0813362C = { 3, { 0 }, sUnk_08133608, 60 };

static const BtlFormStep sUnk_08133638[] = {
    { 31, 65, -12, 0, 0 },
    { 31, 85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_08133650 = { 2, { 0 }, sUnk_08133638, 60 };

static const BtlFormStep sUnk_0813365C[] = {
    { 31, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133668 = { 1, { 0 }, sUnk_0813365C, 60 };

static const BtlFormStep sUnk_08133674[] = {
    { 31, 40, 0, 0, 0 },
    { 31, -40, 0, 0, 1 },
};

static const BtlFormEntry sUnk_0813368C = { 2, { 0 }, sUnk_08133674, 60 };

static const BtlFormStep sUnk_08133698[] = {
    { 31, -65, -12, 0, 0 },
    { 31, -85, 12, 0, 1 },
};

static const BtlFormEntry sUnk_081336B0 = { 2, { 0 }, sUnk_08133698, 60 };

static const BtlFormStep sUnk_081336BC[] = {
    { 46, 65, -12, 0, 0 },
    { 46, 85, 12, 0, 1 },
    { 46, -40, 0, 0, 2 },
};

static const BtlFormEntry sUnk_081336E0 = { 3, { 0 }, sUnk_081336BC, 60 };

static const BtlFormStep sUnk_081336EC[] = {
    { 46, -55, 25, 0, 0 },
    { 46, -25, -25, 0, 1 },
};

static const BtlFormEntry sUnk_08133704 = { 2, { 0 }, sUnk_081336EC, 60 };

static const BtlFormStep sUnk_08133710[] = {
    { 46, 64, 0, 0, 0 },
};

const BtlFormEntry gUnk_0813371C = { 1, { 0 }, sUnk_08133710, 60 };

static const BtlFormStep sUnk_08133728[] = {
    { 47, 65, -12, 0, 0 },
    { 47, 85, 12, 0, 1 },
    { 47, 90, 0, 0, 2 },
};

const BtlFormEntry gUnk_0813374C = { 3, { 0 }, sUnk_08133728, 60 };

static const BtlFormStep sUnk_08133758[] = {
    { 47, 25, -25, 0, 0 },
    { 47, 55, 25, 0, 1 },
};

const BtlFormEntry gUnk_08133770 = { 2, { 0 }, sUnk_08133758, 60 };

static const BtlFormStep sUnk_0813377C[] = {
    { 47, 64, 0, 0, 0 },
};

static const BtlFormEntry sUnk_08133788 = { 1, { 0 }, sUnk_0813377C, 60 };

static const BtlFormList sBtlFormLists[144] = {
    { 14, { 0 }, &gBtlFormListEntries[0], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[14], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[18], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[19], 256, { 0 } },
    { 5, { 0 }, &gBtlFormListEntries[21], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[26], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[27], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[28], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[29], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[30], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[31], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[32], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[34], 266, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[36], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[39], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[42], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[45], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[49], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[50], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[53], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[57], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[61], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[63], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[64], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[67], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[69], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[71], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[74], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[77], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[80], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[83], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[86], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[90], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[93], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[96], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[98], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[102], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[105], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[108], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[111], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[115], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[118], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[121], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[123], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[126], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[130], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[134], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[138], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[141], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[144], 256, { 0 } },
    { 6, { 0 }, &gBtlFormListEntries[148], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[154], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[157], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[160], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[162], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[164], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[167], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[170], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[171], 256, { 0 } },
    { 5, { 0 }, &gBtlFormListEntries[175], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[180], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[184], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[188], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[191], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[193], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[195], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[198], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[202], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[205], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[206], 256, { 0 } },
    { 5, { 0 }, &gBtlFormListEntries[208], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[213], 64, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[214], 128, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[216], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[218], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[220], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[222], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[224], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[227], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[230], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[234], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[236], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[238], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[242], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[245], 256, { 0 } },
    { 5, { 0 }, &gBtlFormListEntries[249], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[254], 256, { 0 } },
    { 5, { 0 }, &gBtlFormListEntries[257], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[262], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[265], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[269], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[273], 256, { 0 } },
    { 5, { 0 }, &gBtlFormListEntries[277], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[282], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[285], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[288], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[290], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[292], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[295], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[299], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[303], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[307], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[309], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[312], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[315], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[318], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[321], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[324], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[327], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[330], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[332], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[335], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[339], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[342], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[345], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[348], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[350], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[354], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[358], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[362], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[366], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[370], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[374], 256, { 0 } },
#ifdef VERSION_EU
    { 6, { 0 }, &gBtlFormListEntries[377], 164, { 0 } },
#else
    { 6, { 0 }, &gBtlFormListEntries[377], 256, { 0 } },
#endif
    { 5, { 0 }, &gBtlFormListEntries[383], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[388], 256, { 0 } },
#ifdef VERSION_EU
    { 8, { 0 }, &gBtlFormListEntries[391], 256, { 0 } },
#else
    { 9, { 0 }, &gBtlFormListEntries[391], 256, { 0 } },
#endif
    { 4, { 0 }, &gBtlFormListEntries[400 - FORMATION_LIST_DROP], 256, { 0 } },
    { 4, { 0 }, &gBtlFormListEntries[404 - FORMATION_LIST_DROP], 256, { 0 } },
#ifdef VERSION_EU
    { 8, { 0 }, &gBtlFormListEntries[408 - FORMATION_LIST_DROP], 196, { 0 } },
#else
    { 8, { 0 }, &gBtlFormListEntries[408 - FORMATION_LIST_DROP], 256, { 0 } },
#endif
    { 5, { 0 }, &gBtlFormListEntries[416 - FORMATION_LIST_DROP], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[421 - FORMATION_LIST_DROP], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[424 - FORMATION_LIST_DROP], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[426 - FORMATION_LIST_DROP], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[427 - FORMATION_LIST_DROP], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[428 - FORMATION_LIST_DROP], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[430 - FORMATION_LIST_DROP], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[431 - FORMATION_LIST_DROP], 256, { 0 } },
    { 2, { 0 }, &gBtlFormListEntries[433 - FORMATION_LIST_DROP], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[435 - FORMATION_LIST_DROP], 256, { 0 } },
    { 1, { 0 }, &gBtlFormListEntries[436 - FORMATION_LIST_DROP], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[437 - FORMATION_LIST_DROP], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[440 - FORMATION_LIST_DROP], 256, { 0 } },
    { 3, { 0 }, &gBtlFormListEntries[443 - FORMATION_LIST_DROP], 256, { 0 } },
};

const BtlFormEntry* gBtlFormListEntries[] = {
    &sUnk_08130ECC,
    &sUnk_08131238,
    &sUnk_08131430,
    &sUnk_08130F80,
    &sUnk_081311FC,
    &sUnk_08131358,
    &sUnk_081313C4,
    &sUnk_081311FC,
    &sUnk_08131328,
    &sUnk_081313E8,
    &sUnk_08131238,
    &sUnk_081312C8,
    &sUnk_08130F2C,
    &sUnk_08131448,
    &sUnk_081336E0,
    &sUnk_08133788,
    &sUnk_08133704,
    &sUnk_08133788,
    &sUnk_081326A8,
    &sUnk_081326A8,
    &sUnk_08132714,
    &sUnk_081326A8,
    &sUnk_081326F0,
    &sUnk_0813272C,
    &sUnk_081326CC,
    &sUnk_08132744,
    &sUnk_08131E74,
    &sUnk_08131E5C,
    &sUnk_08131DE4,
    &sUnk_08131F40,
    &sUnk_08131F28,
    &sUnk_08131EB0,
    &sUnk_08131184,
    &sUnk_08132FF0,
    &sUnk_08133650,
    &sUnk_081321C8,
    &sUnk_08131550,
    &sUnk_08133470,
    &sUnk_08132FF0,
    &sUnk_08132198,
    &sUnk_081336B0,
    &sUnk_0813344C,
    &sUnk_0813137C,
    &sUnk_08132FF0,
    &sUnk_081314CC,
    &sUnk_0813137C,
    &sUnk_08132258,
    &sUnk_08132FF0,
    &sUnk_08133008,
    &sUnk_0813335C,
    &sUnk_0813368C,
    &sUnk_08131358,
    &sUnk_0813152C,
    &sUnk_0813152C,
    &sUnk_08133008,
    &sUnk_08132FF0,
    &sUnk_081312C8,
    &sUnk_081314CC,
    &sUnk_0813344C,
    &sUnk_08133470,
    &sUnk_081320D8,
    &sUnk_08131100,
    &sUnk_08132210,
    &sUnk_08131F94,
    &sUnk_081313A0,
    &sUnk_081324B0,
    &sUnk_08131430,
    &sUnk_08132258,
    &sUnk_08132480,
    &sUnk_08132450,
    &sUnk_081324D4,
    &sUnk_081312F8,
    &sUnk_081321C8,
    &sUnk_081324D4,
    &sUnk_081312F8,
    &sUnk_08131238,
    &sUnk_081310B8,
    &sUnk_0813209C,
    &sUnk_08131430,
    &sUnk_0813140C,
    &sUnk_081324F8,
    &sUnk_081312C8,
    &sUnk_081312F8,
    &sUnk_08132414,
    &sUnk_08132258,
    &sUnk_081312F8,
    &sUnk_08131430,
    &sUnk_08132D2C,
    &sUnk_0813140C,
    &sUnk_08132D8C,
    &sUnk_0813323C,
    &sUnk_08132E04,
    &sUnk_08132DD4,
    &sUnk_08133428,
    &sUnk_08132DBC,
    &sUnk_08132DEC,
    &sUnk_081335CC,
    &sUnk_08132D50,
    &sUnk_081332B4,
    &sUnk_08133470,
    &sUnk_08133314,
    &sUnk_081334AC,
    &sUnk_081313C4,
    &sUnk_08133500,
    &sUnk_081311FC,
    &sUnk_081335CC,
    &sUnk_081332D8,
    &sUnk_08133314,
    &sUnk_081335CC,
    &sUnk_08133494,
    &sUnk_08133314,
    &sUnk_08132D2C,
    &sUnk_08131100,
    &sUnk_08132DBC,
    &sUnk_08132DEC,
    &sUnk_0813326C,
    &sUnk_081333F8,
    &sUnk_0813362C,
    &sUnk_08131268,
    &sUnk_08132FF0,
    &sUnk_0813230C,
    &sUnk_081316A0,
    &sUnk_081322E8,
    &sUnk_0813230C,
    &sUnk_08132FF0,
    &sUnk_08132330,
    &sUnk_081316A0,
    &sUnk_0813239C,
    &sUnk_081316E8,
    &sUnk_08131754,
    &sUnk_0813230C,
    &sUnk_081323D8,
    &sUnk_0813230C,
    &sUnk_081323D8,
    &sUnk_08132FF0,
    &sUnk_081323C0,
    &sUnk_08133008,
    &sUnk_081316C4,
    &sUnk_08132378,
    &sUnk_08132FF0,
    &sUnk_081316C4,
    &sUnk_081311FC,
    &sUnk_081322E8,
    &sUnk_08132FD8,
    &sUnk_08131100,
    &sUnk_081316C4,
    &sUnk_08132FF0,
    &sUnk_0813170C,
    &sUnk_08131670,
    &sUnk_081312F8,
    &sUnk_08132348,
    &sUnk_0813230C,
    &sUnk_0813239C,
    &sUnk_081323C0,
    &sUnk_08131184,
    &sUnk_08131B38,
    &sUnk_0813194C,
    &sUnk_081324F8,
    &sUnk_08132798,
    &sUnk_081332B4,
    &sUnk_08132FF0,
    &sUnk_0813326C,
    &sUnk_08131838,
    &sUnk_08131A6C,
    &sUnk_08131298,
    &sUnk_081324F8,
    &sUnk_08133008,
    &sUnk_08132774,
    &sUnk_08131898,
    &sUnk_08131928,
    &sUnk_081331A0,
    &sUnk_08132FD8,
    &sUnk_08131A6C,
    &sUnk_08132FF0,
    &sUnk_08131B80,
    &sUnk_08131148,
    &sUnk_08131238,
    &sUnk_081312F8,
    &sUnk_08131430,
    &sUnk_08131448,
    &sUnk_08132450,
    &sUnk_081327F8,
    &sUnk_08132810,
    &sUnk_081327F8,
    &sUnk_0813137C,
    &sUnk_081329C0,
    &sUnk_0813140C,
    &sUnk_081329D8,
    &sUnk_081327F8,
    &sUnk_0813362C,
    &sUnk_08132A80,
    &sUnk_08132984,
    &sUnk_0813368C,
    &sUnk_08132A08,
    &sUnk_081327E0,
    &sUnk_081311FC,
    &sUnk_0813368C,
    &sUnk_08132798,
    &sUnk_08132A2C,
    &sUnk_081329D8,
    &sUnk_08132A68,
    &sUnk_081329C0,
    &sUnk_081310B8,
    &sUnk_08132A50,
    &sUnk_08132810,
    &sUnk_08133590,
    &sUnk_0813362C,
    &sUnk_0813293C,
    &sUnk_08132A2C,
    &sUnk_081329A8,
    &sUnk_081311FC,
    &sUnk_08132A50,
    &sUnk_0813293C,
    &sUnk_081312F8,
    &sUnk_0813158C,
    &sUnk_081313A0,
    &sUnk_081313A0,
    &sUnk_081316C4,
    &sUnk_08131550,
    &sUnk_081316C4,
    &sUnk_08132270,
    &sUnk_081313A0,
    &sUnk_081322A0,
    &sUnk_08131550,
    &sUnk_081313C4,
    &sUnk_08132270,
    &sUnk_081322A0,
    &sUnk_08132270,
    &sUnk_081322A0,
    &sUnk_081316C4,
    &sUnk_081313A0,
    &sUnk_0813173C,
    &sUnk_0813158C,
    &sUnk_08132234,
    &sUnk_081311FC,
    &sUnk_081321EC,
    &sUnk_08131CD0,
    &sUnk_08132D50,
    &sUnk_08132834,
    &sUnk_081330BC,
    &sUnk_08132888,
    &sUnk_08132870,
    &sUnk_08132D08,
    &sUnk_08132DA4,
    &sUnk_08132D8C,
    &sUnk_08132798,
    &sUnk_08131D3C,
    &sUnk_08132870,
    &sUnk_081330D4,
    &sUnk_08132D8C,
    &sUnk_08132810,
    &sUnk_08132D8C,
    &sUnk_08132810,
    &sUnk_08132D8C,
    &sUnk_08131C4C,
    &sUnk_08132D8C,
    &sUnk_08132DA4,
    &sUnk_081330BC,
    &sUnk_081328A0,
    &sUnk_081328B8,
    &sUnk_081328D0,
    &sUnk_081328E8,
    &sUnk_08131D0C,
    &sUnk_081327BC,
    &sUnk_081330BC,
    &sUnk_08132834,
    &sUnk_08132DA4,
    &sUnk_08132D8C,
    &sUnk_08132888,
    &sUnk_08131CD0,
    &sUnk_08132858,
    &sUnk_081330BC,
    &sUnk_08132888,
    &sUnk_0813140C,
    &sUnk_08132678,
    &sUnk_08133080,
    &sUnk_08132624,
    &sUnk_081318E0,
    &sUnk_08131B80,
    &sUnk_08133080,
    &sUnk_08131AF0,
    &sUnk_0813194C,
    &sUnk_08131358,
    &sUnk_081324B0,
    &sUnk_08131358,
    &sUnk_08132414,
    &sUnk_08131B98,
    &sUnk_08131B98,
    &sUnk_08133050,
    &sUnk_08133080,
    &sUnk_081325D0,
    &sUnk_08131B38,
    &sUnk_08131184,
    &sUnk_081324D4,
    &sUnk_08131838,
    &sUnk_081312F8,
    &sUnk_081324D4,
    &sUnk_08132624,
    &sUnk_08133080,
    &sUnk_08132624,
    &sUnk_08131ACC,
    &sUnk_08131868,
    &sUnk_08132648,
    &sUnk_081325D0,
    &sUnk_08133068,
    &sUnk_08132624,
    &sUnk_08133080,
    &sUnk_081312F8,
    &sUnk_08132B34,
    &sUnk_08132C0C,
    &sUnk_08132DA4,
    &sUnk_08132D8C,
    &sUnk_081311C0,
    &sUnk_08133470,
    &sUnk_08132BD0,
    &sUnk_081311FC,
    &sUnk_08132D74,
    &sUnk_08132D8C,
    &sUnk_08132C30,
    &sUnk_081333F8,
    &sUnk_08132C9C,
    &sUnk_08132B34,
    &sUnk_08132DA4,
    &sUnk_08132D8C,
    &sUnk_08132B34,
    &sUnk_08132C54,
    &sUnk_08132B64,
    &sUnk_081310B8,
    &sUnk_08132B64,
    &sUnk_08132BD0,
    &sUnk_08132D2C,
    &sUnk_08133428,
    &sUnk_08132C54,
    &sUnk_08132B34,
    &sUnk_08132C6C,
    &sUnk_08131238,
    &sUnk_08132DBC,
    &sUnk_08132DBC,
    &sUnk_08132DEC,
    &sUnk_08130F80,
    &sUnk_08133110,
    &sUnk_081332D8,
    &sUnk_08132E28,
    &sUnk_08132EDC,
    &sUnk_08132D2C,
    &sUnk_0813320C,
    &sUnk_08132E58,
    &sUnk_08132E40,
    &sUnk_081330F8,
    &sUnk_08132EAC,
    &sUnk_081311FC,
    &sUnk_08132EAC,
    &sUnk_081313A0,
    &sUnk_08131430,
    &sUnk_08132E28,
    &sUnk_08132DA4,
    &sUnk_08132D8C,
    &sUnk_08132DA4,
    &sUnk_08133110,
    &sUnk_08132E58,
    &sUnk_08133110,
    &sUnk_08132EDC,
    &sUnk_08132CE4,
    &sUnk_0813326C,
    &sUnk_08132DBC,
    &sUnk_08132DEC,
    &sUnk_08131100,
    &sUnk_08133110,
    &sUnk_08132EDC,
    &sUnk_08133110,
    &sUnk_081311FC,
    &sUnk_08132EAC,
    &sUnk_08131184,
    &sUnk_08132D74,
    &sUnk_081310B8,
    &sUnk_08132F60,
    &sUnk_08132F78,
    &sUnk_08133110,
    &sUnk_081315A4,
    &sUnk_081317B4,
    &sUnk_081319B8,
    &sUnk_08131BE0,
    &sUnk_08132EAC,
    &sUnk_08132D08,
    &sUnk_08132DBC,
    &sUnk_08132DEC,
    &sUnk_08132E04,
    &sUnk_08132D74,
    &sUnk_08132E28,
    &sUnk_081330F8,
    &sUnk_08131838,
    &sUnk_08131550,
    &sUnk_081316C4,
    &sUnk_08131970,
    &sUnk_08131B5C,
#ifndef VERSION_EU
    &sUnk_08132EC4,
#endif
    &sUnk_08131AF0,
    &sUnk_081318E0,
    &sUnk_0813170C,
    &sUnk_08131574,
    &sUnk_08132E28,
    &sUnk_08132F78,
    &sUnk_08132F90,
    &sUnk_08133110,
    &sUnk_081311FC,
    &sUnk_08132EAC,
    &sUnk_08132F90,
    &sUnk_08132F78,
    &sUnk_08133110,
    &sUnk_081315A4,
    &sUnk_081317B4,
    &sUnk_081319B8,
    &sUnk_08131BE0,
#ifdef VERSION_EU
    &sUnk_08132F60,
    &sUnk_08132EC4,
    &sUnk_08132E58,
#else
    &sUnk_08132EC4,
    &sUnk_08132E58,
    &sUnk_08132F60,
#endif
    &sUnk_08132F3C,
    &sUnk_08132F60,
    &sUnk_081311FC,
    &sUnk_08131430,
    &sUnk_08132F78,
    &sUnk_08131268,
    &sUnk_08132D8C,
    &sUnk_08132DA4,
    &sUnk_08133110,
    &sUnk_081311FC,
    &sUnk_08132E28,
    &sUnk_0813320C,
    &sUnk_08132E40,
    &sUnk_08132EC4,
    &sUnk_08132EAC,
    &sUnk_081313C4,
    &sUnk_08132EAC,
    &sUnk_08133110,
    &sUnk_08132EDC,
    &sUnk_08132CE4,
    &sUnk_08131100,
    &sUnk_08132270,
    &sUnk_08133314,
    &sUnk_0813158C,
    &sUnk_08132270,
    &sUnk_081334AC,
    &sUnk_0813158C,
    &sUnk_08132270,
    &sUnk_08133668,
    &sUnk_0813158C,
};

const BtlFormList* gBtlFormListByBattleId[147] = {
    &sBtlFormLists[31],
    &sBtlFormLists[32],
    &sBtlFormLists[33],
    &sBtlFormLists[34],
    &sBtlFormLists[35],
    &sBtlFormLists[36],
    &sBtlFormLists[37],
    &sBtlFormLists[38],
    &sBtlFormLists[39],
    &sBtlFormLists[40],
    &sBtlFormLists[71],
    &sBtlFormLists[72],
    &sBtlFormLists[73],
    &sBtlFormLists[74],
    &sBtlFormLists[75],
    &sBtlFormLists[76],
    &sBtlFormLists[77],
    &sBtlFormLists[78],
    &sBtlFormLists[79],
    &sBtlFormLists[80],
    &sBtlFormLists[11],
    &sBtlFormLists[12],
    &sBtlFormLists[13],
    &sBtlFormLists[14],
    &sBtlFormLists[15],
    &sBtlFormLists[16],
    &sBtlFormLists[17],
    &sBtlFormLists[18],
    &sBtlFormLists[19],
    &sBtlFormLists[20],
    &sBtlFormLists[41],
    &sBtlFormLists[42],
    &sBtlFormLists[43],
    &sBtlFormLists[44],
    &sBtlFormLists[45],
    &sBtlFormLists[46],
    &sBtlFormLists[47],
    &sBtlFormLists[48],
    &sBtlFormLists[49],
    &sBtlFormLists[50],
    &sBtlFormLists[91],
    &sBtlFormLists[92],
    &sBtlFormLists[93],
    &sBtlFormLists[94],
    &sBtlFormLists[95],
    &sBtlFormLists[96],
    &sBtlFormLists[97],
    &sBtlFormLists[98],
    &sBtlFormLists[99],
    &sBtlFormLists[100],
    &sBtlFormLists[81],
    &sBtlFormLists[82],
    &sBtlFormLists[83],
    &sBtlFormLists[84],
    &sBtlFormLists[85],
    &sBtlFormLists[86],
    &sBtlFormLists[87],
    &sBtlFormLists[88],
    &sBtlFormLists[89],
    &sBtlFormLists[90],
    &sBtlFormLists[61],
    &sBtlFormLists[62],
    &sBtlFormLists[63],
    &sBtlFormLists[64],
    &sBtlFormLists[65],
    &sBtlFormLists[66],
    &sBtlFormLists[67],
    &sBtlFormLists[68],
    &sBtlFormLists[69],
    &sBtlFormLists[70],
    &sBtlFormLists[101],
    &sBtlFormLists[102],
    &sBtlFormLists[103],
    &sBtlFormLists[104],
    &sBtlFormLists[105],
    &sBtlFormLists[106],
    &sBtlFormLists[107],
    &sBtlFormLists[108],
    &sBtlFormLists[109],
    &sBtlFormLists[110],
    &sBtlFormLists[51],
    &sBtlFormLists[52],
    &sBtlFormLists[53],
    &sBtlFormLists[54],
    &sBtlFormLists[55],
    &sBtlFormLists[56],
    &sBtlFormLists[57],
    &sBtlFormLists[58],
    &sBtlFormLists[59],
    &sBtlFormLists[60],
    &sBtlFormLists[21],
    &sBtlFormLists[22],
    &sBtlFormLists[23],
    &sBtlFormLists[24],
    &sBtlFormLists[25],
    &sBtlFormLists[26],
    &sBtlFormLists[27],
    &sBtlFormLists[28],
    &sBtlFormLists[29],
    &sBtlFormLists[30],
    &sBtlFormLists[111],
    &sBtlFormLists[112],
    &sBtlFormLists[113],
    &sBtlFormLists[114],
    &sBtlFormLists[115],
    &sBtlFormLists[116],
    &sBtlFormLists[117],
    &sBtlFormLists[118],
    &sBtlFormLists[119],
    &sBtlFormLists[120],
    &sBtlFormLists[121],
    &sBtlFormLists[122],
    &sBtlFormLists[123],
    &sBtlFormLists[124],
    &sBtlFormLists[125],
    &sBtlFormLists[126],
    &sBtlFormLists[127],
    &sBtlFormLists[128],
    &sBtlFormLists[129],
    &sBtlFormLists[130],
    &sBtlFormLists[1],
    &sBtlFormLists[0],
    &sBtlFormLists[63],
    &sBtlFormLists[96],
    &sBtlFormLists[91],
    &sBtlFormLists[2],
    &sBtlFormLists[3],
    &sBtlFormLists[4],
    &sBtlFormLists[5],
    &sBtlFormLists[6],
    &sBtlFormLists[7],
    &sBtlFormLists[8],
    &sBtlFormLists[9],
    &sBtlFormLists[10],
    &sBtlFormLists[131],
    &sBtlFormLists[132],
    &sBtlFormLists[133],
    &sBtlFormLists[134],
    &sBtlFormLists[135],
    &sBtlFormLists[136],
    &sBtlFormLists[137],
    &sBtlFormLists[138],
    &sBtlFormLists[139],
    &sBtlFormLists[140],
    &sBtlFormLists[141],
    &sBtlFormLists[142],
    &sBtlFormLists[143],
};
