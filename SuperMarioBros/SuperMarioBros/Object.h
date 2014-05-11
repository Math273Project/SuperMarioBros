#pragma once
#define WIN32_LEAN_AND_MEAN
#include <list>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <mmsystem.h>
#include "Constants.h"

// This class is the base class of all the objects.
enum ObjectType
{
	MARIO_SMALL,
	MARIO_BIG,
	MARIO_SUPER,
	MARIO_DYING,
	BLOCK,
	FLOWER,
	MUSHROOM,
	MUSHROOM_DYING,
	COIN,
	ENEMY,
	ENEMY_DYING,
	QUESTION,
	BRICK,
	BRICK_DYING,
	POWERUP,
	PIPE_BIG,
	PIPE_MIDDLE,
	PIPE_SMALL,
	TURTLE,
	TURTLE_SPIN,
	BULLET,
	FLOOR,
	FLAG_POLE,
	FLAG,
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
	virtual Direction didCollide(const Object& object) const; // Check if two objects are collide, return a collide direction
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
	void destroy(int delay = 0); // add the object to dyingObject in arena class. 
							// the object will be destroyed in arena class.
							//call it when, example: Mario is killed, Block is destoryed
							// and split to severl pieces or
							//	enemy is killed.
	bool getPassable() const;
	void setPassable(bool passable);
	bool getDying() const;
	virtual ObjectType getType() const = 0;
	virtual int getPriority() const = 0;
	void adjustPosition(const Object& object, Direction collideDirection); // Used for collision.
	int getCurrentFrame() const;
	void setCurrentFrame(int currentFrame);

	virtual double getvx() const;
	virtual double getvy() const;
	virtual Direction getFacingDirection() const;
	virtual void setvx(double vx); // will callsetFacingDirection if the direction of velocity changes;
	virtual void setvy(double vy);
	virtual bool getMoveable() const;
	virtual void setFacingDirection(Direction facingDirection);
	virtual void move(double time);
	virtual bool getGravityAffected() const;
	virtual void setGravityAffected(bool gravityAffected);
	bool getInEvent() const;
	void setInEvent(bool inEvent);
protected:
	int currentFrame_;
	double x_; 
	double y_;
	int width_;
	int height_;
	bool dying_;
	bool enabled_;
	bool passable_;
	bool inEvent_;
	Object(int x, int y);
};

