#include "gtest/gtest.h"

#include <cmath>

#include "../../src/math/constant.h"
#include "../../src/math/function.h"
#include "../../src/math/identity.h"
#include "../../src/math/implicit_function.h"

using namespace std;
using namespace engc::math;

class ImplicitFunctionTest : public ::testing::Test {
protected:

    const double ERR_BOUND = 0.0000001;

    fret_t val1(fret_t x) {
        return x * x - 3 * x + 8;
    };

    fret_t val2(fret_t x) {
        return 4 + sqrt(4 - (x - 3) * (x - 3));
    };

    shared_ptr<Function> f1() {

        auto c8 = make_shared<Constant>(8);
        auto c3 = make_shared<Constant>(3);
        auto x = make_shared<Identity>("x");
        auto y = make_shared<Identity>("y");

        // y = x^2 - 3x + 8 <=> x^2 - 3x + 8 - y = 0

        auto F = x * x - c3 * x + c8 - y;
        return make_shared<ImplicitFunction>(F, "y");
    }

    shared_ptr<Function> f2() {

        auto c4 = make_shared<Constant>(4);
        auto c3 = make_shared<Constant>(3);
        auto x = make_shared<Identity>("x");
        auto y = make_shared<Identity>("y");

        auto F = ((x - c3) * (x - c3)) + ((y - c4) * (y - c4)) - c4;
        return make_shared<ImplicitFunction>(F, "y", 4, 10); //actually it's [4,6], bit let's test it this way
    }
};

TEST_F (ImplicitFunctionTest, valueTest1) {
    auto impl = f1();

    fparams_t params;
    params["x"] = 1.0;
    params["unused"] = -1.0;
    ASSERT_NEAR(val1(1), (*impl)(params), ERR_BOUND);

    params["x"] = -20.0;
    ASSERT_NEAR(val1(-20), (*impl)(params), ERR_BOUND);

    ASSERT_STREQ(impl->toString().c_str(), "\\left{ = 0, solve for x\\right}");
}

TEST_F (ImplicitFunctionTest, valueTest2) {
    auto impl = f2();

    fparams_t params;
    params["x"] = 1.0;
    params["unused"] = -1.0;
    ASSERT_NEAR(val2(1), (*impl)(params), ERR_BOUND);

    params["x"] = 5;
    ASSERT_NEAR(val2(5), (*impl)(params), ERR_BOUND);

    params["x"] = 3;
    ASSERT_NEAR(val2(3), (*impl)(params), ERR_BOUND);
}
