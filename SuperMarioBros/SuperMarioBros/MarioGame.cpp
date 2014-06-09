#include "MarioGame.h"
#include "ObjectMario.h"
#include "ObjectBlock.h"
#include "ObjectGoomba.h"
#include "ObjectTurtle.h"
#include "ObjectFloor.h"
#include "ObjectBrick.h"
#include "ObjectMushroom.h"
#include "ObjectQuestion.h"
#include "ObjectPowerup.h"
#include "ObjectPipe.h"
#include "ObjectCoin.h"
#include "ObjectFlagPole.h"
#include "ObjectTurtle.h"
#include "ObjectVictorySpot.h"
#include "ObjectGoomba.h"

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

	//load level; only have one to start
	level_one();
	levelID_.initialize(graphics_, 48, "Arial");
	ScoreText_.initialize(graphics_, 48, "Arial");
	equal_.initialize(graphics_, 32, "Arial");
	
	bulletTexture_.initialize(graphics_, BULLET_TEXTURE);
	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture1_.initialize(graphics_, BACKGROUND1_TEXTURE); //background should be split in multiple parts
	backgroundTexture2_.initialize(graphics_, BACKGROUND2_TEXTURE);
	goombaTexture_.initialize(graphics_, GOOMBA_TEXTURE);
	blocksTexture_.initialize(graphics_, BLOCKS);
	floorTexture_.initialize(graphics_, FLOOR_TEXTURE);
	pipeBigTexture_.initialize(graphics_, PIPE_BIG_TEXTURE);
	pipeMiddleTexture_.initialize(graphics_, PIPE_MIDDLE_TEXTURE);
	pipeSmallTexture_.initialize(graphics_, PIPE_SMALL_TEXTURE);
	flagPoleTexture_.initialize(graphics_, FLAG_POLE_TEXTURE);
	flagTexture_.initialize(graphics_, FLAG_TEXTURE);
	turtleTexture_.initialize(graphics_, TURTLE_TEXTURE);
	flowerTexture_.initialize(graphics_, FLOWER_TEXTURE);
	scoreTexture_.initialize(graphics_, SEVENSEGMENTS);

	//Initialize images
	score_.initialize(graphics_, &scoreTexture_, 50, 50, .3, 6, D3DCOLOR_XRGB(255, 255, 255));
	coinsCollected_.initialize(graphics_, &scoreTexture_, 600, 5, .3, 2, D3DCOLOR_XRGB(255, 255, 255));
	bullet_.initialize(graphics_, BULLET_WIDTH, BULLET_HEIGHT, 1, &bulletTexture_);
	mario_.initialize(graphics_, MARIO_SMALL_WIDTH, MARIO_SMALL_HEIGHT, MARIO_SMALL_COLS, &marioTexture_);
	background1_.initialize(graphics_, 5170, GAME_HEIGHT, 1, &backgroundTexture1_);
	background2_.initialize(graphics_, 5170, GAME_HEIGHT, 1, &backgroundTexture2_);
	block_.initialize(graphics_, BLOCK_WIDTH, BLOCK_HEIGHT, 6, &blocksTexture_);
	block_.setCurrentFrame(5);
	goomba_.initialize(graphics_, GOOMBA_WIDTH, GOOMBA_HEIGHT, 2, &goombaTexture_);
	turtle_.initialize(graphics_, GOOMBA_WIDTH, TURTLE_HEIGHT, 6, &turtleTexture_);
	turtleSpin_.initialize(graphics_, TURTLE_SPIN_WIDTH, TURTLE_SPIN_HEIGHT, 5, &turtleTexture_);
	goombaDying_.initialize(graphics_, GOOMBA_DYING_WIDTH, GOOMBA_DYING_HEIGHT, 4, &goombaTexture_);
	goombaDying_.setFrames(2, 3);
	goombaDying_.setCurrentFrame(2);
	floor_.initialize(graphics_, FLOOR_WIDTH, FLOOR_HEIGHT, 1, &floorTexture_);
	brick_.initialize(graphics_, BRICK_WIDTH, BRICK_HEIGHT, 2, &blocksTexture_);
	brick_.setCurrentFrame(1);
	mushroom_.initialize(graphics_, MUSHROOM_WIDTH, MUSHROOM_HEIGHT, 2, &blocksTexture_);
	mushroom_.setCurrentFrame(2);
	question_.initialize(graphics_, QUESTION_WIDTH, QUESTION_HEIGHT, 4, &blocksTexture_);
	question_.setFrames(2, 3);
	question_.setFrameDelay(10);
	question_.setCurrentFrame(2);
	questionBlock_.initialize(graphics_, QUESTION_WIDTH, QUESTION_HEIGHT, 6, &blocksTexture_);
	questionBlock_.setCurrentFrame(4);
	powerup_.initialize(graphics_, POWERUP_WIDTH, POWERUP_HEIGHT, 6, &blocksTexture_);
	powerup_.setCurrentFrame(6);
	coin_.initialize(graphics_, COIN_WIDTH, COIN_HEIGHT, 6, &blocksTexture_);
	coin_.setCurrentFrame(9);
	pipeBig_.initialize(graphics_, PIPE_WIDTH, PIPE_BIG_HEIGHT, 1, &pipeBigTexture_);
	pipeMiddle_.initialize(graphics_, PIPE_WIDTH, PIPE_MIDDLE_HEIGHT, 1, &pipeMiddleTexture_);
	pipeSmall_.initialize(graphics_, PIPE_WIDTH, PIPE_SMALL_HEIGHT, 1, &pipeSmallTexture_);
	flagPole_.initialize(graphics_, FLAG_POLE_WIDTH, FLAG_POLE_HEIGHT, 1, &flagPoleTexture_);
	flag_.initialize(graphics_, FLAG_WIDTH, FLAG_HEIGHT, 1, &flagTexture_);
	turtle_.initialize(graphics_, TURTLE_WIDTH, TURTLE_HEIGHT, 4, &turtleTexture_);
	turtleSpin_.initialize(graphics_, TURTLE_SPIN_WIDTH, TURTLE_SPIN_HEIGHT, 6, &turtleTexture_);
	flower_.initialize(graphics_, FLOWER_WIDTH, FLOWER_HEIGHT, 1, &flowerTexture_);

	turtle_.setFrameDelay(.2);
	turtle_.setFrames(2, 3);

	goomba_.setFrameDelay(2);
	goomba_.setFrames(0, 1);

	turtleSpin_.setCurrentFrame(4);
}

void MarioGame::update()
{
	if (input_->isKeyDown(ENTER_KEY)) //Pause the game
	{
		if (paused_)
		{
			paused_ = false;
		}
		else
		{
			paused_ = true;
		}
		input_->clear(ENTER_KEY);
	}
	if (paused_)
	{
		return;
	}

	arena.setFrameTime(frameTime_ * 1000);
	arena.freeFall(); //update ungrounded ogjects
	arena.move();//update arena`

	arena.collisionDetection(); //detect collision
	arena.processEvent(); //process collisions
	arena.removeOutOfBoundObject(); //delete out of bound objects

	if (input_->isKeyDown(MOVE_RIGHT_KEY)) //right key pressed
	{
		mario_.flipHorizontal(false);
		arena.setMarioVx(MARIO_SPEED);
		if (!arena.MarioDownToEarth()) //mario is moving and airborne
		{
			marioJump();
		}
		else
		{
			marioRun();
		}

	}
	else if (input_->isKeyDown(MOVE_LEFT_KEY))
	{
		mario_.flipHorizontal(true);
		arena.setMarioVx(-MARIO_SPEED);
		if (!arena.MarioDownToEarth()) 
		{
			marioJump();
		}
		else
		{
			marioRun();
		}
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
		if (!arena.MarioDownToEarth())
			marioJump();
		else
			marioStop();
	}

	if (input_->isKeyDown(MOVE_UP_KEY))
	{
		marioJump();
		if (arena.MarioDownToEarth())
		{
			arena.setMarioVy(-MARIO_SPEED);
		}
	}

	if (input_->isKeyDown(MOVE_DOWN_KEY) && arena.MarioDownToEarth()
		&& !input_->isKeyDown(MOVE_RIGHT_KEY) && !input_->isKeyDown(MOVE_LEFT_KEY))
	{
		//Very minimal usage: only works if mario can move down
		marioDown();
	}

	if (input_->isKeyDown('Z') && arena.getMarioShootable())
	{
		arena.MarioShoot();
	}

	if (arena.isGameOver())
	{
		PostQuitMessage(0); // end the game
	}

	if (arena.getMarioX() - GAME_WIDTH / 2 > arena.getCenterx() && arena.getMarioX() + GAME_WIDTH / 2 <= 10340) // move the center.
	{
		arena.setCenterx(arena.getMarioX() - GAME_WIDTH / 2);
	}

}

void MarioGame::render()
{
	graphics_->spriteBegin();

	background1_.setX(-arena.getCenterx());
	background2_.setX(5170 - arena.getCenterx());
	background1_.draw();
	background2_.draw();

	levelID_.print(currentLevel_, 250, 0);
	ScoreText_.print("Mario", 50, 0);
	coin_.setX(540);
	coin_.setY(7);
	coin_.setScale(.6);
	coin_.draw();
	equal_.print("X", 570, 6);
	
	for (const auto& i : arena.getObjects())
	{
		if (i->isEnabled() && (i->getx() + i->getWidth() - arena.getCenterx() > 0 || i->getx() - arena.getCenterx() < GAME_WIDTH))
		{
			switch (i->getType())
			{
			case BULLET:
				bullet_.setX(i->getx() - arena.getCenterx());
				bullet_.setY(i->gety());
				bullet_.draw();
				break;

			case BLOCK:
				block_.setX(i->getx() - arena.getCenterx());
				block_.setY(i->gety());
				block_.draw();
				break;
			case BRICK:
			case BRICK_DYING:
				brick_.setX(i->getx() - arena.getCenterx());
				brick_.setY(i->gety());
				brick_.draw();
				break;
			case FLOWER:
				flower_.setX(i->getx() - arena.getCenterx());
				flower_.setY(i->gety());
				flower_.draw();
				break;
			case QUESTION:
				question_.setX(i->getx() - arena.getCenterx());
				question_.setY(i->gety());
				if (!paused_)
					question_.update(frameTime_);
				question_.draw();
				break;
			case QUESTION_BLOCK:
				questionBlock_.setX(i->getx() - arena.getCenterx());
				questionBlock_.setY(i->gety());
				questionBlock_.draw();
				break;
			case FLOOR:
				int x;
				if (i->getx() - arena.getCenterx() < 0)
					x = i->getx() + FLOOR_WIDTH * ((int)(arena.getCenterx() - i->getx()) / FLOOR_WIDTH);
				else
					x = i->getx();
				while ((x + FLOOR_WIDTH < i->getx() + i->getWidth()) && (x + FLOOR_WIDTH - arena.getCenterx() < GAME_WIDTH))
				{
					floor_.setX(x - arena.getCenterx());
					floor_.setY(i->gety());
					floor_.draw();
					x += FLOOR_WIDTH;
				}
				floor_.setX(x - arena.getCenterx());
				floor_.setY(i->gety());
				floor_.initialize(graphics_, i->getx() + i->getWidth() - x, FLOOR_HEIGHT, 1, &floorTexture_); // need floor_.setWidth() function
				floor_.draw();
				floor_.initialize(graphics_, FLOOR_WIDTH, FLOOR_HEIGHT, 1, &floorTexture_);
				break;
			case POWERUP:
				powerup_.setX(i->getx() - arena.getCenterx());
				powerup_.setY(i->gety());
				powerup_.draw();
				break;
			case MARIO_SMALL:
			case MARIO_DYING:
				if (arena.getMarioInvisible() || marioPrev == 1)
				{
					transparancy_ = 100;
					marioDowngrade();
					marioPrev = 0;
				}
				else
				{
					transparancy_ = 255;
				}
				mario_.setX(i->getx() - arena.getCenterx());
				mario_.setY(i->gety());
				if (!paused_)
					mario_.update(frameTime_);
				mario_.draw(D3DCOLOR_ARGB(transparancy_, 255, 255, 255));
				break;
			case MARIO_BIG:
				if (arena.getMarioInvisible() || marioPrev == 0)
				{
					transparancy_ = 100;
					marioUpgrade();
					marioPrev = 1;
				}
				else
				{
					transparancy_ = 255;
				}
				mario_.setX(i->getx() - arena.getCenterx());
				mario_.setY(i->gety());
				if (!paused_)
					mario_.update(frameTime_);
				mario_.draw(D3DCOLOR_ARGB(transparancy_, 255, 255, 255));
				break;
			case MARIO_SUPER:
				mario_.setX(i->getx() - arena.getCenterx());
				mario_.setY(i->gety());
				if (!paused_)
					mario_.update(frameTime_);
				mario_.draw();
				break;

			case MUSHROOM:
			case MUSHROOM_DYING:
				mushroom_.setX(i->getx() - arena.getCenterx());
				mushroom_.setY(i->gety());
				mushroom_.draw();
				break;

			case PIPE_BIG:
				pipeBig_.setX(i->getx() - arena.getCenterx());
				pipeBig_.setY(i->gety());
				pipeBig_.draw();
				break;

			case PIPE_MIDDLE:
				pipeMiddle_.setX(i->getx() - arena.getCenterx());
				pipeMiddle_.setY(i->gety());
				pipeMiddle_.draw();
				break;

			case PIPE_SMALL:
				pipeSmall_.setX(i->getx() - arena.getCenterx());
				pipeSmall_.setY(i->gety());
				pipeSmall_.draw();
				break;

			case COIN:
				coin_.setScale(1);
				coin_.setX(i->getx() - arena.getCenterx());
				coin_.setY(i->gety());
				coin_.draw();
				break;

			case FLAG_POLE:
				flagPole_.setX(i->getx() - arena.getCenterx());
				flagPole_.setY(i->gety());
				flagPole_.draw();
				break;

			case FLAG:
				flag_.setX(i->getx() - arena.getCenterx());
				flag_.setY(i->gety());
				flag_.draw();
				break;

			case GOOMBA:
				if (i->getvx() >= 0)
				{
					goomba_.flipHorizontal(true);
				}
				else
				{
					goomba_.flipHorizontal(false);
				}
				if (!paused_)
					goomba_.update(frameTime_);
				goomba_.setX(i->getx() - arena.getCenterx());
				goomba_.setY(i->gety());
				goomba_.draw();
				break;

			case GOOMBA_DYING:
				goombaDying_.setFrameDelay(.3);
				if (!paused_)
					goombaDying_.update(frameTime_);
				goombaDying_.setX(i->getx() - arena.getCenterx());
				goombaDying_.setY(i->gety());
				goombaDying_.draw();
				break;
			case TURTLE:
				if (i->getvx() >= 0)
				{
					turtle_.flipHorizontal(true);
				}
				else
				{
					turtle_.flipHorizontal(false);
				}
				if (!paused_)
					turtle_.update(frameTime_);
				turtle_.setX(i->getx() - arena.getCenterx());
				turtle_.setY(i->gety());
				turtle_.draw();
				break;

			case TURTLE_SPIN:
				turtleSpin_.setX(i->getx() - arena.getCenterx());
				turtleSpin_.setY(i->gety());
				turtleSpin_.draw();
			}
		}
	}

	score_.set(arena.getScore());
	score_.draw();

	coinsCollected_.set(arena.getCoin());
	coinsCollected_.draw();

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
			mario_.setFrames(MARIO_START_FRAME, MARIO_START_FRAME);
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
	bool done = false;
	for (auto& i = arena.getObjects().begin(); i != arena.getObjects().end() && !done; ++i)
	{
		switch ((*i)->getType())
		{
		case MARIO_SUPER:
			mario_.setHeight(MARIO_SUPER_HEIGHT);
			mario_.setCols(MARIO_SUPER_COLS);
			mario_.setFrames(MARIO_SUPER_START_FRAME + 6, MARIO_SUPER_START_FRAME + 6);
			mario_.setCurrentFrame(MARIO_SUPER_START_FRAME + 6);
			done = true;
			break;
		case MARIO_BIG:
			mario_.setHeight(MARIO_BIG_HEIGHT);
			mario_.setCols(MARIO_COLS);
			mario_.setFrames(MARIO_START_FRAME + 6, MARIO_START_FRAME + 6);
			mario_.setCurrentFrame(MARIO_START_FRAME + 6);
			done = true;
			break;
		}
	}
}

void MarioGame::marioUpgrade()
{
	mario_.setHeight(MARIO_BIG_HEIGHT);
	mario_.setCols(MARIO_COLS);
	mario_.setFrames(MARIO_END_FRAME, MARIO_START_FRAME);
}

void MarioGame::marioDowngrade()
{	
	mario_.setHeight(MARIO_SMALL_HEIGHT);
	mario_.setCols(MARIO_SMALL_COLS);
	
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
	currentLevel_ = "World 1 - 1";

	Object* obj = nullptr;
	arena.addObject(new ObjectMario(50, 620 - MARIO_SMALL_HEIGHT, (int)MARIO_SPEED, 0));
	arena.addObject(new ObjectFloor(0, 620, 3411));
	arena.addObject(new ObjectQuestion(791, 422, POWERUP));
	arena.addObject(new ObjectBrick(989, 422));

	arena.addObject(new ObjectQuestion(989 + BRICK_WIDTH, 422, COIN));
	arena.addObject(new ObjectBrick(989 + BRICK_WIDTH + QUESTION_WIDTH, 422));
	arena.addObject(new ObjectQuestion(989 + 2 * BRICK_WIDTH + QUESTION_WIDTH, 422, COIN));
	arena.addObject(new ObjectBrick(989 + 2 * BRICK_WIDTH + 2 * QUESTION_WIDTH, 422));

	arena.addObject(new ObjectGoomba(1040, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectQuestion(1087, 224, COIN));


	arena.addObject(new ObjectPipe(1384, 620 - PIPE_SMALL_HEIGHT, PIPE_SMALL));
	arena.addObject(new ObjectGoomba(1500, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectPipe(1878, 620 - PIPE_MIDDLE_HEIGHT, PIPE_MIDDLE));
	arena.addObject(new ObjectGoomba(2000, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectPipe(2274, 620 - PIPE_BIG_HEIGHT, PIPE_BIG));
	arena.addObject(new ObjectGoomba(2400, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectGoomba(2600, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectPipe(2819, 620 - PIPE_BIG_HEIGHT, PIPE_BIG));

	arena.addObject(new ObjectQuestion(3164, 372, COIN));
	arena.addObject(new ObjectFloor(3511, 620, 4252));
	arena.addObject(new ObjectBrick(3807, 422));
	arena.addObject(new ObjectQuestion(3807 + BRICK_WIDTH, 422, FLOWER));
	arena.addObject(new ObjectBrick(3807 + BRICK_WIDTH + QUESTION_WIDTH, 422));

	arena.addObject(new ObjectBrick(3956, 224));
	arena.addObject(new ObjectBrick(3956 + BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(3956 + 2 * BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(3956 + 3 * BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(3956 + 4 * BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(3956 + 5 * BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(3956 + 6 * BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(3956 + 7 * BRICK_WIDTH, 224));

	arena.addObject(new ObjectGoomba(4100, 224 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectGoomba(4200, 224 - GOOMBA_HEIGHT, -100, 0));

	arena.addObject(new ObjectBrick(4499, 224));
	arena.addObject(new ObjectBrick(4499 + BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(4499 + 2 * BRICK_WIDTH, 224));
	arena.addObject(new ObjectQuestion(4499 + 3 * BRICK_WIDTH, 224, COIN));

	arena.addObject(new ObjectQuestion(4647, 422, COIN));
	arena.addObject(new ObjectFloor(4401, 620, 2394 + 5170));

	arena.addObject(new ObjectGoomba(4700, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectGoomba(4750, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectTurtle(5000, 620 - TURTLE_HEIGHT, -100, 0));

	arena.addObject(new ObjectBrick(4944, 422));
	arena.addObject(new ObjectQuestion(4944+BRICK_WIDTH, 422, COIN));

	arena.addObject(new ObjectGoomba(5170 + 350, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectGoomba(5170 + 400, 620 - GOOMBA_HEIGHT, -100, 0));

	arena.addObject(new ObjectQuestion(71 + 5170, 422, COIN));
	arena.addObject(new ObjectQuestion(219 + 5170, 422, COIN));
	arena.addObject(new ObjectQuestion(219 + 5170, 224, POWERUP));
	arena.addObject(new ObjectQuestion(368 + 5170, 422, COIN));


	arena.addObject(new ObjectBrick(664 + 5170, 422));
	arena.addObject(new ObjectGoomba(800 + 5170, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectGoomba(900 + 5170, 620 - GOOMBA_HEIGHT, -100, 0));

	arena.addObject(new ObjectBrick(813 + 5170, 224));
	arena.addObject(new ObjectBrick(813 + 5170 + BRICK_WIDTH, 224));
	arena.addObject(new ObjectBrick(813 + 5170 + 2 * BRICK_WIDTH, 224));

	arena.addObject(new ObjectBrick(1159 + 5170, 224));
	arena.addObject(new ObjectQuestion(1159 + 5170 + BRICK_WIDTH, 224, COIN));
	arena.addObject(new ObjectQuestion(1159 + 5170 + BRICK_WIDTH + QUESTION_WIDTH, 224, COIN));
	arena.addObject(new ObjectBrick(1159 + 5170 + BRICK_WIDTH + 2 * QUESTION_WIDTH, 224));
	arena.addObject(new ObjectGoomba(1000 + 5170, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectGoomba(1100 + 5170, 620 - GOOMBA_HEIGHT, -100, 0));
	arena.addObject(new ObjectBrick(1208 + 5170, 422));
	arena.addObject(new ObjectBrick(1208 + 5170 + BRICK_WIDTH, 422));


	arena.addObject(new ObjectFloor(2494 + 5170, 620, 5169 + 5170));

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 1; j <= i + 1; ++j)
		{
			arena.addObject(new ObjectBlock(5170 + 1456 + i*BLOCK_WIDTH, 622 - j*BLOCK_HEIGHT));
		}
	}
	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 1; j <= 4 - i; ++j)
		{
			arena.addObject(new ObjectBlock(5170 + 1752 + i*BLOCK_WIDTH, 622 - j*BLOCK_HEIGHT));
		}
	}
	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 1; j <= i + 1; ++j)
		{
			arena.addObject(new ObjectBlock(5170 + 2148 + i*BLOCK_WIDTH, 622 - j*BLOCK_HEIGHT));
		}
	}

	for (int i = 1; i <= 4; ++i)
		arena.addObject(new ObjectBlock(5170 + 2346, 622 - i*BLOCK_HEIGHT));

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 1; j <= 4 - i; ++j)
		{
			arena.addObject(new ObjectBlock(5170 + 2494 + i*BLOCK_WIDTH, 622 - j*BLOCK_HEIGHT));
		}
	}

	arena.addObject(new ObjectPipe(2889 + 5170, 622 - PIPE_SMALL_HEIGHT, PIPE_SMALL));

	arena.addObject(new ObjectBrick(3137 + 5170, 422));
	arena.addObject(new ObjectBrick(3137 + 5170 + BRICK_WIDTH, 422));
	arena.addObject(new ObjectQuestion(3137 + 5170 + 2 * BRICK_WIDTH, 422, COIN));
	arena.addObject(new ObjectBrick(3137 + 5170 + 2 * BRICK_WIDTH + QUESTION_WIDTH, 422));

	arena.addObject(new ObjectGoomba(3200 + 5170, 620 - GOOMBA_HEIGHT, -100, 0));

	arena.addObject(new ObjectPipe(3680 + 5170, 622 - PIPE_SMALL_HEIGHT, PIPE_SMALL));

	for (int i = 0; i <= 7; ++i)
	{
		for (int j = 1; j <= i + 1; ++j)
		{
			arena.addObject(new ObjectBlock(5170 + 3779 + i*BLOCK_WIDTH, 622 - j*BLOCK_HEIGHT));
		}
	}

	for (int i = 1; i <= 8; ++i)
		arena.addObject(new ObjectBlock(5170 + 4175, 622 - i*BLOCK_HEIGHT));

	arena.addObject(new ObjectBlock(4620 + 5170, 622 - BLOCK_HEIGHT));
	arena.addObject(new ObjectFlagPole(4632 + 5170, 101));

	arena.addObject(new ObjectVictorySpot(4930 + 5170, 622 - VICTORY_SPOT_HEIGHT));

}
