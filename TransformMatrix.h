#pragma once
#include <utility>
#include "Matrix.h"

using namespace std;

class TransformMatrix:public Matrix
{
public:
	TransformMatrix();
	TransformMatrix(const TransformMatrix&);
	TransformMatrix(TransformMatrix&&) noexcept;
	~TransformMatrix() = default;
};

