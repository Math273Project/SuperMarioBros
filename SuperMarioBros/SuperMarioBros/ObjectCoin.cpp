#include "ObjectCoin.h"
#include "Arena.h"

ObjectCoin::ObjectCoin(int id, int x, int y) : Object(id, x, y)
{
	width_ = COIN_WIDTH;
	height_ = COIN_HEIGHT;
	enabled_ = false;
	//initializeSprite(0, 0);
}

ObjectType ObjectCoin::getType() const
{
	return BLOCK;
}
int ObjectCoin::getPriority() const
{
	return COIN_PRIORITY;
}

void ObjectCoin::destroy(bool instantDestroy)
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, COIN_DYING_DURATION);
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
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		default:
			destroy();
		}
	}
}

int ObjectCoin::getDyingDuration() const
{
	return COIN_DYING_DURATION;
}