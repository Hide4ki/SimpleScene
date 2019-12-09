#include "Window.h"
#include "Controller.h"

using namespace std;

//Параллелепипед и
//куб
//Построчное
//заполнение
//Алгоритм
//«художника»
//Построение
//«на землю»
//(источник света на конечном расстоянии)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MSG msg;
	Window mainWindow("Scena", hInstance, nCmdShow, WndProc);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

Controller controler;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return controler.WndProc(hWnd, uMsg, wParam, lParam);
}