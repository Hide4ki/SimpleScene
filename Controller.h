#pragma once
#include <utility>
#define byte win_byte_override
#include <windows.h>
#undef byte
#include "Model.h"
#include "View.h"
#include "Window.h"
#include "Viewer.h"
#include "LightSource.h"

class Controller
{
public:
	Controller();
	~Controller();
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
private:
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	int x, y;
	int ws, hs, wd, hd;
	int dX, dY;
	Model *model;
	View *view;
	Viewer *camera;
	LightSource *light;
};

