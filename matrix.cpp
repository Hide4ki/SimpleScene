#include "Matrix.h"

Matrix::Matrix(size_t h, size_t w) :_h{ h }, _w{ w }
{
	_body = new double*[_h];
	for (size_t i = 0; i < _h; i++)
	{
		_body[i] = new double[_w];
		for (size_t j = 0; j < _w; j++)
			_body[i][j] = 0;
	}
}

Matrix::Matrix(Matrix &&moveMatrix) noexcept :_h{ moveMatrix._h }, _w{ moveMatrix._w }
{
	_body = moveMatrix._body;
	moveMatrix._body = nullptr;
}

Matrix::Matrix(const Matrix &copyMatrix) :_h{ copyMatrix._h }, _w{ copyMatrix._w }
{
	_body = new double*[_h];
	for(size_t i = 0; i < _h; i++)
	{
		_body[i] = new double[_w];
		for(size_t j = 0; j < _w; j++)
			_body[i][j] = copyMatrix._body[i][j];
	}
}

Matrix & Matrix::operator=(const Matrix &copyMatrix)
{
	for (size_t i = 0; i < _h; i++)
	{
		delete[] _body[i];
	}
	delete[] _body;
	_h = copyMatrix._h;
	_w = copyMatrix._w;
	
	_body = new double*[_h];
	for (size_t i = 0; i < _h; i++)
	{
		_body[i] = new double[_w];
		for (size_t j = 0; j < _w; j++)
			_body[i][j] = copyMatrix._body[i][j];
	}
	return *this;
}

Matrix & Matrix::operator=(Matrix &&moveMatrix) noexcept
{
	_h = moveMatrix._h;
	_w = moveMatrix._w;	
	_body = moveMatrix._body;
	moveMatrix._body = nullptr;
	return *this;
}

Matrix Matrix::operator*(Matrix &B) 
{
	Matrix &A = *this;
	Matrix C(A._h, B._w);
	for (size_t i = 0; i < A._h; ++i)
		for (size_t j = 0; j < B._w; ++j)
		{
			C(i, j) = 0;
			for (size_t k = 0; k < A._w; ++k)
				C(i, j) += A(i, k) * B(k, j);
		}
	return C;
}

Matrix & Matrix::operator*=(Matrix &B)
{
	Matrix A = *this;
	Matrix &C = *this;
	for (size_t i = 0; i < A._h; ++i)
		for (size_t j = 0; j < B._w; ++j)
		{
			C(i, j) = 0;
			for (size_t k = 0; k < A._w; ++k)
			{
				A(i, k);
				B(k, j);
				C(i, j) += A(i, k) * B(k, j);
				C(i, j);
			}
		}
	return C;
}

double &Matrix::operator()(int i, int j)
{
	return _body[i][j];
}

Matrix::~Matrix(void)
{
	for(size_t i = 0; i<_h; i++)
		if(_body)
			delete[] _body[i];
	delete[] _body;
}