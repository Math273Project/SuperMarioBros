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
	
};