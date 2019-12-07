#include "Dib.h"

using namespace std;

Dib::Dib(int w, int h)
{  
	_width = w;
	_height = h;
	_bytesPerLine = ((_width * 24 + 31) / 32) * 4;
	_imageSize = _bytesPerLine * _height;
	_infoHead.biSize = sizeof(_infoHead);
	_infoHead.biWidth = _width;
	_infoHead.biHeight = _height;
	_infoHead.biPlanes = 1;
	_infoHead.biBitCount = 24;
	_infoHead.biCompression = BI_RGB;
	_infoHead.biSizeImage = _imageSize;
	_aBitmapBits = new BYTE[_imageSize];
	memset(_aBitmapBits, 0, _imageSize);
}

Dib::~Dib()
{
	if (_aBitmapBits)  
		delete[] _aBitmapBits;  
}

void Dib::SetPixel(int x, int y, COLORREF color)
{
	y %= _height;
	x %= _width;
	int row = y;   
	int col = 3 * x;
	_aBitmapBits[row*_bytesPerLine + col] = GetBValue(color);   
	_aBitmapBits[row*_bytesPerLine + col + 1] = GetGValue(color);   
	_aBitmapBits[row*_bytesPerLine + col + 2] = GetRValue(color);
}

int Dib::Draw(HDC hdc, int xDst, int yDst, int wDst, int hDst, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
{
	return StretchDIBits(hdc, xDst, yDst, wDst, hDst, xSrc, ySrc, wSrc, hSrc, _aBitmapBits, (CONST BITMAPINFO*)&_infoHead, DIB_RGB_COLORS, rop);
}

int Dib::GetWidth()
{
	return _width;
}

int Dib::GetHeight()
{
	return _height;
}
