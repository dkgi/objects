#ifndef __OBJECTS_OBJECT_H
#define __OBJECTS_OBJECT_H

#include <iostream>

#include "Vector.h"

namespace Objects
{

	class Box
	{
		public:
			Box()
			{}

			Vector ll, ur;
	};

	class Object
	{
		public:
			Object()
			:
				m(0.0)
			{}

			float m;
			Vector x, v, F;

			Box bb;
	};



}

#endif
