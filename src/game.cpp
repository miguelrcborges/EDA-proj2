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
		if (toupper(input.get_input<char>("Is this player a computer? Y/N \n")) == 'Y')
		{
			players[i] = new Player(input.get_input<char>("Choose the player's symbol \n"));
		}
		else if (toupper(input.get_input<char>("Is this player a computer? Y/N \n")) == 'N')
		{
			players[i] = new Computer(input.get_input<char>("Choose the player's symbol \n"));
		}
		else
		{
			i--;
			std::cout << "Please provide a valid answer to the question \n";
		}
	}

	int height = input.get_input<int>("What's the board height?\n");
	int width = input.get_input<int>("What's the board width?\n");
	int to_connect = input.get_input<int>("How many symbols should one connect to win the game?\n");

	this->board = Board::board(width,height,to_connect);
	
	turn = 1;
	time_t current_time = time(NULL);
	times = localtime(&current_time);
}

Game::~Game()
{
	std::ofstream out;

	out.open("match logs.txt", std::ios_base::app);
	out << std::setfill('0');
	out << times->tm_year + 1900 << " - " << times->tm_mon + 1 << " - " << times->tm_mday << " / " 
		<< times->tm_hour << ":" << std::setw(2) << times->tm_min << " - 1) " << players[0].name;
	
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		delete players[i]
	}
}
