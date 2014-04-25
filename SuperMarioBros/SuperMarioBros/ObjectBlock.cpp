#include "ObjectBlock.h"
#include "Arena.h"

ObjectBlock::ObjectBlock(int id, int x, int y) : Object(id, x, y) 
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
}

void ObjectBlock::collide(const Object& object, Direction collideDirection)
{

}

ObjectType ObjectBlock::getType() const
{
	return BLOCK;
}

int ObjectBlock::getPriority() const
{
	return PRIORITY; // change it later;
}

void ObjectBlock::destroy(bool instantDestroy)
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

int ObjectBlock::getDyingDuration() const
{
	return DYING_DURATION;
}