#include "gtest/gtest.h"

#include <cmath>

#include "../../src/math/constant.h"
#include "../../src/math/extremum_calculator.h"
#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

class ExtremumCalculatorTest : public ::testing::Test {
protected:

    const double ERR_BOUND = 0.1;
};

TEST_F (ExtremumCalculatorTest, valueTest) {

    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");
    auto t = make_shared<Identity>("t");

    auto f = x + y + z + t;

    fparams_t params;
    params["t"] = 1.2;
    params["unused"] = -1.0;

    auto calc = make_shared<ExtremumCalculator>(f, params, ERR_BOUND / 5);
    calc->setParamBound("x", -0.2, 0.8);
    calc->setParamBound("y", -0.6, -0.1);
    calc->setParamBound("z", 1.4, 3.2);
    calc->calculate();


    ASSERT_NEAR(5.1, calc->maxVal(), ERR_BOUND);
    ASSERT_NEAR(1.8, calc->minVal(), ERR_BOUND);

    ASSERT_NEAR(0.8, calc->maxAt()["x"], ERR_BOUND);
    ASSERT_NEAR(-0.1, calc->maxAt()["y"], ERR_BOUND);
    ASSERT_NEAR(3.2, calc->maxAt()["z"], ERR_BOUND);

    ASSERT_NEAR(-0.2, calc->minAt()["x"], ERR_BOUND);
    ASSERT_NEAR(-0.6, calc->minAt()["y"], ERR_BOUND);
    ASSERT_NEAR(1.4, calc->minAt()["z"], ERR_BOUND);

}