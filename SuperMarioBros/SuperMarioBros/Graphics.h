#pragma once
#define WIN32_LEAN_AND_MEAN
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include "constants.h"
#include "gameError.h"

class Graphics
{
private:
	// DirectX pointers and stuff
	LPDIRECT3D9 direct3d;
	LPDIRECT3DDEVICE9 device3d;
	D3DPRESENT_PARAMETERS d3dpp;
	// Other variables
	HRESULT result; // Standard Windows return codes
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	// (For internal engine use only. No user serviceable parts inside.)
	// Initialize D3D presentation parameters
	void initD3Dpp();
public:
	// Constructor
	Graphics();
	// Destructor
	virtual ~Graphics();
	// Releases direct3d and device3d
	void releaseAll();
	// Initialize DirectX graphics
	// hw = handle to window
	// width = width in pixels
	// height = height in pixels
	// Fullscreen = true for full screen, false for window
	// Throws GameError on error
	void initialize(HWND hw, int width, int height, bool fullscreen);
	// Display the offscreen backbuffer to the screen
	HRESULT showBackbuffer();
};