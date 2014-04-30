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
	auto iNewEnd = std::remove_if(movingObjects_.begin(), movingObjects_.end(), [&](const Object* i)
	{ 	if (i->getType() == SMALL_MARIO || i->getType() == SMALL_MARIO || i->getType() == BIG_MARIO)
			mario_ = nullptr; 
		return *i == object; });
	movingObjects_.erase(iNewEnd, movingObjects_.end());
	auto jNewEnd = std::remove_if(staticObjects_.begin(), staticObjects_.end(), [&object](const Object* i)
	{ return *i == object; });
	staticObjects_.erase(jNewEnd, staticObjects_.end());
}

void Arena::pushBack(MovingObject* pMovingObject)
{
	auto iPos = find_if(movingObjects_.cbegin(), movingObjects_.cend(), [&](MovingObject* i)
				{return (*i).getPriority() > pMovingObject->getPriority(); });
	movingObjects_.insert(iPos, pMovingObject);
	if (pMovingObject->getType() == SMALL_MARIO || pMovingObject->getType() == SMALL_MARIO || pMovingObject->getType() == BIG_MARIO)
		mario_ = pMovingObject;
}

void Arena::pushBack(Object* pObject)
{
	auto iPos = find_if(staticObjects_.cbegin(), staticObjects_.cend(), [&](Object* i)
				{return (*i).getPriority() > pObject->getPriority(); });
	staticObjects_.insert(iPos, pObject);
}

void Arena::move(double time)
{
	for (auto& i: movingObjects_)
		i->move(time);
}

void Arena::deleteDyingObject()
{
	auto iNewEnd = remove_if(movingObjects_.begin(), movingObjects_.end(), [&](const MovingObject* i){
		if (i->gety() > LOWEST_POSITION && (i->getType() == SMALL_MARIO || i->getType() == SMALL_MARIO || i->getType() == BIG_MARIO))
			mario_ = nullptr; 
		return i->gety() > LOWEST_POSITION; });
		movingObjects_.erase(iNewEnd, movingObjects_.end());
	LARGE_INTEGER frequency, now;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&now);
	auto jNewEnd = remove_if(dyingObjectData_.begin(), dyingObjectData_.end(), [&](const DyingObjectData& i)
	{
		if ((double)(now.QuadPart - i.startTime) / (double)frequency.QuadPart > i.duration)
		{
			this->erase(*(i.data));
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

const std::list<Gap>& Arena::getGaps() const
{
	return gaps_;
}

void Arena::addGap(double newStartX, double newEndX)
{
	if (newStartX > newEndX)
		return;
	if (gaps_.empty())
	{
		gaps_.emplace_back(newStartX, newEndX);
	}
	else
	{
		auto iNewEnd = remove_if(gaps_.begin(), gaps_.end(), [&](const Gap& i)
		{
			bool flag = false;
			if (i.startX <= newStartX && newStartX <= i.endX)
			{
				flag = true;
				newStartX = i.startX;
			}
			if (i.startX <= newEndX && newEndX <= i.endX)
			{
				flag = true;
				newEndX = i.endX;
			}
			if (newStartX <= i.startX && i.endX <= newEndX)
				flag = true;

			return flag;
		});
		gaps_.erase(iNewEnd, gaps_.end());
		auto iPos = find_if(gaps_.cbegin(), gaps_.cend(), [&](const Gap& i){ return i.startX > newEndX; });
		gaps_.emplace(iPos, newStartX, newEndX);
	}
}