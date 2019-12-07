#include "figure.h"

#define RED RGB(255,0,0)
#define WHITE RGB(255,255,255)
#define ORANGE RGB(255,153,0)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)

figure::figure(point *p)
{
	device = GetDC(GetConsoleWindow());
	body = new face[6];
	point f0[4];
	f0[0] = point(p[0]);
	f0[1] = point(p[4]);
	f0[2] = point(p[5]);
	f0[3] = point(p[1]);
	point f1[4];
	f1[0] = point(p[0]);
	f1[1] = point(p[1]);
	f1[2] = point(p[2]);
	f1[3] = point(p[3]);
	point f2[4];
	f2[0] = point(p[0]);
	f2[1] = point(p[3]);
	f2[2] = point(p[7]);
	f2[3] = point(p[4]);
	point f3[4];
	f3[0] = point(p[5]);
	f3[1] = point(p[4]);
	f3[2] = point(p[7]);
	f3[3] = point(p[6]);
	point f4[4];
	f4[0] = point(p[1]);
	f4[1] = point(p[5]);
	f4[2] = point(p[6]);
	f4[3] = point(p[2]);
	point f5[4];
	f5[0] = point(p[2]);
	f5[1] = point(p[6]);
	f5[2] = point(p[7]);
	f5[3] = point(p[3]);
	body[0] = face(f0, WHITE, device);
	body[1] = face(f1, RED, device);
	body[2] = face(f2, BLUE, device);
	body[3] = face(f3, YELLOW, device);
	body[4] = face(f4, GREEN, device);
	body[5] = face(f5, ORANGE, device);
	draw();
}

figure::~figure()
{
	clean();
	delete[] body;
}

void figure::draw()const
{
	for(int i = 0; i<M; i++)
		body[i].display();
}

void figure::clean() const
{
	for (int i = 0; i < M; i++)
		body[i].remove();
}

void figure::setCenterShiftMatrixs() const
{
	point tmp;
	for (int i = 0; i < M; i++)
		tmp += body[i].centre();
	tmp/=M;
	matrixMOV tmpTo(-tmp.getx(),-tmp.gety(),-tmp.getz());
	matrixMOV tmpFrom(tmp.getx(),tmp.gety(),tmp.getz());
	to = tmpTo;
	from = tmpFrom;
}

matrixMOV from(0,0,0);
matrixMOV to(0,0,0);

void figure::scale(matrixSCALE &scale)
{
	clean();
	setCenterShiftMatrixs();
	for (int i = 0; i < M; i++)
		body[i].scale(scale,to,from);	
	draw();
}

void figure::move(matrixMOV &mov)
{
	clean();
	for (int i = 0; i < M; i++)
		body[i].move(mov);
	draw();
}