#include <MidasGame.h>
#include "SoundManager.h"
#include "GenericDelegate.h"
#include "GameEvents.h"
#include <aeonlib/Engine.h>
#include <ScoreManager.h>

using namespace Core;
using namespace Audio;

MidasGame::~MidasGame(){

	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	event_manager->removeEventListener(events::GAME_QUIT, typeid(MidasGame).name());
	event_manager->removeEventListener(events::MOUSE_UP, typeid(MidasGame).name());
	event_manager->removeEventListener(events::MOUSE_DOWN, typeid(MidasGame).name());
	event_manager->removeEventListener(events::MOUSE_MOVE, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_FIRST_SELECTED, typeid(MidasGame).name());
	event_manager->removeEventListener(events::TIMER_ENDED, typeid(MidasGame).name());
	event_manager->removeEventListener(events::TIMER_WARNING, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_CLEAR_SELECTION, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_OK_SELECTION, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_WRONG_SELECTION, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_END_CHAIN, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_FALL_MAP_ENDED, typeid(MidasGame).name());
	event_manager->removeEventListener(events::GAME_REBUILD_MAP_ENDED, typeid(MidasGame).name());
}

void MidasGame::Start() {	

	game_state = GAME_STATES::WAIT_FIRST;
	// Registering services
	ServiceManager::getInstance()->regService<Aeonphyxius::Engine>(Services::ENGINE);
	ServiceManager::getInstance()->regService<EventManager>(Services::EVENTS);
	ServiceManager::getInstance()->regService<SoundManager>(Services::AUDIO);
	ServiceManager::getInstance()->regService<InputManager>(Services::INPUT);
	ServiceManager::getInstance()->regService<ScoreManager>(Services::SCORE);
	

	// Initializations
	input_manager = ServiceManager::getInstance()->getService<InputManager>(Services::INPUT);
	engine = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	sound_manager = ServiceManager::getInstance()->getService<SoundManager>(Services::AUDIO);
	event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);

	event_manager->addEventListener(events::GAME_QUIT, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::MOUSE_UP, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::MOUSE_MOVE, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::MOUSE_DOWN, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_FIRST_SELECTED, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::TIMER_WARNING, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::TIMER_ENDED, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_CLEAR_SELECTION, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_OK_SELECTION, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_WRONG_SELECTION, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_END_CHAIN, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_FALL_MAP_ENDED, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));
	event_manager->addEventListener(events::GAME_REBUILD_MAP_ENDED, GenericDelegate::create <MidasGame, &MidasGame::onEvent>(this));

	sound_manager->initializeAudio();
	sound_manager->onPlayMusic();
	
	game_scene.onInitialize();

	onInitialize();

	is_mouse_down = false;
	
}

void MidasGame::onInitialize(){
	//game_state = GAME_STATES::WAIT_FIRST;
	//game_scene.onInitializeMap();

	event_manager->dispacthEvent(events::TIMER_START, new EventData(nullptr, events::TIMER_START));
	engine->Start(*this);
}

void MidasGame::Update() {

	input_manager->onUpdate();
	game_scene.onUpdate();

	// Some state need some "delay" in order to process the next order
	// No time to implement a proper states system
	// http://gameprogrammingpatterns.com/state.html
	switch (game_state)
	{
	case GAME_STATES::WAIT_CHAIN:
		if (timer.finished()){			
			event_manager->dispacthEvent(events::GAME_START_CHAIN, new EventData(nullptr, events::GAME_START_CHAIN));
		}		
		break;
	case GAME_STATES::WAIT_FALL:
		if (timer.finished()){			
			event_manager->dispacthEvent(events::GAME_FALL_MAP, new EventData(nullptr, events::GAME_FALL_MAP));
		}
		break;
	case GAME_STATES::WAIT_REG:
		if (timer.finished()){
			event_manager->dispacthEvent(events::GAME_REBUILD_MAP, new EventData(nullptr, events::GAME_REBUILD_MAP));
		}
		break;
	case GAME_STATES::ENDED:
		if (timer.finished()){
			event_manager->dispacthEvent(events::GAME_REBUILD_MAP, new EventData(nullptr, events::GAME_CHECK_MAP));
		}
		break;
	case GAME_STATES::QUIT:		
		event_manager->clearEvents();
		engine->Quit();		
		break;
	}
}

// Events
void MidasGame::onEvent(EventData *par_evtdata){
	
	if (par_evtdata->getEventName().compare(events::GAME_QUIT)==0){
		onExit();
	}
	else if (par_evtdata->getEventName().compare(events::MOUSE_MOVE) == 0){
		onMouseMove(static_cast<glm::vec2*> (par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::MOUSE_DOWN) == 0){
		onMouseDown(static_cast<glm::vec2*> (par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::MOUSE_UP)==0){
		onMouseUp(static_cast<glm::vec2*> (par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::GAME_FIRST_SELECTED) == 0){
		onFirstSelected();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_CLEAR_SELECTION) == 0){
		onClearSelection();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_WRONG_SELECTION) == 0){
		onWrongChain();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_OK_SELECTION) == 0){
		onRighChain();
	}
	else if (par_evtdata->getEventName().compare(events::TIMER_WARNING) == 0){
		onWarningTime();
	}
	else if (par_evtdata->getEventName().compare(events::TIMER_ENDED) == 0){
		onTimeEneded();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_END_CHAIN) == 0){
		onChainEnded(static_cast <ScoreManager::Score *>(par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::GAME_REBUILD_MAP_ENDED) == 0){
		onRebuildEnded();
	}
	
	else if (par_evtdata->getEventName().compare(events::GAME_FALL_MAP_ENDED) == 0){
		game_state = GAME_STATES::WAIT_FIRST;
	}
	
	
}

void MidasGame::onExit() {	
	game_state = GAME_STATES::QUIT;
}


void MidasGame::onMouseDown(glm::vec2* par_mouse_pos) {

	if (game_state == GAME_STATES::WAIT_FIRST){
		event_manager->dispacthEvent(events::GAME_FIRST_GEM, new EventData(par_mouse_pos, events::GAME_FIRST_GEM));
	}
	else if (game_state == GAME_STATES::WAIT_SECOND){
		event_manager->dispacthEvent(events::GAME_FIRST_GEM, new EventData(par_mouse_pos, events::GAME_SECOND_GEM));
	}
	is_mouse_down = true;
}

void MidasGame::onMouseMove(glm::vec2* par_mouse_pos) {
	if (is_mouse_down){
		event_manager->dispacthEvent(events::GAME_DRAGGING, new EventData(par_mouse_pos, events::GAME_DRAGGING));
	}
}


void MidasGame::onMouseUp(glm::vec2* par_mouse_pos) {
	is_mouse_down = false;
	
}

void MidasGame::onFirstSelected(){
	sound_manager->onPlaySfx("GEM"); 
	game_state = GAME_STATES::WAIT_SECOND;
}

void MidasGame::onClearSelection(){
	is_mouse_down = false;
	game_state = GAME_STATES::WAIT_FIRST;
}

void MidasGame::onWrongChain(){
	is_mouse_down = false;
	game_state = GAME_STATES::WAIT_FIRST;
	sound_manager->onPlaySfx("SWAP_FAILED");
}

void MidasGame::onRighChain(){
	is_mouse_down = false;
	game_state = GAME_STATES::WAIT_CHAIN;
	timer.start(.5f);
	sound_manager->onPlaySfx("SWAP_SUCCESS");
	
}
	
void MidasGame::onWarningTime()const{
	sound_manager->onPlaySfx("TIME_WARNING",true);
}

void MidasGame::onTimeEneded() {
	game_state = GAME_STATES::GAME_OVER;
	sound_manager->onStopAllSfx();
}

void MidasGame::onChainEnded(ScoreManager::Score *par_score) {
	//cout << par_score->points;
	event_manager->dispacthEvent(events::ADD_POINTS, new EventData( par_score, events::ADD_POINTS));
	timer.start(.3f);
	game_state = GAME_STATES::WAIT_REG;
	
}
void MidasGame::onRebuildEnded(){
	timer.start(.3f);
	game_state = GAME_STATES::ENDED;
	//cout << "OnRebuildEnded";
}
