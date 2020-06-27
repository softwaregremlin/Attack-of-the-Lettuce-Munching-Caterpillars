void DisplayFrameRandomBonus() {

	g_RandomBonus.Flash++;
	if (g_RandomBonus.Flash >  g_RandomBonus.FlashFrames*2) g_RandomBonus.Flash = 0;
	if (g_RandomBonus.Flash <= g_RandomBonus.FlashFrames)   DrawText(&g_Text.RandomBonus, g_RandomBonus.RandomBonusMessage);

}

void DisplayFrameScoreTimeBossHits() {

	char msgArray[200];
	
	// Score
	sprintf(msgArray,   "Score %d", g_Game.Score);
	DrawText(&g_Text.Score, msgArray);

	// High Score
	if (g_Game.Score > g_Game.HighScore) {
		g_Game.HighScore = g_Game.Score;
		g_Game.NewHighScore = true;
	}
	sprintf(msgArray, "Hi %d", g_Game.HighScore);
	DrawText(&g_Text.HighScore, msgArray);
	
	// Time
	sprintf(msgArray, "Time %.1f", ((float)g_Time.Remaining/1000));	
	DrawText(&g_Text.Time, msgArray);

	// Wave
	if(g_ThisLevel.Wave > 0) {
		sprintf(msgArray, "Wave %d/%d", g_ThisLevel.Wave, g_ThisLevel.WaveCount);
		DrawText(&g_Text.Wave, msgArray);
	}
	
	// Extended Play / Wave Clear
	if(g_ThisLevel.WaveComplete) {
		DrawText(&g_Text.WaveClear, "Wave Clear!");
		
		DisplayFrameRandomBonus();
		
		//int hits = g_Room != ROOM_LEVEL4 ? g_WaveHits : g_WaveHits * 2;  (WAVE HITS)
		int accurayPercent = (int)(((float)g_ThisLevel.WaveHits / (float)g_ThisLevel.WaveSwipes) * BONUS_MULTIPLIER);
		int timeBonusPoints = ((float)g_Time.RemainingAfterWaveComplete/MS_PER_SECOND) * BONUS_MULTIPLIER;

		// Apply time bonus
		if(g_Time.BonusAdded == false) { g_Game.Score += timeBonusPoints; g_Time.BonusAdded = true; }

		// Show Wave Statistics
		sprintf(msgArray, 
			"swipes: %d\nhits: %d\naccuracy: %d%%\ncompletion time: %d sec\ntime bonus: %d", 
			g_ThisLevel.WaveSwipes, g_ThisLevel.WaveHits, accurayPercent, (int)((float)g_Time.WaveTime/MS_PER_SECOND), timeBonusPoints);

		DrawText(&g_Text.WaveStats, msgArray);
	}

	// BossMan Hits!
	if(g_ThisLevel.BossHitFrame > 0) {	
		sprintf(msgArray , "%d/%d" , g_Enemies[0].Hits, g_Enemies[0].HitsToKill);
		DrawText(&g_Text.BossHits, msgArray);
		g_ThisLevel.BossHitFrame--;
	}

	// Level Complete!
	sprintf(msgArray, g_Game.Level < g_Game.LevelCount ? "Level Clear!" : "GAME COMPLETE!");
	if(g_ThisLevel.Complete) DrawText(&g_Text.WaveClear, msgArray);
}