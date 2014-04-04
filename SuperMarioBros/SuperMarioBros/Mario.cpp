#include "Mario.h"

Mario::Mario() : Object(MARIO, 0, INT_MAX, true) // id 0, highest priority
{
	x_ = 0;
	y_ = 0;
	vx_ = 0;
	vy_ = 0;
	width_ = 32;
	height_ = 32;
	enabled_ = true;
	facingDirection_ = RIGHT;
	initializeSprite(0, 0);

	// need sprite
}