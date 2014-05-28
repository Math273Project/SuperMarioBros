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
				destroy(BRICK_DYING_DURATION);
			break;
		}
		break;
	}
}

ObjectType ObjectBrick::getType() const
{
	return BRICK;
}

int ObjectBrick::getPriority() const
{
	return BRICK_PRIORITY;
}
