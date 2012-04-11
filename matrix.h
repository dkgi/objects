// TODO std::copy, std::fill etc.
#ifndef OBJECTS_MATRIX_H_
#define OBJECTS_MATRIX_H_

#include <iostream>
#include <cassert>
#include <cmath>

#include "vector.h"

namespace objects {

template<class T>
class Matrix3 {
 public:
  // Constructs a 3x3 matrix consisting of all zeros.
  Matrix3() {
    Zero(x_);
  }

  // Constructs a 3x3 matrix from the given array. The interpretation is
  // row-major.
  explicit Matrix3(T v[3][3]) {
    Copy(v, x_);
  }

  // Returns the 3x3 identity matrix.
  static Matrix3<T> Identity() {
    T v[3][3]; One(v);
    return Matrix3<T>(v);
  }

  // Returns an Euler matrix around for the given angles. The order of
  // operations is Rx(a)*Ry(b)*Rz(g), i.e. the rotation starts with the z axis
  // and ends with the x axis.
  static Matrix3<T> Rotation(T a, T b, T g) {
    T ca = cos(a); T sa = sin(a);
    T cb = cos(b); T sb = sin(b);
    T cg = cos(g); T sg = sin(g);

    T v[3][3] = {
      {cb*cg, -cb*sg, sb},
      {sa*sb*cg+ca*sg, -sa*sb*sg+ca*cg, -sa*cb},
      {-ca*sb*cg+sa*sg, ca*sb*sg+sa*cg, ca*cb}
    };
    return Matrix3<T>(v);
  }

  // Returns the element in the ith row and jth column.
  T operator()(unsigned int i, unsigned int j) const {
    assert(0 <= i && i < 3);
    assert(0 <= j && j < 3);
    return x_[i][j];
  }

  // Returns the product of two matrices. 
  Matrix3<T> operator*(const Matrix3<T> &m) const {
    T r[3][3]; Zero(r);

    for (int k = 0; k < 3; k++) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          r[i][j] += x_[i][k]*m(k,j);
        }
      }
    }

    return Matrix3<T>(r);
  }

  // Applies this matrix to a vector and returns the result.
  Vector3<T> operator*(const Vector3<T> &v) const {
    T r[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        r[i] += x_[i][j]*v(j);
      }
    }

    return Vector3<T>(r);
  }

  // Returns the scaled matrix by a scalar factor f.
  Matrix3<T> operator*(T f) const {
    T v[3][3];

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        v[i][j] = f*x_[i][j];
      }
    }

    return Matrix3<T>(v);
  }

  // Returns the transposed.
  Matrix3<T> Transposed() const {
    T v[3][3];

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        v[i][j] = x_[j][i];
      }
    }

    return Matrix3<T>(v);
  }

  // Returns the inverse of this matrix. Issues if the matrix is singular.
  Matrix3<T> Inverse() const {
    T d = Determinant();
    if (d == 0) std::cerr << "Warning: Matrix " << (*this) << " is singular" << std::endl;
    return Transposed() * (1.0 / d);
  }

  // Returns the matrix' determinant.
  T Determinant() const {
    return x_[0][0]*(x_[1][1]*x_[2][2]-x_[1][2]*x_[2][1]) -
      x_[0][1]*(x_[1][0]*x_[2][2]-x_[1][2]*x_[2][0]) +
      x_[0][2]*(x_[1][0]*x_[2][1]-x_[1][1]*x_[2][0]);
  }

  // Returns the ith column of the matrix as a vector.
  Vector3<T> Column(unsigned int i) {
    assert(0 <= i && i <= 3);
    return Vector3<T>(x_[i]);
  }

 private:
  // Copies all elements of v to u.
  static void Copy(T v[3][3], T u[3][3]) {
    for(int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        u[i][j] = v[i][j];
      }
    }
  }

  // Zeros out all elements of v.
  static void Zero(T v[3][3]) {
    for(int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        v[i][j] = 0;
      }
    }
  }

  // Zeros out all elements of v, except where i=j where the element is set to
  // 1.
  static void One(T v[3][3]) {
    Zero(v);
    v[0][0] = v[1][1] = v[2][2] = 1;
  }

  T x_[3][3];   // Elements of the matrix.

};

typedef Matrix3<float> Matrix;

// Prints the matrix to the give output stream.
template<class T>
std::ostream &operator<<(std::ostream &out, const Matrix3<T> &m) {
  out << "[";
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) out << m(i,j) << " ";
    out << m(i,2) << "; ";
  }
  for (int j = 0; j < 2; j++) out << m(2,j) << " ";
  return out << m(2,2) << "]";
}

// Allows for commutative use of scalar multiplication with matrices.
template<class T>
Matrix3<T> operator*(T f, const Matrix3<T> &m) {
  return m*f;
}

}

#endif
