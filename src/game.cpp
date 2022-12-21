#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>

#include "board.h"
#include "player.h"
#include "inputHandler.h"
#include "game.h"
#include "computer.h"

Game::Game()
{
	for (int i=0; i<NUMBER_OF_PLAYERS; i++)
	{ 
		if (toupper(input.get_input<char>("Is this player a computer? Y/N ")) == 'Y')
		{
			players[i] = new Player(input.get_input<char>("Choose the player's symbol "));
		}
		else if (toupper(input.get_input<char>("Is this player a computer? Y/N ")) == 'N')
		{
			players[i] = new Computer(input.get_input<char>("Choose the player's symbol"));
		}
		else
		{
			i--;
			std::cout << "Please provide a valid answer to the question \n";
		}
	}
	while (1)
	{
		int height = input.get_input<int>("What's the board height?");
		if (height < BOARD_DIMENSION_UPPER_LIMIT && height>BOARD_DIMENSION_LOWER_LIMIT) break;
		std::cout << "Please input a number between " << BOARD_DIMENSION_LOWER_LIMIT << " and " << BOARD_DIMENSION_UPPER_LIMIT << std::endl;
	}
	while (1)
	{
		int width = input.get_input<int>("What's the board width?");
		if (width < BOARD_DIMENSION_UPPER_LIMIT && width>BOARD_DIMENSION_LOWER_LIMIT) break;
		std::cout << "Please input a number between " << BOARD_DIMENSION_LOWER_LIMIT << " and " << BOARD_DIMENSION_UPPER_LIMIT << std::endl;
	}
	while (1)
	{
		int to_connect = input.get_input<int>("How many symbols should one connect to win the game?");
		if (to_connect>TO_CONNECT_LOWER_LIMIT && to_connect <std::max(height, width) break;
		std::cout << "Please input a valid number that is higher than " << TO_CONNECT_LOWER_LIMIT << " and possible, given your board. \n";
	}
	

	this->board = Board::board(width,height,to_connect);
	
	turn = FIRST_TURN;
	time_t current_time = time(NULL);
	times = localtime(&current_time);
}

Game::~Game()
{
	std::ofstream out;

	out.open("match logs.txt", std::ios_base::app);
	out << std::setfill('0');
	out << times->tm_year + 1900 << " - " << times->tm_mon + 1 << " - " << times->tm_mday << " / " 
		<< times->tm_hour << ":" << std::setw(2) << times->tm_min << " - 1) " << (players[0])->get_name;
	
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		delete players[i]
	}
}

void Game::loop() const
{
	while (turn < board.get_height * board.get_width) {
		board.draw_board();
		(players[(turn-1)%2])->play(&board)
		if (board.check_win((players[++turn % 2])->get_last_move()))
			break;
	}
	board.draw_board();
	if (board.check_win(players[turn % 2]->get_last_move()))
	{
		std::cout << "Winner is " << (players[turn % 2])->get_name << "! Congratulations!" << std::endl;
	}
	else
	{
		std::cout << "Draw!" << std::endl;
	}
}