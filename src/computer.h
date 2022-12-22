#pragma once

#include "player.h"
#include "boardState.h"

class Computer : public Player {
public:
  Computer(char symbol_to_set);
  void play(Board &board);
  int get_depth();

private:
  int depth;
  BoardState *state;
};