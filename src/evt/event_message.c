/**
 * event_message.c
 * Event Sequence Player
 */

#include "macros.h"
#include "registration_data.h"
#include "eventselect_api.h"
#include "system_state.h"
#include "msg_api.h"
#include "intr.h"
#include "m4a_song.h"
#include "obj_api.h"
#include "pallet.h"
#include "display.h"
#include "text.h"
#include "monsgage.h"
#include "anim.h"
#include "msg.h"
#include "sprites_deck_menu.h"
#include "sprites_evt.h"
#include "sprites_msg.h"
#include "sprites_card.h"
#include "msg_portrait_data.h"
#include "gba/keys.h"
#include "gba/io_reg.h"
#include "bos6_api.h"
#include "evt_obj_api.h"
#include "malloc.h"
#include "fade.h"
#include "songs.h"
#include "jiminy_data.h"
#include "common_text.h"
#include <stdlib.h>
#include <string.h>
#include "battle_actor.h"
#include "battle_actor_types.h"
#include "battle_work.h"
#include "engine_math.h"
#include "event_background_types.h"
#include "event_chara_types.h"
#include "event_index_data.h"
#include "evt_data.h"
#include "evt_object_types.h"
#include "evt_types.h"
#include "gba/defines.h"
#include "key.h"
#include "listpool.h"
#include "msg_types.h"
#include "obj.h"
#include "poo_api.h"
#include "sprite_palettes.h"
#include "taskpool.h"
#include "types.h"
#include <stddef.h>
#include "default_bg_map.h"

static void msgwin_0(MsgWinWork* work, u8* arg);
static u8 msgwin_1(MsgWinWork* work, void* a);
static void msgwin_2(MsgWinWork* work);
static void msgwin_3(MsgWinWork* work);

static const MsgFaceAnim sTalk00FaceAnims[8] = {
    {
        gTalk0000Tiles,
        gTalk0000Palette,
        gTalk0000Frames,
        gTalk0000Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0001Tiles,
        gTalk0000Palette,
        gTalk0001Frames,
        gTalk0001Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0002Tiles,
        gTalk0000Palette,
        gTalk0002Frames,
        gTalk0002Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0003Tiles,
        gTalk0000Palette,
        gTalk0003Frames,
        gTalk0003Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0004Tiles,
        gTalk0000Palette,
        gTalk0004Frames,
        gTalk0004Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0005Tiles,
        gTalk0000Palette,
        gTalk0005Frames,
        gTalk0005Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0005Tiles,
        gTalk0000Palette,
        gTalk0005Frames,
        gTalk0005Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0000Tiles,
        gTalk0000Palette,
        gTalk0000Frames,
        gTalk0000Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk01FaceAnims[6] = {
    {
        gTalk0100Tiles,
        gTalk0100Palette,
        gTalk0100Frames,
        gTalk0100Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0101Tiles,
        gTalk0100Palette,
        gTalk0101Frames,
        gTalk0101Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0102Tiles,
        gTalk0100Palette,
        gTalk0102Frames,
        gTalk0102Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0103Tiles,
        gTalk0100Palette,
        gTalk0103Frames,
        gTalk0103Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0104Tiles,
        gTalk0100Palette,
        gTalk0104Frames,
        gTalk0104Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0105Tiles,
        gTalk0100Palette,
        gTalk0105Frames,
        gTalk0105Anims,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk22FaceAnims[5] = {
    {
        gTalk0100Tiles,
        gTalk2200Palette,
        gTalk0100Frames,
        gTalk0100Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0101Tiles,
        gTalk2200Palette,
        gTalk0101Frames,
        gTalk0101Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0102Tiles,
        gTalk2200Palette,
        gTalk0102Frames,
        gTalk0102Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0103Tiles,
        gTalk2200Palette,
        gTalk0103Frames,
        gTalk0103Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0105Tiles,
        gTalk2200Palette,
        gTalk0105Frames,
        gTalk0105Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk02FaceAnims[5] = {
    {
        gTalk0200Tiles,
        gTalk0200Palette,
        gTalk0200Frames,
        gTalk0200Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0201Tiles,
        gTalk0200Palette,
        gTalk0201Frames,
        gTalk0201Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0202Tiles,
        gTalk0200Palette,
        gTalk0202Frames,
        gTalk0202Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0203Tiles,
        gTalk0200Palette,
        gTalk0203Frames,
        gTalk0203Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0204Tiles,
        gTalk0200Palette,
        gTalk0204Frames,
        gTalk0204Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk23FaceAnims[3] = {
    {
        gTalk0200Tiles,
        gTalk2300Palette,
        gTalk0200Frames,
        gTalk0200Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0201Tiles,
        gTalk2300Palette,
        gTalk0201Frames,
        gTalk0201Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0202Tiles,
        gTalk2300Palette,
        gTalk0202Frames,
        gTalk0202Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk03FaceAnims = {
    gTalk0300Tiles,
    gTalk0300Palette,
    gTalk0300Frames,
    gTalk0300Anims,
    2,
    1,
    { 0, 0 },
};

static const MsgFaceAnim sTalk04FaceAnims[4] = {
    {
        gTalk0400Tiles,
        gTalk0400Palette,
        gTalk0400Frames,
        gTalk0400Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0401Tiles,
        gTalk0400Palette,
        gTalk0401Frames,
        gTalk0401Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0402Tiles,
        gTalk0400Palette,
        gTalk0402Frames,
        gTalk0402Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0403Tiles,
        gTalk0400Palette,
        gTalk0403Frames,
        gTalk0403Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk05FaceAnims[4] = {
    {
        gTalk0500Tiles,
        gTalk0500Palette,
        gTalk0500Frames,
        gTalk0500Anims,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk0500Tiles,
        gTalk0500Palette,
        gTalk0500Frames,
        gTalk0500Anims + 2,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk0500Tiles,
        gTalk0500Palette,
        gTalk0500Frames,
        gTalk0500Anims + 4,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk0500Tiles,
        gTalk0500Palette,
        gTalk0500Frames,
        gTalk0500Anims + 6,
        8,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk06FaceAnims[5] = {
    {
        gTalk0600Tiles,
        gTalk0600Palette,
        gTalk0600Frames,
        gTalk0600Anims,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk0600Tiles,
        gTalk0600Palette,
        gTalk0600Frames,
        gTalk0600Anims + 2,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk0600Tiles,
        gTalk0600Palette,
        gTalk0600Frames,
        gTalk0600Anims + 4,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk0600Tiles,
        gTalk0600Palette,
        gTalk0600Frames,
        gTalk0600Anims + 6,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk0600Tiles,
        gTalk0600Palette,
        gTalk0600Frames,
        gTalk0600Anims + 8,
        10,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk07FaceAnims = {
    gTalk0700Tiles,
    gTalk0700Palette,
    gTalk0700Frames,
    gTalk0700Anims,
    2,
    1,
    { 0, 0 },
};

static const MsgFaceAnim sTalk08FaceAnims[2] = {
    {
        gTalk0800Tiles,
        gTalk0800Palette,
        gTalk0800Frames,
        gTalk0800Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk0800Tiles,
        gTalk0800Palette,
        gTalk0800Frames,
        gTalk0800Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk09FaceAnims[2] = {
    {
        gTalk0900Tiles,
        gTalk0900Palette,
        gTalk0900Frames,
        gTalk0900Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk0900Tiles,
        gTalk0900Palette,
        gTalk0900Frames,
        gTalk0900Anims + 1,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk10FaceAnims[15] = {
    {
        gTalk1000Tiles,
        gTalk1000Palette,
        gTalk1000Frames,
        gTalk1000Anims,
        12,
        1,
        { 0, 0 },
    },
    {
        gTalk1000Tiles,
        gTalk1000Palette,
        gTalk1000Frames,
        gTalk1000Anims + 2,
        12,
        1,
        { 0, 0 },
    },
    {
        gTalk1000Tiles,
        gTalk1000Palette,
        gTalk1000Frames,
        gTalk1000Anims + 4,
        12,
        1,
        { 0, 0 },
    },
    {
        gTalk1000Tiles,
        gTalk1000Palette,
        gTalk1000Frames,
        gTalk1000Anims + 6,
        12,
        1,
        { 0, 0 },
    },
    {
        gTalk1000Tiles,
        gTalk1000Palette,
        gTalk1000Frames,
        gTalk1000Anims + 8,
        12,
        1,
        { 0, 0 },
    },
    {
        gTalk1000Tiles,
        gTalk1000Palette,
        gTalk1000Frames,
        gTalk1000Anims + 10,
        12,
        1,
        { 0, 0 },
    },
    {
        gTalk1002Tiles,
        gTalk1000Palette,
        gTalk1002Frames,
        gTalk1002Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1002Tiles,
        gTalk1000Palette,
        gTalk1002Frames,
        gTalk1002Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1002Tiles,
        gTalk1000Palette,
        gTalk1002Frames,
        gTalk1002Anims + 4,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1003Tiles,
        gTalk1000Palette,
        gTalk1003Frames,
        gTalk1003Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1003Tiles,
        gTalk1000Palette,
        gTalk1003Frames,
        gTalk1003Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1003Tiles,
        gTalk1000Palette,
        gTalk1003Frames,
        gTalk1003Anims + 4,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1004Tiles,
        gTalk1000Palette,
        gTalk1004Frames,
        gTalk1004Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1004Tiles,
        gTalk1000Palette,
        gTalk1004Frames,
        gTalk1004Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1004Tiles,
        gTalk1000Palette,
        gTalk1004Frames,
        gTalk1004Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk11FaceAnims[5] = {
    {
        gTalk1100Tiles,
        gTalk1100Palette,
        gTalk1100Frames,
        gTalk1100Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1101Tiles,
        gTalk1100Palette,
        gTalk1101Frames,
        gTalk1101Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1102Tiles,
        gTalk1100Palette,
        gTalk1102Frames,
        gTalk1102Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1103Tiles,
        gTalk1100Palette,
        gTalk1103Frames,
        gTalk1103Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1104Tiles,
        gTalk1100Palette,
        gTalk1104Frames,
        gTalk1104Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk12FaceAnims[4] = {
    {
        gTalk1200Tiles,
        gTalk1200Palette,
        gTalk1200Frames,
        gTalk1200Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1201Tiles,
        gTalk1200Palette,
        gTalk1201Frames,
        gTalk1201Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1202Tiles,
        gTalk1200Palette,
        gTalk1202Frames,
        gTalk1202Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1203Tiles,
        gTalk1200Palette,
        gTalk1203Frames,
        gTalk1203Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk13FaceAnims[6] = {
    {
        gTalk1300Tiles,
        gTalk1300Palette,
        gTalk1300Frames,
        gTalk1300Anims,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1300Tiles,
        gTalk1300Palette,
        gTalk1300Frames,
        gTalk1300Anims + 2,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1300Tiles,
        gTalk1300Palette,
        gTalk1300Frames,
        gTalk1300Anims + 4,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1300Tiles,
        gTalk1300Palette,
        gTalk1300Frames,
        gTalk1300Anims + 6,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1301Tiles,
        gTalk1300Palette,
        gTalk1301Frames,
        gTalk1301Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk1301Tiles,
        gTalk1300Palette,
        gTalk1301Frames,
        gTalk1301Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk14FaceAnims[3] = {
    {
        gTalk1400Tiles,
        gTalk1400Palette,
        gTalk1400Frames,
        gTalk1400Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1401Tiles,
        gTalk1400Palette,
        gTalk1401Frames,
        gTalk1401Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1402Tiles,
        gTalk1400Palette,
        gTalk1402Frames,
        gTalk1402Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk15FaceAnims[5] = {
    {
        gTalk1500Tiles,
        gTalk1500Palette,
        gTalk1500Frames,
        gTalk1500Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1500Tiles,
        gTalk1500Palette,
        gTalk1500Frames,
        gTalk1500Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1502Tiles,
        gTalk1500Palette,
        gTalk1502Frames,
        gTalk1502Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1503Tiles,
        gTalk1500Palette,
        gTalk1503Frames,
        gTalk1503Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk1500Tiles,
        gTalk1500Palette,
        gTalk1500Frames,
        gTalk1500Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk16FaceAnims[4] = {
    {
        gTalk1600Tiles,
        gTalk1600Palette,
        gTalk1600Frames,
        gTalk1600Anims,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1600Tiles,
        gTalk1600Palette,
        gTalk1600Frames,
        gTalk1600Anims + 2,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1600Tiles,
        gTalk1600Palette,
        gTalk1600Frames,
        gTalk1600Anims + 4,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk1600Tiles,
        gTalk1600Palette,
        gTalk1600Frames,
        gTalk1600Anims + 6,
        8,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk17FaceAnims[3] = {
    {
        gTalk1700Tiles,
        gTalk1700Palette,
        gTalk1700Frames,
        gTalk1700Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1700Tiles,
        gTalk1700Palette,
        gTalk1700Frames,
        gTalk1700Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1700Tiles,
        gTalk1700Palette,
        gTalk1700Frames,
        gTalk1700Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk18FaceAnims[3] = {
    {
        gTalk1800Tiles,
        gTalk1800Palette,
        gTalk1800Frames,
        gTalk1800Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1800Tiles,
        gTalk1800Palette,
        gTalk1800Frames,
        gTalk1800Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1800Tiles,
        gTalk1800Palette,
        gTalk1800Frames,
        gTalk1800Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk19FaceAnims[3] = {
    {
        gTalk1900Tiles,
        gTalk1900Palette,
        gTalk1900Frames,
        gTalk1900Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1900Tiles,
        gTalk1900Palette,
        gTalk1900Frames,
        gTalk1900Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk1900Tiles,
        gTalk1900Palette,
        gTalk1900Frames,
        gTalk1900Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk20FaceAnims[4] = {
    {
        gTalk2000Tiles,
        gTalk2000Palette,
        gTalk2000Frames,
        gTalk2000Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2001Tiles,
        gTalk2000Palette,
        gTalk2001Frames,
        gTalk2001Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2002Tiles,
        gTalk2000Palette,
        gTalk2002Frames,
        gTalk2002Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2003Tiles,
        gTalk2000Palette,
        gTalk2003Frames,
        gTalk2003Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk21FaceAnims[5] = {
    {
        gTalk2100Tiles,
        gTalk2100Palette,
        gTalk2100Frames,
        gTalk2100Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2101Tiles,
        gTalk2100Palette,
        gTalk2101Frames,
        gTalk2101Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2102Tiles,
        gTalk2100Palette,
        gTalk2102Frames,
        gTalk2102Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2103Tiles,
        gTalk2100Palette,
        gTalk2103Frames,
        gTalk2103Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2104Tiles,
        gTalk2100Palette,
        gTalk2104Frames,
        gTalk2104Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk36FaceAnims = {
    gTalk3600Tiles,
    gTalk3600Palette,
    gTalk3600Frames,
    gTalk3600Anims,
    2,
    1,
    { 0, 0 },
};

static const MsgFaceAnim sTalk37FaceAnims[2] = {
    {
        gTalk3700Tiles,
        gTalk3700Palette,
        gTalk3700Frames,
        gTalk3700Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk3700Tiles,
        gTalk3700Palette,
        gTalk3700Frames,
        gTalk3700Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk24FaceAnims[6] = {
    {
        gTalk2400Tiles,
        gTalk2400Palette,
        gTalk2400Frames,
        gTalk2400Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2401Tiles,
        gTalk2400Palette,
        gTalk2401Frames,
        gTalk2401Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2402Tiles,
        gTalk2400Palette,
        gTalk2402Frames,
        gTalk2402Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2403Tiles,
        gTalk2400Palette,
        gTalk2403Frames,
        gTalk2403Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2404Tiles,
        gTalk2400Palette,
        gTalk2404Frames,
        gTalk2404Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2405Tiles,
        gTalk2400Palette,
        gTalk2405Frames,
        gTalk2405Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk25FaceAnims[6] = {
    {
        gTalk2500Tiles,
        gTalk2500Palette,
        gTalk2500Frames,
        gTalk2500Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2501Tiles,
        gTalk2500Palette,
        gTalk2501Frames,
        gTalk2501Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2502Tiles,
        gTalk2500Palette,
        gTalk2502Frames,
        gTalk2502Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2503Tiles,
        gTalk2500Palette,
        gTalk2503Frames,
        gTalk2503Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2504Tiles,
        gTalk2500Palette,
        gTalk2504Frames,
        gTalk2504Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2505Tiles,
        gTalk2500Palette,
        gTalk2505Frames,
        gTalk2505Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk26FaceAnims[2] = {
    {
        gTalk2600Tiles,
        gTalk2600Palette,
        gTalk2600Frames,
        gTalk2600Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2601Tiles,
        gTalk2600Palette,
        gTalk2601Frames,
        gTalk2601Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk30FaceAnims[4] = {
    {
        gTalk3000Tiles,
        gTalk3000Palette,
        gTalk3000Frames,
        gTalk3000Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3001Tiles,
        gTalk3000Palette,
        gTalk3001Frames,
        gTalk3001Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3002Tiles,
        gTalk3000Palette,
        gTalk3002Frames,
        gTalk3002Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3003Tiles,
        gTalk3000Palette,
        gTalk3003Frames,
        gTalk3003Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk31FaceAnims[4] = {
    {
        gTalk3100Tiles,
        gTalk3100Palette,
        gTalk3100Frames,
        gTalk3100Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3101Tiles,
        gTalk3100Palette,
        gTalk3101Frames,
        gTalk3101Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3102Tiles,
        gTalk3100Palette,
        gTalk3102Frames,
        gTalk3102Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3103Tiles,
        gTalk3100Palette,
        gTalk3103Frames,
        gTalk3103Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk33FaceAnims[6] = {
    {
        gTalk3300Tiles,
        gTalk3300Palette,
        gTalk3300Frames,
        gTalk3300Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk3301Tiles,
        gTalk3300Palette,
        gTalk3301Frames,
        gTalk3301Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3302Tiles,
        gTalk3300Palette,
        gTalk3302Frames,
        gTalk3302Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3303Tiles,
        gTalk3300Palette,
        gTalk3303Frames,
        gTalk3303Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3304Tiles,
        gTalk3300Palette,
        gTalk3304Frames,
        gTalk3304Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3300Tiles,
        gTalk3300Palette,
        gTalk3300Frames,
        gTalk3300Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk38FaceAnims[5] = {
    {
        gTalk3800Tiles,
        gTalk3800Palette,
        gTalk3800Frames,
        gTalk3800Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk3800Tiles,
        gTalk3800Palette,
        gTalk3800Frames,
        gTalk3800Anims + 4,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk3802Tiles,
        gTalk3800Palette,
        gTalk3802Frames,
        gTalk3802Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3803Tiles,
        gTalk3800Palette,
        gTalk3803Frames,
        gTalk3803Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3800Tiles,
        gTalk3800Palette,
        gTalk3800Frames,
        gTalk3800Anims + 2,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk40FaceAnims[4] = {
    {
        gTalk4000Tiles,
        gTalk4000Palette,
        gTalk4000Frames,
        gTalk4000Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4001Tiles,
        gTalk4000Palette,
        gTalk4001Frames,
        gTalk4001Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4002Tiles,
        gTalk4000Palette,
        gTalk4002Frames,
        gTalk4002Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4003Tiles,
        gTalk4000Palette,
        gTalk4003Frames,
        gTalk4003Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk41FaceAnims[4] = {
    {
        gTalk4100Tiles,
        gTalk4100Palette,
        gTalk4100Frames,
        gTalk4100Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk4101Tiles,
        gTalk4100Palette,
        gTalk4101Frames,
        gTalk4101Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk4101Tiles,
        gTalk4100Palette,
        gTalk4101Frames,
        gTalk4101Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk4100Tiles,
        gTalk4100Palette,
        gTalk4100Frames,
        gTalk4100Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk42FaceAnims[3] = {
    {
        gTalk4200Tiles,
        gTalk4200Palette,
        gTalk4200Frames,
        gTalk4200Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4200Tiles,
        gTalk4200Palette,
        gTalk4200Frames,
        gTalk4200Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4200Tiles,
        gTalk4200Palette,
        gTalk4200Frames,
        gTalk4200Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk43FaceAnims[3] = {
    {
        gTalk4300Tiles,
        gTalk4300Palette,
        gTalk4300Frames,
        gTalk4300Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4300Tiles,
        gTalk4300Palette,
        gTalk4300Frames,
        gTalk4300Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4300Tiles,
        gTalk4300Palette,
        gTalk4300Frames,
        gTalk4300Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk44FaceAnims[2] = {
    {
        gTalk4400Tiles,
        gTalk4400Palette,
        gTalk4400Frames,
        gTalk4400Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk4400Tiles,
        gTalk4400Palette,
        gTalk4400Frames,
        gTalk4400Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk45FaceAnims[2] = {
    {
        gTalk4500Tiles,
        gTalk4500Palette,
        gTalk4500Frames,
        gTalk4500Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk4500Tiles,
        gTalk4500Palette,
        gTalk4500Frames,
        gTalk4500Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk46FaceAnims[3] = {
    {
        gTalk4600Tiles,
        gTalk4600Palette,
        gTalk4600Frames,
        gTalk4600Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4600Tiles,
        gTalk4600Palette,
        gTalk4600Frames,
        gTalk4600Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4600Tiles,
        gTalk4600Palette,
        gTalk4600Frames,
        gTalk4600Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk47FaceAnims[3] = {
    {
        gTalk4700Tiles,
        gTalk4700Palette,
        gTalk4700Frames,
        gTalk4700Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4700Tiles,
        gTalk4700Palette,
        gTalk4700Frames,
        gTalk4700Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk4700Tiles,
        gTalk4700Palette,
        gTalk4700Frames,
        gTalk4700Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk50FaceAnims[4] = {
    {
        gTalk5000Tiles,
        gTalk5000Palette,
        gTalk5000Frames,
        gTalk5000Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5001Tiles,
        gTalk5000Palette,
        gTalk5001Frames,
        gTalk5001Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5002Tiles,
        gTalk5000Palette,
        gTalk5002Frames,
        gTalk5002Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5001Tiles,
        gUnk_09615058,
        gTalk5001Frames,
        gTalk5001Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk51FaceAnims[3] = {
    {
        gTalk5100Tiles,
        gTalk5100Palette,
        gTalk5100Frames,
        gTalk5100Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5100Tiles,
        gTalk5100Palette,
        gTalk5100Frames,
        gTalk5100Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5102Tiles,
        gTalk5100Palette,
        gTalk5102Frames,
        gTalk5102Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk55FaceAnims[4] = {
    {
        gTalk5500Tiles,
        gTalk5500Palette,
        gTalk5500Frames,
        gTalk5500Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5500Tiles,
        gTalk5500Palette,
        gTalk5500Frames,
        gTalk5500Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5502Tiles,
        gTalk5500Palette,
        gTalk5502Frames,
        gTalk5502Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5503Tiles,
        gTalk5500Palette,
        gTalk5503Frames,
        gTalk5503Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk39FaceAnims[4] = {
    {
        gTalk3900Tiles,
        gTalk3900Palette,
        gTalk3900Frames,
        gTalk3900Anims,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk3900Tiles,
        gTalk3900Palette,
        gTalk3900Frames,
        gTalk3900Anims + 2,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk3900Tiles,
        gTalk3900Palette,
        gTalk3900Frames,
        gTalk3900Anims + 4,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk3900Tiles,
        gTalk3900Palette,
        gTalk3900Frames,
        gTalk3900Anims + 6,
        8,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk52FaceAnims[5] = {
    {
        gTalk5200Tiles,
        gTalk5200Palette,
        gTalk5200Frames,
        gTalk5200Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5201Tiles,
        gTalk5200Palette,
        gTalk5201Frames,
        gTalk5201Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5202Tiles,
        gTalk5200Palette,
        gTalk5202Frames,
        gTalk5202Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5203Tiles,
        gTalk5200Palette,
        gTalk5203Frames,
        gTalk5203Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5204Tiles,
        gTalk5200Palette,
        gTalk5204Frames,
        gTalk5204Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk54FaceAnims[3] = {
    {
        gTalk5400Tiles,
        gTalk5400Palette,
        gTalk5400Frames,
        gTalk5400Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5401Tiles,
        gTalk5400Palette,
        gTalk5401Frames,
        gTalk5401Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5402Tiles,
        gTalk5400Palette,
        gTalk5402Frames,
        gTalk5402Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk49FaceAnims[4] = {
    {
        gTalk4900Tiles,
        gTalk4900Palette,
        gTalk4900Frames,
        gTalk4900Anims,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk4900Tiles,
        gTalk4900Palette,
        gTalk4900Frames,
        gTalk4900Anims + 2,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk4900Tiles,
        gTalk4900Palette,
        gTalk4900Frames,
        gTalk4900Anims + 4,
        8,
        1,
        { 0, 0 },
    },
    {
        gTalk4900Tiles,
        gTalk4900Palette,
        gTalk4900Frames,
        gTalk4900Anims + 6,
        8,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk48FaceAnims[5] = {
    {
        gTalk4800Tiles,
        gTalk4800Palette,
        gTalk4800Frames,
        gTalk4800Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4801Tiles,
        gTalk4800Palette,
        gTalk4801Frames,
        gTalk4801Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4802Tiles,
        gTalk4800Palette,
        gTalk4802Frames,
        gTalk4802Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4803Tiles,
        gTalk4800Palette,
        gTalk4803Frames,
        gTalk4803Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk4804Tiles,
        gTalk4800Palette,
        gTalk4804Frames,
        gTalk4804Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk56FaceAnims[3] = {
    {
        gTalk5600Tiles,
        gTalk5600Palette,
        gTalk5600Frames,
        gTalk5600Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5600Tiles,
        gTalk5600Palette,
        gTalk5600Frames,
        gTalk5600Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5602Tiles,
        gTalk5600Palette,
        gTalk5602Frames,
        gTalk5602Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk58FaceAnims[2] = {
    {
        gTalk5800Tiles,
        gTalk5800Palette,
        gTalk5800Frames,
        gTalk5800Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5800Tiles,
        gTalk5800Palette,
        gTalk5800Frames,
        gTalk5800Anims + 2,
        4,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk59FaceAnims[3] = {
    {
        gTalk5900Tiles,
        gTalk5900Palette,
        gTalk5900Frames,
        gTalk5900Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk5900Tiles,
        gTalk5900Palette,
        gTalk5900Frames,
        gTalk5900Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk5900Tiles,
        gTalk5900Palette,
        gTalk5900Frames,
        gTalk5900Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk60FaceAnims = {
    gTalk6000Tiles,
    gTalk6000Palette,
    gTalk6000Frames,
    gTalk6000Anims,
    2,
    1,
    { 0, 0 },
};

static const MsgFaceAnim sTalk61FaceAnims[3] = {
    {
        gTalk6100Tiles,
        gTalk6100Palette,
        gTalk6100Frames,
        gTalk6100Anims,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk6100Tiles,
        gTalk6100Palette,
        gTalk6100Frames,
        gTalk6100Anims + 2,
        6,
        1,
        { 0, 0 },
    },
    {
        gTalk6100Tiles,
        gTalk6100Palette,
        gTalk6100Frames,
        gTalk6100Anims + 4,
        6,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk34FaceAnims = {
    gTalk3400Tiles,
    gTalk3400Palette,
    gTalk3400Frames,
    gTalk3400Anims,
    2,
    1,
    { 0, 0 },
};

static const MsgFaceAnim sTalk35FaceAnims[3] = {
    {
        gTalk3500Tiles,
        gTalk3500Palette,
        gTalk3500Frames,
        gTalk3500Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3501Tiles,
        gTalk3500Palette,
        gTalk3501Frames,
        gTalk3501Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3502Tiles,
        gTalk3500Palette,
        gTalk3502Frames,
        gTalk3502Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk53FaceAnims[5] = {
    {
        gTalk5300Tiles,
        gTalk5300Palette,
        gTalk5300Frames,
        gTalk5300Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5301Tiles,
        gTalk5300Palette,
        gTalk5301Frames,
        gTalk5301Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5302Tiles,
        gTalk5300Palette,
        gTalk5302Frames,
        gTalk5302Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5303Tiles,
        gTalk5300Palette,
        gTalk5303Frames,
        gTalk5303Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk5304Tiles,
        gTalk5300Palette,
        gTalk5304Frames,
        gTalk5304Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk29FaceAnims[5] = {
    {
        gTalk2900Tiles,
        gTalk2900Palette,
        gTalk2900Frames,
        gTalk2900Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2901Tiles,
        gTalk2900Palette,
        gTalk2901Frames,
        gTalk2901Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2902Tiles,
        gTalk2900Palette,
        gTalk2902Frames,
        gTalk2902Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2903Tiles,
        gTalk2900Palette,
        gTalk2903Frames,
        gTalk2903Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2904Tiles,
        gTalk2900Palette,
        gTalk2904Frames,
        gTalk2904Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk28FaceAnims[6] = {
    {
        gTalk2800Tiles,
        gTalk2800Palette,
        gTalk2800Frames,
        gTalk2800Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2801Tiles,
        gTalk2800Palette,
        gTalk2801Frames,
        gTalk2801Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2802Tiles,
        gTalk2800Palette,
        gTalk2802Frames,
        gTalk2802Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2803Tiles,
        gTalk2800Palette,
        gTalk2803Frames,
        gTalk2803Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2804Tiles,
        gTalk2800Palette,
        gTalk2804Frames,
        gTalk2804Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk2805Tiles,
        gTalk2800Palette,
        gTalk2805Frames,
        gTalk2805Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk32FaceAnims[3] = {
    {
        gTalk3200Tiles,
        gTalk3200Palette,
        gTalk3200Frames,
        gTalk3200Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3201Tiles,
        gTalk3200Palette,
        gTalk3201Frames,
        gTalk3201Anims,
        2,
        1,
        { 0, 0 },
    },
    {
        gTalk3202Tiles,
        gTalk3200Palette,
        gTalk3202Frames,
        gTalk3202Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk57FaceAnims[3] = {
    {
        gTalk5700Tiles,
        gTalk5700Palette,
        gTalk5700Frames,
        gTalk5700Anims,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5700Tiles,
        gTalk5700Palette,
        gTalk5700Frames,
        gTalk5700Anims + 2,
        4,
        1,
        { 0, 0 },
    },
    {
        gTalk5702Tiles,
        gTalk5700Palette,
        gTalk5702Frames,
        gTalk5702Anims,
        2,
        1,
        { 0, 0 },
    },
};

static const MsgFaceAnim sTalk27FaceAnims[5] = {
    {
        gTalk2700Tiles,
        gTalk2700Palette,
        gTalk2700Frames,
        gTalk2700Anims,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk2700Tiles,
        gTalk2700Palette,
        gTalk2700Frames,
        gTalk2700Anims + 2,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk2700Tiles,
        gTalk2700Palette,
        gTalk2700Frames,
        gTalk2700Anims + 4,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk2700Tiles,
        gTalk2700Palette,
        gTalk2700Frames,
        gTalk2700Anims + 6,
        10,
        1,
        { 0, 0 },
    },
    {
        gTalk2700Tiles,
        gTalk2700Palette,
        gTalk2700Frames,
        gTalk2700Anims + 8,
        10,
        1,
        { 0, 0 },
    },
};

const MsgFaceAnim* gMsgFaceAnims[62] = {
    sTalk00FaceAnims,
    sTalk01FaceAnims,
    sTalk02FaceAnims,
    &sTalk03FaceAnims,
    sTalk04FaceAnims,
    sTalk05FaceAnims,
    sTalk06FaceAnims,
    &sTalk07FaceAnims,
    sTalk08FaceAnims,
    sTalk09FaceAnims,
    sTalk10FaceAnims,
    sTalk11FaceAnims,
    sTalk12FaceAnims,
    sTalk13FaceAnims,
    sTalk14FaceAnims,
    sTalk15FaceAnims,
    sTalk16FaceAnims,
    sTalk17FaceAnims,
    sTalk18FaceAnims,
    sTalk19FaceAnims,
    sTalk20FaceAnims,
    sTalk21FaceAnims,
    &sTalk36FaceAnims,
    sTalk37FaceAnims,
    sTalk22FaceAnims,
    sTalk23FaceAnims,
    sTalk24FaceAnims,
    sTalk25FaceAnims,
    sTalk26FaceAnims,
    sTalk38FaceAnims,
    sTalk40FaceAnims,
    sTalk41FaceAnims,
    sTalk43FaceAnims,
    sTalk44FaceAnims,
    sTalk50FaceAnims,
    sTalk51FaceAnims,
    sTalk55FaceAnims,
    sTalk42FaceAnims,
    sTalk30FaceAnims,
    sTalk45FaceAnims,
    sTalk46FaceAnims,
    sTalk47FaceAnims,
    sTalk39FaceAnims,
    sTalk52FaceAnims,
    sTalk54FaceAnims,
    sTalk49FaceAnims,
    sTalk48FaceAnims,
    sTalk56FaceAnims,
    sTalk58FaceAnims,
    sTalk59FaceAnims,
    &sTalk60FaceAnims,
    sTalk61FaceAnims,
    &sTalk34FaceAnims,
    sTalk53FaceAnims,
    sTalk29FaceAnims,
    sTalk33FaceAnims,
    sTalk35FaceAnims,
    sTalk32FaceAnims,
    sTalk31FaceAnims,
    sTalk57FaceAnims,
    sTalk28FaceAnims,
    sTalk27FaceAnims,
};

static const s32 sSpeakerFocusYOffsets[45] = {
    -8192, -8192, -8192, -12288, -8192, -8192, -8192, -12288,
    -8192, -8192, -8192, -12288, -8192, -8192, -8192, -12288,
    -8192, -8192, -8192, -12288, -8192, -8192, -8192, -12288,
    -8192, -8192, -8192, -12288, -8192, -8192, -8192, -12288,
    -8192, -8192, -8192, -12288, -8192, -8192, -8192, -12288,
    -8192, -8192, -8192, -12288, -12288,
};

const EventCharaParams gEventCharaParams[94] = {
    { -42, 256, 460, 0, 0, 0 },
    { -34, 256, 384, 0, 0, 0 },
    { -56, 256, 307, 0, 0, 0 },
    { -64, 256, 384, 16, -32, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -54, 256, 384, 0, 0, 0 },
    { -44, 256, 384, 0, 0, 0 },
    { -16, 256, 384, 0, 0, 0 },
    { -32, 256, 384, 0, 0, 0 },
    { -32, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -64, 256, 384, 0, 0, 0 },
    { -64, 256, 384, 0, 0, 0 },
    { -64, 256, 460, 0, 0, 0 },
    { -54, 256, 460, 0, 0, 0 },
    { -76, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -56, 256, 384, 0, 0, 0 },
    { -60, 256, 460, 0, 0, 0 },
    { -70, 332, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -64, 256, 384, 0, 0, 0 },
    { -33, 256, 384, 0, 0, 0 },
    { -77, 256, 460, 0, 0, 0 },
    { -82, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -30, 256, 384, 0, 0, 0 },
    { -90, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -59, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -64, 256, 384, 16, -50, 0 },
    { -49, 256, 384, 0, 0, 0 },
    { -60, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -70, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -56, 256, 384, 0, 0, 0 },
    { -66, 256, 384, 0, 0, 0 },
    { -44, 256, 384, 0, 0, 0 },
    { -90, 256, 384, 0, 0, 0 },
    { -65, 256, 384, 0, 0, 0 },
    { -34, 256, 384, 0, 0, 0 },
    { -72, 256, 384, 0, 0, 0 },
    { -53, 256, 384, 0, 0, 0 },
    { -45, 256, 384, 0, 0, 0 },
    { -54, 256, 384, 0, 0, 0 },
    { -54, 256, 384, 0, 0, 0 },
    { -72, 256, 384, 0, 0, 0 },
    { -54, 256, 384, 0, 0, 0 },
    { -54, 256, 384, 0, 0, 0 },
    { -71, 256, 384, 0, 0, 0 },
    { -54, 256, 384, 0, 0, 0 },
    { -41, 256, 384, 0, 0, 0 },
    { -34, 128, 384, 0, 0, 0 },
    { -54, 204, 384, 0, 0, 0 },
    { -24, 256, 384, 0, 0, 0 },
    { -32, 256, 384, 0, 0, 0 },
    { -23, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -66, 256, 384, 0, 0, 0 },
    { -66, 256, 384, 0, 0, 0 },
    { -60, 256, 384, 0, 0, 0 },
    { -77, 256, 384, 0, 0, 0 },
    { -64, 256, 384, 0, 0, 0 },
    { -60, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { -40, 256, 384, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0 },
};

TaskDesc gTaskDescEventSeq = {
    "event_seq",
    (TaskInitFunc)event_seq_0,
    (TaskUpdateFunc)event_seq_1,
    (TaskDrawFunc)event_seq_2,
    (TaskDestroyFunc)event_seq_3,
    sizeof(EventSeqWork),
};

static TaskDesc sTaskDescEventChara = {
    "event_chara",
    (TaskInitFunc)event_chara_0,
    (TaskUpdateFunc)event_chara_1,
    (TaskDrawFunc)event_chara_2,
    (TaskDestroyFunc)event_chara_3,
    sizeof(EventCharaWork),
};

static const u16 sEventCharaToggleAnims[2] = {
    145, 167,
};

const u16 gUnk_09033C90[4] = {
    2048, 2048, 2048, 2048,
};

const u16 gMsgwinClosedScrollX[4] = {
    0, 0, 255, 255,
};

const u16 gMsgwinOpenScrollX[4] = {
    255, 255, 0, 0,
};

const s32 gMsgwinTextX[4] = {
    4096, 4096, 18432, 18432,
};

const s32 gMsgwinTextY[4] = {
    3584, 28160, 3584, 28160,
};

static const u16* sMsgwinMapBlockPairs[4][2] = {
    {gUnk_08125E24, gUnk_0951D2B8},
    {gUnk_08125E24, gUnk_0951DAB8},
    {gUnk_0951E2B8, gUnk_08125E24},
    {gUnk_0951EAB8, gUnk_08125E24},
};

const void* gMsgwinMapBlocks[4] = {
    sMsgwinMapBlockPairs[0],
    sMsgwinMapBlockPairs[1],
    sMsgwinMapBlockPairs[2],
    sMsgwinMapBlockPairs[3],
};

static TaskDesc sTaskDescMsgwin = {
    "msgwin",
    (TaskInitFunc)msgwin_0,
    (TaskUpdateFunc)msgwin_1,
    (TaskDrawFunc)msgwin_2,
    (TaskDestroyFunc)msgwin_3,
    sizeof(MsgWinWork),
};

const s32 gMsgfaceHiddenX[4] = {
    114944, 114944, -76544, -76544,
};

const s32 gMsgfaceShownX[4] = {
    52736, 52736, 9216, 9216,
};

const s32 gMsgfaceY[4] = {
    14336, 32768, 14336, 32768,
};

static TaskDesc sTaskDescMsgface = {
    "msgface",
    (TaskInitFunc)msgface_0,
    (TaskUpdateFunc)msgface_1,
    (TaskDrawFunc)msgface_2,
    (TaskDestroyFunc)msgface_3,
    sizeof(MsgFaceWork),
};

const s32 gMsgwaitIconPos[4][2] = {
    {26112, 15872},
    {26112, 40448},
    {36864, 15872},
    {36864, 40448},
};

const s32 gMsgwaitYesnoCursorY[2] = {
    16128, 19968,
};

static TaskDesc sTaskDescMsgwait = {
    "msgwait",
    (TaskInitFunc)msgwait_0,
    (TaskUpdateFunc)msgwait_1,
    (TaskDrawFunc)msgwait_2,
    (TaskDestroyFunc)msgwait_3,
    sizeof(MsgWaitWork),
};

EventScanlineScroll* gEventScanlineScroll EWRAM_COMMON(4);

void event_seq_0(EventSeqWork* work, u8* a) {
#ifdef VERSION_EU
    EventBackgroundDef* u;
#endif
    gEventSoundMix = NULL;
    gBtlWork = NULL;
    work->task = NULL;
    work->eventId = a[0];
    work->unk_2E = a[1];
    work->seqDef = gEventSequenceDefs[work->eventId];
    work->unk_30 = 0;
    work->unk_31 = 0;
    gEventState->skipHoldTime = 0;
    work->ending = 0;
    work->hasBoss = 0;

#ifdef VERSION_EU
    work->hasMapAnim = 0;
    work->bg3MapUnpacked = 0;
    work->bg2MapUnpacked = 0;
    work->bg1MapUnpacked = 0;
#endif

    if (gEventState != NULL) {
        gEventState->running = 1;
        gEventState->talking = 0;
        gEventState->hasBg2Map = 0;
        gEventState->hasBg1Map = 0;
        gEventState->fadedOut = 0;
        gEventState->shakeX = 0;
        gEventState->shakeY = 0;
        gEventState->bgEffectActive = 0;
        gEventState->ending = 0;
        gEventState->answerYes = 0;
        gEventState->askedYesNo = 0;
        gEventState->endRequest = 0;

#ifndef VERSION_EU
        RequestDma3Clear(GetBgCharBase(1), 0x8000);
#endif

        if (work->seqDef->keyframes->flags & CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE) {
            SetBackdropColor(31, 31, 31);
            FadeStartIn(FADE_MODE_WHITE, 0x40);
        }

#ifdef VERSION_EU
        u = gEventBackgroundDefs[work->eventId];

        if (u != NULL) {
            if (u->tiles2 != NULL) {
                if ((u->flags & EVENT_BG_FLAG_POOH_MAP) != 0) {
                    SetupBg(0, 3, 31, 14);
                    SetupBg(1, 0, 29, 0);
                    SetupBg(2, 2, 30, 0);
                    SetupBg(3, 0, 28, 0);
                } else {
                    SetupBg(0, 3, 31, 14);
                    SetupBg(1, 2, 30, 0);
                    SetupBg(2, 0, 22, 0);
                    SetupBg(3, 0, 23, 0);
                }
            }

            if (u->isAffine != 0) {
                if (u->compression[0] == 1 || u->compression[0] == 3) {
                    LoadBgTilesLz77(2, u->tiles);
                } else {
                    LoadBgTiles(2, u->tiles, u->tilesSize);
                }

                LoadBgPalette(2, u->palette, u->paletteSize);
                SetBgColorMode(2, BGCNT_256COLOR);
                SetBgSize(2, 0x8000);

                if (u->compression[0] == 2 || u->compression[0] == 3) {
                    LoadBgMapLz77(2, (void*)*u->maps);
                } else {
                    LoadBgMap(2, *u->maps, 0x1000);
                }

                SetBgAffine(2, 0, 256, 256, 0, 0);
            } else {
                LoadEventBg3(work);
                LoadEventBg2Map(work);
                LoadEventBg1(work);
            }
        }

        if ((work->seqDef->keyframes->flags & 0xFF0) == 0) {
            FadeStartIn(FADE_MODE_BLACK, 64);
        } else if ((work->seqDef->keyframes->flags & 0xFF0) == CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE) {
            FadeStartIn(FADE_MODE_WHITE, 120);
        }

        work->timer = 0;
        InitEventState(work);
#endif
    }
}

#ifdef VERSION_EU
u8 LoadEventBg3(EventSeqWork* work) {
    EventBackgroundDef* u = gEventBackgroundDefs[work->eventId];

    if (u != NULL) {
        if (u->compression[0] == 1 || u->compression[0] == 3) {
            LoadBgTilesLz77(3, u->tiles);
        } else {
            LoadBgTiles(3, u->tiles, u->tilesSize);
        }

        LoadBgPalette(3, u->palette, u->paletteSize);

        if (u->maps != NULL) {
            if (u->compression[0] == 2 || u->compression[0] == 3) {
                work->bg3MapUnpacked = 1;
                SetBgMapBlocksLz77(3, u->maps, u->mapWidth, u->mapHeight);
            } else {
                work->bg3MapUnpacked = 0;
                SetBgMapBlocks(3, u->maps, u->mapWidth, u->mapHeight);
            }

            RedrawBgMapAt(3, 0, 0);
        }
    }

    return 1;
}

u8 LoadEventBg2Map(EventSeqWork* work) {
    EventBackgroundDef* u = gEventBackgroundDefs[work->eventId];

    if (u != NULL) {
        if (u->maps2 != NULL) {
            if (u->compression[0] == 2 || u->compression[0] == 3) {
                work->bg2MapUnpacked = 1;
                SetBgMapBlocksLz77(2, u->maps2, u->mapWidth, u->mapHeight);
            } else {
                work->bg2MapUnpacked = 0;
                SetBgMapBlocks(2, u->maps2, u->mapWidth, u->mapHeight);
            }

            RedrawBgMapAt(2, 0, 0);
            gEventState->hasBg2Map = 1;
        } else {
            DisableBg(2);
        }
    }

    return 1;
}

u8 LoadEventBg1(EventSeqWork* work) {
    EventBackgroundDef* u = gEventBackgroundDefs[work->eventId];

    if (u != NULL) {
        if (u->tiles2 != NULL) {
            if ((u->flags & EVENT_BG_FLAG_POOH_MAP) != 0) {
                LoadBgTiles(2, u->tiles2, u->tilesSize2);
            } else if (u->compression[0] == 1 || u->compression[0] == 3) {
                LoadBgTilesLz77(1, u->tiles2);
            } else {
                LoadBgTiles(1, u->tiles2, u->tilesSize2);
            }
        }

        if (u->maps3 != NULL) {
            if ((u->flags & EVENT_BG_FLAG_ALPHA_BLEND) != 0) {
                gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
                gBldAlpha = BLDALPHA_BLEND(14, 5);
                SetBgPriority(2, 1);
                gEventState->bldCnt = (BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
                gEventState->bldAlpha = BLDALPHA_BLEND(14, 5);
            } else {
                gEventState->bldCnt = 0;
                gEventState->bldAlpha = 0;
            }

            if (u->compression[0] == 2 || u->compression[0] == 3) {
                work->bg1MapUnpacked = 1;
                SetBgMapBlocksLz77(1, u->maps3, u->mapWidth, u->mapHeight);
            } else {
                work->bg1MapUnpacked = 0;
                SetBgMapBlocks(1, u->maps3, u->mapWidth, u->mapHeight);
            }

            RedrawBgMapAt(1, 0, 0);
            gEventState->hasBg1Map = 1;
        } else {
            DisableBg(1);
        }
    }

    return 1;
}

u8 InitEventState(EventSeqWork* work) {
    EventBackgroundDef* u = gEventBackgroundDefs[work->eventId];
    const EventCameraKeyframe* q = work->seqDef->keyframes;
    u16 i;
    gEventState->centerX = q->x;
    gEventState->centerY = q->y;
    gEventState->cameraX = gEventState->centerX - 0x7800;
    gEventState->cameraY = gEventState->centerY - 0x5000;
    gEventState->flags = 0;
    gEventState->frame = 0;
    gEventState->focusSpeaker = 0;
    gEventState->msgWinPosition = 0;
    gEventState->msgWinOpen = 0;
    gEventState->speaker = 0;
    gEventState->focusSteps = 0;
    gEventState->msgWaitActive = 0;
    gEventState->unk_7E = 0;
    gEventState->bossChara = 0;

    // @bug u is NULL for events without a background (NULL read).
    if (u->mapAnim != 5) {
        gEventState->mapAnim = u->mapAnim;
        work->hasMapAnim = 1;
    } else {
        gEventState->mapAnim = u->mapAnim;
    }

    for (i = 0; i < 16; i++) {
        gEventState->charaObjs[i] = NULL;
    }

    return 1;
}
#endif

u8 event_seq_1(EventSeqWork* work, void* a) {
    EventSeqArg arg;
#ifndef VERSION_EU
    s32 flag;
#endif
    EventBackgroundDef* u;
    const EventSequenceDef* t;
#ifndef VERSION_EU
    const EventCameraKeyframe* q;
    u16 i;
#endif
    u8 j;

#ifndef VERSION_EU
    flag = 0;
#endif
    u = gEventBackgroundDefs[work->eventId];

#ifndef VERSION_EU
    if (u != NULL) {
        if (u->tiles2 != NULL) {
            if ((u->flags & EVENT_BG_FLAG_POOH_MAP) != 0) {
                SetupBg(0, 3, 31, 14);
                SetupBg(1, 0, 29, 0);
                SetupBg(2, 2, 30, 0);
                SetupBg(3, 0, 28, 0);
            } else {
                SetupBg(0, 3, 31, 14);
                SetupBg(1, 2, 30, 0);
                SetupBg(2, 0, 22, 0);
                SetupBg(3, 0, 23, 0);
            }
        }

        if (u->isAffine != 0) {
            LoadBgTiles(2, u->tiles, u->tilesSize);
            LoadBgPalette(2, u->palette, u->paletteSize);
            SetBgColorMode(2, BGCNT_256COLOR);
            SetBgSize(2, 0x8000);
            LoadBgMap(2, *u->maps, 0x1000);
            SetBgAffine(2, 0, 256, 256, 0, 0);
        } else {
            LoadBgTiles(3, u->tiles, u->tilesSize);
            LoadBgPalette(3, u->palette, u->paletteSize);

            if (u->tiles2 != NULL) {
                if ((u->flags & EVENT_BG_FLAG_POOH_MAP) != 0) {
                    LoadBgTiles(2, u->tiles2, u->tilesSize2);
                } else {
                    LoadBgTiles(1, u->tiles2, u->tilesSize2);
                }
            }

            if (u->maps != NULL) {
                SetBgMapBlocks(3, u->maps, u->mapWidth, u->mapHeight);
                RedrawBgMapAt(3, 0, 0);
            }

            if (u->maps2 != NULL) {
                SetBgMapBlocks(2, u->maps2, u->mapWidth, u->mapHeight);
                RedrawBgMapAt(2, 0, 0);
                gEventState->hasBg2Map = 1;
            } else {
                DisableBg(2);
            }

            if (u->maps3 != NULL) {
                if ((u->flags & EVENT_BG_FLAG_ALPHA_BLEND) != 0) {
                    gBldCnt = (BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
                    gBldAlpha = BLDALPHA_BLEND(14, 5);
                    SetBgPriority(2, 1);
                    gEventState->bldCnt = (BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ);
                    gEventState->bldAlpha = BLDALPHA_BLEND(14, 5);
                } else {
                    gEventState->bldCnt = 0;
                    gEventState->bldAlpha = 0;
                }

                SetBgMapBlocks(1, u->maps3, u->mapWidth, u->mapHeight);
                RedrawBgMapAt(1, 0, 0);
                gEventState->hasBg1Map = 1;
            } else {
                DisableBg(1);
            }
        }
    }

    q = work->seqDef->keyframes;
    gEventState->centerX = q->x;
    gEventState->centerY = q->y;
    gEventState->cameraX = gEventState->centerX - 0x7800;
    gEventState->cameraY = gEventState->centerY - 0x5000;
    gEventState->flags = 0;
    gEventState->frame = 0;
    gEventState->focusSpeaker = 0;
    gEventState->msgWinPosition = 0;
    gEventState->msgWinOpen = 0;
    gEventState->speaker = 0;
    gEventState->focusSteps = 0;
    gEventState->msgWaitActive = 0;
    gEventState->unk_7E = 0;
    gEventState->bossChara = 0;

    // @bug u is NULL for events without a background (NULL read).
    if (u->mapAnim != 5) {
        gEventState->mapAnim = u->mapAnim;
        flag = 1;
    } else {
        gEventState->mapAnim = 5;
    }

    i = 0;
    t = work->seqDef;

    while (i < 16) {
        gEventState->charaObjs[i] = NULL;
        i++;
    }

#else
    t = work->seqDef;
#endif

    TaskPoolInit(&work->tasks, t->charaCount + 8);
    TaskPoolInit(&work->tasks2, 1);
    work->task = TaskCreate(&work->tasks2, &sTaskDescMsgwin, &work->eventId);

    for (j = 0; j < t->charaCount; j++) {
        arg.eventId = work->eventId;
        arg.chara = t->charaTracks[j].chara;
        arg.track = j;

        if (arg.chara > 94) {
            work->hasBoss = 1;
            gEventState->bossChara = arg.chara;
        }

        TaskCreate(&work->tasks, &sTaskDescEventChara, &arg);
    }

    TaskCreate(&work->tasks, &gTaskDescView, &work->eventId);
    TaskCreate(&work->tasks, &gTaskDescEvSound, &work->eventId);
    TaskCreate(&work->tasks, &gTaskDescEVBGEFFECT, &work->eventId);

#ifdef VERSION_EU
    if (work->hasMapAnim) {
#else
    if (flag) {
#endif
        TaskCreate(&work->tasks, &gTaskDescMapAnim, NULL);
    }

#ifndef VERSION_EU
    if ((work->seqDef->keyframes->flags & 0xFF0) == 0) {
        FadeStartIn(FADE_MODE_BLACK, 64);
    } else if ((work->seqDef->keyframes->flags & 0xFF0) == CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE) {
        FadeStartIn(FADE_MODE_WHITE, 120);
    }

    work->timer = 0;
#endif

    if (u != NULL) {
        if (u->mapObjects != NULL) {
            TaskCreate(&work->tasks, &gTaskDescEvMapObj, &work->eventId);
        }

        if ((u->flags & EVENT_BG_FLAG_POOH_MAP) != 0) {
            func_080CA35C();
            TaskCreate(&work->tasks, &gTaskDescPooMapanime, NULL);
        }
    }

    SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventSeq);
    return 1;
}

u8 UpdateEventSeqSkip() {
    u8 r = FadeIsActive();
    u8 v;

    if (r) {
        v = 1;
    } else {
        gEventState->running = 0;
        m4aMPlayAllStop();
        v = 0;
    }

    return v;
}

u8 UpdateEventSeq(EventSeqWork* work, void* a) {
    const EventSequenceDef* t;
    u8 i;

    if (gEventState == NULL) {
        return 0;
    }

    if ((GetKeysHeld() & START_BUTTON) != 0) {
        switch (work->eventId) {
        case 68:
        case 83:
        case 84:
            break;
        default:
            gEventState->skipHoldTime++;
            break;
        }
    } else {
        gEventState->skipHoldTime = 0;
    }

    if (gEventState->skipHoldTime > 64 || gEventState->endRequest == 1) {
        gEventState->skipHoldTime = 64;
        work->ending = 1;
        gEventState->ending = 1;
        FadeStartOut(FADE_MODE_BLACK, 64);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventSeqSkip);

        for (i = 0; i < 32; i++) {
            FadeSetPaletteExcluded(i, 0);
        }

        return 1;
    }

    if (work->timer == work->seqDef->startDelay) {
        gEventState->flags |= EVENT_FLAG_STARTED;
    } else {
        s32 t = work->seqDef->keyframes->flags & 0xFF0;

        if (t == 0) {
            FadeStartIn(FADE_MODE_BLACK, 64);
        } else if (t == 128) {
            FadeStartIn(FADE_MODE_WHITE, 120);
        }

        work->timer++;
    }

    TaskPoolUpdate(&work->tasks);
    TaskPoolUpdate(&work->tasks2);

    if (work->hasBoss) {
        gBtlWork->viewX = gEventState->cameraX;
        gBtlWork->viewY = gEventState->cameraY;
    }

    if ((gEventState->flags & (EVENT_FLAG_PAUSED | EVENT_FLAG_STARTED)) == EVENT_FLAG_STARTED) {
        gEventState->frame++;
    }

    t = gEventSequenceDefs[work->eventId];

    if (gEventState->frame >= t->endFrame && !work->ending && !FadeIsActive()) {
        if (!gEventState->fadedOut) {
            FadeStartOut(FADE_MODE_BLACK, 64);
        }

        work->ending = 1;
        gEventState->ending = 1;
    }

    if (work->ending == 1) {
        for (i = 0; i < 32; i++) {
            FadeSetPaletteExcluded(i, 0);
        }

        if (!FadeIsActive()) {
            gEventState->running = 0;
            return 0;
        }
    }

    return 1;
}

void event_seq_2(EventSeqWork* work) {
    TaskPoolDraw(&work->tasks2);

    if (work->hasBoss) {
        TaskPoolDraw(&gBtlWork->taskPools[0]);
    }

    TaskPoolDraw(&work->tasks);
}

void event_seq_3(EventSeqWork* work) {
    TaskPoolDestroy(&work->tasks);

    if (work->task != NULL) {
        TaskPoolDestroy(&work->tasks2);
    }

#ifdef VERSION_EU
    if (work->bg3MapUnpacked) {
        FreeBgDecompressedMap(3);
    }

    if (work->bg2MapUnpacked) {
        FreeBgDecompressedMap(2);
    }

    if (work->bg1MapUnpacked) {
        FreeBgDecompressedMap(1);
    }
#endif
}

void event_chara_0(EventCharaWork* work, EventSeqArg* a) {
    s32 v0;
    s32 v1;

    TaskPoolInit(&work->tasks, 8);
    work->arg = *a;
    work->keyframes = gEventSequenceDefs[work->arg.eventId]->charaTracks[work->arg.track].keyframes;
    work->keyframe = 0;
    work->steps = work->keyframes->frame;
    work->hopVelocity = 0;
    work->unk_18C = 0;
    work->unk_198 = 0;
    work->effectLevel = 0;
    work->effectTimer = 0;
    work->spriteX = 0;
    work->spriteY = 0;
    work->tiles = NULL;
    work->palette = NULL;
    work->gfx = NULL;
    work->spriteFlipX = 0;
    work->callbackActive = 0;
    work->usesBtlWork = 0;
    work->finished = 0;
    work->bobPhase = 0;
    work->visible = 1;
    work->unk_1B8 = 0;
    gEventState->charaObjs[work->arg.track] = &work->obj;

    switch (work->arg.chara) {
    case 95:
        // @bug Never sets gBtlWork->actor, which this intro dereferences (NULL read and write).
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        gBtlWork->flags = 0;
        work->usesBtlWork = 1;
        gBtlWork->viewX = gEventState->cameraX;
        gBtlWork->viewY = gEventState->cameraY;
        gBtlWork->scale = 0x100;
        gBtlWork->rotation = 0;
        gBtlWork->zoomScale = 0x100;
        gBtlWork->x = gEventState->cameraX;
        gBtlWork->y = gEventState->cameraY;
        gBtlWork->x2 = 0x10000;
        gBtlWork->y2 = 0x14000;
        gBtlWork->zoomX = 0x10000;
        gBtlWork->zoomY = 0x14000;
        gBtlWork->zoomSteps = 15;
        work->obj.x = work->keyframes->x;
        work->obj.y = work->keyframes->y;
        work->obj.z = work->keyframes->z;
        TaskCreate(&work->tasks, &gTaskDescBosTm, &work->obj);
        break;
    case 96:
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        SetBgPriority(0, 2);
        SetBgPriority(1, 1);
        SetBgPriority(2, 0);
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        gBtlWork->viewY = 0x5400;
        gBtlWork->scale = 0x100;
        gBtlWork->rotation = 0;
        SetBattleBounds(128, 424, 294, 384);
        gEventState->bossTask = TaskCreate(&work->tasks, &gTaskDescBosPc, NULL);
        break;
    case 97:
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        SetBgPriority(0, 2);
        SetBgPriority(1, 1);
        SetBgPriority(2, 0);
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        gBtlWork->viewY = 0x5400;
        gBtlWork->scale = 0x100;
        gBtlWork->rotation = 0;
        SetBattleBounds(128, 424, 294, 384);
        gEventState->bossTask = TaskCreate(&work->tasks, &gTaskDescBosPc, &work->tasks);
        work->hasObj = 0;
        gEventState->cameraX = v0 = gBtlWork->viewX;
        gEventState->cameraY = v1 = gBtlWork->viewY;
        gEventState->centerX = gBtlWork->x;
        gEventState->centerY = gBtlWork->y;
        gEventState->x = v0;
        gEventState->y = v1;
        break;
    case 100:
        SetBgSize(1, 0x4000);
        SetBgPriority(0, 2);
        SetBgPriority(1, 1);
        SetBgPriority(2, 0);
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        gBtlWork->viewY = 0x5400;
        gBtlWork->scale = 0x100;
        gBtlWork->rotation = 0;
        SetBattleBounds(128, 368, 480, 512);
        gEventState->bossTask = TaskCreate(&work->tasks, &gTaskDescBosLst, &work->tasks);
        break;
    case 101:
        SetupBg(0, 0, 24, 0);
        SetupBg(1, 0, 26, 0);
        SetupBg(2, 2, 28, 14);
        SetBgPriority(0, 2);
        SetBgPriority(1, 1);
        SetBgPriority(2, 0);
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        gBtlWork->x = 0x26600;
        gBtlWork->y = 0x12800;
        gBtlWork->viewX = 0x26600;
        gBtlWork->viewY = 0x12800;
        gBtlWork->x2 = 0x26600;
        gBtlWork->y2 = 0x12800;
        work->obj.x = 0x2A200;
        work->obj.y = 0x15E00;
        work->obj.z = -0x3800;
        SetBattleBounds(420, 612, 328, 384);
        TaskCreate(&work->tasks, &gTaskDescBosJf, &work->obj);
        break;
    case 103:
        SetupBg(0, 0, 24, 0);
        SetupBg(1, 0, 26, 0);
        SetupBg(2, 2, 28, 14);
        SetBgPriority(0, 2);
        SetBgPriority(1, 1);
        SetBgPriority(2, 0);
        // @bug Never sets gBtlWork->actor, which this intro dereferences (NULL read and write).
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        gBtlWork->flags = 0;
        work->usesBtlWork = 1;
        gBtlWork->x = 0x12C00;
        gBtlWork->y = 0x16800;
        gBtlWork->viewX = 0x12C00;
        gBtlWork->viewY = 0x16800;
        gBtlWork->x2 = 0x12C00;
        gBtlWork->y2 = 0x16800;
        gEventState->cameraX = gBtlWork->x - 0x7800;
        gEventState->cameraY = gBtlWork->y - 0x5000;
        gEventState->centerX = gBtlWork->x;
        gEventState->centerY = gBtlWork->y;
        gEventState->shakeX = 0;
        gEventState->shakeY = 0;
        work->obj.x = work->keyframes->x;
        work->obj.y = work->keyframes->y;
        work->obj.z = work->keyframes->z;
        SetBattleBounds(0, 256, 328, 424);
        TaskCreate(&work->tasks, &gTaskDescBosDsd, &work->obj);
        break;
    case 98:
        SetupBg(0, 0, 24, 0);
        SetupBg(1, 0, 26, 0);
        SetupBg(2, 2, 28, 10);
        SetBgPriority(0, 3);
        SetBgPriority(1, 2);
        SetBgPriority(2, 1);
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        TaskCreate(&work->tasks, &gTaskDescBosBoogie, NULL);
        gBtlWork->fadeAmount = 5;
        break;
    case 99:
        SetupBg(0, 0, 24, 0);
        SetupBg(1, 0, 26, 0);
        SetupBg(2, 2, 28, 10);
        SetBgPriority(0, 3);
        SetBgPriority(1, 2);
        SetBgPriority(2, 1);
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        TaskCreate(&work->tasks, &gTaskDescBosUrsula, NULL);
        gBtlWork->fadeAmount = 5;
        break;
    case 104:
        SetupBg(0, 0, 24, 0);
        SetupBg(1, 0, 26, 0);
        SetupBg(2, 2, 28, 10);
        SetBgPriority(0, 3);
        SetBgPriority(1, 2);
        SetBgPriority(2, 1);
        gBtlWork = EwramAlloc(sizeof(BtlWork));
        BtlWorkInit();
        gBtlWork->actor = &work->actor;
        gBtlWork->flags = BTL_FLAG_BOSS_BATTLE;
        TaskPoolInit(&gBtlWork->taskPools[0], 32);
        TaskPoolInit(&gBtlWork->taskPools[1], 1);
        work->usesBtlWork = 1;
        TaskCreate(&work->tasks, &gTaskDescBosGa, (void*)1);
        gBtlWork->fadeAmount = 5;
        break;
    default:
        if ((work->keyframes->flags & CHARA_KEYFRAME_FLAG_DEFER_SPAWN) == 0) {
            CreateEvtObjTask(&work->tasks, &work->obj, work->arg.chara, work->keyframes->anim, work->keyframes->x, work->keyframes->y, work->keyframes->z);
            work->hasObj = 1;
        } else {
            work->hasObj = 0;
        }

        SetupEventCharaShadow(work);
        break;
    }

    if (work->hasObj) {
        ApplyEventCharaDrawFlags(work);
    }
}

u8 event_chara_1(EventCharaWork* work, void* a) {
    u8 t;
    s32 v0;
    s32 v1;

    t = AdvanceEventCharaKeyframe(work);

    if (work->hasObj) {
        UpdateEventCharaMotion(work);
    }

    PlayEventCharaAnimSounds(work);

    if (t) {
        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
            ((void (*)(EventCharaWork*, void*))work->keyframes[work->keyframe].update)(work, a);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    if (work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_NO_SHADOW) {
        work->obj.flags |= EVTOBJ_FLAG_NO_SHADOW;
    } else {
        work->obj.flags &= ~EVTOBJ_FLAG_NO_SHADOW;
    }

    if (work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_PLAYER_CONTROL) {
        gEventState->flags |= EVENT_FLAG_PAUSED;
        gEventState->flags |= EVENT_FLAG_PLAYER_CONTROL;
        work->speed = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventCharaControl);
    }

    TaskPoolUpdate(&work->tasks);

    if (work->usesBtlWork) {
        switch (work->arg.chara) {
        case 0x62:
            gEventState->x = gEventState->cameraX = gBtlWork->x2;
            gEventState->y = gEventState->cameraY = gBtlWork->y2;
            TaskPoolUpdate(&gBtlWork->taskPools[1]);
            break;
        case 0x63:
            gBtlWork->viewY = gBtlWork->y;
            gBtlWork->x2 = gEventState->cameraX;
            gBtlWork->y2 = gEventState->cameraY;
            gEventState->x = gEventState->cameraX;
            gEventState->y = gEventState->cameraY;
            TaskPoolUpdate(&gBtlWork->taskPools[0]);
            TaskPoolUpdate(&gBtlWork->taskPools[1]);
            break;
        case 0x65:
            gEventState->cameraX = v0 = gBtlWork->viewX;
            gEventState->cameraY = v1 = gBtlWork->viewY;
            gEventState->centerX = gBtlWork->x;
            gEventState->centerY = gBtlWork->y;
            gEventState->x = v0;
            gEventState->y = v1;
            break;
        case 0x61:
            gBtlWork->x2 = gEventState->centerX;
            gBtlWork->y2 = gEventState->centerY;
            break;
        case 0x67:
            break;
        }
    }

    if (work->arg.chara == 0) {
        if (gBtlWork != NULL) {
            gBtlWork->actor->x = work->obj.x - 0x7800;
            gBtlWork->actor->y = work->obj.y - 0x5000;
            gBtlWork->actor->z = 0;
        }
    }

    if (work->finished) {
        return 0;
    }

    if (work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_TRANSLUCENT) {
        if (gFrameCounter % 6 == 0) {
            u16 v = GetRandom() % 7 + 4;

            gBldAlpha = ((16 - v) << 8) | v;
        }
    }

    return 1;
}

static inline s16 GetEventCharaScreenX(EventCharaWork* work) {
    return (work->spriteX >> 8) - (gEventState->x >> 8);
}

void event_chara_2(EventCharaWork* work) {
    const EventCharaKeyframe* e;
    s32 save;
    s32 x;
    s32 y;
    u16 h;

    save = work->obj.z;
    e = &work->keyframes[work->keyframe];

    if (e->flags & CHARA_KEYFRAME_FLAG_BOB) {
        work->obj.z = gSineTable[work->bobPhase] * 2 + save;
    } else if (e->flags & CHARA_KEYFRAME_FLAG_BOB_LARGE) {
        work->obj.z = gSineTable[work->bobPhase] * 3 + save;
    }

    if (work->visible != 0) {
        TaskPoolDraw(&work->tasks);
    }

    if (work->arg.chara == 99) {
        TaskPoolDraw(&gBtlWork->taskPools[0]);
    }

    if (work->tiles != NULL) {
        h = work->obj.drawFlags;

        if (work->spriteFlipX == 0) {
            h &= ~SPRITE_FLAG_HFLIP;
        } else {
            h |= SPRITE_FLAG_HFLIP;
        }

        x = GetEventCharaScreenX(work);
        y = (work->spriteY >> 8) + gEventCharaParams[work->arg.chara].spriteYOffset - (gEventState->y >> 8);
        DrawSprite(x, y, work->gfx, work->tiles, work->palette, NULL, h, 50);
    }

    work->obj.z = save;
}

void event_chara_3(EventCharaWork* work) {
    TaskPoolDestroy(&work->tasks);

    if (work->usesBtlWork) {
        TaskPoolDestroy(&gBtlWork->taskPools[0]);
        TaskPoolDestroy(&gBtlWork->taskPools[1]);
        EwramFree(gBtlWork);
    }
}

u8 AdvanceEventCharaKeyframe(EventCharaWork* work) {
    const EventCharaKeyframe* e = &work->keyframes[work->keyframe];
    u16 v;

    if (work->keyframes[work->keyframe].frame > gEventState->frame) {
        return 0;
    }

    if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_END) != 0) {
        return 0;
    }

    work->keyframe++;
    work->steps = work->keyframes[work->keyframe].frame - gEventState->frame;
    work->animId = work->keyframes[work->keyframe].anim;

    if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_SPAWN) != 0) {
        CreateEvtObjTask(&work->tasks, &work->obj, work->arg.chara, work->keyframes[work->keyframe].anim,
                      work->keyframes[work->keyframe].x, work->keyframes[work->keyframe].y,
                      work->keyframes[work->keyframe].z);
        work->hasObj = 1;
        SetupEventCharaShadow(work);
    }

    if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_DESPAWN) != 0) {
        work->finished = 1;
    }

    if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_SILHOUETTE) != 0) {
        LoadPalette(gEventSilhouettePalette, (void*)(work->obj.paletteIndex * 32 + OBJ_PLTT), 32);
    } else if ((work->keyframes[work->keyframe - 1].flags & CHARA_KEYFRAME_FLAG_SILHOUETTE) != 0) {
        LoadPalette(gEvtObjResources[work->arg.chara].res.palette, (void*)(work->obj.paletteIndex * 32 + OBJ_PLTT), 32);
    }

    if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_TRANSLUCENT) != 0) {
        gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
        v = work->obj.drawFlags;
        EvtObjSetDrawFlags(&work->obj, v | SPRITE_FLAG_BLEND);
    } else {
        v = work->obj.drawFlags;
        EvtObjSetDrawFlags(&work->obj, work->obj.drawFlags & ~SPRITE_FLAG_BLEND);
        work->unk_1B8 = 0;
    }

    if (work->hasObj) {
        if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_MOTION_MASK) == CHARA_MOTION_SET_POSITION) {
            EvtObjSetPos(&work->obj, work->keyframes[work->keyframe].x, work->keyframes[work->keyframe].y, work->keyframes[work->keyframe].z);
        }

        EvtObjSetAnim(&work->obj, work->animId);
        ApplyEventCharaDrawFlags(work);
        return 1;
    }

    if (work->keyframes[work->keyframe].anim == 0x3AF) {
        BosPcStartEventAnim(gEventState->bossTask);
    }

    if (work->keyframes[work->keyframe].anim == 0x3AB) {
        BosLstAdvanceEventStep(gEventState->bossTask);
    }

    return 0;
}

void UpdateEventCharaMotion(EventCharaWork* work) {
    const EventCharaKeyframe* e = &work->keyframes[work->keyframe];
    BtlObj* t;

    if (e->anim == 0x3A7) {
        t = ListPoolFirst(&gBtlWork->pool);

        if (t != NULL) {
            t->flags |= BTLOBJ_FLAG_DAMAGE_PENDING;
        }
    }

    switch (e->flags & CHARA_KEYFRAME_MOTION_MASK) {
    case CHARA_MOTION_SET_POSITION:
        EvtObjSetPos(&work->obj, work->keyframes[work->keyframe].x, work->keyframes[work->keyframe].y, work->keyframes[work->keyframe].z);
        break;
    case CHARA_MOTION_MOVE_TO:
        ApproachValue(&work->obj.x, work->keyframes[work->keyframe].x, work->steps);
        ApproachValue(&work->obj.y, work->keyframes[work->keyframe].y, work->steps);
        ApproachValue(&work->obj.z, work->keyframes[work->keyframe].z, work->steps);
        work->steps--;

        if (work->steps == 0) {
            if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_KEEP_ANIM) == 0) {
                SetEventCharaEndAnim(work);
            }
        }

        break;
    case CHARA_MOTION_WALK:
        if ((e->flags & CHARA_KEYFRAME_FLAG_FAST) == 0) {
            work->speed = gEventCharaParams[work->arg.chara].slowSpeed;
        } else {
            work->speed = gEventCharaParams[work->arg.chara].fastSpeed;
        }

        if (e->motionArg == 1) {
            work->obj.z -= work->speed;
        } else if (e->motionArg == 2) {
            work->obj.z += work->speed;
        } else {
            work->obj.x += (SIN(e->motionArg) * work->speed) >> 8;
            work->obj.y += (-COS(e->motionArg) * work->speed) >> 8;
        }

        break;
    }

    if ((e->flags & CHARA_KEYFRAME_FLAG_BOB) != 0) {
        work->bobPhase += 4;
    } else if ((e->flags & CHARA_KEYFRAME_FLAG_BOB_LARGE) != 0) {
        work->bobPhase += 4;
    } else {
        work->bobPhase = 0;
    }

    if ((e->flags & CHARA_KEYFRAME_FLAG_BLINK) != 0) {
        work->visible ^= 1;
    } else {
        work->visible = 1;
    }
}

void SetEventCharaEndAnim(EventCharaWork* work) {
    const EventCharaKeyframe* e = &work->keyframes[work->keyframe];

    EvtObjSetAnim(&work->obj, e->motionArg);
}

u8 EventCharaHop(EventCharaWork* work, void* a) {
    work->hopVelocity = 0x800;
    work->unk_18C = 0;
    work->waitTimer = 0;
    work->unk_198 = work->obj.z;
    TaskPoolUpdate(&work->tasks);
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaHopUpdate);
    return 1;
}

u8 EventCharaHopUpdate(EventCharaWork* work, void* a) {
    u16 x;
    u16 y;
    u8 t;

    x = (work->obj.x >> 8) - (gEventState->x >> 8);
    y = (work->obj.y >> 8) + (work->obj.z >> 8) - (gEventState->y >> 8);
    t = AdvanceEventCharaKeyframe(work);
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);

    if (work->waitTimer == 0) {
        work->obj.z -= work->hopVelocity / 4;
        work->hopVelocity -= work->unk_18C / 4;
        work->unk_18C += 51;
    } else {
        work->waitTimer--;

        if (work->waitTimer == 0) {
            if (work->arg.chara == 10) {
                m4aSongNumStart(SONG_SND_324);
                SetEventSoundPosition(SONG_SND_324, x, y);
            }
        }
    }

    if (work->obj.z > work->unk_198) {
        work->obj.z = work->unk_198;
        work->hopVelocity = 0x800;
        work->unk_18C = 0;
        work->waitTimer = 17;
    }

    if (t) {
        work->obj.z = work->unk_198;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaHopHigh(EventCharaWork* work, void* a) {
    work->hopVelocity = 0xC00;
    work->unk_18C = 0;
    work->waitTimer = 0;
    work->unk_198 = work->obj.z;
    TaskPoolUpdate(&work->tasks);
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaHopHighUpdate);
    return 1;
}

u8 EventCharaHopHighUpdate(EventCharaWork* work, void* a) {
    u8 t;

    t = AdvanceEventCharaKeyframe(work);
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);

    if (work->waitTimer == 0) {
        work->obj.z -= work->hopVelocity / 4;
        work->hopVelocity -= work->unk_18C / 4;
        work->unk_18C += 51;
    } else {
        work->waitTimer--;
    }

    if (work->obj.z > work->unk_198) {
        work->obj.z = work->unk_198;
        work->hopVelocity = 0;
        work->unk_18C = 0;
        work->waitTimer = 17;
    }

    if (t) {
        work->obj.z = work->unk_198;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaHopLow(EventCharaWork* work, void* a) {
    work->hopVelocity = 0x300;
    work->unk_18C = 0;
    work->waitTimer = 0;
    work->unk_198 = work->obj.z;
    TaskPoolUpdate(&work->tasks);
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaHopLowUpdate);
    return 1;
}

u8 EventCharaHopLowUpdate(EventCharaWork* work, void* a) {
    u8 t;

    t = AdvanceEventCharaKeyframe(work);
    PlayEventCharaAnimSounds(work);
    UpdateEventCharaMotion(work);

    if (work->waitTimer == 0) {
        work->obj.z -= work->hopVelocity;
        work->hopVelocity -= work->unk_18C;
        work->unk_18C += 51;
    } else {
        work->waitTimer--;
    }

    if (work->obj.z > work->unk_198) {
        work->obj.z = work->unk_198;
        work->hopVelocity = 0x800;
        work->unk_18C = 0;
        work->waitTimer = 17;
    }

    if (t) {
        work->obj.z = work->unk_198;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaDrop(EventCharaWork* work, void* a) {
    work->hopVelocity = 0x300;
    work->unk_18C = 0;
    work->waitTimer = 0;
    work->unk_198 = work->obj.z;
    TaskPoolUpdate(&work->tasks);
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaDropUpdate);
    return 1;
}

u8 EventCharaDropUpdate(EventCharaWork* work, void* a) {
    u8 t;

    t = AdvanceEventCharaKeyframe(work);
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);

    if (work->waitTimer == 0) {
        work->obj.z -= work->hopVelocity;
        work->hopVelocity -= work->unk_18C;
        work->unk_18C += 51;
    } else {
        work->waitTimer--;
    }

    if (work->obj.z > 0) {
        work->obj.z = 0;
        work->waitTimer = 17;
    }

    if (t) {
        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaFadeOut(void* work, void* a) {
    EventCharaWork* p = work;
    const EventCharaKeyframe* e;
    u16 z;

    UpdateEventCharaMotion(p);
    PlayEventCharaAnimSounds(p);

    if (AdvanceEventCharaKeyframe(p)) {
        if (p->keyframes[p->keyframe].update != NULL) {
            SetTaskUpdate(a, p->keyframes[p->keyframe].update);
        }

        if (p->keyframes[p->keyframe].callback != NULL) {
            p->keyframes[p->keyframe].callback(p);
            p->callbackActive = 1;
        } else {
            p->callbackActive = 0;
        }
    }

    z = p->obj.drawFlags;
    z |= 4;
    EvtObjSetDrawFlags(&p->obj, z);
    gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
    gBldAlpha = 16;
    p->effectTimer = 0;
    p->effectLevel = 16;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaFadeOutUpdate);

    if (p->arg.chara == 3) {
        e = &p->keyframes[p->keyframe];

        if ((e->flags & CHARA_KEYFRAME_FLAG_BLINK) == 0) {
            m4aSongNumStart(SONG_EV_WARPIN);
        }
    }

    TaskPoolUpdate(&p->tasks);
    return 1;
}

u8 EventCharaFadeOutUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->effectTimer++;

    if (work->effectTimer % 2 == 0) {
        if (work->effectLevel != 0) {
            work->effectLevel--;
        }
    }

    gBldAlpha = ((16 - work->effectLevel) << 8) | work->effectLevel;

    if (AdvanceEventCharaKeyframe(work)) {
        gBldCnt = 0;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }

        {
            u16 z = work->obj.drawFlags;

            z &= 0xFFFB;
            EvtObjSetDrawFlags(&work->obj, z);
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaFadeIn(void* work, void* a) {
    EventCharaWork* p = work;
    const EventCharaKeyframe* e;
    u16 z;

    UpdateEventCharaMotion(p);
    PlayEventCharaAnimSounds(p);

    if (AdvanceEventCharaKeyframe(p)) {
        if (p->keyframes[p->keyframe].update != NULL) {
            SetTaskUpdate(a, p->keyframes[p->keyframe].update);
        }

        if (p->keyframes[p->keyframe].callback != NULL) {
            p->keyframes[p->keyframe].callback(p);
            p->callbackActive = 1;
        } else {
            p->callbackActive = 0;
        }
    }

    z = p->obj.drawFlags;
    z |= 4;
    EvtObjSetDrawFlags(&p->obj, z);
    gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
    gBldAlpha = 0x1000;
    p->effectTimer = 0;
    p->effectLevel = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaFadeInUpdate);

    if (p->arg.chara == 3) {
        e = &p->keyframes[p->keyframe];

        if ((e->flags & CHARA_KEYFRAME_FLAG_BLINK) == 0) {
            m4aSongNumStart(SONG_EV_WARPOUT);
        }
    }

    TaskPoolUpdate(&p->tasks);
    return 1;
}

u8 EventCharaFadeInUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->effectTimer++;

    if (work->effectTimer % 2 == 0) {
        if (work->effectLevel <= 15) {
            work->effectLevel++;
        }
    }

    gBldAlpha = ((16 - work->effectLevel) << 8) | work->effectLevel;

    if (AdvanceEventCharaKeyframe(work)) {
        gBldCnt = 0;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }

        {
            u16 z = work->obj.drawFlags;

            z &= 0xFFFB;
            EvtObjSetDrawFlags(&work->obj, z);
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaBlendUp(void* work, void* a) {
    EventCharaWork* p = work;
    u16 z;

    UpdateEventCharaMotion(p);
    PlayEventCharaAnimSounds(p);

    if (AdvanceEventCharaKeyframe(p)) {
        if (p->keyframes[p->keyframe].update != NULL) {
            SetTaskUpdate(a, p->keyframes[p->keyframe].update);
        }

        if (p->keyframes[p->keyframe].callback != NULL) {
            p->keyframes[p->keyframe].callback(p);
            p->callbackActive = 1;
        } else {
            p->callbackActive = 0;
        }
    }

    z = p->obj.drawFlags;
    z |= 4;
    EvtObjSetDrawFlags(&p->obj, z);
    gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
    gBldAlpha = 16;
    p->effectTimer = 0;
    p->effectLevel = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaBlendUpUpdate);
    TaskPoolUpdate(&p->tasks);
    return 1;
}

u8 EventCharaBlendUpUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->effectTimer++;

    if (work->effectTimer % 2 == 0) {
        if (work->effectLevel <= 15) {
            work->effectLevel++;
        }
    }

    gBldAlpha = (work->effectLevel << 8) | 16;

    if (AdvanceEventCharaKeyframe(work)) {
        gBldCnt = 0;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaBlendDown(void* work, void* a) {
    EventCharaWork* p = work;
    u16 z;

    UpdateEventCharaMotion(p);
    PlayEventCharaAnimSounds(p);

    if (AdvanceEventCharaKeyframe(p)) {
        if (p->keyframes[p->keyframe].update != NULL) {
            SetTaskUpdate(a, p->keyframes[p->keyframe].update);
        }

        if (p->keyframes[p->keyframe].callback != NULL) {
            p->keyframes[p->keyframe].callback(p);
            p->callbackActive = 1;
        } else {
            p->callbackActive = 0;
        }
    }

    z = p->obj.drawFlags;
    z |= 4;
    EvtObjSetDrawFlags(&p->obj, z);
    gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
    gBldAlpha = 0x1010;
    p->effectTimer = 0;
    p->effectLevel = 16;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaBlendDownUpdate);
    TaskPoolUpdate(&p->tasks);
    return 1;
}

u8 EventCharaBlendDownUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->effectTimer++;

    if (work->effectTimer % 2 == 0) {
        if (work->effectLevel != 0) {
            work->effectLevel--;
        }
    }

    gBldAlpha = (work->effectLevel << 8) | 16;

    if (AdvanceEventCharaKeyframe(work)) {
        gBldCnt = 0;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaCircleSlow(EventCharaWork* work, void* a) {
    work->unk_18C = 0;
    work->unk_198 = 0;
    work->startX = work->obj.x;
    work->startZ = work->obj.z;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaCircleSlowUpdate);
    return 1;
}

u8 EventCharaCircleSlowUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->obj.x += gSineTable[(u8)work->unk_18C] * (work->unk_198 >> 8);
    work->obj.y += -gSineTable[(u8)work->unk_18C + 64] * (work->unk_198 >> 9);
    work->unk_18C += 2;

    if (work->unk_198 < 0x200) {
        work->unk_198 += 25;
    }

    if (AdvanceEventCharaKeyframe(work)) {
        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaCircleFast(EventCharaWork* work, void* a) {
    work->unk_18C = 0;
    work->unk_198 = 0;
    work->startX = work->obj.x;
    work->startZ = work->obj.z;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaCircleFastUpdate);
    return 1;
}

u8 EventCharaCircleFastUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->obj.x += gSineTable[(u8)work->unk_18C] * (work->unk_198 >> 8);
    work->obj.y += -gSineTable[(u8)work->unk_18C + 64] * (work->unk_198 >> 9);
    work->unk_18C += 6;

    if (work->unk_198 < 0x200) {
        work->unk_198 += 25;
    }

    if (AdvanceEventCharaKeyframe(work)) {
        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaJitter(EventCharaWork* work, void* a) {
    work->unk_18C = 1;
    work->unk_198 = 0;
    work->startX = work->obj.x;
    work->startZ = work->obj.z;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaJitterUpdate);
    return 1;
}

u8 EventCharaJitterUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);

    if (work->unk_198 == 2) {
        work->obj.z += work->unk_18C << 10;
        work->unk_18C = -work->unk_18C;
        work->unk_198 = 0;
    } else {
        work->unk_198++;
    }

    if (AdvanceEventCharaKeyframe(work)) {
        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void ApplyEventCharaDrawFlags(EventCharaWork* work) {
    u16 z;

    z = work->obj.drawFlags;

    if (work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_HFLIP) {
        if (work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_PRIORITY_1) {
            z |= SPRITE_PRIORITY(1) | SPRITE_FLAG_HFLIP;
            z &= ~SPRITE_PRIORITY(2);
            EvtObjSetDrawFlags(&work->obj, z);
        } else {
            z |= SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
            z &= ~SPRITE_PRIORITY(1);
            EvtObjSetDrawFlags(&work->obj, z);

            if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_PRIORITY_0) == 0) {
                z |= SPRITE_PRIORITY(2) | SPRITE_FLAG_HFLIP;
                EvtObjSetDrawFlags(&work->obj, z);
            } else {
                z |= SPRITE_FLAG_HFLIP;
                z &= ~SPRITE_PRIORITY(2);
                EvtObjSetDrawFlags(&work->obj, z);
            }
        }
    } else {
        if (work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_PRIORITY_1) {
            z |= SPRITE_PRIORITY(1);
            z &= ~SPRITE_PRIORITY(2);
            z &= ~SPRITE_FLAG_HFLIP;
            EvtObjSetDrawFlags(&work->obj, z);
        } else {
            z |= SPRITE_PRIORITY(2);
            z &= ~SPRITE_PRIORITY(1);
            z &= ~SPRITE_FLAG_HFLIP;
            EvtObjSetDrawFlags(&work->obj, z);

            if ((work->keyframes[work->keyframe].flags & CHARA_KEYFRAME_FLAG_PRIORITY_0) == 0) {
                z |= SPRITE_PRIORITY(2);
                z &= ~SPRITE_FLAG_HFLIP;
                EvtObjSetDrawFlags(&work->obj, z);
            } else {
                z &= ~SPRITE_PRIORITY(2);
                z &= ~SPRITE_FLAG_HFLIP;
                EvtObjSetDrawFlags(&work->obj, z);
            }
        }
    }
}

u8 EventCharaToggleAnim(EventCharaWork* work, void* a) {
    work->effectTimer = 0;
    work->effectLevel = 0;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaToggleAnimUpdate);
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaToggleAnimUpdate(EventCharaWork* work, void* a) {
    u16 buf[2];

    memcpy(buf, sEventCharaToggleAnims, 4);
    EvtObjSetAnim(&work->obj, buf[work->effectLevel]);
    work->effectTimer++;

    if (work->effectTimer == 12) {
        work->effectTimer = 0;
        work->effectLevel ^= 1;
    }

    if (AdvanceEventCharaKeyframe(work)) {
        if (work->tiles != NULL) {
            ReleaseObjTiles(work->tiles);
        }

        if (work->palette != NULL) {
            ReleaseObjPalette(work->palette);
        }

        work->tiles = NULL;
        work->palette = NULL;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaFadeToBlack(void* work, void* a) {
    EventCharaWork* p = work;
    u16 z;

    UpdateEventCharaMotion(p);
    PlayEventCharaAnimSounds(p);

    if (AdvanceEventCharaKeyframe(p)) {
        if (p->keyframes[p->keyframe].update != NULL) {
            SetTaskUpdate(a, p->keyframes[p->keyframe].update);
        }

        if (p->keyframes[p->keyframe].callback != NULL) {
            p->keyframes[p->keyframe].callback(p);
            p->callbackActive = 1;
        } else {
            p->callbackActive = 0;
        }
    }

    z = p->obj.drawFlags;
    z |= 4;
    EvtObjSetDrawFlags(&p->obj, z);
    gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
    gBldAlpha = 16;
    p->effectTimer = 0;
    p->effectLevel = 16;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaFadeToBlackUpdate);
    TaskPoolUpdate(&p->tasks);
    return 1;
}

u8 EventCharaFadeToBlackUpdate(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->effectTimer++;

    if (work->effectTimer % 2 == 0) {
        if (work->effectLevel != 0) {
            work->effectLevel--;
        }
    }

    gBldAlpha = work->effectLevel;

    if (AdvanceEventCharaKeyframe(work)) {
        gBldCnt = 0;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 EventCharaBlendDown2(void* work, void* a) {
    EventCharaWork* p = work;
    u16 z;

    UpdateEventCharaMotion(p);
    PlayEventCharaAnimSounds(p);

    if (AdvanceEventCharaKeyframe(p)) {
        if (p->keyframes[p->keyframe].update != NULL) {
            SetTaskUpdate(a, p->keyframes[p->keyframe].update);
        }

        if (p->keyframes[p->keyframe].callback != NULL) {
            p->keyframes[p->keyframe].callback(p);
            p->callbackActive = 1;
        } else {
            p->callbackActive = 0;
        }
    }

    z = p->obj.drawFlags;
    z |= 4;
    EvtObjSetDrawFlags(&p->obj, z);
    gBldCnt = (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3);
    gBldAlpha = 0;
    p->effectTimer = 0;
    p->effectLevel = 16;
    SetTaskUpdate(a, (TaskUpdateFunc)EventCharaBlendDown2Update);
    TaskPoolUpdate(&p->tasks);
    return 1;
}

u8 EventCharaBlendDown2Update(EventCharaWork* work, void* a) {
    UpdateEventCharaMotion(work);
    PlayEventCharaAnimSounds(work);
    work->effectTimer++;

    if (work->effectTimer % 2 == 0) {
        if (work->effectLevel != 0) {
            work->effectLevel--;
        }
    }

    gBldAlpha = (16 - work->effectLevel) | (work->effectLevel << 8);
    gBldAlpha = (work->effectLevel << 8) | 16;

    if (AdvanceEventCharaKeyframe(work)) {
        gBldCnt = 0;

        if (work->keyframes[work->keyframe].update != NULL) {
            SetTaskUpdate(a, work->keyframes[work->keyframe].update);
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)event_chara_1);
        }

        if (work->keyframes[work->keyframe].callback != NULL) {
            work->keyframes[work->keyframe].callback(work);
            work->callbackActive = 1;
        } else {
            work->callbackActive = 0;
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void ReadEventCharaDpadAngle(EventCharaWork* work) {
    u16 keys = GetKeysHeld();

    switch (keys & DPAD_ANY) {
    case DPAD_UP:
        if (GetKeyReleaseTime(DPAD_LEFT) <= 4) {
            work->angle = 211;
        } else if (GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
            work->angle = 45;
        } else {
            work->angle = 0;
        }

        break;
    case DPAD_DOWN:
        if (GetKeyReleaseTime(DPAD_LEFT) <= 4) {
            work->angle = 173;
        } else if (GetKeyReleaseTime(DPAD_RIGHT) <= 4) {
            work->angle = 83;
        } else {
            work->angle = 128;
        }

        break;
    case DPAD_LEFT:
        if (GetKeyReleaseTime(DPAD_UP) <= 4) {
            work->angle = 211;
        } else if (GetKeyReleaseTime(DPAD_DOWN) <= 4) {
            work->angle = 173;
        } else {
            work->angle = 192;
        }

        break;
    case DPAD_RIGHT:
        if (GetKeyReleaseTime(DPAD_UP) <= 4) {
            work->angle = 45;
        } else if (GetKeyReleaseTime(DPAD_DOWN) <= 4) {
            work->angle = 83;
        } else {
            work->angle = 64;
        }

        break;
    case (DPAD_RIGHT | DPAD_UP):
        work->angle = 45;
        break;
    case (DPAD_LEFT | DPAD_UP):
        work->angle = 211;
        break;
    case (DPAD_RIGHT | DPAD_DOWN):
        work->angle = 83;
        break;
    case (DPAD_LEFT | DPAD_DOWN):
        work->angle = 173;
        break;
    }
}

void UpdateEventCharaAngle(EventCharaWork* work) {
    u8 old = work->angle;

    ReadEventCharaDpadAngle(work);

    if (old != work->angle) {
        if (abs((s8)GetAngleDiff(old, work->angle)) > 100) {
            work->speed = 0;
        } else {
            work->speed >>= 1;
        }
    }
}

void SetEventCharaMoveAnim(EventCharaWork* work, s32 a) {
    u16 f;

    f = work->obj.drawFlags;

    switch (work->angle) {
    case 0xD3:
        f &= 0xFFFE;
        break;
    case 0x2D:
    case 0x40:
    case 0x53:
        f |= 1;
        break;
    case 0x00:
    case 0x80:
    case 0xAD:
    case 0xC0:
        f &= 0xFFFE;
        break;
    }

    if (a != work->animId) {
        EvtObjSetAnim(&work->obj, a);
        work->animId = a;
    }

    EvtObjSetDrawFlags(&work->obj, f);
}

u8 UpdateEventCharaControl(EventCharaWork* work, void* a) {
    u16 keys;
    s32 v;

    keys = GetKeysHeld();
    ReadEventCharaDpadAngle(work);

    switch (work->angle) {
    case 0x00:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 5);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 10);
        }

        break;
    case 0x80:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 6);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 11);
        }

        break;
    case 0xC0:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 8);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 13);
        }

        break;
    case 0x40:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 8);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 13);
        }

        break;
    case 0xD3:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 9);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 14);
        }

        break;
    case 0x2D:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 9);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 14);
        }

        break;
    case 0xAD:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 7);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 12);
        }

        break;
    case 0x53:
        if ((keys & A_BUTTON) != 0) {
            work->moveMode = 1;
            SetEventCharaMoveAnim(work, 7);
        } else {
            work->moveMode = 2;
            SetEventCharaMoveAnim(work, 12);
        }

        break;
    }

    if ((keys & DPAD_ANY) != 0) {
        v = work->speed + 51;
        work->speed = v;

        switch (work->moveMode) {
        case 1:
            if (v > gEventCharaParams[work->arg.chara].slowSpeed) {
                work->speed = gEventCharaParams[work->arg.chara].slowSpeed;
            }

            break;
        case 2:
            if (v > gEventCharaParams[work->arg.chara].fastSpeed) {
                work->speed = gEventCharaParams[work->arg.chara].fastSpeed;
            }

            break;
        }
    } else {
        work->speed -= 102;

        if (work->speed < 0) {
            work->speed = 0;
        }

        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 0);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 1);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 3);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 3);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 2);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 2);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 4);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 4);
            break;
        }
    }

    if ((GetKeysPressed() & B_BUTTON) != 0) {
        work->jumpPhase = 0;
        work->waitTimer = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventCharaJump);
    }

    v = work->obj.x + (gSineTable[work->angle] * work->speed >> 8);
    work->obj.x = v;
    work->obj.y += work->speed * -gSineTable[work->angle + 64] >> 8;

    if (work->arg.chara == 0) {
        if (gBtlWork != NULL) {
            gBtlWork->actor->x = v - 0x7800;
            gBtlWork->actor->y = work->obj.y - 0x5000;
            gBtlWork->actor->z = 0;
        }
    }

    work->lastAngle = work->angle;
    work->lastMoveMode = work->moveMode;
    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 UpdateEventCharaJump(EventCharaWork* work, void* a) {
    u16 keys = GetKeysHeld();

    if ((keys & DPAD_ANY) != 0) {
        work->speed += 5;
    }

    switch (work->jumpPhase) {
    case 0:
        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 38);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 44);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 56);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 56);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 50);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 50);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 62);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 62);
            break;
        }

        work->obj.x += gSineTable[work->angle] * (work->speed >> 2) >> 8;
        work->obj.y += -gSineTable[work->angle + 64] * (work->speed >> 2) >> 8;

        if (work->waitTimer > 3) {
            work->jumpPhase = 1;
            work->unk_18C = -0x540;
            work->unk_198 = work->obj.z;
            work->waitTimer = 0;
        } else {
            work->waitTimer++;
        }

        break;
    case 1:
        UpdateEventCharaAngle(work);

        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 39);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 45);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 57);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 57);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 51);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 51);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 63);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 63);
            break;
        }

        work->obj.x += gSineTable[work->angle] * work->speed >> 8;
        work->obj.y += work->speed * -gSineTable[work->angle + 64] >> 8;
        work->unk_18C += 51;
        work->obj.z += work->unk_18C;

        if ((GetKeysHeld() & B_BUTTON) == 0) {
            work->unk_18C += 64;
        }

        if (work->unk_18C > -0x200) {
            work->jumpPhase = 2;
            work->waitTimer = 0;
        }

        break;
    case 2:
        UpdateEventCharaAngle(work);

        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 40);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 46);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 58);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 58);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 52);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 52);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 64);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 64);
            break;
        }

        work->obj.x += gSineTable[work->angle] * work->speed >> 8;
        work->obj.y += work->speed * -gSineTable[work->angle + 64] >> 8;
        work->unk_18C += 51;
        work->obj.z += work->unk_18C;

        if ((GetKeysHeld() & B_BUTTON) == 0) {
            work->unk_18C += 64;
        }

        if (work->unk_18C > 0) {
            work->jumpPhase = 3;
            work->waitTimer = 0;
        }

        break;
    case 3:
        UpdateEventCharaAngle(work);

        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 40);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 46);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 58);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 58);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 52);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 52);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 64);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 64);
            break;
        }

        work->obj.x += gSineTable[work->angle] * work->speed >> 8;
        work->obj.y += work->speed * -gSineTable[work->angle + 64] >> 8;
        work->obj.z += work->unk_18C;
        work->unk_18C += 51;

        if (work->unk_18C > 0x1FF) {
            work->jumpPhase = 4;
            work->waitTimer = 0;
        }

        break;
    case 4:
        UpdateEventCharaAngle(work);

        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 41);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 47);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 59);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 59);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 53);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 53);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 65);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 65);
            break;
        }

        work->obj.x += gSineTable[work->angle] * work->speed >> 8;
        work->obj.y += work->speed * -gSineTable[work->angle + 64] >> 8;
        work->obj.z += work->unk_18C;
        work->unk_18C += 51;

        if (work->obj.z > work->unk_198) {
            work->obj.z = work->unk_198;
            work->jumpPhase = 5;
            work->waitTimer = 0;
        }

        break;
    case 5:
        switch (work->angle) {
        case 0x00:
            SetEventCharaMoveAnim(work, 42);
            break;
        case 0x80:
            SetEventCharaMoveAnim(work, 48);
            break;
        case 0xC0:
            SetEventCharaMoveAnim(work, 60);
            break;
        case 0x40:
            SetEventCharaMoveAnim(work, 60);
            break;
        case 0xAD:
            SetEventCharaMoveAnim(work, 54);
            break;
        case 0x53:
            SetEventCharaMoveAnim(work, 54);
            break;
        case 0xD3:
            SetEventCharaMoveAnim(work, 66);
            break;
        case 0x2D:
            SetEventCharaMoveAnim(work, 66);
            break;
        }

        work->speed = 204 * work->speed >> 8;

        if ((GetKeysPressed() & B_BUTTON) != 0) {
            work->jumpPhase = 1;
            work->unk_18C = -0x540;
        } else if (work->waitTimer > 10) {
            work->lastAngle = 255;
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateEventCharaControl);
        } else {
            work->waitTimer++;
        }

        break;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}
#ifdef VERSION_EU
#define MSG_SOUND_ID_9E 0x9C
#define MSG_SOUND_ID_B1 0xAF
#else
#define MSG_SOUND_ID_9E 0x9E
#define MSG_SOUND_ID_B1 0xB1
#endif

s32 PlayEventCharaAnimSounds(EventCharaWork* work) {
    u16 x;
    u16 y;

    x = (work->obj.x >> 8) - (gEventState->x >> 8);
    y = (work->obj.y >> 8) + (work->obj.z >> 8) - (gEventState->y >> 8);

    switch (work->keyframes[work->keyframe].anim) {
    case 0x2EB:
    case 0x2F1:
    case 0x2F2:
        if (work->arg.eventId != MSG_SOUND_ID_9E) {
            if (work->obj.anim->timer == 0) {
                if (work->obj.anim->frame == 2) {
                    m4aSongNumStart(SONG_SND_958);
                    SetEventSoundPosition(SONG_SND_958, x, y);
                }

                if (work->obj.anim->frame == 6) {
                    m4aSongNumStart(SONG_SND_959);
                    SetEventSoundPosition(SONG_SND_959, x, y);
                }
            }
        }

        break;
    case 0x2E6:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN2_STONEL);
                SetEventSoundPosition(SONG_EV_MAN2_STONEL, x, y);
            }

            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN2_STONER);
                SetEventSoundPosition(SONG_EV_MAN2_STONER, x, y);
            }
        }

        break;
    case 0x375:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONEL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONER);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONER, x, y);
            }
        }

        break;
    case 0x398:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_SND_373);
                SetEventSoundPosition(SONG_SND_373, x, y);
            }
        }

        break;
    case 0x399:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_SND_374);
                SetEventSoundPosition(SONG_SND_374, x, y);
            }
        }

        break;
    case 0x5E:
        if (work->obj.anim->timer == 9) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_EV_EV01_01);
            }
        }

        break;
    case 0x1C2:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN2_STONEL);
                SetEventSoundPosition(SONG_EV_MAN2_STONEL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_MAN2_STONER);
                SetEventSoundPosition(SONG_EV_MAN2_STONER, x, y);
            }
        }

        break;
    case 0x1C0:
    case 0x1C1:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN2_STONEL);
                SetEventSoundPosition(SONG_EV_MAN2_STONEL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_MAN2_STONER);
                SetEventSoundPosition(SONG_EV_MAN2_STONER, x, y);
            }
        }

        break;
    case 0x34B:
    case 0x34C:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONEL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONER);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONER, x, y);
            }
        }

        break;
    case 0x2B2:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONEL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONER);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONER, x, y);
            }
        }

        break;
    case 0x204:
    case 0x206:
    case 0x207:
    case 0x208:
    case 0x209:
    case 0x20A:
    case 0x20B:
    case 0x2C7:
    case 0x2C8:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                if ((u16)(work->arg.eventId - MSG_SOUND_ID_B1) <= 1) {
                    m4aSongNumStart(SONG_EV_SR_DIRTL);
                    SetEventSoundPosition(SONG_EV_SR_DIRTL, x, y);
                } else {
                    m4aSongNumStart(SONG_EV_MAN_RMARBLEL);
                    SetEventSoundPosition(SONG_EV_MAN_RMARBLEL, x, y);
                }
            }

            if (work->obj.anim->frame == 7) {
                if ((u16)(work->arg.eventId - MSG_SOUND_ID_B1) <= 1) {
                    m4aSongNumStart(SONG_EV_SR_DIRTR);
                    SetEventSoundPosition(SONG_EV_SR_DIRTR, x, y);
                } else {
                    m4aSongNumStart(SONG_EV_MAN_RMARBLER);
                    SetEventSoundPosition(SONG_EV_MAN_RMARBLER, x, y);
                }
            }
        }

        break;
    case 0x2C5:
    case 0x2C6:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                if ((u16)(work->arg.eventId - MSG_SOUND_ID_B1) <= 1) {
                    m4aSongNumStart(SONG_EV_SR_DIRTL);
                    SetEventSoundPosition(SONG_EV_SR_DIRTL, x, y);
                } else {
                    m4aSongNumStart(SONG_EV_MAN_RMARBLEL);
                    SetEventSoundPosition(SONG_EV_MAN_RMARBLEL, x, y);
                }
            }

            if (work->obj.anim->frame == 5) {
                if ((u16)(work->arg.eventId - MSG_SOUND_ID_B1) <= 1) {
                    m4aSongNumStart(SONG_EV_SR_DIRTR);
                    SetEventSoundPosition(SONG_EV_SR_DIRTR, x, y);
                } else {
                    m4aSongNumStart(SONG_EV_MAN_RMARBLER);
                    SetEventSoundPosition(SONG_EV_MAN_RMARBLER, x, y);
                }
            }
        }

        break;
    case 0x371:
    case 0x372:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_EV_WOMAN_STONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 7) {
                m4aSongNumStart(SONG_EV_WOMAN_STONER);
                SetEventSoundPosition(SONG_EV_WOMAN_STONER, x, y);
            }
        }

        break;
    case 0x1EE:
    case 0x1F6:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN_STONEL);
                SetEventSoundPosition(SONG_EV_MAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_MAN_STONER);
                SetEventSoundPosition(SONG_EV_MAN_STONER, x, y);
            }
        }

        break;
    case 0x345:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x344:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x341:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 9) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x30C:
    case 0x30D:
    case 0x30E:
    case 0x30F:
    case 0x310:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 9) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x275:
    case 0x276:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_WOMAN_DIRT_L);
                SetEventSoundPosition(SONG_EV_WOMAN_DIRT_L, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_WOMAN_DIRT_R);
                SetEventSoundPosition(SONG_EV_WOMAN_DIRT_R, x, y);
            }
        }

        break;
    case 0x277:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_EV_WOMAN_DIRT_L);
                SetEventSoundPosition(SONG_EV_WOMAN_DIRT_L, x, y);
            }

            if (work->obj.anim->frame == 7) {
                m4aSongNumStart(SONG_EV_WOMAN_DIRT_R);
                SetEventSoundPosition(SONG_EV_WOMAN_DIRT_R, x, y);
            }
        }

        break;
    case 0x2A5:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_EV_MAN2_DIRTL);
                SetEventSoundPosition(SONG_EV_MAN2_DIRTL, x, y);
            }

            if (work->obj.anim->frame == 7) {
                m4aSongNumStart(SONG_EV_MAN2_DIRTR);
                SetEventSoundPosition(SONG_EV_MAN2_DIRTR, x, y);
            }
        }

        break;
    case 0x2A8:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN_DIRTL);
                SetEventSoundPosition(SONG_EV_MAN_DIRTL, x, y);
            }

            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN_DIRTR);
                SetEventSoundPosition(SONG_EV_MAN_DIRTR, x, y);
            }
        }

        break;
    case 0x271:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN_STONEL);
                SetEventSoundPosition(SONG_EV_MAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_MAN_STONER);
                SetEventSoundPosition(SONG_EV_MAN_STONER, x, y);
            }
        }

        break;
    case 0x241:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN_MARBLEL);
                SetEventSoundPosition(SONG_EV_MAN_MARBLEL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_MAN_MARBLER);
                SetEventSoundPosition(SONG_EV_MAN_MARBLER, x, y);
            }
        }

        break;
    case 0x17A:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_STONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_WOMAN_STONER);
                SetEventSoundPosition(SONG_EV_WOMAN_STONER, x, y);
            }
        }

        break;
    case 0x178:
    case 0x179:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_STONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_WOMAN_STONER);
                SetEventSoundPosition(SONG_EV_WOMAN_STONER, x, y);
            }
        }

        break;
    case 0x19C:
    case 0x19D:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONEL, x, y);
            }

            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONER);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONER, x, y);
            }
        }

        break;
    case 0x14A:
    case 0x14B:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_WOMAN2_DIRTL);
                SetEventSoundPosition(SONG_EV_WOMAN2_DIRTL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_WOMAN2_DIRTR);
                SetEventSoundPosition(SONG_EV_WOMAN2_DIRTR, x, y);
            }
        }

        break;
    case 0x157:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_MAN_WOODL);
                SetEventSoundPosition(SONG_EV_MAN_WOODL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_MAN_WOODR);
                SetEventSoundPosition(SONG_EV_MAN_WOODR, x, y);
            }
        }

        break;
    case 0x23E:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN_RMARBLEL);
                SetEventSoundPosition(SONG_EV_MAN_RMARBLEL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_MAN_RMARBLER);
                SetEventSoundPosition(SONG_EV_MAN_RMARBLER, x, y);
            }
        }

        break;
    case 0x16C:
    case 0x16E:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_MAN_DIRTL);
                SetEventSoundPosition(SONG_EV_MAN_DIRTL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_MAN_DIRTR);
                SetEventSoundPosition(SONG_EV_MAN_DIRTR, x, y);
            }
        }

        break;
    case 0x122:
    case 0x123:
    case 0x128:
    case 0x129:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN_STONEL);
                SetEventSoundPosition(SONG_EV_MAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN_STONER);
                SetEventSoundPosition(SONG_EV_MAN_STONER, x, y);
            }
        }

        break;
    case 0xDF:
    case 0xE0:
    case 0xE1:
    case 0xE2:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                if (work->arg.eventId == 0x61) {
                    m4aSongNumStart(SONG_EV_WOMAN_DIRT_L);
                    SetEventSoundPosition(SONG_EV_WOMAN_DIRT_L, x, y);
                } else {
                    m4aSongNumStart(SONG_EV_MAN_RMARBLEL);
                    SetEventSoundPosition(SONG_EV_MAN_RMARBLEL, x, y);
                }
            }

            if (work->obj.anim->frame == 5) {
                if (work->arg.eventId == 0x61) {
                    m4aSongNumStart(SONG_EV_WOMAN_DIRT_R);
                    SetEventSoundPosition(SONG_EV_WOMAN_DIRT_R, x, y);
                } else {
                    m4aSongNumStart(SONG_EV_MAN_RMARBLER);
                    SetEventSoundPosition(SONG_EV_MAN_RMARBLER, x, y);
                }
            }
        }

        break;
    case 0xD6:
    case 0xD9:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_WOMAN_STONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_WOMAN_STONER);
                SetEventSoundPosition(SONG_EV_WOMAN_STONER, x, y);
            }
        }

        break;
    case 0xCA:
    case 0xCB:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_SND_954);
                SetEventSoundPosition(SONG_SND_954, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_SND_955);
                SetEventSoundPosition(SONG_SND_955, x, y);
            }
        }

        break;
    case 0xD3:
    case 0xD4:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_SND_956);
                SetEventSoundPosition(SONG_SND_956, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_SND_957);
                SetEventSoundPosition(SONG_SND_957, x, y);
            }
        }

        break;
    case 0x10A:
    case 0x10B:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x83:
    case 0x88:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_EV_EV01_03);
                SetEventSoundPosition(SONG_EV_EV01_03, x, y);
            }
        }

        break;
    case 0x12:
    case 0x13:
    case 0x66:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_EV01_01);
                SetEventSoundPosition(SONG_EV_EV01_01, x, y);
            }
        }

        break;
    case 0x5:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
        if (gEventBackgroundDefs[work->arg.eventId] != NULL) {
            if (work->obj.anim->timer == 0) {
                if (work->obj.anim->frame == 1) {
                    PlaySoraFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 1);
                }

                if (work->obj.anim->frame == 5) {
                    PlaySoraFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 0);
                }
            }
        }

        break;
    case 0x75:
    case 0x77:
    case 0x288:
    case 0x28C:
        if (gEventBackgroundDefs[work->arg.eventId] != NULL) {
            if (work->obj.anim->timer == 0) {
                if (work->obj.anim->frame == 2) {
                    PlayDonaldFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 1);
                }

                if (work->obj.anim->frame == 6) {
                    PlayDonaldFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 0);
                }
            }
        }

        break;
    case 0x78:
    case 0x79:
    case 0x289:
    case 0x28D:
        if (gEventBackgroundDefs[work->arg.eventId] != NULL) {
            if (work->obj.anim->timer == 0) {
                if (work->obj.anim->frame == 3) {
                    PlayDonaldFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 1);
                }

                if (work->obj.anim->frame == 7) {
                    PlayDonaldFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 0);
                }
            }
        }

        break;
    case 0x95:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x265:
    case 0x266:
    case 0x267:
        if (gEventBackgroundDefs[work->arg.eventId] != NULL) {
            if (work->obj.anim->timer == 0) {
                if (work->obj.anim->frame == 3) {
                    PlayGoofyFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 1);
                }

                if (work->obj.anim->frame == 7) {
                    PlayGoofyFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 0);
                }
            }
        }

        break;
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
        if (gEventBackgroundDefs[work->arg.eventId] != NULL) {
            if (work->obj.anim->timer == 0) {
                if (work->obj.anim->frame == 3) {
                    PlaySoraFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 1);
                }

                if (work->obj.anim->frame == 7) {
                    PlaySoraFootstep(work, gEventBackgroundDefs[work->arg.eventId]->groundType, 0);
                }
            }
        }

        break;
    case 0xB8:
    case 0xBA:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONEL, x, y);
            }

            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONER);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONER, x, y);
            }
        }

        break;
    case 0xBB:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_EV34_00);
                SetEventSoundPosition(SONG_EV_EV34_00, x, y);
            }
        }

        break;
    case 0xC1:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_CARDTHR);
                SetEventSoundPosition(SONG_EV_CARDTHR, x, y);
            }
        }

        break;
    case 0xE9:
    case 0xEA:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_SND_324);
                SetEventSoundPosition(SONG_SND_324, x, y);
            }
        }

        break;
    case 0xF2:
    case 0xF3:
    case 0xF4:
    case 0xF8:
    case 0xF9:
    case 0xFA:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_PI_FOOTR);
                SetEventSoundPosition(SONG_EV_PI_FOOTR, x, y);
            }

            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_EV_PI_FOOTL);
                SetEventSoundPosition(SONG_EV_PI_FOOTL, x, y);
            }
        }

        break;
    case 0xF5:
    case 0xF6:
    case 0xF7:
    case 0xFB:
    case 0xFC:
    case 0xFD:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_PI_FOOTL);
                SetEventSoundPosition(SONG_EV_PI_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_EV_PI_FOOTR);
                SetEventSoundPosition(SONG_EV_PI_FOOTR, x, y);
            }
        }

        break;
    case 0x280:
    case 0x281:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 7) {
                m4aSongNumStart(SONG_EV_WOMAN_STONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_STONER);
                SetEventSoundPosition(SONG_EV_WOMAN_STONER, x, y);
            }
        }

        break;
    case 0x18D:
    case 0x18E:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN_STONEL);
                SetEventSoundPosition(SONG_EV_MAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN_STONER);
                SetEventSoundPosition(SONG_EV_MAN_STONER, x, y);
            }
        }

        break;
    case 0x18F:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 4) {
                m4aSongNumStart(SONG_BTL_GMIC_OK);
            }
        }

        break;
    case 0x159:
    case 0x15D:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_WOMAN_STONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_STONER);
                SetEventSoundPosition(SONG_EV_WOMAN_STONER, x, y);
            }
        }

        break;
    case 0x15E:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_CARDTHR);
                SetEventSoundPosition(SONG_EV_CARDTHR, x, y);
            }
        }

        break;
    case 0x185:
    case 0x186:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN_STONEL);
                SetEventSoundPosition(SONG_EV_MAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN_STONER);
                SetEventSoundPosition(SONG_EV_MAN_STONER, x, y);
            }
        }

        break;
    case 0x187:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 7) {
                m4aSongNumStart(SONG_EV_MAN_STONEL);
                SetEventSoundPosition(SONG_EV_MAN_STONEL, x, y);
            }

            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_EV_MAN_STONER);
                SetEventSoundPosition(SONG_EV_MAN_STONER, x, y);
            }
        }

        break;
    case 0x2E7:
    case 0x2E8:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_GE_ENTRY);
                SetEventSoundPosition(SONG_EV_GE_ENTRY, x, y);
            }
        }

        break;
    case 0x2AE:
    case 0x2AF:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN2_STONEL);
                SetEventSoundPosition(SONG_EV_MAN2_STONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN2_STONER);
                SetEventSoundPosition(SONG_EV_MAN2_STONER, x, y);
            }
        }

        break;
    case 0x1C5:
    case 0x1C6:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_MAN2_STONEL);
                SetEventSoundPosition(SONG_EV_MAN2_STONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_MAN2_STONER);
                SetEventSoundPosition(SONG_EV_MAN2_STONER, x, y);
            }
        }

        break;
    case 0x27A:
    case 0x27D:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONEL);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONEL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_EV_WOMAN_RSTONER);
                SetEventSoundPosition(SONG_EV_WOMAN_RSTONER, x, y);
            }
        }

        break;
    case 0x10F:
    case 0x11B:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 6) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x110:
    case 0x11C:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 5) {
                m4aSongNumStart(SONG_SYS_POO_FOOTL);
                SetEventSoundPosition(SONG_SYS_POO_FOOTL, x, y);
            }

            if (work->obj.anim->frame == 2) {
                m4aSongNumStart(SONG_SYS_POO_FOOTR);
                SetEventSoundPosition(SONG_SYS_POO_FOOTR, x, y);
            }
        }

        break;
    case 0x118:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_EV_AL_LAND);
                SetEventSoundPosition(SONG_EV_AL_LAND, x, y);
            }
        }

        break;
    case 0x29E:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 3) {
                m4aSongNumStart(SONG_VO_GE_ATTACK02);
                SetEventSoundPosition(SONG_VO_GE_ATTACK02, x, y);
            }
        }

        break;
    case 0x2A2:
        if (work->obj.anim->timer == 0) {
            if (work->obj.anim->frame == 1) {
                m4aSongNumStart(SONG_EV_GE_FOOTUP);
            }
        }

        break;
    case 0x1DE:
        if (work->obj.anim->timer == 1) {
            if (work->obj.anim->frame == 0) {
                m4aSongNumStart(SONG_BTL_DARKDEAD);
                SetEventSoundPosition(SONG_BTL_DARKDEAD, x, y);
            }
        }

        break;
    }
}

void PlaySoraFootstep(EventCharaWork* work, u8 kind, u8 flag) {
    u16 x;
    u16 y;

    x = (work->obj.x >> 8) - (gEventState->x >> 8);
    y = (work->obj.y >> 8) + (work->obj.z >> 8) - (gEventState->y >> 8);

    switch (kind) {
    case 0:
        if (flag) {
            m4aSongNumStart(SONG_EV_SR_DIRTL);
            SetEventSoundPosition(SONG_EV_SR_DIRTL, x, y);
        } else {
            m4aSongNumStart(SONG_EV_SR_DIRTR);
            SetEventSoundPosition(SONG_EV_SR_DIRTR, x, y);
        }

        break;
    case 1:
        if (!flag) {
            m4aSongNumStart(SONG_EV_SR_STONER);
            SetEventSoundPosition(SONG_EV_SR_STONER, x, y);
        } else {
            m4aSongNumStart(SONG_EV_SR_STONEL);
            SetEventSoundPosition(SONG_EV_SR_STONEL, x, y);
        }

        break;
    case 2:
        if ((work->arg.eventId == 0x4B && gEventState->frame > 0x2BC) || (work->arg.eventId == 0x36 && gEventState->frame <= 0x4F)) {
            if (flag) {
                m4aSongNumStart(SONG_EV_SR_STONEL);
                SetEventSoundPosition(SONG_EV_SR_STONEL, x, y);
            } else {
                m4aSongNumStart(SONG_EV_SR_STONER);
                SetEventSoundPosition(SONG_EV_SR_STONER, x, y);
            }

            if (flag) {
                m4aSongNumStart(SONG_EV_SR_STONEL);
                SetEventSoundPosition(SONG_EV_SR_STONEL, x, y);
            } else {
                m4aSongNumStart(SONG_EV_SR_STONER);
                SetEventSoundPosition(SONG_EV_SR_STONER, x, y);
            }
        } else {
            if (flag) {
                m4aSongNumStart(SONG_EV_SR_MUDL);
                SetEventSoundPosition(SONG_EV_SR_MUDL, x, y);
            } else {
                m4aSongNumStart(SONG_EV_SR_MUDR);
                SetEventSoundPosition(SONG_EV_SR_MUDR, x, y);
            }
        }

        break;
    case 3:
        if (flag) {
            m4aSongNumStart(SONG_EV_SR_STONEL);
            SetEventSoundPosition(SONG_EV_SR_STONEL, x, y);
        } else {
            m4aSongNumStart(SONG_EV_SR_STONER);
            SetEventSoundPosition(SONG_EV_SR_STONER, x, y);
        }

        break;
    }
}

void PlayDonaldFootstep(EventCharaWork* work, u8 kind, u8 flag) {
    u16 x;
    u16 y;

    x = (work->obj.x >> 8) - (gEventState->x >> 8);
    y = (work->obj.y >> 8) + (work->obj.z >> 8) - (gEventState->y >> 8);

    switch (kind) {
    case 0:
        if (flag) {
            m4aSongNumStart(SONG_EV_DL_DIRTL);
            SetEventSoundPosition(SONG_EV_DL_DIRTL, x, y);
        } else {
            m4aSongNumStart(SONG_EV_DL_DIRTR);
            SetEventSoundPosition(SONG_EV_DL_DIRTR, x, y);
        }

        break;
    case 1:
        if (!flag) {
            m4aSongNumStart(SONG_EV_DL_STONE_R);
            SetEventSoundPosition(SONG_EV_DL_STONE_R, x, y);
        } else {
            m4aSongNumStart(SONG_EV_DL_STONE_L);
            SetEventSoundPosition(SONG_EV_DL_STONE_L, x, y);
        }

        break;
    case 2:
        if (work->arg.eventId == 0x4B && gEventState->frame > 0x2BC) {
            if (!flag) {
                m4aSongNumStart(SONG_EV_DL_STONE_R);
                SetEventSoundPosition(SONG_EV_DL_STONE_R, x, y);
            } else {
                m4aSongNumStart(SONG_EV_DL_STONE_L);
                SetEventSoundPosition(SONG_EV_DL_STONE_L, x, y);
            }
        } else {
            if (flag) {
                m4aSongNumStart(SONG_EV_DL_MUDL);
                SetEventSoundPosition(SONG_EV_DL_MUDL, x, y);
            } else {
                m4aSongNumStart(SONG_EV_DL_MUDR);
                SetEventSoundPosition(SONG_EV_DL_MUDR, x, y);
            }
        }

        break;
    case 3:
        if (flag) {
            m4aSongNumStart(SONG_EV_DL_STONE_L);
            SetEventSoundPosition(SONG_EV_DL_STONE_L, x, y);
        } else {
            m4aSongNumStart(SONG_EV_DL_STONE_R);
            SetEventSoundPosition(SONG_EV_DL_STONE_R, x, y);
        }

        break;
    }
}

void PlayGoofyFootstep(EventCharaWork* work, u8 kind, u8 flag) {
    u16 x;
    u16 y;

    x = (work->obj.x >> 8) - (gEventState->x >> 8);
    y = (work->obj.y >> 8) + (work->obj.z >> 8) - (gEventState->y >> 8);

    switch (kind) {
    case 0:
        if (flag) {
            m4aSongNumStart(SONG_EV_GF_DIRTL);
            SetEventSoundPosition(SONG_EV_GF_DIRTL, x, y);
        } else {
            m4aSongNumStart(SONG_EV_GF_DIRTR);
            SetEventSoundPosition(SONG_EV_GF_DIRTR, x, y);
        }

        break;
    case 1:
        if (!flag) {
            m4aSongNumStart(SONG_EV_GF_STONE_R);
            SetEventSoundPosition(SONG_EV_GF_STONE_R, x, y);
        } else {
            m4aSongNumStart(SONG_EV_GF_STONE_L);
            SetEventSoundPosition(SONG_EV_GF_STONE_L, x, y);
        }

        break;
    case 2:
        if (work->arg.eventId == 0x4B && gEventState->frame > 0x2BC) {
            if (!flag) {
                m4aSongNumStart(SONG_EV_GF_STONE_R);
                SetEventSoundPosition(SONG_EV_GF_STONE_R, x, y);
            } else {
                m4aSongNumStart(SONG_EV_GF_STONE_L);
                SetEventSoundPosition(SONG_EV_GF_STONE_L, x, y);
            }
        } else {
            if (flag) {
                m4aSongNumStart(SONG_EV_GF_MUDL);
                SetEventSoundPosition(SONG_EV_GF_MUDL, x, y);
            } else {
                m4aSongNumStart(SONG_EV_GF_MUDR);
                SetEventSoundPosition(SONG_EV_GF_MUDR, x, y);
            }
        }

        break;
    case 3:
        if (flag) {
            m4aSongNumStart(SONG_EV_GF_STONE_L);
            SetEventSoundPosition(SONG_EV_GF_STONE_L, x, y);
        } else {
            m4aSongNumStart(SONG_EV_GF_STONE_R);
            SetEventSoundPosition(SONG_EV_GF_STONE_R, x, y);
        }

        break;
    }
}

void SetupEventCharaShadow(EventCharaWork* work) {
    switch (work->arg.chara) {
    case 6:
    case 16:
    case 20:
    case 21:
    case 22:
    case 32:
        work->obj.flags |= EVTOBJ_FLAG_SHADOW_WIDE;
        break;
    case 37:
        CreateTinkerbellTask(work);
    case 8:
    case 10:
    case 33:
    case 38:
    case 39:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
        work->obj.flags |= EVTOBJ_FLAG_SHADOW_SMALL;
        break;
    case 0:
        break;
    }
}
#ifdef VERSION_EU
#define MSG_WIN_ID_A 0x84
#define MSG_WIN_ID_B 0x9A
#else
#define MSG_WIN_ID_A 0x86
#define MSG_WIN_ID_B 0x9C
#endif

static void msgwin_0(MsgWinWork* work, u8* arg) {
    const EventSequenceDef* t;

    work->eventId = arg[0];

    switch (work->eventId) {
    case 11:
        work->glyphPaletteIndex = InitMsgGlyphSpritesAltPalette3(0);
        break;
    case 3:
    case MSG_WIN_ID_A:
    case MSG_WIN_ID_B:
        work->glyphPaletteIndex = InitMsgGlyphSpritesAltPalette5(0);
        break;
    default:
        work->glyphPaletteIndex = InitMsgGlyphSprites(0);
        break;
    }

    if (gEventBackgroundDefs[work->eventId] != NULL) {
        work->bg = 0;
    } else {
        work->bg = 2;
    }

    LoadBgTiles(work->bg, gMsgwinTiles, 0x500);
    LoadBgPalette(work->bg, gMsgwinPalette, 32);
    LoadBgMap(work->bg, gUnk_08125E24, 0x800);
    SetBgPriority(work->bg, 0);
    t = gEventSequenceDefs[work->eventId];
    work->palette = NULL;
    work->steps = 0;
    work->shownChars = 0;
    work->charTimer = 0;
    work->charCount = 0;
    work->scriptIndex = 0;
    work->textLoaded = 0;
    work->started = 0;
    work->script = t->script;
    work->waitCreated = 0;
    work->scrollX = 0;
    work->nextText = NULL;
    gEventState->msgWinOpen = 0;
    gEventState->msgWaitActive = 0;
    gEventState->msgWinCentered = 0;
    TaskPoolInit(&work->tasks, 2);
    CreateMsgfaceTask(&work->tasks, &work->face, work->script->portraitId, work->script->expressionId, work->script->positionIndex);
}

static u8 msgwin_1(MsgWinWork* work, void* a) {
    const MessageScriptEntry* e;

    if (!work->textLoaded) {
        if (!gEventState->bgEffectActive) {
            MsgwinLoadEntry(work);
        }
    } else {
        MsgwinCheckStart(work);
    }

    if (work->started) {
        gEventState->msgWinPosition = work->position;

        if (gEventState->focusSpeaker) {
            if (gEventState->focusSteps != 0) {
                gEventState->focusSteps--;
            } else {
                e = &work->script[work->scriptIndex];

                if (e->portraitId == 62) {
                    void* pal;

                    pal = (void*)(BG_PLTT + 15 * PLTT_SIZE_4BPP);
                    LoadBgTiles(work->bg, gUnk_0950E2F8, 0x140);
                    LoadBgMap(work->bg, gUnk_096112B8, 0x800);
                    LoadPalette(gCard00Palette, pal, 32);

                    if ((e->flags & MSG_SCRIPT_FLAG_NO_FADE) != 0) {
                        FadeSetPaletteExcluded(15, 1);
                    }

                    gEventState->msgWinOpen = 1;

                    switch (e->positionIndex) {
                    case 0:
                    case 2:
                        SetBgScroll(work->bg, (u16)-0x28, 0);
                        break;
                    case 1:
                    case 3:
                        SetBgScroll(work->bg, (u16)-0x28, (u16)-0x60);
                        break;
                    }

                    if (work->palette == NULL) {
                        work->palette = LoadObjPalette(gUnk_09614718, 32);

                        if ((e->flags & MSG_SCRIPT_FLAG_NO_FADE) != 0) {
                            FadeSetPaletteExcluded(work->palette->index + 16, 1);
                        }
                    }

                    RequestMsgfaceSlideIn(&work->face);
                    SetTaskUpdate(a, (TaskUpdateFunc)MsgwinOpenUpdate);
                    gEventState->msgWinCentered = 1;
                } else {
                    LoadBgTiles(work->bg, gMsgwinTiles, 0x500);
                    LoadBgPalette(work->bg, gMsgwinPalette, 32);
                    SetBgMapBlocks(work->bg, gMsgwinMapBlocks[work->position], 2, 1);
                    RedrawBgMapAt(work->bg, work->scrollX, 0);
                    SetTaskUpdate(a, (TaskUpdateFunc)MsgwinOpenUpdate);
                    RequestMsgfaceSlideIn(&work->face);
                    gEventState->msgWinOpen = 1;

                    if (work->palette != NULL) {
                        ReleaseObjPalette(work->palette);
                        work->palette = NULL;
                    }

                    gEventState->msgWinCentered = 0;
                }
            }
        } else {
        e = &work->script[work->scriptIndex];

        if (e->portraitId == 62) {
            void* pal;

            pal = (void*)(BG_PLTT + 15 * PLTT_SIZE_4BPP);
            LoadBgTiles(work->bg, gUnk_0950E2F8, 0x140);
            LoadBgMap(work->bg, gUnk_096112B8, 0x800);
            LoadPalette(gCard00Palette, pal, 32);

            if ((e->flags & MSG_SCRIPT_FLAG_NO_FADE) != 0) {
                FadeSetPaletteExcluded(15, 1);
            }

            gEventState->msgWinOpen = 1;

            switch (e->positionIndex) {
            case 0:
            case 2:
                SetBgScroll(work->bg, (u16)-0x18, 0);
                break;
            case 1:
            case 3:
                SetBgScroll(work->bg, (u16)-0x18, (u16)-0x60);
                break;
            }

            if (work->palette == NULL) {
                work->palette = LoadObjPalette(gUnk_09614718, 32);

                if ((e->flags & MSG_SCRIPT_FLAG_NO_FADE) != 0) {
                FadeSetPaletteExcluded(work->palette->index + 16, 1);
                }
            }

            RequestMsgfaceSlideIn(&work->face);
            SetTaskUpdate(a, (TaskUpdateFunc)MsgwinOpenUpdate);
            gEventState->msgWinCentered = 1;
        } else {
            LoadBgTiles(work->bg, gMsgwinTiles, 0x500);
            LoadBgPalette(work->bg, gMsgwinPalette, 32);
            SetBgMapBlocks(work->bg, gMsgwinMapBlocks[work->position], 2, 1);
            RedrawBgMapAt(work->bg, work->scrollX, 0);
            SetTaskUpdate(a, (TaskUpdateFunc)MsgwinOpenUpdate);
            RequestMsgfaceSlideIn(&work->face);
            gEventState->msgWinOpen = 1;

            if (work->palette != NULL) {
                ReleaseObjPalette(work->palette);
                work->palette = NULL;
            }

            gEventState->msgWinCentered = 0;
        }
        }
    }

    if (gEventState->ending == 1) {
        FadeSetPaletteExcluded(work->glyphPaletteIndex + 16, 0);
        FadeSetPaletteExcluded(14, 0);
    } else {
        FadeSetPaletteExcluded(work->glyphPaletteIndex + 16, 1);
        FadeSetPaletteExcluded(14, 1);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 MsgwinContinueUpdate(MsgWinWork* work, void* a) {
    if (!work->textLoaded) {
        if (!gEventState->bgEffectActive) {
            MsgwinLoadEntry(work);
        }
    } else {
        MsgwinCheckStart(work);
    }

    if (work->started) {
        gEventState->msgWinPosition = work->position;

        if (gEventState->focusSpeaker) {
            if (gEventState->focusSteps != 0) {
                gEventState->focusSteps--;
            } else {
                SetTaskUpdate(a, (TaskUpdateFunc)MsgwinOpenUpdate);
                RequestMsgfaceSlideIn(&work->face);
                gEventState->msgWinOpen = 1;
            }
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)MsgwinOpenUpdate);
            RequestMsgfaceSlideIn(&work->face);
            gEventState->msgWinOpen = 1;
        }
    }

    if (gEventState->ending == 1) {
        FadeSetPaletteExcluded(work->glyphPaletteIndex + 16, 0);
        FadeSetPaletteExcluded(14, 0);
    } else {
        FadeSetPaletteExcluded(work->glyphPaletteIndex + 16, 1);
        FadeSetPaletteExcluded(14, 1);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

static void msgwin_2(MsgWinWork* work) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];

    if (e->portraitId != 62) {
        DrawMsgGlyphs(work->shownChars);
    } else {
        DrawMsgGlyphsWithPalette(work->shownChars, work->palette);
    }

    TaskPoolDraw(&work->tasks);
}

static void msgwin_3(MsgWinWork* work) {
    if (work->palette != NULL) {
        ReleaseObjPalette(work->palette);
    }

    FreeMsgGlyphSprites();
    TaskPoolDestroy(&work->tasks);
}

u8 MsgwinOpenUpdate(MsgWinWork* work, void* a) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];

    ApproachValue(&work->scrollX, gMsgwinOpenScrollX[work->position], work->steps);

    if (e->portraitId != 62) {
        ScrollBgMapTo(work->bg, work->scrollX, 0);
    }

    if (work->steps != 0) {
        work->steps--;
    } else {
        work->steps = 0;

        if ((e->flags & 0xF) == 0) {
            gEventState->talking = 1;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)MsgwinTypeUpdate);
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 MsgwinTypeUpdate(MsgWinWork* work, void* a) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];

    MsgwinTypeStep(work);

    if (e->portraitId == 62) {
        work->shownChars = work->charCount;
    } else if (GetKeysPressed() & A_BUTTON) {
        if (work->shownChars < work->charCount) {
            work->shownChars = work->charCount;
        }
    }

    if (work->waitCreated == 1 && !gEventState->msgWaitActive) {
        MsgLatinChar* text = work->nextText;

        if (text != NULL) {
            work->steps = 0;
            work->textLoaded = 0;
            work->started = 1;
            work->face.shown = 1;
            SetTaskUpdate(a, (TaskUpdateFunc)MsgwinContinueUpdate);
        } else {
            HideMsgGlyphs();

            if ((e->flags & MSG_SCRIPT_FLAG_END) == 0) {
                if (work->script[work->scriptIndex + 1].positionIndex != 4) {
                    work->steps = 8;
                    RequestMsgfaceSlideOut(&work->face);
                    SetTaskUpdate(a, (TaskUpdateFunc)MsgwinCloseUpdate);
                    gEventState->msgWinOpen = 0;
                    work->face.shown = 0;
                } else {
                    work->steps = 0;
                    work->textLoaded = 0;
                    work->started = 0;
                    work->scriptIndex++;
                    gEventState->flags &= ~EVENT_FLAG_PAUSED;
                    work->face.shown = 1;
                    SetTaskUpdate(a, (TaskUpdateFunc)msgwin_1);
                }
            } else {
                work->steps = 8;
                RequestMsgfaceSlideOut(&work->face);
                SetTaskUpdate(a, (TaskUpdateFunc)MsgwinCloseUpdate);
                gEventState->msgWinOpen = 0;
                work->face.shown = 0;
            }
        }

        work->waitCreated = 0;
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

u8 MsgwinCloseUpdate(MsgWinWork* work, void* a) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];

    ApproachValue(&work->scrollX, gMsgwinClosedScrollX[work->position], work->steps);

    if (e->portraitId != 62) {
        ScrollBgMapTo(work->bg, work->scrollX, 0);
    } else {
        DisableBg(work->bg);
    }

    if (work->steps != 0) {
        work->steps--;
    } else {
        work->steps = 0;

        if ((gEventState->flags & EVENT_FLAG_PLAYER_CONTROL) == 0) {
            gEventState->flags &= ~EVENT_FLAG_PAUSED;
        }

        gEventState->focusSpeaker = 0;

        if ((e->flags & MSG_SCRIPT_FLAG_END) == 0) {
            work->started = 0;
            work->textLoaded = 0;
            work->scriptIndex++;
            SetTaskUpdate(a, (TaskUpdateFunc)msgwin_1);
        }
    }

    TaskPoolUpdate(&work->tasks);
    return 1;
}

void MsgwinLoadEntry(MsgWinWork* work) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];
    s32 n;

    n = e->positionIndex;

    if (n != 4) {
        work->position = n;
        work->scrollX = gMsgwinClosedScrollX[n];
    }

    if ((e->flags & MSG_SCRIPT_FLAG_SILHOUETTE) != 0) {
        work->face.silhouette = 1;
    } else {
        work->face.silhouette = 0;
    }

    SetMsgfacePortrait(&work->face, e->portraitId, e->expressionId, work->position);

#ifdef VERSION_JP
    if (e->portraitId == 62) {
        work->charCount = LayoutMsgGlyphsSjis(0x2E00, gMsgwinTextY[work->position], (u8*)e->text);
    } else {
        work->charCount = LayoutMsgGlyphsSjis(gMsgwinTextX[work->position], gMsgwinTextY[work->position], (u8*)e->text);
    }
#else
    if (e->portraitId == 62) {
        if (work->nextText != NULL) {
            work->charCount = LayoutMsgGlyphsPage(0x2E00, gMsgwinTextY[work->position] - 0x200, work->nextText, &work->nextText);
        } else {
            work->charCount = LayoutMsgGlyphsPage(0x2E00, gMsgwinTextY[work->position] - 0x200, LANGSTR(e->text), &work->nextText);
        }
    } else {
        if (work->nextText != NULL) {
            work->charCount = LayoutMsgGlyphsPage(gMsgwinTextX[work->position], gMsgwinTextY[work->position] - 0x200, work->nextText, &work->nextText);
        } else {
            work->charCount = LayoutMsgGlyphsPage(gMsgwinTextX[work->position], gMsgwinTextY[work->position] - 0x200, LANGSTR(e->text), &work->nextText);
        }
    }
#endif

    work->charTimer = 0;
    work->shownChars = 0;
    work->textLoaded = 1;
}

void MsgwinTypeStep(MsgWinWork* work) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];
    u8 v;

    if (work->charTimer >= e->charDelay) {
        if (work->shownChars < work->charCount) {
            work->shownChars++;
            m4aSongNumStart(SONG_SYS_MESSAGE);
        } else {
            gEventState->talking = 0;

            if (!work->waitCreated) {
                if ((work->script[work->scriptIndex].flags & MSG_SCRIPT_FLAG_END) == 0) {
                    if ((work->script[work->scriptIndex].flags & MSG_SCRIPT_FLAG_YES_NO) == 0) {
                        TaskCreate(&work->tasks, &sTaskDescMsgwait, &work->script[work->scriptIndex + 1].positionIndex);
                    } else {
                        TaskCreate(&work->tasks, &gTaskDescMsgwaitYesno, &work->script[work->scriptIndex + 1].positionIndex);
                    }
                } else {
                    v = 0;

                    if ((work->script[work->scriptIndex].flags & MSG_SCRIPT_FLAG_YES_NO) == 0) {
                        TaskCreate(&work->tasks, &sTaskDescMsgwait, &v);
                    } else {
                        TaskCreate(&work->tasks, &gTaskDescMsgwaitYesno, &v);
                    }
                }

                work->waitCreated = 1;
            }
        }

        work->charTimer = 0;
    } else {
        work->charTimer++;
    }
}

void MsgwinCheckStart(MsgWinWork* work) {
    const MessageScriptEntry* e = &work->script[work->scriptIndex];

    if (gEventState->frame >= e->frame) {
        if (!work->started) {
            gEventState->flags |= EVENT_FLAG_PAUSED;
            work->started = 1;
            work->steps = 8;

            if ((e->flags & MSG_SCRIPT_FLAG_FOCUS_SPEAKER) != 0) {
                gEventState->focusSpeaker = 1;
                gEventState->speaker = e->portraitId;
                gEventState->focusSteps = 32;
            } else {
                gEventState->focusSpeaker = 0;
            }
        }
    }
}

void msgface_0(MsgFaceWork* work, MsgFaceControl* ctl) {
    const MsgFaceAnim* anim;
    u32 n;

    work->tiles = AllocObjTiles(0x12C0, NULL);
    work->palette = AllocObjPalette(32);
    work->face = ctl;
    work->steps = 0;
    work->x = gMsgfaceHiddenX[n = work->face->positionIndex];
    work->y = gMsgfaceY[n];
    work->scaleX = 0x100;
    work->arrived = 0;
    work->talking = 0;
    work->visible = 1;

    if (work->face->portraitId != 62) {
        anim = gMsgFaceAnims[work->face->portraitId];
    } else {
        anim = gMsgFaceAnims[0];
    }

    if (work->face->positionIndex <= 1) {
        work->flipX = 1;
    } else if (work->face->positionIndex <= 3) {
        work->flipX = 0;
    }

    if (work->face->portraitId != 62) {
        SetObjTileSource(work->tiles, anim[work->face->expressionId].tiles);
        UpdateAllocatedObjPalette(work->palette, anim[work->face->expressionId].palette);
        AnimInit(&work->anim, anim[work->face->expressionId].anims, anim[work->face->expressionId].gfxTable);
        AnimStart(&work->anim, 0, anim[work->face->expressionId].animFlags);
        work->gfx = AnimGetGfx(&work->anim);
    } else {
        SetObjTileSource(work->tiles, anim->tiles);
        UpdateAllocatedObjPalette(work->palette, anim->palette);
        AnimInit(&work->anim, anim->anims, anim->gfxTable);
        AnimStart(&work->anim, 0, anim->animFlags);
        work->gfx = AnimGetGfx(&work->anim);
    }
}

u8 msgface_1(MsgFaceWork* work, void* a) {
    const MsgFaceAnim* anim = NULL;
    u32 n;

    if (work->face->portraitId != 62) {
        anim = gMsgFaceAnims[work->face->portraitId];
        work->visible = 1;
    } else {
        work->visible = 0;
    }

    switch (work->face->command) {
    case 1:
        if (!work->face->shown) {
            work->x = gMsgfaceHiddenX[n = work->face->positionIndex];
            work->y = gMsgfaceY[n];
        }

        work->steps = 8;

        if (anim != NULL) {
            if (work->face->silhouette == 1) {
                UpdateAllocatedObjPalette(work->palette, gEventSilhouettePalette);
            } else {
                UpdateAllocatedObjPalette(work->palette, anim[work->face->expressionId].palette);
            }
        }

        SetTaskUpdate(a, (TaskUpdateFunc)MsgfaceSlideInUpdate);
        break;
    case 2:
        work->steps = 8;
        work->arrived = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)MsgfaceSlideOutUpdate);
        break;
    case 4:
        work->steps = 4;

        if (work->face->positionIndex <= 1) {
            work->scaleX = -255;
        } else if (work->face->positionIndex <= 3) {
            work->scaleX = 256;
        }

        work->y = gMsgfaceY[work->face->positionIndex];
        SetTaskUpdate(a, (TaskUpdateFunc)MsgfaceFlipOutUpdate);
        break;
    case 3:
        SetTaskUpdate(a, (TaskUpdateFunc)MsgfaceChangeUpdate);
        break;
    }

    if (gEventState->talking == 1) {
        if (!work->talking) {
            if (anim != NULL && anim[work->face->expressionId].animCount > 1) {
                AnimStart(&work->anim, 1, anim[work->face->expressionId].animFlags);
            }

            work->talking = 1;
        }
    } else {
        if (work->talking == 1) {
            if (anim != NULL) {
                AnimStart(&work->anim, 0, anim[work->face->expressionId].animFlags);
            }

            work->talking = 0;
        }
    }

    if (gEventState->ending == 1) {
        FadeSetPaletteExcluded(work->palette->index + 16, 0);
    } else {
        FadeSetPaletteExcluded(work->palette->index + 16, 1);
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

void msgface_2(MsgFaceWork* work) {
    ObjAffine* t;
    u8 v;

    if (work->visible) {
        t = AllocObjAffine(0, work->scaleX, 256, 0);

        if (t != NULL) {
            DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, t, 0, 50);
        } else {
            v = work->flipX;

            if (v) {
                DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, t, SPRITE_FLAG_HFLIP, 50);
            } else {
                DrawSprite(work->x >> 8, work->y >> 8, work->gfx, work->tiles, work->palette, NULL, v, 50);
            }
        }
    }
}

void msgface_3(MsgFaceWork* work) {
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

u8 MsgfaceSlideInUpdate(MsgFaceWork* work, void* a) {
    ApproachValue(&work->x, gMsgfaceShownX[work->face->positionIndex], work->steps);
    work->steps--;

    if (work->steps == 0) {
        work->face->command = 0;
        work->arrived = 1;
        SetTaskUpdate(a, (TaskUpdateFunc)msgface_1);
    }

    return 1;
}

u8 MsgfaceSlideOutUpdate(MsgFaceWork* work, void* a) {
    ApproachValue(&work->x, gMsgfaceHiddenX[work->face->positionIndex], work->steps);
    work->steps--;

    if (work->steps == 0) {
        work->face->command = 0;
        SetTaskUpdate(a, (TaskUpdateFunc)msgface_1);
    }

    return 1;
}

u8 MsgfaceChangeUpdate(MsgFaceWork* work, void* a) {
    const MsgFaceAnim* t;
    s32 n;

    t = NULL;

    if (work->face->portraitId != 62) {
        t = gMsgFaceAnims[work->face->portraitId];
        work->visible = 1;
    } else {
        work->visible = 0;
    }

    if (work->face->positionIndex <= 1) {
        work->flipX = 1;
    } else if (work->face->positionIndex <= 3) {
        work->flipX = 0;
    }

    if (t != NULL) {
        SetObjTileSource(work->tiles, t[work->face->expressionId].tiles);
        UpdateAllocatedObjPalette(work->palette, t[work->face->expressionId].palette);
        AnimInit(&work->anim, t[work->face->expressionId].anims, t[work->face->expressionId].gfxTable);
        AnimStart(&work->anim, 0, t[work->face->expressionId].animFlags);
        work->gfx = AnimGetGfx(&work->anim);
        work->arrived = 0;
        work->steps = 8;
        work->face->command = 0;
    }

    work->x = gMsgfaceHiddenX[n = work->face->positionIndex];
    work->y = gMsgfaceY[n];
    work->scaleX = 256;
    work->steps = 8;
    SetTaskUpdate(a, (TaskUpdateFunc)msgface_1);
    return 1;
}

u8 MsgfaceFlipOutUpdate(MsgFaceWork* work, void* a) {
    const MsgFaceAnim* t;

    if (work->scaleX < 0) {
        ApproachValue(&work->scaleX, -2, work->steps);
    } else {
        ApproachValue(&work->scaleX, 2, work->steps);
    }

    work->steps--;

    if (work->steps == 0) {
        t = NULL;

        if (work->face->portraitId != 62) {
            t = gMsgFaceAnims[work->face->portraitId];
        }

        if (work->face->positionIndex <= 1) {
            work->flipX = 1;
        } else if (work->face->positionIndex <= 3) {
            work->flipX = 0;
        }

        if (t != NULL) {
            SetObjTileSource(work->tiles, t[work->face->expressionId].tiles);
            UpdateAllocatedObjPalette(work->palette, t[work->face->expressionId].palette);
            AnimInit(&work->anim, t[work->face->expressionId].anims, t[work->face->expressionId].gfxTable);
            AnimStart(&work->anim, 0, t[work->face->expressionId].animFlags);
            work->gfx = AnimGetGfx(&work->anim);
            work->arrived = 0;
            work->steps = 8;
        }

        SetTaskUpdate(a, (TaskUpdateFunc)MsgfaceFlipInUpdate);
    }

    return 1;
}

u8 MsgfaceFlipInUpdate(MsgFaceWork* work, void* a) {
    if (work->scaleX < 0) {
        ApproachValue(&work->scaleX, -255, work->steps);
    } else {
        ApproachValue(&work->scaleX, 256, work->steps);
    }

    work->steps--;

    if (work->steps == 0) {
        work->arrived = 1;
        work->face->command = 0;
        work->scaleX = 256;
        SetTaskUpdate(a, (TaskUpdateFunc)msgface_1);
    }

    return 1;
}

void CreateMsgfaceTask(void* pool, MsgFaceControl* p, u8 a, u8 b, u8 c) {
    p->portraitId = a;
    p->expressionId = b;
    p->positionIndex = c;
    p->command = 0;
    p->silhouette = 0;
    TaskCreate(pool, &sTaskDescMsgface, p);
}

void SetMsgfacePortrait(MsgFaceControl* p, u8 a, u8 b, u8 c) {
    u8 v;

    if (p->portraitId != a) {
        v = 3;
    } else {
        if (p->expressionId == b && p->positionIndex == c) {
            return;
        }

        v = 4;
    }

    p->command = v;
    p->portraitId = a;
    p->expressionId = b;
    p->positionIndex = c;
}

void RequestMsgfaceSlideIn(MsgFaceControl* p) {
    p->command = 1;
}

void RequestMsgfaceSlideOut(MsgFaceControl* p) {
    p->command = 2;
}

void msgwait_0(MsgWaitWork* work, u8* arg) {
    work->nextPosition = arg[0];
    work->tiles = AllocObjTiles(64, NULL);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    LoadObjPaletteBank(work->palette->index, gBStatesPalette);
    FadeSetPaletteExcluded(work->palette->index + 16, 1);
    SetObjTileSource(work->tiles, gFEventTiles);
    AnimInit(&work->anim, gFEventAnims, gFEventFrames);
    AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
    work->timer = 0;
    gEventState->msgWaitActive = 1;
}

u8 msgwait_1(MsgWaitWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim);

    if (GetKeysPressed() & A_BUTTON) {
        AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);

        if (work->nextPosition == 4) {
            gEventState->msgWaitActive = 0;
            m4aSongNumStart(SONG_SYS_KETTEI);
            return 0;
        } else {
            SetTaskUpdate(a, (TaskUpdateFunc)UpdateMsgwaitClosing);
            m4aSongNumStart(SONG_SYS_KETTEI);
        }
    }

    return 1;
}

u8 UpdateMsgwaitClosing(MsgWaitWork* work) {
    u8 r;

    work->gfx = AnimUpdate(&work->anim);
    work->timer++;

    if (work->timer <= 15) {
        r = 1;
    } else {
        gEventState->msgWaitActive = 0;
        r = 0;
    }

    return r;
}

void msgwait_2(MsgWaitWork* work) {
    u8 v = gEventState->msgWinCentered;

    if (v) {
        DrawSprite(120, gMsgwaitIconPos[gEventState->msgWinPosition][1] >> 8, work->gfx,
                   work->tiles, work->palette, NULL, 0, 0);
    } else {
        DrawSprite(gMsgwaitIconPos[gEventState->msgWinPosition][0] >> 8,
                   gMsgwaitIconPos[gEventState->msgWinPosition][1] >> 8, work->gfx, work->tiles,
                   work->palette, NULL, 0, 0);
    }
}

void msgwait_3(MsgWaitWork* work) {
    FadeSetPaletteExcluded(work->palette->index + 16, 0);
    ReleaseObjTiles(work->tiles);
    ReleaseObjPalette(work->palette);
}

void msgwait_yesno_0(MsgWaitWork* work, u8* a) {
    work->nextPosition = *a;
    work->tiles = AllocObjTiles(64, NULL);
    work->palette = LoadObjPalette(gBStatesPalette, 32);
    LoadObjPaletteBank(work->palette->index, gBStatesPalette);
    FadeSetPaletteExcluded(work->palette->index + 16, 1);
    SetObjTileSource(work->tiles, gFEventTiles);
    AnimInit(&work->anim, gFEventAnims, gFEventFrames);
    AnimStart(&work->anim, 2, ANIM_FLAG_LOOP);
    work->timer = 0;
    work->tiles2 = AllocObjTiles(288, NULL);
    work->palette2 = LoadObjPalette(gUnk_09614418, 32);
    LoadObjPaletteBank(work->palette2->index, gUnk_09614418);
    SetObjTileSource(work->tiles2, gUnk_090A4664);
    AnimInit(&work->anim2, gUnk_09EEB03C, gUnk_09EEB008);
    AnimStart(&work->anim2, 2, ANIM_FLAG_LOOP);
    work->gfx2 = AnimGetGfx(&work->anim2);
    work->tiles3 = LoadObjTiles(gUnk_093F7C9C, 4032);
    work->palette3 = LoadObjPalette(gCard00Palette, 32);
    LoadObjPaletteBank(work->palette3->index, gCard00Palette);
    FadeSetPaletteExcluded(work->palette->index + 16, 1);
    InitTextSlots(work->textSlots, 10);
    InitTextSlots(work->textSlots2, 10);
    work->palette4 = LoadTextPalette(1);
#ifdef VERSION_EU
    work->textSlotCount = LoadTextSlots(GetLocalizedString(&gUnkEu_08890E1C), work->textSlots);
    work->textSlotCount2 = LoadTextSlots(GetLocalizedString(&gUnkEu_08890E44), work->textSlots2);
#else
    work->textSlotCount = LoadTextSlots(gUnk_08159E10, work->textSlots);
    work->textSlotCount2 = LoadTextSlots(gUnk_08159E18, work->textSlots2);
#endif
    work->x = 0x5800;
    work->cursor = 1;
    work->y = gMsgwaitYesnoCursorY[1];
    work->timer = 0;
    gEventState->msgWaitActive = 1;
    gEventState->askedYesNo = 1;
    gEventState->answerYes = 0;
    work->choiceShown = 0;
}

u8 UpdateMsgwaitYesnoChoice(MsgWaitWork* work, void* a) {
    switch (GetKeysPressed()) {
    case DPAD_UP:
        if (work->cursor != 0) {
            work->cursor--;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->timer = 1;
        break;
    case DPAD_DOWN:
        if (work->cursor == 0) {
            work->cursor++;
            m4aSongNumStart(SONG_SYS_CLICK);
        }

        work->timer = 1;
        break;
    case A_BUTTON:
    case START_BUTTON:
        if (work->cursor == 0) {
            gEventState->answerYes = 1;
        } else {
            gEventState->answerYes = 0;

            if (gEventState->eventId == 68) {
                gEventState->endRequest = 1;
                gEventState->skipHoldTime = 255;
            }
        }

        m4aSongNumStart(SONG_SYS_KETTEI);
        gEventState->msgWaitActive = 0;
        return 0;
    case B_BUTTON:
        gEventState->answerYes = 0;

        if (gEventState->eventId == 68) {
            gEventState->endRequest = 1;
            gEventState->skipHoldTime = 255;
        }

        m4aSongNumStart(SONG_SYS_KETTEI);
        gEventState->msgWaitActive = 0;
        return 0;
    }

    if (work->timer != 0) {
        ApproachValue(&work->y, gMsgwaitYesnoCursorY[work->cursor], work->timer);
        work->timer--;
    }

    work->gfx = AnimUpdate(&work->anim);
    return 1;
}

u8 msgwait_yesno_1(MsgWaitWork* work, void* a) {
    work->gfx = AnimUpdate(&work->anim);

    if (GetKeysPressed() & A_BUTTON) {
        AnimStart(&work->anim, 3, ANIM_FLAG_LOOP);
        work->choiceShown = 1;
        m4aSongNumStart(SONG_SYS_CANSEL);
        SetTaskUpdate(a, (TaskUpdateFunc)UpdateMsgwaitYesnoChoice);
    }

    return 1;
}

void msgwait_yesno_2(MsgWaitWork* work) {
    switch (work->choiceShown) {
    case 0:
        if (gEventState->msgWinCentered) {
            DrawSprite(120, gMsgwaitIconPos[gEventState->msgWinPosition][1] >> 8, work->gfx, work->tiles, work->palette, NULL, 0, 0);
        } else {
            DrawSprite(gMsgwaitIconPos[gEventState->msgWinPosition][0] >> 8, gMsgwaitIconPos[gEventState->msgWinPosition][1] >> 8, work->gfx, work->tiles, work->palette, NULL, 0, 0);
        }

        break;
    case 1:
        DrawSprite(120, 80, gUnk_09EF126C[1], work->tiles3, work->palette3, NULL, 0, 10);
        DrawSprite(work->x >> 8, work->y >> 8, work->gfx2, work->tiles2, work->palette2, NULL, SPRITE_FLAG_HFLIP, 9);
        DrawTextSlots((240 - GetTextSlotsWidth(work->textSlots, work->textSlotCount)) >> 1, 67, work->textSlots, work->palette4, 0, work->textSlotCount);
        DrawTextSlots((240 - GetTextSlotsWidth(work->textSlots2, work->textSlotCount2)) >> 1, 82, work->textSlots2, work->palette4, 0, work->textSlotCount2);
        break;
    }
}

void msgwait_yesno_3(MsgWaitWork* work) {
    ReleaseObjTiles(work->tiles2);
    ReleaseObjTiles(work->tiles3);
    ReleaseObjPalette(work->palette3);
    ReleaseObjPalette(work->palette2);
    ReleaseObjPalette(work->palette4);
    FreeTextSlots(work->textSlots, 10);
    FreeTextSlots(work->textSlots2, 10);
}

void HBlankIntrEventScanlineScroll() {
    vu16 v;

    v = REG_VCOUNT;
    v = (v + 1) % 228;

    if (v < 160) {
        if (gEventScanlineScroll->enabled == 1) {
            REG_BG2HOFS = gEventScanlineScroll->scrollX[v];
            REG_BG3HOFS = gEventScanlineScroll->scrollX[v];
        }
    }
}

void HBlankIntrEventBgWave() {
    gIntrCheck |= INTR_FLAG_HBLANK;
    HBlankIntrEventScanlineScroll();
}

void view_0(EventCameraWork* work, u8* arg) {
    const EventSequenceDef* t;
    EventBackgroundDef* u;
    const EventCameraKeyframe* q;
    EvtObj* obj;
    u8 n;

    gEventScanlineScroll = &work->scanline;
    work->wavePhase = 0;
    work->scanline.enabled = 0;
    work->eventId = arg[0];
    work->keyframe = 0;
    work->steps = 0;
    work->angle = 0;
    work->approachMode = 0;
    work->effectStarted = 0;
    t = gEventSequenceDefs[work->eventId];
    u = gEventBackgroundDefs[work->eventId];
    q = t->keyframes;
    work->keyframes = q;

    if (q->target != 255) {
        n = FindEventCameraTarget(work);
        obj = gEventState->charaObjs[n];
        work->targetX = obj->x;
        work->targetY = obj->y;
    } else {
        work->targetX = q->x;
        work->targetY = q->y;
    }

    gEventState->cameraX = work->targetX - 0x7800;
    gEventState->cameraY = work->targetY - 0x5000;
    gEventState->centerX = work->targetX;
    gEventState->centerY = work->targetY;
    gEventState->shakeX = 0;
    gEventState->shakeY = 0;

    if (u != NULL) {
        if (u->isAffine != 0) {
            SetBgAffine(2, 0, 0x100, 0x100, gEventState->centerX, gEventState->centerY);
        } else {
            if (work->eventId == 77) {
                ScrollBgMapTo(3, (gEventState->cameraX >> 8) + 8 + gEventState->shakeX, (gEventState->cameraY >> 8) + 40);
            } else {
                ScrollBgMapTo(3, (gEventState->cameraX >> 8) + gEventState->shakeX, gEventState->cameraY >> 8);
            }

            if (gEventState->hasBg2Map) {
                ScrollBgMapTo(2, (gEventState->cameraX >> 8) + gEventState->shakeX, gEventState->cameraY >> 8);
            }

            if (gEventState->hasBg1Map) {
                ScrollBgMapTo(1, (gEventState->cameraX >> 8) + gEventState->shakeX, gEventState->cameraY >> 8);
            }
        }
    }
}

void ClearEventObjPaletteExclusions() {
    u8 i;

    for (i = 0; i < 16; i++) {
        FadeSetPaletteExcluded(i + 16, 0);
    }
}

#ifdef VERSION_EU
#define MSG_VIEW_ID_B4 0xB2
#else
#define MSG_VIEW_ID_B4 0xB4
#endif

u8 view_1(EventCameraWork* work, Task* task) {
    EventBackgroundDef* u = gEventBackgroundDefs[work->eventId];
    const EventCameraKeyframe* e;
    EvtObj* q;
    u8 n;

    if (gEventState->bossChara == 98) {
        return 1;
    }

    if (gEventState->bossChara == 101) {
        return 1;
    }

    if (!gEventState->focusSpeaker) {
        e = &work->keyframes[work->keyframe];

        if (gEventState->frame >= (u16)e->frame && !(e->flags & CAMERA_KEYFRAME_FLAG_END)) {
            work->keyframe++;
            e = &work->keyframes[work->keyframe];
            work->effectStarted = 0;

            if (e->callback != NULL) {
                ((void (*)(EventCameraWork*))e->callback)(work);
            }

            switch (e->flags & CAMERA_KEYFRAME_MODE_MASK) {
            case CAMERA_MODE_FOLLOW:
                work->approachMode = 0;
                break;
            case CAMERA_MODE_APPROACH:
                work->approachMode = 1;
                work->steps = e->duration;
                break;
            }
        }

        if ((e->flags & CAMERA_KEYFRAME_MODE_MASK) != CAMERA_MODE_KEEP) {
            if (e->target == 255) {
                work->targetX = e->x;
                work->targetY = e->y;
            } else {
                n = FindEventCameraTarget(work);
                q = gEventState->charaObjs[n];
                work->targetX = q->x;
                work->targetY = q->y + q->z + e->yOffset;
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_FLASH) {
            if (!work->effectStarted) {
                ClearEventObjPaletteExclusions();
                FadeStartIn(FADE_MODE_ADD_WHITE, e->duration);

                if (!(e->flags & CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND)) {
                    m4aSongNumStart(SONG_EV_FLASH01);
                }

                gEventState->fadedOut = 0;
                work->effectStarted = 1;
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_FADE_OUT_WHITE) {
            if (!work->effectStarted) {
                ClearEventObjPaletteExclusions();
                FadeStartOut(FADE_MODE_WHITE, e->duration);
                gEventState->fadedOut = 1;
                work->effectStarted = 1;

                if (e->flags & CAMERA_KEYFRAME_FLAG_END) {
                    m4aSongNumStart(SONG_EV_WHITEOUT);
                }
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_FADE_OUT_BLACK) {
            if (!work->effectStarted) {
                ClearEventObjPaletteExclusions();
                FadeStartOut(FADE_MODE_BLACK, e->duration);
                gEventState->fadedOut = 1;
                work->effectStarted = 1;
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE) {
            if (!work->effectStarted) {
                FadeStartIn(FADE_MODE_WHITE, e->duration);
                gEventState->fadedOut = 0;
                work->effectStarted = 1;
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_FADE_IN_BLACK) {
            if (!work->effectStarted) {
                ClearEventObjPaletteExclusions();
                FadeStartIn(FADE_MODE_BLACK, e->duration);
                gEventState->fadedOut = 0;
                work->effectStarted = 1;
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_HALF_FLASH) {
            if (!work->effectStarted) {
                ClearEventObjPaletteExclusions();
                FadeFromAmount(FADE_MODE_ADD_WHITE, 16, e->duration);

                if (!(e->flags & CAMERA_KEYFRAME_FLAG_NO_FLASH_SOUND)) {
                    m4aSongNumStart(SONG_EV_FLASH00);
                }

                work->effectStarted = 1;
            }
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_WAVE_START) {
            StartBgWave(HBlankIntrEventBgWave);
            work->scanline.enabled = 1;
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_WAVE_STOP) {
            work->scanline.enabled = 0;
            ResetHBlankCallback();
            DisableHBlankIntr();
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_FADE_IN_WHITE_LINEAR) {
            if (!work->effectStarted) {
                FadeStartIn(FADE_MODE_WHITE_BLEND, e->duration);
            }

            work->effectStarted = 1;
        }

        if (e->flags & CAMERA_KEYFRAME_FLAG_SHAKE_SMALL) {
            gEventState->shakeX = GetRandom() % 4;
            gEventState->shakeY = GetRandom() % 4;
        } else if (e->flags & CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM) {
            gEventState->shakeX = GetRandom() % 8;
            gEventState->shakeY = GetRandom() % 8;
        } else if (e->flags & CAMERA_KEYFRAME_FLAG_SHAKE_LARGE) {
            gEventState->shakeX = GetRandom() % 16;
            gEventState->shakeY = GetRandom() % 16;
        } else if (e->flags & CAMERA_KEYFRAME_FLAG_SWAY) {
            gEventState->shakeX = 0;
            gEventState->shakeY = SIN(work->angle >> 3) >> 5;
            work->angle += 4;
        } else {
            gEventState->shakeX = 0;
            gEventState->shakeY = 0;
        }

        if (work->approachMode != 0) {
            EventCameraApproach(work);
        } else {
            EventCameraFollow(work);
        }

        if (u != NULL) {
            if (u->isAffine != 0) {
                SetBgAffine(2, 0, 0x100, 0x100, gEventState->centerX, gEventState->centerY);
            } else {
                if (work->eventId == 77) {
                    ScrollBgMapTo(3, (gEventState->x >> 8) + 8, (gEventState->y >> 8) + 40);
                } else {
                    ScrollBgMapTo(3, gEventState->x >> 8, gEventState->y >> 8);
                }

                if (gEventState->hasBg2Map) {
                    ScrollBgMapTo(2, gEventState->x >> 8, gEventState->y >> 8);
                }

                if (gEventState->hasBg1Map) {
                    ScrollBgMapTo(1, gEventState->x >> 8, gEventState->y >> 8);
                }
            }
        } else {
            switch (work->eventId) {
            case 77:
            case 78:
                gBtlWork->viewX = gEventState->x;
                gBtlWork->viewY = gEventState->y;
                gBtlWork->x = gEventState->x;
                gBtlWork->y = gEventState->y;
                gBtlWork->x2 = gEventState->x;
                gBtlWork->y2 = gEventState->y;
                ScrollBgMapTo(0, (gEventState->x >> 8) + 8, (gEventState->y >> 8) + 40);
                ScrollBgMapTo(1, gEventState->x >> 8, gEventState->y >> 8);
                break;
            case 105:
                gBtlWork->viewX = gEventState->x;
                gBtlWork->viewY = gEventState->y;
                gBtlWork->x = gEventState->x;
                gBtlWork->y = gEventState->y;
                gBtlWork->x2 = gEventState->x;
                gBtlWork->y2 = gEventState->y;
                ScrollBgMapTo(0, gEventState->x >> 8, gEventState->y >> 8);
                break;
            case MSG_VIEW_ID_B4:
                break;
            default:
                gBtlWork->viewX = gEventState->x;
                gBtlWork->viewY = gEventState->y;
                gBtlWork->x = gEventState->x;
                gBtlWork->y = gEventState->y;
                gBtlWork->x2 = gEventState->x;
                gBtlWork->y2 = gEventState->y;
                ScrollBgMapTo(0, gEventState->x >> 8, gEventState->y >> 8);
                ScrollBgMapTo(1, gEventState->x >> 8, gEventState->y >> 8);
                break;
            }
        }
    } else {
        n = FindEventCharaTrack(work, gEventState->speaker);
        work->targetX = gEventState->charaObjs[n]->x;

        switch (gEventState->msgWinPosition) {
        case 0:
        case 2:
            work->targetY = gEventState->charaObjs[n]->y + gEventState->charaObjs[n]->z + sSpeakerFocusYOffsets[n];
            break;
        case 1:
        case 3:
            work->targetY = gEventState->charaObjs[n]->y + gEventState->charaObjs[n]->z;
            break;
        }

        work->steps = gEventState->focusSteps;
        EventCameraApproach(work);

        if (u != NULL) {
            if (u->isAffine != 0) {
                SetBgAffine(2, 0, 0x100, 0x100, gEventState->centerX, gEventState->centerY);
            } else {
                if (work->eventId == 77) {
                    ScrollBgMapTo(3, (gEventState->x >> 8) + 8, (gEventState->y >> 8) + 40);
                } else {
                    ScrollBgMapTo(3, gEventState->x >> 8, gEventState->y >> 8);
                }

                if (gEventState->hasBg2Map) {
                    ScrollBgMapTo(2, gEventState->x >> 8, gEventState->y >> 8);
                }

                if (gEventState->hasBg1Map) {
                    ScrollBgMapTo(1, gEventState->x >> 8, gEventState->y >> 8);
                }
            }
        } else {
            gBtlWork->viewX = gEventState->x;
            gBtlWork->viewY = gEventState->y;
            ScrollBgMapTo(0, (gEventState->x >> 8) + 8, (gEventState->y >> 8) + 40);
            ScrollBgMapTo(1, gEventState->x >> 8, gEventState->y >> 8);
        }
    }

    if (gEventState->flags & EVENT_FLAG_PLAYER_CONTROL) {
        SetTaskUpdate(task, (TaskUpdateFunc)UpdateEventCameraFollowPlayer);
    }

    if (u != NULL && (u->flags & EVENT_BG_FLAG_POOH_MAP)) {
        func_080CA368(3, gEventState->cameraX >> 8, gEventState->cameraY >> 8);
    }

    UpdateEventScanlineWave(work);
    return 1;
}

void view_2() {
}

void view_3() {
}

void SetEventCameraCenter(EventCameraWork* work) {
    gEventState->centerX = work->targetX;
    gEventState->centerY = work->targetY;
}

void EventCameraFollow(EventCameraWork* work) {
    const EventCameraKeyframe* e;
    s32 x;
    s32 y;

    SetEventCameraCenter(work);
    x = gEventState->centerX - 0x7800;
    y = gEventState->centerY - 0x5000;
    e = &work->keyframes[work->keyframe];

    if (e->flags & (CAMERA_KEYFRAME_FLAG_SHAKE_MEDIUM | CAMERA_KEYFRAME_FLAG_SHAKE_LARGE | CAMERA_KEYFRAME_FLAG_SHAKE_SMALL)) {
        gEventState->cameraX = x;
        gEventState->cameraY = y;
    } else {
        gEventState->cameraX += (x - gEventState->cameraX) >> 3;
        gEventState->cameraY += (y - gEventState->cameraY) >> 3;
    }

    gEventState->x = gEventState->cameraX + (gEventState->shakeX << 8);
    gEventState->y = gEventState->cameraY + (gEventState->shakeY << 8);
}

void EventCameraSnap(EventCameraWork* work) {
    s32 x;
    s32 y;

    SetEventCameraCenter(work);
    x = gEventState->centerX - 0x7800;
    y = gEventState->centerY - 0x5000;
    gEventState->cameraX = x;
    gEventState->cameraY = y;
}

void EventCameraApproach(EventCameraWork* work) {
    s32 x;
    s32 y;

    SetEventCameraCenter(work);
    x = gEventState->centerX - 0x7800;
    y = gEventState->centerY - 0x5000;

    if (work->steps != 0) {
        ApproachValue(&gEventState->cameraX, x, work->steps);
        ApproachValue(&gEventState->cameraY, y, work->steps);
        work->steps--;
    } else {
        gEventState->cameraX = x;
        gEventState->cameraY = y;
    }

    gEventState->x = gEventState->cameraX + (gEventState->shakeX << 8);
    gEventState->y = gEventState->cameraY + (gEventState->shakeY << 8);
}

u8 FindEventCameraTarget(EventCameraWork* work) {
    const EventSequenceDef* t = gEventSequenceDefs[work->eventId];
    u8 n = t->charaCount;
    const EventCharaTrack* q = t->charaTracks;
    const EventCameraKeyframe* e = &work->keyframes[work->keyframe];
    u8 i;

    for (i = 0; i < n; i++) {
        if (e->target == q[i].chara) {
            return i;
        }
    }

    return 0xFF;
}

u8 FindEventCharaTrack(EventCameraWork* work, u8 v) {
    const EventSequenceDef* t = gEventSequenceDefs[work->eventId];
    u8 n = t->charaCount;
    const EventCharaTrack* q = t->charaTracks;
    u8 i;

    for (i = 0; i < n; i++) {
        if (v == q[i].chara) {
            return i;
        }
    }

    return 0xFF;
}

u8 UpdateEventCameraFollowPlayer(EventCameraWork* work) {
    EventBackgroundDef* t;
    EvtObj* q;
    u8 n;

    n = FindEventCharaTrack(work, 0);
    t = gEventBackgroundDefs[work->eventId];
    q = gEventState->charaObjs[n];
    work->targetX = q->x;
    work->targetY = q->y + q->z;

    if (t != NULL) {
        if (t->isAffine != 0) {
            EventCameraSnap(work);
            SetBgAffine(2, 0, 0x100, 0x100, gEventState->centerX, gEventState->centerY);
        } else {
            EventCameraFollow(work);

            if (work->eventId == 77) {
                ScrollBgMapTo(3, (gEventState->cameraX >> 8) + 8 + gEventState->shakeX, (gEventState->cameraY >> 8) + 40);
            } else {
                ScrollBgMapTo(3, (gEventState->cameraX >> 8) + gEventState->shakeX, gEventState->cameraY >> 8);
            }

            if (gEventState->hasBg2Map) {
                ScrollBgMapTo(2, gEventState->cameraX >> 8, gEventState->cameraY >> 8);
            }

            if (gEventState->hasBg1Map) {
                ScrollBgMapTo(1, gEventState->cameraX >> 8, gEventState->cameraY >> 8);
            }
        }
    } else {
        EventCameraFollow(work);
        gBtlWork->viewX = gEventState->cameraX;
        gBtlWork->viewY = gEventState->cameraY;
        ScrollBgMapTo(0, (gEventState->cameraX >> 8) + 8, (gEventState->cameraY >> 8) + 40);
        ScrollBgMapTo(1, gEventState->cameraX >> 8, gEventState->cameraY >> 8);
    }

    return 1;
}

void UpdateEventScanlineWave(EventCameraWork* work) {
    u8 i;
    s32 v;

    if (work->scanline.enabled == 1) {
        for (i = 0; i < 160; i++) {
            work->scanline.scrollX[i] = (gEventState->x >> 8) + (v = (u8)SIN((i + work->wavePhase) * 2)) / 32;
        }

        work->wavePhase++;
    }
}

TaskDesc gTaskDescMsgwaitYesno = {
    "msgwait_yesno",
    (TaskInitFunc)msgwait_yesno_0,
    (TaskUpdateFunc)msgwait_yesno_1,
    (TaskDrawFunc)msgwait_yesno_2,
    (TaskDestroyFunc)msgwait_yesno_3,
    sizeof(MsgWaitWork),
};

TaskDesc gTaskDescView = {
    "view",
    (TaskInitFunc)view_0,
    (TaskUpdateFunc)view_1,
    (TaskDrawFunc)view_2,
    (TaskDestroyFunc)view_3,
    sizeof(EventCameraWork),
};
