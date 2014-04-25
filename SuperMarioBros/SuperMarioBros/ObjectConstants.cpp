#include "ObjectBlock.h"
#include "ObjectBrick.h"
#include "ObjectBullet.h"
#include "ObjectCoin.h"
#include "ObjectBlock.h"
#include "ObjectBrick.h"
#include "ObjectCoin.h"
#include "ObjectEnemy.h"
#include "ObjectMario.h"
#include "ObjectMario.h"
#include "ObjectMushroom.h"
#include "ObjectPipe.h"
#include "ObjectPowerup.h"
#include "ObjectQuestion.h"
#include "ObjectTurtle.h"

const int ObjectBlock::DYING_DURATION = 500;
const int ObjectBlock::PRIORITY = 5;
const int ObjectBlock::WIDTH = 32;
const int ObjectBlock::HEIGHT = 32;

const int ObjectBrick::DYING_DURATION = 500;
const int ObjectBrick::PRIORITY = 5;
const int ObjectBrick::WIDTH = 32;
const int ObjectBrick::HEIGHT = 32;
const int ObjectBrick::BRICK_PIECE_WIDTH = 32;
const int ObjectBrick::BRICK_PIECE_HEIGHT = 32;

const int ObjectBullet::DYING_DURATION = 32;
const int ObjectBullet::PRIORITY = 32;
const int ObjectBullet::WIDTH = 32;
const int ObjectBullet::HEIGHT = 32;

const int ObjectCoin::DYING_DURATION = 500;
const int ObjectCoin::PRIORITY = 5;
const int ObjectCoin::WIDTH = 32;
const int ObjectCoin::HEIGHT = 32;

const int ObjectEnemy::DYING_DURATION = 500;
const int ObjectEnemy::PRIORITY = 5;
const int ObjectEnemy::WIDTH = 32;
const int ObjectEnemy::HEIGHT = 32;
const int ObjectEnemy::FLAT_ENEMY_WIDTH = 32;
const int ObjectEnemy::FLAT_ENEMY_HEIGHT = 32;

const int ObjectMario::DYING_DURATION = 500;
const int ObjectMario::PRIORITY = INT_MAX;
const int ObjectMario::SMALL_MARIO_WIDTH = 32;
const int ObjectMario::SMALL_MARIO_HEIGHT = 32;
const int ObjectMario::BIG_MARIO_WIDTH = 32;
const int ObjectMario::BIG_MARIO_HEIGHT = 32;
const int ObjectMario::SUPER_MARIO_WIDTH = 32;
const int ObjectMario::SUPER_MARIO_HEIGHT = 32;

const int ObjectMushroom::DYING_DURATION = 500;
const int ObjectMushroom::PRIORITY = 5;
const int ObjectMushroom::WIDTH = 32;
const int ObjectMushroom::HEIGHT = 32;
const int ObjectMushroom::FLAT_MUSHROOM_WIDTH = 32;
const int ObjectMushroom::FLAT_MUSHROOM_HEIGHT = 32;

const int ObjectPipe::DYING_DURATION = 500;
const int ObjectPipe::PRIORITY = 5;
const int ObjectPipe::WIDTH = 32;
const int ObjectPipe::HEIGHT = 32;

const int ObjectPowerup::DYING_DURATION = 500;
const int ObjectPowerup::PRIORITY = 5;
const int ObjectPowerup::WIDTH = 32;
const int ObjectPowerup::HEIGHT = 32;

const int ObjectQuestion::DYING_DURATION = 500;
const int ObjectQuestion::PRIORITY = 5;
const int ObjectQuestion::WIDTH = 32;
const int ObjectQuestion::HEIGHT = 32;

const int ObjectTurtle::DYING_DURATION = 500;
const int ObjectTurtle::PRIORITY = 5;
const int ObjectTurtle::WIDTH = 32;
const int ObjectTurtle::HEIGHT = 32;
const int ObjectTurtle::SPIN_TURTLE_WIDTH = 32;
const int ObjectTurtle::SPIN_TURTLE_HEIGHT = 32;