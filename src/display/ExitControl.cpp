#include "ExitControl.h"
#include "ServiceManager.h"
#include "EventManager.h"
#include "GenericDelegate.h"
#include "GameEvents.h"
#include "MidasGame.h"

using namespace Display;
using namespace Core;
using namespace Aeonphyxius;

void ExitControl::onInitialize(){
	
	// Initialize events
	TouchObject::onInitialize();

	setTexture(Engine::TEXTURE_EXIT);

	auto engine = ServiceManager::getInstance()->getService<Engine>(Services::ENGINE);
	obj_size = glm::vec2(engine->GetTextureHeight(Engine::TEXTURE_EXIT),
						 engine->GetTextureHeight(Engine::TEXTURE_EXIT));
}

void ExitControl::onButtonClick(){
	// Raise on click event to tell the game logic to exit
	ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS)->dispacthEvent(events::GAME_QUIT, new EventData(nullptr , events::GAME_QUIT));
	
}