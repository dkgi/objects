#include "object.h"


namespace objects {

Object::Object(float m,
               const Vector &x,
               const Vector &v,
               Shape *shape)
    : x_(x), v_(v) {
  assert(shape != nullptr);
  m_ = m;
  shape_ = shape;
}

Object::~Object() {
}

void Object::Step(const TimingContext &timing) {
  Vector a = F_ / m_;
  v_ += timing.dt * a;
  x_ += timing.dt * v_;
}

const Shape* Object::shape() const {
  return shape_;
}

}
