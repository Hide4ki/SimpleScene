#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include "Object.h"
#include "CoordinatMatrix.h"
#include "TransformMatrix.h"
#include "Viewer.h"
#include "View.h"
#include "Color.h"
#include "LightSource.h"

class View;
class Object;

class Face
{
private:
	void Fill(map<int, vector<int>> &a, COLORREF color)const;
	void Draw(COLORREF);
	void Generate2D();
	CoordinatMatrix Centre();
public:
	Face() = delete;
	Face(View&, Viewer&, int, COLORREF);
	Face(const Face&);
	Face(Face&&);
	~Face() = default;
	double GetMidZ();
	void Draw();
	void Clear();
	void SetColor(COLORREF);
	void CalculMidZ();
	Face *Shadow(LightSource&);
	CoordinatMatrix *GetSetCoordinats();
	bool Real();
private:
	CoordinatMatrix _vertex;
	CoordinatMatrix _2Dvertex;
	bool _real;
	int _cntVertex;
	double _midZ;
	COLORREF _color;
	View &_canvas;
	Viewer &_camera;
	friend class Object;
};
