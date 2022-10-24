#pragma once
#include "Log/Log.h"
#include <iostream>
#include <cmath>
#include <cassert>

const float EPSILON = 0.00001;

class Tuple
{
public:
	float x, y, z, w;
	Tuple() : x(0), y(0), z(0), w(0) {};
	Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	bool isPoint() {
		return w == 1.0;
	}

	bool isVector() {
		return w == 0.0;
	}

	static Tuple point(float x, float y, float z) {
		return Tuple(x, y, z, 1.0);
	}

	static Tuple vector(float x, float y, float z) {
		return Tuple(x, y, z, 0.0);
	}

	bool operator ==(const Tuple& a) const {
		return std::abs(a.x - x) < EPSILON
			&& std::abs(a.y - y) < EPSILON
			&& std::abs(a.z - z) < EPSILON
			&& std::abs(a.w - w) < EPSILON;
	}

	Tuple operator +(const Tuple& a) const {
		return Tuple(x + a.x, y + a.y, z + a.z, w + a.w);
	}

	Tuple operator -() const {
		return Tuple(-x, -y, -z, -w);
	}

	Tuple operator -(const Tuple& a) const {
		return Tuple(x - a.x, y - a.y, z - a.z, w - a.w);
	}

	Tuple operator *(float s) const {
		return Tuple(x * s, y * s, z * s, w * s);
	}

	Tuple operator /(float s) const {
		return *this * (1 / s);
	}

	float magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Tuple normalized() const {
		return *this / this->magnitude();
	}

	float dot(const Tuple& a) const {
		return x * a.x + y * a.y + z * a.z + a.w * a.w;
	}

	Tuple cross(const Tuple& a) const {
		assert(a.w == 0);
		return Tuple::vector(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
	}

	friend std::ostream& operator <<(std::ostream& os, const Tuple& a);
};

const Tuple ZERO_VECTOR = Tuple(0, 0, 0, 0);
