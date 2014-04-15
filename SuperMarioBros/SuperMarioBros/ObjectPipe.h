#pragma once

#include "Object.h"

class ObjectPipe : public Object 
{
public:
	ObjectPipe(int id, int x, int y);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy() override;
};