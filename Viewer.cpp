#include "Viewer.h"

Viewer::Viewer(double z) : _z{ z }
{
}

Viewer::~Viewer()
{
}

double Viewer::GetZ()
{
	return _z;
}
