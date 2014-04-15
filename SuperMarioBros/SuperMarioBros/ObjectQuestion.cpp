#include "ObjectQuestion.h"

ObjectQuestion::ObjectQuestion(int id, int x, int y) : Object(id, x, y)
{
	width_ = 32;
	height_ = 32;
	enabled_ = true;
}

void ObjectQuestion::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case SMALLMARIO:
		case BIGMARIO:
		case SUPERMARIO:
			switch (collideDirection)
			{
			case UP:
				if (changed_)
				{
					// change to block
				}
				break;
			}
			break;
		}
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
	return 5; // change it later
}

void ObjectQuestion::destroy()
{
	// change width, height, sprite,
}