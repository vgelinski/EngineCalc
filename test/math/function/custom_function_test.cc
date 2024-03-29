#include "gtest/gtest.h"

#include "../../../src/math/function/custom_function.h"

#include <cmath>

using namespace std;
using namespace engc::math;

TEST (CustomFunctionTest, valueTest) {
    const CustomFunction sinx([](const fparams_t& params){ return sin(params.at("x")); }, fvariables_t({"x"}), "sin(x)");
    const CustomFunction cosy([](const fparams_t& params){ return cos(params.at("y")); }, fvariables_t({"y"}));
    fparams_t params;
    params["x"] = 2.0;
    params["y"] = 3.0;
    ASSERT_DOUBLE_EQ(sinx(params), sin(2));
    ASSERT_DOUBLE_EQ(cosy(params), cos(3));

    ASSERT_EQ(sinx.variables(), fvariables_t({"x"}));
    ASSERT_EQ(cosy.variables(), fvariables_t({"y"}));

    ASSERT_STREQ(sinx.toString().c_str(), "sin(x)");
    ASSERT_STREQ(cosy.toString().c_str(), "unknown_custom_function");
}
