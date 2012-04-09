#ifndef __OBJECTS_MESH_H
#define __OBJECTS_MESH_H

#include <vector>

#include "Vector.h"

namespace Objects
{

	class Box
	{
		public:
			Box(Vector ll, Vector ur) : m_ll(ll), m_ur(ur)
			{}

			bool intersects(const Box &box) const
			{
				return m_ll(0) <= box.ll()(0) && box.ur()(0) <= m_ur(0) &&
					m_ll(1) <= box.ll()(1) && box.ur()(1) <= m_ur(1) &&
					m_ll(2) <= box.ll()(2) && box.ur()(2) <= m_ur(2);

			}

			const Vector& ll() const { return m_ll; }

			const Vector& ur() const { return m_ur; }

		private:
			Vector m_ll, m_ur;
	};


	class Mesh
	{
		public:
			Mesh(const std::vector<Vector> &v, const std::vector<int> &f, const
					Box &b) 
				: 	m_vertices(v),
					m_faces(f),
					m_box(b)
			{}

			bool intersects(Mesh &shape) const
			{
				if (m_box.intersects(shape.box())) {
					return true;
				}
				return false;
			}

			const std::vector<Vector>& vertices() const { return m_vertices; }

			const std::vector<int>& faces() const { return m_faces; }

			const Box& box() const { return m_box; } 

		private:
			std::vector<Vector> m_vertices;
			std::vector<Vector> m_normals;
			std::vector<Vector> m_textures;
			std::vector<int> m_faces;
			Box m_box;
	};

}

#endif
