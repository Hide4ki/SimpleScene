#pragma once
#include "CoordinatMatrix.h"
#include "TransformMatrix.h"

class LightSource
{
private:
	CoordinatMatrix _place;
	LightSource();
	LightSource(double, double, double);
	~LightSource() = default;
public:
	CoordinatMatrix GetPlace();
	void Move(TransformMatrix&);
	friend class Model;
	friend class Controller;
};

