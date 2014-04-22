#pragma once
#include "Object.h"

class MovingObject : public Object
{
public:
	MovingObject(int id, int x, int y, int vx, int vy);
	double getvx() const;
	double getvy() const;
	Direction getFacingDirection() const;
	Direction didCollide(const Object& object) const; // Check if two objects are collide, return a collide direction
	void setvx(double vx); // will callsetFacingDirection if the direction of velocity changes;
	void setvy(double vy);
	bool moveable() const override final;
	void setFacingDirection(Direction facingDirection);
	void move(double time);
protected:
	double vx_; // unit: pixel / second
	double vy_;
	Direction facingDirection_;
};