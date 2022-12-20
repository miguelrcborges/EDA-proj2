#include "boardState.h"
#include <vector>

BoardState::~BoardState() {
  for (int i = 0; i < child_states.size(); i++)
    if (child_states[i] != NULL) {
      delete child_states[i];
      child_states[i] = NULL;
    }
}

BoardState::BoardState(Board &game_board, int depth, char symbol_to_play) : board(game_board) {
  this->depth = depth; 
  this->symbol_to_play = symbol_to_play;

  for (int i = 0; i < board.get_width(); i++) {
    child_states.push_back(NULL);
  }

  if (depth > 0)
    for (int i = 0; board.get_width(); i++)
      if (board.is_playable(i)) {
        child_states[i] = new BoardState(game_board, depth - 1, symbol_to_play == 'X' ? 'O' : 'X');
        child_states[i]->board.play(i, symbol_to_play);
      }
}

void BoardState::evaluate(char player_symbol) {
  if (board.check_win(last_move)) {
    value = symbol_to_play != player_symbol ? depth : -depth;
    return;
  }

  if (depth <= 0) {
    value = 0;
    return;
  }

  value = symbol_to_play == player_symbol ? -depth : depth; 
  for (int i = 0; i < child_states.size(); i++) {
    if (child_states[i] != NULL) {
      child_states[i]->evaluate(player_symbol);
      if (
        (player_symbol == symbol_to_play && child_states[i]->value > value) ||
        (player_symbol != symbol_to_play && child_states[i]->value < value)
      ) value = child_states[i] ->value;
    }
  }
}

std::vector<int> BoardState::get_best_moves(char player_symbol) const {
  std::vector<int> best_moves;

  for (int i = 0; child_states.size(); i++)
    if (child_states[i] != NULL) {
      child_states[i]->evaluate(player_symbol);

      if (best_moves.size() == 0)
        best_moves.push_back(i);
      else if (child_states[i]->value > child_states[best_moves[0]]->value) {
        best_moves.clear();
        best_moves.push_back(i);
      } else if (child_states[i]->value == child_states[best_moves[0]]->value) {
        best_moves.push_back(i);
      }
    }
  
  return best_moves;
}