void ProcessFrameGameComplete() {

	UpdateTime();

	g_GameCompleteSettings.Band.Tick++;
	if (g_GameCompleteSettings.Band.Tick == BAND_TICKS_PER_FRAME) {

		// Animate the Band
		g_GameCompleteSettings.Band.Tick = 0;
		g_GameCompleteSettings.Band.Frame++;
		if (g_GameCompleteSettings.Band.Frame == g_GameCompleteSettings.BandFrames) {
			g_GameCompleteSettings.Band.Frame = 0;
		}

		// Cycle Colours on Background rocks
		g_GameCompleteSettings.ColourCycleOffset++;
		if (g_GameCompleteSettings.ColourCycleOffset > g_GameCompleteSettings.RockCount) g_GameCompleteSettings.ColourCycleOffset = 0;
	}

	// Exit when the time has run out
	if (g_Time.Remaining < 0) {

		g_Game.Level = 0;
		InitialiseLevel();
	}
}