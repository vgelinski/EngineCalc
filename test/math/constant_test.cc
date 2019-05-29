#include "gtest/gtest.h"

#include "../../src/math/constant.h"

using namespace std;
using namespace engc::math;

TEST (ConstantTest, emptyParameters) {
    const Constant c(0.8);
    map<string, double> params;
    ASSERT_EQ(c.value(params), 0.8);
}
