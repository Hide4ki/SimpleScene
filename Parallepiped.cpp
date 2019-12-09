#include "Parallepiped.h"

Parallepiped::Parallepiped(View &canvas, Viewer &camera, PointMatrix *f) :Object{ canvas, camera }
{
	_body.push_back(new Face(_canvas, _camera, 4, RED));
	_body.push_back(new Face(_canvas, _camera, 4, WHITE));
	_body.push_back(new Face(_canvas, _camera, 4, ORANGE));
	_body.push_back(new Face(_canvas, _camera, 4, YELLOW));
	_body.push_back(new Face(_canvas, _camera, 4, GREEN));
	_body.push_back(new Face(_canvas, _camera, 4, BLUE));

	CoordinatMatrix a1{ 4 };
	CoordinatMatrix a2{ 4 };
	CoordinatMatrix a3{ 4 };
	CoordinatMatrix a4{ 4 };
	CoordinatMatrix a5{ 4 };
	CoordinatMatrix a6{ 4 };

	for (int i = 0; i < 4; i++)//0 
	{
		a1(0, i) = f[0](0, i);
		a1(1, i) = f[4](0, i);
		a1(2, i) = f[5](0, i);
		a1(3, i) = f[1](0, i);
	}
	for (int i = 0; i < 4; i++)//1
	{
		a2(0, i) = f[0](0, i);
		a2(1, i) = f[1](0, i);
		a2(2, i) = f[2](0, i);
		a2(3, i) = f[3](0, i);
	}
	for (int i = 0; i < 4; i++)//2
	{
		a3(0, i) = f[0](0, i);
		a3(1, i) = f[3](0, i);
		a3(2, i) = f[7](0, i);
		a3(3, i) = f[4](0, i);
	}
	for (int i = 0; i < 4; i++)//3
	{
		a4(0, i) = f[5](0, i);
		a4(1, i) = f[4](0, i);
		a4(2, i) = f[7](0, i);
		a4(3, i) = f[6](0, i);
	}
	for (int i = 0; i < 4; i++)//4
	{
		a5(0, i) = f[1](0, i);
		a5(1, i) = f[5](0, i);
		a5(2, i) = f[6](0, i);
		a5(3, i) = f[2](0, i);
	}
	for (int i = 0; i < 4; i++)//5
	{
		a6(0, i) = f[2](0, i);
		a6(1, i) = f[6](0, i);
		a6(2, i) = f[7](0, i);
		a6(3, i) = f[3](0, i);
	}

	*_body[0]->GetSetCoordinats() = a1;
	*_body[1]->GetSetCoordinats() = a2;
	*_body[2]->GetSetCoordinats() = a3;
	*_body[3]->GetSetCoordinats() = a4;
	*_body[4]->GetSetCoordinats() = a5;
	*_body[5]->GetSetCoordinats() = a6;
	_body[0]->CalculMidZ();
	_body[1]->CalculMidZ();
	_body[2]->CalculMidZ();
	_body[3]->CalculMidZ();
	_body[4]->CalculMidZ();
	_body[5]->CalculMidZ();
}

Parallepiped::Parallepiped(const Object &copyParallepiped) :Object{ copyParallepiped }
{
}

Parallepiped::Parallepiped(Object &&moveParallepiped) : Object{ move(moveParallepiped) }
{
}
