#include "EventManager.h"
#include "GenericDelegate.h"
#include "EventData.h"

EventManager::~EventManager()
{	
	for (auto &map_it : delegates_map){		
		for (auto &vec_it : map_it.second){			
			delete vec_it;
			vec_it = nullptr;
		}
		// Delete the vector for each event
		map_it.second.clear();
	}
	// delete the map of all events
	delegates_map.clear();

}

void EventManager::clearEvents(){
	for (auto &map_it : delegates_map){		
		// Delete the vector for each event
		map_it.second.clear();
	}
	// delete the map of all events
	delegates_map.clear();
}

void EventManager::addEventListener(const string par_evt_type, GenericDelegate* par_dele)
{
	auto map_it = delegates_map.find(par_evt_type);

	if (map_it == delegates_map.end()){
		TEventDelegateList new_list;
		new_list.push_back(par_dele);
		delegates_map[par_evt_type] = new_list;

	}
	else{
		// Check if the listener was already registered
		auto vec_it = std::find(map_it->second.begin(), map_it->second.end(), par_dele);
		if (vec_it == map_it->second.end())
		{
			map_it->second.push_back(par_dele);
		}
	}
	
}

void EventManager::dispacthEvent(const string par_evt_type, EventData* par_evtdata) const
{
	auto map_it = delegates_map.find(par_evt_type);

	if (map_it != delegates_map.end())
	{		
		for (auto &vec_it : map_it->second ){
			vec_it->OnEvent(par_evtdata);
		}
	}
}


void EventManager::removeEventListener(const std::string par_evt_type, const std::string par_class_name)
{
	auto map_it = delegates_map.find(par_evt_type);

	if (map_it != delegates_map.end()){

		auto vec_it = map_it->second;
		auto index = 0;

		map_it->second.clear();

		/*for (auto &vec_it : map_it->second){			
			if (vec_it->getClassTypeName().compare(par_class_name) == 0) {								
				 erase(map_it->second.begin() + index);
				//delete vec_it;
				//vec_it = nullptr;
			}
			++index;
		}	*/	
	}

}