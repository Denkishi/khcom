#include "macros.h"
#include "battle.h"
#include "battle_actor.h"
#include "hum_types.h"
#include "romcri_backgrounds.h"

BtlWork* gRikuBtlWork EWRAM_COMMON(4);
FieldState* gFieldState EWRAM_COMMON(4);

static const u8 sHumReloadPaletteCycle[8] = { 0, 1, 2, 3, 4, 3, 2, 1 };

void HumDrawSub(HumWork* p, HumSub* s) {
    s16 x;
    s16 y;
    BtlObj* c;
    u16 attr;
    ObjAffine* affine;
    u16 prio;
    s32 sx;
    s32 sy;

    if (s == NULL) {
        return;
    }

    if (s->flags & 2) {
        return;
    }
    c = &p->actor;
    attr = GetBattleSpritePriorityFlags(s->y);

    if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
        sy = gBtlWork->scale;
        sx = sy;
    } else {
        sy = gBtlWork->scale;

        if (sy == 0x100) {
            sx = sy;
            attr |= 1;
        } else {
            sx = -sy;
        }
    }

    if (sy == 0x100 && sx == 0x100) {
        affine = 0;
    } else if (sy <= 0xFF) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }

    if (s->flags & 4) {
        prio = (-0x1004 - (s->y >> 8) * 4) | 3;
    } else if (s->flags & 1) {
        prio = ((-0x1004 - (c->y >> 8) * 4) | 3) - 1;
    } else {
        prio = ((-0x1004 - (c->y >> 8) * 4) | 3) + 1;
    }
    WorldToScreen(&x, &y, s->x, s->y, s->z);
    DrawSprite(x, y, s->gfx, s->tiles, s->palette2, affine, attr, prio);
}

void HumDraw(HumWork* work) {
    s16 x;
    s16 y;
    BtlObj* c = &work->actor;
    u16 attr;
    ObjAffine* affine;
    s32 sx;
    s32 sy;
    s32 g;
    s16 idx;

    if (work->flags & 0x20) {
        attr = 0x800;
    } else {
        attr = GetBattleSpritePriorityFlags(c->y);
    }
    WorldToScreen(&x, &y, c->x, c->y, c->z);

    if (work->scaleX == 0x100 && work->scaleY == 0x100) {
        if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
            sy = gBtlWork->scale;
            sx = sy;
        } else {
            sy = gBtlWork->scale;

            if (sy == 0x100) {
                sx = sy;
                attr |= 1;
            } else {
                sx = -sy;
            }
        }
    } else {
        if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
            sx = (gBtlWork->scale * work->scaleX >> 8);
            g = gBtlWork->scale;
            sy = g * work->scaleY >> 8;
        } else {
            sx = -(gBtlWork->scale * work->scaleX >> 8);
            g = gBtlWork->scale;
            sy = g * work->scaleY >> 8;
        }
    }

    if (sy == 0x100 && sx == 0x100) {
        affine = 0;
    } else if (sy <= 0xFF) {
        affine = AllocObjAffine(0, sx, sy, 0);
    } else {
        affine = AllocObjAffine(0, sx, sy, 1);
    }

    if (work->state == 17) {
        idx = (work->stateTimer >> 2) % 8;

        if (work->stateTimer & 1) {
            work->flags |= 2;
            LoadObjPaletteBank(work->palette->index, gUnk_08F6DA04 + 32 + sHumReloadPaletteCycle[idx] * 32);
        } else {
            work->flags &= ~2;
            LoadObjPaletteBank(work->palette->index, work->paletteData);
        }
    } else if (StepHitFlash(c)) {
        work->flags |= 2;
        LoadObjPaletteBank(work->palette->index, gUnk_08F69BC4);
    } else if (work->flags & 2) {
        work->flags &= ~2;
        LoadObjPaletteBank(work->palette->index, work->paletteData);
    }
    DrawSprite(x, y, work->gfx, work->tiles, work->palette, affine, attr, (-0x1004 - (c->y >> 8) * 4) | 3);
    HumDrawSub(work, work->sub);
    HumDrawSub(work, work->sub2);
    TaskPoolDraw(&work->tasks);
}
void HandleRikuAiCardInput(void) {
    BtlObj* c = gRikuBtlWork->actor;
    u8 keys;
    u16 t;

    if (gRikuBtlWork->flags & BTL_FLAG_RELOAD_CHARGING) {
        return;
    }
    t = gRikuBtlWork->listSwitchTimer;

    if ((s16)t > 0) {
        gRikuBtlWork->listSwitchTimer = t - 1;

        if (gRikuBtlWork->listSwitchTimer == 0) {
            RequestSwitchRikuCardList();
        }
        return;
    }
    keys = gBtlWork->rikuKeys;
    gBtlWork->rikuKeys = 0;

    if (keys & 1) {
        RequestRikuNextCard();
    }

    if (keys & 2) {
        RequestRikuPrevCard();
    }

    if (keys & 4) {
        RequestSwitchRikuCardList();
    }

    if (c->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_BUSY) {
        return;
    }

    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }

    if (c->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }

    if (keys & 0x10) {
        if (GetRikuStockCount() > 2) {
            RequestRikuStockUse();
        } else {
            RequestRikuCardStock();
        }
    }

    if (keys & 0x20) {
        RequestRikuCardUse();

        if (GetRikuCardListIndex() == 3 && !IsRikuSelectionEmpty()) {
            gRikuBtlWork->listSwitchTimer = 15;
        }
    }
}

#ifdef VERSION_EU
void eu_08013190(void) {
    BtlObj* c = gRikuBtlWork->actor;
    u8 keys;

    keys = gBtlWork->rikuKeys;
    gBtlWork->rikuKeys = 0;
    if (c->flags & BTLOBJ_FLAG_CARD_USE_BLOCKED) {
        return;
    }
    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return;
    }
    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_BUSY) {
        return;
    }
    if (gBtlWork->flags & BTL_FLAG_CARD_BREAK) {
        return;
    }
    if (c->flags & BTLOBJ_FLAG_DAMAGE_PENDING) {
        return;
    }
    if (keys & 0x20) {
        RequestRikuCardUse();
    }
}
#endif

void HumFaceTarget(HumWork* p, u16 n) {
    s32 v;
    GetEnemyTargetPosition(&p->actor, &v, 0, 0);

    if (GetRandom() % n == 0) {
        if (p->actor.x > v) {
            p->actor.flags |= BTLOBJ_FLAG_FACING_LEFT;
        } else {
            p->actor.flags &= ~BTLOBJ_FLAG_FACING_LEFT;
        }
    }
}

u8 HumMoveToward(HumWork* p, s32 x, s32 y, s32 spd) {
    u8 ang = GetAngle(p->actor.x, p->actor.y, x, y);

    p->actor.x += gSineTable[ang] * spd >> 8;
    p->actor.y += -gSineTable[ang + 64] * spd >> 8;

    if (p->actor.x - x >= 0 ? p->actor.x - x > 0x1E00 : x - p->actor.x > 0x1E00) {
        return 0;
    }

    if (p->actor.y - y >= 0 ? p->actor.y - y > 0x1000 : y - p->actor.y > 0x1000) {
        return 0;
    }
    return 1;
}

u8 HumIsTargetInReach(HumWork* p, s16 a, u16 b, u16 r) {
    s32 v0;
    s32 v1;
    BtlObj* c = &p->actor;
    s32 d;
    s32 t;
    s32 bb;
    s32 rr;

    GetEnemyTargetPosition(c, &v0, &v1, 0);
    rr = r << 8;
    d = c->y - v1;

    if (d >= 0 ? d > rr : v1 - c->y > rr) {
        return 0;
    }

    if (c->flags & BTLOBJ_FLAG_FACING_LEFT) {
        t = c->x - (a << 8);
        bb = b << 8;

        if (t - bb > v0) {
            return 0;
        }

        if (t + bb < v0) {
            return 0;
        }
    } else {
        t = c->x + (a << 8);
        bb = b << 8;

        if (t + bb < v0) {
            return 0;
        }

        if (t - bb > v0) {
            return 0;
        }
    }
    return 1;
}

u8 HumIsNearAreaEdge(HumWork* p, u16 b) {
    if (p->actor.x < (gBtlWork->xMin + b) << 8) {
        return 1;
    }

    if (p->actor.x > (gBtlWork->xMax - b) << 8) {
        return 1;
    }
    return 0;
}

u8 HumIsInPlayerReach(HumWork* p, s16 a, u16 b, u16 r) {
    s32 v0;
    s32 v1;
    BtlObj* c = &p->actor;
    BtlObj* o = gBtlWork->actor;
    s32 d;
    s32 t;
    s32 bb;
    s32 rr;

    GetEnemyTargetPosition(c, &v0, &v1, 0);
    rr = r << 8;
    d = c->y - v1;

    if (d >= 0 ? d > rr : v1 - c->y > rr) {
        return 0;
    }

    if (o->flags & BTLOBJ_FLAG_FACING_LEFT) {
        t = v0 - (a << 8);
        bb = b << 8;

        if (t - bb > c->x) {
            return 0;
        }

        if (t + bb < c->x) {
            return 0;
        }
    } else {
        t = v0 + (a << 8);
        bb = b << 8;

        if (t + bb < c->x) {
            return 0;
        }

        if (t - bb > c->x) {
            return 0;
        }
    }
    return 1;
}

u8 HumChooseCardAction(HumWork* work, u16 interval, u16 offset, u16 width, u16 depth) {
    u32 value;
    u32 cards;
    u32 id;
    s32 count;
    s32 n;

    if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
        return 0;
    }
    if ((s16)gRikuBtlWork->listSwitchTimer > 0) {
        return 0;
    }
    if ((u16)((u32)GetRandom() % interval) != 0) {
        return 0;
    }
    value = GetRikuSelectedCardValue();
    cards = GetRikuStockCount();
    id = GetRikuSelectedMove();
    count = GetRikuCardsLeft();
    switch (id) {
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
        n = count >> 1;
        if (n <= 0) {
            n = 1;
        }
        if (GetRandom() % n == 0) {
            gBtlWork->rikuKeys |= 0x20;
        } else {
            gBtlWork->rikuKeys |= 1;
        }
        return 0;
    }
    if (IsRikuReloadCardSelected()) {
        if (count > 1 && (u16)(GetRandom() % 20U) == 0) {
            gBtlWork->rikuKeys |= 1;
        }
        return 0;
    }
    if (GetRikuCardListIndex() == 3) {
        if ((GetRandom() & 3) == 0) {
            if (count <= 0) {
                work->flags |= 0x10;
                gBtlWork->rikuKeys |= 4;
            } else {
                gBtlWork->rikuKeys |= 0x20;
                if (count == 1) {
                    work->flags |= 0x10;
                }
            }
        } else if (count > 1) {
            gBtlWork->rikuKeys |= 1;
        }
        return 0;
    }
    if (!(work->flags & 0x10) && gRikuBtlWork->hcEffect == 0
        && (u16)(GetRandom() % 60U) == 0) {
        gBtlWork->rikuKeys |= 4;
        return 0;
    }
    if (cards > 2) {
        if ((u16)(GetRandom() % 6U) == 0) {
            gBtlWork->rikuKeys |= 0x10;
            return 1;
        }
    } else if (GetRandom() % 2 == 0) {
        if (count <= 1 && cards != 0) {
            gBtlWork->rikuKeys |= 0x10;
            return 1;
        }
        // @bug unk_184 is NULL for humanoid bosses without a card table (NULL read).
        if (value == 0 || work->stockMoves[cards] != id) {
            gBtlWork->rikuKeys |= 1;
        } else {
            gBtlWork->rikuKeys |= 0x10;
        }
        return 0;
    }
    if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
        if (HumIsTargetInReach(work, (s16)offset, width, depth)) {
            if (GetActiveCardValue() <= value || value == 0) {
                gBtlWork->rikuKeys |= 0x20;
            }
        } else if (GetActiveCardValue() == value) {
            gBtlWork->rikuKeys |= 0x20;
        }
    } else if (HumIsTargetInReach(work, (s16)offset, width, depth)) {
        gBtlWork->rikuKeys |= 0x20;
    }
    return 0;
}
s32 HumResolveCardMove(HumWork* work) {
    s32 buf[6];
    s32 id = ResolveActiveCardsMove(buf);

    if (id == 145) {
        if (!(gRikuBtlWork->flags & BTL_FLAG_STOCK_SEQUENCE)) {
            gRikuBtlWork->flags |= BTL_FLAG_STOCK_SEQUENCE;
            gRikuBtlWork->stockMove = 0;
        }
        id = buf[gRikuBtlWork->stockMove];
        gRikuBtlWork->stockMove++;
    }
    work->stateTimer = 0;

    switch (id) {
    case 47:
        work->state = 18;
        work->itemIndex = 0;
        break;
    case 48:
        work->state = 18;
        work->itemIndex = 1;
        break;
    case 49:
        work->state = 18;
        work->itemIndex = 2;
        break;
    case 50:
        work->state = 18;
        work->itemIndex = 3;
        break;
    case 51:
        work->state = 18;
        work->itemIndex = 4;
        break;
    case 52:
        work->state = 18;
        work->itemIndex = 5;
        break;
    case 53:
        work->state = 18;
        work->itemIndex = 6;
        break;
    }
    return id;
}
