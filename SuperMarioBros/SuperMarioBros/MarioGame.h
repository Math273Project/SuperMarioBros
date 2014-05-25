#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Image.h"
#include "Object.h"
#include "MovingObject.h"
#include "Arena.h"

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

	TextureManager marioTexture_;
	TextureManager backgroundTexture1_;
	TextureManager backgroundTexture2_;
	TextureManager goombaTexture_;
	TextureManager floorTexture_;
	TextureManager blocksTexture_;
	TextureManager pipeBigTexture_;
	TextureManager pipeMiddleTexture_;
	TextureManager pipeSmallTexture_;
	TextureManager flagPoleTexture_;
	TextureManager flagTexture_;
	TextureManager turtleTexture_;

	//All the animations are done with an image
	//std::list<Image> staticImages_;

	Image mario_; 
	Image background1_;
	Image background2_;
	Image coin_;
	Image goomba_;
	Image goombaDying_;
	Image block_;
	Image floor_;
	Image brick_;
	Image mushroom_;
	Image powerup_;
	Image question_;
	Image questionBlock_;
	Image pipeBig_;
	Image pipeBig2_;
	Image pipeMiddle_;
	Image pipeSmall_;
	Image flagPole_;
	Image flag_;
	Image turtle_;
	Image turtleSpin_;

	//animations
	void marioRun();
	void marioStop();
	void marioJump();
	void marioDown();  //used to crouch or move down stalks in later levels
	void marioUpgrade();
	void marioDowngrade();
	void marioDeath();

	void level_one();
};
