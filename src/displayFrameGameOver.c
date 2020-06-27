
void DisplayFrameGameOver() {


	//////////////
	// background
	//////////////
	BlitBackground();
	
	// ShowScoreTimeBossHits();

	// Game Over
	DrawText(&g_Text.GameOver1, "Game");
	DrawText(&g_Text.GameOver2, "Over");

	// You Scored x
	char youScoredCharArray[200];
	sprintf(youScoredCharArray, "You scored %d", g_Game.Score);
	DrawText(&g_Text.YouScored, youScoredCharArray);
	
	// (flashing) "New High Score" message
	if(g_Game.NewHighScore) {
		g_Game.NewHighScoreFlash++;
		if(g_Game.NewHighScoreFlash > HIGH_SCORE_FLASH_FRAMES * 2) g_Game.NewHighScoreFlash = 0;
		if(g_Game.NewHighScoreFlash <= HIGH_SCORE_FLASH_FRAMES) {
			DrawText(&g_Text.HighCongrats1, "Congratulations");
			DrawText(&g_Text.HighCongrats2, "New High Score!");
		}
	}

}