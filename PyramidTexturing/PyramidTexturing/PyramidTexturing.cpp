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
#define N 100
using namespace std;

typedef float point3[3];
point3	normal;
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
bool key1 = true, key2 = true, key3 = true, key4 = true, key5 = true, key6 = true;
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

int R = 2;
static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat z = 10;

static GLfloat thetax = 0.0;
static GLfloat thetay = 0.0;

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

void Pyramid()
{
	if (key1) {
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-2.5, -1.5, -2.5);

		glNormal3f(0, 0, 1);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, 2.5, 0);

		glNormal3f(0, 0, 1);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(2.5, -1.5, -2.5);
		glEnd();
	}
	if (key2) {
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(2.5, -1.5, 2.5);

		glNormal3f(0, 0, -1);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, 2.5, 0);

		glNormal3f(0, 0, -1);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-2.5, -1.5, 2.5);
		glEnd();
	}
	if (key3) {
		glBegin(GL_TRIANGLES);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.5, -1.5, 2.5);

		glNormal3f(-1, 0, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, 2.5, 0);

		glNormal3f(-1, 0, 0);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(-2.5, -1.5, -2.5);
		glEnd();
	}
	if (key4) {
		glBegin(GL_TRIANGLES);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(2.5, -1.5, -2.5);

		glNormal3f(1, 0, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, 2.5, 0);

		glNormal3f(1, 0, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(2.5, -1.5, 2.5);
		glEnd();
	}
	if (key5) {
		glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.5, -1.5, -2.5);

		glNormal3f(0, -1, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(2.5, -1.5, -2.5);

		glNormal3f(0, -1, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(2.5, -1.5, 2.5);

		glNormal3f(0, -1, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-2.5, -1.5, 2.5);
		glEnd();
	}
	if (key6) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
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
	}
	if (statusl == 1)
	{
		if (delta_x) thetax += delta_x * pix2angle*(M_PI / 180);
	}
	if (statusr == 1) {
		if (delta_y > 0) R++;
		if (delta_y < 0) R--;
		if (R < 2) R = 2;
		if (R > 18) R = 18;
	}

	x = R * cos(thetax)*cos(thetay);
	z = R * sin(thetax)*cos(thetay);
	y = R * sin(thetay);
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, cos(thetay), 0.0);
	glTranslated(0, -3.0, 0);
	Pyramid();
	glFlush();
	glutSwapBuffers();

}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') {
		if (key1) {
			key1 = false;
		}
		else {
			key1 = true;
		}
	}
	else if (key == 'o') {
		if (key2) {
			key2 = false;
		}
		else {
			key2 = true;
		}
	}
	else if (key == 'i') {
		if (key3) {
			key3 = false;
		}
		else {
			key3 = true;
		}
	}
	else if (key == 'u') {
		if (key4) {
			key4 = false;
		}
		else {
			key4 = true;
		}
	}
	else if (key == 'y') {
		if (key5) {
			key5 = false;
		}
		else {
			key5 = true;
		}
	}
	else if (key == 't') {
		if (key6) {
			key6 = false;
		}
		else {
			key6 = true;
		}
	}
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

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{

#pragma pack(1)            
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}

	switch (sDepth)

	{

	case 3:

		*ImFormat = GL_BGR_EXT;

		*ImComponents = GL_RGB8;

		break;

	case 4:

		*ImFormat = GL_BGRA_EXT;

		*ImComponents = GL_RGBA8;

		break;

	case 1:

		*ImFormat = GL_LUMINANCE;

		*ImComponents = GL_LUMINANCE8;

		break;

	};

	fclose(pFile);
	return pbitsperpixel;

}

void MyInit(void)
{

	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat mat_shininess = { 20.0 };

	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };

	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

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

	pBytes = LoadTGAImage("t_256.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	free(pBytes);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	glutCreateWindow("Teksturowanie powierzchni obiektow");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	MyInit();
	glutKeyboardFunc(keys);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

}