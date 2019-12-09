#pragma once
#include <utility>
#include "Matrix.h"

using namespace std;

class CoordinatMatrix:public Matrix
{
public:
	CoordinatMatrix() = delete;
	explicit CoordinatMatrix(int);
	CoordinatMatrix(const CoordinatMatrix&);
	CoordinatMatrix(CoordinatMatrix&&) noexcept;
	CoordinatMatrix &operator = (const Matrix&);
	CoordinatMatrix &operator = (const CoordinatMatrix&);
	~CoordinatMatrix() = default;
};

