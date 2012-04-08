#ifndef __OBJECTS_CONTEXT_H
#define __OBJECTS_CONTEXT_H

#include <vector>

#include "Vector.h"
#include "Matrix.h"

namespace Objects
{


	class InputContext
	{
		public:
			InputContext()
			:
				defaultPosition(250, 250),
				keyDown(1 << (8*sizeof(unsigned char)), false)
			{
				position = defaultPosition;
			}

			Point position;
			Point defaultPosition;
			Point dx;

			std::vector<bool> keyDown;
	};



	class TimingContext 
	{
		public:
			TimingContext()
			{
				then = 0.0;
				t = 0.0;
			}

			int then, now;
			float dt;
			float t;
	};

}

#endif
