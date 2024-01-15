#ifndef __RENDERER_
#define __RENDERER_
#include <Windows.h>
#include "../Utilities/Utils.h"

//This renderer will be responsible for drawing shapes using Pixels eventually I'll have a renderer 
//thats capable of rendering sprites and text 

class Renderer
{
private:
	//Storing some info about the back buffer
	void* m_bufferMemory;
	int m_bufferHeight;
	int m_bufferWidth;
	BITMAPINFO m_bufferBitmapInfo;

	//Bitmap Handler
	HBITMAP m_bitmap;

	//Window Handler 
	HWND m_window;

public:
	void Initialise();									//Initialising the renderer
	void CreateBuffers(HWND hwnd);						//Creating the back buffer

	//Helper Methods
	void ClearBackBuffer();								//Clearing the back buffer helpful for clearing the screen quickly
	void SetBackground(u32 colour);						//Handy method for setting the backgroud colour for the back buffer

	//TODO: Have an option to just draw the wireframe of a shape
	void DrawPixel(int _x, int _y, u32 _colour);
	void DrawLine(int _startingPoint, int _endPoint, u32 _colour);
	void DrawRectInPixels(int _bottomLeft, int _bottomRight, int _topLeft, int _topRight, u32 _colour);
	void DrawRect(float x, float y, float xHalfSize, float yHalfSize, u32 colour);
	void DrawCircle(int _radius, int _x, int _y, u32 _colour);

	//TODO: 
	//void DrawText
	//void Draw16BPPSprite

	//Usesful to ensure no memory leaks or crashes casued by rendering outside of the allocated memory of the back buffer
	int GetBufferHeight();
	int GetBufferWidth();
	void* GetMemoryBuffer();							//Helpful for getting the memory allocated to the back buffer
	BITMAPINFO GetBitmapBufferInfo();					//Allows easy access to all of the info above for simplicity

	//Handy methods for easier drawing to the centre of the screen (X, Y)
	int GetCentreX();
	int GetCentreY();
};
#endif //!__RENDERER_