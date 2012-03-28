#ifndef __OBJECTS_CONTEXT_H
#define __OBJECTS_CONTEXT_H

#include <vector>

namespace Objects
{

	class InputContext
	{
		public:
			InputContext()
			:
				keyDown(1 << (8*sizeof(unsigned char)), false),
				mouse(2, 250)
			{}

			std::vector<bool> keyDown;
			std::vector<int> mouse;

	};


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
