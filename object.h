// TODO
#ifndef OBJECTS_OBJECT_H_
#define OBJECTS_OBJECT_H_

#include <iostream>

#include "vector.h"
#include "mesh.h"

namespace objects {

// The Object is the basic unit of the simulation. It contains information about
// its current location, speed, the forces that are applied to it etc.
class Object {
 public:
  // Creates an object of mass m.
  explicit Object(float m) {
    m_ = m;
  }

  // Cleans up.
  ~Object() {
    if (mesh_ != NULL) delete mesh_;
  }

  // Applies a force represented by a vector to the object.
  void ApplyForce(const Vector &f) {
    F_ += f;
  }

  // Advances the simulation of the object by a single step. Each applied force
  // is evaluated and applied, resulting in a new acceleration etc.
  void Step(const TimingContext &timing) {
    Vector a = F_ / m_;
    v_ += timing.dt * a;
    x_ += timing.dt * v_;
  }

 private:
  float m_;                 // Mass of the object.
  Vector x_, v_, F_;        // Position, velocity and applied force.

  Mesh *mesh_;             // The objects mesh.
};

}

#endif // OBJECTS_OBJECT_H_
