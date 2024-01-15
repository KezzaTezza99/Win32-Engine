#ifndef __PIXEL_RENDERER__
#define __PIXEL_RENDERER__
#include "../Utilities/BackBuffer.h"
#include "../Graphics/32BitPixel.h"

//A simple class that will render pixels and simple 2D shapes in pixels
class PixelRenderer
{
private:
	BackBuffer* m_backBuffer = nullptr;			//Want access to the back buffer created in EntryPoint
	float m_renderScale = 0.01f;				//May want to render certain objects bigger / smaller 

public:
	PixelRenderer(BackBuffer* _backBuffer);
	void DrawPixel(int _x, int _y, PIXEL32 _colour);
	void DrawSquareInPixels(int _bottomLeft, int _bottomRight, int _topLeft, int _topRight, PIXEL32 _colour);
};
#endif // !__PIXEL_RENDERER__