#include "ObjectBlock.h"
#include "Arena.h"

ObjectBlock::ObjectBlock(int id, int x, int y) : Object(id, x, y) 
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
	//initializeSprite(0, 0);
}

void ObjectBlock::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
}

ObjectType ObjectBlock::getType() const
{
	return BLOCK;
}

int ObjectBlock::getPriority() const
{
	return PRIORITY; // change it later;
}

void ObjectBlock::destroy()
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
}

int ObjectBlock::getDyingDuration() const
{
	return DYING_DURATION;
}