#pragma once
#include "matrix.h"

class matrixSCALE:matrix
{
public:
	matrixSCALE(double sx, double sy, double sz);
	double &operator()(int i, int j) const;
};

