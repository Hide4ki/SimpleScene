#pragma once
#define byte win_byte_override
#include <Windows.h>
#undef byte
#include "string.h"

class Window
{
private:
	HWND _hWnd;
	WNDCLASSEX _wc;
public:
	Window(LPCSTR windowName, HINSTANCE hInst, int cmdShow, LRESULT(WINAPI *pWndProc)(HWND, UINT, WPARAM, LPARAM), LPCTSTR menuName = NULL, int x = CW_USEDEFAULT, int y = 0, int width = CW_USEDEFAULT, int height = 0, UINT classStyle = CS_HREDRAW | CS_VREDRAW, DWORD windowStyle = WS_OVERLAPPEDWINDOW, HWND hParent = NULL);
	HWND GetHWnd();
	~Window();
};
