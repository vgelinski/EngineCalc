#include "gtest/gtest.h"

#include "../../../src/math/polynomial/monomial.h"

using namespace std;
using namespace engc::math;

TEST (MonomialTest, common) {
    auto monomialPtr = make_shared<Monomial>();
    monomialPtr->addVariable("x", 2);
    monomialPtr->addVariable("y", 1);
    monomialPtr->addVariable("z", 3);
    monomialPtr->setMultiplier(7);

    const auto& monomial = * monomialPtr;

    fparams_t params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    params["z"] = 4.0;

    ASSERT_EQ(monomial.variables(), fvariables_t({"x", "y", "z"}));
    ASSERT_DOUBLE_EQ(monomial(params), 7 * 2 * 2 * 3 * 4 * 4 * 4);
}