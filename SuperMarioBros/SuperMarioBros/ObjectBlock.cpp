#include "ObjectBlock.h"

ObjectBlock::ObjectBlock(int id, int x, int y) : Object(id, x, y) 
{
	width_ = 32;
	height_ = 32;
	enabled_ = true;
	//initializeSprite(0, 0);
}

void ObjectBlock::collide(const Object& object, Direction collideDirection)
{
	if (passable_ || object.passable())
		return;
}

ObjectType ObjectBlock::getType() const
{
	return BLOCK;
}
int ObjectBlock::getPriority() const
{
	return 5; // change it later;
}

void ObjectBlock::destroy()
{
	// change width, height, sprite, 
	deleted_ = true;
}
