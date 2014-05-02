#include "MarioGame.h"
#include "ObjectMario.h"
#include "ObjectBlock.h"
#include "ObjectFloor.h"
#include "ObjectBrick.h"
#include "ObjectMushroom.h"
#include "ObjectQuestion.h"
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

	ObjectMario* objectMario = new ObjectMario(50, 200, (int)MARIO_SPEED, 0);
	ObjectBlock* objectBlock = new ObjectBlock(50, 250);
	ObjectFloor* objectFloor = new ObjectFloor(0, 600, 6000);
	ObjectBrick* objectBrick = new ObjectBrick(200, 250);
	ObjectQuestion* objectQuestion = new ObjectQuestion(400, 250, MUSHROOM);

	arena.addObject(objectMario);
	arena.addObject(objectBlock);
	arena.addObject(objectFloor);
	arena.addObject(objectBrick);
	arena.addObject(objectQuestion);
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
	brick_.initialize(graphics_, BRICK_WIDTH, BRICK_HEIGHT, 2, &blocksTexture_);
	brick_.setCurrentFrame(1);
	mushroom_.initialize(graphics_, MUSHROOM_WIDTH, MUSHROOM_HEIGHT, 2, &blocksTexture_);
	mushroom_.setCurrentFrame(2);
	question_.initialize(graphics_, QUESTION_WIDTH, QUESTION_HEIGHT, 3, &blocksTexture_);
	question_.setCurrentFrame(2);

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
	arena.processEvent();
	arena.removeOutOfBoundObject();

	if (arena.isGameOver())
	{
		PostQuitMessage(0); // end the game
	}

	if (arena.getMarioX() - centerx_ > GAME_WIDTH / 2) // move the center.
	{
		centerx_ = arena.getMarioX() - GAME_WIDTH / 2;
	}

	if (input_->isKeyDown(MOVE_RIGHT_KEY) && !arena.getMarioDying())
	{
		mario_.flipHorizontal(false);
		arena.setMarioVx(MARIO_SPEED);
		walk();
		
	}
	else if (input_->isKeyDown(MOVE_LEFT_KEY) && arena.getMarioX() - centerx_ > 0 && !arena.getMarioDying()) // some edit here to make Mario cannot go back
	{
		mario_.flipHorizontal(true);
		arena.setMarioVx(-MARIO_SPEED);
	}
	else if (!arena.getMarioDying())
	{
		arena.setMarioVx(0);
	}
	
	if (input_->isKeyDown(MOVE_UP_KEY) && !arena.getMarioDying())
	{
		if (arena.MarioDownToEarth())
			arena.setMarioVy(-MARIO_SPEED);
		//make mario jump or move up
	}

	if (input_->isKeyDown(MOVE_DOWN_KEY) && !arena.getMarioDying())
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
	
	for (const auto& i : arena.getObjects())
	{
		if (i->isEnabled() && (i->getx() + i->getWidth() - centerx_ > 0 || i->getx() - centerx_ < GAME_WIDTH))
		{
			ObjectType m = i->getType();
			switch (i->getType())
			{
			case BLOCK:
				block_.setX(i->getx() - centerx_);
				block_.setY(i->gety());
				block_.draw();
				break;
			case BRICK:
			case BRICK_DYING:
				brick_.setX(i->getx() - centerx_);
				brick_.setY(i->gety());
				brick_.draw();
				break;
			case QUESTION:
				question_.setX(i->getx() - centerx_);
				question_.setY(i->gety());
				question_.draw();
				break;
			case FLOOR:
				int x;
				if (i->getx() - centerx_ < 0)
					x = i->getx() + FLOOR_WIDTH * ((int)(centerx_ - i->getx()) / FLOOR_WIDTH);
				else
					x = i->getx();
				while ((x + FLOOR_WIDTH < i->getx() + i->getWidth()) && (x + FLOOR_WIDTH - centerx_ < GAME_WIDTH))
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
			case MARIO_SMALL:
			case MARIO_DYING:
				mario_.setX(i->getx() - centerx_);
				mario_.setY(i->gety());
				mario_.setCurrentFrame(i->getCurrentFrame());
				mario_.update(frameTime_);
				i->setCurrentFrame(mario_.getCurrentFrame());
				mario_.draw();
				break;

			case MUSHROOM:
			case MUSHROOM_DYING:
				mushroom_.setX(i->getx() - centerx_);
				mushroom_.setY(i->gety());
				mushroom_.draw();
				break;
			}
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

void MarioGame::walk()
{
	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_START_FRAME + 3);
	mario_.setCurrentFrame(MARIO_START_FRAME + 1);
}
