
#include "TextObject.h"
#include "ServiceManager.h"
#include "GenericDelegate.h"

using namespace Core;

void TextObject::onUpdate(){

	auto engine = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	engine->Write(this);

	for (auto child : childs_list){
		if (child){
			child->onUpdate();
		}
	}
}