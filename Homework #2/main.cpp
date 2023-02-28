/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0, 1, 4, 1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = {1.0, 1.0, 1.0, 1.0};
float shininess[] = {50.0};

void problem1() {
	// TODO: Your code here!

	for (int i = 0; i < 11; i++) {
		float angle =  2 * M_PI * i / 11;
		float orient = angle * 180 / M_PI;
		glPushMatrix();
		glTranslatef(cos(angle), sin(angle), 0);
		glRotatef(orient, 0, 0, 1);
		glutSolidTeapot(0.1);
		glPopMatrix();
	}
}

void problem2() {
	// TODO: Your code here!
  int numSteps = 20;
  float stepWidth = 1.0;
  float stepDepth = 2.0;
  float histogramData[] = {7.0 ,6.75, 6.50,6.25,6.0 ,5.75, 5.50, 5.25, 5.0 , 4.75 ,4.5 ,4.25 ,4.0, 3.75, 3.5, 3.25, 3.0, 2.75, 2.5, 2.25, 2.0};
  float center = (numSteps - 1) * stepWidth / 2.0;
  glColor3f(1.0, 1.0, 1.0);
  gluLookAt(0.0, 0.0, 25.0, // eye position (increase z value)
            0.0, 0.0, 0.0,  // look at origin
            0.0, 5.0, 10.0);
  
  for (int i = 0; i < numSteps; i++) 
  {
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(i*stepWidth - center, histogramData[i]/2.0, 0);
    glScalef(stepWidth, histogramData[i], stepDepth);
    glutSolidCube(1.0);
    glPopMatrix();
  }
}

void problem3() 
{
	float teapotSize = 0.1;
	float translation[6] = {-0.75, -0.65, -0.55, -0.45, -0.35, -0.25};
	// TODO: Your code here!
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6 - i; j++) {
			glPushMatrix();
			glTranslatef(
				translation[i] + (j * 0.3) + (i * teapotSize / 2),
				(5 - i) * 0.3 + teapotSize,
				0);
			glRotatef(5.0 * i, 1, 0, 0);
			glutSolidTeapot(teapotSize);
			glPopMatrix();
		}
	}
}
void problem4() 
{
  for (int i = 0; i < 12; i++) 
  { // Draw 12 rays
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix(); // Save the current matrix
    glRotatef(i * 30.0f, 0.0f, 0.0f, 1.0f); // Rotate the matrix around the Z-axis
    glBegin(GL_TRIANGLES); // Begin drawing triangles
    glVertex2f(0.0f, 0.0f); // Center point
    glVertex2f(0.2f, -0.2f); // Bottom point
    glVertex2f(0.2f, 0.2f); // Top point
    glEnd();// End drawing triangles

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); // Begin drawing quads
    glVertex3f(-0.1f, 0.0f, 0.01); // Left point
    glVertex3f(0.0f, 0.1f, 0.01); // Top point
    glVertex3f(0.1f, 0.0f, 0.01); // Right point
    glVertex3f(0.0f, -0.1f, 0.01); // Bottom point
    glEnd();
    
    glPopMatrix(); // Restore the previous matrix
    glPopMatrix();
  }
}


void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0); // x axis
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0); // y axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot, 0, 1, 0);

	if (curProblem == 1)
		problem1();
	if (curProblem == 2)
		problem2();
	if (curProblem == 3)
		problem3();
	if (curProblem == 4)
		problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON)
		rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown)
		yRot += (x - lastPos[0]) * .1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
	}

	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key - '0';
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
