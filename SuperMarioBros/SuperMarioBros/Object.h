#pragma once
#define WIN32_LEAN_AND_MEAN
#include <list>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <mmsystem.h>

// This class is the base class of all the objects.
enum ObjectType
{
	SMALL_MARIO,
	BIG_MARIO,
	SUPER_MARIO,
	BLOCK,
	FLOWER,
	MUSHROOM,
	FLAT_MUSHROOM,
	COIN,
	ENEMY,
	FLAT_ENEMY,
	QUESTION,
	BRICK,
	BRICK_PIECE,
	POWERUP,
	PIPE
	// etc...
};

enum Direction
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
	NONE
};

class Object
{
public:
	virtual ~Object();
	void setPosition(double x, double y);
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
	bool isEnabled() const;
	bool operator == (const Object& rhs) const;
	virtual void destroy(); // add the object to dyingObject in arena class. 
							// the object will be destroyed in arena class.
							//call it when, example: Mario is killed, Block is destoryed
							// and split to severl pieces or
							//	enemy is killed.
	bool passable() const;

	virtual bool moveable() const;
	virtual ObjectType getType() const = 0;
	virtual int getPriority() const = 0;
	virtual int getDyingDuration() const = 0;
	void adjustPosition(const Object& object, Direction collideDirection); // Used for collision.
protected:
	double x_; 
	double y_;
	int width_;
	int height_;
	bool enabled_;
	bool passable_;
	int id_; // a unique id for this object;
	Object(int id);
	Object(int id, int x, int y);
};

