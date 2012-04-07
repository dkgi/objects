#ifndef __OBJECTS_CONTEXT_H
#define __OBJECTS_CONTEXT_H

#include <cmath>

#include "Vector.h"
#include "Matrix.h"

namespace Objects
{


	class InputContext
	{
		public:
			InputContext()
			:
				position(250, 250),
				defaultPosition(250, 250),
				orientation(Matrix::Identity()),
				sensitivity(0.5),
				ireference(1.0/250),
				keyDown(1 << (8*sizeof(unsigned char)), false)
			{
			}

			void passiveMotion(int x, int y)
			{
				Point dm(x - defaultPosition(0), y - defaultPosition(1));
				position += dm;

				// Rotate orientation
				float da = dm(1) * ireference * M_PI/2.0 * sensitivity;
				float db = -dm(0) * ireference * M_PI/2.0 * sensitivity;
				angles += Vector(da, db, 0);
				orientation = Matrix::Rotation(angles(0), angles(1), angles(2));
			}

			void reshape(int w, int h)
			{
				ireference = 1.0 / std::min(w, h);
			}

			void keyboard(unsigned char key, int x, int y)
			{
				keyDown[key] = true;
			}

			void keyboardUp(unsigned char key, int x, int y)
			{
				keyDown[key] = false;
			}

			Point position;
			Point defaultPosition;
			Vector angles;
			Matrix orientation;
			float sensitivity;
			float ireference;
			std::vector<bool> keyDown;

	};

	
	std::ostream& operator<<(std::ostream& out, const InputContext &ic)
	{
		return out;
	}


	class SimulationContext
	{
		public:
			SimulationContext()
			{}

			int then, now;
			float dt;

	};

}

#endif
