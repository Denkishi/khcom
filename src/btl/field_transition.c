#include "mode.h"
#include "obj_api.h"
#include "battle.h"
#include "sprites_evt.h"
#include "sprites_fld.h"
#include "sprites_riku.h"
#include "sprites_sora.h"
#include "gba/io_reg.h"
#include "malloc.h"
#include "anim.h"
#include "game_state.h"
#include "obj.h"
#include <stddef.h>
#include "system_state.h"
#include "types.h"

FieldTransitionWork* gFieldTransitionWork;

void FieldTransitionInit() {
    FieldTransitionWork* p;
    FieldTransitionWork** pp = &gFieldTransitionWork;
    p = EwramAlloc(sizeof(FieldTransitionWork));
    *pp = p;
    p->initialized = 0;
    p->tiles = NULL;
    p->palette = NULL;
    p->flipped = 0;
}

void FieldTransitionUpdate() {
    void* gfx;

    if (IsModeStarted()) {
        ReleaseObjTiles(gFieldTransitionWork->tiles);
        ReleaseObjPalette(gFieldTransitionWork->palette);
        EwramFree(gFieldTransitionWork);
        ModeClearTransitionCallback();
        return;
    }

    REG_DISPCNT |= DISPCNT_OBJ_ON;
    gSystemFlags |= SYSTEM_FLAG_DMA3_IMMEDIATE;

    if (gFieldTransitionWork->initialized == 0) {
        gFieldTransitionWork->tiles = AllocObjTiles(0xA00, NULL);

        if (gGameState.flags & GAME_FLAG_RIKU) {
            gFieldTransitionWork->palette = LoadObjPalette(gRikuPalette, 0x20);
            AnimInit(&gFieldTransitionWork->anim, NULL, NULL);

            switch (gGameState.fieldAngle) {
            case 0:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gUnk_09EDF514, gUnk_09EDF4F4);
                SetObjTileSource(gFieldTransitionWork->tiles, gUnk_08935BC2);
                break;
            case 45:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gRik1bl01Anims, gRik1bl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gRik1bl01Tiles);
                gFieldTransitionWork->flipped = 1;
                break;
            case 64:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gRik1ll01Anims, gRik1ll01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gRik1ll01Tiles);
                gFieldTransitionWork->flipped = 1;
                break;
            case 83:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gRik1fl01Anims, gRik1fl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gRik1fl01Tiles);
                gFieldTransitionWork->flipped = 1;
                break;
            case 128:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gUnk_09EDF4F0, gUnk_09EDF4D0);
                SetObjTileSource(gFieldTransitionWork->tiles, gUnk_0893416A);
                break;
            case 173:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gRik1fl01Anims, gRik1fl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gRik1fl01Tiles);
                break;
            case 192:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gRik1ll01Anims, gRik1ll01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gRik1ll01Tiles);
                break;
            default:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gRik1bl01Anims, gRik1bl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gRik1bl01Tiles);
                break;
            }
        } else {
            gFieldTransitionWork->palette = LoadObjPalette(gSoraPalette, 0x20);
            AnimInit(&gFieldTransitionWork->anim, NULL, NULL);

            switch (gGameState.fieldAngle) {
            case 0:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1bb01Anims, gSor1bb01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1bb01Tiles);
                break;
            case 45:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1bl01Anims, gSor1bl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1bl01Tiles);
                gFieldTransitionWork->flipped = 1;
                break;
            case 64:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1ll01Anims, gSor1ll01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1ll01Tiles);
                gFieldTransitionWork->flipped = 1;
                break;
            case 83:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1fl01Anims, gSor1fl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1fl01Tiles);
                gFieldTransitionWork->flipped = 1;
                break;
            case 128:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1ff01Anims, gSor1ff01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1ff01Tiles);
                break;
            case 173:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1fl01Anims, gSor1fl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1fl01Tiles);
                break;
            case 192:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1ll01Anims, gSor1ll01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1ll01Tiles);
                break;
            default:
                AnimChangeWithTables(&gFieldTransitionWork->anim, 0, ANIM_FLAG_LOOP, gSor1bl01Anims, gSor1bl01Frames);
                SetObjTileSource(gFieldTransitionWork->tiles, gSor1bl01Tiles);
                break;
            }
        }

        gFieldTransitionWork->initialized++;
    }

    gfx = AnimUpdate(&gFieldTransitionWork->anim);

    if (gFieldTransitionWork->flipped != 0) {
        DrawSprite(120, 96, gfx, gFieldTransitionWork->tiles, gFieldTransitionWork->palette, NULL, SPRITE_FLAG_HFLIP, 0);
    } else {
        DrawSprite(120, 96, gfx, gFieldTransitionWork->tiles, gFieldTransitionWork->palette, NULL, 0, 0);
    }

    gSystemFlags &= ~SYSTEM_FLAG_DMA3_IMMEDIATE;
    UpdateSpriteOam();
}

void StartFieldTransition() {
    ModeSetTransitionCallback(FieldTransitionInit, FieldTransitionUpdate);
}

u8 ClampBosBoogieBounds(s32* a, s32* b, s32* c, s32* d) {
    if (*b < 0x24000) {
        if (*c > -0x2000) {
            *d = 0;
            *b = 0x24000;
            return 1;
        }

        *d = -0x2000;
    } else {
        *d = 0;
    }

    return 0;
}
