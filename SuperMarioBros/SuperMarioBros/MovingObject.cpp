#include "MovingObject.h"

void MovingObject::setFacingDirection(Direction facingDirection)
{
	facingDirection_ = facingDirection;
}

double MovingObject::getvx() const
{
	return vx_;
}

double MovingObject::getvy() const
{
	return vy_;
}

void MovingObject::setvx(double vx)
{
	if (vx_ * vx < 0)
	{
		if (vx < 0)
			setFacingDirection(LEFT);
		else
			setFacingDirection(RIGHT);
	}
	vx_ = vx;
}

void MovingObject::setvy(double vy)
{
	vy_ = vy;
}

Direction MovingObject::getFacingDirection() const
{
	return facingDirection_;
}


bool MovingObject::moveable() const
{
	return true;
}


void MovingObject::move(int time)
{
	x_ += vx_ * time / 1000;
	y_ += vy_ * time / 1000;
}


MovingObject::MovingObject(int id, int x, int y, int vx, int vy) : Object(id, x, y), vx_(vx), vy_(vy)
{

}