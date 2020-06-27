void ShowScoreTimeBossHits()
{


	char msgArray[200];
	
	
	// scoreCharArray = {0}; timeCharArray = {}; bossHitArray = {};
	
	// High score and score display!
	
	//if(g_Score > g_UserData.HighScoore) {
	if(g_Score > g_HighScore) {
		g_HighScore = g_Score;
		//g_UserData.HighScore = g_Score;
		g_NewHighScore = true;
	}
	

	// Score
	sprintf(msgArray,   "Score %d", g_Score);	
	drawText(g_TextScore, msgArray);

	// High Score
	sprintf(msgArray, "Hi %d",    g_HighScore);	
	drawText(g_TextHighScore, msgArray);
	
	// Time
	sprintf(msgArray, "Time %.1f", ((float)g_Time/1000));	
	drawText(g_TextTime, msgArray);

	// Wave
	if(g_Wave > 0) {
		sprintf(msgArray, "Wave %d/%d", g_Wave, g_WavesThisLevel);	
		drawText(g_TextWave, msgArray);
	}
	
	// if(g_VitaPad.buttons & SCE_CTRL_RIGHT) g_timeWaveFontXPos++;
	
	
	
	// Extended Play
	//if(g_ExtendedPlayFrame > 0)
	if(g_WaveComplete)
	{
		drawText(g_TextWaveClear, "Wave Clear!");
		
		ShowRandomBonus();
		
		int hits = g_Room != ROOM_LEVEL4 ? g_WaveHits : g_WaveHits * 2;
		int accurayPercent = (int)(((float)hits/(float)g_WaveSwipes) * 100);		
		int timeBonusPoints = ((float)g_RemainingTime/1000.0) * 100;

		// Apply time bonus
		if(g_TimeBonusAdded == false) {	g_Score += timeBonusPoints; g_TimeBonusAdded = true; }

		// Show Wave Statistics
		sprintf(msgArray, 
			"swipes: %d\nhits: %d\naccuracy: %d%%\ncompletion time: %d sec\ntime bonus: %d", 
			g_WaveSwipes, hits, accurayPercent, (int)((float)g_WaveTime/1000.0), timeBonusPoints);

		drawText(g_TextWaveStats, msgArray);		
	}

	

	// BossMan Hits!
	if(g_BossHitFrame > 0) {	
		sprintf(msgArray , "%d/%d" , g_Enemies[0].Hits, g_Enemies[0].HitsToKill);
		drawText(g_TextBossHits, msgArray);
		g_BossHitFrame--;
	}

	// Level Complete!
	if(g_LevelComplete) {	
		drawText(g_TextWaveClear,"Level Clear!");
	}
}