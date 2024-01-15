#ifndef __SPRITE_RENDERER__
#define __SPRITE_RENDERER__
#include <stdint.h>
#include <string>
#include "../Utilities/BackBuffer.h"
#include "../Graphics/Sprite.h"

class SpriteRenderer
{
private:
	BackBuffer* m_backBuffer = nullptr;
public:
	SpriteRenderer(BackBuffer* _backBuffer);
	DWORD Load32BppBitmapFromFile(std::string _filename, Sprite* _sprite);
	void Blit32BppBitmapToBuffer(Sprite* _sprite, uint16_t _x, uint16_t _y);
	void BlitBitmapToBuffer(Sprite* _sprite, uint16_t _x, uint16_t _y);

	std::string LoadBitmapFromFile(std::string _filename, Sprite* _sprite);
	//void BlitBitmap(Sprite* _sprite)
};
#endif // !__SPRITE_RENDERER__