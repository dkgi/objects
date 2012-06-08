#ifndef OBJECTS_SIMULATION_H_
#define OBJECTS_SIMULATION_H_

#include <vector>

#include "config.h"
#include "vector.h"

namespace objects {

class TimingContext;
class Object;

/**
  * The Simulation class is responsible for running the simulation.
  */
class Simulation {
 public:
  /**
    * The basic constructor.
    */
  Simulation();

  /**
    * The basic deconstructor.
    */
  ~Simulation();

  /**
    * Advaces the simulation by one step for the given timing information.
    * @param timing The timing context
    */
  void Step(std::vector<Object*> &objects, const TimingContext &timing);

 private:
  std::vector<Vector*> forces_;     /** All external forces */

  DISALLOW_COPY_AND_ASSIGN(Simulation);
};

}

#endif // OBJECTS_SIMULATION_H_
