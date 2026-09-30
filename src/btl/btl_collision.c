#include "engine_math.h"
#include "listpool.h"
#include "battle.h"
#include "btl_collision.h"
#include "btl_effect.h"
#include "songs.h"

const BattleAttackDef gBattleAttackDefs[330] = {
    { 256, 204, 0, 3, BgFxStartRikuHit, 0x80002000 },
    { 256, 204, 204, 3, BgFxStartRikuHit, 0x80002000 },
    { 384, 384, 384, 16, BgFxStartRikuHit, 0x80002000 },
    { 256, 1024, 384, 8, 0, 0x00003200 },
    { 384, 384, 0, 8, BgFxStartRikuHit, 0x80002000 },
    { 384, 128, 256, 20, BgFxStartRikuHit, 0x80002200 },
    { 384, 384, 512, 0, BgFxStartRikuHit, 0x80002000 },
    { 384, 256, -768, 8, BgFxStartRikuHit, 0x80002000 },
    { 512, 0, -256, 8, 0, 0x09002000 },
    { 1280, 256, 256, 8, BgFxStartRikuHit, 0x09002000 },
    { 2048, 256, 256, 8, 0, 0x09004000 },
    { 768, 0, 0, 8, 0, 0x09204000 },
    { 256, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 256, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 384, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 384, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 384, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 768, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 256, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 768, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 256, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 768, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 384, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 384, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 896, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 384, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 512, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 384, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 384, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 384, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 256, 204, 0, 3, BgFxStartSoraHit, 0x40002000 },
    { 896, 204, 204, 3, BgFxStartSoraHit, 0x40002000 },
    { 384, 384, 384, 16, BgFxStartSoraHit, 0x40002000 },
    { 512, 204, 0, 3, BgFxStartSoraHit, 0x08002000 },
    { 512, 204, 204, 3, BgFxStartSoraHit, 0x08002000 },
    { 896, 384, 384, 16, BgFxStartSoraHit, 0x08002000 },
    { 640, 204, 0, 3, BgFxStartSoraHit, 0x10002000 },
    { 640, 204, 204, 3, BgFxStartSoraHit, 0x10002000 },
    { 768, 384, 384, 16, BgFxStartSoraHit, 0x10002000 },
    { 512, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 512, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 256, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 896, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 256, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 512, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 640, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 1024, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 896, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 896, 204, 0, 3, BgFxStartSoraHit, 0x08002000 },
    { 896, 204, 204, 3, BgFxStartSoraHit, 0x08002000 },
    { 256, 384, 384, 16, BgFxStartSoraHit, 0x08002000 },
    { 1024, 204, 0, 3, BgFxStartSoraHit, 0x80002000 },
    { 1024, 204, 204, 3, BgFxStartSoraHit, 0x80002000 },
    { 1024, 384, 384, 16, BgFxStartSoraHit, 0x80002000 },
    { 768, 204, 0, 3, BgFxStartSoraHit, 0x20002000 },
    { 768, 204, 204, 3, BgFxStartSoraHit, 0x20002000 },
    { 768, 384, 384, 16, BgFxStartSoraHit, 0x20002000 },
    { 384, 204, 0, 3, BgFxStartSoraHit, 0x10002000 },
    { 384, 204, 204, 3, BgFxStartSoraHit, 0x10002000 },
    { 1536, 384, 384, 16, BgFxStartSoraHit, 0x10002000 },
    { 1280, 51, 51, 15, 0, 0x10004800 },
    { 2560, 76, 76, 15, 0, 0x10004800 },
    { 3840, 128, 128, 20, 0, 0x10004800 },
    { 1024, 0, 0, 15, 0, 0x20004000 },
    { 2048, 0, 0, 15, 0, 0x20004000 },
    { 3328, 0, 0, 20, 0, 0x20004000 },
    { 768, 256, 256, 15, 0, 0x40005000 },
    { 1280, 256, 256, 15, 0, 0x40005000 },
    { 2048, 256, 256, 15, 0, 0x40005000 },
    { 51, 0, 0, 0, 0, 0x00004400 },
    { 102, 0, 0, 0, 0, 0x00004400 },
    { 179, 0, 0, 0, 0, 0x00004400 },
    { 512, 0, 0, 15, 0, 0x00004900 },
    { 896, 0, 0, 15, 0, 0x00004100 },
    { 1536, 0, 0, 15, 0, 0x00004100 },
    { 768, -384, 384, 0, 0, 0x08005000 },
    { 1536, -384, 384, 0, 0, 0x08005000 },
    { 2304, -384, 384, 0, 0, 0x08005000 },
    { 512, 0, 256, 8, BgFxStartSoraHit, 0x09002000 },
    { 1536, 0, 256, 8, BgFxStartSoraHit, 0x09002000 },
    { 256, 0, 0, 8, BgFxStartSoraHit, 0x09002200 },
    { 6400, 384, 0, 0, 0, 0x08025000 },
    { 640, 76, 0, 2, BgFxStartFlashHit, 0x09002000 },
    { 768, 332, 384, 2, BgFxStartFlashHit, 0x09002000 },
    { 1280, -921, 384, 13, BgFxStartFlashHit, 0x09002000 },
    { 3328, 0, 0, 0, 0, 0x09004000 },
    { 256, 0, 0, 8, 0, 0x09004200 },
    { 512, 460, -768, 8, BgFxStartFlashHit, 0x09002000 },
    { 640, 332, 307, 3, BgFxStartSoraHit, 0x09002000 },
    { 256, 0, 0, 20, 0, 0x09002000 },
    { 5120, 384, 256, 20, 0, 0x10025000 },
    { 3072, 128, 128, 20, 0, 0x10004000 },
    { 0, 0, 0, 20, 0, 0x010C2000 },
    { 640, 204, 0, 0, 0, 0x20004000 },
    { 2048, 0, 0, 8, BgFxStartSoraHit, 0x01002100 },
    { 1280, 0, 0, 8, 0, 0x11002000 },
    { 1280, 0, 0, 8, 0, 0x21002000 },
    { 3072, 256, 256, 15, 0, 0x41003000 },
    { 179, 0, 0, 0, 0, 0x01003400 },
    { 1280, 0, 0, 4, BgFxStartSoraHit, 0x09002000 },
    { 2048, 0, 256, 8, 0, 0x09002000 },
    { 0, 844, 332, 8, 0, 0x09002000 },
    { 512, 0, 0, 0, 0, 0x01002100 },
    { 1024, 0, 0, 0, 0, 0x01002900 },
    { 0, 0, 0, 0, 0, 0x01102000 },
    { 640, 0, 384, 4, BgFxStartSoraHit, 0x01002800 },
    { 2048, 0, 844, 0, 0, 0x08024000 },
    { 3328, 256, 256, 4, 0, 0x08005200 },
    { 256, 256, 256, 8, 0, 0x00205000 },
    { 256, 0, 0, 8, 0, 0x00405000 },
    { 25, 0, 0, 0, 0, 0x08009000 },
    { 25, 0, 0, 0, 0, 0x08009200 },
    { 25, 0, 0, 0, 0, 0x08208800 },
    { 1152, 0, 256, 8, BgFxStartFriendHit, 0x08011000 },
    { 1024, 384, 384, 3, BgFxStartFriendHit, 0x08011000 },
    { 1024, 384, 384, 3, BgFxStartFriendHit, 0x08011200 },
    { 768, 512, 384, 3, BgFxStartFriendHit, 0x08011000 },
    { 1536, 51, 51, 15, 0, 0x10011800 },
    { 3072, 76, 76, 15, 0, 0x10011800 },
    { 4608, 128, 128, 20, 0, 0x10011800 },
    { 1280, 0, 0, 15, 0, 0x20011000 },
    { 2560, 0, 0, 15, 0, 0x20011000 },
    { 3840, 0, 0, 20, 0, 0x20011000 },
    { 1024, 256, 256, 15, 0, 0x40011000 },
    { 2048, 256, 256, 15, 0, 0x40011000 },
    { 3072, 256, 256, 15, 0, 0x40011000 },
    { 1280, 256, 256, 0, 0, 0x10011000 },
    { 1536, 51, 51, 15, 0, 0x10011800 },
    { 3072, 76, 76, 15, 0, 0x10011800 },
    { 4608, 128, 128, 20, 0, 0x10011800 },
    { 1280, 0, 0, 15, 0, 0x20011000 },
    { 2560, 0, 0, 15, 0, 0x20011000 },
    { 3840, 0, 0, 20, 0, 0x20011000 },
    { 1024, 256, 256, 15, 0, 0x40011000 },
    { 2048, 256, 256, 15, 0, 0x40011000 },
    { 3072, 256, 256, 15, 0, 0x40011000 },
    { 25, 0, 0, 0, 0, 0x00009400 },
    { 76, 0, 0, 0, 0, 0x00009400 },
    { 230, 0, 0, 0, 0, 0x00009400 },
    { 2048, 256, 256, 8, 0, 0x80011000 },
    { 1536, 256, 256, 8, 0, 0x40009000 },
    { 1280, 0, 0, 8, 0, 0x00009900 },
    { 102, 0, 0, 0, 0, 0x00009400 },
    { 512, 384, 256, 8, BgFxStartFriendHit, 0x08011000 },
    { 256, 0, 0, 4, BgFxStartFriendHit, 0x08011000 },
    { 1280, 0, 256, 30, BgFxStartFriendHit, 0x08008000 },
    { 2560, 486, 384, 30, BgFxStartFriendHit, 0x08008000 },
    { 768, 0, 0, 30, 0, 0x08008000 },
    { 768, 0, 0, 30, 0, 0x08008200 },
    { 1280, 0, 0, 30, 0, 0x08008200 },
    { 384, 204, 0, 0, 0, 0x20008000 },
    { 384, 51, 51, 0, 0, 0x10008800 },
    { 512, 76, 76, 0, 0, 0x10008800 },
    { 384, 128, 128, 0, 0, 0x10008800 },
    { 512, 460, 460, 3, BgFxStartFriendHit, 0x08011000 },
    { 768, 460, 460, 3, BgFxStartFriendHit, 0x08011000 },
    { 1024, 0, 0, 0, BgFxStartFriendHit, 0x08010400 },
    { 1024, 0, 0, 0, BgFxStartFriendHit, 0x08010000 },
    { 1536, 0, 0, 0, 0, 0x00040000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 76, 76, 8, BgFxStartEnemyHit, 0x10004000 },
    { 640, 128, 128, 8, BgFxStartEnemyHit, 0x10004000 },
    { 384, 0, 0, 8, BgFxStartEnemyHit, 0x20004000 },
    { 512, 0, 0, 8, BgFxStartEnemyHit, 0x20004000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x40004000 },
    { 384, 256, 256, 15, 0, 0x40005000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00004000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00004000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x00004200 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 384, -256, 12, BgFxStartEnemyHit, 0x80002000 },
    { 384, 128, 512, 12, BgFxStartEnemyHit, 0x80002000 },
    { 179, 358, 179, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 640, 384, 384, 0, BgFxStartEnemyHit, 0x10003000 },
    { 256, 128, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 192, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 384, 256, 256, 15, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 204, 51, 512, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 320, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x10002000 },
    { 153, 332, 0, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 409, 0, 15, BgFxStartEnemyHit, 0x80002200 },
    { 384, 256, 512, 12, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, -256, 12, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 76, 0, 0, 4, BgFxStartEnemyHit, 0x80002000 },
    { 204, 0, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 640, 51, 51, 15, 0, 0x10004000 },
    { 512, 0, 0, 15, 0, 0x20004000 },
    { 256, 256, 256, 15, 0, 0x40005000 },
    { 332, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 0, 384, 8, BgFxStartEnemyHit, 0x08002000 },
    { 307, 256, 256, 15, 0, 0x10004000 },
    { 64, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 204, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 15, 0, 0x40005000 },
    { 153, 332, 204, 8, BgFxStartEnemyHit, 0x80002000 },
    { 307, 256, 256, 8, 0, 0x10000000 },
    { 256, 256, 0, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 281, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 307, 358, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 12, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 102, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 102, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 153, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 8, 0, 0x10002000 },
    { 256, 256, 256, 8, 0, 0x80002000 },
    { 384, 256, 256, 8, 0, 0x40002000 },
    { 384, 256, 256, 8, 0, 0x40002000 },
    { 256, 256, 256, 8, 0, 0x00002000 },
    { 384, 128, 128, 8, 0, 0x10002000 },
    { 512, 256, 0, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 0, 256, 8, 0, 0x08002000 },
    { 256, 0, 0, 8, BgFxStartEnemyHit, 0x08002000 },
    { 384, 460, 435, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x20202000 },
    { 768, 256, 256, 8, 0, 0x40002000 },
    { 384, 256, 256, 8, 0, 0x40002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 512, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 153, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 332, 256, 256, 8, 0, 0x10002000 },
    { 384, 819, 435, 0, BgFxStartEnemyHit, 0x00802000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 512, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 512, 0, 0, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 332, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 384, 256, 0, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 384, 8, BgFxStartEnemyHit, 0x80002000 },
    { 768, 384, 384, 8, 0, 0x10003000 },
    { 76, 0, 256, 0, BgFxStartEnemyHit, 0x80002000 },
    { 512, 0, 1152, 15, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 30, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 30, BgFxStartEnemyHit, 0x80002000 },
    { 512, 256, 256, 30, BgFxStartEnemyHit, 0x08002000 },
    { 204, 563, 256, 8, BgFxStartFireHit, 0x10002000 },
    { 332, 640, 0, 8, BgFxStartFireHit, 0x10002000 },
    { 460, 256, 256, 8, BgFxStartFireHit, 0x10002000 },
    { 76, 256, 256, 8, BgFxStartFireHit, 0x10002000 },
    { 256, 460, 0, 8, BgFxStartRikuHit, 0x80002000 },
    { 384, 128, 256, 20, BgFxStartRikuHit, 0x80002200 },
    { 256, 640, 256, 8, BgFxStartRikuHit, 0x80002000 },
    { 256, 256, 0, 8, BgFxStartRikuHit, 0x80002000 },
    { 512, 0, -256, 8, BgFxStartRikuHit, 0x80002000 },
    { 512, 256, 256, 8, BgFxStartRikuHit, 0x08002000 },
    { 768, 256, 256, 8, 0, 0x08004000 },
    { 512, 0, 0, 8, 0, 0x08204000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 0, BgFxStartFireHit, 0x80002000 },
    { 256, 128, 256, 0, BgFxStartFireHit, 0x80002000 },
    { 256, 256, 256, 3, BgFxStartFireHit, 0x80003000 },
    { 512, 256, 256, 8, 0, 0x10004000 },
    { 768, 0, 128, 8, BgFxStartFireHit, 0x10002000 },
    { 102, 384, 128, 8, BgFxStartThunderHit, 0x80002000 },
    { 102, 128, 384, 8, BgFxStartThunderHit, 0x80002000 },
    { 102, 102, 0, 8, 0, 0x80002000 },
    { 256, 256, 256, 8, 0, 0x40002000 },
    { 204, 256, 256, 8, 0, 0x40004000 },
    { 128, 0, 256, 0, 0, 0x40004200 },
    { 256, 256, 256, 8, 0, 0x40004000 },
    { 204, 256, 256, 8, BgFxStartBlizzardHit, 0x80002000 },
    { 256, 0, 0, 8, 0, 0x20004000 },
    { 384, 0, 0, 8, BgFxStartBlizzardHit, 0x20004000 },
    { 128, 256, 256, 8, BgFxStartEnemyHit, 0x08002000 },
    { 384, 256, 256, 8, 0, 0x08002000 },
    { 204, 256, 256, 8, 0, 0x08003000 },
    { 128, 0, 0, 8, 0, 0x08005000 },
    { 512, 0, 0, 0, 0, 0x08003000 },
    { 128, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 89, 512, 8, BgFxStartEnemyHit, 0x08002000 },
    { 128, 0, 0, 8, 0, 0x08004000 },
    { 256, 460, 332, 8, BgFxStartEnemyHit, 0x00002000 },
    { 384, 0, 0, 12, BgFxStartEnemyHit, 0x80002000 },
    { 384, 307, 256, 12, BgFxStartEnemyHit, 0x80002000 },
    { 384, 256, 256, 8, BgFxStartEnemyHit, 0x80002000 },
    { 256, 256, 256, 8, BgFxStartEnemyHit, 0x00002000 },
    { 256, 179, 179, 3, BgFxStartEnemyHit, 0x08002000 },
    { 384, 307, 256, 12, BgFxStartEnemyHit, 0x80002200 },
};


static ListPool gUnk_020348E8;
static ListPool gUnk_020348F8;
static ListPool gUnk_02034908;
static ListPool gUnk_02034918;

u8 CanAttackBoxHitBtlObj(BtlObj* p, s32 x, s32 y, s32 z, s16 a, s16 b, s16 c) {
    BtlObj* q = p->parent;
    u64 f;

    if (q != 0) {
        f = q->flags | p->flags;
    } else {
        f = p->flags;
        q = p;
    }

    if (f & 0x01000180) {
        return 0;
    }
    if (x - (a << 8) > p->x + (p->radiusX << 8)) {
        return 0;
    }
    if (x + (a << 8) < p->x - (p->radiusX << 8)) {
        return 0;
    }
    if (y - (b << 8) > p->y + (p->radiusY << 8)) {
        return 0;
    }
    if (y + (b << 8) < p->y - (p->radiusY << 8)) {
        return 0;
    }
    if (z - (c << 8) > p->z) {
        return 0;
    }
    if (z + (c << 8) < p->z - (p->height << 8)) {
        return 0;
    }
    if (q->invincibleTimer > 0) {
        return 0;
    }
    return 1;
}

void AbsorbAttack(BtlObj* a, BtlObj* b, const BattleAttackDef* c) {
    gBtlWork->pendingHitStop = 8;
    a->damage = -((b->attack * c->power) >> 8);
    a->flags |= 0x20;
}

s32 ResolveAttackHit(BtlObj* hit, s32 index) {
    const BattleAttackDef* attack = &gBattleAttackDefs[index];
    s32 scale = gBtlWork->damageScale;
    BtlObj* target;
    BtlObj* source;
    if (hit->parent != 0) {
        target = hit->parent;
    } else {
        target = hit;
    }
    target->hitFlags = attack->flags;
    target->hitAttack = index;
    if (attack->flags & 0x40000) {
        if (hit->flags & 0x8000000000ULL) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        }
        if (attack->flags & 0x80000) target->exp = 0;
        target->flags |= 0x40;
        return 0;
    }
    if (gBtlWork->flags & 0x4000) {
        if (gBtlWork->flags & 0x20000000) source = gBtlWork->actor;
        else source = gRikuBtlWork->actor;
    } else if (gBtlWork->flags & 0x800) {
        if (gBtlWork->flags & 0x20000000) source = gBtlWork->actor;
        else source = gBtlWork->actor3;
    } else {
        if (gBtlWork->flags & 0x20000000) source = gBtlWork->actor;
        else source = gBtlWork->actor3;
    }
    if (source->btl != 0) {
        switch (source->btl->hcEffect) {
        case 35:
            if ((attack->flags & 0x01002000) != 0x2000) break;
            if (hit->flags & 0x100000000ULL) break;
            if ((attack->flags & 0x80000000) && (hit->flags & 0x8000)) break;
            if ((attack->flags & 0x08000000) && (hit->flags & 0x0200000000000000ULL)) break;
            if ((attack->flags & 0x10000000) && (hit->flags & 0x4000000)) break;
            if ((attack->flags & 0x20000000) && (hit->flags & 0x8000000)) break;
            if ((attack->flags & 0x40000000) && (hit->flags & 0x10000000)) break;
            if (hit->badStatus == 2) break;
            {
                s16 drain = target->hp >> 3;
                if (drain <= 0) drain = 1;
                else if (drain > 20) drain = 20;
                source->hp += drain;
                target->hp -= drain;
                if (target->hp <= 0) target->hp = 1;
                if (source->hp > source->maxHp) source->hp = source->maxHp;
                CreateBtlPopTask(source, 10);
                target->exp -= target->exp >> 2;
            }
            break;
        case 43:
            if ((attack->flags & 0x01002000) == 0x2000) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            }
            break;
        case 8:
            if ((attack->flags & 0x01002000) == 0x2000 && source->hp < (source->maxHp >> 2)) {
                scale = scale != 0 ? (scale * 512) >> 8 : 512;
            }
            break;
        case 4:
            if (attack->flags & 0x10000000) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            }
            break;
        case 11:
            if (attack->flags & 0x20000000) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            }
            break;
        case 12:
            if (attack->flags & 0x40000000) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            }
            break;
        case 38:
            if (attack->flags & 0x4000) {
                scale = scale != 0 ? (scale * 332) >> 8 : 332;
            }
            break;
        case 39:
            if (attack->flags & 0x8000) {
                scale = scale != 0 ? (scale * 332) >> 8 : 332;
            }
            break;
        case 36:
            if ((attack->flags & 0x01002000) == 0x2000) {
                if (source->flags & 4) {
                    if ((hit->flags & 4) && hit->x < source->x) {
                        scale = scale != 0 ? (scale * 512) >> 8 : 512;
                    }
                } else if (!(hit->flags & 4) && source->x < hit->x) {
                    scale = scale != 0 ? (scale * 512) >> 8 : 512;
                }
            }
            break;
        }
    }
    if (target->btl != 0) {
        switch (target->btl->hcEffect) {
        case 14:
            if (attack->flags & 0x80000000) {
                CreateBtlPopTask(hit, 0);
                scale = scale != 0 ? (scale * 128) >> 8 : 128;
            }
            break;
        case 46:
            target->btl->hcEffectCount--;
#ifdef VERSION_EU
            if (attack->flags & 0x4000)
#endif
            {
                scale = scale != 0 ? (scale * 128) >> 8 : 128;
            }
            break;
        }
    }
    if (attack->flags & 0x80000000) {
        if (hit->flags & 0x8000) {
            switch ((u32)hit->kind) {
            case 7:
            case 28:
            case 50:
            case 52:
                m4aSongNumStart(SONG_BTL_GARD);
                break;
            default:
                m4aSongNumStart(SONG_BTL_RB_GARD);
                break;
            }
            hit->invincibleTimer = 30;
            CreateBtlPopTask(hit, 0);
            BgFxStartGuard(gBtlWork->x3, gBtlWork->y3, hit->z - hit->centerHeight * 256);
            return 2;
        } else if (hit->flags & 0x0020000000000000ULL) {
            scale = scale != 0 ? (scale * 128) >> 8 : 128;
        } else if (hit->flags & 0x0002000000000000ULL) {
            if (target->flags & 0x0440000040000000ULL) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            } else {
                hit->flags |= 0x4000;
            }
        }
    } else if (attack->flags & 0x08000000) {
        if (hit->flags & 0x0200000000000000ULL) {
            switch ((u32)hit->kind) {
            case 7:
            case 28:
            case 50:
                m4aSongNumStart(SONG_BTL_GARD);
                break;
            default:
                m4aSongNumStart(SONG_BTL_RB_GARD);
                break;
            }
            hit->invincibleTimer = 30;
            CreateBtlPopTask(hit, 0);
            BgFxStartGuard(gBtlWork->x3, gBtlWork->y3, hit->z - hit->centerHeight * 256);
            return 2;
        } else if (hit->flags & 0x0100000000000000ULL) {
            scale = scale != 0 ? (scale * 128) >> 8 : 128;
        } else if (hit->flags & 0x0080000000000000ULL) {
            if (target->flags & 0x0440000040000000ULL) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            } else {
                hit->flags |= 0x4000;
            }
        }
    } else if (attack->flags & 0x10000000) {
        if (hit->flags & 0x100000) {
            AbsorbAttack(target, source, attack);
            return 1;
        }
        if (hit->flags & 0x4000000) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        } else if (hit->flags & 0x0004000000000000ULL) {
            scale = scale != 0 ? (scale * 128) >> 8 : 128;
        } else if (hit->flags & 0x0000400000000000ULL) {
            if (target->flags & 0x0040000040000000ULL) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            } else {
                hit->flags |= 0x4000;
            }
        }
    } else if (attack->flags & 0x20000000) {
        if (hit->flags & 0x200000) {
            AbsorbAttack(target, source, attack);
            return 1;
        }
        if (hit->flags & 0x8000000) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        } else if (hit->flags & 0x0008000000000000ULL) {
            scale = scale != 0 ? (scale * 128) >> 8 : 128;
        } else if (hit->flags & 0x0000800000000000ULL) {
            if (target->flags & 0x0040000040000000ULL) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            } else {
                hit->flags |= 0x4000;
            }
        }
    } else if (attack->flags & 0x40000000) {
        if (hit->flags & 0x400000) {
            AbsorbAttack(target, source, attack);
            return 1;
        }
        if (hit->flags & 0x10000000) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        } else if (hit->flags & 0x0010000000000000ULL) {
            scale = scale != 0 ? (scale * 128) >> 8 : 128;
        } else if (hit->flags & 0x0001000000000000ULL) {
            if (target->flags & 0x0040000040000000ULL) {
                scale = scale != 0 ? (scale * 384) >> 8 : 384;
            } else {
                hit->flags |= 0x4000;
            }
        }
    } else if (attack->flags & 0x100) {
        if (hit->flags & 0x80000000ULL) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        }
        hit->flags |= 0x800;
        if (scale == 0) hit->damage = ((u32)attack->power * 15) >> 6;
        else hit->damage = (((attack->power * 60) >> 8) * scale) >> 8;
        gBtlWork->pendingHitStop = (u8)attack->hitStop;
        hit->invincibleTimer = 30;
        return 1;
    }
    if (hit->flags & 0x100000000ULL) {
        CreateBtlPopTask(hit, 0);
        hit->invincibleTimer = 30;
        gBtlWork->hitStop = (u8)attack->hitStop;
        return 1;
    }
    if (attack->flags & 0x200) {
        target->flags |= 0x4000;
    } else if (attack->flags & 0x100000) {
        if (hit->flags & 0x4000000000ULL) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        }
        target->flags |= 0x2000000000ULL;
    } else if (attack->flags & 0x200000) {
        if (hit->flags & 0x20000000000ULL) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        }
        target->flags |= 0x10000000000ULL;
    } else if (attack->flags & 0x400000) {
        if (hit->flags & 0x80000000000ULL) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        }
        target->flags |= 0x40000000000ULL;
    }
    if (attack->flags & 0x400) {
        if (hit->flags & 0x200000000ULL) {
            CreateBtlPopTask(hit, 0);
            hit->invincibleTimer = 30;
            return 2;
        }
        target->flags |= 0x40000;
        if (attack->flags & 0x8000000) {
            if (scale == 0) target->damage = (source->attack * attack->power) >> 8;
            else target->damage = (((source->attack * attack->power) >> 8) * scale) >> 8;
        } else {
            if (scale == 0) target->damage = (target->hp * attack->power) >> 8;
            else target->damage = (((target->hp * attack->power) >> 8) * scale) >> 8;
            if (target->flags & 0x0400000000000000ULL) {
                target->damage = (target->damage * 76) >> 8;
            }
        }
    } else {
        if (scale == 0) target->damage = (source->attack * attack->power) >> 8;
        else target->damage = (((source->attack * attack->power) >> 8) * scale) >> 8;
        if (target->damage == 0 && attack->power > 0) target->damage = 1;
    }
    if (target->btl != 0 && target->btl->hcEffect == 26) {
        if (target->hp > 1 && target->hp - target->damage <= 0) {
            target->damage = target->hp - 1;
            target->invincibleTimer = 60;
            CreateBtlPopTask(target, 0);
            target->btl->hcEffectCount--;
        }
    }
    target->flags |= 2;
    gBtlWork->pendingHitStop = (u8)attack->hitStop;
    target->knockbackSpeed = attack->knockbackSpeed;
    target->knockbackLift = attack->knockbackLift;
    if (attack->flags & 0x800000) {
        if (source->flags & 4) target->angle = 192;
        else target->angle = 64;
    } else if (attack->flags & 0x1000) {
        target->angle = GetAngle(gBtlWork->x3, gBtlWork->y3, target->x, target->y);
    } else {
        target->angle = GetAngle(source->x, source->y, target->x, target->y);
    }
    return 1;
}
u8 TestAttackBox(s32 x, s32 y, s32 z, s16 a, s16 b, s16 c) {
    BtlObj* o;

    gBtlWork->areaUpdated = 1;
    gBtlWork->x3 = x;
    gBtlWork->y3 = y;
    gBtlWork->z3 = z;
    gBtlWork->areaHalfX = a;
    gBtlWork->areaHalfY = b;
    gBtlWork->areaHalfZ = c;

    if (gBtlWork->flags & 0x4000) {
        if (gBtlWork->flags & 0x20000000) {
            o = gRikuBtlWork->actor;
        } else {
            o = gBtlWork->actor;
        }
        if (CanAttackBoxHitBtlObj(o, x, y, z, a, b, c)) {
            return 1;
        }
    } else if (gBtlWork->flags & 0x20000000) {
        o = ListPoolFirst(&gBtlWork->pool);

        while (o != 0) {
            if (CanAttackBoxHitBtlObj(o, x, y, z, a, b, c)) {
                return 1;
            }
            o = ListPoolNext(&o->node);
        }
        return 0;
    } else {
        o = gBtlWork->actor;
        if (CanAttackBoxHitBtlObj(o, x, y, z, a, b, c)) {
            return 1;
        }
    }
    return 0;
}

s32 ApplyAttackToBtlObj(s32 a, BtlObj* b) {
    return ResolveAttackHit(b, a);
}

s32 ApplyAttackBox(s32 a, s32 x, s32 y, s32 z, s16 p, s16 q, s16 r) {
    const BattleAttackDef* t;
    BtlObj* o;
    s32 sx;
    s32 sy;
    s32 sz;
    s16 cnt;
    s32 flag;
    s32 n;
    s32 res;
    s32 r2;

    t = &gBattleAttackDefs[a];
    cnt = 0;
    flag = 0;
    gBtlWork->areaUpdated = 1;
    gBtlWork->x3 = x;
    gBtlWork->y3 = y;
    gBtlWork->z3 = z;
    gBtlWork->areaHalfX = p;
    gBtlWork->areaHalfY = q;
    gBtlWork->areaHalfZ = r;

    if (gBtlWork->flags & 0x4000) {
        if (gBtlWork->flags & 0x20000000) {
            o = gRikuBtlWork->actor;
        } else {
            o = gBtlWork->actor;
        }
        if (CanAttackBoxHitBtlObj(o, x, y, z, p, q, r)) {
            res = ResolveAttackHit(o, a);

            if (res == 1) {
                if (t->hitEffect != 0) {
                    t->hitEffect(o->x, o->y, o->z);
                }
            }
            return res;
        }
    } else if (gBtlWork->flags & 0x20000000) {
        o = ListPoolFirst(&gBtlWork->pool);
        sz = 0;
        sy = 0;
        sx = 0;

        while (o != 0) {
            if (!CanAttackBoxHitBtlObj(o, x, y, z, p, q, r)) {
                o = ListPoolNext(&o->node);
                continue;
            }
            r2 = ResolveAttackHit(o, a);

            if (r2 == 1) {
                sx += o->x;
                sy += o->y;
                sz += o->z;
                cnt++;

                if (t->flags & 0x800) {
                    break;
                }
            } else if (r2 == 2) {
                flag = 1;
            }

            o = ListPoolNext(&o->node);
        }

        if (flag != 0) {
            return 2;
        }

        n = cnt;

        if (n > 0) {
            if (t->hitEffect != 0) {
                sx /= n;
                sy /= n;
                sz /= n;
                t->hitEffect(sx, sy, sz);
            }
            return 1;
        }
    } else {
        o = gBtlWork->actor;
        if (CanAttackBoxHitBtlObj(o, x, y, z, p, q, r)) {
            res = ResolveAttackHit(o, a);

            if (res == 1) {
                if (t->hitEffect != 0) {
                    t->hitEffect(o->x, o->y, o->z);
                }
            }
            return res;
        }
    }

    return 0;
}

s32 ApplyAttackAt(s32 a, s32 b, s32 c, s32 d) {
    return ApplyAttackBox(a, b, c, d, 16, 16, 16);
}

s32 ApplyAttackInFront(BtlObj* p, s16 h, s32 c) {
    if (p->flags & 4) {
        return ApplyAttackAt(p->x - (h << 8), p->y, p->z - (p->height >> 1), c);
    } else {
        return ApplyAttackAt(p->x + (h << 8), p->y, p->z - (p->height >> 1), c);
    }
}

void FldObjRegister(FldObj* p) {
    ListNodeInit(&p->node, &gFieldState->actor.pool, p);
    ListPoolAppend(&p->node, &gFieldState->actor.pool);
}

void FldObjUnregister(FldObj* p) {
    ListPoolRemove(&p->node, &gFieldState->actor.pool);
}

void func_08012214(void) {
}

void* ColliderGetPool(u32 type) {
    switch (type) {
    case 1:
    case 2:
    case 4:
    case 9:
        return &gUnk_020348E8;
    case 3:
        return &gUnk_020348F8;
    case 5:
    case 7:
    case 8:
    case 10:
    case 11:
    case 12:
        return &gUnk_02034908;
    }
    return &gUnk_02034918;
}

void ColliderPoolsInit(void) {
    ListPoolInit(&gUnk_020348E8);
    ListPoolInit(&gUnk_020348F8);
    ListPoolInit(&gUnk_02034908);
    ListPoolInit(&gUnk_02034918);
}

void ColliderInit(Collider* p, u32 type, u16 r, u16 h) {
    void* pool;
    p->otherType = 0;
    p->colliding = 0;
    p->standFlags = 0;
    p->flags = 0;
    p->radius = r << 8;
    p->height = h << 8;
    p->type = type;
    p->self = p;
    p->touchedTypes = 0;
    pool = ColliderGetPool(type);

    switch (type) {
    case 6:
    case 7:
        p->flags |= 1;
        break;
    }
    ListNodeInit(&p->node, pool, p);
    ListPoolAppend(&p->node, pool);
}

void ColliderUnregister(Collider* p) {
    Collider* q = p->self;
    if (q == p) {
        ListPoolRemove(&q->node, ColliderGetPool(q->type));
    }
}

void ColliderSetPosition(Collider* p, s32 a, s32 b, s32 c) {
    p->x = a;
    p->y = b * 2;
    p->z = c;
}

void ColliderClearPoolContacts(ListPool* pool) {
    Collider* p = ListPoolFirst(pool);
    while (p != 0) {
        p->colliding = 0;
        p->touchedTypes = 0;
        p->standFlags = 0;
        p = ListPoolNext(&p->node);
    }
}

void ColliderCheckPoolPairs(ListPool* a, ListPool* b) {
    Collider* p;
    Collider* q;
    s32 sum;
    s32 dx;
    s32 dy;
    s32 pen;
    s32 dz;
    s32 t;
    u8 angle;

    p = ListPoolFirst(a);

    while (p != 0) {
        q = ListPoolLast(b);

        while (q != 0 && p != q) {
            sum = p->radius + q->radius;
            dx = p->x - q->x;

            if (dx < 0) {
                dx = q->x - p->x;
            }

            dy = p->y - q->y;

            if (dy < 0) {
                dy = q->y - p->y;
            }

            if (dx < sum && dy < sum) {
                pen = sum - Sqrt8(((dx * dx) >> 8) + ((dy * dy) >> 8));

                if (pen > 0) {
                    dz = p->z - q->z;

                    if (dz < p->height && -dz < q->height) {
                        q->colliding = 1;
                        p->colliding = 1;
                        p->otherType = q->type;
                        q->otherType = p->type;
                        p->touchedTypes |= 1 << q->type;
                        q->touchedTypes |= 1 << p->type;
                        angle = GetAngle(p->x, p->y, q->x, q->y);
                        t = (pen * gSineTable[angle]) >> 8;
                        p->pushX = -t;
                        p->pushY = -((pen * -gSineTable[angle + 64]) >> 8);
                        p->other = q;
                        q->pushX = t;
                        q->pushY = -p->pushY;
                        q->other = p;

                        if (q->flags & 1) {
                            p->platformZ = q->z - q->height;
                            p->penetration = pen;
                            p->platformY = q->y >> 1;
                            p->platformX = q->x;
                        }

                        if (p->flags & 1) {
                            q->platformZ = p->z - p->height;
                            q->penetration = pen;
                            q->platformY = p->y >> 1;
                            q->platformX = p->x;
                        }
                    } else {
                        if (q->flags & 1) {
                            if (q->z - q->height >= p->z) {
                                p->standFlags |= 1;

                                if (q->z - q->height == p->z) {
                                    q->standFlags |= 2;
                                    p->touchedTypes |= 1 << q->type;
                                    q->touchedTypes |= 1 << p->type;
                                }

                                p->platformZ = q->z - q->height;
                                p->penetration = pen;
                                p->platformY = q->y >> 1;
                                p->platformX = q->x;
                                p->other = q;
                                p->otherType = q->type;
                                q->otherType = p->type;
                            }
                        }

                        if (p->flags & 1) {
                            if (p->z - p->height >= q->z) {
                                q->standFlags |= 1;

                                if (p->z - p->height == q->z) {
                                    p->standFlags |= 2;
                                    p->touchedTypes |= 1 << q->type;
                                    q->touchedTypes |= 1 << p->type;
                                }

                                q->platformZ = p->z - p->height;
                                q->penetration = pen;
                                q->platformY = p->y >> 1;
                                q->platformX = p->x;
                                q->other = p;
                                p->otherType = q->type;
                                q->otherType = p->type;
                            }
                        }
                    }
                }
            }

            q = ListPoolPrev(&q->node);
        }

        p = ListPoolNext(&p->node);
    }
}

void ColliderUpdateAll(void) {
    ColliderClearPoolContacts(&gUnk_020348E8);
    ColliderClearPoolContacts(&gUnk_020348F8);
    ColliderClearPoolContacts(&gUnk_02034908);
    ColliderClearPoolContacts(&gUnk_02034918);
    ColliderCheckPoolPairs(&gUnk_020348E8, &gUnk_020348E8);
    ColliderCheckPoolPairs(&gUnk_020348F8, &gUnk_020348E8);
    ColliderCheckPoolPairs(&gUnk_02034908, &gUnk_020348E8);
    ColliderCheckPoolPairs(&gUnk_020348F8, &gUnk_020348F8);
    ColliderCheckPoolPairs(&gUnk_02034918, &gUnk_020348E8);
    ColliderCheckPoolPairs(&gUnk_02034918, &gUnk_020348F8);
}

void ColliderSetDisabled(Collider* p, u8 b) {
    if (b) {
        p->node.flags |= 2;
        p->colliding = 0;
        p->standFlags = 0;
    } else {
        p->node.flags &= ~2;
    }
}

u8 ColliderIsColliding(Collider* p) {
    return p->colliding;
}

void ColliderSetRadius(Collider* p, u16 r) {
    p->radius = r << 8;
}

void ColliderSetHeight(Collider* p, u16 h) {
    p->height = h << 8;
}

u8 ColliderIsTouchingType(Collider* p, s32 bit) {
    if (p->touchedTypes & (1 << bit)) {
        return 1;
    }
    return 0;
}
