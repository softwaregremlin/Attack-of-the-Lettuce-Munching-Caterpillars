#include "initialisePitman.c"
#include "initialiseIntro.c"
#include "initialiseGameComplete.c"
#include "initialiseLevel.c"
#include "initialiseGameOver.c"

void ShowLoading() {
	StartDrawing();
	char loadingDots[50] = "Loading";
	for (unsigned int dd = 0; dd < g_IntroSettings.LoadingDotCount; dd++) {
		char dot[] = ".";
		strcat(loadingDots, dot);
	}
	DrawText(&g_Text.Loading1, loadingDots);
	StopDrawing();
	g_IntroSettings.LoadingDotCount++;
}

void LoadSounds() {

	g_SoundSamples.StepSound = SoundLoadSample("step.ogg");           ShowLoading();
	g_SoundSamples.SwipeSound = SoundLoadSample("swipe.ogg");         ShowLoading();
	g_SoundSamples.HitSound = SoundLoadSample("hit.ogg");             ShowLoading();
	g_SoundSamples.NextWaveSound = SoundLoadSample("nextwave.ogg");   ShowLoading();
	g_SoundSamples.ExplosionSound = SoundLoadSample("explosion.ogg"); ShowLoading();

	g_Music.Intro = SoundLoadBackgroundMusic("music.ogg");                    ShowLoading();
	g_Music.LevelStartAndGameOver = SoundLoadBackgroundMusic("gameover.ogg"); ShowLoading();
	g_Music.LevelComplete = SoundLoadBackgroundMusic("bossmusic.ogg");        ShowLoading();
	g_Music.GameComplete  = SoundLoadBackgroundMusic("peepshow.ogg");         ShowLoading();
}

void LoadImages() {

	char imageName[20];
	for (unsigned int ee = 1; ee <= g_Game.LevelCount; ee++) {
		sprintf(imageName, "enemy%02d.png", ee);
		LoadImage(&g_Images.Enemy[ee-1], imageName);
		ShowLoading();
	}

	for (unsigned int bb = 1; bb <= g_Game.LevelCount / 2; bb++) {
		sprintf(imageName, "background%02d.png", bb);
		LoadImage(&g_Images.Background[bb-1], imageName);
		ShowLoading();
	}

	LoadImage(&g_Images.Player, "pitman.png");              ShowLoading();
	LoadImage(&g_Images.Rock,   "completed1.png");          ShowLoading();
	LoadImage(&g_Images.Band,   "completed2.png");          ShowLoading();
	LoadImage(&g_Images.PauseBackground, "pausebg.png");    ShowLoading();
}

void Initialise() {

	InitialiseGraphics();
	InitialiseFonts();
	InitialiseInput();
	InitialiseTimer();
	InitialiseSound();

	ShowLoading();

	LoadSounds();
	LoadImages();
	InitialisePitman();
	InitialiseIntro();
}