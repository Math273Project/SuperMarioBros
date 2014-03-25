#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <mmsystem.h>

// This class is the base class of all the objects.

class Object
{
public:
	Object();
	virtual ~Object();
	bool disable();
	bool enable();
	void setPosition(int x, int y);
	virtual bool draw(); 
	virtual bool move(int direction, int distance);
	virtual bool move(int time);
	bool didCollide(const Object& object); // Check if two objects are collide
	virtual bool collide(const);
	
protected:
	enum
	{
		MARIO,
		BLOCK,
		FLOWER,
		MUSHROOM,
				// etc...
	} type;
	int x_;
	int y_;
	int vx_;
	int vy_;
	int width_;
	int height_;
	bool enabled_;
	bool passable_; // example: block, not passable. coins passable.
	int priority_; // The object with higher priority will be drawn at the top of the object with low priority.
					// Change a name?
	LPD3DXSPRITE sprite_; // What is shown on the screen. The typename should not char*, but I forgot what it should be.

};
