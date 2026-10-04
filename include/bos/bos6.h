#ifndef GUARD_BOS6_H
#define GUARD_BOS6_H

#include "battle_actor_types.h"
#include "battle_bg_types.h"
#include "evt_types.h"
#include "types.h"
#include "taskpool.h"
#include "anim.h"
#include "obj.h"

typedef struct PcAnimStep {
    u16 op;
    u8 unk_02[0x2];
    s16 body2X;
    s16 body2Y;
    s16 body2Z;
    u8 unk_0A[0x2];
    u16 anchorCmd;
    s16 hitX;
    s16 hitY;
    s16 hitZ;
    s16 hitHalfX;
    s16 hitHalfY;
    s16 hitHalfZ;
    u8 unk_1A[0x2];
    u16 event;
    s16 gfxSet;
    s16 cmdList;
    s16 duration;
} PcAnimStep;

extern const PcAnimStep gBosPcIdleAnim[];
extern const PcAnimStep gUnk_09A4B174[];
extern const PcAnimStep gUnk_09A4B3B4[];
extern const PcAnimStep gUnk_09A4B5F4[];
extern const PcAnimStep gUnk_09A4B834[];
extern const PcAnimStep gUnk_09A4BBDC[];
extern const PcAnimStep gUnk_09A4BD20[];
extern const PcAnimStep gUnk_09A4BEAC[];
extern const PcAnimStep gUnk_09A4C278[];
extern const PcAnimStep gUnk_09A4C470[];
extern const PcAnimStep gUnk_09A4C5B4[];
extern const PcAnimStep gBosPcDefeatAnim[];
extern const PcAnimStep gUnk_09A4C818[];
extern const PcAnimStep gUnk_09A4C860[];

enum PcSpriteCmdFlag {
    PC_SPRITE_CMD_STANDALONE = 0x1,
    PC_SPRITE_CMD_END = 0x80
};

typedef struct PcSpriteCmd {
    u8 flags;
    u8 gfxIndex;
    s16 layer;
    s16 x;
    s16 y;
    s16 height;
    u16 unk_0A;
} PcSpriteCmd;

extern const PcSpriteCmd gUnk_09A3DF34[];
extern const PcSpriteCmd gUnk_09A3E198[];
extern const PcSpriteCmd gUnk_09A3E3FC[];
extern const PcSpriteCmd gUnk_09A3E660[];
extern const PcSpriteCmd gUnk_09A3E8C4[];
extern const PcSpriteCmd gUnk_09A3EB04[];
extern const PcSpriteCmd gUnk_09A3ED44[];
extern const PcSpriteCmd gUnk_09A3EF84[];
extern const PcSpriteCmd gUnk_09A3F1C4[];
extern const PcSpriteCmd gUnk_09A3F3E0[];
extern const PcSpriteCmd gUnk_09A3F5D8[];
extern const PcSpriteCmd gUnk_09A3F7F4[];
extern const PcSpriteCmd gUnk_09A3F9EC[];
extern const PcSpriteCmd gUnk_09A3FC2C[];
extern const PcSpriteCmd gUnk_09A3FE90[];
extern const PcSpriteCmd gUnk_09A400F4[];
extern const PcSpriteCmd gUnk_09A40358[];
extern const PcSpriteCmd gUnk_09A405BC[];
extern const PcSpriteCmd gUnk_09A40820[];
extern const PcSpriteCmd gUnk_09A409F4[];
extern const PcSpriteCmd gUnk_09A40B80[];
extern const PcSpriteCmd gUnk_09A40D0C[];
extern const PcSpriteCmd gUnk_09A40E98[];
extern const PcSpriteCmd gUnk_09A410FC[];
extern const PcSpriteCmd gUnk_09A41360[];
extern const PcSpriteCmd gUnk_09A415A0[];
extern const PcSpriteCmd gUnk_09A417BC[];
extern const PcSpriteCmd gUnk_09A419D8[];
extern const PcSpriteCmd gUnk_09A41BD0[];
extern const PcSpriteCmd gUnk_09A41DA4[];
extern const PcSpriteCmd gUnk_09A41F78[];
extern const PcSpriteCmd gUnk_09A4214C[];
extern const PcSpriteCmd gUnk_09A42344[];
extern const PcSpriteCmd gUnk_09A4253C[];
extern const PcSpriteCmd gUnk_09A42734[];
extern const PcSpriteCmd gUnk_09A42974[];
extern const PcSpriteCmd gUnk_09A42BD8[];
extern const PcSpriteCmd gUnk_09A42E3C[];
extern const PcSpriteCmd gUnk_09A430A0[];
extern const PcSpriteCmd gUnk_09A432BC[];
extern const PcSpriteCmd gUnk_09A434B4[];
extern const PcSpriteCmd gUnk_09A43718[];
extern const PcSpriteCmd gUnk_09A4397C[];
extern const PcSpriteCmd gUnk_09A43BE0[];
extern const PcSpriteCmd gUnk_09A43D48[];
extern const PcSpriteCmd gUnk_09A43FAC[];
extern const PcSpriteCmd gUnk_09A44210[];
extern const PcSpriteCmd gUnk_09A44474[];
extern const PcSpriteCmd gUnk_09A446D8[];
extern const PcSpriteCmd gUnk_09A4493C[];
extern const PcSpriteCmd gUnk_09A44BA0[];
extern const PcSpriteCmd gUnk_09A44E04[];
extern const PcSpriteCmd gUnk_09A45044[];
extern const PcSpriteCmd gUnk_09A451F4[];
extern const PcSpriteCmd gUnk_09A453C8[];
extern const PcSpriteCmd gUnk_09A455C0[];
extern const PcSpriteCmd gUnk_09A457DC[];
extern const PcSpriteCmd gUnk_09A459B0[];
extern const PcSpriteCmd gUnk_09A45B84[];
extern const PcSpriteCmd gUnk_09A45D34[];
extern const PcSpriteCmd gUnk_09A45F50[];
extern const PcSpriteCmd gUnk_09A46124[];
extern const PcSpriteCmd gUnk_09A462F8[];
extern const PcSpriteCmd gUnk_09A4655C[];
extern const PcSpriteCmd gUnk_09A467C0[];
extern const PcSpriteCmd gUnk_09A46994[];
extern const PcSpriteCmd gUnk_09A46B8C[];
extern const PcSpriteCmd gUnk_09A46DA8[];
extern const PcSpriteCmd gUnk_09A46FC4[];
extern const PcSpriteCmd gUnk_09A47204[];
extern const PcSpriteCmd gUnk_09A47444[];
extern const PcSpriteCmd gUnk_09A47684[];
extern const PcSpriteCmd gUnk_09A478C4[];
extern const PcSpriteCmd gUnk_09A47AE0[];
extern const PcSpriteCmd gUnk_09A47D20[];
extern const PcSpriteCmd gUnk_09A47F84[];
extern const PcSpriteCmd gUnk_09A480EC[];
extern const PcSpriteCmd gUnk_09A48308[];
extern const PcSpriteCmd gUnk_09A48500[];
extern const PcSpriteCmd gUnk_09A48764[];
extern const PcSpriteCmd gUnk_09A489C8[];
extern const PcSpriteCmd gUnk_09A48C2C[];
extern const PcSpriteCmd gUnk_09A48E90[];
extern const PcSpriteCmd gUnk_09A48FF8[];
extern const PcSpriteCmd gUnk_09A49214[];
extern const PcSpriteCmd gUnk_09A4940C[];
extern const PcSpriteCmd gUnk_09A49670[];
extern const PcSpriteCmd gUnk_09A498D4[];
extern const PcSpriteCmd gUnk_09A49B38[];
extern const PcSpriteCmd gUnk_09A49D9C[];
extern const PcSpriteCmd gUnk_09A4A000[];
extern const PcSpriteCmd gUnk_09A4A264[];
extern const PcSpriteCmd gUnk_09A4A4C8[];
extern const PcSpriteCmd gUnk_09A4A708[];
extern const PcSpriteCmd gUnk_09A4A924[];
extern const PcSpriteCmd gUnk_09A4AAD4[];

typedef struct PcGfxSet {
    void* tiles;
    u16 tilesSize;
    u8 unk_06[0x02];
    void* map;
    u16 mapSize;
    u8 unk_0E[0x02];
} PcGfxSet;

typedef struct PcShot {
    s32 targetX;
    s32 targetY;
    u16 steps;
    u8 unk_0A[0x2];
    s32 targetScale;
} PcShot;

typedef struct PcShared {
    s16 hpRatio;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 inEvent;
    u8 unk_06[0x2];
    s32 fltStopTimer;
    s32 gimmickTimer;
} PcShared;

typedef struct PcOam {
    u16 count;
    u16 attr[0x95];
} PcOam;

typedef struct PcWork {
    s16 state;
    s16 step;
    s16 cardDelay;
    s16 hurtTimer;
    s16 reactionAnim;
    s16 flash;
    s16 prevFlash;
    u8 unk_00E[0x2];
    s32 hitAttack;
    s32 hitFlags;
    u8 defeated;
    u8 unk_019[0x3];
    s32 actorMaxX;
    s32 x;
    s32 y;
    s32 z;
    const PcAnimStep* animSteps;
    s16 animIndex;
    s16 animFrame;
    s16 animTimer;
    s16 bgFrame;
    u8 paletteCycle;
    u8 unk_039;
    s16 paletteIndex;
    s16 paletteTimer;
    u8 unk_03E[0x2];
    void* tiles;
    void* tiles2[2];
    void* palette;
    void* palette2;
    BtlObj body;
    BtlObj body2;
    Collider collider;
    Task* fld;
    Task* flt[4];
    Task* acd;
    PcShared shared;
    u8 unk_2F8[0x4];
    PcOam oam[24];
} PcWork;

extern u16 gBosPcBgPalette[];

u16 BosPcGetSpritePriority(PcWork* work, s32 a);
u16 BosPcGetSpriteDepth(PcWork* work, s32 a, s32 b);

typedef struct PcAcdWork {
    u32 unk_000;
    ObjTiles* tiles;
    ObjPalette* palette;
    s32 x;
    s32 y;
    s32 z;
    u8 acdOff;
    u8 unk_019[0x3];
    PcShared* shared;
    AnimState anim;
} PcAcdWork;

typedef struct PcFltWork {
    u16 playerOnPlatform;
    s16 timer;
    u8 index;
    u8 state;
    u8 unk_006;
    u8 unk_007;
    u16 orbitAngle;
    u8 unk_00A[0x2];
    u32 centerX;
    u32 centerY;
    u16 radiusX;
    u16 radiusY;
    s16 sinkTimer;
    u8 unk_01A[0x2];
    u32 baseX;
    u32 baseY;
    u32 baseZ;
    s32 x;
    s32 y;
    s32 z;
    ObjTiles* tiles;
    ObjPalette* palette;
    PcShared* shared;
    Collider collider;
    AnimState anim;
} PcFltWork;

typedef struct PcFldWork {
    u8 paletteCycle;
    u8 unk_001;
    s16 paletteIndex;
    s16 paletteTimer;
    u8 unk_006[0x2];
    ObjTiles* tiles;
    ObjPalette* palette;
    Collider collider;
} PcFldWork;

typedef struct LstSub {
    u8 defeated;
    u8 unk_001;
    u8 restartAnim;
    u8 unk_003;
    s16 state;
    s16 timer;
    s16 hurtTimer;
    s16 animId;
    s16 curAnimId;
    u8 unk_00E[0x2];
    ObjTiles* tiles;
    u8 unk_014[0x4];
    BtlObj body;
    AnimState anim;
} LstSub;

typedef struct BosLstWork {
    u8 inEvent;
    u8 eventStep;
    u8 hidden;
    u8 unk_003;
    s16 unk_004;
    s16 subsDefeated;
    s16 state;
    s16 step;
    s16 moveMode;
    s16 attackKind;
    s16 bodyCycle;
    s16 facing;
    u16 flash;
    u16 prevFlash;
    s32 hpRatio;
    u8 turned;
    u8 unk_01D;
    s16 animId;
    u16 animFlags;
    u16 animFacing;
    u16 bgFrame;
    s16 hittableTimer;
    ObjTiles* tiles;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 offsetX;
    s32 offsetY;
    s32 offsetZ;
    s32 actorX;
    s32 actorY;
    s32 actorZ;
    s16 timer;
    s16 bobFrame;
    u16 frameCount;
    s16 platformTimer;
    u16 cardRequests;
    s16 breakCount;
    u16 falCount;
    u16 hurtTimer;
    u16 unk_078;
    s16 defeatTimer;
    s32 cardDelay;
    s16 groundStep;
    s16 groundCount;
    s32 groundVz;
    s32 groundTargetX;
    s16 kamaStep;
    s16 kamaCount;
    s32 kamaStartX;
    s32 kamaStartY;
    s32 kamaStartZ;
    s32 kamaTargetX;
    s32 kamaTargetY;
    s32 kamaTargetZ;
    s16 dashStep;
    s16 dashCount;
    s16 unk_0AC;
    u8 unk_0AE[0x2];
    s32 dashSpeed;
    s32 dashVz;
    s32 ctrCount;
    s16 bitStep;
    s16 bitRound;
    s16 bitAttackStarted;
    u16 unk_0C2;
    s32 lstTaskCount;
    u8 unk_0C8[0xC];
    u8 playerOnPlatform;
    u8 unk_0D5;
    s16 platformStep;
    u8 unk_0D8[0x4];
    s32 platformSpeed;
    ObjPalette* palette;
    BtlObj body;
    LstSub sub[2];
    Collider collider;
    Collider collider2;
    Collider colliders[8];
    Task* task;
    Task* lstTasks[0x20];
    TaskPool tasks;
    u8 bgMap[0x280];
    u8 unk_B24[0x24];
    u8 unk_B48[0x55C];
} BosLstWork;

extern u8 gUnk_05000080[];

void BosPcDraw(PcWork* work);
void BosPcLoadPaletteCycle(PcWork* work);

s32 BosPcFldGetShake();
void BosPcFldResetPaletteCycle(PcFldWork* work);
void BosPcFldStopPaletteCycle(PcFldWork* work);
void BosPcAcdSetOff(Task* task, u8 v);
void BosLstSetMode(BosLstWork* work, u16 a, u16 b);
void BosLstRequestCardUse(BosLstWork* work);
void task_bos_pc_2(PcWork* work);
void task_bos_pc_acd_3(PcAcdWork* work);
void task_bos_pc_flt_3(PcFltWork* work);
void task_bos_pc_fld_3(PcFldWork* work);
void BosPcFldLoadPaletteCycle(PcFldWork* work);
s32 BosPcFltSquare(s32 x);
s32 BosPcFltSquare2(s32 x);
s32 BosPcAcdSquare(s32 x);
s32 BosPcAcdSquare2(s32 x);
s32 BosLstSquare(s32 x);
s32 BosLstSquare2(s32 x);

void BosPcFldSetPaletteCycle(Task* task, u8 v);

void BosPcSetAnim(PcWork* work, s32 a);
void BosPcUpdateAnim(PcWork* work);
u8 BosPcFltIsSubmerged(Task* task);
u8 BosPcFltIsPlayerOn(Task* task);
void BosPcFltGetPosition(Task* task, s32* a, s32* b, s32* c);

void BosLstDestroyTasks(BosLstWork* work);
s16 BosLstFindActiveSub(BosLstWork* work);
u8 BosLstAnyBitAlive(BosLstWork* work);
void BosLstHoverBits(BosLstWork* work);
void BosLstReturnBits(BosLstWork* work);

void BosPcFldResetShake();
void BosPcFldStartShake(s16 a);
void BosPcFldUpdateShake();
void BosPcFldUpdatePaletteCycle(PcFldWork* work);

void BosPcFltUpdateSinkEnd(PcFltWork* work);
void BosPcFltUpdateRise(PcFltWork* work);
void BosPcFltUpdateState6(PcFltWork* work);

void BosPcFltUpdateSink(PcFltWork* work);
void BosPcFltUpdateSubmerged(PcFltWork* work);
void BosPcFltUpdateState5(PcFltWork* work);
void BosPcFltUpdateState7(PcFltWork* work);
void BosPcFltUpdateGimmick(PcFltWork* work);
void BosPcFltSyncCollider(PcFltWork* work);

typedef struct PcFltFrameDef {
    s16 drawY;
    s16 z;
    u16 radius;
    u16 nextAnim;
} PcFltFrameDef;

extern u8 gUnk_05000220[];

void BosPcStopPaletteCycle(PcWork* work);
void BosLstSetAnim(BosLstWork* work, u16 a, u16 b, u8 c);

void BosPcFldEnableObject(Task* task, u8 a);
u8 BosLstUpdateHurt(BosLstWork* work);
u8 BosLstUpdateState5(BosLstWork* work);
void BosLstInterruptBits(BosLstWork* work);

u8 BosPcIsAnimDone(PcWork* work);

s32 BosLstApproachValue(s32 a, s32 b, s32 c, s32 d, s32 e);
u8 BosPcUpdateReaction(PcWork* work, Task* task);
u8 BosLstAnyBitFiring(BosLstWork* work, s32 idx);

u8 BosPcUpdateBreak(PcWork* work, Task* task);
void BosLstTickCardDelay(BosLstWork* work);
void BosLstUpdateBob(BosLstWork* work);
void BosLstMoveMode0(BosLstWork* work);

s32 BosLstGetPlatformY(BosLstWork* work);

u8 BosLstFireBits(BosLstWork* work, s32 idx, s16 a);
u8 task_bos_pc_flt_1(PcFltWork* work);
void BosPcFltUpdateMotion(PcFltWork* work);

extern u8 gUnk_09C4B012[];
extern u8 gUnk_09C51CBC[];

void BosLstMoveMode2(BosLstWork* work);
void BosLstSetFacing(BosLstWork* work, s16 a);

void task_bos_pc_fld_2(PcFldWork* work);

extern u8 gUnk_09C489E4[];

const PcAnimStep* BosPcGetAnimStep(PcWork* work);
void BosPcUpdatePaletteCycle(PcWork* work);
u8 BosPcUpdateAttack(PcWork* work, Task* task);
u8 task_bos_pc_1(PcWork* work, Task* task);
void task_bos_pc_0(PcWork* work, TaskPool* pool);
void BosPcStartPaletteCycle(PcWork* work);
void CreateBosPcFltTask(PcWork* work, u16 a, s32 b, s32 c, s32 d, u8 e);
void CreateBosPcAcdTask(PcWork* work, TaskPool* pool);

extern u16 gUnk_08F69BC4[];
extern u8 gUnk_09C53724[];
extern u8 gUnk_09C58590[];

void task_bos_lst_0(BosLstWork* work, TaskPool* pool);
u8 task_bos_lst_1(BosLstWork* work);

typedef struct LstAnimDef {
    void* bgMap;
    u16 spriteX;
    u16 spriteY;
    u8 unk_08[0x4];
    u16 subSpriteX;
    u16 subSpriteY;
    u8 unk_10[0x2];
    s16 subX;
    s16 subY;
    s16 subZ;
    u16 sub2SpriteX;
    u16 sub2SpriteY;
    u8 unk_1C[0x2];
    s16 sub2X;
    s16 sub2Y;
    s16 sub2Z;
    s16 bgX;
    s16 bgY;
    s16 bgZ;
    u8 unk_2A[0x2];
} LstAnimDef;

void task_bos_lst_2(BosLstWork* work);
u8 BosLstUpdateDefeat(BosLstWork* work);

extern EventState* gEventState;
void task_bos_pc_acd_2(PcAcdWork* work);

const PcSpriteCmd* BosPcGetSpriteCmds(PcWork* work);

void BosPcPlaceBodies(PcWork* work);
void task_bos_pc_acd_0(PcAcdWork* work, PcShared* arg);
u8 task_bos_pc_acd_1(PcAcdWork* work);
void task_bos_lst_3(BosLstWork* work);

typedef struct PcFltInit {
    u8 index;
    u8 unk_01;
    u16 angle;
    u32 x;
    u32 y;
    u32 z;
    PcShared* shared;
} PcFltInit;

void task_bos_pc_flt_0(PcFltWork* work, PcFltInit* arg);
void task_bos_pc_flt_2(PcFltWork* work);

void task_bos_pc_fld_0(PcFldWork* work, PcBattleBackgroundDef* arg);

u8 task_bos_pc_fld_1(PcFldWork* work);

u8 BosLstSetSubAnim(BosLstWork* work, u16 a);
u8 BosLstUpdateMove(BosLstWork* work);
void BosLstMoveMode1(BosLstWork* work);
void BosLstMoveDash(BosLstWork* work);
void BosLstMoveBits(BosLstWork* work);
void BosLstMovePlatform(BosLstWork* work);

u8 BosLstUpdateEvent(BosLstWork* work);
u8 BosLstUpdateAttack(BosLstWork* work);
u8 BosLstAttackGround(BosLstWork* work);
u8 BosLstAttackKama(BosLstWork* work);
u8 BosLstAttackDash(BosLstWork* work);
u8 BosLstAttackCtr(BosLstWork* work);
u8 BosLstAttackBits(BosLstWork* work);
u8 BosLstAttackHanabira(BosLstWork* work);

u8 BosPcUpdateIdle(PcWork* work, Task* task);
void BosPcFltUpdateFloat(PcFltWork* work);

u8 BosLstSpawnFal(BosLstWork* work, s32 a);

u8 BosPcUpdateDefeat(PcWork* work, Task* task);

u8 BosPcUpdateHurt(PcWork* work, Task* task);

typedef struct LstSpawn3 {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x6];
    s16 kind;
    u8 unk_14[0xC];
} LstSpawn3;

void BosLstUpdateSub(BosLstWork* work, LstSub* p);

u8 BosLstUpdateBreak(BosLstWork* work);

#endif /* GUARD_BOS6_H */
