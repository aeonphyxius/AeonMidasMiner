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
#ifndef MIDAS_DISPLAY_OBJECT_H
#define MIDAS_DISPLAY_OBJECT_H

#include <aeonlib/Engine.h>
#include "GameObject.h"

using namespace Aeonphyxius;

/**
* Class to encapsulate all objects represented by a texture in our world
*
* Provides basic specific functionality to render an sprite and expands the GameObject
* basic functionalities
*
*/
class DisplayObject : public GameObject {

	public:
		DisplayObject() :texture(Engine::NONE){};
		virtual ~DisplayObject() = default;

		virtual Engine::Texture getTexture() const { return texture; }
		virtual void setTexture	(const Engine::Texture par_texture) { texture = par_texture; }
		virtual void onUpdate();

	protected:
		Engine::Texture texture;		/* texture to be rendered */
};

#endif /* defined( MIDAS_DISPLAY_OBJECT_H )*/