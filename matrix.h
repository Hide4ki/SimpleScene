#pragma once
class Matrix
{	
protected:
	Matrix() = delete;
	Matrix(size_t, size_t);
	double **_body;
	size_t _h;
	size_t _w;
public:
	Matrix(Matrix&&) noexcept;
	Matrix(const Matrix &);
	Matrix &operator = (const Matrix&);
	Matrix &operator = (Matrix &&) noexcept;
	Matrix operator * (Matrix&);
	Matrix &operator *= (Matrix&);
	double &operator () (int, int);
	virtual ~Matrix(void);
};

