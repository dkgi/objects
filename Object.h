#ifndef __OBJECTS_OBJECT_H
#define __OBJECTS_OBJECT_H

#include <iostream>

#include "Vector.h"
#include "Mesh.h"

namespace Objects
{

	class Object
	{
		public:
			Object(float m)
			{
				m_m = m;
			}

			~Object()
			{
				if (m_shape != NULL) delete m_shape;
			}

			void applyForce(const Vector &f)
			{
				m_F += f;
			}

			void step(const TimingContext &timing)
			{
				Vector a = m_F / m_m;
				m_v += timing.dt * a;
				m_x += timing.dt * m_v;
			}

		protected:
			float m_m;
			Vector m_x, m_v, m_F;

			Mesh *m_shape;
	};

}

#endif
