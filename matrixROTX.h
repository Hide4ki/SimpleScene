#pragma once
#include "matrix.h"

class matrixROTX:matrix
{
public:
	matrixROTX(double rot);
	double &operator()(int i, int j) const;
};

