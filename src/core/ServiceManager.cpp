#include "ServiceManager.h"

using namespace Core;

static ServiceManager *instance = nullptr;

ServiceManager * ServiceManager::getInstance(){
	if (!instance)	{
		instance = new (std::nothrow) ServiceManager();
	}
	return instance;
}


ServiceManager::~ServiceManager(){
	// clean up and exit
	for (servicelist_t::iterator it = serviceslist.begin(); it != serviceslist.end(); it++) {
		//delete it->second;
	}
}