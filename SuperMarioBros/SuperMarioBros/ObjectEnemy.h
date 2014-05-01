#pragma once

#include "MovingObject.h"

class ObjectEnemy : public MovingObject
{
public:
	ObjectEnemy(int id, int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
	void changeType(); 
protected:
	bool dying_; // if the enemy is dying or not.
	
};