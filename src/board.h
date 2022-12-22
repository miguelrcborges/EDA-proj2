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
  /**
  * Construct of Board.
  *
  * @param width Board width.
  * @param height Board Height.
  * @param to_connect Defines how many pieces in a line are needed for a win.
  * @param player_one_symbol Symbol used by Player 1.
  * @param player_two_symbol Symbol used by Player 2.
  */
  Board(int width, int height, int to_connect, char player_one_symbol, char player_two_symbol);

  /**
  * Construct of Board.
  * Clones an existing board.
  * Useful for the Ai's board states.
  * 
  * @param game_board Pointer to the board that will be cloned.
  */
  Board(Board &game_board);

  /**
  * Prints the board on the console, with all the appropriate formatting.
  */
  void draw_board() const;

  /**
  * Checks if win conditions are met.
  *
  * @param last_move Coordinates of the last placed piece.
  * @return If a player has won the game.
  */
  bool check_win(std::array<int, 2> last_move) const;

  /**
  * Checks if given column has an empty slot.
  *
  * @param column Index of given column to check.
  * @return If column has an empty slot.
  */
  bool is_playable(int column) const;

  /**
  * Returns list of playable columns.
  * Important for the AI.
  * 
  * @return Vector of the indexes of the columns that haven't been filled.
  */
  std::vector<int> playable_columns() const;

  /**
  * Returns the last played column.
  * Important for the AI.
  * 
  * @return Index of the last played column.
  */
  int get_last_played_column() const;

  /**
  * Method to get width.
  *
  * @return Board width.
  */
  int get_width() const;

  /**
  * Method to get height.
  *
  * @return Board height.
  */
  int get_height() const;

  /**
  * Returns the player symbol of the given index.
  *
  * @param player Index of the player to get the symbol.
  * @return Player symbol.
  */
  char get_symbol(int player) const;

  /** 
  * Plays the symbol in the given column.
  * Symbol is used to identify the player. (Players dont know their indexes) 
  *  
  * @param column Column to be played.
  * @param symbol Symbol which will be played.
  * @return row where the symbol was placed.
  */
  int play(int column, char symbol);

private:
  /**
  * Variable which holds the board places.
  */
  std::vector<std::vector<char>> slots;

  /**
  * Helper function to draw the board. Draws the board header.
  */
  void print_header() const;

  /**
  * Variable that holds the last played column. Needed to be able to caching on the AI.
  */
  int last_played_column;

  /**
  * Variable that holds how many symbols has to connect.
  */
  const int to_connect;

  /**
  * Array that holds the player symbols. Used for coloring and to know what symbol is going to be placed on the AI.
  */
  const std::array<char, NUMBER_OF_PLAYERS> symbols;
};