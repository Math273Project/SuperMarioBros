#include "MarioGame.h"
#include "ObjectMario.h"
#include "ObjectBlock.h"
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
		arena.setMarioVx(MARIO_SMALL_SPEED);
		MarioRun();

	}
	else if (input_->isKeyDown(MOVE_LEFT_KEY) && arena.getMarioX() - centerx_ > 0 && !arena.getMarioDying() && !arena.getMarioInEvent()) // some edit here to make Mario cannot go back
	{
		mario_.flipHorizontal(true);
		arena.setMarioVx(-MARIO_SMALL_SPEED);
		MarioRun();
	}
	else if (!arena.getMarioDying())
	{
		arena.setMarioVx(0);
		MarioStop();
	}

	if (input_->isKeyDown(MOVE_UP_KEY) && !arena.getMarioDying())
	{
		MarioJump();
		if (arena.MarioDownToEarth())
		{
			arena.setMarioVy(-MARIO_SPEED);
		}
	}

	if (input_->isKeyDown(MOVE_DOWN_KEY) && !arena.getMarioDying())
	{
		//Very minimal usage: only works if mario can move down
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
				mario_.setX(i->getx() - centerx_);
				mario_.setY(i->gety());
				mario_.update(frameTime_);
				mario_.draw();
				break;

			case MARIO_BIG: // change to big
				mario_.setX(i->getx() - centerx_);
				mario_.setY(i->gety());
				mario_.update(frameTime_);
				mario_.draw();
				break;

			case MARIO_SUPER: // change to super
				mario_.setX(i->getx() - centerx_);
				mario_.setY(i->gety());
				mario_.update(frameTime_);
				mario_.draw();
				break;

			case MUSHROOM:
				mushroom_.setX(i->getx() - centerx_);
				mushroom_.setY(i->gety());
				mushroom_.draw();
				break;
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

void MarioGame::MarioRun()
{
	bool done = false;
	mario_.setLoop(true);
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

void MarioGame::MarioStop()
{
	bool done = false;
	mario_.setLoop(false);
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

void MarioGame::MarioJump()
{
	bool done = false;
	mario_.setLoop(false);
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

void MarioGame::MarioUpgrade()
{

}

void MarioGame::MarioDowngrade()
{

}

void MarioGame::level_one()
{
	ObjectMario* objectMario = new ObjectMario(50, 570, (int)MARIO_SMALL_SPEED, 0);
	//ObjectBlock* objectBlock = new ObjectBlock(50, 250);
	ObjectFloor* objectFloor = new ObjectFloor(0, 618, 6000);
	ObjectBrick* objectBrick = new ObjectBrick(989, 420);

	ObjectQuestion* objectQuestion = new ObjectQuestion(791, 420, MUSHROOM);
	ObjectQuestion* objectQuestion2 = new ObjectQuestion(1039, 420, POWERUP);
	ObjectQuestion* objectQuestion3 = new ObjectQuestion(1139, 420, COIN);
	ObjectPowerup* objectPowerup = new ObjectPowerup(400, 300, 0, 0);
	ObjectCoin* objectCoin = new ObjectCoin(700, 550);

	ObjectPipe* objectPipeBig = new ObjectPipe(2274, 420, PIPE_BIG);
	ObjectPipe* objectPipeMiddle = new ObjectPipe(1878, 469, PIPE_MIDDLE);
	ObjectPipe* objectPipeSmall = new ObjectPipe(1384, 519, PIPE_SMALL);
	ObjectFlagPole* objectFlagPole = new ObjectFlagPole(1200, 150);

//	emplaceObject<ObjectMario>(50, 200, (int)MARIO_SPEED, 0);

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
	arena.addObject(objectFlagPole);

	//Initialize textures
	
	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture_.initialize(graphics_, BACKGROUND_START); //background should be split in multiple parts
	enemyTexture_.initialize(graphics_, MARIO_TEXTURE);
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

	enemy_.initialize(graphics_, MARIO_SMALL_WIDTH, MARIO_SMALL_HEIGHT, MARIO_SMALL_COLS, &enemyTexture_);
	block_.initialize(graphics_, BLOCK_WIDTH, BLOCK_HEIGHT, 1, &blocksTexture_);
	floor_.initialize(graphics_, FLOOR_WIDTH, FLOOR_HEIGHT, 1, &floorTexture_);
	brick_.initialize(graphics_, BRICK_WIDTH, BRICK_HEIGHT, 2, &blocksTexture_);
	brick_.setCurrentFrame(1);
	mushroom_.initialize(graphics_, MUSHROOM_WIDTH, MUSHROOM_HEIGHT, 2, &blocksTexture_);
	mushroom_.setCurrentFrame(2);
	question_.initialize(graphics_, QUESTION_WIDTH, QUESTION_HEIGHT, 3, &blocksTexture_);
	question_.setCurrentFrame(2);
	powerup_.initialize(graphics_, POWERUP_WIDTH, POWERUP_HEIGHT, 6, &blocksTexture_);
	powerup_.setCurrentFrame(10);
	coin_.initialize(graphics_, COIN_WIDTH, COIN_HEIGHT, 6, &blocksTexture_);
	coin_.setCurrentFrame(9);
	pipeBig_.initialize(graphics_, PIPE_WIDTH, PIPE_BIG_HEIGHT, 1, &pipeBigTexture_);
	pipeMiddle_.initialize(graphics_, PIPE_WIDTH, PIPE_MIDDLE_HEIGHT, 1, &pipeMiddleTexture_);
	pipeSmall_.initialize(graphics_, PIPE_WIDTH, PIPE_SMALL_HEIGHT, 1, &pipeSmallTexture_);
	flagPole_.initialize(graphics_, FLAG_POLE_WIDTH, FLAG_POLE_HEIGHT, 1, &flagPoleTexture_);
	flag_.initialize(graphics_, FLAG_WIDTH, FLAG_HEIGHT, 1, &flagTexture_);

	mario_.setX(50);     
	mario_.setY(512); //get rid of magic constant
	mario_.setFrames(MARIO_SMALL_START_FRAME , MARIO_SMALL_END_FRAME);   // animation frames
	mario_.setCurrentFrame(MARIO_SMALL_START_FRAME + 1);     // starting frame
	mario_.setFrameDelay(MARIO_SMALL_ANIMATION_DELAY);
	mario_.setDegrees(0);
	mario_.setScale(MARIO_SMALL_SCALE);
}
