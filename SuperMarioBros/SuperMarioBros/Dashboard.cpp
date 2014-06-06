#include "Dashboard.h"

SevenSegment::SevenSegment()
{
	digits_ = 1;
	numbers_ = 0;
}

SevenSegment::~SevenSegment()
{

}

bool SevenSegment::initialize(Graphics *graphics, TextureManager *textureM,
	int left, int top, float scale, UINT digits, DWORD color)
{
	try {
		Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE,
			dashboardNS::TEXTURE_COLS, textureM);
		setCurrentFrame(dashboardNS::SEGMENT_FRAME);
		spriteData_.x = (float)left;
		spriteData_.y = (float)top;
		spriteData_.scale = scale;
		if (digits < 1)
			digits = 1;
		digits_ = digits;

		decimal_.initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE,
			dashboardNS::TEXTURE_COLS, textureM);
		decimal_.setCurrentFrame(dashboardNS::DECIMAL_FRAME);
	}
	catch (...)
	{
		return false;
	}
	//return okay
	return true;
}

void SevenSegment::set(double value)
{
	numbers_ = value;
}

//=============================================================================
// Display 7 segment digit 0-9, and -
//         A
//       -----
//     F|     |B
//      |  G  |
//       -----
//     E|     |C
//      |  D  |
//       -----  
//=============================================================================
void SevenSegment::drawDigit(char n, DWORD color)
{
	float lowerY = spriteData_.y + spriteData_.height * spriteData_.scale * 0.75f;
	float saveY = spriteData_.y;

	// segment A
	if (n == '0' || n == '2' || n == '3' || n == '5' || n == '6' || n == '7' || n == '8' || n == '9')
	{
		setDegrees(0);
		Image::draw(color);
	}
	// segment B
	if (n == '0' || n == '1' || n == '2' || n == '3' || n == '4' || n == '7' || n == '8' || n == '9')
	{
		setDegrees(90);
		Image::draw(color);
	}
	// segment G
	if (n == '-' || n == '2' || n == '3' || n == '4' || n == '5' || n == '6' || n == '8' || n == '9')
	{
		setDegrees(180);
		Image::draw(color);
	}
	// if segment F
	if (n == '0' || n == '4' || n == '5' || n == '6' || n == '8' || n == '9')
	{
		setDegrees(270);
		Image::draw(color);
	}

	spriteData_.y = lowerY;  // set Y for lower half of digit

	// if segment E
	if (n == '0' || n == '2' || n == '6' || n == '8')
	{
		setDegrees(270);
		Image::draw(color);
	}
	// if segment D
	if (n == '0' || n == '2' || n == '3' || n == '5' || n == '6' || n == '8' || n == '9')
	{
		setDegrees(180);
		Image::draw(color);
	}
	// if segment C
	if (n == '0' || n == '1' || n == '3' || n == '4' || n == '5' || n == '6' || n == '7' || n == '8' || n == '9')
	{
		setDegrees(90);
		Image::draw(color);
	}
	spriteData_.y = saveY;
}

void SevenSegment::drawDecimal(DWORD color)
{
	float saveX = spriteData_.x;
	float saveY = spriteData_.y;

	setDegrees(0);
	spriteData_.x -= spriteData_.width * spriteData_.scale * 0.25f;
	spriteData_.y += spriteData_.height * spriteData_.scale * 0.80f;

	decimal_.draw(spriteData_, color);

	spriteData_.x = saveX;
	spriteData_.y = saveY;
}

void SevenSegment::draw(DWORD color)
{
	float saveX = spriteData_.x;
	float saveY = spriteData_.y;
	char ch;

	if (digits_ == 0)
		return;

	// convert number to string
	std::stringstream strstm;
	strstm.precision(digits_);
	strstm.flags(std::ios_base::fixed);
	strstm << numbers_;           // convert number to string
	std::string str = strstm.str();

	UINT digitN = str.length(); // get digits in string
	if (digitN > digits_)        // if string has more digits than 7-seg display
		digitN = digits_;

	// x location of left most digit
	spriteData_.x += spriteData_.width * spriteData_.scale * 1.2f * (digits_ - digitN);

	UINT n = 0;
	ch = str.at(n++);           // get first digit from number
	while (digitN > 0)           // while digits remain to be displayed
	{
		if (ch == '.')           // if decimal point
			drawDecimal(color);
		else
		{
			drawDigit(ch, color);   // display digit
			// next digit position on screen
			spriteData_.x += spriteData_.width * spriteData_.scale * 1.2f;
		}
		if (n < str.length())
			ch = str.at(n++);   // get next digit
		else
			ch = '0';           // if string ends with '.' pad with 0 digit
		if (ch != '.')           // if not decimal point
			digitN--;           // decrement digit count
	}
	spriteData_.x = saveX;
}