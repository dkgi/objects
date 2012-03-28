#ifndef __OBJECTS_OBJECT_H
#define __OBJECTS_OBJECT_H

#include <vector>
#include <iostream>

namespace Objects
{

	class Box
	{
		public:
			Box()
			:
				ll(3, 0.0),
				ur(3, 0.0)
			{}

			std::vector<float> ll, ur;
	};

	class Object
	{
		public:
			Object()
			:
				m(0.0), 
				x(3, 0.0),
				F(3, 0.0)
			{}

			float m;
			std::vector<float> x;
			std::vector<float> F;

			Box bb;
	};



}

#endif
