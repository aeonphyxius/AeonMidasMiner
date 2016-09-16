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

#ifndef MIDAS_EVENT_DATA_H
#define MIDAS_EVENT_DATA_H

using namespace std;

/**
* class that encapsulates the data send when an event is raised
*
*/

class EventData
{
public:
	typedef void *InstancePtr;

	EventData() : evt_data(0), evt_name(""){}

	EventData(InstancePtr par_data, std::string par_evt_name) :
		evt_data(par_data), 
		evt_name(par_evt_name)
	{}

	inline InstancePtr	getData()		const { return evt_data; };
	inline std::string 	getEventName()	const { return evt_name; };

private:
	InstancePtr		evt_data;		/* data contained in this event (if needed) */
	std::string		evt_name;		/* event name */

};

#endif /* defined( MIDAS_EVENT_DATA_H )*/