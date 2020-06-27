void ProcessFrameGameOver() {

	UpdateTime();

	if (g_Time.Remaining <= 0) {

		// SoundStopBackgroundMusic();

		g_Game.NewHighScore = false;
		InitialiseIntro();
	}
}