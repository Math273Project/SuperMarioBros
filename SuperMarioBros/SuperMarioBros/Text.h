#pragma once

#define WIN32_LEAN_AND_MEAN

#include <string>
#include "Constants.h"
#include "Graphics.h"

class Text
{
public:
	// Constructor (sprite text)
	Text();

	// Destructor
	virtual ~Text();

	// Initialize font
	// Pre: *graphics points to Graphics object
	//      height = height in pixels
	//      &fontName = name of font to use
	virtual bool initialize(Graphics *graphics, int height, const std::string &fontName, bool bold = false, bool italic = false);

	// Call between spriteBegin() & spriteEnd()
	// Return 0 on fail, height of text on success
	virtual int print(const std::string &string, int x, int y);

	// Call between spriteBegin() & spriteEnd()
	// Return 0 on fail, height of text on success
	// Pre: &str = text to display
	//      &rect = rectangular region
	//      format = format specifier
	virtual int print(const std::string &str, RECT &rect, UINT format);

	// Return rotation angle in degrees.
	virtual float getDegrees()      { return angle_*(180.0f / (float)PI); }

	// Return rotation angle in radians.
	virtual float getRadians()      { return angle_; }

	// Returns font color
	virtual DWORD getFontColor() { return color_; }

	// Set rotation angle in degrees.
	// 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg)  { angle_ = deg*((float)PI / 180.0f); }

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad)  { angle_ = rad; }

	// Set the font color. Use SETCOLOR_ARGB macro or colors from graphicsNS::
	virtual void setFontColor(DWORD color) { color_ = color; }

	// Release resources
	virtual void onLostDevice();

	// Restore resources
	virtual void onResetDevice();

private:
	Graphics    *graphics_;
	DWORD  color_;          // font color (a,r,g,b)
	LPD3DXFONT   font_;
	RECT        fontRect_;       // text rectangle
	// matrix to rotate the text
	D3DXMATRIX  matrix_;
	float       angle_;          // rotation angle of text in radians

};