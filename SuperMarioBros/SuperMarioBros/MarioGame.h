#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Image.h"
#include "Object.h"
#include "MovingObject.h"
#include "Arena.h"
<<<<<<< HEAD
#include "ObjectMario.h"
#include "ObjectBlock.h"
=======

>>>>>>> d80733cea5cb2598f2253f1868fa276825ff4add
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

	//Unique instance: Arena has all the movement and collision in the game
	//Need to take all the results and update image based on the frametime_
	Arena& arena = Arena::getUniqueInstance();

	//ALL textures we need to load

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
};
