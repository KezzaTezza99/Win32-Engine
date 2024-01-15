#ifndef __WINDOW_
#define __WINDOW_
#include <windows.h>
#include "../Renderers/Renderer.h"

class Window
{
public:
	bool m_running;										//Is the game currently running?

public:
	HWND m_window;										//Window
	HDC m_context;										//Window Context
	Renderer* m_renderer;								//My Renderer

public:
	Window();
	~Window();

	void Initialise();
	bool IsRunning();
	void SetRunning(bool _isRunning);

	//Getters
	HWND GetWindow();
	HDC GetWindowContext();
	Renderer* GetRenderer() { return m_renderer; }
};
#endif //!__WINDOW_