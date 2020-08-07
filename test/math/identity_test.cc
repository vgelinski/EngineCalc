#include "gtest/gtest.h"

#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

TEST (IdentityTest, valueTest) {
    const Identity x("x");
    const Identity y("y");
    fparams_t params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    ASSERT_EQ(x(params), 2);
    ASSERT_EQ(y(params), 3);

    ASSERT_EQ(x.variables(), fvariables_t({"x"}));
    ASSERT_EQ(y.variables(), fvariables_t({"y"}));

    ASSERT_EQ(x.toString().c_str(), "x");
    ASSERT_EQ(y.toString().c_str(), "y");
}
