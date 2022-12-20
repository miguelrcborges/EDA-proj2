#pragma once

#include <vector>
#include <map>

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

#define PLAYER_ONE_SYMBOL 'X'
#define PLAYER_TWO_SYMBOL 'O'

class Board {
public:
  Board(int width, int height, int to_connect);
  Board(Board &game_board);
  void draw_board() const;
  bool check_win(std::array<int, 2> last_move) const;
  bool is_playable(int column) const;
  std::vector<int> playable_columns() const;
  int get_width() const;
  int get_height() const;
  int play(int column, char symbol);

private:
  std::vector<std::vector<char>> slots;
  void print_header() const;
  int to_connect;
};