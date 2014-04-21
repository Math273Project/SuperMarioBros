#include "ObjectEnemy.h"
#include "Arena.h"

ObjectEnemy::ObjectEnemy(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = WIDTH;
	height_ = HEIGHT;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectEnemy::collide(const Object& object, Direction collideDirection)
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
				destroy();
				break;
			}
			break;
		}
	}
}

ObjectType ObjectEnemy::getType() const
{
	return ENEMY;
}

int ObjectEnemy::getPriority() const
{
	return 5; // change it later
}

void ObjectEnemy::destroy() 
{
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
}

int ObjectEnemy::getDyingDuration() const
{
	return DYING_DURATION;
}
