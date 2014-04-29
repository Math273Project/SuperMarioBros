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

// Sprite constants

// Big and Super Mario
const int  MARIO_START_FRAME = 0;            // starting frame of Mario animation
const int  MARIO_END_FRAME = 7;              // last frame of Mario animation
const double MARIO_ANIMATION_DELAY = 0.25;    // time between frames of Mario animation
const int  MARIO_COLS = 7;                   // Mario texture has 7 columns
const int TEXTURE_WIDTH = 72;     //standard size of entity textures
const int TEXTURE_HEIGHT = 144;
const int BIG_MARIO_WIDTH = 72;     //standard size of entity textures
const int BIG_MARIO_HEIGHT = 144;
const double MARIO_SPEED = 100.0; // pixels per second
const double MARIO_SCALE = 1.0;

// Small Mario
const int SMALL_MARIO_START_FRAME = 0;
const int SMALL_MARIO_END_FRAME = 1; //change later
const double SMALL_MARIO_ANIMATION_DELAY = 0.1; //should look like its moving faster
const int SMALL_MARIO_COLS = 6;
const int SMALL_MARIO_WIDTH = 72;
const int SMALL_MARIO_HEIGHT = 72;
const double SMALL_MARIO_SPEED = 100.0;
const double SMALL_MARIO_SCALE = 1.0;


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
