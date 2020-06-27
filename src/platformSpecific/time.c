
void InitialiseTimer() {
	sceRtcGetCurrentTick(&g_VitaTime.Tick);
	g_VitaTime.LastTick = g_VitaTime.Tick.tick; 	
}

void WaitForNextFrame() {
	
	int tickChange = 0;
	while(tickChange < TICKS_PER_FRAME) {
		sceRtcGetCurrentTick(&g_VitaTime.Tick);
		tickChange = g_VitaTime.Tick.tick - g_VitaTime.LastTick;
	}
	g_VitaTime.LastTick = g_VitaTime.Tick.tick;
	g_Time.MsElapsedSinceLastFrame = (int)(tickChange / 1000);	
}