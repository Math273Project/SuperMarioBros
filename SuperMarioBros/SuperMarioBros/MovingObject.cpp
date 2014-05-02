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
	if (enabled_)
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


bool MovingObject::moveable() const
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


MovingObject::MovingObject(int id, int x, int y, int vx, int vy) : Object(id, x, y), vx_(vx), vy_(vy)
{

}

Direction MovingObject::didCollide(const Object& object) const // Check if two objects are collide
{

	if (!enabled_ || !object.isEnabled())
		return NONE;
	if (passable_ || object.passable())
		return NONE;
	double left = x_ + width_  - object.getx(), right  = object.getx() + object.getWidth() -  x_;
	double up  = y_ + height_ - object.gety(), down = object.gety() + object.getHeight() - y_;
	if (!(
		((left > 0 && left <= object.getWidth())  || (right > 0 && right <= object.getWidth())   || (left > 0 && right > 0)) && 
		((up   > 0 && up   <= object.getHeight()) || (down  > 0 && down  <= object.getHeight())  || (up   > 0 && down  > 0))
		   ))
		return NONE;
	Direction direction = NONE;
	if (vx_ == 0 && vy_ == 0)
	{
		double minDistance = INT_MAX;
		if (((left > 0 && left <= object.getWidth()) || (left > 0 && right > 0)) && left < minDistance)
		{
			minDistance = left;
			direction = LEFT;
		}
		if (((right > 0 && right <= object.getWidth()) || (left > 0 && right > 0)) && right < minDistance)
		{
			minDistance = right;
			direction = RIGHT;
		}
		if (((up > 0 && up <= object.getHeight()) || (up > 0 && down > 0)) && up < minDistance)
		{
			minDistance = up;
			direction = UP;
		}
		if (((down > 0 && down <= object.getHeight()) || (up > 0 && down > 0)) && down < minDistance)
		{
			minDistance = down;
			direction = DOWN;
		}
	}
	else
	{
		double minTime = INT_MAX;
		if (vx_ > 0 && ((left > 0 && left <= object.getWidth()) || (left > 0 && right > 0)) && left / vx_ < minTime)
		{
			minTime = left / vx_;
			direction = LEFT;
		}
		else if (vx_ < 0 && ((right > 0 && right <= object.getWidth()) || (left > 0 && right > 0)) && right / (-vx_) < minTime)
		{
			minTime = right / (-vx_);
			direction = RIGHT;
		}
		if (vy_ > 0 && ((up > 0 && up <= object.getHeight()) || (up > 0 && down > 0)) && up / vy_ < minTime)
		{
			minTime = up / vy_;
			direction = UP;
		}
		else if (vy_ < 0 && ((down > 0 && down <= object.getHeight()) || (up > 0 && down > 0)) && down / (-vy_) < minTime)
		{
			minTime = down / (-vy_);
			direction = DOWN;
		}	
	}
	return direction;
}


Direction MovingObject::didCollide(const MovingObject& object) const // Check if two objects are collide
{
	double vx = vx_ - object.getvx();
	double vy = vy_ - object.getvy();
	if (!enabled_ || !object.isEnabled())
		return NONE;
	if (passable_ || object.passable())
		return NONE;
	double left = x_ + width_ - object.getx(), right = object.getx() + object.getWidth() - x_;
	double up = y_ + height_ - object.gety(), down = object.gety() + object.getHeight() - y_;
	if (!(
		((left > 0 && left <= object.getWidth()) || (right > 0 && right <= object.getWidth()) || (left > 0 && right > 0)) &&
		((up   > 0 && up <= object.getHeight()) || (down  > 0 && down <= object.getHeight()) || (up   > 0 && down  > 0))
		))
		return NONE;
	Direction direction = NONE;
	if (vx == 0 && vy == 0)
	{
		double minDistance = INT_MAX;
		if (((left > 0 && left <= object.getWidth()) || (left > 0 && right > 0)) && left < minDistance)
		{
			minDistance = left;
			direction = LEFT;
		}
		if (((right > 0 && right <= object.getWidth()) || (left > 0 && right > 0)) && right < minDistance)
		{
			minDistance = right;
			direction = RIGHT;
		}
		if (((up > 0 && up <= object.getHeight()) || (up > 0 && down > 0)) && up < minDistance)
		{
			minDistance = up;
			direction = UP;
		}
		if (((down > 0 && down <= object.getHeight()) || (up > 0 && down > 0)) && down < minDistance)
		{
			minDistance = down;
			direction = DOWN;
		}
	}
	else
	{
		double minTime = INT_MAX;
		if (vx > 0 && ((left > 0 && left <= object.getWidth()) || (left > 0 && right > 0)) && left / vx < minTime)
		{
			minTime = left / vx;
			direction = LEFT;
		}
		else if (vx < 0 && ((right > 0 && right <= object.getWidth()) || (left > 0 && right > 0)) && right / (-vx) < minTime)
		{
			minTime = right / (-vx);
			direction = RIGHT;
		}
		if (vy > 0 && ((up > 0 && up <= object.getHeight()) || (up > 0 && down > 0)) && up / vy < minTime)
		{
			minTime = up / vy;
			direction = UP;
		}
		else if (vy < 0 && ((down > 0 && down <= object.getHeight()) || (up > 0 && down > 0)) && down / (-vy) < minTime)
		{
			minTime = down / (-vy);
			direction = DOWN;
		}
	}
	return direction;
}