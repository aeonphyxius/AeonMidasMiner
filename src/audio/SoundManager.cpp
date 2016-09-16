#include "SoundManager.h"
#include "AudioImp.h"

using namespace Core;
using namespace Audio;

SoundManager::~SoundManager(){

	// Release all music and sfx
	Mix_FreeMusic(music_mixer);
		
	audio_handler.release();

	// Quite the music subsystem
	Mix_Quit();
}

bool SoundManager::initializeAudio()
{
	auto res = false;
	if (audio_handler == nullptr) {
		// Depending on the platform, we can load different audio implementations
		audio_handler = std::make_unique< AudioImp>();
	}

	res = audio_handler->initialize();
	if (!res) {
		return false;
	}
	// loas sound conf file
	auto json_err = json_error_t();
	auto music_conf = json_load_file("./assets/conf/music_conf.json", 0, &json_err);

	if (music_conf == nullptr){
		return false;
	}
	
	onLoadAudioConf(music_conf);

	// Music song load procedure
	res = onLoadMusic(music_conf);
	if (!res) {
		return false;
	}

	// SFX load procedure	
	res = onLoadSfx(music_conf);	
	if (!res) {
		return false;
	}

	// release the json object
	json_decref(music_conf);
	return true;
}

void SoundManager::onLoadAudioConf(const json_t * par_music_conf){
	
	music_volume	= (int) json_integer_value(json_object_get(par_music_conf, "music_volume"));
	sfx_volume		= (int) json_integer_value(json_object_get(par_music_conf, "sfx_volume"));
	
	audio_handler->setMusicVolume(music_volume);
}

bool SoundManager::onLoadMusic(const json_t * par_music_conf){
	
	auto music_track = json_string_value(json_object_get(par_music_conf, "music_track"));
	music_mixer = audio_handler->loadMusicTrack(music_track);

	if (music_mixer == nullptr) {
		return false;
	}
	return true;
}
bool SoundManager::onLoadSfx(const json_t * par_music_conf){

	auto sfx_conf = json_object_get(par_music_conf, "sfx_list");
	for (unsigned int i = 0; i < json_array_size(sfx_conf); ++i) {
		
		auto sfx_data = json_array_get(sfx_conf, i);
		if (sfx_data){
			// Get the name and resource path
			auto sfx_name = json_string_value (json_object_get(sfx_data, "sfx_name"));
			auto sfx_resource = json_string_value(json_object_get(sfx_data, "sfx_asset"));
			
			// build the sfx and insert it in the sfx list
			auto sfx = audio_handler->loadSfxTrack(sfx_resource, sfx_volume);
			
			sfx_list.insert(make_pair(sfx_name, sfx));
		}
	}

	// Check if all sfx have been loaded
	if (sfx_list.size() != json_array_size(sfx_conf)){
		return false;
	}

	return true;
}
// Music
void SoundManager::onPlayMusic(bool par_loop) {
	audio_handler->playMusic(music_mixer, par_loop);
}

void SoundManager::onStopMusic() {
	audio_handler->stopMusic();
}

void SoundManager::onPauseMusic() {
	audio_handler->pauseMusic();
}

void SoundManager::onResumeMusic() {
	audio_handler->resumeMusic();
}

// SFX
void SoundManager::onPlaySfx(const std::string par_sfx, const bool par_loop){
	if (sfx_enabled){
		audio_handler->playSfx(sfx_list[par_sfx], par_loop);
	}	
}

void SoundManager::onStopAllSfx(){
	audio_handler->stopAllSfx();
}

void SoundManager::onPauseSfx(){
	sfx_enabled = false;
}

void SoundManager::onResumeSfx(){
	sfx_enabled = true;
}



