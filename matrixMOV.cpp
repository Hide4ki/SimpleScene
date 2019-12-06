#include "matrixMOV.h"

matrixMOV::matrixMOV(double dx, double dy, double dz)
{
	H = 4;
	W = 4;
	body = new double*[H];
	for(int i = 0; i<H; i++)
		body[i] = new double[W];
	body[0][0] = 1;
	body[0][1] = 0;
	body[0][2] = 0;
	body[0][3] = 0;
	body[1][0] = 0;
	body[1][1] = 1;
	body[1][2] = 0;
	body[1][3] = 0;
	body[2][0] = 0;
	body[2][1] = 0;
	body[2][2] = 1;
	body[2][3] = 0;
	body[3][0] = dx;
	body[3][1] = dy;
	body[3][2] = dz;
	body[3][3] = 1;
}

void matrixMOV::operator = (matrixMOV &myMatrix) const
{
	body[3][0] = myMatrix.body[3][0];
	body[3][1] = myMatrix.body[3][1];
	body[3][2] = myMatrix.body[3][2];
}

double &matrixMOV::operator()(int i, int j) const
{
	return body[i][j];
}
