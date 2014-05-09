#include "ObjectFlag.h"

ObjectFlag::ObjectFlag(int x, int y) : Object(x, y)
{
	width_ = FLAG_POLE_WIDTH;
	height_ = FLAG_POLE_HEIGHT;
}

void ObjectFlag::collide(const Object& object, Direction collideDirection)
{

}

ObjectType ObjectFlag::getType() const
{
	return FLAG;
}

int ObjectFlag::getPriority() const
{
	return FLAG_PRIORITY;
}