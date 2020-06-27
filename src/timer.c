int nextSecond(int targetSeconds) {
	/*
	//if(targetSeconds == 0) return 0;
	// June 2012 - we're allowing 0 time now...
	if(targetSeconds < -1) return -1;

    uint64 timeMilli = s3eTimerGetUTC() % MS_PER_DAY;
	int sec = (int) ((timeMilli / MS_PER_SECOND) % 60);
	if(g_oldSecond == -1) g_oldSecond = sec;
	if(sec == g_oldSecond) return targetSeconds;
	*/
	// decrease the seconds
	int sec = 0;
	g_oldSecond = sec;
	return targetSeconds - 1;
}

void UpdateTime()
{
	// g_Time = nextSecond(g_Time);
	g_Time -= g_msElapsedSinceLastFrame;
}

void UpdateHiddenTime()
{
	//g_hiddenTime = nextSecond(g_hiddenTime);
	g_hiddenTime -= g_msElapsedSinceLastFrame;
}

void ResetLevelTime()
{
	g_Time = g_StartTime;
	//if(g_isSmallScreen) g_Time += g_SmallScreenHandicap;
	//if(g_isWideScreen)  g_Time += g_WideScreenHandicap;
}
