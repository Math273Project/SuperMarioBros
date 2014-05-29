#pragma once

#include "Object.h"

class ObjectBrick : public Object
{
public:
	ObjectBrick(int x, int y);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
protected:

};