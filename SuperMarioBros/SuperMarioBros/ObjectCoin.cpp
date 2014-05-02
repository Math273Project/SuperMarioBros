#include "ObjectCoin.h"

ObjectCoin::ObjectCoin(int x, int y) : Object(x, y)
{
	width_ = COIN_WIDTH;
	height_ = COIN_HEIGHT;
}

ObjectType ObjectCoin::getType() const
{
	return BLOCK;
}

int ObjectCoin::getPriority() const
{
	return COIN_PRIORITY;
}

void ObjectCoin::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		default:
			destroy();
		}
	}
}
