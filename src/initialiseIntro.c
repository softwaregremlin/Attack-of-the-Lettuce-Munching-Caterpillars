
void InitialiseIntro() {
	
	

	//LoadImage(&g_ImageBackground, "background01.png");
	//LoadImage(&g_ImagePlayer,     "pitman.png");

	// set vars
	g_Game.Room = ROOM_INTRO;

	// Load High Score and Level Data
	FILE* dataFile;
	if ((dataFile = fopen(g_DataPaths.HighScore, "r"))) {
		fscanf(dataFile, "%d", &g_Game.HighScore);
		fclose(dataFile);
	}

	if ((dataFile = fopen(g_DataPaths.Level, "r"))) {
		fscanf(dataFile, "%d", &g_Game.Level);
		fclose(dataFile);
		if (g_Game.Level > 0) g_Game.Level--;
		if (g_Game.Level >= g_Game.LevelCount) g_Game.Level = 1;
	}

	if ((dataFile = fopen(g_DataPaths.MaxLevel, "r"))) {
		fscanf(dataFile, "%d", &g_Game.MaxLevelReached);
		fclose(dataFile);
	}

	// Initialise Pitman (just position)
	InitialisePitmanIntro();
	
	// Special Settings for the Intro
	g_ThisLevel.Complete = false;
	
	// Reset intro settings
	if (g_IntroSettings.StartGameTextInitialSize == 0) g_IntroSettings.StartGameTextInitialSize = g_Text.IntroStart.size;
	if (g_IntroSettings.StartGameTextInitialY == 0) g_IntroSettings.StartGameTextInitialY = g_Text.IntroStart.yPos;
	g_IntroSettings.TimeSinceSwipe = 0;

	g_Text.IntroStart.size = g_IntroSettings.StartGameTextInitialSize;
	g_Text.IntroStart.xPos = -1;
	g_IntroSettings.StartGameTextX = GetTextXCentered(&g_Text.IntroStart, "Start Game");
	g_Text.IntroStart.xPos = g_IntroSettings.StartGameTextX;
	g_Text.IntroStart.yPos = g_IntroSettings.StartGameTextInitialY;
	g_IntroSettings.Swiped = false;
	g_IntroSettings.SelectedMenuButton = INTRO_BUTTON_START;
	g_IntroSettings.ExplosionSoundPlayed = false;
	/////
	
	// Play Intro Music!
	SoundStartBackgroundMusicLoop(g_Music.Intro);
}