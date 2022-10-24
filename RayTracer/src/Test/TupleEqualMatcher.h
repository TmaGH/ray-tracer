#pragma once
#include "catch.hpp"
#include "Tuple/Tuple.h"

// matcher class
class TupleEqualMatcher : public Catch::MatcherBase<Tuple> {
    Tuple tupleToTestAgainst;
public:
    TupleEqualMatcher(Tuple tupleToTestAgainst) : tupleToTestAgainst(tupleToTestAgainst) {}

    // Performs the test for this matcher
    bool match(Tuple const& a) const override {
        return a == tupleToTestAgainst;
    }

    // Produces a string describing what this matcher does. It should
    // include any provided data (the begin/ end in this case) and
    // be written as if it were stating a fact (in the output it will be
    // preceded by the value under test).
    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to " << tupleToTestAgainst;
        return ss.str();
    }
};

inline TupleEqualMatcher isEqualTo(Tuple a) {
    return TupleEqualMatcher(a);
}