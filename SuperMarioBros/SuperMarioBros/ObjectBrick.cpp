#include "ObjectBrick.h"
#include "Arena.h"

ObjectBrick::ObjectBrick(int id, int x, int y) : Object(id, x, y)
{
	width_ = BRICK_WIDTH;
	height_ = BRICK_HEIGHT;
	enabled_ = true;
}

void ObjectBrick::collide(const Object& object, Direction collideDirection)
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
		case UP:
			destroy();
			break;
		}
		break;
	}
}

ObjectType ObjectBrick::getType() const
{
	if (dying_)
		return BRICK_DYING;
	return BRICK;
}

void ObjectBrick::changeType() 
{
	dying_ = true;
	passable_ = true;
	width_ = BRICK_DYING_WIDTH;
	height_ = BRICK_DYING_HEIGHT;
}

int ObjectBrick::getPriority() const
{
	return BRICK_PRIORITY;
}

void ObjectBrick::destroy(bool instantDestroy)
{
	// working on
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, BRICK_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

int ObjectBrick::getDyingDuration() const
{
	return BRICK_DYING_DURATION;
}
