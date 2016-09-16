#include "TouchObject.h"
#include "GameEvents.h"
#include "EventData.h"
#include "EventManager.h"
#include "ServiceManager.h"
#include "GenericDelegate.h"

using namespace Display;
using namespace Core;

void TouchObject::onInitialize(){
	auto em = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	em->addEventListener(events::MOUSE_UP, GenericDelegate::create <TouchObject, &TouchObject::onEvent>(this));

}
void TouchObject::onEvent(EventData *par_evtdata){	
	if (par_evtdata->getEventName().compare(events::MOUSE_UP) == 0){

		auto res = isPointInside(static_cast<glm::vec2*> (par_evtdata->getData()));

		if (res){
			onButtonClick();
		}
	}
}

/*
bool TouchObject::onClickEvent(glm::vec2 *par_point){
	
	if (par_point->x >= getPosition().x &&
		par_point->x < getSize().x + getPosition().x &&
		par_point->y >= getPosition().y &&
		par_point->y < getSize().y + getPosition().y){

		return true;
	}

	return false;
}
*/
