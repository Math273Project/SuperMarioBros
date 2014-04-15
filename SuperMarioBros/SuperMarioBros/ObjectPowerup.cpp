#include "ObjectPowerup.h"

ObjectPowerup::ObjectPowerup(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = 32;
	height_ = 32;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectPowerup::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case BLOCK:
			switch (collideDirection)
			{
			case LEFT:
			case RIGHT:
				setvx(-vx_);
				break;
			}
			break;

		case SMALLMARIO:
		case BIGMARIO:
		case SUPERMARIO:
			destroy();
			break;
		}
	}
}

ObjectType ObjectPowerup::getType() const
{
	return POWERUP;
}

int ObjectPowerup::getPriority() const
{
	return 5; // change it later
}

void ObjectPowerup::destroy()
{
	// change width, height, sprite, 
	deleted_ = true;
}
