#ifndef GUARD_BTL_EFFECT_H
#define GUARD_BTL_EFFECT_H

#include "battle_actor_types.h"
#include "types.h"

u8 BgFxIsActive();
void BgFxSetPosition(s32 x, s32 y, s32 z);

void BgFxInit(u16 affine, u16 bg);
void BgFxFree();
void BgFxUpdate();
void BgFxStartCure(u16 variant, s32 x, s32 y, s32 z);
void BgFxStartFire(u16 variant, s32 x, s32 y, s32 z, s32 targetX, s32 targetY, s32 targetZ, u8 flip, s32 w);
void BgFxStartFireAtPlayer(s32 x, s32 y, s32 z, u8 flip, s32 unused, s32 w, u16 timer);
void BgFxStartBlizzard(u16 variant, s32 x, s32 y, s32 z, s32 targetX, s32 targetY, s32 targetZ, u8 flip, s32 w);
void BgFxStartFlash(s32 x, s32 y, s32 z);
void BgFxStartThunderHit(s32 x, s32 y, s32 z);
void BgFxStartPotion(s32 x, s32 y, s32 z);
void BgFxStartWideThunder(u16 variant, s32 x, s32 y, s32 z, s32 groundZ, s32 attack);
void BgFxStartEnemyDeath(s32 x, s32 y, s32 z, s32 s);
void BgFxStartDarkDeath(s32 x, s32 y, s32 z, s32 s);
void BgFxStartEnemySpawn(s32 x, s32 y, s32 z, s32 s);
void BgFxStartDarkDeathBlend(s32 x, s32 y, s32 s, u16 alphaA, u16 alphaB);
void BgFxStartExplosion(s32 x, s32 y, s32 z);
void BgFxGetPosition(s32* x, s32* y, s32* z);
void BgFxStartSummon(s32 x, s32 y, s32 z);
void BgFxStartFriendHit(s32 x, s32 y, s32 z);
void BgFxStartActorThunder(BtlObj* actor);
void BgFxStartDsdEnergy(s32 x, s32 y, s32 z, s32 w, s32 steps, s32 spinSpeed);
void BgFxAddPosition(s32 dx, s32 dy, s32 dz);
void BgFxSignalEnd(u8 bit);
void BgFxSetTarget(s32 x, s32 y, s32 z);
void BgFxSetAngle(u8 angle);
void BgFxSetScale(s32 scaleX, s32 scaleY);
void BgFxStartGroundImpact(s32 x, s32 y);
void BgFxStartStop(u16 variant, s32 x, s32 y, s32 z, s32 w);
void BgFxStartCharaDefeat(s32 x, s32 y);
void BgFxStartHumDefeat(s32 x, s32 y);
void BgFxStartBossDeath(s32 x, s32 y);
void BgFxStartCharaDefeatEnd(s32 x, s32 y);
void BgFxStartGravity(u16 variant, s32 x, s32 y, s32 z, s32 targetX, s32 targetY, s32 targetZ, u8 flip, s32 w);
void BgFxStartGravityStrike(s32 x, s32 y, s32 z, s32 w);
void BgFxStartShockwave(s32 x, s32 y, u8 flip);
void BgFxStartGas(s32 x, s32 y, s32 z, u8 facingLeft);
void BgFxStartBoogieKaihuku(s32 x, s32 y, s32 z, s32 s);
void BgFxStartBossDeathFlash();
void BgFxStartPcShot(s32 x, s32 y, s32 z, s32 targetX, s32 targetY, s32 targetZ, s32 attack, u16 steps, s32 targetScale);
void BgFxStartThunderStrike(s32 x, s32 y, s32 z, s32 w);
void BgFxStartThunder(u16 variant, s32 x, s32 y, s32 z, s32 targetX, s32 targetY, s32 targetZ, s32 attack);
void BgFxStartDumboSplash(u16 variant, s32 x, s32 y, s32 z, u8 flip, s32 w);
void BgFxStartTrinityLimit(s32 x, s32 y, s32 z);
void BgFxStartTrinityLimitCharge(s32 x, s32 y, s32 z);
void BgFxStartTrinityLimitBlast(s32 x, s32 y, s32 z);
void BgFxStartRagnarokCharge(s32 x, s32 y, s32 z);
void BgFxStartSync(s32 x, s32 y, s32 z);
void BgFxStartStunImpact(s32 x, s32 y, s32 z);
void BgFxStartZantetsuken(s32 x, s32 y, s32 z, u8 facingRight);
void BgFxStartUrsulaBeam(s32 x, s32 y, s32 z, u8 facingLeft, s32 w, u16 steps);
void BgFxStartAnsemRush(s32 x, s32 y, s32 z, u8 flip);
void BgFxStartJfMajinBeam(s32 x, s32 y, s32 z, s32 w, u8 angle, u16 steps);
void BgFxStartFireBurst(s32 x, s32 y, s32 z, s32 targetX, s32 targetY, s32 targetZ, u8 flip, s32 w);
void BgFxStartFireExplosion(s32 x, s32 y, s32 z);
void BgFxStartXmas(u16 steps);
void BgFxStartVixenIceFall(u16 steps);
void BgFxStartFlame(s32 x, s32 y, s32 z, s32 s);
void BgFxStartFrost(s32 x, s32 y, s32 z, s32 s);
void BgFxStartUrsulaThunder(s32 x, s32 y, s32 z);
void BgFxStartHoly(s32 x, s32 y, s32 z, s32 w);
void BgFxStartTornado(s32 x, s32 y, s32 z, s32 w, u8 flip);
void BgFxStartBind(s32 x, s32 w);
void BgFxStartMahluxiaGround(s32 x, s32 y, s32 z, s32 w);
void BgFxStartLexceusGround(s32 x, s32 y, s32 z, s32 w);
void BgFxStartHanabira(s32 x, s32 y, s32 z, s32 w);
void BgFxStartKama(s32 x, s32 y, s32 z, s32 w, s32 v);
void BgFxStartLaxeneBeam(s32 x, s32 y, s32 z, u8 flip, s32 v);
void BgFxStartRikuLimit(s32 x, s32 y, s32 z, u8 angle);
void BgFxStartDragonFire(s32 x, s32 y, s32 z, s32 s);
void BgFxStartAero(u16 variant, s32 x, s32 y, s32 z, s32 w);
void BgFxStartRikuDarkModeFlash(s32 x, s32 y, s32 z);
void BgFxStartLstCtr(s32 x, s32 y, s32 z, s32 s);
void BgFxStartLstCtrFlipped(s32 x, s32 y, s32 z, s32 s);
void BgFxStartDsdTransition(s32 x, s32 y, s32 z, s32 s);
void BgFxStartRikuDarkMode(s32 x, s32 y, s32 z);
void BgFxStartRikuLimitFinish(s32 x, s32 y, s32 z);
void BgFxStartRikuDiveHit(s32 x, s32 y, s32 z);

#endif
