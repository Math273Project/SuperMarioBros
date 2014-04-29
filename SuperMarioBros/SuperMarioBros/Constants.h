#pragma once
//directx constants

const double PI = 3.14159265;
const double FRAME_RATE = 200.0;
const double MIN_FRAME_RATE = 10.0;
const double MIN_FRAME_TIME = 1.0 / FRAME_RATE;
const double MAX_FRAME_TIME = 1.0 / MIN_FRAME_RATE;

//Sprite constants

const int  MARIO_START_FRAME = 0;            // starting frame of Mario animation
const int  MARIO_END_FRAME = 7;              // last frame of Mario animation
const double MARIO_ANIMATION_DELAY = 0.25;    // time between frames of Mario animation
const int  MARIO_COLS = 7;                   // Mario texture has 7 columns
const int TEXTURE_WIDTH = 72;     //standard size of entity textures
const int TEXTURE_HEIGHT = 144;
const double MARIO_SPEED = 100.0; // pixels per second
const double MARIO_SCALE = 1.0;

//constants

const char CLASS_NAME[] = "Super Mario Bros";
const char WINDOW_NAME[] = "Super Mario Bros";
const int GAME_WIDTH = 1280;      // width of game in pixels
const int GAME_HEIGHT = 720;      // height of game in pixels


// key mappings

const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ENTER_KEY = VK_RETURN;       // Enter key used for pause
const UCHAR MOVE_LEFT_KEY = 'a';     // left arrow
const UCHAR MOVE_RIGHT_KEY = 'd';    // right arrow
const UCHAR MOVE_UP_KEY = 'w';       // up arrow
const UCHAR MOVE_DOWN_KEY = 's';     // down arrow
