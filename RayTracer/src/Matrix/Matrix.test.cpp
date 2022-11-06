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
			float matrixSubContent[] = {
				-6.0f, 1.0f, 6.0f,
				-8.0f, 8.0f, 6.0f,
				-7.0f, -1.0f, 1.0f,
			};
			subA.setData(matrixSubContent);

			CHECK_THAT(Matrix::submatrix(a, 2, 1), isEqualTo(subA));
		}
	}
}

SCENARIO("Calculating a minor of a 3x3 matrix") {
	GIVEN("a 3x3 matrix A AND B <- submatrix(A, 1, 0)") {
		Matrix a{ 3, 3 };
		float matrixContent[] = {
			3.0f, 5.0f, 0.0f,
			2.0f, -1.0f, -7.0f,
			6.0f, -1.0f, 5.0f,
		};
		a.setData(matrixContent);
		Matrix b = Matrix::submatrix(a, 1, 0);

		THEN("determinant(B) = 25 AND minor(A, 1, 0) = 25") {
			REQUIRE(b.determinant2x2() == 25);
			REQUIRE(a.minor(1, 0) == 25);
		}
	}
}

SCENARIO("Calculating a cofactor of a 3x3 matrix") {
	GIVEN("a 3x3 matrix A") {
		Matrix a{ 3, 3 };
		float matrixContent[] = {
			3.0f, 5.0f, 0.0f,
			2.0f, -1.0f, -7.0f,
			6.0f, -1.0f, 5.0f,
		};
		a.setData(matrixContent);

		THEN("minor(A, 0, 0) = -12 AND cofactor(A, 0, 0) = -12 AND minor(A, 1, 0) = 25 AND cofactor(A, 1, 0) = -25") {
			REQUIRE(a.minor(0, 0) == -12);
			REQUIRE(a.minor(1, 0) == 25);


		}
	}
}

SCENARIO("Calculating the determinant of a 3x3 matrix") {
	GIVEN("a 3x3 matrix A") {
		Matrix a{ 3, 3 };
		float matrixContent[] = {
			1.0f, 2.0f, 6.0f,
			-5.0f, 8.0f, -4.0f,
			2.0f, 6.0f, 4.0f
		};
		a.setData(matrixContent);

		THEN("cofactor(A, 0, 0) = 56 AND cofactor(A, 0, 1) = 12 AND cofator(A, 0, 2 = -46 AND determinant(A) = -196") {
			REQUIRE(a.cofactor(0, 0) == 56);
			REQUIRE(a.cofactor(0, 1) == 12);
			REQUIRE(a.cofactor(0, 2) == -46);
			REQUIRE(a.determinant() == -196);
		}
	}
}

SCENARIO("Calculating the determinant of a 4x4 matrix") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			-2.0f, -8.0f, 3.0f, 5.0f,
			-3.0f, 1.0f, 7.0f, 3.0f,
			1.0f, 2.0f, -9.0f, 6.0f,
			-6.0f, 7.0f, 7.0f, -9.0f,
		};
		a.setData(matrixContent);

		THEN("cofactor(A, 0,0) = 690 AND cofactor(A, 0, 1) = 447 AND cofactor(A, 0, 2) = 210 AND cofactor(A, 0, 3) = 51 AND determinant(A) = -4071") {
			REQUIRE(a.cofactor(0, 0) == 690);
			REQUIRE(a.cofactor(0, 1) == 447);
			REQUIRE(a.cofactor(0, 2) == 210);
			REQUIRE(a.cofactor(0, 3) == 51);
			REQUIRE(a.determinant() == -4071);
		}

	}
}

SCENARIO("Testing a invertible matrix for invertibility") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			6.0f, 4.0f, 4.0f, 4.0f,
			5.0f, 5.0f, 7.0f, 6.0f,
			4.0f, -9.0f, 3.0f, -7.0f,
			9.0f, 1.0f, 7.0f, -6.0f,
		};
		a.setData(matrixContent);

		THEN("determinant(A) = -2120 AND A is invertible") {
			REQUIRE(a.determinant() == -2120);
			REQUIRE(a.isInvertible());

		}
	}
}

SCENARIO("Testing a noninvertible matrix for invertibility") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			-4.0f, 2.0f, -2.0f, -3.0f,
			9.0f, 6.0f, 2.0f, 6.0f,
			0.0f, -5.0f, 1.0f, -5.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
		};
		a.setData(matrixContent);

		THEN("determinant(A) = 0 AND a is not invertible") {
			REQUIRE(a.determinant() == 0);
			REQUIRE(!a.isInvertible());
		}

	}
}

SCENARIO("Calculating the inverse of a matrix") {
	GIVEN("a 4x4 matrix A AND B <- inverse(A)") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			-5.0, 2.0f, 6.0f, -8.0f,
			1.0f, -5.0f, 1.0f, 8.0f,
			7.0f, 7.0f, -6.0f, -7.0f,
			1.0f, -3.0f, 7.0f, 4.0f,
		};
		a.setData(matrixContent);

		Matrix b = Matrix::invert(a);

		THEN("determinant(A) = 532") {
			REQUIRE(a.determinant() == 532);
		}
		
		THEN("cofactor(A, 2, 3) = -160 AND B[3,2] = -160/532") {
			REQUIRE(a.cofactor(2, 3) == -160);
			REQUIRE(std::abs(b.at(3, 2) - (-160.0f / 532)) < EPSILON);
		}

		THEN("cofactor(A, 3, 2) = 105 AND B[2,3] = 105/532") {
			REQUIRE(a.cofactor(3, 2) == 105);
			REQUIRE(std::abs(b.at(2, 3) - 105.0f / 532) < EPSILON);
		}

		THEN("B is the correct inverse matrix of A") {
			Matrix bExpected{ 4, 4 };
			float expectedContent[] = {
				0.21805f, 0.45113f, 0.24060f, -0.04511f,
				-0.80827f, -1.45677f, -0.44361f, 0.52068f,
				-0.07895f, -0.22368f, -0.05263f, 0.19737f,
				-0.52256f, -0.81391f, -0.30075f, 0.30639f,
			};
			bExpected.setData(expectedContent);

			CHECK_THAT(b, isEqualTo(bExpected));
		}
	}
}

SCENARIO("Calculating the inverse of another matrix") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			8.0f, -5.0f, 9.0f, 2.0f,
			7.0f, 5.0f, 6.0f, 1.0f,
			-6.0f, 0.0f, 9.0f, 6.0f,
			-3.0f, 0.0f, -9.0f, -4.0f,
		};
		a.setData(matrixContent);

		Matrix b = Matrix::invert(a);

		THEN("inverse(A) is the correct inverse matrix of A") {
			Matrix bExpected{ 4, 4 };
			float expectedContent[] = {
				-0.15385f, -0.15385f, -0.28205f, -0.53846f,
				-0.07692f, 0.12308f, 0.02564f, 0.03077f,
				0.35897f, 0.35897f, 0.43590f, 0.92308f,
				-0.69231f, -0.69231f, -0.76923f, -1.92308f, 
			};
			bExpected.setData(expectedContent);

			CHECK_THAT(b, isEqualTo(bExpected));
		}
	}
}

SCENARIO("Calculating the inverse of a third matrix") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4, 4 };
		float matrixContent[] = {
			9.0f, 3.0f, 0.0f, 9.0f,
			-5.0f, -2.0f, -6.0f, -3.0f,
			-4.0f, 9.0f, 6.0f, 4.0f,
			-7.0f, 6.0f, 6.0f, 2.0f,
		};
		a.setData(matrixContent);

		Matrix b = Matrix::invert(a);

		THEN("inverse(A) is the correct inverse matrix of A") {
			Matrix bExpected{ 4, 4 };
			float expectedContent[] = {
				-0.04074f, -0.07778f, 0.14444f, -0.22222f, 
				-0.07778f, 0.03333f, 0.36667f, -0.33333f, 
				-0.02901f, -0.14630f, -0.10926f, 0.12963f, 
				0.17778f, 0.06667f, -0.26667f, 0.33333f, 
			};
			bExpected.setData(expectedContent);

			CHECK_THAT(b, isEqualTo(bExpected));
		}
	}
}

SCENARIO("Multiplying a product by its inverse") {
	GIVEN("a 4x4 matrix A") {
		Matrix a{ 4,4 };
		float matrixContent[] = {
			3.0f, -9.0f, 7.0f, 3.0f,
			3.0f, -8.0f, 2.0f, -9.0f,
			-4.0f, 4.0f, 4.0f, 1.0f,
			-6.0f, 5.0f, -1.0f, 1.0f,
		};

		GIVEN("a 4x4 matrix B AND C <- A * B") {
			Matrix b{ 4, 4 };
			float matrixContent[] = {
				8.0f, 2.0f, 2.0f, 2.0f,
				3.0f, -1.0f, 7.0f, 0.0f,
				7.0f, 0.0f, 5.0f, 4.0f,
				6.0f, -2.0f, 0.0f, 5.0f,
			};

			Matrix c = a * b;

			THEN("C * inverse(B) = A") {
				CHECK_THAT(c * Matrix::invert(b), isEqualTo(a));
			}
		}
	}
}

