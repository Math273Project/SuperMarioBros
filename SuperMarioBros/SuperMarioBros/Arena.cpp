#include "Arena.h"
#include <algorithm>


const double Arena::ACCELARATION = 200;
const int Arena::LOWEST_POSITION = 2000;

Arena::Arena()
{

}

void Arena::collisionDetection() // Do collisionDetection of every objects in Arena
{
	Direction collideDirection1 = NONE, collideDirection2 = NONE;
	for (auto& i = movingObjects_.begin(); i != movingObjects_.end(); ++i)
	{
		for (auto& j = staticObjects_.begin(); j != staticObjects_.end(); ++j)
		{
			collideDirection1 = collideDirection2 = NONE;
			collideDirection1 = (*i)->didCollide(**j);
			if (collideDirection1 != NONE)
				collideDirection2 = (Direction)((collideDirection1 + 2) % 4);

			(*i)->collide(**j, collideDirection1);
			(*j)->collide(**i, collideDirection2);
		}
	}
	for (auto i = movingObjects_.begin(), j = i; i != movingObjects_.end(); ++i)
	{
		for (auto j = std::next(i,1); j != movingObjects_.end(); ++j)
		{
			collideDirection1 = collideDirection2 = NONE;
			collideDirection1 = (*i)->didCollide(**j);
			if (collideDirection1 != NONE)
				collideDirection2 = (Direction)((collideDirection1 + 2) % 4);
			else
			{
				collideDirection2 = (*j)->didCollide(**i);
				if (collideDirection2 != NONE)
					collideDirection1 = (Direction)((collideDirection2 + 2) % 4);
			}

			(*i)->collide(**j, collideDirection1);
			(*j)->collide(**i, collideDirection2);
		}
	}
}

void Arena::freeFall(double time)
{
	bool onTopOrCollide = false;
	for (auto& i = movingObjects_.begin(); i != movingObjects_.end(); ++i)
	{
		onTopOrCollide = false;
		for (auto& j = staticObjects_.begin(); j != staticObjects_.end() && !onTopOrCollide; ++j)
		{
			if ((*i)->onTop(**j) ) //if ((*i)->onTop(**j) || (*i)->didCollide(**j) != NONE)
				onTopOrCollide = true;
		}
		if (!onTopOrCollide)
			(*i)->setvy((*i)->getvy() + ACCELARATION * time / 1000);
	}
}

void Arena::erase(const Object& object)
{
	auto iNewEnd = std::remove_if(movingObjects_.begin(), movingObjects_.end(), [&](const Object* obj)
	{ 	if (obj->getType() == SMALL_MARIO || obj->getType() == SMALL_MARIO || obj->getType() == BIG_MARIO)
			mario_ = nullptr; 
		return *obj == object; });
	movingObjects_.erase(iNewEnd, movingObjects_.end());
	auto jNewEnd = std::remove_if(staticObjects_.begin(), staticObjects_.end(), [&object](const Object* obj)
	{ return *obj == object; });
	staticObjects_.erase(jNewEnd, staticObjects_.end());
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

void Arena::move(double time)
{
	for (auto& i: movingObjects_)
		i->move(time);
}

void Arena::deleteDyingObject()
{
	auto iNewEnd = remove_if(movingObjects_.begin(), movingObjects_.end(), [&](const MovingObject* obj){
		if (obj->gety() > LOWEST_POSITION && (obj->getType() == SMALL_MARIO || obj->getType() == SMALL_MARIO || obj->getType() == BIG_MARIO))
			mario_ = nullptr; 
		return obj->gety() > LOWEST_POSITION; });
		movingObjects_.erase(iNewEnd, movingObjects_.end());
	LARGE_INTEGER frequency, now;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&now);
	auto jNewEnd = remove_if(dyingObjectData_.begin(), dyingObjectData_.end(), [&](const DyingObjectData& data)
	{
		if ((double)(now.QuadPart - data.startTime_) / (double)frequency.QuadPart > data.duration_)
		{
			this->erase(*(data.data_));
			return true;
		}
		return false;
	});
	dyingObjectData_.erase(jNewEnd, dyingObjectData_.end());
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

void Arena::setMarioVx(double vx)
{
	if (mario_ != nullptr)
		mario_->setvx(vx);
}

void Arena::setMarioVy(double vy)
{
	if (mario_ != nullptr)
		mario_->setvy(vy);
}

double Arena::getMarioVx() const
{
	if (mario_ != nullptr)
		return mario_->getvx();
	else
		return INT_MIN;
}

double Arena::getMarioVy() const
{
	if (mario_ != nullptr)
		return mario_->getvy();
	else
		return INT_MIN;
}

double Arena::getMarioX() const
{
	if (mario_ != nullptr)
		return mario_->getx();
	else
		return INT_MIN;
}

double Arena::getMarioY() const
{
	if (mario_ != nullptr)
		return mario_->gety();
	else
		return INT_MIN;
}

bool Arena::isGameOver() const
{
	return mario_ == nullptr;
}

const std::list<MovingObject*>& Arena::getMovingObjects() const
{
	return movingObjects_;
}

const std::list<Object*>& Arena::getStaticObjects() const
{
	return staticObjects_;
}