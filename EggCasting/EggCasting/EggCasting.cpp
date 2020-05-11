/*
	Autor: Piotr Jasiczek
	URL: www.piotrjasiczek.pl
*/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#define M_PI 3.14159265358979323846
#define N 50
using namespace std;


typedef float point3[3];
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };

int model = 1; 
int Colors[N][N][3];
static GLfloat pix2angle;
static GLfloat pix2angle1;		

static GLint statusl = 0;
static GLint statusr = 0;

static int x_pos_old = 0;   
static int y_pos_old = 0;

static int delta_x = 0;
static int delta_y = 0;

int R = 5;
static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat z = 10;

static GLfloat theta = 0.0;   
static GLfloat phi = 0.0;

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

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
									
	if (statusl == 1)                     
	{
		if (delta_x) theta += delta_x * pix2angle*(M_PI / 180);
	}
	if (statusl == 1)                   
	{
		if (delta_y) phi += delta_y * pix2angle1*(M_PI / 180);
	}
	if (statusr == 1) {
		if (delta_y > 0)
			R++;
		if (delta_y < 0)
			R--;
		if (R < 1)
			R = 1;
		if (R > 15)
			R = 15;
	}

	x = R * cos(theta)*cos(phi);
	z = R * sin(theta)*cos(phi);
	y = R * sin(phi);

	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, cos(phi), 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	Axes();
	glTranslated(0, -5.0, 0);
	Egg();
	glFlush();
	glutSwapBuffers();

}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene(); 
}

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;
		y_pos_old = y;			     
		statusr = 1;                
	}
	else
		if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			x_pos_old = x;			  
			y_pos_old = y;		      
			statusl = 1;			  
		}
		else
		{
			statusr = statusl = 0;	 
		}
}

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;  
	delta_y = y - y_pos_old;

	x_pos_old = x;          
	y_pos_old = y;

	glutPostRedisplay(); 
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	pix2angle = 360.0 / (float)vertical;
	pix2angle1 = 360.0 / (float)horizontal;  
	glMatrixMode(GL_PROJECTION);
	if (vertical == 0)
		vertical = 1;
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	glLoadIdentity();

	gluPerspective(70, AspectRatio, 1.0, 30.0);

	glViewport(0, 0, horizontal, vertical);

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

	glutCreateWindow("Rzutowanie perspektywiczne");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);                    
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(keys);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}