void InitialiseInput() {
	memset(&g_VitaPad, 0, sizeof(g_VitaPad));
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
}

unsigned int InputStartPressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_START;
}

unsigned int InputCrossPressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_CROSS;
}

unsigned int InputTrianglePressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_TRIANGLE;
}

unsigned int InputCirclePressed() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return g_VitaPad.buttons & SCE_CTRL_CIRCLE;
}


unsigned int InputLeft() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.lx < MIN_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_LEFT);
}

unsigned int InputRight() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.lx > MAX_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_RIGHT);
}

unsigned int InputUp() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.ly < MIN_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_UP);
}

unsigned int InputDown() {
	sceCtrlPeekBufferPositive(0, &g_VitaPad, 1);
	return (g_VitaPad.ly > MAX_ANALOG_STICK_THRESHOLD) || (g_VitaPad.buttons & SCE_CTRL_DOWN);
}