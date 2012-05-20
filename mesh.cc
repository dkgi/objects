#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

#include "mesh.h"

namespace objects {

Mesh::Mesh(const std::vector<Vector> &vertices, 
     const std::vector<Vector> &normals,
     const std::vector<Vector> &texture_coordinates, 
     const std::vector<std::vector<std::vector<int> > > &faces, 
     const Box &box) 
    : Shape(box),
      vertices_(vertices),
      normals_(normals),
      texture_coordinates_(texture_coordinates),
      faces_(faces) {}

void Mesh::Render(Renderer &renderer) const {
  renderer.Render(*this);
}

const std::vector<Vector>& Mesh::vertices() const { 
  return vertices_; 
}
  
const std::vector<Vector>& Mesh::normals() const { 
  return normals_; 
}
  
const std::vector<Vector>& Mesh::texture_coordinates() const { 
  return texture_coordinates_; 
}
  
const std::vector<std::vector<std::vector<int> > >& Mesh::faces() const { 
  return faces_; 
}

}
