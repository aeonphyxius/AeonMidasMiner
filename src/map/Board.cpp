#include "Board.h"
#include <random>
#include <iostream>
#include <ScaleTo.h>
#include <MoveTo.h>
#include <functional>

using namespace Core;
using namespace GemBoard;

void Board::onInitialize(){

	map_info.x = 320;
	map_info.y = 100;
	map_info.tile_size = 45;
	map_info.end_x = map_info.x + (map_info.tile_size * MAP_WIDHT);
	map_info.end_y = map_info.y + (map_info.tile_size * MAP_HEIGHT);

	
	selected_gem = std::unique_ptr<DisplayObject>(new DisplayObject);
	selected_gem->setTexture(Aeonphyxius::Engine::TEXTURE_SELECTED_GEM);
	selected_gem->setScale(glm::vec3(1.f, 1.f, 1.f));
	selected_gem->addChild(new tweens::ScaleTo(selected_gem->getScale(), glm::vec3(1.2, 1.2, 1), 0.2f, true));	
	selected_gem->setIsVisible(false);	
	
	onBuildNewMap();
}
Board::~Board(){
	for (auto ls : lst_gems_remove){
		ls.clear();		
	}
	lst_gems_remove.clear();	
}

void Board::onBuildNewMap(const bool par_random)
{		
	std::random_device r;
	default_random_engine re (r());
	uniform_int_distribution<int> dist{ 1,5 };  

	for (auto x = 0; x < MAP_WIDHT; ++x)
	{
		for (auto y = 0; y < MAP_HEIGHT; ++y)
		{			
			uint8_t new_gem;
			do{
				new_gem = dist(re);
			} while (!isNewGemValid(x, y, new_gem) || !par_random);
			data.gems_list[x][y] = new_gem;
			data.do_list[x][y] = DisplayObject();
		}
	}
	onBindMap(true);
}
void Board::reGenerateEmpty(){
	std::random_device r;
	default_random_engine re(r());
	uniform_int_distribution<int> dist{ 1, 5 };

	for (auto x = 0; x < MAP_WIDHT; ++x)
	{
		for (auto y = 0; y < MAP_HEIGHT; ++y)
		{
			if (data.gems_list[x][y] == Engine::NONE){ // Only generate a new one if the position is empty
				uint8_t new_gem;
				new_gem = dist(re);
				// Set the new gem and texture
				data.gems_list[x][y] = new_gem;
				data.do_list[x][y].setTexture(getTexture(new_gem));
				// Set the gem out of the board to generate the falling effect
				auto origin = getGemPosition(x, y);				
				origin.y = 0;
				data.do_list[x][y].setPosition(origin);

				// final "correct" position.
				auto destiny = getGemPosition(x, y);				
				onAddGemFall(UIntVec2(x, y), origin, destiny, .2f);				
			}				
		}
	}
}
bool Board::isNewGemValid(const uint8_t par_x, const uint8_t par_y, const uint8_t par_new_gem)const{

	// Check 2 up and 2 to the left if there are enough gems to do so
	// if a match 3 (3 in a row) is found we need to re-generate this gem
	if ((par_y >= 2 && data.gems_list[par_x][par_y - 1] == par_new_gem && data.gems_list[par_x][par_y - 2] == par_new_gem) ||
		(par_x >= 2 && data.gems_list[par_x - 1][par_y] == par_new_gem && data.gems_list[par_x - 2][par_y] == par_new_gem)){
		return false;
	}
	return true;
}
void Board::onAddGemFall(const UIntVec2 gem,const glm::vec3 par_origin, const glm::vec3 par_destiny, const float par_time){
	data.do_list[gem.x][gem.y].addChild(new tweens::MoveTo(par_origin, par_destiny, par_time, false, EaseType::bounceOut));
}

void Board::onBindMap(const bool par_initial){
	// Reset all DisplayObjects to its "correct" position and texture
	// according to the gems list
	for (auto x = 0; x < MAP_WIDHT; ++x){
		for (auto y = 0; y < MAP_HEIGHT; ++y){
			data.do_list[x][y].setTexture(getTexture(data.gems_list[x][y]));						
			auto destiny = getGemPosition(x, y);

			if (par_initial){				
				auto origin = data.do_list[x][y].getPosition();	
				origin.x = destiny.x;
				onAddGemFall(UIntVec2(x, y), origin, destiny, 1.5f);
			}
			else{
				data.do_list[x][y].setPosition(destiny);
			}
		}
	}
}

glm::vec3 Board::getMarkerPosition(const int par_x, const int par_y)const{
	
	glm::vec3 marker_pos = getGemPosition(par_x, par_y);
	return marker_pos - glm::vec3(5, 5, 0.0f);// in order to leave the gem centered in the square box
}

glm::vec3 Board::getGemPosition(const int par_x, const int par_y)const{
	// using the map size and tile size get the gem position
	return glm::vec3(map_info.x + (map_info.tile_size * par_x), map_info.y + (map_info.tile_size * par_y), 1.0f);
}

bool Board::adjacentPoints(const UIntVec2 par_first_point, const UIntVec2 par_second_point)const{
	// Check if both points are adjacent (is a valid swap action?)
	if (((par_first_point.x == par_second_point.x - 1 || par_first_point.x == par_second_point.x + 1) && (par_first_point.y == par_second_point.y)) ||
		((par_first_point.y == par_second_point.y - 1 || par_first_point.y == par_second_point.y + 1) && (par_first_point.x == par_second_point.x))){

		return true;
	}

	return false;
}


bool Board::translateClickToBoard(const glm::vec2* par_mouse_pos, UIntVec2 *par_board_pos)const{
	if (par_mouse_pos->x >= map_info.x && par_mouse_pos->x <= map_info.end_x &&
		par_mouse_pos->y >= map_info.y && par_mouse_pos->y <= map_info.end_y){

		// Make the mouse point relative to the gems map
		par_board_pos->x = static_cast<uint8_t> ((par_mouse_pos->x - map_info.x) / map_info.tile_size);
		par_board_pos->y = static_cast<uint8_t> ((par_mouse_pos->y - map_info.y) / map_info.tile_size);				
		return true;
	}
	else{		
		return false;
	}
}

void Board::enableSelector(const UIntVec2 par_point){
	selected_gem->setPosition(getMarkerPosition(par_point.x, par_point.y));
	selected_gem->setIsVisible(true);
}

void Board::disableSelector(){	
	selected_gem->setIsVisible(false);
}

void Board::swapGems(const UIntVec2 par_pos1, const UIntVec2 par_pos2, bool par_is_correct_swap){
	
	auto &do1 = data.do_list[par_pos1.x][par_pos1.y];
	auto &do2 = data.do_list[par_pos2.x][par_pos2.y];

	if (par_is_correct_swap){
		do1.addChild(new tweens::MoveTo(do1.getPosition(), do2.getPosition(), .2f));
		do2.addChild(new tweens::MoveTo(do2.getPosition(), do1.getPosition(), .2f));
	}
	else{
		do1.addChild(new tweens::MoveToBack(do1.getPosition(), do2.getPosition(), .2f));
		do2.addChild(new tweens::MoveToBack(do2.getPosition(), do1.getPosition(), .2f));
	}
}

void Board::swapBoardGems(const UIntVec2 par_pos1, const UIntVec2 par_pos2){
	std::swap(data.gems_list[par_pos1.x][par_pos1.y], data.gems_list[par_pos2.x][par_pos2.y]);	
}

int  Board::getMatchesMultiplier(){

	int matches = 0;
	for (auto lst_item : lst_gems_remove){
		if (lst_item.size() >= 3)
			matches += lst_item.size();			
	}
	return matches;
}

void Board::prepareFall(){	
	// Set to NONE or empty the gems to be remved
	for (auto lst_item : lst_gems_remove){
		if (lst_item.size() >= 3){
			for (auto gem_pos : lst_item){
				data.gems_list[gem_pos.x][gem_pos.y] = Engine::NONE;
				data.do_list[gem_pos.x][gem_pos.y].setTexture(Engine::NONE);				
			}
		}		
	}

	// Rebind the map in order to set every Display object at its right position and right texture
	onBindMap();

	// Make the "fall" effect
	for (auto x = (MAP_WIDHT -1); x >= 0; --x){
		for (auto col = (MAP_HEIGHT - 2); col >= 0; --col){
						
			if (data.gems_list[x][col +1] == Engine::NONE){
				auto y = col +1;
				while (data.gems_list[x][y + 1] == Engine::NONE && y < MAP_HEIGHT) {
					++y;
				};

				auto origin = getGemPosition(x, col);
				auto target = getGemPosition(x, y);
				data.do_list[x][col].addChild(new tweens::MoveTo(origin, target, 0.2f, false, EaseType::bounceOut));
				swapBoardGems(UIntVec2(x, col), UIntVec2(x, y));
			}			
		}
	}
}

void Board::rebuildMap(){
	//after the fall its time to re-build the empty spaces and add the needed fall effects
	onBindMap();
	reGenerateEmpty();
}

bool Board::boardHasChains(){
	
	auto hasChains = false;
	
	auto vertical = UIntVec2(1, 0);
	auto horizontal = UIntVec2(0, 1);

	lst_gems_remove.clear();
	lst_gems_remove.push_back(std::vector <UIntVec2>());
	for (auto col = 0; col < MAP_HEIGHT; ++col){		
		checkBoardLine(0, col, &lst_gems_remove, vertical);
	}

	for (auto row = 0; row < MAP_WIDHT; ++row){
		checkBoardLine(row, 0, &lst_gems_remove, horizontal);
	}

	return lst_gems_remove.front().size() >= 3 ? true : false; // If at least the last vector has 3 o more it means that there are 3-chains
}

uint8_t Board::checkBoardLine(const uint8_t par_x, const uint8_t par_y, std::vector< std::vector <UIntVec2>> *lst, const UIntVec2 par_check){
	// In order to avoid extra calculations, this is a recursive fucntion. 
	// it goes first till the last row or col elemnt and from ther "rolls" back
	// Once finds 3 matches or more, adds them to the lst
	// when no macht, just resets the list and continues
	uint8_t num_matches;
	if (par_check.x == 1 ? par_x < (MAP_WIDHT - 1) : par_y < (MAP_HEIGHT - 1)){
		num_matches = checkBoardLine(par_x + par_check.x, par_y + par_check.y, lst, par_check);
	}

	if (par_check.x == 1 ? par_x == (MAP_WIDHT - 1) : par_y == (MAP_HEIGHT - 1)){
		if (lst->back().size() >= 3){ // In case any previous check have generated a 3-chain
			lst->push_back(std::vector <UIntVec2>());
		}
		lst->back().clear();
		lst->back().push_back(UIntVec2(par_x, par_y));
		return 1;
	}
	else{
		if (data.gems_list[par_x][par_y] == data.gems_list[par_x + par_check.x][par_y + par_check.y]){
			lst->back().push_back(UIntVec2(par_x, par_y));
			return num_matches + 1;
		}
		else{
			if (num_matches >= 3){
				lst->push_back(std::vector <UIntVec2>());				
			}
			else{
				lst->back().clear();
			}
			lst->back().push_back(UIntVec2(par_x, par_y));
			return 1;
		}
	}	
}

const Engine::Texture Board::getTexture(const int par_texture) const{

	Engine::Texture texture;

	switch (par_texture){
	case 1:
		texture = Aeonphyxius::Engine::TEXTURE_BLUE;
		break;
	case 2:
		texture = Aeonphyxius::Engine::TEXTURE_GREEN;
		break;
	case 3:
		texture = Aeonphyxius::Engine::TEXTURE_PURPLE;
		break;
	case 4:
		texture = Aeonphyxius::Engine::TEXTURE_RED;
		break;
	case 5:
		texture = Aeonphyxius::Engine::TEXTURE_YELLOW;
		break;
	case 10:
	default:
		texture = Aeonphyxius::Engine::NONE;
		break;
	}
	return texture;
}



void Board::onUpdate(){
	// every update, call the Display Objects to draw / update them
	auto engine = ServiceManager::getInstance()->getService<Aeonphyxius::Engine>(Services::ENGINE);
	selected_gem->onUpdate();
	engine->Render(selected_gem.get() );

	for (auto &rows : data.do_list){
		for (auto &go : rows){
		go.onUpdate();
		}
	}
}