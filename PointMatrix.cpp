#include "PointMatrix.h"

PointMatrix::PointMatrix() :CoordinatMatrix{ 1 }
{
}

PointMatrix::PointMatrix(double x, double y, double z) :CoordinatMatrix{ 1 }
{
	_body[0][0] = x;
	_body[0][1] = y;
	_body[0][2] = z;
}

PointMatrix::PointMatrix(const PointMatrix &copyMatrix) :CoordinatMatrix{ copyMatrix }
{
}

PointMatrix::PointMatrix(PointMatrix &&moveMatrix) : CoordinatMatrix{ moveMatrix }
{
}

void PointMatrix::Set(double x, double y, double z)
{
	_body[0][0] = x;
	_body[0][1] = y;
	_body[0][2] = z;
}

PointMatrix::~PointMatrix()
{
}
