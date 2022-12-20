#pragma once

#include "player.h"

class Computer : public Player {
public:
  Computer(char symbol_to_set);
  void play(Board &board);

private:
  int depth;
};