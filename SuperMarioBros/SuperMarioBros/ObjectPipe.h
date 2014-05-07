#pragma once

#include "Object.h"

class ObjectPipe : public Object 
{
public:
	ObjectPipe::ObjectPipe(int x, int y, ObjectType objectType);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;

protected:
	ObjectType type_;
};

