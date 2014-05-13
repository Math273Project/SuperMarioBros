#pragma once
#include <list>
#include "Object.h"
#include "ObjectMario.h"
#include "event.h"


// call this name?

class Arena
{
public:
	Arena(const Arena&) = delete; // Unique Instance
	Arena& operator=(const Arena&) = delete;
	static Arena& getUniqueInstance()
	{
		static Arena arena;
		return arena;
	}
	void addEvent(EventType type, Object* pObject, int time, double param);
	void collisionDetection(); // Do collisionDetection of every objects in Arena
	void freeFall(double time); //adjust the object' vy according to gravity if it is in the air
	void erase(const Object* pObject);
	void addObject(Object* pObject);
	void move(double time); // move all objects according to current velocity.
	void removeOutOfBoundObject();
	void setMarioVx(double vx);
	void setMarioVy(double vy);
	bool getMarioDying() const;
	bool MarioDownToEarth() const;
	double getMarioVx() const;
	double getMarioVy() const;
	double getMarioX() const;
	double getMarioY() const;
	bool getMarioInEvent() const;
	bool isGameOver() const;
	void processEvent();
	~Arena();
	const std::list<Object*>& getObjects() const;

protected:
	std::list<Object*> objects_; //  in accedning order of priority
	Arena(); // Unique Instance
	ObjectMario* mario_;
	std::list<Event> events_;
	bool loseControl_;
};

