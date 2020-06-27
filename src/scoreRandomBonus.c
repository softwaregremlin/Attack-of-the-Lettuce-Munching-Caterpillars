void ShowRandomBonus()
{   
	// Assign the extra points or seconds according to the random number g_RandomBonus
	// set when the wave was completed
	int extraPoints = 0, extraSeconds = 0;
	if(g_RandomBonus >=1 && g_RandomBonus <= 4) extraPoints = 100;
	if(g_RandomBonus >=5 && g_RandomBonus <= 8) extraPoints = 200;
	if(g_RandomBonus == 9  ) extraPoints = 500;
	if(g_RandomBonus == 10 ) extraPoints = 1000;
	if(g_RandomBonus >=11 && g_RandomBonus <= 14) extraSeconds = 1;
	if(g_RandomBonus >=15 && g_RandomBonus <= 18) extraSeconds = 2;
	if(g_RandomBonus == 19 ) extraSeconds = 5;
	if(g_RandomBonus == 20 ) extraSeconds = 10;

	// Display the appropriate message
	char msgArray[200];
	if(extraPoints > 0)  sprintf(msgArray,  "RANDOM BONUS\n     %d Points!",  extraPoints);
	if(extraSeconds == 1) sprintf(msgArray, "RANDOM BONUS\n     1 Second!");
	if(extraSeconds >  1) sprintf(msgArray, "RANDOM BONUS\n     %d Seconds!", extraSeconds);

	// int randomBonusOffset =  g_isSmallScreen ? 80 : 180;

	g_RandomBonusFlash++;
	if(g_RandomBonusFlash > 16) g_RandomBonusFlash = 0;

	if(g_RandomBonusFlash <=8) drawText(g_TextRandomBonus,msgArray);



	// Apply the random bonus
	if(!g_RandomBonusAdded)
	{
		//g_Time += extraSeconds;
		g_BonusTime = extraSeconds * 1000;
		g_Score += extraPoints;
		g_RandomBonusAdded = true;
	}
}