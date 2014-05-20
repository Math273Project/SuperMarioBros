#include "ObjectTurtle.h"
#include "Arena.h"

ObjectTurtle::ObjectTurtle(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = TURTLE_WIDTH;
	height_ = TURTLE_HEIGHT;
	spin_ = false;
}

void ObjectTurtle::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BULLET:
		destroy(true);
		break;
	case BLOCK:
	case QUESTION_BLOCK:
	case BRICK:
	case FLOOR:
	case PIPE_BIG:
	case PIPE_MIDDLE:
	case PIPE_SMALL:
	case MUSHROOM_DYING:
	case ENEMY_DYING:
	case TURTLE_SPIN:
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
				const MovingObject* obj = dynamic_cast<const MovingObject*>(&object);
				if (obj->getvy() - getvy() > 20) // change it later
					destroy(TURTLE_DYING_DURATION);
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
	setvx(-4); // change the number later
	y_ += TURTLE_HEIGHT - TURTLE_SPIN_HEIGHT;
}