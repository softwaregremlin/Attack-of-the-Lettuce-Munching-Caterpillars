void InitialiseGraphics() {

	sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND);
	sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF);

	g_Game.ScaleFactorDevice = (float)SCREEN_HEIGHT / (float)MAX_DEVICE_HEIGHT;

	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
}

void StartDrawing() {
	vita2d_start_drawing();
	vita2d_clear_screen();
}

void StopDrawing() {
	vita2d_end_drawing();
	vita2d_swap_buffers();
}

void LoadImage(vita2d_texture ** image, const char *filename) {
	
	char folderAndFile[50] = "app0:data/images/";
	strcat(folderAndFile, filename);
	
	vita2d_wait_rendering_done(); 
	vita2d_free_texture(*image);	
	*image = vita2d_load_PNG_file(folderAndFile);
}

void BlitImage(vita2d_texture* image, float x, float y) {
	vita2d_draw_texture(image, x, y);
}

void BlitImageRegion(vita2d_texture* image, float xPos, float yPos,
	float regionX, float regionY, float regionWidth, float regionHeight,
	float xScale, float yScale) {
	
	vita2d_draw_texture_part_scale(image,
		xPos, yPos, regionX, regionY, regionWidth, regionHeight, xScale, yScale);
}

void BlitImageRegionTinted(vita2d_texture* image, float xPos, float yPos,
	float regionX, float regionY, float regionWidth, float regionHeight,
	float xScale, float yScale,
	int r, int g, int b) {
	
	vita2d_draw_texture_tint_part_scale(image,
		xPos, yPos, regionX, regionY, regionWidth, regionHeight, xScale, yScale, RGBA8(r,g,b,255));
}

int GetImageHeight(vita2d_texture* image) {
	return vita2d_texture_get_height(image);
}

int GetImageWidth(vita2d_texture* image) {
	return vita2d_texture_get_width(image);
}

