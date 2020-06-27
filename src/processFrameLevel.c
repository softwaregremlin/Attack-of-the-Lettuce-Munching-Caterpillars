unsigned int AllEnemiesDead(int enemyCount) {
	for (int ee = 0; ee < enemyCount; ee++) {
		if (g_Enemies[ee].State != SPRITE_STATE_DEAD &&
			g_Enemies[ee].State != SPRITE_STATE_DYING) return false;
	}
	return true;
}

void CheckEnemyCollision(int index) {
	if (CollisionWithEnemy(index)) {
		// Play sound effect!
		SoundPlaySample(g_SoundSamples.HitSound);
		// TODO - use a fresh channel each time		

		// Increase score
		g_Game.Score += g_ThisLevel.EnemyPointsPerKill;
		if (g_Game.Score > g_Game.HighScore) {
			g_Game.HighScore = g_Game.Score;
			g_Game.NewHighScore = true;
		}

		// Boss Man
		if (g_Enemies[index].IsBoss) {
			g_ThisLevel.BossHitFrame = BOSS_HIT_FRAMES;
			g_Enemies[0].IsHit = 1;
			g_Enemies[0].Hits++;

			// Bossman has been killed!
			if (g_Enemies[0].Hits == g_Enemies[0].HitsToKill) {

				g_ThisLevel.BossKilled = true;
				// Explosion sound!!
				SoundPlaySample(g_SoundSamples.ExplosionSound);

				g_Enemies[0].State = SPRITE_STATE_DYING;
				g_Enemies[0].Frame = -1;

				g_Enemies[0].StepSize = (int)(g_Game.ScaleFactorDevice * g_Game.BossDeathSettings.Speed);

				g_Enemies[0].DestinationX = SCREEN_WIDTH / 2 - (int)((float)g_Enemies[0].Width * g_Game.BossDeathSettings.XOffsetRatio);
				g_Enemies[0].DestinationY = g_ThisLevel.BossFinalSceneTopLimit;
			}
			return;
		}

		// Special case for undead - come back to life...
		if (g_Enemies[index].EnemyIsUndead) {

			// First life - go into "hiding state" (fake death)
			if (g_Enemies[index].State == SPRITE_STATE_MOVING) {
				g_Enemies[index].State = SPRITE_STATE_HIDING;
			}

			// Second life - go into actual dying state
			if (g_Enemies[index].State == SPRITE_STATE_UNDEAD) {
				g_Enemies[index].State = SPRITE_STATE_DYING;
			}
			return;
		}

		// Normal case - go to dying state
		g_Enemies[index].State = SPRITE_STATE_DYING;
		g_Enemies[index].Frame = -1;
	}
}

void CheckWaveComplete() {

	if (AllEnemiesDead(g_ThisLevel.EnemyCount) && !g_ThisLevel.WaveComplete) {
		g_ThisLevel.WaveComplete = true;

		// 5 second pause
		g_Time.HiddenTime = WAVE_CLEAR_PAUSE_TIME;

		// Calculate time to complete
		// for display of statistics
		g_Time.WaveTime = g_Time.WaveStartTime - g_Time.Remaining;
		g_Time.RemainingAfterWaveComplete = g_Time.Remaining;

		// Random Bonus!
		CalculateRandomBonus();

		// Siren sound
		SoundPlaySample(g_SoundSamples.NextWaveSound);
	}
}

void CheckLaunchNextWaveOrLevel() {
	if (!(g_ThisLevel.WaveComplete && g_Time.HiddenTime <= 0)) return;

	// Last Wave - Launch Boss Man Level
	if (g_ThisLevel.Wave + 1 > g_ThisLevel.WaveCount) {
		g_ThisLevel.WaveComplete = false;
		InitialiseLevel();
		return;
	}

	// Launch the Next Wave
	InitialiseWave();
	for (unsigned int ee = 0; ee < g_ThisLevel.EnemyCount; ee++) InitialiseEnemy(ee);
	
}

void CheckStartOfHidingSequence(int index) {

	// Flag must be set, and must be moving (not already hiding)
	if (!(g_Enemies[index].EnemyHides && g_Enemies[index].State == SPRITE_STATE_MOVING)) return;

	// Check for a random match
	unsigned int enemyHideRand = 0;
	randMinMax(1, g_Enemies[index].EnemyRandomHideNumber, &enemyHideRand);
	if (enemyHideRand == 3) {
		g_Enemies[index].State = SPRITE_STATE_HIDING;
		g_Enemies[index].StepsMoved = 0;
		g_Enemies[index].Frame = 0;
	}	
}

void CheckEndOfHidingSequence(int index) {
	// End of Hiding sequence
	if (g_Enemies[index].State != SPRITE_STATE_HIDING) return;

	// Undead - come back to second life
	if (g_Enemies[index].EnemyIsUndead) {
		g_Enemies[index].State = SPRITE_STATE_UNDEAD;
		g_Enemies[index].Frame = 0;
	}
	else {
		// Non - Undead (e.g. Snails) - go back to moving
		g_Enemies[index].State = SPRITE_STATE_MOVING;
	}	
}

void CheckStartOfDeathSequenceBoss(int index) {

	// Death sequence for the BOSS MAN
	if (!(g_Enemies[index].IsBoss && g_Enemies[index].State == SPRITE_STATE_DYING)) return;

	// Grow the sprite
	if (g_Enemies[index].ScalePercent < (int)g_Game.BossDeathSettings.MaxScale) g_Enemies[index].ScalePercent += 5;

	// Fall to the bottom of the screen
	if (g_Enemies[index].ScalePercent >= (int)g_Game.BossDeathSettings.MaxScale &&
		g_Enemies[index].XPos == g_Enemies[index].DestinationX &&
		g_Enemies[index].YPos == g_Enemies[index].DestinationY){
		g_Enemies[index].DestinationY = SCREEN_HEIGHT + g_Game.BossDeathSettings.AfterFallDistance;
	}

	// Falling complete - Go to "Level Complete"
	if (g_Enemies[0].YPos > SCREEN_HEIGHT) {
		if (!g_ThisLevel.Complete) {
			g_ThisLevel.Complete = true;
			//SaveLevelProgress();

			// Play some music!
			// SoundLoadBackgroundMusic("bossmusic.ogg");
			SoundStartBackgroundMusicLoop(g_Music.LevelComplete);

			// show the "level clear message" for 15s
			g_Time.HiddenTime = LEVEL_CLEAR_PAUSE_TIME;
		}
	}

	// Step right
	if (g_Enemies[index].XPos < g_Enemies[index].DestinationX) {
		if (g_Enemies[index].DestinationX - g_Enemies[index].XPos < g_Enemies[index].StepSize) {
			g_Enemies[index].XPos = g_Enemies[index].DestinationX;
		}
		else{
			g_Enemies[index].XPos += g_Enemies[index].StepSize;
		}
	}

	// Step left
	if (g_Enemies[index].XPos > g_Enemies[index].DestinationX) {
		if (g_Enemies[index].XPos - g_Enemies[index].DestinationX < g_Enemies[index].StepSize) {
			g_Enemies[index].XPos = g_Enemies[index].DestinationX;
		}
		else{
			g_Enemies[0].XPos -= g_Enemies[0].StepSize;
		}
	}

	// Step up
	if (g_Enemies[0].YPos < g_Enemies[0].DestinationY){
		if (g_Enemies[0].DestinationY - g_Enemies[0].YPos < g_Enemies[0].StepSize){
			g_Enemies[0].YPos = g_Enemies[0].DestinationY;
		}
		else{
			g_Enemies[0].YPos += g_Enemies[0].StepSize;
		}
	}

	// Step down
	if (g_Enemies[0].YPos > g_Enemies[0].DestinationY) {
		if (g_Enemies[0].YPos - g_Enemies[0].DestinationY < g_Enemies[0].StepSize) {
			g_Enemies[0].YPos = g_Enemies[0].DestinationY;
		}
		else{
			g_Enemies[0].YPos -= g_Enemies[0].StepSize;
		}
	}	
}

void CheckEndOfDeathSequenceBoss(int index) {

	// Compeleted a Boss-Man Level 
	if (!(g_ThisLevel.IsBoss && g_ThisLevel.Complete && g_Time.HiddenTime <= 0)) return;

	// SoundStopBackgroundMusic();
	g_ThisLevel.Complete = false;
	g_ThisLevel.BossKilled = false;

	// WriteLog("CheckEndOfDeathSequenceBoss - InitialiseLevel");
	InitialiseLevel();
	return;
}

void CheckEndOfDeathSequenceNonBoss(int index) {
	if (g_ThisLevel.IsBoss || g_Enemies[index].State != SPRITE_STATE_DYING) return;

	g_Enemies[index].State = SPRITE_STATE_DEAD;

	// WAVE COMPLETE?					
	CheckWaveComplete();
}

void RandomiseBossYPossAfterWrap(int index) {
	// Boss Man - randomise Y Position
	if (!g_Enemies[index].IsBoss) return;

	int topLimit = (int)(g_Game.ScaleFactorDevice * g_Enemies[index].BossTopLimit);
	int bottomLimit =
		SCREEN_HEIGHT - (int)(ENEMY_BOTTOM_LIMIT_SCALE_FACTOR * g_Enemies[index].Height);

	unsigned int yPos = 0;
	randMinMax(topLimit, bottomLimit, &yPos);

	g_Enemies[index].YPos = yPos;
}

void MoveEnemyStandard(int index) {

	// Standard movement - step from right to left
	if (g_Enemies[index].XPos > g_Enemies[index].DestinationX) {
		g_Enemies[index].XPos -= g_Enemies[index].StepSize;
		g_Enemies[index].StepsMoved++;
		return;
	}

	// Wrap!	
	g_Enemies[index].XPos = SCREEN_WIDTH + g_Enemies[index].Width;
	RandomiseBossYPossAfterWrap(index);
}


void MoveEnemyStepPattern(int index) {

	g_Enemies[index].Step++;
	if (g_Enemies[index].StepSequences[SPRITE_STATE_MOVING][g_Enemies[index].Step] == -1) {
		g_Enemies[index].Step = 0;
	}

	int stepDirection =
		g_Enemies[index].StepSequences[SPRITE_STATE_MOVING][g_Enemies[index].Step];

	// Step left
	if (stepDirection == SPRITE_DIRECTION_LEFT ||
		stepDirection == SPRITE_DIRECTION_UPLEFT ||
		stepDirection == SPRITE_DIRECTION_DOWNLEFT) {
		g_Enemies[index].XPos -= g_Enemies[index].StepSize;
	}

	// Step up
	if (stepDirection == SPRITE_DIRECTION_UPLEFT ||
		stepDirection == SPRITE_DIRECTION_UP ||
		stepDirection == SPRITE_DIRECTION_UPRIGHT) {
		g_Enemies[index].YPos -= g_Enemies[index].StepSize;
	}

	// Step down
	if (stepDirection == SPRITE_DIRECTION_DOWNLEFT ||
		stepDirection == SPRITE_DIRECTION_DOWN ||
		stepDirection == SPRITE_DIRECTION_DOWNRIGHT) {
		g_Enemies[index].YPos += g_Enemies[index].StepSize;
	}

	// Edge of screen reached - wrap!
	if (g_Enemies[index].XPos <= g_Enemies[index].DestinationX) {
		g_Enemies[index].XPos = SCREEN_WIDTH + g_Enemies[index].Width;
		RandomiseBossYPossAfterWrap(index);
	}
}

void MoveEnemy(int index) {

	// Must be in a moving state
	if(!(g_Enemies[index].State == SPRITE_STATE_MOVING ||
		g_Enemies[index].State == SPRITE_STATE_UNDEAD)) return;

	// Standard Movement
	if (!g_Enemies[index].EnemyStepPattern) {
		MoveEnemyStandard(index);
	}
	else {
		// Step Patterns
		MoveEnemyStepPattern(index);
	}
}

void ProcessFrameEnemy(int index) {
	
	// Enemy has been hit?
	CheckEnemyCollision(index);	

	g_Enemies[index].Tick++;
	if(g_Enemies[index].Tick == ENEMY_TICKS_PER_FRAME) {

		// Animation
		g_Enemies[index].Tick = 0;
		g_Enemies[index].Frame++;

		// End of current sequence
		if(g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] == -1) {
			g_Enemies[index].Frame = 0;

			// End of Hiding sequence
			CheckEndOfHidingSequence(index);

			// End of death sequence (non-Boss levels)
			CheckEndOfDeathSequenceNonBoss(index);
		}
		
		// STATISTICS DISPLAY FINISHED - next wave!
		CheckLaunchNextWaveOrLevel();
	}

	// Movement / Hiding
	MoveEnemy(index);
	CheckStartOfHidingSequence(index);

	// Death Sequence for Boss Man
	CheckStartOfDeathSequenceBoss(index);
	CheckEndOfDeathSequenceBoss(index);
}

void ProcessFrameLevel() {

	// Pause / Resume game!
	if(InputStartPressed() && !g_Time.IsPaused) g_Time.IsPaused = true;
	if(InputCrossPressed() && g_Time.IsPaused)  g_Time.IsPaused = false;
	if (g_Time.IsPaused) return;

	// Check if the time has run out! - but stop counting if all worms are dead
	if(!AllEnemiesDead(g_ThisLevel.EnemyCount)) UpdateTime();

	// End of Wave or Level
	if(g_ThisLevel.WaveComplete || g_ThisLevel.Complete) UpdateHiddenTime();

	// Game Over LOAD TESTING!
	if (g_Time.Remaining < 0) InitialiseGameOver();
	//if (g_Time < 0) InitialiseLevel();

	// Movement / animation
	MovePitman();
	for (unsigned int ee = 0; ee < g_ThisLevel.EnemyCount; ee++) ProcessFrameEnemy(ee);


}