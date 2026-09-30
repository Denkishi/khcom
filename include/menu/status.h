#ifndef GUARD_STATUS_H
#define GUARD_STATUS_H

#include "anim.h"
#include "types.h"
#include "text_types.h"
#include "taskpool.h"

typedef struct StatusEntry {
    s32 items[72];
    u16 count;
    u16 unk_122;
} StatusEntry;

typedef struct StatusBarWork {
    void* tiles;
    void* palette;
    u16 steps;
    u16 unk_0A;
    s32 y;
    s32 targetY;
    s32 y2;
    s32 targetY2;
    s32 x;
    s32 targetX;
    u8 closing;
    u8 fadeStarted;
    u8 unk_26[0x6];
} StatusBarWork;

typedef struct StatusTabWork {
    void* tiles;
    void* tiles2;
    void* palette;
    void* palette2;
    void* gfx;
    void* gfx2;
    s32* tab;
} StatusTabWork;

typedef struct StatusSoraWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
} StatusSoraWork;

typedef struct StatusDecknameWork {
    TextSlot textSlots[10];
    void* palette;
    u8 textSlotCount;
    u8 unk_55[0x3];
    u8* mesWindowOpen;
} StatusDecknameWork;

typedef struct StatusCursorWork {
    void* tiles;
    void* tiles2;
    void* palette;
    void* palette2;
    void* gfx[2];
    AnimState anim[2];
    s16* cursor;
    s16 lastCursor;
    u16 unk_4E;
    s32 y;
    s32 targetY;
    s32 x;
    s32 targetX;
} StatusCursorWork;

typedef struct StatusScrollcursorWork {
    void* tiles;
    void* palette;
    void* gfx;
    u16* scroll;
    u16 unk_10;
    s16 y;
} StatusScrollcursorWork;

typedef struct StatusMeswindowWork {
    TaskPool pool;
    void* task;
    s32 item;
    u8* open;
    u8 textIndex;
    u8 unk_21[3];
} StatusMeswindowWork;

typedef struct StatusMessageParam {
    void* text;
    s16 x;
    s16 y;
} StatusMessageParam;

typedef struct StatusMessageWork {
    TextSlot textSlots[100];
    u8 textSlotCount;
    u8 unk_321[3];
    void* palette;
    StatusMessageParam param;
} StatusMessageWork;

typedef struct StatusFriendWork {
    void* tiles[3];
    void* palette[3];
    void* gfx[3];
    u16 count;
    u16 unk_26;
} StatusFriendWork;

typedef struct StatusMesParam {
    u32 x : 16;
    u32 y : 16;
    u32 textIndex : 8;
    u32 unk_04_08 : 8;
    u32 helpIndex : 16;
} StatusMesParam;

typedef struct StatusFriendEntry {
    u16 flag;
    u16 cardId;
} StatusFriendEntry;

typedef struct StatusFriendTable {
    StatusFriendEntry entries[8];
} StatusFriendTable;

typedef struct StockMesDispWork {
    void* tiles;
    void* palette;
    void* tiles2;
    void* tiles3;
    void* palette2;
    void* palette3;
    void* gfx;
    void* gfx2;
    u16 frame;
    u16 unk_22;
    TaskPool tasks;
    void* task;
    u16 x;
    u16 y;
    u8 textIndex;
    u8 unk_41;
    u16 helpIndex;
    u8 textCount;
    u8 unk_45[3];
} StockMesDispWork;

typedef struct StatusWork {
    TaskPool pool;
    u32 tab;
    u16 unk_18;
    s16 cursor;
    s16 scroll;
    u16 unk_1E;
} StatusWork;

typedef struct StatusStocklistWork {
    StatusEntry entries[4];
    void* tiles2[8];
    void* palette;
    void* tiles;
    void* palette2;
    void* gfx;
    s32* tab;
    u16 scroll;
    u16 timer;
    u8 blink;
    u8 unk_4C9[3];
} StatusStocklistWork;

extern s32 gStatusBarState;

extern u8 gBStatesPalette[];
extern u8 gUnk_097A2CF6[];
extern u8 gUnk_097A2E16[];
extern u8 gUnk_097A2DF8[];
extern u8 gUnk_097A18EC[];
extern u8 gUnk_097A18CC[];
extern u8 gUnk_097A1864[];
extern u8 gUnk_097A1898[];
extern u8 gUnk_097A24A6[];
extern u8 gUnk_097A28DA[];
extern u8 gRikuPalette[];
extern u8 gRikuBt00Tiles[];
extern u8 gSoraPalette[];
extern u8 gSor1ll51Tiles[];
extern u8 gUnk_097A1C54[];
extern u8 gUnk_097A2394[];

u8 IsStatusBarIdle(void);
void StatusHandleInput(StatusWork* work);
s16 GetStatusScroll(void);
u16 GetStatusVisibleRowCount(void);
u16 GetStatusMaxScroll(void);
u8 StatusTabHasItems(void);
void StatusStocklistLoadRows(u16 a);
s32 GetStatusListItem(s16 a);
void StatusEntryClear(StatusEntry* e);
void StatusEntryAppend(StatusEntry* e, s32 v);
s32 GetStatusItemTab(u32 a);
void* GetCardHelpText(u16 a, u8 b);
u8 GetCardHelpTextCount(u16 a);
void* LoadStockNameTiles(u16 a);
s32 GetStatusItemStockIndex(s32 a);
s16 GetStatusScrollcursorY(StatusScrollcursorWork* work);
void StatusStocklistScrollDown(void);
void* CreateStockMesDispTask(void* a, u16 b, u8 c, u16 d, s32 e);
u8 GetStockMesDispTextIndex(void* a);

void StatusBarStartClose(StatusBarWork* work);
u8 IsStatusMesWindowOpen(void);
void StatusStocklistScrollUp(void);

void task_status_0(StatusWork* work);
u8 task_status_1(StatusWork* work);
void task_status_2(StatusWork* work);
void task_status_3(StatusWork* work);
void task_status_bar_0(StatusBarWork* work);
u8 task_status_bar_1(StatusBarWork* work);
void task_status_bar_2(StatusBarWork* work);
void task_status_bar_3(StatusBarWork* work);
void task_status_tab_0(StatusTabWork* work, s32* arg);
u8 task_status_tab_1(StatusTabWork* work);
void task_status_tab_2(StatusTabWork* work);
void task_status_tab_3(StatusTabWork* work);
void task_status_sora_0(StatusSoraWork* work);
u8 task_status_sora_1(StatusSoraWork* work);
void task_status_sora_2(StatusSoraWork* work);
void task_status_sora_3(StatusSoraWork* work);
void task_status_deckname_0(StatusDecknameWork* work, u8* arg);
u8 task_status_deckname_1(StatusDecknameWork* work);
void task_status_deckname_2(StatusDecknameWork* work);
void task_status_deckname_3(StatusDecknameWork* work);
void task_status_cursor_0(StatusCursorWork* work, s16* arg);
u8 task_status_cursor_1(StatusCursorWork* work);
void task_status_cursor_2(StatusCursorWork* work);
void task_status_cursor_3(StatusCursorWork* work);
void task_status_stocklist_0(StatusStocklistWork* work, s32* arg);
u8 task_status_stocklist_1(StatusStocklistWork* work);
void task_status_stocklist_2(StatusStocklistWork* work);
void task_status_stocklist_3(StatusStocklistWork* work);
void task_status_scrollcursor_0(StatusScrollcursorWork* work, u16* arg);
u8 task_status_scrollcursor_1(StatusScrollcursorWork* work);
void task_status_scrollcursor_2(StatusScrollcursorWork* work);
void task_status_scrollcursor_3(StatusScrollcursorWork* work);
void task_status_meswindow_0(StatusMeswindowWork* work, u8* arg);
u8 task_status_meswindow_1(StatusMeswindowWork* work);
void task_status_meswindow_2(StatusMeswindowWork* work);
void task_status_meswindow_3(StatusMeswindowWork* work);
void task_status_message_0(StatusMessageWork* work, StatusMessageParam* arg);
u8 task_status_message_1(StatusMessageWork* work);
void task_status_message_2(StatusMessageWork* work);
void task_status_message_3(StatusMessageWork* work);
void task_status_friend_0(StatusFriendWork* work);
u8 task_status_friend_1(StatusFriendWork* work);
void task_status_friend_2(StatusFriendWork* work);
void task_status_friend_3(StatusFriendWork* work);

#endif /* GUARD_STATUS_H */
