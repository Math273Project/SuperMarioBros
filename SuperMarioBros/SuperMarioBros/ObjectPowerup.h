#pragma once

#include "MovingObject.h"

class ObjectPowerup : public MovingObject
{
	ObjectPowerup(int id, int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
protected:
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int WIDTH ;
	static const int HEIGHT;
};