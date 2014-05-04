#include "ObjectBlock.h"

ObjectBlock::ObjectBlock(int x, int y) : Object(x, y)
{
	width_ = BLOCK_WIDTH;
	height_ = BLOCK_HEIGHT;
}

void ObjectBlock::collide(const Object& object, Direction collideDirection)
{

}

ObjectType ObjectBlock::getType() const
{
	return BLOCK;
}

int ObjectBlock::getPriority() const
{
	return BLOCK_PRIORITY; // change it later;
}
