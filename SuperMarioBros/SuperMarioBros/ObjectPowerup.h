#pragma once

#include "MovingObject.h"

class ObjectPowerup : public MovingObject
{
public:
	ObjectPowerup(int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	int getScore() const override;
protected:
	
};