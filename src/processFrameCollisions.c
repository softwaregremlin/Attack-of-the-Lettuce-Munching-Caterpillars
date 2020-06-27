int CollisionPitmanHeight() {
	return (int)((float)g_Pitman.CollisionRectangle.height * ((float)g_Pitman.ScalePercent / 100.0));
}

int CollisionPitmanWidth() {
	return (int)((float)g_Pitman.CollisionRectangle.width * ((float) g_Pitman.ScalePercent / 100.0));
}

int CollisionPitmanLeft() {
	
	// Left Facing (mirror image)
	if(g_Pitman.FlippedX) {
		return g_Pitman.XPos +
			(int)((float)g_Pitman.Width * (float)g_Pitman.ScalePercent / 100.0) -
			(int)((float)g_Pitman.CollisionRectangle.x * (float)g_Pitman.ScalePercent / 100.0) -
			(int)(g_Pitman.CollisionRectangle.LeftFacingXOffsetRatio * (float)CollisionPitmanWidth());
	}
	// Right Facing
	else {
		return g_Pitman.XPos +
			(int)((float)g_Pitman.CollisionRectangle.x * (float)g_Pitman.ScalePercent / 100.0) -
			(int)(g_Pitman.CollisionRectangle.RightFacingXOffsetRatio * (float)CollisionPitmanWidth());
	}
	
}

int CollisionPitmanRight() {
	return CollisionPitmanLeft() + CollisionPitmanWidth();
}

int CollisionPitmanTop() {
	return g_Pitman.YPos +  
		(int)(int)((float)g_Pitman.CollisionRectangle.y) * ((float)g_Pitman.ScalePercent / 100.0) +
		CollisionPitmanHeight();
}


// Helper function
int Between(int value, int min, int max) {
	return value >= min && value <= max;
}

// Helper function
int InRectangle(int x, int y, int left, int top, int width, int height) {
	return Between(x, left, left + width) &&
		   Between(y, top,  top  + height);
}

// Helper function
int RectanglesCollide(int left1, int top1, int width1, int height1,
					  int left2, int top2, int width2, int height2) {
	return (InRectangle(left1,          top1,           left2, top2, width2, height2) ||
		    InRectangle(left1 + width1, top1,           left2, top2, width2, height2) ||
		    InRectangle(left1,          top1 + height1, left2, top2, width2, height2) ||
		    InRectangle(left1 + width1, top1 + height1, left2, top2, width2, height2))
		   ||
		   (InRectangle(left2,          top2,           left1, top1, width1, height1) ||
		    InRectangle(left2 + width2, top2,           left1, top1, width1, height1) ||
		    InRectangle(left2,          top2 + height2, left1, top1, width1, height1) ||
		    InRectangle(left2 + width2, top2 + height2, left1, top1, width1, height1));
}

int CollisionWithEnemy(int index) {
	// must be at the bottom of the "swipe" movement
	if(!(g_Pitman.State == SPRITE_STATE_FIRING && g_Pitman.Frame==1)) return false;

	// Worm must be moving (or "undead") (not dying / dead)
	if(!((g_Enemies[index].State == SPRITE_STATE_MOVING) ||
		 (g_Enemies[index].State == SPRITE_STATE_UNDEAD))) return false;

	// Get scaled dimensions of the enemy's collision rectangle
	int enemyCollisionLeft = g_Enemies[index].XPos +
		(int)(g_Enemies[index].CollisionRectangle.x * g_Enemies[index].ScalePercent / 100);
	int enemyCollisionTop = g_Enemies[index].YPos +
		(int)(g_Enemies[index].CollisionRectangle.y * g_Enemies[index].ScalePercent / 100);

	int enemyCollisionWidth  = (int)(g_Enemies[index].CollisionRectangle.width  * g_Enemies[index].ScalePercent / 100);
	int enemyCollisionHeight = (int)(g_Enemies[index].CollisionRectangle.height * g_Enemies[index].ScalePercent / 100);

	return RectanglesCollide(
		enemyCollisionLeft, enemyCollisionTop,
		enemyCollisionWidth, enemyCollisionHeight,
		CollisionPitmanLeft(), CollisionPitmanTop(), 
		CollisionPitmanWidth(), CollisionPitmanHeight());
}
