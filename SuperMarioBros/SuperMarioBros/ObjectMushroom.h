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
	bool changed_;
	void changeType(); // change mushroom to flat mushroom, change type
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int MUSHROOM_WIDTH;
	static const int MUSHROOM_HEIGHT;
	static const int FLAT_MUSHROOM_WIDTH;
	static const int FLAT_MUSHROOM_HEIGHT;
}; 
