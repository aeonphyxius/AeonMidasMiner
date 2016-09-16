#include "ScorePanel.h"
#include "EventManager.h"
#include "ServiceManager.h"
#include "GenericDelegate.h"
#include "GameEvents.h"
#include "EventData.h"
#include <ScoreManager.h>
#include <string>

using namespace Display;
using namespace Core;


ScorePanel::ScorePanel(){	
	points_obj = new TextObject();
	points_text_obj = new TextObject();	
}

ScorePanel::~ScorePanel(){
	delete points_obj;
	delete points_text_obj;
	
}

void ScorePanel::onInitialize(){
	//register events
	auto em = ServiceManager::getInstance()->getService<EventManager>(Services::EVENTS);
	em->addEventListener(events::SCORE_UPDATED, GenericDelegate::create <ScorePanel, &ScorePanel::onEvent>(this));

	// load panel texture
	setTexture(Aeonphyxius::Engine::TEXTURE_SCORE_PANEL);

	// Score text and value
	points_text.assign("Points: ");
	points_obj->setPosition(glm::vec3(30.f, 40.f, 1));
	points_obj->setScale(glm::vec3(0.5f, 0.5f, 1));
	points_obj->setText(points_text);

	points_value_text.assign("0");	
	points_text_obj->setText(points_value_text);
	points_text_obj->setPosition(glm::vec3(70.f, 70.f, 1));
	points_text_obj->setScale(glm::vec3(0.7f, 0.7f, 1));
	
	addChild(points_obj);
	addChild(points_text_obj);

	auto ge = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	obj_size = glm::vec2(ge->GetTextureHeight(Aeonphyxius::Engine::TEXTURE_SCORE_PANEL),
		ge->GetTextureHeight(Aeonphyxius::Engine::TEXTURE_SCORE_PANEL));

}

void ScorePanel::onUpdate(){
	DisplayObject::onUpdate();

	auto score = ServiceManager::getInstance()->getService<ScoreManager>(Services::SCORE);
	points_value_text = std::to_string(score->getPoints());
	points_text_obj->setText(points_value_text);

	auto engine = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	engine->Write(points_obj);
	engine->Write(points_text_obj);

}

void ScorePanel::onEvent(EventData *par_evtdata){
	
	if (par_evtdata->getEventName().compare(events::SCORE_UPDATED) == 0){
		onScoreUpdated();
	}
}

void ScorePanel::onScoreUpdated(){

}