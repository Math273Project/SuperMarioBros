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

	//Unique instance: Arena has all the movement and collision in the game
	//Need to take all the results and update image based on the frametime_
	Arena& arena = Arena::getUniqueInstance();

	//ALL textures we need to load

	//std::list<TextureManager> textures_;
	TextureManager marioTexture_;
	TextureManager backgroundTexture_;
	TextureManager enemyTexture_;
	TextureManager floorTexture_;
	TextureManager blocksTexture_;
	TextureManager pipeBigTexture_;
	TextureManager pipeMiddleTexture_;
	TextureManager pipeSmallTexture_;
	TextureManager flagPoleTexture_;
	TextureManager flagTexture_;

	//All the animations are done with an image
	//std::list<Image> images_;
	Image mario_; 
	Image background_;
	Image coin_;
	Image enemy_;
	Image block_;
	Image floor_;
	Image brick_;
	Image mushroom_;
	Image powerup_;
	Image question_;
	Image pipeBig_;
	Image pipeMiddle_;
	Image pipeSmall_;
	Image flagPole_;
	Image flag_;


	int centerx_;

	//animations
	void MarioRun();
	void MarioStop();
	void MarioJump();
	void MarioDown();  //used to crouch or move down stalks in later levels
	void MarioUpgrade();
	void MarioDowngrade();

	void level_one();
};
