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
#ifndef MIDAS_TIMER_CONTROL_H
#define MIDAS_TIMER_CONTROL_H

#include <vector>
#include "DisplayObject.h"
#include "TextObject.h"
#include <sdl\SDL.h>

class EventData;

/**
* Class to manage the game's timer.
*
* by default the start time is 60
* by default the warnig time will start at 15s
* the end time is always 0
*
*/
namespace Display
{
	class TimerControl : public DisplayObject {

	public:
		TimerControl();
		const TextObject* getTextObject() const { return clock_text_object.get(); }
		
		void onInitialize();		

		void onProcessTime(Uint32 par_interval);

		void onPauseTimer();
		void onResumeTimer();
		void onStartTimer();
		void onStopTimer();

	private:
		void onEvent(EventData *par_evtdata);

		int							warning_time;			/* time when warning time event will be raised */
		int							start_time;				/* clock's start time */
		int							end_time;				/* end game's time*/
		int							current_time;			/* current time */
		SDL_TimerID					timer_id;				/* SDL timer ID*/
		unique_ptr <TextObject> 	clock_text_object;		/* text object to show the timer */
		unique_ptr <DisplayObject>	scale_action;			/* action that will scale this object when warning time */
	};
}
#endif /* defined( MIDAS_TIMER_CONTROL_H )*/
