
void InitialisePitman() {

	// Scale everything according to the screen size of the device
	g_Pitman.UnScaledFrameHeight = GetImageHeight(g_Images.Player);
	g_Pitman.UnScaledFrameWidth  = GetImageWidth(g_Images.Player) / g_Pitman.Columns;
	
	g_Pitman.Height = (int)(g_Game.ScaleFactorDevice * g_Pitman.UnScaledFrameHeight);
	g_Pitman.Width  = (int)(g_Game.ScaleFactorDevice * g_Pitman.UnScaledFrameWidth);

	g_Pitman.CollisionRectangle.x = g_Pitman.CollisionRectangle.x * g_Game.ScaleFactorDevice;
	g_Pitman.CollisionRectangle.y = g_Pitman.CollisionRectangle.y * g_Game.ScaleFactorDevice;
	g_Pitman.CollisionRectangle.width = g_Pitman.CollisionRectangle.width * g_Game.ScaleFactorDevice;
	g_Pitman.CollisionRectangle.height = g_Pitman.CollisionRectangle.height * g_Game.ScaleFactorDevice;

	g_Pitman.XPos = g_Pitman.XPos * g_Game.ScaleFactorDevice;
	g_Pitman.YPos = g_Pitman.YPos * g_Game.ScaleFactorDevice;
	g_Pitman.IntroXPos = g_Pitman.XPos;
	g_Pitman.IntroYPos = g_Pitman.YPos;
	
	g_Pitman.TurnOffsetX = g_Pitman.TurnOffsetX * g_Game.ScaleFactorDevice;
	g_Pitman.StepSize =	g_Pitman.StepSize * g_Game.ScaleFactorDevice;
	
	g_Pitman.XMinLimitBottom = g_Pitman.XMinLimitBottom * g_Game.ScaleFactorDevice;
	g_Pitman.XMaxLimitBottom = g_Pitman.XMaxLimitBottom * g_Game.ScaleFactorDevice;
	g_Pitman.XMinLimitTop = g_Pitman.XMinLimitTop * g_Game.ScaleFactorDevice;
	g_Pitman.XMaxLimitTop =	g_Pitman.XMaxLimitTop * g_Game.ScaleFactorDevice;
	g_Pitman.YMinLimit = g_Pitman.YMinLimit * g_Game.ScaleFactorDevice;
	g_Pitman.YMaxLimit = g_Pitman.YMaxLimit * g_Game.ScaleFactorDevice;

}

void InitialisePitmanIntro() {
	g_Pitman.XPos = g_Pitman.IntroXPos;
	g_Pitman.YPos = g_Pitman.IntroYPos;
	g_Pitman.FlippedX = false;
}

