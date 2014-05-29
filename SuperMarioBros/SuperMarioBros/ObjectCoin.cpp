#include "ObjectCoin.h"

ObjectCoin::ObjectCoin(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = COIN_WIDTH;
	height_ = COIN_HEIGHT;
}

ObjectType ObjectCoin::getType() const
{
	return COIN;
}

int ObjectCoin::getPriority() const
{
	return COIN_PRIORITY;
}

void ObjectCoin::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	destroy();
}

int ObjectCoin::getScore() const
{
	return COIN_SCORE;
}