#include "Object.h"

Object::Object(ObjectType type, int id, int priority, bool moveable)
:type_(type), id_(id), priority_(priority), moveable_(moveable)
{

}

Object::~Object()
{

}

void Object::setPosition(int x, int y)
{
	x_ = x;
	y_ = y;
}



void Object::draw() //should call the game update();
{
	// Should be rewrite?
}

// Make Mario always stand in the middle of screen.
void Object::move(int time)
{
	x_ += vx_ * time / 1000;
	y_ += vy_ * time / 1000;
}



bool Object::didCollide(const Object& object) const // Check if two objects are collide
{
	return ((object.x_ <= x_ && x_ <= object.x_ + object.width_ - 1) || (object.x_ <= x_ && x_ + width_ - 1 <= object.x_ + object.width_ - 1))
		&& ((object.y_ <= y_ && y_ <= object.y_ + object.height_ - 1) || (object.y_ <= y_ && y_ + height_ - 1 <= object.y_ + object.height_ - 1));
}


void Object::collide(const Object& object)
{
	// Should be rewrite if there will be any things to do.
}



int Object::getx() const
{
	return x_;
}

int Object::gety() const
{
	return y_;
}

int Object::getvx() const
{
	return vx_;
}

int Object::getvy() const
{
	return vy_;
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

FacingDirection Object::getFacingDirection() const
{
	return facingDirection_;
}

ObjectType Object::getType() const
{
	return type_;
}

int Object::getId() const
{
	return type_;
}

int Object::getPriority() const
{
	return priority_;
}

bool Object::moveable() const
{
	return moveable_;
}

LPD3DXSPRITE Object::getSprite() const
{
	return sprite_;
}


void Object::setx(int x)
{
	x_ = x;
}

void Object::sety(int y)
{
	y_ = y;
}

void Object::setvx(int vx)
{
	vx_ = vx;
}

void Object::setvy(int vy)
{
	vy_ = vy;
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

void Object::setFacingDirection(FacingDirection facingDirection)
{
	facingDirection_ = facingDirection;
}

void Object::setSprite(LPD3DXSPRITE sprite)
{
	sprite_ = sprite;
}