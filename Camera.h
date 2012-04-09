#ifndef __OBJECTS_CAMERA_H
#define __OBJECTS_CAMERA_H

#include "Vector.h"
#include "Context.h"

namespace Objects
{

	class Camera
	{
		public:
			Camera()
			:
				m_position(0.0, 0.0, -5.0),
				m_orientation(Matrix::Identity())
			{
				m_speed = 5.0;
				m_sensitivity = 1.0;
				m_inverted = -1.0;
			}

			void step(const TimingContext &timing, const InputContext &input)
			{
				Vector dz = m_orientation.column(2) * m_speed * timing.dt;
				Vector dx = m_orientation.column(0) * m_speed * timing.dt;
				if (input.keyDown['s']) m_position -= dz;
				if (input.keyDown['w']) m_position += dz;
				if (input.keyDown['d']) m_position -= dx;
				if (input.keyDown['a']) m_position += dx;
			}

			void mouseMotion(const InputContext &input)
			{
				float db = input.dx(0) * m_isize * M_PI/2.0 * m_sensitivity;
				float da = input.dx(1) * m_isize * M_PI/2.0 * m_sensitivity * m_inverted;
				m_angles += Vector(da, db, 0);
				m_orientation = Matrix::Rotation(m_angles(0), m_angles(1), m_angles(2));
			}

			void reshape(int w, int h)
			{
				m_isize = 1.0 / std::min(w, h);
			}

			Vector position() { return m_position; }

			Vector at() { return m_position + m_orientation.column(2); }

			Vector up() { return m_orientation.column(1); }


		protected:
			Vector m_position;
			Vector m_angles;
			Matrix m_orientation;

			float m_speed;
			float m_sensitivity;
			float m_isize;
			float m_inverted;
	};

}

#endif
