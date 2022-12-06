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

	static Matrix translation(float x, float y, float z) {
		Matrix translationMatrix{ 4, 4 };

		float matrixContent[] = {
			1.0f, 0.0f, 0.0f, x,
			0.0f, 1.0f, 0.0f, y,
			0.0f, 0.0f, 1.0f, z,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		translationMatrix.setData(matrixContent);
		return translationMatrix;
	}

	static Matrix scaling(float x, float y, float z) {
		Matrix scalingMatrix{ 4, 4 };

		float matrixContent[] = {
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		scalingMatrix.setData(matrixContent);
		return scalingMatrix;
	}

	static Matrix rotationX(float r) {
		Matrix rotationXMatrix{ 4, 4 };

		float matrixContent[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, std::cos(r), -std::sin(r), 0.0f,
			0.0f, std::sin(r), std::cos(r), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		rotationXMatrix.setData(matrixContent);
		return rotationXMatrix;
	}

	static Matrix rotationY(float r) {
		Matrix rotationYMatrix{ 4, 4 };

		float matrixContent[] = {
			std::cos(r), 0.0f, std::sin(r), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-std::sin(r), 0.0f, std::cos(r), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		rotationYMatrix.setData(matrixContent);
		return rotationYMatrix;
	}

	static Matrix rotationZ(float r) {
		Matrix rotationZMatrix{ 4, 4 };

		float matrixContent[] = {
			std::cos(r), -std::sin(r), 0.0f, 0.0f,
			std::sin(r), std::cos(r), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		rotationZMatrix.setData(matrixContent);
		return rotationZMatrix;
	}

	static Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
		Matrix shearingMatrix{ 4, 4 };

		float matrixContent[] = {
			1.0f, xy, xz, 0.0f,
			yx, 1.0f, yz, 0.0f,
			zx, zy, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		shearingMatrix.setData(matrixContent);
		return shearingMatrix;
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

	static Matrix invert(Matrix a) {
		if (!a.isInvertible()) return a;

		Matrix b{ a.width, a.height };

		for (int i = 0; i < a.height; i++) {
			for (int j = 0; j < a.width; j++) {
				float c = a.cofactor(i, j);

				b.set(i, j, c / a.determinant());
			}
		}

		return 	Matrix::transpose(b);
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

	float minor(int row, int col) const {
		return Matrix::submatrix(*this, row, col).determinant();
	}

	float cofactor(int row, int col) const {
		float cof = minor(row, col);
		if ((row + col) % 2 != 0) cof = -1 * cof;
		return cof;
	}

	float determinant2x2() const {
		return at(0,0) * at(1,1) - at(0,1) * at(1,0);
	}

	float determinant() const {
		if (height == 2 && width == 2) return determinant2x2();

		float determinant = 0;
		int i = 0;

		for (int j = 0; j < width; j++) {
			determinant += at(i, j) * cofactor(i, j);
		}
		
		return determinant;
	}

	bool isInvertible() const {
		if (determinant() != 0) return true;
		return false;
	}

	Matrix operator *(const Matrix& b) const {
		if (height != b.width) return Matrix{ 0,0 };

		size_t n = height;
		Matrix c{ n, n };

		auto bT = Matrix::transpose(b);

		for (int ai = 0; ai < height; ai++) {
			for (int bi = 0; bi < bT.height; bi++) {
				float sum = 0.0;
				for (int j = 0; j < n; j++) {
					sum += at(ai, j) * bT.at(bi, j);
				}
				c.set(ai, bi, sum);
			}
		}
		return c;
	}

	Tuple operator *(const Tuple& b) const {
		if (height != 4 || width != 4) return Tuple{ 0,0,0,0 };

		float x = at(0, 0) * b.x + at(0, 1) * b.y + at(0, 2) * b.z + at(0, 3) * b.w;
		float y = at(1, 0) * b.x + at(1, 1) * b.y + at(1, 2) * b.z + at(1, 3) * b.w;
		float z = at(2, 0) * b.x + at(2, 1) * b.y + at(2, 2) * b.z + at(2, 3) * b.w;
		float w = at(3, 0) * b.x + at(3, 1) * b.y + at(3, 2) * b.z + at(3, 3) * b.w;

		return Tuple{ x, y, z, w };
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
