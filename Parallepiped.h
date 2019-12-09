#pragma once
#include <utility>
#include "Object.h"
#include "View.h"
#include "PointMatrix.h"
#include "Color.h"

class Model;

class Parallepiped :public Object
{
private:
	Parallepiped(const Object&);
	Parallepiped(Object&&);
public:
	explicit Parallepiped(View&, Viewer&, PointMatrix*);
	Parallepiped() = delete;
	~Parallepiped() = default;
	friend class Model;
};

