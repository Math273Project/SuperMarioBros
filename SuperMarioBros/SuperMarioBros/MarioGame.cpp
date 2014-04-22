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
	//Initialze textures
	Arena& arena = Arena::getUniqueInstance();
	ObjectMario* objectMario = new ObjectMario(0, 50, 490, MARIO_SPEED, 0);
	arena.pushBack(objectMario);
	//Initialize textures
	if (!marioTexture_.initialize(graphics_, "Textures\\Robot_Mario.bmp"))
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing Mario texture"));
	}
	if (!backgroundTexture_.initialize(graphics_, "Textures\\Level_One_resized.bmp"))
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

	mario_.setX(arena.getMario()->getx());     
	mario_.setY(arena.getMario()->gety()); //get rid of magic constant
	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0); 

}

void MarioGame::update()
{
	Arena& arena = Arena::getUniqueInstance();
	mario_.update(frameTime_);

	if (input_->isKeyDown(MOVE_RIGHT_KEY))
	{
		arena.move(frameTime_ * 1000);
		arena.getMario()->setvx(100);
		mario_.setX(arena.getMario()->getx()); // move mario right

		if (arena.getMario()->getx() > GAME_WIDTH) // If offscreen right
		{
			arena.getMario()->setx(-arena.getMario()->getWidth());
			mario_.setX(arena.getMario()->getx());// Position off screen left
			mario_.setScale(MARIO_SCALE); // Set to starting size
		}
	}

	if (input_->isKeyDown(MOVE_LEFT_KEY))
	{
		arena.move(frameTime_ * 1000);
		arena.getMario()->setvx(-100);
		mario_.setX(arena.getMario()->getx());

		if (arena.getMario()->getx() < 0)
		{
			arena.getMario()->setx(arena.getMario()->getWidth());
			mario_.setX(arena.getMario()->getx());
			mario_.setScale(MARIO_SCALE);
		}
	}
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
