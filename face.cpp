#include "face.h"
#define round(x) floor((x)+0.5)

face::face()
{
}

face::face(point *p, COLORREF c,HDC d)
{
	device = d;
	body = new matrixCD(p);
	color = c;
}

face::face(const face &myFace)
{
	device = myFace.device;
	body = new matrixCD(*myFace.body);
	color = myFace.color;
}

void face::operator = (face &myFace)
{
	device = myFace.device;
	body = new matrixCD(*myFace.body);
	color = myFace.color;
}

face::~face()
{
	delete body;
}
	
void generate2Dpoint(matrixCD *_3D, point *_2D)
{
	//X = x*(zc - zpl)/(zc-z);
	//Y = y*(zc - zpl)/(zc-z);
	//Z = z-zpl;
	static const double zc = -1000.0;//z camera;
	static const double zpl = -50.0;//z plane;
	for(int i = 0; i<M; i++)
	{	
		double k = (zc - (*_3D)(i,2));
		k = (k==0)? -1 : k;
		_2D[i] = point((*_3D)(i,0)*(zc - zpl)/k, (*_3D)(i,1)*(zc - zpl)/k,(*_3D)(i,2) - zpl);
	}
}

void face::display()const
{
	point _2D[M];
	generate2Dpoint(body,_2D);
	if(visible(_2D))
		draw(_2D, color);
}

bool face::visible(point *_2D)const
{
	double sum = 0;
	int j;	
	for (int i = 0; i < M; i++)
	{
		j = i == M-1 ? 0 : i + 1;
		sum += (_2D[i].getx() - _2D[j].getx())*(_2D[i].gety() + _2D[j].gety());
	}
	return sum > 0;
}

void face::remove()const
{
	point _2D[M];
	generate2Dpoint(body,_2D);
	if(visible(_2D))
		draw(_2D, 0x000000);
}

void face::draw(point *_2D, COLORREF color)const
{
	map<int,vector<int>> a;
	int x0,x1,y0,y1,dx,dy,err,e2,sx,sy;
	for (int i = 0; i < M; i++)
	{
		x0 = round(_2D[i].getx());
		x1 = round(_2D[(i + 1 == M) ? 0: i + 1].getx());
		y0 = round(_2D[i].gety());
		y1 = round(_2D[(i + 1 == M) ? 0: i + 1].gety());
		dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		err = (dx > dy ? dx : -dy) / 2;
		e2 = err;
		for (;;)
		{
			if(a.count(y0) == 0)
				a.insert(pair<int, vector<int>>(y0,vector<int>(0)));
			a.find(y0)->second.push_back(x0);
			bmp.SetPixel(x0, y0, color);
			if (x0 == x1 && y0 == y1) 
				break;
			e2 = err;
			if (e2 > -dx)
				err -= dy, x0 += sx;
			if (e2 < dy)
				err += dx, y0 += sy;
		}
	}
	fill(a, color);
}	

void face::fill(map<int,vector<int>> &a, COLORREF color)const
{
	for(auto i = a.begin(); i!=a.end(); i++)
	{
		sort(i->second.begin(),i->second.end()); 
		for(int j = 0; j<i->second.size()-1; j++)
			for(int k = i->second[j]; k < i->second[j+1]; k++)
				SetPixel(device, k, i->first, color);
	}
}

point face::centre(void)const
{
	point tmp;
	for(int i=0; i<M; i++)
		tmp += point((*body)(i,0),(*body)(i,1),(*body)(i,2));
	tmp/=M;
	return tmp;
}

void face::move(matrixMOV &mov)
{
	*body*=mov;
}

void face::scale(matrixSCALE &scale, matrixMOV &to, matrixMOV &from)
{
	*body*=to;
	*body*=scale;
	*body*=from;
}
