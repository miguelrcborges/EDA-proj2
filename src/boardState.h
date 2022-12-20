#pragma once

#include "board.h"

#include <vector>

class BoardState {
public:
  BoardState(Board &game_board, int depth, char symbol_to_play);
  ~BoardState();
  std::vector<int> get_best_moves(char player_symbol) const;
private:
  void evaluate(char player_symbol);
  Board board;
  int value;
  int depth;
  std::array<int, 2> last_move;
  std::vector<BoardState *> child_states;
  char symbol_to_play;
};