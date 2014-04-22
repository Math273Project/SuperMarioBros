#pragma once

#include "MovingObject.h"

class ObjectEnemy : public MovingObject
{
public:
	ObjectEnemy(int id, int x, int y, int vx, int vy);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy() override;
	int getDyingDuration() const override;
	void changeType(); // change mushroom to flat mushroom, change sprite
protected:
	bool dying_; // if the enemy is dying or not.
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int WIDTH;
	static const int HEIGHT;
	static const int FLAT_ENEMY_WIDTH;
	static const int FLAT_ENEMY_HEIGHT;
};