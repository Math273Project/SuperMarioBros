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
	void clearTextIn() { textIn_.clear(); }
	std::string getTextIn() { return textIn_; }
	char getCharIn()        { return charIn_; }
	void mouseIn(LPARAM);
	void mouseRawIn(LPARAM);

	void setMouseLButton(bool b) { mouseLButton_ = b; }
	void setMouseMButton(bool b) { mouseMButton_ = b; }
	void setMouseRButton(bool b) { mouseRButton_ = b; }
	void setMouseXButton(WPARAM wParam) { mouseX1Button_ = (wParam & MK_XBUTTON1) ? true : false;
										  mouseX2Button_ = (wParam & MK_XBUTTON2) ? true : false; }

	int  getMouseX()        const { return mouseX_; }
	int  getMouseY()        const { return mouseY_; }
	int  getMouseRawX()     const { return mouseRawX_; }
	int  getMouseRawY()     const { return mouseRawY_; }
	bool getMouseLButton()  const { return mouseLButton_; }
	bool getMouseMButton()  const { return mouseMButton_; }
	bool getMouseRButton()  const { return mouseRButton_; }
	bool getMouseX1Button() const { return mouseX1Button_; }
	bool getMouseX2Button() const { return mouseX2Button_; }

private:
	bool keysDown_[InputConstants::KEYS_ARRAY_LEN];// True if specified key is dow
	bool keysPressed_[InputConstants::KEYS_ARRAY_LEN]; // True if specified key was
	// pressed
	std::string textIn_; // User entered text
	char charIn_; // Last character entered
	bool newLine_; // True on start of new line
	int mouseX_, mouseY_; // Mouse screen coordinates
	int mouseRawX_, mouseRawY_; // High-definition mouse data
	RAWINPUTDEVICE Rid_[1]; // For high-definition mouse
	bool mouseCaptured_; // True if mouse captured
	bool mouseLButton_; // True if left mouse button down
	bool mouseMButton_; // True if middle mouse button down
	bool mouseRButton_; // True if right mouse button down
	bool mouseX1Button_; // True if X1 mouse button down
	bool mouseX2Button_; // True if X2 mouse button down
};