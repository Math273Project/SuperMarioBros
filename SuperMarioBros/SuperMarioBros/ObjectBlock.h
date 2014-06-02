#pragma once

#include "Object.h"

class ObjectBlock : public Object
{
public:
	ObjectBlock(int x, int y);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	
};
