#include "shape.h"

namespace objects {

Box::Box(const Box &b) : ll_(b.ll_), ur_(b.ur_) {}

Box::Box(Vector ll, Vector ur) : ll_(ll), ur_(ur) {}

void Box::operator=(const Box &b) {
  ll_ = b.ll_; ur_ = b.ur_;
}

bool Box::Intersects(const Box &box) const {
  return (box.ll() <= ll_ && ll_ <= box.ur()) ||
    (box.ur() <= ur_ && ur_ <= box.ur());
}
  
const Vector& Box::ll() const { 
  return ll_; 
}

const Vector& Box::ur() const { 
  return ur_; 
}


Shape::Shape(const Box &bounds) : bounds_(bounds) {}

}
