
void DisplayFrameIntro() {

	BlitPitman();

	// Intro - Title
	if (g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START) {
		DrawText(&g_Text.Intro1, "attack of the");
		DrawText(&g_Text.Intro2, "Lettuce");
		DrawText(&g_Text.Intro3, "Munching");
		DrawText(&g_Text.Intro4, "Caterpillars");
	}
	else { // Show the Selected Level
		char levelNumber[10];
		sprintf(levelNumber, "Level %d", g_Game.Level + 1);
		DrawText(&g_Text.LevelStart1, levelNumber);
		DrawText(&g_Text.LevelStart2, g_LevelSettings[g_Game.Level].Name);
	}

	if(g_Game.MaxLevelReached > 1) DrawText(&g_Text.IntroLevel, "Change Level");
	DrawText(&g_Text.IntroStart, "Start Game");
}