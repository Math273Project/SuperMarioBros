// To store the information of every object
#include <vector>
#include "Object.h"
class Arena
{
	Arena() = delete; // Unique Instance
	Arena(const Arena&) = delete; // Unique Instance
	Arena& operator=(const Arena&) = delete;
	static Arena& getUniqueInstance()
	{
		static Arena arena;
		return arena;
	}
	Object** FindCollide(const Object object, int& collisionNumber) const; // array of pointer to the objects

protected:
	std::vector<Object> data_;
};