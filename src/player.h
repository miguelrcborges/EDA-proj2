#pragma once

#include <string>
#include "board.h"

class Player {
public:
  std::string get_name();
  void play();

private:
  std::string name;
  int last_move[2];
  char symbol;
};