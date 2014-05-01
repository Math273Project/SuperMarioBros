#pragma once

#include "Object.h"

class ObjectFloor : public Object
{
public:
	ObjectFloor(int id, int x, int y, int width);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
protected:
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int WIDTH;
	static const int HEIGHT;
};