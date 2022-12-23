#pragma once

#include <string>
#include <array>
#include "board.h"
#include "inputHandler.h"

/**
* Our Player class. This class represents each person playing the game.
* 
* It holds the player information as well needed methods required by the player
* to interact with the game.
*/
class Player {
public:
  /**
  * Constructor.
  *
  * @param Symbol to represent the player.
  */
  Player(char symbol_to_set);

  /**
  * Method that makes it able to get the player's name from the outside.
  *
  * @return Player's name.
  */
  std::string get_name() const;

  /**
  * Method that makes it able to get the player's last moves from the outside.
  *
  * @return Last move coordinates.
  */
  std::array<int, 2> get_last_move() const;

  /**
  * Method that makes it able to get the player symbol from the outside.
  *
  * @return Player symbol.
  */
  char get_symbol() const;

  /**
  * Method that makes an able able to play.
  *
  * @param board Board where the play is going to play.
  */
  virtual void play(Board &board);

protected:
  /** 
  * Element that makes it able to ask the user for stdin inputs.
  */
  InputHandler input;
  
  /**
  * Player name. Used on the logs and to specify who is playing.
  */
  const std::string name;

  /**
  * Array with the coordinates of the last played move. Speeds up the win verification.
  */
  std::array<int, 2> last_move;

  /**
  * Player symbol.
  */
  const char symbol;
};
