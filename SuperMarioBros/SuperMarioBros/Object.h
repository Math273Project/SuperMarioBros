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
	~Object();
	bool disable();
	bool enable();
	void setPosition(int x, int y);
	virtual bool draw(); 
	virtual bool move(int direction, int distance);
	bool isCollide(const Object& object);
	bool virtual dosomething(); // Check every other Objects position or velocity and do sth according to it
								// Change name?
	
protected:
	int x_;
	int y_;
	int vx_;
	int vy_;
	int width_; //width of the sprite
	int height_; //height of the sprite
	bool isEnabled_; // determines whether the sprite should draw
	bool isPassable_; // example: block, not passable. coins passable.
	int priority_; // The object with higher priority will be drawn at the top of the object with low priority.
					// Change a name?
	LPD3DXSPRITE sprite_; // used to draw the sprites to the screen

};