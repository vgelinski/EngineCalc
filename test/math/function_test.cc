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

    double totalCompVal(double y) {
        return (y - 2) * (y - 2) * (y - 2);
    };
};

TEST_F (FunctionTest, aggregation) {
    auto c5 = make_shared<Constant>(5);
    auto c3 = make_shared<Constant>(3);
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");


    auto total_ptr = (x + y * z) / (c5 - c3);
    const auto &total = *total_ptr;

    map<string, double> params;
    params["x"] = 1.0;
    params["y"] = 2.0;
    params["z"] = 9.0;
    params["unused"] = -1.0;

    ASSERT_EQ(total(params), totalAggVal(1.0, 2.0, 9.0));

    params["x"] = -20.0;
    params["y"] = 3.14;
    params["z"] = 0.002;
    
    ASSERT_EQ(total(params), totalAggVal(-20.0, 3.14, 0.002));
}

TEST_F(FunctionTest, compositon) {

    auto x = make_shared<Identity>("x");
    auto x_3 = x * x * x;
    auto y = make_shared<Identity>("y");
    auto c2 = make_shared<Constant>(2);
    auto y2 = y - c2;

    map<string, double> params;
    params["x"] = 5.0;
    params["y"] = 8.0;
    params["unused"] = -1.0;

    auto comp_ptr = x_3->compose(y2, "x");
    const auto &comp = *comp_ptr; 

    ASSERT_EQ(comp(params), totalCompVal(8.0));
    params["x"] = -2;
    ASSERT_EQ(comp(params), totalCompVal(8.0));
    params["y"] = -3.14;
    ASSERT_EQ(comp(params), totalCompVal(-3.14));

}

TEST_F(FunctionTest, variables) {
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");

    auto xy = x + y;
    auto zy = xy->compose(z, "x");
    auto xyOfX = xy->compose(x, "x");
    auto xyOfY = xy->compose(x, "y");

    ASSERT_EQ(xy->variables(), fvariables_t({"y", "x"}));
    ASSERT_EQ(zy->variables(), fvariables_t({"y", "z"}));
    ASSERT_EQ(xyOfX->variables(), fvariables_t({"y", "x"}));
    ASSERT_EQ(xyOfY->variables(), fvariables_t({"x"}));
}
