#include "ObjectBrick.h"

ObjectBrick::ObjectBrick(int id, int x, int y) : Object(id, x, y)
{
	width_ = 32;
	height_ = 32;
	enabled_ = true;
	//initializeSprite(0, 0);
}

void ObjectBrick::collide(const Object& object, Direction collideDirection)
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
				destroy();
				break;
			}
			break;
		}
	}
}

ObjectType ObjectBrick::getType() const
{
	return BRICK;
}

int ObjectBrick::getPriority() const
{
	return 5; // change it later;
}

void ObjectBrick::destroy()
{
	// change width, height, sprite, 
	deleted_ = true;
}
