#include "Text.h"

Text::Text()
{
	color_ = D3DCOLOR_ARGB(255, 255, 255, 255); // default to white font

	// set font position
	fontRect_.top = 0;
	fontRect_.left = 0;
	fontRect_.right = GAME_WIDTH;
	fontRect_.bottom = GAME_HEIGHT;
	font_ = nullptr;
	angle_ = 0;
}

Text::~Text()
{
	SAFE_RELEASE(font_);
}

bool Text::initialize(Graphics *graphics, int height, const std::string &fontName,
					  bool bold, bool italic)
{
	graphics_ = graphics;                   // the graphics system

	UINT weight = FW_NORMAL;
	if (bold)
		weight = FW_BOLD;

	// create DirectX font
	if (FAILED(D3DXCreateFont(graphics_->get3Ddevice(), height, 0, weight, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(),
		&font_))) return false;

	// Create the tranformation matrix
	D3DXMatrixTransformation2D(&matrix_, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

	return true;
}

int Text::print(const std::string &str, int x, int y)
{
	if (font_ == nullptr)
		return 0;
	// set font position
	fontRect_.top = y;
	fontRect_.left = x;

	// Rotation center
	D3DXVECTOR2 rCenter = D3DXVECTOR2((float)x, (float)y);
	// Setup matrix to rotate text by angle
	D3DXMatrixTransformation2D(&matrix_, NULL, 0.0f, NULL, &rCenter, angle_, NULL);
	// Tell the sprite about the matrix "Hello Neo"
	graphics_->getSprite()->SetTransform(&matrix_);
	return font_->DrawTextA(graphics_->getSprite(), str.c_str(), -1, &fontRect_, DT_LEFT, color_);
}

int Text::print(const std::string &str, RECT &rect, UINT format)
{
	if (font_ == nullptr)
		return 0;

	// Setup matrix to not rotate text
	D3DXMatrixTransformation2D(&matrix_, NULL, 0.0f, NULL, NULL, NULL, NULL);
	// Tell the sprite about the matrix "Hello Neo"
	graphics_->getSprite()->SetTransform(&matrix_);
	return font_->DrawTextA(graphics_->getSprite(), str.c_str(), -1, &rect, format, color_);
}

void Text::onLostDevice()
{
	if (font_ == nullptr)
		return;
	font_->OnLostDevice();
}

void Text::onResetDevice()
{
	if (font_ == nullptr)
		return;
	font_->OnResetDevice();
}