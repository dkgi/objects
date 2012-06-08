#ifndef OBJECTS_PARSER_H_
#define OBJECTS_PARSER_H_

#include <map>
#include <string>
#include <memory>

#include "config.h"

namespace objects {

class Shape;
class Object;
class Mesh;

/**
  * The ShapeParser class provides basic facilities to parse shapes from
  * files. Furthermore it is responsible for managing the resources allocated
  * after parsing. Shapes parsed by a parser will only live as long as the
  * parser lives itself.
  */
class ShapeParser {
 public:
  /**
    * The basic constructor.
    */
  ShapeParser();

  /**
    * The destructor. Upon deallocation of the parser all shapes parsed by this
    * parser will automatically be deallocated. 
    */
  ~ShapeParser();

  /**
    * The operator provides access to the previously parsed shapes.
    * @param file The file which the shapes was parsed from.
    * @return The parsed shape or nullptr if no such shape exists.
    */
  Shape* operator()(const std::string &file) const;
  
  /**
    * Parses a shape from a file. The upon success the shapes will be
    * available using the () operator.
    * @return The parsed shape.
    */
  Shape* Parse(const std::string &file);

  /**
    * Parses a mesh from a file.
    * @return The parsed mesh.
    */
  Mesh* ParseMesh(const std::string &file);
 private:
  /**
    * Parses a mesh face.
    * @param in The input stream.
    * @param f The resulting face vector.
    */
  void ParseFace(std::istream &in, std::vector<std::vector<int> > &f);

  std::map<std::string, Shape*> shape_map_;   /** The map of parsed shapes. */
  std::vector<Shape*> shapes_;                /** The parsed shapes. */

  DISALLOW_COPY_AND_ASSIGN(ShapeParser);
};


/**
  * The ObjectParser class provides basic facilities to parse objects from
  * files. Furthermore it is responsible for managing the resources allocated
  * after parsing. Objects parsed by a parser will only live as long as the
  * parser lives itself.
  */
class ObjectParser {
 public:
  /**
    * The basic constructor.
    */
  ObjectParser();

  /**
    * The destructor. Upon deallocation of the parser all objects parsed by this
    * parser will automatically be deallocated. 
    */
  ~ObjectParser();

  /**
    * The operator provides access to the previously parsed objects.
    * @param file The file which the object was parsed from.
    * @return The parsed object or nullptr if no such object exists.
    */
  Object* operator()(const std::string &file) const;
  
  /**
    * Parses an object from a file. Upon success the object will be available
    * using the () operator.
    * @return The parsed object.
    */
  Object* Parse(const std::string &file);

  /**
    * Parses all objects in the a given directory. Upon success the objects will
    * be available using the () operator.
    */
  void ParseAll(const std::string &directory);

  const std::vector<Object*> &Objects() const;
 private:
  std::map<std::string, Object*> object_map_;   /** The map of parsed objects. */
  std::vector<Object*> objects_;                /** The parsed objects. */
  std::unique_ptr<ShapeParser> shape_parser_;   /** The parsed shapes. */

  DISALLOW_COPY_AND_ASSIGN(ObjectParser);
};

}


#endif // OBJECTS_PARSER_H_
