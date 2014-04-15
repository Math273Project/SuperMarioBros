#pragma once

#include "MovingObject.h"

class ObjectMushroom : public MovingObject
{
public:
	ObjectMushroom(int id, int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy() override;
protected:
	bool changed_;
}; 

