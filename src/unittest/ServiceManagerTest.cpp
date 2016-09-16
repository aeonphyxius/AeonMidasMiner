#include "ServiceManager.h"
#include "EventManager.h"
#include "SoundManager.h"

using namespace Core;
/*
void main(int argc, char *argv[]) {

	

		
	ServiceManager::getInstance()->regService <EventManager>(std::string("events"));
	ServiceManager::getInstance()->regService <Core::SoundManager>(std::string("audio"));


	//sm.getService <EventManager>(std::string("events"))->addEventListener ("test_evt",new GenericDelegate());
	
	auto res = ServiceManager::getInstance()->getService <Core::SoundManager>(std::string("audio"))->initializeAudio();
	cout << "Music Initialized: " << (res ? "OK" : "FAILED") << ". Press enter to play the music.\n";
	cin.get();

	// Test a music song
	ServiceManager::getInstance()->getService <Core::SoundManager>(std::string("audio"))->onPlayMusic();
	cout << "Press enter to stop the music.\n";
	cin.get();
	
	// Stop the music as a service
	ServiceManager::getInstance()->getService <Core::SoundManager>(std::string("audio"))->onStopMusic();
	cout << "Press enter to exit .\n";
	cin.get();
	
	
	//return 0;
}
*/