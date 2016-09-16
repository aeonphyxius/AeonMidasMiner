#include "TimerControl.h"
#include <iostream>
#include <string>
#include <iostream>
#include "ServiceManager.h"
#include <EventManager.h>
#include <GameEvents.h>
#include <EventData.h>
#include <GenericDelegate.h>
#include <ScaleTo.h>

using namespace Core;
using namespace Display;

// C->C++ Wrapper for SDL_Timer
Uint32 process(Uint32 par_interval, void* par_param)
{	
	auto timer_control_obj = static_cast<TimerControl*>(par_param);
	timer_control_obj->onProcessTime(par_interval);
	return par_interval;
}

TimerControl::TimerControl() : 
	warning_time(15), 
	start_time(60), 
	end_time(0), 
	current_time(0), 
	timer_id(0){

	clock_text_object = unique_ptr <TextObject> (new TextObject);
	texture = Engine::NONE;
}

void TimerControl::onInitialize(){	
	current_time = start_time;
	clock_text_object->setText(std::string(std::to_string(current_time)));
	addChild(clock_text_object.get());

	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	
	event_manager->addEventListener(events::TIMER_START, GenericDelegate::create <TimerControl, &TimerControl::onEvent>(this));
	event_manager->addEventListener(events::TIMER_STOP, GenericDelegate::create <TimerControl, &TimerControl::onEvent>(this));	
}


// Events
void TimerControl::onEvent(EventData *par_evtdata){	
	if (par_evtdata->getEventName().compare(events::TIMER_START) == 0){
		onStartTimer();
	}
	if (par_evtdata->getEventName().compare(events::TIMER_STOP) == 0){
		onStopTimer();
	}
}

void TimerControl::onProcessTime(Uint32 par_interval){
	--current_time;
	if (current_time == warning_time){
		auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
		event_manager->dispacthEvent(events::TIMER_WARNING, new EventData(nullptr, events::TIMER_WARNING));	
		scale_action.release();
		scale_action = unique_ptr <DisplayObject>(new tweens::ScaleTo(clock_text_object->getScale(), glm::vec3(.6f, .6f, 1), 0.4f, true));
		clock_text_object->addChild(scale_action.get());
	}
	if (current_time == end_time ){

		clock_text_object->removeChild(scale_action.get());
		scale_action.release();
		clock_text_object->setScale(glm::vec3(1.f, 1.f, 1.f));
		auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
		event_manager->dispacthEvent(events::TIMER_ENDED, new EventData(nullptr, events::TIMER_ENDED));		

		SDL_RemoveTimer(timer_id);
	}

	clock_text_object->setText(std::string(std::to_string(current_time)));
}

void TimerControl::onStopTimer(){
	// Raise end timer event
	SDL_RemoveTimer(timer_id);
}

void TimerControl::onPauseTimer(){
	// Raise end timer event
	SDL_RemoveTimer(timer_id);
}

void TimerControl::onResumeTimer(){
	onStartTimer();
}

void TimerControl::onStartTimer(){
	int32_t delay = (1 * 1000);
	timer_id = SDL_AddTimer(delay, process, this);
}