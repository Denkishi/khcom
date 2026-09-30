#include "task_descriptors.h"
#include "jiminy_records_data.h"
#ifndef GUARD_HUM_H
#define GUARD_HUM_H

#include "hum_types.h"

#include "card_api.h"

#include "map_api.h"
#include "ms_api.h"
#include "hum_tasks.h"

#include "pallet.h"
#include "save_api.h"

#include "player_progression.h"

#include "m4a_song.h"
#include <string.h>
#include <stdlib.h>
#include "text.h"
#include "fade.h"
#include "btl_effect.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "battle_actor.h"
#include "display.h"
#include "types.h"
#include "engine_math.h"
#include "battle_work.h"
#include "game_state.h"
#include "text_types.h"
#include "jiminy_types.h"
#include "save_types.h"
#include "key.h"
#include "anim.h"
#include "taskpool.h"
#include "obj.h"
#include "hum_common.h"
#include "bos3.h"
#include "bos4_api.h"
#include "btl_api.h"
#include "pc_api.h"

typedef struct VixenSub {
    u8 pending;
    u8 active;
    u8 unk_02[0x02];
    s32 x;
    s32 y;
} VixenSub;

typedef struct CloudWork {
    HumWork base;
    u32 unk_188;
    u16 state;
    u16 unk_18E;
    u16 nextState;
    u8 unk_192[0x02];
} CloudWork;

typedef struct HookWork {
    HumWork base;
    u32 unk_188;
    s32 playerSlide;
    s32 slide;
    u16 angle;
    u16 rollLevel;
    u16 flags;
    u8 unk_19A[0x02];
    TaskPool tasks;
    void* bombTask;
    void* bombTask2;
    void* bombTask3;
} HookWork;

typedef struct HookMoonWork {
    void* tiles;
    ObjPalette* palette;
    u16 angle;
    u8 backdropSet;
    u8 unk_0B;
} HookMoonWork;

typedef struct VixenNdlArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x06];
    s16 unk_12;
    u16 unk_14;
    u16 unk_16;
    void* tiles;
    u8 unk_1C[0x04];
} VixenNdlArgs;

typedef struct VixenNdlWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 hitPhase;
    u8 hitDone;
    u8 flipped;
    u8 unk_2F;
} VixenNdlWork;

typedef struct VixenFrzWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u32 state;
    s16 timer;
    u16 variant;
    u16 flipped;
    u16 unk_36;
} VixenFrzWork;

typedef struct VixenIceWork {
    u32 state;
    void* tiles;
    void* palette;
    AnimState anim;
    VixenSub* sub;
    Collider collider;
    s16 stateTimer;
    u16 steps;
    u16 lifetime;
    u8 unk_8A[0x02];
    s32 scale;
    s32 targetScale;
} VixenIceWork;

typedef struct LexTmh0Work {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 facingLeft;
    u8 unk_2D[0x03];
    s32 scale;
    s16 steps;
    u8 unk_36[0x02];
} LexTmh0Work;

typedef struct LexTmhWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 facingLeft;
    u8 done;
    u16 unk_2E;
    s32 state;
    s32 targetX;
    s32 targetY;
    s32 vz;
    void* tiles2;
    void* palette2;
    u8 flyLeft;
    u8 unk_49;
    s16 timer;
} LexTmhWork;

typedef struct RikuSpawn {
    s32 x;
    s32 y;
    s32 z;
    u16 flags;
    u16 unk_0E;
    AnimState anim;
    void* tileSrc;
    s32 scale;
} RikuSpawn;

typedef struct MahluxiaFlwWork {
    s32 state;
    void* tiles;
    void* palette;
    AnimState anim;
    u8 unk_24[0x04];
    s32 vz;
    s32 vx;
    s32 x;
    s32 y;
    s32 z;
} MahluxiaFlwWork;

typedef struct MahluxiaWork {
    HumWork base;
    HumSub sub;
    s32 hoverZ;
    s16 swingAmplitude;
    u16 steps;
    s32 angle;
    u16 flags;
    u8 unk_1D2[0x02];
    s32 swingBaseY;
    s16 unk_1D8;
    u8 unk_1DA[0x02];
    RikuSpawn spawns[9];
    s32 subSpeed;
    TaskPool tasks;
} MahluxiaWork;

typedef struct LaxeneKnfWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 facingLeft;
    u8 onScreen;
    u16 timer;
    s32 playerPrevX;
    s32 playerPrevY;
    s32 playerPrevZ;
    s32 state;
    s32 vx;
} LaxeneKnfWork;

typedef struct LaxeneWork {
    HumWork base;
    s32 hoverZ;
    u16 unk_18C;
    u16 flags;
    u16 scaleSteps;
    u16 unk_192;
    TaskPool tasks;
} LaxeneWork;

typedef struct VixenWork {
    HumWork base;
    s32 hoverZ;
    u8 unk_18C[0x0C];
    s32 needleX;
    s32 needleY;
    u16 angle;
    u16 flags;
    TaskPool tasks;
    void* task;
    u8 needleCount;
    u8 unk_1BD[0x03];
    s32 slideSpeed;
    VixenSub sub[3];
    ObjTiles needleTiles;
} VixenWork;

typedef struct LexceusWork {
    HumWork base;
    u8 unk_188[0x38];
    s32 unk_1C0;
    s32 hoverZ;
    u8 unk_1C8[0x02];
    u16 flags;
    s16 scaleSteps;
    u16 unk_1CE;
    s32 targetScaleX;
    s32 targetScaleY;
    TaskPool tasks;
    void* task;
    s32 tilt;
    s32 targetTilt;
    u16 tiltSteps;
    u16 unk_1FA;
    s32 tiltSlide;
    s32 cameraBaseY;
} LexceusWork;

typedef struct HadesSub {
    s32 groundY;
    s32 x;
    s32 y;
    s32 z;
    s32 x2;
    s32 y2;
    s32 z2;
    s32 x3;
    s32 y3;
    s32 z3;
} HadesSub;

typedef struct HadesWork {
    HumWork base;
    HumSub sub;
    s32 hoverZ;
    u16 unk_1C8;
    u16 flags;
    s16 angryAttacks;
    u8 unk_1CE[0x02];
    s32 subVz;
    void* tiles;
    void* tiles2;
    void* tiles3;
    AnimState anim;
    AnimState anim2;
    AnimState anim3;
    void* palette;
    HadesSub sub2[2];
    s32 scale;
} HadesWork;

typedef struct LeonWork {
    HumWork base;
    u16 flashTimer;
    u8 unk_18A;
    u8 unk_18B;
    u64 savedLearnedStocks;
    u64 savedLearnedStocks2;
} LeonWork;

typedef struct AnsemWork {
    HumWork base;
    HumSub sub;
    s32 hoverZ;
    s32 subOffsetX;
    s32 subOffsetZ;
    s32 subRiseSpeed;
    u8 unk_1D4[0x02];
    s16 steps;
    s16 repeatCount;
    u8 unk_1DA[0x02];
} AnsemWork;

typedef struct VixenFrgDef {
    s16 x;
    s16 z;
    u16 frame;
    u16 spriteFlags;
} VixenFrgDef;

typedef struct VixenFrgSub {
    void* gfx;
    s32 x;
    s32 y;
    s32 z;
    s32 vz;
    s32 vx;
    s32 vy;
    u16 spriteFlags;
    u16 unk_1E;
} VixenFrgSub;

typedef struct VixenFrgWork {
    ObjTiles tilesSlot;
    void* tiles;
    void* palette;
    s16 timer;
    u16 unk_3A;
    VixenFrgSub sub[15];
    u8 blinking;
    u8 unk_21D[0x03];
} VixenFrgWork;

typedef struct RikuWork {
    HumWork base;
    HumSub sub;
    s32 unk_1C4;
    u16 unk_1C8;
    u16 flags;
    s16 unk_1CC;
    u16 unk_1CE;
    RikuSpawn spawns[9];
    u16 dashCount;
    u8 unk_382[0x02];
} RikuWork;

typedef struct HookBombWork {
    void* tiles;
    void* palette;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 facingLeft;
    u8 unk_2D[0x03];
    s32 vz;
    u8 angle;
    u8 unk_35[0x03];
    s32 state;
    s16 timer;
    u16 unk_3E;
    void* tiles2;
    void* palette2;
    u8 visible;
    u8 unk_49;
    s16 bounceCount;
    s16 maxBounces;
    u16 variant;
    s32 speed;
} HookBombWork;

typedef struct LexRockSub {
    u8 hasHit;
    u8 unk_01[0x03];
    s32 x;
    s32 y;
    s32 z;
    s32 vz;
    s32 vx;
    s32 vy;
} LexRockSub;

typedef struct LexRockWork {
    void* tiles2[12];
    void* palette2;
    AnimState anim[12];
    s32 x;
    s32 y;
    s32 z;
    u8 facingLeft;
    u8 unk_161;
    u16 state;
    u16 rockCount;
    s16 timer;
    LexRockSub sub[12];
    void* tiles;
    void* palette;
    u8 blinking;
    u8 unk_2C1[0x03];
} LexRockWork;

typedef struct AxcelWork {
    HumWork base;
    HumSub sub;
    HumSub sub2;
    s32 hoverZ;
    u16 steps;
    u16 flags;
    u16 scaleSteps;
    u16 unk_20A;
    s32 targetScaleX;
    s32 targetScaleY;
    s32 orbitRadius;
    void* tiles;
    void* palette;
    TaskPool tasks;
    u16 subAngle;
    u16 sub2Angle;
} AxcelWork;

typedef struct AxcelPtcWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
} AxcelPtcWork;

typedef struct RobeWork {
    HumWork base;
    u16 idleAnim;
    u8 unk_18A[0x02];
} RobeWork;

extern u8 gMaruxhaBtEff2Tiles[];
extern u8 gVixenE2Tiles[];
extern u8 gMaruxhaBtEffPalette[];
extern u8 gRexeusPalette[];
extern u8 gRexeusTmhTiles[];
extern u8 gLaxineKnifeTiles[];
extern u8 gLaxinePalette[];
extern u8 gUnk_08F6DC64[];
extern u8 gRexeusTmhAxTiles[];
extern u8 gHadesPalette[];
extern u8 gHadesAngryPalette[];

extern u8 gVixEPalette[];
extern u8 gRexeusRock01Palette[];
extern u8 gRexeusRock02Palette[];
extern u8 gRexeusRock01Tiles[];
extern u8 gRexeusRock02Tiles[];
extern u8 gBStatesPalette[];
extern u8 gVixenE1Tiles[];
extern u8 gVixenReitouHahenTiles[];
extern u8 gHadesFramespreadHiTiles[];
extern u8 gPBakudanPalette[];
extern u8 gPBakudanTiles[];
extern JiminyWork* gJiminyWork;

void AxcelDrawSubShadow(AxcelWork* work, HumSub* sub);
void BgFxStartLaxeneBeam(s32 x, s32 y, s32 z, s32 f, s32 w);
void RikuDrawAfterimage(RikuWork* work, RikuSpawn* p);
void RikuSaveAfterimage(RikuWork* work, RikuSpawn* dst);
void BgFxStartAnsemWave(s32 x, s32 y, s32 z, u8 f, s32 w);
void LexceusHover(HumWork* work, s32 a);
s32 __modsi3(s32 a, s32 b);
void WriteCardSaveSlice(void* p);
void CopyMapCardInventory(void* p);
void RestoreMapCardInventory(void* p);
u16 GetJiminyTextLength(u16* p);
void JiminyLoadHiddenRow(s32 a, u16** b);
void JiminyInitCursor(s16 a, s16 b, s16 c);
void JiminyReloadRows(void);
void JiminyUpdateCursor(s16 a, s16 b, s16 c);
void JiminyLoadRows(s16 a, s16 b, u16** d, const u16* c, const u16* e, s16 f, s16 g, s16 h);
u8 IsJiminyFlagNew(u16 a);

s32 GetJiminyEntryState(s32 idx);

#endif /* GUARD_HUM_H */
