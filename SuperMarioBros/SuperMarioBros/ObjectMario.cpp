#include "ObjectMario.h"
#include "Arena.h"

ObjectMario::ObjectMario(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy) // id 0, highest priority, moveable
{
	width_ = MARIO_SMALL_WIDTH;
	height_ = MARIO_SMALL_HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
	type_ = MARIO_SMALL;
}

void ObjectMario::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BULLET:
		destroy(true);
		break;
	case BLOCK:
	case FLOOR:
	case PIPE:
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
			destroy();
			break;
		case UP:
			setvy(0);
			break;
		}
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

void ObjectMario::destroy(bool instantDestroy)
{
	// need add more
	setvy(-100); // mario jumps and die
	facingDirection_ = UP;
	passable_ = true;
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, MARIO_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
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

int ObjectMario::getDyingDuration() const
{
	return MARIO_DYING_DURATION;
}