#include "ObjectPowerup.h"
#include "Arena.h"

ObjectPowerup::ObjectPowerup(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = POWERUP_WIDTH;
	height_ = POWERUP_HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectPowerup::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		destroy();
		break;
	}
}

ObjectType ObjectPowerup::getType() const
{
	return POWERUP;
}

int ObjectPowerup::getPriority() const
{
	return POWERUP_PRIORITY; // change it later
}

void ObjectPowerup::destroy(bool instantDestroy)
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, POWERUP_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

int ObjectPowerup::getDyingDuration() const
{
	return POWERUP_DYING_DURATION;
}