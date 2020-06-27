#include "displayFrameScoreTimeHits.c"
#include "displayFrameBlitting.c"
#include "displayFrameGameOver.c"
#include "displayFrameGameComplete.c"
#include "displayFrameIntro.c"
#include "displayFrameLevel.c"

void DisplayFrame() {

	StartDrawing();
	
	BlitBackground();

	if(g_Game.Room == ROOM_INTRO)        DisplayFrameIntro();
	if(g_Game.Room == ROOM_LEVEL)        DisplayFrameLevel();
	if(g_Game.Room == ROOM_GAMEOVER)     DisplayFrameGameOver();
	if(g_Game.Room == ROOM_GAMECOMPLETE) DisplayFrameGameComplete();

	StopDrawing();
}