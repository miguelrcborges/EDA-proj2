#include "boardState.h"
#include <vector>
#include <cstddef>
#include <iostream>

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

  if (depth > 0) {
    for (int i = 0; i < board.get_width(); i++) {
      if (board.is_playable(i)) {
        child_states.push_back(new BoardState(game_board, depth - 1, symbol_to_play == board.get_symbol(0) ? board.get_symbol(1) : board.get_symbol(0)));
        child_states[i]->board.play(i, symbol_to_play);
      }
    }
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
    child_states[i]->evaluate(player_symbol);
    if (
      (player_symbol == symbol_to_play && child_states[i]->value > value) ||
      (player_symbol != symbol_to_play && child_states[i]->value < value)
    ) value = child_states[i]->value;
  }
}

std::vector<int> BoardState::get_best_moves(char player_symbol) const {
  std::vector<int> best_moves;
  int best_value;

  for (int i = 0; i < child_states.size(); i++) {
    child_states[i]->evaluate(player_symbol);

    if (best_moves.size() == 0) {
      best_moves.push_back(child_states[i]->last_move[0]);
      best_value = child_states[i]->value;
    }
    else if (child_states[i]->value > best_value) {
      best_moves.clear();
      best_moves.push_back(child_states[i]->last_move[0]);
    } else if (child_states[i]->value == value) {
      best_moves.push_back(child_states[i]->last_move[0]);
    }
  }

  return best_moves;
}