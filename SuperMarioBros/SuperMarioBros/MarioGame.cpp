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

	//Initialize arena and started objects

	Arena& arena = Arena::getUniqueInstance();
	ObjectMario* objectMario = new ObjectMario(0, 50, 490, (int)MARIO_SPEED, 0);
	arena.pushBack(objectMario);

	//Initialize textures

	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture_.initialize(graphics_, BACKGROUND_START); //background will be split in multiple parts
	enemyTexture_.initialize(graphics_, /*temporary*/MARIO_TEXTURE);


	//Initialize images
	mario_.initialize(graphics_, TEXTURE_WIDTH, TEXTURE_HEIGHT, MARIO_COLS, &marioTexture_);
	background_.initialize(graphics_, GAME_WIDTH, GAME_HEIGHT, 1, &backgroundTexture_);
	enemy_.initialize(graphics_, )

	mario_.setX(50);     
	mario_.setY(490); //get rid of magic constant
	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0); 

}

void MarioGame::update()
{
	Image temp;
	Arena& arena = Arena::getUniqueInstance();
	for (const auto& i : arena.getMovingObjects())
	{
		/* 
		 * The textures of each entity needs to be updated
		 */
		switch (i->getType())
		{
		case SMALL_MARIO:
			temp.initialize(graphics_, (*i).getWidth(), (*i).getHeight(), 1, &marioTexture_);
			break;
		case BIG_MARIO:
			temp.initialize(graphics_, (*i).getWidth(), (*i).getHeight(), 1, &marioTexture_);
			break;
		case SUPER_MARIO:
			temp.initialize(graphics_, (*i).getWidth(), (*i).getHeight(), 1, &marioTexture_);
			break;
		case BLOCK:
			temp.initialize(graphics_, (*i).getWidth(), (*i).getHeight(), 1, &marioTexture_);
		default:
			break;
		}
	}

	for (const auto& i : arena.getStaticObjects())
	{
		switch (i->getType())
		{
		case SMALL_MARIO:
			break;
		default:
			break;
		}
	}
	mario_.update(frameTime_);

	if (input_->isKeyDown(MOVE_RIGHT_KEY))
	{
		arena.move(frameTime_ * 1000);
		arena.collisionDetection();

		/*mario_.setX(arena); // move mario right

		if (arena.getMario()->getx() > GAME_WIDTH) // If offscreen right
		{
			arena.getMario()->setx(-arena.getMario()->getWidth());
			mario_.setX(arena.getMario()->getx());// Position off screen left
			mario_.setScale(MARIO_SCALE); // Set to starting size
		}*/
	}

	if (input_->isKeyDown(MOVE_LEFT_KEY))
	{
		/*
		arena.move(frameTime_ * 1000);
		arena.getMario()->setvx(-MARIO_SPEED);
		mario_.setX(arena.getMario()->getx());

		if (arena.getMario()->getx() < 0)
		{
			arena.getMario()->setx(arena.getMario()->getWidth());
			mario_.setX(arena.getMario()->getx());
			mario_.setScale(MARIO_SCALE);
		}*/
	}

	if (input_->isKeyDown(MOVE_UP_KEY))
	{
		//make mario jump or move up
	}

	if (input_->isKeyDown(MOVE_DOWN_KEY))
	{
		//Very minimal usage: only works if mario can move down
		//ex: flag pole, . . .
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
