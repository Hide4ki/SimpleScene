#pragma once
#include "CoordinatMatrix.h"

using namespace std;

class PointMatrix: public CoordinatMatrix
{
public:
	PointMatrix();
	PointMatrix(double, double, double);
	PointMatrix(const PointMatrix&);
	PointMatrix(PointMatrix&&);
	void Set(double, double, double);
	~PointMatrix();
};

