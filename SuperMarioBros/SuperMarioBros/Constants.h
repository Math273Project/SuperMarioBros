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
const double MARIO_ANIMATION_DELAY = 0.2;    // time between frames of Mario animation
const int  MARIO_COLS = 7;                   // Mario texture has 7 columns
const int TEXTURE_WIDTH = 32;     //standard size of entity textures
const int TEXTURE_HEIGHT = 64;

//constants

const char CLASS_NAME[] = "Super Mario Bros";
const char WINDOW_NAME[] = "Super Mario Bros";
const int GAME_WIDTH = 1280;      // width of game in pixels
const int GAME_HEIGHT = 720;      // height of game in pixels
