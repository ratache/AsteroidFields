#include <time.h>
#include <stdio.h>
#include <windows.h>
#include "Engine.h"

#define APPTITLE "AsteroidFields"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

ATOM MyRegisterClass(HINSTANCE);

//entry point for a Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	// register the class
	MyRegisterClass(hInstance);
	//set up the screen in windowed or fullscreen mode?
	DWORD style;
	//style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	style = WS_OVERLAPPED;
	//create a new window
	hWnd = CreateWindow(
		APPTITLE, //window class
		APPTITLE, //title bar
		style, //window style
		CW_USEDEFAULT, //x position of window
		CW_USEDEFAULT, //y position of window
		SCREEN_WIDTH, //width of the window
		SCREEN_HEIGHT, //height of the window
		NULL, //parent window
		NULL, //menu
		hInstance, //application instance
		NULL); //window parameters
	//was there an error creating the window?
	if (!hWnd)
		return FALSE;

	//display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/////////////////////////////////////////////////
	//DIRECTX INITS
	/////////////////////////////////////////////////
	//initialize DirectInput
	if (!Init_Graphics(hWnd)){
		MessageBox(hWnd, "Error initializing Direct3d", "Error", MB_OK);
		return 0;
	}
	if (!Init_DirectInput(hWnd))
	{
		MessageBox(hWnd, "Error initializing DirectInput", "Error", MB_OK);
		return 0;
	}
	if (!Init_DirectSound(hWnd))
	{
		MessageBox(hWnd, "Error initializing DirectSound", "Error", MB_OK);
		return 0;
	}

	//initialize the game
	if (!Game_Init(hWnd))
	{
		MessageBox(hWnd, "Error initializing the game", "Error", MB_OK);
		return 0;
	}
	// main message loop
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//look for quit message
			if (msg.message == WM_QUIT)
				done = 1;
			//decode and pass messages on to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			//process game loop (prevents running after window is closed)
			Game_Run(hWnd);
	}
	return msg.wParam;
}

//window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Game_End(hWnd);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//helper function to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	//fill the struct with info
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;
	//set up the window with the class info
	return RegisterClassEx(&wc);
}