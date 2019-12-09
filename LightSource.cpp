#include "LightSource.h"

LightSource::LightSource():_place{1}
{
}

LightSource::LightSource(double a, double b, double c) : _place{ 1 }
{
	_place(0, 0) = a;
	_place(0, 1) = b;
	_place(0, 2) = c;
}

CoordinatMatrix LightSource::GetPlace()
{
	return _place;
}

void LightSource::Move(TransformMatrix &A)
{
	_place *= A;
}