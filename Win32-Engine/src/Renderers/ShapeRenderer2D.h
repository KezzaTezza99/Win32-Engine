#ifndef __SHAPE_RENDERER_2D__
#define __SHAPE_RENDERER_2D__
#include "../Utilities/BackBuffer.h"
#include "../Graphics/32BitPixel.h"

//A simple class that can render simple 2D shapes
class ShapeRenderer2D
{
private:
	BackBuffer* m_backBuffer = nullptr;			//Want access to the back buffer to draw the shapes too
	int m_pixelScale = 16;
public: 
	ShapeRenderer2D(BackBuffer* _backBuffer);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_bottomLeft"></param>
	/// <param name="_topLeft"></param>
	/// <param name="_scale"></param>
	/// <param name="_colour"></param>
	void DrawRect(int _bottomLeft, int _topLeft, int _scale, PIXEL32 _colour);
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_bottomLeft"></param>
	/// <param name="_bottomRight"></param>
	/// <param name="_topLeft"></param>
	/// <param name="_topRight"></param>
	/// <param name="_colour"></param>
	void DrawSquare(int _bottomLeft, int _bottomRight, int _topLeft, int _topRight, PIXEL32 _colour);
};
#endif // !__SHAPE_RENDERER_2D__