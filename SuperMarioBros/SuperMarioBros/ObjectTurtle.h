#pragma once

#include "MovingObject.h"

class ObjectTurtle : public MovingObject
{
public:
	ObjectTurtle(int id, int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
	void changeType();
protected:
	bool spining_; // if the turtle is spining or not.
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int WIDTH;
	static const int HEIGHT;
	static const int SPIN_TURTLE_WIDTH;
	static const int SPIN_TURTLE_HEIGHT;
};