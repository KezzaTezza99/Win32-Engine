#include <windows.h>
#include <iostream>
#include <debugapi.h>
#include "src/Utilities/BackBuffer.h"
#include "src/Renderers/PixelRenderer.h"
#include "src/Renderers/ShapeRenderer2D.h"
#include "src/Renderers/SpriteRenderer.h"

//TODO: Have a window class that creates the window etc to keep it seperate from the Entry Point

//TODO: Shapes need to scale with fullscreen and window resizing 
#define WIDTH 384
#define HEIGHT 240
#define BPP 32
#define BACK_BUFFER_MEMORY_SIZE (WIDTH * HEIGHT * (BPP / 8))

//TODO: 
// DO I WANT TO RENDER 16BPP INSTEAD OF 1BPP

bool isRunning = true;
BackBuffer backBuffer;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg)
	{
		case WM_SIZE:
		{
			//Getting the size of the users screen
			RECT rect;
			GetClientRect(hwnd, &rect);
			backBuffer.width = rect.right - rect.left;
			backBuffer.height = rect.bottom - rect.top;

			int backBufferSize = backBuffer.width * backBuffer.height * sizeof(unsigned int);

			//Setting the back buffer
			if (backBuffer.memory)
				VirtualFree(backBuffer.memory, 0, MEM_RELEASE);
			backBuffer.memory = VirtualAlloc(0, backBufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			//Initialising the back buffer after creating the window
			backBuffer.pixels.bmiHeader.biSize = sizeof(backBuffer.pixels.bmiHeader);
			backBuffer.pixels.bmiHeader.biWidth = backBuffer.width;
			backBuffer.pixels.bmiHeader.biHeight = backBuffer.height;
			backBuffer.pixels.bmiHeader.biBitCount = BPP;
			backBuffer.pixels.bmiHeader.biCompression = BI_RGB;
			backBuffer.pixels.bmiHeader.biPlanes = 1;

			break;
		}

		case WM_CLOSE:
		{
			isRunning = false;
			break;
		}

		case WM_DESTROY:
		{
			isRunning = false;
			break;
		}
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}	
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Hiding the cursor
	//ShowCursor(false);

	//Creating the window class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window";
	windowClass.lpfnWndProc = window_callback;

	//Registering the class
	RegisterClass(&windowClass);

	//Creating the window - width height
	HWND window = CreateWindow(windowClass.lpszClassName, L"Win32-ENGINE", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	//Creating a context
	HDC hdc = GetDC(window);

	// ---- RENDERERERS ----
	PIXEL32 pixel{ 0 };
	pixel.red = 0xFFFF;

	//Basic Colours RGB
	PIXEL32 RED{ 0 };
	RED.red = 0xFFFF;
	PIXEL32 GREEN{ 0 };
	GREEN.green = 0xFFFF;
	PIXEL32 BLUE{ 0 };
	BLUE.blue = 0xFFFF;

	//Rendering the three pixel colour
	PixelRenderer renderer(&backBuffer);
	renderer.DrawPixel((backBuffer.width / 2) - 1, backBuffer.height / 2, RED);
	renderer.DrawPixel(backBuffer.width / 2, backBuffer.height / 2, GREEN);
	renderer.DrawPixel((backBuffer.width / 2) + 1, backBuffer.height / 2, BLUE);


	//renderer.DrawSquareInPixels(100, 200, 100, 200, pixel);
	//renderer.DrawPixel(backBuffer.width / 2, backBuffer.height / 2, pixel);
	
#pragma region TESTING SPRITES
	// -- TESTING
	//SpriteRenderer sp(&backBuffer);
	//Sprite p = { 0 };
	//OutputDebugStringA((LPCSTR)sp.LoadBitmapFromFile("Assets/Test/test.bmp", &p).c_str());
	//------------


	////Creating the Sprite Renderer
	//SpriteRenderer spriteRenderer(&backBuffer);

	////Loading a 32BPP bitmap
	//DWORD error = ERROR_SUCCESS;
	//Sprite player = { 0 };

	//if ((error = spriteRenderer.LoadBitmapFromFile("Assets/Test/hero.bmpx", &player) == ERROR_SUCCESS))
	//	spriteRenderer.BlitBitmapToBuffer(&player, backBuffer.width / 2, backBuffer.height / 2);
	//
	//if ((error = spriteRenderer.LoadBitmapFromFile("Assets/test.bmp", &player) != ERROR_SUCCESS))
	//{
	//	OutputDebugString(L"I failed due to not loading a bitmap file");
	//}
	//else
	//	spriteRenderer.Blit32BppBitmapToBuffer(&player, 10, 10);
#pragma endregion


	//Gameloop
	while (isRunning)
	{
		MSG message;

		//Handling input
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//Rendering the back-buffer
		StretchDIBits(hdc, 0, 0, backBuffer.width, backBuffer.height, 0, 0,
			backBuffer.width, backBuffer.height, backBuffer.memory, &backBuffer.pixels, DIB_RGB_COLORS, SRCCOPY);
	}
}