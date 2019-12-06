#include <iostream>
#include "myException.h"

myException::myException(const char *a):textEx(a)
{
}

myException::myException(void):textEx("Is error undefind")
{
}

myException::myException(const myException &e)
{
	textEx = e.textEx;
}

myException::~myException(void)
{
}

ostream &operator<< (ostream &stream, const myException &a)
{
	stream  << "Error!!! " << a.textEx << endl;
	return stream;
}