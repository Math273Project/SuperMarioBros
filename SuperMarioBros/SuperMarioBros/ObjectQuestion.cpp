#include "ObjectQuestion.h"
#include "Arena.h"
#include "ObjectMushroom.h"
#include "ObjectCoin.h"
#include "ObjectPowerup.h"

ObjectQuestion::ObjectQuestion(int x, int y, ObjectType attachedObjectType) : Object(x, y)
{
	width_ = QUESTION_WIDTH;
	height_ = QUESTION_HEIGHT;
	changed_ = false;
	attachedObjectType_ = attachedObjectType;
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
					attachedObject_ = new ObjectMushroom(x_, y_, 0, 0);
					break;
				case COIN:
					attachedObject_ = new ObjectCoin(x_, y_);
					break;
				case POWERUP:
					attachedObject_ = new ObjectPowerup(x_, y_, 0, 0);
					break;
				}
				arena.addObject(attachedObject_);
				switch (attachedObject_->getType())
				{
				case MUSHROOM:			
					attachedObject_->setPassable(true);
					arena.addEvent(KEEP_MOVING_Y, attachedObject_, MUSHROOM_HEIGHT * 1000 / 40, -40);
					arena.addEvent(START_MOVING_X, attachedObject_, MUSHROOM_HEIGHT * 1000 / 40 + 100, 40);
					break;

				case POWERUP:
					attachedObject_->setPassable(true);
					arena.addEvent(KEEP_MOVING_Y, attachedObject_, POWERUP_HEIGHT * 1000 / 40, -40);
					break;

				case COIN:
					attachedObject_->setPassable(true);
					arena.addEvent(KEEP_MOVING_Y, attachedObject_, COIN_HEIGHT * 1000 / 40, -40);
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