#include "ObjectFlower.h"

ObjectFlower::ObjectFlower(int x, int y) : Object(x, y)
{
	width_ = FLOWER_WIDTH;
	height_ = FLOWER_HEIGHT;
}

void ObjectFlower::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
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

ObjectType ObjectFlower::getType() const
{
	return FLOWER;
}

int ObjectFlower::getPriority() const
{
	return FLOWER_PRIORITY;
}

int ObjectFlower::getScore() const
{
	return FLOWER_SCORE;
}