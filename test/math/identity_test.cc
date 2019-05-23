#include "gtest/gtest.h"

#include "../../src/math/identity.h"

using namespace std;

TEST (IdentityTest, valueTest) {
    const Identity x("x");
    map<string, double> params;
    params["x"] = 2.0;
    ASSERT_EQ(x.value(params), 2);
}
