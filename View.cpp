#include "View.h"

using namespace std;

View::View(int w, int h)
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

View::~View()
{
	delete[] _aBitmapBits;  
}

void View::SetPixel(int x, int y, COLORREF color)
{
	int row = y;   
	int col = 3 * x;
	if (row < _height  && row > 0 && col > 0 && col < _bytesPerLine)
	{
		_aBitmapBits[row*_bytesPerLine + col] = GetBValue(color);
		_aBitmapBits[row*_bytesPerLine + col + 1] = GetGValue(color);
		_aBitmapBits[row*_bytesPerLine + col + 2] = GetRValue(color);
	}
}

COLORREF View::GetPixel(int y, int x)
{
	int row = y;
	int col = 3 * x;
	int blue = 0, green = 0, red = 0;
	if (row < _height  && row > 0 && col > 0 && col < _bytesPerLine)
	{
		blue  = _aBitmapBits[row*_bytesPerLine + col];
		green = _aBitmapBits[row*_bytesPerLine + col + 1];
		red   = _aBitmapBits[row*_bytesPerLine + col + 2];
	}
	return RGB(red, green, blue);
}

int View::Draw(HDC hdc, int xDst, int yDst, int wDst, int hDst, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
{
	return StretchDIBits(hdc, xDst, yDst, wDst, hDst, xSrc, ySrc, wSrc, hSrc, _aBitmapBits, (CONST BITMAPINFO*)&_infoHead, DIB_RGB_COLORS, rop);
}

int View::GetWidth()
{
	return _width;
}

int View::GetHeight()
{
	return _height;
}

bool View::RequestsUpdate()
{
	auto a = _update;
	_update = false;
	return a;
}
