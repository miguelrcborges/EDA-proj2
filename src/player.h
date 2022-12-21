#pragma once

#include <string>
#include <array>
#include "board.h"
#include "inputHandler.h"

class Player {
public:
  Player(char symbol_to_set);
  std::string get_name() const;
  std::array<int, 2> get_last_move() const;
  char get_symbol() const;
  virtual void play(Board &board);

protected:
  InputHandler input;
  std::string name;
  std::array<int, 2> last_move;
  char symbol;
};