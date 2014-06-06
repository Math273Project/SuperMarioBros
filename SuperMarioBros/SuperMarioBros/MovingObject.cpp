#include "MovingObject.h"

MovingObject::MovingObject(int x, int y, int vx, int vy) : Object(x, y)
{
	vx_ = vx;
	vy_ = vy;
	facingDirection_ = RIGHT;
	gravityAffected_ = true;
}

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
	if (enabled_)
	{
		if (vx < 0)
			setFacingDirection(LEFT);
		else if (vx > 0)
			setFacingDirection(RIGHT);
		vx_ = vx;
	}
}

void MovingObject::setvy(double vy)
{
	if (enabled_)
		vy_ = vy;
}

Direction MovingObject::getFacingDirection() const
{
	return facingDirection_;
}


bool MovingObject::getMoveable() const
{
	return true;
}


void MovingObject::move(double time)
{
	if (enabled_)
	{
		x_ += vx_ * time / 1000;
		y_ += vy_ * time / 1000;
	}
}

bool MovingObject::getGravityAffected() const
{
	return gravityAffected_;
}

void MovingObject::setGravityAffected(bool gravityAffected)
{
	gravityAffected_ = gravityAffected;
}
