
// Perform 2 arm movements every 1.5 secs
void DoIntroArmMovement() {

	if (g_IntroSettings.TimeSinceArmMovement < g_IntroSettings.ArmMovementInterval) return;
	if (g_Pitman.State == SPRITE_STATE_MOVING) return;
	if (g_IntroSettings.Swiped) return;

	g_Pitman.State = SPRITE_STATE_MOVING;
	g_IntroSettings.ArmMovements++;
	if (g_IntroSettings.ArmMovements < g_IntroSettings.ArmMovementsMax) return;
	g_IntroSettings.ArmMovements = 0;
	g_IntroSettings.TimeSinceArmMovement = 0;
}

void CycleIntroButtonColours(textStruct *selectedButton) {

	selectedButton->g += g_IntroSettings.CycleSpeed;
	selectedButton->b += g_IntroSettings.CycleSpeed;
	if (selectedButton->g > g_IntroSettings.CycleMaxG) selectedButton->g = g_IntroSettings.CycleMinG;
	if (selectedButton->b > g_IntroSettings.CycleMaxB) selectedButton->b = g_IntroSettings.CycleMinB;
}

void ResetIntroButtonColours(textStruct* nonSelectedButton) {
	nonSelectedButton->r = g_IntroSettings.NonSelectedR;
	nonSelectedButton->g = g_IntroSettings.NonSelectedG;
	nonSelectedButton->b = g_IntroSettings.NonSelectedB;
}

void ProcessFrameIntro() {

	UpdateTimeIntro();
	DoIntroArmMovement();
	AnimatePitman();

	// Cycle colours on the selected button
	CycleIntroButtonColours(g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START ? &g_Text.IntroStart : &g_Text.IntroLevel);
	ResetIntroButtonColours(g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START ? &g_Text.IntroLevel : &g_Text.IntroStart);

	// Change Buttons (if Change Level is available)
	if (g_Game.MaxLevelReached > 1 &&
		!(g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START && g_IntroSettings.Swiped) &&
		((InputDown() && g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START) ||
		 (InputUp()   && g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_LEVEL))) {
		g_IntroSettings.SelectedMenuButton = !g_IntroSettings.SelectedMenuButton;
		SoundPlaySample(g_SoundSamples.SwipeSound);
		g_IntroSettings.TimeSinceSwipe = 0;
		g_IntroSettings.Swiped = 0;
	}

	// Fire button - Swipe the selected button
	if (InputCrossPressed() && !g_Game.FingerOnCross) {
		g_IntroSettings.Swiped = true;
		CheckButtonAndSwipe();

		// Increment the selected level, cycling at the maximum
		if (g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_LEVEL) {
			if (g_Game.Level == g_Game.MaxLevelReached - 1) {
				g_Game.Level = 0;
			}
			else {
				g_Game.Level++;
			}
		}
	}

	// Flag to enforce repeated fire button presses
	if (!(InputCrossPressed())) g_Game.FingerOnCross = false;

	// Explosion sound (delay so the swipe can be heard first)
	if (g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START && !g_IntroSettings.ExplosionSoundPlayed &&
		g_IntroSettings.TimeSinceSwipe > g_IntroSettings.ExplosionDelay) {
		SoundPlaySample(g_SoundSamples.ExplosionSound);
		g_IntroSettings.ExplosionSoundPlayed = true;
	}

	// Move / Animate text (Start Game)
	if (g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START && g_IntroSettings.Swiped) {
		g_Text.IntroStart.xPos += g_IntroSettings.StartGameTextXSpeed;
		g_Text.IntroStart.yPos -= g_IntroSettings.StartGameTextYSpeed;
		g_Text.IntroStart.size += g_IntroSettings.StartGameTextGrowth;
	}

	// Start Game
	if(g_IntroSettings.SelectedMenuButton == INTRO_BUTTON_START && 
	   g_IntroSettings.TimeSinceSwipe >= g_IntroSettings.StartGameDelay) {		

		// CHEAT / TESTING MODE = externalised
		FILE* dataFile;
		if ((dataFile = fopen(g_DataPaths.CheatMode, "r"))) {
			fscanf(dataFile, "%d", &g_Game.TestMode);
			fclose(dataFile);
		}
		
		if (g_Game.TestMode) {
			for (unsigned int level = 0; level < g_Game.LevelCount; level++) {
				// Waves
				if (level % 2 == 0) {
					g_LevelSettings[level].WaveCount = 2;
					g_LevelSettings[level].EnemyCount = 5;
				}
				g_LevelSettings[level].TimeReplenish = 15;
				g_LevelSettings[level].BossHits = 10;
			}			
		}
		//

		g_Game.Score = 0;
		InitialiseLevel();
	}
}