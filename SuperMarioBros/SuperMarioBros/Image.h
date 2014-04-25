#pragma once

#include "textureManager.h"
#include "constants.h"
#include "Arena.h"

class Image
{
public:
	Image();
	virtual ~Image();

	// Initialize Image
	// Pre: *graphics = pointer to Graphics object
	//      width = width of Image in pixels (0 = use full texture width)
	//      height = height of Image in pixels (0 = use full texture height)
	//      ncols = number of columns in texture ( 0 = 1)
	//      *textureManager = pointer to TextureManager object
	virtual bool Image::initialize(Graphics *graphics, int width, int height,
		int numOfCols, TextureManager* textureManager);

	// Flip image horizontally (mirror)
	virtual void flipHorizontal(bool flipHorizontal)  { spriteData_.flipHorizontal = flipHorizontal; }

	// Flip image vertically
	virtual void flipVertical(bool flipVertical)    { spriteData_.flipVertical = flipVertical; }

	// Draw Image. Default color is white
	virtual void draw();

	// Draw this image using the specified SpriteData.
	// The current SpriteData.rect is used to select the texture.
	virtual void draw(SpriteData spriteData);

	// Update the animation. frameTime is used to regulate the speed.
	// All code that needs to be synchronized with elapsed time should be placed here.
	virtual void update(double frameTime);


	// Return reference to SpriteData structure.
	const virtual SpriteData& getSpriteInfo() { return spriteData_; }

	// Return visible parameter.
	virtual bool  getVisible() { return visible_; }

	// Return X position.
	virtual double getX() { return spriteData_.x; }

	// Return Y position.
	virtual double getY() { return spriteData_.y; }

	// Return scale factor.
	virtual double getScale() { return spriteData_.scale; }

	// Return width.
	virtual int   getWidth() { return spriteData_.width; }

	// Return height.
	virtual int   getHeight() { return spriteData_.height; }

	// Return center X.
	virtual double getCenterX() { return spriteData_.x + spriteData_.width / 2 * getScale(); }

	// Return center Y.
	virtual double getCenterY() { return spriteData_.y + spriteData_.height / 2 * getScale(); }

	// Return rotation angle in degrees.
	virtual double getDegrees() { return spriteData_.angle * (180.0 / PI); }

	// Return rotation angle in radians.
	virtual double getRadians() { return spriteData_.angle; }

	// Return delay between frames of animation.
	virtual double getFrameDelay() { return frameDelay_; }

	// Return number of starting frame.
	virtual int   getStartFrame() { return startFrame_; }

	// Return number of ending frame.
	virtual int   getEndFrame() { return endFrame_; }

	// Return number of current frame.
	virtual int   getCurrentFrame() { return currentFrame_; }

	// Return RECT structure of Image.
	virtual RECT  getSpriteDataRect() { return spriteData_.rect; }

	// Return state of animation complete.
	virtual bool  getAnimationComplete() { return animationComplete_; }


	// Set X location.
	virtual void setX(double x)   { spriteData_.x = x; }

	// Set Y location.
	virtual void setY(double y)   { spriteData_.y = y; }

	// Set scale.
	virtual void setScale(double scale)  { spriteData_.scale = scale; }

	// Set rotation angle in degrees.
	// 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(double angle)  { spriteData_.angle = angle * (PI / 180.0); }

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(double radians)  { spriteData_.angle = radians; }

	// Set visible.
	virtual void setVisible(bool visible) { visible_ = visible; }

	// Set delay between frames of animation.
	virtual void setFrameDelay(double delay) { frameDelay_ = delay; }

	// Set starting and ending frames of animation.
	virtual void setFrames(int start, int end){ startFrame_ = start; endFrame_ = end; }

	// Set current frame of animation.
	// This function may be used to change an animation sequence or select a different
	// texture to apply to the image from a multiple - image texture.
	virtual void setCurrentFrame(int currentFrame);

	// Set spriteData.rect to draw currentFrame
	// Used to select the rectangular region of the texture to use for the current sprite.
	virtual void setRect();

	// Set spriteData_.rect to rect.
	virtual void setSpriteDataRect(RECT rect)  { spriteData_.rect = rect; }

	// Set animation loop.
	virtual void setLoop(bool loop) { loop_ = loop; }

	// Set animation complete Boolean.
	virtual void setAnimationComplete(bool animationComplete) { animationComplete_ = animationComplete; };

	// Set TextureManager
	virtual void setTextureManager(TextureManager* textureManager)
	{
		textureManager_ = textureManager;
	}

protected:
		HRESULT hResult_;
		Graphics* graphics_;     // pointer to graphics
		TextureManager* textureManager_; // pointer to texture manager
		// spriteData contains the data required to draw the image by Graphics::drawSprite()
		SpriteData spriteData_;  // SpriteData is defined in "graphics.h"
		int     cols_;           // number of cols (1 to n) in multi-frame sprite
		int     startFrame_;     // first frame of current animation
		int     endFrame_;       // end frame of current animation
		int     currentFrame_;   // current frame of animation
		double   frameDelay_;     // how long between frames of animation
		double   animationTimer_; // animation timer		
		bool    loop_;           // true to loop frames
		bool    visible_;        // true when visible
		bool    initialized_;    // true when successfully initialized
		bool    animationComplete_;   // true when loop is false and endFrame has finished displaying
		friend class Arena;
};

