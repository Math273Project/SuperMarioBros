#include "ObjectMushroom.h"
#include "Arena.h"

ObjectMushroom::ObjectMushroom(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = MUSHROOM_WIDTH;
	height_ = MUSHROOM_HEIGHT;
	dying_ = false;
	Arena& arena = Arena::getUniqueInstance();
	arena.addEvent(START_MOVING_X_CENTERX, this, x - GAME_WIDTH, vx);
	vx_ = 0;
	gravityAffected_ = false;
	vy_ = 0;
}

void ObjectMushroom::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BULLET:
		destroy(true);
		break;
	case BLOCK:
	case QUESTION_BLOCK:
	case FLOOR:
	case PIPE_BIG:
	case PIPE_MIDDLE:
	case PIPE_SMALL:
	case BRICK:
	case QUESTION:
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
				destroy(MUSHROOM_DYING_DURATION);
			}
			break;
		}
		break;
	case TURTLE_SPIN:
		destroy();
		break;
	}
}

ObjectType ObjectMushroom::getType() const
{
	if (dying_)
		return MUSHROOM_DYING;
	return MUSHROOM;
}

int ObjectMushroom::getPriority() const
{
	return MUSHROOM_PRIORITY; // change it later
}

void ObjectMushroom::changeType() // change mushroom to flat mushroom, change sprite
{
	dying_ = true;
	width_ = MUSHROOM_DYING_WIDTH;
	height_ = MUSHROOM_DYING_HEIGHT;
	vx_ = 0;
	y_ += MUSHROOM_HEIGHT - MUSHROOM_DYING_HEIGHT;
}
