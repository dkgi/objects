#include "mesh.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

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

void Mesh::Render(const Renderer &renderer) const {
  std:: cout << "render mesh";
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


MeshParser::~MeshParser() {
  for (auto mp : meshes_) delete mp.second;
}

Mesh* MeshParser::operator()(std::string path) {
  std::map<std::string,Mesh*>::const_iterator it = meshes_.find(path);
  return (it != meshes_.end()) ? it->second : nullptr;
}

Mesh* MeshParser::Parse(const std::string &filename, const std::string &id) {
  std::ifstream file(filename.c_str());

  std::vector<Vector> vertices;
  std::vector<Vector> normals;
  std::vector<Vector> texture_coordinates;
  std::vector<std::vector<std::vector<int> > > faces;
  Vector ll = Vector::Max();
  Vector ur = Vector::Min();

  std::string line, str;
  Vector v;

  while (std::getline(file, line)) {
    std::istringstream line_stream(line);
    line_stream >> str;
    if (str == std::string("v") && line_stream >> v) {
      vertices.push_back(v);
      if (v <= ll) ll = v;
      if (ur <= v) ur = v;
    }
    if (str == std::string("vn") && line_stream >> v) normals.push_back(v);
    if (str == std::string("vt") && line_stream >> v) texture_coordinates.push_back(v);
    if (str == std::string("f")) {
      std::vector<std::vector<int> > f;
      ParseFace(line_stream, f);
      faces.push_back(f);
    }
  }

  file.close();

  Box box(ll - Vector::Epsilon(), ur + Vector::Epsilon());
  Mesh *mesh = new Mesh(vertices, normals, texture_coordinates, faces, box);
  meshes_[id] = mesh;
  
  return mesh;
}

void MeshParser::ParseFace(std::istream &in, std::vector<std::vector<int> > &f) {
  std::vector<int> fi(3);
  char c;
  while (in.good()) {
    if (in >> fi[0]) {              // v
      if (in.peek() == '/') {
        in >> c;
        if (in.peek() == '/') {
          in >> c >> fi[2];         // v//vn
        } else {
          in >> fi[1];
          if (in.peek() == '/') {
            in >> c >> fi[2];       // v/vt/vn
          }
        }
      }

      for (auto &i : fi) i--;       // 0 based indices

      f.push_back(fi);
      fi.clear(); fi.resize(3);
    } else{
      break;
    }
  }
}

}
