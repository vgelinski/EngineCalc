#include "gtest/gtest.h"

#include "../../src/math/constant.h"

using namespace std;
using namespace engc::math;

TEST (ConstantTest, emptyParameters) {
    const Constant c(0.8);
    fparams_t params;
    ASSERT_EQ(c(params), 0.8);
    ASSERT_EQ(c.variables(), fvariables_t({}));
}
