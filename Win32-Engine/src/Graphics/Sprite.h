#ifndef __SPRITE__
#define __SPRITE__
#include <windows.h>

struct Sprite
{
	void* memory;
	BITMAPINFO pixelInfo;
};
#endif // !__SPRITE__