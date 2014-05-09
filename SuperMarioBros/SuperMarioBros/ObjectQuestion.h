#pragma once

#include "Object.h"

// This object does not include the powerup or coin insde the question mark
class ObjectQuestion : public Object
{
public:
	ObjectQuestion(int x, int y, ObjectType attachedObject);
	void collide(const Object& object, Direction collideDirection);
	ObjectType getType() const override;
	int getPriority() const override;
protected:
	bool changed_;
	ObjectType attachedObjectType_;
	Object* attachedObject_;
};