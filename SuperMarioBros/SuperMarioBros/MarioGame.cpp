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
	ObjectMario* objectMario = new ObjectMario(0, 50, 490, (int)MARIO_SPEED, 0);
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

	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0); 

}
void MarioGame::update()
{
	arena.move(frameTime_*1000);
	arena.collisionDetection();
}

void MarioGame::render()
{
	graphics_->spriteBegin();
	
	background_.draw();
	for (const auto& i : arena.getMovingObjects())
	{
		switch (i->getType())
		{
		case SMALL_MARIO:
			mario_.setX(i->getx());
			mario_.setY(i->gety());
			mario_.setCurrentFrame(i->getCurrentFrame());
			
			mario_.update(frameTime_);
			i->setCurrentFrame(mario_.getCurrentFrame());
			mario_.draw();
			break;
		}
	}

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
