#pragma once

#include "Object.h"

class ObjectFlagPole : public Object
{
public:
	ObjectFlagPole(int x, int y);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	Object* flag_;
};
