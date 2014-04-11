#include "TextureManager.h"


TextureManager::TextureManager()
{
	texture_ = NULL;
	width_ = 0;
	height_ = 0;
	file_ = NULL;
	graphics_ = NULL;
	initialized_ = false;
}

TextureManager::~TextureManager()
{
	if (texture_)
	{
		texture_->Release();
	}
}

bool TextureManager::initialize(Graphics* graphics, const char* file)
{
	try{
		graphics_ = graphics;
		file_ = file;  // the texture file

		hResult_ = graphics_->loadTexture(file_, D3DCOLOR_XRGB(255, 0, 255), width_, height_, texture_);
		if (FAILED(hResult_))
		{
			if (texture_)
			{
				texture_->Release();
			}
			return false;
		}
	}
	catch (...) { return false; }

	initialized_ = true;  // set true when successfully initialized
	return true;
}

void TextureManager::onLostDevice()
{
	if (!initialized_)
	{
		return;
	}
	if (texture_)
	{
		texture_->Release();
		texture_ = NULL;
	}
}

void TextureManager::onResetDevice()
{
	if (initialized_)
	{
		graphics_->loadTexture(file_, D3DCOLOR_XRGB(255, 0, 255), width_, height_, texture_);
	}
}