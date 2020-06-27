// TODO - move to a "utils" include
void randMinMax(unsigned int min, unsigned int max, unsigned int* randNum) {
	int range = max - min;
	*randNum = rand() % range + min;
}

// Load time from a hidden file for testing
void LoadTestTimeFromFile() {
	FILE* dataFile;
	if ((dataFile = fopen(g_DataPaths.WaveTime, "r"))) {
		fscanf(dataFile, "%d", &g_Time.Remaining);
		g_Time.Remaining = g_Time.Remaining * MS_PER_SECOND;
		fclose(dataFile);
	}
}

// Helper fn
void ResetLevelTime() {
	g_Time.Remaining = (g_LevelSettings[g_Game.Level - 1].TimeReplenish * MS_PER_SECOND);
	LoadTestTimeFromFile();
}

// Load a sequence of frames into the enemy sprite's strycture
void InitialiseEnemyFrames(int index, int frameArray[], int state) {
	int frameIndex = 0,	frame = 0;
	while (frame > -1) {
		frame = frameArray[frameIndex];
		g_Enemies[index].Sequences[state][frameIndex] = frame;
		frameIndex++;
	}
}

// Load a sequence of frames into the enemy sprite's strycture
void InitialiseEnemyStepSequence(int index, int frameArray[], int state) {
	int frameIndex = 0, frame = 0;
	while (frame > -1) {
		frame = frameArray[frameIndex];
		g_Enemies[index].StepSequences[state][frameIndex] = frame;
		frameIndex++;
	}
}

// Load the level's enemy settings into the enemy's sprite structures
void InitialiseEnemy(int index) {

	// NOTE: yPos = before scaling
	// g_Enemies[index].FrameCount = g_ThisLevel.EnemyFrameCount;
	g_Enemies[index].Rows       = g_ThisLevel.EnemyFrameRows;
	g_Enemies[index].Columns    = g_ThisLevel.EnemyFrameColumns;

	g_Enemies[index].UnScaledFrameHeight = GetImageHeight(g_Images.Enemy[g_Game.Level -1]) / g_Enemies[index].Rows;
	g_Enemies[index].UnScaledFrameWidth  = GetImageWidth (g_Images.Enemy[g_Game.Level -1]) / g_Enemies[index].Columns;

	g_Enemies[index].Width  = (int)(g_Game.ScaleFactorDevice * g_Enemies[index].UnScaledFrameWidth);
	g_Enemies[index].Height = (int)(g_Game.ScaleFactorDevice * g_Enemies[index].UnScaledFrameHeight);

	// Collision rectangle
	g_Enemies[index].CollisionRectangle.width  = (int)(g_ThisLevel.EnemyCollisionWidthRatio  * g_Enemies[index].Width);
	g_Enemies[index].CollisionRectangle.height = (int)(g_ThisLevel.EnemyCollisionHeightRatio * g_Enemies[index].Height);
	g_Enemies[index].CollisionRectangle.x = (int)(g_ThisLevel.EnemyCollisionXOffsetPercent * g_Enemies[index].Width);
	g_Enemies[index].CollisionRectangle.y = (int)(g_ThisLevel.EnemyCollisionYOffsetPercent * g_Enemies[index].Height);

	g_Enemies[index].XPos = SCREEN_WIDTH + g_Enemies[index].Width +
		(int)(g_Game.ScaleFactorDevice * g_ThisLevel.EnemyXInterval * index);


	// Random y position	
	int topLimit = (int)(g_Game.ScaleFactorDevice * ENEMY_TOP_LIMIT),
		bottomLimit = SCREEN_HEIGHT -
		(int)(ENEMY_BOTTOM_LIMIT_SCALE_FACTOR * g_Enemies[index].Height);
	unsigned int yPos = 0;
	randMinMax(topLimit, bottomLimit, &yPos);

	g_Enemies[index].YPos = yPos;

	g_Enemies[index].DestinationX = -g_Enemies[index].Width;
	g_Enemies[index].DestinationY =  g_Enemies[index].YPos;

	g_Enemies[index].StepSize = (int)(g_Game.ScaleFactorDevice * g_ThisLevel.EnemyStepSize);
	g_Enemies[index].FlippedX = 0;
	g_Enemies[index].ScalePercent = 100;
	g_Enemies[index].MinScale = 30;

	g_Enemies[index].Frame = 0;
	g_Enemies[index].Tick = 0;
	g_Enemies[index].State = SPRITE_STATE_MOVING;

	// Frames
	InitialiseEnemyFrames(index, g_ThisLevel.EnemyMovingFrames, SPRITE_STATE_MOVING);
	InitialiseEnemyFrames(index, g_ThisLevel.EnemyHidingFrames, SPRITE_STATE_HIDING);
	InitialiseEnemyFrames(index, g_ThisLevel.EnemyDyingFrames,  SPRITE_STATE_DYING);
	InitialiseEnemyFrames(index, g_ThisLevel.EnemyUndeadFrames, SPRITE_STATE_UNDEAD);

	// Step Sequences
	InitialiseEnemyStepSequence(index, g_ThisLevel.EnemyStepSequenceFrames, SPRITE_STATE_MOVING);
	
	// Hiding
	g_Enemies[index].EnemyHides = g_ThisLevel.EnemyHides;
	g_Enemies[index].EnemyRandomHideNumber = g_ThisLevel.EnemyRandomHideNumber;

	// Step Pattern
	g_Enemies[index].EnemyStepPattern = g_ThisLevel.EnemyStepPattern;

	//UnDead
	g_Enemies[index].EnemyIsUndead = g_ThisLevel.EnemyIsUndead;

	// Boss
	g_Enemies[index].IsBoss       = g_ThisLevel.IsBoss;
	g_Enemies[index].HitsToKill   = g_ThisLevel.BossHits;
	g_Enemies[index].BossTopLimit = g_ThisLevel.BossTopLimit;
	g_Enemies[index].Hits = 0;
}

// Start a new wave
void InitialiseWave() {
	g_ThisLevel.WaveComplete = false;
	g_ThisLevel.WaveSwipes = 0;
	g_RandomBonus.Added = false;
	g_Time.BonusAdded = false;

	SaveHighScore();

	/////////////////////////////////////
	// Restart wave
	g_ThisLevel.Wave++;

	// Reset back to level replenish time
	ResetLevelTime();

	// Random Bonus Time!
	g_Time.Remaining += g_RandomBonus.Time;
	g_RandomBonus.Time = 0;
	g_Time.WaveStartTime = g_Time.Remaining;

	// Music
	// SoundStopBackgroundMusic();
	// SoundLoadBackgroundMusic("gameover.ogg");
	// SoundStartBackgroundMusic(	// SoundLoadBackgroundMusic("gameover.ogg");
	SoundStartBackgroundMusic(g_Music.LevelStartAndGameOver,1);
}

void InitialiseLevel() {

	//TESTING!!!!
	if(g_Game.TestMode) g_Game.LevelLoadCounter++;

	// Advance to the next Level, fetch settings
	g_Game.Level++;
	g_Game.Room = ROOM_LEVEL;

	// Time Counter
	g_Time.SinceLevelStarted = 0;

	// Save our progress
	SaveHighScore();
	SaveLevelProgress();

	// Completed the game!
	if (g_Game.Level > g_Game.LevelCount) {
		InitialiseGameComplete();
		return;
	}

	g_ThisLevel = g_LevelSettings[g_Game.Level - 1];

	// Start from the 1st Wave (non Boss levels)	
	g_ThisLevel.Wave = g_ThisLevel.IsBoss ? 0 : 1;

	// Set Time
	ResetLevelTime();
	g_Time.Remaining += MS_PER_SECOND;
	g_Time.WaveStartTime = g_Time.Remaining;

	// Set Statistics Vars
	g_ThisLevel.WaveHits = g_ThisLevel.EnemyCount;

	// Initialise the Enemies
	for (unsigned int ee = 0; ee < g_ThisLevel.EnemyCount; ee++) InitialiseEnemy(ee);

	// Music for the beginning of the level
	SoundStartBackgroundMusic(g_Music.LevelStartAndGameOver, 1);
}