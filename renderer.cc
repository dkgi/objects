#include <GL/gl.h>
#include <GL/glut.h>

#include "renderer.h"
#include "mesh.h"
#include "shape.h"

namespace objects {

OpenGLRenderer::OpenGLRenderer() {}


void OpenGLRenderer::Render(const Shape &shape) {
  std::cout << "render shape" << std::endl;
}

void OpenGLRenderer::Render(const Mesh &mesh) {
  std::cout << "render mesh" << std::endl;
}

void OpenGLRenderer::Render(const Box &b)
{
  glBegin(GL_LINE_LOOP);
  glVertex3f(b.ll()(0), b.ll()(1), b.ll()(3));
  glVertex3f(b.ur()(0), b.ll()(1), b.ll()(3));
  glVertex3f(b.ur()(0), b.ur()(1), b.ll()(3));
  glVertex3f(b.ll()(0), b.ur()(1), b.ll()(3));
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(b.ll()(0), b.ll()(1), b.ur()(3));
  glVertex3f(b.ur()(0), b.ll()(1), b.ur()(3));
  glVertex3f(b.ur()(0), b.ur()(1), b.ur()(3));
  glVertex3f(b.ll()(0), b.ur()(1), b.ur()(3));
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(b.ll()(0), b.ll()(1), b.ll()(3));
  glVertex3f(b.ll()(0), b.ll()(1), b.ur()(3));
  glVertex3f(b.ur()(0), b.ll()(1), b.ll()(3));
  glVertex3f(b.ur()(0), b.ll()(1), b.ur()(3));
  glVertex3f(b.ur()(0), b.ur()(1), b.ll()(3));
  glVertex3f(b.ur()(0), b.ur()(1), b.ur()(3));
  glVertex3f(b.ll()(0), b.ur()(1), b.ll()(3));
  glVertex3f(b.ll()(0), b.ur()(1), b.ur()(3));
  glEnd();
}

}

