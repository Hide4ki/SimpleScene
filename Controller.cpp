#include "Controller.h"

Controller::Controller()
{
	_light = new LightSource(100.0, 100.0, 600.0);
	_view = new View(640, 480);
	_model = new Model(*_view, *_light);
	_camera = new Viewer(1000);

	PointMatrix *tmp1 = new PointMatrix[8];
	tmp1[0](0, 0) = 200.0; tmp1[0](0, 1) = 100.0; tmp1[0](0, 2) = 00.0;
	tmp1[1](0, 0) = 250.0; tmp1[1](0, 1) = 100.0; tmp1[1](0, 2) = 00.0;
	tmp1[2](0, 0) = 250.0; tmp1[2](0, 1) = 150.0; tmp1[2](0, 2) = 00.0;
	tmp1[3](0, 0) = 200.0; tmp1[3](0, 1) = 150.0; tmp1[3](0, 2) = 00.0;
	tmp1[4](0, 0) = 200.0; tmp1[4](0, 1) = 100.0; tmp1[4](0, 2) = 50.0;
	tmp1[5](0, 0) = 250.0; tmp1[5](0, 1) = 100.0; tmp1[5](0, 2) = 50.0;
	tmp1[6](0, 0) = 250.0; tmp1[6](0, 1) = 150.0; tmp1[6](0, 2) = 50.0;
	tmp1[7](0, 0) = 200.0; tmp1[7](0, 1) = 150.0; tmp1[7](0, 2) = 50.0;
	Cube cube(*_view, *_camera, tmp1);
	_model->AddObj(TypeObject::CUBE, move(cube));

	PointMatrix *tmp2 = new PointMatrix[8];
	tmp2[0](0, 0) =  75.0; tmp2[0](0, 1) =  75.0; tmp2[0](0, 2) = 250.0;
	tmp2[1](0, 0) = 125.0; tmp2[1](0, 1) =  75.0; tmp2[1](0, 2) = 250.0;
	tmp2[2](0, 0) = 125.0; tmp2[2](0, 1) = 175.0; tmp2[2](0, 2) = 250.0;
	tmp2[3](0, 0) =  75.0; tmp2[3](0, 1) = 175.0; tmp2[3](0, 2) = 250.0;
	tmp2[4](0, 0) =  75.0; tmp2[4](0, 1) =  75.0; tmp2[4](0, 2) = 300.0;
	tmp2[5](0, 0) = 125.0; tmp2[5](0, 1) =  75.0; tmp2[5](0, 2) = 300.0;
	tmp2[6](0, 0) = 125.0; tmp2[6](0, 1) = 175.0; tmp2[6](0, 2) = 300.0;
	tmp2[7](0, 0) =  75.0; tmp2[7](0, 1) = 175.0; tmp2[7](0, 2) = 300.0;
	Parallepiped parallepiped(*_view, *_camera, tmp2);
	_model->AddObj(TypeObject::PARALLEPIPED, move(parallepiped));

	delete[] tmp1;
	delete[] tmp2;
}

Controller::~Controller()
{
	delete _light;
	delete _camera;
	delete _model;
	delete _view;
}

LRESULT CALLBACK Controller::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			int yBotton = 0;
			int wBotton = 220;
			int hBotton = 20;
			int xBotton1 = 640;
			int xBotton2 = 640 + wBotton;
			_hDC = GetDC(hWnd);
			GetClientRect(hWnd, &_rect);
			_dX = _view->GetWidth() - _rect.right + 2*wBotton;
			_dY = _view->GetHeight() - _rect.bottom + hBotton;
			GetWindowRect(hWnd, &_rect);
			InflateRect(&_rect, _dX / 2, _dY / 2);
			MoveWindow(hWnd, _rect.left, _rect.top, _rect.right - _rect.left, _rect.bottom - _rect.top, TRUE);
			_hWinLightX = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 480, 50, hBotton - 1, hWnd, NULL, NULL, NULL);
			_hWinLightY = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 480, 50, hBotton - 1, hWnd, NULL, NULL, NULL);
			_hWinLightZ = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 480, 50, hBotton - 1, hWnd, NULL, NULL, NULL);
			CreateWindow("Button", "Set place light source", WS_VISIBLE | WS_CHILD, 150, 480, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::CHANGE_LS), NULL, NULL);
			CreateWindow("Button", "Move cube right", WS_VISIBLE | WS_CHILD, xBotton1, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_R1), NULL, NULL);
			CreateWindow("Button", "Move cube left", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_L1), NULL, NULL);
			CreateWindow("Button", "Move cube forward", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_F1), NULL, NULL);
			CreateWindow("Button", "Move cube back", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_B1), NULL, NULL);
			CreateWindow("Button", "Move cube up", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_U1), NULL, NULL);
			CreateWindow("Button", "Move cube down", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_D1), NULL, NULL);
			CreateWindow("Button", "Rotate cube clock wise oX", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_X1), NULL, NULL);
			CreateWindow("Button", "Rotate cube no clock wise oX", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_X1), NULL, NULL);
			CreateWindow("Button", "Rotate cube clock wise oY", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_Y1), NULL, NULL);
			CreateWindow("Button", "Rotate cube no clock wise oY", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_Y1), NULL, NULL);
			CreateWindow("Button", "Rotate cube clock wise oZ", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_Z1), NULL, NULL);
			CreateWindow("Button", "Rotate cube no clock wise oZ", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_Z1), NULL, NULL);
			CreateWindow("Button", "Scale cube X2", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE1M), NULL, NULL);
			CreateWindow("Button", "Scale cube X0.5", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE1L), NULL, NULL);
			CreateWindow("Button", "Move para right", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_R2), NULL, NULL);
			CreateWindow("Button", "Move para left", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_L2), NULL, NULL);
			CreateWindow("Button", "Move para forward", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_F2), NULL, NULL);
			CreateWindow("Button", "Move para back", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_B2), NULL, NULL);
			CreateWindow("Button", "Move para up", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_U2), NULL, NULL);
			CreateWindow("Button", "Move para down", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_D2), NULL, NULL);
			CreateWindow("Button", "Rotate para clock wise oX", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_X2), NULL, NULL);
			CreateWindow("Button", "Rotate para no clock wise oX", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_X2), NULL, NULL);
			CreateWindow("Button", "Rotate para clock wise oY", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_Y2), NULL, NULL);
			CreateWindow("Button", "Rotate para no clock wise oY", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_Y2), NULL, NULL);
			CreateWindow("Button", "Rotate para clock wise oZ", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_Z2), NULL, NULL);
			CreateWindow("Button", "Rotate para no clock wise oZ", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_Z2), NULL, NULL);
			CreateWindow("Button", "Scale para X2", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE2M), NULL, NULL);
			CreateWindow("Button", "Scale para X0.5", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE2L), NULL, NULL);
			CreateWindow("Button", "Move scene right", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_R0), NULL, NULL);
			CreateWindow("Button", "Move scene left", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_L0), NULL, NULL);
			CreateWindow("Button", "Move scene forward", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_F0), NULL, NULL);
			CreateWindow("Button", "Move scene back", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_B0), NULL, NULL);
			CreateWindow("Button", "Move scene up", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_U0), NULL, NULL);
			CreateWindow("Button", "Move scene down", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::MOVE_D0), NULL, NULL);
			CreateWindow("Button", "Rotate scene clock wise oX", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_X0), NULL, NULL);
			CreateWindow("Button", "Rotate scene no clock wise oX", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_X0), NULL, NULL);
			CreateWindow("Button", "Rotate scene clock wise oY", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_Y0), NULL, NULL);
			CreateWindow("Button", "Rotate scene no clock wise oY", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_Y0), NULL, NULL);
			CreateWindow("Button", "Rotate scene clock wise oZ", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_CW_Z0), NULL, NULL);
			CreateWindow("Button", "Rotate scene no clock wise oZ", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::ROTATE_ACW_Z0), NULL, NULL);
			CreateWindow("Button", "Scale scene X2", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE0M), NULL, NULL);
			CreateWindow("Button", "Scale scene X0.5", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE0L), NULL, NULL);
			ReleaseDC(hWnd, _hDC);
			break;
		}
	case WM_COMMAND:
		switch (wParam)
		{
		case static_cast<int>(CommandBotton::CHANGE_LS) :
			{
				char lightX[10];
				char lightY[10];
				char lightZ[10];
				GetWindowText(_hWinLightX, lightX, 10);
				GetWindowText(_hWinLightY, lightY, 10);
				GetWindowText(_hWinLightZ, lightZ, 10);
				_model->ChangeLightSource(atoi(lightX), atoi(lightY), atoi(lightZ));
			}
			SetFocus(hWnd);
			break;
		case static_cast<int>(CommandBotton::MOVE_B0) :
			_model->AloneChange(Transform::MOVE_B, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_D0) :
			_model->AloneChange(Transform::MOVE_D, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_F0) :
			_model->AloneChange(Transform::MOVE_F, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_L0) :
			_model->AloneChange(Transform::MOVE_L, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_R0) :
			_model->AloneChange(Transform::MOVE_R, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_U0) :
			_model->AloneChange(Transform::MOVE_U, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_X0) :
			_model->AloneChange(Transform::ROTATE_ACW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Y0) :
			_model->AloneChange(Transform::ROTATE_ACW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Z0) :
			_model->AloneChange(Transform::ROTATE_ACW_Z, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_X0) :
			_model->AloneChange(Transform::ROTATE_CW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Y0) :
			_model->AloneChange(Transform::ROTATE_CW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Z0) :
			_model->AloneChange(Transform::ROTATE_CW_Z, 10.0);		
		case static_cast<int>(CommandBotton::SCALE0L) :
			_model->AloneChange(Transform::SCALE, 0.5);
			break;
		case static_cast<int>(CommandBotton::SCALE0M) :
			_model->AloneChange(Transform::SCALE, 2);
			break;
			break;
		case static_cast<int>(CommandBotton::MOVE_B1) :
			_model->AloneChangeObj(1, Transform::MOVE_B, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_D1) :
			_model->AloneChangeObj(1, Transform::MOVE_D, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_F1) :
			_model->AloneChangeObj(1, Transform::MOVE_F, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_L1) :
			_model->AloneChangeObj(1, Transform::MOVE_L, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_R1) :
			_model->AloneChangeObj(1, Transform::MOVE_R, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_U1) :
			_model->AloneChangeObj(1, Transform::MOVE_U, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_X1) :
			_model->AloneChangeObj(1, Transform::ROTATE_ACW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Y1) :
			_model->AloneChangeObj(1, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Z1) :
			_model->AloneChangeObj(1, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_X1) :
			_model->AloneChangeObj(1, Transform::ROTATE_CW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Y1) :
			_model->AloneChangeObj(1, Transform::ROTATE_CW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Z1) :
			_model->AloneChangeObj(1, Transform::ROTATE_CW_Z, 10.0);
			break;		
		case static_cast<int>(CommandBotton::SCALE1L) :
			_model->AloneChangeObj(1, Transform::SCALE, 0.5);
			break;
		case static_cast<int>(CommandBotton::SCALE1M) :
			_model->AloneChangeObj(1, Transform::SCALE, 2);
			break;
		case static_cast<int>(CommandBotton::MOVE_B2) :
			_model->AloneChangeObj(2, Transform::MOVE_B, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_D2) :
			_model->AloneChangeObj(2, Transform::MOVE_D, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_F2) :
			_model->AloneChangeObj(2, Transform::MOVE_F, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_L2) :
			_model->AloneChangeObj(2, Transform::MOVE_L, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_R2) :
			_model->AloneChangeObj(2, Transform::MOVE_R, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_U2) :
			_model->AloneChangeObj(2, Transform::MOVE_U, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_X2) :
			_model->AloneChangeObj(2, Transform::ROTATE_ACW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Y2) :
			_model->AloneChangeObj(2, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Z2) :
			_model->AloneChangeObj(2, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_X2) :
			_model->AloneChangeObj(2, Transform::ROTATE_CW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Y2) :
			_model->AloneChangeObj(2, Transform::ROTATE_CW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Z2) :
			_model->AloneChangeObj(2, Transform::ROTATE_CW_Z, 10.0);
			break;		
		case static_cast<int>(CommandBotton::SCALE2L) :
			_model->AloneChangeObj(2, Transform::SCALE, 0.5);
			break;
		case static_cast<int>(CommandBotton::SCALE2M) :
			_model->AloneChangeObj(2, Transform::SCALE, 2);
			break;
		}
		break;
	case WM_PAINT:
		_hDC = BeginPaint(hWnd, &_ps);
		_wd = _ws = _view->GetWidth();
		_hd = _hs = _view->GetHeight();
		_view->Draw(_hDC, 0, 0, _wd, _hd, 0, _hs, _ws, -_hs, SRCCOPY);
		EndPaint(hWnd, &_ps);
		SetFocus(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'q':
			_model->AloneChangeObj(2, Transform::MOVE_B, 10.0);
			break;
		case 'w':
			_model->AloneChangeObj(2, Transform::MOVE_U, 10.0);
			break;
		case 'e':
			_model->AloneChangeObj(2, Transform::MOVE_F, 10.0);
			break;
		case 'a':
			_model->AloneChangeObj(2, Transform::MOVE_L, 10.0);
			break;
		case 's':
			_model->AloneChangeObj(2, Transform::MOVE_D, 10.0);
			break;
		case 'd':
			_model->AloneChangeObj(2, Transform::MOVE_R, 10.0);
			break;
		case 'z':
			_model->AloneChangeObj(2, Transform::SCALE, 0.5);
			break;
		case 'x':
			_model->AloneChangeObj(2, Transform::SCALE, 2.0);
			break;
		case 'r':
			_model->AloneChangeObj(2, Transform::ROTATE_CW_X, 10.0);
			break;
		case 't':
			_model->AloneChangeObj(2, Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'f':
			_model->AloneChangeObj(2, Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'g':
			_model->AloneChangeObj(2, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case 'v':
			_model->AloneChangeObj(2, Transform::ROTATE_CW_Z, 10.0);
			break;
		case 'b':
			_model->AloneChangeObj(2, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case 'A':
			_model->AloneChangeObj(1, Transform::MOVE_L, 10.0);
			break;
		case 'W':
			_model->AloneChangeObj(1, Transform::MOVE_U, 10.0);
			break;
		case 'S':
			_model->AloneChangeObj(1, Transform::MOVE_D, 10.0);
			break;
		case 'Q':
			_model->AloneChangeObj(1, Transform::MOVE_B, 10.0);
			break;
		case 'E':
			_model->AloneChangeObj(1, Transform::MOVE_F, 10.0);
			break;
		case 'D':
			_model->AloneChangeObj(1, Transform::MOVE_R, 10.0);
			break;
		case 'Z':
			_model->AloneChangeObj(1, Transform::SCALE, 2);
			break;
		case 'X':
			_model->AloneChangeObj(1, Transform::SCALE, 0.5);
			break;
		case 'R':
			_model->AloneChangeObj(1, Transform::ROTATE_CW_X, 10.0);
			break;
		case 'T':
			_model->AloneChangeObj(1, Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'F':
			_model->AloneChangeObj(1, Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'G':
			_model->AloneChangeObj(1, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case 'V':
			_model->AloneChangeObj(1, Transform::ROTATE_CW_Z, 10.0);
			break;
		case 'B':
			_model->AloneChangeObj(1, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case '<':
			_model->AloneChange(Transform::MOVE_F, 10.0);
			break;
		case '>':
			_model->AloneChange(Transform::MOVE_B, 10.0);
			break;
		case '{':
			_model->AloneChange(Transform::SCALE, 2);
			break;
		case '}':
			_model->AloneChange(Transform::SCALE, 0.5);
			break;
		case 'i':
			_model->AloneChange(Transform::ROTATE_CW_X, 10.0);
			break;
		case 'o':
			_model->AloneChange(Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'j':
			_model->AloneChange(Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'k':
			_model->AloneChange(Transform::ROTATE_ACW_Y, 10.0);
			break;
		case 'n':
			_model->AloneChange(Transform::ROTATE_CW_Z, 10.0);
			break;
		case 'm':
			_model->AloneChange(Transform::ROTATE_ACW_Z, 10.0);
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_LEFT:
			_model->AloneChange(Transform::MOVE_L, 10.0);
			break;
		case VK_RIGHT:
			_model->AloneChange(Transform::MOVE_R, 10.0);
			break;
		case VK_UP:
			_model->AloneChange(Transform::MOVE_U, 10.0);
			break;
		case VK_DOWN:
			_model->AloneChange(Transform::MOVE_D, 10.0);
			break;
		}
		break;
	default:
		if (_view->RequestsUpdate())
			InvalidateRect(hWnd, NULL, FALSE);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	if (_view->RequestsUpdate())
		InvalidateRect(hWnd, NULL, FALSE);
	return 0;
}