#pragma once

#include "MovingObject.h"

class ObjectMushroom : public MovingObject
{
public:
	ObjectMushroom(int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	int getScore() const override;
protected:
	bool dying_; // if the mushroom is dying or not.
	void changeType(); // change mushroom to flat mushroom(Dying mushroom)
	
}; 
