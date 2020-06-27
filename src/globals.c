// Boolean!
#define true 1
#define false 0

// Room constants
#define ROOM_INTRO        0
#define ROOM_LEVEL        1
#define ROOM_GAMEOVER     2
#define ROOM_GAMECOMPLETE 3
#define ROOM_HIGHSCORE    4

// Game-wide settings and variables
gameStruct g_Game = {
	.Score = 0, .HighScore = 0, .NewHighScore = false, .NewHighScoreFlash = 0,
	.Room = ROOM_INTRO, .Level = 0, .LevelCount = 8, .MaxLevelReached = 1,
	.ScaleFactorDevice = 1, .LoggingActivated = false,
	.FingerOnCross = false,
	.BossDeathSettings = {.XOffsetRatio = 0.625, .Speed = 50, .MaxScale = 200, .GrowthSize = 5, .AfterFallDistance = 50 }
};

// Control Vars
#define MIN_ANALOG_STICK_THRESHOLD 50
#define MAX_ANALOG_STICK_THRESHOLD 205

// Sprite State flags
#define SPRITE_STATE_STANDING 0
#define SPRITE_STATE_MOVING   1
#define SPRITE_STATE_FIRING   2
#define SPRITE_STATE_DYING    3
#define SPRITE_STATE_DEAD     4
#define SPRITE_STATE_DANCING  5
#define SPRITE_STATE_HIDING   6
#define SPRITE_STATE_UNDEAD   7

// Sprite Direction flags
#define SPRITE_DIRECTION_UPLEFT    1
#define SPRITE_DIRECTION_UP        2
#define SPRITE_DIRECTION_UPRIGHT   3
#define SPRITE_DIRECTION_LEFT      4
#define SPRITE_DIRECTION_NONE      5
#define SPRITE_DIRECTION_RIGHT     6
#define	SPRITE_DIRECTION_DOWNLEFT  7
#define SPRITE_DIRECTION_DOWN      8
#define SPRITE_DIRECTION_DOWNRIGHT 9

// Sprites
spriteStruct g_Pitman = { 
  .Columns = 5, .CollisionRectangle = {456, 229, 114, 63, 0.9, 0.5}, 
  .XPos = 15, .YPos = 364,
  .TurnOffsetX = 100, .StepSize = 25, 
  .XMinLimitBottom = -38, .XMaxLimitBottom = 1044,
  .XMinLimitTop = -8, .XMaxLimitTop = 1200, 
  .YMinLimit = 110, .YMaxLimit = 428,
  .FlippedX = false, .ScalePercent = 100, 
  .Tick = 0,
  .State = SPRITE_STATE_STANDING,
  .Sequences[SPRITE_STATE_STANDING] = {0,-1},
  .Sequences[SPRITE_STATE_MOVING]   = {0,1,2,1,-1},
  .Sequences[SPRITE_STATE_FIRING]   = {3,4,3,-1}

};

#define ENEMY_TOP_LIMIT 160
#define ENEMY_BOTTOM_LIMIT_SCALE_FACTOR 1.2
spriteStruct g_Enemies[100]; 

// Screen vars
#define MAX_DEVICE_HEIGHT 768
// float g_scaleFactorDevice = 1;

// Stores IDs for Music Streams
musicStruct g_Music;

// Time Constants / Variables
#define MS_PER_DAY      86400000
#define MS_PER_HOUR     3600000
#define MS_PER_MINUTE   60000
#define MS_PER_SECOND   1000
#define FRAME_RATE		30
#define BOSS_HIT_FRAMES 20
#define START_TIME               30 * MS_PER_SECOND
#define LEVEL_CLEAR_PAUSE_TIME   10 * MS_PER_SECOND
#define GAME_OVER_PAUSE_TIME     7  * MS_PER_SECOND
#define GAME_OVER_HI_PAUSE_TIME  15 * MS_PER_SECOND
#define WAVE_CLEAR_PAUSE_TIME    5  * MS_PER_SECOND
#define LEVEL_INTRO_TIME         3  * MS_PER_SECOND
#define GAME_COMPLETE_SONG_TIME (3 * MS_PER_MINUTE) + (3 * MS_PER_SECOND)

#define HIGH_SCORE_FLASH_FRAMES 8
#define PITMAN_TICKS_PER_FRAME  2
#define ENEMY_TICKS_PER_FRAME   2

timeStruct g_Time = {
	.Frame=0, .WaveStartTime = START_TIME, .Remaining = START_TIME, .HiddenTime=0,
	.MsElapsedSinceLastFrame=0,
	.IsPaused = false, .BonusAdded = false
};

// Enemy Settings - per Level
levelSettingsStruct g_LevelSettings[8] = {

	// Level 1: WORMS
	{ .Name = "Worms!",
	  .Complete = false,
	  .EnemyCount = 43, .EnemyXInterval = 200, .EnemyPointsPerKill = 10,
	  .EnemyFrameRows = 1, .EnemyFrameColumns = 6,
	  .EnemyCollisionWidthRatio = 1.0, .EnemyCollisionHeightRatio = 0.85,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.3,
	  .Wave = 1, .WaveCount = 6, .WaveSwipes = 0, .WaveHits = 0, .WaveComplete = false,
	  .TimeReplenish = 34,
	  .IsBoss = false, .BossHits = 0, 
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {-1},
	  .EnemyDyingFrames = {3,4,3,4,5,4,5,4,3,4,3,4,5,4,5,4,-1},
	  .EnemyStepSequenceFrames = {-1},
	  .EnemyHides = false, .EnemyRandomHideNumber = 0,
	  .EnemyStepSize = 15,
	  .EnemyStepPattern = false, .EnemyYStepShift = 0
	},

	// Level 2: CATERPILLAR BOSS
	{ .Name = "GIANT Caterpiller!",
	  .Complete = false,
	  .EnemyCount = 1, .EnemyXInterval = 0, .EnemyPointsPerKill = 20,
	  .EnemyFrameRows = 2, .EnemyFrameColumns = 3,
	  .EnemyCollisionWidthRatio = 0.75, .EnemyCollisionHeightRatio = 0.6,
	  .EnemyCollisionXOffsetPercent = 0, .EnemyCollisionYOffsetPercent = 0.55,
	  .WaveCount = 0,
	  .TimeReplenish = 50,
	  .IsBoss = true, .BossHits = 200, .BossTopLimit = 200, .BossFinalSceneTopLimit = 0,
	  .BossHitFrame = 0, .BossKilled = false,
	  .EnemyMovingFrames = {0,1,2,3,2,1,-1},
	  .EnemyHidingFrames = {-1},
	  .EnemyDyingFrames = {4,5,-1},
	  .EnemyStepSequenceFrames = {-1},
	  .EnemyHides = false, .EnemyRandomHideNumber = 0,
	  .EnemyStepSize = 25,
	  .EnemyStepPattern = false, .EnemyYStepShift = 0
	},

	// Level 3: SNAILS!
	{ .Name = "Snails!",
	  .Complete = false,
	  .EnemyCount = 40, .EnemyXInterval = 150, .EnemyPointsPerKill = 10,
	  .EnemyFrameRows = 1, .EnemyFrameColumns = 8,
	  .EnemyCollisionWidthRatio = 1.0, .EnemyCollisionHeightRatio = 0.75,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.25,
	  .Wave = 1, .WaveCount = 8, .WaveSwipes = 0, .WaveHits = 0, .WaveComplete = false,
	  .TimeReplenish = 38,
	  .IsBoss = false, .BossHits = 120,
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {3,4,4,4,3,-1},
	  .EnemyDyingFrames  = {5,6,5,6,7,6,7,6,5,6,5,6,7,6,7,6,-1},
	  .EnemyStepSequenceFrames = {-1},
	  .EnemyHides = true, .EnemyRandomHideNumber = 35,
	  .EnemyStepSize = 15,
	  .EnemyStepPattern = false, .EnemyYStepShift = 0
	},

	// Level 4: SNAIL BOSS
	{ .Name = "GIANT Snail!",
	  .Complete = false,
	  .EnemyCount = 1, .EnemyXInterval = 0, .EnemyPointsPerKill = 20,
	  .EnemyFrameRows = 1, .EnemyFrameColumns = 7,
	  .EnemyCollisionWidthRatio = 0.75, .EnemyCollisionHeightRatio = 0.25,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.55,
	  .WaveCount = 0,
	  .TimeReplenish = 55,
	  .IsBoss = true, .BossHits = 120, .BossTopLimit = 200, .BossFinalSceneTopLimit = 0,
	  .BossHitFrame = 0, .BossKilled = false,
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {3,4,4,4,3,-1},
	  .EnemyDyingFrames = {5,6,-1},
	  .EnemyStepSequenceFrames = {-1},
	  .EnemyHides = true, .EnemyRandomHideNumber = 35,
	  .EnemyStepSize = 25,
	  .EnemyStepPattern = false, .EnemyYStepShift = 0
	},

	// Level 5: SPIDERS!
	{ .Name = "Spiders!",
	  .Complete = false,
	  .EnemyCount = 85, .EnemyXInterval = 75, .EnemyPointsPerKill = 10,
	  .EnemyFrameRows = 1, .EnemyFrameColumns = 6,
	  .EnemyCollisionWidthRatio = 1.0, .EnemyCollisionHeightRatio = 0.75,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.25,
	  .Wave = 1, .WaveCount = 10, .WaveSwipes = 0, .WaveHits = 0, .WaveComplete = false,
	  .TimeReplenish = 35,
	  .IsBoss = false,  
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {-1},
	  .EnemyDyingFrames  = {3,4,3,4,5,4,5,4,3,4,3,4,5,4,5,4,-1},
	  .EnemyStepSequenceFrames = {1,1,1,1,1,7,7,7,7,7,-1},
	  .EnemyHides = false, .EnemyRandomHideNumber = 0,
	  .EnemyStepSize = 15,
	  .EnemyStepPattern = true, .EnemyYStepShift = 15
	},

	// Level 6: SPIDER BOSS
	{ .Name = "GIANT Spider!",
	  .Complete = false,
	  .EnemyCount = 1, .EnemyXInterval = 0, .EnemyPointsPerKill = 20,
	  .EnemyFrameRows = 1, .EnemyFrameColumns = 5,
	  .EnemyCollisionWidthRatio = 1.0, .EnemyCollisionHeightRatio = 0.5,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.17,
	  .WaveCount = 0, 
	  .TimeReplenish = 60,
	  .IsBoss = true, .BossHits = 180, .BossTopLimit = 150, .BossFinalSceneTopLimit = -100,
	  .BossHitFrame = 0, .BossKilled = false,
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {-1},
	  .EnemyDyingFrames = {3,4,-1},
	  .EnemyStepSequenceFrames = {1,1,1,1,1,7,7,7,7,7,-1},
	  .EnemyHides = false, .EnemyRandomHideNumber = 35,
	  .EnemyStepSize = 20,
	  .EnemyStepPattern = true, .EnemyYStepShift = 0
	},

	// Level 7: UNDEAD CATERPILLARS!
	{ .Name = "Undead Snakes!",
	  .Complete = false,
	  .EnemyCount = 40, .EnemyXInterval = 90, .EnemyPointsPerKill = 10,
	  .EnemyFrameRows = 1, .EnemyFrameColumns = 6,
	  .EnemyCollisionWidthRatio = 1.0, .EnemyCollisionHeightRatio = 0.75,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.25,
	  .Wave = 1, .WaveCount = 12, .WaveSwipes = 0, .WaveHits = 0, .WaveComplete = false,
	  .TimeReplenish = 42,
	  .IsBoss = false, .BossHits = 0, .BossTopLimit = 0, 
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {3,4,3,4,5,4,5,4,3,4,3,4,5,4,5,4,3,0,3,0,3,0,3,0,-1},
	  .EnemyDyingFrames  = {3,4,3,4,5,4,5,4,3,4,3,4,5,4,5,4,-1},
	  .EnemyUndeadFrames = {0,1,2,1,-1},
	  .EnemyStepSequenceFrames = {-1},
	  .EnemyHides = false, .EnemyRandomHideNumber = 0,
	  .EnemyStepSize = 15,
	  .EnemyStepPattern = false, .EnemyYStepShift = 0,
	  .EnemyIsUndead = true
	},

	// Level 8: UNDEAD CATERPILLAR BOSS
	{ .Name = "GIANT Undead Snake!",
	  .Complete = false,
	  .EnemyCount = 1, .EnemyXInterval = 0, .EnemyPointsPerKill = 20,
	  .EnemyFrameRows = 2, .EnemyFrameColumns = 3,
	  .EnemyCollisionWidthRatio = 0.75, .EnemyCollisionHeightRatio = 0.35,
	  .EnemyCollisionXOffsetPercent = 0,   .EnemyCollisionYOffsetPercent = 0.7,
	  .WaveCount = 0, .TimeReplenish = 90,
	  .IsBoss = true, .BossHits = 320, .BossTopLimit = 100, .BossFinalSceneTopLimit = -100,
	  .BossHitFrame = 0, .BossKilled = false,
	  .EnemyMovingFrames = {0,1,2,1,-1},
	  .EnemyHidingFrames = {-1},
	  .EnemyDyingFrames = {3,4,5,4,-1},
	  .EnemyStepSequenceFrames = {-1},
	  .EnemyHides = false, .EnemyRandomHideNumber = 0,
	  .EnemyStepSize = 25,
	  .EnemyStepPattern = false, .EnemyYStepShift = 0,
	  .EnemyIsUndead = false
	},
};

levelSettingsStruct g_ThisLevel;



// Game Complete settings
#define BAND_TICKS_PER_FRAME 4
gameCompleteStruct g_GameCompleteSettings = {
	.ColourArray = { {255,255,0},   {255,255,34},  {255,255,68},
	 			     {255,255,102}, {255,255,136}, {255,255,176} },
	.ColourCycleOffset = 0, .RockCount = 6, .RockStep = 60, .RockYPosStep = 10, .BandFrames = 2
};

//Fonts and text positions
#define FONT_STYLE_SHADOW  		1
#define FONT_STYLE_OUTLINE 		2

#define FONT_SIZE_SMALLEST	   30 
#define FONT_SIZE_SMALL  	   36	 
#define FONT_SIZE_MEDIUM	   45
#define FONT_SIZE_MEDIUM_LARGE 60
#define FONT_SIZE_LARGE		   80
#define FONT_SIZE_LARGEST	   104
#define FONT_SIZE_COUNT		   6

#define FONT_COLOUR_1	  		 220,0,0
#define FONT_COLOUR_5	  		 180,0,0
#define FONT_COLOUR_2	  		 255,50,50
#define FONT_COLOUR_3	  		 0,0,0
#define FONT_COLOUR_4	  		 255,136,136
#define FONT_COLOUR_SHADOW 		 0,0,0
#define FONT_SHADOW_OFFSET_SMALL 2
#define FONT_SHADOW_OFFSET       4



textSettingsStruct g_Text = {

	.FontGrowth = 1, .FontSkipFrame = 0, .FontSkipFrames = 3,

	.Loading1 = { 20, 150, FONT_SIZE_MEDIUM_LARGE,	  FONT_COLOUR_1, FONT_STYLE_SHADOW,  false },
	.Loading2 = { 20, 220, FONT_SIZE_SMALL,	  FONT_COLOUR_1, FONT_STYLE_SHADOW,  false },

	.Intro1 = { -1, 15,  FONT_SIZE_SMALLEST,	  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.Intro2 = { -1, 50,  FONT_SIZE_MEDIUM,		  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.Intro3 = { -1, 95,  FONT_SIZE_MEDIUM_LARGE,  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.Intro4 = { -1, 155, FONT_SIZE_LARGE,		  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },

	.IntroStart = { -1, 350, FONT_SIZE_MEDIUM,        FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },
	.IntroLevel = { -1, 405, FONT_SIZE_SMALL,        FONT_COLOUR_5, FONT_STYLE_OUTLINE, false },

	.LevelStart1 = { -1,  70, FONT_SIZE_LARGE,		  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.LevelStart2 = { -1,  180, FONT_SIZE_MEDIUM,		  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },

	.Score = { 10,  10,  FONT_SIZE_SMALLEST,	  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },
	.HighScore = { 10,  55,  FONT_SIZE_SMALLEST,	  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },
	.Time = { 720, 10,  FONT_SIZE_SMALLEST,	  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },
	.Wave = { 720, 55,  FONT_SIZE_SMALLEST,	  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },

	.GameOver1 = { -1, 60,  FONT_SIZE_LARGEST,	  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.GameOver2 = { -1, 180, FONT_SIZE_LARGEST,	  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.YouScored = { -1, 315, FONT_SIZE_SMALL, 		  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },
	.HighCongrats1 = { -1, 355, FONT_SIZE_MEDIUM, 	  FONT_COLOUR_1, FONT_STYLE_OUTLINE, false },
	.HighCongrats2 = { -1, 405, FONT_SIZE_MEDIUM, 	  FONT_COLOUR_1, FONT_STYLE_OUTLINE, false },

	.GamePaused = { -1,120,  FONT_SIZE_LARGE,	  FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.Resume = { -1, 240, FONT_SIZE_MEDIUM,        FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },

	.WaveClear = { -1, 100, FONT_SIZE_MEDIUM_LARGE, FONT_COLOUR_1, FONT_STYLE_SHADOW,  true },
	.WaveStats = { 290, 205, FONT_SIZE_SMALL, 		  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false },

	.RandomBonus = { 270, 25,  FONT_SIZE_SMALL, 		  FONT_COLOUR_4, FONT_STYLE_OUTLINE, false },
	.BossHits = { 420, 155, FONT_SIZE_MEDIUM, 	  FONT_COLOUR_2, FONT_STYLE_OUTLINE, false }
};



#define BONUS_MULTIPLIER 100
randomBonusStruct g_RandomBonus = { 
	.RandomNumber = 0,	.RandomNumberRange = 20, .Time = 0, .Added = false, .TimeBonusAdded = false, .Flash = 0, .FlashFrames = 8,
	.RewardRanges = { {.MinLimit = 1,  .MaxLimit = 4,  .ExtraPoints = 100  },
					  {.MinLimit = 5,  .MaxLimit = 8,  .ExtraPoints = 500  },
					  {.MinLimit = 9,  .MaxLimit = 9,  .ExtraPoints = 900  },
					  {.MinLimit = 10, .MaxLimit = 10, .ExtraPoints = 1000 },
					  {.MinLimit = 11, .MaxLimit = 14, .ExtraSeconds = 1   },
					  {.MinLimit = 15, .MaxLimit = 18, .ExtraSeconds = 2   },
					  {.MinLimit = 19, .MaxLimit = 19, .ExtraSeconds = 5   },
					  {.MinLimit = 20, .MaxLimit = 20, .ExtraSeconds = 10, .IsLastRange = true }
					}
};

// Intro vars
#define INTRO_BUTTON_START 0
#define INTRO_BUTTON_LEVEL 1

introSettingsStruct g_IntroSettings = {
	.LoadingDotCount = 0,
	.TimeSinceArmMovement = 0, .ArmMovements = 0, .ArmMovementsMax = 2, .ArmMovementInterval = 1500,
	.Swiped = false, .ExplosionSoundPlayed = false, .ExplosionDelay = 50, .TimeSinceSwipe = 0,
	.StartGameTextX = 0, .StartGameTextInitialY = 0, .StartGameTextInitialSize = 0, .SelectedMenuButton = 0,
	.StartGameTextXSpeed = 20, .StartGameTextYSpeed = 5, .StartGameTextGrowth = 1, .StartGameDelay = 2000,
	.CycleMinR = 0, .CycleMaxR = 0, .CycleMinG = 50, .CycleMaxG = 140, .CycleMinB = 50, .CycleMaxB = 140, .CycleSpeed = 5,
	.NonSelectedR = 180, .NonSelectedG = 0, .NonSelectedB = 0
};