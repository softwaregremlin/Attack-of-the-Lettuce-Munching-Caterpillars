
void InitialiseGameCompleteBackgroundRocks() {

	float unscaledRockWidth = GetImageWidth(g_Images.Rock),
		unscaledRockHeight = GetImageHeight(g_Images.Rock),
		rockWidth = SCREEN_WIDTH;

	int xPos = 0, yPos = (int)(10 * g_Game.ScaleFactorDevice),
		rockStep = (int)((float)g_GameCompleteSettings.RockStep * g_Game.ScaleFactorDevice);

	for (unsigned int rr = 0; rr < g_GameCompleteSettings.RockCount; rr++) {
		g_GameCompleteSettings.BackgroundRocks[rr].UnScaledFrameWidth = unscaledRockWidth;
		g_GameCompleteSettings.BackgroundRocks[rr].UnScaledFrameHeight = unscaledRockHeight;

		g_GameCompleteSettings.BackgroundRocks[rr].ScalePercent = (int)(100 * ((float)rockWidth / (float)unscaledRockWidth));
		g_GameCompleteSettings.BackgroundRocks[rr].XPos = xPos;
		g_GameCompleteSettings.BackgroundRocks[rr].YPos = yPos;

		// Shrink down to the next size
		xPos += rockStep;
		yPos += rockStep;
		rockWidth -= 2 * rockStep;
	}
}

void InitialiseGameCompleteBand() {

	g_GameCompleteSettings.Band.UnScaledFrameWidth =
		(int)(GetImageWidth(g_Images.Band) / (float)g_GameCompleteSettings.BandFrames);

	g_GameCompleteSettings.Band.UnScaledFrameHeight = (int)GetImageHeight(g_Images.Band);

	float bandWidth = g_GameCompleteSettings.Band.UnScaledFrameWidth * g_Game.ScaleFactorDevice;
	g_GameCompleteSettings.Band.XPos = (float)((SCREEN_WIDTH - bandWidth) / 2);
	g_GameCompleteSettings.Band.YPos = (float)(100 * g_Game.ScaleFactorDevice);
}


void InitialiseGameComplete() {
	
	// set vars
	g_Game.Level = 9; // extra "level" for game complete song

	g_Game.Room = ROOM_GAMECOMPLETE;

	SoundStartBackgroundMusic(g_Music.GameComplete, 1);

	// Length of the song
	int songLength = GAME_COMPLETE_SONG_TIME;
	// if (g_Game.TestMode) songLength = LEVEL_CLEAR_PAUSE_TIME;
	g_Time.Remaining = songLength;
	
	// Background - flashing rocks
	InitialiseGameCompleteBackgroundRocks();

	// Band
	InitialiseGameCompleteBand();
}