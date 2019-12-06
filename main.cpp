#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "figure.h"
#include "myException.h"

#include "Window.h"
#include "Dib.h"

using namespace std;

point p[8];
figure *myFigure = new figure(p);
matrixMOV left(-5, 0, 0);
matrixMOV right(5, 0, 0);
matrixMOV top(0, -5, 0);
matrixMOV bottom(0, 5, 0);
matrixMOV forward(0, 0, 5);
matrixMOV back(0, 0, -5);
matrixSCALE less(0.5, 0.5, 0.5);
matrixSCALE more(2, 2, 2);
matrixROTX leftRX(10);
matrixROTX rightRX(-10);
matrixROTY leftRY(10);
matrixROTY rightRY(-10);
matrixROTZ leftRZ(10);
matrixROTZ rightRZ(-10);

#define ANSI_CODE  65 
#define FILE_NAME "symbol.bmp"

Dib bmp;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	p[0] = point(100, 100, -25);
	p[1] = point(150, 100, -25);
	p[2] = point(150, 150, -25);
	p[3] = point(100, 150, -25);
	p[4] = point(100, 100, 25);
	p[5] = point(150, 100, 25);
	p[6] = point(150, 150, 25);
	p[7] = point(100, 150, 25);
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
	RECT rect;   
	int dX, dY;   
	int ws, hs, wd, hd;   
	static BOOL isFileLoaded;
	switch (uMsg) 
	{
	case WM_CREATE:      
		hDC = GetDC(hWnd);      
		isFileLoaded = bmp.LoadFromFile(FILE_NAME);
		if (!isFileLoaded) 
		{ 
			MessageBox(hWnd, "file " FILE_NAME " not.", "Error", MB_OK);
			MessageBox(hWnd, bmp.GetError(), "Error", MB_OK);         
			break; 
		}      
		GetClientRect(hWnd, &rect);      
		dX = bmp.GetWidth() - rect.right;      
		dY = bmp.GetHeight() - rect.bottom;      
		GetWindowRect(hWnd, &rect);      
		InflateRect(&rect, dX/2, dY/2);      
		MoveWindow(hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, TRUE);
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
	case WM_KEYDOWN:
		try
		{
			switch (_getch())
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
		}
		catch (myException e)
		{
			cout << e;
		}
	default:      
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}   
	return 0;
}