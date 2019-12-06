#pragma once
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

class Dib
{
public:
	Dib();
	~Dib();
	BOOL CreateDib24(int w, int h, const char* fileName);   
	void StoreDib24();   
	BOOL LoadFromFile(const char* fileName);   
	void SetPixel(int x, int y, COLORREF color);   
	int Draw(HDC hdc, int xDst, int yDst, int wDst, int hDst, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);   
	int GetWidth();
	int GetHeight();
	const char* GetError();
private:   
	int _width;   
	int _height;   
	int _bytesPerLine;   
	BITMAPFILEHEADER _fileHead;   
	BITMAPINFOHEADER _infoHead;
	BITMAPINFOHEADER* _pInfoHead;   
	BYTE* _aBitmapBits;  
	int _fileHeadSize;   
	int _infoHeadSize;
	int _imageSize;   
	string _error;
	ifstream _inputFile;   
	ofstream _outFile;
};

