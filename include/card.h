#include "mode_deck.h"
#include "boss_card_data.h"
#include "map_animation_data.h"
#include "card_deck_data.h"
#include "card_selection_data.h"
#include "event_index_data.h"
#include "card_def_data.h"
#include "battle_localized_data.h"
#include "msg_portrait_data.h"
#include "card_help_data.h"
#include "map_text_data.h"
#include "card_localized_data.h"
#include "card_message_data.h"
#include "registration_data.h"
#include "system_state.h"
#ifndef GUARD_CARD_H
#define GUARD_CARD_H

#include "anim.h"

#include "card_label_data.h"

#include "card_description_data.h"

#include "map_card_data.h"

#include "bg_animation_data.h"

#include "msg_types.h"

#include "field_state.h"

#include "card_ui_types.h"

#include "obj_resource_types.h"

#include "card_api.h"

#include "card_deck.h"

#include "types.h"
#include "engine_math.h"
#include "game_state.h"
#include "text_types.h"
#include "obj.h"
#include "taskpool.h"
#include "listpool.h"
#include "battle_actor_types.h"
#include "card_types.h"
#include "fld_types.h"
#include "game.h"
#include "mode.h"
#include "mode_battle_data.h"

typedef struct UnkStruct_09EE752C {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} UnkStruct_09EE752C;

void func_080A0944(u16 a, u16* p);
void func_080A096C(u16 a, u16* p);

typedef struct CardSlot {
    u32 cardId;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} CardSlot;

typedef char CardSlot_size[(sizeof(CardSlot) == 0xC) ? 1 : -1];

typedef struct CardDisplayArgs {
    ListPool* pool;
    CardSlot* slot;
    s32 unk_08;
    u16 index;
    u8 unk_0E;
    u8 unk_0F;
} CardDisplayArgs;

typedef char CardDisplayArgs_size[(sizeof(CardDisplayArgs) == 0x10) ? 1 : -1];

typedef struct CardDisplayWork {
    void* tiles;
    void* tiles2;
    void* tiles3;
    void* tiles4;
    void* tiles5;
    void* palette;
    void* unk_18;
    void* unk_1C;
    struct UnkStruct_08095A5C* unk_20;
    TaskPool tasks;
    CardDisplayArgs args;
    CardDef* cardDef;
    s32 x;
    s32 y;
    s32 unk_54;
    s32 unk_58;
    u16 unk_5C;
    u8 unk_5E;
    u8 unk_5F;
    u8 unk_60[0x04];
    ListNode node;
    u32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    u16 unk_9C;
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    u8 unk_A1;
    u8 unk_A2;
    u8 unk_A3;
    s8 unk_A4;
    u8 unk_A5;
    u8 unk_A6;
    u8 unk_A7;
} CardDisplayWork;

typedef char CardDisplayWork_size[(sizeof(CardDisplayWork) == 0xA8) ? 1 : -1];

typedef struct CardBattleWork {
    TaskPool tasks;
    void* tiles;
    void* palette;
    CardDisplayWork* unk_1C[3];
    CardDisplayWork* unk_28[3];
    CardDisplayWork* unk_34[4];
    CardSlot* slots[4];
    ListPool unk_54[4];
    u16 unk_94[4];
    s16 unk_9C[4];
    s16 x;
    s16 unk_A6;
    s16 unk_A8[4];
    s16 unk_B0[4];
    s8 unk_B8;
    u8 unk_B9;
    u8 unk_BA;
    u8 unk_BB;
    u8 unk_BC[4];
    u8 unk_C0[4];
    u8 unk_C4[5];
    u8 unk_C9;
} CardBattleWork;

typedef char CardBattleWork_size[(sizeof(CardBattleWork) == 0xCC) ? 1 : -1];
extern const u16 gUnk_0903BFD4[];
extern const u16 gUnk_0903BFBC[];
extern u8 gUnk_096148D8[];
extern u8 gRiCardF0RedTiles[];
typedef struct CardListWork {
    ListPool cards;
    struct UnkStruct_0809C534* selectedCard;
    TaskPool effectTasks;
    u8 effectCount;
    u8 unk_29;
    u8 unk_2A[2];
} CardListWork;

typedef char CardListWork_size[(sizeof(CardListWork) == 0x2C) ? 1 : -1];

extern u8 gUnk_081283C0[];
extern vu16 gSystemFlags;
extern u8 gUnk_09614118[];
extern u8 gUnk_096142F8[];
extern u8 gUnk_05000160[];
extern void* gUnk_09EE7938[];
extern u8 gUnk_09613F78[];

typedef struct EventMapObjectWork {
    u8 background;
    u8 unk_01[0x03];
    void* tiles[0x0A];
    ObjPalette* palettes[0x0A];
    u8 unk_54[0x04];
    struct EventMapObjectDef* definition;
} EventMapObjectWork;

struct MapCardDef;
struct MapCardBackDef;

typedef struct UnkStruct_08096F94 {
    void* tiles;
    void* palette;
    void* tiles2;
    void* tiles3;
    void* palette2;
    void* tiles4;
    void* tiles5;
    void* palette3;
    struct MapCardDef* cardDef;
    struct MapCardBackDef* cardBack;
    TaskPool tasks;
    u16 unk_3C;
    u16 unk_3E;
    s32 unk_40;
    u8 unk_44[0x2C];
    u8 unk_70;
    u8 unk_71[0x2F];
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
    s32 unk_BC;
    s32 unk_C0;
    s32 unk_C4;
    s16 scaleX;
    s16 scaleY;
    u16 unk_CC;
    s16 x;
    s16 y2;
    s16 x3;
    s16 y3;
    s16 x2;
    s16 y;
    s16 unk_DA;
    u16 unk_DC;
    u8 unk_DE;
    u8 unk_DF;
    u8 unk_E0;
    u8 unk_E1;
    u8 unk_E2;
    u8 unk_E3;
    u8 unk_E4;
    u8 unk_E5;
    u8 unk_E6;
    u8 unk_E7;
    u8 unk_E8;
} UnkStruct_08096F94;

typedef char UnkStruct_08096F94_sizechk[(sizeof(struct UnkStruct_08096F94) == 0xEC) ? 1 : -1];

typedef struct UnkStruct_02034B38 {
    s8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u8 unk_06[0x02];
    s32 x;
    s32 y;
    s32 y2;
    void* tiles;
    void* palette;
    void* gfx2[3];
    void* tiles2;
    void* palette2;
    void* gfx3;
    void* tiles3;
    void* palette3;
    void* gfx4;
    void* tiles4;
    void* palette4;
    void* gfx;
    AnimState anim;
    s32 unk_64;
    u16 unk_68;
    u8 unk_6A[0x02];
} UnkStruct_02034B38;

typedef struct UnkStruct_0809A02C {
    void* tiles;
    void* palette;
    void* tiles2;
    void* palette2;
    void* tiles3;
    void* tiles4;
    void* palette3;
    CardDef* cardDef;
    TaskPool tasks;
    u8 unk_34[0x04];
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    u8 unk_48[0xFC];
    Collider collider;
    s32 cardId;
    s32 unk_1A4;
    s32 unk_1A8;
    s32 unk_1AC;
    s32 unk_1B0;
    s32 unk_1B4;
    s16 scaleX;
    s16 scaleY;
    s16 unk_1BC;
    s16 x;
    s16 y;
    u16 unk_1C2;
    u16 unk_1C4;
    u8 unk_1C6;
    u8 unk_1C7;
    u8 unk_1C8;
    u8 unk_1C9;
    u8 unk_1CA;
    u8 unk_1CB;
    u8 unk_1CC;
    u8 unk_1CD;
    u8 unk_1CE;
    u8 unk_1CF;
    u16 unk_1D0;
} UnkStruct_0809A02C;

typedef char UnkStruct_0809A02C_sizechk[(sizeof(struct UnkStruct_0809A02C) == 0x1D4) ? 1 : -1];

typedef char CardStat_sizechk[(sizeof(struct CardStat) == 0x18) ? 1 : -1];

typedef struct UnkStruct_080993D4 {
    u8 unk_000[0xE4];
    s16 unk_0E4;
} UnkStruct_080993D4;

typedef struct RevCountArgs {
    void* unk_00;
    void* unk_04;
    void* unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E[0x02];
} RevCountArgs;

typedef struct RevCountWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    u8 unk_24;
    u8 unk_25;
    u16 unk_26;
    u8 unk_28;
    u8 unk_29[0x03];
    RevCountArgs args;
    s32 x;
    s32 y;
} RevCountWork;

typedef char UnkStruct_08098CE4_sizechk[(sizeof(struct RevCountWork) == 0x44) ? 1 : -1];

extern const s16 gUnk_09037FB4[];
extern const s16 gUnk_09037FBA[];
extern const s32 gUnk_09037FFC[];
extern const s32 gUnk_0903800C[];
extern const u16 gUnk_0903801C[];
extern u16 gUnk_09EE48F4[47];
extern const s32 gUnk_090352E4[];
extern const s16 gUnk_090352F4[];
extern u8 gUnk_09619178[];
typedef struct WorldSelAnim {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02[0x2];
} WorldSelAnim;

extern WorldSelAnim gWorldSelAnims[30];
extern u8 gUnk_09619378[];
extern const s32 gUnk_09041E80[];
extern const s32 gUnk_09041E9C[];
extern const s16 gUnk_09041EB4[];
extern const s16 gUnk_09041F30[];
extern const s16 gUnk_09041F34[];
extern const u16 gUnk_09041F3E[];
extern const s16 gUnk_09041EBA[];
extern const u16 gUnk_09041EEE[];
extern const s16 gUnk_09041F04[];
extern const s16 gUnk_09041F1A[];
extern const s16 gUnk_09041F0A[];
extern u8 gUnk_08159E18[];
extern u8 gUnk_08159F38[];
extern u8 gUnk_08159FBC[];
extern u8 gUnk_0815C204[];
extern u8 gUnk_0815C1C2[];
extern u8 gUnk_08159E10[];
extern u8 gUnk_09614418[];
extern u8 gUnk_09614438[];
extern u8 gFEventTiles[];
extern u8 gUnk_08F69BE4[];

typedef struct CardMessageArgs {
    u32 bg;
    u32 messageId : 16;
    u32 unk_06 : 8;
    u32 unk_07 : 8;
} CardMessageArgs;

typedef struct DeckCard2Args {
    void* pool;
    u16 cardId;
    s16 col;
    s16 row;
    u8 unk_0A;
    u8 unk_0B;
    u16* slot;
} DeckCard2Args;

typedef struct DeckCard2Work {
    u8 unk_00[0x04];
    ObjPalette* palette2;
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjTiles* tiles2;
    CardDef* cardDef;
    CardBack* cardBack;
    DeckCard2Args args;
    ListNode node;
    s32 x;
    s32 y;
    u16 flags;
    u8 unk_4A;
    u8 unk_4B[0x02];
    u8 unk_4D;
} DeckCard2Work;

typedef struct UnkStruct_0809C534 {
    CardDef* cardDef;
    CardBack* cardBack;
    void* tiles;
    void* tiles2;
    void* tiles3;
    void* unk_14;
    void* tiles4;
    void* tiles5;
    ObjPalette* palette;
    ObjPalette* palette2;
    ObjPalette* palette3;
    AnimState anim;
    void* gfx;
    u16 unk_48;
    s16 x;
    s16 y;
    s16 angle;
    s16 radius;
    s8 unk_52;
    u8 unk_53;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56[0x02];
    ListNode node;
    s16 scaleX;
    s16 scaleY;
    u16 x2;
    u16 y2;
    u8 unk_74;
} UnkStruct_0809C534;

typedef struct DeckExchangeWork {
    ObjTiles* tiles;
    ObjTiles* tiles2;
    ObjTiles* tiles3;
    ObjPalette* palette;
    ObjTiles* tiles4;
    ObjTiles* tiles5;
    ObjTiles* tiles6;
    ObjTiles* tiles7;
    ObjPalette* palette2;
    ObjPalette* palette3;
    TextSlot textSlots[8];
    TextSlot textSlots2[8];
    TextSlot textSlots3[8];
    TextSlot textSlots4[30];
    TextSlot textSlots5[90];
    ObjTiles* tiles8;
    ObjPalette* palette5;
    ObjTiles* tiles9;
    ObjPalette* palette6;
    ObjPalette* palette7;
    ObjPalette* palette4;
    void* unk_4C0;
    void* unk_4C4;
    u8 unk_4C8[4];
    struct UnkStruct_08084D78* unk_4CC;
    struct UnkStruct_08084D78* unk_4D0;
    void* gfx3;
    void* gfx4;
    void* gfx5;
    u8 unk_4E0[8];
    void* gfx;
    void* gfx2;
    u8 unk_4F0[4];
    u8 unk_4F4[0x120];
    TaskPool tasks;
    TaskPool tasks2;
    ListPool pool;
    AnimState anim;
    AnimState anim2;
    u8 unk_67C[0x18];
    s32 x2;
    s32 y2;
    s32 x;
    s32 y;
    s32 unk_6A4;
    s32 unk_6A8;
    s32 unk_6AC;
    s32 unk_6B0;
    s32 unk_6B4;
    s32 x3;
    s32 y3;
    u8 unk_6C0[2];
    u16 unk_6C2;
    u16 unk_6C4;
    u16 unk_6C6;
    u16 unk_6C8;
    u16 unk_6CA;
    u16 unk_6CC;
    u16 unk_6CE;
    s16 unk_6D0;
    s16 unk_6D2;
    s16 x4;
    s16 x5;
    s16 x6;
    s16 y4;
    s16 y5;
    s16 y6;
    u16 unk_6E0;
    u16 unk_6E2[4];
    u8 unk_6EA[2];
    s16 unk_6EC;
    s16 unk_6EE;
    u8 unk_6F0;
    u8 unk_6F1;
    u8 unk_6F2;
    u8 unk_6F3;
    u8 unk_6F4;
    u8 unk_6F5;
    u8 unk_6F6;
    u8 unk_6F7;
    u8 unk_6F8;
    u8 unk_6F9;
    u8 unk_6FA;
    u8 unk_6FB;
    u8* unk_6FC;
    u8 unk_700;
    u8 unk_701;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 textSlotCount3;
    u8 textSlotCount4;
    u8 unk_706;
    u8 unk_707;
    s16 x7;
    s16 y7;
    u8 textSlotCount5;
    u8 unk_70D;
    u8 unk_70E;
    u8 unk_70F;
    u8 unk_710;
    u8 unk_711;
    u8 unk_712;
    u8 unk_713;
    u8 unk_714;
    u8 unk_715;
    u16 unk_716;
} DeckExchangeWork;

typedef char DeckExchangeWork_size[(sizeof(DeckExchangeWork) == 0x718) ? 1 : -1];

typedef struct UnkStruct_08084D78 {
    u16 unk_00[0x0A];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u8 unk_1A[0x02];
    u16* unk_1C;
} UnkStruct_08084D78;

typedef struct DeckMenuWork {
    ObjTiles* tiles;
    ObjTiles* tiles2;
    ObjTiles* tiles3;
    ObjPalette* palette2;
    ObjTiles* tiles4;
    ObjPalette* palette;
    ObjTiles* tiles12;
    ObjTiles* tiles7;
    ObjTiles* tiles8;
    ObjTiles* tiles9;
    ObjTiles* tiles10;
    void* unk_02C;
    ObjPalette* palette5;
    ObjPalette* palette6;
    TextSlot textSlots[8];
    TextSlot textSlots2[8];
    TextSlot textSlots3[8];
    TextSlot textSlots4[30];
    TextSlot textSlots5[90];
    ObjTiles* tiles5;
    ObjTiles* tiles6;
    ObjPalette* palette3;
    ObjPalette* palette4;
    DeckCard2Work* unk_4C8;
    DeckCard2Work* unk_4CC;
    void* unk_4D0;
    UnkStruct_08084D78* unk_4D4;
    UnkStruct_08084D78* unk_4D8;
    void* gfx4;
    void* gfx5;
    void* gfx6;
    void* gfx7;
    void* gfx8;
    void* gfx;
    void* gfx2;
    void* gfx3;
    u8 unk_4FC[0x23C];
    ObjTiles* tiles11;
    ObjTiles* tiles13;
    ObjPalette* palette7;
    TextSlot textSlots6[8];
    u8 unk_784[20];
    AnimState anim4;
    void* gfx9;
    s32 x9;
    s32 y8;
    s32 x10;
    union {
        struct {
            s16 x;
            s16 y;
        } parts;
        u32 packed;
    } cursor;
    u8 textSlotCount6;
    u8 unk_7C5;
    u8 unk_7C6;
    u8 unk_7C7;
#ifdef VERSION_EU
    u8 unk_7C8;
    u8 unk_7C9[3];
#endif
    TaskPool taskpool;
    TaskPool cardpool;
    ListPool pool;
    AnimState anim2;
    AnimState anim3;
    AnimState anim;
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    s32 x5;
    s32 x6;
    s32 y5;
    s32 y6;
    s32 x7;
    s32 x3;
    s32 y3;
    s16 unk_874;
    s16 unk_876;
    s16 unk_878;
    s16 unk_87A;
    s16 unk_87C;
    s16 unk_87E;
    u16 unk_880;
    u16 unk_882;
    s16 unk_884;
    s16 unk_886;
    s16 unk_888;
    s16 unk_88A;
    s16 unk_88C;
    s16 unk_88E;
    s16 unk_890;
    s16 unk_892;
    s16 unk_894;
    s16 unk_896;
    u16 unk_898;
    u16 unk_89A[4];
    u16 unk_8A2;
    u16 unk_8A4;
    u16 unk_8A6;
    u16 unk_8A8;
    u8 unk_8AA[2];
    s16 unk_8AC;
    s16 unk_8AE;
    u8 unk_8B0;
    u8 unk_8B1;
    u8 unk_8B2;
    u8 unk_8B3[2];
    s8 unk_8B5;
    s8 unk_8B6;
    u8 unk_8B7;
    u8 unk_8B8[4];
    u8* unk_8BC;
    u8 unk_8C0;
    u8 unk_8C1;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 textSlotCount3;
    u8 textSlotCount4;
    u8 textSlotCount5;
    u8 unk_8C7;
    u8 unk_8C8;
    u8 unk_8C9;
    u8 unk_8CA;
    u8 unk_8CB;
    u8 unk_8CC;
    u8 unk_8CD;
    s8 unk_8CE;
    u8 unk_8CF;
    u8 unk_8D0;
    u8 unk_8D1;
    u8 unk_8D2;
    u8 unk_8D3;
    u16 unk_8D4;
} DeckMenuWork;

typedef struct RikuDeckMenuWork {
    ObjTiles* tiles;
    ObjTiles* tiles2;
    ObjTiles* tiles3;
    ObjPalette* palette2;
    ObjTiles* tiles4;
    ObjPalette* palette;
    ObjTiles* tiles7;
    ObjTiles* tiles8;
    ObjTiles* tiles9;
    ObjTiles* tiles10;
    ObjPalette* palette5;
    ObjPalette* palette6;
    TextSlot textSlots[8];
    TextSlot textSlots2[8];
    TextSlot textSlots3[8];
    TextSlot textSlots4[30];
    TextSlot textSlots5[60];
    u8 unk_3C0[4];
    ObjTiles* tiles6;
    ObjPalette* palette3;
    ObjTiles* tiles12;
    u8 unk_3D0[8];
    ObjPalette* palette4;
    DeckCard2Work* unk_3DC;
    DeckCard2Work* unk_3E0;
    u8 unk_3E4[4];
    UnkStruct_08084D78* unk_3E8;
    void* gfx4;
    void* gfx5;
    void* gfx6;
    u8 unk_3F8[8];
    void* gfx;
    void* gfx2;
    void* gfx3;
    TaskPool taskpool;
    TaskPool cardpool;
    ListPool pool;
    AnimState anim2;
    AnimState anim3;
    AnimState anim;
    s32 unk_48C;
    s32 unk_490;
    s32 unk_494;
    s32 unk_498;
    s32 unk_49C;
    s32 unk_4A0;
    s32 unk_4A4;
    s32 unk_4A8;
    s32 unk_4AC;
    u8 unk_4B0[4];
    s32 unk_4B4;
    u8 unk_4B8[2];
    s16 unk_4BA;
    u16 unk_4BC;
    u16 unk_4BE;
    u16 unk_4C0;
    u16 unk_4C2;
    u8 unk_4C4[2];
    u16 unk_4C6;
    s16 unk_4C8;
    s16 unk_4CA;
    u8 unk_4CC[0xC];
    s16 unk_4D8;
    s16 unk_4DA;
    u16 unk_4DC;
    u8 unk_4DE[8];
    u8 unk_4E6;
    u8 unk_4E7;
    u8 unk_4E8;
    u8 unk_4E9;
    u8 unk_4EA[2];
    u8 unk_4EC;
    u8 unk_4ED;
    u8 unk_4EE;
    u8 unk_4EF;
    u8 unk_4F0;
    u8 unk_4F1;
    u8 unk_4F2;
    u8 unk_4F3;
    u8* unk_4F4;
    u8 unk_4F8;
    u8 unk_4F9;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 textSlotCount3;
    u8 textSlotCount4;
    u8 textSlotCount5;
    u8 unk_4FF;
    u8 unk_500;
    u8 unk_501;
    u8 unk_502;
    u8 unk_503;
    u8 unk_504;
    u8 unk_505;
    u8 unk_506;
    s8 unk_507;
    u8 unk_508;
    u8 unk_509;
    u8 unk_50A;
    u8 unk_50B;
    u8 unk_50C;
} RikuDeckMenuWork;

typedef struct UnkStruct_080A324C {
    u8 unk_000;
    u8 unk_001[0x10E];
    u16 unk_110[999];
    u16 unk_8DE;
    Deck unk_8E0[3];
} UnkStruct_080A324C;

typedef struct HcEffectNameWork {
    s16 x;
    u8 unk_02[0x06];
    void* tiles2;
    void* tiles3;
    void* palette;
    void* tiles;
    u8 unk_18;
    u8 unk_19;
    u16 timer;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 unk_22;
    u8 unk_23;
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
} HcEffectNameWork;

struct UnkStruct_0809BB4C;

typedef struct StockNameWork {
    u8 unk_00[4];
    u16 unk_04;
    u8 unk_06[2];
    ObjTiles* tiles;
    ObjPalette* palette;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12[2];
    u32 unk_14;
    s32 unk_18[6];
    u8 unk_30;
    u8 unk_31;
    u8 unk_32[2];
} StockNameWork;

typedef struct ReloadChildArgs {
    ListPool* unk_00;
    s32* unk_04;
    s32* unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u16 unk_10;
    u8 unk_12[0x02];
} ReloadChildArgs;

typedef struct ReloadChildWork {
    void* tiles;
    void* palette;
    void* tiles2;
    ReloadChildArgs args;
    s32 unk_20;
    s32 unk_24;
    s32 scale;
    u8 unk_2C[0x04];
    ListNode node;
    u8 unk_44;
    u8 angle;
    u8 unk_46;
} ReloadChildWork;

typedef char UnkStruct_08098BE8_sizechk[(sizeof(struct ReloadChildWork) == 0x48) ? 1 : -1];

typedef struct UnkStruct_08098670 {
    void* tiles;
    void* tiles2;
    void* tiles3;
    void* palette;
    void* palette2;
    void* palette3;
    void* gfx;
    void* gfx2;
    void* gfx3;
    s32 x;
    s32 y;
} UnkStruct_08098670;

typedef struct PremiumCardEffectWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 x;
    s32 y;
    s32 unk_38;
    s32 angle;
    s32 unk_40;
    s32 vx;
    s32 vy;
    s32 unk_4C;
    s32 unk_50;
} PremiumCardEffectWork;

typedef char PremiumCardEffectWork_sizechk[(sizeof(struct PremiumCardEffectWork) == 0x54) ? 1 : -1];

typedef struct CardNameWork {
    void* tiles;
    ObjPalette* unk_04;
    TextSlot textSlots[32];
    TextSlot textSlots2[32];
#ifdef VERSION_EU
    TextSlot textSlots3[32];
#else
    TextSlot textSlots3[2];
#endif
    ObjPalette* unk_218;
    ObjPalette* palette;
    s16 unk_220;
    s16 unk_222;
    s16 unk_224;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 textSlotCount3;
} CardNameWork;

#ifdef VERSION_EU
typedef char CardNameWork_sizechk[(sizeof(struct CardNameWork) == 0x31C) ? 1 : -1];
#else
typedef char CardNameWork_sizechk[(sizeof(struct CardNameWork) == 0x22C) ? 1 : -1];
#endif

typedef struct DarkPointWork {
    ObjTiles* tiles;
    s32 x;
    u8 unk_08[0x02];
    s8 slideTimer;
    u8 unk_0B;
    u8 hundreds;
    u8 tens;
    u8 ones;
} DarkPointWork;

typedef char DarkPointWork_sizechk[(sizeof(struct DarkPointWork) == 0x10) ? 1 : -1];

typedef struct MapcardWork {
    void* tiles;
    void* unk_04;
    void* tiles2;
    void* palette;
    u8 unk_10[0x08];
    MapCardDef* cardDef;
    MapCardBackDef* cardBack;
    u8 unk_20;
    u8 unk_21;
    u8 unk_22[0x06];
    ListPool* pool;
    u8 unk_2C[0x0C];
    ListNode node;
    s32 x;
    s32 y;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    u16 scale;
    u16 unk_6A;
    u16 unk_6C;
    u8 angle;
    u8 unk_6F;
    u8 unk_70;
    u8 unk_71;
    u8 unk_72;
    u8 unk_73;
    u8 unk_74;
    u8 unk_75[0x03];
} MapcardWork;

typedef struct UnkStruct_08095A5C {
    s16 unk_00;
    u16 angle;
    s32 unk_04;
    u8 unk_08[0x05];
    u8 unk_0D;
    u8 unk_0E[0x02];
    AnimState anim;
    AnimState anim2;
    AnimState anim3;
    void* gfx;
    void* gfx2;
    void* gfx3;
    s8 unk_64;
    u8 unk_65;
    u8 unk_66[0x02];
} UnkStruct_08095A5C;

typedef char UnkStruct_08095A5C_size[(sizeof(UnkStruct_08095A5C) == 0x68) ? 1 : -1];

typedef struct MapcardArgs {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    void* unk_04;
    void* unk_08;
    u8 unk_0C[0x0C];
} MapcardArgs;

typedef struct ReloadGageArgs {
    void* unk_00;
    void* unk_04;
    s32 unk_08;
    u16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
} ReloadGageArgs;

typedef struct UnkStruct_02034AD4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04[32];
} UnkStruct_02034AD4;

typedef struct NumberPlusArgs {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} NumberPlusArgs;

typedef struct NumberPlusWork {
    void* tiles;
    void* palette;
    NumberPlusArgs args;
    s16 unk_24;
    s16 unk_26;
    u8 unk_28;
    u8 unk_29;
} NumberPlusWork;

typedef struct MapTileAnimationWork {
    u8 unk_00;
    u8 frameTimers[8];
    u8 frameIndices[8];
    u8 unk_11[3];
    const MapTileAnimationDef* definition;
} MapTileAnimationWork;

typedef struct PrizeCardArgs {
    s32 unk_00[8];
} PrizeCardArgs;

typedef struct PrizeCardTaskArgs {
    s32 x;
    s32 y;
    s32 z;
    u8 unk_0C[0x14];
    s32 cardId;
} PrizeCardTaskArgs;

typedef struct PrizeCardInitWork {
    TaskPool tasks;
    u8 unk_14;
    PrizeCardArgs args;
} PrizeCardInitWork;

typedef struct ScrollBarWork {
    u8 unk_00[0x08];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 unk_16;
    u8 unk_17;
} ScrollBarWork;

typedef char ScrollBarWork_sizechk[(sizeof(struct ScrollBarWork) == 0x18) ? 1 : -1];

typedef struct PrizeCardWork {
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjTiles* tiles2;
    ObjTiles* tiles3;
    ObjPalette* palette2;
    ObjTiles* tiles4;
    ObjTiles* tiles5;
    ObjPalette* palette3;
    TaskPool tasks;
    CardStat stat;
    Collider collider;
    FldPos pos;
    FldPos prevPos;
    u32 cardId;
    s32 unk_CC;
    s32 unk_D0;
    s32 unk_D4;
    s32 unk_D8;
    s32 unk_DC;
    s16 scaleX;
    s16 scaleY;
    s16 unk_E4;
    s16 x;
    s16 y2;
    s16 unk_EA;
    s16 unk_EC;
    s16 x2;
    s16 y;
    s16 unk_F2;
    s16 unk_F4;
    u8 unk_F6;
    u8 unk_F7;
    u8 unk_F8;
    u8 unk_F9;
    u8 unk_FA;
    u8 unk_FB;
    u8 unk_FC[0x04];
} PrizeCardWork;

typedef struct ReloadGageWork {
    void* tiles;
    void* tiles2;
    void* tiles3;
    void* tiles4;
    void* tiles5;
    void* palette;
    u8 unk_18[0x04];
    ListPool* pool;
    UnkStruct_08095A5C* unk_20;
    TaskPool tasks;
    ListPool* pool2;
    void* unk_3C;
    u32 unk_40;
    u8 unk_44[0x02];
    u8 unk_46;
    u8 unk_47[0x05];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 unk_5C[0x08];
    ListNode node;
    u32 flags;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    s32 angle;
    s32 targetAngle;
    s16 unk_9C;
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    u8 unk_A1;
    u8 unk_A2;
    u8 unk_A3;
    u8 unk_A4[0x04];
} ReloadGageWork;

typedef struct UnkStruct_08096C38_Item {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_08096C38_Item;

typedef struct UnkStruct_08096C38 {
    const UnkStruct_08096C38_Item* unk_00;
    u16 unk_04;
    u16 unk_06;
} UnkStruct_08096C38;

typedef struct UnkStruct_09035DCC {
    const UnkStruct_08096C38* data;
    u16 size;
    u16 unk_06;
} UnkStruct_09035DCC;

extern const UnkStruct_09035DCC gUnk_09035DCC[];
extern const UnkStruct_09035DCC gUnk_090360BC[];
extern const u16 gUnk_0903612C[];
extern const u16 gUnk_090359FC[];
extern Deck gUnk_09041FA0;
extern u16 gUnk_09041F70[];
extern const u32 gUnk_09036210[];
extern const s16 gUnk_09036278[];
extern const u8 gUnk_0903628A[];
extern u8 gRikuBt00Tiles[];
extern u8 gSor1ll51Tiles[];
extern u8 gUnk_09618D38[];
extern const s32 gUnk_09033FF4[][2];
extern const s32 gUnk_09033FA8[];
extern const s32 gUnk_09033FB8[];
extern const u16 gUnk_09033FC8[];
extern const s32 gUnk_0903401C[][2];
extern const s32 gUnk_0903404C[];
extern const s32 gUnk_09034054[];
extern const s32 gUnk_09035978[];
extern u8 gUnk_096144D8[];
extern u8 gUnk_096FBA04[];
extern u8 gUnk_09628DC0[];
extern u8 gUnk_0962B090[];
extern u8 gUnk_096FBAA4[];
extern u8 gUnk_0962AD62[];
extern u8 gUnk_096FBA44[];
extern u8 gUnk_0962B286[];
extern u8 gUnk_096FBA64[];
extern u8 gUnk_0962B8BE[];
extern u8 gUnk_096FBA84[];

#ifdef VERSION_EU
extern u8 gUnkEu_095EDAAA[];
extern u8 gUnkEu_095EE0E2[];
extern u8 gUnkEu_095EE71A[];
extern u8 gUnkEu_095EED52[];
extern u8 gUnkEu_095EF38A[];
extern u8 gUnkEu_095EF9C2[];
extern u8 gUnkEu_095EFFFA[];
extern u8 gUnkEu_095F0632[];
extern u8 gUnkEu_095F0C6A[];
extern u8 gUnkEu_095F12A2[];
#endif

extern const s16 gUnk_09035950[];
extern const s16 gUnk_09035956[];
extern const s16 gUnk_090356EC[];
extern const s16 gUnk_090356F2[];
extern const s16 gUnk_09035702[];
extern const s16 gUnk_0903571A[];
extern const s16 gUnk_0903571E[];
extern const s16 gUnk_090356F8[];
extern const s16 gUnk_0903570E[];
typedef struct UnkStruct_09035730 {
    s32 unk_00[2];
} UnkStruct_09035730;

extern const UnkStruct_09035730 gUnk_09035730;
#ifdef VERSION_EU
extern const u16 gUnkEu_090CE9E0[];
extern const u16 gUnkEu_090CE9EA[];
extern const u16 gUnkEu_090CE9F4[];
#endif
extern u8 gUnk_09618C58[];
extern u8 gUnk_09619098[];
extern u8 gUnk_090A3E46[];
extern u8 gUnk_096144F8[];
extern u8 gUnk_09619158[];
extern u8 gUnk_09614458[];
extern u8 gUnk_09614478[];
extern u8 gUnk_09614498[];
extern u8 gUnk_096144B8[];
extern u8 gUnk_09614406[];
extern const Deck gUnk_09034084[];
extern u8 gCard00Palette[];
extern u8 gSor1ff00Tiles[];
extern u8 gRikuFf00Tiles[];
extern u8 gUnk_09614798[];
extern u8 gUnk_09618C38[];
extern u8 gUnk_050001A0[];
extern u8 gUnk_050001C0[];
extern u8 gUnk_0500016C[];
extern u8 gUnk_06010000[];

typedef struct UnkStruct_080933D8 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_080933D8;

typedef struct SpotlightWork {
    u8 unk_00;
    u8 unk_01[0x03];
    s32 unk_04;
    s32 unk_08;
    u16 unk_0C;
    u8 unk_0E[0x02];
    u8* unk_10;
    u8 unk_14;
} SpotlightWork;

typedef struct CardEffectArgs {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 unk_0C;
    u8* count;
} CardEffectArgs;

typedef struct CardEffectWork {
    void* tiles;
    void* palette;
    AnimState anim;
    void* gfx;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s16 x;
    s16 y;
    u16 priority;
    u8 unk_36[0x02];
    CardEffectArgs args;
} CardEffectWork;

typedef struct BossPrizeWork {
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjTiles* tiles2;
    ObjTiles* tiles3;
    ObjPalette* palette2;
    ObjTiles* tiles4;
    ObjTiles* tiles5;
    ObjPalette* palette3;
    TaskPool tasks;
    CardStat stat;
    Collider collider;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    s32 unk_B4;
    s32 cardId;
    s32 unk_BC;
    s32 unk_C0;
    s32 unk_C4;
    s32 unk_C8;
    s32 unk_CC;
    s16 unk_D0;
    s16 unk_D2;
    u16 priority;
    s16 x;
    s16 y;
    s16 x3;
    s16 y3;
    s16 x2;
    s16 y2;
    s16 unk_E2;
    s16 unk_E4;
    u8 unk_E6;
    u8 unk_E7;
    u8 unk_E8;
    u8 unk_E9;
    u8 unk_EA;
    u8 unk_EB;
    u8 unk_EC;
    u8 unk_ED;
    u8 unk_EE;
    u8 unk_EF;
} BossPrizeWork;

typedef char BossPrizeWork_sizechk[(sizeof(struct BossPrizeWork) == 0xF0) ? 1 : -1];

typedef struct EventMapObjectPlacement {
    s32 x : 24;
    s32 unk_03 : 8;
    s32 y : 24;
    s32 unk_07 : 8;
    u8 spriteIndex;
    u8 unk_09[0x03];
} EventMapObjectPlacement;

typedef struct EventMapObjectDef {
    UnkStruct_09035DCC* tileResources;
    UnkStruct_09035DCC* paletteResources;
    void** sprites;
    EventMapObjectPlacement* placements;
    u16 placementCount;
} EventMapObjectDef;

typedef struct SelmapEventKeyArgs {
    ObjPalette* palette;
    void* unk_04;
    s32 unk_08;
} SelmapEventKeyArgs;

typedef struct MapSelectWork {
    TaskPool tasks;
    ListPool cards;
    u8 unk_024[8];
    ObjTiles* tiles4;
    ObjPalette* palette;
    void* tiles2;
    void* tiles3;
    void* tiles;
    ObjPalette* palette2;
    void* tiles5;
    ObjPalette* palette3;
    TextSlot textSlots[48];
    ObjPalette* palette4;
    u8 unk_1D0[0x10];
    void* tiles6;
    void* unk_1E4;
    void* tiles7;
    MapcardWork* card;
    MapcardWork* prevCard;
    MapcardWork* card2;
    AnimState anim;
    AnimState anim2;
    u8 unk_228[0x10];
    struct SelmapEventKeyWork* eventKey;
    s32 unk_23C;
    s32 unk_240;
    s32 unk_244;
    s32 x3;
    s32 unk_24C;
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    s32 unk_260;
    s32 unk_264;
    s32 unk_268;
    s32 y3;
    s32 y4;
    void* gfx;
    void* gfx2;
    u16 unk_27C;
    u16 unk_27E;
    s16 unk_280;
    s16 unk_282;
    u8 unk_284;
    u8 unk_285;
    u8 unk_286;
    u8 unk_287[0x04];
    u8 unk_28B;
    u8 unk_28C;
    u8 unk_28D[0x02];
    u8 unk_28F;
    u8 unk_290;
    u8 unk_291[0x03];
    u8* unk_294;
    u8 unk_298;
    u8 unk_299;
    u8 unk_29A;
    u8 unk_29B;
    u8 unk_29C;
    u8 unk_29D;
    u8 unk_29E[0x20];
    u8 unk_2BE;
    u8 unk_2BF;
    u8 unk_2C0;
    u8 unk_2C1;
    u8 unk_2C2;
    u8 unk_2C3;
    SelmapEventKeyArgs eventKeyArgs;
    u8 unk_2D0[0x0A];
    u8 unk_2DA;
    u8 unk_2DB;
    void* unk_2DC;
    UnkStruct_080933D8* unk_2E0;
} MapSelectWork;

typedef char MapSelectWork_size[(sizeof(struct MapSelectWork) == 0x2E4) ? 1 : -1];

typedef struct LvupMsgWork {
    TextSlot textSlots[20];
    TextSlot textSlots2[20];
    TextSlot textSlots3[20];
#ifndef VERSION_JP
    TextSlot textSlots4[20];
#endif
    ObjPalette* unk_280;
    void* tiles;
    void* palette;
    u16 unk_28C;
    u8 unk_28E[2];
    s32 y;
    s32 x;
    s32 x2;
    s32 x3;
    s32 y2;
    s32 y3;
    s32 y4;
    s8 unk_2AC;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 textSlotCount3;
#ifndef VERSION_JP
    u8 textSlotCount4;
#endif
    u8 unk_2B1;
    u8* unk_2B4;
} LvupMsgWork;

typedef struct DeckConfirmWork {
    TextSlot textSlots[80];
    TextSlot textSlots2[80];
    TextSlot textSlots3[80];
    ObjTiles* tiles;
    ObjPalette* palette;
    ObjPalette* palette2;
    u8 textSlotCount;
    u8 textSlotCount2;
    u8 textSlotCount3;
    u8 unk_78F;
    s16 unk_790;
    s16 x;
    s16 x2;
    s16 y;
    s16 y2;
    s16 x3;
    s16 y3;
    u8 unk_79E[2];
    u8* unk_7A0;
    u8 unk_7A4;
} DeckConfirmWork;

struct BtlObj;

typedef struct LevelUpEffectArgs {
    s32 x;
    s32 y;
    u8 unk_08;
    u8 unk_09[3];
    struct BtlObj* target;
    void* tiles;
    ObjPalette* palette;
} LevelUpEffectArgs;

typedef struct LevelUpEffectWork {
    void* tiles;
    void* palette;
    void* unk_08;
    struct BtlObj* target;
    s32 unk_10[4];
    s32 unk_20[4];
    s32 unk_30;
    s32 x[4];
    s32 y[4];
    s32 unk_54[4];
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C[4];
    s32 unk_7C[4];
    u16 angle[4];
    s8 unk_94;
    u8 unk_95;
    u8 unk_96;
    u8 unk_97;
    TaskPool tasks;
} LevelUpEffectWork;

typedef struct StockInfoWork {
    void* tiles;
    void* palette;
    s32 x;
    s32 y;
    s8 timer;
    u8 unk_11[3];
    u8* active;
    TaskPool tasks;
} StockInfoWork;

typedef struct UnkStruct_080ABA80 {
    s32 unk_00[6];
} UnkStruct_080ABA80;

extern const UnkStruct_080ABA80 gUnk_09045188;
extern const UnkStruct_080ABA80 gUnk_09033FD0;
extern const UnkStruct_080ABA80 gUnk_090352FC;

typedef struct GimmickCardArgs {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 cardId;
} GimmickCardArgs;

typedef struct WorldSelBeforeWork {
    void* tiles;
    ObjPalette* palette;
    void* tiles2;
    ObjPalette* palette2;
    s32 x;
    s32 y;
    s32 z;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E[0x02];
    s32 x2[10];
    s32 y2[10];
    s32 z2[10];
    u8 angle[10];
    u8 unk_A2;
    u8 unk_A3;
    u8 unk_A4[0x14];
} WorldSelBeforeWork;

typedef struct WorldSelBeforeArgs {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} WorldSelBeforeArgs;

typedef struct EventBgEffectFrame {
    u16 duration;
    u16 tilesOffset;
} EventBgEffectFrame;

typedef struct EventBgEffectDef {
    void** maps;
    u8* tiles;
    void* palette;
    u16 tilesSize;
    u16 paletteSize;
    u8 unk_10[0x04];
    const EventBgEffectFrame* frames;
    u8 frameCount;
    s8 loopFrame;
} EventBgEffectDef;

typedef struct EventBgEffectWork {
    const EventBgEffectEntry* entries;
    u8 unk_04[0x08];
    u16 unk_0C;
    u16 unk_0E;
    u8 unk_10[0x02];
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
} EventBgEffectWork;

extern const EventBgEffectDef* gUnk_09EE79B4[];

typedef struct ReloadArgs {
    u8 slot;
    u8 mode;
    u8 unk_02[0x02];
    u8* state;
} ReloadArgs;

typedef struct ReloadWork {
    void* tiles;
    void* palette;
    void* gfx;
    AnimState anim;
    s32 x;
    s32 y;
    ReloadArgs args;
    u8 unk_34;
} ReloadWork;

typedef struct UnkStruct_080984E4 {
    u8 unk_00[0x08];
    UnkStruct_080038C8* tiles;
    u8 unk_0C[0x14];
    s32 unk_20;
    u8 unk_24[0x0A];
    u16 unk_2E;
    u16 unk_30;
} UnkStruct_080984E4;

typedef struct SysMsgWinWork {
    ObjTiles* tiles3;
    ObjPalette* palette;
    ObjTiles* tiles4;
    ObjPalette* palette2;
    ObjTiles* tiles;
    ObjPalette* palette3;
    ObjTiles* tiles2;
    ObjPalette* palette4;
    TextSlot textSlots[10];
    TextSlot textSlots2[10];
    ObjPalette* unk_0C0;
    AnimState anim;
    AnimState anim2;
    AnimState anim3;
    CardMessageArgs args;
    CardMessageDef* messageDef;
    s32 x;
    s32 unk_11C;
    s32 unk_120;
    s32 unk_124;
    void* gfx4;
    void* gfx;
    TextChar* nextText;
    u16 unk_134;
    s16 unk_136;
    u8 unk_138[0x05];
    u8 unk_13D;
    u8 unk_13E;
    u8 unk_13F;
    u8 unk_140;
    u8 unk_141;
    u8 unk_142;
    u8 unk_143;
    u8 unk_144;
    u8 unk_145;
    u8 unk_146[0x02];
} SysMsgWinWork;

typedef char SysMsgWinWork_size[(sizeof(SysMsgWinWork) == 0x148) ? 1 : -1];

typedef struct CardMsgWinWork {
    ObjTiles* tiles3;
    ObjPalette* palette;
    ObjTiles* tiles4;
    ObjPalette* palette2;
    ObjTiles* tiles;
    ObjPalette* palette3;
    ObjTiles* tiles2;
    ObjPalette* palette4;
    TextSlot textSlots[10];
    TextSlot textSlots2[10];
    ObjPalette* unk_0C0;
    AnimState anim;
    AnimState anim2;
    AnimState anim3;
    CardMessageArgs args;
    CardMessageDef* messageDef;
    s32 x;
    s32 unk_11C;
    s32 unk_120;
    s32 unk_124;
    s32 unk_128;
    void* gfx;
    void* gfx2;
    void* gfx3;
    TextChar* nextText;
    u16 unk_13C;
    s16 unk_13E;
    u8 unk_140;
    u8 unk_141;
    u8 unk_142;
    u8 unk_143;
    u8 unk_144;
    u8 unk_145;
    u8 unk_146[0x02];
    u8 unk_148;
    u8 unk_149;
    u8 unk_14A[0x02];
    u8 unk_14C;
    u8 unk_14D;
    u8 unk_14E;
    u8 unk_14F;
} CardMsgWinWork;

typedef char CardMsgWinWork_size[(sizeof(CardMsgWinWork) == 0x150) ? 1 : -1];

typedef struct UnkStruct_08094CE4_A {
    void* tiles;
    void* palette;
    u8 unk_08[0x10];
    u16 tilesSize;
} UnkStruct_08094CE4_A;

typedef struct UnkStruct_08094CE4_B {
    void* tiles;
    void* palette;
    u8 unk_08[0x0C];
    u16 tilesSize;
} UnkStruct_08094CE4_B;

extern const s16 gUnk_090361B0[];
extern const s16 gUnk_090361B8[];
extern const s16 gUnk_090361C0[];

typedef struct BossCardWork {
    CardDef* cardDef;
    CardBack* cardBack;
    const s32* unk_08;
    u8 unk_0C[0x18];
    s32 unk_24;
    s16 unk_28;
    u16 unk_2A;
    s16 unk_2C;
    u8 unk_2E;
    u8 unk_2F;
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
} BossCardWork;

extern const s16 gUnk_0903595E[];
extern const s16 gUnk_09035964[];

s32 func_0808F358(DeckMenuWork* w);

void func_0807E230(void);
void func_0807E254(void);

Deck* GetActiveDeck(void);
Deck* GetDeck(u8 index);
u8 func_08085B84(u16 index);
u16 func_08085B5C(u16 index);
void SetActiveDeckIndex(u8 index);
u16 GetDeckCpCost(u8 index);

void func_08066588(s16 a, s16 b, void* c, void* d, s32 e, u8 f);
void func_0807B410(TaskPool* pool);
void func_080933D8(UnkStruct_080933D8* p);
u8 func_0807B60C(void);
u8 func_08081888(void);
u16 func_08078754(CardBattleWork* w, u8 n);
u8 func_0809C448(struct UnkStruct_0809BB4C* w, void* a);
u8 func_0807BE54(CardDisplayWork* p, void* a);
u8 func_08088EB4(DeckMenuWork* w, void* a);
void func_08078330(CardSlot* slots, s32 deckIndex);
u8 func_0807CBC0(CardDisplayWork* p, void* a);
u8 func_0807D930(CardDisplayWork* p, void* a);
u8 func_08094934(MapcardWork* w, void* a);
u8 SpotLight_1(SpotlightWork* w, void* a);
u8 func_08098FDC(RevCountWork* w);
void REV_COUNT_0(RevCountWork* w, RevCountArgs* a);
u8 REV_COUNT_1(RevCountWork* w, void* a);
void REV_COUNT_2(RevCountWork* w);
void REV_COUNT_3(RevCountWork* w);
u8 func_080990CC(RevCountWork* w, void* a);
void func_0809A4E0(UnkStruct_0809A02C* w, u8 kind);
void Friend_card_0(UnkStruct_0809A02C* w, s32* args);
void Heartless_card_0(UnkStruct_0809A02C* w, s32* args);
s32 Friend_card_1(UnkStruct_0809A02C* w, void* a);
s32 Gimmick_card_1(UnkStruct_0809A02C* w, void* a);
u8 func_0809AB2C(UnkStruct_0809A02C* w);
s32 func_0809AD60(UnkStruct_0809A02C* w, void* a);
s32 func_0809AD98(UnkStruct_0809A02C* w, void* a);
s32 Heartless_card_1(UnkStruct_0809A02C* w, void* a);
void func_0809B200(UnkStruct_0809A02C* w);
void Heartless_card_2(UnkStruct_0809A02C* w);
void func_0809B59C(UnkStruct_0809A02C* w);
void Heartless_card_3(UnkStruct_0809A02C* w);
void func_08090100(DeckCard2Work* n);
u8 Card_EFFECT_1(CardEffectWork* w);
void func_0809D1FC(u8 bg);
u8 func_08083B20(BossCardWork* w, u8 b);
void func_08097390(UnkStruct_08096F94* w);
void func_080999A4(BossPrizeWork* w);
u8 StockInfo_1(StockInfoWork* w, void* a);
void func_08090A54(CardDisplayWork* p, void* a);
u8 func_0809438C(MapSelectWork* w, void* a);
void func_080A6E3C(RikuDeckMenuWork* w);
void func_080AA328(DeckExchangeWork* w);
void func_08083F08(u8 kind, u16* out);
void func_0808E364(DeckMenuWork* w, u8 kind);
void func_08096638(PrizeCardWork* w);
void func_080978B0(UnkStruct_08096F94* w);
void func_08099928(BossPrizeWork* w);
void PrizeBoss_0(BossPrizeWork* w, PrizeCardTaskArgs* args);
u8 PrizeBoss_1(BossPrizeWork* w, void* a);
void PrizeBoss_2(BossPrizeWork* w);
void PrizeBoss_3(BossPrizeWork* w);
u8 func_0809C710(UnkStruct_0809C534* w, void* a);
void func_080AAA8C(DeckExchangeWork* w, u8 kind);
u8 func_0808FA0C(DeckMenuWork* w, void* a);
void func_0807FAD8(CardBattleWork* w);
void InitDecks(void);
void func_08090ACC(CardDisplayWork* p, void* a);
u8 func_0809486C(MapcardWork* w, void* a);
void SpotLight_0(SpotlightWork* w, u8* src);
u8 func_08099048(RevCountWork* w, void* a);
u8 func_0809ACDC(UnkStruct_0809A02C* w);
u8 func_0809C4B0(struct UnkStruct_0809BB4C* w, void* a);
void func_0809D87C(u16 a, u16 b, u16 c, u16 bits);
void func_080A09C0(u16 n, u16* out);
u8 func_080A5F70(RikuDeckMenuWork* w, void* a);
u8 func_08097600(UnkStruct_08096F94* w);
u8 func_0809CBF8(UnkStruct_0809C534* w, void* a);
u8 func_080A6474(RikuDeckMenuWork* w, void* a);
void RecalculateInactiveDeckCpCosts(void);
u8 RELOAD_1(ReloadWork* w, void* a);
u8 func_08099C4C(BossPrizeWork* w);
void func_080A1BB8(EventMapObjectWork* w, EventBackgroundDef* t);
void Mode_riku_deckTutorial_1(void);
void func_0807A6C8(CardBattleWork* w);
u8 func_0807B578(CardBattleWork* w, void* a);
void func_0807FA44(CardBattleWork* w);
u8 func_080829D0(CardDisplayWork* p, void* a);
void card_enemy_0(CardDisplayWork* p, CardDisplayArgs* a);
void card_not_have_2(CardDisplayWork* p);
u8 func_0809C078(struct UnkStruct_0809BB4C* w, void* a);
void func_0809D900(u16 a, u16 b, u16 c, u32 v);
void func_080A69A0(RikuDeckMenuWork* w);
void func_080A99A0(DeckExchangeWork* w);
void func_08078D98(CardBattleWork* w, u8 kind, u8 c);
u8 func_0807CB24(CardDisplayWork* p, void* a);
u8 card_enemy_1(CardDisplayWork* p, void* a);
void func_080A6BB4(RikuDeckMenuWork* w);
void func_080A6B40(u8 a, u8 b);
void func_080A9AE8(DeckExchangeWork* w);
u8 func_0807D4E4(CardDisplayWork* p);
u8 func_08082F50(CardDisplayWork* p);
void func_0808CD48(DeckMenuWork* w);
void Mode_Premire_0(void);
void func_080A1DAC(EventBgEffectWork* w);
u8 func_080A207C(EventBgEffectWork* w);
u8 func_080A5C9C(RikuDeckMenuWork* w, void* a);
void func_080837FC(CardDisplayWork* p);
u8 map_anim_1(MapTileAnimationWork* w);
u8 Mapcard_1(MapcardWork* w, void* a);
void RELOAD_0(ReloadWork* w, ReloadArgs* a);
void func_0809C1EC(struct UnkStruct_0809BB4C* w);
void NO_Card_2(CardDisplayWork* p);
void ClearDeck(u8 deck);
void func_0807A75C(CardBattleWork* w);
u8 func_0807BA54(void);
u8 func_0807CE9C(CardDisplayWork* p);
u8 func_08082B48(CardDisplayWork* p);
void RemoveCardFromDeck(u16* p, u8 deck);
void func_0808D4E4(u8 kind, u8 slot);
u8 func_080909A4(CardDisplayWork* p);
u8 func_080A6A38(RikuDeckMenuWork* w);
u8 func_080A9A38(DeckExchangeWork* w);
void func_080AA148(u8 kind, u8 slot);
void Ev_mapObj_2(EventMapObjectWork* w);
void func_080984E4(UnkStruct_080984E4* w);
u8 card_reload_1(CardDisplayWork* p, void* a);
void func_0808E7D8(DeckMenuWork* w);
u8 func_080947B4(MapcardWork* w, void* a);
u8 func_080A63B8(RikuDeckMenuWork* w, void* a);
s16 func_080859A0(s32 mode, Deck* d);
u8 func_080A3DD0(CardMsgWinWork* w);
u8 func_08098AE4(ReloadChildWork* w, void* a);
void DeckCard2_2(DeckCard2Work* n);
void func_08081760(CardBattleWork* w);
void func_08094CE4(MapcardWork* w);
void func_0808D0A4(u8 deck);
void func_080A9E40(u8 deck);
void func_080A6C50(u8 deck);
u8 func_0809B840(StockNameWork* w);
u8 func_0809B9F4(StockNameWork* w);
u8 DeckCard2_1(DeckCard2Work* n);
void func_08078914(CardBattleWork* w, u8 n);
u8 func_08082154(CardDisplayWork* p, void* a);
void Bosscard_0(BossCardWork* w, u32* a);
void func_080985A0(UnkStruct_08098670* w, u16 b, s16 c, s16 d);
void RemoveCardFromActiveDeck(u16 slot);
u8 func_0807C3E8(CardDisplayWork* p, void* a);
u8 func_0808E934(DeckMenuWork* w, s16 x, s16 y, u16 dir);
void Mapcard_0(MapcardWork* w, MapcardArgs* a);
u8 AddCardToDeck(u16 card, u8 deck);
void func_08084D78(UnkStruct_08084D78* out, u8 deck, u8 mode, u16 n, void* p);
void func_080AB228(void);
u16 func_08093384(void);
void LVUP_EFFECT_0(LevelUpEffectWork* w, LevelUpEffectArgs* a);
void Deck_Clear_0(DeckConfirmWork* w, u8* a);
void Deck_Yes_No_0(DeckConfirmWork* w, u8* a);
void LVUP_EFFECT_2(LevelUpEffectWork* w);
u8 func_0809CB0C(UnkStruct_0809C534* w, void* a);
void Lvup_Logo_0(LevelUpEffectWork* w, LevelUpEffectArgs* a);
u8 func_080A3E8C(CardMsgWinWork* w, void* a);
u8 func_080A5EA0(RikuDeckMenuWork* w, void* a);
void func_080A4C1C(SysMsgWinWork* w);
void func_080A53E4(SysMsgWinWork* w);
s32 func_080A4D7C(CardMessageArgs* src);
s32 func_080A4DAC(void);
void func_08090864(CardDisplayWork* p);
void func_08099CDC(BossPrizeWork* w);
void func_0809C110(struct UnkStruct_0809BB4C* w);
void func_0809CE88(PremiumCardEffectWork* w, s16* a);
void func_0809CF64(PremiumCardEffectWork* w, s16* a);
void RELOAD_CHILDREN_2(ReloadChildWork* w);
u8 func_080AADD4(DeckExchangeWork* w, s16 x, s16 y, u16 dir);
u8 func_08090550(CardDisplayWork* p, void* a);
u8 AddCardToActiveDeck(u16 card);
void func_08084AC8(u16 a);
void func_08085A58(s32 a, u16* out);
void func_080A2E14(DeckConfirmWork* w);
void func_080A2EF8(DeckConfirmWork* w);
u8 func_0808CA78(DeckMenuWork* w, u8 a);
void func_0808C2F0(DeckMenuWork* w);
void HCEffectName_2(HcEffectNameWork* w);
u8 func_080A3558(CardMsgWinWork* w, void* a);
void func_08090B50(CardDisplayWork* p, void* a);
void RELOAD_CHILDREN_0(ReloadChildWork* w, ReloadChildArgs* a);
u8 Bosscard_1(BossCardWork* w, void* a);
void func_08094548(MapSelectWork* w);
u8 func_08099B60(BossPrizeWork* w, void* a);
void func_08083714(CardDisplayWork* w);
void func_080836C4(UnkStruct_08095A5C* p, void* a, u8 b, s8 c);
u8 func_08082A64(CardDisplayWork* p, void* a);
void func_0808E3E0(DeckMenuWork* w);
u8 func_080A18F4(LevelUpEffectWork* w);
u8 func_0809753C(UnkStruct_08096F94* w, void* a);
void func_0809B76C(StockNameWork* w, const s32* src);
void func_0809B920(StockNameWork* w, const s32* src);
void func_0808D438(u8 kind, u8 slot);
u8 func_0807BD64(CardDisplayWork* p, void* a);
u8 func_0807D3A0(CardDisplayWork* p, void* a);
u8 func_08082E0C(CardDisplayWork* p, void* a);
u8 func_08090DB0(CardDisplayWork* p, void* a);
void card_reload_0(CardDisplayWork* p, CardDisplayArgs* a);
void func_08091048(CardDisplayWork* p, CardDisplayArgs* a);
void func_0807DAD0(CardDisplayWork* p);
void Reload_Card_0(CardDisplayWork* p, CardDisplayArgs* a);
void func_08091138(CardDisplayWork* p, CardDisplayArgs* a);
u8 func_0809C620(UnkStruct_0809C534* w, void* a);
u8 EV_BG_EFFECT_1(EventBgEffectWork* w, void* a);
void func_0809C534(UnkStruct_0809C534* w, CardSlot* a);
void Card_EFFECT_0(CardEffectWork* w, CardEffectArgs* a);
void deckexchange_3(DeckExchangeWork* w);
void func_0807BB04(void);
void func_080818E4(void);
u8 func_0809DA64(HcEffectNameWork* w, u16 n);
void StockInfo_0(StockInfoWork* w, u8* active);
u8 func_080A3754(CardMsgWinWork* w, void* a);
u8 func_08082C98(CardDisplayWork* p, void* a);
u8 Reload_Card_1(CardDisplayWork* p, void* a);
u8 func_0808686C(DeckMenuWork* w, void* a);
u8 func_0807C4BC(CardDisplayWork* p, void* a);
u8 func_080A5034(SysMsgWinWork* w, void* a);
u8 func_0808E474(DeckMenuWork* w);
u8 func_080A3A98(CardMsgWinWork* w, void* a);
u8 func_08082224(CardDisplayWork* p, void* a);
u8 func_08081B70(CardDisplayWork* p, void* a);
u8 func_0807D68C(CardDisplayWork* p, void* a);
u8 func_0808A7E4(DeckMenuWork* w, void* a);
u8 func_080A5198(SysMsgWinWork* w, void* a);
void func_080A52BC(SysMsgWinWork* w);
void func_080A6D0C(void);
void WorldSel_Before_0(WorldSelBeforeWork* w, WorldSelBeforeArgs* a);
void func_0807BC24(CardDisplayWork* p, CardDisplayArgs* a);
void func_08081A3C(CardDisplayWork* p, CardDisplayArgs* a);
u8 RELOAD_CHILDREN_1(ReloadChildWork* w, void* a);
u8 func_0807CFA8(CardDisplayWork* p, void* a);
u8 func_08097404(UnkStruct_08096F94* w, void* a);
u8 func_080824C8(CardDisplayWork* p, void* a);
u8 func_0809423C(MapSelectWork* w, void* a);
u8 func_08099A18(BossPrizeWork* w, void* a);
void HCEffectName_0(HcEffectNameWork* w, u8* a);
u8 func_08082348(CardDisplayWork* p, void* a);
u8 func_0809C2D0(struct UnkStruct_0809BB4C* w, void* a);
u8 func_08090C3C(CardDisplayWork* p, void* a);

void CardName_0(CardNameWork* w);
void DarkPoint_0(DarkPointWork* w);
s32 DarkPoint_1(DarkPointWork* w);
void DarkPoint_2(DarkPointWork* w);
void DarkPoint_3(DarkPointWork* w);
#ifndef VERSION_EU
void func_080A8C58(DeckExchangeWork* w, u8 b);
#ifndef VERSION_EU
u8 func_080A7ABC(DeckExchangeWork* w, void* a);
void func_080A9B84(DeckExchangeWork* w, u8 b);
#endif
#endif

typedef struct SelmapEventKeyWork {
    void* tiles;
    void* palette;
    u8 unk_08[0xD0];
    void** unk_D8;
    AnimState anim;
    void* gfx;
    void* unk_F8;
    s32 unk_FC;
    s32 unk_100;
    s32 unk_104;
    s32 unk_108;
    s32 unk_10C;
    s32 unk_110;
    u16 unk_114;
    u16 unk_116;
    u16 unk_118;
    u8 unk_11A;
    u8 unk_11B;
    u8 unk_11C;
    u8 unk_11D;
    u8 unk_11E;
    u8 unk_11F;
    u8 unk_120;
    u8 unk_121;
    u8 unk_122;
    u8 unk_123;
} SelmapEventKeyWork;

typedef struct UnkStruct_09035898 {
    const s16* unk_00;
    s16 unk_04;
    u8 unk_06[2];
} UnkStruct_09035898;

extern const s16 gUnk_09035808[];
extern const s16 gUnk_09035874[];
extern const UnkStruct_09035898 gUnk_09035898[];
extern const UnkStruct_09035898 gUnk_090358D0[];
#ifdef VERSION_EU
extern const UnkStruct_09035898 gUnkEu_090CEC30[];
extern const UnkStruct_09035898 gUnkEu_090CEC70[];
extern const s16 gUnkEu_090CECE8[];
#endif
#ifdef VERSION_JP
extern const s16 gUnkJp_09008DEC[];
extern const u8 gUnkJp_090089B0[];
extern const u8 gUnkJp_090089BC[];
extern const u8 gUnkJp_090089C8[];
#endif

typedef struct UnkStruct_0809BB4C {
    void* tiles;
    ObjPalette* palette;
    void* tiles2;
    ObjPalette* palette2;
    void* tiles3;
    ObjPalette* palette3;
    void* tiles4;
    ObjPalette* palette4;
    void* tiles5;
    CardSlot* slots;
    void* gfx;
    void* gfx2;
    s16 unk_30;
    u8 unk_32[2];
    s32 unk_34;
    s32 unk_38;
    TaskPool tasks;
    u8 unk_50;
    u8 unk_51;
    u8 unk_52;
    u8 unk_53;
    AnimState anim;
    AnimState anim2;
    u8 unk_84;
    u8 unk_85;
    u8 unk_86;
    u8 unk_87;
    u8 unk_88;
    u8 unk_89;
    u8 unk_8A;
    u8 unk_8B;
    u8 unk_8C;
    u8 unk_8D[3];
} UnkStruct_0809BB4C;

typedef struct LevelUpWork {
    void* unk_000[8];
#ifdef VERSION_EU
    void* tiles5[3];
    u8 unk_02C[0xC];
#else
    TextSlot textSlots[6][36];
#endif
    void* palette;
    void* palette2;
    void* tiles;
    void* palette3;
    void* tiles2;
    void* tiles3;
    void* palette4;
    TaskPool pool;
    AnimState anim;
    void* tiles4;
    void* palette5;
    void* gfx;
    AnimState anim2;
    void* gfx2;
    s16 x4[3];
    s16 y4[3];
    s16 x5[3];
    s16 y5[3];
    s16 x;
    s16 x2;
    s32 y;
    s32 y2;
    s16 x3;
    s16 y3;
    s16 x6;
    s16 unk_77A;
    s16 unk_77C;
    u16 unk_77E[3];
    u16 unk_784[4];
    u16 unk_78C[4];
    u16 unk_794[4];
    u16 unk_79C[4];
    s16 unk_7A4;
    s16 unk_7A6;
    s32 x7;
    s32 y6;
    s8 unk_7B0;
    s8 unk_7B1;
    s8 unk_7B2[3];
    s8 unk_7B5;
    s8 unk_7B6;
    u8 textSlotCounts[6];
    u8 unk_7BD;
    u8 unk_7BE;
    u8 unk_7BF;
    u8 unk_7C0;
    u8 unk_7C1;
    u8 unk_7C2[2];
    u8 unk_7C4;
    u8 unk_7C5;
    u8 unk_7C6;
    u8 unk_7C7;
    u8 unk_7C8[3];
} LevelUpWork;

typedef struct StatIncreaseDisplayArgs {
    u8* done;
    u32 flags : 16;
    u32 amount : 16;
} StatIncreaseDisplayArgs;

extern s8 gUnk_0203C374;

extern const MapTileAnimationDef* gUnk_09EE4A2C[6];
extern const MapTileAnimationDef* gUnk_09EE4A44;
extern const MapTileAnimationDef* gUnk_09EE4A48;
extern const MapTileAnimationDef* gUnk_09EE4A4C;
extern const u16* gUnk_09EE4A68[12];
extern const u16* gUnk_09EE4A98[12];
#ifdef VERSION_EU
extern u8 gUnkEu_09F6FD74[7];
extern u8 gUnkEu_09F6FD7B[7];
extern u8 gUnkEu_09F6FD82[7];
extern void* gUnkEu_09F6FD8C[5];
extern void** gUnkEu_09F6FDA0[5];
extern void* gUnkEu_09F6FDB4[5];
extern void* gUnkEu_09F6FDDC[5];
extern u8* gUnkEu_09F6FE04[5];
extern void* gUnkEu_09F6FE30[5];
extern void** gUnkEu_09F6FE44[5];
extern void* gUnkEu_09F6FE58[5];
extern const u8* gUnkEu_09F6FE6C[8];
extern const u8* gUnkEu_09F6FE8C[7];
extern void* gUnkEu_09F6FF30[5];
extern void** gUnkEu_09F6FF44[5];
extern void** gUnkEu_09F6FF70[5];
extern u8 gUnkEu_09189F36[];
extern u8 gUnkEu_0918A73A[];
extern u8 gUnkEu_0918A48E[];
extern u8 gUnkEu_0918A1E2[];
extern u8 gUnkEu_0918B8F2[];
extern u8 gUnkEu_0919016A[];
extern u8 gUnkEu_0918E942[];
extern u8 gUnkEu_0918D11A[];
extern u8 gUnkEu_09191992[];
extern u8 gUnkEu_0919236A[];
extern u8 gUnkEu_09192022[];
extern u8 gUnkEu_09191CDA[];
extern u8 gUnkEu_094C9860[];
extern u8 gUnkEu_094C9C20[];
#else
extern u16 gUnk_09EE4AC8[7];
extern u16 gUnk_09EE4AD6[7];
extern u16 gUnk_09EE4AE4[7];
extern const u8* gUnk_09EE4B0C[7];
#endif
#ifdef VERSION_JP
extern const u8* gUnkJp_09EBC148[7];
extern const u8* gUnkJp_09EBC164[7];
#endif
extern const u16 gUnk_096102B8[];
extern const void* gUnk_09EE4BB0[2];
extern s16 gUnk_09EE4BB8[5];
extern s16 gUnk_09EE4BC2[2];
extern u16 gUnk_09EE4BE0[10];

extern Mode gModePremire;
#ifdef VERSION_EU
extern void* gUnkEu_09F72CB0[5];
extern void** gUnkEu_09F72CC4[5];
extern void* gUnkEu_09F72D08[5];
extern void* gUnkEu_09F72D1C[5];
extern void* gUnkEu_09F72DB0[6];
extern void* gUnkEu_09F72DC8[6];
extern void* gUnkEu_09F72DE0[6];
extern void* gUnkEu_09F72DF8[6];
extern void** gUnkEu_09F72E10[5];
extern u8 gUnkEu_094CE490[];
extern u8 gUnkEu_094CE820[];
extern u8 gUnkEu_094CE6F0[];
extern u8 gUnkEu_094CE5C0[];
extern u8 gUnkEu_094CF704[];
extern u8 gUnkEu_094D72E4[];
extern u8 gUnkEu_094DB664[];
extern u8 gUnkEu_094D9FE4[];
extern u8 gUnkEu_094D8964[];
#else
#ifdef VERSION_JP
extern const u8 gUnk_09037FAC[];
#else
extern const u16 gUnk_09037FAC[];
#endif
extern u16 gUnk_0815A066[];
extern u16 gUnk_0815A0BA[];
extern u16 gUnk_0815B1D2[];
extern u16 gUnk_0815A078[];
extern u16 gUnk_0815A0CC[];
extern u16 gUnk_0815B1A8[];
extern u16 gUnk_0815A116[];
extern u16 gUnk_0815A158[];
extern u16 gUnk_0815A0F4[];
extern u16 gUnk_0815A130[];
extern u16 gUnk_0815A176[];
extern u16* gUnk_09EE78D4[7];
extern u16* gUnk_09EE78F0[7];
#endif
extern const void* gUnk_09EE790C[2];
extern void* gUnk_09EE7914[3];
extern void* gUnk_09EE7998[7];
extern const EventBgEffectDef gUnk_0903803C;
extern const EventBgEffectDef gUnk_09038078;
extern const EventBgEffectDef gUnk_090380B4;
extern const EventBgEffectDef gUnk_090380F8;
extern const EventBgEffectDef gUnk_0903813C;
extern const EventBgEffectDef gUnk_09038198;
extern const EventBgEffectDef gUnk_090381CC;

extern CardHelpText* gUnk_09EE79EC[];
extern CardHelpText* gUnk_09EE79F4[];
extern CardHelpText* gUnk_09EE7A00[];
extern CardHelpText* gUnk_09EE7A08[];
extern CardHelpText* gUnk_09EE7A10[];
extern CardHelpText* gUnk_09EE7A18[];
extern CardHelpText* gUnk_09EE7A20[];
extern CardHelpText* gUnk_09EE7A28[];
extern CardHelpText* gUnk_09EE7A30[];
extern CardHelpText* gUnk_09EE7A38[];
extern CardHelpText* gUnk_09EE7A40[];
extern CardHelpText* gUnk_09EE7A48[];
extern CardHelpText* gUnk_09EE7A50[];
extern CardHelpText* gUnk_09EE7A58[];
extern CardHelpText* gUnk_09EE7A60[];
extern CardHelpText* gUnk_09EE7A68[];
extern CardHelpText* gUnk_09EE7A70[];
extern CardHelpText* gUnk_09EE7A78[];
extern CardHelpText* gUnk_09EE7A80[];
extern CardHelpText* gUnk_09EE7A88[];
extern CardHelpText* gUnk_09EE7A90[];
extern CardHelpText* gUnk_09EE7A98[];
extern CardHelpText* gUnk_09EE7AA0[];
extern CardHelpText* gUnk_09EE7AA8[];
extern CardHelpText* gUnk_09EE7AB8[];
extern CardHelpText* gUnk_09EE7AC8[];
extern CardHelpText* gUnk_09EE7AD8[];
extern CardHelpText* gUnk_09EE7AE8[];
extern CardHelpText* gUnk_09EE7AF8[];
extern CardHelpText* gUnk_09EE7B08[];
extern CardHelpText* gUnk_09EE7B18[];
extern CardHelpText* gUnk_09EE7B30[];
extern CardHelpText* gUnk_09EE7B28[];
extern CardHelpText* gUnk_09EE7B38[];
extern CardHelpText* gUnk_09EE7B48[];
extern CardHelpText* gUnk_09EE7B58[];
extern CardHelpText* gUnk_09EE7B68[];
extern CardHelpText* gUnk_09EE7B78[];
extern CardHelpText* gUnk_09EE7B88[];
extern CardHelpText* gUnk_09EE7B98[];
extern CardHelpText* gUnk_09EE7BA0[];
extern CardHelpText* gUnk_09EE7BA8[];
extern CardHelpText* gUnk_09EE7BB8[];
extern CardHelpText* gUnk_09EE7BC8[];
extern CardHelpText* gUnk_09EE7BD8[];
extern CardHelpText* gUnk_09EE7BE8[];
extern CardHelpText* gUnk_09EE7BF8[];
extern CardHelpText* gUnk_09EE7C08[];
extern CardHelpText* gUnk_09EE7C18[];
extern CardHelpText* gUnk_09EE7C28[];
extern CardHelpText* gUnk_09EE7C38[];
extern CardHelpText* gUnk_09EE7D54[];
extern CardHelpText* gUnk_09EE7D44[];
extern CardHelpText* gUnk_09EE7D64[];
extern CardHelpText* gUnk_09EE7C48[];
extern CardHelpText* gUnk_09EE7C50[];
extern CardHelpText* gUnk_09EE7C58[];
extern CardHelpText* gUnk_09EE7C64[];
extern CardHelpText* gUnk_09EE7D74[];
extern CardHelpText* gUnk_09EE7C6C[];
extern CardHelpText* gUnk_09EE7C74[];
extern CardHelpText* gUnk_09EE7C7C[];
extern CardHelpText* gUnk_09EE7C84[];
extern CardHelpText* gUnk_09EE7C8C[];
extern CardHelpText* gUnk_09EE7C94[];
extern CardHelpText* gUnk_09EE7C9C[];
extern CardHelpText* gUnk_09EE7CA4[];
extern CardHelpText* gUnk_09EE7CAC[];
extern CardHelpText* gUnk_09EE7CB4[];
extern CardHelpText* gUnk_09EE7D7C[];
extern CardHelpText* gUnk_09EE7CBC[];
extern CardHelpText* gUnk_09EE7CC8[];
extern CardHelpText* gUnk_09EE7CD0[];
extern CardHelpText* gUnk_09EE7CD8[];
extern CardHelpText* gUnk_09EE7CE0[];
extern CardHelpText* gUnk_09EE7CE8[];
extern CardHelpText* gUnk_09EE7CF0[];
extern CardHelpText* gUnk_09EE7CF8[];
extern CardHelpText* gUnk_09EE7D00[];
extern CardHelpText* gUnk_09EE7D08[];
extern CardHelpText* gUnk_09EE7D10[];
extern CardHelpText* gUnk_09EE7D18[];
extern CardHelpText* gUnk_09EE7D20[];
extern CardHelpText* gUnk_09EE7D2C[];
extern CardHelpText* gUnk_09EE7D34[];
extern CardHelpText* gUnk_09EE7D3C[];
extern const CardHelpDef* gCardHelpDefs[];
#ifdef VERSION_EU
extern u8 gUnkEu_090D1DA5[];
extern u8* gUnkEu_09F73464[5];
extern u8 gUnkEu_091926B2[];
extern u8 gUnkEu_0919308A[];
extern u8 gUnkEu_09192D42[];
extern u8 gUnkEu_091929FA[];
extern void* gUnkEu_09F7434C[5];
extern u8* gUnkEu_09F74374[5];
extern Mode gUnkEu_09F74600;
#else
extern Mode gUnk_09EE8F20;
#endif

extern u32 gUnk_02034AA4;
extern u32 gUnk_02034AA8;
extern CardDisplayWork* gUnk_02034AAC;
extern u8 gActiveDeck;
extern u8 gUnk_02034AB1[3];
extern s16 gUnk_02034AB4;
extern u8 gUnk_02034AB6[2];
#ifdef VERSION_EU
extern u8 gUnkEu_02034AD4[4];
#endif
extern TaskPool gUnk_02034AB8;
extern u8 gUnk_02034ACC;
extern u32 gUnk_02034AD0;
extern UnkStruct_02034AD4* gUnk_02034AD4;
extern u8 gUnk_02034AD8;
extern u8 gUnk_02034AD9;
extern u8 gUnk_02034ADA[6];
extern TaskPool gUnk_02034AE0;
#ifndef VERSION_EU
extern u8 gUnk_02034AF4[4];
#endif
extern u8 gUnk_02034AF8;
extern CardMsgWinWork* gUnk_02034AFC;
extern SysMsgWinWork* gUnk_02034B00;
#ifndef VERSION_EU
extern u8 gUnk_02034B04[4];
extern TaskPool gUnk_02034B08;
extern u8 gUnk_02034B1C;
extern u8 gUnk_02034B1D[3];
#endif
extern TaskPool gUnk_02034B20;
extern s32 gUnk_02034B34;
#ifdef VERSION_EU
extern TaskPool gUnkEu_02034B38;
extern u32 gUnkEu_02034B4C;
#endif
extern u8 gUnk_02039DD8;
extern u8 gUnk_02039DDC;
extern Deck gDecks[3];
extern u16 gCardCollection[999];
extern Deck* gUnk_0203A850;
extern void* gUnk_0203A854;
extern u16 gCardCount;
extern CardUiSpriteState gCardUiSpriteState;
extern MapCardUiResources gMapCardUiResources;
extern u8 gUnk_0203A8C0[270];
extern struct CardListWork* gCardListWork;
extern u8 gUnk_0203A9D4;
extern u8 gUnk_0203A9D8;
#ifndef VERSION_EU
extern u16 gUnk_0203A9DC;
#endif
extern u8 gUnk_0203A9E0;
extern s8 gUnk_0203A9E4;
extern u8 gUnk_0203A9E8;
extern TaskDesc gUnk_09EE496C;
extern TaskDesc gTaskDescCardNotHave;
extern TaskDesc gTaskDescCardReload;
extern TaskDesc gUnk_09EE49CC;
extern TaskDesc gTaskDescNOCard;
extern TaskDesc gTaskDescReloadCard;
extern TaskDesc gTaskDescBosscard;
extern const MapTileAnimationDef* gUnk_09EE4A2C[6];
extern const u16* gUnk_09EE4A68[12];
extern const u16* gUnk_09EE4A98[12];
#ifdef VERSION_EU
#else
extern u16 gUnk_09EE4AC8[7];
extern u16 gUnk_09EE4AD6[7];
extern u16 gUnk_09EE4AE4[7];
#endif
#ifdef VERSION_EU
extern void* gUnkEu_09F6FD8C[5];
extern void** gUnkEu_09F6FDA0[5];
extern void* gUnkEu_09F6FDB4[5];
extern void** gUnkEu_09F6FDC8[5];
extern void* gUnkEu_09F6FDDC[5];
extern void** gUnkEu_09F6FDF0[5];
extern u8* gUnkEu_09F6FE04[5];
extern void* gUnkEu_09F6FE30[5];
extern void** gUnkEu_09F6FE44[5];
extern void* gUnkEu_09F6FE58[5];
#endif
#ifdef VERSION_US
extern const u8* gUnk_09EE4B0C[7];
#endif
#ifdef VERSION_JP
extern const u8* gUnkJp_09EBC148[7];
extern const u8* gUnkJp_09EBC164[7];
#endif
#ifdef VERSION_EU
extern const u8* gUnkEu_09F6FE6C[8];
extern const u8* gUnkEu_09F6FE8C[7];
#endif
extern TaskDesc gTaskDescDeckCard2;
extern TaskDesc gUnk_09EE4B58;
extern TaskDesc gUnk_09EE4B70;
extern TaskDesc gUnk_09EE4B88;
#ifdef VERSION_EU
extern void* gUnkEu_09F6FF30[5];
extern void** gUnkEu_09F6FF44[5];
#endif
extern const void* gUnk_09EE4BB0[2];
extern s16 gUnk_09EE4BB8[5];
extern s16 gUnk_09EE4BC2[2];
#ifdef VERSION_EU
extern void** gUnkEu_09F6FF70[5];
#endif
extern TaskDesc gTaskDescMapSelect;
extern u16 gUnk_09EE4BE0[10];
extern MapCardBackDef gUnk_09EE4BF4[5];
extern MapCardDef gUnk_09EE4C80[260];
extern s16 gUnk_09EE7520[6];
extern UnkStruct_09EE752C gUnk_09EE752C[7];
extern TaskDesc gTaskDescMapcard;
extern TaskDesc gTaskDescReloadGage;
extern void* gUnk_09EE7578[4];
extern AnimHeader** gUnk_09EE7588[4];
extern void** gUnk_09EE7598[4];
extern void* gUnk_09EE75A8[4];
extern void** gUnk_09EE75B8[4];
extern AnimHeader** gUnk_09EE75C8[4];
extern TaskDesc gUnk_09EE75D8;
extern TaskDesc gTaskDescPrizeCardInit;
extern TaskDesc gTaskDescPrizeCardInitBoss;
extern TaskDesc gTaskDescDispCardname;
extern TaskDesc gTaskDescVersion;
extern TaskDesc gUnk_09EE7650;
#ifdef VERSION_EU
extern void* gUnkEu_09F72A3C[5];
extern void* gUnkEu_09F72A50[5];
extern void* gUnkEu_09F72A64[5];
#endif
extern TaskDesc gTaskDescSELMAPEVKEY;
extern void* gUnk_09EE7698[4];
extern TaskDesc gTaskDescReloadChildren;
extern void* gUnk_09EE76C0[4];
extern void** gUnk_09EE76D0[4];
extern TaskDesc gTaskDescREVCOUNT;
extern void* gUnk_09EE7708[3];
extern AnimHeader** gUnk_09EE7714[3];
extern void** gUnk_09EE7720[3];
extern TaskDesc gTaskDescRELOAD;
extern TaskDesc gTaskDescPrizeBoss;
extern TaskDesc gTaskDescCardEFFECT;
extern TaskDesc gTaskDescScrollbar;
extern TaskDesc gTaskDescFriendCard;
extern TaskDesc gTaskDescHeartlessCard;
extern TaskDesc gTaskDescGimmickCard;
extern TaskDesc gUnk_09EE77EC;
#ifdef VERSION_EU
extern void** gUnkEu_09F72BFC[5];
#endif
extern TaskDesc gUnk_09EE7804;
extern TaskDesc gUnk_09EE781C;
extern TaskDesc gTaskDescCardName;
#ifdef VERSION_EU
extern void* gUnkEu_09F72CB0[5];
extern void** gUnkEu_09F72CC4[5];
#endif
extern TaskDesc gTaskDescHCEffectName;
extern TaskDesc gTaskDescNumberPlus;
#ifdef VERSION_EU
extern void* gUnkEu_09F72D08[5];
extern void* gUnkEu_09F72D1C[5];
extern void** gUnk_09EEA1BC[5];
extern void* gUnkEu_09F72D44[5];
extern void** gUnkEu_09F72D58[5];
#endif
#ifndef VERSION_EU
extern u16* gUnk_09EE78D4[7];
extern u16* gUnk_09EE78F0[7];
#endif
extern const void* gUnk_09EE790C[2];
extern void* gUnk_09EE7914[3];
extern TaskDesc gTaskDescLevelUp;
#ifdef VERSION_EU
extern void* gUnk_09EE7938[6];
extern void** gUnkEu_09F72E10[5];
#endif
extern TaskDesc gTaskDescLVUPEFFECT;
extern TaskDesc gTaskDescLvupLogo;
extern const EventBgEffectDef* gUnk_09EE79B4[8];
extern TaskDesc gTaskDescEVBGEFFECT;
extern const CardHelpDef* gCardHelpDefs[];
extern TaskDesc gTaskDescStockInfo;
extern TaskDesc gTaskDescLvupMsg;
extern TaskDesc gTaskDescDeckEquip;
extern TaskDesc gTaskDescDeckYesNo;
extern TaskDesc gTaskDescDeckClear;
extern TaskDesc gUnk_09EE7FA8;
extern TaskDesc gUnk_09EE7FC0;
extern TaskDesc gUnk_09EE7FD8;
extern TaskDesc gUnk_09EE7FF0;
extern CardMessageDef gCardMessageDefs[];
extern TaskDesc gUnk_09EE8E18;
extern TaskDesc gUnk_09EE8E30;
extern TaskDesc gUnk_09EE8E48;
extern WorldSelAnim gWorldSelAnims[30];
extern TaskDesc gTaskDescWorldSelBefore;
#ifdef VERSION_EU
extern void* gUnkEu_09F7434C[5];
extern void** gUnkEu_09F74360[5];
extern u8* gUnkEu_09F74374[5];
#endif
#ifndef VERSION_EU
extern TaskDesc gTaskDescDeckexchange;
#endif
extern CardDescriptionText* gUnk_09EE8F48[98];

#endif /* GUARD_CARD_H */
