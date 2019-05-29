#include "gtest/gtest.h"

#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

TEST (IdentityTest, valueTest) {
    const Identity x("x");
    const Identity y("y");
    map<string, double> params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    ASSERT_EQ(x.value(params), 2);
    ASSERT_EQ(y.value(params), 3);
}
