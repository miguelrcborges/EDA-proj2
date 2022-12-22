#include "boardState.h"
#include <ostream>
#include <type_traits>
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

BoardState::BoardState(Board &game_board, int depth, char symbol) : board(game_board) {
  this->depth = depth; 
  this->symbol_to_play = symbol;

  if (depth <= 0) return;
  for (int i = 0; i < board.get_width(); i++) {
    if (board.is_playable(i)) {
      // Old implementation. It is bad since creates another board unnecessarily, so I created a BoardState method to do this better
      //Board tmp(game_board);
      //int row = tmp.play(i, symbol_to_play);
      //child_states.push_back(new BoardState(tmp, depth - 1, symbol_to_play == board.get_symbol(0) ? board.get_symbol(1) : board.get_symbol(0)));
      int row;
      BoardState *tmp = new BoardState(board, depth, symbol_to_play, i, row);
      tmp->last_move[1] = row;
      tmp->last_move[0] = i;
      child_states.push_back(tmp);
    }
  }
}

BoardState::BoardState(Board &game_board, int parents_depth, char symbol_playing, int column, int &row) : board(game_board) {
  row = board.play(column, symbol_playing);
  symbol_to_play = symbol_playing == board.get_symbol(0) ? board.get_symbol(1) : board.get_symbol(0);
  depth = parents_depth - 1;
  value = 0;
  if (depth <= 0) return;
  for (int i = 0; i < board.get_width(); i++) {
    if (board.is_playable(i)) {
      int row;
      BoardState *tmp = new BoardState(board, depth, symbol_to_play, i, row);
      tmp->last_move[1] = row;
      tmp->last_move[0] = i;
      child_states.push_back(tmp);
    }
  }
}

void BoardState::evaluate(char player_symbol) {
  if (value != 0) {
    value += 2 * (value > 0);
  }

  if (board.check_win(last_move)) {
    value = symbol_to_play != player_symbol ? depth + 1 : - depth - 1;
    return;
  }

  if (depth <= 0) {
    value = 0;
    return;
  }

  value = symbol_to_play == player_symbol ? - depth - 1 : depth + 1; 
  for (int i = 0; i < child_states.size(); i++) {
    //if (child_states[i] == NULL) continue;

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
    //if (child_states[i] == NULL) continue;

    child_states[i]->evaluate(player_symbol);
    #ifdef _MDEBUG
    std::cout << "Position " << i << ": " << child_states[i]->value << "\tx: " << child_states[i]->last_move[0] << " y: " << child_states[i]->last_move[1] << std::endl;
    #endif

    if (best_moves.size() == 0) {
      best_moves.push_back(child_states[i]->last_move[0]);
      best_value = child_states[i]->value;
    }
    else if (child_states[i]->value > best_value) {
      best_moves.clear();
      best_moves.push_back(child_states[i]->last_move[0]);
      best_value = child_states[i]->value;
    } else if (child_states[i]->value == best_value) {
      best_moves.push_back(child_states[i]->last_move[0]);
    }
    #ifdef _MDEBUG
    std::cout << "Possible moves: " << best_moves.size() << std::endl;
    #endif
  }

  return best_moves;
}


BoardState *BoardState::update_state(int computer_move, int opponent_move) {
  BoardState *return_p = NULL;
  for (int i = 0; i < child_states.size(); i++) {
    if (child_states[i]->last_move[0] != computer_move) continue;
    for (int ii = 0; ii < child_states[i]->child_states.size(); ii++) {
      if (child_states[i]->child_states[ii]->last_move[0] != opponent_move) continue;
      return_p = child_states[i]->child_states[ii];
      child_states[i]->child_states[ii] = NULL;

      goto outside;
    } 
  }
  return return_p;
outside:
  return_p->increment_depth();
  return_p->generate_missing_states();

  delete this;
  return return_p;
}

void BoardState::increment_depth() {
  depth += 2;
  for (int i = 0; i < child_states.size(); i++) {
    child_states[i]->increment_depth();
  }
}

void BoardState::generate_missing_states() {
  if (value != 0) return;
  if (depth <= 0) return;
  if (child_states.size() == 0) {
    for (int i = 0; i < board.get_width(); i++) {
      if (board.is_playable(i)) {
        int row;
        BoardState *tmp = new BoardState(board, depth, symbol_to_play, i, row);
        tmp->last_move[1] = row;
        tmp->last_move[0] = i;
        child_states.push_back(tmp);
      }
    }
  } else {
    for (int i = 0; i < child_states.size(); i++) {
      child_states[i]->generate_missing_states();
    }
  }
}