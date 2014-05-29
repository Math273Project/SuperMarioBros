#include "ObjectBullet.h"

ObjectBullet::ObjectBullet(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = BULLET_WIDTH;
	height_ = BULLET_HEIGHT;
	gravityAffected_ = false;
}

void ObjectBullet::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	if (object.getType() != MARIO_SMALL && object.getType() != MARIO_BIG && object.getType() != MARIO_SUPER)
	{
		destroy();
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
