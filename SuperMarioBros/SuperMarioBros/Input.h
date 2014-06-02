#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "GameError.h"

namespace InputConstants
{
	const int KEYS_ARRAY_LEN = 256;     // size of key arrays

	// what values for clear(), bit flags
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR KEYS = KEYS_DOWN + KEYS_PRESSED;
}

class Input
{
public:
	Input();
	~Input();
	void keyDown(WPARAM);
	void keyUp(WPARAM);
	void keyIn(WPARAM);
	bool isKeyDown(UCHAR virtualkey) const;
	bool wasKeyPressed(UCHAR virtualkey) const;
	bool anyKeyPressed() const;
	void clearKeyPress(UCHAR virtualkey);
	void clear(UCHAR what);
	void clearAll() { clear(InputConstants::KEYS); }
	char getCharIn() { return charIn_; }

private:
	bool keysDown_[InputConstants::KEYS_ARRAY_LEN];// True if specified key is down
	bool keysPressed_[InputConstants::KEYS_ARRAY_LEN]; // True if specified key was pressed
	char charIn_; // Last character entered
};
