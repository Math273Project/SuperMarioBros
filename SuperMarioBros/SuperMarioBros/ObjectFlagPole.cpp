#include "ObjectFlagPole.h"
#include "ObjectFlag.h"
#include "Arena.h"

ObjectFlagPole::ObjectFlagPole(int x, int y) : Object(x, y)
{
	width_ = FLAG_POLE_WIDTH;
	height_ = FLAG_POLE_HEIGHT;
	flag_ = new ObjectFlag(x_ - FLAG_WIDTH + 12, y_ + 25);
	Arena& arena = Arena::getUniqueInstance();
	arena.addObject(flag_);
}

void ObjectFlagPole::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;

	switch (object.getType())
	{
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		if (!inEvent_)
		{
			Arena& arena = Arena::getUniqueInstance();
			arena.addEvent(KEEP_NOT_PASSABLE, this, 1000, 0);
			arena.addEvent(KEEP_MOVING_Y, flag_, 1000, FLAG_POLE_HEIGHT - 30);
		}
		break;
	}
}

ObjectType ObjectFlagPole::getType() const
{
	return FLAG_POLE;
}

int ObjectFlagPole::getPriority() const
{
	return FLAG_POLE_PRIORITY; 
}