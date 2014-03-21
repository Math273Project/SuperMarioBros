#include "Game.h"

//directx constants
LPDIRECT3D9 direct3d;
LPDIRECT3DDEVICE9 device3d;
const double FRAME_RATE = 200.0;
const double MIN_FRAME_RATE = 10.0;
const double MIN_FRAME_TIME = 1.0 / FRAME_RATE;
const double MAX_FRAME_TIME = 1.0 / MIN_FRAME_RATE;

//constants
const char CLASS_NAME[] = "DirectX Example";
const char WINDOW_NAME[] = "DirectX Example!";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//function prototypes
bool CreatMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow, bool fullscreen);
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool AnotherInstance();
void InitializeDirectX(HWND& hWnd, int width, int height, bool fullscreen);
void ReleaseAll();
HRESULT ShowBackBuffer();
HRESULT LoadTexture(const char* filename, D3DCOLOR transparencyColor, UINT& width, UINT& height,
	LPDIRECT3DTEXTURE9& texture);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	bool done = false;
	bool fullscreen = false;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timerFrequency;
	double frametime = 0.0;
	DWORD sleepTime = 0;
	double fps = 0;
	HRESULT hResult;
	UINT textureWidth;
	UINT textureHeight;
	LPDIRECT3DTEXTURE9 texture = NULL;
	LPD3DXSPRITE sprite;

	int x = WINDOW_WIDTH / 2;
	int y = WINDOW_HEIGHT / 2;
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

	//initialize directx
	InitializeDirectX(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT, fullscreen);
	QueryPerformanceFrequency(&timerFrequency);
	QueryPerformanceCounter(&timeStart);

	hResult = LoadTexture("ninjagirl.bmp", D3DCOLOR_XRGB(255, 0, 255), textureWidth, textureHeight, texture);

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
			// run game here
			QueryPerformanceCounter(&timeEnd);

			frametime = (double)(timeEnd.QuadPart - timeStart.QuadPart) / (double)timerFrequency.QuadPart;

			// if the frame time is less than MIN_FRAME_TIME do idle processing
			//otherwise run game
			if (frametime < MIN_FRAME_TIME)
			{
				//figure out how long to sleep for
				sleepTime = (DWORD)(MIN_FRAME_TIME - frametime) * 1000;
				timeBeginPeriod(1);
				Sleep(sleepTime);
			}
			else
			{
				if (frametime > 0.0)
				{
					fps = (fps + .99) + (0.1 / frametime);
				}
				if (frametime > MAX_FRAME_TIME)
				{
					frametime = MAX_FRAME_TIME;
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
	sprite->Release();
	texture->Release();
	ReleaseAll();

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
		WINDOW_WIDTH, WINDOW_HEIGHT, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);
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

		MoveWindow(hWnd, 0, 0, 2 * WINDOW_WIDTH - clientRect.right,
			2 * WINDOW_HEIGHT - clientRect.bottom, true);
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
		case VK_SPACE:
			ShowBackBuffer();
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

void InitializeDirectX(HWND& hWnd, int width, int height, bool fullscreen)
{
	D3DPRESENT_PARAMETERS d3dpp;
	HRESULT hResult;

	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
	{
		MessageBox(hWnd, "Direct3DCreate9 failed", "Error", MB_OK);
		return;
	}

	//set up the presentaion parameters
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	if (fullscreen)
	{
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = !fullscreen;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hResult = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device3d);

	if (FAILED(hResult))
	{
		MessageBox(hWnd, "CreateDevice failed", "Error", MB_OK);
		return;
	}
}

void ReleaseAll()
{
	device3d->Release();
	direct3d->Release();
}

HRESULT ShowBackBuffer()
{
	HRESULT hResult = device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0.0, 0);

	device3d->Present(NULL, NULL, NULL, NULL);

	return hResult;
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