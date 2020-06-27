
void UpdateTime() {

	if (g_Time.IsPaused) return;

	g_Time.Remaining -= g_Time.MsElapsedSinceLastFrame;
	g_Time.SinceLevelStarted += g_Time.MsElapsedSinceLastFrame;

	// Test mode - allow time to run out quickly
	if (g_Game.TestMode && InputCirclePressed()) {
		g_Time.Remaining -= 1000;
	}
}

void UpdateHiddenTime() {
	if (g_Time.IsPaused) return;
	g_Time.HiddenTime -= g_Time.MsElapsedSinceLastFrame;
}

void UpdateTimeIntro() {
	g_IntroSettings.TimeSinceArmMovement += g_Time.MsElapsedSinceLastFrame;
	if(g_IntroSettings.Swiped) g_IntroSettings.TimeSinceSwipe += g_Time.MsElapsedSinceLastFrame;
}

