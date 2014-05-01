#include "ObjectBullet.h"
#include "Arena.h"

ObjectBullet::ObjectBullet(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = BULLET_WIDTH;
	height_ = BULLET_HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectBullet::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	default:
		destroy();
		break;
	}
}

ObjectType ObjectBullet::getType() const
{
	return BULLET;
}

int ObjectBullet::getPriority() const
{
	return BULLET_PRIORITY;
}

void ObjectBullet::destroy(bool instantDestroy)
{
	setvx(0);
	setvy(0);
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, BULLET_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

int ObjectBullet::getDyingDuration() const
{
	return BULLET_DYING_DURATION;
}
