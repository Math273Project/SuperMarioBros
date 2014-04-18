#include "Arena.h"
#include <algorithm>

void Arena::collisionDetection() // Do collisionDetection of every objects in Arena
{
	Direction collideDirection1, collideDirection2;
	for (int i = 0; i < movingObjects_.size(); i++)
	{
		for (int j = 0; j < staticObjects_.size(); j++)
		{
			collideDirection1 = movingObjects_[i]->didCollide(*staticObjects_[j]);
			if (collideDirection1 != NONE)
				movingObjects_[i]->collide(*staticObjects_[j], collideDirection1);
			collideDirection2 = staticObjects_[j]->didCollide(*movingObjects_[i]);
			if (collideDirection2 != NONE)
				staticObjects_[j]->collide(*movingObjects_[i], collideDirection2);
		}
	}
	for (int i = 0; i < movingObjects_.size(); i++)
	{
		for (int j = i + 1; j < movingObjects_.size(); j++)
		{
			collideDirection1 = movingObjects_[i]->didCollide(*movingObjects_[j]);
			if (collideDirection1 != NONE)
				movingObjects_[i]->collide(*movingObjects_[j], collideDirection1);
			collideDirection2 = movingObjects_[j]->didCollide(*movingObjects_[i]);
			if (collideDirection2 != NONE)
				movingObjects_[j]->collide(*movingObjects_[i], collideDirection2);
		}
	}
}

void Arena::freeFall(int time)
{
	bool onTop = false;
	for (int i = 0; i < movingObjects_.size(); i++)
	{
		onTop = false;
		for (int j = i + 1; j < staticObjects_.size() && !onTop; j++)
		{
			if (movingObjects_[i]->onTop(*staticObjects_[j]))
				onTop = true;
		}
		if (!onTop)
			movingObjects_[i]->setvy(movingObjects_[i]->getvy() + ACCELARATION * time / 1000);
	}
}

void Arena::remove(const Object& object)
{
	std::remove_if(movingObjects_.begin(), movingObjects_.end(), [&object](const Object* obj)
	{ return *obj == object; });
	std::remove_if(staticObjects_.begin(), staticObjects_.end(), [&object](const Object* obj)
	{ return *obj == object; });
}

void Arena::pushBack(MovingObject* pMovingObject)
{
	movingObjects_.push_back(pMovingObject);
}

void Arena::pushBack(Object* pObject)
{
	staticObjects_.push_back(pObject);
}

void Arena::move(int time)
{
	for (int i = 0; i < movingObjects_.size(); i++)
		movingObjects_[i]->move(time);
}

void Arena::deleteObject()
{
	for (int i = 0; i < movingObjects_.size(); i++)
		movingObjects_[i]->tryDelete();
	for (int i = 0; i < staticObjects_.size(); i++)
		staticObjects_[i]->tryDelete();
	remove_if(movingObjects_.begin(), movingObjects_.end(), [](const MovingObject* obj){return obj->deleted()
		|| obj->gety() > 2000; }); // change the constant 2000 later
	remove_if(staticObjects_.begin(), staticObjects_.end(), [](const Object* obj){return obj->deleted(); });
}