#include "ObjectEnemy.h"

ObjectEnemy::ObjectEnemy(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy)
{
	width_ = 32;
	height_ = 32;
	enabled_ = true;
	facingDirection_ = RIGHT;
}

void ObjectEnemy::collide(const Object& object, Direction collideDirection)
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
			switch (collideDirection)
			{
			case DOWN:
				destroy();
				break;
			}
			break;
		}
	}
}

ObjectType ObjectEnemy::getType() const
{
	return ENEMY;
}

int ObjectEnemy::getPriority() const
{
	return 5; // change it later
}

void ObjectEnemy::destroy() 
{
	// change width, height, sprite, 
	deleted_ = true;
}
