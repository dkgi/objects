#ifndef __OBJECTS_CONTEXT_H
#define __OBJECTS_CONTEXT_H

#include <cmath>

#include "Vector.h"
#include "Matrix.h"

namespace Objects
{


	class MouseContext
	{
		public:
			MouseContext()
			:
				position(250, 250),
				defaultPosition(250, 250),
				orientation(0, 0, 1),
				sensitivity(0.5),
				ireference(1.0/250)
			{
			}

			void passiveMotion(int x, int y)
			{
				Point dm(x - defaultPosition(0), y - defaultPosition(1));
				position += dm;

				// Rotate orientation
				float da = -dm(1) * ireference * M_PI/2.0 * sensitivity;
				float db = dm(0) * ireference * M_PI/2.0 * sensitivity;
				Matrix r = Matrix::Rotation(da, db, 0);
				orientation = r*orientation;
			}

			void adjustReference(int w, int h)
			{
				ireference = 1.0 / std::min(w, h);
			}

			Point position;
			Point defaultPosition;
			Vector orientation;
			float sensitivity;
			float ireference;

	};


	class InputContext
	{
		public:
			InputContext()
			:
				keyDown(1 << (8*sizeof(unsigned char)), false)
			{
			}

			void keyboard(unsigned char key, int x, int y)
			{
				keyDown[key] = true;
			}

			void keyboardUp(unsigned char key, int x, int y)
			{
				keyDown[key] = false;
			}

			std::vector<bool> keyDown;
			MouseContext mouse;
	};
	
	std::ostream& operator<<(std::ostream& out, const InputContext &ic)
	{
		out << "Ref: " << ic.mouse.ireference<< "\n";
		return out << "Mouse: " << ic.mouse.position << ", " << ic.mouse.orientation;
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
