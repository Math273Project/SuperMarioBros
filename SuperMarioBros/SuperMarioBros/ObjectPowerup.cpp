#include "ObjectPowerup.h"
#include "Arena.h"

ObjectPowerup::ObjectPowerup(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectPowerup::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case BLOCK:
			switch (collideDirection)
			{
			case LEFT:
			case RIGHT:
				setvx(-vx_);
				break;
			}
			break;

		case SMALL_MARIO:
		case BIG_MARIO:
		case SUPER_MARIO:
			destroy();
			break;
		}
	}
}

ObjectType ObjectPowerup::getType() const
{
	return POWERUP;
}

int ObjectPowerup::getPriority() const
{
	return PRIORITY; // change it later
}

void ObjectPowerup::destroy()
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
}

int ObjectPowerup::getDyingDuration() const
{
	return DYING_DURATION;
}