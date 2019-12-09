#include "Controller.h"

Controller::Controller()
{
	light = new LightSource(-600.0, -600.0, 2000.0);
	view = new View(640, 480);
	model = new Model(*view, *light);
	camera = new Viewer(-1000);
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
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		dX = view->GetWidth() - rect.right;
		dY = view->GetHeight() - rect.bottom;
		GetWindowRect(hWnd, &rect);
		InflateRect(&rect, dX / 2, dY / 2);
		MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		wd = ws = view->GetWidth();
		hd = hs = view->GetHeight();
		view->Draw(hDC, 0, 0, wd, hd, 0, hs, ws, -hs, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'q':
			model->AloneChange(Transform::MOVE_B, 10.0);
			break;
		case 'w':
			model->AloneChange(Transform::MOVE_U, 10.0);
			break;
		case 'e':
			model->AloneChange(Transform::MOVE_F, 10.0);
			break;
		case 'a':
			model->AloneChange(Transform::MOVE_L, 10.0);
			break;
		case 's':
			model->AloneChange(Transform::MOVE_D, 10.0);
			break;
		case 'd':
			model->AloneChange(Transform::MOVE_R, 10.0);
			break;
		case 'z':
			model->AloneChange(Transform::SCALE, 0.5);
			break;
		case 'x':
			model->AloneChange(Transform::SCALE, 2.0);
			break;
		case 'y':
			model->AloneChange(Transform::ROTATE_CW_X, 10.0);
			break;
		case 'u':
			model->AloneChange(Transform::ROTATE_ACW_X, 10.0);
			break;
		case 'h':
			model->AloneChange(Transform::ROTATE_CW_Y, 10.0);
			break;
		case 'j':
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
	default:
		if (view->RequestsUpdate())
			InvalidateRect(hWnd, NULL, FALSE);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	if (view->RequestsUpdate())
		InvalidateRect(hWnd, NULL, FALSE);
	return 0;
}