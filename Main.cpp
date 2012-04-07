#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

#include "Context.h"
#include "Vector.h"

using namespace Objects;

InputContext input;
SimulationContext simulation;

// TODO move into context
// TODO up should be dynamic
Vector camera(0.0, 0.0, -5.0); 
float speed = 5.0;

void init()
{
	std::cout << std::fixed << std::setprecision(2);
	glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));
}

void idle()
{
	simulation.now = glutGet(GLUT_ELAPSED_TIME);
	simulation.dt = (simulation.now - simulation.then) / 1000.0f;
	simulation.then = simulation.now;

	// Move camera
	Vector dz = input.orientation.column(2) * speed * simulation.dt;
	Vector dx = input.orientation.column(0) * speed * simulation.dt;
	if (input.keyDown['s']) camera -= dz;
	if (input.keyDown['w']) camera += dz;
	if (input.keyDown['d']) camera -= dx;
	if (input.keyDown['a']) camera += dx;
	

	// Move simulation

	// Redisplay
	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	// Camera transformation
	Vector at = camera + input.orientation.column(2);
	Vector up = input.orientation.column(1);
	gluLookAt(camera(0), camera(1), camera(2), 
			at(0), at(1), at(2),
			up(0), up(1), up(2));
			

	// Render scene 
	glutWireTeapot(1.0);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	input.reshape(w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w/h, 0.1, 500);
	glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));
}

void keyboard(unsigned char key, int x, int y)
{
	input.keyboard(key, x, y);

	switch(key) {
		case 'q':
			exit(0);
			break;
		case 'f':
			glutFullScreenToggle();
			break;
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	input.keyboardUp(key, x, y);
}

void passiveMotion(int x, int y)
{
	input.passiveMotion(x, y);
	glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 10);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Objects");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(passiveMotion);

	init();

	glutSetCursor(GLUT_CURSOR_NONE);
//	glutFullScreen();
	glutMainLoop();

	return 0;
}
