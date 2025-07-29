#include "Game.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;
}

Game& Game::Get()
{
	return *instance;
}