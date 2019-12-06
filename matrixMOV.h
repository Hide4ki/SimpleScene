#pragma once
#include "matrix.h"

class matrixMOV:matrix
{
public:
	matrixMOV(double dx, double dy, double dz);
	double &operator()(int i, int j) const;
	void operator = (matrixMOV &myMatrix) const;
};

