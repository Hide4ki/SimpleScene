#include "point.h"

point::point(double x, double y, double z):x(x),y(y),z(z)
{
}
	
point::point()
{
	x = 0;
	y = 0;
	z = 0;
}

double point::getx() const
{
	return x;
}

double point::gety() const
{
	return y;
}

double point::getz() const
{
	return z;
}	

point point::operator + (const point &myPoint)
{
	return point(x+myPoint.x, y+myPoint.y, z+myPoint.z);
}

void point::operator +=(const point &myPoint)
{
	x+=myPoint.x;
	y+=myPoint.y;
	z+=myPoint.z;
}

void point::operator = (const point &myPoint)
{		
	x=myPoint.x;
	y=myPoint.y;
	z=myPoint.z;
}

point point::operator / (const int &myPoint)
{
	return point(
	x/myPoint,
	y/myPoint,
	z/myPoint);
}

void point::operator /=(const int &myPoint)
{
	x/=myPoint;
	y/=myPoint;
	z/=myPoint;
}