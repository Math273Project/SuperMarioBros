#include "Input.h"

Input::Input()
{
	// Clear key down array
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
	{
		keysDown_[i] = false;
	}
	// Clear key pressed array
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
	{
		keysPressed_[i] = false;
	}
	charIn_ = 0; // Clear charIn
}

Input::~Input()
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
	if (wParam == VK_ESCAPE)
	{
		PostQuitMessage(0);
	}
}

bool Input::isKeyDown(UCHAR virtualkey) const
{
	if (virtualkey < InputConstants::KEYS_ARRAY_LEN)
	{
		return keysDown_[virtualkey];
	}
	else
	{
		return false;
	}
}

bool Input::wasKeyPressed(UCHAR virtualkey) const
{
	if (virtualkey < InputConstants::KEYS_ARRAY_LEN)
		return keysPressed_[virtualkey];
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

void Input::clearKeyPress(UCHAR virtualkey)
{
	if (virtualkey < InputConstants::KEYS_ARRAY_LEN)
		keysPressed_[virtualkey] = false;
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