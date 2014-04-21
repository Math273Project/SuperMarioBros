#include "ObjectMario.h"
#include "Arena.h"

ObjectMario::ObjectMario(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy) // id 0, highest priority, moveable
{
	width_ = 32;
	height_ = 64;
	enabled_ = true;
	facingDirection_ = RIGHT;
	type_ = SMALL_MARIO;
	//initializeSprite(0, 0);

	// need sprite
}

void ObjectMario::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case BLOCK:
			vx_ = vy_ = 0;
			switch (collideDirection)
			{
			case UP:
				y_ = object.gety() - height_;
				break;
			case DOWN:
				y_ = object.gety() + object.getHeight();
				break;
			case LEFT:
				x_ = object.getx() - width_;
				break;
			case RIGHT:
				x_ = object.getx() + object.getWidth();
				break;
			}
			break;
		
		case ENEMY:
			switch (collideDirection)
			{
			case LEFT:
			case RIGHT:
			case DOWN:
				destroy();
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
	vy_ = -100;
	facingDirection_ = UP;
	passable_ = true;
	Arena& arena = Arena::getUniqueInstance();
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	arena.getDyingObjectData().emplace_back(this, time.QuadPart, DYING_DURATION);
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