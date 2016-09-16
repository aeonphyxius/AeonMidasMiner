/****************************************************************************
Copyright (c) 2016 Alejandro Santiago Varela

http://www.aeonphyxius.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef MIDAS_EVTMGR_H
#define MIDAS_EVTMGR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "ServiceManager.h"


class GenericDelegate;
class EventData;

using namespace std;

/**
* Adds functionality to register / deregister events. Once an event is called, all the registered listeners
* will recieve a call
*
*/
class EventManager : public Core::Service
{

public:

	typedef std::vector<GenericDelegate*> TEventDelegateList;
	typedef std::map<std::string, TEventDelegateList> TEventDelegateDictionary;
	
	EventManager() = default;
	~EventManager();

	void addEventListener(const string par_type, GenericDelegate* par_delegate);	
	void removeEventListener(const std::string par_evt_type, const std::string par_class_name);
	void dispacthEvent(const string par_type, EventData* par_input) const;
	void clearEvents();

private:
	
	TEventDelegateDictionary delegates_map;		// List of events and all the objects registered to them
};

#endif
