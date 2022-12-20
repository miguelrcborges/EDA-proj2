
#include <iostream>
#include <string>
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
	Game(Board board,Player players); //initialization of the game class
	~Game(); //end of match; logs the results
	start(); //creates
private:
	tm* times;
	players;
	int turn;
	Board board;
};

