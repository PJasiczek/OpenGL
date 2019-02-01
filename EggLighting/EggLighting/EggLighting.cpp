/*
	Autor: Piotr Jasiczek
	URL: www.piotrjasiczek.pl
*/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#define M_PI 3.14159265358979323846
#define N 75
using namespace std;

typedef float point3[3];
point3	normal_vec;
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; 
int model = 1;  
static GLfloat viewer[] = { 0.0, 0.0, 15.0 };

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
	GLfloat	length;
	float	xu, xv, yu, yv, zu, zv;

	for (int i = 0; i < N + 1; i++)
	{
		for (int k = 0; k < N + 1; k++)
		{
			PointsEgg[i][k].x = set_x(i, k);
			PointsEgg[i][k].y = set_y(i, k);
			PointsEgg[i][k].z = set_z(i, k);
		}
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

				float u = (float)i / N;
				float v = (float)k / N;
				xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(M_PI * v);
				xv = M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(M_PI * v);
				yu = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
				yv = 0;
				zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(M_PI * v);
				zv = -1 * M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(M_PI * v);

				normal_vec[0] = (yu * zv) - (zu * yv);
				normal_vec[1] = (zu * xv) - (xu * zv);
				normal_vec[2] = (xu * yv) - (yu * xv);

				length = sqrt(pow(normal_vec[0], 2) + pow(normal_vec[1], 2) + pow(normal_vec[2], 2));

				if (length == 0) {
					if (i == 0) normal_vec[1] = -1;
					length = 1;
				}

				if (i >= (N / 2)) {
					normal_vec[0] = -1 * normal_vec[0];
					normal_vec[1] = -1 * normal_vec[1];
					normal_vec[2] = -1 * normal_vec[2];
				}
				if (i == (N / 2)) {
					normal_vec[1] = -1 * normal_vec[1];
				}

				normal_vec[0] = normal_vec[0] / length;
				normal_vec[1] = normal_vec[1] / length;
				normal_vec[2] = normal_vec[2] / length;

				if ((k + 1) != N + 1) {
					glBegin(GL_TRIANGLES);
					glNormal3fv(normal_vec);
					glVertex3f(PointsEgg[i][k].x, PointsEgg[i][k].y, PointsEgg[i][k].z);
					glVertex3f(PointsEgg[i + 1 % N][k].x, PointsEgg[i + 1 % N][k].y, PointsEgg[i + 1 % N][k].z);
					glVertex3f(PointsEgg[i][k + 1].x, PointsEgg[i][k + 1].y, PointsEgg[i][k + 1].z);
					glEnd();

					xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(M_PI * v);
					xv = M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(M_PI * v);
					yu = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
					yv = 0;
					zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(M_PI * v);
					zv = -M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(M_PI * v);

					normal_vec[0] = (yu * zv) - (zu * yv);
					normal_vec[1] = (zu * xv) - (xu * zv);
					normal_vec[2] = (xu * yv) - (yu * xv);
					length = sqrt(pow(normal_vec[0], 2) + pow(normal_vec[1], 2) + pow(normal_vec[2], 2));

					if (length == 0) {
						if (i == 0) normal_vec[1] = -1;
						length = 1;
					}

					if (i >= (N / 2)) {
						normal_vec[0] = -1 * normal_vec[0];
						normal_vec[1] = -1 * normal_vec[1];
						normal_vec[2] = -1 * normal_vec[2];
					}
					if (i == (N / 2)) {
						normal_vec[1] = -1 * normal_vec[1];
					}

					normal_vec[0] = normal_vec[0] / length;
					normal_vec[1] = normal_vec[1] / length;
					normal_vec[2] = normal_vec[2] / length;

					glBegin(GL_TRIANGLES);
					glNormal3fv(normal_vec);
					glVertex3f(PointsEgg[(i + 1) % N][k].x, PointsEgg[(i + 1) % N][k].y, PointsEgg[(i + 1) % N][k].z);
					glVertex3f(PointsEgg[(i + 1) % N][k + 1].x, PointsEgg[(i + 1) % N][k + 1].y, PointsEgg[(i + 1) % N][k + 1].z);
					glVertex3f(PointsEgg[i][k + 1].x, PointsEgg[i][k + 1].y, PointsEgg[i][k + 1].z);
					glEnd();
				}
				else {
					if (i > 0) {
						glBegin(GL_TRIANGLES);
						glVertex3f(PointsEgg[(i + 1) % N][k].x, PointsEgg[(i + 1) % N][k].y, PointsEgg[(i + 1) % N][k].z);
						glVertex3f(PointsEgg[(i + 1) % N][k + 1].x, PointsEgg[(i + 1) % N][k + 1].y, PointsEgg[(i + 1) % N][k + 1].z);
						glVertex3f(PointsEgg[i][k + 1].x, PointsEgg[i][k + 1].y, PointsEgg[i][k + 1].z);
						glEnd();
					}

					xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * cos(M_PI * v);
					xv = M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * sin(M_PI * v);
					yu = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
					yv = 0;
					zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(M_PI * v);
					zv = -M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u) * cos(M_PI * v);

					normal_vec[0] = (yu * zv) - (zu * yv);
					normal_vec[1] = (zu * xv) - (xu * zv);
					normal_vec[2] = (xu * yv) - (yu * xv);
					length = sqrt(pow(normal_vec[0], 2) + pow(normal_vec[1], 2) + pow(normal_vec[2], 2));

					if (length == 0) {
						if (i == 0) normal_vec[1] = -1;
						length = 1;
					}


					if (i >= (N / 2)) {
						normal_vec[0] = -1 * normal_vec[0];
						normal_vec[1] = -1 * normal_vec[1];
						normal_vec[2] = -1 * normal_vec[2];
					}

					normal_vec[0] = normal_vec[0] / length;
					normal_vec[1] = normal_vec[1] / length;
					normal_vec[2] = normal_vec[2] / length;

					glBegin(GL_TRIANGLES);
					glNormal3fv(normal_vec);
					glVertex3f(PointsEgg[(i + 1) % N][k].x, PointsEgg[(i + 1) % N][k].y, PointsEgg[(i + 1) % N][k].z);
					glVertex3f(PointsEgg[(N - i) % N][0].x, PointsEgg[(N - i) % N][0].y, PointsEgg[(N - i) % N][0].z);
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
	glTranslated(0, -3.0, 0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	Egg();
	glFlush();
	glutSwapBuffers();

}


void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };            

	GLfloat mat_shininess = { 20.0 };

	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };

	GLfloat light_ambient[] = { 1.0, 1.0, 0.0, 0.0 };

	GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 0.0 };

	GLfloat light_specular[] = { 1.0, 1.0, 0.0, 0.0 };

	GLfloat att_constant = { 1.0 };

	GLfloat att_linear = { 0.05 };

	GLfloat att_quadratic = { 0.001 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glShadeModel(GL_SMOOTH); 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    
	glEnable(GL_DEPTH_TEST);

}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;
	RenderScene();
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

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Oswietlanie - jedno zrodlo swiatla");
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keys);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(spinEgg);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}