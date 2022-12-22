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
  state = NULL;
}

void Computer::play(Board &board) {
  std::vector<int> columns_to_play;
  if (depth <= 0) {
    columns_to_play = board.playable_columns();
  } else {
    if (state == NULL) {
      state = new BoardState(board, depth, symbol);
    } else {
      state = state->update_state(last_move[0], board.get_last_played_column());
      if (!state)
        state = new BoardState(board, depth, symbol);
    }
    columns_to_play = state->get_best_moves(symbol);
  }

  int index_to_play = rand() % columns_to_play.size();
  #ifdef _MDEBUG
  std::cout << "Available moves: " << columns_to_play.size() << " choosed to play " << index_to_play << std::endl;
  #endif 
  last_move[1] = board.play(columns_to_play[index_to_play], symbol);
  last_move[0] = columns_to_play[index_to_play];
  std::cout << "The computer " << name << " played on " << (char) ('A' + last_move[0]) << '.' << std::endl;
  if (depth == 1) { delete state; state = NULL; }

  return;
}

int Computer::get_depth() {
  return depth;
}