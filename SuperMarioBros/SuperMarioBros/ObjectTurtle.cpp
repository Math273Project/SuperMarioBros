#include "ObjectTurtle.h"
#include "Arena.h"

ObjectTurtle::ObjectTurtle(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = TURTLE_WIDTH;
	height_ = TURTLE_HEIGHT;
	spin_ = false;
	Arena& arena = Arena::getUniqueInstance();
	arena.addEvent(START_MOVING_X_CENTERX, this, x - GAME_WIDTH, vx);
	vx_ = 0;
	gravityAffected_ = false;
	vy_ = 0;
	spinStartTime_ = 0;
}

void ObjectTurtle::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;
	switch (object.getType())
	{
	case BULLET:
		destroy();
		break;
	case BLOCK:
	case QUESTION_BLOCK:
	case BRICK:
	case FLOOR:
	case PIPE_BIG:
	case PIPE_MIDDLE:
	case PIPE_SMALL:
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
		if (dynamic_cast<const ObjectMario*>(&object)->getInvisible())
			break;
		if (!spin_)
		{
			switch (collideDirection)
			{
			case DOWN:
				changeType();
				break;
			}
		}
		else
		{
			switch (collideDirection)
			{
			case DOWN:
				LARGE_INTEGER endTime, frequency;
				QueryPerformanceCounter(&endTime);
				QueryPerformanceFrequency(&frequency);
				double time = (endTime.QuadPart - spinStartTime_) / (double)frequency.QuadPart;
				if (time > 2.0)
				{
					setvx(0);
					destroy(TURTLE_DYING_DURATION);
				}
				break;
			}
		}
		break;
	}
}

ObjectType ObjectTurtle::getType() const
{
	if (spin_)
		return TURTLE_SPIN;
	return TURTLE;
}

int ObjectTurtle::getPriority() const
{
	return TURTLE_PRIORITY; // change it later
}

void ObjectTurtle::changeType()
{
	spin_ = true;
	width_ = TURTLE_SPIN_WIDTH;
	height_ = TURTLE_SPIN_HEIGHT;
	if (vx_ < 0)
		setvx(-300);
	else
		setvx(300);
	y_ += TURTLE_HEIGHT - TURTLE_SPIN_HEIGHT;
	LARGE_INTEGER tmp;
	QueryPerformanceCounter(&tmp);
	spinStartTime_ = tmp.QuadPart;
}

int ObjectTurtle::getScore() const
{
	return TURTLE_SCORE;
}