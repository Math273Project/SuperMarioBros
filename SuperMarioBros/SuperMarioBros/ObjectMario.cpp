#include "ObjectMario.h"

ObjectMario::ObjectMario(int id, int x, int y, int vx, int vy) : MovingObject(id, x, y, vx, vy) // id 0, highest priority, moveable
{
	width_ = 32;
	height_ = 64;
	enabled_ = true;
	facingDirection_ = RIGHT;
	type_ = SMALLMARIO;
	//initializeSprite(0, 0);

	// need sprite
}

void ObjectMario::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case BLOCK:
			vx_ = vy_ = 0;
			switch (collideDirection)
			{
			case UP:
				y_ = object.gety() - height_;
				break;
			case DOWN:
				y_ = object.gety() + object.getHeight();
				break;
			case LEFT:
				x_ = object.getx() - width_;
				break;
			case RIGHT:
				x_ = object.getx() + object.getWidth();
				break;
			}
			break;
		
		case ENEMY:
			switch (collideDirection)
			{
			case LEFT:
			case RIGHT:
			case DOWN:
				destroy();
				break;
			}
		case POWERUP:
			switch (type_)
			{
			case SMALLMARIO:
				setType(BIGMARIO);
				break;
			case BIGMARIO:
				setType(SUPERMARIO);
				break;
			}
		}
	}
}

ObjectType ObjectMario::getType() const
{
	return type_;
}


int ObjectMario::getPriority() const
{
	return INT_MAX;
}

void ObjectMario::destroy()
{
	// need add more
	vy_ = -100;
	facingDirection_ = UP;
	passable_ = true;
}

void ObjectMario::setType(ObjectType type)
{
	switch (type)
	{
	case SMALLMARIO:
		type_ = SMALLMARIO;
		width_ = 32; // need data
		height_ = 32;
		break;
	case BIGMARIO:
		type_ = BIGMARIO;
		width_ = 32;
		height_ = 32;
		break;
	case SUPERMARIO:
		type_ = SUPERMARIO;
		width_ = 32;
		height_ = 32;
		break;
	}
}