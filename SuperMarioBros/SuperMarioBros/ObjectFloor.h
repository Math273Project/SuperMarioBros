#pragma once

#include "Object.h"

class ObjectFloor : public Object
{
public:
	ObjectFloor(int x, int y, int endx);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	
};