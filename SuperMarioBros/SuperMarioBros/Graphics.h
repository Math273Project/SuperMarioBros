#pragma once
#define WIN32_LEAN_AND_MEAN
#include <d3d9.h>
#include <d3dx9tex.h>
#include "constants.h"
#include "gameError.h"

// Properties required by Graphics::drawSprite to draw a sprite
struct SpriteData
{
	int         width;      // width of sprite in pixels
	int         height;     // height of sprite in pixels
	double       x;          // screen location (top left corner of sprite)
	double       y;
	double       scale;      // <1 smaller, >1 bigger
	double       angle;      // rotation angle in radians
	RECT        rect;       // used to select an image from a larger texture
	LPDIRECT3DTEXTURE9 texture;// pointer to texture
	bool        flipHorizontal; // true to flip sprite horizontally (mirror)
	bool        flipVertical;   // true to flip sprite vertically
};

class Graphics
{
public:
	// Constructor
	Graphics();

	// Destructor
	virtual ~Graphics();

	// Releases all pointers
	void releaseAll();

	// Initialize DirectX graphics
	void initialize(HWND hWnd, int width, int height, bool fullscreen);

	//Load Textures
	HRESULT loadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
		LPDIRECT3DTEXTURE9& texture);

	// Display the offscreen backbuffer to the screen
	HRESULT showBackbuffer();

	void drawSprite(const SpriteData &spriteData, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	//Returns direct3d
	LPDIRECT3D9 get3D() { return direct3d_; }

	//Returns devide
	LPDIRECT3DDEVICE9 get3Ddevice() { return device3d_; }

	// Return sprite
	LPD3DXSPRITE getSprite() { return sprite_; }

	// Return handle to device context (window).
	HDC getDC() { return GetDC(hWnd_); }

	//Returns the state of device to determine if reset is needed
	HRESULT getDeviceState();

	//If device is lost use to reinitialize D3D presentation parameters
	HRESULT reset();

	//Begin a DirectX scene
	HRESULT beginScene();

	//End a DirectX scene
	HRESULT endScene();

	//Begin drawing sprite
	void spriteBegin();

	//End drawing sprite
	void spriteEnd();
private:
	// DirectX pointers
	LPDIRECT3D9 direct3d_;
	LPDIRECT3DDEVICE9 device3d_;
	D3DPRESENT_PARAMETERS d3dpp_;

	//Sprite pointers
	LPD3DXSPRITE sprite_;

	// Other variables
	HRESULT hResult_; // Standard Windows return codes
	HWND hWnd_;   //HANDLE to the window
	bool fullscreen_;  //true if screen is fullscreen, false otherwise
	int width_;  //width of the window
	int height_;   //height of the window

	// (For internal engine use only)
	// Initialize D3D presentation parameters
	void initD3Dpp();
};