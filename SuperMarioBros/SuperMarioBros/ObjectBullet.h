#pragma once

#include "MovingObject.h"

class ObjectBullet : public MovingObject
{
public:
	ObjectBullet(int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	
};
