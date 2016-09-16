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
#ifndef MIDAS_AUDIO_IMP_H
#define MIDAS_AUDIO_IMP_H

#include "Audio.h"
#include "ServiceManager.h"
#include <sdl/SDL_mixer.h>
#include <sdl/SDL.h>
#include <map>

namespace Core
{
	/**
	* Windows audio low level implementation of Audio base class
	*
	*
	*/
	class AudioImp : public Audio{
		
	public:
		AudioImp() = default;
		~AudioImp() = default;
		virtual bool initialize();
		virtual Mix_Music* loadMusicTrack(const std::string par_file_name);
		virtual Mix_Chunk* loadSfxTrack(const std::string par_file_name, const int par_volumne);

		virtual void playMusic(Mix_Music* par_music_mixer, bool par_loop = false);
		virtual void stopMusic();
		virtual void pauseMusic();
		virtual void resumeMusic();		
		virtual void playSfx(Mix_Chunk * par_sfx, const bool par_loop = false);
		virtual void stopSfx(Mix_Chunk * par_sfx);
		virtual void stopAllSfx();
		virtual void setSfxVolume(Mix_Chunk* par_sfx, const int par_sfx_volume) const;
		virtual void setMusicVolume(const int par_volume_volume) const;

	};
}

#endif /* defined( MIDAS_AUDIO_IMP_H )*/