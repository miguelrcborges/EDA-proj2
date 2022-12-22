#pragma once

#include <iostream>
#include <string>
#include <array>
#include <ctime>

#include "board.h"
#include "player.h"
#include "constants.h"
#include "inputHandler.h"



/**
* Our Game class. This class initializes each match that is played, containing information related
* to the board, to the players and the time of play.
* It also registers in "match log" file the results after match end.
*/
class Game {
public:
	/** 
	* Initialization of the Game class.  
	*/
	Game(); 
	/** 
	* End of match; logs the results, desctructor of Game class. 
	*/
	~Game();
	/** 
	* Loop of game. 
	*/
	void loop(); 
private:
	/** 
	* Element that allows the usage of the modes in InputHandler class. Essential for reading inputs from the user/player. 
	*/
	InputHandler input;
	/** 
	* Element that employs the use of the tm structure for time handling. 
	*/
	tm* times;
	/** 
	* Element that constitues an array of pointers to Player class elements. 
	*/
	std::array<Player* ,NUMBER_OF_PLAYERS> players;
	/** 
	* Integer that registers the turn of game. 
	*/
	int turn;
	/** 
	* Pointer to a Board class element. 
	*/
	Board* board_ptr;
};

