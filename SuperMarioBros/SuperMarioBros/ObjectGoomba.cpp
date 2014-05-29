#include "ObjectGoomba.h"
#include "Arena.h"

ObjectGoomba::ObjectGoomba(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = GOOMBA_WIDTH;
	height_ = GOOMBA_HEIGHT;
	Arena& arena = Arena::getUniqueInstance();
	arena.addEvent(START_MOVING_X_CENTERX, this, x - GAME_WIDTH, vx);
	vx_ = 0;
	gravityAffected_ = false;
	vy_ = 0;
}

void ObjectGoomba::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;
	switch (object.getType())
	{
	case BULLET:
		destroy();
		break;
	case BLOCK:
	case QUESTION_BLOCK:
	case FLOOR:
	case BRICK:
	case PIPE_BIG:
	case PIPE_MIDDLE:
	case PIPE_SMALL:
	case MUSHROOM_DYING:
	case GOOMBA:
	case TURTLE:
	case GOOMBA_DYING:
		adjustPosition(object, collideDirection);
		switch (collideDirection)
		{
		case UP:
			setvy(0);
			break;
		case DOWN:
			setvy(0);
			break;
		case LEFT:
			setvx(-vx_);
			break;
		case RIGHT:
			setvx(-vx_);
			break;
		}
		break;
		
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		if (dynamic_cast<const ObjectMario*>(&object)->getInvisible())
			break;
		switch (collideDirection)
		{
		case DOWN:
			if (!dying_)
			{
				changeType();
				destroy(GOOMBA_DYING_DURATION);
			}
			break;
		}
		break;
	
	case TURTLE_SPIN:
		destroy();
		break;
	}
	
}

ObjectType ObjectGoomba::getType() const
{
	if (dying_)
		return GOOMBA_DYING;
	return GOOMBA;
}

int ObjectGoomba::getPriority() const
{
	return GOOMBA_PRIORITY;
}

void ObjectGoomba::changeType()
{
	dying_ = true;
	width_ = GOOMBA_DYING_WIDTH;
	height_ = GOOMBA_DYING_HEIGHT;
	vx_ = 0;
	y_ += GOOMBA_HEIGHT - GOOMBA_DYING_HEIGHT;
}

int ObjectGoomba::getScore() const 
{
	return GOOMBA_SCORE;
}