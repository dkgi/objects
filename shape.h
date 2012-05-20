#ifndef OBJECTS_SHAPE_H_
#define OBJECTS_SHAPE_H_

#include <map>
#include <vector>
#include <string>

#include "config.h"
#include "vector.h"
#include "renderer.h"

namespace objects {

// The Box class represents an axis aligned bounding box defined by two
// vertices; the lower left (ll) and the upper right (ur) corner.
class Box {
 public:
  // Constructs a box with the same corners as the argument.
  explicit Box(const Box &b);

  // Constructs a box out of the two corner vectors.
  Box(Vector ll, Vector ur);

  // Copies the contents of the argument box.
  void operator=(const Box &b);

  // Tests if the box intersects another box.
  bool Intersects(const Box &box) const;

  // Returns the lower left corner.
  const Vector& ll() const;

  // Returns the upper right corner.
  const Vector& ur() const;

private:
  Vector ll_, ur_;      // The two corner vertices
};


// TODO
class Shape {
 public:
  Shape(const Box &bounds);

  virtual void Render(const Renderer &renderer) const {};

 private:
  Box bounds_;
};

}

#endif // OBJECTS_SHAPE_H_
