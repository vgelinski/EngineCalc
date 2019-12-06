#include "gtest/gtest.h"

#include "../../src/math/constant.h"
#include "../../src/math/function.h"
#include "../../src/math/identity.h"
#include "../../src/math/implicit_function.h"

using namespace std;
using namespace engc::math;

class ImplicitFunctionTest : public ::testing::Test {
protected:

    const double ERR_BOUND = 0.0000001;

    fret_t funcVal(fret_t x) {
        return x * x - 3 * x + 8;
    };
};

TEST_F (ImplicitFunctionTest, valueTest) {
    auto c8 = make_shared<Constant>(8);
    auto c3 = make_shared<Constant>(3);
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");

    // y = x^2 - 3x + 8 <=> x^2 - 3x + 8 - y = 0

    auto F = x * x - c3 * x + c8 - y;
    auto impl = make_shared<ImplicitFunction>(F, "y");

    fparams_t params;
    params["x"] = 1.0;
    params["unused"] = -1.0;
    ASSERT_NEAR(funcVal(1), (*impl)(params), ERR_BOUND);

    params["x"] = -20.0;
    ASSERT_NEAR(funcVal(-20), (*impl)(params), ERR_BOUND);
}
