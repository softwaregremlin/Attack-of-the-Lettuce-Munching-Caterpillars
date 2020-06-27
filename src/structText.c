typedef struct {
	int xPos, yPos;
	unsigned int size, r, g, b, style, isPulsating, initialSize;
} textStruct;

typedef struct {
	unsigned int FontGrowth, FontSkipFrame, FontSkipFrames;
	textStruct Loading1, Loading2,
		Intro1, Intro2, Intro3, Intro4, IntroStart,
		IntroLevel, LevelStart1, LevelStart2,
		Score, HighScore, Time, Wave,
		GameOver1, GameOver2, YouScored, HighCongrats1, HighCongrats2,
		GamePaused, Resume,
		WaveClear, WaveStats,
		RandomBonus, BossHits;
} textSettingsStruct;
