#include "ObjectPipe.h"

ObjectPipe::ObjectPipe(int x, int y) : Object(x, y)
{
	width_ = PIPE_WIDTH;
	height_ = PIPE_HEIGHT;
}

void ObjectPipe::collide(const Object& object, Direction collideDirection)
{
	
}

ObjectType ObjectPipe::getType() const
{
	return PIPE;
}

int ObjectPipe::getPriority() const
{
	return PIPE_PRIORITY; // change it later
}
