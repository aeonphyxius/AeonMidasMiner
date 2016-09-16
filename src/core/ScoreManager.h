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
#ifndef MIDAS_SCORE_MANAGER_H
#define MIDAS_SCORE_MANAGER_H


#include "ServiceManager.h"
#include <EventData.h>
#include <glm\fwd.hpp>

/**
* Small score manager, to handle all the socre system
*
*/
namespace Core
{
	class ScoreManager : public Service{
	public:
		struct Score{
			Score(): multiplier(0), points(0){}
			Score(int par_points, int par_score) : multiplier(par_score), points(par_points){}
		public:
			int multiplier;
			int points;			
		};

	
		ScoreManager();

		void onEvent(EventData *par_evtdata);
		void onAddPoints(Score* par_points);
		void onSavePoints();
		void onResetPoints();

		int getPoints()const { return score.points; }
		int getMultiplier()const { return score.multiplier; }

	private:		
		int		high_score;
		Score	score;
		

	};
}
#endif /* defined( MIDAS_INPUT_MANAGER_H )*/
