// TODO
#ifndef OBJECTS_MESH_H_
#define OBJECTS_MESH_H_

#include <map>
#include <vector>
#include <string>

#include "config.h"
#include "vector.h"

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


// The Mesh class represents a mesh consisting of vertices, normals, texture
// coordinates and faces relating vertices.
class Mesh {
 public:
  // Constructs a new mesh from vertices, normals, texture coordinates, faces
  // and a bounding box.
  Mesh(const std::vector<Vector> &vertices, 
       const std::vector<Vector> &normals,
       const std::vector<Vector> &texture_coordinates, 
       const std::vector<std::vector<std::vector<int> > > &faces, 
       const Box &box);

  // Tests if two meshes intersect.
  bool Intersects(const Mesh &shape) const;

  // Returns the vertices.
  const std::vector<Vector>& vertices() const;

  // Returns the faces.
  const std::vector<std::vector<std::vector<int> > >& faces() const;

  // Returns the bounding box.
  const Box& box() const;

private:
  std::vector<Vector> vertices_;
  std::vector<Vector> normals_;
  std::vector<Vector> texture_coordinates_;
  std::vector<std::vector<std::vector<int> > > faces_;
  Box box_;

  DISALLOW_COPY_AND_ASSIGN(Mesh);
};


// The MeshParser class manages a collection of meshes that and provides facilities
// to parse meshes from files.
class MeshParser {
 public:
  // Create an empty collection of meshes.
  MeshParser() {}

  // Make sure all the meshes are deallocated.
  ~MeshParser();

  // Returns a pointer to the mesh that what parsed from the file with the given
  // path or NULL if no such mesh exists.
  Mesh* operator()(std::string path);

  // Parse a mesh from an obj file and store it with for the given id.
  Mesh* Parse(const std::string &filename, const std::string &id);

 private:
  // Parse a single face.
  void ParseFace(std::istream &in, std::vector<std::vector<int> > &f);

  std::map<std::string, Mesh*> meshes_;     // The loaded meshes

  DISALLOW_COPY_AND_ASSIGN(MeshParser);
};


}

#endif // OBJECTS_MESH_H_
