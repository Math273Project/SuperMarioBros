#include "Input.h"

Input::Input()
{
	// Clear key down array
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
		keysDown_[i] = false;
	// Clear key pressed array
	for (size_t i = 0; i < InputConstants::KEYS_ARRAY_LEN; i++)
		keysPressed_[i] = false;
	newLine_ = true; // Start new line
	textIn_ = ""; // Clear textIn
	charIn_ = 0; // Clear charIn
	// Mouse data
	mouseX_ = 0; // Screen X
	mouseY_ = 0; // Screen Y
	mouseRawX_ = 0; // High-definition X
	mouseRawY_ = 0; // High-definition Y
	mouseLButton_ = false; // True if left mouse button is down
	mouseMButton_ = false; // True if middle mouse button is down
	mouseRButton_ = false; // True if right mouse button is down
	mouseX1Button_ = false; // True if X1 mouse button is down
	mouseX2Button_ = false; // True if X2 mouse button is down
}

Input::~Input()
{
	if (mouseCaptured_)
	{
		ReleaseCapture();
	}
}

void Input::initialize(HWND hWnd, bool capture)
{
	try{
		mouseCaptured_ = capture;
		// Register high-definition mouse
		Rid_[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid_[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid_[0].dwFlags = RIDEV_INPUTSINK;
		Rid_[0].hwndTarget = hWnd;
		RegisterRawInputDevices(Rid_, 1, sizeof(Rid_[0]));
		if (mouseCaptured_)
		{
			SetCapture(hWnd); // Capture mouse
		}
	}
	catch (...)
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing input system"));
	}
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
	if (newLine_)                            // if start of new line
	{
		textIn_.clear();
		newLine_ = false;
	}

	if (wParam == '\b')                     // if backspace
	{
		if (textIn_.length() > 0)             // if characters exist
			textIn_.erase(textIn_.size() - 1);  // erase last character entered
	}
	else
	{
		textIn_ += wParam;                   // add character to textIn
		charIn_ = wParam;                    // save last char entered
	}

	if ((char)wParam == '\r')               // if return    
		newLine_ = true;                     // start new line
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
	if (what & InputConstants::MOUSE)           // if clear mouse
	{
		mouseX_ = 0;
		mouseY_ = 0;
		mouseRawX_ = 0;
		mouseRawY_ = 0;
	}
	if (what & InputConstants::TEXT_IN)
		clearTextIn();
}

void Input::mouseIn(LPARAM lParam)
{
	mouseX_ = GET_X_LPARAM(lParam);
	mouseY_ = GET_Y_LPARAM(lParam);
}

void Input::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
		lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX_ = raw->data.mouse.lLastX;
		mouseRawY_ = raw->data.mouse.lLastY;
	}
}