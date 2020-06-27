
typedef struct {

	char Name[100];

	unsigned int EnemyCount, EnemyFrameRows, EnemyFrameColumns;
	unsigned int EnemyXInterval, EnemyStepSize;
	unsigned int EnemyHides, EnemyRandomHideNumber;
	unsigned int EnemyStepPattern, EnemyYStepShift;
	unsigned int EnemyIsUndead;
	unsigned int EnemyPointsPerKill;

	float EnemyCollisionWidthRatio, EnemyCollisionHeightRatio,
		EnemyCollisionXOffsetPercent, EnemyCollisionYOffsetPercent;

	unsigned int Wave, WaveCount, WaveComplete, WaveSwipes, WaveHits;
	unsigned int TimeReplenish, Complete;
	unsigned int  IsBoss, BossHits, BossTopLimit, BossHitFrame, BossKilled;
	int BossFinalSceneTopLimit;

	int	EnemyMovingFrames[10], EnemyUndeadFrames[5],
		EnemyHidingFrames[25], EnemyDyingFrames[20],
		EnemyStepSequenceFrames[15];

} levelSettingsStruct;