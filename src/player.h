#pragma once

#include <string>
#include <array>
#include "board.h"
#include "inputHandler.h"

class Player {
public:
  Player(char symbol_to_set);
  const std::string get_name() const;
  virtual void play(Board &board);

protected:
  InputHandler input;
  std::string name;
  std::array<int, 2> last_move;
  char symbol;
};