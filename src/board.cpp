#include "board.h"

#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <utility>


Board::Board(int width, int height, int to_connect) {
	//vector of with appropriate length, that will be apended multiple times to slots to form the board
	std::vector<char> line_vector(height, EMPTY_CHAR);
	//adds a new column to the board
	for (int x = 0; x < width; x++) {
		slots.push_back(line_vector);
	}

	this->to_connect = to_connect;
}

Board::Board(Board &game_board) {
	slots = game_board.slots;
}

void Board::draw_board() const {
	//draws the letter indexes in yellow at the top of the board
	print_header();

	//draws positions, X in red and O in green, properly formated
	for (int y = get_height() - 1; y >= 0; y--) {
		for (int x = 0; x < get_width(); x++) {
			if (slots[x][y] == PLAYER_ONE_SYMBOL)
				std::cout << PRINT_RED; //sets characters color to red
			else if (slots[x][y] == PLAYER_TWO_SYMBOL)
				std::cout << PRINT_GREEN; //sets characters color to green
			std::cout << std::setw(5) << slots[x][y]; //prints the symbol slots[x][y], formatted by std::setw
		}
		std::cout << std::endl;
	}
	std::cout << CLEAR_STYLE;

	//draws the letter indexes in yellow at the bottom of the board
	print_header();
	std::cout << std::endl;
}

bool Board::check_win(std::array<int, 2> last_move) const {
	bool win = false;

	for (int reference_position = -3;reference_position < 1;reference_position++) {
		//horizontal win check
		if (!(win) && (reference_position + last_move[0] > -1 && reference_position + last_move[0] + to_connect - 1 < get_width())) { /*checks if horizontal limits are not crossed and if another winning condition hasn't been already found*/
			win = true; /*assumes that there is a win for that line, and checks if every element is equal to the first one. if not, there is no win and the other positions of that particular line aren't checked*/
			for (int n = 1;n < to_connect;n++) {
				if (slots[reference_position + last_move[0]][last_move[1]] != slots[reference_position + last_move[0] + n][last_move[1]]) {
					win = false;
					break;
				}
			}
		}
		//vertical win check
		if (!(win) && (reference_position + last_move[1] > -1 && reference_position + last_move[1] + to_connect - 1 < get_height())) {/*checks if vertical limits are not crossed and if another winning condition hasn't been already found*/
			win = true;
			for (int n = 1;n < to_connect;n++) {
				if (slots[last_move[0]][reference_position + last_move[1]] != slots[last_move[0]][reference_position + last_move[1] + n]) {
					win = false;
					break;
				}
			}
		}
		//negative diagonal win check
		if (!(win) && (reference_position + last_move[1] > -1 && reference_position + last_move[1] + to_connect - 1 < get_height()) && (reference_position + last_move[0] > -1 && reference_position + last_move[0] + to_connect - 1 < get_width())) { /*checks if  limits are not crossed and if another winning condition hasn't been already found*/
			win = true;
			for (int n = 1;n < to_connect;n++) {
				if ((slots[reference_position + last_move[0]][reference_position + last_move[1]] != slots[reference_position + last_move[0] + n][reference_position + last_move[1] + n])) {
					win = false;
					break;
				}
			}
		}
		//positive diagonal win check
		if (!(win) && (-reference_position + last_move[1] < get_height() && -reference_position + last_move[1] - to_connect + 1 >-1) && (reference_position + last_move[0] > -1 && reference_position + last_move[0] + to_connect - 1 < get_width())) { /*checks if limits are not crossed and if another winning condition hasn't been already found*/
			win = true;
			for (int n = 1;n < to_connect;n++) {
				if ((slots[reference_position + last_move[0]][-reference_position + last_move[1]] != slots[reference_position + last_move[0] + n][-reference_position + last_move[1] - n])) {
					win = false;
					break;
				}
			}
		}
	}
	return win;
}

int Board::get_width() const {
	return slots.size();
}

int Board::get_height() const {
	return slots[0].size();
}

bool Board::is_playable(int s) const {
	return s >= 0 && s < slots.size() && slots[s][get_height() - 1] == EMPTY_CHAR;
}

int Board::play(int column, char symbol) {
	int row = 0;
	while (1) {
		if (slots[column][row] == ' ') {
			slots[column][row] = symbol;
			return row;
		}	
		row++;
	}
	return -1;
}

std::vector<int> Board::playable_columns() const {
	std::vector<int> playable_places;
	for (int i = 0; i < get_width(); i++)
		if (is_playable(i))
			playable_places.push_back(i);
	return playable_places;
}

void Board::print_header() const {
	//draws the letter indexes in yellow
	std::cout << PRINT_YELLOW; //sets characters color to yellow
	for (char i = 'A'; i < 'A' + get_width(); i++)
		std::cout << std::setw(5) << i;
	std::cout << std::endl << CLEAR_STYLE;
}