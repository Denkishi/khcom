#ifndef GUARD_MSG_H
#define GUARD_MSG_H

#include "obj.h"
#include "msg_types.h"
#include "evt_types.h"
#include "event_chara_types.h"
#include "types.h"
#include "anim.h"
#include "text_types.h"
#include "taskpool.h"

typedef struct SpriteTextLine {
    s32 x;
    s32 y;
    ObjTiles* glyphTiles[16];
    ObjPalette* palette;
    ObjPalette* alternatePalette;
    u8 length;
    u8 font;
    u8 visible;
    u8 unk_53;
    u8 useAlternatePalette;
    u8 unk_55[3];
} SpriteTextLine;

typedef struct BgTextLine {
    u8 x;
    u8 y;
    u16 glyphs[16];
    u8 length;
    u8 glyphHeight;
    u8 bg;
    u8 dirty;
    u8 paletteIndex;
} BgTextLine;

typedef struct MsgFaceWork {
    void* tiles;
    ObjPalette* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    s32 scaleX;
    u8 steps;
    u8 unk_31;
    u8 talking;
    u8 flipX;
    u8 visible;
    u8 unk_35[3];
    MsgFaceControl* face;
} MsgFaceWork;

typedef struct MsgWinWork {
    TaskPool tasks;
    ObjPalette* palette;
    s32 scrollX;
    u16 unk_1C;
    u8 steps;
    u8 unk_1F;
    u32 position;
    u8 shownChars;
    u8 charTimer;
    u8 charCount;
    u8 scriptIndex;
    u8 eventId;
    u8 textLoaded;
    u8 started;
    u8 waitCreated;
    MsgFaceControl face;
    u8 bg;
    u8 unk_39[3];
    const MessageScriptEntry* script;
    MsgLatinChar* nextText;
} MsgWinWork;

typedef struct EventSeqWork {
    TaskPool tasks;
    TaskPool tasks2;
    Task* task;
    u16 eventId;
    u8 unk_2E;
    u8 ending;
    u8 unk_30;
    u8 unk_31;
    u8 hasBoss;
    u8 unk_33;
    struct EventSequenceDef* seqDef;
    u16 timer;
#ifdef VERSION_EU
    u8 bg3MapUnpacked;
    u8 bg2MapUnpacked;
    u8 bg1MapUnpacked;
    u8 hasMapAnim;
#endif
} EventSeqWork;

typedef struct EventScanlineScroll {
    u8 unk_00[2];
    u8 enabled;
    u8 unk_03;
    u16 scrollX[160];
} EventScanlineScroll;

typedef struct EventCameraWork {
    s32 targetX;
    s32 targetY;
    u8 eventId;
    u8 keyframe;
    u8 unk_0A[2];
    const EventCameraKeyframe* keyframes;
    u16 steps;
    u16 angle;
    u8 approachMode;
    u8 unk_15;
    u16 wavePhase;
    EventScanlineScroll scanline;
} EventCameraWork;

typedef struct MsgWaitWork {
    void* tiles;
    void* tiles2;
    ObjPalette* palette2;
    void* tiles3;
    ObjPalette* palette3;
    ObjPalette* palette;
    void* palette4;
    TextSlot textSlots[10];
    TextSlot textSlots2[10];
    void* gfx;
    void* gfx2;
    AnimState anim2;
    AnimState anim;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 unk_F6[2];
    s32 x;
    s32 y;
    u8 cursor;
    u8 unk_101;
    u8 timer;
    u8 unk_103;
    u8 choiceShown;
    u8 unk_105[3];
} MsgWaitWork;

typedef struct TextGlyphSprite {
    s32 x;
    s32 y;
    void* tiles;
    ObjPalette* palette;
    ObjPalette* alternatePalette;
    u8 useAlternatePalette;
    u8 visible;
    u8 unk_16[2];
} TextGlyphSprite;

extern EventState* gEventState;
extern u8 gBStatesPalette[];
extern u8 gFEventTiles[];

extern u8 gUnk_09614718[];
extern u8 gUnk_09614738[];
extern u8 gUnk_09614758[];
extern u8 gUnk_09614778[];
extern u8 gUnk_09614798[];
extern u8 gUnk_096147B8[];
extern u8 gUnk_050001C0[];
extern u8 gUnk_096148D8[];
extern u8 gUnk_08F69BE4[];
extern u8 gUnk_090AA506[];
extern u8 gUnk_090B3FBE[];
extern u8 gUnk_090BC9CA[];
extern u8 gUnk_090C51A6[];
extern u8 gSoraPalette[];
extern u8 gRikuPalette[];
extern u8 gUnk_09614418[];
extern u8 gCard00Palette[];
extern u8 gUnk_090CBFB2[];
extern const EventCharaParams gEventCharaParams[];

void HideMsgGlyphs();
u16 LoadTwoDigitTextTileArray(u8 v, void** out);
void InitTextTileArray(void** p, u8 n);
void FreeTextTileArray(void** p, u8 n);
u16 LoadTwoDigitTextSlots(u8 v, TextSlot* out);
void RequestMsgfaceSlideIn(MsgFaceControl* p);
void RequestMsgfaceSlideOut(MsgFaceControl* p);
void view_2();
void view_3();
s32 LoadLatinTextSlots(u16* a, TextSlot* b);
s32 LoadJapaneseTextSlots(u16* a, TextSlot* b);
void SetBgTextLine(u8 a, u8 b, u8 c, u8* s, u8 e, u8 f);
void SetSpriteTextSlotAscii(s32 x, s32 y, u8* s, u8 slot, u8 a);
void DrawBgTextLines();
u8 GetStringLength(u8* s);
u8 _0806E9DC(EventCharaWork* p, void* a);
void CreateMsgfaceTask(void* pool, MsgFaceControl* p, u8 a, u8 b, u8 c);
u8 LayoutMsgGlyphsPage(s32 x, s32 y, MsgLatinChar* s, MsgLatinChar** d);
void HBlankIntrEventScanlineScroll();
u8 MsgfaceFlipInUpdate(MsgFaceWork* p, void* a);
u8 MsgwinOpenUpdate(MsgWinWork* p, void* a);
u8 MsgwinTypeUpdate(MsgWinWork* p, void* a);
u8 MsgwinCloseUpdate(MsgWinWork* p, void* a);
void MsgwinTypeStep(MsgWinWork* p);
void MsgwinLoadEntry(MsgWinWork* p);
void MsgwinCheckStart(MsgWinWork* p);
u8 UpdateMsgwaitClosing(MsgWaitWork* p);
u8 msgface_1(MsgFaceWork* p, void* a);
u8 MsgfaceSlideInUpdate(MsgFaceWork* p, void* a);
u8 MsgfaceSlideOutUpdate(MsgFaceWork* p, void* a);
u8 MsgfaceChangeUpdate(MsgFaceWork* p, void* a);
u8 MsgfaceFlipOutUpdate(MsgFaceWork* p, void* a);
u8 UpdateMsgwaitYesnoChoice(MsgWaitWork* p, void* a);
void DrawMsgGlyphsWithPalette(u8 a, void* b);
void ClearSpriteTextLines();

void GetSjisGlyph(u16 a, u16* b, u8* c);

u8 event_chara_1(EventCharaWork* p, void* a);
u8 func_0806FA84(EventCharaWork* p, void* a);
u8 func_0806FB6C(void* work, void* a);
u8 func_0806FDB0(EventCharaWork* p, void* a);
u8 func_0806FC28(EventCharaWork* p, void* a);
u8 func_0806FAB8(EventCharaWork* p, void* a);
u8 AdvanceEventCharaKeyframe(EventCharaWork* p);
void UpdateEventCharaMotion(EventCharaWork* p);
s32 PlayEventCharaAnimSounds(EventCharaWork* p);
u8 func_0806EA28(EventCharaWork* p, void* a);
u8 func_0806EB94(EventCharaWork* p, void* a);
u8 func_0806EBE0(EventCharaWork* p, void* a);
u8 func_0806ECE0(EventCharaWork* p, void* a);
u8 func_0806ED2C(EventCharaWork* p, void* a);
u8 func_0806EE20(EventCharaWork* p, void* a);
u8 func_0806EE6C(EventCharaWork* p, void* a);
u8 EventCharaFadeOut(void* work, void* a);
u8 EventCharaFadeOutUpdate(EventCharaWork* p, void* a);
u8 EventCharaFadeIn(void* work, void* a);
u8 EventCharaFadeInUpdate(EventCharaWork* p, void* a);
u8 func_0806F2EC(void* work, void* a);
u8 func_0806F3A8(EventCharaWork* p, void* a);
u8 func_0806F47C(void* work, void* a);
u8 func_0806F53C(EventCharaWork* p, void* a);
u8 func_0806F610(EventCharaWork* p, void* a);
u8 func_0806F64C(EventCharaWork* p, void* a);
u8 func_0806F734(EventCharaWork* p, void* a);
u8 func_0806F770(EventCharaWork* p, void* a);
u8 func_0806F858(EventCharaWork* p, void* a);
u8 func_0806F898(EventCharaWork* p, void* a);
void SetEventCharaEndAnim(EventCharaWork* p);
void ApplyEventCharaDrawFlags(EventCharaWork* p);
void SetMsgfacePortrait(MsgFaceControl* p, u8 a, u8 b, u8 c);
void ClearEventObjPaletteExclusions();
void PlaySoraFootstep(EventCharaWork* p, u8 kind, u8 flag);
void PlayDonaldFootstep(EventCharaWork* p, u8 kind, u8 flag);
void PlayGoofyFootstep(EventCharaWork* p, u8 kind, u8 flag);
void SetEventCameraCenter(EventCameraWork* p);
void EventCameraFollow(EventCameraWork* a);
u8 FindEventCameraTarget(EventCameraWork* p);
void EventCameraSnap(EventCameraWork* a);
u8 FindEventCharaTrack(EventCameraWork* p, u8 v);
u8 _08074EC8(EventCameraWork* p);
void UpdateEventScanlineWave(EventCameraWork* p);
void EventCameraApproach(EventCameraWork* a);

void ReadEventCharaDpadAngle(EventCharaWork* p);
u8 UpdateEventCharaJump(EventCharaWork* p, void* a);
void SetupEventCharaShadow(EventCharaWork* p);
#ifdef VERSION_EU
u8 eu_0806C734(EventSeqWork* work);
u8 eu_0806C7C8(EventSeqWork* work);
u8 eu_0806C848(EventSeqWork* work);
u8 eu_0806C974(EventSeqWork* work);
#endif

void msgwait_yesno_0(MsgWaitWork* p, u8* a);
u8 UpdateEventSeq(EventSeqWork* p, void* a);
void UpdateEventCharaAngle(EventCharaWork* p);
u8 UpdateEventCharaControl(EventCharaWork* p, void* a);

void event_seq_0(EventSeqWork* work, u8* a);
u8 event_seq_1(EventSeqWork* work, void* a);
void event_seq_2(EventSeqWork* p);
void event_seq_3(EventSeqWork* p);
void event_chara_0(EventCharaWork* p, EventSeqArg* a);
void event_chara_2(EventCharaWork* p);
void event_chara_3(EventCharaWork* p);
void msgface_0(MsgFaceWork* p, MsgFaceControl* ctl);
void msgface_2(MsgFaceWork* p);
void msgface_3(MsgFaceWork* p);
void msgwait_0(MsgWaitWork* p, u8* arg);
u8 msgwait_1(MsgWaitWork* p, void* a);
void msgwait_2(MsgWaitWork* p);
void msgwait_3(MsgWaitWork* p);

extern const u16 gUnk_0951D2B8[1024];
extern const u16 gUnk_0951DAB8[1024];
extern const u16 gUnk_0951E2B8[1024];
extern const u16 gUnk_0951EAB8[1024];

#endif /* GUARD_MSG_H */
