// TODO
#ifndef OBJECTS_RENDERER_H_
#define OBJECTS_RENDERER_H_

#include <GL/gl.h>
#include <GL/glut.h>

#include "config.h"
#include "simulation.h"

namespace objects {

// This is the class that is responsible for all the drawing going on. 
class Renderer {
 public:
  // Constructs an new renderer.
  Renderer() {}

  // Render the simulation in its current state.
  void Render(const Simulation &simulation) {
    glutSolidCube(1.0);
  }

  /*
  template<class Box>
  inline void renderWireframe(const Box &b)
  {
    glBegin(GL_LINE_LOOP);
    glVertex3f(b.ll[0], b.ll[1], b.ll[3]);
    glVertex3f(b.ur[0], b.ll[1], b.ll[3]);
    glVertex3f(b.ur[0], b.ur[1], b.ll[3]);
    glVertex3f(b.ll[0], b.ur[1], b.ll[3]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(b.ll[0], b.ll[1], b.ur[3]);
    glVertex3f(b.ur[0], b.ll[1], b.ur[3]);
    glVertex3f(b.ur[0], b.ur[1], b.ur[3]);
    glVertex3f(b.ll[0], b.ur[1], b.ur[3]);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(b.ll[0], b.ll[1], b.ll[3]);
    glVertex3f(b.ll[0], b.ll[1], b.ur[3]);
    glVertex3f(b.ur[0], b.ll[1], b.ll[3]);
    glVertex3f(b.ur[0], b.ll[1], b.ur[3]);
    glVertex3f(b.ur[0], b.ur[1], b.ll[3]);
    glVertex3f(b.ur[0], b.ur[1], b.ur[3]);
    glVertex3f(b.ll[0], b.ur[1], b.ll[3]);
    glVertex3f(b.ll[0], b.ur[1], b.ur[3]);
    glEnd();
  }*/

 private:
  DISALLOW_COPY_AND_ASSIGN(Renderer);
};

}

#endif // OBJECTS_RENDERER_H_
