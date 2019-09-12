#include "gtest/gtest.h"

#include <cmath>

#include "../../src/math/constant.h"
#include "../../src/math/custom_function.h"
#include "../../src/math/function.h"
#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

class DifferentialTest : public ::testing::Test {

protected:

#if defined FULL_TEST
    const double ERR_BOUND = 0.00001;
#else
    const double ERR_BOUND = 0.00001;
#endif
};


TEST_F (DifferentialTest, deriving) {
    auto c2 = make_shared<Constant>(2);
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto x2 = (x * x) / c2 + y;
    auto scopeGuardDx = x2->derive("x", ERR_BOUND);
    auto& dx = *scopeGuardDx;

    fparams_t params;
    params["unused"] = -1.0;


    params["x"] = 1.0;
    params["y"] = 2.0;
    ASSERT_NEAR(dx(params), x->operator()(params), ERR_BOUND);

    params["x"] = 20.0;
    params["y"] = -2.0;
    ASSERT_NEAR(dx(params), x->operator()(params), ERR_BOUND);

    params["x"] = 12.076;
    params["y"] = 6.0;
    ASSERT_NEAR(dx(params), x->operator()(params), ERR_BOUND);


    ASSERT_EQ(dx.variables(), fvariables_t({"x", "y"}));
}

TEST_F (DifferentialTest, deriving2) {
    auto c2 = make_shared<Constant>(2);
    auto x = make_shared<Identity>("x");
    auto x3 = (x * x * x);
    auto scopeGuardDx = x3->derive("x", ERR_BOUND);
    auto scopeGuardDx2 = scopeGuardDx->derive("x", ERR_BOUND);
    auto& dx = *scopeGuardDx2;

    fparams_t params;
    params["unused"] = -1.0;



    for (fret_t i = 1; i < 20; i+= 0.01) {
        params["x"] = i;
        ASSERT_NEAR(dx(params), 6 * i, ERR_BOUND) << "i = " << i;
    }


    ASSERT_EQ(dx.variables(), fvariables_t({"x"}));
}

TEST_F (DifferentialTest, trigonometry) {
    auto sinAlpha = make_shared<CustomFunction>([](const fparams_t& params){
        return sin(params.at("alpha"));
        },  fvariables_t({"alpha"}));
    auto scopeGuard = sinAlpha->derive("alpha", ERR_BOUND);
    auto& cosAlpha = *scopeGuard;

    fparams_t params;
    params["unused"] = -1.0;

    for (fret_t i = 0; i < 6.28; i+= 0.001) {
        params["alpha"] = i;
        ASSERT_NEAR(cosAlpha(params), cos(i), ERR_BOUND) << "i = " << i;
    }
}
