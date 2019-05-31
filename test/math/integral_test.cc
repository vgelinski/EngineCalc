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
        return (y * y * z / 2 - x * y) / 2;
    }

protected:

    const double START_X = -2;
    const double END_X = 7;

    const double START_Y = 3.14;
    const double END_Y = -18.4;

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
        START_X, END_X, "x", 0.0001);
    const auto &integralX = *integralX_ptr;

    auto integralY_ptr = ((x + y * z) / (c5 - c3))->integrate(
        START_Y, END_Y, "y", 0.0001);
    const auto &integralY = *integralY_ptr;

    auto integralZ_ptr = ((x + y * z) / (c5 - c3))->integrate(
        START_X, START_X, "z", 0.0001);
    const auto &integralZ = *integralZ_ptr;

    map<string, double> params;
    params["x"] = 1.0;
    params["y"] = 2.0;
    params["z"] = 9.0;
    params["unused"] = -1.0;

    ASSERT_EQ(integralX(params), totalValByX(1.0, 2.0, 9.0));

    params["x"] = -20.0;
    params["y"] = 3.14;
    params["z"] = 0.002;

    ASSERT_EQ(integralY(params), totalValByY(-20.0, 3.14, 0.002));

    ASSERT_EQ(integralZ(params), 0);

    ASSERT_EQ(integralX.variables(), fvariables_t({"y", "z"}));
    ASSERT_EQ(integralY.variables(), fvariables_t({"x", "z"}));
    ASSERT_EQ(integralZ.variables(), fvariables_t({"x", "y"}));
}
