#pragma once
#include <list>
#include "Object.h"
#include "MovingObject.h"

// call this name?
struct DyingObjectData
{
	Object* data_;
	long long startTime_;
	int duration_;
	DyingObjectData(Object* data, long long startTime, int duration)
	{
		data_ = data;
		startTime_ = startTime;
		duration_ = duration;
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
	void erase(const Object& object);
	void pushBack(MovingObject* object);
	void pushBack(Object* object);
	void move(double time); // move all objects according to current velocity.
	void deleteDyingObject(); // delete the object in queue if the time duration is satisfied.
								// and also delete the object that it's y position is too big.
	MovingObject* getMario() const;
	~Arena();
	const std::list<MovingObject*>& getMovingObjects() const;
	const std::list<Object*>& getStaticObjects() const;
	void pushDyingObjectData(const DyingObjectData& data);
	// delete the objects that flagged as deleted_;
protected:
	std::list<MovingObject*> movingObjects_;
	std::list<Object*> staticObjects_;
	Arena(); // Unique Instance
	MovingObject* mario_;
	std::list<DyingObjectData> dyingObjectData_;
	static const double ACCELARATION;
	static const int LOWEST_POSITION; // the biggest y-position. 
											// The object beyond this position will be deleted in deleteDyingObject(). 
};

