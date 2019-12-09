#pragma once
class Viewer
{
private:
	double _z;
public:
	Viewer() = delete;
	explicit Viewer(double);
	~Viewer();
	double GetZ();
};