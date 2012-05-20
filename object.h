#ifndef OBJECTS_OBJECT_H_
#define OBJECTS_OBJECT_H_

#include <iostream>

#include "config.h"
#include "vector.h"
#include "context.h"

namespace objects {

class Shape;

/**
  * The Object is the basic unit of the simulation. It contains information
  * about its current location, speed, the forces that are applied to it etc.
  */
class Object {
 public:
  /**
    * Creates an object of mass m, with initial position x, velocity v and a non
    * null shape represented by a shape.
    * @param m The objects mass
    * @param x The objects position
    * @param v The objects velocity
    * @param shape The objects shape
    */
  explicit Object(float m,
                  const Vector &x,
                  const Vector &v,
                  Shape *shape);

  /**
    * Cleans up.
    */
  ~Object();

  /**
    * Advances the simulation of the object by a single step. Each applied force
    * is evaluated and applied, resulting in a new acceleration etc.
    * @param timing The current timing context
    */
  void Step(const TimingContext &timing);

  /**
    * The shape of this object.
    * @return The objects shape
    */
  const Shape* shape() const;

 private:
  float m_;                 /** Mass of the object. */
  Vector x_, v_, F_;        /** Position, velocity and applied force. */

  Shape *shape_;            /** The objects shape. */

  DISALLOW_COPY_AND_ASSIGN(Object);
};

}

#endif // OBJECTS_OBJECT_H_
