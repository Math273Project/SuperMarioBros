#pragma once

#include "Object.h"

class ObjectFlower : public Object
{
public:
	ObjectFlower(int x, int y);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
protected:

};