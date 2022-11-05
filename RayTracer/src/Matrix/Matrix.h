#pragma once
#include<memory>
#include<algorithm>
#include <cmath>
#include "Log/Log.h"
#include "Tuple/Tuple.h"

class Matrix {
private:
	size_t width, height;
	std::shared_ptr <float[]> m_data;
public:
	Matrix(size_t w, size_t h): width(w), height(h) {
		m_data = std::make_shared<float[]>(w * h);
	}

	static Matrix getFourByFourIdentity() {
		Matrix identity{ 4, 4};

		float matrixContent[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		identity.setData(matrixContent);
		return identity;
	}

	static Matrix submatrix(Matrix a, int row, int col) {
		size_t subWidth = a.width - 1, subHeight = a.height - 1;
		Matrix sub{ subWidth, subHeight };
		int subI = 0, subJ = 0;

		for (int i = 0; i < a.height; i++) {
			for (int j = 0; j < a.width; j++) {
				if (i == row || j == col) continue;
				if (subJ == subWidth) {
					subJ = 0;
					subI++;
				}
				if (subI == subHeight) break;

				sub.set(subI, subJ, a.at(i, j));
				subJ++;
			}
			if (subI == subHeight) break;
		}

		return sub;
	};

	static Matrix transpose(Matrix a) {
		Matrix transposeMatrix{ a.width, a.height };
		for (int i = 0; i < a.height; i++) {
			for (int j = 0; j < a.width; j++) {
				transposeMatrix.set(i, j, a.at(j, i));
			}
		}

		return transposeMatrix;
	}

	float at(int i, int j) const {
		return m_data[j + i * width];
	}

	void set(int i, int j, float val) {
		m_data[j + i * width] = val;
	}

	void setData(float *m) {
		std::copy(m, m + height * width, m_data.get());
	}

	auto getData() const {
		return m_data;
	}

	float determinant2x2() const {
		return at(0,0) * at(1,1) - at(0,1) * at(1,0);
	}

	Matrix operator *(const Matrix& b) const {
		if (height != b.width) return Matrix{ 0,0 };

		size_t n = height;
		Matrix c{ n, n };

		auto bT = Matrix::transpose(b);

		for (int ai = 0; ai < height; ai++) {
			for (int bi = 0; bi < bT.height; bi++) {
				double sum = 0.0;
				for (int j = 0; j < n; j++) {
					sum += at(ai, j) * bT.at(bi, j);
				}
				c.set(ai, bi, sum);
			}
		}
		return c;
	}

	bool operator ==(const Matrix& a) const {
		if (width * height != a.width * a.height) return false;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (std::abs(at(i, j) - a.at(i, j)) > EPSILON) return false;
			}
		}

		return true;
	}

	friend std::ostream& operator <<(std::ostream& os, const Matrix& a);
};
