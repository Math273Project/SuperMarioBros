#pragma once

#include "MovingObject.h"

class ObjectEnemy : public MovingObject
{
public:
	ObjectEnemy(int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	void changeType();
	bool dying_; // if the enemy is dying or not.
	
};