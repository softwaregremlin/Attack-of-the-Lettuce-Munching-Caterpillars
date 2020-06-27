
int ScalePercentCalculate(int yPos) {
	// Scaling
	// area in which scaling applies
	int scaleArea = SCREEN_HEIGHT - g_Pitman.Height;
	
	// Percent to scale 0-100
	int scalePercent = scaleArea == 0 ? 0 : yPos * 100 / scaleArea;

	// Factor to minimum scale, e.g. 0 becomes 30%
	int result = g_Pitman.MinScale + (scalePercent * (100 - g_Pitman.MinScale)/100);
	if(result > 100) result = 100;
	
	return result;
	//return 100;
}

void BlitBackground() {	

	// Intro - level hasn't been incremented yet
	unsigned int level = g_Game.Level;
	if (g_Game.Room == ROOM_INTRO) level++;
	
	int backgroundIndex = (level + 1) / 2;
	// Game complete level - use last level's background
	if (level > g_Game.LevelCount) backgroundIndex--;

	BlitImage(g_Images.Background[backgroundIndex-1], 0, 0);
	//BlitImageRegionTinted(g_Images.Background[backgroundIndex-1], 0, 0,0,0,960, 544, 1.75, 1.75,255,255,255);
}



void BlitPitman() {
	
	// Set the scale
	if(!g_Pitman.IgnoreScale) g_Pitman.ScalePercent = ScalePercentCalculate(g_Pitman.YPos);

	// Flipping
	float xPos = g_Pitman.FlippedX ? 
		(float)g_Pitman.XPos  + ((((float)g_Pitman.ScalePercent / 100.0)*(float)g_Pitman.UnScaledFrameWidth) * 0.64) : 
		(float)g_Pitman.XPos;
	float xScale = (g_Pitman.FlippedX ? -1.0 : 1.0) * ((float)g_Pitman.ScalePercent / 100.0);
	
	BlitImageRegion(g_Images.Player,
		xPos, (float)g_Pitman.YPos,
		(float)(g_Pitman.Sequences[g_Pitman.State][g_Pitman.Frame] * g_Pitman.UnScaledFrameWidth), 0,
		(float)g_Pitman.UnScaledFrameWidth, (float)g_Pitman.UnScaledFrameHeight,
		xScale, ((float)g_Pitman.ScalePercent / 100.0));	
}


void BlitEnemy(int index) {

	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;

	 ///////////////////////////////////////////////////////////////
	if (g_Enemies[index].XPos < 0 - g_Enemies[index].Width) return;	
	///////////////////////////////////////////////////////////////

	// Set the scale (Exception is Boss Death Sequence)
	if (!(g_Enemies[index].IsBoss && g_Enemies[index].State == SPRITE_STATE_DYING)) {
		g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);
	}

	// For large images we need to have rows and columns
	int column = g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] % 
			     g_Enemies[index].Columns,
		row = g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] / 
			  g_Enemies[index].Columns;

	// Tinting for Boss Hits
	int tintR = 255, tintG = 255, tintB = 255;

	// Tint red when hit
	if (g_Enemies[index].IsHit == 1) {
		g_Enemies[index].IsHit = 0;
		tintG = 0; 
		tintB = 0;
	}

	BlitImageRegionTinted(g_Images.Enemy[g_Game.Level-1],
		(float)g_Enemies[index].XPos, (float)g_Enemies[index].YPos,
		(float)(column * g_Enemies[index].UnScaledFrameWidth),
		(float)(row    * g_Enemies[index].UnScaledFrameHeight),
		(float)g_Enemies[index].UnScaledFrameWidth, (float)g_Enemies[index].UnScaledFrameHeight,
		((float)g_Enemies[index].ScalePercent / 100.0), ((float)g_Enemies[index].ScalePercent / 100.0),
		tintR, tintG, tintB);
		
	// Debugging - blit collision rectangle!!	
	//BlitDebugCollisionRectangle(index);
}



void BitEnemies() {
	for (unsigned int ee = 0; ee < g_ThisLevel.EnemyCount; ee++) BlitEnemy(ee);
}

void BlitGameComplete() {
	
	// Bit the Rocks
	for(unsigned int xx=0; xx < g_GameCompleteSettings.RockCount; xx++) {

		// Set our colour
		unsigned int colourIndex = xx + g_GameCompleteSettings.ColourCycleOffset;
		if(colourIndex >= g_GameCompleteSettings.RockCount) colourIndex -= g_GameCompleteSettings.RockCount;
	
		spriteStruct backgroundRock = g_GameCompleteSettings.BackgroundRocks[xx];
		
		BlitImageRegionTinted(g_Images.Rock, backgroundRock.XPos, backgroundRock.YPos, 0, 0, 
			backgroundRock.UnScaledFrameWidth, backgroundRock.UnScaledFrameHeight, 
			(float)backgroundRock.ScalePercent / 100, (float)backgroundRock.ScalePercent / 100,
			g_GameCompleteSettings.ColourArray[colourIndex][0], 
			g_GameCompleteSettings.ColourArray[colourIndex][1], 
			g_GameCompleteSettings.ColourArray[colourIndex][2]);
	}

	// Blit the band	
	BlitImageRegion(
		g_Images.Band, g_GameCompleteSettings.Band.XPos, g_GameCompleteSettings.Band.YPos,
		g_GameCompleteSettings.Band.Frame * g_GameCompleteSettings.Band.UnScaledFrameWidth, 0,
		g_GameCompleteSettings.Band.UnScaledFrameWidth, g_GameCompleteSettings.Band.UnScaledFrameHeight,
		g_Game.ScaleFactorDevice, g_Game.ScaleFactorDevice);
}

void BlitPauseBackground() {
	BlitImageRegion(g_Images.PauseBackground, 0, 0, 0, 0, 1, 1, SCREEN_WIDTH, SCREEN_HEIGHT);
}