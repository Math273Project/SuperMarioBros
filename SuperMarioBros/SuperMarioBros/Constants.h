#pragma once

// Directx constants

const double PI = 3.14159265;
const double FRAME_RATE = 200.0;
const double MIN_FRAME_RATE = 10.0;
const double MIN_FRAME_TIME = 1.0 / FRAME_RATE;
const double MAX_FRAME_TIME = 1.0 / MIN_FRAME_RATE;

// Texture constants

const char BACKGROUND_START[] = "Textures\\Level_One_resized.bmp"; //The background needs to be broken down
const char MARIO_TEXTURE[] = "Textures\\Robot_Mario.bmp";
const char BLOCKS[] = "Textures\\Blocks.bmp";
const char FLOOR_TEXTURE[] = "Textures\\floor.bmp";

// Sprite constants

// Big and Super Mario
const int  MARIO_START_FRAME = 0;            // starting frame of Mario animation
const int  MARIO_END_FRAME = 7;              // last frame of Mario animation
const double MARIO_ANIMATION_DELAY = 0.25;    // time between frames of Mario animation
const int  MARIO_COLS = 7;                   // Mario texture has 7 columns
const int TEXTURE_WIDTH = 72;     //standard size of entity textures
const int TEXTURE_HEIGHT = 144;
//const int BIG_MARIO_WIDTH = 72;     //standard size of entity textures
//const int BIG_MARIO_HEIGHT = 144;
const double MARIO_SPEED = 200.0; // pixels per second (velocity)
const double MARIO_SCALE = 1.00;

// Small Mario
const int MARIO_SMALL_START_FRAME = 0;
const int MARIO_SMALL_END_FRAME = 1; //change later
const double MARIO_SMALL_ANIMATION_DELAY = 0.1; //should look like its moving faster
const int MARIO_SMALL_COLS = 6;
const double MARIO_SMALL_SPEED = 200.0;
const double MARIO_SMALL_SCALE = .25;

const int BLOCK_DYING_DURATION = 500;
const int BLOCK_PRIORITY = 5;
const int BLOCK_WIDTH = 72;
const int BLOCK_HEIGHT = 72;

const int BRICK_DYING_DURATION = 500;
const int BRICK_PRIORITY = 5;
const int BRICK_WIDTH = 32;
const int BRICK_HEIGHT = 32;
const int BRICK_DYING_WIDTH = 32;
const int BRICK_DYING_HEIGHT = 32;

const int BULLET_DYING_DURATION = 32;
const int BULLET_PRIORITY = 32;
const int BULLET_WIDTH = 32;
const int BULLET_HEIGHT = 32;

const int COIN_DYING_DURATION = 500;
const int COIN_PRIORITY = 5;
const int COIN_WIDTH = 32;
const int COIN_HEIGHT = 32;

const int ENEMY_DYING_DURATION = 500;
const int ENEMY_PRIORITY = 5;
const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 32;
const int ENEMY_DYING_WIDTH = 32;
const int ENEMY_DYING_HEIGHT = 32;

const int FLOOR_DYING_DURATION = 500;
const int FLOOR_PRIORITY = 5;
const int FLOOR_WIDTH = 51;
const int FLOOR_HEIGHT = 100;

const int MARIO_DYING_DURATION = 500;
const int MARIO_PRIORITY = INT_MAX;
const int MARIO_SMALL_WIDTH = 72;
const int MARIO_SMALL_HEIGHT = 144;
const int MARIO_BIG_WIDTH = 72;
const int MARIO_BIG_HEIGHT = 144;
const int MARIO_SUPER_WIDTH = 72;
const int MARIO_SUPER_HEIGHT = 144;

const int MUSHROOM_DYING_DURATION = 500;
const int MUSHROOM_PRIORITY = 5;
const int MUSHROOM_WIDTH = 32;
const int MUSHROOM_HEIGHT = 32;
const int MUSHROOM_DYING_WIDTH = 32;
const int MUSHROOM_DYING_HEIGHT = 32;

const int PIPE_DYING_DURATION = 500;
const int PIPE_PRIORITY = 5;
const int PIPE_WIDTH = 32;
const int PIPE_HEIGHT = 32;

const int POWERUP_DYING_DURATION = 500;
const int POWERUP_PRIORITY = 5;
const int POWERUP_WIDTH = 32;
const int POWERUP_HEIGHT = 32;

const int QUESTION_DYING_DURATION = 500;
const int QUESTION_PRIORITY = 5;
const int QUESTION_WIDTH = 32;
const int QUESTION_HEIGHT = 32;

const int TURTLE_DYING_DURATION = 500;
const int TURTLE_PRIORITY = 5;
const int TURTLE_WIDTH = 32;
const int TURTLE_HEIGHT = 32;
const int TURTLE_SPIN_WIDTH = 32;
const int TURTLE_SPIN_HEIGHT = 32;
//constants

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
