#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Image.h"
//All necessary object headers will go here!

/* We can migrate all the functionality of object onto this class
 * Has most of the same funtions as Object anyway*/

class MarioGame : public Game
{
public:
	MarioGame();
	virtual ~MarioGame();

	void initialize(HWND hWnd, bool fullscreen);

	void update();
	void render();

	void releaseAll();
	void resetAll();
private:
	//ALL textures we need to draw
	TextureManager marioTexture_;
	TextureManager backgroundTexture_;

	//All the animations are done with an image
	Image mario_; 
	Image background_;
};
