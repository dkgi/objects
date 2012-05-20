#ifndef OBJECTS_SIMULATION_H_
#define OBJECTS_SIMULATION_H_

#include <vector>
#include <algorithm>

#include "config.h"
#include "context.h"
#include "object.h"

namespace objects {

// This class specifies the physical behavior of the objects of the simulation.
class Simulation {
 public:
  // Constructs an empty simulation.
  Simulation() {}

  // Advances the simulation a single step.
  void Step(const TimingContext &timing) {
  }

 private:
  std::vector<Object*> objects_;    // The objects of the simulation
  std::vector<Vector*> forces_;     // All external forces

  DISALLOW_COPY_AND_ASSIGN(Simulation);
};

}

#endif // OBJECTS_SIMULATION_H_
