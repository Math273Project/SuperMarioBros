#include "Object.h"


Object::Object(int id)
:id_(id)
{
	passable_ = false;
}

Object::~Object()
{

}

void Object::setPosition(int x, int y)
{
	x_ = x;
	y_ = y;
}

Direction Object::didCollide(const Object& object) const // Check if two objects are collide
{
	if (!enabled_ || object.enabled_ == false)
		return NONE;
	if (object.y_ <= y_ + height_ - 1 && y_ + height_ - 1 <= object.y_ + object.height_ - 1)
		return UP;
	if (object.y_ <= y_ && y_ <= object.y_ + object.height_ - 1)
		return DOWN;
	if (object.x_ <= x_ + width_ - 1 && x_ + width_ - 1 <= object.x_ + object.width_ - 1)
		return LEFT;
	if (object.x_ <= x_ && x_ <= object.x_ + object.width_ - 1)
		return RIGHT;
	return NONE;
}


void Object::collide(const Object& object, Direction collideDirection)
{
	// Should be rewrite if there will be any things to do.
}

bool Object::onTop(const Object& object) const
{
	return y_ + height_ - 2 == object.y_ || 
		(object.y_ <= y_ + height_ - 1 && y_ + height_ - 1 <= object.y_ + object.height_ - 1);
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

void Object::destroy()
{
	
}

bool Object::passable() const
{
	return passable_;
}

bool Object::deleted() const
{
	return deleted_;
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

void Object::tryDelete()
{
	if (y_ > 2000)
		deleted_ = true;
}