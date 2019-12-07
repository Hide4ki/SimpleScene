#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include <algorithm>
#include "matrixCD.h"
#include "Dib.h"

#define M 4

using namespace std;

class face
{
	matrixCD *body;
	COLORREF color;
	HDC device;
	bool visible(point *_2D)const;
	void draw(point *_2D, COLORREF color)const;
	void fill(map<int,vector<int>> &a, COLORREF color) const;
public:
	face();
	face(point *p, COLORREF color,HDC d);
	face(const face &myFace);
	~face();
	void display()const;
	void remove()const;
	point centre(void)const;
	void move(matrixMOV &mov);
	void scale(matrixSCALE &scale, matrixMOV &to, matrixMOV &from);
	template<class T> void rot(T &rot, matrixMOV &to, matrixMOV &from);
	void operator = (face &myFace);
};

template<class T>
void face::rot(T &rot, matrixMOV &to, matrixMOV &from)
{
	(*body)*=to;
	(*body)*=rot;
	(*body)*=from;
}