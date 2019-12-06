#include "Dib.h"

Dib::Dib()
{
	_fileHeadSize = sizeof(BITMAPFILEHEADER);   
	_fileHead.bfType = 0x4d42;   
	_aBitmapBits = NULL;
}

Dib::~Dib()
{
	if (_pInfoHead)  
		delete[] _pInfoHead;   
	if (_aBitmapBits)  
		delete[] _aBitmapBits;   
	if (_outFile)  
		_outFile.close();
}

BOOL Dib::CreateDib24(int w, int h, const char * fileName)
{
	_width = w;
	_height = h;   
	_bytesPerLine = ((_width * 24 + 31) / 32) * 4;   
	_imageSize = _bytesPerLine * _height;
	_infoHeadSize = sizeof(BITMAPINFOHEADER);   
	_fileHead.bfSize = _fileHeadSize + _infoHeadSize + _bytesPerLine * _height;
	_fileHead.bfOffBits = _fileHeadSize + _infoHeadSize;
	_infoHead.biSize = _infoHeadSize;   
	_infoHead.biWidth = _width;   
	_infoHead.biHeight = _height;   
	_infoHead.biPlanes = 1;   
	_infoHead.biBitCount = 24;   
	_infoHead.biCompression = BI_RGB;   
	_infoHead.biSizeImage = _imageSize;
	_aBitmapBits = new BYTE[_imageSize];   
	memset(_aBitmapBits, 0, _imageSize);
	_outFile.open(fileName, ios::out | ios::binary | ios::trunc);   
	if (!_outFile) 
		return FALSE;   
	else 
		return TRUE;
}

void Dib::StoreDib24()
{
	 _outFile.write((char*)&_fileHead, _fileHeadSize);   
	 _outFile.write((char*)&_infoHead, _infoHeadSize);
	 _outFile.write((char*)_aBitmapBits, _imageSize); 
}

BOOL Dib::LoadFromFile(const char * fileName)
{
	_inputFile.open(fileName, ios::in | ios::binary);   
	if (!_inputFile) 
	{ 
		_error = "File name not right";
		return FALSE; 
	}   
	_inputFile.read((char*)&_fileHead, _fileHeadSize);
	if (_fileHead.bfType != 0x4d42) 
	{
		_error = "That not BMP-file"; 
		return FALSE;
	}   
	_infoHeadSize = _fileHead.bfOffBits - _fileHeadSize;   
	int fileSize = _fileHead.bfSize;   
	_imageSize = fileSize - (_fileHeadSize + _infoHeadSize);
	_pInfoHead = (BITMAPINFOHEADER*)(new BYTE[_infoHeadSize]);   
	_inputFile.read((char*)_pInfoHead, _infoHeadSize);
	_width = _pInfoHead->biWidth;   
	_height = _pInfoHead->biHeight;
	_aBitmapBits = new BYTE[_imageSize];   
	_inputFile.read((char*)_aBitmapBits, _imageSize);   
	return true;
}

void Dib::SetPixel(int x, int y, COLORREF color)
{
	int row = y;   
	int col = 3 * x;
	_aBitmapBits[row*_bytesPerLine + col] = GetBValue(color);   
	_aBitmapBits[row*_bytesPerLine + col + 1] = GetGValue(color);   
	_aBitmapBits[row*_bytesPerLine + col + 2] = GetRValue(color);
}

int Dib::Draw(HDC hdc, int xDst, int yDst, int wDst, int hDst, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
{
	return StretchDIBits(hdc, xDst, yDst, wDst, hDst, xSrc, ySrc, wSrc, hSrc, _aBitmapBits, (CONST BITMAPINFO*)_pInfoHead, DIB_RGB_COLORS, rop);
}

int Dib::GetWidth()
{
	return _width;
}

int Dib::GetHeight()
{
	return _height;
}

const char * Dib::GetError()
{
	return _error.c_str();
}
