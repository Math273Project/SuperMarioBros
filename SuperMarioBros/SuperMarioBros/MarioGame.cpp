#include "MarioGame.h"
#include "ObjectMario.h"
#include "ObjectBlock.h"

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

	Arena& arena = Arena::getUniqueInstance();
	ObjectMario* objectMario = new ObjectMario(0, 50, 490, (int)MARIO_SPEED, 0);
	ObjectBlock* objectBlock = new ObjectBlock(0, 500, 0);
	arena.pushBack(objectMario);
	arena.pushBack(objectBlock);
	//Initialize textures
	
	marioTexture_.initialize(graphics_, MARIO_TEXTURE);
	backgroundTexture_.initialize(graphics_, BACKGROUND_START); //background will be split in multiple parts
	enemyTexture_.initialize(graphics_, MARIO_TEXTURE);
	blocksTexture_.initialize(graphics_, BLOCKS);


	//Initialize images
	mario_.initialize(graphics_, BIG_MARIO_WIDTH, BIG_MARIO_HEIGHT, MARIO_COLS, &marioTexture_);
	background_.initialize(graphics_, GAME_WIDTH, GAME_HEIGHT, 1, &backgroundTexture_);
	enemy_.initialize(graphics_, SMALL_MARIO_WIDTH, SMALL_MARIO_HEIGHT, SMALL_MARIO_COLS, &enemyTexture_);
	block_.initialize(graphics_, BLOCK_WIDTH, BLOCK_HEIGHT, 1, &blocksTexture_);

	mario_.setX(50);     
	mario_.setY(490); //get rid of magic constant
	mario_.setFrames(MARIO_START_FRAME + 1, MARIO_END_FRAME - 4);   // animation frames
	mario_.setCurrentFrame(MARIO_START_FRAME);     // starting frame
	mario_.setFrameDelay(MARIO_ANIMATION_DELAY);
	mario_.setDegrees(0);

	enemy_.setX(200);
	enemy_.setY(490);
	enemy_.setFrames(SMALL_MARIO_START_FRAME, SMALL_MARIO_END_FRAME);
	enemy_.setCurrentFrame(SMALL_MARIO_START_FRAME);
	enemy_.setFrameDelay(SMALL_MARIO_ANIMATION_DELAY);
	enemy_.setDegrees(0);
	

}

void MarioGame::update()
{
	arena.move(frameTime_*1000);
	arena.collisionDetection();
	if (arena.getMarioX() - centerx_ > GAME_WIDTH / 2)
		centerx_ = arena.getMarioX() - GAME_WIDTH / 2;

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
	for (const auto& i : arena.getMovingObjects())
	{
		switch (i->getType())
		{
		case SMALL_MARIO:
			mario_.setX(i->getx() - centerx_);
			mario_.setY(i->gety());
			mario_.setCurrentFrame(i->getCurrentFrame());
			mario_.update(frameTime_);
			i->setCurrentFrame(mario_.getCurrentFrame());
			mario_.draw();
			break;
		}
	}
	for (const auto& i : arena.getStaticObjects())
	{
		switch (i->getType())
		{
		case BLOCK:
			block_.setX(i->getx() - centerx_);
			block_.setY(i->gety());
			block_.draw();
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
