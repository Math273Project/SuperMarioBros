#pragma once
#include <list>
#include "Object.h"
#include "ObjectMario.h"
#include "event.h"


// call this name?

class Arena
{
public:
	void setFrameTime(int frameTime); // must be set
	double getFrameTime() const;
	Arena(const Arena&) = delete; // Unique Instance
	Arena& operator=(const Arena&) = delete;
	static Arena& getUniqueInstance()
	{
		static Arena arena;
		return arena;
	}
	void addEvent(EventType type, Object* pObject, int wParam, double lParam);
	void collisionDetection(); // Do collisionDetection of every objects in Arena
	void freeFall(); //adjust the object' vy according to gravity if it is in the air in one frameTime_;
	void deleteObject(const Object* pObject);
	void deleteEvent(const Object* pObject);
	void addObject(Object* pObject);
	void move(); // move all objects according to current velocity in one frameTime_;
	void removeOutOfBoundObject();
	void setMarioVx(double vx);
	void setMarioVy(double vy);
	bool getMarioDying() const;
	bool MarioDownToEarth() const;
	double getMarioVx() const;
	double getMarioVy() const;
	double getMarioX() const;
	double getMarioY() const;
	bool getMarioInvisible() const;
	bool getMarioInEvent() const;
	bool isGameOver() const;
	void processEvent();
	~Arena();
	const std::list<Object*>& getObjects() const;
	int getCenterx() const;
	void setCenterx(int centerx);
	int getLevel() const;
	void levelPlus(); // add code for victory screen text here.
	void addScore(int score);
	int getScore() const;
	void addCoin(int coin = 1);
	int getCoin() const;
	bool getMarioShootable() const;
	void MarioShoot();
	
protected:
	std::list<Object*> objects_; //  in accedning order of priority
	Arena(); // Unique Instance
	ObjectMario* mario_;
	std::list<Event> events_;
	bool loseControl_;
	int centerx_;
	int level_;
	int score_;
	int coin_;
	bool pause_;
	double frameTime_;
};
