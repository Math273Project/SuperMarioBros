#include "ObjectBrick.h"

ObjectBrick::ObjectBrick(int x, int y) : Object(x, y)
{
	width_ = BRICK_WIDTH;
	height_ = BRICK_HEIGHT;
}

void ObjectBrick::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;
	switch (object.getType())
	{
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		case UP:
			if (!dying_)
			destroy();
			break;
		}
		break;
	}
}

ObjectType ObjectBrick::getType() const
{
	if (dying_)
		return BRICK_DYING;
	return BRICK;
}

void ObjectBrick::changeType() 
{
	dying_ = true;
	passable_ = true;
	width_ = BRICK_DYING_WIDTH;
	height_ = BRICK_DYING_HEIGHT;
}

int ObjectBrick::getPriority() const
{
	return BRICK_PRIORITY;
}
