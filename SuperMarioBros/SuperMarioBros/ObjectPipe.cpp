#include "ObjectPipe.h"
#include "Arena.h"

ObjectPipe::ObjectPipe(int id, int x, int y) : Object(id, x, y)
{
	width_ = PIPE_WIDTH;
	height_ = PIPE_HEIGHT;
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
	return PIPE_PRIORITY; // change it later
}

void ObjectPipe::destroy(bool instantDestroy)
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, PIPE_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

int ObjectPipe::getDyingDuration() const
{
	return PIPE_DYING_DURATION;
}