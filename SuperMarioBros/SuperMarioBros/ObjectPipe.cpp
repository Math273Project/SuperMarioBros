#include "ObjectPipe.h"
#include "Arena.h"

ObjectPipe::ObjectPipe(int id, int x, int y) : Object(id, x, y)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
}

void ObjectPipe::collide(const Object& object, Direction collideDirection)
{
	
}

ObjectType ObjectPipe::getType() const
{
	return PIPE;
}

int ObjectPipe::getPriority() const
{
	return PRIORITY; // change it later
}

void ObjectPipe::destroy()
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
}

int ObjectPipe::getDyingDuration() const
{
	return DYING_DURATION;
}