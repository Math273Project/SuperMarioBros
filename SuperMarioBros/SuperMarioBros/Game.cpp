#include "Game.h"

Game::Game()
{
	input_ = new Input(); // Initialize keyboard input immediately
	// Additional initialization is handled in later call to input->
	// initialize()
	paused_ = false; // Game is not paused
	graphics_ = NULL;
	initialized_ = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (initialized_) // Do not process messages if not initialized
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0); // Tell Windows to kill this program
			break;
		case WM_KEYDOWN: 
		case WM_SYSKEYDOWN:// Key down
			input_->keyDown(wParam);
			break;
		case WM_KEYUP: 
		case WM_SYSKEYUP: // Key up
			input_->keyUp(wParam);
			break;
		case WM_CHAR: // Character entered
			input_->keyIn(wParam);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Game::initialize(HWND hWnd, bool fullscreen)
{
	hWnd_ = hWnd;
	graphics_ = new Graphics();
	// Throws GameError
	graphics_->initialize(hWnd_, GAME_WIDTH, GAME_HEIGHT, fullscreen);
	// Initialize input, do not capture mouse
	input_->initialize(hWnd_, false); // Throws GameError
	// Attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq_) == false)
	{
		throw(GameError(gameErrors::FATAL_ERROR, "Error initializing high resolution timer"));
	}
	// Get starting time
	QueryPerformanceCounter(&timeStart_);

	initialized_ = true;
}

void Game::run(HWND hWnd)
{
	if (graphics_ == NULL) // If graphics not initialized
	{
		return;
	}

	QueryPerformanceCounter(&timeEnd_);

	frameTime_ = (double)(timeEnd_.QuadPart - timeStart_.QuadPart) /
		(double)timerFreq_.QuadPart;

	// if the frame time is less than MIN_FRAME_TIME do idle processing
	//otherwise run game
	if (frameTime_ < MIN_FRAME_TIME)
	{
		//figure out how long to sleep for
		sleepTime_ = (DWORD)(MIN_FRAME_TIME - frameTime_) * 1000;
		timeBeginPeriod(1);// Request 1mS resolution for windows timer
		Sleep(sleepTime_); // Release CPU for sleepTime
		timeEndPeriod(1); // End 1mS timer resolution
		return;
	}
	if (frameTime_ > 0.0)
	{
		fps_ = (fps_ * .99) + (0.1 / frameTime_);
	}
	if (frameTime_ > MAX_FRAME_TIME)
	{
		frameTime_ = MAX_FRAME_TIME;
	}

	// reset the elapsed time to 0
	timeStart_ = timeEnd_;
	if (!paused_)
	{
		//Pure virtual functions defined by derived Classes
		update(); // Update all game items
		ai(); // Artificial intelligence
		collisions(); // Handle collisions
	}
	renderGame(); //renderGame() draws all items and calls pure virtual function render
	// Clear input
	// Call this after all key checks are done
	input_->clear(InputConstants::KEYS_PRESSED);
}

void Game::releaseAll()
{

}

void Game::resetAll()
{

}

void Game::deleteAll()
{
	releaseAll();
	graphics_->releaseAll();
	input_->~Input();
	initialized_ = false;
}

void Game::renderGame()
{
	//Begin a DirectX scene
	if (SUCCEEDED(graphics_->beginScene()))
	{
		//Render is a pure virtual function that must be provided in the
		//inheriting class.
		render(); //Call render in derived class
		//Begin a DirectX scene
		graphics_->endScene();

	}

	handleLostGraphicsDevice();

	//Display the backbuffer on the screen
	graphics_->showBackbuffer();
}

void Game::handleLostGraphicsDevice()
{
	hResult_ = graphics_->getDeviceState();
	if (FAILED(hResult_)) // If graphics device is not in a valid state
	{
		// If the device is lost and not available for reset
		if (hResult_ == D3DERR_DEVICELOST)
		{
			Sleep(100); // Yield CPU time (100 milliseconds)
			return;
		}
		// The device was lost but is now available for reset
		else if (hResult_ == D3DERR_DEVICENOTRESET)
		{
			releaseAll();
			hResult_ = graphics_->reset(); // Attempt to reset graphics device
			if (FAILED(hResult_))// If reset failed
			{
				return;
			}
			resetAll();
		}
		else
		{
			return; // Other device error
		}
	}
}
