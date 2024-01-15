#include "PixelRenderer.h"
#include "../Utilities/Utils.h"

const char* letters[][7] =
{
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",
};

PixelRenderer::PixelRenderer(BackBuffer* _backBuffer)
	: m_backBuffer(_backBuffer) {}

void PixelRenderer::DrawPixel(int _x, int _y, PIXEL32 _colour)
{
	//Probably should check these values dont exceed the bounds of the back buffer to ensure that app doesn't crash
	memcpy((PIXEL32*)m_backBuffer->memory + _x + _y * m_backBuffer->width, &_colour, sizeof(PIXEL32));
}

void PixelRenderer::DrawSquareInPixels(int _bottomLeft, int _bottomRight, int _topLeft, int _topRight, PIXEL32 _colour)
{
	//Clamping the values
	_bottomLeft = ClampValues(0, _bottomLeft, m_backBuffer->width);
	_bottomRight = ClampValues(0, _bottomRight, m_backBuffer->width);
	_topLeft = ClampValues(0, _topLeft, m_backBuffer->height);
	_topRight = ClampValues(0, _topRight, m_backBuffer->height);

	for (int y = _topLeft; y < _topRight; y++)
		for (int x = _bottomLeft; x < _bottomRight; x++)
			memcpy((PIXEL32*)m_backBuffer->memory + x + y * m_backBuffer->width, &_colour, sizeof(PIXEL32));
}