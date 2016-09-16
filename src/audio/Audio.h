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
#ifndef MIDAS_AUDIO_H
#define MIDAS_AUDIO_H

#include <string>
#include "sdl/SDL_mixer.h"

/**
* Base class for all Audio implementations
*
* Being audio usually platfform dependent, tries to define a set of basic functionalities to be
* implemented in each plattform 
*
*/

namespace Core
{
	class Audio
	{
	public:

		virtual ~Audio() = default;
		// Loaders
		virtual bool initialize() = 0;
		virtual Mix_Music* loadMusicTrack(const std::string par_file_name) = 0;
		virtual Mix_Chunk* loadSfxTrack(const std::string par_file_name, const int par_volumne) = 0;

		virtual void playMusic(Mix_Music* par_music_mixer, bool par_loop = false) = 0;
		virtual void stopMusic() = 0;
		virtual void pauseMusic() = 0;
		virtual void resumeMusic() = 0;

		virtual void playSfx(Mix_Chunk * par_sfx, const bool par_loop = false) = 0;
		virtual void stopSfx(Mix_Chunk * par_sfx) = 0;
		virtual void stopAllSfx() = 0;

		virtual void setSfxVolume(Mix_Chunk* par_sfx, const int par_sfx_volume) const = 0;
		virtual void setMusicVolume(const int par_volume_volume) const = 0;

	};
}

#endif /* defined( MIDAS_AUDIO_H )*/