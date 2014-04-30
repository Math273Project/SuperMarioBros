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
	ObjectBlock* block = new ObjectBlock(1, 200, 50);
	arena.pushBack(objectMario);
	arena.pushBack(block);

	//Initialize textures
	
	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture_.initialize(graphics_, BACKGROUND_START); //background will be split in multiple parts
	enemyTexture_.initialize(graphics_, MARIO_TEXTURE);
	blockTexture_.initialize(graphics_, BLOCKS);


	//Initialize images
	mario_.initialize(graphics_, BIG_MARIO_WIDTH, BIG_MARIO_HEIGHT, MARIO_COLS, &marioTexture_);
	background_.initialize(graphics_, GAME_WIDTH, GAME_HEIGHT, 1, &backgroundTexture_);
	enemy_.initialize(graphics_, SMALL_MARIO_WIDTH, SMALL_MARIO_HEIGHT, SMALL_MARIO_COLS, &enemyTexture_);
	block_.initialize(graphics_, 72, 72, 1, &blockTexture_);

	block_.setX(1000);
	block_.setY(490);

	mario_.setX(50);     
	mario_.setY(512); //get rid of magic constant
	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0);
	mario_.setScale(.75);

	enemy_.setX(200);
	enemy_.setY(490);
	enemy_.setFrames(SMALL_MARIO_START_FRAME, SMALL_MARIO_END_FRAME);
	enemy_.setCurrentFrame(SMALL_MARIO_START_FRAME);
	enemy_.setFrameDelay(SMALL_MARIO_ANIMATION_DELAY);
	enemy_.setDegrees(0);
	enemy_.flipHorizontal(true);
	

}

void MarioGame::update()
{
	Image temp;
	for (const auto& i : arena.getMovingObjects())
	{
		/* 
		 * The textures of each entity needs to be updated
		 */
		switch (i->getType())
		{
		case SMALL_MARIO:
			temp.initialize(graphics_, (*i).getWidth(), (*i).getHeight(), 1, &marioTexture_);
			temp.setX(i->getx());
			temp.setY(i->gety());
			temp.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
			temp.setCurrentFrame(MARIO_START_FRAME);     // starting frame
			temp.setFrameDelay(MARIO_ANIMATION_DELAY);
			temp.setDegrees(0);
			temp.draw();
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
		arena.setMarioVx(100);
		arena.move(frameTime_ * 1000);
		arena.collisionDetection();

		for (auto& i : arena.getMovingObjects())
		{
			if ((*i).getFacingDirection() == RIGHT)
			{
				mario_.flipHorizontal(false);
			}
		}
		mario_.setX(mario_.getX() + frameTime_ * mario_.getWidth());
		if (mario_.getX() > (GAME_WIDTH) / 2)
		{
			RECT update = background_.getSpriteDataRect();
			update.left += 1;
			update.right += 1;
			background_.setSpriteDataRect(update);
			mario_.setX(GAME_WIDTH / 2);

			block_.setX(block_.getX() - 1);
		}
	}

	if (input_->isKeyDown(MOVE_LEFT_KEY))
	{
		arena.setMarioVx(100);
		arena.move(frameTime_ * 1000);
		arena.collisionDetection();

		mario_.flipHorizontal(true);
		mario_.setX(mario_.getX() - frameTime_ * mario_.getWidth());
		if (mario_.getX() < 0)
		{
			mario_.setX(0);
		}
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

	//loop through images to draw
	Image temp;

	for (const auto& i : arena.getMovingObjects())
	{
		/*
		* The textures of each entity needs to be updated
		*/
		switch (i->getType())
		{
		case SMALL_MARIO:
			temp.initialize(graphics_, (*i).getWidth(), (*i).getHeight(), 1, &marioTexture_);
			temp.setX(i->getx());
			temp.setY(i->gety());
			temp.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
			temp.setCurrentFrame(MARIO_START_FRAME);     // starting frame
			temp.setFrameDelay(MARIO_ANIMATION_DELAY);
			temp.setDegrees(0);
			temp.draw();
			break;
		}
	}

	background_.draw();
	mario_.draw();
	enemy_.draw();
	block_.draw();

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
