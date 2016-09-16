
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

#ifndef MIDAS_MIDAS_GAME_H
#define MIDAS_MIDAS_GAME_H

#define GLM_FORCE_RADIANS 

#include <aeonlib/Engine.h>
#include <aeonlib/Updater.h>
#include "GameScene.h"
#include "EventData.h"
#include "ServiceManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Timer.h"
#include <ScoreManager.h>
using namespace Audio;

class MidasGame : public Aeonphyxius::Updater {
public:
	enum class GAME_STATES{ COUNT_DOWN, WAIT_FIRST, WAIT_SECOND, WAIT_CHAIN,WAIT_FALL, WAIT_REG, ENDED, GAME_OVER, QUIT };
	MidasGame() = default;
	~MidasGame();

	void Start();
	void Update();
	
private:
	void onInitialize();
	void onEvent(EventData *par_evtdata);
	void onExit();
	void onMouseUp(glm::vec2* par_mouse_pos);
	void onMouseDown(glm::vec2* par_mouse_pos);
	void onMouseMove(glm::vec2* par_mouse_pos);

	void onFirstSelected();
	void onClearSelection();
	void onWrongChain();
	void onRighChain();
	void onWarningTime()const ;
	void onTimeEneded();
	void onChainEnded(Core::ScoreManager::Score *par_score);
	void onRebuildEnded();

	GAME_STATES				game_state;
	Aeonphyxius::Engine			*engine;
	EventManager			*event_manager;
	Display::GameScene		game_scene;
	Core::InputManager		*input_manager;
	SoundManager			*sound_manager;
	Core::Timer				timer;
	bool					is_mouse_down;

};


#endif /* defined( MIDAS_MIDAS_GAME_H )*/
