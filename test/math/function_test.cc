#include "gtest/gtest.h"

#include "../../src/math/constant.h"
#include "../../src/math/function.h"
#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

class FunctionTest : public ::testing::Test {
protected:
    double totalAggVal(double x, double y, double z) {
        return (x + y * z) / (5 - 3);
    };
};

TEST_F (FunctionTest, aggregation) {
    auto c5 = make_shared<Constant>(5);
    auto c3 = make_shared<Constant>(3);
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");

    auto total = (x + y * z) / (c5 - c3);


    map<string, double> params;
    params["x"] = 1.0;
    params["y"] = 2.0;
    params["z"] = 9.0;
    params["unused"] = -1.0;

    ASSERT_EQ(total->value(params), totalAggVal(1.0, 2.0, 9.0));

    params["x"] = -20.0;
    params["y"] = 3.14;
    params["z"] = 0.002;
    
    ASSERT_EQ(total->value(params), totalAggVal(-20.0, 3.14, 0.002));
}

