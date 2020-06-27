
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

/*

void BlitDebugCollisionRectangle(int index) {
	
	int collisionLeft = g_Enemies[index].XPos + 
		(int)(g_Enemies[index].OffsetX * g_Enemies[index].ScalePercent / 100);
	int collisionTop = g_Enemies[index].YPos + 
		(int)(g_Enemies[index].OffsetY * g_Enemies[index].ScalePercent / 100);	
	
	vita2d_draw_rectangle((float)collisionLeft, (float)collisionTop, 
						  (float)(g_Enemies[index].CollisionRecWidth * g_Enemies[index].ScalePercent / 100), 
						  (float)(g_Enemies[index].CollisionRecHeight* g_Enemies[index].ScalePercent / 100), 
						  RGBA8(0, 0, 255, 90));
}

void BlitBackground() {

	if(g_Room == ROOM_LEVEL2 ||
	   g_Room == ROOM_LEVEL2_BOSS ||
	   g_Room == ROOM_LEVEL2_GAMEOVER) { //||
	   //(g_Room == ROOM_INTRO && (g_Level == 3 || g_Level == 4))) {
		vita2d_draw_texture(g_ImageBackground2, 0, 0);
		return;
	}
	
	if(g_Room == ROOM_LEVEL3 ||
	   g_Room == ROOM_LEVEL3_BOSS ||
	   g_Room == ROOM_LEVEL3_GAMEOVER )  {// ||
	   //(g_Room == ROOM_INTRO && (g_Level == 5 || g_Level == 6))) {
		vita2d_draw_texture(g_ImageBackground3, 0, 0);
		return;
	}

	if(g_Room == ROOM_LEVEL4 ||
	   g_Room == ROOM_LEVEL4_BOSS ||
	   g_Room == ROOM_LEVEL4_GAMEOVER ) {// ||
	   //(g_Room == ROOM_INTRO && (g_Level == 7 || g_Level == 8))) {
		vita2d_draw_texture(g_ImageBackground4, 0, 0);
		return;
	}

	// Default (intro / level 1)
	vita2d_draw_texture(g_ImageBackground, 0, 0);
}

*/
void BlitPitman() {
	
	// Set the scale
	if(!g_PitmanIgnoreScale) g_Pitman.ScalePercent = ScalePercentCalculate(g_Pitman.YPos);

	// Flipping
	float xPos = g_Pitman.FlippedX ? 
		(float)g_Pitman.XPos  + ((((float)g_Pitman.ScalePercent / 100.0)*(float)g_Pitman.UnScaledFrameWidth) * 0.64) : 
		(float)g_Pitman.XPos;
	float xScale = (g_Pitman.FlippedX ? -1.0 : 1.0) * ((float)g_Pitman.ScalePercent / 100.0);
	
	BlitImageRegion(g_ImagePlayer,
		xPos, (float)g_Pitman.YPos,
		(float)(g_Pitman.Sequences[g_Pitman.State][g_Pitman.Frame] * g_Pitman.UnScaledFrameWidth), 0,
		(float)g_Pitman.UnScaledFrameWidth, (float)g_Pitman.UnScaledFrameHeight,
		xScale, ((float)g_Pitman.ScalePercent / 100.0));	
		

	///////////////////////////////////
	// Debug - collision rectangle!!
	///////////////////////////////////


	if(g_Pitman.State == SPRITE_STATE_FIRING && g_Pitman.Frame==1) {
		/*
		vita2d_draw_rectangle((float)CollisionPitmanLeft(), (float)CollisionPitmanTop(), 
							  (float)CollisionPitmanWidth(), (float)CollisionPitmanHeight(), 
							  RGBA8(100, 0, 0, 128));							 
		*/
	}
	//////////////////////////////////////////////////////////

}



// TODO: Split into include files
// ??????????????? Boss - normal enemy??

void BlitEnemy(int index) {

	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	//if(g_Enemies[index].XPos > Iw2DGetSurfaceWidth()) return;
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;

	 ///////////////////////////////////////////////////////////////
	// if (g_Enemies[index].XPos < 50) return; // 0 - g_Enemies[index].Width) return;	
	if (g_Enemies[index].XPos < 0 - g_Enemies[index].Width) return;	
	///////////////////////////////////////////////////////////////

	// Set the scale
	g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);

	// void vita2d_draw_texture_part_scale(const vita2d_texture *texture, float x, float y, float tex_x, float tex_y, float tex_w, float tex_h, float x_scale, float y_scale)							 
	BlitImageRegion(g_ImageEnemy,
		(float)g_Enemies[index].XPos, (float)g_Enemies[index].YPos,
		(float)(g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] * g_Enemies[index].UnScaledFrameWidth), 0,
		(float)g_Enemies[index].UnScaledFrameWidth, (float)g_Enemies[index].UnScaledFrameHeight,
		((float)g_Enemies[index].ScalePercent / 100.0), ((float)g_Enemies[index].ScalePercent / 100.0));	
		
	// Debugging - blit collision rectangle!!	
	//BlitDebugCollisionRectangle(index);
}

/*
void BlitSnail(int index) {
	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	// or off-screen
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;

	// Set the scale
	g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);

	vita2d_draw_texture_part_scale(g_ImageEnemyLevel2,
		(float)g_Enemies[index].XPos, (float)g_Enemies[index].YPos,
		(float)(g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] * g_Enemies[index].UnScaledFrameWidth), 0,
		(float)g_Enemies[index].UnScaledFrameWidth, (float)g_Enemies[index].UnScaledFrameHeight,
		((float)g_Enemies[index].ScalePercent / 100.0), ((float)g_Enemies[index].ScalePercent / 100.0));	
	
	// Debugging - blit collision rectangle!!	
	//BlitDebugCollisionRectangle(index);

}

void BlitSpider(int index) {
	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	// or off-screen
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;

	// Set the scale
	g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);

	vita2d_draw_texture_part_scale(g_ImageEnemyLevel3,
		(float)g_Enemies[index].XPos, (float)g_Enemies[index].YPos,
		(float)(g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] * g_Enemies[index].UnScaledFrameWidth), 0,
		(float)g_Enemies[index].UnScaledFrameWidth, (float)g_Enemies[index].UnScaledFrameHeight,
		((float)g_Enemies[index].ScalePercent / 100.0), ((float)g_Enemies[index].ScalePercent / 100.0));	
	
	// Debugging - blit collision rectangle!!	
	// BlitDebugCollisionRectangle(index);

}

void BlitSkeleWorm(int index) {
	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	// or off-screen
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;

	// Set the scale
	g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);

	vita2d_draw_texture_part_scale(g_ImageEnemyLevel4,
		(float)g_Enemies[index].XPos, (float)g_Enemies[index].YPos,
		(float)(g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] * g_Enemies[index].UnScaledFrameWidth), 0,
		(float)g_Enemies[index].UnScaledFrameWidth, (float)g_Enemies[index].UnScaledFrameHeight,
		((float)g_Enemies[index].ScalePercent / 100.0), ((float)g_Enemies[index].ScalePercent / 100.0));	
	
	// Debugging - blit collision rectangle!!	
	//BlitDebugCollisionRectangle(index);

}
//////////////////////////////////////
//////////////////////////////////////
///////////////////////////////////////

void BlitBoss1() {
	int index = 0;
	//unsigned int tintColour = RGBA8(0,0,0,255);

	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;

	// Set the scale - exception is during death sequence!
	if(g_Enemies[index].State == SPRITE_STATE_MOVING) {
		g_Enemies[index].ScalePercent = 
			ScalePercentCalculate(g_Enemies[index].YPos);
	}

	int column 	= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] % g_Enemies[index].Columns,
		row		= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] / g_Enemies[index].Columns;
		
	float	x = (float)g_Enemies[index].XPos, y = (float)g_Enemies[index].YPos,
			partWidth  = (float)(column * g_Enemies[index].UnScaledFrameWidth),
			partHeight = (float)(row    * g_Enemies[index].UnScaledFrameHeight),
			unscaledWidth = (float)g_Enemies[index].UnScaledFrameWidth,
			unscaledHeight = (float)g_Enemies[index].UnScaledFrameHeight,
			scale = ((float)g_Enemies[index].ScalePercent / 100.0);
	
	// Tint red when hit
	if(g_Enemies[index].IsHit == 1) {
		g_Enemies[index].IsHit = 0;

		vita2d_draw_texture_tint_part_scale(
			g_ImageBossLevel1, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale, RGBA8(255,0,0,255));		
	} else {
		// Normal display
		vita2d_draw_texture_part_scale(
			g_ImageBossLevel1, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale);
	}
	
	// Debugging - blit collision rectangle!!	
	//BlitDebugCollisionRectangle(index);
}


void BlitBoss2() {
	int index = 0;

	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	// or off-screen
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;


	// Set the scale - exception is during death sequence!
	if(g_Enemies[index].State == SPRITE_STATE_MOVING) {
		g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);
	}

	int column 	= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] % g_Enemies[index].Columns,
		row		= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] / g_Enemies[index].Columns;
		
	float	x = (float)g_Enemies[index].XPos, y = (float)g_Enemies[index].YPos,
			partWidth  = (float)(column * g_Enemies[index].UnScaledFrameWidth),
			partHeight = (float)(row    * g_Enemies[index].UnScaledFrameHeight),
			unscaledWidth = (float)g_Enemies[index].UnScaledFrameWidth,
			unscaledHeight = (float)g_Enemies[index].UnScaledFrameHeight,
			scale = ((float)g_Enemies[index].ScalePercent / 100.0);
	
	// Tint red when hit
	if(g_Enemies[index].IsHit == 1) {
		g_Enemies[index].IsHit = 0;

		vita2d_draw_texture_tint_part_scale(
			g_ImageBossLevel2, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale, RGBA8(255,0,0,255));		
	} else {
		// Normal display
		vita2d_draw_texture_part_scale(
			g_ImageBossLevel2, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale);
	}

}

void BlitBoss3() {
	int index = 0;

	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	// or off-screen
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;


	// Set the scale - exception is during death sequence!
	if(g_Enemies[index].State == SPRITE_STATE_MOVING) {
		g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);
	}

	int column 	= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] % g_Enemies[index].Columns,
		row		= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] / g_Enemies[index].Columns;
		
	float	x = (float)g_Enemies[index].XPos, y = (float)g_Enemies[index].YPos,
			partWidth  = (float)(column * g_Enemies[index].UnScaledFrameWidth),
			partHeight = (float)(row    * g_Enemies[index].UnScaledFrameHeight),
			unscaledWidth = (float)g_Enemies[index].UnScaledFrameWidth,
			unscaledHeight = (float)g_Enemies[index].UnScaledFrameHeight,
			scale = ((float)g_Enemies[index].ScalePercent / 100.0);
	
	// Tint red when hit
	if(g_Enemies[index].IsHit == 1) {
		g_Enemies[index].IsHit = 0;

		vita2d_draw_texture_tint_part_scale(
			g_ImageBossLevel3, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale, RGBA8(255,0,0,255));		
	} else {
		// Normal display
		vita2d_draw_texture_part_scale(
			g_ImageBossLevel3, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale);
	}

}

void BlitBoss4() {
	int index = 0;

	// Don't blit if dead!
	if(g_Enemies[index].State == SPRITE_STATE_DEAD) return;

	// or off-screen
	if(g_Enemies[index].XPos > SCREEN_WIDTH) return;


	// Set the scale - exception is during death sequence!
	if(g_Enemies[index].State == SPRITE_STATE_MOVING) {
		g_Enemies[index].ScalePercent = ScalePercentCalculate(g_Enemies[index].YPos);
	}

	int column 	= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] % g_Enemies[index].Columns,
		row		= g_Enemies[index].Sequences[g_Enemies[index].State][g_Enemies[index].Frame] / g_Enemies[index].Columns;
		
	float	x = (float)g_Enemies[index].XPos, y = (float)g_Enemies[index].YPos,
			partWidth  = (float)(column * g_Enemies[index].UnScaledFrameWidth),
			partHeight = (float)(row    * g_Enemies[index].UnScaledFrameHeight),
			unscaledWidth = (float)g_Enemies[index].UnScaledFrameWidth,
			unscaledHeight = (float)g_Enemies[index].UnScaledFrameHeight,
			scale = ((float)g_Enemies[index].ScalePercent / 100.0);
	
	// Tint red when hit
	if(g_Enemies[index].IsHit == 1) {
		g_Enemies[index].IsHit = 0;

		vita2d_draw_texture_tint_part_scale(
			g_ImageBossLevel4, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale, RGBA8(255,0,0,255));		
	} else {
		// Normal display
		vita2d_draw_texture_part_scale(
			g_ImageBossLevel4, x, y, partWidth, partHeight, unscaledWidth, unscaledHeight, scale, scale);
	}
	
	// Debugging - blit collision rectangle!!	
	// BlitDebugCollisionRectangle(index);

}
 
void BlitGameComplete() {

	int rockCount = 6;
	int rockStep = (int)(60 * g_scaleFactorDevice);
	float rockWidth = SCREEN_WIDTH, rockHeight = SCREEN_HEIGHT / 2; 


	// 6 shades of yellow
	unsigned int colourArray[6] = {RGBA8(255,255,0,255),   RGBA8(255,255,34,255),  RGBA8(255,255,68,255),
								   RGBA8(255,255,102,255), RGBA8(255,255,136,255), RGBA8(255,255,176,255)};
	float unscaledWidth = vita2d_texture_get_width(g_ImageCompleteRock),
		  unscaledHeight = vita2d_texture_get_height(g_ImageCompleteRock);	

	int xPos = 0, yPos = (int)(10 * g_scaleFactorDevice);
	for(int xx=0; xx < rockCount; xx++) {
		// Set our colour
		int colourIndex = xx + g_GameCompleteColourCycleOffset;
		if(colourIndex >= rockCount) colourIndex -= rockCount;
		// Iw2DSetColour(colourArray[colourIndex]);

		float scaleX = rockWidth / unscaledWidth,
			  scaleY = rockHeight / unscaledHeight;
		
		vita2d_draw_texture_tint_scale(g_ImageCompleteRock, xPos, yPos, scaleX, scaleY, colourArray[colourIndex]);		
							
		// Shrink down to the next size
		xPos += rockStep;
		yPos += rockStep;
		rockWidth  -= 2 * rockStep;
		rockHeight -=  rockStep;
	}

	// reset back to white for next time we blit the background
	// Iw2DSetColour(0xffffffff);

	// Colour cycling counters
	g_GameCompleteColourCycleFrame++;
	if(g_GameCompleteColourCycleFrame > 0) {
		g_GameCompleteColourCycleFrame = 0;
		g_GameCompleteColourCycleOffset++;
		if(g_GameCompleteColourCycleOffset > rockCount) g_GameCompleteColourCycleOffset = 0;
	}

	// Blit the band
	int bandFramesPerChange = 4;
	
	float bandFrameWidth = vita2d_texture_get_width(g_ImageCompleteBand) / 2, 
		  bandFrameHeight = vita2d_texture_get_height(g_ImageCompleteBand);
	float bandXOffset = g_GameCompleteBandFrame > (bandFramesPerChange - 1) ? 
							0 : bandFrameWidth;

	float bandWidth = bandFrameWidth * g_scaleFactorDevice;

	float bandTop = (float)(100 * g_scaleFactorDevice);
	float bandLeft = (float)((SCREEN_WIDTH - bandWidth)/2);

	vita2d_draw_texture_part_scale(
		g_ImageCompleteBand, bandTop, bandLeft, bandXOffset, 0,
							 bandFrameWidth, bandFrameHeight, g_scaleFactorDevice, g_scaleFactorDevice);		
	
	g_GameCompleteBandFrame++;
	if(g_GameCompleteBandFrame >= (bandFramesPerChange * 2)) g_GameCompleteBandFrame = 0;

		
		
		char msgArray[200];
		int m = g_GameCompleteMsg, mCount = 4;
		if(g_GameCompleteScrollPos == -9999) g_GameCompleteScrollPos = Iw2DGetSurfaceWidth();

		// Switch different sentences in/out
		if(m==1) sprintf(msgArray, ".... GAME COMPLETE .... thank you for playing! ....");
		if(m==2) sprintf(msgArray, ".... Attack of the Lettuce Munching Caterpillars by Gremlin Software .... ");
		if(m==3) sprintf(msgArray, ".... Please check www.gremlinsoftware.co.nz for updates, new levels and new games ....");
		if(m==4) sprintf(msgArray, ".... Outro music by the White Tails ....");
		char *msg = msgArray;

		// Show the text
		Iw2DSetFont(g_isSmallScreen ? g_FontMedium : g_FontLarge);
		Iw2DDrawString(msg,
						CIwSVec2(g_GameCompleteScrollPos, Iw2DGetSurfaceHeight() - 100),
						CIwSVec2(3500,100),
						IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_BOTTOM);
		
		// Scroll the text
		g_GameCompleteScrollPos-=5;
		int scrollLimit = (int) (Iw2DGetSurfaceWidth() * 3.5);
		if(g_GameCompleteScrollPos < -scrollLimit)
		{
				g_GameCompleteScrollPos = Iw2DGetSurfaceWidth();
				g_GameCompleteMsg++;
				if(g_GameCompleteMsg > mCount) g_GameCompleteMsg = 1;
		}

		

		// Draw the exit button
		
		UpdateTime();
		if(g_Time <= 0)
		{
			g_GameCompleteExitVisible = true;
			Iw2DDrawImageRegion(g_ImageButtonBg,
								CIwSVec2(Iw2DGetSurfaceWidth() - 105, 5), 
								CIwSVec2(100,30),
								CIwSVec2(0,0), 
								CIwSVec2(g_ImageButtonBg->GetWidth(), g_ImageButtonBg->GetHeight()));

			Iw2DSetFont(g_FontSmall);
			Iw2DDrawString("exit",
							CIwSVec2(Iw2DGetSurfaceWidth() - 83, 8),
							CIwSVec2(100,20),
							IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
		}
		
}
*/