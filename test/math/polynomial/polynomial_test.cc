#include "gtest/gtest.h"

#include "../../../src/math/polynomial/polynomial.h"

using namespace std;
using namespace engc::math;

shared_ptr<Monomial> getMonomial1() {
    auto monomial = make_shared<Monomial>();
    monomial->addVariable("x", 2);
    monomial->addVariable("y", 1);
    monomial->addVariable("z", 3);
    monomial->setMultiplier(7);
    return monomial;
}

shared_ptr<Monomial> getMonomial2() {
    auto monomial = make_shared<Monomial>();
    monomial->addVariable("t", 2);
    monomial->addVariable("u", 1);
    monomial->addVariable("v", 3);
    monomial->setMultiplier(-3);
    return monomial;
}

shared_ptr<Monomial> getMonomial3() {
    auto monomial = make_shared<Monomial>();
    monomial->addVariable("x", 2);
    monomial->addVariable("t", 1);
    monomial->addVariable("w", 30);
    monomial->setMultiplier(2);
    return monomial;
}


TEST (PolynomialTest, common) {
    auto polynomial = make_shared<Polynomial>();
    polynomial->add(getMonomial1());
    polynomial->add(getMonomial2());
    polynomial->add(getMonomial3());


    fparams_t params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    params["z"] = 4.0;
    params["t"] = 2.0;
    params["u"] = 3.0;
    params["v"] = 4.0;
    params["w"] = 1.0;

    ASSERT_EQ(polynomial->variables(), fvariables_t({"x", "y", "z", "t", "u", "v", "w"}));
    ASSERT_DOUBLE_EQ(( * polynomial)(params), 4 * 2 * 2 * 3 * 4 * 4 * 4 + 16);
}