#include "MarioGame.h"

MarioGame* marioGame = new MarioGame();
HWND hWnd;

//function prototypes
bool CreateMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow, bool fullscreen);
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool AnotherInstance();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
	
	MSG msg;

	bool fullscreen = false;

	if (AnotherInstance())
	{
		MessageBox(NULL, "Slow down ... another instance is loading...", "Error", MB_OK);
		return 1;
	}

	//window creation code
	if (!CreateMainWindow(hWnd, hInstance, nCmdShow, fullscreen))
	{
		return 1;
	}

	marioGame->initialize(hWnd, fullscreen);

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
		}
	}
	marioGame->releaseAll();
	delete marioGame;

	//return value
	return msg.wParam;
}

bool CreateMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow, bool fullscreen)
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
