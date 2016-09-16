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

#ifndef MIDAS_SFX_CONTROL_H
#define MIDAS_SFX_CONTROL_H

#include "TouchObject.h"

using namespace Aeonphyxius;

/**
* Class to encapsulate a clickable sprite with 2 status (on/off)that will enable and disable the game's sfx
*
*/
namespace Display
{
	class SfxControl : public TouchObject {

	public:
		SfxControl() = default;

		virtual void onInitialize();
	private:

		virtual void onButtonClick();

		Engine::Texture 	on_icon_texture;
		Engine::Texture 	off_icon_texture;
	};
}
#endif /* defined( MIDAS_SFX_CONTROL_H )*/
