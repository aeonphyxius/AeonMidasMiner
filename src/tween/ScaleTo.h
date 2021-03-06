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

#ifndef MIDAS_SCALE_TO_H
#define MIDAS_SCALE_TO_H

#include <DisplayObject.h>
#include <Ease.h>
#include <Timer.h>

/**
* Using a timer will scale the parent object between 2 sizes
*
*/

namespace tweens
{
	class ScaleTo : public DisplayObject
	{
	public:

		ScaleTo(const glm::vec3 par_origin, const glm::vec3 par_target, float par_seconds, bool par_loop = false, EaseType curve = EaseType::linear);
		void onUpdate();

	private:

		bool			loop;			/* is looping this operation */
		bool			to_target;		/* in case of looping, have we arrived to target */
		glm::vec3		origin;			/* origin size */
		glm::vec3		target;			/* target size */
		float           time;			/* time toperform the move effect */
		Core::Timer	    timer;			/* timer to be used to calculate the move effect */
		EaseType		curve;			/* type of curve used in this action */
	};
}

#endif /* defined( MIDAS_SCALE_TO_H )*/