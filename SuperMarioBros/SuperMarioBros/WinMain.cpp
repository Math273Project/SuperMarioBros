#include "Game.h"
#include "Mario.h"
#include "Object.h"
#include <mmsystem.h>

LPDIRECT3D9 direct3d;
LPDIRECT3DDEVICE9 device3d;
//function prototypes
bool CreatMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow, bool fullscreen);
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool AnotherInstance();
HRESULT LoadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
	LPDIRECT3DTEXTURE9& texture);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	Graphics* graphics = new Graphics;
	HWND hWnd;
	MSG msg;

	bool fullscreen = false;

	UINT textureWidth;
	UINT textureHeight;
	LPDIRECT3DTEXTURE9 texture = NULL;
    LPD3DXSPRITE sprite;
	Mario mario;

	LARGE_INTEGER timeStart, timeEnd, timerFrequency;
	double frameTime;
	DWORD sleepTime, fps = 200;


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

	graphics->initialize(hWnd, GAME_WIDTH, GAME_HEIGHT, fullscreen);

	QueryPerformanceFrequency(&timerFrequency);
	QueryPerformanceCounter(&timeStart);

	HRESULT hResult = LoadTexture("mario.bmp", D3DCOLOR_XRGB(255, 0, 255), textureWidth, textureHeight, texture);
	if (FAILED(hResult))
	{
		MessageBox(hWnd, "LoadTexture failed", "Error", MB_OK);
	}
	hResult = D3DXCreateSprite(device3d, &sprite);
	if (FAILED(hResult))
	{
		MessageBox(hWnd, "D3DXCreateSprite failed", "Error", MB_OK);
	}

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
			graphics->showBackbuffer();
			// run game here
			QueryPerformanceCounter(&timeEnd);

			frameTime = (double)(timeEnd.QuadPart - timeStart.QuadPart) / (double)timerFrequency.QuadPart;

			// if the frame time is less than MIN_FRAME_TIME do idle processing
			//otherwise run game
			if (frameTime < MIN_FRAME_TIME)
			{
				//figure out how long to sleep for
				sleepTime = (DWORD)(MIN_FRAME_TIME - frameTime) * 1000;
				timeBeginPeriod(1);
				Sleep(sleepTime);
			}
			else
			{
				if (frameTime > 0.0)
				{
					fps = (fps + .99) + (0.1 / frameTime);
				}
				if (frameTime > MAX_FRAME_TIME)
				{
					frameTime = MAX_FRAME_TIME;
				}

				// reset the elapsed time to 0
				timeStart = timeEnd;

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
			}
		}
	}

	//kill all pointer objects
	//sprite->Release();
	//texture->Release();
	graphics->releaseAll();

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
	static TCHAR tChar = NULL;

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
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

HRESULT LoadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
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
}
