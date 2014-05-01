#include "ObjectFloor.h"
#include "Arena.h"

ObjectFloor::ObjectFloor(int id, int x, int y, int width) : Object(id, x, y)
{
	width_ = width;
	height_ = FLOOR_HEIGHT;
	enabled_ = true;
}

void ObjectFloor::collide(const Object& object, Direction collideDirection)
{

}

ObjectType ObjectFloor::getType() const
{
	return FLOOR;
}

int ObjectFloor::getPriority() const
{
	return FLOOR_PRIORITY; // change it later;
}

void ObjectFloor::destroy(bool instantDestroy)
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, FLOOR_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

int ObjectFloor::getDyingDuration() const
{
	return FLOOR_DYING_DURATION;
}