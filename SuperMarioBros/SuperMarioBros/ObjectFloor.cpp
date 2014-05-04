#include "ObjectFloor.h"

ObjectFloor::ObjectFloor(int x, int y, int width) : Object(x, y)
{
	width_ = width;
	height_ = FLOOR_HEIGHT;
}

void ObjectFloor::collide(const Object& object, Direction collideDirection)
{

}

ObjectType ObjectFloor::getType() const
{
	return FLOOR;
}

int ObjectFloor::getPriority() const
{
	return FLOOR_PRIORITY; // change it later;
}
