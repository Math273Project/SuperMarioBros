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

	case SMALL_MARIO:
	case BIG_MARIO:
	case SUPER_MARIO:
		switch (collideDirection)
		{
		case DOWN:
			destroy();
			break;
		case UP:
		case LEFT:
		case RIGHT:
			break;
		}
		break;
	}
}

ObjectType ObjectEnemy::getType() const
{
	if (dying_)
		return FLAT_ENEMY;
	return ENEMY;
}

int ObjectEnemy::getPriority() const
{
	return PRIORITY; // change it later
}

void ObjectEnemy::changeType()
{
	dying_ = true;
	width_ = FLAT_ENEMY_WIDTH;
	height_ = FLAT_ENEMY_HEIGHT;
}

void ObjectEnemy::destroy() 
{
	changeType();
	setvx(0);
	setvy(0);
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
