#pragma once
#include <utility>
#include "Object.h"
#include "View.h"
#include "PointMatrix.h"
#include "Color.h"

class Model;

class Cube:public Object
{
private:
	Cube(const Object&);
	Cube(Object&&);
public:
	Cube(View&, Viewer&, PointMatrix*);
	Cube() = delete;
	~Cube() = default;
	friend class Model;
};

