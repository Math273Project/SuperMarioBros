#include "ObjectMushroom.h"
#include "Arena.h"

ObjectMushroom::ObjectMushroom(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
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
	case PIPE:
	case BRICK:
	case QUESTION:
		switch (collideDirection)
		{
		case LEFT:
		case RIGHT:
			setvx(-vx_);
			break;
		case UP:
		case DOWN:
			setvy(0);
		}
		break;

	case SMALL_MARIO:
	case BIG_MARIO:
	case SUPER_MARIO:
		switch (collideDirection)
		{
		case DOWN:
			destroy();
			break;
		}
		break;
	}
}

ObjectType ObjectMushroom::getType() const
{
	if (dying_)
		return FLAT_MUSHROOM;
	return MUSHROOM;
}

int ObjectMushroom::getPriority() const
{
	return PRIORITY; // change it later
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
		DyingObjectData data(this, time.QuadPart, DYING_DURATION);
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
	width_ = FLAT_MUSHROOM_WIDTH;
	height_ = FLAT_MUSHROOM_HEIGHT;
}

int ObjectMushroom::getDyingDuration() const
{
	return DYING_DURATION;
}