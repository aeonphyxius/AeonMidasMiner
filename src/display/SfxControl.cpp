#include "SfxControl.h"
#include "ServiceManager.h"
#include "EventManager.h"
#include "GenericDelegate.h"
#include "GameEvents.h"
#include "MidasGame.h"

using namespace Display;
using namespace Core;


void SfxControl::onInitialize(){
	
	TouchObject::onInitialize();

	on_icon_texture = Aeonphyxius::Engine::TEXTURE_SFX_ON;
	off_icon_texture = Aeonphyxius::Engine::TEXTURE_SFX_OFF;

	auto ge = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	obj_size = glm::vec2(ge->GetTextureHeight(Aeonphyxius::Engine::TEXTURE_SFX_ON),
		ge->GetTextureHeight(Aeonphyxius::Engine::TEXTURE_SFX_OFF));

	texture = on_icon_texture;
}

void SfxControl::onButtonClick(){
	auto sound_manager = ServiceManager::getInstance()->getService<SoundManager>(Services::AUDIO);

	if (texture == Aeonphyxius::Engine::TEXTURE_SFX_ON){
		texture = off_icon_texture;
		sound_manager->onPauseSfx();
	}
	else{
		texture = on_icon_texture;
		sound_manager->onResumeSfx();
	}
}