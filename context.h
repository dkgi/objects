// TODO License etc.

#ifndef OBJECTS_CONTEXT_H_
#define OBJECTS_CONTEXT_H_

#include <vector>

#include "vector.h"
#include "matrix.h"

namespace objects {

// The InputContext represents all current knowledge of the input devices
// such as the mouse or the keyboard.
struct InputContext {
  // Initializes the context with default values.
  InputContext()
      : defaultPosition(250, 250),
        keyDown(1 << (8*sizeof(unsigned char)), false) {
    position = defaultPosition;      
  }

  Point position;               // Current mouse position
  Point defaultPosition;        // Actual mouse position which is kept constant
  Point dx;                     // The most recent mouse movement

  std::vector<bool> keyDown;    // Map of keys that are currently pressed
};


// The TimingContext keeps track of information related to the timing of the
// simulation.
struct TimingContext {
  TimingContext() {
    then = 0.0;
    t = 0.0;
  }

  int then, now;    // The last two time measurements in ms
  float dt;         // The difference between those measurements.
  float t;          // The total elapsed time in the simulation.
};

}

#endif // OBJECTS_CONTEXT_H_
