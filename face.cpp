#include "Face.h"

static const int OFFSET = 200;

Face::Face(View &canvas, Viewer &camera, int cnt, COLORREF color) : _canvas{ canvas }, _color{ color }, _vertex{ cnt }, _cntVertex{ cnt }, _camera{ camera }, _2Dvertex{ cnt }
{
	_real = true;
}

Face::Face(const Face &copyFace):_vertex { copyFace._vertex }, _camera{ copyFace._camera }, _canvas { copyFace._canvas }, _2Dvertex{ copyFace._2Dvertex }
{
	_cntVertex = copyFace._cntVertex;
	_midZ = copyFace._midZ;
	_color = copyFace._color; 
	_real = copyFace._real;
}

Face::Face(Face &&moveFace) :_vertex{ move(moveFace._vertex) }, _camera{ moveFace._camera }, _canvas{ moveFace._canvas }, _2Dvertex{ move(moveFace._2Dvertex) }
{
	_cntVertex = moveFace._cntVertex;
	_midZ = moveFace._midZ;
	_color = moveFace._color;
	_real = moveFace._real;
}

void Face::Fill(map<int, vector<int>>& a, COLORREF color) const
{
	//str fill
	for (auto i = a.begin(); i != a.end(); i++)
	{
		sort(i->second.begin(), i->second.end());
		for (unsigned int j = 0; j < i->second.size() - 1; j++)
			for (int k = i->second[j]; k < i->second[j + 1]; k++)
				_canvas.SetPixel(k + OFFSET, i->first + OFFSET, color);
	}
}

void Face::Draw(COLORREF color)
{
	Generate2D();
	//Brezenhem
	map<int, vector<int>> points;
	int x1, x2, y1, y2, dx, dy, err, e2, sx, sy;
	for (int i = 0; i < _cntVertex; i++)
	{
		auto i2 = (i + 1 == _cntVertex) ? 0 : i + 1;
		x1 = static_cast<int>(round(_2Dvertex(i, 0)/ _2Dvertex(i, 3)));
		x2 = static_cast<int>(round(_2Dvertex(i2, 0) / _2Dvertex(i2, 3)));
		y1 = static_cast<int>(round(_2Dvertex(i, 1) / _2Dvertex(i, 3)));
		y2 = static_cast<int>(round(_2Dvertex(i2, 1) / _2Dvertex(i2, 3)));
		dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
		dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
		err = (dx > dy ? dx : -dy) / 2;
		e2 = err;
		for (;;)
		{
			if (points.count(y1) == 0)
				points.insert(pair<int, vector<int>>(y1, vector<int>(0)));
			points.find(y1)->second.push_back(x1);
			_canvas.SetPixel(x1 + OFFSET, y1 + OFFSET, color);
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

Face *Face::Shadow(LightSource &lightSource)
{
	// xs = (xl*zp - xp*zp)/(zp - zl)
	// ys = (yl*zp - yp*zp)/(zp - zl)
	// zs = 0

	auto l = lightSource.GetPlace();
	Face *shadow = new Face{ *this };
	shadow->SetColor(RGB(170, 70, 70));

	auto tmp = shadow->GetSetCoordinats();

	for (int i = 0; i < 4; i++)
	{
		(*tmp)(i, 0) = ((*tmp)(i, 2)*(l)(0, 0) - (*tmp)(i, 0)*(l)(0, 2)) / ((*tmp)(i, 2) - (l)(0, 2));
		(*tmp)(i, 1) = ((*tmp)(i, 2)*(l)(0, 1) - (*tmp)(i, 1)*(l)(0, 2)) / ((*tmp)(i, 2) - (l)(0, 2));
		(*tmp)(i, 2) = 0;
	}

	shadow->CalculMidZ();
	return shadow;
}

void Face::SetColor(COLORREF color)
{
	_color = color;
}

void Face::CalculMidZ()
{
	_midZ = (_vertex(0, 2) + _vertex(1, 2) + _vertex(2, 2) + _vertex(3, 2)) / _cntVertex;
}

CoordinatMatrix * Face::GetSetCoordinats()
{
	return &_vertex;
}

bool Face::Real()
{
	return _real;
}
