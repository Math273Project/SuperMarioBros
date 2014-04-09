#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "GameError.h"


#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif

namespace InputConstants
{
	const int KEYS_ARRAY_LEN = 256;     // size of key arrays

	// what values for clear(), bit flags
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

class Input
{
public:
	Input();
	~Input();
	void initialize(HWND hwnd, bool capture);
	void keyDown(WPARAM);
	void keyUp(WPARAM);
	void keyIn(WPARAM);
	bool isKeyDown(UCHAR vkey) const;
	bool wasKeyPressed(UCHAR vkey) const;
	bool anyKeyPressed() const;
	void clearKeyPress(UCHAR vkey);
	void clear(UCHAR what);
	void clearAll() { clear(InputConstants::KEYS_MOUSE_TEXT); }
	char getCharIn()        { return charIn_; }

private:
	bool keysDown_[InputConstants::KEYS_ARRAY_LEN];// True if specified key is dow
	bool keysPressed_[InputConstants::KEYS_ARRAY_LEN]; // True if specified key was
	// pressed
	char charIn_; // Last character entered
};