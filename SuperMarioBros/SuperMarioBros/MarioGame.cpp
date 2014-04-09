#include "MarioGame.h"

MarioGame::MarioGame()
{

}

MarioGame::~MarioGame()
{
	releaseAll();
	Game::deleteAll();
}

void MarioGame::initialize(HWND hWnd, bool fullscreen)
{
	Game::initialize(hWnd, fullscreen);
	//Initialize textures
	if (!marioTexture_.initialize(graphics_, "Robot_Mario.png"))
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing Mario texture"));
	}
	if (!backgroundTexture_.initialize(graphics_, "Level_One.png"))
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing Mario texture"));
	}

	//Initialize images
	if (!mario_.initialize(graphics_, TEXTURE_WIDTH, TEXTURE_HEIGHT, MARIO_COLS, &marioTexture_))
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing mario"));
	}
	if (!background_.initialize(graphics_, 1280, 720, 1, &backgroundTexture_))
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing background"));
	}

	mario_.setX(GAME_WIDTH / 2);     
	mario_.setY(GAME_HEIGHT / 2);
	mario_.setFrames(MARIO_START_FRAME, MARIO_END_FRAME - 3);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0);                     // angle of ship

	background_.setX(0);
	background_.setY(0);
}
void MarioGame::update()
{
	mario_.update(frameTime_);
}

void MarioGame::ai()
{

}

void MarioGame::collisions()
{

}

void MarioGame::render()
{
	graphics_->spriteBegin();

	background_.draw();
	mario_.draw();

	graphics_->spriteEnd();
}

void MarioGame::releaseAll()
{
	marioTexture_.onLostDevice();

	Game::releaseAll();
	return;
}

void MarioGame::resetAll()
{
	marioTexture_.onResetDevice();
	Game::resetAll();
	return;
}