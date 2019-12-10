#include "Controller.h"

Controller::Controller()
{
	light = new LightSource(100.0, 100.0, 600.0);
	view = new View(640, 480);
	model = new Model(*view, *light);
	camera = new Viewer(1000);
	PointMatrix *tmp1 = new PointMatrix[8];
	tmp1[0](0, 0) = 200.0; tmp1[0](0, 1) = 100.0; tmp1[0](0, 2) = 150.0;
	tmp1[1](0, 0) = 250.0; tmp1[1](0, 1) = 100.0; tmp1[1](0, 2) = 150.0;
	tmp1[2](0, 0) = 250.0; tmp1[2](0, 1) = 150.0; tmp1[2](0, 2) = 150.0;
	tmp1[3](0, 0) = 200.0; tmp1[3](0, 1) = 150.0; tmp1[3](0, 2) = 150.0;
	tmp1[4](0, 0) = 200.0; tmp1[4](0, 1) = 100.0; tmp1[4](0, 2) = 200.0;
	tmp1[5](0, 0) = 250.0; tmp1[5](0, 1) = 100.0; tmp1[5](0, 2) = 200.0;
	tmp1[6](0, 0) = 250.0; tmp1[6](0, 1) = 150.0; tmp1[6](0, 2) = 200.0;
	tmp1[7](0, 0) = 200.0; tmp1[7](0, 1) = 150.0; tmp1[7](0, 2) = 200.0;
	Cube cube(*view, *camera, tmp1);
	model->AddObj(TypeObject::CUBE, move(cube));

	PointMatrix *tmp2 = new PointMatrix[8];
	tmp2[0](0, 0) = 75.0; tmp2[0](0, 1) = 75.0; tmp2[0](0, 2) = 250.0;
	tmp2[1](0, 0) = 125.0; tmp2[1](0, 1) = 75.0; tmp2[1](0, 2) = 250.0;
	tmp2[2](0, 0) = 125.0; tmp2[2](0, 1) = 175.0; tmp2[2](0, 2) = 250.0;
	tmp2[3](0, 0) = 75.0; tmp2[3](0, 1) = 175.0; tmp2[3](0, 2) = 250.0;
	tmp2[4](0, 0) = 75.0; tmp2[4](0, 1) = 75.0; tmp2[4](0, 2) = 300.0;
	tmp2[5](0, 0) = 125.0; tmp2[5](0, 1) = 75.0; tmp2[5](0, 2) = 300.0;
	tmp2[6](0, 0) = 125.0; tmp2[6](0, 1) = 175.0; tmp2[6](0, 2) = 300.0;
	tmp2[7](0, 0) = 75.0; tmp2[7](0, 1) = 175.0; tmp2[7](0, 2) = 300.0;
	Parallepiped parallepiped(*view, *camera, tmp2);
	model->AddObj(TypeObject::PARALLEPIPED, move(parallepiped));

	delete[] tmp1;
	delete[] tmp2;
}

Controller::~Controller()
{
	delete camera;
	delete model;
	delete view;
}

LRESULT CALLBACK Controller::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		int yBotton = 0;
		int wBotton = 220;
		int hBotton = 17;
		int xBotton1 = 640;
		int xBotton2 = 640 + wBotton;
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		dX = view->GetWidth() - rect.right + 2*wBotton;
		dY = view->GetHeight() - rect.bottom + hBotton;
		GetWindowRect(hWnd, &rect);
		InflateRect(&rect, dX / 2, dY / 2);
		MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		hWinLightX = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 480, 50, 15, hWnd, NULL, NULL, NULL);
		hWinLightY = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 480, 50, 15, hWnd, NULL, NULL, NULL);
		hWinLightZ = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 480, 50, 15, hWnd, NULL, NULL, NULL);
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
		CreateWindow("Button", "Scale scene X0", WS_VISIBLE | WS_CHILD, xBotton1, yBotton += hBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE0M), NULL, NULL);
		CreateWindow("Button", "Scale scene X0.5", WS_VISIBLE | WS_CHILD, xBotton2, yBotton, wBotton, hBotton, hWnd, (HMENU)static_cast<int>(CommandBotton::SCALE0L), NULL, NULL);
		ReleaseDC(hWnd, hDC);
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
				GetWindowText(hWinLightX, lightX, 10);
				GetWindowText(hWinLightY, lightY, 10);
				GetWindowText(hWinLightZ, lightZ, 10);
				model->ChangeLightSource(atoi(lightX), atoi(lightY), atoi(lightZ));
			}
			SetFocus(hWnd);
			break;
		case static_cast<int>(CommandBotton::MOVE_B0) :
			model->AloneChange(Transform::MOVE_B, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_D0) :
			model->AloneChange(Transform::MOVE_D, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_F0) :
			model->AloneChange(Transform::MOVE_F, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_L0) :
			model->AloneChange(Transform::MOVE_L, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_R0) :
			model->AloneChange(Transform::MOVE_R, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_U0) :
			model->AloneChange(Transform::MOVE_U, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_X0) :
			model->AloneChange(Transform::ROTATE_ACW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Y0) :
			model->AloneChange(Transform::ROTATE_ACW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Z0) :
			model->AloneChange(Transform::ROTATE_ACW_Z, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_X0) :
			model->AloneChange(Transform::ROTATE_CW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Y0) :
			model->AloneChange(Transform::ROTATE_CW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Z0) :
			model->AloneChange(Transform::ROTATE_CW_Z, 10.0);		
		case static_cast<int>(CommandBotton::SCALE0L) :
			model->AloneChange(Transform::SCALE, 0.5);
			break;
		case static_cast<int>(CommandBotton::SCALE0M) :
			model->AloneChange(Transform::SCALE, 2);
			break;
			break;
		case static_cast<int>(CommandBotton::MOVE_B1) :
			model->AloneChangeObj(1, Transform::MOVE_B, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_D1) :
			model->AloneChangeObj(1, Transform::MOVE_D, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_F1) :
			model->AloneChangeObj(1, Transform::MOVE_F, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_L1) :
			model->AloneChangeObj(1, Transform::MOVE_L, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_R1) :
			model->AloneChangeObj(1, Transform::MOVE_R, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_U1) :
			model->AloneChangeObj(1, Transform::MOVE_U, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_X1) :
			model->AloneChangeObj(1, Transform::ROTATE_ACW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Y1) :
			model->AloneChangeObj(1, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Z1) :
			model->AloneChangeObj(1, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_X1) :
			model->AloneChangeObj(1, Transform::ROTATE_CW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Y1) :
			model->AloneChangeObj(1, Transform::ROTATE_CW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Z1) :
			model->AloneChangeObj(1, Transform::ROTATE_CW_Z, 10.0);
			break;		
		case static_cast<int>(CommandBotton::SCALE1L) :
			model->AloneChangeObj(1, Transform::SCALE, 0.5);
			break;
		case static_cast<int>(CommandBotton::SCALE1M) :
			model->AloneChangeObj(1, Transform::SCALE, 2);
			break;
		case static_cast<int>(CommandBotton::MOVE_B2) :
			model->AloneChangeObj(2, Transform::MOVE_B, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_D2) :
			model->AloneChangeObj(2, Transform::MOVE_D, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_F2) :
			model->AloneChangeObj(2, Transform::MOVE_F, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_L2) :
			model->AloneChangeObj(2, Transform::MOVE_L, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_R2) :
			model->AloneChangeObj(2, Transform::MOVE_R, 10.0);
			break;
		case static_cast<int>(CommandBotton::MOVE_U2) :
			model->AloneChangeObj(2, Transform::MOVE_U, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_X2) :
			model->AloneChangeObj(2, Transform::ROTATE_ACW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Y2) :
			model->AloneChangeObj(2, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_ACW_Z2) :
			model->AloneChangeObj(2, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_X2) :
			model->AloneChangeObj(2, Transform::ROTATE_CW_X, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Y2) :
			model->AloneChangeObj(2, Transform::ROTATE_CW_Y, 10.0);
			break;
		case static_cast<int>(CommandBotton::ROTATE_CW_Z2) :
			model->AloneChangeObj(2, Transform::ROTATE_CW_Z, 10.0);
			break;		
		case static_cast<int>(CommandBotton::SCALE2L) :
			model->AloneChangeObj(2, Transform::SCALE, 0.5);
			break;
		case static_cast<int>(CommandBotton::SCALE2M) :
			model->AloneChangeObj(2, Transform::SCALE, 2);
			break;
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetWindowText;
		wd = ws = view->GetWidth();
		hd = hs = view->GetHeight();
		view->Draw(hDC, 0, 0, wd, hd, 0, hs, ws, -hs, SRCCOPY);
		EndPaint(hWnd, &ps);
		SetFocus(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'q':
			model->AloneChangeObj(2, Transform::MOVE_B, 10.0);
			break;
		case 'w':
			model->AloneChangeObj(2, Transform::MOVE_U, 10.0);
			break;
		case 'e':
			model->AloneChangeObj(2, Transform::MOVE_F, 10.0);
			break;
		case 'a':
			model->AloneChangeObj(2, Transform::MOVE_L, 10.0);
			break;
		case 's':
			model->AloneChangeObj(2, Transform::MOVE_D, 10.0);
			break;
		case 'd':
			model->AloneChangeObj(2, Transform::MOVE_R, 10.0);
			break;
		case 'z':
			model->AloneChangeObj(2, Transform::SCALE, 0.5);
			break;
		case 'x':
			model->AloneChangeObj(2, Transform::SCALE, 2.0);
			break;
		case 'r':
			model->AloneChangeObj(2, Transform::ROTATE_CW_X, 10.0);
			break;
		case 't':
			model->AloneChangeObj(2, Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'f':
			model->AloneChangeObj(2, Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'g':
			model->AloneChangeObj(2, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case 'v':
			model->AloneChangeObj(2, Transform::ROTATE_CW_Z, 10.0);
			break;
		case 'b':
			model->AloneChangeObj(2, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case 'A':
			model->AloneChangeObj(1, Transform::MOVE_L, 10.0);
			break;
		case 'W':
			model->AloneChangeObj(1, Transform::MOVE_U, 10.0);
			break;
		case 'S':
			model->AloneChangeObj(1, Transform::MOVE_D, 10.0);
			break;
		case 'Q':
			model->AloneChangeObj(1, Transform::MOVE_B, 10.0);
			break;
		case 'E':
			model->AloneChangeObj(1, Transform::MOVE_F, 10.0);
			break;
		case 'D':
			model->AloneChangeObj(1, Transform::MOVE_R, 10.0);
			break;
		case 'Z':
			model->AloneChangeObj(1, Transform::SCALE, 2);
			break;
		case 'X':
			model->AloneChangeObj(1, Transform::SCALE, 0.5);
			break;
		case 'R':
			model->AloneChangeObj(1, Transform::ROTATE_CW_X, 10.0);
			break;
		case 'T':
			model->AloneChangeObj(1, Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'F':
			model->AloneChangeObj(1, Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'G':
			model->AloneChangeObj(1, Transform::ROTATE_ACW_Y, 10.0);
			break;
		case 'V':
			model->AloneChangeObj(1, Transform::ROTATE_CW_Z, 10.0);
			break;
		case 'B':
			model->AloneChangeObj(1, Transform::ROTATE_ACW_Z, 10.0);
			break;
		case '<':
			model->AloneChange(Transform::MOVE_F, 10.0);
			break;
		case '>':
			model->AloneChange(Transform::MOVE_B, 10.0);
			break;
		case '{':
			model->AloneChange(Transform::SCALE, 2);
			break;
		case '}':
			model->AloneChange(Transform::SCALE, 0.5);
			break;
		case 'i':
			model->AloneChange(Transform::ROTATE_CW_X, 10.0);
			break;
		case 'o':
			model->AloneChange(Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'j':
			model->AloneChange(Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'k':
			model->AloneChange(Transform::ROTATE_ACW_Y, 10.0);
			break;
		case 'n':
			model->AloneChange(Transform::ROTATE_CW_Z, 10.0);
			break;
		case 'm':
			model->AloneChange(Transform::ROTATE_ACW_Z, 10.0);
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_LEFT:
			model->AloneChange(Transform::MOVE_L, 10.0);
			break;
		case VK_RIGHT:
			model->AloneChange(Transform::MOVE_R, 10.0);
			break;
		case VK_UP:
			model->AloneChange(Transform::MOVE_U, 10.0);
			break;
		case VK_DOWN:
			model->AloneChange(Transform::MOVE_D, 10.0);
			break;
		}
		break;
	default:
		if (view->RequestsUpdate())
			InvalidateRect(hWnd, NULL, FALSE);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	if (view->RequestsUpdate())
		InvalidateRect(hWnd, NULL, FALSE);
	return 0;
}