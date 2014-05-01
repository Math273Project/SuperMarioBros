#include "ObjectBlock.h"
#include "Arena.h"

ObjectBlock::ObjectBlock(int id, int x, int y) : Object(id, x, y) 
{
	width_ = BLOCK_WIDTH;
	height_ = BLOCK_HEIGHT;
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
	return BLOCK_PRIORITY; // change it later;
}

void ObjectBlock::destroy(bool instantDestroy)
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, BLOCK_DYING_DURATION);
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
	return BLOCK_DYING_DURATION;
}