
#pragma once
#include <vector>
#include "Object.h"

// call this name?
class Arena
{
	Arena(const Arena&) = delete; // Unique Instance
	Arena& operator=(const Arena&) = delete;
	static Arena& getUniqueInstance()
	{
		static Arena arena;
		return arena;
	}
	void collisionDetection(); // Do collisionDetection of every objects in Arena
	void gravityDetection();
	void remove(const Object& object);
	void pushBack(const Object& object);
protected:
	std::vector<Object> movingObjects_, staticObjects_;
	Arena(); // Unique Instance
};
