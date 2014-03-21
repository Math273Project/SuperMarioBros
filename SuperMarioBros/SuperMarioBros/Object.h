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
	Object();
	bool inVisible(); // return true if object changed to invisible. If it is originally invisible, return false.
	bool Visible();
	virtual void draw();
	virtual void move(int direction);
	
protected:
	int x;
	int y;
	bool isVisible;
};