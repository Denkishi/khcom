#include "monsgage.h"
#include "map_resource_assets.h"
#include "map_tasks.h"
#include "map_enemy_assets.h"
#include "sprites_btl.h"
#include "sprites_emy.h"
#include "sprites_evt.h"
#include "sprites_map.h"
#include "sprites_map_tasks.h"
#include "battle_backgrounds.h"
#include "sprites_card_pictures.h"

extern u8 gUnk_09EF6C38[2];

#ifdef VERSION_EU
#define LANGSEL(x) eu_0805E924(x)
#else
#define LANGSEL(x) (x)
#endif

const AnimDef gUnk_0984BB9C[10] = {
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0, { 0, 0, 0 } },
    { gEmy00L06Frames, gEmy00L06Anims, gEmy00L06Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDF860, gUnk_09EDF880, gUnk_08958AC8, 0, { 0, 0, 0 } },
    { gEmy00L00Frames, gEmy00L00Anims, gEmy00L00Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDF8A8, gUnk_09EDF8C8, gUnk_0895B2C0, 0, { 0, 0, 0 } },
    { gEmy00L02Frames, gEmy00L02Anims, gEmy00L02Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EDF97C, gUnk_09EDF9A4, gUnk_0896213C, 0, { 0, 0, 0 } },
    { gEmy00L07Frames, gEmy00L07Anims, gEmy00L07Tiles, 0, { 0, 0, 0 } },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0, { 0, 0, 0 } },
    { gEmy00L09Frames, gEmy00L09Anims, gEmy00L09Tiles, 0, { 0, 0, 0 } },
};

const AnimDef gUnk_0984BC3C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 1, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC4C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 1, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC5C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC6C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC7C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 2, { 0, 0, 0 },
};

const AnimDef gUnk_0984BC8C = {
    gUnk_09EF8D00, gUnk_09EF8D18, gUnk_098A5F22, 2, { 0, 0, 0 },
};

const UnkStruct_0984BC9C gUnk_0984BC9C = {
    gUnk_0984BB9C, gEmy00Palette,
    32, 8, 16, 0,
    &gTaskDescMapEnm00, 1, 0,
};

const char gTaskNameMapEnm00[] = "Task_MapEnm00";

const AnimDef gUnk_0984BCC4[6] = {
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 0, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 2, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
    { gEmy01L00Frames, gEmy01L00Anims, gEmy01L00Tiles, 3, { 0, 0, 0 } },
};

const UnkStruct_0984BC9C gUnk_0984BD24 = {
    gUnk_0984BCC4, gEmy01Palette,
    17, 16, 16, 0,
    &gTaskDescMapEnm01, 2, 0,
};

const char gTaskNameMapEnm01[] = "Task_MapEnm01";

const AnimDef gUnk_0984BD4C[2] = {
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0, { 0, 0, 0 } },
    { gEmy3800Frames, gEmy3800Anims, gEmy3800Tiles, 0, { 0, 0, 0 } },
};

const AnimDef gUnk_0984BD6C = {
    gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BD7C = {
    gEmy3801Frames, gEmy3801Anims, gEmy3801Tiles, 0, { 0, 0, 0 },
};

const UnkStruct_0984BC9C gUnk_0984BD8C = {
    gUnk_0984BD4C, gEmy38Palette,
    106, 48, 36, 0,
    &gTaskDescMapEnm02, 8, 0,
};

const char gTaskNameMapEnm02[] = "Task_MapEnm02";

const AnimDef gUnk_0984BDB4[4] = {
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
    { gEmy2900Frames, gEmy2900Anims, gEmy2900Tiles, 0, { 0, 0, 0 } },
};

const AnimDef gUnk_0984BDF4 = {
    gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0, { 0, 0, 0 },
};

const AnimDef gUnk_0984BE04 = {
    gEmy2902Frames, gEmy2902Anims, gEmy2902Tiles, 0, { 0, 0, 0 },
};

const UnkStruct_0984BC9C gUnk_0984BE14 = {
    gUnk_0984BDB4, gEmy29Palette,
    73, 56, 36, 0,
    &gTaskDescMapEnm03, 10, 0,
};

const char gTaskNameMapEnm03[] = "Task_MapEnm03";

const AnimDef gUnk_0984BE3C[6] = {
    { gUnk_09EF8D24, gUnk_09EF8D44, gUnk_098A659A, 0, { 0, 0, 0 } },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0, { 0, 0, 0 } },
    { gUnk_09EF8D24, gUnk_09EF8D44, gUnk_098A659A, 0, { 0, 0, 0 } },
    { gEmy0600Frames, gEmy0600Anims, gEmy0600Tiles, 0, { 0, 0, 0 } },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0, { 0, 0, 0 } },
    { gEmy0603Frames, gEmy0603Anims, gEmy0603Tiles, 0, { 0, 0, 0 } },
};

const UnkStruct_0984BC9C gUnk_0984BE9C = {
    gUnk_0984BE3C, gEmy06Palette,
    34, 16, 12, 0,
    &gTaskDescMapEnm04, 2, 0,
};

const char gTaskNameMapEnm04[] = "Task_MapEnm04";

const AnimDef gUnk_0984BEC4[8] = {
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
};

const UnkStruct_0984BC9C gUnk_0984BF44 = {
    gUnk_0984BEC4, gEmy07Palette,
    26, 16, 12, 0,
    &gTaskDescMapEnm05, 4, 0,
};

const char gTaskNameMapEnm05[] = "Task_MapEnm05";

const AnimDef gUnk_0984BF6C[8] = {
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl01Frames, gEmy07Fl01Anims, gEmy07Fl01Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl00Frames, gEmy07Fl00Anims, gEmy07Fl00Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl02Frames, gEmy07Fl02Anims, gEmy07Fl02Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
    { gEmy07Fl03Frames, gEmy07Fl03Anims, gEmy07Fl03Tiles, 0, { 0, 0, 0 } },
};

const UnkStruct_0984BC9C gUnk_0984BFEC = {
    gUnk_0984BF6C, gEmy07bPalette,
    26, 16, 12, 0,
    &gTaskDescMapEnm06, 4, 0,
};

const char gTaskNameMapEnm06[] = "Task_MapEnm06";

const char gTaskNameMapDbg[] = "Task_MapDbg";

const char gTaskNameMapGmkJump[] = "Task_MapGmk_Jump";

const char gTaskNameMapGmkEnm[] = "Task_MapGmk_Enm";

const char gTaskNameMapGmkDmy[] = "Task_MapGmk_Dmy";

const char gTaskNameMapGmkTutorial[] = "Task_MapGmk_Tutorial";

const char gTaskNameMapGmkSpider[] = "Task_MapGmk_Spider";

const char gTaskNameMapGmkGP00[] = "Task_MapGmk_GP00";

const char gTaskNameMapGmkGP01[] = "Task_MapGmk_GP01";

const char gTaskNameMapGmkGP02[] = "Task_MapGmk_GP02";

const char gTaskNameMapGmkGP03[] = "Task_MapGmk_GP03";

const char gTaskNameMapGmkGP04[] = "Task_MapGmk_GP04";

const char gTaskNameMapGmkGP05[] = "Task_MapGmk_GP05";

const char gTaskNameMapGmkGP06[] = "Task_MapGmk_GP06";

const char gTaskNameMapGmkGP07[] = "Task_MapGmk_GP07";

const char gTaskNameMapGmkGP08[] = "Task_MapGmk_GP08";

const char gTaskNameMapGmkGP09[] = "Task_MapGmk_GP09";

const char gTaskNameMapGmk00[] = "Task_MapGmk00";

s32 func_080EF3A0(MapEnmWork* p) {
    FldPos* q = &p->obj.fieldPosition;

    if (p->obj.fieldPosition.x < gFieldState->x - 0x1800 || p->obj.fieldPosition.x > gFieldState->x + 0x10800 ||
        q->y + q->z < gFieldState->y - 0x800 || q->y + q->z > gFieldState->y + 0xC000) {
        p->update = 0;
        ColliderSetDisabled(&p->collider, 1);
        return 1;
    }
    return 0;
}

void func_080EF404(MapEnmWork* p, s32 b, s32 c) {
    FldObj* q = &p->obj;

    if (p->flags & 0x10) {
        b /= 5;
        c /= 5;
    }
    p->obj.fieldPosition.x += gSineTable[q->angle] * q->unk_10 >> 8;
    q->fieldPosition.y += -gSineTable[q->angle + 64] * q->unk_10 >> 8;
    q->unk_10 += b;
    if (q->unk_10 > c) {
        q->unk_10 = c;
    }
}

void func_080EF478(MapEnmWork* p, s32 b, s32 c) {
    FldPos* q = &p->obj.fieldPosition;

    if (func_080DFBDC(q) != 0 || func_080DFF1C(q) != q->z) {
        p->obj.fieldPosition.x = b;
        q->y = c;
        p->update = func_080EF84C;
        ColliderSetDisabled(&p->collider, 1);
    }
}

s32 func_080EF4BC(MapEnmWork* p) {
    FldObj* q = &p->obj;
    u8 ang;

    if (gFieldState->actor.fieldPosition.unk_0C != q->fieldPosition.unk_0C) {
        return 0;
    }
    ang = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    if (abs(GetAngleDiff(ang, q->angle)) > 0x18) {
        return 0;
    }
    q->angle = ang;
    return 1;
}

void func_080EF508(MapEnmWork* p) {
    s32 z;

    func_080E5D6C(p, 0, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        if (p->flags & 8) {
            p->update = func_080EF7B8;
        } else {
            p->update = func_080EF58C;
        }
        *(u16*)&p->unk_D0 = z = 0;
        ColliderSetDisabled(&p->collider, z);
    } else {
        func_080E5DEC(p);

        if (*(s16*)&p->unk_E0 > 0) {
            (*(s16*)&p->unk_E0)--;

            if (*(s16*)&p->unk_E0 <= 0) {
                ColliderSetDisabled(&p->collider, 0);
            }
        }
    }
}

void func_080EF58C(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;
    s32 v;

    func_080E5D6C(p, 1, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    x = p->obj.fieldPosition.x;
    y = q->fieldPosition.y;

    if ((u8)func_080EF4BC(p) != 0) {
        p->unk_D0 = 0;
        p->update = func_080EF718;
    } else if (GetRandom() % 80 == 0) {
        switch (GetRandom() % 4) {
        case 0:
            v = 173;
            break;
        case 1:
            v = 83;
            break;
        case 2:
            v = 211;
            break;
        default:
            v = 45;
            break;
        }
        *(u8*)&q->angle = v;
        p->unk_D0 = 0;
        p->update = func_080EF664;
    }

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EF88C;
    } else {
        func_080E5F50(p);

        if ((u8)func_080EF3A0(p) == 0) {
            func_080EF478(p, x, y);
        }
    }
}

void func_080EF664(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    func_080E5D6C(p, 2, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    x = p->obj.fieldPosition.x;
    y = q->fieldPosition.y;

    if ((u8)func_080EF4BC(p) != 0) {
        p->unk_D0 = 0;
        p->update = func_080EF718;
    } else if (GetRandom() % 80 == 0) {
        q->unk_10 = 0;
        p->update = func_080EF58C;
    } else {
        func_080EF404(p, 12, 0x80);
    }

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EF88C;
    } else {
        func_080E5F50(p);

        if ((u8)func_080EF3A0(p) == 0) {
            func_080EF478(p, x, y);
        }
    }
}

void func_080EF718(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    func_080E5D6C(p, 2, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    x = q->fieldPosition.x;
    y = q->fieldPosition.y;

    if (p->unk_D0 % 8 == 0) {
        if ((u8)func_080EF4BC(p) == 0) {
            q->unk_10 = 0;
            p->update = func_080EF58C;
        }
    }
    func_080EF404(p, 12, 0x180);
    p->unk_D0++;

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EF88C;
    } else {
        func_080E5F50(p);

        if ((u8)func_080EF3A0(p) == 0) {
            func_080EF478(p, x, y);
        }
    }
}

void func_080EF7B8(MapEnmWork* p) {
    FldObj* q = &p->obj;
    s32 x;
    s32 y;

    func_080E5D6C(p, 2, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    x = q->fieldPosition.x;
    y = q->fieldPosition.y;

    if (p->unk_D0 % 8 == 0) {
        q->angle = GetAngle(x, y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }
    func_080EF404(p, 25, 0x200);

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EF88C;
    } else {
        func_080E5F50(p);
        func_080EF478(p, x, y);
        p->unk_D0++;
    }
}

void func_080EF84C(MapEnmWork* p) {
    p->flags |= 4;
    func_080E5D6C(p, 3, 0);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->update = 0;
    }
}

void func_080EF88C(MapEnmWork* p) {
    func_080E5D6C(p, 4, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= 0x40;
        func_080E5EAC(p);
    } else {
        func_080E5DEC(p);
    }
}

void func_080EF8CC(MapEnmWork* p) {
    func_080E5D6C(p, 1, 0);
    p->gfx = AnimGetGfx(&p->anim);
    TaskPoolUpdate(&p->tasks);

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EF88C;
    } else {
        func_080E5F50(p);
    }
}

void Task_MapEnm00_0(MapEnmWork* p, UnkStruct_080E5B90* q) {
    func_080E6394(p, q);

    if (p->update == 0) {
        if (p->flags & 0x20) {
            p->update = func_080EF8CC;
            func_080E5D6C(p, 1, 0);
            p->gfx = AnimGetGfx(&p->anim);
            ColliderSetDisabled(&p->collider, 0);
        } else {
            p->update = func_080EF508;
            func_080E5D6C(p, 0, 0);
            p->gfx = AnimGetGfx(&p->anim);
            ColliderSetDisabled(&p->collider, 1);
        }
    } else {
        ColliderSetDisabled(&p->collider, 0);
    }
    *(u16*)&p->unk_D0 = 0;
}

s32 Task_MapEnm00_1(MapEnmWork* p) {
    FldPos* q = &p->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if ((gUnk_0203C7AC->flags & 4) && p->update != func_080EF88C) {
        return 1;
    }

    if (p->update != 0) {
        p->update(p);

        if (p->update != 0) {
            ColliderSetPosition(&p->collider, q->x, q->y, q->z);
            return 1;
        }
    }
    return 0;
}

void Task_MapEnm00_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm00_3(MapEnmWork* p) {
    func_080E657C(p);
}

void func_080EFA30(MapEnm01Work* p) {
    if (p->enm.obj.fieldPosition.x < gFieldState->x - 0x1800 || p->enm.obj.fieldPosition.x > gFieldState->x + 0x10800) {
        if (p->unk_F8 != 0) {
            p->enm.update = 0;
        }
    } else if (p->unk_F8 == 0) {
        p->unk_F8 = 1;
    }
}

void func_080EFA7C(MapEnmWork* p, u8 a) {
    s32* q = &p->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = p->unk_DC + gSineTable[gFrameCounter & 0xFF] * 10;
        break;
    case 0:
    default:
        v = p->unk_DC + gSineTable[gFrameCounter * 2 & 0xFF] * 12;
        break;
    }

    if (p->flags & 16) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }
    if (q[3] < q[2]) {
        q[2] = t;
        p->unk_DC = t - 0x1C00;
    }
}

void func_080EFB24(MapEnmWork* w, u8 a) {
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;

    if (a != 0) {
        w->unk_D4 = gFieldState->actor.fieldPosition.x;
        w->unk_D8 = gFieldState->actor.fieldPosition.y;
        w->unk_DC = gFieldState->actor.fieldPosition.z - 0x1000;
    } else {
        w->unk_D4 = gFieldState->actor.fieldPosition.x;
        w->unk_D8 = gFieldState->actor.fieldPosition.y;
        w->unk_DC = gFieldState->actor.fieldPosition.z;

        if (GetRandom() % 2) {
            t1 = GetRandom() % 65 * 256;
            t1 += 0x2000;
            w->unk_D4 -= t1;
        } else {
            t2 = GetRandom() % 65 * 256;
            t2 += 0x2000;
            w->unk_D4 += t2;
        }

        t3 = GetRandom() % 121 * 256;
        t3 -= 0x3C00;
        w->unk_D8 += t3;
        t4 = GetRandom() % 49 * 256;
        t4 += 0x1000;
        w->unk_DC -= t4;
    }
}

void func_080EFC08(MapEnmWork* p) {
    MapEnmWork* w = p;
    FldObj* q = &p->obj;

    func_080E5D6C(p, 0, 3);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    func_080EFA7C(p, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if (q->fieldPosition.z < gFieldState->actor.fieldPosition.z - 0x4000) {
        func_080EFB24(p, 0);
        p->unk_D0 = 0;
        q->unk_10 = 0;
        p->update = func_080EFCF4;
    } else if (GetRandom() % 130 == 0) {
        if (GetRandom() % 2 != 0) {
            func_080EFB24(p, 0);
        } else {
            func_080EFB24(p, 1);
        }
        w->unk_D0 = 0;
        q->unk_10 = 0;
        w->update = func_080EFCF4;
    }

    if ((u8)func_080E5FB4(w) != 0) {
        w->update = func_080EFE54;
    } else {
        func_080E5F50(w);
        func_080EFA30((MapEnm01Work*)p);
    }
}

void func_080EFCF4(MapEnmWork* p) {
    FldObj* q = &p->obj;
    FldPos t;
    s32 dx;
    s32 dy;
    s32 v;
    s32 r;
    u32 lim;

    func_080E5D6C(p, 1, 3);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    func_080EFA7C(p, 1);
    t = p->obj.fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    dx = p->unk_D4;
    dy = p->unk_D8;

    if (p->flags & 16) {
        lim = 0x140;
        q->unk_10 += 10;

        if (q->unk_10 > 76) {
            q->unk_10 = 76;
        }
    } else {
        lim = 64;
        q->unk_10 += 51;

        if (q->unk_10 > 0x180) {
            q->unk_10 = 0x180;
        }
    }

    v = (dx - q->fieldPosition.x) >> 5;

    if (v > q->unk_10) {
        v = q->unk_10;
    } else if (v < -q->unk_10) {
        v = -q->unk_10;
    }

    q->fieldPosition.x += v;
    v = (dy - q->fieldPosition.y) >> 5;

    if (v > q->unk_10) {
        v = q->unk_10;
    } else if (v < -q->unk_10) {
        v = -q->unk_10;
    }

    q->fieldPosition.y += v;

    if (p->unk_D0 > lim) {
        p->update = func_080EFC08;
    } else {
        p->unk_D0++;
    }

    r = func_080DFF1C(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = t;
        p->unk_D8 = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = t;
        p->unk_D8 = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.unk_0C = r;
    }

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EFE54;
    } else {
        func_080E5F50(p);
    }
}

void func_080EFE54(MapEnmWork* p) {
    func_080E5D6C(p, 2, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= 0x40;
        func_080E5EAC(p);
    } else {
        func_080E5DEC(p);
    }
}

void func_080EFE94(MapEnmWork* p) {
    func_080E5D6C(p, 0, 0);
    p->gfx = AnimGetGfx(&p->anim);
    TaskPoolUpdate(&p->tasks);

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080EFE54;
    } else {
        func_080E5F50(p);
    }
}

void Task_MapEnm01_0(MapEnmWork* p, UnkStruct_080E5B90* q) {
    MapEnm01Work* w = (MapEnm01Work*)p;

    func_080E6394(p, q);

    if (p->flags & 0x20) {
        p->update = func_080EFE94;
        func_080E5D6C(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    } else {
        p->update = func_080EFC08;
        func_080E5D6C(p, 0, 1);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    }
    w->enm.unk_D0 = 0;
    ((MapEnm01Work*)p)->unk_F8 = 0;
}

s32 Task_MapEnm01_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if ((gUnk_0203C7AC->flags & 4) && p->update != func_080EFE54) {
        return 1;
    }

    if (p->update != 0) {
        ((void (*)(MapEnmWork*))p->update)(q);

        if (p->update != 0) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm01_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm01_3(MapEnmWork* p) {
    func_080E657C(p);
}

void func_080EFFF8(MapEnmWork* p) {
    func_080E5D6C(p, 0, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);

    if (func_080E02E0(&p->obj.fieldPosition, p->unk_C8, p->unk_CA)) {
        m4aSongNumStart(SONG_SYS_FIELD_ATT00);
        gUnk_0203C7AC->flags |= 0x80;
        gUnk_0203C7AC->flags |= 4;
        func_080E5EAC(p);
    }
    func_080E5F50(p);
}

void Task_MapEnm02_0(MapEnmWork* p, UnkStruct_080E5B90* q) {
    func_080E6394(p, q);
    p->update = func_080EFFF8;
    func_080E5D6C(p, 0, 1);
    p->gfx = AnimGetGfx(&p->anim);
    ColliderSetDisabled(&p->collider, 0);
}

s32 Task_MapEnm02_1(MapEnmWork* p) {
    MapEnmWork* w = p;
    FldPos* q = &w->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if (w->update != 0) {
        ((void (*)(MapEnmWork*))w->update)(w);

        if (w->update != 0) {
            ColliderSetPosition(&w->collider, q->x, q->y, q->z);
            return 1;
        }
    }
    return 0;
}

void Task_MapEnm02_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm02_3(MapEnmWork* p) {
    func_080E657C(p);
}

void func_080F0108(MapEnmWork* p, u8 a) {
    s32* q = &p->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = p->unk_DC + gSineTable[gFrameCounter & 0xFF] * 10;
        break;
    case 0:
    default:
        v = p->unk_DC + gSineTable[gFrameCounter * 2 & 0xFF] * 12;
        break;
    }

    if (p->flags & 16) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }
    if (q[3] < q[2]) {
        q[2] = t;
        p->unk_DC = t - 0x1C00;
    }
}

s32 func_080F01B0(MapEnmWork* p) {
    s32* q = &p->obj.fieldPosition.x;
    s32 dx;
    s32 dy;
    s32 lim;

    q[4] += 0x100;
    if (q[4] > 0x500) {
        q[4] = 0x500;
    }

    dx = (p->unk_D4 - p->obj.fieldPosition.x) / 32;
    lim = q[4];

    if (dx > lim) {
        dx = lim;
    } else if (dx < -lim) {
        dx = -lim;
    }
    q[0] += dx;

    dy = (p->unk_D8 - q[1]) / 32;

    if (dy > lim) {
        dy = lim;
    } else if (dy < -lim) {
        dy = -lim;
    }
    q[1] += dy;

    if (p->unk_D0 > 64) {
        return 1;
    }
    p->unk_D0++;
    return 0;
}

s32 func_080F023C(MapEnm03Work* p, s32 lim) {
    s32 dx;
    s32 dy;

    dx = p->home.x - gFieldState->actor.fieldPosition.x;
    if (dx < 0) {
        dx = gFieldState->actor.fieldPosition.x - p->home.x;
    }
    dy = p->home.y - gFieldState->actor.fieldPosition.y;
    if (dy < 0) {
        dy = gFieldState->actor.fieldPosition.y - p->home.y;
    }

    if (dx > 0x8000 || dy > 0x8000) {
        return 0;
    }
    return Sqrt8((dx * dx >> 8) + (dy * dy >> 8)) < lim ? 1 : 0;
}

void func_080F02A0(MapEnmWork* w) {
    FldObj* q = &w->obj;

    func_080E5D6C(w, 0, 3);
    func_080E5DEC(w);
    TaskPoolUpdate(&w->tasks);
    func_080F0108(w, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(w->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)func_080F023C((MapEnm03Work*)w, 0x6000) != 0 && q->fieldPosition.unk_0C == gFieldState->actor.fieldPosition.unk_0C) {
        w->unk_D4 = gFieldState->actor.fieldPosition.x;
        w->unk_D8 = gFieldState->actor.fieldPosition.y;
        w->unk_DC = gFieldState->actor.fieldPosition.unk_0C - 0x1000;
        w->unk_D0 = 0;
        q->unk_10 = 0;
        w->update = func_080F0348;
    }
    func_080E5F50(w);
}

void func_080F0348(MapEnmWork* w) {
    MapEnm03Work* q = (MapEnm03Work*)w;
    FldObj* v = &w->obj;
    FldPos tmp;
    s32 n;

    func_080E5D6C(w, 1, 3);
    func_080E5DEC(w);
    TaskPoolUpdate(&w->tasks);
    func_080F0108(w, 1);
    tmp = v->fieldPosition;

    if (GetRandom() % 20 != 0) {
        v->angle = GetAngle(w->obj.fieldPosition.x, v->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)func_080F023C((MapEnm03Work*)w, 0x6000) != 0 && v->fieldPosition.unk_0C == gFieldState->actor.fieldPosition.unk_0C) {
        w->unk_D4 = gFieldState->actor.fieldPosition.x;
        w->unk_D8 = gFieldState->actor.fieldPosition.y;
    }

    if ((u8)func_080F01B0(&q->enm) != 0) {
        w->unk_D4 = q->home.x;
        w->unk_D8 = q->home.y;
        w->unk_DC = q->home.z;
        w->unk_D0 = 0;
        v->unk_10 = 0;
        w->update = func_080F0470;
    }

    n = func_080DFF1C(&v->fieldPosition);

    if (n < v->fieldPosition.z) {
        v->fieldPosition = tmp;
        w->unk_D8 = v->fieldPosition.y + 0x1000;
    } else if (n == 0x100000) {
        v->fieldPosition = tmp;
        w->unk_D8 = v->fieldPosition.y - 0x1000;
    } else {
        v->fieldPosition.unk_0C = n;
    }

    func_080E5F50(w);
}

void func_080F0470(MapEnmWork* w) {
    FldObj* q = &w->obj;
    FldPos save;
    s32 r;

    func_080E5D6C(w, 1, 3);
    func_080E5DEC(w);
    TaskPoolUpdate(&w->tasks);
    func_080F0108(w, 1);
    save = q->fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(w->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)func_080F01B0(w) != 0) {
        w->unk_D0 = 0;
        q->unk_10 = 0;
        w->update = func_080F02A0;
    }

    r = func_080DFF1C(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = save;
        w->unk_D8 = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = save;
        w->unk_D8 = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.unk_0C = r;
    }
    func_080E5F50(w);
}

void Task_MapEnm03_0(MapEnmWork* w, UnkStruct_080E5B90* arg) {
    func_080E6394(w, arg);
    w->update = func_080F02A0;
    func_080E5D6C(w, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderSetDisabled(&w->collider, 0);
    w->unk_D0 = 0;
    ((MapEnm03Work*)w)->home = w->obj.fieldPosition;
}

s32 Task_MapEnm03_1(MapEnmWork* p) {
    MapEnmWork* w = p;
    FldPos* q = &w->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if (w->update != 0) {
        ((void (*)(MapEnmWork*))w->update)(w);

        if (w->update != 0) {
            ColliderSetPosition(&w->collider, q->x, q->y, q->z);
            return 1;
        }
    }
    return 0;
}

void Task_MapEnm03_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm03_3(MapEnmWork* p) {
    func_080E657C(p);
}

void func_080F0614(MapEnm01Work* p) {
    if (p->enm.obj.fieldPosition.x < gFieldState->x - 0x1800 || p->enm.obj.fieldPosition.x > gFieldState->x + 0x10800) {
        if (p->unk_F8 != 0) {
            p->enm.update = 0;
        }
    } else if (p->unk_F8 == 0) {
        p->unk_F8 = 1;
    }
}

void func_080F0660(MapEnmWork* p, u8 a) {
    s32* q = &p->obj.fieldPosition.x;
    s32 t = q[2];
    s32 v;

    switch (a) {
    case 1:
        v = p->unk_DC + gSineTable[gFrameCounter & 0xFF] * 10;
        break;
    case 0:
    default:
        v = p->unk_DC + gSineTable[gFrameCounter * 2 & 0xFF] * 12;
        break;
    }

    if (p->flags & 16) {
        q[2] += (v - q[2]) / 80;
    } else {
        q[2] += (v - q[2]) >> 4;
    }
    if (q[3] < q[2]) {
        q[2] = t;
        p->unk_DC = t - 0x1C00;
    }
}

void func_080F0708(MapEnmWork* p, u8 flag) {
    if (flag) {
        p->unk_D4 = gFieldState->actor.fieldPosition.x;
        p->unk_D8 = gFieldState->actor.fieldPosition.y;
        p->unk_DC = gFieldState->actor.fieldPosition.z - 0x1000;
    } else {
        p->unk_D4 = gFieldState->actor.fieldPosition.x;
        p->unk_D8 = gFieldState->actor.fieldPosition.y;
        p->unk_DC = gFieldState->actor.fieldPosition.z;

        if (GetRandom() % 2) {
            s32 t = GetRandom() % 65 * 256 + 0x2000;

            p->unk_D4 -= t;
        } else {
            s32 t = GetRandom() % 65 * 256 + 0x2000;

            p->unk_D4 += t;
        }
        {
            s32 t = GetRandom() % 121 * 256 - 0x3C00;

            p->unk_D8 += t;
        }
        {
            s32 t = GetRandom() % 49 * 256 + 0x1000;

            p->unk_DC -= t;
        }
    }
}

void func_080F07EC(MapEnmWork* p) {
    MapEnmWork* r = p;
    FldObj* q = &p->obj;
    FldPos tmp;

    func_080E5D6C(p, 0, 3);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    tmp = p->obj.fieldPosition;
    func_080F0660(p, 0);

    if (GetRandom() % 20 == 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if (q->fieldPosition.z < gFieldState->actor.fieldPosition.z - 0x4000) {
        func_080F0708(p, 0);
        p->unk_D0 = 0;
        q->unk_10 = 0;
        p->update = func_080F08E4;
    } else if (GetRandom() % 130 == 0) {
        if (GetRandom() % 2) {
            func_080F0708(p, 0);
        } else {
            func_080F0708(p, 1);
        }

        r->unk_D0 = 0;
        q->unk_10 = 0;
        r->update = func_080F08E4;
    }

    if ((u8)func_080E5FB4(r) != 0) {
        r->update = func_080F0A44;
    } else {
        func_080E5F50(r);
        func_080F0614((MapEnm01Work*)p);
    }
}

void func_080F08E4(MapEnmWork* p) {
    FldObj* q = &p->obj;
    FldPos t;
    s32 dx;
    s32 dy;
    s32 v;
    s32 r;
    u32 lim;

    func_080E5D6C(p, 1, 3);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);
    func_080F0660(p, 1);
    t = p->obj.fieldPosition;

    if (GetRandom() % 20 != 0) {
        q->angle = GetAngle(p->obj.fieldPosition.x, q->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    dx = p->unk_D4;
    dy = p->unk_D8;

    if (p->flags & 16) {
        lim = 0x140;
        q->unk_10 += 10;

        if (q->unk_10 > 76) {
            q->unk_10 = 76;
        }
    } else {
        lim = 64;
        q->unk_10 += 51;

        if (q->unk_10 > 0x180) {
            q->unk_10 = 0x180;
        }
    }

    v = (dx - q->fieldPosition.x) >> 5;

    if (v > q->unk_10) {
        v = q->unk_10;
    } else if (v < -q->unk_10) {
        v = -q->unk_10;
    }

    q->fieldPosition.x += v;
    v = (dy - q->fieldPosition.y) >> 5;

    if (v > q->unk_10) {
        v = q->unk_10;
    } else if (v < -q->unk_10) {
        v = -q->unk_10;
    }

    q->fieldPosition.y += v;

    if (p->unk_D0 > lim) {
        p->update = func_080F07EC;
    } else {
        p->unk_D0++;
    }

    r = func_080DFF1C(&q->fieldPosition);

    if (r < q->fieldPosition.z) {
        q->fieldPosition = t;
        p->unk_D8 = q->fieldPosition.y + 0x1000;
    } else if (r == 0x100000) {
        q->fieldPosition = t;
        p->unk_D8 = q->fieldPosition.y - 0x1000;
    } else {
        q->fieldPosition.unk_0C = r;
    }

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080F0A44;
    } else {
        func_080E5F50(p);
    }
}

void func_080F0A44(MapEnmWork* p) {
    func_080E5D6C(p, 2, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= 0x40;
        func_080E5EAC(p);
    } else {
        func_080E5DEC(p);
    }
}

void func_080F0A84(MapEnmWork* p) {
    func_080E5D6C(p, 0, 0);
    p->gfx = AnimGetGfx(&p->anim);
    TaskPoolUpdate(&p->tasks);

    if ((u8)func_080E5FB4(p)) {
        p->update = func_080F0A44;
    } else {
        func_080E5F50(p);
    }
}

void Task_MapEnm04_0(MapEnmWork* p, UnkStruct_080E5B90* q) {
    MapEnm01Work* w = (MapEnm01Work*)p;

    func_080E6394(p, q);

    if (p->flags & 0x20) {
        p->update = func_080F0A84;
        func_080E5D6C(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    } else {
        p->update = func_080F07EC;
        func_080E5D6C(p, 0, 1);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 0);
    }
    w->enm.unk_D0 = 0;
    ((MapEnm01Work*)p)->unk_F8 = 0;
}

s32 Task_MapEnm04_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if ((gUnk_0203C7AC->flags & 4) && p->update != func_080F0A44) {
        return 1;
    }

    if (p->update != 0) {
        ((void (*)(MapEnmWork*))p->update)(q);

        if (p->update != 0) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm04_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm04_3(MapEnmWork* p) {
    func_080E657C(p);
}

void func_080F0BE8(MapEnmWork* p) {
    MapEnmWork* q = p;

    func_080E5D6C(p, 0, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        ColliderSetDisabled(&p->collider, 0);
        p->unk_D0 = GetRandom() % 121 + 60;
        p->update = func_080F0C68;
    } else {
        func_080E5DEC(q);
        if (q->unk_E0 > 0) {
            q->unk_E0--;

            if (q->unk_E0 <= 0) {
                ColliderSetDisabled(&q->collider, 0);
            }
        }
    }
}

void func_080F0C68(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldObj* r = &p->obj;

    func_080E5D6C(p, 1, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);

    if (GetRandom() % 20 == 0) {
        r->angle = GetAngle(p->obj.fieldPosition.x, r->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080F0D40;
    } else {
        func_080E5F50(p);

        if (p->unk_D0 != 0) {
            p->unk_D0--;
        } else {
            ColliderSetDisabled(&q->collider, 1);
            q->update = func_080F0D00;
        }
    }
}

void func_080F0D00(MapEnmWork* p) {
    p->flags |= 4;
    func_080E5D6C(p, 2, 0);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->update = 0;
    }
}

void func_080F0D40(MapEnmWork* p) {
    func_080E5D6C(p, 3, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= 0x40;
        func_080E5EAC(p);
    } else {
        func_080E5DEC(p);
    }
}

void Task_MapEnm05_0(MapEnmWork* p, UnkStruct_080E5B90* q) {
    func_080E6394(p, q);

    if (p->update == 0) {
        p->update = func_080F0BE8;
        func_080E5D6C(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 1);
    } else {
        ColliderSetDisabled(&p->collider, 0);
    }
    p->unk_D0 = 0;
}

s32 Task_MapEnm05_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if ((gUnk_0203C7AC->flags & 4) && p->update != func_080F0D40) {
        return 1;
    }

    if (p->update != 0) {
        ((void (*)(MapEnmWork*))p->update)(q);

        if (p->update != 0) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm05_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm05_3(MapEnmWork* p) {
    func_080E657C(p);
}

void func_080F0E6C(MapEnmWork* p) {
    MapEnmWork* q = p;

    func_080E5D6C(p, 0, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        ColliderSetDisabled(&p->collider, 0);
        p->unk_D0 = GetRandom() % 121 + 60;
        p->update = func_080F0EEC;
    } else {
        func_080E5DEC(q);
        if (q->unk_E0 > 0) {
            q->unk_E0--;

            if (q->unk_E0 <= 0) {
                ColliderSetDisabled(&q->collider, 0);
            }
        }
    }
}

void func_080F0EEC(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldObj* r = &p->obj;

    func_080E5D6C(p, 1, 1);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);

    if (GetRandom() % 20 == 0) {
        r->angle = GetAngle(p->obj.fieldPosition.x, r->fieldPosition.y, gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y);
    }

    if ((u8)func_080E5FB4(p) != 0) {
        p->update = func_080F0FC4;
    } else {
        func_080E5F50(p);

        if (p->unk_D0 != 0) {
            p->unk_D0--;
        } else {
            ColliderSetDisabled(&q->collider, 1);
            q->update = func_080F0F84;
        }
    }
}

void func_080F0F84(MapEnmWork* p) {
    p->flags |= 4;
    func_080E5D6C(p, 2, 0);
    func_080E5DEC(p);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->update = 0;
    }
}

void func_080F0FC4(MapEnmWork* p) {
    func_080E5D6C(p, 3, 0);
    TaskPoolUpdate(&p->tasks);

    if (AnimIsFinished(&p->anim)) {
        p->flags |= 0x40;
        func_080E5EAC(p);
    } else {
        func_080E5DEC(p);
    }
}

void Task_MapEnm06_0(MapEnmWork* p, UnkStruct_080E5B90* q) {
    func_080E6394(p, q);

    if (p->update == 0) {
        p->update = func_080F0E6C;
        func_080E5D6C(p, 0, 0);
        p->gfx = AnimGetGfx(&p->anim);
        ColliderSetDisabled(&p->collider, 1);
    } else {
        ColliderSetDisabled(&p->collider, 0);
    }
    p->unk_D0 = 0;
}

s32 Task_MapEnm06_1(MapEnmWork* p) {
    MapEnmWork* q = p;
    FldPos* pos = &p->obj.fieldPosition;

    if (gFieldState->flags & 0x40000) {
        func_080E6034(p);
        return 0;
    }

    if ((gUnk_0203C7AC->flags & 4) && p->update != func_080F0FC4) {
        return 1;
    }

    if (p->update != 0) {
        ((void (*)(MapEnmWork*))p->update)(q);

        if (p->update != 0) {
            ColliderSetPosition(&p->collider, pos->x, pos->y, pos->z);
            return 1;
        }
    }

    return 0;
}

void Task_MapEnm06_2(MapEnmWork* p) {
    func_080E64D4(p);
}

void Task_MapEnm06_3(MapEnmWork* p) {
    func_080E657C(p);
}

s32 func_080F10F0(UnkStruct_080DEE18* p) {
    return ((s8)gGameState.floor << 28) + (p->unk_09 << 20) + (p->unk_0A << 16) + (gUnk_0203C590.unk_06 << 8) + (gUnk_0203C590.unk_05 << 4) + gUnk_0203C590.unk_04;
}

void func_080F1124(MapDbgWork* w) {
    if ((GetKeysHeld() & (L_BUTTON | R_BUTTON)) == (L_BUTTON | R_BUTTON)) {
        if (GetKeysPressed() & SELECT_BUTTON) {
            *w->unk_04 = 1;
            func_0801CB0C();
            ModeRequest(&gModeDebflag, 1);
        }

#ifndef VERSION_EU
        if (GetKeysPressed() & START_BUTTON) {
            w->unk_00 = 1;
            *w->unk_04 = 1;
            w->update = func_080F117C;
        }
#endif
    }
}

void func_080F117C(MapDbgWork* w) {
    UnkStruct_080DEE18* d;
    s32 step;
    s32 i;

    step = 1;

    for (i = w->unk_0C; i > 0; i--) {
        step <<= 4;
    }

    d = func_080DEE18(gUnk_0203C590.unk_06);

    if (GetKeysRepeat() & DPAD_UP) {
        d->unk_04 += step;
    }

    if (GetKeysRepeat() & DPAD_DOWN) {
        d->unk_04 -= step;
    }

    if (GetKeysPressed() & DPAD_LEFT) {
        w->unk_0C = w->unk_0C == 7 ? 0 : w->unk_0C + 1;
    }

    if (GetKeysPressed() & DPAD_RIGHT) {
        w->unk_0C = w->unk_0C == 0 ? 7 : w->unk_0C - 1;
    }

    w->unk_2C = FormatSmallFontHex(d->unk_04, w->unk_18);

    if (GetKeysPressed() & SELECT_BUTTON) {
        if (++gUnk_0203C590.unk_04 > 12) {
            gUnk_0203C590.unk_04 = 0;
        }

        w->unk_42 = FormatSmallFontHex(func_080F10F0(d), w->unk_2E);
    }

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        w->update = func_080F1274;
    } else if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        *w->unk_04 = 0;
        w->update = func_080F1124;
    }
}

void func_080F1274(MapDbgWork* w) {
    UnkStruct_080DEE18* d = func_080DEE18(gUnk_0203C590.unk_06);

    if ((GetKeysRepeat() & DPAD_UP) && w->unk_0D == 0) {
        gUnk_0203C590.unk_04 = gUnk_0203C590.unk_04 < 12 ? gUnk_0203C590.unk_04 + 1 : 0;
    }

    if ((GetKeysRepeat() & DPAD_DOWN) && w->unk_0D == 0) {
        gUnk_0203C590.unk_04 = gUnk_0203C590.unk_04 != 0 ? gUnk_0203C590.unk_04 - 1 : 12;
    }

    w->unk_42 = FormatSmallFontHex(func_080F10F0(d), w->unk_2E);

    if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
        w->update = func_080F117C;
    }

    if (GetKeysPressed() & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        *w->unk_04 = 0;
        w->update = func_080F1124;
    }
}

void Task_MapDbg_0(MapDbgWork* w, u8* p) {
#ifndef VERSION_EU
    UnkStruct_080DEE18* d;
#endif

    w->unk_00 = 0;
    w->unk_04 = p;
    *p = 0;
    w->update = func_080F1124;
    w->unk_0C = 0;
    w->unk_0D = 0;
#ifdef VERSION_EU
    func_080DEE18(gUnk_0203C590.unk_06);
#else
    d = func_080DEE18(gUnk_0203C590.unk_06);
    w->tiles = LoadSmallFontTiles();
    w->palette = LoadSmallFontPalette();
    w->unk_2C = FormatSmallFontHex(d->unk_04, w->unk_18);
    w->unk_42 = FormatSmallFontHex(func_080F10F0(d), w->unk_2E);
    w->unk_46 = EncodeSmallFontString(gUnk_09EF6C38, &w->unk_44);
#endif
}

s32 Task_MapDbg_1(MapDbgWork* w) {
    w->update(w);
    return 1;
}

void Task_MapDbg_2(MapDbgWork* w) {
#ifndef VERSION_EU
    if (w->unk_00 != 0) {
        DrawSmallFontString(240 - w->unk_2C * 8, 0x8E, w->unk_18, w->tiles, w->palette, 0, w->unk_2C);
        DrawSmallFontString(240 - w->unk_42 * 8, 0x96, w->unk_2E, w->tiles, w->palette, 0, w->unk_42);

        if (*w->unk_04 != 0) {
            if (w->update == func_080F117C) {
                DrawSmallFontString(240 - (w->unk_0C + 1) * 8, 0x90, &w->unk_44, w->tiles, w->palette, 0, w->unk_46);
            } else {
                DrawSmallFontString(240 - (w->unk_0D + 1) * 8, 0x98, &w->unk_44, w->tiles, w->palette, 0, w->unk_46);
            }
        }
    }
#endif
}

void Task_MapDbg_3(MapDbgWork* w) {
#ifndef VERSION_EU
    FreeSmallFontResources(w->tiles, w->palette);
#endif
}

void func_080F1460(MapGmkJumpWork* w) {
    if (ColliderIsTouchingType(&w->collider, 1) && (w->collider.unk_2E & 2)) {
        gUnk_0203C7AC->unk_1C = w->unk_0C4;
        gUnk_0203C7AC->unk_18 = w->obj.angle;
        w->update = func_080F14C4;
        w->unk_0C0 = 1;
        AnimStart(&w->anim, 1, 1);
    } else {
        AnimUpdate(&w->anim);
    }
}

void func_080F14C4(MapGmkJumpWork* w) {
    if (ColliderIsTouchingType(&w->collider, 1)) {
        gUnk_0203C7AC->unk_1C = w->unk_0C4;
        gUnk_0203C7AC->unk_18 = w->obj.angle;
    } else if (gFieldState->actor.fieldPosition.z != gFieldState->actor.fieldPosition.unk_0C) {
        w->update = func_080F1544;
        w->unk_0C0 = 2;
        AnimStart(&w->anim, 2, 1);
    } else {
        w->update = func_080F1460;
        w->unk_0C0 = 0;
        AnimStart(&w->anim, 0, 1);
    }
}

void func_080F1544(MapGmkJumpWork* w) {
    if (AnimIsFinished(&w->anim)) {
        w->update = func_080F1460;
        w->unk_0C0 = 0;
        AnimStart(&w->anim, 0, 1);
    } else {
        AnimUpdate(&w->anim);
    }
}

void Task_MapGmk_Jump_0(MapGmkJumpWork* w, UnkStruct_02034F20* arg) {
    FldObj* p = &w->obj;
    AnimState* a;
    s32 v;

    p->fieldPosition.x = arg->x << 13;
    p->fieldPosition.y = arg->y << 12;
    p->fieldPosition.z = 0;
    p->fieldPosition.z = w->obj.fieldPosition.unk_0C = func_080DFF30(&p->fieldPosition);
    p->fieldPosition.y -= w->obj.fieldPosition.unk_0C;

    switch (arg->unk_0E) {
    case 3:
        v = 211;
        break;
    case 5:
        v = 45;
        break;
    case 0:
    default:
        v = 0;
        break;
    }
    *(u8*)&p->angle = v;
    w->unk_0C4 = arg->unk_14 - arg->unk_10;
    w->palette = LoadObjPalette(&gUnk_099910C4[0x240], 32);
    w->tiles = LoadObjTiles(gUnk_0985A3EA, 0x980);
    a = &w->anim;
    AnimInit(a, gUnk_09EF8488, gUnk_09EF8468);
    w->unk_0C0 = 0;
    AnimStart(a, 0, 1);
    w->update = func_080F1460;
    ColliderInit(&w->collider, 6, 16, 0);
    ColliderSetPosition(&w->collider, p->fieldPosition.x, p->fieldPosition.y, p->fieldPosition.z);
}

s32 Task_MapGmk_Jump_1(MapGmkJumpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        w->update(w);
    }
    return 1;
}

void Task_MapGmk_Jump_2(MapGmkJumpWork* w) {
    u16 v;
    s32 k;
    s16 x;
    s16 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_Jump_3(MapGmkJumpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F173C(MapGmkEnmWork* w) {
    if (w->unk_070 != 0) {
        w->gfx = AnimUpdate(&w->anim);
        ApproachValue(&w->obj.fieldPosition.z, w->unk_06C, w->unk_070);
        w->unk_070--;
    } else {
        gUnk_0203C7AC->flags |= 2;
        gFieldState->flags |= 0x80;
        gUnk_0203C7AC->unk_0E = func_080E5E44();
        w->unk_064 = 0;
    }

    return 1;
}

void Task_MapGmk_Enm_0(MapGmkEnmWork* w, FldPos* arg) {
    FldPos* e = &w->obj.fieldPosition;
    AnimState* an;
    void* anim;
    void* frames;
    u8 f;

    w->obj.fieldPosition = *arg;
    w->obj.fieldPosition.y += 0x800;
    w->obj.fieldPosition.z -= 0x1000;
    w->obj.unk_1A = 16;

    if (gUnk_0203C590.unk_04 != 2) {
        w->tiles = AllocObjTiles(0x220, gEmy01L00Tiles);
        w->palette = LoadObjPalette(gEmy01Palette, 32);
        an = &w->anim;
        anim = gEmy01L00Anims;
        frames = gEmy01L00Frames;
    } else {
        w->tiles = AllocObjTiles(0x440, gEmy0600Tiles);
        w->palette = LoadObjPalette(gEmy06Palette, 32);
        an = &w->anim;
        anim = gEmy0600Anims;
        frames = gEmy0600Frames;
    }

    do {
        AnimInit(an, anim, frames);
        AnimStart(an, 0, 1);
    } while (0);
    w->gfx = AnimGetGfx(an);
    w->unk_064 = func_080F173C;
    f = 0;

    if (gFieldState->actor.fieldPosition.x >= e->x) {
        f = 1;
    }
    w->unk_068 = f;
    w->unk_070 = 8;
    w->unk_06C = e->z - 0x1000;
}

u8 Task_MapGmk_Enm_1(MapGmkEnmWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->unk_064 != 0) {
        return w->unk_064(w);
    }
    return 1;
}

void Task_MapGmk_Enm_2(MapGmkEnmWork* w) {
    u16 flags;
    s32 k;
    s32 x;
    s32 y;
    s32 t;

    t = w->unk_068;
    flags = 0x800;

    if (t) {
        flags = 0x801;
    }
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, flags, -0x1004 - k * 4);
}

void Task_MapGmk_Enm_3(MapGmkEnmWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void Task_MapGmk_Dmy_0(MapGmkDmyWork* w) {
    w->tiles = AllocObjTiles(func_080E83C4() << 5, 0);
}

s32 Task_MapGmk_Dmy_1(void) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }
    return 1;
}

void Task_MapGmk_Dmy_2(MapGmkDmyWork* w) {
}

void Task_MapGmk_Dmy_3(MapGmkDmyWork* w) {
    if (w->tiles != 0) {
        ReleaseObjTiles(w->tiles);
    }
}

u8 func_080F1978(MapGmkTutorialWork* w) {
    if (func_080E02E0(&w->obj.fieldPosition, 0, 8) != 0) {
        if ((gFieldState->flags & 0x800000) == 0 && gFieldState->actor.fieldPosition.z == gFieldState->actor.fieldPosition.unk_0C) {
            TaskPool* pool = &w->tasks;

            TaskCreate(pool, &gTaskDescMapSpark, &w->obj);
            m4aSongNumStart(SONG_SND_220);
            gUnk_0203C7AC->flags |= 0x80;
            gFieldState->unk_68 = &w->obj;
            gUnk_0203C7AC->unk_14 = &w->obj;
            w->update = func_080F1A10;
            gUnk_0203C7AC->unk_0F = 0;
            gUnk_0203C7AC->unk_10 = 0;
            FadeSetPaletteExcluded(w->palette->index + 16, 1);
            TaskCreate(pool, &gTaskDescRoomcreate, 0);
        }
    }
    return 1;
}

u8 func_080F1A10(MapGmkTutorialWork* w) {
    void* p = func_08093BF8();

    if (p != 0) {
        func_080DF640(gUnk_0984C868[0], p);
        w->update = func_080F1A84;
    }

    if ((gFieldState->flags & 0x40000) == 0) {
        gUnk_0203C7AC->flags &= ~0x80;
        FadeSetPaletteExcluded(w->palette->index + 16, 0);
        w->update = func_080F1978;
    }
    return 1;
}

u8 func_080F1A84(MapGmkTutorialWork* w) {
    if (gFieldState->flags & 0x200000) {
        UpdateSpriteFrameTiles(w->tiles, gMapUiSpriteUs_098A94A0, gUnk_0994C364);
        w->unk_0A8 = 1;
        w->update = func_080F1ACC;
    }
    return 1;
}

u8 func_080F1ACC(MapGmkTutorialWork* w) {
    return 1;
}

void Task_MapGmk_Tutorial_0(MapGmkTutorialWork* w) {
    w->obj.fieldPosition.x = 0x19000;
    w->obj.fieldPosition.y = 0xAA00;
    w->obj.fieldPosition.z = 0;
    w->obj.fieldPosition.unk_0C = func_080DFF30(&w->obj.fieldPosition);
    w->obj.fieldPosition.z = w->obj.fieldPosition.unk_0C;
    w->obj.fieldPosition.y -= w->obj.fieldPosition.unk_0C;
    w->obj.angle = 0xAD;
    w->obj.unk_1A = 32;
    w->palette = LoadObjPalette(&gUnk_099910C4[0x140], 32);
    w->tiles = AllocSpriteFrameTiles(0x400);
    UpdateSpriteFrameTiles(w->tiles, gMapUiSpriteUs_098A94A0, gUnk_0994BF64);
    ColliderInit(&w->collider, 6, 16, 0);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, w->obj.fieldPosition.y, w->obj.fieldPosition.z);
    w->unk_0A8 = 0;
    w->update = func_080F1978;
    TaskPoolInit(&w->tasks, 2);
}

s32 Task_MapGmk_Tutorial_1(MapGmkTutorialWork* w) {
    if (w->unk_0A8 != 0 && (w->collider.unk_2E & 2) && w->collider.unk_34 == 1) {
        gUnk_0203C7AC->flags |= 0x200;
    }

    if (w->update != 0) {
        if (w->update(w) == 0) {
            return 0;
        }
    }

    TaskPoolUpdate(&w->tasks);
    return 1;
}

void Task_MapGmk_Tutorial_2(MapGmkTutorialWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0xFE4 - k * 4;
    DrawSprite(x, y, 0, w->tiles, w->palette, 0, 0x800, v);
    TaskPoolDraw(&w->tasks);
}

void Task_MapGmk_Tutorial_3(MapGmkTutorialWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
}

u8 func_080F1C64(MapGmkSpiderWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        gUnk_0203C7AC->flags |= 2;
        gFieldState->flags |= 0x80;
        gUnk_0203C7AC->unk_0E = GetRandom() % 3 + 125;
        w->update = 0;
    } else {
        w->gfx = AnimUpdate(a);
    }
    return 1;
}

void Task_MapGmk_Spider_0(MapGmkSpiderWork* w, UnkStruct_0203C7B8* arg) {
    u8 v;

    w->obj.fieldPosition = arg->unk_04;
    w->obj.unk_1A = 24;
    w->tiles = AllocObjTiles(0x720, gEmy2103Tiles);
    w->palette = LoadObjPalette(&gUnk_08F691E4[0x6A0], 32);
    AnimInit(&w->anim, gEmy2103Anims, gEmy2103Frames);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, gEmy2103Tiles);
    w->update = func_080F1C64;
    v = 0;

    if (gFieldState->actor.fieldPosition.x >= w->obj.fieldPosition.x) {
        v = 1;
    }
    w->unk_0C4 = v;
}

u8 Task_MapGmk_Spider_1(MapGmkSpiderWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_Spider_2(MapGmkSpiderWork* w) {
    u16 flags;
    u16 v;
    s32 t;
    s32 k;
    s32 x;
    s32 y;

    t = w->unk_0C4;
    flags = 0x800;

    if (t) {
        flags = 0x801;
    }

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, flags, v);
}

void Task_MapGmk_Spider_3(MapGmkSpiderWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

u8 func_080F1E28(MapGmkGpWork* w) {
    FldPos* p = &w->obj.fieldPosition;

    if (func_080E02E0(p, 8, 8)) {
        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);

        if (!(w->unk_000->unk_00 & 2)) {
            w->unk_000->unk_00 |= 2;
            func_080E84DC(p);
        }

        gUnk_0203C7AC->flags |= 0x80;
        w->timer = 20;
        w->update = func_080F1EA0;
    }
    return 1;
}

u8 func_080F1EA0(MapGmkGpWork* w) {
    if (w->timer != 0) {
        w->timer--;
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->update = func_080F1E28;
    }
    return 1;
}

void Task_MapGmk_GP00_0(MapGmkGpWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->timer = 0;
    w->update = func_080F1E28;
}

u8 Task_MapGmk_GP00_1(MapGmkGpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP00_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP00_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F207C(MapGmkGp1Work* w) {
    FldPos* p = &w->obj.fieldPosition;

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (!func_080E02E0(p, 8, 8)) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);
        func_080E84DC(&w->obj.fieldPosition);
        gUnk_0203C7AC->flags |= 0x80;
        w->unk_000->unk_00 |= 1;
        ColliderSetDisabled(&w->collider, 1);
        AnimStart(&w->anim, 1, 0);
        w->update = func_080F2130;
    }
    return 1;
}

u8 func_080F2130(MapGmkGp1Work* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx = AnimUpdate(a);
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->unk_0C6 = 0;
        w->update = 0;
    }
    return 1;
}

void Task_MapGmk_GP01_0(MapGmkGp1Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, 1);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->unk_0C6 = 1;
    w->update = func_080F207C;
}

u8 Task_MapGmk_GP01_1(MapGmkGp1Work* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP01_2(MapGmkGp1Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (w->unk_0C6 != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
    }
}

void Task_MapGmk_GP01_3(MapGmkGp1Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F230C(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (func_080E02E0(q, 8, 8)) {
        UnkStruct_0203C7B8* e;

        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        e = w->unk_000;

        if ((e->unk_00 & 2) == 0) {
            e->unk_00 |= 2;
            func_080E84DC(q);
        }

        gUnk_0203C7AC->flags |= 0x80;
        AnimStart(&w->anim, 1, 0);
        w->update = func_080F238C;
    }
    return 1;
}

u8 func_080F238C(MapGmkGpWork* w) {
    if (AnimIsFinished(&w->anim) == 0) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        AnimStart(&w->anim, 0, 0);
        w->gfx = AnimGetGfx(&w->anim);
        w->update = func_080F230C;
    }

    return 1;
}

void Task_MapGmk_GP02_0(MapGmkGpWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, 1);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->update = func_080F230C;
}

u8 Task_MapGmk_GP02_1(MapGmkGpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP02_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP02_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F2594(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (func_080E02E0(q, 8, 8)) {
        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        gUnk_0203C7AC->flags |= 0x80;
        AnimStart(&w->anim, 1, 0);
        w->update = func_080F25FC;
    }
    return 1;
}

u8 func_080F25FC(MapGmkGpWork* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        UnkStruct_0203C7B8* e = w->unk_000;

        if ((e->unk_00 & 2) == 0) {
            e->unk_00 |= 2;
            func_080E84DC(&w->obj.fieldPosition);
        }
        AnimStart(a, 2, 0);
        w->update = func_080F2654;
    } else {
        w->gfx = AnimUpdate(a);
    }
    return 1;
}

u8 func_080F2654(MapGmkGpWork* w) {
    if (AnimIsFinished(&w->anim) == 0) {
        w->gfx = AnimUpdate(&w->anim);
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        AnimStart(&w->anim, 0, 0);
        w->gfx = AnimGetGfx(&w->anim);
        w->update = func_080F2594;
    }

    return 1;
}

void Task_MapGmk_GP03_0(MapGmkGpWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, 1);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->update = func_080F2594;
}

u8 Task_MapGmk_GP03_1(MapGmkGpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP03_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP03_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F285C(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if ((w->unk_000->unk_00 & 2) == 0 && func_080E02E0(q, 8, 8)) {
        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        func_080E84DC(q);
        w->unk_000->unk_00 |= 2;
        gUnk_0203C7AC->flags |= 0x80;
        AnimStart(a, 1, 1);
        w->timer = 20;
        w->update = func_080F28F4;
    }
    return 1;
}

u8 func_080F28F4(MapGmkGpWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->timer != 0) {
        w->timer--;
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->update = 0;
    }
    return 1;
}

void Task_MapGmk_GP04_0(MapGmkGpWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);

    if (w->unk_000->unk_00 & 2) {
        AnimStart(&w->anim, 1, 1);
    } else {
        AnimStart(&w->anim, 0, 1);
    }

    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->update = func_080F285C;
}

u8 Task_MapGmk_GP04_1(MapGmkGpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP04_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP04_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F2AF4(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (!(w->unk_000->unk_00 & 2) && func_080E02E0(q, 8, 8)) {
        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);
        func_080E84DC(q);
        w->unk_000->unk_00 |= 2;
        gUnk_0203C7AC->flags |= 0x80;
        AnimStart(&w->anim, 1, 0);
        w->update = func_080F2B78;
    }
    return 1;
}

u8 func_080F2B78(MapGmkGpWork* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx = AnimUpdate(a);
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        AnimStart(a, 2, 0);
        w->gfx = AnimGetGfx(a);
        w->update = 0;
    }
    return 1;
}

void Task_MapGmk_GP05_0(MapGmkGpWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);

    if (w->unk_000->unk_00 & 2) {
        AnimStart(&w->anim, 2, 1);
    } else {
        AnimStart(&w->anim, 0, 1);
    }

    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->update = func_080F2AF4;
}

u8 Task_MapGmk_GP05_1(MapGmkGpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP05_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP05_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F2D90(MapGmkGpWork* w) {
    FldPos* q = &w->obj.fieldPosition;
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if (func_080E02E0(q, 8, 8)) {
        m4aSongNumStart(w->unk_0C4);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);

        if ((w->unk_000->unk_00 & 2) == 0) {
            w->unk_000->unk_00 |= 2;
            func_080E84DC(q);
        }

        gUnk_0203C7AC->flags |= 0x80;

        if (w->unk_000->unk_00 & 4) {
            w->unk_000->unk_00 &= ~4;
            AnimStart(a, 0, 1);
        } else {
            w->unk_000->unk_00 |= 4;
            AnimStart(a, 1, 1);
        }

        w->timer = 20;
        w->update = func_080F2E4C;
    }
    return 1;
}

u8 func_080F2E4C(MapGmkGpWork* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (w->timer != 0) {
        w->timer--;
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->update = func_080F2D90;
    }
    return 1;
}

void Task_MapGmk_GP06_0(MapGmkGpWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);

    if (w->unk_000->unk_00 & 4) {
        AnimStart(&w->anim, 1, 1);
    } else {
        AnimStart(&w->anim, 0, 1);
    }

    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = d->unk_20;
    w->update = func_080F2D90;
}

u8 Task_MapGmk_GP06_1(MapGmkGpWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP06_2(MapGmkGpWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP06_3(MapGmkGpWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

s32 func_080F3050(MapGmkGp07Work* w) {
    AnimState* a = &w->anim;

    w->gfx = AnimUpdate(a);

    if (ColliderIsTouchingType(&w->collider, 1) != 0) {
        if (w->collider.unk_2E & 2) {
            if (!(w->unk_000->unk_00 & 2)) {
                w->unk_000->unk_00 |= 2;
                func_080E84DC(&w->obj.fieldPosition);
            }
            AnimStart(a, 1, 0);
            w->gfx = AnimGetGfx(a);
            w->update = func_080F30C4;
        }
    }
    return 1;
}

s32 func_080F30C4(MapGmkGp07Work* w) {
    w->gfx = AnimUpdate(&w->anim);

    if (ColliderIsTouchingType(&w->collider, 1) == 0) {
        AnimStart(&w->anim, 2, 0);
        w->update = func_080F3108;
    }
    return 1;
}

s32 func_080F3108(MapGmkGp07Work* w) {
    AnimState* a = &w->anim;

    if (AnimIsFinished(a)) {
        AnimStart(a, 0, 1);
        w->gfx = AnimGetGfx(a);
        w->update = func_080F3050;
    } else {
        w->gfx = AnimUpdate(a);
    }
    return 1;
}

void Task_MapGmk_GP07_0(MapGmkGp07Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->update = func_080F3050;
}

u8 Task_MapGmk_GP07_1(MapGmkGp07Work* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP07_2(MapGmkGp07Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk_GP07_3(MapGmkGp07Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

s32 func_080F32F4(MapGmkGp08Work* w) {
    FldPos* q = &w->obj.fieldPosition;
    AnimState* a;

    if (func_080E02E0(q, 8, 8)) {
        m4aSongNumStart(w->unk_0C8);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, q);

        if (!(w->unk_000->unk_00 & 2)) {
            w->unk_000->unk_00 |= 2;
            func_080E84DC(q);
        }

        gUnk_0203C7AC->flags |= 0x80;
        a = &w->anim;
        AnimStart(a, 1, 0);
        w->gfx2 = AnimGetGfx(a);
        w->unk_0CA = 1;
        w->update = func_080F3384;
    }
    return 1;
}

s32 func_080F3384(MapGmkGp08Work* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx2 = AnimUpdate(a);
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->unk_0CA = 0;
        w->update = func_080F32F4;
    }
    return 1;
}

void Task_MapGmk_GP08_0(MapGmkGp08Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C8 = d->unk_20;
    w->unk_0CA = 0;
    w->update = func_080F32F4;
}

u8 Task_MapGmk_GP08_1(MapGmkGp08Work* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP08_2(MapGmkGp08Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);

    if (w->unk_0CA != 0) {
        DrawSprite(x, y, w->gfx2, w->tiles, w->palette, 0, 0x800, v - 1);
    }
}

void Task_MapGmk_GP08_3(MapGmkGp08Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

s32 func_080F35C0(MapGmkGp09Work* w) {
    AnimState* a = &w->anim;

    w->gfx2 = AnimUpdate(a);

    if (ColliderIsTouchingType(&w->collider, 1) != 0) {
        if (w->collider.unk_2E & 2) {
            if (!(w->unk_000->unk_00 & 2)) {
                w->unk_000->unk_00 |= 2;
                func_080E84DC(&w->obj.fieldPosition);
            }
            AnimStart(a, 1, 0);
            w->gfx2 = AnimGetGfx(a);
            w->unk_0C8 = 1;
            w->update = func_080F3638;
        }
    }
    return 1;
}

s32 func_080F3638(MapGmkGp09Work* w) {
    if (AnimIsFinished(&w->anim)) {
        w->unk_0C8 = 0;
        w->update = func_080F3674;
    } else {
        w->gfx2 = AnimUpdate(&w->anim);
    }

    return 1;
}

s32 func_080F3674(MapGmkGp09Work* w) {
    if (ColliderIsTouchingType(&w->collider, 1) == 0) {
        w->update = func_080F35C0;
    }
    return 1;
}

void Task_MapGmk_GP09_0(MapGmkGp09Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C8 = 0;
    w->update = func_080F35C0;
}

u8 Task_MapGmk_GP09_1(MapGmkGp09Work* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj)) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_GP09_2(MapGmkGp09Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);

    if (w->unk_0C8 != 0) {
        DrawSprite(x, y, w->gfx2, w->tiles, w->palette, 0, 0x800, v - 1);
    }
}

void Task_MapGmk_GP09_3(MapGmkGp09Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void Task_MapGmk00_0(MapGmk00Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = LoadObjTiles(d->tiles, d->tilesSize);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, 1);
    w->gfx = AnimGetGfx(a);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);

    if (func_080E8374(e) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    }
    w->unk_0C4 = d->unk_1C;
    w->unk_0C9 = 0;
    w->unk_0C8 = 1;
    w->unk_0C6 = 0;
}

u8 Task_MapGmk00_1(MapGmk00Work* w) {
    FldPos* q = &w->obj.fieldPosition;
    u16 t;

    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }

    if (!(w->unk_000->unk_00 & 2)) {
        t = w->collider.unk_2E & 2;

        if (t != 0) {
            if (w->unk_0C9 != 1) {
                w->unk_0C9 = 1;
                w->unk_000->unk_00 |= 2;
                func_080E84DC(q);
            }
        } else {
            w->unk_0C9 = 0;
        }
    }
    return 1;
}

void Task_MapGmk00_2(MapGmk00Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (w->unk_0C8 != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
    }
}

void Task_MapGmk00_3(MapGmk00Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

u8 func_080F3A74(MapGmk01Work* w) {
    if (func_080E02E0(&w->obj.fieldPosition, 8, 8)) {
        AnimState* a;

        gUnk_0203C7AC->flags |= 0x80;
        m4aSongNumStart(SONG_SYS_TRESURE);
        a = &w->anim;
        AnimStart(a, 1, 1);
        w->gfx = AnimGetGfx(a);
        SetObjTileSource(w->tiles, gUnk_09858320);
        w->update = func_080F3ADC;
    }
    return 1;
}

u8 func_080F3ADC(MapGmk01Work* w) {
    FldPos* q = &w->obj.fieldPosition;

    if (w->unk_000->unk_00 & 8) {
        gUnk_0203C7AC->flags |= 4;
        w->unk_000->unk_00 |= 2;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkEnm, q);
        w->update = 0;
    } else {
        gUnk_0203C7AC->flags &= ~0x20;
        func_080E9078(gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y, gFieldState->actor.fieldPosition.z);
        func_080DEE18(gUnk_0203C590.unk_06)->unk_00 |= 0x10;
        w->unk_000->unk_00 |= 2;
        w->timer = 20;
        w->update = func_080F3B84;
    }

    return 1;
}

u8 func_080F3B84(MapGmk01Work* w) {
    if (w->timer != 0) {
        if (func_080A42C8() == 0) {
            w->timer--;
        }
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->update = 0;
    }
    return 1;
}

void Task_MapGmk01_0(MapGmk01Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(0x320, gUnk_09858320);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);

    if (w->unk_000->unk_00 & 2) {
        AnimStart(a, 1, 1);
        w->gfx = AnimGetGfx(a);
        w->update = 0;
    } else {
        gUnk_0203C7AC->flags |= 0x20;
        AnimStart(a, 0, 1);
        w->gfx = AnimGetGfx(a);
        w->update = func_080F3A74;
    }
    SetObjTileSource(w->tiles, gUnk_09858320);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
}

u8 Task_MapGmk01_1(MapGmk01Work* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk01_2(MapGmk01Work* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = w->obj.fieldPosition.y >> 8;
    y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk01_3(MapGmk01Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void func_080F3D58(FldPos* p) {
    u16 r;

    if (gGameState.flags & 8) {
        r = GetRandom() % 10000;
        if (r < 6000) {
            CreateMapPrizeTasks(0, 5, p->x, p->y, p->z);
        } else if (r < 10000) {
            CreateMapPrizeTasks(1, 3, p->x, p->y, p->z);
        }
    } else {
        r = GetRandom() % 10000;
        if (r < 3000) {
            CreateMapPrizeTasks(0, 5, p->x, p->y, p->z);
        } else if (r < 5000) {
            CreateMapPrizeTasks(1, 3, p->x, p->y, p->z);
        } else if (r < 8000) {
            CreateMapPrizeTasks(2, 5, p->x, p->y, p->z);
        } else {
            CreateMapPrizeTasks(3, 5, p->x, p->y, p->z);
        }
    }
}

u8 func_080F3E24(MapGmkBarrelWork* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 r;

    if (func_080E02E0(p, 8, 8) != 0) {
        r = GetRandom() % 10000;

        if (r <= 1499) {
            m4aSongNumStart(SONG_SYS_OBJ_BREAK);
            TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);
            gUnk_0203C7AC->flags |= 0x80;
            gUnk_0203C7AC->flags |= 4;
            w->unk_000->unk_00 |= 1;
            TaskCreate(&gFieldState->tasks, &gTaskDescMapGmkSpider, w->unk_000);
            return 0;
        }

        m4aSongNumStart(SONG_SYS_OBJ_BREAK);
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSpark, p);

        if (r <= 5999) {
            if ((u8)func_080E8FB8(0, p->x, p->y, p->z) != 1) {
                func_080F3D58(p);
            }
        } else if (r <= 9999) {
            func_080F3D58(p);
        }

        gUnk_0203C7AC->flags |= 0x80;
        w->unk_000->unk_00 |= 1;
        ColliderSetDisabled(&w->collider, 1);
        AnimStart(&w->anim, 1, 0);
        w->update = func_080F3F6C;
        return 1;
    }

    if ((u8)func_080E8374(&w->obj) != 0) {
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetDisabled(&w->collider, 0);
    }
    return 1;
}

u8 func_080F3F6C(MapGmkBarrelWork* w) {
    AnimState* a = &w->anim;

    if (!AnimIsFinished(a)) {
        w->gfx = AnimUpdate(a);
    } else {
        gUnk_0203C7AC->flags &= ~0x80;
        w->unk_0C4 = 0;
        w->update = 0;
    }
    return 1;
}

void Task_MapGmk_Barrel_0(MapGmkBarrelWork* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    w->obj.fieldPosition.x += d->unk_16 << 8;
    e->fieldPosition.y += d->unk_18 << 8;
    e->fieldPosition.z += d->unk_1A << 8;
    e->unk_1A = d->unk_1E;
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    w->palette = LoadObjPalette(d->palette, 32);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, 1);
    w->gfx = AnimGetGfx(a);
    SetObjTileSource(w->tiles, d->tiles);
    ColliderInit(&w->collider, 6, d->unk_1C, d->unk_1E);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    w->unk_0C4 = 1;
    w->update = func_080F3E24;
}

u8 Task_MapGmk_Barrel_1(MapGmkBarrelWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->update != 0) {
        return w->update(w);
    }
    return 1;
}

void Task_MapGmk_Barrel_2(MapGmkBarrelWork* w) {
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    if (w->unk_0C4 != 0) {
        x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
        k = w->obj.fieldPosition.y >> 8;
        y = k + (w->obj.fieldPosition.z >> 8) - (gFieldState->y >> 8);
        v = -0x1004 - k * 4;
        DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
    }
}

void Task_MapGmk_Barrel_3(MapGmkBarrelWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void func_080F4140(MapGmk04Work* w) {
    if ((gUnk_0203C7AC->flags & 0x4000) == 0 && (u8)func_080E03C0(&w->obj) != 0 && (GetKeysPressed() & A_BUTTON)) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        gFieldState->flags |= 0x1000;
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSave, 0);
        w->update = 0;
    }
}

void func_080F41A4(MapGmk04Work* w) {
    u32 state = gUnk_0203C7AC->flags;

    if (state & 0x4000) {
        gFieldState->flags |= 0x1000;
        CreateCardMessageTask(&w->tasks, 0, 0x69);
        w->update = func_080F4258;
    } else if (gFieldState->unk_68 == &w->obj) {
        gFieldState->flags |= 0x1000;
        gUnk_0203C7AC->flags = state | 0x4000;
        CreateCardMessageTask(&w->tasks, 0, 0x67);
        w->update = func_080F4224;
    }
}

void func_080F4224(MapGmk04Work* w) {
    if (func_080A42C8() == 0) {
        TaskCreate(&gFieldState->tasks, &gTaskDescMapSave, 0);
        w->update = 0;
    }
}

void func_080F4258(MapGmk04Work* w) {
    if (func_080A42C8() == 0) {
        gUnk_0203C7AC->flags &= ~0x4000;
        gFieldState->flags &= ~0x1000;
        gGameState.progression.unk_82 |= 0x10;
        w->update = func_080F4140;
    }
}

void Task_MapGmk04_0(MapGmk04Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    w->unk_000 = arg;
    e->fieldPosition = arg->unk_04;
    e->unk_1A = d->unk_1E;
    e->unk_30 = 3;

    if (gGameState.progression.unk_82 & 0x10) {
        w->update = func_080F4140;
    } else {
        w->update = func_080F41A4;
    }

    w->palette = LoadObjPalette(d->palette, 32);
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 4, 24, 24);
    ColliderSetPosition(&w->collider, e->fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    TaskPoolInit(&w->tasks, 1);
    FldObjRegister(e);
}

s32 Task_MapGmk04_1(MapGmk04Work* w) {
    TaskPoolUpdate(&w->tasks);

    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    w->gfx = AnimUpdate(&w->anim);

    if (w->update != 0) {
        w->update(w);

        if (w->update != 0) {
            return 1;
        }
    }
    return 0;
}

void Task_MapGmk04_2(MapGmk04Work* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    TaskPoolDraw(&w->tasks);
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = p->y >> 8;
    y = k + (p->z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk04_3(MapGmk04Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    FldObjUnregister(&w->obj);
}

void func_080F445C(MapGmk05Work* w) {
    if (w->unk_0C8 != 0 && (GetKeysPressed() & A_BUTTON)) {
        gFieldState->flags |= 0x1000;
        func_0801CB0C();
        FadeStartOut(0, 16);
        m4aSongNumStart(SONG_SYS_MOUGURI);
        w->update = func_080F44AC;
    }
}

void func_080F44AC(MapGmk05Work* w) {
    UnkStruct_080DEE18* e;

    if ((u8)FadeIsActive() != 0) {
        return;
    }
    e = func_080DEE18(gUnk_0203C590.unk_06);

    if (e->unk_00 & 0x20) {
        ModeRequest(&gModeMsTop, 0);
    } else {
        e->unk_00 |= 0x20;
        ModeRequest(&gModeMsTop, 1);
    }
    w->update = 0;
}

void Task_MapGmk05_0(MapGmk05Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;
    AnimState* a;

    e->fieldPosition = arg->unk_04;
    e->unk_1A = d->unk_1E;
    e->unk_30 = 2;
    w->update = func_080F445C;
    w->palette = LoadObjPalette(d->palette, 32);
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    a = &w->anim;
    AnimInit(a, d->anims, d->gfxTable);
    AnimStart(a, 0, 1);
    w->gfx = AnimGetGfx(a);
    ColliderInit(&w->collider, 4, 16, 24);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    FldObjRegister(e);
    TaskPoolInit(&w->tasks, 1);
    TaskCreate(&w->tasks, &gTaskDescFldShadow, e);
    w->unk_0C8 = 0;
    TaskPoolInit(&w->tasks2, 1);
    TaskCreate(&w->tasks2, &gTaskDescMapTalk, e);
}

s32 Task_MapGmk05_1(MapGmk05Work* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    TaskPoolUpdate(&w->tasks);
    TaskPoolUpdate(&w->tasks2);
    w->gfx = AnimUpdate(&w->anim);
    w->unk_0C8 = func_080E03C0(&w->obj);

    if (w->update != 0) {
        w->update(w);

        if (w->update != 0) {
            return 1;
        }
    }
    return 0;
}

void Task_MapGmk05_2(MapGmk05Work* w) {
    FldObj* p = &w->obj;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    k = p->fieldPosition.y >> 8;
    v = -0x1004 - k * 4;
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = k + (p->fieldPosition.z >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
    p->unk_3C = p->fieldPosition.unk_0C;
    p->unk_3A = v + 1;
    TaskPoolDraw(&w->tasks);

    if (w->unk_0C8 != 0) {
        TaskPoolDraw(&w->tasks2);
    }
}

void Task_MapGmk05_3(MapGmk05Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    FldObjUnregister(&w->obj);
    TaskPoolDestroy(&w->tasks);
    TaskPoolDestroy(&w->tasks2);
}

void func_080F46FC(MapGmk06Work* w) {
    if (gFieldState->unk_68 == &w->obj && (gGameState.progression.unk_82 & 0x100) == 0) {
        gFieldState->flags |= 0x1000;
        gUnk_0203C7AC->flags |= 0x4000;
        CreateCardMessageTask(&w->tasks, 0, 0x84);
        gFieldState->unk_6C = 30;
        w->update = func_080F47DC;
    } else if ((u8)func_080E03C0(&w->obj) != 0 && (GetKeysPressed() & A_BUTTON)) {
        m4aSongNumStart(SONG_SYS_KETTEI);
        gFieldState->flags |= 0x1000;
        func_0801CB0C();
        FadeStartOut(0, 16);
        w->update = func_080F47B4;
    }
}

void func_080F47B4(MapGmk06Work* w) {
    if (FadeIsActive() == 0) {
        ModeRequest(&gModeWorldwarp, 0);
        w->update = 0;
    }
}

void func_080F47DC(MapGmk06Work* w) {
    if (func_080A42C8() == 0) {
        gFieldState->flags &= ~0x1000;
        gUnk_0203C7AC->flags &= ~0x4000;
        gGameState.progression.unk_82 |= 0x100;
        w->update = func_080F46FC;
    } else {
        gFieldState->unk_6C = 30;
    }
}

void Task_MapGmk06_0(MapGmk06Work* w, UnkStruct_0203C7B8* arg) {
    FldObj* e = &w->obj;
    const UnkStruct_080E7D80* d = arg->unk_14;

    e->fieldPosition = arg->unk_04;
    e->unk_1A = d->unk_1E;
    e->unk_30 = 3;
    w->update = func_080F46FC;
    w->palette = LoadObjPalette(d->palette, 32);
    w->tiles = AllocObjTiles(d->tilesSize, d->tiles);
    AnimInit(&w->anim, d->anims, d->gfxTable);
    AnimStart(&w->anim, 0, 1);
    w->gfx = AnimGetGfx(&w->anim);
    ColliderInit(&w->collider, 4, 24, 24);
    ColliderSetPosition(&w->collider, w->obj.fieldPosition.x, e->fieldPosition.y, e->fieldPosition.z);
    TaskPoolInit(&w->tasks, 1);
    FldObjRegister(e);
}

s32 Task_MapGmk06_1(MapGmk06Work* w) {
    TaskPoolUpdate(&w->tasks);

    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    w->gfx = AnimUpdate(&w->anim);

    if (w->update != 0) {
        w->update(w);

        if (w->update != 0) {
            return 1;
        }
    }
    return 0;
}

void Task_MapGmk06_2(MapGmk06Work* w) {
    FldPos* p = &w->obj.fieldPosition;
    u16 v;
    s32 k;
    s32 x;
    s32 y;

    TaskPoolDraw(&w->tasks);
    x = (w->obj.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    k = p->y >> 8;
    y = k + (p->z >> 8) - (gFieldState->y >> 8);
    v = -0x1004 - k * 4;
    DrawSprite(x, y, w->gfx, w->tiles, w->palette, 0, 0x800, v);
}

void Task_MapGmk06_3(MapGmk06Work* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
    TaskPoolDestroy(&w->tasks);
    FldObjUnregister(&w->obj);
}

void func_080F49D0(MapPrizeWork* w) {
    w->vz += 0x38;
    w->z += w->vz;
    w->x += gSineTable[w->angle] * w->unk_88 >> 8;
    w->y += -gSineTable[w->angle + 64] * w->unk_88 >> 8;

    if (func_080DFBDC((FldPos*)w) != 0) {
        w->angle = w->angle + (100 + GetRandom() % 57);
    } else {
        w->unk_0C = func_080DFF1C((FldPos*)w);
    }

    if (w->z > w->unk_0C) {
        w->z = w->unk_0C;
        w->vz = -(GetRandom() % 0x181 + 0x180);
    }

    if (w->collider.unk_2C != 0) {
        u16 t;

        switch (w->unk_80) {
        case 2:
        case 3:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.progression.mooglePoints += w->unk_94;

            if (gGameState.progression.mooglePoints > 99999) {
                gGameState.progression.mooglePoints = 99999;
            }
            break;
        case 0:
        case 1:
        default:
            m4aSongNumStart(SONG_SYS_POWER_GET);
            gGameState.hp += w->unk_94;
            t = gGameState.progression.maxHp;

            if ((s16)gGameState.hp > (s16)t) {
                gGameState.hp = t;
            }
            break;
        }

        w->update = func_080F4BA0;
        w->unk_82 = 0;
        w->angle = GetAngle(gFieldState->actor.fieldPosition.x, gFieldState->actor.fieldPosition.y, w->x, w->y);
        w->unk_97 = 1;
        w->unk_96 = 1;
        w->unk_8D = GetRandom() % 6 + 5;
        ColliderSetDisabled(&w->collider, 1);
    } else {
        ColliderSetPosition(&w->collider, w->x, w->y, w->z);

        if (w->unk_82 == 20) {
            ColliderSetDisabled(&w->collider, 0);
        }

        if (w->unk_82 > 420) {
                w->unk_96 = w->unk_96 == 0 ? 1 : 0;
        }

        if (w->unk_82++ > 480) {
            w->update = 0;
        }
    }
}

void func_080F4BA0(MapPrizeWork* w) {
    s32 x;
    s32 y;
    s32 z;
    s32 s;
    FieldState* g = gFieldState;

    s = gSineTable[w->angle] * 32;
    x = g->actor.fieldPosition.x + (s * w->scale >> 8);
    s = -gSineTable[w->angle + 64] * 22;
    y = g->actor.fieldPosition.y + (s * w->scale >> 8);
    z = g->actor.fieldPosition.z - (w->unk_82 / 2 << 8);
    w->angle += w->unk_8D;
    w->x += (x - w->x) >> 2;
    w->y += (y - w->y) >> 2;
    w->z += (z - w->z) >> 2;
    w->unk_0C = func_080DFE7C(w->x, w->y, w->z);
    w->scale -= 2;

    if (w->unk_82 > 60) {
        w->update = 0;
    } else {
        w->unk_82++;
    }
}

void Task_MapPrize_0(MapPrizeWork* w, UnkStruct_080E8F50* arg) {
    w->x = arg->unk_04;
    w->y = arg->unk_08;
    w->z = arg->unk_0C;
    w->unk_0C = 0;
    func_080DFF4C((FldPos*)w);
    w->vz = -(GetRandom() % 0x301 + 0x200);
    w->unk_88 = GetRandom() % 155 + 153;
    w->angle = GetRandom();
    w->tiles = LoadObjTiles(gUnk_098A5CF4, 0x160);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    w->unk_80 = arg->unk_14;

    switch (w->unk_80) {
    case 3:
        w->gfx = gUnk_098A5CAE;
        w->unk_94 = 10;
        break;
    case 2:
        w->gfx = gUnk_098A5CA4;
        w->unk_94 = 4;
        break;
    case 1:
        w->gfx = gUnk_098A5C9A;
        w->unk_94 = gGameState.progression.maxHp / 20;
        break;
    case 0:
    default:
        w->gfx = gUnk_098A5C90;
        w->unk_94 = gGameState.progression.maxHp * 3 / 100;
        break;
    }

    w->gfx2 = gUnk_098A5CB8;
    w->unk_97 = 0;
    w->unk_96 = 1;
    w->unk_82 = 0;
    w->update = func_080F49D0;
    w->scale = 0x100;
    ColliderInit(&w->collider, 5, 16, 50);
    ColliderSetPosition(&w->collider, w->x, w->y, w->z);
    ColliderSetDisabled(&w->collider, 1);
}

s32 Task_MapPrize_1(MapPrizeWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->update == 0) {
        return 0;
    }
    w->update(w);

    if (w->update == 0) {
        return 0;
    }
    return 1;
}

void Task_MapPrize_2(MapPrizeWork* w) {
    s16 x;
    s16 y;
    ObjAffine* aff;

    if (w->unk_96 != 0) {
        x = (w->x >> 8) - (gFieldState->x >> 8);
        y = (w->y >> 8) + (w->z >> 8) - (gFieldState->y >> 8);

        if (w->scale != 0x100) {
            aff = AllocObjAffine(0, w->scale, w->scale, 0);
        } else {
            aff = 0;
        }

        DrawSprite(x, y, w->gfx, w->tiles, w->palette, aff, 0x800, -0x1004 - (w->y >> 8) * 4);

        if (w->unk_97 == 0) {
            DrawSprite(x, (w->y >> 8) + (w->unk_0C >> 8) - (gFieldState->y >> 8), w->gfx2, w->tiles, w->palette, aff, 0x800, 0xFFFF);
        }
    }
}

void Task_MapPrize_3(MapPrizeWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
    ColliderUnregister(&w->collider);
}

void func_080F4EE4(MapPrzCardWork* work) {
    work->scaleX = -gSineTable[((work->unk_0D0 + 0x80) & 0xFF) + 0x40] * work->unk_0CC >> 8;
    work->scaleY = -gSineTable[((work->unk_0CF + 0x80) & 0xFF) + 0x40] * work->unk_0CC >> 8;

    if ((u16)(work->scaleX + 2) <= 4) {
        work->scaleX = 2;
    }
    if ((u16)(work->scaleY + 2) <= 4) {
        work->scaleY = 2;
    }
}

void func_080F4F60(MapPrzCardWork* w) {
    s32 dx;
    s32 dy;

    dx = 0x7800;
    dy = 0x5000;
    dx -= w->unk_000;
    dy -= w->unk_004;
    w->unk_0C8 = NormalizeVector2D8(&dx, &dy);
    w->unk_0C0 = -dx;
    w->unk_0C4 = -dy;
    w->unk_0B0 = 0x300;
    w->unk_0AC = 2;
}

void func_080F4FB0(MapPrzCardWork* w) {
    FldPos v = *(FldPos*)w;
    s32 nx;
    s32 ny;

    w->unk_0AC += 0x38;
    w->unk_008 += w->unk_0AC;
    w->unk_000 += gSineTable[w->unk_0B8] * w->unk_0B0 >> 8;
    w->unk_004 += -gSineTable[w->unk_0B8 + 64] * w->unk_0B0 >> 8;

    if (func_080DFBDC((FldPos*)w) != 0) {
        w->unk_0B8 = w->unk_0B8 + (112 + GetRandom() % 33);
        w->unk_000 = v.x;
        w->unk_004 = v.y;
    } else {
        w->unk_00C = func_080DFF1C((FldPos*)w);
    }

    if (w->unk_008 - 0x800 > w->unk_00C) {
        w->unk_008 = w->unk_00C - 0x800;
        w->unk_0AC = -(w->unk_0AC * 217 >> 8);

        if (w->unk_0AC > -0x200) {
            w->unk_0AC = -0x200;
        }
    }

    if (w->collider.unk_2C != 0) {
        w->unk_0D2 = 1;
        m4aSongNumStart(SONG_SYS_ITEMGET);
        func_08084458(w->cardId);

        if (w->unk_0D1 == 0) {
            UnkStruct_080DEE18* e = func_080DEE18(gUnk_0203C590.unk_06);

            if (e->unk_0C != 0) {
                e->unk_0C--;
            }
        }

        nx = (w->unk_000 >> 8) - (gFieldState->x >> 8);
        ny = (w->unk_004 >> 8) + (w->unk_008 >> 8) - (gFieldState->y >> 8);
        w->unk_000 = (s16)nx << 8;
        w->unk_004 = (s16)ny << 8;
        ColliderSetDisabled(&w->collider, 1);
        w->unk_0BE = 50;
        func_080F4F60(w);
        w->unk_088 = 0;
        w->update = func_080F51A0;
    } else {
        w->x = (w->unk_000 >> 8) - (gFieldState->x >> 8);
        w->y = (w->unk_004 >> 8) + (w->unk_008 >> 8) - (gFieldState->y >> 8);
        w->unk_0BE = -0x1004 - (w->unk_004 >> 8) * 4;
        func_080F4EE4(w);
        w->unk_0D0 += 2;
        ColliderSetPosition(&w->collider, w->unk_000, w->unk_004, w->unk_008);

        if (w->timer == 20) {
            ColliderSetDisabled(&w->collider, 0);
        }

        if (w->timer <= 59) {
            w->timer++;
        }
    }
}

void func_080F51A0(MapPrzCardWork* w) {
    s32 dx;
    s32 dy;
    s32 x;
    s32 y;

    if (w->unk_0B0 < 0) {
        dx = 0x7800 - w->unk_000;
        dy = 0x5000 - w->unk_004;
        NormalizeVector2D8(&dx, &dy);
        w->unk_0C0 = -dx;
        w->unk_0C4 = -dy;

        if (w->unk_0C8 <= 0x7FF) {
            w->unk_0CE = 0;
            w->timer = 0;
            w->update = func_080F52D4;
            TaskCreate(&w->tasks, &gTaskDescMapMsg, LANGSEL(gCardDefs[w->cardId].name));
        }
    }

    w->unk_000 += w->unk_0C0 * w->unk_0B0 >> 8;
    w->unk_004 += w->unk_0C4 * w->unk_0B0 >> 8;
    w->unk_0CE += 32;
    w->unk_0CF += (64 - w->unk_0CF) >> 4;
    w->unk_0D0 = 0;
    w->unk_0C8 = VectorLength2D(0x7800 - w->unk_000, 0x5000 - w->unk_004);
    w->unk_0B0 -= w->unk_0AC;
    w->unk_0AC += 2;
    w->unk_0CC += 3;

    if (w->unk_0CC > 0x100) {
        w->unk_0CC = 0x100;
    }

    x = w->unk_000 >> 8;
    w->x = x;
    y = w->unk_004 >> 8;
    w->y = y;
    func_080F4EE4(w);
}

void func_080F52D4(MapPrzCardWork* w) {
    s32 x;
    s32 y;

    w->unk_000 = 0x7800;
    w->unk_004 = 0x5800;
    w->unk_0CE = 0;
    w->unk_0CF = 0;
    w->unk_0CC += 2;

    if (w->unk_0CC > 0x100) {
        w->unk_0CC = 0x100;
    }

    x = w->unk_000 >> 8;
    w->x = x;
    y = w->unk_004 >> 8;
    w->y = y;
    func_080F4EE4(w);
    w->timer++;

    if (w->timer == 30) {
        w->timer = 0;
        w->update = func_080F534C;
    }

    TaskPoolUpdate(&w->tasks);
}

void func_080F534C(MapPrzCardWork* w) {
    s32 x;
    s32 y;

    w->unk_0CE += 32;
    x = (gFieldState->actor.fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (gFieldState->actor.fieldPosition.y >> 8) + (gFieldState->actor.fieldPosition.z >> 8) - (gFieldState->y >> 8);
    w->x += ((s16)x - w->x) >> 3;
    w->y += ((s16)y - w->y) >> 3;
    w->scaleX -= 10;
    w->scaleY -= 10;

    if (w->scaleX <= 10) {
        w->update = 0;
    }
}

void Task_MapPrzCard_0(MapPrzCardWork* w, UnkStruct_080E8F50* p) {
    CardDef* d;
    CardBack* q;

    gUnk_0203C7AC->flags |= 0x10;
    w->cardId = p->unk_14;
    d = &gCardDefs[w->cardId];
    w->tiles = LoadObjTiles(d->tiles, 0x300);
    w->palette = LoadObjPalette(d->palette, 32);
    w->unk_090 = *(UnkStruct_08F70ACC*)&d->unk_1C;
    q = &gUnk_08F709B0[w->unk_090.unk_0E];
    w->palette2 = LoadObjPalette(gCard00Palette, 32);
    w->tiles2 = LoadObjTiles(q->tiles, 0x280);
    w->tiles3 = LoadObjTiles(gUnk_0905EAE8, 0x1E0);
    w->palette3 = LoadObjPalette(gUnk_08F69BE4, 32);
    w->tiles4 = LoadObjTiles(gUnk_08B22BBC, 0x100);
    w->unk_000 = p->unk_04;
    w->unk_004 = p->unk_08;
    w->unk_008 = p->unk_0C;
    w->unk_00C = 0;
    func_080DFF4C((FldPos*)w);
    w->unk_0AC = -(GetRandom() % 129 + 0x300);
    w->unk_0B0 = GetRandom() % 129 + 128;
    w->unk_0B8 = GetRandom();
    w->scaleX = 128;
    w->scaleY = 128;
    w->unk_0CC = 128;
    w->unk_0CE = 24;
    w->unk_0CF = 0;
    w->unk_0D0 = 0;
    w->unk_0D1 = p->unk_00;
    ColliderInit(&w->collider, 5, 30, 10);
    ColliderSetPosition(&w->collider, w->unk_000, w->unk_004, w->unk_008);

    if (w->unk_0D1 != 0) {
        ColliderSetDisabled(&w->collider, 0);
    } else {
        ColliderSetDisabled(&w->collider, 1);
    }

    w->unk_088 = 0x800;
    w->timer = 0;
    w->update = func_080F4FB0;
    w->unk_0D2 = 0;
    TaskPoolInit(&w->tasks, 1);
}

s32 Task_MapPrzCard_1(MapPrzCardWork* w) {
    if ((u8)func_080E0390() != 0) {
        return 0;
    }

    if (w->update == 0) {
        return 0;
    }
    w->update(w);

    if (w->update == 0) {
        return 0;
    }
    return 1;
}

void Task_MapPrzCard_2(MapPrzCardWork* w) {
    CardDef* d;
    CardBack* q;
    void* t;
    ObjAffine* affine;
    s16 x;
    s16 y;
    s16 s;

    if (*(s32*)&w->scaleX == 0x01000100 && w->unk_0CE == 0) {
        affine = 0;
    } else {
        affine = AllocObjAffine(w->unk_0CE, w->scaleX, w->scaleY, 1);
    }

    d = &gCardDefs[w->cardId];
    DrawSprite(w->x, *(u16*)&w->y - 8, d->gfx, w->tiles, w->palette,
        affine, w->unk_088, w->unk_0BE + 1);
    q = &gUnk_08F709B0[w->unk_090.unk_0E];
    DrawSprite(w->x, *(u16*)&w->y - 8, q->gfx, w->tiles2,
        w->palette2, affine, w->unk_088, w->unk_0BE);

    if (w->unk_090.unk_0E != 3) {
        t = gUnk_09EE981C[w->unk_090.unk_04];
        DrawSprite(w->x, *(u16*)&w->y - 8, t, w->tiles3,
            w->palette2, affine, w->unk_088, w->unk_0BE - 1);
    }

    if (w->unk_0D2 == 0) {
        x = (w->unk_000 >> 8) - (gFieldState->x >> 8);
        y = (w->unk_004 >> 8) + (w->unk_00C >> 8) - (gFieldState->y >> 8);
        s = 204 - ((w->unk_00C - w->unk_008) >> 7);

        if (s <= 2) {
            s = 2;
        }

        DrawSprite(x, y, gUnk_09EE1380[0], w->tiles4, w->palette3,
            AllocObjAffine(0, s, s, 0), 0x800, w->unk_0BE + 2);
    }

    TaskPoolDraw(&w->tasks);
}
void Task_MapPrzCard_3(MapPrzCardWork* w) {
    FadeSetPaletteExcluded(w->palette2->index + 0x10, 0);
    FadeSetPaletteExcluded(w->palette->index + 0x10, 0);
    ColliderUnregister(&w->collider);
    ReleaseObjTiles(w->tiles);
    ReleaseObjTiles(w->tiles2);
    ReleaseObjTiles(w->tiles3);
    ReleaseObjTiles(w->tiles4);
    ReleaseObjPalette(w->palette);
    ReleaseObjPalette(w->palette2);
    ReleaseObjPalette(w->palette3);
    TaskPoolDestroy(&w->tasks);
    gUnk_0203C7AC->flags &= ~0x10;
}

void func_080F5800(MapPrzStockWork* w) {
    CreateCardMessageTask(&w->tasks, 0, w->unk_00[1]);
    w->update = func_080F5820;
}

void func_080F5820(MapPrzStockWork* w) {
    if (func_080A42C8() == 0) {
        w->update = 0;
    }
}

void Task_MapPrzStock_0(MapPrzStockWork* w, u16* a) {
    w->unk_00 = a;
    gFieldState->flags |= 0x1000;
    gFieldState->flags |= 0x80;
    w->update = func_080F5800;
    TaskPoolInit(&w->tasks, 1);
}

s32 Task_MapPrzStock_1(MapPrzStockWork* w) {
    TaskPoolUpdate(&w->tasks);

    if (w->update != 0) {
        w->update(w);

        if (w->update != 0) {
            return 1;
        }
    }
    return 0;
}

void Task_MapPrzStock_2(MapPrzStockWork* w) {
    TaskPoolDraw(&w->tasks);
}

void Task_MapPrzStock_3(MapPrzStockWork* w) {
    TaskPoolDestroy(&w->tasks);
    gFieldState->flags &= ~0x1000;
    gFieldState->flags &= ~0x80;
}

void func_080F58C4(MapMsgWork* w, void* text) {
    LoadBgTiles(0, &gUnk_099597E4[0x140], 0x140);
    LoadBgMap(0, &gUnk_09985F44[0x800], 0x800);
    SetBgScroll(0, 0, (u16)-46);
    LoadPalette(gCard00Palette, &gUnk_050001C0[0x20], 32);
    InitTextSlots(w->textSlots, 48);
    w->textSlotCount = LoadTextSlots(text, w->textSlots);
    w->palette = _08066468(1);
    FadeSetPaletteExcluded(w->palette->index + 16, 1);
    w->unk_186 = (240 - GetTextSlotsWidth(w->textSlots, w->textSlotCount)) / 2;
    w->timer = 0;
}

s32 Task_MapMsg_1(MapMsgWork* w) {
    return 1;
}

void func_080F596C(MapMsgWork* w) {
    DrawTextSlots(w->unk_186, 120, w->textSlots, w->palette, 50, w->textSlotCount);
}

void func_080F59A0(MapMsgWork* w) {
    if ((gFieldState->flags & 0x40000) == 0) {
        DisableBg(0);
    }

    FadeSetPaletteExcluded(w->palette->index + 0x10, 0);
    ReleaseObjPalette(w->palette);
    FreeTextSlots(w->textSlots, 0x30);
}

s32 Task_MapMsg2_1(MapMsgWork* w) {
    w->timer++;

    if (w->timer == 120) {
        return 0;
    }
    return 1;
}

void Task_MapSpark_0(MapSparkWork* w, FldObj* obj) {
    AnimState* a;

    w->obj = obj;
    w->tiles = AllocObjTiles(0x200, gUnk_098A4B68);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    a = &w->anim;
    AnimInit(a, gUnk_09EF8CC0, gUnk_09EF8CA0);

    if (gGameState.flags & 8) {
        AnimStart(a, 1, 1);
    } else {
        AnimStart(a, 0, 1);
    }
}

s32 Task_MapSpark_1(MapSparkWork* w) {
    AnimUpdate(&w->anim);

    if (AnimIsFinished(&w->anim) != 0) {
        return 0;
    }
    return 1;
}

void Task_MapSpark_2(MapSparkWork* w) {
    FldObj* p = w->obj;
    s32 h;
    u16 x;
    u16 y;

    if (p->unk_1A <= 32) {
        h = p->unk_1A << 8;
    } else {
        h = 0x2000;
    }

    x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8);
    y = (p->fieldPosition.y >> 8) + ((p->fieldPosition.z - h) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x400, 0x50);
}

void Task_MapSpark_3(MapSparkWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

void Task_MapTalk_0(MapTalkWork* w, FldObj* obj) {
    w->obj = obj;
    w->tiles = AllocObjTiles(0x200, &gUnk_098A4B68[0x1028]);
    w->palette = LoadObjPalette(gUnk_08F69BE4, 32);
    AnimInit(&w->anim, gUnk_09EF8CD0, gUnk_09EF8CC8);
    AnimStart(&w->anim, 0, 1);
    w->unk_28 = 0;
}

s32 Task_MapTalk_1(MapTalkWork* w) {
    FldObj* p = w->obj;
    AnimState* anim = &w->anim;

    AnimUpdate(anim);

    if (gFieldState->actor.fieldPosition.x < p->fieldPosition.x) {
        w->unk_28 = 0;
        AnimStart(anim, 0, 1);
    } else {
        w->unk_28 = 1;
        AnimStart(anim, 1, 1);
    }
    return 1;
}

void Task_MapTalk_2(MapTalkWork* w) {
    FldObj* p = w->obj;
    u16 x;
    u16 y;

    if (w->unk_28 != 0) {
        x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8) - 16;
    } else {
        x = (p->fieldPosition.x >> 8) - (gFieldState->x >> 8) + 16;
    }
    y = (p->fieldPosition.y >> 8) + ((p->fieldPosition.z - (p->unk_1A << 8)) >> 8) - (gFieldState->y >> 8);
    DrawSprite(x, y, AnimGetGfx(&w->anim), w->tiles, w->palette, 0, 0x400, 0x50);
}

void Task_MapTalk_3(MapTalkWork* w) {
    ReleaseObjTiles(w->tiles);
    ReleaseObjPalette(w->palette);
}

const UnkStruct_080E7D80 gUnk_0984C158 = {
    gUnk_099912C4, gUnk_09858320, 0x200, 0, 0, gUnk_09EF8414, gUnk_09EF841C,
    1, 13, 0, 0, 0, 16, 16, 208, 0, &gTaskDescMapGmk01,
};

const char gTaskNameMapGmk01[] = "Task_MapGmk01";

const UnkStruct_080E7D80 gUnk_0984C190 = {
    gUnk_099912E4, gUnk_09858B3C, 0x400, 0, 0, gUnk_09EF8424, gUnk_09EF8460,
    1, 0, 0, 0, 0, 12, 24, 144, 0, &gTaskDescMapGmkBarrel,
};

const char gTaskNameMapGmkBarrel[] = "Task_MapGmk_Barrel";

const UnkStruct_080E7D80 gUnk_0984C1CC = {
    gUnk_09991324, gUnk_0985ADAA, 0x400, 0, 0, &gUnk_09EF8494, &gUnk_09EF84A4,
    1, 13, 0, 0, 0, 24, 62, 102, 0, &gTaskDescMapGmk04,
};

const char gTaskNameMapGmk04[] = "Task_MapGmk04";

const UnkStruct_080E7D80 gUnk_0984C204 = {
    gMoguPalette, gMoguFl00Tiles, 0x100, 0, 0, gMoguFl00Frames, gMoguFl00Anims,
    1, 13, 0, 0, 0, 16, 24, 207, 0, &gTaskDescMapGmk05,
};

const char gTaskNameMapGmk05[] = "Task_MapGmk05";

const UnkStruct_080E7D80 gUnk_0984C23C = {
    gUnk_09991344, gUnk_0985BDEA, 0x400, 0, 0, &gUnk_09EF84A8, &gUnk_09EF84B8,
    1, 13, 0, 0, 0, 24, 54, 102, 0, &gTaskDescMapGmk06,
};

const char gTaskNameMapGmk06[] = "Task_MapGmk06";

const char gTaskNameMapPrize[] = "Task_MapPrize";

const char gTaskNameMapPrzCard[] = "Task_MapPrzCard";

const char gTaskNameMapPrzStock[] = "Task_MapPrzStock";

const char gTaskNameMapMsg[] = "Task_MapMsg";

const char gTaskNameMapMsg2[] = "Task_MapMsg2";

const char gTaskNameMapSpark[] = "Task_MapSpark";

const char gTaskNameMapTalk[] = "Task_MapTalk";

TaskDesc gTaskDescMapEnm00 = {
    gTaskNameMapEnm00,
    (TaskInitFunc)Task_MapEnm00_0,
    (TaskUpdateFunc)Task_MapEnm00_1,
    (TaskFunc)Task_MapEnm00_2,
    (TaskFunc)Task_MapEnm00_3,
    sizeof(MapEnmWork),
};

TaskDesc gTaskDescMapEnm01 = {
    gTaskNameMapEnm01,
    (TaskInitFunc)Task_MapEnm01_0,
    (TaskUpdateFunc)Task_MapEnm01_1,
    (TaskFunc)Task_MapEnm01_2,
    (TaskFunc)Task_MapEnm01_3,
    sizeof(MapEnm01Work),
};

TaskDesc gTaskDescMapEnm02 = {
    gTaskNameMapEnm02,
    (TaskInitFunc)Task_MapEnm02_0,
    (TaskUpdateFunc)Task_MapEnm02_1,
    (TaskFunc)Task_MapEnm02_2,
    (TaskFunc)Task_MapEnm02_3,
    sizeof(MapEnmWork),
};

TaskDesc gTaskDescMapEnm03 = {
    gTaskNameMapEnm03,
    (TaskInitFunc)Task_MapEnm03_0,
    (TaskUpdateFunc)Task_MapEnm03_1,
    (TaskFunc)Task_MapEnm03_2,
    (TaskFunc)Task_MapEnm03_3,
    sizeof(MapEnm03Work),
};

TaskDesc gTaskDescMapEnm04 = {
    gTaskNameMapEnm04,
    (TaskInitFunc)Task_MapEnm04_0,
    (TaskUpdateFunc)Task_MapEnm04_1,
    (TaskFunc)Task_MapEnm04_2,
    (TaskFunc)Task_MapEnm04_3,
    sizeof(MapEnm01Work),
};

TaskDesc gTaskDescMapEnm05 = {
    gTaskNameMapEnm05,
    (TaskInitFunc)Task_MapEnm05_0,
    (TaskUpdateFunc)Task_MapEnm05_1,
    (TaskFunc)Task_MapEnm05_2,
    (TaskFunc)Task_MapEnm05_3,
    sizeof(MapEnmWork),
};

TaskDesc gTaskDescMapEnm06 = {
    gTaskNameMapEnm06,
    (TaskInitFunc)Task_MapEnm06_0,
    (TaskUpdateFunc)Task_MapEnm06_1,
    (TaskFunc)Task_MapEnm06_2,
    (TaskFunc)Task_MapEnm06_3,
    sizeof(MapEnmWork),
};

u8 gUnk_09EF6C38[] = "_";

TaskDesc gTaskDescMapDbg = {
    gTaskNameMapDbg,
    (TaskInitFunc)Task_MapDbg_0,
    (TaskUpdateFunc)Task_MapDbg_1,
    (TaskFunc)Task_MapDbg_2,
    (TaskFunc)Task_MapDbg_3,
    sizeof(MapDbgWork),
};

TaskDesc gTaskDescMapGmkJump = {
    gTaskNameMapGmkJump,
    (TaskInitFunc)Task_MapGmk_Jump_0,
    (TaskUpdateFunc)Task_MapGmk_Jump_1,
    (TaskFunc)Task_MapGmk_Jump_2,
    (TaskFunc)Task_MapGmk_Jump_3,
    sizeof(MapGmkJumpWork),
};

TaskDesc gTaskDescMapGmkEnm = {
    gTaskNameMapGmkEnm,
    (TaskInitFunc)Task_MapGmk_Enm_0,
    (TaskUpdateFunc)Task_MapGmk_Enm_1,
    (TaskFunc)Task_MapGmk_Enm_2,
    (TaskFunc)Task_MapGmk_Enm_3,
    sizeof(MapGmkEnmWork),
};

TaskDesc gTaskDescMapGmkDmy = {
    gTaskNameMapGmkDmy,
    (TaskInitFunc)Task_MapGmk_Dmy_0,
    (TaskUpdateFunc)Task_MapGmk_Dmy_1,
    (TaskFunc)Task_MapGmk_Dmy_2,
    (TaskFunc)Task_MapGmk_Dmy_3,
    sizeof(MapGmkDmyWork),
};

TaskDesc gTaskDescMapGmkTutorial = {
    gTaskNameMapGmkTutorial,
    (TaskInitFunc)Task_MapGmk_Tutorial_0,
    (TaskUpdateFunc)Task_MapGmk_Tutorial_1,
    (TaskFunc)Task_MapGmk_Tutorial_2,
    (TaskFunc)Task_MapGmk_Tutorial_3,
    sizeof(MapGmkTutorialWork),
};

TaskDesc gTaskDescMapGmkSpider = {
    gTaskNameMapGmkSpider,
    (TaskInitFunc)Task_MapGmk_Spider_0,
    (TaskUpdateFunc)Task_MapGmk_Spider_1,
    (TaskFunc)Task_MapGmk_Spider_2,
    (TaskFunc)Task_MapGmk_Spider_3,
    sizeof(MapGmkSpiderWork),
};

TaskDesc gTaskDescMapGmkGP00 = {
    gTaskNameMapGmkGP00,
    (TaskInitFunc)Task_MapGmk_GP00_0,
    (TaskUpdateFunc)Task_MapGmk_GP00_1,
    (TaskFunc)Task_MapGmk_GP00_2,
    (TaskFunc)Task_MapGmk_GP00_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP01 = {
    gTaskNameMapGmkGP01,
    (TaskInitFunc)Task_MapGmk_GP01_0,
    (TaskUpdateFunc)Task_MapGmk_GP01_1,
    (TaskFunc)Task_MapGmk_GP01_2,
    (TaskFunc)Task_MapGmk_GP01_3,
    sizeof(MapGmkGp1Work),
};

TaskDesc gTaskDescMapGmkGP02 = {
    gTaskNameMapGmkGP02,
    (TaskInitFunc)Task_MapGmk_GP02_0,
    (TaskUpdateFunc)Task_MapGmk_GP02_1,
    (TaskFunc)Task_MapGmk_GP02_2,
    (TaskFunc)Task_MapGmk_GP02_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP03 = {
    gTaskNameMapGmkGP03,
    (TaskInitFunc)Task_MapGmk_GP03_0,
    (TaskUpdateFunc)Task_MapGmk_GP03_1,
    (TaskFunc)Task_MapGmk_GP03_2,
    (TaskFunc)Task_MapGmk_GP03_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP04 = {
    gTaskNameMapGmkGP04,
    (TaskInitFunc)Task_MapGmk_GP04_0,
    (TaskUpdateFunc)Task_MapGmk_GP04_1,
    (TaskFunc)Task_MapGmk_GP04_2,
    (TaskFunc)Task_MapGmk_GP04_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP05 = {
    gTaskNameMapGmkGP05,
    (TaskInitFunc)Task_MapGmk_GP05_0,
    (TaskUpdateFunc)Task_MapGmk_GP05_1,
    (TaskFunc)Task_MapGmk_GP05_2,
    (TaskFunc)Task_MapGmk_GP05_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP06 = {
    gTaskNameMapGmkGP06,
    (TaskInitFunc)Task_MapGmk_GP06_0,
    (TaskUpdateFunc)Task_MapGmk_GP06_1,
    (TaskFunc)Task_MapGmk_GP06_2,
    (TaskFunc)Task_MapGmk_GP06_3,
    sizeof(MapGmkGpWork),
};

TaskDesc gTaskDescMapGmkGP07 = {
    gTaskNameMapGmkGP07,
    (TaskInitFunc)Task_MapGmk_GP07_0,
    (TaskUpdateFunc)Task_MapGmk_GP07_1,
    (TaskFunc)Task_MapGmk_GP07_2,
    (TaskFunc)Task_MapGmk_GP07_3,
    sizeof(MapGmkGp07Work),
};

TaskDesc gTaskDescMapGmkGP08 = {
    gTaskNameMapGmkGP08,
    (TaskInitFunc)Task_MapGmk_GP08_0,
    (TaskUpdateFunc)Task_MapGmk_GP08_1,
    (TaskFunc)Task_MapGmk_GP08_2,
    (TaskFunc)Task_MapGmk_GP08_3,
    sizeof(MapGmkGp08Work),
};

TaskDesc gTaskDescMapGmkGP09 = {
    gTaskNameMapGmkGP09,
    (TaskInitFunc)Task_MapGmk_GP09_0,
    (TaskUpdateFunc)Task_MapGmk_GP09_1,
    (TaskFunc)Task_MapGmk_GP09_2,
    (TaskFunc)Task_MapGmk_GP09_3,
    sizeof(MapGmkGp09Work),
};

TaskDesc gTaskDescMapGmk00 = {
    gTaskNameMapGmk00,
    (TaskInitFunc)Task_MapGmk00_0,
    (TaskUpdateFunc)Task_MapGmk00_1,
    (TaskFunc)Task_MapGmk00_2,
    (TaskFunc)Task_MapGmk00_3,
    sizeof(MapGmk00Work),
};

TaskDesc gTaskDescMapGmk01 = {
    gTaskNameMapGmk01,
    (TaskInitFunc)Task_MapGmk01_0,
    (TaskUpdateFunc)Task_MapGmk01_1,
    (TaskFunc)Task_MapGmk01_2,
    (TaskFunc)Task_MapGmk01_3,
    sizeof(MapGmk01Work),
};

TaskDesc gTaskDescMapGmkBarrel = {
    gTaskNameMapGmkBarrel,
    (TaskInitFunc)Task_MapGmk_Barrel_0,
    (TaskUpdateFunc)Task_MapGmk_Barrel_1,
    (TaskFunc)Task_MapGmk_Barrel_2,
    (TaskFunc)Task_MapGmk_Barrel_3,
    sizeof(MapGmkBarrelWork),
};

TaskDesc gTaskDescMapGmk04 = {
    gTaskNameMapGmk04,
    (TaskInitFunc)Task_MapGmk04_0,
    (TaskUpdateFunc)Task_MapGmk04_1,
    (TaskFunc)Task_MapGmk04_2,
    (TaskFunc)Task_MapGmk04_3,
    sizeof(MapGmk04Work),
};

TaskDesc gTaskDescMapGmk05 = {
    gTaskNameMapGmk05,
    (TaskInitFunc)Task_MapGmk05_0,
    (TaskUpdateFunc)Task_MapGmk05_1,
    (TaskFunc)Task_MapGmk05_2,
    (TaskFunc)Task_MapGmk05_3,
    sizeof(MapGmk05Work),
};

TaskDesc gTaskDescMapGmk06 = {
    gTaskNameMapGmk06,
    (TaskInitFunc)Task_MapGmk06_0,
    (TaskUpdateFunc)Task_MapGmk06_1,
    (TaskFunc)Task_MapGmk06_2,
    (TaskFunc)Task_MapGmk06_3,
    sizeof(MapGmk06Work),
};

TaskDesc gTaskDescMapPrize = {
    gTaskNameMapPrize,
    (TaskInitFunc)Task_MapPrize_0,
    (TaskUpdateFunc)Task_MapPrize_1,
    (TaskFunc)Task_MapPrize_2,
    (TaskFunc)Task_MapPrize_3,
    sizeof(MapPrizeWork),
};

TaskDesc gTaskDescMapPrzCard = {
    gTaskNameMapPrzCard,
    (TaskInitFunc)Task_MapPrzCard_0,
    (TaskUpdateFunc)Task_MapPrzCard_1,
    (TaskFunc)Task_MapPrzCard_2,
    (TaskFunc)Task_MapPrzCard_3,
    sizeof(MapPrzCardWork),
};

TaskDesc gTaskDescMapPrzStock = {
    gTaskNameMapPrzStock,
    (TaskInitFunc)Task_MapPrzStock_0,
    (TaskUpdateFunc)Task_MapPrzStock_1,
    (TaskFunc)Task_MapPrzStock_2,
    (TaskFunc)Task_MapPrzStock_3,
    sizeof(MapPrzStockWork),
};

TaskDesc gTaskDescMapMsg = {
    gTaskNameMapMsg,
    (TaskInitFunc)func_080F58C4,
    (TaskUpdateFunc)Task_MapMsg_1,
    (TaskFunc)func_080F596C,
    (TaskFunc)func_080F59A0,
    sizeof(MapMsgWork),
};

TaskDesc gTaskDescMapMsg2 = {
    gTaskNameMapMsg2,
    (TaskInitFunc)func_080F58C4,
    (TaskUpdateFunc)Task_MapMsg2_1,
    (TaskFunc)func_080F596C,
    (TaskFunc)func_080F59A0,
    sizeof(MapMsgWork),
};

TaskDesc gTaskDescMapSpark = {
    gTaskNameMapSpark,
    (TaskInitFunc)Task_MapSpark_0,
    (TaskUpdateFunc)Task_MapSpark_1,
    (TaskFunc)Task_MapSpark_2,
    (TaskFunc)Task_MapSpark_3,
    sizeof(MapSparkWork),
};

TaskDesc gTaskDescMapTalk = {
    gTaskNameMapTalk,
    (TaskInitFunc)Task_MapTalk_0,
    (TaskUpdateFunc)Task_MapTalk_1,
    (TaskFunc)Task_MapTalk_2,
    (TaskFunc)Task_MapTalk_3,
    sizeof(MapTalkWork),
};
