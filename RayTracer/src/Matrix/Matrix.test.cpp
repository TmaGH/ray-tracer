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
		m.setData(matrixContent, 4*4);

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
		m.setData(matrixContent, 2 * 2);

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
		m.setData(matrixContent, 3 * 3);

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
	GIVEN("a specific matrix A AND a specific matrix B") {
		Matrix a{ 4, 4 };
		Matrix b{ 4, 4 };
		float matrixContent[] = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 8.0f, 7.0f, 6.0f,
			5.0f, 4.0f, 3.0f, 2.0f
		};

		a.setData(matrixContent, 4*4);
		b.setData(matrixContent, 4*4);

		CHECK_THAT(a, isEqualTo(b));

	}
}

