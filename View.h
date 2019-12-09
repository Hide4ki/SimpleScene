#pragma once
#define byte win_byte_override
#include <windows.h>
#undef byte
#include "Face.h"

class View
{
private:
	void SetPixel(int, int, COLORREF);
	COLORREF GetPixel(int, int);
public:
	View(int, int);
	~View();
	int Draw(HDC, int, int, int, int, int, int, int, int, DWORD);   
	int GetWidth();
	int GetHeight();
	bool RequestsUpdate();
private:   
	int _width;   
	int _height;   
	int _bytesPerLine;  
	bool _update;
	BITMAPINFOHEADER _infoHead; 
	BYTE* _aBitmapBits;  
	int _imageSize;   
	friend class Model;
	friend class Face;
};

