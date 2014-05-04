#include "ObjectBullet.h"

ObjectBullet::ObjectBullet(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = BULLET_WIDTH;
	height_ = BULLET_HEIGHT;
}

void ObjectBullet::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	default:
		destroy();
		break;
	}
}

ObjectType ObjectBullet::getType() const
{
	return BULLET;
}

int ObjectBullet::getPriority() const
{
	return BULLET_PRIORITY;
}
