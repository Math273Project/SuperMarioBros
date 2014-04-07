#include "MarioGame.h"

MarioGame::MarioGame()
{

}

MarioGame::~MarioGame()
{
	releaseAll();
}

void MarioGame::initialize(HWND hWnd, bool fullscreen)
{
	Game::initialize(hWnd, fullscreen);

}
void MarioGame::update()
{

}

void MarioGame::ai()
{

}

void MarioGame::collisions()
{

}

void MarioGame::render()
{
	SpriteData spriteData;
	UINT textureWidth;
	UINT textureHeight;
	int horizontalFrame = 0;
	int verticalFrame = 1;

	spriteData.x = GAME_WIDTH / 2;
	spriteData.y = GAME_HEIGHT / 2;
	spriteData.width = 16;
	spriteData.height = 32;
	spriteData.scale = 1.0;
	spriteData.angle = 1;
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	spriteData.rect.left = spriteData.width * horizontalFrame;
	spriteData.rect.top = spriteData.height * verticalFrame;
	spriteData.rect.right = spriteData.rect.left + spriteData.width - 1;
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height - 1;

	hResult_ = graphics_->LoadTexture("Mario.png", D3DCOLOR_XRGB(255, 0, 255), textureWidth, textureHeight, spriteData.texture);

	if (FAILED(hResult_))
	{
		MessageBox(hWnd_, "LoadTexture failed", "Error", MB_OK);
	}

	horizontalFrame++;
	if (horizontalFrame > 2)
	{
		horizontalFrame = 0;
	}

	graphics_->spriteBegin();
	graphics_->drawSprite(spriteData);
	graphics_->spriteEnd();
}
