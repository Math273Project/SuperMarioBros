#include "ObjectCoin.h"
#include "Arena.h"

ObjectCoin::ObjectCoin(int id, int x, int y) : Object(id, x, y)
{
	width_ = 32;
	height_ = 32;
	enabled_ = false;
	//initializeSprite(0, 0);
}

ObjectType ObjectCoin::getType() const
{
	return BLOCK;
}
int ObjectCoin::getPriority() const
{
	return 5; // change it later;
}

void ObjectCoin::destroy(bool instantDestroy)
{
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

void ObjectCoin::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case SMALL_MARIO:
	case BIG_MARIO:
	case SUPER_MARIO:
		switch (collideDirection)
		{
		default:
			destroy();
		}
	}
}

int ObjectCoin::getDyingDuration() const
{
	return DYING_DURATION;
}