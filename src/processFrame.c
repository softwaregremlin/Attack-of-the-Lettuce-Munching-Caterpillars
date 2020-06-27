#include "processFrameTimer.c"
#include "processFrameCollisions.c"
#include "processFramePitman.c"
#include "processFrameGameOver.c"
#include "processFrameGameComplete.c"
#include "processFrameRandomBonus.c"
#include "processFrameIntro.c"
#include "processFrameLevel.c"

void ProcessFrame() {

	if (g_Game.Room == ROOM_INTRO)        { ProcessFrameIntro();        return; }
	if (g_Game.Room == ROOM_LEVEL)        { ProcessFrameLevel();        return; }
	if (g_Game.Room == ROOM_GAMEOVER)     { ProcessFrameGameOver();     return; }
	if (g_Game.Room == ROOM_GAMECOMPLETE) { ProcessFrameGameComplete(); return; }
}