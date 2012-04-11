// TODO std::copy
#ifndef OBJECTS_VECTOR_H_
#define OBJECTS_VECTOR_H_

#include <iostream>
#include <cassert>

#include "config.h"

namespace objects {

// The vector class implements a standard 3 dimensional vector.
template<class T>
class Vector3 {
 public:
  // Creates a vector containing only zeros.
  Vector3() {
    T v[3] = {0, 0, 0};
    Init(v);
  }

  // Creates a vector by copying another.
  Vector3(const Vector3 &v) {
    Init(v.x_);
  }

  // Creates a vector representing the vector given as argument.
  Vector3(T v[3]) {
    Init(v);
  }

  // Creates a vector for the first two values, zeroing the 3rd element.
  Vector3(T x0, T x1) {
    T v[3] = {x0, x1, 0};
    Init(v);
  }

  // Creates a vector for the three argument elements.
  Vector3(T x0, T x1, T x2) {
    T v[3] = {x0, x1, x2};
    Init(v);
  }

  // Copies the contents of the other vector.
  void operator=(const Vector3 &v) {
    Init(v.x_);
  }

  // Returns the element at position i.
  T operator()(unsigned int i) const {
    assert(0 <= i && i < 3);
    return x_[i];
  }

  // Returns the scalar product with another vector.
  T operator*(const Vector3<T> &v) const {
    return x_[0]*v(0) + x_[1]*v(1) + x_[2]*v(2);
  }

  // Returns the scaled vector by factor f.
  Vector3<T> operator*(T f) const {
    return Vector3<T>(f*x_[0], f*x_[1], f*x_[2]);
  }

  // Scales this vector by a factor f.
  void operator*=(T f) {
    x_[0] *= f; x_[1] *= f; x_[2] *= f;
  }

  // Returns the scaled vector by the inverse of a factor f.
  Vector3<T> operator/(T f) const {
    return Vector3<T>(x_[0]/f, x_[1]/f, x_[2]/f);
  }

  // Scales this vector by the inverse of a factor f.
  void operator/=(T f) {
    x_[0] /= f; x_[1] /= f; x_[2] /= f;
  }

  // Returns the sum of two vectors. Addition is performed element-wise.
  Vector3<T> operator+(const Vector3<T> &v) const {
    return Vector3<T>(x_[0]+v(0), x_[1]+v(1), x_[2]+v(2));
  }

  // Adds a vector to this vector.
  void operator+=(const Vector3<T> &v) {
    x_[0] += v(0); x_[1] += v(1); x_[2] += v(2);
  }

  // Returns the difference of two vectors. Subtraction is performed element-wise.
  Vector3<T> operator-(Vector3<T> &v) const {
    return Vector3<T>(x_[0]-v(0), x_[1]-v(1), x_[2]-v(2));
  }

  // Subtracts a vector from this vector.
  void operator-=(Vector3<T> &v) {
    x_[0] -= v(0); x_[1] -= v(1); x_[2] -= v(2);
  }

  // Returns the cross product of the two vectors.
  Vector3<T> Cross(const Vector3<T> &v) const {
    return Vector3<T>(x_[1]*v(2)-v(1)*x_[2], x_[2]*v(0)-v(2)*x_[0], x_[0]*v(1)-v(0)*x_[1]);
  }

  // Returns the squared length of the vector.
  T SquaredLength() const {
    return x_[0]*x_[0] + x_[1]*x_[1] + x_[2]*x_[2];   
  }

 private:
  // Initializes the vector to the values of the argument.
  void Init(const T v[3]) {
    for (int i = 0; i < 3; i++) {
      x_[i] = v[i];
    }
  }

  T x_[3];    // The internal representation of the vector.

};

typedef Vector3<int> Point;
typedef Vector3<float> Vector;

// Ensures multiplication with a scalar can be applied commutatively.
template<class T>
Vector3<T> operator*(T f, const Vector3<T> &v) {
  return v*f;
}

// Prints the vector to the given output stream.
template<class T>
std::ostream& operator<<(std::ostream& out, Vector3<T> v) {
  return out << "[" << v(0) << "," << v(1) << "," << v(2) << "]";
}

}

#endif // OBJECTS_VECTOR_H_
