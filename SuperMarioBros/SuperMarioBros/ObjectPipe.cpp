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
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case SMALL_MARIO:
			switch (collideDirection)
			{
			case UP:
				break;
			}
			break;
		}
	}
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