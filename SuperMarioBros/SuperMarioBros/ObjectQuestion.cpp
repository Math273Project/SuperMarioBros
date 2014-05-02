#include "ObjectQuestion.h"
#include "Arena.h"

ObjectQuestion::ObjectQuestion(int id, int x, int y, Object* linkedObject) : Object(id, x, y)
{
	width_ = QUESTION_WIDTH;
	height_ = QUESTION_HEIGHT;
	enabled_ = true;
	linkedObject_ = linkedObject;
}

void ObjectQuestion::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE) //  need more working
		return;

	switch (object.getType())
	{
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		case UP:
			if (!changed_)
			{
				changed_ = true;
				linkedObject_->enable();
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
	return QUESTION_PRIORITY; // change it later
}

void ObjectQuestion::destroy(bool instantDestroy)
{
	// change width, height, sprite,
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, QUESTION_DYING_DURATION);
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
	return QUESTION_DYING_DURATION;
}