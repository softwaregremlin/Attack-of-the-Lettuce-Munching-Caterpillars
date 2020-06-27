void SaveHighScore() {
	// No need to save!
	if(g_Game.Score < g_Game.HighScore) return;

	g_Game.HighScore = g_Game.Score;
	g_Game.NewHighScore = true;
	
	// Save hi
	CreateDataFolderIfNotExists();
	FILE* dataFile;
	if ((dataFile = fopen(g_DataPaths.HighScore, "w"))) {
		fprintf(dataFile, "%d", g_Game.HighScore);
			fclose(dataFile);
	}
}

void SaveLevelProgress() {	

	// Save the level reached
	CreateDataFolderIfNotExists();
	FILE* dataFile;
	if ((dataFile = fopen(g_DataPaths.Level, "w"))) {
		fprintf(dataFile, "%d", g_Game.Level);
		fclose(dataFile);
	}

	// Maximum
	if (g_Game.Level <= g_Game.MaxLevelReached) return;
	if (g_Game.Level >  g_Game.LevelCount) return;
	g_Game.MaxLevelReached = g_Game.Level;
	if ((dataFile = fopen(g_DataPaths.MaxLevel, "w"))) {
		fprintf(dataFile, "%d", g_Game.MaxLevelReached);
		fclose(dataFile);
	}
}

void ActivateLogging() {
	g_Game.LoggingActivated = true;
	FILE* dataFile;
	if ((dataFile = fopen(g_DataPaths.Log, "w"))) {
		fprintf(dataFile, "Logging Activated");
			fclose(dataFile);
	}
}

void WriteLog(const char* msg) {
	if (!g_Game.LoggingActivated) return;
	FILE* dataFile;
	if ((dataFile = fopen(g_DataPaths.Log, "a"))) {
		fprintf(dataFile, "\n");
		fprintf(dataFile, msg);
		fclose(dataFile);
	}
}