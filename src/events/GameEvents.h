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

#ifndef MIDAS_GAME_EVENTS_H
#define MIDAS_GAME_EVENTS_H

#include <iostream>

/**
* This is a list of simple events names to be used by the EventManager
*/
namespace events
{
	static const std::string GAME_QUIT = "GAME_QUIT";
	static const std::string MOUSE_UP = "MOUSE_UP";
	static const std::string MOUSE_DOWN = "MOUSE_DOWN";
	static const std::string MOUSE_MOVE = "MOUSE_MOVE";
	

	static const std::string GAME_FIRST_GEM = "GAME_FIRST_GEM";
	static const std::string GAME_DRAGGING = "GAME_DRAGGING";	
	static const std::string GAME_SECOND_GEM = "GAME_SECOND_GEM";
	static const std::string GAME_START_CHAIN = "GAME_START_CHAIN";
	static const std::string GAME_END_CHAIN = "GAME_END_CHAIN";
	static const std::string GAME_FALL_MAP = "GAME_FALL_MAP";
	static const std::string GAME_REBUILD_MAP = "GAME_REBUILD_MAP";
	static const std::string GAME_REBUILD_MAP_ENDED = "GAME_REBUILD_MAP_ENDED";
	static const std::string GAME_CHECK_MAP = "GAME_CHECK_MAP";
	
	static const std::string GAME_FALL_MAP_ENDED = "GAME_FALL_MAP_ENDED";

	// SCORE
	static const std::string ADD_POINTS = "ADD_POINTS";
	static const std::string RESET_POINTS = "RESET_POINTS";
	static const std::string SAVE_POINTS = "SAVE_POINTS";

	static const std::string GAME_WRONG_SELECTION = "GAME_WRONG_SELECTION";
	static const std::string GAME_OK_SELECTION = "GAME_OK_SELECTION";
	static const std::string GAME_FIRST_SELECTED = "GAME_FIRST_SELECTED";
	static const std::string GAME_CLEAR_SELECTION = "GAME_CLEAR_SELECTION";
	
	static const std::string TIMER_START = "TIMER_START";
	static const std::string TIMER_STOP = "TIMER_STOP";
	static const std::string TIMER_WARNING = "TIMER_WARNING";
	static const std::string TIMER_ENDED = "TIMER_ENDED";

	static const std::string SCORE_UPDATED = "SCORE_UPDATED";

};

#endif /* defined( MIDAS_GAME_EVENTS_H )*/