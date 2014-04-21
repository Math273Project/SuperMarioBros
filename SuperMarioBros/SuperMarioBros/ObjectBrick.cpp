#include "ObjectBrick.h"
#include "Arena.h"

ObjectBrick::ObjectBrick(int id, int x, int y) : Object(id, x, y)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
	//initializeSprite(0, 0);
}

void ObjectBrick::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
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
}

ObjectType ObjectBrick::getType() const
{
	return BRICK;
}

int ObjectBrick::getPriority() const
{
	return PRIORITY; // change it later;
}

void ObjectBrick::destroy()
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	arena.getDyingObjectData().emplace_back(this, time.QuadPart, DYING_DURATION);
}

int ObjectBrick::getDyingDuration() const
{
	return DYING_DURATION;
}
