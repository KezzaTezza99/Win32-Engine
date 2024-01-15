#include "SpriteRenderer.h"
#include "../Graphics/32BitPixel.h"

SpriteRenderer::SpriteRenderer(BackBuffer* _backBuffer)
    : m_backBuffer(_backBuffer) {}

DWORD SpriteRenderer::Load32BppBitmapFromFile(std::string _filename, Sprite* _sprite)
{
    DWORD error = ERROR_SUCCESS;
    HANDLE fileHandle = INVALID_HANDLE_VALUE;
    WORD bitmapHeader = 0;
    DWORD pixelDataOffset = 0;
    DWORD numberOfBytesRead = 2;

    if ((fileHandle = CreateFileA(_filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        error = GetLastError();
        return(error);
    }

    //Read the first two bytes of the file to confirm its a bitmap (BM header)
    if (ReadFile(fileHandle, &bitmapHeader, 2, &numberOfBytesRead, NULL) == 0)
    {
        error = GetLastError();
        return(error);
    }

    if (bitmapHeader != 0x4d42) //this is "BM" backwards
    {
        //This isnt a bitmap file that has been read
        error = ERROR_FILE_INVALID;
        return(error);
    }

    //Need to read the file 10 bytes in to get the pixel data
    if (SetFilePointer(fileHandle, 0xA, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        //RE-USING A LOT OF CODE NEED TO KEEP IT DRY
        error = GetLastError();
        return(error);
    }

    //Now try and read the next 4 bytes from the 10th bit (this is now all the pixel data)
    if (ReadFile(fileHandle, &pixelDataOffset, sizeof(DWORD), &numberOfBytesRead, NULL) == 0)
    {
        error = GetLastError();
        return(error);
    }

    //Now reading the bitmap header 
    if (SetFilePointer(fileHandle, 0xE, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        error = GetLastError();
        return(error);
    }

    //Reading the files bitmap header
    if (ReadFile(fileHandle, &_sprite->pixelInfo.bmiHeader, sizeof(BITMAPINFOHEADER), &numberOfBytesRead, NULL) == 0)
    {
        error = GetLastError();
        return(error);
    }

    //Getting the exact pixel size info from the header then allocating memory for that size
    if ((_sprite->memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, _sprite->pixelInfo.bmiHeader.biSizeImage)) == NULL)
    {
        error = ERROR_NOT_ENOUGH_MEMORY;
        return(error);
    }

    //Moving the cursor to the beginning off where the pixel data is set 
    if (SetFilePointer(fileHandle, pixelDataOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        error = GetLastError();
        return(error);
    }

    //Copying the pixel data to memory by reading directly from the file
    if (ReadFile(fileHandle, _sprite->memory, _sprite->pixelInfo.bmiHeader.biSizeImage, &numberOfBytesRead, NULL) == 0)
    {
        //Failed to read the pixel data from the file into memory
        error = GetLastError();
        return(error);
    }

    if (fileHandle && (fileHandle != INVALID_HANDLE_VALUE))
        CloseHandle(fileHandle);

    return(error);
}

void SpriteRenderer::Blit32BppBitmapToBuffer(Sprite* _sprite, uint16_t _x, uint16_t _y)
{
    int32_t startingScreenPixel = ((m_backBuffer->width * m_backBuffer->height) - m_backBuffer->width) - (m_backBuffer->width* _y) + _x;
    int32_t startingBitmapPixel = ((_sprite->pixelInfo.bmiHeader.biWidth * _sprite->pixelInfo.bmiHeader.biHeight) - _sprite->pixelInfo.bmiHeader.biWidth);

    int32_t memoryOffset = 0;
    int32_t bitmapOffset = 0;

    PIXEL32 bitmapPixel = { 0 };
    PIXEL32 backgroundPixel = { 0 };

    for (int16_t yPixel = 0; yPixel < _sprite->pixelInfo.bmiHeader.biHeight; yPixel++)
    {
        for (int16_t xPixel = 0; xPixel < _sprite->pixelInfo.bmiHeader.biHeight; xPixel++)
        {
            memoryOffset = startingScreenPixel + xPixel - (m_backBuffer->width * yPixel);
            bitmapOffset = startingBitmapPixel + xPixel - (_sprite->pixelInfo.bmiHeader.biWidth * yPixel);

            //Copying the current pixel data from the loaded bitmap and storing it in the sprites memory (buffer)
            memcpy_s(&bitmapPixel, sizeof(PIXEL32), (PIXEL32*)_sprite->memory + bitmapOffset, sizeof(PIXEL32));

            if (bitmapPixel.alpha == 255)
            {
                //Copying the pixel data onto the screen buffer (back buffer) 
                memcpy_s((PIXEL32*)m_backBuffer->memory + memoryOffset, sizeof(PIXEL32), &bitmapPixel, sizeof(PIXEL32));
            }
        }
    }
}

void SpriteRenderer::BlitBitmapToBuffer(Sprite* _sprite, uint16_t _x, uint16_t _y)
{
    int32_t startingScreenPixel = ((m_backBuffer->width * m_backBuffer->height) - m_backBuffer->width) - (m_backBuffer->width * _y) + _x;
    //int32_t startingBitmapPixel = ((_sprite->pixelInfo.bmiHeader.biWidth * _sprite->pixelInfo.bmiHeader.biHeight) - _sprite->pixelInfo.bmiHeader.biWidth);
    int32_t startingBitmapPixel = ((_sprite->pixelInfo.bmiHeader.biWidth * _sprite->pixelInfo.bmiHeader.biHeight) - _sprite->pixelInfo.bmiHeader.biWidth);

    int32_t memoryOffset = 0;
    int32_t bitmapOffset = 0;

    PIXEL32 bitmapPixel = { 0 };
    PIXEL32 backgroundPixel = { 0 };

    for (int16_t yPixel = 0; yPixel < _sprite->pixelInfo.bmiHeader.biHeight; yPixel++)
    {
        for (int16_t xPixel = 0; xPixel < _sprite->pixelInfo.bmiHeader.biHeight; xPixel++)
        {
            memoryOffset = startingScreenPixel + xPixel - (m_backBuffer->width * yPixel);
            bitmapOffset = startingBitmapPixel + xPixel - (_sprite->pixelInfo.bmiHeader.biWidth * yPixel);

            //Copying the current pixel data from the loaded bitmap and storing it in the sprites memory (buffer)
            memcpy_s(&bitmapPixel, sizeof(PIXEL32), (PIXEL32*)_sprite->memory + bitmapOffset, sizeof(PIXEL32));

            if (bitmapPixel.alpha == 255)
            {
                //Copying the pixel data onto the screen buffer (back buffer) 
                memcpy_s((PIXEL32*)m_backBuffer->memory + memoryOffset, sizeof(PIXEL32), &bitmapPixel, sizeof(PIXEL32));
            }
        }
    }
}

std::string SpriteRenderer::LoadBitmapFromFile(std::string _filename, Sprite* _sprite)
{
    //TODO: ACTUALLY HANDLE ERRORS INSTEAD OF JUST PRINTING DEBUG STRINGS ----
    
    HANDLE fileHandle = INVALID_HANDLE_VALUE;
    WORD bitmapHeader = 0;
    DWORD pixelDataOffset = 0;
    DWORD numberOfBytesRead = 2;
    std::string error = "Something went wrong: ";

    //Create the file to read
    if ((fileHandle = CreateFileA(_filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        //TODO: Actual logging system
        return error += _filename;
    }

    //Read the first two bytes of the file to confirm its a bitmap (BM header)
    if (ReadFile(fileHandle, &bitmapHeader, 2, &numberOfBytesRead, NULL) == 0)
    {
        return  error += "some bullshit";
    }


    if (bitmapHeader != 0x4d42) //this is "BM" backwards
        return error += "this is a scuffed file";

    //We have got here so the file has been successfully read and is also definitely a BMP file
    //First lets see if we can successfully read the size of the BMP file in bytes
    if (SetFilePointer(fileHandle, 0x12, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        return error += "couldn't read the BMP file size in bytes";

    if (ReadFile(fileHandle, _sprite->memory, _sprite->pixelInfo.bmiHeader.biWidth, &numberOfBytesRead, NULL) == 0)
        return error += "failed to read the width of the BMP file";
   
    int size = _sprite->pixelInfo.bmiHeader.biSize;
    return "the size of the BMP file: " + size;
    //return "success";
}
