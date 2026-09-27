#ifndef GUARD_BOS3_H
#define GUARD_BOS3_H

#include "types.h"
#include "game.h"
#include "save_types.h"

typedef struct JfShadowWork {
    void* tiles;
    void* palette;
    void* gfx;
    BtlObj* actor;
} JfShadowWork;

void task_bos_jf_shadow_0(JfShadowWork* work, BtlObj* obj);
s32 task_bos_jf_shadow_1(void);
void task_bos_jf_shadow_2(JfShadowWork* work);
void task_bos_jf_shadow_3(JfShadowWork* work);

void func_080C6FF8(void);
void func_080C700C(SaveSliceE6C* out);
void func_080C7024(SaveSliceE6C* in);

#endif /* GUARD_BOS3_H */
