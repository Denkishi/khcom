#ifndef GUARD_BOSS_TM_H
#define GUARD_BOSS_TM_H

#include "types.h"
#include "battle_actor_types.h"
#include "anim.h"
#include "taskpool.h"
#include "obj.h"

typedef struct TmArmSrc {
    s32 x;
    s32 y;
    s32 z;
    s32 x2;
    s32 y2;
    s32 z2;
    struct TmWork* tm;
} TmArmSrc;

typedef struct TmWork {
    u16 x;
    u16 y;
    u16 z;
    u8 unk_06[0x2];
    s32 baseX;
    s32 baseY;
    s32 baseZ;
    s32 x2;
    s32 y2;
    s32 z2;
    s32 vx;
    s32 vy;
    u16 flags;
    u8 unk_2A[0x2];
    u32 state;
    s16 hitCount;
    s16 hurtTimer;
    s16 step;
    s16 stepTimer;
    s16 stateTimer;
    s8 tableState;
    u8 unk_3B;
    s32 resumeState;
    u16 tileIndex;
    u16 tileCount;
    u16 paletteIndex;
    u8 unk_46[0x2];
    TmArmSrc arm;
} TmWork;

typedef struct TmBodyWork {
    TmWork* tm;
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    BtlObj body;
    u8 unk_120[0x4];
    void* gfx;
    u8 angle;
    u8 unk_129[0x3];
    BtlObj body2;
    u8 unk_23C[0x4];
    void* gfx2;
    u8 angle2;
    u8 unk_245[0x3];
    BtlObj body3;
    u8 unk_358[0x4];
    void* gfx3;
    u8 angle3;
    u8 unk_361[0x3];
    BtlObj body4;
    u8 unk_474[0x4];
    void* gfx4;
    u8 angle4;
    u8 unk_47D[0x3];
    s16 unk_480;
    s16 angleStep;
    s16 angleTimer;
    s16 unk_486;
    u8 unk_488;
    u8 unk_489;
    s16 hp;
    s16 prevHp;
    s16 unk_48E;
    u8 unk_490;
    u8 unk_491;
    s16 unk_492;
} TmBodyWork;

typedef struct TmTblWork {
    TmWork* tm;
    Collider collider;
    u16 height;
    u8 unk_062;
    u8 unk_063[0x1];
    u16 unk_064;
    s8 frame;
    u8 gimmickPlayed;
    u32 state;
} TmTblWork;

typedef struct TmArmPos {
    s32 x;
    s32 y;
    s32 z;
    u16 angle;
    u16 unk_0E;
} TmArmPos;

typedef struct TmClbArg {
    u32 moveMode;
    u32 spinMode;
    TmArmPos* src;
    s32 vz;
    ObjTiles* tiles;
    void* gfx;
} TmClbArg;

typedef struct TmClbWork {
    TmClbArg* arg;
    ObjTiles* tiles;
    ObjPalette* palette;
    u16 angle;
    u8 unk_00E[0x2];
    s32 x;
    s32 y;
    s32 z;
} TmClbWork;

typedef struct TmAnimFrame {
    s16 duration;
    u8 unk_02[0x2];
    u8 angles[0x10];
} TmAnimFrame;

typedef struct TmAnim {
    s16 timer;
    s16 frame;
    s16 frameCount;
    u8 unk_06[0x2];
    const TmAnimFrame* frames;
} TmAnim;

typedef struct TmArmJoint {
    s32 curX;
    s32 curY;
    u8 angle;
    u8 unk_09[0x3];
    s32 x;
    s32 y;
    u16 targetAngle;
    u8 unk_16[0x2];
    AnimState anim;
    void* gfx;
} TmArmJoint;

typedef struct TmArmWork {
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    TmArmSrc* src;
    union {
        TmArmJoint all[8];
        TmArmJoint arms[2][4];
    } joints;
    u16 timer;
    u16 timer2;
    TaskPool tasks;
    TmClbArg clb;
    TmClbArg clb2;
    TmArmPos tips[2];
    TmAnim jointAnim;
    TmAnim jointAnim2;
    u8 clbSwapped;
    u8 unk_231[0x3];
    u32 prevState;
    ObjTiles* tiles2;
    AnimState anim;
    u8 paletteStep;
    u8 unk_255[0x3];
} TmArmWork;

typedef struct TmFootWork {
    u16 unk_000;
    u8 unk_002;
    u8 footFrame;
    u8 footFrame2;
    u8 unk_005[0x3];
    ObjTiles* tiles;
    ObjTiles* tiles2;
    ObjTiles* tiles3;
    ObjPalette* palette;
    ObjPalette* palette2;
    BtlObj body;
    void* gfx;
    u8 unk_130;
    u8 unk_131[0x3];
    BtlObj body2;
    void* gfx2;
    u8 unk_248;
    u8 unk_249[0x3];
    BtlObj body3;
    void* gfx3;
    u8 unk_360;
    u8 unk_361[0x3];
    BtlObj body4;
    void* gfx4;
    u8 unk_478;
    u8 unk_479[0x3];
    TmWork* tm;
    u32 unk_480;
} TmFootWork;

typedef char TmArmWork_size[(sizeof(TmArmWork) == 0x258) ? 1 : -1];

typedef char TmFootWork_size[(sizeof(TmFootWork) == 0x484) ? 1 : -1];

typedef struct TmBodyStep {
    s16 dx;
    s16 dz;
    u8 dAngle;
    u8 unk_05[0x3];
    s16 dx2;
    s16 dz2;
    u8 dAngle2;
    u8 unk_0D[0x3];
    s16 dx3;
    s16 dz3;
    u8 unk_14[0x2];
    s16 gfx3Index;
    s16 dx4;
    s16 dz4;
    u8 unk_1C[0x2];
    s16 gfx4Index;
} TmBodyStep;

typedef struct TmFootStep {
    s16 unk_00;
    s16 dz;
    s16 unk_04;
    s16 gfxIndex;
    s16 unk_08;
    s16 dz2;
    s16 unk_0C;
    s16 gfx2Index;
    s16 x3;
    s16 z3;
    u8 unk_14[0x4];
    s16 x4;
    s16 z4;
    u8 unk_1C[0x4];
} TmFootStep;

typedef char TmWork_size[(sizeof(TmWork) == 0x64) ? 1 : -1];
typedef char TmBodyWork_size[(sizeof(TmBodyWork) == 0x494) ? 1 : -1];

void BosTmBodyResetTimers(TmBodyWork* p);
void BosTmBodyInitEnemy(BtlObj* p, s16 a, s16 b, s16 c);
void BosTmBodySetObjPos(BtlObj* p, s16 a, s16 b, s16 c);
void BosTmBodyReleaseEnemy(BtlObj* a);
void BosTmBodyUpdateAngle(TmBodyWork* p);
void BosTmBodyPlaceParts(TmBodyWork* p);
void BosTmBodyResetPose(TmBodyWork* p);
void BosTmBodySetDefeatPose(TmBodyWork* p);
void BosTmBodySetBreakPose(TmBodyWork* p);
void BosTmBodyApplyThrowStep(TmBodyWork* p, s16 a);
void BosTmBodySetWalkPose(TmBodyWork* p);
void BosTmBodyWalk(TmBodyWork* p);
void func_080B8A00(TmBodyWork* p);
void func_080B8FF4(TmBodyWork* p, s16 a);
void BosTmBodyChooseAction(TmBodyWork* p);
void _080B949C(BtlObj* a, TmBodyWork* b);
void BosTmBodyRollBossCard(TmBodyWork* p);

s32 GetAbsoluteDifference(s32 a, s32 b);
void BosTmSetArmPositions(TmWork* w);
void task_bos_tm_0(TmWork* w, BtlObj* arg);
u8 task_bos_tm_1(TmWork* w);
void task_bos_tm_2(TmWork* w);
void task_bos_tm_3(TmWork* w);
void BosTmDestroyParts(void);
void BosTmArmUpdateArm1(TmArmWork* work);
void BosTmArmUpdateArm0(TmArmWork* work);
u8 task_bos_tm_clb_1(TmClbWork* work);
u8 task_bos_tm_arm_1(TmArmWork* work);
void task_bos_tm_arm_3(TmArmWork* work);
void task_bos_tm_foot_3(TmFootWork* work);
void task_bos_tm_clb_0(TmClbWork* work, TmClbArg* arg);
void task_bos_tm_clb_2(TmClbWork* work);
void task_bos_tm_tbl_0(TmTblWork* work, TmWork* arg);
void task_bos_tm_tbl_3(TmTblWork* work);
void task_bos_tm_clb_3(TmClbWork* work);
void BosTmFootSetPartPos(BtlObj* p, s32 a, s32 b, s32 c);
void BosTmFootReleasePart(BtlObj* work);
void task_bos_tm_body_3(TmBodyWork* work);
void CreateBosTmClbTask(TaskPool* pool, TmClbArg* p, TmArmPos* a);
void BosTmClbThrow(TmClbArg* p, TmArmPos* a, s32 b);
void BosTmClbHoldSpinning(TmClbArg* p, TmArmPos* a);
void BosTmClbHold(TmClbArg* p, TmArmPos* a, u8 mode);
void BosTmArmSetTargetAngles(TmArmJoint* joints, const u8* src);
void BosTmArmStartJointAnim(TmAnim* anim, const TmAnimFrame* src, u16 a, TmArmJoint* joints);
void BosTmArmUpdateArm1Tip(TmArmWork* work);
void BosTmArmUpdateArm0Tip(TmArmWork* work);
void BosTmFootSyncCollider(BtlObj* sub, TmFootWork* work);
void BosTmFootApplyThrowStep(TmFootWork* work, s16 a);
void BosTmFootWalk(TmFootWork* work);
void func_080BA8C8(TmFootWork* work, s16 a);
void BosTmArmUpdateJoints(TmArmJoint* joints, u16 a);
void BosTmArmStepJointAnim(TmArmJoint* joints, TmAnim* a);

extern s16 gBosTmActorZ;
extern s16 gUnk_0203AB40;
extern s16 gBosTmActorY;
extern s16 gUnk_0203AB48;
extern BtlObj gBosTmBodyObjCopy;
extern s16 gUnk_0203AC60;
extern s32 gUnk_0203AC64;
extern s16 gUnk_0203AC68;
extern s16 gUnk_0203AC6C;
extern s32 gUnk_0203AC70;
extern u16 gUnk_0203AC74;
extern s32 gUnk_0203AC78;

void task_bos_tm_body_0(TmBodyWork* work, TmWork* arg);
u8 task_bos_tm_body_1(TmBodyWork* work);
void task_bos_tm_body_2(TmBodyWork* work);
void task_bos_tm_foot_0(TmFootWork* work, TmWork* arg);
u8 task_bos_tm_foot_1(TmFootWork* work);
void task_bos_tm_foot_2(TmFootWork* work);

#endif
