int CalculatePitmanXMaxLimit() {
	// The x limit up the top has to be bigger than down the bottom
	// Due to the sprite scaling
	float xLimitScaleFactor = (float)(g_Pitman.XMaxLimitTop - g_Pitman.XMaxLimitBottom) / 
							  (float)(g_Pitman.YMaxLimit - g_Pitman.YMinLimit);
	return g_Pitman.XMaxLimitBottom + 
			(int)((float)(g_Pitman.YMaxLimit - g_Pitman.YPos) * xLimitScaleFactor);
}

int CalculatePitmanXMinLimit() {
	// The x limit up the top has to be smaller than down the bottom
	// Due to the sprite scaling
	float xLimitScaleFactor = (float)(g_Pitman.XMinLimitBottom - g_Pitman.XMinLimitTop) / 
							  (float)(g_Pitman.YMaxLimit - g_Pitman.YMinLimit);
	return g_Pitman.XMinLimitTop + 
			(int)((float)(g_Pitman.YPos - g_Pitman.YMinLimit) * xLimitScaleFactor);
}


void CheckStickAndMove() {

	// No Josystick movement - do nothing
	int stickLeft = InputLeft(), stickRight = InputRight(),
		stickUp = InputUp(), stickDown = InputDown();

	if(!stickLeft && !stickRight && !stickUp && !stickDown) return;

	if (InputLeft())  g_Pitman.XPos -= g_Pitman.StepSize;
	if (InputRight()) g_Pitman.XPos += g_Pitman.StepSize;
	
	if(stickLeft)  { g_Pitman.XPos -= g_Pitman.StepSize; g_Pitman.FlippedX = true;  }
	if(stickRight) { g_Pitman.XPos += g_Pitman.StepSize; g_Pitman.FlippedX = false; }
	
	if(stickUp) { 
		g_Pitman.YPos -= g_Pitman.StepSize;
		// Due to the scaling, adjust the sprite to the right to keep it centered
		if(!(stickRight || stickLeft) && g_Pitman.YPos > g_Pitman.YMaxLimit) g_Pitman.XPos += g_Pitman.StepSize / 2;
	}
	if(stickDown) {
		g_Pitman.YPos += g_Pitman.StepSize;	
		// Due to the scaling, adjust the sprite to the left to keep it centered
		if(!(stickRight || stickLeft) && g_Pitman.YPos < g_Pitman.YMinLimit) g_Pitman.XPos -= g_Pitman.StepSize / 2;		
	}
	
	// Enforce screen boundaries
	int xMaxLimit = CalculatePitmanXMaxLimit(), xMinLimit =  CalculatePitmanXMinLimit();
	if(g_Pitman.XPos > xMaxLimit) g_Pitman.XPos = xMaxLimit;
	if(g_Pitman.XPos < xMinLimit) g_Pitman.XPos =  xMinLimit;
	if(g_Pitman.YPos > g_Pitman.YMaxLimit) g_Pitman.YPos = g_Pitman.YMaxLimit;
	if(g_Pitman.YPos < g_Pitman.YMinLimit) g_Pitman.YPos = g_Pitman.YMinLimit;	
	
	// Set flag to start or continue animation
	g_Pitman.State = SPRITE_STATE_MOVING;
	
	// Play the stepping sound
	if(!(g_ThisLevel.WaveComplete || g_ThisLevel.BossKilled)) SoundPlaySample(g_SoundSamples.StepSound);
}

void CheckButtonAndSwipe() {

	if(g_ThisLevel.WaveComplete || g_ThisLevel.BossKilled) return;
	
	// Fire button - launch swipe
	if (InputCrossPressed() && !g_Game.FingerOnCross && g_Pitman.State != SPRITE_STATE_FIRING) {
		
		SoundPlaySample(g_SoundSamples.SwipeSound);
		g_Pitman.Frame = 0;
		g_Pitman.State = SPRITE_STATE_FIRING;	
		g_Game.FingerOnCross = true;
		g_ThisLevel.WaveSwipes++;
	}
	
	// Flag to enforce repeated fire button presses
	if(!(InputCrossPressed())) g_Game.FingerOnCross = false;
}

// Animation (moving or swiping)
void AnimatePitman() {

	g_Pitman.Tick++;
	if(g_Pitman.Tick == PITMAN_TICKS_PER_FRAME) {

		g_Pitman.Tick = 0;
		g_Pitman.Frame++;		
		
		if(g_Pitman.Sequences[g_Pitman.State][g_Pitman.Frame] == -1) {
			g_Pitman.Frame = 0;
			g_Pitman.State = SPRITE_STATE_STANDING;
		}
	}	
}

void MovePitman()
{
	// Joystick movement - can move if we're not swiping
	if(g_Pitman.State != SPRITE_STATE_FIRING) CheckStickAndMove();

	// Swiping - can swipe if we're moving or standing still
	CheckButtonAndSwipe();
	
	// Animation
	AnimatePitman();

	// if (InputTrianglePressed()) ActivateLogging();	
}