#include <algorithm>
#include <dirent.h>
#include <exception>
#include <fstream>
#include <sstream>

#include "parser.h"
#include "shape.h"
#include "object.h"
#include "mesh.h"
#include "log.h"

namespace objects {

ShapeParser::ShapeParser() {}

ShapeParser::~ShapeParser() {
  for (auto shape : shapes_) delete shape;
}

Shape* ShapeParser::operator()(const std::string &file) const {
  auto it = shape_map_.find(file);
  return (it != shape_map_.end()) ? nullptr : it->second;
}

Shape* ShapeParser::Parse(const std::string &file) {
  // TODO support for different shapes
  return ParseMesh(file);   
}

Mesh* ShapeParser::ParseMesh(const std::string &file) {
  std::ifstream file_stream(file.c_str());
  Log::info() << (file_stream.fail() ? "Cannot parse '" : "Parsing '") << file <<
      "'" << std::endl;

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
  shape_map_[file] = mesh;
  shapes_.push_back(mesh);

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

ObjectParser::ObjectParser() : shape_parser_{new ShapeParser()} {}

ObjectParser::~ObjectParser() {
  for (auto object : objects_) delete object;
}

Object* ObjectParser::operator()(const std::string &file) const {
  auto it = object_map_.find(file);
  return (it != object_map_.end()) ? nullptr : it->second;
}

Object* ObjectParser::Parse(const std::string &file) {
  std::ifstream file_stream(file.c_str());
  Log::info() << (file_stream.fail() ? "Cannot parse '" : "Parsing '") << file <<
      "'" << std::endl;

  std::string line, str;
  std::string name, mesh_file;
  Vector x, v;
  Shape *shape = nullptr;
  float m;

  while (std::getline(file_stream, line)) {
    std::stringstream line_stream(line);
    line_stream >> str;

    if (str == std::string("o") && line_stream >> name) {}
    if (str == std::string("f") && line_stream >> mesh_file) {
      shape = (*shape_parser_)(mesh_file);
      if (shape == nullptr) shape = (*shape_parser_).Parse(mesh_file);
    }
    if (str == std::string("m") && line_stream >> m) {}
    if (str == std::string("x") && line_stream >> x) {}
    if (str == std::string("v") && line_stream >> v) {}
  }

  Object *object = new Object(m, x, v, shape);
  object_map_[file] = object;
  objects_.push_back(object);
  
  return object;
}

void ObjectParser::ParseAll(const std::string &directory) {
  DIR *dir = nullptr;
  struct dirent *ent = nullptr;

  dir = opendir(directory.c_str());
  if (dir != nullptr) {
    while ((ent = readdir(dir)) != nullptr) {
      std::string entry(ent->d_name);
      if (entry.length() > 4 && entry.substr(entry.length()-4) == ".ode") {
        Parse(directory + "/" + entry);
      }
    }
  } else {
    Log::info() << "Cannot open directory '" << directory << "'" <<
      std::endl;
  }
}

const std::vector<Object*> &ObjectParser::Objects() const {
  return objects_;
}

}
