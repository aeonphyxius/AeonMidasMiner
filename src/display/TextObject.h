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
#ifndef MIDAS_TEXTOBJECT_H
#define MIDAS_TEXTOBJECT_H

#include "GameObject.h"
#include <string>
#include <aeonlib/Engine.h>


/**
* Class to encapsulate all objects represented by a text to be rendered
*
* Provides basic specific functionality to render an text and expands the GameObject
* basic functionalities.
*/
class TextObject : public GameObject {

public:
	TextObject() : text(""){};
	virtual ~TextObject() = default;

	const char* getText() const { return text.c_str(); }

	void setText(const std::string par_text) { text = par_text; }
	virtual void onUpdate() ;

protected:
	std::string		text; /* Text contained in this object*/
};

#endif /* defined( MIDAS_TEXTOBJECT_H )*/