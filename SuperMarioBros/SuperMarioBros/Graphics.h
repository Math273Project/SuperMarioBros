#pragma once
#define WIN32_LEAN_AND_MEAN
#include <d3d9.h>
#include "constants.h"
#include "gameError.h"

class Graphics
{
public:
	// Constructor
	Graphics();
	// Destructor
	virtual ~Graphics();
	// Releases direct3d and device3d
	void releaseAll();
	// Initialize DirectX graphics
	void initialize(HWND hWnd, int width, int height, bool fullscreen);
	// Display the offscreen backbuffer to the screen
	HRESULT showBackbuffer();
private:
	// DirectX pointers
	LPDIRECT3D9 direct3d_;
	LPDIRECT3DDEVICE9 device3d_;
	D3DPRESENT_PARAMETERS d3dpp_;
	// Other variables
	HRESULT hResult_; // Standard Windows return codes
	HWND hWnd_;   //HANDLE to the window
	bool fullscreen_;  //true if scree is fullscreen, false otherwise
	int width_;  //width of the window
	int height_;   //height of the window
	// (For internal engine use only)
	// Initialize D3D presentation parameters
	void initD3Dpp();
};