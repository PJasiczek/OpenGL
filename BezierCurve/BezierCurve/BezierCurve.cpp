/*
	Autor: Piotr Jasiczek 
	URL: www.piotrjasiczek.pl
*/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>
#define M_PI 3.14159265358979323846
#define N 25
#define M 25
using namespace std;
typedef float point3[3];
int model = 1;					
int Px[25] = { 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4 };
int Py[25] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 2, 6, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 };
int Pz[25] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4 };

int Zx[25] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4 };
int Zy[25] = { 0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 0, 1, 6, 1, 0, 0, 1, 2, 1, 0, 1, 1, 1, 1, 1 };
int Zz[25] = { 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4 };

int Pjkx[25] = { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };
int Pjky[25] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 2, 6, 2, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1 };
int Pjkz[25] = { 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };

struct Point
{
	GLfloat x, y, z;
};
Point BezierPoints[N][M];

float silnia(int value)
{
	if (value == 0) return 1;
	else return value * silnia(value - 1);
}

GLfloat set_x(int ui, int uk)
{
	long double sum = 0;
	float u = (float)ui / N;
	float v = (float)uk / M;
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			sum += (Pjkx[j] * (silnia(M) / (silnia(j)*(silnia(M - j))))*pow(u, j)*pow(1 - u, M - j)*(silnia(N) / (silnia(k)*silnia(N - k)))*pow(v, k)*pow(1 - v, N - k));
		}
	}
	return sum;
}

GLfloat set_y(int ui, int uk)
{
	long double sum = 0;
	float u = (float)ui / N;
	float v = (float)uk / M;
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			sum += (Pjky[j] * (silnia(M) / (silnia(j)*(silnia(M - j))))*pow(u, j)*pow(1 - u, M - j)*(silnia(N) / (silnia(k)*silnia(N - k)))*pow(v, k)*pow(1 - v, N - k));

		}
	}
	return sum;
}

GLfloat set_z(int ui, int uk)
{
	long double sum = 0;
	float u = (float)ui / N;
	float v = (float)uk / M;
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			sum += (Pjkz[j] * (silnia(M) / (silnia(j)*(silnia(M - j))))*pow(u, j)*pow(1 - u, M - j)*(silnia(N) / (silnia(k)*silnia(N - k)))*pow(v, k)*pow(1 - v, N - k));

		}
	}
	return sum;
}

void BezierArea()
{
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			BezierPoints[j][k].x = set_x(j, k);
			BezierPoints[j][k].y = set_y(j, k);
			BezierPoints[j][k].z = set_z(j, k);
		}
	}

	switch (model)
	{

	case 1:
	{
		for (int k = 0; k < M - 1; k++)
		{
			glBegin(GL_LINES);
			glLineWidth(2);
			glColor3ub(255, 18, 18);
			glVertex3f(Px[k], Py[k], Pz[k]);
			glVertex3f(Px[k + 1], Py[k + 1], Pz[k + 1]);
			glEnd();
		}
		for (int k = 0; k < M - 1; k++)
		{
			glBegin(GL_LINES);
			glLineWidth(2);
			glColor3ub(255, 18, 18);
			glVertex3f(Zx[k], Zy[k], Zz[k]);
			glVertex3f(Zx[k + 1], Zy[k + 1], Zz[k + 1]);
			glEnd();
		}
		for (int k = 0; k < M; k++)
		{
			glPointSize(5.0f);
			glBegin(GL_POINTS);
			glColor3ub(255, 224, 0);
			glVertex3f(Px[k], Py[k], Pz[k]);
			glEnd();
		}

	}
	break;
	case 2:
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				glPointSize(3.0f);
				glBegin(GL_POINTS);
				glColor3ub(255, 224, 0);
				glVertex3f(BezierPoints[j][k].x, BezierPoints[j][k].y, BezierPoints[j][k].z);
				glEnd();
			}
		}
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				glBegin(GL_LINES);
				glColor3ub(0, 140, 0);
				glVertex3f(BezierPoints[j][k].x, BezierPoints[j][k].y, BezierPoints[j][k].z);
				glVertex3f(BezierPoints[j][(k + 1) % N].x, BezierPoints[j][(k + 1) % N].y, BezierPoints[j][(k + 1) % N].z);
				glEnd();
			}
		}

		for (int j = 0; j < N - 1; j++)
		{
			for (int k = M - 1; k >= 0; k--)
			{
				glBegin(GL_LINES);
				glColor3ub(0, 140, 0);
				glVertex3f(BezierPoints[j][k].x, BezierPoints[j][k].y, BezierPoints[j][k].z);
				glVertex3f(BezierPoints[j + 1][k].x, BezierPoints[j + 1][k].y, BezierPoints[j + 1][k].z);
				glEnd();
			}
		}

	}
	break;
	}
}

void Axes(void)
{
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };


	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };


	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);

	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, -2.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	BezierArea();
	glFlush();

	glutSwapBuffers();
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;

	RenderScene();
}

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(70, 1.0, 1.0, 30.0);

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Bezier Curve");

	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);                 
	glutKeyboardFunc(keys);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}