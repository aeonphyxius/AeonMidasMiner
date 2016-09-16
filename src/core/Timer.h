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
#ifndef MIDAS_TIMER_H
#define MIDAS_TIMER_H

#include <Ease.h>
#include <time.h>
#include <sys\timeb.h>
#include <winsock2.h>


/**
* This class builds a small timer, using the Ease functions to give the current delta
*
* uses a windows implementation for timeval (winsock2.h)
*
* used as a reference :/*
* http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Elapsed-Time.html
*
*/

using namespace tweens;

namespace Core
{
	class Timer
	{
	public:

		enum { ONEMILLION = 1000000 };

		Timer();

		virtual void start(const float time, const bool loop = false, const float startTime = 0.0f);
		virtual float getDelta(EaseType easetype = EaseType::linear);
		virtual bool finished();
		virtual bool started() const;
		virtual void stop();
		virtual float getDuration() const { return time; }

	private:

		void getTimeOfDay(timeval * par_tp);
		int timeval_subtract(timeval* par_result, timeval* par_x, timeval* par_y);

		float deltaTime;			/* delta time */
		float realDeltaTime;		/* real delta time (no conversion) */
		double realElapsedTime;		/* real elapsed delta time */
		float time;					/* */
		bool loop;					/* is this timer looping */
		Ease ease;					/* easy type (to calculate the */
		timeval startTime;			/* start time in time of the day */
		timeval current;			/* curent time in time of the day*/
		timeval elapsed;			/* elapsed time in time interval */
	};
}


#endif /* defined( MIDAS_TIMER_H )*/
