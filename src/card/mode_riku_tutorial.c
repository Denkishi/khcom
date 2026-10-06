/**
 * mode_riku_tutorial.c
 * Sleight Combos and Riku Tutorial Modes
 */

#include "macros.h"
#include "registration_data.h"
#include "card_battle.h"
#include "player_progression.h"
#include "game_state.h"
#include <string.h>
#include "fade.h"
#include "taskpool.h"
#include "card.h"
#include "battle_work.h"
#include "card_api.h"
#include "card_types.h"
#include "mode.h"
#include "mode_battle_data.h"
#include "player_progression_types.h"
#include "types.h"
#include <stddef.h>
#include "mode_riku_tutorial.h"
#include "battle.h"
#include "btl.h"
#include "card_ids.h"
#include "card_message_data.h"

static TaskPool sRikuTutorialTasks;

static s32 sRikuTutorialModeArg;

u8 gRikuDeckTutorialState EWRAM_COMMON(4);

enum RikuDeckTutorialState {
    RIKU_DECK_TUTORIAL_STATE_SHOW_MESSAGE,
    RIKU_DECK_TUTORIAL_STATE_WAIT_MESSAGE
};

void RikuTutorialModeInit(s32 arg) {
    FadeStartIn(FADE_MODE_BLACK, 16);
    sRikuTutorialModeArg = arg;
    TaskPoolInit(&sRikuTutorialTasks, 1);
    gRikuDeckTutorialState = RIKU_DECK_TUTORIAL_STATE_SHOW_MESSAGE;
}

void Mode_riku_btlTutorial_1() {
    u16 tutorialFlags;

    tutorialFlags = gGameState.progression.tutorialFlags | 0x1000;
    gGameState.progression.tutorialFlags = tutorialFlags;
    ModeRequest(&gModeBattle, sRikuTutorialModeArg);
    TaskPoolUpdate(&sRikuTutorialTasks);
    TaskPoolDraw(&sRikuTutorialTasks);
}

void Mode_riku_deckTutorial_1() {
    if (!FadeIsActive()) {
        switch (gRikuDeckTutorialState) {
        case RIKU_DECK_TUTORIAL_STATE_SHOW_MESSAGE:
            if (!IsMessageWindowOpen() && gRikuDeckTutorialState == RIKU_DECK_TUTORIAL_STATE_SHOW_MESSAGE) {
                CreateSysmsgwinTask(&sRikuTutorialTasks, CARD_MSG_RIKU_DECK_TUTORIAL);
                gRikuDeckTutorialState = RIKU_DECK_TUTORIAL_STATE_WAIT_MESSAGE;
            }

            break;
        case RIKU_DECK_TUTORIAL_STATE_WAIT_MESSAGE:
            if (!IsMessageWindowOpen()) {
                gGameState.progression.tutorialFlags |= 0x800;
                ModeRequest(&gModeDeck, sRikuTutorialModeArg);
            }

            break;
        }
    }

    TaskPoolUpdate(&sRikuTutorialTasks);
    TaskPoolDraw(&sRikuTutorialTasks);
}

void RikuTutorialModeDestroy() {
    TaskPoolDestroy(&sRikuTutorialTasks);
}

s32 ResolveActiveCardsMove(s32* out) {
    StockKeys stockKeys;
    u8 found[6];
    u8 flag;
    u8 i;
    s32 stockName;
    BtlWork* btl;
#ifdef VERSION_EU
    u8 soraStockActive;
    s32 j;
#endif

    stockKeys = gTutorialEmptyKeys;
    flag = 0;
    memset(found, 0, 6);

#ifdef VERSION_EU
    soraStockActive = 0;
    out[0] = -1;
    out[1] = -1;
    out[2] = -1;
    out[3] = -1;
    out[4] = -1;
    out[5] = -1;
#endif

    for (i = 0; i < gCardBattleState->activeCardCount; i++) {
        stockKeys.keys[i] = gCardBattleState->activeCards[i]->cardDef->catalogNumber;
#ifdef VERSION_EU
        out[i] = gCardBattleState->activeCards[i]->cardDef->move;
#else

        if (out != NULL) {
            out[i] = gCardBattleState->activeCards[i]->cardDef->move;
        }
#endif
    }

#ifdef VERSION_EU
    if (gCardBattleState->activeCardCount == 1 && (soraStockActive = gCardBattleState->soraStockActive) == 0) {
#else
    if (gCardBattleState->activeCardCount == 1) {
#endif
        gCardBattleState->stockMoveCount = 1;

        if ((gGameState.flags & GAME_FLAG_RIKU) && gBtlWork->soraOwnsPlay == 1 && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            if (gCardBattleState->darkModeReady == 1 || gBtlWork->darkPoints > 29) {
                gCardBattleState->darkModeReady = 0;
                return 46;
            }
        }

        return gCardBattleState->activeCards[0]->cardDef->move;
#ifdef VERSION_EU
    } else if (gCardBattleState->activeCardCount == 1 && (btl = gBtlWork)->soraOwnsPlay == 1) {
        if (btl->hcEffect == 47) {
            out[0] = out[1] = gCardBattleState->activeCards[0]->cardDef->move;
            gCardBattleState->stockMoveCount = 2;
            return 145;
        } else {
            return gCardBattleState->activeCards[0]->cardDef->move;
        }
#endif
    } else if (gCardBattleState->activeCardCount == 0) {
        gCardBattleState->stockMoveCount = 0;
        return -1;
    } else {
        stockName = LookupStockName(gCardBattleState->activeCards, gCardBattleState->activeCardCount, gCardBattleState->activeValue, &stockKeys, &flag);

        switch (stockName) {
        case 108:
            gCardBattleState->stockMoveCount = 1;
            return 46;
        default:
            btl = gBtlWork;

            if (btl->soraOwnsPlay == 1) {
                if (btl->hcEffect == 47) {
                    out[0] = out[1] = GetStockMove(stockName);
                    gCardBattleState->stockMoveCount = 2;
                    return 145;
                } else {
                    return GetStockMove(stockName);
                }
            } else {
                if (gRikuBtlWork->hcEffect == 47) {
                    out[0] = out[1] = GetStockMove(stockName);
                    gCardBattleState->stockMoveCount = 2;
                    return 145;
                } else {
                    return GetStockMove(stockName);
                }
            }
        case 106:
#ifndef VERSION_EU
            if (out != NULL) {
#endif
                FindStockPairsInCombo(stockKeys.keys, found);

                if (found[0] == 1) {
                    out[0] = stockKeys.keys[0];
#ifdef VERSION_EU
                    out[1] = 145;
#else
                    out[1] = -1;
#endif
                    out[3] = out[0];
                    out[4] = out[1];
                    out[5] = out[2];
                } else if (found[1] == 1) {
#ifdef VERSION_EU
                    out[1] = 145;
#else
                    out[1] = -1;
#endif
                    out[2] = stockKeys.keys[1];
                    out[3] = out[0];
                    out[4] = out[1];
                    out[5] = out[2];
                } else {
                    out[3] = out[0];
                    out[4] = out[1];
                    out[5] = out[2];

#ifdef VERSION_EU
                    for (j = 0; j < 5; j++) {
                        if (out[j] == -1) {
                            out[j] = out[j + 1];
                            out[j + 1] = -1;
                        }
                    }
#endif
                }

                if (gBtlWork->soraOwnsPlay == 1) {
                    if (gBtlWork->hcEffect == 47) {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount * 2;
                    } else {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount;
                    }
                } else {
                    if (gRikuBtlWork->hcEffect == 47) {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount * 2;
                    } else {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount;
                    }
                }

#ifndef VERSION_EU
            }
#endif

            return 145;
        }
    }
}

s32 ResolveLinkActiveCardsMove(s32* out, s32 side) {
    StockKeys stockKeys;
    u8 found[6];
    u8 flag;
    u8 i;
    s32 stockName;
#ifdef VERSION_EU
    u8 stockActive;
    s32 j;
    s32 move;
#endif

    memset(&stockKeys, 0, sizeof(stockKeys));
    flag = 0;
    memset(found, 0, 6);

#ifdef VERSION_EU
    stockActive = 0;
    out[0] = -1;
    out[1] = -1;
    out[2] = -1;
    out[3] = -1;
    out[4] = -1;
    out[5] = -1;
#endif

    for (i = 0; i < gCardBattleState->activeCardCount; i++) {
        stockKeys.keys[i] = gCardBattleState->activeCards[i]->cardDef->catalogNumber;
#ifdef VERSION_EU
        out[i] = gCardBattleState->activeCards[i]->cardDef->move;
#else

        if (out != NULL) {
            out[i] = gCardBattleState->activeCards[i]->cardDef->move;
        }
#endif
    }

    if (gCardBattleState->activeCardCount == 1) {
#ifdef VERSION_EU
        switch (side) {
        case 0:
            stockActive = gCardBattleState->soraStockActive;
            break;
        case 1:
            stockActive = gCardBattleState->rikuStockActive;
            break;
        }

        if (!stockActive) {
#endif
        gCardBattleState->stockMoveCount = 1;

        if ((gGameState.flags & GAME_FLAG_RIKU) && gBtlWork->soraOwnsPlay && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
            if (gCardBattleState->darkModeReady == 1 || gBtlWork->darkPoints > 29) {
                gCardBattleState->darkModeReady = 0;
                return 46;
            }
        }

        return gCardBattleState->activeCards[0]->cardDef->move;
#ifdef VERSION_EU
        } else {
            if (gBtlWork->soraOwnsPlay == 1) {
                if (gBtlWork->hcEffect == 47) {
                    out[0] = out[1] = gCardBattleState->activeCards[0]->cardDef->move;
                    gCardBattleState->stockMoveCount = 2;
                    return 145;
                } else {
                    return gCardBattleState->activeCards[0]->cardDef->move;
                }
            } else {
                if (gRikuBtlWork->hcEffect == 47) {
                    out[0] = out[1] = gCardBattleState->activeCards[0]->cardDef->move;
                    gCardBattleState->stockMoveCount = 2;
                    return 145;
                } else {
                    return gCardBattleState->activeCards[0]->cardDef->move;
                }
            }
        }
#endif
    } else if (gCardBattleState->activeCardCount == 0) {
        gCardBattleState->stockMoveCount = 0;
        return -1;
    } else {
        stockName = LookupLinkStockName(gCardBattleState->activeCards, gCardBattleState->activeCardCount, gCardBattleState->activeValue, &stockKeys, &flag, side);

        switch (stockName) {
        case 108:
            gCardBattleState->stockMoveCount = 1;
            return 46;
        default:
            if (gBtlWork->soraOwnsPlay == 1) {
                if (gBtlWork->hcEffect == 47) {
                    out[0] = out[1] = GetStockMove(stockName);
                    gCardBattleState->stockMoveCount = 2;
                    return 145;
                } else {
                    return GetStockMove(stockName);
                }
            } else {
                if (gRikuBtlWork->hcEffect == 47) {
                    out[0] = out[1] = GetStockMove(stockName);
                    gCardBattleState->stockMoveCount = 2;
                    return 145;
                } else {
                    return GetStockMove(stockName);
                }
            }
        case 106:
#ifndef VERSION_EU
            if (out != NULL) {
#endif
                FindStockPairsInCombo(stockKeys.keys, found);

                if (found[0] == 1) {
                    out[0] = stockKeys.keys[0];
#ifdef VERSION_EU
                    out[1] = 145;
#else
                    out[1] = -1;
#endif
                    out[3] = out[0];
                    out[4] = out[1];
                    out[5] = out[2];
                } else if (found[1] == 1) {
#ifdef VERSION_EU
                    out[1] = 145;
#else
                    out[1] = -1;
#endif
                    out[2] = stockKeys.keys[1];
                    out[3] = out[0];
                    out[4] = out[1];
                    out[5] = out[2];
                } else {
                    out[3] = out[0];
                    out[4] = out[1];
                    out[5] = out[2];

#ifdef VERSION_EU
                    for (j = 0; j < 5; j++) {
                        if (out[j] == -1) {
                            move = out[j];
                            out[j] = out[j + 1];
                            out[j + 1] = move;
                        }
                    }
#endif
                }

                if (gBtlWork->soraOwnsPlay == 1) {
                    if (gBtlWork->hcEffect == 47) {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount * 2;
                    } else {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount;
                    }
                } else {
                    if (gRikuBtlWork->hcEffect == 47) {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount * 2;
                    } else {
                        gCardBattleState->stockMoveCount = gCardBattleState->activeCardCount;
                    }
                }

#ifndef VERSION_EU
            }
#endif

            return 145;
        }
    }
}

u8 GetStockMoveCount() {
    // @bug Still called after the card battle frees gCardBattleState (NULL read).
    if (gCardBattleState->soraStockActive || gCardBattleState->rikuStockActive) {
        return gCardBattleState->stockMoveCount;
    }

    return 0;
}

#define SIO_PAIR_CASE(v) \
    case v: \
        keys[i] = key; \
        found[i] = 1; \
        break;
u8 FindStockPairsInCombo(s32* keys, u8* found) {
    u32 catalogNumbers[6];
    u32 key;
    s32 i = 0;

    if (gCardBattleState->activeCardCount <= 2) {
        return 0;
    }

    catalogNumbers[0] = keys[0];
    catalogNumbers[1] = keys[1];
    catalogNumbers[2] = keys[2];
    key = (catalogNumbers[1] << 10) | catalogNumbers[0] | 0x80000000;

    switch (key) {
    SIO_PAIR_CASE(0x8002ACAB)
    SIO_PAIR_CASE(0x8002D4B5)
    SIO_PAIR_CASE(0x8002FCBF)
    SIO_PAIR_CASE(0x800324C9)
    SIO_PAIR_CASE(0x80034CD3)
    SIO_PAIR_CASE(0x800374DD)
    SIO_PAIR_CASE(0x80039CE7)
    SIO_PAIR_CASE(0x8003C4F1)
    SIO_PAIR_CASE(0x8003ECFB)
    SIO_PAIR_CASE(0x80041505)
    SIO_PAIR_CASE(0x80043D0F)
    SIO_PAIR_CASE(0x80046519)
    SIO_PAIR_CASE(0x80048D23)
    SIO_PAIR_CASE(0x8004B52D)
    SIO_PAIR_CASE(0x8004DD37)
    SIO_PAIR_CASE(0x80050541)
    SIO_PAIR_CASE(0x80052D4B)
    SIO_PAIR_CASE(0x80055555)
    SIO_PAIR_CASE(0x80057D5F)
    SIO_PAIR_CASE(0x8005A569)
    SIO_PAIR_CASE(0x8005CD73)
    SIO_PAIR_CASE(0x800A7E9F)
    }

    i++;
    key = catalogNumbers[1] | (catalogNumbers[2] << 10) | 0x80000000;

    switch (key) {
    SIO_PAIR_CASE(0x8002ACAB)
    SIO_PAIR_CASE(0x8002D4B5)
    SIO_PAIR_CASE(0x8002FCBF)
    SIO_PAIR_CASE(0x800324C9)
    SIO_PAIR_CASE(0x80034CD3)
    SIO_PAIR_CASE(0x800374DD)
    SIO_PAIR_CASE(0x80039CE7)
    SIO_PAIR_CASE(0x8003C4F1)
    SIO_PAIR_CASE(0x8003ECFB)
    SIO_PAIR_CASE(0x80041505)
    SIO_PAIR_CASE(0x80043D0F)
    SIO_PAIR_CASE(0x80046519)
    SIO_PAIR_CASE(0x80048D23)
    SIO_PAIR_CASE(0x8004B52D)
    SIO_PAIR_CASE(0x8004DD37)
    SIO_PAIR_CASE(0x80050541)
    SIO_PAIR_CASE(0x80052D4B)
    SIO_PAIR_CASE(0x80055555)
    SIO_PAIR_CASE(0x80057D5F)
    SIO_PAIR_CASE(0x8005A569)
    SIO_PAIR_CASE(0x8005CD73)
    SIO_PAIR_CASE(0x800A7E9F)
    }
}

s32 GetStockMove(s32 stock) {
    switch (stock) {
    case 0:
        return 0x8002ACAB;
    case 1:
        return 0x8002D4B5;
    case 2:
        return 0x8002FCBF;
    case 3:
        return 0x800324C9;
    case 11:
        return 0x80034CD3;
    case 4:
        return 0x800374DD;
    case 5:
        return 0xC0100401;
    case 6:
        return 0x64;
    case 7:
        return 0xCAB2ACAB;
    case 8:
        return 0xCB52D4B5;
    case 9:
        return 0xCBF2FCBF;
    case 10:
        return 0xCC9324C9;
    case 13:
        return 0xCDD374DD;
    case 12:
        return 0xCD334CD3;
    case 14:
        return 0xCFB3ECFB;
    case 15:
        return 0x8003ECFB;
    case 16:
        return 0xCF13C4F1;
    case 17:
        return 0x8003C4F1;
    case 18:
        return 0xD0541505;
    case 19:
        return 0x80041505;
    case 20:
        return 0xD0F43D0F;
    case 21:
        return 0x80043D0F;
    case 22:
        return 0xD1946519;
    case 23:
        return 0x80046519;
    case 24:
        return 0xD2348D23;
    case 25:
        return 0x80048D23;
    case 26:
        return 0xD2D4B52D;
    case 27:
        return 0x8004B52D;
    case 28:
        return 0xD374DD37;
    case 29:
        return 0x8004DD37;
    case 30:
        return 0xD4150541;
    case 31:
        return 0x80050541;
    case 32:
        return 0xD4B52D4B;
    case 33:
        return 0x80052D4B;
    case 34:
        return 0xD5555555;
    case 35:
        return 0x80055555;
    case 36:
        return 0xD5F57D5F;
    case 37:
        return 0x80057D5F;
    case 38:
        return 0xD695A569;
    case 39:
        return 0x8005A569;
    case 40:
        return 0xD735CD73;
    case 41:
        return 0x8005CD73;
    case 42:
        return 0xE9FA7E9F;
    case 43:
        return 0x800A7E9F;
    case 44:
        return 0x80039CE7;
    case 45:
        return 0xCE739CE7;
    case 46:
        return 0x65;
    case 47:
        return 0x66;
    case 48:
        return 0x67;
    case 49:
        return 0x68;
    case 50:
        return 0x69;
    case 51:
        return 0x6A;
    case 52:
        return 0x6B;
    case 53:
        return 0x6C;
    case 54:
        return 0x6D;
    case 55:
        return 0x6E;
    case 56:
        return 0x6F;
    case 57:
        return 0x70;
    case 58:
        return 0x71;
    case 59:
        return 0x72;
    case 60:
        return 0x73;
    case 61:
        return 0x74;
    case 62:
        return 0x75;
    case 63:
        return 0x76;
    case 64:
        return 0x77;
    case 65:
        return 0x78;
    case 66:
        return 0x79;
    case 67:
        return 0x7A;
    case 69:
        return 0x7C;
    case 70:
        return 0x7D;
    case 71:
        return 0x7E;
    case 72:
        return 0x7F;
    case 73:
        return 0x80;
    case 74:
        return 0x81;
    case 75:
        return 0x82;
    case 76:
        return 0x83;
    case 77:
        return 0x84;
    case 78:
        return 0x85;
    case 79:
        return 0x86;
    case 80:
        return 0x87;
    case 81:
        return 0x88;
    case 82:
        return 0x89;
    case 83:
        return 0x8A;
    case 84:
        return 0x8B;
    case 108:
        return 0x2E;
    case 85:
        return 0xF21C8721;
    case 86:
        return 0xEB3ACEB3;
    case 87:
        return 0xEB3AA6B3;
    case 88:
        return 0xEE5B96E5;
    case 89:
        return 0xEEFB96EF;
    case 90:
        return 0xF49D2735;
    case 91:
        return 0xED1AF6BD;
    case 92:
        return 0xED1B1EC7;
    case 93:
        return 0xF0DBE6F9;
    case 94:
        return 0xF53D7753;
    case 95:
        return 0xF53D4F5D;
    case 96:
        return 0xF5DD4F53;
    case 97:
        return 0xF17C0F03;
    case 98:
        return 0xF35CFF3F;
    case 99:
        return 0xF21CAF21;
    case 100:
        return 0xF71D9F71;
    case 101:
        return 0xF7BDC767;
    case 102:
        return 0xFADEB7A3;
    case 103:
        return 0xFA3EB7A3;
    case 104:
        return 0xF85E3F85;
    case 105:
        return 0xF53D4F53;
    }
}

u8 AreThreeCardValuesEqual(CardDisplayWork** cards, u8 count) {
    u8 x;
    u8 y;
    u8 z;

    if (count != 3) {
        return 0;
    }

    x = cards[0]->value;
    y = cards[1]->value;
    z = cards[2]->value;

    if (x != y) {
        return 0;
    }

    if (x != z) {
        return 0;
    }

    return 1;
}

s32 LookupStockName(CardDisplayWork** cards, u8 count, u8 value, StockKeys* stockKeys, u8* flag) {
    s32 catalogNumbers[3];
    u32 key;
    u8 matchCount;
    u8 i;

    memset(catalogNumbers, 0, 12);
    matchCount = 0;

    for (i = 0; i < count; i++) {
        catalogNumbers[i] = (*(i + cards))->cardDef->catalogNumber;
    }

    if ((gGameState.flags & GAME_FLAG_RIKU) && gBtlWork->soraOwnsPlay && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
        if (gCardBattleState->darkModeReady == 1 || gBtlWork->darkPoints > 29) {
            gCardBattleState->darkModeReady = 0;
            return 108;
        }
    }

    key = catalogNumbers[0] | (catalogNumbers[1] << 10) | (catalogNumbers[2] << 20) | (count << 30);

    switch (key) {
    case 0x8002ACAB:
        return 0;
    case 0x8002FCBF:
        return 2;
    case 0x8002D4B5:
        return 1;
    case 0x800324C9:
        return 3;
    case 0x80034CD3:
        return 11;
    case 0x800374DD:
        return 4;
    case 0x80039CE7:
        return 44;
    case 0x8003ECFB:
        return 15;
    case 0x8003C4F1:
        return 17;
    case 0x80041505:
        return 19;
    case 0x80043D0F:
        return 21;
    case 0x80046519:
        return 23;
    case 0x80048D23:
        return 25;
    case 0x8004B52D:
        return 27;
    case 0x8004DD37:
        return 29;
    case 0x80050541:
        return 31;
    case 0x80052D4B:
        return 33;
    case 0x80055555:
        return 35;
    case 0x80057D5F:
        return 37;
    case 0x8005A569:
        return 39;
    case 0x8005CD73:
        return 41;
    case 0x800A7E9F:
        return 43;
    case 0xC0100401:
    case 0xC0B02C0B:
    case 0xC1505415:
    case 0xC1F07C1F:
    case 0xC290A429:
    case 0xC330CC33:
    case 0xC3D0F43D:
    case 0xC4711C47:
    case 0xC5114451:
    case 0xC5B16C5B:
    case 0xC6519465:
    case 0xC6F1BC6F:
    case 0xC791E479:
    case 0xC8320C83:
    case 0xC8D2348D:
    case 0xC9725C97:
    case 0xCA1284A1:
        if ((u16)(value - 10) <= 5 && IsStockLearned(0)) {
            stockKeys->keys[0] = 50;
            return 50;
        }

        if ((u16)(value - 20) <= 3 && IsStockLearned(2)) {
            stockKeys->keys[0] = 51;
            return 51;
        }

        break;
    case 0xCAB2ACAB:
        return 7;
    case 0xCB52D4B5:
        return 8;
    case 0xCBF2FCBF:
        return 9;
    case 0xCC9324C9:
        return 10;
    case 0xCD334CD3:
        return 12;
    case 0xCDD374DD:
        return 13;
    case 0xCE739CE7:
        return 45;
    case 0xCFB3ECFB:
        return 14;
    case 0xCF13C4F1:
        return 16;
    case 0xD0541505:
        return 18;
    case 0xD0F43D0F:
        return 20;
    case 0xD1946519:
        return 22;
    case 0xD2348D23:
        return 24;
    case 0xD2D4B52D:
        return 26;
    case 0xD374DD37:
        return 28;
    case 0xD4150541:
        return 30;
    case 0xD4B52D4B:
        return 32;
    case 0xD5555555:
        return 34;
    case 0xD5F57D5F:
        return 36;
    case 0xD695A569:
        return 38;
    case 0xD735CD73:
        return 40;
    case 0xE9FA7E9F:
        return 42;
    case 0xCE739CDD:
        if (IsStockLearned(39)) {
            return 53;
        }

        break;
    case 0xCE734CDD:
        if (IsStockLearned(38)) {
            return 54;
        }

        break;
    case 0xCE72ACB5:
        if (IsStockLearned(34)) {
            return 65;
        }

        break;
    case 0xCAB2AD37:
        if (IsStockLearned(32)) {
            return 70;
        }

        break;
    case 0xCE734CC9:
        if (IsStockLearned(43)) {
            return 77;
        }

        break;
    case 0xE95A5695:
        if (gBtlWork->flags & BTL_FLAG_DARK_MODE) {
            if ((u16)(value - 5) <= 10) {
                return 82;
            }

            if ((u16)(value - 16) <= 9) {
                return 83;
            }

            if (value > 26) {
                return 84;
            }
        }

        break;
    case 0xF21C8721:
        return 85;
    case 0xEB3ACEB3:
        return 86;
    case 0xEB3AA6B3:
        return 87;
    case 0xEE5B96E5:
        return 88;
    case 0xEEFB96EF:
        return 89;
    case 0xF49D2735:
        return 90;
    case 0xED1AF6BD:
        return 91;
    case 0xED1B1EC7:
        return 92;
    case 0xF0DBE6F9:
        return 93;
    case 0xF53D7753:
        return 94;
    case 0xF53D4F5D:
        return 95;
    case 0xF5DD4F53:
        return 96;
    case 0xF17C0F03:
        return 97;
    case 0xF35CFF3F:
        return 98;
    case 0xF21CAF21:
        return 99;
    case 0xF71D9F71:
        return 100;
    case 0xF7BDC767:
        return 101;
    case 0xFADEB7A3:
        return 102;
    case 0xFA3EB7A3:
        return 103;
    case 0xF85E3F85:
        return 104;
    case 0xF53D4F53:
        return 105;
    }

    if ((u8)IsTwoSummonsThenKind(cards, count, 43) || (u8)IsSimbaMushuItem(cards, count)) {
        if (IsStockLearned(42)) {
            return 55;
        }
    }

    if ((u8)IsGenieTinkerBellSummon(cards, count) && IsStockLearned(41)) {
        return 56;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 23, count) && IsStockLearned(27)) {
        return 58;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 24, count) && IsStockLearned(28)) {
        return 59;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 31, count) && IsStockLearned(29)) {
        return 60;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 18, count) && IsStockLearned(23)) {
        return 61;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 19, count) && IsStockLearned(24)) {
        return 62;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 20, count) && IsStockLearned(25)) {
        return 63;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 22, count) && IsStockLearned(26)) {
        return 64;
    }

    if ((u8)IsMegaEtherMegalixirItem(cards, count) && IsStockLearned(46)) {
        return 66;
    }

    if ((u8)IsFireDonaldMagic(cards, count) && IsStockLearned(58)) {
        return 67;
    }

    if ((u8)IsSummonMagicJackOrBambiBlizzardItem(cards, count) && IsStockLearned(44)) {
        return 69;
    }

    if ((u8)IsFireMushuAttack(cards, count) && IsStockLearned(31)) {
        return 71;
    }

    if ((u8)IsKindThenTwoOfCategory(cards, 25, 0, count) && IsStockLearned(35)) {
        return 72;
    }

    if ((u8)IsKindThenTwoOfCategory(cards, 27, 0, count) && IsStockLearned(50)) {
        return 73;
    }

    if ((u8)IsCloudStopAttack(cards, count) && IsStockLearned(56)) {
        return 74;
    }

    if ((u8)IsAeroFireMagic(cards, count) && IsStockLearned(30)) {
        return 75;
    }

    if ((u8)IsAeroBlizzardMagic(cards, count) && IsStockLearned(33)) {
        return 76;
    }

    if ((u8)IsKindPairThenNonSummonOfCategory(cards, count, 22, 23, 1) && IsStockLearned(40)) {
        return 78;
    }

    if ((u8)IsKindPairThenSummon(cards, count, 24, 22) && IsStockLearned(36)) {
        return 79;
    }

    if ((u8)IsKindPairThenNonSummonOfCategory(cards, count, 22, 25, 1) && IsStockLearned(37)) {
        return 80;
    }

    if ((u8)IsTwoMagicThenPeterPan(cards, count) && IsStockLearned(45)) {
        return 81;
    }

    if ((u8)IsThreeDistinctAttackCards(cards, count)) {
        if ((u16)(value - 10) <= 5 && IsStockLearned(1)) {
            stockKeys->keys[0] = 46;
            return 46;
        }

        if ((u16)(value - 20) <= 3 && IsStockLearned(5)) {
            stockKeys->keys[0] = 5;
            return 5;
        }
    }

    if ((u8)IsThreeAttackCardsNoMove18(cards, count)) {
        if ((u16)(value - 1) <= 5 && IsStockLearned(6)) {
            stockKeys->keys[0] = 47;
            return 47;
        }

        if ((u16)(value - 24) <= 2 && IsStockLearned(4)) {
            stockKeys->keys[0] = 6;
            return 6;
        }

        if ((u16)(value - 7) <= 2 && IsStockLearned(7)) {
            stockKeys->keys[0] = 48;
            return 48;
        }

        if (value == 0 || value == 27) {
            if (IsStockLearned(3)) {
                stockKeys->keys[0] = 52;
                return 52;
            }
        }
    }

    if ((u8)IsAttackDonaldGoofyAnyOrder(cards, count) && IsStockLearned(8)) {
        stockKeys->keys[0] = 49;
        return 49;
    }

    *flag = matchCount;

    if (matchCount == 0) {
        return 106;
    }

    if (matchCount == 1) {
        return stockKeys->keys[0];
    }

    return 107;
}

s32 LookupLinkStockName(CardDisplayWork** cards, u8 count, u8 value, StockKeys* stockKeys, u8* flag, s32 side) {
    s32 catalogNumbers[3];
    u32 key;
    u8 matchCount;
    u8 i;

    memset(catalogNumbers, 0, 12);
    matchCount = 0;

    for (i = 0; i < count; i++) {
        catalogNumbers[i] = (*(i + cards))->cardDef->catalogNumber;
    }

    if ((gGameState.flags & GAME_FLAG_RIKU) && gBtlWork->soraOwnsPlay && !(gBtlWork->flags & BTL_FLAG_DARK_MODE)) {
        if (gCardBattleState->darkModeReady == 1 || gBtlWork->darkPoints > 29) {
            gCardBattleState->darkModeReady = 0;
            return 108;
        }
    }

    key = catalogNumbers[0] | (catalogNumbers[1] << 10) | (catalogNumbers[2] << 20) | (count << 30);

    switch (key) {
    case 0x8002ACAB:
        return 0;
    case 0x8002FCBF:
        return 2;
    case 0x8002D4B5:
        return 1;
    case 0x800324C9:
        return 3;
    case 0x80034CD3:
        return 11;
    case 0x800374DD:
        return 4;
    case 0x80039CE7:
        return 44;
    case 0x8003ECFB:
        return 15;
    case 0x8003C4F1:
        return 17;
    case 0x80041505:
        return 19;
    case 0x80043D0F:
        return 21;
    case 0x80046519:
        return 23;
    case 0x80048D23:
        return 25;
    case 0x8004B52D:
        return 27;
    case 0x8004DD37:
        return 29;
    case 0x80050541:
        return 31;
    case 0x80052D4B:
        return 33;
    case 0x80055555:
        return 35;
    case 0x80057D5F:
        return 37;
    case 0x8005A569:
        return 39;
    case 0x8005CD73:
        return 41;
    case 0x800A7E9F:
        return 43;
    case 0xC0100401:
    case 0xC0B02C0B:
    case 0xC1505415:
    case 0xC1F07C1F:
    case 0xC290A429:
    case 0xC330CC33:
    case 0xC3D0F43D:
    case 0xC4711C47:
    case 0xC5114451:
    case 0xC5B16C5B:
    case 0xC6519465:
    case 0xC6F1BC6F:
    case 0xC791E479:
    case 0xC8320C83:
    case 0xC8D2348D:
    case 0xC9725C97:
    case 0xCA1284A1:
        if ((u16)(value - 10) <= 5 && IsLinkSideStockLearned(0, side)) {
            stockKeys->keys[0] = 50;
            return 50;
        }

        if ((u16)(value - 20) <= 3 && IsLinkSideStockLearned(2, side)) {
            stockKeys->keys[0] = 51;
            return 51;
        }

        break;
    case 0xCAB2ACAB:
        return 7;
    case 0xCB52D4B5:
        return 8;
    case 0xCBF2FCBF:
        return 9;
    case 0xCC9324C9:
        return 10;
    case 0xCD334CD3:
        return 12;
    case 0xCDD374DD:
        return 13;
    case 0xCE739CE7:
        return 45;
    case 0xCFB3ECFB:
        return 14;
    case 0xCF13C4F1:
        return 16;
    case 0xD0541505:
        return 18;
    case 0xD0F43D0F:
        return 20;
    case 0xD1946519:
        return 22;
    case 0xD2348D23:
        return 24;
    case 0xD2D4B52D:
        return 26;
    case 0xD374DD37:
        return 28;
    case 0xD4150541:
        return 30;
    case 0xD4B52D4B:
        return 32;
    case 0xD5555555:
        return 34;
    case 0xD5F57D5F:
        return 36;
    case 0xD695A569:
        return 38;
    case 0xD735CD73:
        return 40;
    case 0xE9FA7E9F:
        return 42;
    case 0xCE739CDD:
        if (IsLinkSideStockLearned(39, side)) {
            return 53;
        }

        break;
    case 0xCE734CDD:
        if (IsLinkSideStockLearned(38, side)) {
            return 54;
        }

        break;
    case 0xCE72ACB5:
        if (IsLinkSideStockLearned(34, side)) {
            return 65;
        }

        break;
    case 0xCAB2AD37:
        if (IsLinkSideStockLearned(32, side)) {
            return 70;
        }

        break;
    case 0xCE734CC9:
        if (IsLinkSideStockLearned(43, side)) {
            return 77;
        }

        break;
    case 0xE95A5695:
        if (gBtlWork->flags & BTL_FLAG_DARK_MODE) {
            if ((u16)(value - 5) <= 10) {
                return 82;
            }

            if ((u16)(value - 16) <= 9) {
                return 83;
            }

            if (value > 26) {
                return 84;
            }
        }

        break;
    case 0xF21C8721:
        return 85;
    case 0xEB3ACEB3:
        return 86;
    case 0xEB3AA6B3:
        return 87;
    case 0xEE5B96E5:
        return 88;
    case 0xEEFB96EF:
        return 89;
    case 0xF49D2735:
        return 90;
    case 0xED1AF6BD:
        return 91;
    case 0xED1B1EC7:
        return 92;
    case 0xF0DBE6F9:
        return 93;
    case 0xF53D7753:
        return 94;
    case 0xF53D4F5D:
        return 95;
    case 0xF5DD4F53:
        return 96;
    case 0xF17C0F03:
        return 97;
    case 0xF35CFF3F:
        return 98;
    case 0xF21CAF21:
        return 99;
    case 0xF71D9F71:
        return 100;
    case 0xF7BDC767:
        return 101;
    case 0xFADEB7A3:
        return 102;
    case 0xFA3EB7A3:
        return 103;
    case 0xF85E3F85:
        return 104;
    case 0xF53D4F53:
        return 105;
    }

    if ((u8)IsTwoSummonsThenKind(cards, count, 43) || (u8)IsSimbaMushuItem(cards, count)) {
        if (IsLinkSideStockLearned(42, side)) {
            return 55;
        }
    }

    if ((u8)IsGenieTinkerBellSummon(cards, count) && IsLinkSideStockLearned(41, side)) {
        return 56;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 23, count) && IsLinkSideStockLearned(27, side)) {
        return 58;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 24, count) && IsLinkSideStockLearned(28, side)) {
        return 59;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 31, count) && IsLinkSideStockLearned(29, side)) {
        return 60;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 18, count) && IsLinkSideStockLearned(23, side)) {
        return 61;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 19, count) && IsLinkSideStockLearned(24, side)) {
        return 62;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 20, count) && IsLinkSideStockLearned(25, side)) {
        return 63;
    }

    if ((u8)IsKindThenTwoAttackCards(cards, 22, count) && IsLinkSideStockLearned(26, side)) {
        return 64;
    }

    if ((u8)IsMegaEtherMegalixirItem(cards, count) && IsLinkSideStockLearned(46, side)) {
        return 66;
    }

    if ((u8)IsFireDonaldMagic(cards, count) && IsLinkSideStockLearned(58, side)) {
        return 67;
    }

    if ((u8)IsSummonMagicJackOrBambiBlizzardItem(cards, count) && IsLinkSideStockLearned(44, side)) {
        return 69;
    }

    if ((u8)IsFireMushuAttack(cards, count) && IsLinkSideStockLearned(31, side)) {
        return 71;
    }

    if ((u8)IsKindThenTwoOfCategory(cards, 25, 0, count) && IsLinkSideStockLearned(35, side)) {
        return 72;
    }

    if ((u8)IsKindThenTwoOfCategory(cards, 27, 0, count) && IsLinkSideStockLearned(50, side)) {
        return 73;
    }

    if ((u8)IsCloudStopAttack(cards, count) && IsLinkSideStockLearned(56, side)) {
        return 74;
    }

    if ((u8)IsAeroFireMagic(cards, count) && IsLinkSideStockLearned(30, side)) {
        return 75;
    }

    if ((u8)IsAeroBlizzardMagic(cards, count) && IsLinkSideStockLearned(33, side)) {
        return 76;
    }

    if ((u8)IsKindPairThenNonSummonOfCategory(cards, count, 22, 23, 1) && IsLinkSideStockLearned(40, side)) {
        return 78;
    }

    if ((u8)IsKindPairThenSummon(cards, count, 24, 22) && IsLinkSideStockLearned(36, side)) {
        return 79;
    }

    if ((u8)IsKindPairThenNonSummonOfCategory(cards, count, 22, 25, 1) && IsLinkSideStockLearned(37, side)) {
        return 80;
    }

    if ((u8)IsTwoMagicThenPeterPan(cards, count) && IsLinkSideStockLearned(45, side)) {
        return 81;
    }

    if ((u8)IsThreeDistinctAttackCards(cards, count)) {
        if ((u16)(value - 10) <= 5 && IsLinkSideStockLearned(1, side)) {
            stockKeys->keys[0] = 46;
            return 46;
        }

        if ((u16)(value - 20) <= 3 && IsLinkSideStockLearned(5, side)) {
            stockKeys->keys[0] = 5;
            return 5;
        }
    }

    if ((u8)IsThreeAttackCardsNoMove18(cards, count)) {
        if ((u16)(value - 1) <= 5 && IsLinkSideStockLearned(6, side)) {
            stockKeys->keys[0] = 47;
            return 47;
        }

        if ((u16)(value - 24) <= 2 && IsLinkSideStockLearned(4, side)) {
            stockKeys->keys[0] = 6;
            return 6;
        }

        if ((u16)(value - 7) <= 2 && IsLinkSideStockLearned(7, side)) {
            stockKeys->keys[0] = 48;
            return 48;
        }

        if (value == 0 || value == 27) {
            if (IsLinkSideStockLearned(3, side)) {
                stockKeys->keys[0] = 52;
                return 52;
            }
        }
    }

    if ((u8)IsAttackDonaldGoofyAnyOrder(cards, count) && IsLinkSideStockLearned(8, side)) {
        stockKeys->keys[0] = 49;
        return 49;
    }

    *flag = matchCount;

    if (matchCount == 0) {
        return 106;
    }

    if (matchCount == 1) {
        return stockKeys->keys[0];
    }

    return 107;
}

s32 IsThreeDistinctAttackCards(CardDisplayWork** cards, u8 count) {
    const CardDef* firstDef;
    const CardDef* secondDef;
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;
    u16 thirdKind;

    if (count == 3) {
        firstDef = cards[0]->cardDef;
        firstKind = firstDef->kind;
        secondDef = cards[1]->cardDef;
        secondKind = secondDef->kind;
        thirdDef = cards[2]->cardDef;
        thirdKind = thirdDef->kind;

        if (firstDef->category == 0 && secondDef->category == 0 && thirdDef->category == 0 &&
            firstKind != secondKind && firstKind != thirdKind && secondKind != thirdKind) {
            return 1;
        }
    }

    return 0;
}

s32 IsThreeAttackCardsNoMove18(CardDisplayWork** cards, u8 count) {
    const CardDef* firstDef;
    const CardDef* secondDef;
    const CardDef* thirdDef;

    if (count == 3) {
        firstDef = cards[0]->cardDef;
        secondDef = cards[1]->cardDef;
        thirdDef = cards[2]->cardDef;

        if (firstDef->move != 18 && secondDef->move != 18 && thirdDef->move != 18 &&
            firstDef->category == 0 && secondDef->category == 0 && thirdDef->category == 0) {
            return 1;
        }
    }

    return 0;
}

s32 IsAttackDonaldGoofyAnyOrder(CardDisplayWork** cards, u8 count) {
    const CardDef* firstDef;
    u16 firstKind;
    u16 secondKind;
    u16 thirdKind;

    if (count == 3) {
        firstDef = cards[0]->cardDef;
        firstKind = firstDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdKind = cards[2]->cardDef->kind;

        if (firstKind != secondKind && secondKind != thirdKind && thirdKind != firstKind) {
            if (firstDef->category == 0) {
                if (secondKind == 39 && thirdKind == 40) {
                    return 1;
                }

                if (secondKind == 40 && thirdKind == 39) {
                    return 1;
                }
            }

            if (cards[1]->cardDef->category == 0) {
                if (firstKind == 39 && thirdKind == 40) {
                    return 1;
                }

                if (firstKind == 40 && thirdKind == 39) {
                    return 1;
                }
            }

            if (cards[2]->cardDef->category == 0) {
                if (secondKind == 39 && firstKind == 40) {
                    return 1;
                }

                if (secondKind == 40 && firstKind == 39) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

s32 IsKindPairThenNonSummonOfCategory(CardDisplayWork** cards, u8 count, u16 firstKind, u16 secondKind, u8 category) {
    // @bug Outside EU, reads three cards even when fewer are stocked (NULL read).
    if (
#ifdef VERSION_EU
        count == 3 &&
#endif
        cards[0]->cardDef->kind == firstKind && cards[1]->cardDef->kind == secondKind &&
        cards[2]->cardDef->category == category && !(cards[2]->cardDef->flags & CARD_DEF_FLAG_SUMMON)) {
        return 1;
    }

    return 0;
}

s32 IsKindPairThenSummon(CardDisplayWork** cards, u8 count, u16 firstKind, u16 secondKind) {
    // @bug Outside EU, reads three cards even when fewer are stocked (NULL read).
    if (
#ifdef VERSION_EU
        count == 3 &&
#endif
        cards[0]->cardDef->kind == firstKind && cards[1]->cardDef->kind == secondKind &&
        (cards[2]->cardDef->flags & CARD_DEF_FLAG_SUMMON)) {
        return 1;
    }

    return 0;
}

s32 IsKindThenTwoAttackCards(CardDisplayWork** cards, u16 kind, u8 count) {
    const CardDef* secondDef;
    const CardDef* thirdDef;
    u16 firstKind;
    u8 secondCategory;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondDef = cards[1]->cardDef;
        thirdDef = cards[2]->cardDef;
        secondCategory = secondDef->category;
        thirdCategory = thirdDef->category;

        if (secondCategory == 0 && thirdCategory == 0 && firstKind == kind) {
            return 1;
        }
    }

    return 0;
}

s32 IsKindThenTwoOfCategory(CardDisplayWork** cards, u16 kind, u8 category, u8 count) {
    const CardDef* secondDef;
    const CardDef* thirdDef;
    u16 firstKind;
    u8 secondCategory;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondDef = cards[1]->cardDef;
        thirdDef = cards[2]->cardDef;
        secondCategory = secondDef->category;
        thirdCategory = thirdDef->category;

        if (firstKind == kind && secondCategory == category && thirdCategory == secondCategory) {
            return 1;
        }
    }

    return 0;
}

#ifndef VERSION_EU
s32 IsAnyThenTwoGenie(CardDisplayWork** cards, u8 count) {
    u16 firstKind;
    u16 secondKind;
    u16 thirdKind;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdKind = cards[2]->cardDef->kind;

        if (secondKind == thirdKind && secondKind == 26 && firstKind != 26) {
            return 1;
        }
    }

    return 0;
}
#endif

s32 IsFireMushuAttack(CardDisplayWork** cards, u8 count) {
    u16 firstKind;
    u16 secondKind;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;

        if (firstKind == 18 && secondKind == 30 && cards[2]->cardDef->category == 0) {
            return 1;
        }
    }

    return 0;
}

s32 IsTwoSummonsThenKind(CardDisplayWork** cards, u8 count, u16 kind) {
    u16 firstFlags;
    u16 secondFlags;

    if (count == 3) {
        firstFlags = cards[0]->cardDef->flags;
        secondFlags = cards[1]->cardDef->flags;

        if ((firstFlags & 4) && (secondFlags & 4) && cards[2]->cardDef->kind == kind) {
            return 1;
        }
    }

    return 0;
}

s32 IsSimbaMushuItem(CardDisplayWork** cards, u8 count) {
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;

        if (firstKind == 25 && secondKind == 30) {
            thirdDef = cards[2]->cardDef;

            if (thirdDef->category == 2 && !(thirdDef->flags & CARD_DEF_FLAG_FRIEND)) {
                return 1;
            }
        }
    }

    return 0;
}

s32 IsSummonMagicJackOrBambiBlizzardItem(CardDisplayWork** cards, u8 count) {
    const CardDef* secondDef;
    u16 firstFlags;
    u16 secondFlags;

    if (count == 3) {
        firstFlags = cards[0]->cardDef->flags;
        secondDef = cards[1]->cardDef;
        secondFlags = secondDef->flags;

        if ((firstFlags & 4) && secondFlags == 0 && secondDef->category == 1 &&
            cards[2]->cardDef->kind == CARD_KIND_JACK) {
            return 1;
        }

        if (cards[0]->cardDef->kind == CARD_KIND_BAMBI && cards[1]->cardDef->kind == CARD_KIND_BLIZZARD &&
            cards[2]->cardDef->category == 2 && !(cards[2]->cardDef->flags & CARD_DEF_FLAG_FRIEND)) {
            return 1;
        }
    }

    return 0;
}

s32 IsGenieTinkerBellSummon(CardDisplayWork** cards, u8 count) {
    u16 firstKind;
    u16 secondKind;
    u16 thirdFlags;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdFlags = cards[2]->cardDef->flags;

        if (firstKind == 26 && secondKind == 29 && (thirdFlags & 4)) {
            return 1;
        }
    }

    return 0;
}

s32 IsMegaEtherMegalixirItem(CardDisplayWork** cards, u8 count) {
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdDef = cards[2]->cardDef;
        thirdCategory = thirdDef->category;

        if (firstKind == 36 && secondKind == 38 && thirdCategory == 2 && !(thirdDef->flags & CARD_DEF_FLAG_FRIEND)) {
            return 1;
        }
    }

    return 0;
}

s32 IsFireDonaldMagic(CardDisplayWork** cards, u8 count) {
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdDef = cards[2]->cardDef;
        thirdCategory = thirdDef->category;

        if (firstKind == 18 && secondKind == 39 && thirdCategory == 1 && !(thirdDef->flags & CARD_DEF_FLAG_SUMMON)) {
            return 1;
        }
    }

    return 0;
}

s32 IsCloudStopAttack(CardDisplayWork** cards, u8 count) {
    u16 firstKind;
    u16 secondKind;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdCategory = cards[2]->cardDef->category;

        if (firstKind == 31 && secondKind == 23 && thirdCategory == 0) {
            return 1;
        }
    }

    return 0;
}

s32 IsAeroFireMagic(CardDisplayWork** cards, u8 count) {
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdDef = cards[2]->cardDef;
        thirdCategory = thirdDef->category;

        if (firstKind == 24 && secondKind == 18 && thirdCategory == 1 && !(thirdDef->flags & CARD_DEF_FLAG_SUMMON)) {
            return 1;
        }
    }

    return 0;
}

s32 IsAeroBlizzardMagic(CardDisplayWork** cards, u8 count) {
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;
    u8 thirdCategory;

    if (count == 3) {
        firstKind = cards[0]->cardDef->kind;
        secondKind = cards[1]->cardDef->kind;
        thirdDef = cards[2]->cardDef;
        thirdCategory = thirdDef->category;

        if (firstKind == 24 && secondKind == 19 && thirdCategory == 1 && !(thirdDef->flags & CARD_DEF_FLAG_SUMMON)) {
            return 1;
        }
    }

    return 0;
}

s32 IsTwoMagicThenPeterPan(CardDisplayWork** cards, u8 count) {
    const CardDef* firstDef;
    const CardDef* secondDef;
    const CardDef* thirdDef;
    u16 firstKind;
    u16 secondKind;
    u16 thirdKind;
    u8 firstCategory;
    u8 secondCategory;
    u8 thirdCategory;

    if (count == 3) {
        firstDef = cards[0]->cardDef;
        firstKind = firstDef->kind;
        secondDef = cards[1]->cardDef;
        secondKind = secondDef->kind;
        thirdDef = cards[2]->cardDef;
        thirdKind = thirdDef->kind;
        firstCategory = firstDef->category;
        secondCategory = secondDef->category;
        thirdCategory = thirdDef->category;

        if (firstCategory == 1 && !(firstDef->flags & CARD_DEF_FLAG_SUMMON) && secondCategory == 1 && !(secondDef->flags & CARD_DEF_FLAG_SUMMON) &&
            thirdKind == 44) {
            return 1;
        }

        if (firstKind == 23 && secondKind == 24 && thirdCategory == 2 && !(cards[2]->cardDef->flags & CARD_DEF_FLAG_FRIEND)) {
            return 1;
        }
    }

    return 0;
}

u8 IsLinkSideStockLearned(s32 stock, s32 side) {
    u8 learned;

    if (side != 0) {
        learned = IsLinkPartnerStockLearned(stock);
    } else {
        learned = IsLinkStockLearned(stock);
    }

    return learned;
}

s32 LookupStockPairName(StockKeys* cards, u8* output, u8 count) {
    u32 catalogNumbers[6];

    catalogNumbers[0] = cards->keys[0];
    catalogNumbers[1] = cards->keys[1];
    catalogNumbers[2] = cards->keys[2];

    switch ((catalogNumbers[1] << 10) | catalogNumbers[0] | 0x80000000) {
    case 0x8002ACAB:
        return 0;
    case 0x8002D4B5:
        return 1;
    case 0x8002FCBF:
        return 2;
    case 0x800324C9:
        return 3;
    case 0x80034CD3:
        return 11;
    case 0x800374DD:
        return 4;
    case 0x80039CE7:
        return 44;
    case 0x8003ECFB:
        return 15;
    case 0x8003C4F1:
        return 17;
    case 0x80041505:
        return 19;
    case 0x80043D0F:
        return 21;
    case 0x80046519:
        return 23;
    case 0x80048D23:
        return 25;
    case 0x8004B52D:
        return 27;
    case 0x8004DD37:
        return 29;
    case 0x80050541:
        return 31;
    case 0x80052D4B:
        return 33;
    case 0x80055555:
        return 35;
    case 0x80057D5F:
        return 37;
    case 0x8005A569:
        return 39;
    case 0x8005CD73:
        return 41;
    case 0x800A7E9F:
        return 43;
    }

    switch (catalogNumbers[1] | (catalogNumbers[2] << 10) | 0x80000000) {
    case 0x8002ACAB:
        return 0;
    case 0x8002D4B5:
        return 1;
    case 0x8002FCBF:
        return 2;
    case 0x800324C9:
        return 3;
    case 0x80034CD3:
        return 11;
    case 0x800374DD:
        return 4;
    case 0x80039CE7:
        return 44;
    case 0x8003ECFB:
        return 15;
    case 0x8003C4F1:
        return 17;
    case 0x80041505:
        return 19;
    case 0x80043D0F:
        return 21;
    case 0x80046519:
        return 23;
    case 0x80048D23:
        return 25;
    case 0x8004B52D:
        return 27;
    case 0x8004DD37:
        return 29;
    case 0x80050541:
        return 31;
    case 0x80052D4B:
        return 33;
    case 0x80055555:
        return 35;
    case 0x80057D5F:
        return 37;
    case 0x8005A569:
        return 39;
    case 0x8005CD73:
        return 41;
    case 0x800A7E9F:
        return 43;
    }

    return 106;
}

Mode gModeRikuBtlTutorial = {
    "Mode_riku_btlTutorial",
    RikuTutorialModeInit,
    Mode_riku_btlTutorial_1,
    RikuTutorialModeDestroy,
};

Mode gModeRikuDeckTutorial = {
    "Mode_riku_deckTutorial",
    RikuTutorialModeInit,
    Mode_riku_deckTutorial_1,
    RikuTutorialModeDestroy,
};

const StockKeys gTutorialEmptyKeys = {
    { -1, -1, -1, -1, -1, -1 },
};
