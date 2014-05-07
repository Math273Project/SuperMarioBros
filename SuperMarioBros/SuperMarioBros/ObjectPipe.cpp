#include "ObjectPipe.h"

ObjectPipe::ObjectPipe(int x, int y, ObjectType objectType) : Object(x, y)
{
	width_ = PIPE_WIDTH;
	type_ = objectType;
	switch (type_)
	{
	case PIPE_BIG:
		height_ = PIPE_BIG_HEIGHT;
		break;
	case PIPE_MIDDLE:
		height_ = PIPE_MIDDLE_HEIGHT;
		break;
	case PIPE_SMALL:
		height_ = PIPE_SMALL_HEIGHT;
		break;
	}	
}

void ObjectPipe::collide(const Object& object, Direction collideDirection)
{
	
}

ObjectType ObjectPipe::getType() const
{
	return type_;
}

int ObjectPipe::getPriority() const
{
	return PIPE_PRIORITY; // change it later
}
