#include "MarioGame.h"
#include "ObjectMario.h"
#include "ObjectBlock.h"
#include "ObjectFloor.h"
MarioGame::MarioGame()
{
	centerx_ = 0;
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
	//Initialize arena and started objects

	ObjectMario* objectMario = new ObjectMario(0, 50, 490-300, (int)MARIO_SPEED, 0);
	ObjectBlock* objectBlock = new ObjectBlock(0, 50, 490+144-300);
	ObjectFloor* objectFloor = new ObjectFloor(0, 0, 600, 2000);

	arena.pushBack(objectMario);
	arena.pushBack(objectBlock);
	arena.pushBack(objectFloor);
	//Initialize textures
	
	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture_.initialize(graphics_, BACKGROUND_START); //background will be split in multiple parts
	enemyTexture_.initialize(graphics_, MARIO_TEXTURE);
	blocksTexture_.initialize(graphics_, BLOCKS);
	floorTexture_.initialize(graphics_, FLOOR_TEXTURE);


	//Initialize images
	mario_.initialize(graphics_, MARIO_BIG_WIDTH, MARIO_BIG_HEIGHT, MARIO_COLS, &marioTexture_);
	background_.initialize(graphics_, 16384, GAME_HEIGHT, 1, &backgroundTexture_); // some edit here, full load the background is okay.
	enemy_.initialize(graphics_, MARIO_SMALL_WIDTH, MARIO_SMALL_HEIGHT, MARIO_SMALL_COLS, &enemyTexture_);
	block_.initialize(graphics_, BLOCK_WIDTH, BLOCK_HEIGHT, 1, &blocksTexture_);
	floor_.initialize(graphics_, FLOOR_WIDTH, FLOOR_HEIGHT, 1, &floorTexture_);

	mario_.setX(50);     
	mario_.setY(512); //get rid of magic constant
	mario_.setFrames(MARIO_START_FRAME , MARIO_START_FRAME);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME + 8);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0);
	mario_.setScale(MARIO_SCALE);

	enemy_.setX(200);
	enemy_.setY(490);
	enemy_.setFrames(MARIO_SMALL_START_FRAME, MARIO_SMALL_END_FRAME);
	enemy_.setCurrentFrame(MARIO_SMALL_START_FRAME);
	enemy_.setFrameDelay(MARIO_SMALL_ANIMATION_DELAY);
	enemy_.setDegrees(0);
	enemy_.flipHorizontal(true);
	

}

void MarioGame::update()
{
	arena.move(frameTime_ * 1000);
	arena.freeFall(frameTime_ * 1000);
	arena.collisionDetection();
	arena.deleteDyingObject();

	if (arena.isGameOver())
	{
		PostQuitMessage(0); // end the game
	}

	if (arena.getMarioX() - centerx_ > GAME_WIDTH / 2) // move the center.
	{
		centerx_ = arena.getMarioX() - GAME_WIDTH / 2;
	}

	if (input_->isKeyDown(MOVE_RIGHT_KEY))
	{
		mario_.flipHorizontal(false);
		arena.setMarioVx(MARIO_SPEED);
		walk();
		
	}
	else if (input_->isKeyDown(MOVE_LEFT_KEY) && arena.getMarioX() - centerx_ > 0) // some edit here to make Mario cannot go back
	{
		mario_.flipHorizontal(true);
		arena.setMarioVx(-MARIO_SPEED);
	}
	else
	{
		arena.setMarioVx(0);
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

	background_.setX(-centerx_);
	background_.draw();
	
	for (const auto& i : arena.getStaticObjects())
	{
		switch (i->getType())
		{
		case BLOCK:
			block_.setX(i->getx() - centerx_);
			block_.setY(i->gety());
			block_.draw();
			break;
		case QUESTION:
			i->setx(i->getx() - centerx_);
			i->sety(i->gety() - centerx_);
			break;
		case FLOOR:
			int x = i->getx();
			while (x + FLOOR_WIDTH < i->getx() + i->getWidth())
			{
				floor_.setX(x - centerx_);
				floor_.setY(i->gety());
				floor_.draw();
				x += FLOOR_WIDTH;
			}
			floor_.setX(x - centerx_);
			floor_.setY(i->gety());
			floor_.initialize(graphics_, i->getx() + i->getWidth() - x, FLOOR_HEIGHT, 1, &floorTexture_); // need floor_.setWidth() function
			floor_.draw();
			floor_.initialize(graphics_, FLOOR_WIDTH, FLOOR_HEIGHT, 1, &floorTexture_);
			break;
		}
	}
	for (const auto& i : arena.getMovingObjects())
	{
		switch (i->getType())
		{
		case MARIO_SMALL:
			mario_.setX(i->getx() - centerx_);
			mario_.setY(i->gety());
			mario_.setCurrentFrame(i->getCurrentFrame());
			mario_.update(frameTime_);
			i->setCurrentFrame(mario_.getCurrentFrame());
			mario_.draw();
			
			break;
		}
	}
	//enemy_.draw();
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

void MarioGame::walk()
{
	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_START_FRAME + 3);
	mario_.setCurrentFrame(MARIO_START_FRAME + 1);
}
