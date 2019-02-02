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
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };

static GLfloat theta_y = 0.0;  
static GLfloat theta_x = 0.0;
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

static GLfloat thetax = 0.0;  
static GLfloat thetay = 0.0;

static GLfloat	fi_1 = 0;
static GLfloat	theta_1 = M_PI / 2;

static GLfloat	fi_2 = 0;
static GLfloat	theta_2 = M_PI / 2;

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

			normal_vec[0] = yu * zv - zu * yv;
			normal_vec[1] = zu * xv - xu * zv;
			normal_vec[2] = xu * yv - yu * xv;

			length = sqrt(pow(normal_vec[0], 2) + pow(normal_vec[1], 2) + pow(normal_vec[2], 2));

			if (length == 0) {
				if (i == 0) normal_vec[1] = -1;
				length = 1;
			}

			if (i >= (N / 2)) {
				normal_vec[0] = normal_vec[0] * -1;
				normal_vec[1] = normal_vec[1] * -1;
				normal_vec[2] = normal_vec[2] * -1;
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

				normal_vec[0] = yu * zv - zu * yv;
				normal_vec[1] = zu * xv - xu * zv;
				normal_vec[2] = xu * yv - yu * xv;
				length = sqrt(pow(normal_vec[0], 2) + pow(normal_vec[1], 2) + pow(normal_vec[2], 2));

				if (length == 0) {
					if (i == 0) normal_vec[1] = -1;
					length = 1;
				}

				if (i >= (N / 2)) {
					normal_vec[0] = normal_vec[0] * -1;
					normal_vec[1] = normal_vec[1] * -1;
					normal_vec[2] = normal_vec[2] * -1;
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

				normal_vec[0] = yu * zv - zu * yv;
				normal_vec[1] = zu * xv - xu * zv;
				normal_vec[2] = xu * yv - yu * xv;
				length = sqrt(pow(normal_vec[0], 2) + pow(normal_vec[1], 2) + pow(normal_vec[2], 2));

				if (length == 0) {
					if (i == 0) normal_vec[1] = -1;
					length = 1;
				}

				if (i >= (N / 2)) {
					normal_vec[0] = normal_vec[0] * -1;
					normal_vec[1] = normal_vec[1] * -1;
					normal_vec[2] = normal_vec[2] * -1;
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


void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (statusl == 1)
	{
		if (delta_y) thetay += delta_y * pix2angle1*(M_PI / 180);
		if (delta_y) theta_1 += delta_y;
		if (delta_y) theta_2 += delta_y;
	}
	if (statusl == 1)
	{
		if (delta_x) thetax += delta_x * pix2angle*(M_PI / 180);
		if (delta_x) fi_1 += delta_y;
		if (delta_x) fi_2 += delta_y;
	}
	if (statusr == 1) {
		if (delta_y > 0) R++;
		if (delta_y < 0) R--;
		if (R < 5) R = 5;
		if (R > 18) R = 18;
	}

	x = R * cos(thetax)*cos(thetay);
	z = R * sin(thetax)*cos(thetay);
	y = R * sin(thetay);
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, cos(thetay), 0.0);
	glTranslated(0, -3.0, 0);
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

	GLfloat light_position[] = { -30.0, 5.0, 3.0, 1.0 };
	GLfloat light_ambient[] = { 0.0f, 1.0f, 0.0f };
	GLfloat light_diffuse[] = { 0.0f, 1.0f, 0.0f };
	GLfloat light_specular[] = { 0.0f, 1.0f, 0.0f };


	GLfloat light1_position[] = { 30.0, 5.0, 3.0, 1.0 };
	GLfloat light1_ambient[] = { 1.0f, 0.0f, 0.0f };
	GLfloat light1_diffuse[] = { 1.0f, 0.0f, 0.0f };
	GLfloat light1_specular[] = { 1.0f, 0.0f, 0.0f };

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

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glShadeModel(GL_SMOOTH); 
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);  
	glEnable(GL_LIGHT1);     
	glEnable(GL_DEPTH_TEST); 

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
			statusr = statusl = 0;
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
	pix2angle = 360.0 / (float)horizontal;
	pix2angle1 = 360.0 / (float)vertical; 
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

	glutCreateWindow("Oświetlanie scen 3-D");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}