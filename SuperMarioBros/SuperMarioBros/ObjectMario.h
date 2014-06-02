#pragma once

#include "MovingObject.h"

class ObjectMario : public MovingObject
{
public:
	ObjectMario(int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	bool getInvisible() const;
	void setInvisible(bool invisible = true);
protected:
	bool invisible_;
	ObjectType type_;
	void destroy();
	void setType(ObjectType type); // will change the sprite
};
