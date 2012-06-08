#ifndef OBJECTS_RENDERER_H_
#define OBJECTS_RENDERER_H_

#include <vector>

#include "config.h"

namespace objects {

class Object;
class Shape;
class Mesh;
class Box;

/**
  * TODO
  */
class Renderer {
 public:
  Renderer() {}

  virtual void Render(const std::vector<Object*> &objects) = 0;

  virtual void Render(const Shape &shape) = 0;

  virtual void Render(const Mesh &mesh) = 0;

  virtual void Render(const Box &b) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Renderer);
};


// This is the class that is responsible for all the drawing going on. 
class OpenGLRenderer : public Renderer {
 public:
  // Constructs an new renderer.
  OpenGLRenderer();

  void Render(const std::vector<Object*> &objects);

  void Render(const Shape &shape);

  void Render(const Mesh &mesh); 

  void Render(const Box &b);

 private:
  DISALLOW_COPY_AND_ASSIGN(OpenGLRenderer);
};

}

#endif // OBJECTS_RENDERER_H_
