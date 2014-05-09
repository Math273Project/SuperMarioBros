#pragma once

#include "Object.h"

class ObjectFlag : public Object
{
public:
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	ObjectFlag(int x, int y);
	friend class ObjectFlagPole;
};