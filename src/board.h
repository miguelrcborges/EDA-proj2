#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <map>

class Board {
public:
  Board();
  void draw_board();
  bool check_win();
  bool is_playable(int column);
  void play(int column, char symbol);

private:
  std::vector<std::vector<char>> slots;
  std::map<std::string, std::string> colors;
};