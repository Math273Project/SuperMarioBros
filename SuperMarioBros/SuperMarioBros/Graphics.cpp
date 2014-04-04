#include "Graphics.h"

Graphics::Graphics()
{
	direct3d_ = NULL;
	device3d_ = NULL;
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
}

HRESULT Graphics::showBackbuffer()
{
	HRESULT hResult = device3d_->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0.0, 0);

	device3d_->Present(NULL, NULL, NULL, NULL);

	return hResult;
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
	device3d_->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0.0, 0);
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