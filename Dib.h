#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class Dib
{
public:
	Dib(int, int);
	~Dib();
	void SetPixel(int x, int y, COLORREF color);   
	int Draw(HDC hdc, int xDst, int yDst, int wDst, int hDst, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);   
	int GetWidth();
	int GetHeight();
private:   
	int _width;   
	int _height;   
	int _bytesPerLine;   
	BITMAPINFOHEADER _infoHead; 
	BYTE* _aBitmapBits;  
	int _imageSize;   
};

