// TODO std::copy
#ifndef OBJECTS_VECTOR_H_
#define OBJECTS_VECTOR_H_

#include <iostream>
#include <algorithm>
#include <cassert>
#include <limits>

#include "config.h"

namespace objects {

// The vector class implements a standard 3 dimensional vector.
template<typename T>
class Vector3 {
 public:
  // Creates a vector containing only zeros.
  Vector3() {
    std::fill(x_, x_+3, 0);
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

  // Returns a vector containing the maximum values for the current numeric
  // type.
  static Vector3<T> Max() {
    T max = std::numeric_limits<T>::max();
    return Vector3<T>(max, max, max);
  }

  // Returns a vector containing the minimum values for the current numeric
  // type.
  static Vector3<T> Min() {
    T min = std::numeric_limits<T>::min();
    return Vector3<T>(min, min, min);
  }

  // Returns a vector containing the epsilon values for the current numeric
  // type.
  static Vector3<T> Epsilon() {
    T epsilon = std::numeric_limits<T>::epsilon();
    return Vector3<T>(epsilon, epsilon, epsilon);
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

  // Returns true if all elements are smaller than the argument, false
  // otherwise.
  bool operator<(const Vector3 &v) const {
    return x_[0] < v(0) && x_[1] < v(1) && x_[2] < v(2);
  }

  // Returns true if all elements are equal, false otherwise.
  bool operator==(const Vector3 &v) const {
    return x_[0] == v(0) && x_[1] == v(1) && x_[2] == v(2);
  }

  // Returns true if all elements are smaller or equal than the argument, false
  // otherwise.
  bool operator<=(const Vector3 &v) const {
    return (*this) < v || (*this) == v;
  }

  // Returns true if all elements are smaller than the argument, false
  // otherwise.
  bool operator>(const Vector3 &v) const {
    return !((*this) <= v);
  }

  // Returns true if all elements are smaller than the argument, false
  // otherwise.
  bool operator>=(const Vector3 &v) const {
    return !((*this) < v);
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
  Vector3<T> operator-(const Vector3<T> &v) const {
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
    std::copy(v, v+3, x_);
  }

  T x_[3];    // The internal representation of the vector.

};

typedef Vector3<int> Point;
typedef Vector3<float> Vector;

// Ensures multiplication with a scalar can be applied commutatively.
template<typename T>
Vector3<T> operator*(T f, const Vector3<T> &v) {
  return v*f;
}

// Prints the vector to the given output stream.
template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector3<T> &v) {
  return out << "[" << v(0) << "," << v(1) << "," << v(2) << "]";
}

// Reads a vector from a given input stream. The supported formats are:
//    x1 x2
//    x1 x2 x3
//    x1 x2 x3 w
// where w is the homogeneous part of the coordinate.
template<typename T>
std::istream &operator>>(std::istream &in, Vector3<T> &r) {
  T v[3] = {0, 0, 0};
  T w = 1;

  in >> v[0] >> v[1];
  if (!in.fail()) {
    in >> v[2];
    if (!in.fail()) {
      in >> w;
      if (!in.fail()) {
        v[0] /= w; v[1] /= w; v[2] /= w;
      }
    }
    in.clear();
  }
  
  r = Vector3<T>(v);
  return in;
}

}

#endif // OBJECTS_VECTOR_H_
