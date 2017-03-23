
#include "Game.h"

Game *Game::instance = 0;

Game::Game() 
{
	
}

Game::~Game()
{
	
}


Game *Game::init()
{
	if(!Game::instance)
	{
		Game::instance = new Game;
	}
	else
	{
		fprintf(stderr, "WARNING: Game::init() has already been called.\n");
	}
	return Game::instance;
}

//----------------------------------------------------------
Game *Game::getInstance()
{
	if(!instance)
	{
		return Game::init();
	}
	else
		return Game::instance;
}

//----------------------------------------------------------
void Game::destroy()
{
	delete Game::instance;
	Game::instance = 0;
}