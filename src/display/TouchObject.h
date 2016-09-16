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
#ifndef MIDAS_TOUCH_OBJECT_H
#define MIDAS_TOUCH_OBJECT_H

#include "DisplayObject.h"
#include <sdl\SDL.h>

class EventData;

/**
* Class to encapsulate all display objects (sprite / texture) represented in our world that will be
* recieving events ( click or touch event )
*
* Provides basic specific functionality to render an sprite that receives events (click)
*
*/

namespace Display
{
	class TouchObject : public DisplayObject {

	public:
		TouchObject() = default;

		virtual void onInitialize();
		virtual void onEvent(EventData *par_evtdata);
		

	protected:		
		virtual void onButtonClick() = 0;
	};
}
#endif /* defined( MIDAS_TOUCH_OBJECT_H )*/
