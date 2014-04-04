#include "Game.h"

Game::Game()
{
	//input_ = new Input(); // Initialize keyboard input immediately
	// Additional initialization is handled in later call to input->
	// initialize()
	paused_ = false; // Game is not paused
	graphics_ = NULL;
	initialized_ = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

void Game::initialize(HWND hwnd)
{

}

void Game::run(HWND)
{

}

void Game::releaseAll()
{

}

void Game::resetAll()
{

}

void Game::deleteAll()
{

}

void Game::renderGame()
{
}

void Game::handleLostGraphicsDevice()
{

}

