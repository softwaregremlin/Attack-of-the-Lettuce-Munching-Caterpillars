
typedef struct {
	unsigned int LoadingDotCount, TimeSinceArmMovement, ArmMovements, ArmMovementsMax, ArmMovementInterval;
	unsigned int Swiped, ExplosionSoundPlayed, ExplosionDelay, TimeSinceSwipe;
	unsigned int StartGameTextX, StartGameTextInitialY, StartGameTextInitialSize, SelectedMenuButton;
	unsigned int StartGameTextXSpeed, StartGameTextYSpeed, StartGameTextGrowth, StartGameDelay;
	unsigned int CycleMinR, CycleMaxR, CycleMinG, CycleMaxG, CycleMinB, CycleMaxB, CycleSpeed;
	unsigned int NonSelectedR, NonSelectedG, NonSelectedB;

} introSettingsStruct;