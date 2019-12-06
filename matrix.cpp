#include "matrix.h"

matrix::matrix()
{
}

matrix::matrix(const matrix &myMatrix)
{
	H = myMatrix.H;
	W = myMatrix.W;
	body = new double*[H];
	for(int i = 0; i<H; i++)
	{
		body[i] = new double[W];
		for(int j = 0; j < W; j++)
			body[i][j] = myMatrix.body[i][j];
	}
}

matrix::~matrix(void)
{
	for(int i = 0; i<H; i++)
		delete[] body[i];
	delete[] body;
}
