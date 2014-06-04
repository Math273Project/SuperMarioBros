#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "Image.h"
#include "Constants.h"
#include "TextureManager.h"
#include "Input.h"

namespace dashboardNS
{
	const int   IMAGE_SIZE = 64;        // each texture size
	const int   TEXTURE_COLS = 4;       // texture has 4 columns
	const int   BAR_FRAME = 0;          // the frame number of each texture
	const int   DIAL360_FRAME = 1;      // "
	const int   DIAL270_FRAME = 2;      // ...
	const int   DIAL180_FRAME = 3;
	const int   LIGHT_FRAME = 4;
	const int   POINTER_FRAME = 5;
	const int   SEGMENT_FRAME = 6;
	const int   DECIMAL_FRAME = 7;
	const int   SWITCH_OFF_FRAME = 8;
	const int   SWITCH_ON_FRAME = 9;
	const int   BUTTON_UP_FRAME = 10;
	const int   BUTTON_DOWN_FRAME = 11;
	const int   BAR_GRAPH_FRAME = 12;
	const int   SWITCH_WIDTH = 44;      // width of toggle switch 
	const int   BAR_GRAPH_WIDTH = 8;    // width of bar + gap
	enum DialType{ DIAL360, DIAL270, DIAL180 };
}

class SevenSegment : public Image
{
public:
	SevenSegment();

	~SevenSegment();

	// Initialize Seven Segment
	// Pre: *graphics = pointer to Graphics object
	//      *textureM = pointer to TextureManager object
	//      left, top = screen location
	//      scale = scaling (zoom) amount
	//      digits = number of digits
	//      color = color of digits
	bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
		float scale, UINT digits, DWORD color);

	// Set Number in 7-Segment
	void set(double value);
	// Override update
	virtual void update(double frameTime)    {}
	// Draw 1 digit (internal use)
	void drawDigit(char n, DWORD color);
	// Draw decimal point (internal use)
	void drawDecimal(DWORD color);
	// Draw Image using color as filter. Default color is WHITE.
	virtual void draw(DWORD color);
private:
	Image decimal_;
	UINT digits_;
	double numbers_;
};