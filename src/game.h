
#include <iostream>
#include <string>
#include "board.h"
#include "player.h"
#include <array>


//template do Miguel

/**
* Our Game class. This class initializes each match that is played, containing information related
* to the board, to the players in play and the time of play.
* It also registers the results after match end
*/
class Game {
public:
	Game(Player player1, Player player2); //initialization of the game class
	~Game(); //end of match; logs the results
	start(); //creates a new match
private:
	tm* times;
	std::array<Player,2> players;
	int turn;
	Board board;
};

