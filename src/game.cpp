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
	int height, width, to_connect;
	std::array<char, NUMBER_OF_PLAYERS> player_symbols;

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		char symbol = input.get_input<char>("Is this player a computer? Y/N ");
		if (toupper(symbol) == 'Y')
		{
			player_symbols[i] = symbol;
			players[i] = new Player(input.get_input<char>("Choose the player's symbol "));
		}
		else if (toupper(symbol) == 'N')
		{
			player_symbols[i] = symbol;
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
		height = input.get_input<int>("What's the board height?");
		if (height < BOARD_DIMENSION_UPPER_LIMIT && height>BOARD_DIMENSION_LOWER_LIMIT) break;
		std::cout << "Please input a number between " << BOARD_DIMENSION_LOWER_LIMIT << " and " << BOARD_DIMENSION_UPPER_LIMIT << std::endl;
	}
	while (1)
	{
		width = input.get_input<int>("What's the board width?");
		if (width < BOARD_DIMENSION_UPPER_LIMIT && width>BOARD_DIMENSION_LOWER_LIMIT) break;
		std::cout << "Please input a number between " << BOARD_DIMENSION_LOWER_LIMIT << " and " << BOARD_DIMENSION_UPPER_LIMIT << std::endl;
	}
	while (1)
	{
		to_connect = input.get_input<int>("How many symbols should one connect to win the game?");
		if (to_connect > TO_CONNECT_LOWER_LIMIT && to_connect < std::max(height, width)) break;
		std::cout << "Please input a valid number that is higher than " << TO_CONNECT_LOWER_LIMIT << " and possible, given your board. \n";
	}

	turn = FIRST_TURN;
	board_ptr = new Board(width, height, to_connect, player_symbols[0], player_symbols[1]); 

	time_t current_time = time(NULL);
	times = localtime(&current_time);
}

Game::~Game()
{
	std::ofstream out;

	out.open("match logs.txt", std::ios_base::app);
	out << std::setfill('0');

	out << times->tm_year + 1900 << " - " << times->tm_mon + 1 << " - " << times->tm_mday << " / "  //tm_year needs to be converted by adding 1900 and tm_mon by adding 1
		<< times->tm_hour << ":" << std::setw(2) << times->tm_min << " - 1) " << (players[0])->get_name();

	Computer* tmp_p = dynamic_cast<Computer*>(players[0]);

	if (tmp_p != NULL)
	{
		out << " (CPU - " << tmp_p->get_depth() << ')';
	}
	out << " vs 2) " << (players[1])->get_name();

	tmp_p = dynamic_cast<Computer*>(players[1]);
	if (tmp_p != NULL)
	{
		out << " (CPU - " << tmp_p->get_depth() << ')';
	}
	if (board_ptr->check_win(players[turn % 2]->get_last_move()))
	{
		out << " - vencedor : ";
		if (turn % 2 == 0)
		{
			out << "1) " << (players[0])->get_name();
		}
		else
		{
			out << "2) " << players[1]->get_name();
		}
		
		tmp_p = dynamic_cast<Computer*>(players[turn%2]);
		if (tmp_p != NULL)
		{
			out << " (CPU - " << tmp_p->get_depth() << ')';
		}
	}
	else
	{
		out << " - Empate";
	}
	out << ".\n";
	out.close();

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		delete players[i];
	}
	delete tmp_p;
}

void Game::loop()
{
	while (turn < board_ptr->get_height() * board_ptr->get_width()) {
		board_ptr->draw_board();
		(players[(turn - 1) % 2])->play(*board_ptr);
		if (board_ptr->check_win((players[++turn % 2])->get_last_move())) break;
	}
	board_ptr->draw_board();
	if (board_ptr->check_win(players[turn % 2]->get_last_move()))
	{
		std::cout << "Winner is " << (players[turn % 2])->get_name() << "! Congratulations!" << std::endl;
	}
	else
	{
		std::cout << "Draw!" << std::endl;
	}
}