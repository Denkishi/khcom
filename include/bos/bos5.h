#ifndef GUARD_BOS5_H
#define GUARD_BOS5_H

#include "battle_actor_types.h"
#include "obj.h"
#include "ga_types.h"
#include "types.h"
#include "taskpool.h"
#include "anim.h"

typedef struct MdFrameSprite {
    u16 x;
    u16 y;
    u16 z;
    u16 unk_06;
    void* src;
    u32 unk_0C;
    void* sprite;
} MdFrameSprite;

typedef struct MdFramePos {
    s16 x;
    s16 y;
    s16 z;
    u16 unk_06;
} MdFramePos;

typedef struct MdFrameDef {
    u16 bgOffsetX;
    u16 bgOffsetY;
    void* tiles;
    u16 tilesSize;
    u16 unk_0A;
    const void* blocks[4];
    MdFrameSprite desc[2];
    MdFramePos pos[1];
} MdFrameDef;

typedef struct MdAnimFrame {
    u16 gfxIndex;
    u16 duration;
} MdAnimFrame;

typedef struct MdAnimDef {
    const MdAnimFrame* frames;
    u16 frameCount;
    u16 unk_06;
} MdAnimDef;

typedef struct MdAnim {
    u16 animId;
    u16 unk_02;
    const MdAnimFrame* frames;
    s16 frameCount;
    s16 frame;
    s16 timer;
    u16 unk_0E;
} MdAnim;

typedef struct MdHahenWork {
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
    ObjPalette* palette;
    ObjTiles* tiles;
    void* gfx;
    u16 timer;
    u8 unk_026[0x2];
} MdHahenWork;

typedef struct MdDaiWork {
    s32 x;
    s32 y;
    s32 z;
    s32 dropZ;
    s16 dropSteps;
    u8 unk_012[0x2];
    ObjPalette* palette;
    ObjTiles* tiles;
    Collider collider;
    u16* flags;
    s16 level;
    u16 state;
    TaskPool* pool;
} MdDaiWork;

typedef struct MdFireWork {
    u32 state;
    s16 timer;
    s16 flashTimer;
    s16 contactCooldown;
    u8 unk_00A[0x2];
    ObjPalette* palette;
    ObjPalette* palette2;
    ObjTiles* tiles;
    AnimState anim;
    u32 scale;
    s16 scaleSteps;
    u8 unk_036[0x2];
    BtlObj sub;
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s16 motion;
    s16 pattern;
    s16 index;
    u8 angle;
    u8 unk_163;
    u32 centerX;
    u32 centerY;
    u16* flags;
} MdFireWork;

typedef struct MdFireArg {
    TaskPool* pool;
    s16 pattern;
    u16 index;
    u16* flags;
} MdFireArg;

typedef struct MdFirePoint {
    s16 x;
    s16 y;
    u16 delay;
    u16 unk_06;
} MdFirePoint;

typedef struct MdFireDef {
    const MdFirePoint* points;
    s16 count;
    u16 unk_06;
} MdFireDef;

typedef struct WorldselectWorldDef {
    u16 worldBit;
    s16 world;
    s16 eventId;
    s16 rikuEventId;
    void* palette;
    void* tiles;
    void* gfx;
    void* nameTiles;
#ifdef VERSION_EU
    u16 nameTilesOffset;
    u16 unkEu_1A;
#endif
} WorldselectWorldDef;

typedef struct WorldselectSlot {
    s16 listIndex;
    u8 unk_02[0x6];
    u8 angle;
    u8 unk_09[0x3];
    void* palette;
    void* tiles;
    void* gfx;
} WorldselectSlot;

typedef struct WorldselectTileSizes {
    u16 sizes[5];
} WorldselectTileSizes;

typedef struct MdGfx {
    void* tiles;
    void* src;
    void* sprite;
    s16 x;
    s16 y;
    s16 z;
    u16 unk_12;
} MdGfx;

enum MdFlag {
    MD_FLAG_STATE_REQUESTED = 0x1
};

typedef struct MdWork {
    u32 state;
    u32 nextState;
    u32 statePhase;
    u16 step;
    u16 unk_00E;
    u32 hurtState[1];
    u16 flags;
    s16 timer;
    u16 unk_018;
    s16 hurtTimer;
    u8 bgVisible;
    u8 unk_01D[0x3];
    ObjPalette* palette;
    ObjPalette* palette2;
    void* bgPalette;
    TaskPool tasks;
    TaskPool tasks2;
    TaskPool tasks3;
    BtlObj sub[1];
    u16 bgOffsetX;
    u16 bgOffsetY;
    MdGfx gfx[2];
    MdAnim anim;
    u16 signals;
    u8 unk_1B6[0x2];
} MdWork;

extern u8 gUnk_09A3C9BC[];

void BosMdFireHandleReaction(MdFireWork* work);
u8 BosMdFireUpdateMotion(MdFireWork* work);

s32 task_bos_md_hahen_1(MdHahenWork* work);
void task_bos_md_hahen_2(MdHahenWork* work);
void task_bos_md_dai_0(MdDaiWork* work, void** args);
void task_bos_md_hahen_0(MdHahenWork* work, s32* src);
u8 task_bos_md_fire_1(MdFireWork* work);
void task_bos_md_fire_2(MdFireWork* work);
void task_bos_md_3(MdWork* work);
void WorldselectLoadSlotPalette(s16 model, s16 slot);
void WorldselectLoadSlotTiles(s16 model, s16 slot);
s16 WorldselectSetSlotGfx(s16 model, s16 slot);

extern GaWork* gGaWork;

void task_bos_ga_2(GaWork* work);
void task_bos_ga_3(GaWork* work);
void task_bos_md_hahen_3(MdHahenWork* work);
void task_bos_md_fire_3(MdFireWork* work);
void task_bos_md_dai_3(MdDaiWork* work);
void BosMdSetBgMap(MdWork* work, u16 index);
void BosMdLoadBgTiles(MdWork* work, u16 index);

typedef struct MdMapData {
    void* tiles;
    u16 tilesSize;
    u8 unk_06[0x2];
    void* palette;
    u16 paletteSize;
    u8 unk_0E[0x2];
    void* map[4];
} MdMapData;

typedef struct MdMapWork {
    u32 unk_00;
} MdMapWork;

void task_bos_ga_0(GaWork* work, s32 arg);
s32 task_bos_md_dai_1(MdDaiWork* work);
void task_bos_md_fire_0(MdFireWork* work, MdFireArg* arg);
void BosMdFirePlace(MdFireWork* work);
extern u8 gUnk_09A3C99C[];
void task_bos_md_dai_2(MdDaiWork* work);
u8 task_bos_ga_1(GaWork* work);
u16 Bos5Atan(s32 a);
s32 Bos5GetAngle(s32 x0, s32 y0, s32 x1, s32 y1);
void BosGaEntryUpdateFall(GaEntryWork* e);
void BosGaRequestState(GaWork* work, s32 state);
s32 BosGaEntryOffsetX(GaWork* work, s16 i);
s32 BosGaEntryOffsetY(GaWork* work, s16 i);
s32 BosGaEntryHomeX(GaWork* work, s16 i);
s32 BosGaEntryHomeY(GaWork* work, s16 i);
s32 BosGaEntryHomeZ(GaWork* work, s16 i);
void BosGaEntryResetHome(GaWork* work, s32 i);
void BosGaUpdateFacing(GaWork* work);
void BosGaEntryInit(GaWork* work, u32 i, s32 c);
void BosGaEntryRelease(GaEntryWork* e);
void BosGaReleaseBody();
void BosGaEntryDraw(GaWork* work, GaEntryWork* e);
u8 BosGaUpdateAssemble(GaWork* work);
u8 BosGaUpdateIdle(GaWork* work);
u8 BosGaUpdateWalk(GaWork* work);
u8 BosGaUpdateStomp(GaWork* work);
u8 BosGaUpdateThrust(GaWork* work);
u8 BosGaUpdateOrbit(GaWork* work);
u8 BosGaUpdateJump(GaWork* work);
u8 BosGaUpdateBodyChase(GaWork* work);
u8 BosGaUpdateBodyDash(GaWork* work);
u8 BosGaUpdateBodyJump(GaWork* work);
u8 BosGaUpdateGimmick(GaWork* work);
u8 BosGaUpdateDefeat(GaWork* work);
void BosGaEntryUpdate(GaWork* work, GaEntryWork* p);
extern u8 gBoss01objPalette[];
void BosMdSetFrame(MdWork* work, u16 id);
void BosMdRequestState(MdWork* work, s32 state);
void MdAnimStart(MdWork* work, s16 id);
u8 BosMdAnimIsLastFrame(MdWork* work);
u8 BosMdUpdateIdle(MdWork* work);
u8 BosMdUpdateBite(MdWork* work);
u8 BosMdUpdateQuake(MdWork* work);
u8 BosMdUpdateFireBreath(MdWork* work);
s32 task_bos_md_1(MdWork* work);
void task_bos_md_0(MdWork* work, void* arg);
void WorldselectSetBgMode0();
void mode_worldselect_1();
void WorldselectHandleInput();
void WorldselectDraw();
void mode_worldselect_0();
extern u8 gUnk_09A3C9DC[];
extern u8 gUnk_09A3CC5C[];
extern u8 gUnk_09A3CC7C[];

void WorldselectDrawName(s16 model, s16 n);
void mode_worldselect_2();
void WorldselectSetBgMode1();

void WorldselectCyclePalette();
extern u8 gUnk_09A3C8BC[];
void MdAnimUpdate(MdWork* work);
extern u8 gUnk_08F69BC4[];
extern u8 gUnk_09A3C97C[];
void task_bos_md_2(MdWork* work);
void BosMdEndHurt(MdWork* work);
void BosMdHandleReaction(MdWork* work);

u8 BosMdUpdateDefeat(MdWork* work);
void BosMdChooseAttack(MdWork* work);
void task_bos_md_map_0(MdMapWork* work, MdMapData* p);
s32 task_bos_md_map_1(MdMapWork* work);

#endif /* GUARD_BOS5_H */
