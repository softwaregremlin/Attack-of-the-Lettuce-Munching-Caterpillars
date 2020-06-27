void CalculateRandomBonus() {

	// No time bonus for the last level (50% chance of points or seconds)

	unsigned int randBonusMax = (g_ThisLevel.Wave == g_ThisLevel.WaveCount) ?
		g_RandomBonus.RandomNumberRange / 2 : g_RandomBonus.RandomNumberRange, 
		rangeIndex = 0, isLastRange = false, randomBonusNumber;
	randMinMax(1, randBonusMax, &randomBonusNumber);

	// Assign the extra points or seconds according to the random number
	int extraPoints = 0, extraSeconds = 0;

	// Loop through the reward ranges
	while (!isLastRange) {
		if (randomBonusNumber >= g_RandomBonus.RewardRanges[rangeIndex].MinLimit &&
			randomBonusNumber <= g_RandomBonus.RewardRanges[rangeIndex].MaxLimit) {
			  extraPoints  = g_RandomBonus.RewardRanges[rangeIndex].ExtraPoints;
			  extraSeconds = g_RandomBonus.RewardRanges[rangeIndex].ExtraSeconds;
		}
		rangeIndex++;
		isLastRange = g_RandomBonus.RewardRanges[rangeIndex].IsLastRange;
	}

	// Render the message
	if (extraPoints  > 0)  sprintf(g_RandomBonus.RandomBonusMessage, "RANDOM BONUS\n     %d Points!", extraPoints);
	if (extraSeconds == 1) sprintf(g_RandomBonus.RandomBonusMessage, "RANDOM BONUS\n     1 Second!");
	if (extraSeconds > 1)  sprintf(g_RandomBonus.RandomBonusMessage, "RANDOM BONUS\n     %d Seconds!", extraSeconds);

	// Apply the random bonus
	if (!g_RandomBonus.Added) {
		//g_Time += extraSeconds;
		g_RandomBonus.Time = extraSeconds * 1000;
		g_Game.Score += extraPoints;
		g_RandomBonus.Added = true;
	}
}