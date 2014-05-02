#pragma once

#include "Object.h"

// This object does not include the powerup or coin insde the question mark
class ObjectQuestion : public Object
{
public:
	ObjectQuestion(int id, int x, int y, Object* linkedObject);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy(bool instantDestroy = false) override;
	int getDyingDuration() const override;
protected:
	bool changed_;
	Object* linkedObject_;
};