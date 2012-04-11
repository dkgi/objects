// TODO
#ifndef OBJECTS_MESH_H_
#define OBJECTS_MESH_H_

#include <vector>

#include "config.h"
#include "vector.h"

namespace objects {

// The Box class represents an axis aligned bounding box defined by two
// vertices; the lower left (ll) and the upper right (ur) corner.
class Box {
 public:
  // Constructs a box with the same corners as the argument.
  explicit Box(const Box &b) : ll_(b.ll_), ur_(b.ur_) {}

  // Constructs a box out of the two corner vectors.
  Box(Vector ll, Vector ur) : ll_(ll), ur_(ur) {}

  // Copies the contents of the argument box.
  void operator=(const Box &b) {
    ll_ = b.ll_; ur_ = b.ur_;
  }

  // Tests if the box intersects another box.
  bool Intersects(const Box &box) const {
    return ll_(0) <= box.ll()(0) && box.ur()(0) <= ur_(0) &&
      ll_(1) <= box.ll()(1) && box.ur()(1) <= ur_(1) &&
      ll_(2) <= box.ll()(2) && box.ur()(2) <= ur_(2);
  }

  // Returns the lower left corner.
  const Vector& ll() const { return ll_; }

  // Returns the upper right corner.
  const Vector& ur() const { return ur_; }

private:
  Vector ll_, ur_;      // The two corner vertices
};


// The Mesh class represents a mesh consisting of vertices, normals, texture
// coordinates and faces relating vertices.
class Mesh {
 public:
  // Constructs a new mesh from vertices, faces and a bounding box.
  Mesh(const std::vector<Vector> &v, const std::vector<int> &f, const Box &b) 
    : vertices_(v),
      faces_(f),
      box_(b) {}

  // Tests if two meshes intersect.
  bool Intersects(Mesh &shape) const
  {
    if (box_.Intersects(shape.box())) {
      return true;
    }
    return false;
  }

  // Returns the vertices.
  const std::vector<Vector>& vertices() const { return vertices_; }

  // Returns the faces.
  const std::vector<int>& faces() const { return faces_; }

  // Returns the bounding box.
  const Box& box() const { return box_; } 

private:
  std::vector<Vector> vertices_;
  std::vector<Vector> normals_;
  std::vector<Vector> texture_coordinates_;
  std::vector<int> faces_;
  Box box_;
};

}

#endif // OBJECTS_MESH_H_
