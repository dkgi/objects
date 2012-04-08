#ifndef __OBJECTS_MATRIX_H
#define __OBJECTS_MATRIX_H

#include <iostream>
#include <cassert>
#include <cmath>

#include "Vector.h"

namespace Objects
{

	template<class T>
	class Matrix3
	{
		public:
			Matrix3()
			{
				zero(m_x);
			}

			explicit Matrix3(T v[3][3])
			{
				copy(v, m_x);
			}

			static Matrix3<T> Identity()
			{
				T v[3][3]; one(v);
				return Matrix3<T>(v);
			}

			/**
			  * Euler rotation with rx(a)*ry(b)*rz(g)
			  */
			static Matrix3<T> Rotation(T a, T b, T g)
			{
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

			T operator()(unsigned int i, unsigned int j) const
			{
				assert(0 <= i && i < 3);
				assert(0 <= j && j < 3);
				return m_x[i][j];
			}

			Matrix3<T> operator*(const Matrix3<T>& m) const
			{
				T r[3][3]; zero(r);

				for (int k = 0; k < 3; k++) {
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							r[i][j] += m_x[i][k]*m(k,j);
						}
					}
				}

				return Matrix3<T>(r);
			}

			Vector3<T> operator*(const Vector3<T>& v) const
			{
				T r[3] = {0, 0, 0};

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						r[i] += m_x[i][j]*v(j);
					}
				}

				return Vector3<T>(r);
			}

			Matrix3<T> operator*(T f) const
			{
				T v[3][3];

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						v[i][j] = f*m_x[i][j];
					}
				}

				return Matrix3<T>(v);
			}

			Matrix3<T> transposed() const
			{
				T v[3][3];

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						v[i][j] = m_x[j][i];
					}
				}

				return Matrix3<T>(v);
			}

			Matrix3<T> inverse() const
			{
				T d = determinant();
				if (d == 0) std::cerr << "Warning: Matrix " << (*this) << " is singular" << std::endl;
				return transposed() * (1.0 / d);
			}

			T determinant() const
			{
				return m_x[0][0]*(m_x[1][1]*m_x[2][2]-m_x[1][2]*m_x[2][1]) -
					m_x[0][1]*(m_x[1][0]*m_x[2][2]-m_x[1][2]*m_x[2][0]) +
					m_x[0][2]*(m_x[1][0]*m_x[2][1]-m_x[1][1]*m_x[2][0]);
			}

			Vector3<T> column(unsigned int i)
			{
				assert(0 <= i && i <= 3);
				return Vector3<T>(m_x[i]);
			}

		private:
			static void copy(T v[3][3], T u[3][3]) 
			{
				for(int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						u[i][j] = v[i][j];
					}
				}
			}

			static void zero(T v[3][3])
			{
				for(int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						v[i][j] = 0;
					}
				}
			}

			static void one(T v[3][3]) 
			{
				zero(v);
				v[0][0] = v[1][1] = v[2][2] = 1;
			}

			T m_x[3][3];

	};

	typedef Matrix3<float> Matrix;

	template<class T>
	std::ostream& operator<<(std::ostream& out, const Matrix3<T> &m)
	{
		out << "[";
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) out << m(i,j) << " ";
			out << m(i,2) << "; ";
		}
		for (int j = 0; j < 2; j++) out << m(2,j) << " ";
		return out << m(2,2) << "]";
	}

	template<class T>
	Matrix3<T> operator*(T f, const Matrix3<T> m)
	{
		return m*f;
	}

}

#endif
