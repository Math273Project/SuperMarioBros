#include "ObjectQuestion.h"
#include "Arena.h"
#include "ObjectMushroom.h"

ObjectQuestion::ObjectQuestion(int x, int y, ObjectType attachedObjectType) : Object(x, y)
{
	width_ = QUESTION_WIDTH;
	height_ = QUESTION_HEIGHT;
	attachedObjectType_ = attachedObjectType;
	changed_ = false;
}

void ObjectQuestion::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE) //  need more working
		return;

	switch (object.getType())
	{
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		case UP:
			if (!changed_)
			{
				Arena& arena = Arena::getUniqueInstance();
				changed_ = true;
				switch (attachedObjectType_)
				{
				case MUSHROOM:
					ObjectMushroom* mushroom = new ObjectMushroom(x_, y_, 0, 0);
					mushroom->setPassable(true);
					mushroom->setGravityAffected(true);
					arena.addObject(mushroom);
					arena.addEvent(KEEP_MOVING_Y, mushroom, MUSHROOM_HEIGHT * 1000 / 40, -40);
					arena.addEvent(START_MOVING_X, mushroom, MUSHROOM_HEIGHT * 1000 / 40 + 100, 40);
					break;
				}
			}
			break;
		}
		break;
	}
}

ObjectType ObjectQuestion::getType() const
{
	if (changed_)
		return BLOCK;
	return QUESTION;
}

int ObjectQuestion::getPriority() const
{
	return QUESTION_PRIORITY; // change it later
}