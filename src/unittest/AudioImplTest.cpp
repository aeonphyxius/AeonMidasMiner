/*#include "SoundManager.h"
#include <iostream>

using namespace Audio;

int main(int argc, char *argv[]) {
	
	auto sm = SoundManager();
	auto res = sm.initializeAudio();
	cout << "Music Initialized: " << (res ? "OK" : "FAILED") << ". Press enter to play the music.\n";
	cin.get();
	
	// Test a music song
	sm.onPlayMusic();
	cout << "Press enter to pause the music.\n";
	cin.get();
	
	sm.onPauseMusic();
	cout << "Music paused.\n\n";	
	cout << "Press enter to resume the music.\n";
	cin.get();

	// Test resuming usic
	sm.onResumeMusic();
	cout << "Music resumed.\n\n";
	cout << "Press enter to stop the music.\n\n";
	cin.get();

	// Test stopping music
	sm.onStopMusic();
	cout << "Music stopped.\n";	
	
	// Try to play, pause and play again
	cout << "Press enter to play the music.\n";
	cin.get();
	sm.onPlayMusic();

	cout << "Press enter to pause the music.\n";
	cin.get();
	sm.onPauseMusic();

	//cout << "Press enter to play the music.\n";
	//cin.get();
	//sm.onPlayMusic();
	
	cout << "Press enter to play SWAP_FAILED - SFX.\n";
	cin.get();
	sm.onPlaySfx("SWAP_FAILED");

	cout << "Press enter to play TIME_WARNING - SFX.\n";
	cin.get();
	sm.onPlaySfx("TIME_WARNING");
	
	cout << "Press enter to stop ALL - SFX.\n";
	cin.get();
	sm.onStopAllSfx();	
	
	cout << "Press enter to exit the test.\n";
	cin.get();




	return 0;
}	
	
*/