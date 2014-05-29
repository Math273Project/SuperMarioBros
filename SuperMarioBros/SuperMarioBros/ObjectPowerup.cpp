#include "ObjectPowerup.h"

ObjectPowerup::ObjectPowerup(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = POWERUP_WIDTH;
	height_ = POWERUP_HEIGHT;
}

void ObjectPowerup::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case BULLET:
		destroy();
		break;
	case BLOCK:
	case FLOOR:
	case PIPE_BIG:
	case PIPE_MIDDLE:
	case PIPE_SMALL:
	case BRICK:
	case QUESTION:
	case QUESTION_BLOCK:
	case MUSHROOM_DYING:
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
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		destroy();
		break;
	}
}

ObjectType ObjectPowerup::getType() const
{
	return POWERUP;
}

int ObjectPowerup::getPriority() const
{
	return POWERUP_PRIORITY; // change it later
}


int ObjectPowerup::getScore() const
{
	return POWERUP_SCORE;
}