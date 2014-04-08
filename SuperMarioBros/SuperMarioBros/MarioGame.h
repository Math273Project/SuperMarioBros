#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Image.h"

/* We can migrate all the functionality of object onto this class
 * Has most of the same funtions as Object anyway plus it will */
class MarioGame : public Game
{
public:
	MarioGame();
	virtual ~MarioGame();

	void initialize(HWND hWnd, bool fullscreen);

	// Game will made non pure vurtual later 
	void update();    
	void ai();
	void collisions();
	void render();

	void releaseAll();
	void resetAll();
private:
	TextureManager marioTexture_; // Texture that holds all mario movements
	Image mario_;                 // Draws the animation of mario movements
};
