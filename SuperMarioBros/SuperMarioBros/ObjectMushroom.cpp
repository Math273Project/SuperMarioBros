#include "ObjectMushroom.h"
#include "Arena.h"

ObjectMushroom::ObjectMushroom(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = MUSHROOM_WIDTH;
	height_ = MUSHROOM_HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectMushroom::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case BLOCK:
			switch (collideDirection)
			{
			case LEFT:
			case RIGHT:
				setvx(-vx_);
				break;
			}
			break;

		case SMALL_MARIO:
		case BIG_MARIO:
		case SUPER_MARIO:
			switch (collideDirection)
			{
			case DOWN:
				changeType();
				break;
			}
			break;
		}
	}
}

ObjectType ObjectMushroom::getType() const
{
	if (changed_)
		return FLAT_MUSHROOM;
	return MUSHROOM;
}

int ObjectMushroom::getPriority() const
{
	return PRIORITY; // change it later
}

void ObjectMushroom::destroy()
{
	changeType();
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
}

void ObjectMushroom::changeType() // change mushroom to flat mushroom, change sprite
{
	changed_ = true;
	width_ = FLAT_MUSHROOM_WIDTH;
	height_ = FLAT_MUSHROOM_HEIGHT;
}

int ObjectMushroom::getDyingDuration() const
{
	return DYING_DURATION;
}