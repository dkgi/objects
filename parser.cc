#include <algorithm>
#include <fstream>
#include <sstream>

#include "parser.h"
#include "shape.h"
#include "object.h"
#include "mesh.h"

namespace objects {

ObjectParser::ObjectParser() {}

ObjectParser::~ObjectParser() {
  for (auto pair : objects_) delete pair.second;
}

Object* ObjectParser::operator()(const std::string &file) const {
  // auto it = objects_.find(file);
  // TODO implement
  return nullptr;
}

Object* ObjectParser::Parse(const std::string &file) {
  // TODO implement.
  return nullptr;
}

ShapeParser::ShapeParser() {}

ShapeParser::~ShapeParser() {
  for (auto pair : shapes_) delete pair.second;
}

Shape* ShapeParser::Parse(const std::string &file) {
  return ParseMesh(file);   // TODO support for different shapes.
}

Mesh* ShapeParser::ParseMesh(const std::string &file) {
  // TODO proper error handling
  std::ifstream file_stream(file.c_str());

  std::vector<Vector> vertices;
  std::vector<Vector> normals;
  std::vector<Vector> texture_coordinates;
  std::vector<std::vector<std::vector<int> > > faces;
  Vector ll = Vector::Max();
  Vector ur = Vector::Min();

  std::string line, str;
  Vector v;

  while (std::getline(file_stream, line)) {
    std::stringstream line_stream(line);
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

  file_stream.close();

  Box box(ll - Vector::Epsilon(), ur + Vector::Epsilon());
  Mesh *mesh = new Mesh(vertices, normals, texture_coordinates, faces, box);
  shapes_[file] = mesh;
  
  return mesh;
}

void ShapeParser::ParseFace(std::istream &in, std::vector<std::vector<int> > &f) {
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
