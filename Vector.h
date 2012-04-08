#ifndef __OBJECTS_VECTOR_H
#define __OBJECTS_VECTOR_H

#include <iostream>
#include <cassert>

namespace Objects
{

	template<class T>
	class Vector3
	{
		public:
			Vector3()
			{
				T v[3] = {0, 0, 0};
				init(v);
			}

			Vector3(T x0, T x1)
			{
				T v[3] = {x0, x1, 0};
				init(v);
			}

			Vector3(T x0, T x1, T x2)
			{
				T v[3] = {x0, x1, x2};
				init(v);
			}

			/*
			explicit Vector3(const Vector3<T> &v)
			{
				init(v.x);
			}
			*/

			explicit Vector3(T v[3])
			{
				init(v);
			}

			T operator()(unsigned int i) const
			{
				assert(0 <= i && i < 3);
				return m_x[i];
			}

			T operator*(const Vector3<T> &v) const
			{
				return m_x[0]*v(0) + m_x[1]*v(1) + m_x[2]*v(2);
			}

			Vector3<T> operator*(T f) const
			{
				return Vector3<T>(f*m_x[0], f*m_x[1], f*m_x[2]);
			}

			void operator*=(T f)
			{
				m_x[0] *= f; m_x[1] *= f; m_x[2] *= f;
			}

			Vector3<T> operator+(const Vector3<T> &v) const
			{
				return Vector3<T>(m_x[0]+v(0), m_x[1]+v(1), m_x[2]+v(2));
			}

			void operator+=(const Vector3<T> &v)
			{
				m_x[0] += v(0); m_x[1] += v(1); m_x[2] += v(2);
			}

			Vector3<T> operator-(Vector3<T> &v) const
			{
				return Vector3<T>(m_x[0]-v(0), m_x[1]-v(1), m_x[2]-v(2));
			}

			void operator-=(Vector3<T> &v)
			{
				m_x[0] -= v(0); m_x[1] -= v(1); m_x[2] -= v(2);
			}

			Vector3<T> cross(const Vector3<T> &v) const
			{
				return Vector3<T>(m_x[1]*v(2)-v(1)*m_x[2], m_x[2]*v(0)-v(2)*m_x[0], m_x[0]*v(1)-v(0)*m_x[1]);
			}

			T squaredLength() const
			{
				return m_x[0]*m_x[0] + m_x[1]*m_x[1] + m_x[2]*m_x[2]; 	
			}

		private:
			void init(const T v[3])
			{
				for (int i = 0; i < 3; i++) {
					m_x[i] = v[i];
				}
			}

			T m_x[3];
	};

	typedef Vector3<int> Point;
	typedef Vector3<float> Vector;

	template<class T>
	Vector3<T> operator*(T f, const Vector3<T> &v)
	{
		return v*f;
	}

	template<class T>
	std::ostream& operator<<(std::ostream& out, Vector3<T> v)
	{
		return out << "[" << v(0) << "," << v(1) << "," << v(2) << "]";
	}

}

#endif
