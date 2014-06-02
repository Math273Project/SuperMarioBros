#pragma once
#include "Object.h"

class MovingObject : public Object
{
public:
	MovingObject();
	MovingObject(int x, int y, int vx, int vy);
	double getvx() const;
	double getvy() const;
	Direction getFacingDirection() const;
	void setvx(double vx); // will callsetFacingDirection if the direction of velocity changes;
	void setvy(double vy);
	bool getMoveable() const;
	void setFacingDirection(Direction facingDirection);
	void move(double time);
	bool getGravityAffected() const;
	void setGravityAffected(bool gravityAffected);
protected:
	bool gravityAffected_;
	double vx_; // unit: pixel / second
	double vy_;
	Direction facingDirection_;
};
