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

/* Easing Function as referenced here http://easings.net/ */
/* EG: used when gems fall down scale or move in the board */

#ifndef MIDAS_EASE_H
#define MIDAS_EASE_H

#include <iostream>
#include <math.h>

/**
* This class contains the ease functions for the twenning engine
*
* only linear and bouceOut have been implemtned for this example
*
*/
namespace tweens
{
	enum class EaseType
	{
		linear,
		bounceOut
	};

	class Ease
	{
	public:
		Ease(EaseType par_type = EaseType::linear) : type(EaseType::linear) {};

		EaseType getType() const { return type; }
		void setType(const EaseType par_type) { type = par_type; }

		float get(float t /*current (t)*/, float d /*total (t)*/) const {
			if (t >= d){
				//std::cout << "return 0";
				return 0;
			}

			switch (type)
			{
			case EaseType::linear:				
				return t / d;
				break;
			case EaseType::bounceOut:
				return (bounce(t, d));
				break;
			}
			return 0;
		}
		

		static float bounce(float t, const float d)
		{
			float value;
			if ((t /= d) < (1.f / 2.75f)){
				value = 1.0f*(7.5625f*t*t);
			}
			else if (t < (2.f / 2.75f)){
				float postFix = t -= (1.5f / 2.75f);
				value = 1.0f*(7.5625f*(postFix)*t + .75f);
			}
			else if (t < (2.5f / 2.75f)){
				float postFix = t -= (2.25f / 2.75f);

				value = 1.0f*(7.5625f*(postFix)*t + .9375f);
			}
			else{
				float postFix = t -= (2.625f / 2.75f);
				value = 1.0f*(7.5625f*(postFix)*t + .984375f);
			}
			
			return value;
		}

	private:
		EaseType type;
	};
}



#endif /* defined( MIDAS_EASE_H )*/