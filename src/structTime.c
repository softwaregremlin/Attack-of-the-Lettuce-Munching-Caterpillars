
typedef struct {

	int Frame, WaveStartTime, WaveTime, Remaining, RemainingAfterWaveComplete, SinceLevelStarted, HiddenTime;
	double MsElapsedSinceLastFrame;


	unsigned int IsPaused, BonusAdded;
} timeStruct;