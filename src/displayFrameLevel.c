
void DisplayFrameLevel() {	
	

	
	// Special case for Boss-Man levels where we order the layers
	if (g_ThisLevel.IsBoss && 
		(g_Enemies[0].YPos > g_Pitman.YPos || g_Enemies[0].State == SPRITE_STATE_DYING)) {

		BlitPitman();
		BitEnemies();
	}
	else {
		BitEnemies();	
		BlitPitman();
	}

	// Introduce the Level
	if (g_Time.SinceLevelStarted <= LEVEL_INTRO_TIME) {
		char levelNumber[10];
		sprintf(levelNumber, "Level %d", g_Game.Level);
		DrawText(&g_Text.LevelStart1, levelNumber);
		DrawText(&g_Text.LevelStart2, g_ThisLevel.Name);
	}

	// score, time and boss hits
	DisplayFrameScoreTimeBossHits();

	// Paused
	if (g_Time.IsPaused) {
		BlitPauseBackground();
		DrawText(&g_Text.GamePaused, "Game Paused");
		DrawText(&g_Text.Resume,     "Resume");
		CycleTextColours(&g_Text.Resume);

	}
}