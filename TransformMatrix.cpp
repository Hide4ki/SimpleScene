#include "TransformMatrix.h"

TransformMatrix::TransformMatrix() : Matrix{ 4, 4 }
{
	for (int i = 0; i < 4; i++)
		_body[i][i] = 1;
}

TransformMatrix::TransformMatrix(const TransformMatrix &copyMatrix) : Matrix{static_cast<const Matrix&>(copyMatrix)}
{
}

TransformMatrix::TransformMatrix(TransformMatrix &&moveMatrix) noexcept : Matrix{ move(static_cast<Matrix&&>(moveMatrix)) }
{
}
