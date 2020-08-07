#include "gtest/gtest.h"

#include "../../src/math/constant.h"
#include "../../src/math/function.h"
#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

class IntegralTest : public ::testing::Test {

private:

    double undefinedIntrX(double x, double y, double z) {
        return (x * x / 2 + x * y * z) / 2;
    }

    double undefinedIntrY(double x, double y, double z) {
        return (y * y * z / 2 + x * y) / 2;
    }

protected:

    const double START_X = -2;
    const double END_X = 7;

    const double START_Y = 3.14;
    const double END_Y = -18.4;

#if defined FULL_TEST
    const double ERR_BOUND = 0.00001;
#else
    const double ERR_BOUND = 0.01;
#endif

    double totalValByX(double x, double y, double z) {
        return undefinedIntrX(END_X, y, z) - undefinedIntrX(START_X, y, z);
    };

    double totalValByY(double x, double y, double z) {
        return undefinedIntrY(x, END_Y, z) - undefinedIntrY(x, START_Y, z);
    };
};

TEST_F (IntegralTest, integration) {
    auto c5 = make_shared<Constant>(5);
    auto c3 = make_shared<Constant>(3);
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");


    auto integralX_ptr = ((x + y * z) / (c5 - c3))->integrate(
        START_X, END_X, "x", ERR_BOUND);
    const auto& integralX = *integralX_ptr;

    auto integralY_ptr = ((x + y * z) / (c5 - c3))->integrate(
        START_Y, END_Y, "y", ERR_BOUND);
    const auto& integralY = *integralY_ptr;

    auto integralZ_ptr = ((x + y * z) / (c5 - c3))->integrate(
        START_X, START_X, "z", ERR_BOUND);
    const auto& integralZ = *integralZ_ptr;

    fparams_t params;
    params["x"] = 1.0;
    params["y"] = 2.0;
    params["z"] = 9.0;
    params["unused"] = -1.0;

    ASSERT_NEAR(integralX(params), totalValByX(1.0, 2.0, 9.0), ERR_BOUND);

    params["x"] = -20.0;
    params["y"] = 3.14;
    params["z"] = 0.002;

    ASSERT_NEAR(integralY(params), totalValByY(-20.0, 3.14, 0.002), ERR_BOUND);

    ASSERT_NEAR(integralZ(params), 0, ERR_BOUND);

    ASSERT_EQ(integralX.variables(), fvariables_t({"y", "z"}));
    ASSERT_EQ(integralY.variables(), fvariables_t({"x", "z"}));
    ASSERT_EQ(integralZ.variables(), fvariables_t({}));

    auto f = string("\\frac{\\left(x + \\left(y * z\\right)\\right)}{\\left(5 - 3\\right)}");

    ASSERT_STREQ(integralX.toString().c_str(), ("\\int_{-2}^{7}\\left(" + f + "\\right)\\,dx").c_str());
    ASSERT_STREQ(integralY.toString().c_str(), ("\\int_{3.14}^{-18.4}\\left(" + f + "\\right)\\,dy").c_str());
    ASSERT_STREQ(integralZ.toString().c_str(), ("\\int_{-2}^{7}\\left(" + f + "\\right)\\,dz").c_str());
}
