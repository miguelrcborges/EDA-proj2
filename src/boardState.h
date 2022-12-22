#pragma once

#include "board.h"

#include <vector>

class BoardState {
public:
  BoardState(Board &game_board, int depth, char symbol_to_play);
  BoardState(Board &game_board, int parents_depth, char symbol_playing, int column, int &row);
  ~BoardState();
  BoardState *update_state(int computer_move, int opponent_move);
  std::vector<int> get_best_moves(char player_symbol) const;
private:
  void evaluate(char player_symbol);
  void increment_depth();
  void generate_missing_states();
  Board board;
  int value;
  int depth;
  std::array<int, 2> last_move;
  std::vector<BoardState *> child_states;
  char symbol_to_play;
};