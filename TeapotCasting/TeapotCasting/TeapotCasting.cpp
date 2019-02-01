/*
	Autor: Piotr Jasiczek
	URL: www.piotrjasiczek.pl
*/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
using namespace std;

typedef float point3[3];

static GLfloat viewer[] = { 0.0, 0.0, 10.0 };

static GLfloat theta_y = 0.0;   
static GLfloat theta_x = 0.0;
static GLfloat pix2angle;      

static GLint statusl = 0;     
static GLint statusr = 0;

int zoom = 5;

static int x_pos_old = 0;     
static int y_pos_old = 0;

static int delta_x = 0;
static int delta_y = 0;

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
	if (statusl == 1)                     
	{
		theta_y += delta_x * pix2angle;
		theta_x += delta_y * pix2angle; 
	}
	if (statusr == 1) {
		if (delta_y > 0)
			zoom++;
		if (delta_y < 0)
			zoom--;
		if (zoom < 1)
			zoom = 1;
		if (zoom > 20)
			zoom = 20;
	}
	gluLookAt(viewer[0], viewer[1], zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(theta_y, 0.0, 1.0, 0.0); 
	glRotatef(theta_x, 1.0, 0.0, 0.0); 
	Axes();
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireTeapot(3.0);
	glFlush();
	glutSwapBuffers();

}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
	pix2angle = 360.0 / (float)horizontal;  
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

	glutCreateWindow("Rzutowanie perspektywiczne");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);                     
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	MyInit();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}