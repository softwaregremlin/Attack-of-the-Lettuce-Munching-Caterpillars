#include "platformSpecific/includeFiles.c"
#include "structures.c"
#include "globals.c"
#include "platformSpecific.c"
#include "saveData.c"
#include "initialise.c"
#include "processFrame.c"
#include "displayFrame.c"

int main() {

	Initialise();

	while (true) {	
		ProcessFrame();
		DisplayFrame();
		WaitForNextFrame();	
	}
	Exit();
	return 0;
}