#ifndef OBJECTS_MESH_H_
#define OBJECTS_MESH_H_

#include <map>
#include <vector>
#include <string>

#include "config.h"
#include "vector.h"
#include "shape.h"
#include "renderer.h"

namespace objects {

/**
  * The Mesh class represents a mesh consisting of vertices, normals, texture 
  * coordinates and faces relating vertices.
  */
class Mesh : public Shape {
 public:
  /**
    * The basic constructor.
    * @param vertices The meshes' vertices.
    * @param normals The meshes' normals corresponding to the vertices.
    * @param texture_coordinates The texture coordinates corresponding to the
    * vertices.
    * @param faces The faces represented by the indices of vertices that form
    * the given face.
    * @param box The bounding box of the mesh.
    */
  Mesh(const std::vector<Vector> &vertices, 
       const std::vector<Vector> &normals,
       const std::vector<Vector> &texture_coordinates, 
       const std::vector<std::vector<std::vector<int> > > &faces, 
       const Box &box);

  /**
    * Renders the mesh.
    * @param renderer The renderer.
    */
  void Render(Renderer &renderer) const;

  /**
    * The meshes' vertices.
    * @return The list of vertices.
    */
  const std::vector<Vector>& vertices() const;

  /**
    * The meshes' normals.
    * @return The list of normals.
    */
  const std::vector<Vector>& normals() const;

  /**
    * The meshes' texture coordinates.
    * @return The list of texture coordinates.
    */
  const std::vector<Vector>& texture_coordinates() const;

  /**
    * The meshes' faces.
    * @return The list of lists of indices to vertices forming the faces.
    */
  const std::vector<std::vector<std::vector<int> > >& faces() const;

private:
  std::vector<Vector> vertices_;
  std::vector<Vector> normals_;
  std::vector<Vector> texture_coordinates_;
  std::vector<std::vector<std::vector<int> > > faces_;

  DISALLOW_COPY_AND_ASSIGN(Mesh);
};

}

#endif // OBJECTS_MESH_H_
