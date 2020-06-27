
typedef struct {
	unsigned int MinLimit, MaxLimit, ExtraPoints, ExtraSeconds, IsLastRange;
} randomBonusRewardRange;

typedef struct {
	unsigned int RandomNumber, RandomNumberRange, Time, Added, TimeBonusAdded, Flash, FlashFrames;
	char RandomBonusMessage[200];
	randomBonusRewardRange RewardRanges[10];
} randomBonusStruct;

