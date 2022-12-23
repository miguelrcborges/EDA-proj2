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
    // Every column that is possible is a option (RANDOM).
    columns_to_play = board.playable_columns();
  } else {
    // In case it is the first move or the depth is 1 (explanation in futher comments).
    if (state == NULL) {
      state = new BoardState(board, depth, symbol);
    } else {
      state = state->update_state(last_move[0], board.get_last_played_column());
      // State can not be found, especially if the depth is 1 (you need to walk 2 steps, at depth 1 you see only one).
      // Other case this happens when the opponent has a guaranteed win.
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
  // At depth 1 it has to delete the state, since it wont provide any state for the next turn.
  // It can only find from depth 2 or higher.
  // (Next turn => + 2 steps).
  if (depth == 1) { delete state; state = NULL; }

  return;
}

int Computer::get_depth() {
  return depth;
}