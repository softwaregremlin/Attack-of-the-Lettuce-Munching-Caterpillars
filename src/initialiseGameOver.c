void InitialiseGameOver() {
	g_Game.Room = ROOM_GAMEOVER;

	// SoundLoadBackgroundMusic("gameover.ogg");
	SoundStartBackgroundMusicLoop(g_Music.LevelStartAndGameOver);

	SaveHighScore();

	// display the game over screen (longer for new high score)
	g_Time.Remaining = GAME_OVER_PAUSE_TIME;
	if (g_Game.NewHighScore) g_Time.Remaining = GAME_OVER_HI_PAUSE_TIME;
}