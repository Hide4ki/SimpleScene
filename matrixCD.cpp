#include "matrixCD.h"

matrixCD::matrixCD(point *a)
{
	H = 8;
	W = 4;
	body = new double*[H];
	for (int i = 0; i < H; i++)
	{
		body[i] = new double[W];
		body[i][0] = a[i].getx();
		body[i][1] = a[i].gety();
		body[i][2] = a[i].getz();
		body[i][3] = 1;
	}
}

void matrixCD::operator *=(matrixMOV &a)
{
	for (int i = 0; i < H; i++)
	{
		body[i][0] += a(3, 0);
		body[i][1] += a(3, 1);
		body[i][2] += a(3, 2);
	}
}

void matrixCD::operator *=(matrixSCALE &a)
{
	for (int i = 0; i < H; i++)
	{
		body[i][0] *= a(0, 0);
		body[i][1] *= a(1, 1);
		body[i][2] *= a(2, 2);
	}
}

void matrixCD::operator *=(matrixROTX &a)
{
	for (int i = 0; i < H; i++)
	{
		double tmp = body[i][1] * a(1, 1) + body[i][2] * a(1, 2);
		body[i][2] = body[i][1] * a(2, 1) + body[i][2] * a(2, 2);
		body[i][1] = tmp;
	}
}

void matrixCD::operator *=(matrixROTY &a)
{
	for (int i = 0; i < H; i++)
	{
		double tmp = body[i][0] * a(0, 0) + body[i][2] * a(2, 0);
		body[i][2] = body[i][0] * a(0, 2) + body[i][2] * a(2, 2);
		body[i][0] = tmp;
	}
}

void matrixCD::operator *=(matrixROTZ &a)
{
	for (int i = 0; i < H; i++)
	{
		double tmp = body[i][0] * a(0, 0) + body[i][1] * a(1, 0);
		body[i][1] = body[i][0] * a(0, 1) + body[i][1] * a(1, 1);
		body[i][0] = tmp;
	}
}
double &matrixCD::operator()(int i, int j) const
{
	return body[i][j];
}