#include "ShapeRenderer2D.h"
#include "../Utilities/Utils.h"

ShapeRenderer2D::ShapeRenderer2D(BackBuffer* _backBuffer)
	: m_backBuffer(_backBuffer) {}

void ShapeRenderer2D::DrawRect(int _bottomLeft, int _topLeft, int _scale, PIXEL32 _colour)
{
	//Clamping the values
	_bottomLeft = ClampValues(0, _bottomLeft, m_backBuffer->width);
	_topLeft = ClampValues(0, _topLeft, m_backBuffer->height);

	//some dog shit code 
	int xScale;
	if (_scale == 1)
		xScale = 2;
	else
		xScale = _scale * _scale;

	xScale = ClampValues(0, xScale, m_backBuffer->width);

	for (int y = _topLeft; y < _topLeft + m_pixelScale * _scale; y++)
		for (int x = _bottomLeft; x < _bottomLeft + m_pixelScale * xScale; x++)
			memcpy((PIXEL32*)m_backBuffer->memory + x + y * m_backBuffer->width, &_colour, sizeof(PIXEL32));
}

//Should come up with a way to make sure that the lengths are equal (make sure its an actual square that is being created?)
void ShapeRenderer2D::DrawSquare(int _bottomLeft, int _bottomRight, int _topLeft, int _topRight, PIXEL32 _colour)
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
