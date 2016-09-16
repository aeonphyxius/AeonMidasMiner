#include "SoundControl.h"
#include "ExitControl.h"
#include "ServiceManager.h"
#include "EventManager.h"
#include "GenericDelegate.h"
#include "GameEvents.h"
#include "MidasGame.h"

using namespace Display;
using namespace Core;

void SoundControl::onInitialize(){

	TouchObject::onInitialize();

	on_icon_texture = Aeonphyxius::Engine::TEXTURE_MUSIC_ON;
	off_icon_texture = Aeonphyxius::Engine::TEXTURE_MUSIC_OFF;

	auto engine = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	obj_size = glm::vec2(engine->GetTextureHeight(Aeonphyxius::Engine::TEXTURE_EXIT),
		engine->GetTextureHeight(Aeonphyxius::Engine::TEXTURE_EXIT));
	
	texture = on_icon_texture;
}


void SoundControl::onButtonClick(){
	auto sound_manager = ServiceManager::getInstance()->getService<SoundManager>(Services::AUDIO);

	if (texture == Aeonphyxius::Engine::TEXTURE_MUSIC_ON){
		texture = off_icon_texture;
		sound_manager->onPauseMusic();		
	}
	else{
		texture = on_icon_texture;
		sound_manager->onResumeMusic();
	}	
}