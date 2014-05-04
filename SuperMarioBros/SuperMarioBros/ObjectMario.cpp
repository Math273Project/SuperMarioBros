#include "ObjectMario.h"

ObjectMario::ObjectMario(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = MARIO_SMALL_WIDTH;
	height_ = MARIO_SMALL_HEIGHT;
	type_ = MARIO_SMALL;
}

void ObjectMario::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BLOCK:
	case FLOOR:
	case PIPE:
	case BRICK:
	case QUESTION:
	case MUSHROOM_DYING:
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
			setvx(0);
			break;
		case RIGHT:
			setvx(0);
			break;
		}
		break;
		
	case ENEMY:
	case MUSHROOM:
		adjustPosition(object, collideDirection);
		switch (collideDirection)
		{
		case LEFT:
		case RIGHT:
		case DOWN:
			setvx(0);
			destroy();
			break;
		case UP:
			setvy(0);
			break;
		}
		break;
	case POWERUP:
		switch (type_)
		{
		case MARIO_SMALL:
			setType(MARIO_BIG);
			break;
		case MARIO_BIG:
			setType(MARIO_SUPER);
			break;
		}
		break;
	}
}

ObjectType ObjectMario::getType() const
{
	return type_;
}


int ObjectMario::getPriority() const
{
	return MARIO_PRIORITY;
}

void ObjectMario::setType(ObjectType type)
{
	switch (type)
	{
	case MARIO_SMALL:
		type_ = MARIO_SMALL;
		width_ = MARIO_SMALL_WIDTH; // need data
		height_ = MARIO_SMALL_HEIGHT;
		break;
	case MARIO_BIG:
		type_ = MARIO_BIG;
		width_ = MARIO_BIG_WIDTH;
		height_ = MARIO_BIG_HEIGHT;
		break;
	case MARIO_SUPER:
		type_ = MARIO_SUPER;
		width_ = MARIO_SUPER_WIDTH;
		height_ = MARIO_SUPER_HEIGHT;
		break;
	}
}

void ObjectMario::destroy()
{
	passable_ = true;
	dying_ = true;
	type_ = MARIO_DYING;
	setvy(-100);
}
