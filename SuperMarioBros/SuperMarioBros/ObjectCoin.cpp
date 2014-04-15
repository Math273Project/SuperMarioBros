#include "ObjectCoin.h"

ObjectCoin::ObjectCoin(int id, int x, int y) : Object(id, x, y)
{
	width_ = 32;
	height_ = 32;
	enabled_ = false;
	//initializeSprite(0, 0);
}

ObjectType ObjectCoin::getType() const
{
	return BLOCK;
}
int ObjectCoin::getPriority() const
{
	return 5; // change it later;
}

void ObjectCoin::destroy()
{
	// change width, height, sprite, 
	deleted_ = true;
}

void ObjectCoin::collide(const Object& object, Direction collideDirection)
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
			case DOWN:
				if (!enabled_)
					y_ -= height_;
				break;
			default:
				if (enabled_)
					destroy();
				break;
			}
		}
	}
}
