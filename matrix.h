#pragma once
class matrix
{	
protected:
	matrix();
	double **body;
	size_t H;
	size_t W;
public:
	matrix(const matrix &myMatrix);
	virtual ~matrix(void);
};

