#pragma once

#include "MovingObject.h"

class ObjectMario : public MovingObject
{
public:
	ObjectMario(int id, int x, int y, int vx, int vy);
	//~Mario();
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
protected:
	ObjectType type_;
	void setType(ObjectType type); // will change the sprite
};

