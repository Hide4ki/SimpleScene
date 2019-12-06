#pragma once
#include "matrix.h"

class matrixROTY:matrix
{
public:
	matrixROTY(double rot);
	double &operator()(int i, int j) const;
};

