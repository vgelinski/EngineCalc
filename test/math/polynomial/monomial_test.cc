#include "gtest/gtest.h"

#include "../../../src/math/polynomial/monomial.h"

using namespace std;
using namespace engc::math;

TEST (MonomialTest, common) {
    auto monomialPtr = make_shared<Monomial>("x", 2, 7)
            ->multiply(make_shared<Monomial>("y", 1))
            ->multiply(make_shared<Monomial>("z", 3));

    const auto& monomial = * monomialPtr;

    fparams_t params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    params["z"] = 4.0;

    ASSERT_EQ(monomial.variables(), fvariables_t({"x", "y", "z"}));
    ASSERT_DOUBLE_EQ(monomial(params), 7 * 2 * 2 * 3 * 4 * 4 * 4);
}