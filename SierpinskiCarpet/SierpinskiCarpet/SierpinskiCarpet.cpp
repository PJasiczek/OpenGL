/*
	Autor: Piotr Jasiczek
	URL: www.piotrjasiczek.pl
*/

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

GLfloat rand_perm(GLfloat a, GLint pert_lvl)
{
	if (pert_lvl == 0) {
		return pert_lvl;
	}
	else {
		return ((rand() % pert_lvl) + 0) / a;
	}
}

void draw_sierpinski(GLfloat x, GLfloat y, GLfloat a, GLint step)
{
	if (step > 0) {
		a = a / 3;
		//creation of squares with widths a / 3 for the next level
		draw_sierpinski(x, y, a, step - 1);
		draw_sierpinski(x - a, y, a, step - 1);
		draw_sierpinski(x - 2 * a, y, a, step - 1);
		draw_sierpinski(x, y - a, a, step - 1);
		draw_sierpinski(x - 2 * a, y - a, a, step - 1);
		draw_sierpinski(x, y - 2 * a, a, step - 1);
		draw_sierpinski(x - a, y - 2 * a, a, step - 1);
		draw_sierpinski(x - 2 * a, y - 2 * a, a, step - 1);
	}
	else {
		glBegin(GL_QUADS);
		GLint pert = 5;						//perturbation degree
		glColor3ub((rand() % 255) + 0, (rand() % 255) + 0, (rand() % 255) + 0);
		glVertex2f(x + rand_perm(a, pert), y + rand_perm(a, pert));
		glColor3ub((rand() % 255) + 0, (rand() % 255) + 0, (rand() % 255) + 0);
		glVertex2f(x - a + rand_perm(a, pert), y + rand_perm(a, pert));
		glColor3ub((rand() % 255) + 0, (rand() % 255) + 0, (rand() % 255) + 0);
		glVertex2f(x - a + rand_perm(a, pert), y - a + rand_perm(a, pert));
		glColor3ub((rand() % 255) + 0, (rand() % 255) + 0, (rand() % 255) + 0);
		glVertex2f(x + rand_perm(a, pert), y - a + rand_perm(a, pert));
		glEnd();
	}
}


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	draw_sierpinski(50.f, 50.f, 100.f, 3);
	glFlush();

}


void MyInit(void)
{

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	srand(time(NULL));

	glutCreateWindow("Dywan Sierpiñskiego z perturbancjami");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	MyInit();

	glutMainLoop();
}