#include "Arena.h"
#include <algorithm>


const double Arena::ACCELARATION = 9.8;
const int Arena::LOWEST_POSITION = 2000;

Arena::Arena()
{

}

void Arena::collisionDetection() // Do collisionDetection of every objects in Arena
{
	Direction collideDirection1, collideDirection2;
	for (auto& i = movingObjects_.begin(); i != movingObjects_.end(); i++)
	{
		for (auto& j = staticObjects_.begin(); j != staticObjects_.end(); j++)
		{
			collideDirection1 = (*i)->didCollide(**j);
			if (collideDirection1 != NONE)
				(*i)->collide(**j, collideDirection1);
			collideDirection2 = (*j)->didCollide(**i);
			if (collideDirection2 != NONE)
				(*j)->collide(**i, collideDirection2);
		}
	}
	for (auto& i = movingObjects_.begin(), j = i; i != movingObjects_.end(); j = ++i)
	{
		for (; j != movingObjects_.end(); j++)
		{
			collideDirection1 = (*i)->didCollide(**j);
			if (collideDirection1 != NONE)
				(*i)->collide(**j, collideDirection1);
			collideDirection2 = (*j)->didCollide(**i);
			if (collideDirection2 != NONE)
				(*j)->collide(**i, collideDirection2);
		}
	}
}

void Arena::freeFall(int time)
{
	bool onTop = false;
	for (auto& i = movingObjects_.begin(); i != movingObjects_.end(); i++)
	{
		onTop = false;
		for (auto& j = staticObjects_.begin() ; j != staticObjects_.end() && !onTop; j++)
		{
			if ((*i)->onTop(**j))
				onTop = true;
		}
		if (!onTop)
			(*i)->setvy((*i)->getvy() + ACCELARATION * time / 1000);
	}
}

void Arena::erase(const Object& object)
{
	std::remove_if(movingObjects_.begin(), movingObjects_.end(), [&](const Object* obj)
	{ 	if (obj->getType() == SMALL_MARIO || obj->getType() == SMALL_MARIO || obj->getType() == BIG_MARIO)
			mario_ = nullptr; 
		return *obj == object; });
	std::remove_if(staticObjects_.begin(), staticObjects_.end(), [&object](const Object* obj)
	{ return *obj == object; });
}

void Arena::pushBack(MovingObject* pMovingObject)
{
	movingObjects_.push_back(pMovingObject);
	if (pMovingObject->getType() == SMALL_MARIO || pMovingObject->getType() == SMALL_MARIO || pMovingObject->getType() == BIG_MARIO)
		mario_ = pMovingObject;
}

void Arena::pushBack(Object* pObject)
{
	staticObjects_.push_back(pObject);
}

void Arena::move(int time)
{
	for (auto& i = movingObjects_.begin(); i != movingObjects_.end(); i++)
		(*i)->move(time);
}

void Arena::deleteDyingObject()
{
	remove_if(movingObjects_.begin(), movingObjects_.end(), [](const MovingObject* obj){
		return obj->gety() > LOWEST_POSITION; }); 
	LARGE_INTEGER frequency, now;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&now);
	remove_if(dyingObjectData_.begin(), dyingObjectData_.end(), [&](const DyingObjectData& data)
	{
		if ((double)(now.QuadPart - data.startTime_) / (double)frequency.QuadPart > data.duration_)
		{
			this->erase(*(data.data_));
			return true;
		}
		return false;
	});
}

Arena::~Arena()
{
	for (auto& i : staticObjects_)
	{
		delete i;
		i = 0;
	}
	for (auto& i : movingObjects_)
	{
		delete i;
		i = 0;
	}
}

void Arena::pushDyingObjectData(const DyingObjectData& data)
{
	dyingObjectData_.push_back(data);
}

MovingObject* Arena::getMario() const
{
	return mario_;
}

const std::list<MovingObject*>& Arena::getMovingObjects() const
{
	return movingObjects_;
}

const std::list<Object*>& Arena::getStaticObjects() const
{
	return staticObjects_;
}