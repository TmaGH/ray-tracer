#include "catch.hpp"
#include "Matrix/Matrix.h"
#include "Test/MatrixEqualMatcher.h"

SCENARIO("Constructing and inspecting a 4x4 matrix") {
	GIVEN("a specific 4x4 matrix M") {
		Matrix m{ 4, 4 };
		float matrixContent[] = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.5f, 6.5f, 7.5f, 8.5f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.5f, 14.5f, 15.5f, 16.5f
		};
		m.setData(matrixContent);

		THEN("M[0, 0] = 1") {
			REQUIRE(m.at(0, 0) == 1.0f);
		}

		THEN("M[0, 3] = 4") {
			REQUIRE(m.at(0, 3) == 4.0f);
		}

		THEN("M[1, 0] = 5.5") {
			REQUIRE(m.at(1, 0) == 5.5f);
		}

		THEN("M[1, 2] = 7.5") {
			REQUIRE(m.at(1, 2) == 7.5f);
		}

		THEN("M[2, 2] = 11.0") {
			REQUIRE(m.at(2, 2) == 11.0f);
		}

		THEN("M[3, 0] = 13.5") {
			REQUIRE(m.at(3, 0) == 13.5f);
		}

		THEN("M[3, 2] = 15.5") {
			REQUIRE(m.at(3, 2) == 15.5f);
		}
	}
}

SCENARIO("A 2x2 matrix ought to be representable") {
	GIVEN("a specific 2x2 matrix M") {
		Matrix m{ 2, 2 };
		float matrixContent[] = {
			-3.0f, 5.0f, 1.0f, -2.0f
		};
		m.setData(matrixContent);

		THEN("M[0, 0] = -3") {
			REQUIRE(m.at(0, 0) == -3.0f);
		}

		THEN("M[0, 1] = 5") {
			REQUIRE(m.at(0, 1) == 5.0f);
		}

		THEN("M[1, 0] = 1") {
			REQUIRE(m.at(1, 0) == 1.0f);
		}

		THEN("M[1, 1] = -2") {
			REQUIRE(m.at(1, 1) == -2);
		}
	}
}

SCENARIO("A 3x3 matrix ought to be representable") {
	GIVEN("a specific 3x3 matrix M") {
		Matrix m{ 3, 3 };
		float matrixContent[] = {
			-3.0f, 5.0f, 0.0f,
			1.0f, -2.0f, -7.0f,
			0.0f, 1.0f, 1.0f
		};
		m.setData(matrixContent);

		THEN("M[0, 0] = -3") {
			REQUIRE(m.at(0, 0) == -3.0f);
		}

		THEN("M[1, 1] = -2") {
			REQUIRE(m.at(1, 1) == -2.0f);
		}

		THEN("M[2, 2] = 1") {
			REQUIRE(m.at(2, 2) == 1.0f);
		}
	}
}

SCENARIO("Matrix equality with identical matrices") {
	GIVEN("a specific matrix A AND B") {
		Matrix a{ 4, 4 };
		Matrix b{ 4, 4 };
		float matrixContent[] = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 8.0f, 7.0f, 6.0f,
			5.0f, 4.0f, 3.0f, 2.0f
		};

		a.setData(matrixContent);
		b.setData(matrixContent);

		THEN("A = B") {
			CHECK_THAT(a, isEqualTo(b));
		}
	}
}

SCENARIO("Matrix equality with different matrices") {
	GIVEN("a specific matrix A AND B ") {
		Matrix a{ 4, 4 };
		Matrix b{ 4, 4 };
		float matrixContent[] = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 8.0f, 7.0f, 6.0f,
			5.0f, 4.0f, 3.0f, 2.0f
		};
		float matrixContent2[] = {
			1.0f, 2.0f, 9.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 8.0f, 7.0f, 6.0f,
			5.0f, 4.0f, 3.0f, 2.0f
		};


		a.setData(matrixContent);
		b.setData(matrixContent2);

		THEN("A != B") {
			REQUIRE(a != b);
		}
	}
}

SCENARIO("Multiplying two matrices") {
	GIVEN("a matrix A AND B") {
		Matrix a{ 4, 4 };
		Matrix b{ 4, 4 };
		Matrix result{ 4, 4 };
		float matrixContent[] = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 8.0f, 7.0f, 6.0f,
			5.0f, 4.0f, 3.0f, 2.0f
		};
		float matrixContent2[] = {
			-2.0f, 1.0f, 2.0f, 3.0f,
			3.0f, 2.0f, 1.0f, -1.0f,
			4.0f, 3.0f, 6.0f, 5.0f,
			1.0f, 2.0f, 7.0f, 8.0f,
		};
		float resultMatrix[] = {
			20.0f, 22.0f, 50.0f, 48.0f,
			44.0f, 54.0f, 114.0f, 108.0f,
			40.f, 58.0f, 110.0f, 102.0f,
			16.0f, 26.0f, 46.0f, 42.0f
		};
		a.setData(matrixContent);
		b.setData(matrixContent2);
		result.setData(resultMatrix);

		THEN("A * B is the expected 4x4 matrix") {
			CHECK_THAT(a * b, isEqualTo(result));
		}
	}
}

SCENARIO("Multiplying a matrix by the identity matrix") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 8.0f, 7.0f, 6.0f,
			5.0f, 4.0f, 3.0f, 2.0f
		};
		a.setData(matrixContent);

		THEN("A * identity = A") {
			CHECK_THAT(a * Matrix::getFourByFourIdentity(), isEqualTo(a));
		}
	}
}

SCENARIO("Transposing a matrix") {
	GIVEN("a matrix A") {
			Matrix a{ 4, 4 };
			float matrixContent[] = {
				0.0f, 9.0f, 3.0f, 0.0f,
				9.0f, 8.0f, 0.0f, 8.0f,
				1.0f, 8.0f, 5.0f, 3.0f,
				0.0f, 0.0f, 5.0f, 8.0f,
			};
			a.setData(matrixContent);

			Matrix transposeOfA{ 4,4 };
			float transposedMatrixContent[] = {
				0.0f, 9.0f, 1.0f, 0.0f,
				9.0f, 8.0f, 8.0f, 0.0f,
				3.0f, 0.0f, 5.0f, 5.0f,
				0.0f, 8.0f, 3.0f, 8.0f,
			};
			transposeOfA.setData(transposedMatrixContent);

		THEN("transpose(A) is the transposed matrix of A") {
			CHECK_THAT(Matrix::transpose(a), isEqualTo(transposeOfA));
		}
	}
}

SCENARIO("Transposing the identity matrix") {
	GIVEN("A <- transpose(identity_matrix)") {
		Matrix a = Matrix::transpose(Matrix::getFourByFourIdentity());
		THEN("A = identity_matrix") {
			CHECK_THAT(a, isEqualTo(Matrix::getFourByFourIdentity()));
		}
	}
}


SCENARIO("Calculating the determinant of a 2x2 matrix") {
	GIVEN("a 2x2 matrix A") {
		Matrix a{ 2, 2 };
		float matrixContent[] = {
			1.0f, 5.0f,
			-3.0f, 2.0f,
		};
		a.setData(matrixContent);

		THEN("determinant(A) = 17") {
			REQUIRE(a.determinant2x2() == 17);
		}
	}
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix") {
	GIVEN("a 3x3 matrix A") {
		Matrix a{ 3, 3 };
		float matrixContent[] = {
			1.0f, 5.0f, 0.0f,
			-3.0f, 2.0f, 7.0f,
			0.0f, 6.0f, -3.0f,
		};
		a.setData(matrixContent);

		THEN("submatrix(A, 0, 2) is a 2x2 matrix with row 0 and column 2 removed") {
			Matrix subA{ 2,2 };
			float MatrixSubContent[] = {
				-3.0f, 2.0f,
				0.0f, 6.0f,
			};
			subA.setData(MatrixSubContent);

			CHECK_THAT(Matrix::submatrix(a, 0, 2), isEqualTo(subA));
		}
	}
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			-6.0f, 1.0f, 1.0f, 6.0f,
			-8.0f, 5.0f, 8.0f, 6.0f,
			-1.0f, 0.0f, 8.0f, 2.0f,
			-7.0f, 1.0f, -1.0f, 1.0f,
		};
		a.setData(matrixContent);

		THEN("submatrix(A, 2, 1) is a 3x3 matrix with row 2 and column 1 removed") {
			Matrix subA{ 3,3 };
			float MatrixSubContent[] = {
				-6.0f, 1.0f, 6.0f,
				-8.0f, 8.0f, 6.0f,
				-7.0f, -1.0f, 1.0f,
			};
			subA.setData(MatrixSubContent);

			CHECK_THAT(Matrix::submatrix(a, 2, 1), isEqualTo(subA));
		}
	}
}

