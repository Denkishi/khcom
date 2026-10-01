#ifndef GUARD_BTL_EFFECT_H
#define GUARD_BTL_EFFECT_H

#include "battle_actor_types.h"
#include "types.h"

u8 BgFxIsActive();
void BgFxSetPosition(s32 x, s32 y, s32 z);

void BgFxInit(u16 a, u16 bg);
void BgFxFree();
void BgFxUpdate();
void BgFxStartCure(u16 a, s32 x, s32 y, s32 z);
void BgFxStartFire(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w);
void BgFxStartFireAtPlayer(s32 x, s32 y, s32 z, u8 f, s32 unused, s32 w, u16 a);
void BgFxStartBlizzard(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w);
void BgFxStartFlash(s32 x, s32 y, s32 z);
void BgFxStartThunderHit(s32 x, s32 y, s32 z);
void BgFxStartPotion(s32 x, s32 y, s32 z);
void BgFxStartWideThunder(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q);
void BgFxStartEnemyDeath(s32 x, s32 y, s32 z, s32 s);
void BgFxStartDarkDeath(s32 x, s32 y, s32 z, s32 s);
void BgFxStartEnemySpawn(s32 x, s32 y, s32 z, s32 s);
void BgFxStartDarkDeathBlend(s32 x, s32 y, s32 s, u16 b, u16 c);
void BgFxStartExplosion(s32 x, s32 y, s32 z);
void BgFxGetPosition(s32* a, s32* b, s32* c);
void BgFxStartSummon(s32 x, s32 y, s32 z);
void BgFxStartFriendHit(s32 x, s32 y, s32 z);
void BgFxStartActorThunder(BtlObj* p);
void BgFxStartDsdEnergy(s32 x, s32 y, s32 z, s32 w, s32 a, s32 b);
void BgFxAddPosition(s32 a, s32 b, s32 c);
void BgFxSignalEnd(u8 bit);
void BgFxSetTarget(s32 a, s32 b, s32 c);
void BgFxSetAngle(u8 a);
void BgFxSetScale(s32 a, s32 b);
void BgFxStartGroundImpact(s32 x, s32 y);
void BgFxStartStop(u16 a, s32 x, s32 y, s32 z, s32 w);
void BgFxStartCharaDefeat(s32 x, s32 y);
void BgFxStartHumDefeat(s32 x, s32 y);
void BgFxStartBossDeath(s32 x, s32 y);
void BgFxStartCharaDefeatEnd(s32 x, s32 y);
void BgFxStartGravity(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w);
void BgFxStartGravityStrike(s32 x, s32 y, s32 z, s32 w);
void BgFxStartShockwave(s32 x, s32 y, u8 f);
void BgFxStartGas(s32 x, s32 y, s32 z, u8 f);
void BgFxStartBoogieKaihuku(s32 x, s32 y, s32 z, s32 s);
void BgFxStartBossDeathFlash();
void BgFxStartPcShot(s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, s32 s, u16 a, s32 t);
void BgFxStartThunderStrike(s32 x, s32 y, s32 z, s32 w);
void BgFxStartThunder(u16 a, s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, s32 s);
void BgFxStartDumboSplash(u16 a, s32 x, s32 y, s32 z, u8 f, s32 w);
void BgFxStartTrinityLimit(s32 x, s32 y, s32 z);
void BgFxStartTrinityLimitCharge(s32 x, s32 y, s32 z);
void BgFxStartTrinityLimitBlast(s32 x, s32 y, s32 z);
void BgFxStartRagnarokCharge(s32 x, s32 y, s32 z);
void BgFxStartSync(s32 x, s32 y, s32 z);
void BgFxStartStunImpact(s32 x, s32 y, s32 z);
void BgFxStartZantetsuken(s32 x, s32 y, s32 z, u8 f);
void BgFxStartUrsulaBeam(s32 x, s32 y, s32 z, u8 f, s32 w, u16 a);
void func_080169A0(s32 x, s32 y, s32 z, u8 f);
void BgFxStartJfMajinBeam(s32 x, s32 y, s32 z, s32 w, u8 f, u16 a);
void BgFxStartFireBurst(s32 x, s32 y, s32 z, s32 p, s32 q, s32 r, u8 f, s32 w);
void BgFxStartFireExplosion(s32 x, s32 y, s32 z);
void BgFxStartXmas(u16 a);
void BgFxStartVixenIceFall(u16 a);
void BgFxStartFlame(s32 x, s32 y, s32 z, s32 s);
void BgFxStartFrost(s32 x, s32 y, s32 z, s32 s);
void BgFxStartUrsulaThunder(s32 x, s32 y, s32 z);
void BgFxStartHoly(s32 x, s32 y, s32 z, s32 w);
void BgFxStartTornado(s32 x, s32 y, s32 z, s32 w, u8 f);
void BgFxStartBind(s32 x, s32 w);
void BgFxStartMahluxiaGround(s32 x, s32 y, s32 z, s32 w);
void BgFxStartLexceusGround(s32 x, s32 y, s32 z, s32 w);
void BgFxStartHanabira(s32 x, s32 y, s32 z, s32 w);
void BgFxStartKama(s32 x, s32 y, s32 z, s32 w, s32 v);
void BgFxStartLaxeneBeam(s32 x, s32 y, s32 z, u8 f, s32 v);
void BgFxStartRikuLimit(s32 x, s32 y, s32 z, u8 f);
void BgFxStartDragonFire(s32 x, s32 y, s32 z, s32 s);
void BgFxStartAero(u16 a, s32 x, s32 y, s32 z, s32 w);
void BgFxStartRikuDarkModeFlash(s32 x, s32 y, s32 z);
void BgFxStartLstCtr(s32 x, s32 y, s32 z, s32 s);
void BgFxStartLstCtrFlipped(s32 x, s32 y, s32 z, s32 s);
void func_08018B04(s32 x, s32 y, s32 z, s32 s);
void BgFxStartRikuDarkMode(s32 x, s32 y, s32 z);
void BgFxStartRikuLimitFinish(s32 x, s32 y, s32 z);
void func_08018FE4(s32 x, s32 y, s32 z);

#endif
