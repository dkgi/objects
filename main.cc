// TODO
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <sstream>

#include "parser.h"
#include "context.h"
#include "mesh.h"
#include "vector.h"
#include "camera.h"
#include "renderer.h"
#include "simulation.h"

objects::InputContext input;
objects::TimingContext timing;

objects::Camera *camera = new objects::Camera();
objects::Simulation *simulation = new objects::Simulation();
objects::Renderer *renderer = new objects::OpenGLRenderer();

// Initializes OpenGL and initiates further initialization.
void Init() {
  std::cout << std::fixed << std::setprecision(2);
  glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  objects::ObjectParser object_parser;
  object_parser.Parse(std::string("objects/cone.objd"));
}

// Computes time since last invocation, then advances both camera and the
// simulation before initiating a new render cycle.
void Idle() {
  timing.now = glutGet(GLUT_ELAPSED_TIME);
  timing.dt = (timing.now - timing.then) / 1000.0f;
  timing.t += timing.dt;
  timing.then = timing.now;

  camera->Step(timing, input);
  simulation->Step(timing);

  glutPostRedisplay();
}

// Renders the whole scene.
void Display() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  objects::Vector pos = camera->position();
  objects::Vector at = camera->at();
  objects::Vector up = camera->up();
  gluLookAt(pos(0), pos(1), pos(2), 
      at(0), at(1), at(2),
      up(0), up(1), up(2));

  //renderer->Render(*simulation);

  glutSwapBuffers();
}

// Adjusts viewport, projection matrix and informs the camera about the new
// size.
void Reshape(int w, int h) {
  camera->Reshape(w, h);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w/h, 0.1, 500);
  glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));
}

// Updates the input context to keep track of the pressed key.
void Keyboard(unsigned char key, int x, int y) {
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

// Updates the input context to keep track of the release key.
void KeyboardUp(unsigned char key, int x, int y) {
  input.keyDown[key] = false;
}

// Updates the input context to keep track of the mouse movement. The function
// resets the mouse pointer to make sure that it can be moved indefinitely.
void PassiveMotion(int x, int y) {
  input.dx = objects::Point(x, y) - input.defaultPosition;
  input.position += input.dx;
  camera->MouseMotion(input);
  glutWarpPointer(input.defaultPosition(0), input.defaultPosition(1));
}

// The main function initializes glut, sets the different callback functions,
// calls Init() and starts the main loop.
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(300, 10);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Objects");

  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutIdleFunc(Idle);
  glutKeyboardFunc(Keyboard);
  glutKeyboardUpFunc(KeyboardUp);
  glutPassiveMotionFunc(PassiveMotion);

  Init();

  glutSetCursor(GLUT_CURSOR_NONE);
//  glutFullScreen();
  glutMainLoop();

  return 0;
}
