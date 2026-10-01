#ifndef GUARD_KEY_H
#define GUARD_KEY_H

#include "types.h"

u16 GetKeysHeld();
u16 GetKeysPressed();
u16 GetKeysRepeat();
u8 GetKeyReleaseTime(u16 key);
void UpdateKeyState();
void ResetKeyState();



u16 ReadKeyChord(u16 a, u16 b);
u16 ReadDpadChord();

#endif
