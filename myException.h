#pragma once

#include <iostream>

using namespace std;

class myException
{
	const char *textEx;
public:
	explicit myException(const char *a);
	myException(void);
	myException(const myException &e);
	~myException(void);
	friend ostream &operator<< (ostream &stream, const myException &a);
};
