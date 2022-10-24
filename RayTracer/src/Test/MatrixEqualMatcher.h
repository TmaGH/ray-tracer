#pragma once
#include "catch.hpp"
#include "Matrix/Matrix.h"

// matcher class
class MatrixEqualMatcher: public Catch::MatcherBase<Matrix> {
    Matrix matrixToTestAgainst;
public:
    MatrixEqualMatcher(Matrix matrixToTestAgainst) : matrixToTestAgainst(matrixToTestAgainst) {}

    // Performs the test for this matcher
    bool match(Matrix const& a) const override {
        return a == matrixToTestAgainst;
    }

    // Produces a string describing what this matcher does. It should
    // include any provided data (the begin/ end in this case) and
    // be written as if it were stating a fact (in the output it will be
    // preceded by the value under test).
    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to " << std::endl << matrixToTestAgainst;
        return ss.str();
    }
};

inline MatrixEqualMatcher isEqualTo(Matrix a) {
    return MatrixEqualMatcher(a);
}
