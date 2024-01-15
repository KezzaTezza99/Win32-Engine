#include "Window.h"

Window* window;

HANDLE hImg = NULL;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			window->SetRunning(false);
			break;
		}
		case WM_DESTROY:
		{
			window->SetRunning(false);
			break;
		}
		case WM_SIZE:
		{
			window->m_renderer->CreateBuffers(hwnd);
			break;
		}
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

Window::Window()
{
	window = this;
	m_running = true;
	m_renderer = new Renderer();
	m_renderer->Initialise();
	Initialise();
}

Window::~Window() { m_running = false; }

bool Window::IsRunning() { return m_running; }

void Window::SetRunning(bool _isRunning) { m_running = _isRunning; }

void Window::Initialise()
{
	//Create Window Class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window";
	windowClass.lpfnWndProc = window_callback;

	//Register Class
	RegisterClass(&windowClass);

	//Create Window
	m_window = CreateWindow(windowClass.lpszClassName, L"WIN32-Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
		CW_USEDEFAULT, 1280, 720, 0, 0, 0, 0);

	//Creating a Context
	m_context = GetDC(m_window);
}

HWND Window::GetWindow() { return m_window; }
HDC Window::GetWindowContext() { return m_context; }