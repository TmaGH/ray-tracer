#pragma once
#include<memory>
#include<algorithm>
#include <cmath>
#include "Log/Log.h"
#include "Tuple/Tuple.h"

class Matrix {
private:
	int width, height;
	std::shared_ptr <float[]> m_data;
public:
	Matrix(size_t w, size_t h): width(w), height(h) {
		m_data = std::make_shared<float[]>(w * h);
	}

	float at(int i, int j) const {
		return m_data[j + i * width];
	}

	void setData(float *m, int n) {
		if (n <= width * height) {
			std::copy(m, m + n, m_data.get());
		}
	}

	auto getData() const {
		return m_data;
	}

	bool operator ==(const Matrix& a) const {
		float* thisData = this->m_data.get();
		int thisLen = width * height;
		float* aData = a.getData().get();
		int aLen = width * height;
		if (thisLen == aLen) {
			auto mismatch = std::mismatch(
				thisData, thisData + thisLen,
				aData, aData + aLen,
				[](const float a, const float b) { return std::abs(a - b) < EPSILON; }
			);
			return std::abs(*mismatch.first - *mismatch.second) < EPSILON;
		}

		return false;
	}

	friend std::ostream& operator <<(std::ostream& os, const Matrix& a);
};