#include "platformSpecific/includeFiles.c"

#include "structSprite.c"
#include "structText.c"
#include "structLevel.c"
#include "structGameComplete.c"

#include "globals.c"

#include "platformSpecific/globals.c"
#include "platformSpecific/imageRoutines.c"
#include "platformSpecific/time.c"
#include "platformSpecific/text.c"
#include "platformSpecific/input.c"
#include "platformSpecific/sound.c"
#include "platformSpecific/exit.c"

#include "saveData.c"

#include "initialisePitman.c"
#include "initialiseIntro.c"
#include "initialiseGameComplete.c"
#include "initialiseLevel.c"
#include "initialiseGameOver.c"
#include "initialise.c"

#include "processFrameTimer.c"
#include "processFrameCollisions.c"
#include "processFramePitman.c"
#include "processFrameGameOver.c"
#include "processFrameGameComplete.c"
#include "processFrameIntro.c"
#include "processFrameLevel.c"
#include "processFrame.c"

#include "displayFrameScoreTimeHits.c"
#include "displayFrameBlitting.c"
#include "displayFrameGameOver.c"
#include "displayFrameGameComplete.c"
#include "displayFrameIntro.c"
#include "displayFrameLevel.c"
#include "displayFrame.c"
/////////////////////////////////////////////////


textStruct
g_TextTesting = { 20, 20,  FONT_SIZE_SMALL, FONT_COLOUR_1, FONT_STYLE_SHADOW,  true };


void DoTest() {

	int imageNo = 0, counter = 1;
	int musicNo = 0;
	char msg[10];
	g_Time = 10000;

	LoadImage(&g_ImageEnemy[0], "test01.png");
	// soundLoadBackgroundMusic("gameover.ogg", musicNo);

	while (true) {

		if(imageNo == 1) LoadImage(&g_ImageEnemy[0], "test01.png");
		if(imageNo == 2) LoadImage(&g_ImageEnemy[0], "test02.png");

		StartDrawing();
		BlitImageRegion(g_ImageEnemy[0], 0, 0,0,0,
						GetImageWidth(g_ImageEnemy[0]), GetImageHeight(g_ImageEnemy[0]), 0.234, 0.234);

		sprintf(msg, "%d", musicNo);
		DrawText(&g_TextTesting, msg);
		
		StopDrawing();

	    if(InputStartPressed()) break;	


		while (g_Time > 0) {
			WaitForNextFrame();
			UpdateTime();
			
		}
	    g_Time = 5000;

		//if (imageNo <= 1) SoundLoadBackgroundMusic("gameover.ogg");
		//if (imageNo == 2) SoundLoadBackgroundMusic("music.ogg");
		//SoundStartBackgroundMusic(1);

		imageNo++;
		if (imageNo == 3) imageNo = 1;

		counter++;
			
	}
}
////////////////////////////////////////////////


int main() {

	Initialise();

	//DoTest();
	//return 0;

	while (true) {	
		
		ProcessFrame();
		DisplayFrame();
		WaitForNextFrame();
		// if (InputStartPressed()) break;		
	}
	Exit();
	return 0;
}