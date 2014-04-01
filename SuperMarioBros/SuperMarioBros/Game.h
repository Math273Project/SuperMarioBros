#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <mmsystem.h>
#include "Graphics.h"
#include "Input.h"
#include "Constants.h"
#include "GameError.h"

///Game will hold all DirectX functionality
class Game
{
public:
	Game();
	~Game();
	//message handler handles all windows messages
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Initialize the game
	// Pre: hwnd is handle to window
	virtual void initialize(HWND hwnd);
	// Call run repeatedly by the main message loop in WinMain
	virtual void run(HWND);
	// Release all reserved video memory so graphics device may be reset
	virtual void releaseAll();
	// Recreate all surfaces and reset all entities
	virtual void resetAll();
	// Delete all reserved memory
	virtual void deleteAll();
	// Render game items
	virtual void renderGame() = 0;
	void exitGame() { PostMessage(hwnd_, WM_DESTROY, 0, 0); }
	virtual void update();
	virtual void collisions();

protected:
	HWND hwnd_; // Window handle
	HRESULT hResult_; // Standard return type
	LARGE_INTEGER timeStart_; // Performance Counter start value
	LARGE_INTEGER timeEnd_; // Performance Counter end value
	LARGE_INTEGER timerFreq_; // Performance Counter frequency
	float frameTime_; // Time required for last frame
	float fps_; // Frames per second
	DWORD sleepTime_; // Milliseconds to sleep between frames
	bool paused_; // True if game is paused
	bool initialized_;
};