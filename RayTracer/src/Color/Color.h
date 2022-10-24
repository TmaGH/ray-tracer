#pragma once
#include "Tuple/Tuple.h"

class Color : public Tuple
{
public:
	Color(): Tuple(0, 0, 0, 0) {};
	Color(float r, float g, float b) : Tuple(r, g, b, 0) {};
	Color(const Tuple &a) : Tuple(a.x, a.y, a.z, 0) {};

	float red() const {
		return x;
	}

	float green() const {
		return y;
	}

	float blue() const {
		return z;
	}

	Color operator *(const Color& c) const {
		return Color(red() * c.red(), green() * c.green(), blue() * c.blue());
	}

	Color operator *(float s) const {
		return Tuple::operator*(s);
	}


};
