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
#include "card.h"
#include "card_message_assets.h"
#include <stddef.h>
#include "game.h"
#include "bos4_api.h"
#include "sprites_card_pictures.h"
#include "songs.h"

s16 gBossCardValue;

u8 gUnk_02034AB6[2];
#ifdef VERSION_EU
u8 gUnkEu_02034AD4[4];
#endif

u8 func_0809075C(CardDisplayWork* p, void* a);
u8 func_08090808(CardDisplayWork* p, void* a);
u8 func_08090940(CardDisplayWork* p);

static const s32 sEnemyCardLayout[10] = {
    0x11000, 0xBC00, 0xDC00, 0x5800, 0xDC00, 0x4400, 0xDC00, 0x3000, 0x10400, 0xB800,
};

void LookupEnemyCardDef(CardDisplayArgs* a, CardDef** b, u8 c) {
    CardSlot* t;
    s32 v;
    s32 id;

    t = a->slot;
    v = a->unk_08;

    if (v != -1) {
        ((CardDisplayWork*)((u8*)b - offsetof(CardDisplayWork, cardDef)))->enemyKind = v;
    }

    if (t != 0) {
        id = t[c].cardId;

        if (id != 0xFFFF) {
            *b = &gCardDefs[id];
        }
    }
}
void LinkEnemyCardDisplay(CardDisplayWork* p) {
    ListNodeInit(&p->node, p->args.pool, p);
    ListPoolAppend(&p->node, p->args.pool);
}

void card_enemy_0(CardDisplayWork* p, CardDisplayArgs* a) {
    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->palette = 0;
    p->command = 0;
    p->args = *a;
    p->flags = 0;
    p->priority = 0x50;
    p->timer = 0;
    LookupEnemyCardDef(&p->args, &p->cardDef, p->args.index);
    p->scaleX = 0x100;
    p->scaleY = 0x100;
    p->bobAngle = GetRandom();
    p->angle = 0;
    p->unk_84 = 0;
    p->unk_88 = 0x2400;
    p->unk_8C = sEnemyCardLayout[0];
    p->unk_90 = sEnemyCardLayout[1];
    p->x = 0xDC00;
    p->y = 0x8400;
    p->value = p->cardDef->value;
    LinkEnemyCardDisplay(p);
}

u8 card_enemy_1(CardDisplayWork* p, void* a) {
    if (!(p->flags & 0x800)) {
        if (p->flags & 0x80) {
            ReleaseCardDisplayGfx(p);
            p->flags &= ~0x80;
            p->flags |= 1;
        }
    }

    UpdateCardDisplayFlip(p);

    if (p->flags & 0x10) {
        p->timer = 8;
        SetTaskUpdate(a, (TaskUpdateFunc)func_0809075C);
    } else if (!(p->flags & 0x1000)) {
        UpdateEnemyCardRingPosition(p);
        p->bobAngle += 4;
        DispatchEnemyCardCommand(p, a);

        if (!(p->flags & 0x20)) {
            p->flags &= ~0x40;
            SetTaskUpdate(a, (TaskUpdateFunc)func_08090808);
        }
    }

    return 1;
}

void EnemyCardDraw(CardDisplayWork* p) {
    void* gfx;
    ObjAffine* affine;
    u16 flags;

    gfx = p->cardDef->gfx;

    if (p->flags & 0x800) {
        if (!(p->flags & 1)) {
            if (p->flags & 0x80) {
                if ((p->flags & 8) == 0) {
                    affine = AllocObjAffine(p->angle, p->scaleX, p->scaleY, 0);
                } else {
                    affine = AllocObjAffine(p->angle, p->scaleX, p->scaleY, 1);
                }

                flags = 0x410;
                DrawSprite(p->x >> 8, (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
                           gEnemyCardBacks[0].gfx, gCardBattleState->tiles[p->cardDef->category],
                           gCardBattleState->palette, affine, flags, (u16)(p->priority - 1));
                DrawSprite(p->x >> 8, (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
                           gfx, p->tiles, p->palette, affine, flags, p->priority);

                if (p->valueModified != 0) {
                    DrawSprite(p->x >> 8, (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
                               gUnk_09EE981C[p->value], gCardBattleState->tiles7,
                               gCardBattleState->palette2, affine, flags, (u16)(p->priority - 2));
                } else {
                    DrawSprite(p->x >> 8, (p->y >> 8) + (gSineTable[p->bobAngle] >> 8),
                               gUnk_09EE981C[p->value], gCardBattleState->tiles5,
                               gCardBattleState->palette, affine, flags, (u16)(p->priority - 2));
                }
            }
        }
    }
}
void EnemyCardDestroy(CardDisplayWork* p) {
    if (p->tiles != 0) {
        ReleaseCardDisplayGfx(p);
    }

    if (p->palette2 != 0) {
        ReleaseObjPalette(p->palette2);
    }
}

u8 func_08090550(CardDisplayWork* p, void* a) {
    if (gBtlWork->flags & 0x20) {
        p->timer = 8;
        p->unk_9E = 8;
        gCardBattleState->activeCardCount = 0;
        gCardBattleState->activeValue = 0;
        gBtlWork->flags &= ~0x20;
        gBtlWork->flags &= ~0x80;
        gBtlWork->flags &= ~0x10000000;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090940);
    } else if (p->flags & 0x200000) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = (u16)(GetRandom() % 33) - 16;
        p->unk_9E = GetRandom() % 5 + 254;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090DB0);
    }

    return 1;
}

u8 EnemyUsecard_1(CardDisplayWork* p, void* a) {
    p->priority = 80;
    ApproachValue(&p->x, 0x7800, p->timer);
    ApproachValue(&p->y, 0x8400, p->timer);

    if ((s16)p->timer > 0) {
        p->timer--;
    }

    if (gBtlWork->flags & 0x80) {
        if (p->flags & 0x2000) {
            if ((s16)p->timer == 0) {
                SetTaskUpdate(a, (TaskUpdateFunc)func_08090550);
            }
        } else if ((s16)p->timer <= 2) {
            p->priority -= 4;
            p->unk_84 = 0x500;
            p->timer = 0x100;
            p->unk_7C = (u16)(GetRandom() % 33) - 16;
            p->unk_9E = GetRandom() % 5 + 254;
            SetTaskUpdate(a, (TaskUpdateFunc)func_080909A4);
            return 1;
        }
    } else if ((s16)p->timer <= 2) {
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = (u16)(GetRandom() % 33) - 16;
        p->unk_9E = GetRandom() % 5 + 254;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080909A4);
    }

    return 1;
}

u8 func_0809075C(CardDisplayWork* p, void* a) {
    ApproachValue(&p->x, gSineTable[((p->unk_7C >> 8) - 32) & 0xFF] * (p->unk_84 >> 8) + sEnemyCardLayout[0],
                  p->timer);
    ApproachValue(&p->y, -gSineTable[(((p->unk_7C >> 8) - 32) & 0xFF) + 0x40] * (p->unk_84 >> 8) + sEnemyCardLayout[1],
                  p->timer);
    p->timer--;

    if ((s16)p->timer <= 1) {
        p->timer = 0;
        p->flags &= ~0x10;
        SetTaskUpdate(a, (TaskUpdateFunc)card_enemy_1);
    }

    return 1;
}

u8 func_08090808(CardDisplayWork* p, void* a) {
    if (p->command == 7) {
        return 0;
    }

    p->unk_84 += -p->unk_84 >> 1;
    p->x += (sEnemyCardLayout[8] - p->x) >> 1;
    p->y += (sEnemyCardLayout[9] - p->y) >> 1;

    if (p->flags & 0x20) {
        SetTaskUpdate(a, (TaskUpdateFunc)card_enemy_1);
    }

    return 1;
}

void UpdateEnemyCardRingPosition(CardDisplayWork* p) {
    s32 t;

    if (p->unk_80 - p->unk_7C > 0x7F00) {
        p->unk_7C += 0x10000;
    }

    t = p->unk_7C - 0x10000;

    if (p->unk_80 - t < p->unk_7C - p->unk_80) {
        p->unk_7C = t;
    }

    p->swingAngle += (p->swingAngleTarget - p->swingAngle) >> 2;
    p->unk_84 += (p->unk_88 - p->unk_84) >> 1;
    ApproachValue(&p->unk_7C, p->unk_80, p->timer);
    p->timer--;

    if ((s16)p->timer <= 1) {
        p->timer = 0;
        p->flags |= 0x40;
    } else {
        p->flags &= ~0x40;
    }

    p->x = gSineTable[((p->unk_7C >> 8) - 32) & 0xFF] * (p->unk_84 >> 8) + p->unk_8C;
    p->y = -gSineTable[(((p->unk_7C >> 8) - 32) & 0xFF) + 64] * (p->unk_84 >> 8) + p->unk_90;
}

u8 func_08090940(CardDisplayWork* p) {
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

u8 func_080909A4(CardDisplayWork* p) {
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
        p->flags &= ~0x80;
        gBtlWork->flags &= ~0x10000000;
        return 0;
    }

    return 1;
}

void func_08090A54(CardDisplayWork* p, void* a) {
    p->x -= gSineTable[p->unk_9E] * 3;
    UpdateCardDisplayFlip(p);

    if (p->unk_9E != 0) {
        p->unk_9E -= 8;
    } else {
        p->unk_9E = 0;
        p->flags &= ~0x800;
        SetTaskUpdate(a, (TaskUpdateFunc)card_enemy_1);
    }

    if (!(p->flags & 0x20)) {
        p->flags &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090808);
    }
}

void func_08090ACC(CardDisplayWork* p, void* a) {
    p->x += gSineTable[p->unk_9E] * 3;
    UpdateCardDisplayFlip(p);

    if ((s8)p->unk_9E >= 0) {
        p->unk_9E += 8;
    } else {
        p->unk_9E = 0x80;
        p->flags &= ~4;
        p->priority = 100;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090A54);
    }

    if (!(p->flags & 0x20)) {
        p->flags &= ~0x40;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090808);
    }
}

void DispatchEnemyCardCommand(CardDisplayWork* p, void* a) {
    switch (p->command) {
    case 5:
        p->timer = 16;
        p->priority -= 4;
        SetTaskUpdate(a, (TaskUpdateFunc)EnemyUsecard_1);
        break;
    case 6:
        p->timer = 8;
        p->priority -= 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090C3C);
        break;
    case 8:
        p->priority -= 4;
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = (u16)(GetRandom() % 33) - 16;
        p->unk_9E = GetRandom() % 5 + 254;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080909A4);
        break;
    case 7:
        p->unk_84 = 0x500;
        p->timer = 0x100;
        p->unk_7C = (u16)(GetRandom() % 33) - 16;
        p->unk_9E = GetRandom() % 5 + 254;
        SetTaskUpdate(a, (TaskUpdateFunc)func_080909A4);
        break;
    case 9:
        p->unk_9E = 0;
        p->priority -= 4;
        SetTaskUpdate(a, (TaskUpdateFunc)func_08090ACC);
        p->command = 0;
        break;
    }
}

u8 func_08090C3C(CardDisplayWork* p, void* a) {
    s32 (*tbl)[2]; s32* q;

    if (gBtlWork->paused == 1) {
        return 1;
    }

    UpdateCardDisplayFlip(p);

    if (p->flags & 0x20) {
        q = &p->x; tbl = (s32 (*)[2])sEnemyCardLayout; ApproachValue(q, tbl[3 - p->stockIndex][0], p->timer); ApproachValue(&p->y, ((s32 (*)[2])sEnemyCardLayout)[3 - p->stockIndex][1], p->timer);
    } else {
        ApproachValue(&p->x, sEnemyCardLayout[8], p->timer);
        ApproachValue(&p->y, sEnemyCardLayout[9], p->timer);
    }

    if ((s16)p->timer > 0) {
        p->timer--;
        p->flags &= ~0x40;
    } else {
        p->timer = 0;
        p->flags |= 0x40;
    }

    if (p->command == 5) {
        if (!(gBtlWork->flags & 0x80) && p->stockIndex == 0) {
            gBtlWork->flags |= 0x80;
        }

        if (p->flags & 0x8000) {
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807CF4C);
        } else {
            p->timer = 15;
            p->unk_88 = 0x800;
            p->unk_84 = 0;
            p->unk_80 = gPlayedCardAngles[p->stockIndex] * 2;
            p->unk_7C = 0;
            p->unk_8C = p->x;
            p->unk_90 = p->y;
            SetTaskUpdate(a, (TaskUpdateFunc)func_0807CFA8);
        }
    }

    p->bobAngle += 4;
    return 1;
}
u8 func_08090DB0(CardDisplayWork* p, void* a) {
    p->command = 0;
    p->y -= p->unk_84;
    p->unk_84 -= (s16)p->timer >> 1;
    p->timer++;
    p->x += 0x200;
    p->angle += 16;

    if (!(p->flags & 0x400000)) {
        p->scaleX -= 20;

        if (p->scaleX >= -2 && p->scaleX <= 2) {
            p->scaleX = -20;
        }

        if (p->scaleX <= -0x100) {
            p->scaleX = -0x100;
            p->flags |= 0x400000;
        }
    } else {
        p->scaleX -= 20;

        if (p->scaleX >= -2 && p->scaleX <= 2) {
            p->scaleX = 20;
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
void func_08090EA0(CardDisplayWork* p, CardDisplayArgs* a) {
    const s32* tbl;
    u8 n;
    s32 id;

    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->tiles4 = 0;
    p->tiles5 = 0;
    p->palette2 = 0;
    p->palette = 0;
    p->children = 0;
    p->command = 0;
    p->args = *a;
    p->flags = 0;
    p->priority = 50;
    p->timer = 0;
    tbl = gEnemyCardIds[p->args.unk_08];
    n = gEnemyCardCounts[p->args.unk_08];
    p->enemyKind = p->args.unk_08;

    if (n == 1) {
        id = tbl[0];
    } else if ((s16)p->args.index != -1) {
        if ((s16)p->args.index > n) {
            id = tbl[GetRandom() % n];
        } else {
            id = tbl[(s16)p->args.index - 1];
        }
    } else {
        if (gCardBattleState->nextEnemyCardIndex > n) {
            gCardBattleState->nextEnemyCardIndex = n;
        }

        id = tbl[gCardBattleState->nextEnemyCardIndex];
        gCardBattleState->nextEnemyCardIndex = GetRandom() % n;
    }

    p->cardDef = &gCardDefs[id];
    p->scaleX = 0x100;
    p->scaleY = 0x100;
    p->bobAngle = GetRandom();
    p->angle = 0;
    p->unk_84 = 0;
    p->unk_88 = 0x2400;
    p->flags |= 0x804;
    p->unk_8C = 0xDC00;
    p->unk_90 = 0x8800;
    p->x = 0xDC00;
    p->y = 0x8800;
    p->timer = 10;
    p->priority -= 4;
    LoadCardDisplayGfx(p);
    p->value = p->cardDef->value;
    switch (gGameState.roomEffect) {
    case 1:
        p->value += 2;

        if (p->value > 9) {
            p->value = 9;
        }

        p->valueModified = 1;
        break;
    case 2:
        if (p->value > 2) {
            p->value -= 2;
        } else {
            p->value = 1;
        }
        p->valueModified = 1;
        break;
    default:
        p->valueModified = 0;
        break;
    }

    p->flags |= 0x80;
}

void func_08091048(CardDisplayWork* p, CardDisplayArgs* a) {
    const s32* tbl;
    u8 n;
    s32 id;

    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->palette = 0;
    p->command = 0;
    p->args = *a;
    p->flags = 0;
    p->priority = 50;
    p->timer = 0;
    tbl = gEnemyCardIds[p->args.unk_08];
    n = gEnemyCardCounts[p->args.unk_08];
    p->enemyKind = p->args.unk_08;

    if (n == 1) {
        id = tbl[0];
    } else if ((s16)p->args.index < n) {
        id = tbl[(s16)p->args.index];
    } else {
        id = tbl[GetRandom() % n];
    }

    p->cardDef = &gCardDefs[id];
    p->scaleX = 0x100;
    p->scaleY = 0x100;
    p->bobAngle = GetRandom();
    p->angle = 0;
    p->unk_84 = 0;
    p->unk_88 = 0x2400;
    p->flags |= 0x801;
    p->unk_8C = 0x10000;
    p->unk_90 = 0x8800;
    p->x = 0x10000;
    p->y = 0x8800;
    p->timer = 0x10;
    p->priority -= 4;
    p->value = p->cardDef->value;
}
void func_08091138(CardDisplayWork* p, CardDisplayArgs* a) {
    const s32* tbl;
    u8 n;
    s32 id;

    p->tiles = 0;
    p->tiles2 = 0;
    p->tiles3 = 0;
    p->palette = 0;
    p->command = 0;
    p->args = *a;
    p->flags = 0;
    p->priority = 50;
    p->timer = 0;
    tbl = gEnemyCardIds[p->args.unk_08];
    n = gEnemyCardCounts[p->args.unk_08];
    p->enemyKind = p->args.unk_08;

    if (n == 1) {
        id = tbl[0];
    } else if ((s16)p->args.index < n) {
        id = tbl[GetRandom() % (s16)p->args.index];
    } else {
        id = tbl[GetRandom() % n];
    }

    p->cardDef = &gCardDefs[id];
    p->scaleX = 0x100;
    p->scaleY = 0x100;
    p->bobAngle = GetRandom();
    p->angle = 0;
    p->unk_84 = 0;
    p->unk_88 = 0x2400;
    p->flags |= 0x801;
    p->unk_8C = 0x10000;
    p->unk_90 = 0x8800;
    p->x = 0x10000;
    p->y = 0x8800;
    p->timer = 0x10;
    p->priority -= 4;
    p->value = p->cardDef->value;
}

void UseEnemyCard(u16 arg) {
    CardDisplayArgs args;
    CardDisplayWork* p;
    u8 i;
    u8 flag;
    u8 found;
#ifdef VERSION_EU
    s32 j;
    s32 k;
#endif

    args.pool = 0;
    args.slot = 0;
    args.unk_08 = arg;
    args.index = gBossCardValue;
    args.listIndex = 0;
    p = TaskCreate(&gCardBattleState->tasks, &gTaskDescEnemyUsecard, &args)->work;
    gBtlWork->flags |= 0x10000000;
    gCardBattleState->enemyCardUsed = 1;

    if ((gBtlWork->flags & 0x80) == 0) {
        p->flags |= 0x2000;
        gCardBattleState->activeCards[0] = p;
        gCardBattleState->activeValue = p->value;
        gCardBattleState->activeCardCount = 1;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
    } else if ((gBtlWork->flags & 0x20) == 0) {
#ifdef VERSION_EU
        if ((s16)gCardBattleState->activeValue <= p->value || p->value == 0) {
#else
        if ((s16)gCardBattleState->activeValue <= p->value) {
#endif
            found = 0;

            if (gBtlWork->hcEffect == 2) {
#ifdef VERSION_EU
                if (gCardBattleState->activeCards[0]->cardDef->category == 0 && gCardBattleState->soraStockActive == 0) {
                    found = 1;
                }
#else
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    if (gCardBattleState->activeCards[i]->cardDef->category == 0) {
                        found = 1;
                        break;
                    }
                }
#endif
            }

            if (gBtlWork->hcEffect == 20) {
#ifdef VERSION_EU
                for (j = 0; j < gCardBattleState->activeCardCount; j++) {
                    if (gCardBattleState->activeCards[j]->cardDef->move == 22) {
                        found = 1;
                    }
                }
#else
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    if (gCardBattleState->activeCards[i]->cardDef->move == 22) {
                        found = 1;
                        break;
                    }
                }
#endif
            }

            if (gBtlWork->hcEffect == 29) {
#ifdef VERSION_EU
                for (k = 0; k < gCardBattleState->activeCardCount; k++) {
                    if (gCardBattleState->activeCards[k]->cardDef->category == 2 && !(gCardBattleState->activeCards[k]->cardDef->flags & 8)) {
                        found = 1;
                    }
                }
#else
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    if (gCardBattleState->activeCards[i]->cardDef->category == 2) {
                        found = 1;
                        break;
                    }
                }
#endif
            }

            if (found == 0) {
                gBtlWork->flags |= 0x800000;

                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    gCardBattleState->activeCards[i]->flags |= 0x200000;
                }

                if ((s16)gCardBattleState->activeValue != p->value) {
                    if (p->value == 0) {
                        gBtlWork->breakDifference = -(s8)gCardBattleState->activeValue;
                    } else {
                        gBtlWork->breakDifference = gCardBattleState->activeValue - p->value;
                    }

                    m4aSongNumStart(SONG_SYS_CARDLOSE);
                    gBtlWork->flags |= 0x400;
                    gBtlWork->flags |= 0x80;
                    gBtlWork->flags &= ~0x20;
                    gCardBattleState->activeCards[0] = p;

                    if (gBtlWork->hcEffect == 48) {
                        if (p->value != 0) {
                            gCardBattleState->activeValue = p->value - gCardBattleState->activeValue;
                            p->value = gCardBattleState->activeValue;
                        } else {
                            gCardBattleState->activeValue = 0;
                        }

                        if ((s16)gCardBattleState->activeValue < 0) {
                            gCardBattleState->activeValue = 0;
                        }

                        gBtlWork->hcEffectCount--;
                    } else {
                        gCardBattleState->activeValue = p->value;
                    }

                    gCardBattleState->activeCardCount = 1;
                    gBtlWork->soraOwnsPlay = 0;
                    p->flags |= 0x2000;
                    AddBreakDarkPoints();
                } else {
                    m4aSongNumStart(SONG_SYS_DROW);
                    gBtlWork->flags &= ~0x80;
                    gBtlWork->flags &= ~0x20;
                    gBtlWork->flags &= ~0x400;
                    gBtlWork->soraOwnsPlay = 0;
                }
            }
        }
    } else {
#ifdef VERSION_EU
        if ((s16)gCardBattleState->activeValue <= p->value || p->value == 0) {
#else
        if ((s16)gCardBattleState->activeValue <= p->value) {
#endif
            flag = 0;

            if (gBtlWork->hcEffect == 2) {
#ifdef VERSION_EU
                if (gCardBattleState->activeCards[0]->cardDef->category == 0 && gCardBattleState->soraStockActive == 0) {
                    flag = 1;
                }
#else
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    if (gCardBattleState->activeCards[i]->cardDef->category == 0) {
                        flag = 1;
                        break;
                    }
                }
#endif
            }

#ifndef VERSION_EU
            if (gBtlWork->hcEffect == 54) {
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    if (gCardBattleState->activeCards[i]->cardDef->category == 1) {
                        flag = 1;
                        break;
                    }
                }
            }

#endif
            if (gBtlWork->hcEffect == 20) {
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    if (gCardBattleState->activeCards[i]->cardDef->move == 22) {
                        flag = 1;
                        break;
                    }
                }
            }

            if (gBtlWork->hcEffect == 29) {
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
#ifdef VERSION_EU
                    if (gCardBattleState->activeCards[i]->cardDef->category == 2 && !(gCardBattleState->activeCards[i]->cardDef->flags & 8)) {
#else
                    if (gCardBattleState->activeCards[i]->cardDef->category == 2) {
#endif
                        flag = 1;
                        break;
                    }
                }
            }

            if (flag == 0) {
                gBtlWork->flags |= 0x800000;

                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    gCardBattleState->activeCards[i]->flags |= 0x200000;
                }

                if ((s16)gCardBattleState->activeValue != p->value) {
                    if (p->value == 0) {
                        gBtlWork->breakDifference = -(s8)gCardBattleState->activeValue;
                    } else {
                        gBtlWork->breakDifference = gCardBattleState->activeValue - p->value;
                    }

                    m4aSongNumStart(SONG_SYS_CARDLOSE);
                    gBtlWork->flags |= 0x400;
                    gBtlWork->flags |= 0x80;
                    gBtlWork->flags &= ~0x20;
                    gCardBattleState->activeCards[0] = p;
#ifdef VERSION_EU

                    if (gBtlWork->hcEffect == 48) {
                        if (p->value != 0) {
                            gCardBattleState->activeValue = p->value - gCardBattleState->activeValue;
                            p->value = gCardBattleState->activeValue;
                        } else {
                            gCardBattleState->activeValue = 0;
                        }

                        if ((s16)gCardBattleState->activeValue < 0) {
                            gCardBattleState->activeValue = 0;
                        }

                        gBtlWork->hcEffectCount--;
                    } else {
                        gCardBattleState->activeValue = p->value;
                    }

#else
                    gCardBattleState->activeValue = p->value;
#endif
                    gCardBattleState->activeCardCount = 1;
                    gBtlWork->soraOwnsPlay = 0;
                    p->flags |= 0x2000;
                    AddBreakDarkPoints();
                } else {
                    m4aSongNumStart(SONG_SYS_DROW);
                    gBtlWork->flags &= ~0x80;
                    gBtlWork->flags &= ~0x20;
                    gBtlWork->flags &= ~0x400;
                    gBtlWork->soraOwnsPlay = 0;
                }
            }
        }
    }

    p->flags = (p->flags | 4) & ~0x40;
}

void func_080917C8(u16 a, u8 b) {
    CardDisplayArgs arg;
    CardDisplayWork* p;
    u8 i;

    arg.pool = 0;
    arg.slot = 0;
    arg.unk_08 = a;
    arg.index = b;
    arg.listIndex = 0;
    p = TaskCreate(&gCardBattleState->tasks, &gUnk_09EE4B70, &arg)->work;
    gBtlWork->flags |= 0x10000000;

    if ((gBtlWork->flags & 0x80) == 0) {
        p->flags |= 0x2000;
        gCardBattleState->activeCards[0] = p;
        gCardBattleState->activeValue = p->cardDef->value;
        gCardBattleState->activeCardCount = 1;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
    } else if ((gBtlWork->flags & 0x20) == 0) {
        if (gCardBattleState->soraHcEffect != 2) {
            if ((s16)gCardBattleState->activeValue < p->cardDef->value) {
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    gCardBattleState->activeCards[i]->flags |= 0x200000;
                }

                m4aSongNumStart(SONG_SYS_CARDLOSE);
                gBtlWork->flags |= 0x800000;
                gBtlWork->flags |= 0x400;
                gBtlWork->flags |= 0x80;
                gCardBattleState->activeCards[0] = p;
                gCardBattleState->activeValue = p->cardDef->value;
                gCardBattleState->activeCardCount = 1;
                gBtlWork->soraOwnsPlay = 0;
                p->flags |= 0x2000;
            }
        }
    }

    p->flags |= 4;
    p->flags &= ~0x40;
}

void func_08091978(u16 a, u8 b) {
    CardDisplayArgs arg;
    CardDisplayWork* p;
    u8 i;

    arg.pool = 0;
    arg.slot = 0;
    arg.unk_08 = a;
    arg.index = b;
    arg.listIndex = 0;
    p = TaskCreate(&gCardBattleState->tasks, &gUnk_09EE4B88, &arg)->work;
    gBtlWork->flags |= 0x10000000;

    if ((gBtlWork->flags & 0x80) == 0) {
        p->flags |= 0x2000;
        gCardBattleState->activeCards[0] = p;
        gCardBattleState->activeValue = p->cardDef->value;
        gCardBattleState->activeCardCount = 1;
        gBtlWork->soraOwnsPlay = 0;
        gBtlWork->flags |= 0x400;
        gBtlWork->flags |= 0x80;
    } else if (gBtlWork->flags & 0x20) {
        if (gBtlWork->hcEffect == 2) {
            if ((s16)gCardBattleState->activeValue < p->cardDef->value) {
                for (i = 0; i < gCardBattleState->activeCardCount; i++) {
                    gCardBattleState->activeCards[i]->flags |= 0x200000;
                }

                m4aSongNumStart(SONG_SYS_CARDLOSE);
                gBtlWork->flags |= 0x800000;
                gBtlWork->flags |= 0x400;
                gBtlWork->flags |= 0x80;
                gCardBattleState->activeCards[0] = p;
                gCardBattleState->activeValue = p->cardDef->value;
                gCardBattleState->activeCardCount = 1;
                gBtlWork->soraOwnsPlay = 0;
                p->flags |= 0x2000;
            }
        }
    }

    p->flags |= 4;
    p->flags &= ~0x40;
}
void ResetBossCardValue(void) {
    gBossCardValue = -1;
}

void SetBossCardValue(u16 a) {
    gBossCardValue = a;
}
u16 GetBossCardValue(void) {
    if (gBossCardValue != -1) {
        return gBossCardValue;
    }

    return gCardBattleState->nextEnemyCardIndex;
}

TaskDesc gTaskDescCardEnemy = {
    "card_enemy",
    (TaskInitFunc)card_enemy_0,
    (TaskUpdateFunc)card_enemy_1,
    (TaskDrawFunc)EnemyCardDraw,
    (TaskDestroyFunc)EnemyCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gTaskDescEnemyUsecard = {
    "EnemyUsecard",
    (TaskInitFunc)func_08090EA0,
    (TaskUpdateFunc)EnemyUsecard_1,
    (TaskDrawFunc)EnemyCardDraw,
    (TaskDestroyFunc)EnemyCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gUnk_09EE4B70 = {
    "EnemyUsecard",
    (TaskInitFunc)func_08091048,
    (TaskUpdateFunc)EnemyUsecard_1,
    (TaskDrawFunc)EnemyCardDraw,
    (TaskDestroyFunc)EnemyCardDestroy,
    sizeof(CardDisplayWork),
};

TaskDesc gUnk_09EE4B88 = {
    "EnemyUsecard",
    (TaskInitFunc)func_08091138,
    (TaskUpdateFunc)EnemyUsecard_1,
    (TaskDrawFunc)EnemyCardDraw,
    (TaskDestroyFunc)EnemyCardDestroy,
    sizeof(CardDisplayWork),
};
