/*
	Autor: Piotr Jasiczek 
	URL: www.piotrjasiczek.pl
*/

#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>
#define M_PI 3.14159265358979323846
#define N 50
using namespace std;
typedef float point3[3];

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; 
int model = 1; 
int Colors[N][N][3];

struct Point
{
	GLfloat x, y, z;
};

GLfloat set_x(int i, int k)
{
	float u = (float)i / N;
	float v = (float)k / N;
	return ((-90 * pow(u, 5)) + (225 * pow(u, 4)) + (-270 * pow(u, 3)) + (180 * pow(u, 2) - 45 * u)) * cos(M_PI * v);
}

GLfloat set_y(int i, int k)
{
	float u = (float)i / N;
	float v = (float)k / N;
	return (160 * pow(u, 4)) + (-320 * pow(u, 3)) + (160 * pow(u, 2));
}

GLfloat set_z(int i, int k)
{
	float u = (float)i / N;
	float v = (float)k / N;
	return ((-90 * pow(u, 5)) + (225 * pow(u, 4)) + (-270 * pow(u, 3)) + (180 * pow(u, 2)) + (-45 * u)) * sin(M_PI * v);
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

void Egg()
{
	Point PointsEgg[N + 1][N + 1];

	for (int i = 0; i < N + 1; i++)
	{
		for (int k = 0; k < N + 1; k++)
		{
			PointsEgg[i][k].x = set_x(i, k);
			PointsEgg[i][k].y = set_y(i, k);
			PointsEgg[i][k].z = set_z(i, k);
		};
	}

	switch (model)
	{

	case 1:
	{
		for (int i = 0; i < N + 1; i++)
		{
			for (int k = 0; k < N + 1; k++)
			{
				glBegin(GL_POINTS);
				glColor3ub(0, 140, 0);
				glVertex3f(PointsEgg[i][k].x, PointsEgg[i][k].y, PointsEgg[i][k].z);
				glEnd();
			}
		}
	}
	break;
	case 2:
	{
		for (int i = 0; i < N + 1; i++)
		{
			for (int k = 1; k < N + 1; k++)
			{
				glBegin(GL_LINES);
				glColor3ub(0, 140, 0);
				glVertex3f(PointsEgg[i][k - 1].x, PointsEgg[i][k - 1].y, PointsEgg[i][k - 1].z);
				glVertex3f(PointsEgg[i][k].x, PointsEgg[i][k].y, PointsEgg[i][k].z);
				glEnd();
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int k = N; k > 0; k--)
			{
				glBegin(GL_LINES);
				glColor3ub(0, 140, 0);
				glVertex3f(PointsEgg[i][k].x, PointsEgg[i][k].y, PointsEgg[i][k].z);
				glVertex3f(PointsEgg[i + 1][k].x, PointsEgg[i + 1][k].y, PointsEgg[i + 1][k].z);
				glEnd();
			}
		}
	}
	break;
	case 3:
	{
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				if ((k + 1) != N + 1) {
					glBegin(GL_TRIANGLES);
					glColor3ub(Colors[i][k][0], Colors[i][k][1], Colors[i][k][2]);
					glVertex3f(PointsEgg[i][k].x, PointsEgg[i][k].y, PointsEgg[i][k].z);
					glColor3ub(Colors[i + 1 % N][k][0], Colors[i + 1 % N][k][1], Colors[i + 1 % N][k][2]);
					glVertex3f(PointsEgg[i + 1 % N][k].x, PointsEgg[i + 1 % N][k].y, PointsEgg[i + 1 % N][k].z);
					glColor3ub(Colors[i][k + 1][0], Colors[i][k + 1][1], Colors[i][k + 1][2]);
					glVertex3f(PointsEgg[i][k + 1].x, PointsEgg[i][k + 1].y, PointsEgg[i][k + 1].z);
					glEnd();

					glBegin(GL_TRIANGLES);
					glColor3ub(Colors[(i + 1) % N][k][0], Colors[(i + 1) % N][k][1], Colors[(i + 1) % N][k][2]);
					glVertex3f(PointsEgg[(i + 1) % N][k].x, PointsEgg[(i + 1) % N][k].y, PointsEgg[(i + 1) % N][k].z);
					glColor3ub(Colors[(i + 1) % N][k + 1][0], Colors[(i + 1) % N][k + 1][1], Colors[(i + 1) % N][k + 1][2]);
					glVertex3f(PointsEgg[(i + 1) % N][k + 1].x, PointsEgg[(i + 1) % N][k + 1].y, PointsEgg[(i + 1) % N][k + 1].z);
					glColor3ub(Colors[i][k + 1][0], Colors[i][k + 1][1], Colors[i][k + 1][2]);
					glVertex3f(PointsEgg[i][k + 1].x, PointsEgg[i][k + 1].y, PointsEgg[i][k + 1].z);
					glEnd();
				}
				else {
					if (i > 0) {
						glBegin(GL_TRIANGLES);
						glColor3ub(Colors[(i + 1) % N][k][0], Colors[(i + 1) % N][k][1], Colors[(i + 1) % N][k][2]);
						glVertex3f(PointsEgg[(i + 1) % N][k].x, PointsEgg[(i + 1) % N][k].y, PointsEgg[(i + 1) % N][k].z);
						glColor3ub(Colors[(i + 1) % N][k + 1][0], Colors[(i + 1) % N][k + 1][1], Colors[(i + 1) % N][k + 1][2]);
						glVertex3f(PointsEgg[(i + 1) % N][k + 1].x, PointsEgg[(i + 1) % N][k + 1].y, PointsEgg[(i + 1) % N][k + 1].z);
						glColor3ub(Colors[i][k + 1][0], Colors[i][k + 1][1], Colors[i][k + 1][2]);
						glVertex3f(PointsEgg[i][k + 1].x, PointsEgg[i][k + 1].y, PointsEgg[i][k + 1].z);
						glEnd();
					}
					glBegin(GL_TRIANGLES);
					glColor3ub(Colors[(i + 1) % N][k][0], Colors[(i + 1) % N][k][1], Colors[(i + 1) % N][k][2]);
					glVertex3f(PointsEgg[(i + 1) % N][k].x, PointsEgg[(i + 1) % N][k].y, PointsEgg[(i + 1) % N][k].z);
					glColor3ub(Colors[(N - i) % N][0][0], Colors[(N - i) % N][0][1], Colors[(N - i) % N][0][2]);
					glVertex3f(PointsEgg[(N - i) % N][0].x, PointsEgg[(N - i) % N][0].y, PointsEgg[(N - i) % N][0].z);
					glColor3ub(Colors[N - i - 1][0][0], Colors[N - i - 1][0][1], Colors[N - i - 1][0][2]);
					glVertex3f(PointsEgg[N - i - 1][0].x, PointsEgg[N - i - 1][0].y, PointsEgg[N - i - 1][0].z);
					glEnd();

				}

			}
		}
	}
	break;
	}
}

void spinEgg()
{
	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotated(30.0, 1.0, 3.0, 3.0);

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glTranslated(0, -3.0, 0);
	Egg();
	glFlush();

	glutSwapBuffers();
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene(); 
}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	if (vertical == 0)  
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();          
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;        
	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);                              

	glLoadIdentity();
}


void main(void)
{
	srand(time(NULL));
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < N + 1; j++) {

			Colors[i][j][0] = (rand() % 255) + 1;
			Colors[i][j][1] = (rand() % 255) + 1;
			Colors[i][j][2] = (rand() % 255) + 1;
		}
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Uk³ad wspó³rzêdnych 3-D");

	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keys);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(spinEgg);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}