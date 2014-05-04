#pragma once

#include "MovingObject.h"

class ObjectPowerup : public MovingObject
{
	ObjectPowerup(int x, int y, int vx, int vy);
	ObjectPowerup(int x, int y);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	
};