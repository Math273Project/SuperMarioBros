#pragma once

#include "Object.h"

class ObjectCoin : public Object
{
public:
	ObjectCoin(int x, int y);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	
};