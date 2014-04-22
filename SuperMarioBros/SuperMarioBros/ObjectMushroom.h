#pragma once

#include "MovingObject.h"

class ObjectMushroom : public MovingObject
{
public:
	ObjectMushroom(int id, int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy() override;
	int getDyingDuration() const override;
protected:
	bool dying_; // if the mushroom is dying or not.
	void changeType(); // change mushroom to flat mushroom(Dying mushroom)
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int WIDTH;
	static const int HEIGHT;
	static const int FLAT_MUSHROOM_WIDTH;
	static const int FLAT_MUSHROOM_HEIGHT;
}; 
