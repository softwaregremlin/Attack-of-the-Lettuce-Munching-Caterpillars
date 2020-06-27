
typedef struct {
	float x, y, width, height, LeftFacingXOffsetRatio, RightFacingXOffsetRatio;
} collisionRectangleStruct;

typedef struct {
	// Position vars 
	int YPos, XPos, IntroXPos, IntroYPos;
	int YMaxLimit, YMinLimit;
	int XMaxLimitTop, XMinLimitTop;
	int XMaxLimitBottom, XMinLimitBottom;
	int DestinationX, DestinationY;
	//int OffsetX, OffsetY;
	int TurnOffsetX, TurnOffsetY;

	// Transformation vars
	int FlippedX, FlippedY, ScalePercent, MinScale;

	// Dimensions: height, width to be scaled to the device
	int Height, Width;
	int UnScaledFrameHeight, UnScaledFrameWidth;
	//int CollisionRecHeight, CollisionRecWidth;

	collisionRectangleStruct CollisionRectangle;

	// Ignore Scale?
	int IgnoreScale;

	// Step vars
	int StepSize, StepsMoved, Step, StepCount;
	int StepSequences [20][100];

	// Animation vars
	int State, Frame, Tick, Rows, Columns;
	int Sequences [20][30];

	// Hits (for "Boss Men")!
	int IsHit, Hits, HitsToKill, IsBoss, BossTopLimit;

	// Hiding - snail and undead worms
	int EnemyHides, EnemyRandomHideNumber, EnemyStepPattern, EnemyIsUndead;


} spriteStruct;