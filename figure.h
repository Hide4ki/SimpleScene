#pragma once
#include <Windows.h>
#include "matrixCD.h"
#include "face.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define M 6

using namespace std;

extern matrixMOV from;
extern matrixMOV to;

class figure
{
	face *body;
	HDC device;
	void draw() const;
	void clean() const;
	void setCenterShiftMatrixs() const;
public:
	figure(point *p);
	~figure();
	void move(matrixMOV &mov);
	void scale(matrixSCALE &scale);
	template <class T> void rot(T &rot);
};

template <class T>
void figure::rot(T &rot)
{
	clean();
	setCenterShiftMatrixs();
	for (int i = 0; i < M; i++)
		body[i].rot<T>(rot,to,from);
	draw();		
}