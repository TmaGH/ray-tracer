#include "Tuple.h"

std::ostream& operator <<(std::ostream& os, const Tuple& a) {
	return (os << "Tuple (" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << ")");
}

