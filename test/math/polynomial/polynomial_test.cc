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
    ASSERT_EQ(polynomial->toString().c_str(), "\\left(7x^2yz^3 - 3t^2uv^3+2x^2tw^{30}\\right)");
}

TEST (PolynomialTest, arithmetics) {
    // (2x + 8) * (3y - 5) * (6z - 20) =
    // = (2x + 8) * (18yz -60y - 30z + 100) =
    // = 36xyz - 120xy - 60xz + 200x + 144yz - 480y - 240z + 800

    auto polynomial1 = make_shared<Polynomial>();
    polynomial1->add(make_shared<Monomial>("x", 1, 2));
    polynomial1->add(make_shared<Monomial>(8));

    auto polynomial2 = make_shared<Polynomial>();
    polynomial2->add(make_shared<Monomial>("y", 1, 3));
    auto tmp = make_shared<Polynomial>();
    tmp->add(make_shared<Monomial>(-5));
    polynomial2 = polynomial2->add(tmp);

    auto polynomial3 = make_shared<Polynomial>();
    polynomial3->add(make_shared<Monomial>("z", 1, 6));
    polynomial3->add(make_shared<Monomial>(-20));

    auto polynomial = polynomial1->multiply(polynomial2)->multiply(polynomial3);

    fret_t x = 2;
    fret_t y = 3;
    fret_t z = 4;

    fparams_t params;
    params["x"] = x;
    params["y"] = y;
    params["z"] = z;

    auto expected = 36*x*y*z - 120*x*y - 60*x*z + 200*x + 144*y*z - 480*y - 240*z + 800;

    ASSERT_EQ(polynomial->variables(), fvariables_t({"x", "y", "z"}));
    ASSERT_DOUBLE_EQ(( * polynomial)(params), expected);
}