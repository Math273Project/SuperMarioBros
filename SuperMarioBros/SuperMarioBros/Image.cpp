#include "Image.h"


Image::Image()
{

	initialized_ = false;            // set true when successfully initialized
	spriteData_.width = 2;
	spriteData_.height = 2;
	spriteData_.x = 0.0;
	spriteData_.y = 0.0;
	spriteData_.scale = 1.0;
	spriteData_.angle = 0.0;
	spriteData_.rect.left = 0;       // rect is used to select one frame from a larger texture image
	spriteData_.rect.top = 0;
	spriteData_.rect.right = spriteData_.width;
	spriteData_.rect.bottom = spriteData_.height;
	spriteData_.texture = NULL;  // the sprite texture (picture)
	spriteData_.flipHorizontal = false;
	spriteData_.flipVertical = false;
	cols_ = 1;
	textureManager_ = NULL;
	startFrame_ = 0;
	endFrame_ = 0;
	currentFrame_ = 0;
	frameDelay_ = 1.0;  // default to 1 second per frame of animation
	animationTimer_ = 0.0;
	visible_ = true;  // the image is visible
	loop_ = true;  // loop frames
	animationComplete_ = false;
	graphics_ = NULL;
}


Image::~Image()
{
}

bool Image::initialize(Graphics* graphics, int width, int height, int ncols,
	TextureManager* textureManager)
{
	try{
		graphics_ = graphics;  // the graphics object
		textureManager_ = textureManager; // pointer to texture object

		spriteData_.texture = textureManager_->getTexture();
		if (width == 0)
		{
			width = textureManager_->getWidth(); // use full width of texture
		}
		spriteData_.width = width;

		if (height == 0)
		{
			height = textureManager_->getHeight(); // use full height of texture
		}
		spriteData_.height = height;

		cols_ = ncols;
		if (cols_ == 0)
		{
		cols_ = 1;                               // if 0 cols use 1
		}

		// configure spriteData.rect to draw currentFrame
		spriteData_.rect.left = (currentFrame_ % cols_) * spriteData_.width;
		// right edge + 1
		spriteData_.rect.right = spriteData_.rect.left + spriteData_.width;
		spriteData_.rect.top = (currentFrame_ / cols_) * spriteData_.height;
		// bottom edge + 1
		spriteData_.rect.bottom = spriteData_.rect.top + spriteData_.height;
	}
	catch (...) { return false; }

	initialized_ = true;                                // successfully initialized
	return true;
}

// Pre : spriteBegin() is called
// Post: spriteEnd() is called
void Image::draw()
{
	if (visible_ || graphics_ != NULL)
	{
		spriteData_.texture = textureManager_->getTexture();  // get fresh texture incase onReset() was called

		graphics_->drawSprite(spriteData_);
	}
}

// Pre : spriteBegin() is called
// Post: spriteEnd() is called
void Image::draw(SpriteData spriteData)
{
	if (visible_ || graphics_ != NULL)
	{
		spriteData.rect = spriteData_.rect;                  // use this Images rect to select texture
		spriteData.texture = textureManager_->getTexture();  // get fresh texture incase onReset() was called

		graphics_->drawSprite(spriteData);
	}
}

void Image::update(double frameTime)
{
	if (endFrame_ - startFrame_ > 0)  // if animated sprite
	{
		animationTimer_ += frameTime;  // total elapsed time
		if (animationTimer_ > frameDelay_)
		{
			animationTimer_ -= frameDelay_;
			currentFrame_++;
			if (currentFrame_ < startFrame_ || currentFrame_ > endFrame_)
			{
				if (loop_ == true)            // if looping animation
					currentFrame_ = startFrame_;
				else                        // not looping animation
				{
					currentFrame_ = endFrame_;
					animationComplete_ = true;    // animation complete
				}
			}
			setRect();                      // set spriteData.rect
		}
	}
}

void Image::setCurrentFrame(int currentFrame)
{
	if (currentFrame >= 0)
	{
		currentFrame_ = currentFrame;
		animationComplete_ = false;
		setRect();                          // set spriteData.rect
	}
}

inline void Image::setRect()
{
	// configure spriteData.rect to draw currentFrame
	spriteData_.rect.left = (currentFrame_ % cols_) * spriteData_.width;
	// right edge + 1
	spriteData_.rect.right = spriteData_.rect.left + spriteData_.width;
	spriteData_.rect.top = (currentFrame_ / cols_) * spriteData_.height;
	// bottom edge + 1
	spriteData_.rect.bottom = spriteData_.rect.top + spriteData_.height;
}