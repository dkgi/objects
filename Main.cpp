#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "Context.h"

using namespace Objects;

InputContext ic;
SimulationContext sc;

std::vector<float> m_position(3, 0.0); 

void init()
{
	glutWarpPointer(ic.mouse[0], ic.mouse[1]);
m_position[2] = -5.0;
}

void idle()
{
	sc.now = glutGet(GLUT_ELAPSED_TIME);
	sc.dt = (sc.now - sc.then) / 1000.0f;
	sc.then = sc.now;

	// Move camera
	if (ic.keyDown['s']) m_position[2] -= 0.1;
	if (ic.keyDown['w']) m_position[2] += 0.1;

	// Move scene

	// Redisplay
	glutPostRedisplay();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	// Camera transformation
	glTranslatef(m_position[0], m_position[1], m_position[2]);

	// Render scene
	glutWireTeapot(1.0);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w/h, 0.1, 500);
}

void keyboard(unsigned char key, int x, int y)
{
	ic.keyDown[key] = true;

	switch(key) {
		case 'q':
			exit(0);
			break;
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	ic.keyDown[key] = false;
}

void passiveMotion(int x, int y)
{
	glutWarpPointer(ic.mouse[0], ic.mouse[1]);
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
