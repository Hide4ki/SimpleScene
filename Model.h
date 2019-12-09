#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include "TransformMatrix.h"
#include "Object.h"
#include "LightSource.h"
#include "Cube.h"
#include "Parallepiped.h"

using namespace std;

enum class Transform { MOVE_L, MOVE_R, MOVE_U, MOVE_D, MOVE_B, MOVE_F, SCALE, ROTATE_CW_X, ROTATE_ACW_X, ROTATE_CW_Y, ROTATE_ACW_Y, ROTATE_CW_Z, ROTATE_ACW_Z };

class Model
{
private:
	static int GenerateId();
	static TransformMatrix GenerateTransformMatrix(Transform, double);
	void Draw();
	void Clear();
	void UpdateView();
public:
	Model(View&, LightSource&);
	~Model() = default;
	void ChangeLightSource(int, int, int);
	int AddObj(TypeObject, Object&&);
	void RemoveObj(int);
	void AloneChangeObj(int, Transform, double);
	void MultiChangeObj(int, TransformMatrix&);
	void AloneChange(Transform, double);
	void MultiChange(TransformMatrix&);
private:
	vector<Object*> _items;
	LightSource &_lightSource;
	double _room[8][4];
	View &_canvas;
};

