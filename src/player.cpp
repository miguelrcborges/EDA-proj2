#include "player.h"

#include <iostream>
#include <cctype>

const std::string Player::get_name() const {
  return name;
}

Player::Player(char symbol_to_set) {
  name = input.get_string("What's the player name?");
  last_move[0] = 0;
  last_move[1] = 0;
  symbol = symbol_to_set;
}

void Player::play(Board &board) {
  while (true) {
    char column_to_play_input = input.get_input<char>("On which column do you want to play in?");
    column_to_play_input = toupper(column_to_play_input);
    int column_to_play_index = column_to_play_input - 'A';

    if (column_to_play_index < 'A' || column_to_play_index > 'A' + board.get_width() - 1) {
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