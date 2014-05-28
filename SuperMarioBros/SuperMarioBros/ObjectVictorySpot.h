#pragma once

#include "Object.h"

class ObjectVictorySpot : public Object
{
public:
	ObjectVictorySpot(int x, int y);
	void collide(const Object& object, Direction collideDirection) override;
	ObjectType getType() const override;
	int getPriority() const override;
protected:

};