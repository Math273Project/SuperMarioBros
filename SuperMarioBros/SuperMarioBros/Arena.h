#pragma once
#include <vector>
#include "Object.h"
#include "MovingObject.h"

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
	void collisionDetection(); // Do collisionDetection of every objects in Arena
	void freeFall(int time); //adjust the object' vy according to gravity if it is in the air
	void remove(const Object& object);
	void pushBack(MovingObject* object);
	void pushBack(Object* object);
	void move(int time); // move all objects according to current velocity.
	void deleteObject(); // call all objects' trydelete()
	// delete the objects that flagged as deleted_;
protected:
	std::vector<MovingObject*> movingObjects_;
	std::vector<Object*> staticObjects_;
	Arena(); // Unique Instance
	static const double ACCELARATION;
};

const double Arena::ACCELARATION = 9.8;