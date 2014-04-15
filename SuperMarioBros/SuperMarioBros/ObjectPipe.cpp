#include "ObjectPipe.h"

ObjectPipe::ObjectPipe(int id, int x, int y) : Object(id, x, y)
{
	width_ = 32;
	height_ = 32;
	enabled_ = true;
}

void ObjectPipe::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
	if (collideDirection != NONE)
	{
		switch (object.getType())
		{
		case SMALLMARIO:
			switch (collideDirection)
			{
			case UP:
				break;
			}
			break;
		}
	}
}

ObjectType ObjectPipe::getType() const
{
	return PIPE;
}

int ObjectPipe::getPriority() const
{
	return 5; // change it later
}

void ObjectPipe::destroy()
{
	// change width, height, sprite, 
	deleted_ = true;
}