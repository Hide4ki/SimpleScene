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

enum class CommandBotton { CHANGE_LS, MOVE_L1, MOVE_R1, MOVE_U1, MOVE_D1, MOVE_B1, MOVE_F1, SCALE1M, SCALE1L, ROTATE_CW_X1, ROTATE_ACW_X1, ROTATE_CW_Y1, ROTATE_ACW_Y1, ROTATE_CW_Z1, ROTATE_ACW_Z1, MOVE_L2, MOVE_R2, MOVE_U2, MOVE_D2, MOVE_B2, MOVE_F2, SCALE2M, SCALE2L, ROTATE_CW_X2, ROTATE_ACW_X2, ROTATE_CW_Y2, ROTATE_ACW_Y2, ROTATE_CW_Z2, ROTATE_ACW_Z2, MOVE_L0, MOVE_R0, MOVE_U0, MOVE_D0, MOVE_B0, MOVE_F0, SCALE0M, SCALE0L, ROTATE_CW_X0, ROTATE_ACW_X0, ROTATE_CW_Y0, ROTATE_ACW_Y0, ROTATE_CW_Z0, ROTATE_ACW_Z0
};

class Controller
{
public:
	Controller();
	~Controller();
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
private:
	HDC _hDC;
	HWND _hWinLightX;
	HWND _hWinLightY;
	HWND _hWinLightZ;
	HWND _setLIGHT;
	int _lightX;
	PAINTSTRUCT _ps;
	RECT _rect;
	int _ws, _hs, _wd, _hd;
	int _dX, _dY;
	Model *_model;
	View *_view;
	Viewer *_camera;
	LightSource *_light;
};

