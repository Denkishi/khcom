#include "registration_data.h"
#include "battle_actor_types.h"
#ifndef GUARD_BOS4_H
#define GUARD_BOS4_H

#include "boss_boogie.h"

#include "map_text_data.h"

#include "battle_bg_types.h"

#include "map_types.h"

#include "prize_types.h"

#include "card_api.h"

#include "map_api.h"
#include "msg_api.h"
#include "mode_test_api.h"

#include "save_api.h"

#include "player_progression.h"

#include "m4a_song.h"
#include <string.h>
#include "fade.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "types.h"
#include "malloc.h"
#include "engine_math.h"
#include "listpool.h"
#include "battle_work.h"
#include "game_state.h"
#include "anim.h"
#include "mode.h"
#include "key.h"
#include "taskpool.h"
#include "bos4_api.h"
#include "map_runtime.h"
#include "poo_api.h"
#include "btl_api.h"

extern UnkStruct_0203C590 gUnk_0203C590;

extern const UnkStruct_096FE034Entry gUnk_096FE020[5];
extern const UnkStruct_096FE034 gUnk_096FE034;
extern const UnkStruct_096FE034 gUnk_096FE04C;
extern const UnkStruct_096FE034 gUnk_096FE064;

typedef struct BoogieExplosiondiceWork {
    u32 unk_000;
    u16 unk_004;
    u8 unk_006[0x2];
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    TaskPool tasks;
    BtlObj obj;
    u32 unk_150;
    u32 unk_154;
    u8 unk_158;
    u8 unk_159[0x3];
    BoogieWork* boogie;
} BoogieExplosiondiceWork;

typedef struct BoogieDiskWork {
    u32 state;
    u16 timer;
    u8 unk_006[0x2];
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    TaskPool tasks;
    BtlObj obj;
    s32 unk_150;
    s32 unk_154;
    s32 unk_158;
    u8 unk_15C;
    u8 unk_15D[0x3];
} BoogieDiskWork;

typedef struct UrsulaWork {
    u32 state;
    u16 unk_004;
    u8 unk_006[0x2];
    TaskPool tasks;
    Task* tako;
    Task* tako2;
    BtlObj obj;
    const u16** mapBlocks;
    s32 unk_138;
    s32 unk_13C;
    u16 unk_140;
    u16 unk_142;
    u8 unk_144[0x4];
    u32 unk_148;
    u32 unk_14C;
    u32 unk_150;
    u32 unk_154;
    u16 unk_158;
    u16 unk_15A;
    u16 unk_15C;
    u16 unk_15E;
    u8 unk_160;
    u8 unk_161[0x3];
} UrsulaWork;

typedef struct BoogieMapanimeWork {
    UnkStruct_080DDDDC unk_000[3];
} BoogieMapanimeWork;

typedef struct UrsulaThunderWork {
    u16 unk_000;
    u8 unk_002[0x2];
    s32 x;
    s32 y;
    s32 z;
} UrsulaThunderWork;

void func_080DD69C(s32 a);

u8 func_080DD754(void);
u8 func_080DD794(void);

u16 func_080DBE64(void);
u8 func_080DA4DC(BoogieExplosiondiceWork* work);
u8 func_080DDE74(UnkStruct_080DDDDC* p);
void task_bos_boogie_explosiondice_3(BoogieExplosiondiceWork* work);
void task_bos_boogie_disk_3(BoogieDiskWork* work);
void task_bos_ursula_3(UrsulaWork* work);
void task_bos_boogie_mapanime_0(BoogieMapanimeWork* work);
void task_bos_ursula_thunder_0(UrsulaThunderWork* work);
u8 task_bos_ursula_thunder_1(UrsulaThunderWork* work);

extern UnkStruct_0203C7AC* gUnk_0203C7AC;

typedef struct UrsulaBubbleSingleWork {
    void* tiles;
    void* palette;
    void* palette2;
#ifndef VERSION_EU
    AnimState anim;
#endif
    BtlObj obj;
    u16 timer;
    u8 unk_136[0x2];
    u32 unk_138;
    u16 angle;
    u16 targetAngle;
    s32 unk_140;
    u8 unk_144[0x4];
} UrsulaBubbleSingleWork;

void task_bos_ursula_bubble_single_3(UrsulaBubbleSingleWork* work);

typedef struct BoogieKnifereaderWork {
    u32 state;
    u16 timer;
    u8 unk_006[0x2];
    TaskPool tasks;
    BtlObj obj;
    Task* knives[5];
} BoogieKnifereaderWork;

typedef struct UrsulaBubbleWork {
    u32 unk_000;
    TaskPool tasks;
    Task* bubbles[10];
    u16 bubbleCount;
    u8 unk_042[0x2];
#ifdef VERSION_EU
    AnimState anim;
#endif
} UrsulaBubbleWork;

typedef struct UrsulaTakoWork {
    void* tiles;
    void* palette;
    void* palette2;
    AnimState anim;
    u16 unk_024;
    u8 unk_026[0x2];
    BtlObj obj;
    u32 state;
    u16 unk_13C;
    u8 unk_13E;
    u8 unk_13F[0x1];
    Collider collider;
    Collider collider2;
    s32 unk_1F8;
    s32 unk_1FC;
    s32 unk_200;
} UrsulaTakoWork;

extern u8 gUnk_0979D0B6[];
extern const UnkStruct_096FE034Entry gUnk_096FE1EC[6];
extern const UnkStruct_096FE034Entry gUnk_096FE204[12];
extern const UnkStruct_096FE034Entry gUnk_096FE234[5];
extern const UnkStruct_096FE034Entry gUnk_096FE248[5];
extern const UnkStruct_096FE034Entry gUnk_096FE25C[1];
extern const UnkStruct_096FE034 gUnk_096FE278;
extern const UnkStruct_096FE034 gUnk_096FE290;
extern const UnkStruct_096FE034 gUnk_096FE2A8;
extern u8 gUnk_0984B0D8[];

extern EventKeyList gEventKeyLists[];

extern const u8 gUnk_0984D0CC[][4];

typedef struct BoogieMapWork {
    u32 unk_00;
} BoogieMapWork;

void task_bos_boogie_map_0(BoogieMapWork* work, BattleBackgroundDef* arg);

extern const EmyKind gBosBoogieKnifereaderEmyKind;
u8 func_080DABFC(s32* x, s32* y, s16 w, s16 h, s32 z);
void task_bos_boogie_dice_3(BoogieDiceWork* work);

extern const u8 gUnk_0984D134[][8];
extern u8 gSakuTiles[];
extern u8 gBoss02objPalette[];
extern UrsulaWork* gUrsulaWork;

void func_080DB978(UrsulaWork* work);
void task_bos_ursula_2(UrsulaWork* work);
u16 func_080DD7C4(UrsulaBubbleWork* work);
u16 func_080DD854(UrsulaBubbleWork* work);
void task_bos_ursula_bubble_0(UrsulaBubbleWork* work);
u16 func_080DD8A8(UrsulaBubbleWork* work);
u8 task_bos_boogie_mapanime_1(BoogieMapanimeWork* work);

u8 func_080DBA14(UrsulaWork* work);
u8 func_080DBC68(UrsulaWork* work);
void func_080DBC00(UrsulaWork* work);
s32 func_080DBCC0(UrsulaWork* work);
s32 func_080DBCEC(UrsulaWork* work);
s32 func_080DBDC0(UrsulaWork* work);
void func_080DBDEC(UrsulaWork* work);
void func_080DBE18(UrsulaWork* work);
void task_bos_ursula_tako_3(UrsulaTakoWork* work);
u8 func_080DD1FC(UrsulaTakoWork* work);
void func_080DD210(UrsulaTakoWork* work);
u8 func_080DD230(UrsulaTakoWork* work);
void func_080DD9B0(UrsulaBubbleWork* work);

typedef struct UrsulaMapanimeWork {
    UnkStruct_080DDDDC unk_000;
    u32 unk_00C;
    TaskPool tasks;
    Task* task;
    u8 unk_028;
    u8 unk_029[0x3];
} UrsulaMapanimeWork;

typedef struct UrsulaMapWork {
    s32 unk_00;
    s32 unk_04;
    u16 unk_08;
    u8 unk_0A[0x2];
} UrsulaMapWork;

typedef struct UrsulaBorderWork {
    ObjTiles* tiles;
    ObjPalette* palette;
} UrsulaBorderWork;

void task_bos_ursula_map_0(UrsulaMapWork* work, BattleBackgroundDef* arg);
u8 task_bos_ursula_map_1(UrsulaMapWork* work);

typedef struct BoogieSakuWork {
    ObjTiles* tiles;
    ObjPalette* palette;
    AnimState anim;
    u16 unk_020;
    u8 unk_022[0x2];
    BoogieWork* boogie;
    TaskPool tasks;
    Task* task;
    u8 unk_040;
    u8 unk_041[0x3];
} BoogieSakuWork;

typedef struct BoogieKnifeWork {
    u32 state;
    u16 timer;
    u8 unk_006[0x2];
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    BtlObj obj;
    s32 unk_13C;
    s32 unk_140;
    u8 unk_144[0x4];
    u32 scaleX;
    u32 unk_14C;
    s32 unk_150;
    s32 unk_154;
} BoogieKnifeWork;

typedef struct UrsulaBacktakoWork {
    ObjTiles* tiles;
    ObjPalette* palette;
    AnimState anim;
    u16 unk_020;
    u8 unk_022;
    u8 unk_023[0x1];
    u32 unk_024;
    u32 unk_028;
    u32 x;
    u32 y;
    u32 z;
    u32 x2;
    u32 y2;
    u32 z2;
} UrsulaBacktakoWork;

typedef struct BoogieKaihukuWork {
    u32 state;
    u16 timer;
    u8 unk_006[0x2];
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    AnimState anim;
    u8 unk_02C[0x14];
    BtlObj obj;
    u32 unk_150;
    BoogieWork* boogie;
} BoogieKaihukuWork;

u16 func_080DDEA0(UnkStruct_080DDDDC* p);
u8 func_080DC510(void);
u8 func_080DC528(void);
u8 func_080DC544(void);
u8 func_080DC578(void);
u8 func_080DC5B0(void);
u32 func_080DC5E8(void);
u8 func_080DA73C(void);
u8 func_080DB428(BoogieKnifeWork* work);
u8 func_080DC628(void);
s32 func_080DCA78(u8 a);
void task_bos_ursula_border_0(UrsulaBorderWork* work);
void task_bos_ursula_border_3(UrsulaBorderWork* work);
u8 task_bos_ursula_backtako_1(UrsulaBacktakoWork* work);
void task_bos_ursula_backtako_3(UrsulaBacktakoWork* work);
void func_080DA954(BoogieSakuWork* work, s32 a, u16 b);
void task_bos_boogie_saku_0(BoogieSakuWork* work, BoogieWork* arg);
void task_bos_boogie_saku_3(BoogieSakuWork* work);
void task_bos_boogie_knife_3(BoogieKnifeWork* work);
u8 func_080DB438(BoogieKnifereaderWork* work);
void task_bos_boogie_kaihuku_3(BoogieKaihukuWork* work);

void task_bos_boogie_knifereader_0(BoogieKnifereaderWork* work);
void task_bos_boogie_knifereader_2(BoogieKnifereaderWork* work);
void task_bos_boogie_knifereader_3(BoogieKnifereaderWork* work);
void task_bos_boogie_mapanime_2(void);
void task_bos_boogie_mapanime_3(void);
void task_bos_ursula_thunder_2(void);
void task_bos_ursula_thunder_3(void);
void task_bos_ursula_map_3(void);
s32 task_bos_ursula_border_1(void);
void func_080DDD30(UrsulaBubbleSingleWork* work);
u8 task_bos_ursula_bubble_1(UrsulaBubbleWork* work);
void task_bos_ursula_bubble_2(UrsulaBubbleWork* work);
void task_bos_ursula_bubble_3(UrsulaBubbleWork* work);

void task_bos_ursula_mapanime_0(UrsulaMapanimeWork* work);
u8 task_bos_ursula_mapanime_1(UrsulaMapanimeWork* work);
void task_bos_ursula_mapanime_2(UrsulaMapanimeWork* work);
void task_bos_ursula_mapanime_3(UrsulaMapanimeWork* work);

void task_bos_ursula_tako_2(UrsulaTakoWork* work);
void task_bos_ursula_tako_0(UrsulaTakoWork* work, u8* arg);
u8 task_bos_ursula_tako_1(UrsulaTakoWork* work);
extern const EmyKind gBosUrsulaTakoEmyKind;
u8 task_bos_boogie_explosiondice_1(BoogieExplosiondiceWork* work);
void task_bos_boogie_kaihuku_2(BoogieKaihukuWork* work);

void func_080DB04C(BoogieKnifeWork* work);

u8 task_bos_ursula_bubble_single_1(UrsulaBubbleSingleWork* work);
void task_bos_ursula_0(UrsulaWork* work);
extern const BattleBackgroundDef gBosUrsulaBattleBackgroundDef;
extern const EmyKind gBosUrsulaEmyKind;
extern const EmyKind gBosBoogieDiskEmyKind;
extern u8 gNokogiriTiles[];
u8 task_bos_boogie_saku_1(BoogieSakuWork* work);

void task_bos_boogie_dice_0(BoogieDiceWork* work, BoogieWork* arg);
u8 task_bos_boogie_dice_1(BoogieDiceWork* work);
u8 ClampBoogieDicePosition(s32* a, s32* b, s16 c, u16 d);
void func_080D9B6C(BoogieDiceWork* work);

extern u8 gUnk_09796EAA[];
u8 task_bos_boogie_kaihuku_1(BoogieKaihukuWork* work);

extern const UnkStruct_096FE034 gUnk_096FE260;

void task_bos_boogie_knife_0(BoogieKnifeWork* work, s32* arg);
extern u8 gKnifeTiles[];
extern u8 gKnifePalette[];

void task_bos_boogie_disk_0(BoogieDiskWork* work, BtlObj* arg);
u8 task_bos_boogie_disk_1(BoogieDiskWork* work);
u8 task_bos_boogie_knifereader_1(BoogieKnifereaderWork* work);
u8 task_bos_boogie_knife_1(BoogieKnifeWork* work);
void task_bos_boogie_knife_2(BoogieKnifeWork* work);
void task_bos_boogie_explosiondice_0(BoogieExplosiondiceWork* work, BoogieWork* arg);
extern u8 gUnk_0979666A[];
extern u8 gUnk_0984AF98[];

extern const EmyKind gUnk_096FDFC4;
extern const EmyKind gUnk_096FE0C0;
extern const EmyKind gUnk_096FDF54;
u8 task_bos_boogie_map_1(void);

void task_bos_boogie_dice_2(BoogieDiceWork* work);
u8 func_080D9B28(BoogieDiceWork* work);
void task_bos_ursula_backtako_0(UrsulaBacktakoWork* work, u8* arg);
extern u8 gUnk_0979E344[];
void task_bos_ursula_bubble_single_0(UrsulaBubbleSingleWork* work, u8* arg);
extern const EmyKind gBosUrsulaBubbleSingleEmyKind;
extern u8 gUnk_097A0DE4[];
extern u8 gUnk_0984B0F8[];
void task_bos_ursula_border_2(UrsulaBorderWork* work);
extern u8 gUnk_0979D090[];
extern u8 gUnk_0979D8B8[];
s32 strcmp(const char* a, const char* b);
extern const UnkStruct_096FE034 gUnk_096FE2C0;
void RollBoogieDice(BoogieDiceWork* work);
extern void* const gBoogieDiceFaces[6][3];
extern u8 gUnk_097976DC[];
extern u8 gUnk_09797D0C[];
extern u8 gUnk_0979833C[];
extern u8 gUnk_0979896C[];
extern u8 gUnk_09798F9C[];
extern u8 gUnk_097995CC[];
extern u8 gUnk_0984AFF8[];

void task_bos_boogie_kaihuku_0(BoogieKaihukuWork* work, BoogieWork* arg);
extern const EmyKind gBosBoogieKaihukuEmyKind;
extern u8 gKaifukuTiles[];
extern u8 gKaifukuPalette[];
extern u8 gUnk_08F69BC4[];
void func_080DB468(BoogieKnifereaderWork* work);
void task_bos_ursula_backtako_2(UrsulaBacktakoWork* work);
void func_080DC9DC(s32* a, s32* b, s32* c, UrsulaTakoWork* d);
extern const u8 gUnk_0984B844[];
extern const u8 gUnk_0984B851[];
void task_bos_boogie_explosiondice_2(BoogieExplosiondiceWork* work);
void func_080DD248(s32* a, s32* b, s32* c, UrsulaBacktakoWork* d);
void task_bos_boogie_disk_2(BoogieDiskWork* work);
void task_bos_ursula_bubble_single_2(UrsulaBubbleSingleWork* work);

s32 func_080DBD44(UrsulaWork* work);

#endif /* GUARD_BOS4_H */
