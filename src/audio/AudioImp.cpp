#include "AudioImp.h"
#include <iostream>

using namespace Core;


bool AudioImp::initialize() {
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false; // audio engine init fail
	}
	return true;
}

Mix_Music* AudioImp::loadMusicTrack(std::string par_file_name){
	Mix_Music* music_mixer = Mix_LoadMUS(par_file_name.c_str());
	
	if (music_mixer == 0){
		std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;		
	}	
	
	return music_mixer;
}

Mix_Chunk* AudioImp::loadSfxTrack(std::string par_file_name, int par_volumne){
	
	auto * sfx = Mix_LoadWAV(par_file_name.c_str());
	
	if (sfx == 0){
		std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;		
	}

	Mix_VolumeChunk(sfx, par_volumne);

	return sfx;
	
}

void AudioImp::playMusic(Mix_Music* par_music_mixer, bool par_loop) {
	Mix_PlayMusic(par_music_mixer, par_loop);
}

void AudioImp::stopMusic() {
	Mix_HaltMusic();
}

void AudioImp::pauseMusic() {
	Mix_PauseMusic();	
}

void AudioImp::resumeMusic() {
	Mix_ResumeMusic();
}

void AudioImp::playSfx(Mix_Chunk * par_sfx, const bool par_loop ){
	Mix_PlayChannel(-1, par_sfx, par_loop ? -1: 0);
}

void AudioImp::stopSfx(Mix_Chunk * par_sfx){
	//Mix_
}

void AudioImp::stopAllSfx(){
	Mix_HaltChannel(-1);
}


void AudioImp::setMusicVolume(const int par_volume_volume) const{
	Mix_VolumeMusic(par_volume_volume);
}

void AudioImp::setSfxVolume(Mix_Chunk* par_sfx, const int par_sfx_volume) const{
	Mix_VolumeChunk(par_sfx, par_sfx_volume);
}

