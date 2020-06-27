#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/clib.h>
#include <psp2/io/fcntl.h>
#include <psp2/audioout.h>
#include <psp2/appmgr.h>

#include <vorbis/vorbisfile.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define SOUND_BUFFER_SIZE 1024


/// Global Variables /////////////////
int g_soundBgmPort = 0, g_soundMainPort = 0;

#define BACKGROUND_MUSIC_FILE_ARRAY_LENGTH 2
OggVorbis_File g_soundBackgroundMusicOggFile[BACKGROUND_MUSIC_FILE_ARRAY_LENGTH];
OggVorbis_File g_soundSampleOggFile;
SceUID g_soundBackgroundMusicThreadUid, g_soundMainThreadUid;

int g_soundBackgroundMusicIsPlaying = 0;
int g_soundBackgroundMusicVorbisFileIndex = 0;
int g_soundBackgroundMusicLoaded = 0;
int g_soundBackgroundMusicLoop = 0;
int g_soundBackgroundMusicThreadRunning = 0;
int g_soundBackgroundMusicVolume = SCE_AUDIO_VOLUME_0DB;

int g_soundMainThreadRunning = 0;
int g_soundSampleCount = 0;
int g_soundSamplePlaying = 0;
int g_soundNewSampleToPlay = 0;

int16_t g_soundBackgroundMusicBuffer[SOUND_BUFFER_SIZE];
int16_t g_soundMainBuffer[SOUND_BUFFER_SIZE];

int16_t ***g_soundSampleArray3D = NULL;

///////////////////////////////////////////





////// Library Routines //////////////////////

// Background Music Loading
void soundClearBackgroundMusicOggIfLoaded() {
	if(g_soundBackgroundMusicLoaded==0) return;
	
	g_soundBackgroundMusicLoaded = 0;;
	//WriteLog("CLEARING(2)");
	ov_clear(&g_soundBackgroundMusicOggFile[g_soundBackgroundMusicVorbisFileIndex]);
}

 void soundLoadBackgroundMusic(char *path) {
	
	//WriteLog("CLEARING!!");
	g_soundBackgroundMusicIsPlaying = 0;
	soundClearBackgroundMusicOggIfLoaded();
	
	g_soundBackgroundMusicVorbisFileIndex++;
	if(g_soundBackgroundMusicVorbisFileIndex >= BACKGROUND_MUSIC_FILE_ARRAY_LENGTH) g_soundBackgroundMusicVorbisFileIndex =0;	
			
	if(ov_fopen(path, &g_soundBackgroundMusicOggFile[g_soundBackgroundMusicVorbisFileIndex]) < 0) return;
	g_soundBackgroundMusicLoaded = 1;
	
	//WriteLog("DONE!");
 }

 // Background Music Playing
 void soundStartBackgroundMusicLoop() {
	g_soundBackgroundMusicIsPlaying = 1;
	g_soundBackgroundMusicLoop = 0;	
 }
 
  void soundStartBackgroundMusic(int repeats) {
	g_soundBackgroundMusicIsPlaying = 1;
	g_soundBackgroundMusicLoop = repeats;	
 }
 
  void soundStopBackgroundMusic() {
	g_soundBackgroundMusicIsPlaying = 0;
	soundClearBackgroundMusicOggIfLoaded();
 }
 
  // Background Music Volume
  void soundSetBackgroundMusicVolume(int volume) {
	sceAudioOutSetVolume(g_soundBgmPort, SCE_AUDIO_VOLUME_FLAG_L_CH |SCE_AUDIO_VOLUME_FLAG_R_CH, (int[]){volume,volume});
 }
 
 void soundChangeBackgroundMusicVolume(int volumeChange) {
	g_soundBackgroundMusicVolume += volumeChange;
	if(g_soundBackgroundMusicVolume > SCE_AUDIO_VOLUME_0DB) g_soundBackgroundMusicVolume = SCE_AUDIO_VOLUME_0DB;
	if(g_soundBackgroundMusicVolume < 0) g_soundBackgroundMusicVolume = 0;
	soundSetBackgroundMusicVolume(g_soundBackgroundMusicVolume);
 }
 
 void soundMuteBackgroundMusic() {
	soundSetBackgroundMusicVolume(0);
 }
 
  void soundUnMuteBackgroundMusic() {
	soundSetBackgroundMusicVolume(g_soundBackgroundMusicVolume);
 }
 
// Samples Playing
 void soundPlaySample(int sampleNumber) {
	g_soundSamplePlaying = 0;
	g_soundNewSampleToPlay = sampleNumber;
 }
 
  void soundStopSamples() {
	g_soundSamplePlaying = 0;
 }
 
 // Samples - Unload
 void soundUnloadSamples() {
	
	for(int ss=0; ss<g_soundSampleCount; ss++) {
		// Get number of buffers to free
		int bufferCount = g_soundSampleArray3D[ss][0][0];
		for(int bb=0; bb<=bufferCount; bb++) {
			// Free 2nd dimensions
			free(g_soundSampleArray3D[ss][bb]);
		}
		// Free 1st dimensions
		free(g_soundSampleArray3D[ss]);
	}	
	// Free the array
	free(g_soundSampleArray3D);
 }
 
////////////////////////////////////////////////////
// Samples - Load an entire .ogg file into memory
////////////////////////////////////////////////////

void soundLoadSampleBufferArraysFromVorbisFile(int sampleIndex, OggVorbis_File *f) {
	
	int currentSize = 0, readingFile = 1;

	// Single dimension array
	int *listOfSamples = malloc(sizeof(int)); 
	listOfSamples[0] = 0;
	
	while(readingFile) {
		int current_section;
		int16_t buf[4096];
		int rb = ov_read(f,(char*)buf,4096,0,2,1,&current_section), sizeIncrease = rb/2;
		if(rb <= 0) {
			readingFile = 0;
			break;
		}
		// Put the samples in
		listOfSamples = realloc(listOfSamples, (currentSize + sizeIncrease) * sizeof(int)); 		
		for(int xx=0; xx<sizeIncrease; xx++) {
			listOfSamples[currentSize + xx] = buf[xx];
		}	
		currentSize += sizeIncrease;		
	}	
	
	// Add second dimensions (buffers)
	int bufferCount = currentSize / SOUND_BUFFER_SIZE + (currentSize % SOUND_BUFFER_SIZE != 0 ? 1:0);	
	g_soundSampleArray3D[sampleIndex] = malloc((bufferCount + 1) * sizeof(int16_t*)); 
	
	// Now fill in the 3rd dimension (samples)
	int listPos = 0;
	for(int bb=0; bb<=bufferCount; bb++) {
		
		g_soundSampleArray3D[sampleIndex][bb] = malloc((bb==0 ? 1 : SOUND_BUFFER_SIZE) * sizeof(int16_t)); 
		if(bb==0) {
			// 1st row - store the number of buffers
			g_soundSampleArray3D[sampleIndex][bb][0] = (int16_t)bufferCount;
		} else {
			for(int ss=0; ss<SOUND_BUFFER_SIZE; ss++) {
				// Pad the end of the last buffer with zeros
				g_soundSampleArray3D[sampleIndex][bb][ss] = listPos < currentSize ? listOfSamples[listPos] : 0;
				listPos++;
			}
		}
	}
	
	// Dispose of the list
	free(listOfSamples);
}

/////////////////////////////////////////
int soundLoadFromVorbisFile(char *path) {

	//OggVorbis_File vorbisFile;
	if(ov_fopen(path, &g_soundSampleOggFile) < 0) return -1;
		
	// Add another row to our 3D array for this sound
	if(g_soundSampleCount == 0) {
		g_soundSampleArray3D = malloc(sizeof(int16_t **));
	} else {
		g_soundSampleArray3D = realloc(g_soundSampleArray3D, (g_soundSampleCount + 1) * sizeof(int16_t**));
	}
	g_soundSampleCount++;	
		
	// Fill in the 2D array of buffers / samples on this row
	soundLoadSampleBufferArraysFromVorbisFile(g_soundSampleCount - 1, &g_soundSampleOggFile);
		
	ov_clear(&g_soundSampleOggFile);
	return g_soundSampleCount;
}

///////////////////////////////////////////////////////////////////
//// Background Music -  Stream an OGG file from disk /////////////
///////////////////////////////////////////////////////////////////

int soundFillBackgroundMusicBuffer() {
	size_t samplesRead = 0;
	int samplesToRead = SOUND_BUFFER_SIZE, fileEnd = 0, current_section; 

	while(samplesToRead > 0 && g_soundBackgroundMusicIsPlaying && g_soundBackgroundMusicLoaded ) {
		int rb = ov_read(&g_soundBackgroundMusicOggFile[g_soundBackgroundMusicVorbisFileIndex],
						 (char*)g_soundBackgroundMusicBuffer,
						 SOUND_BUFFER_SIZE,0,2,1,&current_section);		
		if(rb <= 0) { fileEnd = 1; break; }		
		samplesRead += rb / 2;
		samplesToRead -= rb;
	}

	// Pad the end of the buffer with zeros
	if(samplesRead < SOUND_BUFFER_SIZE) {	
		for(int xx = samplesRead; xx <SOUND_BUFFER_SIZE; xx++)	g_soundBackgroundMusicBuffer[xx] = 0;		
	}
	
	// 1 if we're at the end of the file
	return fileEnd;
}

//////////////////////////////
///// Threads ////////////////
//////////////////////////////
int soundBackgroundMusicThread(SceSize argc, void* argv) {

	// Wait for the port to be aquired
	int soundIsReady = 0;
	while(!soundIsReady) soundIsReady = sceAudioOutGetAdopt(SCE_AUDIO_OUT_PORT_TYPE_BGM);
	
	while(g_soundBackgroundMusicThreadRunning) {
		if(g_soundBackgroundMusicIsPlaying) {
		
			int loops = g_soundBackgroundMusicLoop == 0 ? 1 : g_soundBackgroundMusicLoop;			
			while(loops > 0 && g_soundBackgroundMusicIsPlaying && g_soundBackgroundMusicLoaded) {
			
				int fileEnd = 0;  	
				while(!fileEnd && g_soundBackgroundMusicIsPlaying && g_soundBackgroundMusicLoaded) {
						fileEnd = soundFillBackgroundMusicBuffer(); 
						sceAudioOutOutput(g_soundBgmPort, g_soundBackgroundMusicBuffer);								
				}
				
				// rewind the stream
				if(g_soundBackgroundMusicIsPlaying && g_soundBackgroundMusicLoaded) ov_pcm_seek( 
					&g_soundBackgroundMusicOggFile[g_soundBackgroundMusicVorbisFileIndex], 0);
				
				// 0 = loop forever
				if(g_soundBackgroundMusicLoop > 0) loops--;
			}
			g_soundBackgroundMusicIsPlaying = 0;
		} else {
			// Required for the thread to play nicely with Vita2D
			sceKernelDelayThread(0);
		}
	}
	return 0;
}

////////////////////////////////////////////////
int soundMainThread(SceSize argc, void* argv) {

	// Wait for the port to be aquired
	int soundIsReady = 0;
	while(!soundIsReady) soundIsReady = sceAudioOutGetAdopt(SCE_AUDIO_OUT_PORT_TYPE_MAIN);
	
	while(g_soundMainThreadRunning) {
		if(g_soundSamplePlaying > 0) {
			
			int bufferCount = g_soundSampleArray3D[g_soundSamplePlaying-1][0][0], buffer=1;
			while(buffer <= bufferCount && g_soundSamplePlaying > 0) {
				sceAudioOutOutput(g_soundMainPort, g_soundSampleArray3D[g_soundSamplePlaying-1][buffer]);
				buffer++;
			}
						
			g_soundSamplePlaying = 0;
		} else {
			// Required for the thread to play nicely with Vita2D
			sceKernelDelayThread(0);
		}
		if(g_soundNewSampleToPlay > 0) {
			g_soundSamplePlaying = g_soundNewSampleToPlay;
			g_soundNewSampleToPlay = 0;
		}		
	}
	return 0; 
}

/////////////////////////////////////////////////////////
///// Set-up and Clean-up ///////////////////////////////
/////////////////////////////////////////////////////////

void soundInitialise() {

	g_soundBgmPort  = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_BGM,  SOUND_BUFFER_SIZE / 4, 44100, SCE_AUDIO_OUT_MODE_STEREO);
	g_soundMainPort = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_MAIN, SOUND_BUFFER_SIZE, 48000, SCE_AUDIO_OUT_MODE_MONO);
	sceAppMgrAcquireBgmPort();
	sceAudioOutOutput(g_soundBgmPort, NULL);	
	sceAudioOutOutput(g_soundMainPort, NULL);		
	
	
	g_soundBackgroundMusicThreadUid = sceKernelCreateThread("Background Music Thread",  soundBackgroundMusicThread, 0x40, 0x10000, 0, 0, NULL);
	g_soundMainThreadUid            = sceKernelCreateThread("Main Sound Thread",        soundMainThread,            0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(g_soundBackgroundMusicThreadUid, sizeof(int), NULL);
	sceKernelStartThread(g_soundMainThreadUid,            sizeof(int), NULL);
	////
	g_soundBackgroundMusicThreadRunning = 1;
	g_soundMainThreadRunning            = 1;
}

void soundDenitialise() {
	g_soundBackgroundMusicThreadRunning = 0;
	g_soundMainThreadRunning            = 0;
	soundStopBackgroundMusic();
	
	sceKernelWaitThreadEnd(g_soundBackgroundMusicThreadUid, 0, 0);
	sceKernelWaitThreadEnd(g_soundMainThreadUid,            0, 0);
	
	sceAppMgrReleaseBgmPort();
	sceAudioOutReleasePort(g_soundBgmPort);
	sceAudioOutReleasePort(g_soundMainPort);
	soundClearBackgroundMusicOggIfLoaded();
	soundUnloadSamples();
}

/// Wrapper functions /////////////////////////////////////////
void SoundLoadBackgroundMusic(const char* filename) {
	char folderAndFile[50] = "app0:data/sounds/";
	strcat(folderAndFile, filename);
	soundLoadBackgroundMusic(folderAndFile);
}

int SoundLoadSample(const char* filename) {
	char folderAndFile[50] = "app0:data/sounds/";
	strcat(folderAndFile, filename);
	return soundLoadFromVorbisFile(folderAndFile);
}


void SoundStartBackgroundMusicLoop() 		{ soundStartBackgroundMusicLoop();    }
void SoundStopBackgroundMusic()     		{ soundStopBackgroundMusic();         }
void SoundStartBackgroundMusic(int repeats) { soundStartBackgroundMusic(repeats); }
void SoundPlaySample(int sampleNumber) 		{ soundPlaySample(sampleNumber);      }

/*
void SoundStartBackgroundMusicLoop() 		{  }
void SoundStopBackgroundMusic()     		{  }
void SoundStartBackgroundMusic(int repeats) {  }
void SoundPlaySample(int sampleNumber) 		{  }
*/

void InitialiseSound() {
	soundInitialise();
	
	
	// TODO - move out of here
	g_StepSound		 = SoundLoadSample("step.ogg");
	g_SwipeSound	 = SoundLoadSample("swipe.ogg");
	g_HitSound		 = SoundLoadSample("hit.ogg");
	g_NextWaveSound  = SoundLoadSample("nextwave.ogg");
	g_ExplosionSound = SoundLoadSample("explosion.ogg");
}
////////////////////////////////////////////


