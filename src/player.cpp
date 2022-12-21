#include "player.h"

#include <array>
#include <iostream>
#include <cctype>

std::string Player::get_name() const {
  return name;
}

Player::Player(char symbol_to_set) : symbol(symbol_to_set), name(input.get_string("What's the player name?")) {
  last_move[0] = 0;
  last_move[1] = 0;
}

void Player::play(Board &board) {
  while (true) {
    char column_to_play_input = input.get_input<char>("On which column do you want to play in, " + name + "?");
    column_to_play_input = toupper(column_to_play_input);
    int column_to_play_index = column_to_play_input - 'A';

    if (column_to_play_input < 'A' || column_to_play_input > ('A' + board.get_width() - 1)) {
      std::cout << "Your input must be a letter between A and " << (char) ('A' + board.get_width() - 1) << '!' << std::endl;
      continue;
    }

    if (!board.is_playable(column_to_play_index)) {
      std::cout << "That column is already stacked!" << std::endl;
      continue;
    }
    
    last_move[1] = board.play(column_to_play_index, symbol);
    last_move[0] = column_to_play_index;
    return;
  }
}

std::array<int, 2> Player::get_last_move() const {
  return last_move;
}

char Player::get_symbol() const {
  return symbol;
}