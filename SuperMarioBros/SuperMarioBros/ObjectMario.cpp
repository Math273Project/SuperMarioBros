#include "ObjectMario.h"
#include "Arena.h"

ObjectMario::ObjectMario(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy) // id 0, highest priority, moveable
{
	width_ = SMALL_MARIO_HEIGHT;
	height_ = SMALL_MARIO_WIDTH;
	enabled_ = true;
	facingDirection_ = RIGHT;
	type_ = SMALL_MARIO;
	//initializeSprite(0, 0);

	// need sprite
}

void ObjectMario::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BLOCK:
	case PIPE:
	case BRICK:
	case QUESTION:
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
			setvx(0);
			break;
		case RIGHT:
			setvx(0);
			break;
		}
		break;
		
	case ENEMY:
	case MUSHROOM:
		adjustPosition(object, collideDirection);
		switch (collideDirection)
		{
		case LEFT:
		case RIGHT:
		case DOWN:
			destroy();
			break;
		case UP:
			setvy(0);
			break;
		}
	case POWERUP:
		switch (type_)
		{
		case SMALL_MARIO:
			setType(BIG_MARIO);
			break;
		case BIG_MARIO:
			setType(SUPER_MARIO);
			break;
		}
	}
}

ObjectType ObjectMario::getType() const
{
	return type_;
}


int ObjectMario::getPriority() const
{
	return PRIORITY;
}

void ObjectMario::destroy()
{
	// need add more
	setvy(-100); //
	facingDirection_ = UP;
	passable_ = true;
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	DyingObjectData data(this, time.QuadPart, DYING_DURATION);
	arena.pushDyingObjectData(data);
}

void ObjectMario::setType(ObjectType type)
{
	switch (type)
	{
	case SMALL_MARIO:
		type_ = SMALL_MARIO;
		width_ = SMALL_MARIO_WIDTH; // need data
		height_ = SMALL_MARIO_HEIGHT;
		break;
	case BIG_MARIO:
		type_ = BIG_MARIO;
		width_ = BIG_MARIO_WIDTH;
		height_ = BIG_MARIO_HEIGHT;
		break;
	case SUPER_MARIO:
		type_ = SUPER_MARIO;
		width_ = SUPER_MARIO_WIDTH;
		height_ = SUPER_MARIO_HEIGHT;
		break;
	}
}

int ObjectMario::getDyingDuration() const
{
	return DYING_DURATION;
}