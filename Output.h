#ifndef __OBJECTS_OUTPUT_H
#define __OBJECTS_OUTPUT_H

namespace Objects
{

	std::ostream& operator<<(std::ostream& out, const std::vector<float>& v)
	{
		unsigned int i;
		out << "[";
		for (i = 0; i < v.size()-1; i++) out << v[i] << ", ";
		return out << v[i] << "]";
	}

	std::ostream& operator<<(std::ostream& out, const Object &o)
	{
		return out << o.m << " @ " << o.x;
	}

	std::ostream& operator<<(std::ostream& out, const Box &b)
	{
		return out << "[" << b.ll << "/" << b.ur << "]";
	}

}

#endif
