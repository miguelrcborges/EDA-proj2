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

Game::Game(Player* pointer_player1, Player* pointer_player2)
{
	int height = input.get_input<int>("What's the board height?");
	int width = input.get_input<int>("What's the board width?");
	this->board = Board board(width,height);
	std::array<Player* , 2> players = { pointer_player1 , pointer_player2 };
	this->players = players;
	this->turn = 1;
	time_t current_time = time(NULL);
	this->times = localtime(&current_time);
}

Game::~Game()
{
	std::ofstream out;
	out.open("match logs.txt", std::ios_base::app);
	out << std::setfill('0');
	out << times->tm_year + 1900 << " - " << times->tm_mon + 1 << " - " << times->tm_mday << " / " 
		<< times->tm_hour << ":" << std::setw(2) << times->tm_min << " - 1) " << players[0].name;

}
