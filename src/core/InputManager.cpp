#include "InputManager.h"
#include <sdl\SDL_events.h>
#include <EventManager.h>
#include "EventData.h"
#include "GameEvents.h"
#include <glm/glm.hpp>

using namespace Core;

void InputManager::onUpdate(){
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		onHandleEvent(&event);
	}

}


void InputManager::onHandleEvent(SDL_Event* par_event)
{
	switch (par_event->type) {
		case SDL_QUIT:			
			ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS)->dispacthEvent(events::GAME_QUIT, new EventData(nullptr, events::GAME_QUIT));
			break;
		case SDL_KEYDOWN:
			switch (par_event->key.keysym.sym) {
			case SDLK_ESCAPE:
				ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS)->dispacthEvent(events::GAME_QUIT, new EventData(nullptr, events::GAME_QUIT));
			case SDLK_q:
				//gameover = 1;
				break;
			}			
		break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseDown();
		break;
		case SDL_MOUSEBUTTONUP:						
			onMouseUp();
		break;
		case SDL_MOUSEMOTION:
			onMouseMove();
		break;
		
		default:
		break;
	}		
}

void InputManager::onMouseMove(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	auto mouse_pos = new glm::vec2(x, y);

	ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS)->dispacthEvent(events::MOUSE_UP, new EventData(mouse_pos, events::MOUSE_MOVE));
}
	
void InputManager::onMouseDown(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	auto mouse_pos = new glm::vec2(x, y);

	ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS)->dispacthEvent(events::MOUSE_UP, new EventData(mouse_pos, events::MOUSE_DOWN));
}

void InputManager::onMouseUp(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	auto mouse_pos = new glm::vec2(x, y);

	ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS)->dispacthEvent(events::MOUSE_UP, new EventData(mouse_pos, events::MOUSE_UP));
}