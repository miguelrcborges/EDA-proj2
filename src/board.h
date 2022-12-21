#pragma once

#include <vector>
#include <map>
#include <array>

#include "constants.h"

#define EMPTY_CHAR	 ' '
/** ANSI escape code to clear the screen. */
#define CLEAR_SCR    "\033[2J\033[H"
/** ANSI escape code to write in red. */
#define PRINT_RED    "\033[91m"
/** ANSI escape code to write in green. */
#define PRINT_GREEN  "\033[92m"
/** ANSI escape code to write in yellow. */
#define PRINT_YELLOW "\033[93m"
/** ANSI escape code to clear applied styles. */
#define CLEAR_STYLE  "\033[m"

class Board {
public:
  Board(int width, int height, int to_connect, char player_one_symbol, char player_two_symbol);
  Board(Board &game_board);
  void draw_board() const;
  bool check_win(std::array<int, 2> last_move) const;
  bool is_playable(int column) const;
  std::vector<int> playable_columns() const;

  /**
  * Method to get width
  *
  * @return Board width 
  */
  int get_width() const;

  /**
  * Method to get height
  *
  * @return Board height
  */
  int get_height() const;

  /**
  * Returns the player symbol of the given index
  *
  * @param player Index of the player to get the symbol
  * @return Player symbol
  */
  char get_symbol(int player) const;

  /** 
  * Plays the symbol in the given column.
  * Symbol is used to identify the player. (Players dont know their indexes) 
  *  
  * @param column Column to be played
  * @param symbol Symbol which will be played
  * @return row where the symbol was placed
  */
  int play(int column, char symbol);

private:
  std::vector<std::vector<char>> slots;
  void print_header() const;
  const int to_connect;
  const std::array<char, NUMBER_OF_PLAYERS> symbols;
};