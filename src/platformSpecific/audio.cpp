/*
	VitaPong
	Copyright (C) 2016-2017, NamelessGhoul0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

SoLoud::Soloud gSoloud;
SoLoud::Wav gSamples[10];
SoLoud::WavStream gMusic[10];

int SoLoudMusicCount = 0, soLoundSampleCount = 0;

void InitialiseSound() {
	gSoloud.init();
}

int SoundLoadBackgroundMusic(const char* filename) {
	char folderAndFile[50] = "app0:data/sounds/";
	strcat(folderAndFile, filename);
	SoLoudMusicCount++;
	gMusic[SoLoudMusicCount].load(folderAndFile);	
	return SoLoudMusicCount;
}

int SoundLoadSample(const char* filename) {
	char folderAndFile[50] = "app0:data/sounds/";
	strcat(folderAndFile, filename);
	soLoundSampleCount++;
	gSamples[soLoundSampleCount].load(folderAndFile);	
	return soLoundSampleCount;
}

void SoundStartBackgroundMusicLoop(int musicIndex) {
	for(int ss=0; ss<10; ss++) {
		gMusic[ss].stop();
	}
	gMusic[musicIndex].setLooping(true);
	gSoloud.play(gMusic[musicIndex]);
}

void SoundStartBackgroundMusic(int musicIndex, int repeats) {
	for(int ss=0; ss<10; ss++) {
		gMusic[ss].stop();
	}
	gMusic[musicIndex].setLooping(false);
	gSoloud.play(gMusic[musicIndex]);
}



void SoundPlaySample(int sampleIndex) {
	gSoloud.play(gSamples[sampleIndex]);
}

void SoundDenitialise() {
	gSoloud.deinit();
}




#ifdef __cplusplus
}
#endif
