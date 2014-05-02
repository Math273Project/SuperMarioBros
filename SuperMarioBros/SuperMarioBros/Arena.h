#pragma once
#include <list>
#include "Object.h"
#include "MovingObject.h"


// call this name?
struct DyingObjectData
{
	Object* data;
	long long startTime;
	int duration;
	DyingObjectData(Object* newData, long long newStartTime, int newDuration)
	{
		data = newData;
		startTime = newStartTime;
		duration = newDuration;
	}
};

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
	void collisionDetection(); // Do collisionDetection of every objects in Arena
	void freeFall(double time); //adjust the object' vy according to gravity if it is in the air
	void erase(const Object* object);
	void pushBack(MovingObject* object);
	void pushBack(Object* object);
	void move(double time); // move all objects according to current velocity.
	void deleteDyingObject(); // delete the object in queue if the time duration is satisfied.
								// and also delete the object that it's y position is too big.

	void setMarioVx(double vx);
	void setMarioVy(double vy);
	bool MarioDownToEarth() const;
	double getMarioVx() const;
	double getMarioVy() const;
	double getMarioX() const;
	double getMarioY() const;
	bool isGameOver() const;
	~Arena();
	const std::list<MovingObject*>& getMovingObjects() const;
	const std::list<Object*>& getStaticObjects() const;
	void pushDyingObjectData(const DyingObjectData& data);
	// delete the objects that flagged as deleted_;
protected:
	std::list<MovingObject*> movingObjects_; // in accending order of priority.
	std::list<Object*> staticObjects_; //  in accedning order of priority
	Arena(); // Unique Instance
	MovingObject* mario_;
	std::list<DyingObjectData> dyingObjectData_;
	
};

