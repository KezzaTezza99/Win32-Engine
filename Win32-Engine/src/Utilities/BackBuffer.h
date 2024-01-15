#ifndef __BACKBUFFER__
#define __BACKBUFFER__
#include <Windows.h>

struct BackBuffer
{
	int width, height;
	void* memory;
	BITMAPINFO pixels;
};
#endif // !__BACKBUFFER__