#include "ObjectMushroom.h"
#include "Arena.h"

ObjectMushroom::ObjectMushroom(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = MUSHROOM_WIDTH;
	height_ = MUSHROOM_HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
	dying_ = false;
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

	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		case DOWN:
			if (!dying_)
				destroy();
			break;
		}
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

void ObjectMushroom::destroy(bool instantDestroy)
{
	setvx(0);
	setvy(0);
	changeType();
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, MUSHROOM_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

void ObjectMushroom::changeType() // change mushroom to flat mushroom, change sprite
{
	dying_ = true;
	width_ = MUSHROOM_DYING_WIDTH;
	height_ = MUSHROOM_DYING_HEIGHT;
}

int ObjectMushroom::getDyingDuration() const
{
	return MUSHROOM_DYING_DURATION;
}