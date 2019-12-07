#include <Windows.h>
#include <iostream>
#include <winuser.h>
#include "Window.h"
#include "Dib.h"
#include "figure.h"
#include "myException.h"

using namespace std;

 
Dib bmp(640, 480);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	Window mainWindow("Scena", hInstance, nCmdShow, WndProc);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;   
	PAINTSTRUCT ps;
	SIZE sz;
	RECT rect;
	static int width, height;
	static point p[8];
	static figure *myFigure = new figure(p);
	COLORREF color;
	static matrixMOV left(-5, 0, 0);
	static matrixMOV right(5, 0, 0);
	static matrixMOV top(0, -5, 0);
	static matrixMOV bottom(0, 5, 0);
	static matrixMOV forward(0, 0, 5);
	static matrixMOV back(0, 0, -5);
	static matrixSCALE less(0.5, 0.5, 0.5);
	static matrixSCALE more(2, 2, 2);
	static matrixROTX leftRX(10);
	static matrixROTX rightRX(-10);
	static matrixROTY leftRY(10);
	static matrixROTY rightRY(-10);
	static matrixROTZ leftRZ(10);
	static matrixROTZ rightRZ(-10);
	int x, y; 
	int ws, hs, wd, hd;
	int dX, dY;
	switch (uMsg) 
	{
	case WM_CREATE:      
		hDC = GetDC(hWnd);
		p[0] = point(100, 100, -25);
		p[1] = point(150, 100, -25);
		p[2] = point(150, 150, -25);
		p[3] = point(100, 150, -25);
		p[4] = point(100, 100, 25);
		p[5] = point(150, 100, 25);
		p[6] = point(150, 150, 25);
		p[7] = point(100, 150, 25);
		myFigure = new figure(p);
		GetClientRect(hWnd, &rect);
		dX = bmp.GetWidth() - rect.right;
		dY = bmp.GetHeight() - rect.bottom;
		GetWindowRect(hWnd, &rect);
		InflateRect(&rect, dX / 2, dY / 2);
		MoveWindow(hWnd, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:      
		hDC = BeginPaint(hWnd, &ps);
		wd = ws = bmp.GetWidth();
		hd = hs = bmp.GetHeight();
		bmp.Draw(hDC, 0, 0, wd, hd, 0, 0, ws, hs, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:      
		PostQuitMessage(0);      
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'r':
			delete myFigure;
			myFigure = new figure(p);
			break;
		case 'q':
			myFigure->move(bottom);
			break;
		case 'w':
			myFigure->move(forward);
			break;
		case 'e':
			myFigure->move(top);
			break;
		case 'a':
			myFigure->move(left);
			break;
		case 's':
			myFigure->move(back);
			break;
		case 'd':
			myFigure->move(right);
			break;
		case 'z':
			myFigure->scale(less);
			break;
		case 'x':
			myFigure->scale(more);
			break;
		case 'y':
			myFigure->rot<matrixROTX>(leftRX);
			break;
		case 'u':
			myFigure->rot<matrixROTX>(rightRX);
			break;
		case 'h':
			myFigure->rot<matrixROTY>(leftRY);
			break;
		case 'j':
			myFigure->rot<matrixROTY>(rightRY);
			break;
		case 'n':
			myFigure->rot<matrixROTZ>(leftRZ);
			break;
		case 'm':
			myFigure->rot<matrixROTZ>(rightRZ);
			break;
		case  27:
			delete myFigure;
			return 0;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	default:      
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}   
	return 0;
}