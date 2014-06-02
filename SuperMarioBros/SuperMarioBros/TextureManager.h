#pragma once
#include "graphics.h"
#include "constants.h"

class TextureManager
{

public:
	// Constructor
	TextureManager();

	// Destructor
	virtual ~TextureManager();

	// Initialize the textureManager
	// Pre: *graphics points to Graphics object
	//         *file points to name of texture file to load
	virtual bool initialize(Graphics* graphics, const char* file);

	// Release resources
	virtual void onLostDevice();

	// Restore resourses
	virtual void onResetDevice();

	// Returns a pointer to the texture
	LPDIRECT3DTEXTURE9 getTexture() const { return texture_; }

	// Returns the texture width
	UINT getWidth() const { return width_; }

	// Return the texture height
	UINT getHeight() const { return height_; }

private:
	UINT       width_;       // width of texture in pixels
	UINT       height_;      // height of texture in pixels
	LPDIRECT3DTEXTURE9 texture_;     // pointer to texture
	const char* file_;       // name of file
	Graphics* graphics_;     // save pointer to graphics
	bool    initialized_;    // true when successfully initialized
	HRESULT hResult_;

};
