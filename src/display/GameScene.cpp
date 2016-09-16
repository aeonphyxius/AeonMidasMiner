#include "GameScene.h"
#include "GameObject.h"
#include "DisplayObject.h"
#include "TimerControl.h"
#include "SoundControl.h"
#include "SfxControl.h"
#include "ExitControl.h"
#include "ScorePanel.h"
#include <ServiceManager.h>

using namespace Display;
using namespace Core;
using namespace Aeonphyxius;

void GameScene::onInitialize(){

	// Background
	auto bg = new DisplayObject();
	bg->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	bg->setTexture(Engine::TEXTURE_BACKGROUND);	
	scene_gos.push_back(bg);

	
	// ********* ui elements
	// Timer control
	timer_control = std::unique_ptr<TimerControl> (new TimerControl);
	timer_control->setPosition(glm::vec3(82, 430, 0));
	timer_control->setScale(glm::vec3(1.8f, 1.8f, 1.f));
	timer_control->onInitialize();
	scene_gos.push_back(timer_control.get());

	// OF / OFF Muisic
	auto sound_icon = new SoundControl();
	sound_icon->onInitialize();
	sound_icon->setPosition(glm::vec3(550, 5, 0));
	sound_icon->setScale(glm::vec3(0.5f, 0.5f, 0));
	scene_gos.push_back(sound_icon);

	// OF / OFF SFX
	auto sfx_icon = new SfxControl();
	sfx_icon->onInitialize();
	sfx_icon->setPosition(glm::vec3(600, 5, 0));
	sfx_icon->setScale(glm::vec3(0.5f, 0.5f, 0));
	scene_gos.push_back(sfx_icon);

	// Exit icon
	auto sfx_exit = new ExitControl();
	sfx_exit->onInitialize();
	sfx_exit->setPosition(glm::vec3(650, 5, 0));
	sfx_exit->setScale(glm::vec3(0.5f, 0.5f, 0));
	scene_gos.push_back(sfx_exit);

	// Score Panel
	auto score_panel = new ScorePanel();
	score_panel->onInitialize();
	score_panel->setPosition(glm::vec3(10, 10, 0));
	score_panel->setScale(glm::vec3(1.5f, 1.5f, 1.f));
	scene_gos.push_back(score_panel);

	// map
	game_board = std::unique_ptr<BoardManager> (new BoardManager);
	game_board->onInitialize();
}

void GameScene::onUpdate(){

	for (auto go : scene_gos){
		go->onUpdate();
	}
	game_board->onUpdate();

	auto engine = ServiceManager::getInstance()->getService<Engine>(Services::ENGINE);
	engine->Write(timer_control->getTextObject());

}