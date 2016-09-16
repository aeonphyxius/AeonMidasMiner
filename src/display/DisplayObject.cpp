#include "DisplayObject.h"
#include "ServiceManager.h"
#include "GenericDelegate.h"

using namespace Core;

void DisplayObject::onUpdate(){

	auto engine = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	engine->Render(this);

	for (auto child : childs_list){
		if (child){
			child->onUpdate();
		}		
	}	
}