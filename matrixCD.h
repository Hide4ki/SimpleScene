#pragma once
#include "matrix.h"
#include "matrixMOV.h"
#include "matrixSCALE.h"
#include "matrixROTX.h"
#include "matrixROTY.h"
#include "matrixROTZ.h"
#include "point.h"

class matrixCD:matrix
{
public:
	matrixCD(point *a);
	void operator *=(matrixMOV &a);
	void operator *=(matrixSCALE &a);
	void operator *=(matrixROTX &a);
	void operator *=(matrixROTY &a);
	void operator *=(matrixROTZ &a);
	double &matrixCD::operator()(int i, int j) const;
};
