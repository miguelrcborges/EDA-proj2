#pragma once

#include "player.h"
#include "boardState.h"

/**
* Our Computer class. This class is a variant of the Player Class changed to it can play
* autonomously.
* 
* It holds the player information, AI information as well needed methods required 
* to find the best move and interact with the game.
*/
class Computer : public Player {
public:
  /**
  * Class constructor.
  *
  * @param symbol_to_set Symbol to represent the computer.
  */
  Computer(char symbol_to_set);

  /**
  * Plays according to pre-defined depth.
  * If the depth is null or negative, the move will be random.
  *
  * @param board Current game board.
  */
  void play(Board &board);

  /**
  * Method to return computer's AI depth.
  *
  * @return depth.
  */
  int get_depth();

private:
  /**
  * Number of turns that the computer's AI simulates.
  */
  int depth;

  /**
  * Pointer corresponding to the game's current state.
  */
  BoardState *state;
};