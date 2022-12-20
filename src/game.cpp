#include <iostream>
#include <string>
#include <vector>

#include "board.h"
#include "player.h"
#include "inputHandler.h"
#include "game.h"

Game::Game(Player player1, Player player2)
{
	int height = input.get_input<int>("What's the board height?");
	int width = input.get_input<int>("What's the board width?");
	this->board = Board board(width,height);
	std::array<Player, 2> players = { player1, player2 };
	this->players = players;
}

Game::~Game()
{

}

Game::start()
{

}
