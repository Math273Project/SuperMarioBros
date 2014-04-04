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
	LRESULT messageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Initialize the game
	virtual void initialize(HWND hWnd);
	// Call run repeatedly by the main message loop in WinMain
	virtual void run(HWND hWnd);
	// Release all reserved video memory so graphics device may be reset
	virtual void releaseAll();
	// Recreate all surfaces and reset all entities
	virtual void resetAll();
	// Delete all reserved memory
	virtual void deleteAll();
	// Render game items
	virtual void renderGame();
	// Handle lost graphics device
	virtual void handleLostGraphicsDevice();
	// Return pointer to Graphics
	Graphics* getGraphics() { return graphics_; }
	// Return pointer to Input
	//Input* getInput() { return input; }
	//Exit game
	void exitGame() { PostMessage(hWnd_, WM_DESTROY, 0, 0); }
	virtual void update() = 0;
	// Perform AI calculations
	virtual void ai() = 0;
	// Check for collisions
	virtual void collisions() = 0;
	//Render graphics
	virtual void render() = 0;

protected:
	Graphics* graphics_;
	Input* input_;
	HWND hWnd_; // Window handle
	HRESULT hResult_; // Standard return type
	LARGE_INTEGER timeStart_; // Performance Counter start value
	LARGE_INTEGER timeEnd_; // Performance Counter end value
	LARGE_INTEGER timerFreq_; // Performance Counter frequency
	double frameTime_; // Time required for last frame
	double fps_; // Frames per second
	DWORD sleepTime_; // Milliseconds to sleep between frames
	bool paused_; // True if game is paused
	bool initialized_;
};