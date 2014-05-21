#include "MarioGame.h"
#include "ObjectMario.h"
#include "ObjectBlock.h"
#include "ObjectEnemy.h"
#include "ObjectTurtle.h"
#include "ObjectFloor.h"
#include "ObjectBrick.h"
#include "ObjectMushroom.h"
#include "ObjectQuestion.h"
#include "ObjectPowerup.h"
#include "ObjectPipe.h"
#include "ObjectCoin.h"
#include "ObjectFlagPole.h"

template <typename... Args> void emplaceObject(Args&&... args)
{
	Object* object = new T(std::forward<Args>(args)...);
}
MarioGame::MarioGame()
{
	centerx_ = 0;
	marioLives_ = 3;
}

MarioGame::~MarioGame()
{
	releaseAll();
	Game::deleteAll();
}

void MarioGame::initialize(HWND hWnd, bool fullscreen)
{
	Game::initialize(hWnd, fullscreen);

	//load level; only have one to start
	level_one();
	
	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture_.initialize(graphics_, BACKGROUND_START); //background should be split in multiple parts
	goombaTexture_.initialize(graphics_, ENEMY_TEXTURE);
	turtleTexture_.initialize(graphics_, ENEMY_2_TEXTURE);
	blocksTexture_.initialize(graphics_, BLOCKS);
	floorTexture_.initialize(graphics_, FLOOR_TEXTURE);
	pipeBigTexture_.initialize(graphics_, PIPE_BIG_TEXTURE);
	pipeMiddleTexture_.initialize(graphics_, PIPE_MIDDLE_TEXTURE);
	pipeSmallTexture_.initialize(graphics_, PIPE_SMALL_TEXTURE);
	flagPoleTexture_.initialize(graphics_, FLAG_POLE_TEXTURE);
	flagTexture_.initialize(graphics_, FLAG_TEXTURE);

	//Initialize images
	mario_.initialize(graphics_, MARIO_SMALL_WIDTH, MARIO_SMALL_HEIGHT, MARIO_SMALL_COLS, &marioTexture_);
	background_.initialize(graphics_, 16384, GAME_HEIGHT, 1, &backgroundTexture_);

	goomba_.initialize(graphics_, ENEMY_WIDTH, ENEMY_HEIGHT, 2, &goombaTexture_);
	turtle_.initialize(graphics_, ENEMY_WIDTH, TURTLE_HEIGHT, 6, &turtleTexture_);
	enemyDying_.initialize(graphics_, ENEMY_DYING_WIDTH, ENEMY_DYING_HEIGHT, 4, &goombaTexture_);
	block_.initialize(graphics_, BLOCK_WIDTH, BLOCK_HEIGHT, 5, &blocksTexture_);
	floor_.initialize(graphics_, FLOOR_WIDTH, FLOOR_HEIGHT, 1, &floorTexture_);
	brick_.initialize(graphics_, BRICK_WIDTH, BRICK_HEIGHT, 2, &blocksTexture_);
	brick_.setCurrentFrame(1);
	mushroom_.initialize(graphics_, MUSHROOM_WIDTH, MUSHROOM_HEIGHT, 2, &blocksTexture_);
	mushroom_.setCurrentFrame(2);
	question_.initialize(graphics_, QUESTION_WIDTH, QUESTION_HEIGHT, 3, &blocksTexture_);
	question_.setCurrentFrame(2);
	questionBlock_.initialize(graphics_, QUESTION_WIDTH, QUESTION_HEIGHT, 6, &blocksTexture_);
	questionBlock_.setCurrentFrame(4);
	powerup_.initialize(graphics_, POWERUP_WIDTH, POWERUP_HEIGHT, 6, &blocksTexture_);
	powerup_.setCurrentFrame(10);
	coin_.initialize(graphics_, COIN_WIDTH, COIN_HEIGHT, 6, &blocksTexture_);
	coin_.setCurrentFrame(9);
	pipeBig_.initialize(graphics_, PIPE_WIDTH, PIPE_BIG_HEIGHT, 1, &pipeBigTexture_);
	pipeMiddle_.initialize(graphics_, PIPE_WIDTH, PIPE_MIDDLE_HEIGHT, 1, &pipeMiddleTexture_);
	pipeSmall_.initialize(graphics_, PIPE_WIDTH, PIPE_SMALL_HEIGHT, 1, &pipeSmallTexture_);
	flagPole_.initialize(graphics_, FLAG_POLE_WIDTH, FLAG_POLE_HEIGHT, 1, &flagPoleTexture_);
	flag_.initialize(graphics_, FLAG_WIDTH, FLAG_HEIGHT, 1, &flagTexture_);

	turtle_.setFrames(3, 4);
	turtle_.setCurrentFrame(3);

}

void MarioGame::update()
{
	arena.move(frameTime_ * 1000);
	arena.freeFall(frameTime_ * 1000);
	arena.collisionDetection();
	arena.processEvent();
	arena.removeOutOfBoundObject();
	
	if (input_->isKeyDown(MOVE_RIGHT_KEY) && !arena.getMarioDying() && !arena.getMarioInEvent())
	{
		mario_.flipHorizontal(false);
		arena.setMarioVx(MARIO_SPEED);
		marioRun();

	}
	else if (input_->isKeyDown(MOVE_LEFT_KEY) && arena.getMarioX() - centerx_ > 0 && !arena.getMarioDying() && !arena.getMarioInEvent()) // some edit here to make Mario cannot go back
	{
		mario_.flipHorizontal(true);
		arena.setMarioVx(-MARIO_SPEED);
		marioRun();
	}
	else if (arena.getMarioDying())
	{
		for (const auto& i : arena.getObjects())
		{
			if (i->getType() == MARIO_DYING)
			{
				marioDeath();
			}
		}
	}
	else
	{
		arena.setMarioVx(0);
		marioStop();
	}

	if (input_->isKeyDown(MOVE_UP_KEY) && !arena.getMarioDying())
	{
		marioJump();
		if (arena.MarioDownToEarth())
		{
			arena.setMarioVy(-MARIO_SPEED);
		}
	}

	if (input_->isKeyDown(MOVE_DOWN_KEY) && !arena.getMarioDying())
	{
		//Very minimal usage: only works if mario can move down
		marioDown();
	}

	if (arena.isGameOver())
	{
		PostQuitMessage(0); // end the game
	}

	if (arena.getMarioX() - centerx_ > GAME_WIDTH / 2) // move the center.
	{
		centerx_ = arena.getMarioX() - GAME_WIDTH / 2;
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
			case QUESTION_BLOCK:
				questionBlock_.setX(i->getx() - centerx_);
				questionBlock_.setY(i->gety());
				questionBlock_.draw();
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
			case POWERUP:
				powerup_.setX(i->getx() - centerx_);
				powerup_.setY(i->gety());
				powerup_.draw();
				break;
			case MARIO_SMALL:
			case MARIO_DYING:
			case MARIO_BIG:
			case MARIO_SUPER:
				mario_.setX(i->getx() - centerx_);
				mario_.setY(i->gety());
				mario_.update(frameTime_);
				mario_.draw();
				break;

			case MUSHROOM:
			case MUSHROOM_DYING:
				mushroom_.setX(i->getx() - centerx_);
				mushroom_.setY(i->gety());
				mushroom_.draw();
				break;

			case PIPE_BIG:
				pipeBig_.setX(i->getx() - centerx_);
				pipeBig_.setY(i->gety());
				pipeBig_.draw();
				break;

			case PIPE_MIDDLE:
				pipeMiddle_.setX(i->getx() - centerx_);
				pipeMiddle_.setY(i->gety());
				pipeMiddle_.draw();
				break;

			case PIPE_SMALL:
				pipeSmall_.setX(i->getx() - centerx_);
				pipeSmall_.setY(i->gety());
				pipeSmall_.draw();
				break;

			case COIN:
				coin_.setX(i->getx() - centerx_);
				coin_.setY(i->gety());
				coin_.draw();
				break;

			case FLAG_POLE:
				flagPole_.setX(i->getx() - centerx_);
				flagPole_.setY(i->gety());
				flagPole_.draw();
				break;

			case FLAG:
				flag_.setX(i->getx() - centerx_);
				flag_.setY(i->gety());
				flag_.draw();
				break;

			case ENEMY:
				if (i->getvx() >= 0)
					goomba_.setCurrentFrame(0);
				else
					goomba_.setCurrentFrame(1);
				goomba_.setX(i->getx() - centerx_);
				goomba_.setY(i->gety());
				goomba_.draw();
				break;

			case ENEMY_DYING:
				if (i->getvx() >= 0)
					enemyDying_.setCurrentFrame(2);
				else
					enemyDying_.setCurrentFrame(3);
				enemyDying_.setX(i->getx() - centerx_);
				enemyDying_.setY(i->gety());
				enemyDying_.draw();
				break;
			case TURTLE:
				if (i->getvx() >= 0)
				{
					turtle_.flipHorizontal(true);
					turtle_.setFrames(3, 4);
					turtle_.setCurrentFrame(3);
				}
				else
				{
					turtle_.flipHorizontal(false);
				}
				turtle_.update(frameTime_);
				turtle_.setX(i->getx() - centerx_);
				turtle_.setY(i->gety());
				turtle_.draw();
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

void MarioGame::marioRun()
{
	bool done = false;
	for (auto& i = arena.getObjects().begin(); i != arena.getObjects().end() && !done; ++i)
	{
		switch ((*i)->getType())
		{
		case MARIO_SMALL:
			mario_.setHeight(MARIO_SMALL_HEIGHT);
			mario_.setCols(MARIO_SMALL_COLS);
			mario_.setFrames(MARIO_SMALL_START_FRAME + 1, MARIO_SMALL_START_FRAME + 3);
			mario_.setFrameDelay(MARIO_SMALL_ANIMATION_DELAY);
			done = true;
			break;
		case MARIO_SUPER:
			mario_.setHeight(MARIO_SUPER_HEIGHT);
			mario_.setCols(MARIO_SUPER_COLS);
			mario_.setFrames(MARIO_SUPER_START_FRAME + 1, MARIO_SUPER_START_FRAME + 3);
			mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
			done = true;
			break;
		case MARIO_BIG:
			mario_.setHeight(MARIO_BIG_HEIGHT);
			mario_.setCols(MARIO_COLS);
			mario_.setFrames(MARIO_START_FRAME + 1, MARIO_START_FRAME + 3);
			mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
			done = true;
			break;
		}
	}
}

void MarioGame::marioStop()
{
	bool done = false;
	for (auto& i = arena.getObjects().begin(); i != arena.getObjects().end() && !done; ++i)
	{
		switch ((*i)->getType())
		{
		case MARIO_SMALL:
			mario_.setHeight(MARIO_SMALL_HEIGHT);
			mario_.setCols(MARIO_SMALL_COLS);
			mario_.setFrames(MARIO_SMALL_START_FRAME, MARIO_SMALL_START_FRAME);
			mario_.setCurrentFrame(MARIO_SMALL_START_FRAME);
			done = true;
			break;
		case MARIO_SUPER:
			mario_.setHeight(MARIO_SUPER_HEIGHT);
			mario_.setCols(MARIO_SUPER_COLS);
			mario_.setFrames(MARIO_SUPER_START_FRAME, MARIO_SUPER_START_FRAME);
			mario_.setCurrentFrame(MARIO_SUPER_START_FRAME);
			done = true;
			break;
		case MARIO_BIG:
			mario_.setHeight(MARIO_BIG_HEIGHT);
			mario_.setCols(MARIO_COLS);
			mario_.setFrames(MARIO_START_FRAME, MARIO_END_FRAME);
			mario_.setCurrentFrame(MARIO_START_FRAME);
			done = true;
			break;
		}
	}
}

void MarioGame::marioJump()
{
	bool done = false;
	for (auto& i = arena.getObjects().begin(); i != arena.getObjects().end() && !done; ++i)
	{
		switch ((*i)->getType())
		{
		case MARIO_SMALL:
			mario_.setHeight(MARIO_SMALL_HEIGHT);
			mario_.setCols(MARIO_SMALL_COLS);
			mario_.setFrames(MARIO_SMALL_START_FRAME + 5, MARIO_SMALL_START_FRAME + 5);
			mario_.setCurrentFrame(MARIO_SMALL_START_FRAME + 5);
			done = true;
			break;
		case MARIO_SUPER:
			mario_.setHeight(MARIO_SUPER_HEIGHT);
			mario_.setCols(MARIO_SUPER_COLS);
			mario_.setFrames(MARIO_SUPER_START_FRAME + 5, MARIO_SUPER_START_FRAME + 5);
			mario_.setCurrentFrame(MARIO_SUPER_START_FRAME + 5);
			done = true;
			break;
		case MARIO_BIG:
			mario_.setHeight(MARIO_BIG_HEIGHT);
			mario_.setCols(MARIO_COLS);
			mario_.setFrames(MARIO_START_FRAME + 5, MARIO_START_FRAME + 5);
			mario_.setCurrentFrame(MARIO_START_FRAME + 5);
			done = true;
			break;
		}
	}
}

void MarioGame::marioDown()
{

}

void MarioGame::marioUpgrade()
{

}

void MarioGame::marioDowngrade()
{

}

void MarioGame::marioDeath()
{
	mario_.setHeight(MARIO_SMALL_HEIGHT);
	mario_.setCols(MARIO_SMALL_COLS);
	mario_.setFrames(MARIO_SMALL_START_FRAME + 6, MARIO_SMALL_START_FRAME + 6);
	mario_.setCurrentFrame(MARIO_SMALL_START_FRAME + 6);
}

void MarioGame::level_one()
{
	ObjectMario* objectMario = new ObjectMario(50, 570, (int)MARIO_SPEED, 0);
	//ObjectBlock* objectBlock = new ObjectBlock(50, 250);
	ObjectFloor* objectFloor = new ObjectFloor(0, 618, 3412);
	ObjectBrick* objectBrick = new ObjectBrick(989, 420);

	ObjectQuestion* objectQuestion = new ObjectQuestion(791, 420, MUSHROOM);
	ObjectQuestion* objectQuestion2 = new ObjectQuestion(1039, 420, POWERUP);
	ObjectQuestion* objectQuestion3 = new ObjectQuestion(1139, 420, COIN);
	ObjectPowerup* objectPowerup = new ObjectPowerup(400, 300, 0, 0);
	ObjectCoin* objectCoin = new ObjectCoin(700, 550);

	ObjectPipe* objectPipeBig = new ObjectPipe(2274, 420, PIPE_BIG);
	ObjectPipe* objectPipeMiddle = new ObjectPipe(1878, 469, PIPE_MIDDLE);
	ObjectPipe* objectPipeSmall = new ObjectPipe(1384, 519, PIPE_SMALL);
	ObjectPipe* objectPipeBig2 = new ObjectPipe(2818, 420, PIPE_BIG);
	ObjectFlagPole* objectFlagPole = new ObjectFlagPole(9802, 150);
	ObjectEnemy* objectEnemy = new ObjectEnemy(500, 570, -100, 0);
	ObjectTurtle* objectTurtle = new ObjectTurtle(1800, 570, 100, 0);

	arena.addObject(objectMario);
	//arena.addObject(objectBlock);
	arena.addObject(objectFloor);
	arena.addObject(objectBrick);
	arena.addObject(objectQuestion);
	arena.addObject(objectQuestion2);
	arena.addObject(objectQuestion3);
	arena.addObject(objectPowerup);
	arena.addObject(objectCoin);
	arena.addObject(objectPipeBig);
	arena.addObject(objectPipeMiddle);
	arena.addObject(objectPipeSmall);
	arena.addObject(objectPipeBig2);
	arena.addObject(objectFlagPole);
	arena.addObject(objectEnemy);
	arena.addObject(objectTurtle);
}
