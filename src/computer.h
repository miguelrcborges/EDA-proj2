#pragma once

#include "player.h"
#include "boardState.h"

class Computer : public Player {
public:
  
  /**
  * Constructor.
  *
  * @param symbol_to_set Symbol to represent the computer.
  */
  Computer(char symbol_to_set);
  
  /**
  * Plays according to pre-defined depth.
  *
  * @param board Current game board.
  */
  void play(Board &board);
  
  /**
  * Method to return depth.
  *
  * @return depth.
  */
  int get_depth();

private:
  
  /**
  * Number of turns the computer simulates.
  */
  int depth;
  
  /**
  * Pointer corresponding to the game's current State.
  */
  BoardState *state;
};
