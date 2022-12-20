#define NUMBER_OF_PLAYERS 2

#include <iostream>
#include <string>
#include <array>
#include <ctime>

#include "board.h"
#include "player.h"



//template do Miguel

/**
* Our Game class. This class initializes each match that is played, containing information related
* to the board, to the players in play and the time of play.
* It also registers the results after match end
*/
class Game {
public:
	Game(); //initialization of the game class
	~Game(); //end of match; logs the results
private:
	InputHandler input;
	tm* times;
	std::array<Player* ,2> players;
	int turn;
	Board board;
};

