#include "gtest/gtest.h"

#include "../../src/math/custom_function.h"

#include <cmath>

using namespace std;
using namespace engc::math;

TEST (CustomFunctionTest, valueTest) {
    const CustomFunction sinx([](const fparams_t& params){ return sin(params.at("x")); }, fvariables_t({"x"}));
    const CustomFunction cosy([](const fparams_t& params){ return cos(params.at("y")); }, fvariables_t({"y"}));
    fparams_t params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    ASSERT_DOUBLE_EQ(sinx(params), sin(2));
    ASSERT_DOUBLE_EQ(cosy(params), cos(3));

    ASSERT_EQ(sinx.variables(), fvariables_t({"x"}));
    ASSERT_EQ(cosy.variables(), fvariables_t({"y"}));
}
