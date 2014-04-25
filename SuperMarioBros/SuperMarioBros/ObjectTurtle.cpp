#include "ObjectTurtle.h"
#include "Arena.h"

ObjectTurtle::ObjectTurtle(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectTurtle::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BULLET:
		destroy(true);
		break;
	case BLOCK:
	case BRICK:
	case PIPE:
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

	case SMALL_MARIO:
	case BIG_MARIO:
	case SUPER_MARIO:
		if (!spining_)
		{
			switch (collideDirection)
			{
			case DOWN:
				changeType();
				break;
			}
		}
		else
		{
			switch (collideDirection)
			{
			case DOWN:
				destroy();
				break;
			}
		}
		break;
	}
}

ObjectType ObjectTurtle::getType() const
{
	if (spining_)
		return SPIN_TURTLE;
	return TURTLE;
}

int ObjectTurtle::getPriority() const
{
	return PRIORITY; // change it later
}

void ObjectTurtle::changeType()
{
	spining_ = true;
	width_ = SPIN_TURTLE_WIDTH;
	height_ = SPIN_TURTLE_HEIGHT;
	setvx(100); // change the number later
}

void ObjectTurtle::destroy(bool instantDestroy)
{
	changeType();
	setvx(0);
	setvy(0);
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

int ObjectTurtle::getDyingDuration() const
{
	return DYING_DURATION;
}
