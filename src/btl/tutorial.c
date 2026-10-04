#include "tutorial.h"
#include "gba/keys.h"
#include "sprites_btl_hud.h"
#include "system_state.h"
#include "anim.h"
#include "battle_work.h"
#include "btl4.h"
#include "btl_effect.h"
#include "card_api.h"
#include "card_battle.h"
#include "display.h"
#include "engine_math.h"
#include "game.h"
#include "gba/io_reg.h"
#include "key.h"
#include "obj.h"
#include "obj_api.h"
#include <stddef.h>
#include "taskpool.h"
#include "types.h"

void TutorialOpenMessage(u16 a) {
    gDispCnt = (gDispCnt & ~DISPCNT_MODE_MASK) | DISPCNT_MODE_1;
    CreateCardMessageTask(&gBtlWork->taskPools[1], 0, a);
}

void TutorialOpenPersistentMessage(u16 a) {
    CreatePersistentSysmsgwinTask(&gBtlWork->taskPools[1], a);
}

void TutorialRestoreBgMode() {
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

void TutorialCloseMessage() {
    CloseMessageWindow();
}

void TutorialWait(TutorialWork* p, u16 b, u32 c) {
    p->timer = 0;
    p->state = 0;
    p->nextState = c;
    p->unk_00E = b;
}

void TutorialShowArrow(TutorialWork* p, u16 b, u16 c, u16 d) {
    p->flags |= TUTORIAL_FLAG_SHOW_ARROW;
    p->arrowX = b;
    p->arrowY = c;
    AnimStart(&p->anim, d, ANIM_FLAG_LOOP);
}

void TutorialHideArrow(TutorialWork* p) {
    p->flags &= ~TUTORIAL_FLAG_SHOW_ARROW;
}

void task_tutorial_0(TutorialWork* work, s32 arg1) {
    gBg0Cnt = 0;
    SetupBg(0, 2, 28, 14);
    SetBgScroll(0, 0, 0);
    work->flags = 0;
    work->timer = 0;
    work->state = 0;
    work->unk_00E = 120;
    work->nextState = arg1 == 0 ? 5 : 0x2B;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CONTROL;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_JUMP;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_DODGE;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_USE;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_SELECT;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_STOCK;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_STOCK_USE;
    gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_LIST_SWITCH;
    work->tiles = AllocObjTiles(0x100, gUnk_08B263D2);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    AnimInit(&work->anim, gUnk_09EE15F0, gUnk_09EE15C0);
    AnimStart(&work->anim, 0, ANIM_FLAG_LOOP);
    SeedRandom(2);
}

s32 task_tutorial_1(TutorialWork* work) {
    switch (work->state) {
    case 0:
        if (work->timer > work->unk_00E) {
            work->state = work->nextState;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 1:
        gBtlWork->hitStop = 8;

        if (work->timer > 20) {
            work->state = 2;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 2:
        gBtlWork->hitStop = 8;

        if (work->timer == 0) {
            if (BgFxIsActive()) {
                break;
            }

            TutorialOpenMessage(work->message);
            work->timer++;
            break;
        }

        if (IsMessageWindowOpen()) {
            break;
        }

        TutorialRestoreBgMode();
        work->state = work->nextState;
        work->timer = 0;
        break;
    case 3:
        gBtlWork->hitStop = 8;

        if (work->timer > 20) {
            work->state = 4;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 4:
        gBtlWork->hitStop = 8;

        if (BgFxIsActive()) {
            break;
        }

        TutorialOpenPersistentMessage(work->message);
        work->state = work->nextState;
        work->timer = 0;
        break;
    case 5:
        TutorialQueueMessage(work, 0x48, 6);
        break;
    case 6:
        if (work->timer == 0) {
            CreateFriendCardTask(&gBtlWork->taskPools[0], 320, 0x181, 0, 1);
        }

        if (work->timer > 120) {
            work->state = 7;
            work->timer = 0;
        } else {
            work->timer++;
        }

        break;
    case 7:
        TutorialQueueMessage(work, 0x49, 9);
        break;
    case 9:
        TutorialQueuePersistentMessage(work, 0x4A, 10);
        break;
    case 10:
        if (work->timer == 0) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CONTROL;
        }

        if (!(gBtlWork->flags & 0x20000000000ULL)) {
            work->timer++;
            break;
        }

        TutorialCloseMessage();
        gBtlWork->flags &= ~0x20000000000ULL;
        work->state = 11;
        work->timer = 0;
        break;
    case 11:
        if (work->timer > 20) {
            RequestSoraPrevCard();
            TutorialWait(work, 30, 12);
        } else {
            work->timer++;
        }

        break;
    case 12:
        TutorialQueueMessage(work, 0x4B, 13);
        break;
    case 13:
        TutorialQueuePersistentMessage(work, 0x4C, 14);
        break;
    case 14:
        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CARD_USE;
        }

        if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
            work->timer++;
            break;
        }

        TutorialCloseMessage();
        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_USE;
        work->state = 15;
        work->timer = 0;
        break;
    case 15:
        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            break;
        }

        TutorialQueueMessage(work, 0x4D, 16);
        break;
    case 16:
        TutorialQueueMessage(work, 0x4E, 17);
        break;
    case 17:
        TutorialQueuePersistentMessage(work, 0x4F, 18);
        break;
    case 18:
        if (work->timer == 0) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_DODGE;
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_JUMP;
        }

        if (!(gBtlWork->flags & BTL_FLAG_DODGE_ROLL_DONE)) {
            work->timer++;
            break;
        }

        if (!(gBtlWork->flags & BTL_FLAG_JUMP_LANDED)) {
            work->timer++;
            break;
        }

        TutorialCloseMessage();
        gBtlWork->flags &= ~BTL_FLAG_DODGE_ROLL_DONE;
        gBtlWork->flags &= ~BTL_FLAG_JUMP_LANDED;
        TutorialWait(work, 15, 19);
        break;
    case 19:
        TutorialQueueMessage(work, 0x50, 20);
        break;
    case 20:
        TutorialQueuePersistentMessage(work, 0x51, 21);
        break;
    case 21:
        if (work->timer == 0) {
            work->unk_00E = 0;
            work->flags &= ~TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
        }

        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CARD_USE;
        }

        if (work->flags & TUTORIAL_FLAG_CARD_ACTION_ACTIVE) {
            if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
                if (work->unk_00E == 0) {
                    TutorialCloseMessage();
                }

                work->flags &= ~TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
                work->unk_00E++;
            }
        } else if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            work->flags |= TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
        }

        if (work->unk_00E <= 2) {
            work->timer++;
            break;
        }

        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_USE;
        TutorialWait(work, 30, 22);
        break;
    case 22:
        TutorialQueueMessage(work, 0x52, 23);
        break;
    case 23:
        TutorialQueueMessage(work, 0x53, 25);
        break;
    case 25:
        TutorialShowArrow(work, 14, 90, 0);
        TutorialQueueMessage(work, 0x54, 26);
        break;
    case 26:
        if (work->timer == 0) {
            TutorialHideArrow(work);
        }

        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CARD_USE;
        }

        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            work->timer++;
            break;
        }

        if (!IsSoraReloadCardSelected()) {
            work->timer++;
            break;
        }

        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_USE;
        TutorialWait(work, 60, 27);
        break;
    case 27:
        TutorialShowArrow(work, 14, 90, 0);
        TutorialQueueMessage(work, 0x55, 29);
        break;
    case 29:
        TutorialQueueMessage(work, 0x56, 30);
        break;
    case 30:
        TutorialHideArrow(work);
        TutorialQueuePersistentMessage(work, 0x57, 31);
        break;
    case 31:
        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CARD_USE;
        }

        if (gBtlWork->flags & BTL_FLAG_RELOADING) {
            work->timer++;
            break;
        }

        if (IsSoraReloadCardSelected()) {
            work->timer++;
            break;
        }

        TutorialCloseMessage();
        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_USE;
        TutorialWait(work, 30, 32);
        break;
    case 32:
        TutorialQueueMessage(work, 0x58, 33);
        break;
    case 33:
        TutorialQueueMessage(work, 0x59, 34);
        break;
    case 34:
        TutorialQueuePersistentMessage(work, 0x5A, 35);
        break;
    case 35:
        if (work->timer == 0) {
            work->unk_00E = 0;
            work->inputCooldown = 0;
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CARD_SELECT;
        }

        if (work->inputCooldown <= 0) {
            if (GetKeysPressed() & (L_BUTTON | R_BUTTON)) {
                work->inputCooldown = 10;
                work->unk_00E++;
            }
        } else {
            work->inputCooldown--;
        }

        if (work->unk_00E <= 6) {
            work->timer++;
            break;
        }

        work->timer = 0;
        work->state = 36;
        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_SELECT;
        TutorialCloseMessage();
        break;
    case 36:
        TutorialQueueMessage(work, 0x5B, 37);
        break;
    case 37:
        TutorialQueueMessage(work, 0x5C, 38);
        break;
    case 38:
        TutorialQueuePersistentMessage(work, 0x5D, 39);
        break;
    case 39:
        if (work->timer == 0) {
            work->unk_00E = 0;
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_LIST_SWITCH;
        }

        if (GetKeysPressed() & SELECT_BUTTON) {
            work->unk_00E++;
        }

        if (work->unk_00E <= 1) {
            work->timer++;
            break;
        }

        TutorialCloseMessage();
        work->timer = 0;
        work->state = 40;
        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_LIST_SWITCH;
        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_SELECT;
        break;
    case 40:
        TutorialQueueMessage(work, 0x5E, 41);
        break;
    case 41:
        TutorialWait(work, 0x50, 42);
        break;
    case 43:
        TutorialWait(work, 30, 44);
        break;
    case 44:
        TutorialShowArrow(work, 48, 144, 1);
        TutorialQueueMessage(work, 0x72, 45);
        break;
    case 45:
        if (work->timer == 0) {
            TutorialHideArrow(work);
            work->flags &= ~TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
            work->unk_00E = 0;
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CONTROL;
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_JUMP;
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_DODGE;
            gBtlWork->flags |= 0x100000ULL;
            gBtlWork->flags |= 0x20000000000ULL;
        }

        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_CARD_USE;
        }

        if (work->flags & TUTORIAL_FLAG_CARD_ACTION_ACTIVE) {
            if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
                work->flags &= ~TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
                work->unk_00E++;
            }
        } else if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            work->flags |= TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
        }

        if (work->unk_00E <= 6) {
            work->timer++;
            break;
        }

        work->timer = 0;
        work->state = 46;
        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_CARD_USE;
        gBtlWork->flags &= ~0x100000ULL;
        gBtlWork->flags &= ~0x20000000000ULL;
        break;
    case 46:
        if (work->timer > 30) {
            work->timer = 0;
            work->state = 47;
        } else {
            work->timer++;
        }

        break;
    case 47:
        if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            break;
        }

        if (gBtlWork->flags & BTL_FLAG_OPPONENT_CARD_ACTION) {
            break;
        }

        TutorialQueueMessage(work, 0x73, 48);
        break;
    case 48:
        TutorialQueueMessage(work, 0x74, 49);
        break;
    case 49:
        TutorialQueueMessage(work, 0x75, 50);
        break;
    case 50:
        TutorialQueueMessage(work, 0x76, 51);
        break;
    case 51:
        TutorialQueueMessage(work, 0x77, 52);
        break;
    case 52:
        TutorialQueueMessage(work, 0x78, 53);
        break;
    case 53:
        TutorialQueueMessage(work, 0x79, 54);
        break;
    case 54:
        TutorialQueueMessage(work, 0x7A, 55);
        break;
    case 55:
        TutorialQueueMessage(work, 0x7B, 56);
        break;
    case 56:
        TutorialQueuePersistentMessage(work, 0x7C, 57);
        break;
    case 57:
        if (work->timer == 0) {
            work->unk_00E = 0;
        }

        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_STOCK;
        }

        if (work->unk_00E == 0 && GetSoraStockCount() != 0) {
            TutorialCloseMessage();
            work->unk_00E++;
        }

        if (GetSoraStockCount() <= 2) {
            work->timer++;
            break;
        }

        gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_STOCK;
        work->timer = 0;
        work->state = 58;
        break;
    case 58:
        TutorialQueueMessage(work, 0x7D, 59);
        break;
    case 59:
        TutorialQueuePersistentMessage(work, 0x7E, 60);
        break;
    case 60:
        if (work->timer == 0) {
            gBtlWork->flags |= 0x20000000000ULL;
            work->flags &= ~TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
            work->unk_00E = 0;
        }

        if (work->timer == 10) {
            gBtlWork->flags &= ~BTL_FLAG_TUTORIAL_NO_STOCK_USE;
        }

        if (work->flags & TUTORIAL_FLAG_CARD_ACTION_ACTIVE) {
            if (!(gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION)) {
                work->flags &= ~TUTORIAL_FLAG_CARD_ACTION_ACTIVE;
                work->unk_00E++;
            }
        } else if (gBtlWork->flags & BTL_FLAG_PLAYER_CARD_ACTION) {
            work->flags |= TUTORIAL_FLAG_CARD_ACTION_ACTIVE;

            if (work->unk_00E == 0) {
                TutorialCloseMessage();
            }
        }

        if (work->unk_00E > 0) {
            gBtlWork->flags |= BTL_FLAG_TUTORIAL_NO_STOCK_USE;
            gBtlWork->flags &= ~0x20000000000ULL;
            TutorialWait(work, 30, 61);
        } else {
            work->timer++;
        }

        break;
    case 61:
        TutorialQueueMessage(work, 0x7F, 62);
        break;
    case 62:
        TutorialQueueMessage(work, 0x80, 63);
        break;
    case 63:
        TutorialWait(work, 0x50, 64);
        break;
    case 42:
    case 64:
        gBtlWork->flags |= BTL_FLAG_BATTLE_OVER;
        break;
    }

    return 1;
}

void task_tutorial_2(TutorialWork* work) {
    void* spr;
    u16 x;
    u16 y;
    s32 s;

    if (work->flags & TUTORIAL_FLAG_SHOW_ARROW) {
        spr = AnimUpdate(&work->anim);

        if (work->anim.animId == 0) {
            x = work->arrowX;
            s = gSineTable[(gFrameCounter << 3) & 0xFF];
            y = (s >> 7) + work->arrowY;
        } else {
            s = gSineTable[(gFrameCounter << 3) & 0xFF];
            x = (s >> 7) + work->arrowX;
            y = work->arrowY;
        }

        DrawSprite(x, y, spr, work->tiles, work->palette, NULL, SPRITE_FLAG_NO_MOSAIC, 0);
    }
}

void task_tutorial_3(TutorialWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
    SeedRandom(gFrameCounter);
}

TaskDesc gTaskDescTutorial = {
    "task_tutorial",
    (TaskInitFunc)task_tutorial_0,
    (TaskUpdateFunc)task_tutorial_1,
    (TaskDrawFunc)task_tutorial_2,
    (TaskDestroyFunc)task_tutorial_3,
    sizeof(TutorialWork),
};
