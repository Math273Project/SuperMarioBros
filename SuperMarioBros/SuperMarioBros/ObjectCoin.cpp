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

void ObjectCoin::destroy()
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
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
		case DOWN:
			if (!enabled_)
				y_ -= height_;
			break;
		default:
			if (enabled_)
				destroy();
			break;
		}
	}
}

int ObjectCoin::getDyingDuration() const
{
	return DYING_DURATION;
}