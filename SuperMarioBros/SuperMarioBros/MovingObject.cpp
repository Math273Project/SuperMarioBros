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


void MovingObject::move(double time)
{
	x_ += vx_ * time / 1000;
	y_ += vy_ * time / 1000;
}


MovingObject::MovingObject(int id, int x, int y, int vx, int vy) : Object(id, x, y), vx_(vx), vy_(vy)
{

}

Direction MovingObject::didCollide(const Object& object) const // Check if two objects are collide
{
	if (!enabled_ || !object.isEnabled())
		return NONE;
	if (passable_ || object.passable())
		return NONE;
	if (vy_ > 0 && object.gety() <= y_ + height_ - 1 && y_ + height_ - 1 <= object.gety() + object.getHeight() - 1)
		return UP;
	if (vy_ < 0 && object.gety() <= y_ && y_ <= object.gety() + object.getHeight() - 1)
		return DOWN;
	if (vx_ > 0 && object.getx() <= x_ + width_ - 1 && x_ + width_ - 1 <= object.getx() + object.getWidth() - 1)
		return LEFT;
	if (vx_ < 0 && object.getx() <= x_ && x_ <= object.getx() + object.getWidth() - 1)
		return RIGHT;
	return NONE;
}
