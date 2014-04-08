#include "Graphics.h"

Graphics::Graphics()
{
	direct3d_ = NULL;
	device3d_ = NULL;
	sprite_ = NULL;
	fullscreen_ = false;
	width_ = GAME_WIDTH; // Width & height are replaced in initialize()
	height_ = GAME_HEIGHT;
}

Graphics::~Graphics()
{
	releaseAll();
}

void Graphics::releaseAll()
{
	sprite_->Release();
	device3d_->Release();
	direct3d_->Release();
}

void Graphics::initD3Dpp()
{
	try{
		//set up the presentaion parameters
		ZeroMemory(&d3dpp_, sizeof(d3dpp_));

		d3dpp_.BackBufferWidth = width_;
		d3dpp_.BackBufferHeight = height_;
		if (fullscreen_)
		{
			d3dpp_.BackBufferFormat = D3DFMT_X8R8G8B8;
		}
		else
		{
			d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN;
		}
		d3dpp_.BackBufferCount = 1;
		d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp_.hDeviceWindow = hWnd_;
		d3dpp_.Windowed = !fullscreen_;
		d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing D3D presentation parameters"));
	}
}

void Graphics::initialize(HWND hWnd, int width, int height, bool fullscreen)
{
	hWnd_ = hWnd;
	width_ = width;
	height_ = height;
	fullscreen_ = fullscreen;

	direct3d_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d_ == NULL)
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing Direct3D"));
	}

	initD3Dpp();

	hResult_ = direct3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd_,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp_, &device3d_);

	if (FAILED(hResult_))
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error creating Direct3D device"));
	}

	hResult_ = D3DXCreateSprite(device3d_, &sprite_);
	if (FAILED(hResult_))
		throw(GameError(gameErrors::FATAL_ERROR, "Error creating Direct3D sprite"));
}

HRESULT Graphics::loadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
	LPDIRECT3DTEXTURE9& texture)
{
	D3DXIMAGE_INFO info;
	hResult_;

	if (filename == NULL)
	{
		texture = NULL;
		return D3DERR_INVALIDCALL; //bad file name return error
	}

	hResult_ = D3DXGetImageInfoFromFile(filename, &info);
	if (hResult_ != D3D_OK)
	{
		return hResult_;
	}

	width = info.Width;    //returns width
	height = info.Height;  //return height

	hResult_ = D3DXCreateTextureFromFileEx(device3d_, filename, width, height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, transparencyColor, &info, NULL, &texture);

	return hResult_;
}

HRESULT Graphics::showBackbuffer()
{
	hResult_ = device3d_->Present(NULL, NULL, NULL, NULL);

	return hResult_;
}

void Graphics::drawSprite(const SpriteData &spriteData)
{
	if (spriteData.texture == NULL) // If no texture
	{
		return;
	}

	D3DXVECTOR2 spriteCenter((double)(spriteData.width / 2 * spriteData.scale),
		(double)(spriteData.height / 2 * spriteData.scale));

	D3DXVECTOR2 position((double)spriteData.x, (double)spriteData.y);

	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);

	if (spriteData.flipHorizontal)
	{
		scaling.x *= -1;
		spriteCenter.x -= (double)(spriteData.width * spriteData.scale);
		position.x += (double)(spriteData.width * spriteData.scale);
	}
	if (spriteData.flipVertical)
	{
		scaling.y *= -1;
		spriteCenter.y -= (double)(spriteData.height * spriteData.scale);
		position.y += (double)(spriteData.height * spriteData.scale);
	}

	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &scaling, &spriteCenter, (double)(spriteData.angle), &position);

	sprite_->SetTransform(&matrix);

	sprite_->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

HRESULT Graphics::getDeviceState()
{
	hResult_ = E_FAIL; // Default to fail, replace on success
	if (device3d_ == NULL)
	{
		return hResult_;
	}
	hResult_ = device3d_->TestCooperativeLevel();
	return hResult_;
}

HRESULT Graphics::reset()
{
	hResult_ = E_FAIL; // Default to fail, replace on success
	initD3Dpp(); // Initialize D3D presentation parameters again
	hResult_ = device3d_->Reset(&d3dpp_); // Attempt to reset graphics device
	return hResult_;
}

HRESULT Graphics::beginScene()
{
	hResult_ = E_FAIL;
	if (device3d_ == NULL)
	{
		return hResult_;
	}
	// Clear backbuffer to backColor
	device3d_->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 0.0, 0);
	hResult_ = device3d_->BeginScene(); // Begin scene for drawing
	return hResult_;
}

HRESULT Graphics::endScene()
{
	hResult_ = E_FAIL;
	if (device3d_)
	{
		hResult_ = device3d_->EndScene();
	}
	return hResult_;
}

void Graphics::spriteBegin()
{
	sprite_->Begin(D3DXSPRITE_ALPHABLEND);
}

void Graphics::spriteEnd()
{
	sprite_->End();
}