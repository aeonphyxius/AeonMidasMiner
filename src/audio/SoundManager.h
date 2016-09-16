/****************************************************************************
Copyright (c) 2016 Alejandro Santiago Varela

http://www.aeonphyxius.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef MIDAS_SOUNDMANAGER_H
#define MIDAS_SOUNDMANAGER_H

#include <sdl/SDL_mixer.h>
#include <map>
#include <jansson/jansson.h>
#include <Audio.h>
#include <ServiceManager.h>

using namespace std;

/**
* SoundManager encapsulates all the audio logic. 
*
* Responding to game events will manage the low level audio implementation in order to play / pause 
* stop the different music tracks and sfx
*/
namespace Audio
{
	class SoundManager: public Core::Service {
		
	public:
		SoundManager() : music_volume(0), sfx_volume(0), audio_handler(nullptr), music_mixer(nullptr), sfx_enabled(true){}
		~SoundManager();


		bool initializeAudio();
		void onPlayMusic( bool par_loop = false);
		void onStopMusic();
		void onPauseMusic();
		void onResumeMusic();
		void onPlaySfx(const std::string par_sfx, const bool par_loop  = false);
		void onStopAllSfx();
		void onPauseSfx();
		void onResumeSfx();

	private:

		bool onLoadSfx(const json_t * par_music_conf);
		bool onLoadMusic(const json_t * par_music_conf);
		void onLoadAudioConf(const json_t * par_music_conf);

		Mix_Music							*music_mixer;	/* music track*/
		std::map<std::string, Mix_Chunk*>	sfx_list;		/* sfk list */
		std::unique_ptr <Core::Audio>		audio_handler;	/* low level audio implementation (platfform dependet*/
		int									music_volume;	/* music volume to be applied*/
		int									sfx_volume;		/* sfx volume*/
		bool								sfx_enabled;	/* are the sfx enabled */
	};
}
#endif /* defined( MIDAS_SOUNDMANAGER_H )*/
