#include "Object.h"
#include "Arena.h"

Object::~Object()
{

}

void Object::setPosition(double x, double y)
{
	x_ = x;
	y_ = y;
}

void Object::collide(const Object& object, Direction collideDirection)
{
	// Should be rewrite if there will be any things to do.
}

bool Object::onTop(const Object& object) const
{
	return y_ + height_ == object.y_ && ((object.getx() <= x_ + width_ - 1 && x_ + width_ <= object.getx() + object.getWidth()) ||
		(object.getx() <= x_ && x_ <= object.getx() + object.getWidth() - 1));
}

double Object::getx() const
{
	return x_;
}

double Object::gety() const
{
	return y_;
}


int Object::getWidth() const
{
	return width_;
}

int Object::getHeight() const
{
	return height_;
}

bool Object::getEnabled() const
{
	return enabled_;
}

void Object::setx(double x)
{
	x_ = x;
}

void Object::sety(double y)
{
	y_ = y;
}


void Object::setWidth(int width)
{
	width_ = width;
}

void Object::setHeight(int height)
{
	height_ = height;
}

void Object::disable()
{
	enabled_ = false;
}


void Object::enable()
{
	enabled_ = true;
}

void Object::destroy(int delay)
{	
	Arena& arena = Arena::getUniqueInstance();
	dying_ = true;
	arena.addScore(this->getScore());
	arena.addEvent(DESTROY, this, delay, NULL);
}

bool Object::getPassable() const
{
	return passable_;
}

void Object::setPassable(bool passable)
{
	passable_ = passable;
}

Object::Object(int x, int y) 
{
	x_ = x;
	y_ = y;
	enabled_ = true;
	passable_ = false;
	dying_ = false;
	currentFrame_ = 36;
	inEvent_ = false;
	setGravityAffected(false);
	setvx(0);
	setvy(0);
}


void Object::adjustPosition(const Object& object, Direction collideDirection)
{
	if (enabled_)
	{
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
	}
}

bool Object::isEnabled() const
{
	return enabled_;
}

int Object::getCurrentFrame() const
{
	return currentFrame_;
}

void Object::setCurrentFrame(int currentFrame)
{
	currentFrame_ = currentFrame;
}


double Object::getvx() const
{
	return 0;
}

double Object::getvy() const
{
	return 0;
}

Direction Object::getFacingDirection() const
{
	return NONE;
}

Direction Object::didCollide(const Object& object) const
{
	double vx = getvx() - object.getvx();
	double vy = getvy() - object.getvy();
	if (!enabled_ || !object.isEnabled())
		return NONE;
	if (passable_ || object.getPassable())
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

void Object::setvx(double vx)
{

}

void Object::setvy(double vy)
{

}

bool Object::getMoveable() const
{
	return false;
}

void Object::setFacingDirection(Direction facingDirection)
{

}

void Object::move(double time)
{

}

bool Object::getGravityAffected() const
{
	return false;
}

void Object::setGravityAffected(bool gravityAffected)
{

}

bool Object::getDying() const
{
	return dying_;
}

bool Object::getInEvent() const
{
	return inEvent_;
}

void Object::setInEvent(bool inEvent)
{
	inEvent_ = inEvent;
}

int Object::getScore() const
{
	return 0;
}