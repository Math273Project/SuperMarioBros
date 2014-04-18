#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <mmsystem.h>

// This class is the base class of all the objects.
enum ObjectType
{
	SMALLMARIO,
	BIGMARIO,
	SUPERMARIO,
	BLOCK,
	FLOWER,
	MUSHROOM,
	COIN,
	ENEMY,
	QUESTION,
	BRICK,
	POWERUP,
	PIPE
	// etc...
};

enum Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Object
{
public:
	virtual ~Object();
	void setPosition(int x, int y);
	void move(int time); //unit: millisecond
	Direction didCollide(const Object& object) const; // Check if two objects are collide									// return a collide direction
	bool onTop(const Object& object) const; // check if this object is on the top of another object;
	virtual void collide(const Object& object, Direction collideDirection) = 0;
	double getx() const;
	double gety() const;
	int getWidth() const;
	int getHeight() const;
	bool getEnabled() const;
	int getId() const;
	void setx(double x);
	void sety(double y);
	void setWidth(int width);
	void setHeight(int height);
	void disable();
	void enable();
	bool operator == (const Object& rhs) const;
	virtual void destroy(); // destroy the object, call it when, example: Mario is killed, Block is destoryed
							// and split to severl pieces or
							//	enemy is killed.
							// Need more work for this function
	virtual void tryDelete(); // set deleted_ to true if certain condition is satisfied.
	bool passable() const;
	bool deleted() const;
	virtual bool moveable() const;
	virtual ObjectType getType() const = 0;
	virtual int getPriority() const = 0;
protected:
	double x_; 
	double y_;
	int width_;
	int height_;
	bool enabled_;
	bool passable_;
	bool deleted_; // if it is true, delete the object from arena
	int id_; // a unique id for this object;
	Object(int id);
	Object(int id, int x, int y);
};
