#include <ScoreManager.h>
#include <GameEvents.h>
#include <GenericDelegate.h>
#include <EventManager.h>

using namespace Core;

ScoreManager::ScoreManager() : score(), high_score(0){

	auto event_manager = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	event_manager->addEventListener(events::ADD_POINTS, GenericDelegate::create <ScoreManager, &ScoreManager::onEvent>(this));
	event_manager->addEventListener(events::RESET_POINTS, GenericDelegate::create <ScoreManager, &ScoreManager::onEvent>(this));
	event_manager->addEventListener(events::SAVE_POINTS, GenericDelegate::create <ScoreManager, &ScoreManager::onEvent>(this));


}

void ScoreManager::onEvent(EventData *par_evtdata){

	if (par_evtdata->getEventName().compare(events::ADD_POINTS) == 0){
		onAddPoints(static_cast<Score*> (par_evtdata->getData()));
	}
	else if (par_evtdata->getEventName().compare(events::SAVE_POINTS ) == 0){
		onSavePoints();
	}
	else if (par_evtdata->getEventName().compare(events::RESET_POINTS) == 0){
		onResetPoints();
	}
}


void ScoreManager::onAddPoints(Score* par_score){
	//cout << par_score->points;
	score.points += par_score->points;
	score.multiplier += par_score->multiplier;
}

void ScoreManager::onSavePoints(){
	if (high_score < score.points){
		high_score = score.points;
	}
}

void ScoreManager::onResetPoints(){
	score = Score();
}