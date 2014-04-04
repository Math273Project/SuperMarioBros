#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <mmsystem.h>

// This class is the base class of all the objects.
enum ObjectType
{
	MARIO,
	BLOCK,
	FLOWER,
	MUSHROOM,
	COIN
	// etc...
};

enum FacingDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};


class Object
{
public:
	virtual ~Object();
	void setPosition(int x, int y);
	void draw(); //should call the game update();
	// Make Mario always stand in the middle of screen.
	void move(int time);
	bool didCollide(const Object& object) const; // Check if two objects are collide
	virtual void collide(const Object& object);

	int getx() const;
	int gety() const;
	int getvx() const;
	int getvy() const;
	int getWidth() const;
	int getHeight() const;
	bool getEnabled() const;
	FacingDirection getFacingDirection() const;
	ObjectType getType() const;
	int getId() const;
	int getPriority() const;
	bool moveable() const;
	LPD3DXSPRITE getSprite() const;


	void setx(int x);
	void sety(int y);
	void setvx(int vx);
	void setvy(int vy);
	void setWidth(int width);
	void setHeight(int height);
	void disable();
	void enable();
	virtual void setFacingDirection(FacingDirection facingDirection); // Change sprite at the same time
	void setSprite(LPD3DXSPRITE sprite);


protected:
	int x_;
	int y_;
	int vx_;
	int vy_;
	int width_;
	int height_;
	bool enabled_;
	FacingDirection facingDirection_;
	const ObjectType type_;
	const int id_; // a unique id for this object;
	const int priority_; // The object with higher priority will be drawn at the top of the object with low priority.
	// Change a name?
	const bool moveable_;
	LPD3DXSPRITE sprite_; // used to draw the sprites to the screen
	Object(ObjectType type, int id, int priority, bool moveable);
};