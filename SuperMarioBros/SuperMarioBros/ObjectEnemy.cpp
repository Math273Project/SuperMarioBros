#include "ObjectEnemy.h"
#include "Arena.h"

ObjectEnemy::ObjectEnemy(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = ENEMY_WIDTH;
	height_ = ENEMY_HEIGHT;
	dying_ = false;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectEnemy::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;
	
	switch (object.getType())
	{
	case BLOCK:
	case BRICK:
	case PIPE:
		adjustPosition(object, collideDirection);
		switch (collideDirection)
		{
		case UP:
			setvy(0);
			break;
		case DOWN:
			setvy(0);
			break;
		case LEFT:
			setvx(-vx_);
			break;
		case RIGHT:
			setvx(-vx_);
			break;
		}
		break;

	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		case DOWN:
			destroy();
			break;
		}
		break;
	}
}

ObjectType ObjectEnemy::getType() const
{
	if (dying_)
		return ENEMY_DYING;
	return ENEMY;
}

int ObjectEnemy::getPriority() const
{
	return ENEMY_PRIORITY;
}

void ObjectEnemy::changeType()
{
	dying_ = true;
	width_ = ENEMY_DYING_WIDTH;
	height_ = ENEMY_DYING_HEIGHT;
}

void ObjectEnemy::destroy(bool instantDestroy)
{
	changeType();
	setvx(0);
	setvy(0);
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	if (!instantDestroy)
	{
		DyingObjectData data(this, time.QuadPart, ENEMY_DYING_DURATION);
		arena.pushDyingObjectData(data);
	}
	else
	{
		DyingObjectData data(this, time.QuadPart, 0);
		arena.pushDyingObjectData(data);
	}
}

int ObjectEnemy::getDyingDuration() const
{
	return ENEMY_DYING_DURATION;
}
