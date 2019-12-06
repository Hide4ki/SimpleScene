#include "matrixSCALE.h"

matrixSCALE::matrixSCALE(double sx, double sy, double sz)
{
	H = 4;
	W = 4;
	body = new double*[H];
	for(int i = 0; i<H; i++)
		body[i] = new double[W];
	body[0][0] = sx;
	body[0][1] = 0;
	body[0][2] = 0;
	body[0][3] = 0;
	body[1][0] = 0;
	body[1][1] = sy;
	body[1][2] = 0;
	body[1][3] = 0;
	body[2][0] = 0;
	body[2][1] = 0;
	body[2][2] = sz;
	body[2][3] = 0;
	body[3][0] = 0;
	body[3][1] = 0;
	body[3][2] = 0;
	body[3][3] = 1;
}

double &matrixSCALE::operator()(int i, int j) const
{
	return body[i][j];
}
