#include "Matrix/Matrix.h"

std::ostream& operator <<(std::ostream& os, const Matrix& a) {
	for (int i = 0; i < a.height; i++) {
		os << "| ";
		for (int j = 0; j < a.width; j++) {
			os << a.at(i, j) << " | ";
		}
		os << std::endl;
	}
	return os;
}
