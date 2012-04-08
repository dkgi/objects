#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

#include "Context.h"
#include "Vector.h"

#include "Simulation.h"
#include "Renderer.h"
#include "Camera.h"

using namespace Objects;

InputContext input;
TimingContext timing;

Camera *camera = new Camera();
Simulation *simulation = new Simulation();
Renderer *renderer = new Renderer();

void init()
{
	std::cout << std::fixed << std::setprecision(2);
	glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void idle()
{
	timing.now = glutGet(GLUT_ELAPSED_TIME);
	timing.dt = (timing.now - timing.then) / 1000.0f;
	timing.t += timing.dt;
	timing.then = timing.now;

	camera->step(timing, input);
	simulation->step(timing);

	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera transformation
	Vector pos = camera->position();
	Vector at = camera->at();
	Vector up = camera->up();
	gluLookAt(pos(0), pos(1), pos(2), 
			at(0), at(1), at(2),
			up(0), up(1), up(2));

	// Render scene 
	renderer->render(*simulation);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	camera->reshape(w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w/h, 0.1, 500);
	glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));
}

void keyboard(unsigned char key, int x, int y)
{
	input.keyDown[key] = true;

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
	input.keyDown[key] = false;
}

void passiveMotion(int x, int y)
{
	input.dx = Point(x, y) - input.defaultPosition;
	input.position += input.dx;
	camera->mouseMotion(input);
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
