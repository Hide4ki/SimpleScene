#include "Window.h"

Window::Window(LPCSTR windowName, HINSTANCE hInst, int cmdShow, LRESULT(WINAPI*pWndProc)(HWND, UINT, WPARAM, LPARAM), LPCTSTR menuName, int x, int y, int width, int height, UINT classStyle, DWORD windowStyle, HWND hParent)
{
	char szClassName[] = "Window";

	_wc.cbSize = sizeof(_wc);
	_wc.style = classStyle;
	_wc.lpfnWndProc = pWndProc;
	_wc.cbClsExtra = 0;
	_wc.cbWndExtra = 0;
	_wc.hInstance = hInst;
	_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	_wc.lpszMenuName = menuName;
	_wc.lpszClassName = szClassName;
	_wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&_wc))
	{
		char msg[100] = "Cannot register class: ";
		myStrcat(msg, szClassName);
		MessageBox(NULL, msg, "Error", MB_OK);
		return;
	}

	_hWnd = CreateWindow(szClassName, windowName, windowStyle, x, y, width, height, hParent, (HMENU)NULL, hInst, NULL);
	
	if (!_hWnd)
	{
		char text[100] = "Cannot create window: ";
		myStrcat(text, windowName);
		MessageBox(NULL, text, "Error", MB_OK);
		return;
	}
	ShowWindow(_hWnd, cmdShow);
}

HWND Window::GetHWnd()
{
	return _hWnd;
}

Window::~Window()
{
}
