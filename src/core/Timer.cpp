#include "Timer.h"
#include <stdint.h>
#include <iostream>

using namespace Core;

Timer::Timer()
: time(0.f)
, loop(false)
, deltaTime(0.f)
, realDeltaTime(0.f)
, realElapsedTime(0.f)
{

}

bool Timer::started() const
{
	return time != 0;
}

void Timer::stop()
{
	time = 0.0f;
	loop = false;
}

void Timer::getTimeOfDay(timeval * par_tp)
{
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	static const  uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;

	par_tp->tv_sec = (long)((time - EPOCH) / 10000000L);
	par_tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
	
}

void Timer::start(float time, bool loop, float sTime)
{
	this->time = time;
	this->loop = loop;

	getTimeOfDay(&startTime);
}

bool Timer::finished()
{
	return getDelta() == 0;
}

float Timer::getDelta(EaseType easetype)
{
	if (time == 0.0f){ // not started		
		return 1.0f;
	}

	getTimeOfDay(&current);
	timeval_subtract(&elapsed, &current, &startTime);

	float fcur = elapsed.tv_sec + (float)elapsed.tv_usec / ONEMILLION;

	if (loop)
	{
		int cycles = static_cast <int> (fcur / time);
		fcur -= time * cycles;
	}

	ease.setType(easetype);
	float delta = ease.get(fcur, time);
	//std::cout << delta << "\n";
	return delta;
}
/*
* http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Elapsed-Time.html
*
* Subtract the `struct timeval' values X and Y,
* storing the result in RESULT.
* Return 1 if the difference is negative, otherwise 0.
*/
int Timer::timeval_subtract(timeval* result, timeval* x, timeval* y)
{
	// Perform the carry for the later subtraction by updating y
	if (x->tv_usec < y->tv_usec)
	{
		int nsec = (y->tv_usec - x->tv_usec) / ONEMILLION + 1;
		y->tv_usec -= ONEMILLION * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > ONEMILLION)
	{
		int nsec = (x->tv_usec - y->tv_usec) / ONEMILLION;
		y->tv_usec += ONEMILLION * nsec;
		y->tv_sec -= nsec;
	}

	// Compute the time remaining to wait.
	// tv_usec is certainly positive.
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;

	// Return 1 if result is negative
	return x->tv_sec < y->tv_sec;
}