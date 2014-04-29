#include "Object.h"


Object::Object(int id)
:id_(id)
{
	passable_ = false;
	currentFrame_ = 0;
}

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

int Object::getId() const
{
	return id_;
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


bool Object::operator ==(const Object& rhs) const
{
	return id_ == rhs.id_;
}

void Object::destroy(bool instantDestroy)
{
	
}

bool Object::passable() const
{
	return passable_;
}

bool Object::moveable() const
{
	return false;
}

Object::Object(int id, int x, int y) : Object(id)
{
	x_ = x;
	y_ = y;
}


void Object::adjustPosition(const Object& object, Direction collideDirection)
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

bool Object::isEnabled() const
{
	return enabled_;
}

Direction Object::didCollide(const Object& object) const // Check if two objects are collide
{
	if (!enabled_ || !object.isEnabled())
		return NONE;
	if (passable_ || object.passable())
		return NONE;
	if (!(((object.gety() <= y_ + height_ - 1 && y_ + height_ <= object.gety() + object.getHeight()) ||
		(object.gety() <= y_ && y_ <= object.gety() + object.getHeight() - 1))
		&& ((object.getx() <= x_ + width_ - 1 && x_ + width_ <= object.getx() + object.getWidth()) ||
		(object.getx() <= x_ && x_ <= object.getx() + object.getWidth() - 1))))
		return NONE;
	if (object.gety() <= y_ + height_ - 1 && y_ + height_ <= object.gety() + object.getHeight())
		return UP;
	if (object.gety() <= y_ && y_ <= object.gety() + object.getHeight() - 1)
		return DOWN;
	if (object.getx() <= x_ + width_ - 1 && x_ + width_ <= object.getx() + object.getWidth())
		return LEFT;
	if (object.getx() <= x_ && x_ <= object.getx() + object.getWidth() - 1)
		return RIGHT;
	return NONE;
}

int Object::getCurrentFrame() const
{
	return currentFrame_;
}

void Object::setCurrentFrame(int currentFrame)
{
	currentFrame_ = currentFrame;
}