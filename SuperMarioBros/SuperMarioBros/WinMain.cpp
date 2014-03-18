#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>
#include <mmsystem.h>


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
	//message loop
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
		}
		else
		{
			// run game here
			QueryPerformanceCounter(&timeEnd);

			frametime = (double) (timeEnd.QuadPart - timeStart.QuadPart) / (double) timerFrequency.QuadPart;

			// if the frame time is less than MIN_FRAME_TIME do idle processing
			//otherwise run game
			if (frametime < MIN_FRAME_TIME)
			{
				//figure out how long to sleep for
				sleepTime = (DWORD) (MIN_FRAME_TIME - frametime) * 1000;
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
				if (FAILED(ShowBackBuffer()))
				{
					MessageBox(hWnd, "ShowBackBuffer failed", "Error", MB_OK);
				}
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//kill all pointer objects
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
		WINDOW_WIDTH, WINDOW_HEIGHT, (HWND) NULL, (HMENU) NULL, hInstance, (LPVOID)NULL);
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
		break;
		//case WM_RBUTTONDOWN:
		//case WM_KEYDOWN:
		//case WM_KEYUP:
		//....
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool AnotherInstance()
{
	HANDLE outMutex = CreateMutex(NULL, true, "ksjdfghlksjfhghs;ldfj");
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
	if(direct3d == NULL)
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
	//destroy in reverse of creation so keep track as you go
	device3d->Release();
	direct3d->Release();
}

HRESULT ShowBackBuffer()
{
	HRESULT hResult = device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 0.0, 0);

	hResult =  device3d->Present(NULL, NULL, NULL, NULL);

	return hResult;
}