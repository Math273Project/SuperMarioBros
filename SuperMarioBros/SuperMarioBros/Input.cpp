#include "Input.h"

Input::Input()
{
	// Clear key down array
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
		keysDown_[i] = false;
	// Clear key pressed array
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
		keysPressed_[i] = false;
	charIn_ = 0; // Clear charIn
}

Input::~Input()
{
}

void Input::initialize(HWND hWnd, bool capture)
{
}

void Input::keyDown(WPARAM wParam)
{
	// Make sure key code is within buffer range
	if (wParam < InputConstants::KEYS_ARRAY_LEN)
	{
		keysDown_[wParam] = true; // Update keysDown array
		// Key has been pressed, erased by clear()
		keysPressed_[wParam] = true; // Update keysPressed array
	}
}

void Input::keyUp(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < InputConstants::KEYS_ARRAY_LEN)
		// update state table
		keysDown_[wParam] = false;
}

void Input::keyIn(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	case 'a':  //move left

		break;
	case 's':   //move down

		break;
	case 'd':   //move right

		break;
	case 'w':   //move up

		break;
	case 'j':  //use as "A" button
		
		break;
	case 'k':  //use as "B" button

		break;
		//case "enter" : used for select
		//need case for 
	}
}

bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < InputConstants::KEYS_ARRAY_LEN)
	{
		return keysDown_[vkey];
	}
	else
	{
		return false;
	}
}

bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < InputConstants::KEYS_ARRAY_LEN)
		return keysPressed_[vkey];
	else
		return false;
}

bool Input::anyKeyPressed() const
{
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
	if (keysPressed_[i] == true)
		return true;
	return false;
}

void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < InputConstants::KEYS_ARRAY_LEN)
		keysPressed_[vkey] = false;
}

void Input::clear(UCHAR what)
{
	if (what & InputConstants::KEYS_DOWN)       // if clear keys down
	{
		for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
			keysDown_[i] = false;
	}
	if (what & InputConstants::KEYS_PRESSED)    // if clear keys pressed
	{
		for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
			keysPressed_[i] = false;
	}
}