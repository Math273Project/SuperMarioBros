#pragma once
#include "Game.h"

/* We can migrate all the functionality of object onto this class
 * Has most of the same funtions as Object anyway plus it will */
class MarioGame : public Game
{
public:
	MarioGame();
	virtual ~MarioGame();

	void update();
	void ai();
	void collisions();
	void render();

private:

};
