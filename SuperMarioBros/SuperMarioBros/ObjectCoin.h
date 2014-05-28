#pragma once

#include "MovingObject.h"

class ObjectCoin : public MovingObject
{
public:
	ObjectCoin(int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
	int getScore() const override;
protected:
	
};