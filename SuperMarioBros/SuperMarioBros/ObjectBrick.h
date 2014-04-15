#pragma once

#include "Object.h"

class ObjectBrick : public Object
{
public:
	ObjectBrick(int id, int x, int y);
	//~Mario();
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy() override;
};