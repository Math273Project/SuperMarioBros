#pragma once

#include "Object.h"

// This object does not include the powerup or coin insde the question mark
class ObjectQuestion : public Object
{
public:
	ObjectQuestion(int id, int x, int y);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
	void destroy() override;
protected:
	bool changed_;
};