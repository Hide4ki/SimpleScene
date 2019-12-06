#pragma once
#include "matrix.h"

class matrixROTZ:matrix
{
public:
	matrixROTZ(double rot);
	double &operator()(int i, int j) const;
};

