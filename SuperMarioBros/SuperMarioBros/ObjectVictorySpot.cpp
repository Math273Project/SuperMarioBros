#include "ObjectVictorySpot.h"
#include "Arena.h"

ObjectVictorySpot::ObjectVictorySpot(int x, int y) : Object(x, y)
{
	width_ = VICTORY_SPOT_WIDTH;
	height_ = VICTORY_SPOT_HEIGHT;
}

void ObjectVictorySpot::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	Arena& arena = Arena::getUniqueInstance();
	switch (object.getType())
	{
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		default:
			disable();
			arena.levelPlus();
			destroy();
			break;
		}
	}
}

ObjectType ObjectVictorySpot::getType() const
{
	return VICTORY_SPOT;
}

int ObjectVictorySpot::getPriority() const
{
	return VICTORY_SPOT_PRIORITY; 
}
