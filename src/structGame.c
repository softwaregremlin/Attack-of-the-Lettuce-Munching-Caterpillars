
typedef struct {
	float XOffsetRatio;
	unsigned int Speed, MaxScale, GrowthSize, AfterFallDistance;
} bossDeathSequenceStruct;

typedef struct {
	unsigned int Score, HighScore, NewHighScore, NewHighScoreFlash;
	unsigned int Room, Level, LevelCount, MaxLevelReached;
	unsigned int FingerOnCross;
	unsigned int TestMode, LoggingActivated, LevelLoadCounter;
	float ScaleFactorDevice;
	bossDeathSequenceStruct BossDeathSettings;
} gameStruct;