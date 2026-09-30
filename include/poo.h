#include "task_descriptors.h"
#include "registration_data.h"
#ifndef GUARD_POO_H
#define GUARD_POO_H

#include "poo_data.h"

#include "poo_background_data.h"

#include "mode_allmap_api.h"

#include "pooh_actor_types.h"

#include "prize_types.h"

#include "mode_pooh_api.h"

#include "player_progression.h"

#include "m4a_song.h"
#include <string.h>
#include <stdlib.h>
#include "fade.h"
#include "btl_collision.h"
#include "obj_api.h"
#include "display.h"
#include "types.h"
#include "field_state.h"
#include "engine_math.h"
#include "listpool.h"
#include "game_state.h"
#include "anim.h"
#include "key.h"
#include "taskpool.h"
#include "main.h"
#include "obj.h"
#include "bos4_api.h"
#include "poo_api.h"
#include "btl_api.h"
#include "gba/io_reg.h"
typedef struct PooHit {
    Collider* collider;
    u16 message;
    u8 enabled;
    u8 unk_07;
} PooHit;

typedef struct PoohInteractionRegistry {
    PooHit entries[6];
    u16 count;
    u8 rabbitTalkBlocked;
} PoohInteractionRegistry;

typedef struct PooMapWork {
    u8 mapWidth;
    u8 mapHeight;
    u8 unk_02[0x02];
    TaskPool tasks;
} PooMapWork;

typedef struct PooShadowWork {
    s32 x;
    s32 y;
    void* tiles;
    void* palette;
    void* gfx;
    PooPos* pos;
    PooShadowInfo* shadowInfo;
    AnimState anim;
} PooShadowWork;

typedef struct PooShadowArgs {
    PooPos* pos;
    PooShadowInfo* shadowInfo;
    s32 scale;
} PooShadowArgs;

typedef struct PooTileDesc {
    s32 x;
    s32 y;
    u32 kind;
} PooTileDesc;

typedef struct PooGaugeWork {
    void* tiles;
    ObjPalette* palette;
    void* gfx;
    void* paletteSrc;
    u8 warning;
    u8 unk_11;
    u16 blinkTimer;
} PooGaugeWork;

typedef struct PooMapBornWork {
    s32 x;
    s32 y;
    s32 unk_08;
    u8 unk_0C[0x04];
    PooPos pos;
    Collider collider;
    u8 unk_7C;
    u8 unk_7D[0x03];
    TaskPool tasks;
    Task* task;
    u8 colliderActive;
    u8 armed;
    u8 unk_9A[0x02];
} PooMapBornWork;

typedef struct PooScaleWork {
    s32 x;
    s32 y;
    void* tiles;
    void* palette;
    PooPos* pos;
    AnimState anim;
    s32 scale;
    void* gfx;
} PooScaleWork;

typedef struct PooBalloonObjWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    PooPos* pos;
} PooBalloonObjWork;

typedef struct PooNode {
    u16 weight;
    u16 baseWeight;
    u16 unk_04;
    u16 unk_06;
    void* pos;
    ListNode node;
} PooNode;

typedef char PooNode_size[(sizeof(PooNode) == 0x20) ? 1 : -1];

typedef struct PooFrame {
    u16 duration;
    u16 unk_02;
} PooFrame;

typedef struct PooAnimData {
    u8 unk_00[0x04];
    u16 frameCount;
    u16 unk_06;
    PooFrame frames[1];
} PooAnimData;

typedef struct PooAnimDesc {
    void* unk_00;
    void* unk_04;
    void* tiles;
    u16 animId;
    u16 unk_0E;
} PooAnimDesc;

typedef struct PooHoneyWork {
    void* tiles;
    void* palette;
    AnimState anim;
    u16 tileBytes;
    u16 unk_22;
    PooPos pos;
    PooPos pos2;
    PooPos pos3;
    PooPos minPos;
    PooPos maxPos;
    Collider collider;
    PooNode node;
    u32 state;
    TaskPool tasks;
    u16 timer;
    u16 unk_10A;
} PooHoneyWork;

typedef struct PooPileArgs {
    s32 x;
    s32 y;
    u8 unk_08[0x08];
    s32 stage;
} PooPileArgs;

typedef struct PooPileWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_30[0x04];
    Collider collider;
    PooNode node;
    u16 stage;
    u16 unk_B2;
    TaskPool tasks;
    Task* task;
    u8 colliderActive;
    u8 unk_CD[0x03];
} PooPileWork;

typedef struct PooPigletWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    u8 flipped;
    u8 unk_25;
    u16 animIndex;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_34;
    Collider collider;
    TaskPool tasks;
    u32 state;
    u16 timer;
    u16 unk_AE;
    s32 speed;
    u16 interactionId;
    u16 unk_B6;
} PooPigletWork;

typedef struct PooEeyoreWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_30;
    Collider collider;
    TaskPool tasks;
    s32 animId;
    u16 tileBytes;
    u16 moveTimer;
    u8 colliderActive;
    u8 unk_AD;
    u16 interactionId;
} PooEeyoreWork;

typedef struct PooRabbitWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    u8 flipped;
    u8 unk_25[0x03];
    s32 x;
    s32 y;
    s32 z;
    s32 unk_34;
    TaskPool tasks;
    Collider collider;
    s32 animIndex;
    u16 timer;
    u16 interactionId;
    u16 waitTimer;
    u16 unk_B2;
} PooRabbitWork;

typedef struct PooGfxDesc {
    void* gfxTable;
    u16 gfxCount;
    u16 unk_06;
} PooGfxDesc;

typedef struct PooTiggerWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    u8 flipped;
    u8 unk_25;
    u16 animIndex;
    s32 x;
    s32 y;
    s32 z;
    s32 ground;
    Collider collider;
    TaskPool tasks;
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    u8 unk_B4[0x04];
    u8 heading;
    u8 unk_B9;
    s16 hopTimer;
    u16 stepTimer;
    u16 step;
    s32 mode;
    u8 unk_C4[0x04];
    PooShadowInfo shadowInfo;
    u8 onCollider;
    u8 isTigger;
    u16 tileBytes;
} PooTiggerWork;

typedef struct PooBalloonWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    PooPos pos;
    Collider collider;
    PooNode node;
    TaskPool tasks;
    Task* task;
    Task* freeBalloonTask;
    u16 tileBytes;
    u16 angle;
} PooBalloonWork;

typedef struct PooOwlBalloonWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    PooPos pos;
    Collider collider;
    PooNode node;
    TaskPool tasks;
    Task* task;
    u16 tileBytes;
    u16 unk_CA;
} PooOwlBalloonWork;

typedef struct PooPrizeWork {
    s32 x;
    s32 y;
    s32 z;
    s32 ground;
    Collider collider;
    void* tiles;
    void* palette;
    void* gfx;
    void* gfx2;
    void (*update)(struct PooPrizeWork* w);
    u16 kind;
    u16 timer;
    s32 vz;
    s32 speed;
    u8 angle;
    u8 spin;
    u16 unk_8E;
    s32 scale;
    u16 amount;
    u8 visible;
    u8 collected;
} PooPrizeWork;

typedef struct PooEeyoreTailWork {
    void* tiles;
    void* palette;
    void* gfx;
    u32 x;
    u32 y;
    s32 z;
    s32 unk_18;
    u16 tileBytes;
    u16 unk_1E;
    u32 height;
    TaskPool tasks;
} PooEeyoreTailWork;

typedef struct PooFreeBalloonWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    PooPos pos2;
    PooPos pos3;
    s16 x;
    s16 y;
    void* tiles2;
    void* palette2;
    void* gfx2;
    AnimState anim2;
    PooPos pos4;
    PooPos pos5;
    s16 x2;
    s16 y2;
    u16 timer;
    u16 unk_92;
    PooPos* pos;
} PooFreeBalloonWork;

typedef struct PooMapObjHitDesc {
    void* tiles;
    u16 gfxCount;
    u16 unk_06;
    void* anims;
    void* gfxTable;
    void* palette;
} PooMapObjHitDesc;

typedef struct PooSpawn {
    s32 x;
    s32 y;
    TaskDesc* desc;
} PooSpawn;

typedef struct PooSpawnArgs {
    PooPos pos;
    u16 prizeId;
    u16 unk_12;
} PooSpawnArgs;

typedef struct PooMapObjHitArgs {
    s32 x;
    s32 y;
    u8 unk_08[0x08];
    const PooMapObjHitDesc* desc;
    s32 kind;
    u16 prizeId;
    u16 unk_1A;
} PooMapObjHitArgs;

typedef struct PooMapObjHitWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_30[0x04];
    const PooMapObjHitDesc* desc;
    u8 playing;
    u8 unk_39;
    u16 tileBytes;
    Collider collider;
    s32 kind;
    u16 prizeId;
    u16 unk_9E;
} PooMapObjHitWork;

typedef struct PooLeafWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_30[0x04];
    Collider collider;
    u8 playing;
    u8 unk_91;
    u16 tileBytes;
    u16 prizeId;
    u16 unk_96;
} PooLeafWork;

typedef struct PooOwlWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    PooPos pos;
    TaskPool tasks;
    u8 flying;
    u8 descending;
    u16 flyTimer;
    u16 tileBytes;
    u16 unk_4E;
} PooOwlWork;

typedef struct PooStumpWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 unk_2C;
    u8 unk_30[0x04];
    Collider collider;
} PooStumpWork;

typedef struct PooFootmarkWork {
    void* tiles;
    void* palette;
    void* gfx;
    s32 x;
    s32 y;
    s32 unk_14;
    u8 unk_18[0x04];
    PooNode node;
} PooFootmarkWork;

typedef struct PooBoardWork {
    void* tiles;
    void* palette;
    void* gfx;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_18[0x04];
    Collider collider;
} PooBoardWork;

typedef struct PooVegetableWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_30;
    u16 tileBytes;
    u16 unk_36;
    Collider collider;
} PooVegetableWork;

typedef struct PooTanpopoWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    void* tiles2;
    void* gfx2;
    AnimState anim2;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_50[0x04];
    Collider collider;
    u8 playing;
    u8 unk_B1;
    u16 tileBytes;
    u16 tileBytes2;
    u16 prizeId;
} PooTanpopoWork;

typedef struct PooHoneycombWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_30;
    u16 tileBytes;
    u16 unk_36;
    Collider collider;
    u16 shakeTimer;
    u16 angle;
    s32 shakeX;
    u8 colliderActive;
    u8 unk_9D[0x03];
} PooHoneycombWork;

typedef struct PooBeeSub {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x04];
    s32 targetX;
    s32 targetY;
    u8 unk_18[0x08];
} PooBeeSub;

typedef struct PooBeeWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    PooBeeSub sub[4];
    s32 x;
    s32 y;
    s32 z;
    s32 unk_B0;
    s32 dx;
    s32 dy;
    u8 unk_BC[0x0A];
    u16 releaseTimer;
    u8 setupPending;
    u8 unk_C9[0x03];
} PooBeeWork;

typedef struct PooWagonWork {
    void* tiles;
    void* palette;
    void* gfx;
    void* tiles2;
    void* gfx2;
    void* tiles3;
    void* gfx3;
    PooPos pos;
    PooPos pos2;
    u8 poohAboard;
    u8 unk_3D;
    u16 timer;
    u16 angle;
    u16 unk_42;
} PooWagonWork;

typedef struct PooWheelWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_30;
    u16 tileBytes;
    u16 animId;
    s32 speed;
    s32 startX;
    u8 unk_40;
    u8 unk_41[0x03];
} PooWheelWork;

typedef struct PooCabbageWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_30;
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    s32 unk_40;
    Collider collider;
    s32 hopHeight;
    u16 state;
    u16 unk_A6;
    TaskPool tasks;
    Task* task;
    s32 speed;
    s32 vz;
    u8 angle;
    u8 unk_C9;
    u16 moveTimer;
    u16 zTimer;
    u16 age;
    u8 colliderActive;
    u8 wasOnScreen;
    u8 animating;
    u8 unk_D3;
    u16 stackIndex;
    u16 unk_D6;
} PooCabbageWork;

typedef struct PooCabbageBornWork {
    TaskPool tasks;
    u16 unk_14;
    u16 timer;
} PooCabbageBornWork;

typedef struct PooMapButterflyWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_30[0x04];
    u8 onScreen;
    u8 unk_35[0x03];
} PooMapButterflyWork;

typedef struct PooBflyPart {
    void* tiles;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_2C;
    s32 pointAX;
    s32 pointAY;
    s32 pointBX;
    s32 pointBY;
    s32 targetX;
    s32 targetY;
    u8 angle;
    u8 unk_49[0x03];
    s32 dirIndex;
    u8 flipped;
    u8 unk_51;
    u16 timer;
    u8 unk_54[0x14];
} PooBflyPart;

typedef struct PooMapBeeWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_30[0x04];
    u8 onScreen;
    u8 unk_35;
    u16 state;
} PooMapBeeWork;

typedef struct PooZzzWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    void* pos;
} PooZzzWork;

typedef struct PooPileDesc {
    s32 x;
    s32 y;
    u16 kind;
    u16 unk_0A;
} PooPileDesc;

typedef struct PooCabbageAfterEventWork {
    void* tiles;
    void* palette;
    void* gfx;
    s32 x;
    s32 y;
    s32 unk_14;
    s32 unk_18;
    u16 tileBytes;
    u16 unk_1E;
} PooCabbageAfterEventWork;

typedef struct PooRabbitAfterEventWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_30;
    TaskPool tasks;
    Collider collider;
    u16 tileBytes;
    u16 interactionId;
} PooRabbitAfterEventWork;

typedef struct PooBeeAfterEventWork {
    void* tiles;
    void* tiles2;
    void* palette;
    void* gfx;
    void* gfx2;
    AnimState anim;
    AnimState anim2;
    s32 x;
    s32 y;
    s32 z;
    u32 unk_50;
} PooBeeAfterEventWork;

typedef struct PooMapAnimeWork {
    BosMapanimeState anims[2];
} PooMapAnimeWork;

typedef struct PooSparkWork {
    PooPos pos;
    AnimState anim;
    void* tiles;
    void* palette;
    u8 unk_30[0x04];
} PooSparkWork;

typedef struct PooButterflyWork {
    PooBflyPart parts[2];
    void* palette;
    s32 x;
    s32 y;
    s32 z;
    s32 unk_E0;
} PooButterflyWork;

typedef struct PooSoraWork {
    void* tiles;
    void* palette;
    AnimState anim;
    void* gfx;
    TaskPool tasks;
    Collider collider;
    u32 state;
    s16 timer;
    s16 unk_9A;
    s32 vz;
    u16 flags;
    u16 unk_A2;
    s32 animAction;
    const u16* sounds;
    u8 onCollider;
    u8 unk_AD[0x03];
    PooNode node;
} PooSoraWork;

typedef struct PooTrapWork {
    void* tiles;
    void* palette;
    void* gfx;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_18[0x04];
    Collider collider;
    TaskPool tasks;
    u8 colliderActive;
    u8 unk_8D[0x03];
    PooNode node;
} PooTrapWork;

typedef struct PooRooWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    u8 flipped;
    u8 unk_25[0x03];
    PooPos pos;
    PooPos* srcPos;
    Collider collider;
    TaskPool tasks;
    s32 vz;
    s32 lastZ;
    u32 state;
    u16 interactionId;
    u16 unk_BA;
} PooRooWork;

typedef struct PooBgSet {
    void* map;
    void* tiles;
    void* palette;
} PooBgSet;

typedef struct PooPalStep {
    u16 palette;
    u16 duration;
} PooPalStep;

extern const s32 gUnk_096FDA74[];
extern u8 gUnk_0984A138[];
extern const PooBgSet gAllmapWorldBgs[];
extern const PooPalStep gAllmapPalSteps[];

extern const BosMapanimeFrame gPooMapanimeFrames0[4];
extern const BosMapanimeFrame gPooMapanimeFrames1[4];
extern const BosMapanimeDef gPooMapanimeDef0;
extern const s32 gPooPileKindStages[];
extern u8 gUnk_097561D4[];
extern u8 gUnk_09755F34[];
extern const PooAnimDesc gPooPigletAnimDescs[];
extern const PooAnimDesc gPooSoraAnimDescs[11][5];
extern const u16 gPooSoraSounds[8];
extern const PooAnimDesc gPooTiggerAnimDescs[];
extern u8 gUnk_097565FC[];
extern u8 gUnk_097565E8[];
extern u8 gUnk_09849D58[];
extern u8 gEeyorePalette[];
extern u8 gUnk_09849D38[];
extern u8 gUnk_097561E8[];
extern u8 gUnk_09755F54[];
extern u8 gRoFootmarkPalette[];
extern u8 gEeHoneycombPalette[];
extern u8 gOwlPalette[];
extern u8 gRabbitPalette[];
extern u8 gUnk_09849C18[];
extern u8 gUnk_09849C98[];
extern u8 gUnk_0974B4D8[];
extern u8 gRaWagonTiles[];
extern u8 gRaWagonPalette[];
extern u8 gUnk_09849DF8[];
extern u8 gUnk_0975C3E2[];
extern u8 gUnk_0975E40E[];
extern u8 gUnk_0975EC8E[];
extern u8 gUnk_09849E18[];
extern u8 gRabbitBl00Tiles[];
extern u8 gEeBeePalette[];
extern u8 gEeBeeTiles[];
extern u8 gTrap0006Tiles[];
extern u8 gUnk_09849B78[];
extern u8 gOwlFl00Tiles[];
extern u8 gEeHoneycombTiles[];
extern u8 gEeyoreFl00Tiles[];
extern u8 gRaVegetablesPalette[];
extern u8 gRaVegetablesTiles[];
extern u8 gRaWagonFrame3[];
extern u8 gRaWagonFrame10[];
extern u8 gOwlFl00Frame0[];
extern u8 gRaVegetablesFrame0[];
extern u8 gRaVegetablesFrame9[];
extern u8 gRaVegetablesFrame1[];
extern u8 gRaVegetablesFrame10[];
extern u8 gRaVegetablesFrame11[];
extern const u16 gPooCabbageRemoveCounts[];
extern const PooMapObjHitDesc gPooMapObjHitDescs[];
extern const PooPileDesc gPooPileDescs[];
extern const PooAnimDesc gPooRabbitAnimDescs[];
extern u8 gRoFootmarkTiles[];
extern u8 gRoFootmarkFrame0[];
extern u8 gRoFootmarkFrame1[];
extern u8 gUnk_098A4B68[];
extern u8 gUnk_08F69BE4[];
extern u8 gUnk_0972BD8C[];
extern u8 gUnk_09849AB8[];
extern u8 gUnk_0972BD78[];
extern const PooTileDesc gPooTileDescs[];
extern u8 gUnk_097356F4[];
extern u8 gPoohGaugePalette[];
extern u8 gUnk_09760986[];
extern u8 gUnk_09849E58[];
extern const PooSpawn gPooSpawns[85];
extern u8 gUnk_097A2ED8[];
extern u8 gUnk_097AAED8[];
extern u8 gUnk_09849898[];
extern u8 gUnk_09742FD8[];
extern u8 gUnk_097430EC[];
extern u8 gUnk_09743262[];
extern u8 gUnk_09743ADA[];
extern u8 gUnk_09849E78[];
extern u8 gUnk_09849E98[];
extern u8 gUnk_09849EB8[];
extern u8 gUnk_09849ED8[];
extern u8 gUnk_09849EF8[];
extern u8 gUnk_09849F18[];
extern u8 gUnk_09849F38[];
extern u8 gUnk_09849F58[];
extern const s32 gPooTiggerHopHeights[];
extern const s32 gPooTiggerHopCorners[8];
extern const PooGfxDesc gPooTiggerGfxDescs[];
extern const PooGfxDesc gPooRabbitGfxDescs[];
extern const PooGfxDesc gPooPigletGfxDescs[];

extern u8 gTrap0100Palette[];
extern u8 gTrap0004Tiles[];
extern u8 gTrap0005Tiles[];
extern u8 gTrap0004Palette[];
extern u8 gUnk_09849B58[];
extern u8 gPoohHoneyTiles[];
extern u8 gUnk_09742CC2[];
extern u8 gUnk_09849BF8[];
extern u8 gTiggerPalette[];
extern u8 gRooPalette[];
extern u8 gRooFl00Tiles[];
extern const PooPoint gPooBeePoints[];
extern u8 gEeyoreFl00Frame15[];
extern u8 gEeHoneycombFrame0[];
extern u8 gRaWagonFrame11[];
extern u8 gRaWagonFrame1[];
extern u8 gRaWagonFrame12[];
extern u8 gPoohFl05Tiles[];
extern u8 gPoohPalette[];
extern u8 gUnk_097606E8[];
extern u8 gUnk_09849E38[];
extern u8 gUnk_09849BB8[];
extern const BosMapanimeDef gPooMapanimeDef1;

void task_poo_mapbee_0(PooMapBeeWork* w, PooPos* p);
void task_poo_zzz_2(PooZzzWork* w);
s32 GetPooWagonSide(s32 a, s32 b);
u8 task_poo_wagonwheel_1(PooWheelWork* w);
u8 task_poo_gauge_1(PooGaugeWork* w);
void task_poo_roo_0(PooRooWork* w, PooPos* p);
u8 task_poo_roo_1(PooRooWork* w);
void task_poo_roo_2(PooRooWork* w);
void task_poo_shadowdodai_2(PooShadowWork* w);
void task_poo_pooh_2(PoohWork* w);
void task_poo_pooh_3(PoohWork* w);
u8 task_poo_butterflyRight_1(PooButterflyWork* w);
void task_poo_butterflyRight_2(PooButterflyWork* w);
u8 task_poo_butterflyLeft_1(PooButterflyWork* w);
void task_poo_butterflyLeft_2(PooButterflyWork* w);
u8 task_poo_mapbeeborn_1(PooMapBornWork* w);
u8 task_poo_mapbutterflyborn_1(PooMapBornWork* w);
u8 task_poo_leaf_1(PooLeafWork* w);
u8 GetPooScreenOverflow(s16 x, s16 y, s16 h, s16 vy, s16 w, s16 vx, s32* ox, s32* oy);
void SetPooTiggerrooAnimation(PooTiggerWork* w, u16 b);
u8 task_poo_tiggerroo_1(PooTiggerWork* w);
void task_poo_tiggerroo_2(PooTiggerWork* w);
s32 IsInPooWagonAreaForPooh(PooPos* p);
u8 task_poo_eeyoretail_1(PooEeyoreTailWork* w);
void MovePooh(PoohWork* w, s32 b, u8 c);
void task_poo_shadowscale_2(PooScaleWork* w);
void task_poo_wagon_0(PooWagonWork* w);
u8 task_poo_wagon_1(PooWagonWork* w);
void task_poo_zzz_0(PooZzzWork* w, u8* arg);
u8 IsPoohBeeChaseOver(void);
void PooBflyPartUpdate(PooBflyPart* p);
u8 task_poo_owlballoon_1(PooOwlBalloonWork* w);
s32 GetPoohStumpIndex(PoohWork* w);
PooNode* FindPoohTargetNode(void);
void StartPooTiggerHopStep(PooTiggerWork* w);
void SnapToPooWagonLine(u32* a, u32* b, u16 c);
void GetPooCabbageStackSpot(PooSpot* p);
void task_poo_eeyoretail_0(PooEeyoreTailWork* w);
void task_poo_honeycomb_0(PooHoneycombWork* w);
void task_poo_spark_2(PooSparkWork* w);
s32 GetPooNodeScore(PooNode* n);
u16 CreatePooMapobjhitTasks(void* pool, u16 b);
u8 IsPooPosBlocked(PooPos* p);
u8 GetPooWallSlide(PooActor* p, s32 x, s32 y, s32* ox, s32* oy);
void task_poo_gauge_0(PooGaugeWork* w);
void task_poo_mapbeeborn_0(PooMapBornWork* w, PooPos* p);
void task_poo_mapbutterflyborn_0(PooMapBornWork* w, PooPos* p);
void task_poo_butterfly_0(PooButterflyWork* w, PooPos* p);
void task_poo_freeballoon_0(PooFreeBalloonWork* w, PooPos* p);
void task_poo_butterfly_3(PooButterflyWork* w);
void task_poo_mapbutterfly_0(PooMapButterflyWork* w, PooPos* p);
void task_poo_shadowdodai_0(PooShadowWork* w, PooShadowArgs* a);
void task_poo_shadowscale_0(PooScaleWork* w, PooShadowArgs* a);
void CreatePooMapobjhitTask(void* pool, u32 a, s32 x, s32 y, u16 e);
void task_poo_zzz_3(PooZzzWork* w);
void SetPooRabbitAnimation(PooRabbitWork* w, s32 b, u16 c);
void PooBflyPartInit(PooBflyPart* p);
void task_poo_roo_footmark_0(PooFootmarkWork* w);
void task_poo_spark_0(PooSparkWork* w, PooPos* p);
void task_poo_trap_0(PooTrapWork* w, PooPos* p);
u8 CanSpawnPooCabbage(void);
void UpdatePoohGauge(PoohWork* w);
void UpdatePoohAction(PoohWork* w, PooNode* n);
u8 task_poo_pooh_1(PoohWork* w);
u8 task_poo_mapbee_1(PooMapBeeWork* w);
void task_poo_roo_3(PooRooWork* w);
u8 IsPooRooAnimFrameEnding(void);
u8 IsPooRooAnimFinished(void);
u8 IsPoohOffScreen(void);
void task_poo_tanpopo_3(PooTanpopoWork* w);
void task_poo_ti_board_0(PooBoardWork* w, PooPos* p);
u8 task_poo_ti_board_1(PooBoardWork* w);
void task_poo_honeycomb_3(PooHoneycombWork* w);
void task_poo_bee_0(PooBeeWork* w);
u8 task_poo_bee_1(PooBeeWork* w);
void task_poo_vegetable_0(PooVegetableWork* w);
u8 task_poo_vegetable_1(PooVegetableWork* w);
u8 IsPooSoraOverWagon(void);
void func_080CFFC0(s32* a, s32* b);
void func_080CFFF0(s32* a, s32* b);
void func_080D001C(s32* a, s32* b);
void task_poo_wagon_2(PooWagonWork* w);
void task_poo_wagon_3(PooWagonWork* w);
void task_poo_wagonwheel_3(PooWheelWork* w);
void task_poo_spark_3(PooSparkWork* w);
u8 IsPooBeeAfterEventVisible(void);
void task_poo_cabbage_3(PooCabbageWork* w);
void task_poo_cabbageborn_0(PooCabbageBornWork* w);
u8 task_poo_cabbageborn_1(PooCabbageBornWork* w);
void PooBflyPartSetAnimation(PooBflyPart* p);
u8 task_poo_butterfly_1(PooButterflyWork* w);
void task_poo_mapbee_3(PooMapBeeWork* w);
u8 task_poo_mapbutterfly_1(PooMapButterflyWork* w);
void CreatePooPileTasks(void* pool);
void PooBflyPartSetDir(PooBflyPart* p);

void AddPooNode(PooNode* n, u16 v, void* p);
void task_poo_honey_3(PooHoneyWork* w);
u8 task_poo_mapanime_1(PooMapAnimeWork* w);
s32 GetRandomPooPileStage(void);
void task_poo_pile_3(PooPileWork* w);
void CreatePooPileTask(void* pool, u16 b, s32 x, s32 y);
void task_poo_tigerstump_0(PooStumpWork* w, PooPos* p);
u8 task_poo_tigerstump_1(PooStumpWork* w);
void task_poo_poohstump_0(PooStumpWork* w, PooPos* p);
u8 task_poo_poohstump_1(PooStumpWork* w);
void SetPooPigletAnimation(PooPigletWork* w, s32 b, u16 c);
u8 task_poo_piglet_1(PooPigletWork* w);
void task_poo_piglet_3(PooPigletWork* w);
void task_poo_eeyore_3(PooEeyoreWork* w);
u8 task_poo_rabbit_1(PooRabbitWork* w);
void task_poo_rabbit_3(PooRabbitWork* w);
u16 GetPooTiggerAnimDuration(PooTiggerWork* w);
void task_poo_tiggerroo_3(PooTiggerWork* w);
void task_poo_trapballoon_3(PooBalloonWork* w);
void task_poo_owlballoon_3(PooOwlBalloonWork* w);
s32 GetPooGroundZ(Collider* w, PooPos* p, u8* c);
u8 task_poo_map_1(PooMapWork* w);
u16 GetPooMapTile(u16 x, u16 y);
u8 IsPooExitTile(PooPos* p);
void UpdatePooActorAngle(PooActor* p);
void SetPooSoraAnimation(PooSoraWork* w, s32 b, u16 c);
void SetPooSoraAttackPoint(PooActor* p);
s32 GetPooSoraGroundZ(PooSoraWork* w);
void task_poo_sora_3(PooSoraWork* w);
u8 task_poo_sora_1(PooSoraWork* w, Task* t);
u8 PooSoraUpdateCall(PooSoraWork* w, Task* t);
u8 PooSoraUpdateJump(PooSoraWork* w, Task* t);
u8 PooSoraUpdateAttack(PooSoraWork* w, Task* t);
void task_poo_trapballoon_2(PooBalloonWork* w);
u8 ConstrainPooActorMove(PooActor* a, s32 x, s32 y);
u8 IsPooSoraCallStarting(void);
u8 IsPooSoraCalling(void);
u8 task_poo_trap_1(PooTrapWork* w);
void task_poo_shadow_0(TaskPool* w, void* arg);
u8 IsPooNearScreen(s16 x, s16 y);
s32 GetPooGaugeFrame(u16 a);
void task_poo_gauge_2(PooGaugeWork* w);
void UpdatePooCameraCenter(void);
void ScrollPooCamera(PooMapWork* w);
void SetPooActorAngleFromDpad(PooActor* p);
void task_poo_butterfly_2(PooButterflyWork* w);
u8 task_poo_prize_1(PooPrizeWork* w);
void task_poo_prize_3(PooPrizeWork* w);
u8 AreAllPooEventsDone(void);
u8 IsPooSoraOnWagon(void);
void task_poo_eeyoretail_3(PooEeyoreTailWork* w);
void task_poo_freeballoon_3(PooFreeBalloonWork* w);
void task_poo_leaf_3(PooLeafWork* w);
void task_poo_mapanime_0(PooMapAnimeWork* w);
void task_poo_mapbeeborn_3(PooMapBornWork* w);
void task_poo_owl_3(PooOwlWork* w);
void task_poo_poohstump_3(PooStumpWork* w);
void task_poo_roo_footmark_3(PooFootmarkWork* w);
u8 task_poo_spark_1(PooSparkWork* w);
void task_poo_ti_board_3(PooBoardWork* w);
void task_poo_tigerstump_3(PooStumpWork* w);
void task_poo_vegetable_3(PooVegetableWork* w);
u8 PooBflyPartDraw(PooBflyPart* p, void* pal);
void task_poo_mapobjhit_3(PooMapObjHitWork* w);
void PooPrizeUpdateCollect(PooPrizeWork* w);
u16 CreatePooSpawnTasks(void* pool, u16 b);
u8 task_poo_honeycomb_1(PooHoneycombWork* w);
u8 task_poo_eeyore_1(PooEeyoreWork* w);
void task_poo_mapobjhit_2(PooMapObjHitWork* w);
void task_poo_ti_board_2(PooBoardWork* w);
void task_poo_cabbageAfterEvent_2(PooCabbageAfterEventWork* w);
void StartPooTiggerHop(PooTiggerWork* w);
void task_poo_tigger_0(PooTiggerWork* w);
void task_poo_tiggerroo_0(PooTiggerWork* w);
void task_poo_trap_2(PooTrapWork* w);
void SetPooTiggerAnimation(PooTiggerWork* w, u16 b);
void task_poo_wagonwheel_0(PooWheelWork* w);
void task_poo_trapballoon_0(PooBalloonWork* w, PooPos* p);
void task_poo_owlballoon_0(PooOwlBalloonWork* w, PooPos* p);
u8 ApplyPooSoraPushOut(PooSoraWork* w, PooPos* p);
u8 GetPooAngleToPooh(PooPos* p);
void task_poo_owl_0(PooOwlWork* w);
u8 task_poo_owl_1(PooOwlWork* w);
void task_poo_rabbitAfterEvent_0(PooRabbitAfterEventWork* w);
void task_poo_balloon_2(PooBalloonObjWork* w);
void task_poo_mapbeeborn_2(PooMapBornWork* w);
void task_poo_mapbutterflyborn_2(PooMapBornWork* w);
void task_poo_mapbutterfly_2(PooMapButterflyWork* w);
void task_poo_freeballoon_2(PooFreeBalloonWork* w);
void task_poo_mapobjhit_0(PooMapObjHitWork* w, PooMapObjHitArgs* a);
void task_poo_mapbee_2(PooMapBeeWork* w);
void task_poo_leaf_0(PooLeafWork* w, PooSpawnArgs* a);
void task_poo_beeAfterEvent_0(PooBeeAfterEventWork* w);
u8 task_poo_tanpopo_1(PooTanpopoWork* w);
void task_poo_pile_0(PooPileWork* w, PooPileArgs* a);
u8 task_poo_cabbageAfterEvent_1(PooCabbageAfterEventWork* w);
void PlayPooTiggerHopSound(s32 x, s32 y, s32 z, u8 c);
u8 IsPoohNearScreenEdge(void);
void ResetPoohStumpCount(PoohWork* w);
void task_poo_pitAndButterfly_0(PooTrapWork* w, PooPos* p);
u8 CheckPoohInterrupts(PoohWork* w, PooNode* n);
void ChoosePoohTarget(PoohWork* w, PooNode* n);
void task_poo_sora_0(PooSoraWork* w);
u8 task_poo_pile_1(PooPileWork* w);
u8 task_poo_freeballoon_1(PooFreeBalloonWork* w);
void task_poo_prize_0(PooPrizeWork* w, PoohPrizeArgs* a);
void PooPrizeUpdateBounce(PooPrizeWork* w);
void ClampToPooWagonArea(u32* a, u32* b, u16 c);
void task_poo_bee_2(PooBeeWork* w);
void task_poo_map_0(PooMapWork* w);
u8 task_poo_trapballoon_1(PooBalloonWork* w);
u8 task_poo_cabbage_1(PooCabbageWork* w);
void task_poo_cabbage_2(PooCabbageWork* w);
void task_poo_pooh_0(PoohWork* w);
extern const u16 gPooCabbageStackPriorities[];
extern u8 gUnk_098A5C90[];
extern u8 gUnk_098A5C9A[];
extern u8 gUnk_098A5CA4[];
extern u8 gUnk_098A5CAE[];
extern u8 gUnk_098A5CB8[];
extern u8 gUnk_098A5CF4[];
extern u8 gSoraPalette[];
void UpdatePoohStumpCircle(PoohWork* w);
s32 func_080D01BC(s32 x, s32 y);
u8 HandlePoohRequest(PoohWork* w);

void task_poo_mapbutterflyborn_3(PooMapBornWork* w);
void task_poo_trap_3(PooTrapWork* w);
u8 task_poo_pitAndButterfly_1(PooTrapWork* w);
void task_poo_pitAndButterfly_2(PooTrapWork* w);
void task_poo_pitAndButterfly_3(PooTrapWork* w);
u8 task_poo_rabbitAfterEvent_1(PooRabbitAfterEventWork* w);
void task_poo_rabbitAfterEvent_3(PooRabbitAfterEventWork* w);
void func_080D0050(s32* a, s32* b);
u8 func_080D1738(void);
void task_poo_cabbageAfterEvent_0(PooCabbageAfterEventWork* w);
u16 GetPooCabbageLandedCount(void);
u32 NextPoohStumpIndex(u32 a);
void task_poo_bee_3(PooBeeWork* w);
void task_poo_cabbageAfterEvent_3(PooCabbageAfterEventWork* w);
u8 AreAllPooBeesOut(void);
void ApplyPooh04FrameOffset(PoohWork* w);
u8 task_poo_beeAfterEvent_1(PooBeeAfterEventWork* w);
void task_poo_beeAfterEvent_3(PooBeeAfterEventWork* w);

s32 IsInPooWagonArea(PooPos* p);
void task_poo_map_2(PooMapWork* w);
void task_poo_map_3(PooMapWork* w);
void UnfreezePooCamera(void);
void StartPooCameraFollowPooh(void);
u16 GetPooSoraPriority(void);
void IncPooCabbageLandedCount(void);
u8 task_poo_shadowdodai_1(PooShadowWork* w);
u8 task_poo_shadowscale_1(PooScaleWork* w);
void ApplyPooh04aFrameOffset(PoohWork* w);
void SetPooCameraFocus(s32 a, s32 b);
void RemovePooNode(PooNode* p);
u8 IsPooEeyoreTailLanded(void);
u8 IsPooHoneycombShaken(void);
void IncPooCabbageCount(void);
void task_poo_balloon_3(PooBalloonObjWork* w);
void task_poo_gauge_3(PooGaugeWork* w);
void task_poo_mapbutterfly_3(PooMapButterflyWork* w);
void task_poo_shadowdodai_3(PooShadowWork* w);
void task_poo_shadowscale_3(PooScaleWork* w);
void CreatePooShadowscaleTask(void* pool, void* a, s32 b);
s32 NextPooPileStage(u32 a);
s32 GetPooPileHeight(u32 a);
void ApplyPoohFrameOffset(PoohWork* w, const PooSpot* b, u16 c);
u16 GetPooNodeWeight(PooNode* n);
void SetPooNodeWeight(PooNode* n, u16 v);
u16 GetPooNodeBaseWeight(PooNode* n);
void SetPooNodeBaseWeight(PooNode* n, u16 v);
u8 task_poo_balloon_1(void* w);
void task_poo_mapanime_2(void* w);
void task_poo_mapanime_3(void* w);
u8 task_poo_roo_footmark_1(void* w);
u8 task_poo_zzz_1(void* w);
void FreezePooCamera(void);
void StopPooCameraFollowPooh(void);
u16 GetPooWagonPriority2(void);
u16 GetPooWagonPriority(void);
u16 GetPooCabbageCount(void);
void task_poo_cabbageborn_2(PooCabbageBornWork* w);
void task_poo_cabbageborn_3(PooCabbageBornWork* w);
u8 task_poo_shadow_1(TaskPool* w);
void task_poo_shadow_2(TaskPool* w);
void task_poo_shadow_3(TaskPool* w);
u8 IsPoohDescendingWithOwl(void);
u8 IsPoohOnOwlBalloon(void);
u8 IsPoohWalkingToTarget(void);
u8 IsPoohWaitingOnWagon(void);
u8 IsPoohAtLowerExit(void);
u16 GetPoohHoneyAnim(void);
u8 task_poo_honey_1(PooHoneyWork* w);
u8 IsPoohLookingAtHoneycomb(void);
void SetPooPrizeDropped(u16 a);
u8 IsPooPrizeDropped(u16 a);
void ResetPooProgress(void);
void GetPooStatePooh(PooPos* p, s32* b);
void SetPooStateGauge(u16 a, u16 b);
void GetPooStateGauge(u16* a, u16* b);
void SetPooStateWheelPos(s16 a, s16 b);
void GetPooStateWheelPos(u16* a, u16* b);
void GetPooStatePos2(PooPos* p);
void SetPooEventDone(s32 a);
void ClearPooFlag(s32 a);
u16 AddPoohInteraction(Collider* a, u16 b);
void SetPoohInteractionEnabled(u16 a, u8 b);
u16 FindPoohInteractionMessage(void);
void SetPooRabbitTalkBlocked(u8 a);

u16 GetPooExitAt(PooPos* p);
u16 CheckPooSoraExit(PooPos* p);

u8 IsPoohOnWagon(void);

#endif /* GUARD_POO_H */
