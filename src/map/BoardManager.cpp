#include <BoardManager.h>
#include <ServiceManager.h>
#include <EventManager.h>
#include <GameEvents.h>
#include <GenericDelegate.h>
#include <EventData.h>
#include <ScoreManager.h>

using namespace GemBoard;
using namespace Core;

BoardManager::~BoardManager(){
	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	event_manager->removeEventListener(events::GAME_FIRST_GEM, typeid(BoardManager).name());
	event_manager->removeEventListener(events::GAME_SECOND_GEM, typeid(BoardManager).name());
	event_manager->removeEventListener(events::GAME_START_CHAIN, typeid(BoardManager).name());
	event_manager->removeEventListener(events::GAME_REBUILD_MAP, typeid(BoardManager).name());
	event_manager->removeEventListener(events::GAME_CHECK_MAP, typeid(BoardManager).name());
	event_manager->removeEventListener(events::GAME_DRAGGING, typeid(BoardManager).name());
}

BoardManager::BoardManager(){
	// register listening events
	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	event_manager->addEventListener(events::GAME_FIRST_GEM, GenericDelegate::create <BoardManager, &BoardManager::onEvent>(this));
	event_manager->addEventListener(events::GAME_SECOND_GEM, GenericDelegate::create <BoardManager, &BoardManager::onEvent>(this));
	event_manager->addEventListener(events::GAME_START_CHAIN, GenericDelegate::create <BoardManager, &BoardManager::onEvent>(this));
	event_manager->addEventListener(events::GAME_REBUILD_MAP, GenericDelegate::create <BoardManager, &BoardManager::onEvent>(this));
	event_manager->addEventListener(events::GAME_CHECK_MAP, GenericDelegate::create <BoardManager, &BoardManager::onEvent>(this));
	event_manager->addEventListener(events::GAME_DRAGGING, GenericDelegate::create <BoardManager, &BoardManager::onEvent>(this));	
}

void BoardManager::onInitialize(){	
	
	// create the board and intialize it
	game_board.onBuildNewMap();
	game_board.onInitialize();
}

void BoardManager::onUpdate(){
	game_board.onUpdate();
}

void BoardManager::onEvent(EventData *par_evtdata){

	if (par_evtdata->getEventName().compare(events::GAME_FIRST_GEM) == 0){
		onSelectFirstGem(static_cast<glm::vec2*> (par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::GAME_SECOND_GEM) == 0){
		onSelectSecondGem(static_cast<glm::vec2*> (par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::GAME_START_CHAIN) == 0){
		onStartChain();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_REBUILD_MAP) == 0){
		onRebuildMap();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_CHECK_MAP) == 0){
		onCheckMap();
	}
	else if (par_evtdata->getEventName().compare(events::GAME_DRAGGING) == 0){
		onMouseDrag(static_cast<glm::vec2*> (par_evtdata->getData()));
	}
}

void BoardManager::onMouseDrag(const glm::vec2* par_mouse_pos){
	if (game_board.translateClickToBoard(par_mouse_pos, &second_click))	{
		// Are the 2 point adjacents?
		if (game_board.adjacentPoints(first_click, second_click)){
			onSelectSecondGem(par_mouse_pos);
		}
	}
}

void BoardManager::onSelectFirstGem(const glm::vec2* par_mouse_pos){

	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);

	if (game_board.translateClickToBoard(par_mouse_pos, &first_click) )
	{		
		game_board.enableSelector(first_click);
		event_manager->dispacthEvent(events::GAME_FIRST_SELECTED, new EventData(nullptr, events::GAME_FIRST_SELECTED));
	}

}

void BoardManager::onSelectSecondGem(const glm::vec2* par_mouse_pos){

	game_board.disableSelector();

	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	
	if (game_board.translateClickToBoard(par_mouse_pos, &second_click))
	{
		// Are the 2 point adjacents?
		if (game_board.adjacentPoints(first_click, second_click)){
			// Before the checks swap the board position
			game_board.swapBoardGems(first_click, second_click);

			// Check if there is a chain (result of the swap)
			if (game_board.boardHasChains()){
				game_board.swapGems(first_click, second_click, true);
				event_manager->dispacthEvent(events::GAME_CLEAR_SELECTION, new EventData(nullptr, events::GAME_OK_SELECTION));
			}
			// if not rollback the changes and make the wrong swap effect
			else{
				game_board.swapBoardGems(first_click, second_click);
				game_board.swapGems(first_click, second_click, false);
				event_manager->dispacthEvent(events::GAME_WRONG_SELECTION, new EventData(nullptr, events::GAME_WRONG_SELECTION));
			}
		}
		else{
			event_manager->dispacthEvent(events::GAME_CLEAR_SELECTION, new EventData(nullptr, events::GAME_CLEAR_SELECTION));
		}
	}
	else{
		event_manager->dispacthEvent(events::GAME_CLEAR_SELECTION, new EventData(nullptr, events::GAME_CLEAR_SELECTION));
	}
}

void BoardManager::onStartChain(){

	// get the multiplier to be applied later
	int multiplier = game_board.getMatchesMultiplier();
	cout << multiplier << "\n";
	// Prepare board for the cells fall and continue
	game_board.prepareFall();

	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	event_manager->dispacthEvent(events::GAME_END_CHAIN, new EventData(new ScoreManager::Score(100 * multiplier, multiplier), events::GAME_END_CHAIN));
}


void BoardManager::onRebuildMap(){
	// rebuild map after the cells have fallen
	game_board.rebuildMap();
	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	event_manager->dispacthEvent(events::GAME_REBUILD_MAP_ENDED, new EventData(nullptr, events::GAME_REBUILD_MAP_ENDED));
	
}

void BoardManager::onCheckMap(){
	
	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);	
	
	// Check if there is a chain (result of the swap)
	if (game_board.boardHasChains()){				
		event_manager->dispacthEvent(events::GAME_OK_SELECTION, new EventData(nullptr, events::GAME_OK_SELECTION));
	}
	// If not, swap operation has ended
	else{		
		event_manager->dispacthEvent(events::GAME_FALL_MAP_ENDED, new EventData(nullptr, events::GAME_FALL_MAP_ENDED));
	}
}