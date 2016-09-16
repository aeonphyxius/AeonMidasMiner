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

#ifndef MIDAS_BOARD_H
#define MIDAS_BOARD_H

#include <vector>
#include <DisplayObject.h>

using namespace std;
using namespace Aeonphyxius;

/**
* This class manages all the boad operations. Create, fall, move gems, ...
*
* tries to use a fix number DisplaObjects swaping textures between them in order to 
* mantain the relationship between the gems list and the displayobjects list
*
* to look for 3 or more matches uses a recursive function, going thill the last gem
* in the given row or call, and going backwards checking if there is a match (saving it in 
* that case to be used in the fall operations).
*
* No logic have been implemented here
*
*/

namespace GemBoard{

	class Board{
	public:
		static const uint8_t MAP_WIDHT = 8;
		static const uint8_t MAP_HEIGHT = 8;
		
		struct BoardData{
		public:
			BoardData() = default;
			uint8_t				gems_list[MAP_WIDHT][MAP_HEIGHT];
			DisplayObject		do_list[MAP_WIDHT][MAP_HEIGHT];
		};
		struct UIntVec2{
			UIntVec2() = default;
			UIntVec2(const uint8_t par_x, const uint8_t par_y) : x(par_x), y(par_y){}
		public:
			uint8_t x;
			uint8_t y;
		};
		struct MapInfo{
		public:
			int x;
			int y;
			int tile_size;
			int end_x;
			int end_y;
		};
		
		Board() = default;
		~Board();

		int getMatchesMultiplier();

		void onInitialize();
		void onBuildNewMap(const bool par_random = true);
		void onAddGemFall(const UIntVec2 gem, const glm::vec3 par_origin, const glm::vec3 par_destiny, const float par_time);
		void onBindMap(const bool par_initial = false);

		bool translateClickToBoard(const glm::vec2* par_mouse_pos, UIntVec2 *par_board_pos)const;
		bool adjacentPoints(const UIntVec2 par_first_point, const UIntVec2 par_second_point) const;
		
		void enableSelector(const UIntVec2 par_point);
		void disableSelector();
		
		void swapGems(const UIntVec2 par_pos1, const UIntVec2 par_pos2, bool par_is_correct_swap);
		void swapBoardGems(const UIntVec2 par_pos1, const UIntVec2 par_pos2);
		
		bool boardHasChains();		
		void checkColumnChains(const uint8_t par_col, uint8_t &par_x, std::map <int, UIntVec2 > col_matches);
		void prepareFall();
		void rebuildMap();
		
		void onUpdate();
	private:
		void reGenerateEmpty();
		uint8_t checkBoardLine(const uint8_t par_x, const uint8_t par_y, std::vector< std::vector <UIntVec2>> *lst, const UIntVec2 par_check);		
		bool isNewGemValid(const uint8_t par_x, const uint8_t par_y, const uint8_t par_new_gem) const;
		glm::vec3 getGemPosition(const int par_x, const int par_y) const;
		glm::vec3 getMarkerPosition(const int par_x, const int par_y)const;				
		const Engine::Texture getTexture(const int par_texture) const;

		BoardData							 data;				/* board information. contains a list of gems and another of DisplayObjects */
		unique_ptr< DisplayObject>			 selected_gem;		/* selecte gem effect*/
		MapInfo								 map_info;			/* some map default information */
		std::vector< std::vector <UIntVec2>> lst_gems_remove;	/* List of gems to remove after swap */
		
	};
}
#endif /* defined( MIDAS_BOARD_H )*/