#ifndef __OBJECTS_SIMULATION_H
#define __OBJECTS_SIMULATION_H

#include <vector>
#include <algorithm>

#include "Context.h"
#include "Object.h"

namespace Objects
{

	class Simulation
	{
		public:
			Simulation()
			{
			}

			~Simulation()
			{
			}

			void step(const TimingContext &timing)
			{
			}

			const std::vector<Object*>& getObjects()
			{
				return objects;
			}

		private:
			std::vector<Object*> objects;
			std::vector<Vector*> forces;

	};

}

#endif
