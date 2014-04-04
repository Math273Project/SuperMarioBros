#include "Game.h"

//function prototypes
bool CreatMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow, bool fullscreen);
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool AnotherInstance();
HRESULT LoadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
	LPDIRECT3DTEXTURE9& texture);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	MarioGame marioGame = new MarioGame;
	HWND hWnd;
	MSG msg;

	bool fullscreen = false;

	//UINT textureWidth;
	//UINT textureHeight;
	//LPDIRECT3DTEXTURE9 texture = NULL;
	//LPD3DXSPRITE sprite;

	int x = GAME_WIDTH / 2;
	int y = GAME_HEIGHT / 2;
	int frameWidth = 24;
	int frameHeight = 48;
	int horizontalFrame = 0; 
	int verticalFrame = 1; 

	double scale = 1.0;
	double angle = 0;
	bool flipVertical = false;
	bool flipHorizontal = false;

	RECT frameRect;


	if (AnotherInstance())
	{
		MessageBox(NULL, "Slow down ... another instance is loading...", "Error", MB_OK);
		return 1;
	}

	//window creation code
	if (!CreatMainWindow(hWnd, hInstance, nCmdShow, fullscreen))
	{
		return 1;
	}

	marioGame->initialize(hWnd, GAME_WIDTH, GAME_HEIGHT, fullscreen);

	/*initialize directx

	hResult = LoadTexture("ninjagirl.bmp", D3DCOLOR_XRGB(255, 0, 255), textureWidth, textureHeight, texture);

	if (FAILED(hResult))
	{
		MessageBox(hWnd, "LoadTexture failed", "Error", MB_OK);
	}
	hResult = D3DXCreateSprite(device3d, &sprite);
	if (FAILED(hResult))
	{
		MessageBox(hWnd, "D3DXCreateSprite failed", "Error", MB_OK);
	}*/

	//message loop
	bool done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			marioGame->run(hWnd);
			/*
				//game processing
				//move
				horizontalFrame++;
				if (horizontalFrame > 2)
				{
					horizontalFrame = 0;
				}
				//render
				device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0, 0);
				device3d->BeginScene();

				//call draw funtions for each object
				sprite->Begin(D3DXSPRITE_ALPHABLEND);

				frameRect.left = frameWidth*horizontalFrame;
				frameRect.top = frameHeight * verticalFrame;
				frameRect.right = frameRect.left + frameWidth - 1;
				frameRect.bottom = frameRect.top + frameHeight - 1;

				D3DXVECTOR2 center(frameWidth / 2 * scale, frameHeight / 2 * scale);
				D3DXVECTOR2 position(x, y);
				D3DXVECTOR2 scaling(scale, scale);

				if (flipVertical)
				{
					scaling.y *= -1;
					center.y -= textureHeight * scale;
					position.y += textureHeight *scale;
				}
				if (flipHorizontal)
				{
					scaling.x *= -1;
					center.x -= textureWidth * scale;
					position.x += textureWidth * scale;
				}

				D3DXMATRIX matrix;
				D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &scaling, &center, angle, &position);

				sprite->SetTransform(&matrix);
				hResult = sprite->Draw(texture, &frameRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

				if (FAILED(hResult))
				{
					MessageBox(hWnd, "draw failed", "Error", MB_OK);
				}
				sprite->End();
				device3d->EndScene();
				device3d->Present(NULL, NULL, NULL, NULL);
			}*/
		}
	}

	//kill all pointer objects
	//sprite->Release();
	//texture->Release();
	marioGame->releaseAll();

	//return value
	return msg.wParam;
}

bool CreatMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow, bool fullscreen)
{
	//fill wndclassex
	WNDCLASSEX wcx;
	DWORD style;


	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == NULL)
	{
		MessageBox(NULL, "RegisterClassEX failed", "Error!", MB_OK);
		return false;
	}

	if (fullscreen)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}

	hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME, style, CW_USEDEFAULT, CW_USEDEFAULT,
		GAME_WIDTH, GAME_HEIGHT, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL, "CreateWindow failed", "Error!", MB_OK);
		return false;
	}

	//resize the window so the client area has correct width and height
	if (!fullscreen)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);

		MoveWindow(hWnd, 0, 0, 2 * GAME_WIDTH - clientRect.right,
			2 * GAME_HEIGHT - clientRect.bottom, true);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return marioGame->messageHandler(hWnd, msg, wParam, lParam);
}

bool AnotherInstance()
{
	HANDLE ourMutex = CreateMutex(NULL, true, "ksjdfghlksjfhghs;ldfj");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return true;
	}

	return false;

}

/*HRESULT LoadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
	LPDIRECT3DTEXTURE9& texture)
{
	D3DXIMAGE_INFO info;
	HRESULT hResult;

	if (filename == NULL)
	{
		texture = NULL;
		return D3DERR_INVALIDCALL; //bad file name return error
	}

	hResult = D3DXGetImageInfoFromFile(filename, &info);
	if (hResult != D3D_OK)
	{
		return hResult;
	}

	width = info.Width;    //returns width
	height = info.Height;  //return height

	hResult = D3DXCreateTextureFromFileEx(device3d, filename, width, height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, transparencyColor, &info, NULL, &texture);

	return hResult;
}*/
