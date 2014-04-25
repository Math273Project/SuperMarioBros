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
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
	void changeType();
protected:
	bool dying_;
	static const int DYING_DURATION;
	static const int PRIORITY;
	static const int WIDTH;
	static const int HEIGHT;
	static const int BRICK_PIECE_WIDTH;
	static const int BRICK_PIECE_HEIGHT;
};