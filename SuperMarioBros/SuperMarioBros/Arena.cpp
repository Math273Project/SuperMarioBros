#include "Arena.h"
#include "Constants.h"
#include <algorithm>


Arena::Arena()
{
	loseControl_ = false;
}

void Arena::addEvent(EventType type, Object* pObject, int time, double param)
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	events_.emplace_back(type, pObject, now.QuadPart, time, param);
}

void Arena::collisionDetection() // Do collisionDetection of every objects in Arena
{
	Direction collideDirection1 = NONE, collideDirection2 = NONE;
	for (auto i = objects_.begin(), j = i; i != objects_.end(); ++i)
	{
		for (auto j = std::next(i, 1); j != objects_.end(); ++j)
		{
			collideDirection1 = collideDirection2 = NONE;
			collideDirection1 = (*i)->didCollide(**j);
			if (collideDirection1 != NONE)
				collideDirection2 = (Direction)((collideDirection1 + 2) % 4);

			(*i)->collide(**j, collideDirection1);
			(*j)->collide(**i, collideDirection2);
		}
	}
}

void Arena::freeFall(double time)
{
	if (getMarioDying())
		mario_->setvy(mario_->getvy() + GRAVITY * time / 1000);
	else
	{
		bool onTopOrCollide = false;
		for (auto& i = objects_.begin(); i != objects_.end(); ++i)
		{
			if ((*i)->getGravityAffected())
				(*i)->setvy((*i)->getvy() + GRAVITY * time / 1000);
		}
	}
}

void Arena::erase(const Object* object)
{
	if (object == nullptr)
		return;
	if (object == mario_)
		mario_ = nullptr;
	auto iNewEnd = std::remove_if(objects_.begin(), objects_.end(), [&object](const Object* i)
	{ 
		if (i == object)
		{
			delete i;
			i = nullptr;
			return true;
		}
		return false;
	});
	objects_.erase(iNewEnd, objects_.end());
}

void Arena::addObject(Object* pObject)
{
	auto iPos = find_if(objects_.cbegin(), objects_.cend(), [&](Object* i)
				{return (*i).getPriority() > pObject->getPriority(); });
	objects_.insert(iPos, pObject);
	if (pObject->getType() == MARIO_SMALL || pObject->getType() == MARIO_BIG || pObject->getType() == MARIO_SUPER)
	{
		if (mario_ != nullptr)
			delete mario_;
		mario_ = dynamic_cast<ObjectMario*>(pObject);
	}
}

void Arena::move(double time)
{
	if (getMarioDying())
		mario_->move(time);
	else
		for (auto& i: objects_)
			i->move(time);
}

void Arena::removeOutOfBoundObject()
{
	auto iNewEnd = remove_if(objects_.begin(), objects_.end(), [&](const Object* i){
		if (i->gety() > LOWEST_POSITION)
		{
			if (mario_ == i)
				mario_ = nullptr;
			delete i;
			i = nullptr;
			return true;
		}
		return false; });
	objects_.erase(iNewEnd, objects_.end());
}

Arena::~Arena()
{
	for (auto& i : objects_)
	{
		delete i;
		i = nullptr;
	}
}

void Arena::setMarioVx(double vx)
{
	if (loseControl_)
		return;
	if (mario_ == nullptr || mario_->getDying())
		return;
	return mario_->setvx(vx);
}

void Arena::setMarioVy(double vy)
{
	if (loseControl_)
		return;
	if (mario_ == nullptr || mario_->getDying())
		return;
	return mario_->setvy(vy);
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

const std::list<Object*>& Arena::getObjects() const
{
	return objects_;
}

bool Arena::MarioDownToEarth() const
{
	if (mario_ == nullptr)
		return false;
	for (auto& i = objects_.begin(); i != objects_.end(); ++i)
	{
		if (mario_ != *i)
		{
			if (mario_->onTop(**i))
				return true;
			if (mario_->didCollide(**i) != NONE)
				return true;
		}
	}
	return false;
}

void Arena::processEvent()
{
	LARGE_INTEGER frequency, now;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&now);
	auto iNewEnd = std::remove_if(events_.begin(), events_.end(), [&](Event& i)
	{
		double timeElapsed = ((double)(now.QuadPart - i.getStartTime()) / (double)frequency.QuadPart) * 1000;
		i.getObject()->setInEvent(true);
		switch (i.getType())
		{
		case DESTROY:
			if (timeElapsed > i.getTime())
			{
				i.getObject()->setInEvent(false);
				erase(i.getObject());
				return true;
			}
			return false;
			break;
		case START_MOVING_X:
			if (timeElapsed > i.getTime())
			{
				i.getObject()->setvx(i.getParam());
				return true;
			}
			return false;
			break;
		case KEEP_MOVING_Y:
			i.setTime(i.getTime() - timeElapsed);
			i.setStartTime(now.QuadPart);
			i.getObject()->setvx(0);
			if (i.getTime() > 0)
			{
				//i.getObject()->setvy(i.getParam());
				i.getObject()->sety(i.getObject()->gety() + i.getParam() * timeElapsed / 1000);
				i.getObject()->setPassable(true);
				i.getObject()->setGravityAffected(false);
				return false;
			}
			else
			{
				//i.getObject()->setvy(0);
				i.getObject()->setInEvent(false);
				i.getObject()->sety(i.getObject()->gety() + i.getParam() * (timeElapsed + i.getTime()) / 1000);
				i.getObject()->setPassable(false);
				i.getObject()->setGravityAffected(true);
				return true;
			}
			break;
		case KEEP_NOT_PASSABLE:
			i.setTime(i.getTime() - timeElapsed);
			i.setStartTime(now.QuadPart);
			if (i.getTime() > 0)
			{
				i.getObject()->setPassable(false);
				return false;
			}
			else
			{
				i.getObject()->setInEvent(false);
				i.getObject()->setPassable(true);
				return true;
			}
			break;
		case KEEP_LOSE_CONTROL:
			loseControl_ = true;
			if (timeElapsed > i.getTime())
			{
				loseControl_ = false;
				i.getObject()->setInEvent(false);
				return true;
			}
			return false;
			break;
		}
		return false;
	});
	events_.erase(iNewEnd, events_.end());
}

bool Arena::getMarioDying() const
{
	if (mario_ != nullptr)
		return mario_->getDying();
	else
		return false;
}

bool Arena::getMarioInEvent() const
{
	if (mario_ != nullptr)
		return mario_->getInEvent();
	else
		return false;
}