#include "Face.h"

Face::Face(View &canvas, Viewer &camera, int cnt, COLORREF color) : _canvas{ canvas }, _color{ color }, _vertex{ cnt }, _cntVertex{ cnt }, _camera{ camera }, _2Dvertex{ cnt }
{
	real = true;
}

Face::Face(const Face &copyFace):_vertex { copyFace._vertex }, _camera{ copyFace._camera }, _canvas { copyFace._canvas }, _2Dvertex{ copyFace._2Dvertex }
{
	_cntVertex = copyFace._cntVertex;
	_midZ = copyFace._midZ;
	_color = copyFace._color; 
	real = copyFace.real;
}

Face::Face(Face &&moveFace) :_vertex{ move(moveFace._vertex) }, _camera{ moveFace._camera }, _canvas{ moveFace._canvas }, _2Dvertex{ move(moveFace._2Dvertex) }
{
	_cntVertex = moveFace._cntVertex;
	_midZ = moveFace._midZ;
	_color = moveFace._color;
	real = moveFace.real;
}

void Face::Fill(map<int, vector<int>>& a, COLORREF color) const
{
	for (auto i = a.begin(); i != a.end(); i++)
	{
		sort(i->second.begin(), i->second.end());
		for (unsigned int j = 0; j < i->second.size() - 1; j++)
			for (int k = i->second[j]; k < i->second[j + 1]; k++)
				_canvas.SetPixel(k, i->first, color);
	}
}

void Face::Draw(COLORREF color)
{
	Generate2D();
	map<int, vector<int>> points;
	int x1, x2, y1, y2, dx, dy, err, e2, sx, sy;
	for (int i = 0; i < _cntVertex; i++)
	{
		auto i2 = (i + 1 == _cntVertex) ? 0 : i + 1;
		x1 = round(_2Dvertex(i, 0)/ _2Dvertex(i, 3));
		x2 = round(_2Dvertex(i2, 0) / _2Dvertex(i2, 3));
		y1 = round(_2Dvertex(i, 1) / _2Dvertex(i, 3));
		y2 = round(_2Dvertex(i2, 1) / _2Dvertex(i2, 3));
		dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
		dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
		err = (dx > dy ? dx : -dy) / 2;
		e2 = err;
		for (;;)
		{
			if (points.count(y1) == 0)
				points.insert(pair<int, vector<int>>(y1, vector<int>(0)));
			points.find(y1)->second.push_back(x1);
			_canvas.SetPixel(x1, y1, color);
			if (x1 == x2 && y1 == y2)
				break;
			e2 = err;
			if (e2 > -dx)
				err -= dy, x1 += sx;
			if (e2 < dy)
				err += dx, y1 += sy;
		}
	}
	Fill(points, color);
}

void Face::Generate2D()
{	
	//X = x*(zc - zpl)/(zc-z);
	//Y = y*(zc - zpl)/(zc-z);
	//Z = z-zpl;

	double zpl = 400;
    for (int i = 0; i<_cntVertex; i++)
	{
		double k = (_camera.GetZ() - _vertex(i, 2));
		_2Dvertex(i, 0) = _vertex(i, 0)*(_camera.GetZ() - zpl) / k;
		_2Dvertex(i, 1) = _vertex(i, 1)*(_camera.GetZ() - zpl) / k;
		_2Dvertex(i, 2) = _vertex(i, 2) - zpl;
	}
}

CoordinatMatrix Face::Centre()
{
	CoordinatMatrix tmp{1};
	for (int i = 0; i < _cntVertex; i++)
	{
		tmp(0, 0) += _vertex(i, 0);
		tmp(0, 1) += _vertex(i, 1);
		tmp(0, 2) += _vertex(i, 2);
	}
	tmp(0, 0) /= _cntVertex;
	tmp(0, 1) /= _cntVertex;
	tmp(0, 2) /= _cntVertex;
	return tmp;
}

double Face::GetMidZ()
{
	return _midZ;
}

void Face::Draw()
{
	Draw(_color);
}

void Face::Clear()
{
	Draw(0);
}

void Face::SetColor(COLORREF color)
{
	_color = color;
}

void Face::CalculMidZ()
{
	_midZ = (_vertex(0, 2) + _vertex(1, 2) + _vertex(2, 2) + _vertex(3, 2)) / _cntVertex;
}

Face Face::operator()(TransformMatrix &tr)
{
	Face tmp{ *this };
	tmp._vertex *= tr;
	tmp._color = RGB(170, 70, 70);
	tmp.real = false;
	return tmp;
}

CoordinatMatrix * Face::GetSetCoordinats()
{
	return &_vertex;
}
