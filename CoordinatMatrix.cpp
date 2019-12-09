#include "CoordinatMatrix.h"

CoordinatMatrix::CoordinatMatrix(int i) : Matrix{ i, 4 }
{
	for (int j = 0; j < i; j++)
		_body[j][3] = 1;
}

CoordinatMatrix::CoordinatMatrix(const CoordinatMatrix &copyMatrix) : Matrix{ static_cast<const Matrix&>(copyMatrix) }
{
}

CoordinatMatrix::CoordinatMatrix(CoordinatMatrix &&moveMatrix) noexcept : Matrix{ move(static_cast<Matrix&&>(moveMatrix)) }
{
}

CoordinatMatrix & CoordinatMatrix::operator=(const Matrix &copyMatrix)
{
	Matrix::operator=(copyMatrix);
	return *this;
}

CoordinatMatrix & CoordinatMatrix::operator=(const CoordinatMatrix &copyMatrix)
{
	Matrix::operator=(copyMatrix);
	return *this;
}
