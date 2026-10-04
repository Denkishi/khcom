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
    u8 arrived;
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
    u16 glyphPaletteIndex;
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
    const struct EventSequenceDef* seqDef;
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
    u8 effectStarted;
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
    u8 nextPosition;
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
extern u16 gBStatesPalette[];
extern u8 gFEventTiles[];

extern u16 gUnk_09614718[];
extern u16 gUnk_09614738[];
extern u16 gUnk_09614758[];
extern u16 gUnk_09614778[];
extern u16 gUnk_09614798[];
extern u16 gUnk_096147B8[];
extern u8 gUnk_050001C0[];
extern u16 gUnk_096148D8[];
extern u16 gUnk_08F69BE4[];
extern u8 gUnk_090AA506[];
extern u8 gUnk_090B3FBE[];
extern u8 gUnk_090BC9CA[];
extern u8 gUnk_090C51A6[];
extern u16 gSoraPalette[];
extern u16 gRikuPalette[];
extern u16 gUnk_09614418[];
extern u16 gCard00Palette[];
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
s32 LoadLatinTextSlots(const u16* a, TextSlot* b);
s32 LoadJapaneseTextSlots(const u16* a, TextSlot* b);
void SetBgTextLine(u8 a, u8 b, u8 c, u8* s, u8 e, u8 f);
void SetSpriteTextSlotAscii(s32 x, s32 y, u8* s, u8 slot, u8 a);
void DrawBgTextLines();
u8 GetStringLength(const u8* s);
u8 EventCharaHop(EventCharaWork* work, void* a);
void CreateMsgfaceTask(void* pool, MsgFaceControl* p, u8 a, u8 b, u8 c);
u8 LayoutMsgGlyphsPage(s32 x, s32 y, MsgLatinChar* s, MsgLatinChar** d);
void HBlankIntrEventScanlineScroll();
u8 MsgfaceFlipInUpdate(MsgFaceWork* work, void* a);
u8 MsgwinOpenUpdate(MsgWinWork* work, void* a);
u8 MsgwinTypeUpdate(MsgWinWork* work, void* a);
u8 MsgwinCloseUpdate(MsgWinWork* work, void* a);
void MsgwinTypeStep(MsgWinWork* work);
void MsgwinLoadEntry(MsgWinWork* work);
void MsgwinCheckStart(MsgWinWork* work);
u8 UpdateMsgwaitClosing(MsgWaitWork* work);
u8 msgface_1(MsgFaceWork* work, void* a);
u8 MsgfaceSlideInUpdate(MsgFaceWork* work, void* a);
u8 MsgfaceSlideOutUpdate(MsgFaceWork* work, void* a);
u8 MsgfaceChangeUpdate(MsgFaceWork* work, void* a);
u8 MsgfaceFlipOutUpdate(MsgFaceWork* work, void* a);
u8 UpdateMsgwaitYesnoChoice(MsgWaitWork* work, void* a);
void DrawMsgGlyphsWithPalette(u8 a, void* b);
void ClearSpriteTextLines();

void GetSjisGlyph(u16 a, u16* b, u8* c);

u8 event_chara_1(EventCharaWork* work, void* a);
u8 EventCharaToggleAnim(EventCharaWork* work, void* a);
u8 EventCharaFadeToBlack(void* work, void* a);
u8 func_0806FDB0(EventCharaWork* work, void* a);
u8 EventCharaFadeToBlackUpdate(EventCharaWork* work, void* a);
u8 EventCharaToggleAnimUpdate(EventCharaWork* work, void* a);
u8 AdvanceEventCharaKeyframe(EventCharaWork* work);
void UpdateEventCharaMotion(EventCharaWork* work);
s32 PlayEventCharaAnimSounds(EventCharaWork* work);
u8 EventCharaHopUpdate(EventCharaWork* work, void* a);
u8 EventCharaHopHigh(EventCharaWork* work, void* a);
u8 EventCharaHopHighUpdate(EventCharaWork* work, void* a);
u8 EventCharaHopLow(EventCharaWork* work, void* a);
u8 EventCharaHopLowUpdate(EventCharaWork* work, void* a);
u8 EventCharaDrop(EventCharaWork* work, void* a);
u8 EventCharaDropUpdate(EventCharaWork* work, void* a);
u8 EventCharaFadeOut(void* work, void* a);
u8 EventCharaFadeOutUpdate(EventCharaWork* work, void* a);
u8 EventCharaFadeIn(void* work, void* a);
u8 EventCharaFadeInUpdate(EventCharaWork* work, void* a);
u8 EventCharaBlendUp(void* work, void* a);
u8 EventCharaBlendUpUpdate(EventCharaWork* work, void* a);
u8 EventCharaBlendDown(void* work, void* a);
u8 EventCharaBlendDownUpdate(EventCharaWork* work, void* a);
u8 EventCharaCircleSlow(EventCharaWork* work, void* a);
u8 EventCharaCircleSlowUpdate(EventCharaWork* work, void* a);
u8 EventCharaCircleFast(EventCharaWork* work, void* a);
u8 EventCharaCircleFastUpdate(EventCharaWork* work, void* a);
u8 EventCharaJitter(EventCharaWork* work, void* a);
u8 EventCharaJitterUpdate(EventCharaWork* work, void* a);
void SetEventCharaEndAnim(EventCharaWork* work);
void ApplyEventCharaDrawFlags(EventCharaWork* work);
void SetMsgfacePortrait(MsgFaceControl* p, u8 a, u8 b, u8 c);
void ClearEventObjPaletteExclusions();
void PlaySoraFootstep(EventCharaWork* work, u8 kind, u8 flag);
void PlayDonaldFootstep(EventCharaWork* work, u8 kind, u8 flag);
void PlayGoofyFootstep(EventCharaWork* work, u8 kind, u8 flag);
void SetEventCameraCenter(EventCameraWork* work);
void EventCameraFollow(EventCameraWork* work);
u8 FindEventCameraTarget(EventCameraWork* work);
void EventCameraSnap(EventCameraWork* work);
u8 FindEventCharaTrack(EventCameraWork* work, u8 v);
u8 UpdateEventCameraFollowPlayer(EventCameraWork* work);
void UpdateEventScanlineWave(EventCameraWork* work);
void EventCameraApproach(EventCameraWork* work);

void ReadEventCharaDpadAngle(EventCharaWork* work);
u8 UpdateEventCharaJump(EventCharaWork* work, void* a);
void SetupEventCharaShadow(EventCharaWork* work);
#ifdef VERSION_EU
u8 LoadEventBg3(EventSeqWork* work);
u8 LoadEventBg2Map(EventSeqWork* work);
u8 LoadEventBg1(EventSeqWork* work);
u8 InitEventState(EventSeqWork* work);
#endif

void msgwait_yesno_0(MsgWaitWork* work, u8* a);
u8 UpdateEventSeq(EventSeqWork* work, void* a);
void UpdateEventCharaAngle(EventCharaWork* work);
u8 UpdateEventCharaControl(EventCharaWork* work, void* a);

void event_seq_0(EventSeqWork* work, u8* a);
u8 event_seq_1(EventSeqWork* work, void* a);
void event_seq_2(EventSeqWork* work);
void event_seq_3(EventSeqWork* work);
void event_chara_0(EventCharaWork* work, EventSeqArg* a);
void event_chara_2(EventCharaWork* work);
void event_chara_3(EventCharaWork* work);
void msgface_0(MsgFaceWork* work, MsgFaceControl* ctl);
void msgface_2(MsgFaceWork* work);
void msgface_3(MsgFaceWork* work);
void msgwait_0(MsgWaitWork* work, u8* arg);
u8 msgwait_1(MsgWaitWork* work, void* a);
void msgwait_2(MsgWaitWork* work);
void msgwait_3(MsgWaitWork* work);

extern const u16 gUnk_0951D2B8[1024];
extern const u16 gUnk_0951DAB8[1024];
extern const u16 gUnk_0951E2B8[1024];
extern const u16 gUnk_0951EAB8[1024];

#endif /* GUARD_MSG_H */
