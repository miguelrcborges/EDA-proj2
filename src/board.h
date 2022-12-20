#pragma once

#include <vector>
#include <map>

class Board {
public:
  Board(int width, int height);
  Board(&game_board);
  void draw_board() const;
  bool check_win(std::array<int, 2> last_move) const;
  bool is_playable(int column) const;
  std::vector<int> playable_places() const;
  int get_width() const;
  int get_height() const;
  int play(int column, char symbol);

private:
  std::vector<std::vector<char>> slots;
  std::map<std::string, std::string> colors;
};