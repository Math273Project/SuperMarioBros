#pragma once

// Directx constants

const double PI = 3.14159265;
const double FRAME_RATE = 200.0;
const double MIN_FRAME_RATE = 10.0;
const double MIN_FRAME_TIME = 1.0 / FRAME_RATE;
const double MAX_FRAME_TIME = 1.0 / MIN_FRAME_RATE;

const double GRAVITY = 400;
const double LOWEST_POSITION = 1500; // the biggest y-position. 
									// The object beyond this position will be deleted in deleteDyingObject(). 
// Texture constants

const char BACKGROUND1_TEXTURE[] = "Textures\\Background1.bmp"; 
const char BACKGROUND2_TEXTURE[] = "Textures\\Background2.bmp";
const char GOOMBA_TEXTURE[] = "Textures\\Enemies.bmp";
const char GOOMBA_2_TEXTURE[] = "Textures\\Enemies2.bmp";
const char MARIO_TEXTURE[] = "Textures\\Robot_Mario.bmp";
const char BLOCKS[] = "Textures\\Blocks.bmp";
const char FLOOR_TEXTURE[] = "Textures\\floor.bmp";
const char PIPE_BIG_TEXTURE[] = "Textures\\Pipe_Big.bmp";
const char PIPE_MIDDLE_TEXTURE[] = "Textures\\Pipe_Middle.bmp";
const char PIPE_SMALL_TEXTURE[] = "Textures\\Pipe_Small.bmp";
const char FLAG_POLE_TEXTURE[] = "Textures\\Flag_Pole.bmp";
const char FLAG_TEXTURE[] = "Textures\\Flag.bmp";
const char TURTLE_TEXTURE[] = "Textures\\turtles.bmp";

// Sprite constants

// Big Mario
const int  MARIO_START_FRAME = 0;            // starting frame of Mario animation
const int  MARIO_END_FRAME = 7;              // last frame of Mario animation
const double MARIO_ANIMATION_DELAY = 0.25;    // time between frames of Mario animation
const int  MARIO_COLS = 7;                   // Mario texture has 7 columns
const double MARIO_SPEED = 400; // pixels per second (velocity)
const double MARIO_SCALE = 1.00;

//Super Mario

const int MARIO_SUPER_START_FRAME = 11;
const int MARIO_SUPER_END_FRAME = 21;
const int MARIO_SUPER_COLS = 11;


// Small Mario
const int MARIO_SMALL_START_FRAME = 36;
const int MARIO_SMALL_END_FRAME = 44;
const double MARIO_SMALL_ANIMATION_DELAY = .15; //should look like its moving faster
const int MARIO_SMALL_COLS = 9;
const double MARIO_DYING_SPEED = 100.0;
const double MARIO_SMALL_SCALE = 1.00;

const int BLOCK_PRIORITY = 5;
const int BLOCK_WIDTH = 50;
const int BLOCK_HEIGHT = 50;

const int BRICK_DYING_DURATION = 500;
const int BRICK_PRIORITY = 5;
const int BRICK_WIDTH = 50;
const int BRICK_HEIGHT = 50;

const int BULLET_DYING_DURATION = 50;
const int BULLET_PRIORITY = 50;
const int BULLET_WIDTH = 50;
const int BULLET_HEIGHT = 50;

const int COIN_DYING_DURATION = 500;
const int COIN_PRIORITY = 5;
const int COIN_WIDTH = 50;
const int COIN_HEIGHT = 50;

const int GOOMBA_DYING_DURATION = 500;
const int GOOMBA_PRIORITY = 5;
const int GOOMBA_WIDTH = 50;
const int GOOMBA_HEIGHT = 50;
const int GOOMBA_COLS = 2;
const int GOOMBA_DYING_WIDTH = 50;
const int GOOMBA_DYING_HEIGHT = 33;

const int FLAG_PRIORITY = 5;
const int FLAG_WIDTH = 50;
const int FLAG_HEIGHT = 50;

const int FLOWER_PRIORITY = 5;
const int FLOWER_WIDTH = 50;
const int FLOWER_HEIGHT = 50;

const int FLAG_POLE_PRIORITY = 4;
const int FLAG_POLE_WIDTH = 25;
const int FLAG_POLE_HEIGHT = 470;

const int FLOOR_PRIORITY = 5;
const int FLOOR_WIDTH = 50;
const int FLOOR_HEIGHT = 100;

const int MARIO_DYING_DURATION = 10000;
const int MARIO_PRIORITY = INT_MAX;
const int MARIO_SMALL_WIDTH = 50;
const int MARIO_SMALL_HEIGHT = 50;
const int MARIO_BIG_WIDTH = 50;
const int MARIO_BIG_HEIGHT = 100;
const int MARIO_SUPER_WIDTH = 50;
const int MARIO_SUPER_HEIGHT = 100;

const int MUSHROOM_DYING_DURATION = 500;
const int MUSHROOM_PRIORITY = 5;
const int MUSHROOM_WIDTH = 50;
const int MUSHROOM_HEIGHT = 50;
const int MUSHROOM_DYING_WIDTH = 50;
const int MUSHROOM_DYING_HEIGHT = 50;

const int PIPE_PRIORITY = 5;
const int PIPE_WIDTH = 100;
const int PIPE_BIG_HEIGHT = 200;
const int PIPE_MIDDLE_HEIGHT = 150;
const int PIPE_SMALL_HEIGHT = 100;

const int POWERUP_DYING_DURATION = 500;
const int POWERUP_PRIORITY = 5;
const int POWERUP_WIDTH = 50;
const int POWERUP_HEIGHT = 50;

const int QUESTION_DYING_DURATION = 500;
const int QUESTION_PRIORITY = INT_MAX - 1;
const int QUESTION_WIDTH = 50;
const int QUESTION_HEIGHT = 50;

const int TURTLE_DYING_DURATION = 500;
const int TURTLE_PRIORITY = 5;
const int TURTLE_WIDTH = 50;
const int TURTLE_HEIGHT = 75;
const int TURTLE_SPIN_WIDTH = 50;
const int TURTLE_SPIN_HEIGHT = 47;

const int VICTORY_SPOT_PRIORITY = 0;
const int VICTORY_SPOT_WIDTH = 50;
const int VICTORY_SPOT_HEIGHT = 50;
const int VICTORY_SPOT_DYING_DURATION = 0;
//constants

//const int MUSHROOM_RED_

const char CLASS_NAME[] = "Super Mario Bros";
const char WINDOW_NAME[] = "Super Mario Bros";
const int GAME_WIDTH = 1280;      // width of game in pixels
const int GAME_HEIGHT = 720;      // height of game in pixels


// key mappings

const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ENTER_KEY = VK_RETURN;       // Enter key used for pause
const UCHAR MOVE_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR MOVE_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR MOVE_UP_KEY = VK_UP;       // up arrow
const UCHAR MOVE_DOWN_KEY = VK_DOWN;     // down arrow
