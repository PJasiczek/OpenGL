/*
	Autor: Piotr Jasiczek
	URL: www.piotrjasiczek.pl
*/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#define M_PI 3.14159265358979323846
using namespace std;

typedef float point3[3];
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
		if (R < 5) R = 5;
		if (R > 18) R= 18;
	}

	x = R * cos(thetax)*cos(thetay);
	z = R * sin(thetax)*cos(thetay);
	y = R * sin(thetay);
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, cos(thetay), 0.0);

	glColor3f(1.0f, 1.0f, 1.0f);

	glutSolidTeapot(3.0);
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

	glutCreateWindow("Rzutowanie perspektywiczne");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);                   
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	MyInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

}