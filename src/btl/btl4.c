#include "battle_localized_data.h"
#include "registration_data.h"
#include "system_state.h"
#include "btl4.h"
#include "btl4_api.h"
#include "tutorial.h"
#include "sprites_btl.h"
#include "sprites_btl_hud.h"
#include "gba/io_reg.h"

void task_btl_pop_cb_0(BtlPopCbWork* work, BtlPopSrc* src) {
#ifdef VERSION_EU
    work->palette = LoadObjPalette(gBStatesPalette, 32);

    switch (gLanguage) {
    case 0:
    case 1:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B4AC46);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B4AB9C;
            break;
        case 1:
            work->gfx = gUnkEu_08B4ABAC;
            break;
        case 2:
            work->gfx = gUnkEu_08B4ABBC;
            break;
        case 3:
            work->gfx = gUnkEu_08B4ABCC;
            break;
        case 4:
            work->gfx = gUnkEu_08B4ABDC;
            break;
        case 5:
            work->gfx = gUnkEu_08B4ABEC;
            break;
        case 6:
            work->gfx = gUnkEu_08B4ABFC;
            break;
        case 7:
            work->gfx = gUnkEu_08B4AC0C;
            break;
        case 8:
            work->gfx = gUnkEu_08B4AC1C;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B4AC2C;
            break;
        }
        break;
    case 4:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B52782);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B526D8;
            break;
        case 1:
            work->gfx = gUnkEu_08B526E8;
            break;
        case 2:
            work->gfx = gUnkEu_08B526F8;
            break;
        case 3:
            work->gfx = gUnkEu_08B52708;
            break;
        case 4:
            work->gfx = gUnkEu_08B52718;
            break;
        case 5:
            work->gfx = gUnkEu_08B52728;
            break;
        case 6:
            work->gfx = gUnkEu_08B52738;
            break;
        case 7:
            work->gfx = gUnkEu_08B52748;
            break;
        case 8:
            work->gfx = gUnkEu_08B52758;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B52768;
            break;
        }
        break;
    case 3:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B533BE);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B53314;
            break;
        case 1:
            work->gfx = gUnkEu_08B53324;
            break;
        case 2:
            work->gfx = gUnkEu_08B53334;
            break;
        case 3:
            work->gfx = gUnkEu_08B53344;
            break;
        case 4:
            work->gfx = gUnkEu_08B53354;
            break;
        case 5:
            work->gfx = gUnkEu_08B53364;
            break;
        case 6:
            work->gfx = gUnkEu_08B53374;
            break;
        case 7:
            work->gfx = gUnkEu_08B53384;
            break;
        case 8:
            work->gfx = gUnkEu_08B53394;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B533A4;
            break;
        }
        break;
    case 2:
    default:
        work->tiles = AllocObjTiles(0x200, gUnkEu_08B53FFA);

        switch (src->number) {
        case 0:
            work->gfx = gUnkEu_08B53F50;
            break;
        case 1:
            work->gfx = gUnkEu_08B53F60;
            break;
        case 2:
            work->gfx = gUnkEu_08B53F70;
            break;
        case 3:
            work->gfx = gUnkEu_08B53F80;
            break;
        case 4:
            work->gfx = gUnkEu_08B53F90;
            break;
        case 5:
            work->gfx = gUnkEu_08B53FA0;
            break;
        case 6:
            work->gfx = gUnkEu_08B53FB0;
            break;
        case 7:
            work->gfx = gUnkEu_08B53FC0;
            break;
        case 8:
            work->gfx = gUnkEu_08B53FD0;
            break;
        case 9:
        default:
            work->gfx = gUnkEu_08B53FE0;
            break;
        }
        break;
    }
#else
    work->tiles = AllocObjTiles(0x200, gUnk_08B1FD66);
    work->palette = LoadObjPalette(gBStatesPalette, 32);

    switch (src->number) {
    case 0:
        work->gfx = gUnk_08B1FCBC;
        break;
    case 1:
        work->gfx = gUnk_08B1FCCC;
        break;
    case 2:
        work->gfx = gUnk_08B1FCDC;
        break;
    case 3:
        work->gfx = gUnk_08B1FCEC;
        break;
    case 4:
        work->gfx = gUnk_08B1FCFC;
        break;
    case 5:
        work->gfx = gUnk_08B1FD0C;
        break;
    case 6:
        work->gfx = gUnk_08B1FD1C;
        break;
    case 7:
        work->gfx = gUnk_08B1FD2C;
        break;
    case 8:
        work->gfx = gUnk_08B1FD3C;
        break;
    case 9:
    default:
        work->gfx = gUnk_08B1FD4C;
        break;
    }
#endif

    work->x = src->x;
    work->y = src->y;
    work->z = src->z;
    work->timer = 0;
}

s32 task_btl_pop_cb_1(BtlPopCbWork* work) {
    work->z -= 192;

    if (work->timer > 49) {
        return 0;
    }

    work->timer++;
    return 1;
}

void task_btl_pop_cb_2(BtlPopCbWork* work) {
    s16 x;
    s16 y;

    WorldToScreen(&x, &y, work->x, work->y, work->z);
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0, 16, 5);
}

void task_btl_pop_cb_3(BtlPopCbWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void* GetExpDigitGfx(s32 digit, u8 leading) {
    switch (digit) {
    case 0:
        if (leading != 0) {
            return gUnk_08B25E6E;
        }
        break;
    case 1:
        return gUnk_08B25E78;
    case 2:
        return gUnk_08B25E82;
    case 3:
        return gUnk_08B25E8C;
    case 4:
        return gUnk_08B25E96;
    case 5:
        return gUnk_08B25EA0;
    case 6:
        return gUnk_08B25EAA;
    case 7:
        return gUnk_08B25EB4;
    case 8:
        return gUnk_08B25EBE;
    case 9:
        return gUnk_08B25EC8;
    }
    return 0;
}

void BtlExpSetNumber(BtlExpWork* work, u32 value) {
    void* d0;
    void* d1;
    void* d2;
    void* d3;
    u8 flag;

    d0 = GetExpDigitGfx(value / 10000, 0);
    work->gfx2[0] = d0;
    value %= 10000;
    flag = d0 != 0;

    d1 = GetExpDigitGfx(value / 1000, flag);
    work->gfx2[1] = d1;
    value %= 1000;

    if (d1 != 0) {
        flag = 1;
    }

    d2 = GetExpDigitGfx(value / 100, flag);
    work->gfx2[2] = d2;
    value %= 100;

    if (d2 != 0) {
        flag = 1;
    }

    d3 = GetExpDigitGfx(value / 10, flag);
    work->gfx2[3] = d3;
    value %= 10;

    if (d3 != 0) {
        flag = 1;
    }

#ifdef VERSION_JP
    work->gfx2[4] = gUnk_09EE1538[value + 4];
#else
    work->gfx2[4] = gUnk_09EE157C[value + 4];
#endif
    work->gfx2[5] = gUnk_08B25ED2;
}

void task_btl_exp_0(BtlExpWork* work) {
    s32 i;

    work->palette = LoadObjPalette(gBStatesPalette, 32);
#ifdef VERSION_EU
    work->tiles = AllocObjTiles(0xC0, gUnk_08B25EF0);
#else
    work->tiles = AllocObjTiles(0xA0, gUnk_08B25EF0);
#endif
    work->gfx = 0;

    for (i = 0; i <= 5; i++) {
        work->tiles2[i] = AllocObjTiles(32, gUnk_08B25EF0);
        work->gfx2[i] = 0;
    }

    work->timer = 0;
    work->level = gGameState.progression.level;
    work->lastExp = gGameState.progression.exp;
    work->state = 0;
    work->gainedExp = 0;
}

s32 task_btl_exp_1(BtlExpWork* work) {
    if (gBtlWork->flags & 0x2000) {
        return 0;
    }

    if (work->level < gGameState.progression.level) {
        BtlExpSetNumber(work, gGameState.progression.level);
#ifdef VERSION_EU
        switch (gLanguage) {
        case 0:
            work->gfx = gUnkEu_08B55C58;
            break;
        case 1:
            work->gfx = gUnkEu_08B55CFE;
            break;
        case 4:
            work->gfx = gUnkEu_08B55D18;
            break;
        case 3:
            work->gfx = gUnkEu_08B55D32;
            break;
        case 2:
        default:
            work->gfx = gUnkEu_08B55D66;
            break;
        }
#else
        work->gfx = gUnk_08B25E40;
#endif
        work->timer = 0;
        work->state = 3;
        work->level = gGameState.progression.level;
        work->gainedExp = 0;
    }

    if (work->state != 3) {
        if (work->lastExp < gGameState.progression.exp) {
            work->gainedExp += gGameState.progression.exp - work->lastExp;
            BtlExpSetNumber(work, work->gainedExp);
#ifdef VERSION_EU
            switch (gLanguage) {
            case 0:
                work->gfx = gUnk_08B25E54;
                break;
            case 1:
                work->gfx = gUnk_08B25E54;
                break;
            case 4:
                work->gfx = gUnk_08B25E54;
                break;
            case 3:
                work->gfx = gUnkEu_08B55D4C;
                break;
            case 2:
            default:
                work->gfx = gUnkEu_08B55D80;
                break;
            }
#else
            work->gfx = gUnk_08B25E54;
#endif
            work->timer = 0;
            work->state = 1;
            work->lastExp = gGameState.progression.exp;
        }
    }

    switch (work->state) {
    case 0:
        break;
    case 3:
        if (work->timer > 100) {
            if (gGameState.progression.level > 98) {
                work->state = 0;
            } else {
                work->state = 2;
                BtlExpSetNumber(work, gGameState.progression.nextExp - gGameState.progression.exp);
#ifdef VERSION_EU
                switch (gLanguage) {
                case 0:
                    work->gfx = gUnk_08B25E5E;
                    break;
                case 1:
                    work->gfx = gUnkEu_08B55D08;
                    break;
                case 4:
                    work->gfx = gUnkEu_08B55D22;
                    break;
                case 3:
                    work->gfx = gUnkEu_08B55D3C;
                    break;
                case 2:
                default:
                    work->gfx = gUnkEu_08B55D70;
                    break;
                }
#else
                work->gfx = gUnk_08B25E5E;
#endif
            }
            work->timer = 0;
            work->gainedExp = 0;
        } else {
            work->timer++;
        }
        break;
    case 1:
        if (work->timer > 60) {
            if (gGameState.progression.level > 98) {
                work->state = 0;
            } else {
                work->state = 2;
                BtlExpSetNumber(work, gGameState.progression.nextExp - gGameState.progression.exp);
#ifdef VERSION_EU
                switch (gLanguage) {
                case 0:
                    work->gfx = gUnk_08B25E5E;
                    break;
                case 1:
                    work->gfx = gUnkEu_08B55D08;
                    break;
                case 4:
                    work->gfx = gUnkEu_08B55D22;
                    break;
                case 3:
                    work->gfx = gUnkEu_08B55D3C;
                    break;
                case 2:
                default:
                    work->gfx = gUnkEu_08B55D70;
                    break;
                }
#else
                work->gfx = gUnk_08B25E5E;
#endif
            }
            work->timer = 0;
            work->gainedExp = 0;
        } else {
            work->timer++;
        }
        break;
    case 2:
        if (work->timer > 100) {
            work->timer = 0;
            work->state = 0;
        } else {
            work->timer++;
        }
        break;
    }

    return 1;
}

void task_btl_exp_2(BtlExpWork* work) {
    s32 i;
    s16 x;
    u16 y;

    if (work->state != 0) {
        y = 40;
        x = 0;
        DrawSprite(0, y, work->gfx, work->tiles, work->palette, 0, 0x410, x);

#ifdef VERSION_JP
        x = 32;
#else
        if (work->state == 2) {
#ifdef VERSION_EU
            x = 48;
#else
            x = 40;
#endif
        } else {
            x = 32;
        }
#endif

        for (i = 0; i <= 5; i++) {
            if (work->gfx2[i] != 0) {
                DrawSprite(x, y, work->gfx2[i], work->tiles2[i], work->palette, 0, 0x410, 0);
                x += 8;
            }
        }
    }
}

void task_btl_exp_3(BtlExpWork* work) {
    s32 i;

    for (i = 0; i < 6; i++) {
        ReleaseObjTiles(work->tiles2[i]);
    }

    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_vslockon_0(BtlVslockonWork* work) {
    work->tiles = LoadObjTiles(gUnk_08B1D8BC, 0x180);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    AnimInit(&work->anim, gUnk_09EE10F8, gUnk_09EE10EC);
    AnimStart(&work->anim, 0, 1);
    work->gfx = AnimGetGfx(&work->anim);
    gBtlWork->actor2 = gRikuBtlWork->actor;
    gRikuBtlWork->actor2 = gBtlWork->actor;
}

s32 task_btl_vslockon_1(BtlVslockonWork* work) {
    if (gBtlWork->hcEffect == 19) {
        gRikuBtlWork->actor2 = 0;
    } else {
        gRikuBtlWork->actor2 = gBtlWork->actor;
    }

    if (gRikuBtlWork->hcEffect == 19) {
        gBtlWork->actor2 = 0;
    } else {
        gBtlWork->actor2 = gRikuBtlWork->actor;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void task_btl_vslockon_2(BtlVslockonWork* work) {
    s16 x;
    s16 y;
    BtlObj* p;

    p = gBtlWork->actor2;
    if (p != 0) {
        WorldToScreen(&x, &y, p->x, p->y, p->z - (p->centerHeight << 8));
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, 0, 0, 0x100);
    }
}

void task_btl_vslockon_3(BtlVslockonWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void task_btl_hpoth_0(BtlHpothWork* work) {
    work->palette = LoadObjPalette(gUnk_096FAC64, 32);
    work->tiles = AllocObjTiles(0x280, gUnk_08B20D6E);
    work->gfx = gUnk_08B20D20;
    AnimInit(&work->anim, gUnk_09EE12B0, gUnk_09EE12A4);
    work->palette2 = LoadObjPalette(gBStatesPalette, 32);
    work->tiles2 = AllocObjTiles(0x280, gBHpgagTiles);
    work->tiles3 = AllocObjTiles(0x120, gBHpgagTiles);
    work->tiles4 = AllocObjTiles(0x80, gBHpgagTiles);
    work->gfx2 = gBHpgagFrame1;
    AnimInit(&work->anim2, gBHpgagAnims, gBHpgagFrames);
    AnimStart(&work->anim, 0, 1);

    if (gRikuBtlWork->actor->maxHp <= 40) {
        work->gaugeSize = 0;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 80) {
        work->gaugeSize = 1;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 120) {
        work->gaugeSize = 2;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 160) {
        work->gaugeSize = 3;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 200) {
        work->gaugeSize = 4;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 240) {
        work->gaugeSize = 5;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 280) {
        work->gaugeSize = 6;
        work->gaugeMode = 0;
    } else if (gRikuBtlWork->actor->maxHp <= 320) {
        work->gaugeSize = 0;
        work->gaugeMode = 1;
    } else if (gRikuBtlWork->actor->maxHp <= 360) {
        work->gaugeSize = 1;
        work->gaugeMode = 1;
    } else if (gRikuBtlWork->actor->maxHp <= 400) {
        work->gaugeSize = 2;
        work->gaugeMode = 1;
    } else if (gRikuBtlWork->actor->maxHp <= 440) {
        work->gaugeSize = 3;
        work->gaugeMode = 1;
    } else if (gRikuBtlWork->actor->maxHp <= 480) {
        work->gaugeSize = 4;
        work->gaugeMode = 1;
    } else if (gRikuBtlWork->actor->maxHp <= 520) {
        work->gaugeSize = 5;
        work->gaugeMode = 1;
    } else if (gRikuBtlWork->actor->maxHp <= 560) {
        work->gaugeSize = 6;
        work->gaugeMode = 1;
    } else {
        work->gaugeSize = 6;
        work->gaugeMode = 1;
    }

    if (work->gaugeMode == 0) {
        switch (work->gaugeSize) {
        case 0:
        case 1:
            AnimStart(&work->anim2, 1, 1);
            break;
        case 2:
            AnimStart(&work->anim2, 3, 1);
            break;
        case 3:
            AnimStart(&work->anim2, 5, 1);
            break;
        case 4:
            AnimStart(&work->anim2, 7, 1);
            break;
        case 5:
            AnimStart(&work->anim2, 9, 1);
            break;
        case 6:
            AnimStart(&work->anim2, 11, 1);
            break;
        default:
            AnimStart(&work->anim2, 11, 1);
            break;
        }
        work->gfx3 = 0;
    } else {
        AnimStart(&work->anim2, 11, 1);

        switch (work->gaugeSize) {
        case 0:
            work->gfx3 = gBHpgagFrame19;
            break;
        case 1:
            work->gfx3 = gBHpgagFrame20;
            break;
        case 2:
            work->gfx3 = gBHpgagFrame21;
            break;
        case 3:
            work->gfx3 = gBHpgagFrame22;
            break;
        case 4:
            work->gfx3 = gBHpgagFrame23;
            break;
        case 5:
            work->gfx3 = gBHpgagFrame24;
            break;
        case 6:
        default:
            work->gfx3 = gBHpgagFrame25;
            break;
        }
    }

    work->hpRatio = 0x100;
    work->firstUpdate = 1;
    work->unk_5C = 1;
    work->timer = 0;
    work->prevHp = 0;
    work->displayHp = 0;
}

s32 task_btl_hpoth_1(BtlHpothWork* work) {
    BtlObj* actor;
    s32 flag;
    u32 state;

    actor = gRikuBtlWork->actor;
    if (actor == 0) {
        return 0;
    }

    if (gBtlWork->flags & 0x2000) {
        return 0;
    }

    if (work->gaugeMode != 1 && work->hpRatio < 64) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (actor->hp < work->prevHp) {
        work->timer = 44;
    }

    if (work->timer != 0) {
        AnimChange(&work->anim, 1, 1);
        work->timer--;
    } else if (flag != 0) {
        AnimChange(&work->anim, 2, 1);
    } else {
        AnimChange(&work->anim, 0, 1);
    }

    if (work->firstUpdate != 0) {
        work->firstUpdate = 0;
        work->displayHp = actor->hp;
    } else if (work->displayHp < actor->hp) {
        work->displayHp += 3;
        if (work->displayHp > actor->hp) {
            work->displayHp = actor->hp;
        }
    } else if (work->displayHp > actor->hp) {
        work->displayHp -= 3;
        if (work->displayHp < actor->hp) {
            work->displayHp = actor->hp;
        }
    }

    if (work->gaugeMode == 1) {
        if (work->displayHp <= 280) {
            work->gaugeMode = 2;
        }
    } else if (work->gaugeMode == 2) {
        if (work->displayHp > 280) {
            work->gaugeMode = 1;
        }
    }

    state = work->gaugeMode;

    switch (state) {
    case 0:
        work->hpRatio = (work->displayHp << 8) / actor->maxHp;
        break;
    case 1:
        work->hpRatio = ((work->displayHp - 280) << 8) / (actor->maxHp - 280);
        break;
    case 2:
        work->hpRatio = (work->displayHp << 8) / 280;
        break;
    }

    if (flag != 0) {
        if (state == 0) {
            switch (work->gaugeSize) {
            case 0:
            case 1:
                AnimChange(&work->anim2, 2, 1);
                break;
            case 2:
                AnimChange(&work->anim2, 4, 1);
                break;
            case 3:
                AnimChange(&work->anim2, 6, 1);
                break;
            case 4:
                AnimChange(&work->anim2, 8, 1);
                break;
            case 5:
                AnimChange(&work->anim2, 10, 1);
                break;
            case 6:
                AnimChange(&work->anim2, 12, 1);
                break;
            default:
                AnimChange(&work->anim2, 12, 1);
                break;
            }
        } else {
            AnimChange(&work->anim2, 12, 1);
        }
    } else {
        if (state == 0) {
            switch (work->gaugeSize) {
            case 0:
            case 1:
                AnimChange(&work->anim2, 1, 1);
                break;
            case 2:
                AnimChange(&work->anim2, 3, 1);
                break;
            case 3:
                AnimChange(&work->anim2, 5, 1);
                break;
            case 4:
                AnimChange(&work->anim2, 7, 1);
                break;
            case 5:
                AnimChange(&work->anim2, 9, 1);
                break;
            case 6:
            default:
                AnimChange(&work->anim2, 11, 1);
                break;
            }
        } else {
            AnimChange(&work->anim2, 11, 1);
        }
    }

    work->gfx = AnimUpdate(&work->anim);
    work->gfx2 = AnimUpdate(&work->anim2);
    work->prevHp = actor->hp;
    return 1;
}

void task_btl_hpoth_2(BtlHpothWork* work) {
    s32 scale;
    ObjAffine* affine;

    DrawSprite(236, 2, work->gfx, work->tiles, work->palette, 0, 0x411, 1);

    switch (work->gaugeMode) {
    case 0:
        DrawSprite(236, 2, work->gfx2, work->tiles2, work->palette2, 0, 0x411, 4);
        break;
    case 1:
        DrawSprite(236, 2, gBHpgagFrame27, work->tiles2, work->palette2, 0, 0x411, 4);
        DrawSprite(236, 2, work->gfx3, work->tiles3, work->palette2, 0, 0x411, 3);
        break;
    case 2:
        DrawSprite(236, 2, work->gfx2, work->tiles2, work->palette2, 0, 0x411, 4);
        DrawSprite(236, 2, work->gfx3, work->tiles3, work->palette2, 0, 0x411, 5);
        break;
    }

    switch (work->gaugeMode) {
    case 2:
        scale = work->hpRatio;
        break;
    case 0:
        switch (work->gaugeSize) {
        case 0:
        case 1:
            scale = work->hpRatio * 72 >> 8;
            break;
        case 2:
            scale = work->hpRatio * 109 >> 8;
            break;
        case 3:
            scale = work->hpRatio * 146 >> 8;
            break;
        case 4:
            scale = work->hpRatio * 182 >> 8;
            break;
        case 5:
            scale = work->hpRatio * 219 >> 8;
            break;
        case 6:
        default:
            scale = work->hpRatio;
            break;
        }
        break;
    case 1:
    default:
        switch (work->gaugeSize) {
        case 0:
            scale = work->hpRatio * 36 >> 8;
            break;
        case 1:
            scale = work->hpRatio * 72 >> 8;
            break;
        case 2:
            scale = work->hpRatio * 109 >> 8;
            break;
        case 3:
            scale = work->hpRatio * 146 >> 8;
            break;
        case 4:
            scale = work->hpRatio * 182 >> 8;
            break;
        case 5:
            scale = work->hpRatio * 219 >> 8;
            break;
        case 6:
        default:
            scale = work->hpRatio;
            break;
        }
        break;
    }

    scale *= 2;

    if (work->displayHp > 0) {
        if (scale < 10) {
            scale = 10;
        }

        if (scale > 256) {
            affine = AllocObjAffine(0, scale, 256, 1);
        } else {
            affine = AllocObjAffine(0, scale, 256, 0);
        }

        if (work->gaugeMode == 1) {
            DrawSprite(209, 9, gBHpgagFrame29, work->tiles4, work->palette2, affine, 0x410, 2);
        } else {
            DrawSprite(209, 6, gBHpgagFrame28, work->tiles4, work->palette2, affine, 0x410, 2);
        }
    }
}

void task_btl_hpoth_3(BtlHpothWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjTiles(work->tiles4);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette);
}

void TutorialOpenMessage(u16 a) {
    gDispCnt = (gDispCnt & ~DISPCNT_MODE_MASK) | DISPCNT_MODE_1;
    CreateCardMessageTask(&gBtlWork->taskPools[1], 0, a);
}

void TutorialOpenPersistentMessage(u16 a) {
    CreatePersistentSysmsgwinTask(&gBtlWork->taskPools[1], a);
}

void TutorialRestoreBgMode(void) {
    gDispCnt = (gDispCnt & ~DISPCNT_MODE_MASK) | DISPCNT_MODE_2;
}

void TutorialQueueMessage(TutorialWork* p, u16 b, u32 c) {
    p->timer = 0;
    p->state = 1;
    p->nextState = c;
    p->message = b;
}

void TutorialQueuePersistentMessage(TutorialWork* p, u16 b, u32 c) {
    p->timer = 0;
    p->state = 3;
    p->nextState = c;
    p->message = b;
}

void TutorialCloseMessage(void) {
    CloseMessageWindow();
}

void TutorialWait(TutorialWork* p, u16 b, u32 c) {
    p->timer = 0;
    p->state = 0;
    p->nextState = c;
    p->unk_00E = b;
}

void TutorialShowArrow(TutorialWork* p, u16 b, u16 c, u16 d) {
    p->flags |= 4;
    p->arrowX = b;
    p->arrowY = c;
    AnimStart(&p->anim, d, 1);
}

void TutorialHideArrow(TutorialWork* p) {
    p->flags &= ~4;
}

TaskDesc gTaskDescBtlPopCb = {
    "task_btl_pop_cb",
    (TaskInitFunc)task_btl_pop_cb_0,
    (TaskUpdateFunc)task_btl_pop_cb_1,
    (TaskDrawFunc)task_btl_pop_cb_2,
    (TaskDestroyFunc)task_btl_pop_cb_3,
    sizeof(BtlPopCbWork),
};

TaskDesc gTaskDescBtlExp = {
    "task_btl_exp",
    (TaskInitFunc)task_btl_exp_0,
    (TaskUpdateFunc)task_btl_exp_1,
    (TaskDrawFunc)task_btl_exp_2,
    (TaskDestroyFunc)task_btl_exp_3,
    sizeof(BtlExpWork),
};

TaskDesc gTaskDescBtlVslockon = {
    "task_btl_vslockon",
    (TaskInitFunc)task_btl_vslockon_0,
    (TaskUpdateFunc)task_btl_vslockon_1,
    (TaskDrawFunc)task_btl_vslockon_2,
    (TaskDestroyFunc)task_btl_vslockon_3,
    sizeof(BtlVslockonWork),
};

TaskDesc gTaskDescBtlHpoth = {
    "task_btl_hpoth",
    (TaskInitFunc)task_btl_hpoth_0,
    (TaskUpdateFunc)task_btl_hpoth_1,
    (TaskDrawFunc)task_btl_hpoth_2,
    (TaskDestroyFunc)task_btl_hpoth_3,
    sizeof(BtlHpothWork),
};
