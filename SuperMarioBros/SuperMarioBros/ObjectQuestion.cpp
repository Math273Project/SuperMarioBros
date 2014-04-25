#include "ObjectQuestion.h"
#include "Arena.h"

ObjectQuestion::ObjectQuestion(int id, int x, int y) : Object(id, x, y)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
}

void ObjectQuestion::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE) //  need more working
		return;

	switch (object.getType())
	{
	case SMALL_MARIO:
	case BIG_MARIO:
	case SUPER_MARIO:
		switch (collideDirection)
		{
		case UP:
			if (changed_)
			{

			}
			break;
		}
		break;
	}
}

ObjectType ObjectQuestion::getType() const
{
	if (changed_)
		return BLOCK;
	return QUESTION;
}

int ObjectQuestion::getPriority() const
{
	return PRIORITY; // change it later
}

void ObjectQuestion::destroy(bool instantDestroy)
{
	// change width, height, sprite,
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

int ObjectQuestion::getDyingDuration() const
{
	return DYING_DURATION;
}