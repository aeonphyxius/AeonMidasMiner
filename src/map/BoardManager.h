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
#ifndef MIDAS_BOARD_MANAGER_H
#define MIDAS_BOARD_MANAGER_H

#include <vector>
#include <DisplayObject.h>
#include <Board.h>

class EventData;

using namespace std;


/**
* This class will manage all the boad operations logic (are 2 cells adjacent? shall the swap?..)
*
* Will receive different calls from the game logic to respond different events ( first cell select, fall map, ..)
*
*/
namespace GemBoard{

	class BoardManager {
	public:
		
		BoardManager();
		~BoardManager();

		void onInitialize();
		void buildMap();
		void onUpdate();

	private:

		void onEvent(EventData *par_evtdata);
		void onSelectFirstGem(const glm::vec2* par_mouse_click_pos);
		void onMouseDrag(const glm::vec2* par_mouse_pos);
		void onSelectSecondGem(const glm::vec2* par_mouse_pos);
		void onStartChain();
		void onFillMapHoles();
		void onRebuildMap();
		void onCheckMap();

		Board			game_board;			/* game board with all cells information */
		Board::UIntVec2	first_click;		/* first click point information */
		Board::UIntVec2	second_click;		/* second click point information*/
	};

}

#endif /* defined( MIDAS_BOARD_MANAGER_H )*/