#pragma once
class point
{	
	double x;
	double y;
	double z;
public:	
	point();
	point(double x, double y, double z);
	double getx() const;
	double gety() const;
	double getz() const;
	point operator + (const point &myPoint);
	void operator +=(const point &myPoint);
	void operator = (const point &myPoint);
	point operator / (const int &myPoint);
	void operator /=(const int &myPoint);
};

