#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Image.h"
#include "Object.h"
#include "MovingObject.h"
#include "Arena.h"

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

	//std::list<TextureManager> textures_;
	TextureManager marioTexture_;
	TextureManager backgroundTexture_;
	Arena& arena = Arena::getUniqueInstance();
	TextureManager enemyTexture_;
	TextureManager blocksTexture_;
	//All the animations are done with an image
	//std::list<Image> images_;
	Image mario_; 
	Image background_;
	Image enemy_;
	Image block_;

	int centerx_;
};
