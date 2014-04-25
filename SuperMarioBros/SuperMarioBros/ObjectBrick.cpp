#include "ObjectBrick.h"
#include "Arena.h"

ObjectBrick::ObjectBrick(int id, int x, int y) : Object(id, x, y)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
}

void ObjectBrick::collide(const Object& object, Direction collideDirection)
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
		return BRICK_PIECE;
	return BRICK;
}

void ObjectBrick::changeType() 
{
	dying_ = true;
	passable_ = true;
	width_ = BRICK_PIECE_WIDTH;
	height_ = BRICK_PIECE_HEIGHT;
}

int ObjectBrick::getPriority() const
{
	return PRIORITY;
}

void ObjectBrick::destroy(bool instantDestroy)
{
	// working on
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

int ObjectBrick::getDyingDuration() const
{
	return DYING_DURATION;
}
