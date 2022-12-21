#include "computer.h"

#include "boardState.h"
#include <iostream>
#include <cstdlib>
#include <vector>

Computer::Computer(char symbol_to_set) : Player(symbol_to_set) {
  depth = input.get_input<int>("What should be the computer depth?");
  if (depth > 8)
    std::cout << "WARNING: The depth is high, it may take some time for the computer to play." << std::endl;
  else if (depth < 0)
    std::cout << "WARNING: Values of depth lower than 0 are the same to 0." << std::endl;
}

void Computer::play(Board &board) {

  std::vector<int> columns_to_play;
  if (depth <= 0) {
    columns_to_play = board.playable_columns();
  } else {
    BoardState state(board, depth, symbol);
    columns_to_play = state.get_best_moves(symbol);
  }

  int column_to_play = rand() % columns_to_play.size();
  last_move[1] = board.play(columns_to_play[column_to_play], symbol);
  last_move[0] = column_to_play;

  return;
}

int Computer::get_depth() {
  return depth;
}