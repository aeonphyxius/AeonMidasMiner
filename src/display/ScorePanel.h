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
#ifndef MIDAS_SCORE_PANEL_H
#define MIDAS_SCORE_PANEL_H

#include "DisplayObject.h"
#include "TextObject.h"

class EventData;

/**
* Class to encapsulate a clickable object that will exit the game when clicked on
*
*/

namespace Display
{
	class ScorePanel : public DisplayObject {

	public:
		ScorePanel();
		~ScorePanel();
		
		void onInitialize();
		virtual void onUpdate();
		
	private:		
		void onScoreUpdated();
		void onEvent(EventData *par_evtdata);

		std::string		points_text;
		std::string		points_value_text;

		TextObject		*points_text_obj;
		TextObject		*points_obj;
	};
}
#endif /* defined( MIDAS_TIMER_CONTROL_H )*/
