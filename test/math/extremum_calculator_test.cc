#include "gtest/gtest.h"

#include <cmath>

#include "../../src/math/constant.h"
#include "../../src/math/extremum_calculator.h"
#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

class ExtremumCalculatorTest : public ::testing::Test {
protected:

    const double ERR_BOUND = 0.0000001;
};

TEST_F (ExtremumCalculatorTest, valueTest) {

    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");
    auto t = make_shared<Identity>("t");

    auto f = x + y + z + t;

    fparams_t params;
    params["t"] = 12.0;
    params["unused"] = -1.0;

    auto calc = make_shared<ExtremumCalculator>(f, params);
    calc->setParamBound("x", -2, 8);
    calc->setParamBound("y", -6, -1);
    calc->setParamBound("z", 14, 32);
    calc->calculate();


    ASSERT_NEAR(51, calc->maxVal(), ERR_BOUND);
    ASSERT_NEAR(18, calc->minVal(), ERR_BOUND);

    ASSERT_NEAR(8, calc->maxAt()["x"], ERR_BOUND);
    ASSERT_NEAR(-1, calc->maxAt()["y"], ERR_BOUND);
    ASSERT_NEAR(32, calc->maxAt()["z"], ERR_BOUND);

    ASSERT_NEAR(-2, calc->minAt()["x"], ERR_BOUND);
    ASSERT_NEAR(-6, calc->minAt()["y"], ERR_BOUND);
    ASSERT_NEAR(14, calc->minAt()["z"], ERR_BOUND);

}