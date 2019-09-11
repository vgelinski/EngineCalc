#include "gtest/gtest.h"

#include "../../src/math/constant.h"
#include "../../src/math/function.h"
#include "../../src/math/identity.h"

using namespace std;
using namespace engc::math;

class DifferentialTest : public ::testing::Test {

protected:

#if defined FULL_TEST
    const double ERR_BOUND = 0.00001;
#else
    const double ERR_BOUND = 0.01;
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
    auto x3 = (x * x * x) ;
    auto scopeGuardDx = x3->derive("x", ERR_BOUND * ERR_BOUND);
    auto scopeGuardDx2 = scopeGuardDx->derive("x", ERR_BOUND * ERR_BOUND);
    auto& dx = *scopeGuardDx2;

    fparams_t params;
    params["unused"] = -1.0;


    params["x"] = 1.0;
    ASSERT_NEAR(dx(params), 6, ERR_BOUND * ERR_BOUND);

    params["x"] = 20.0;
    ASSERT_NEAR(dx(params), 120, ERR_BOUND * ERR_BOUND);

    params["x"] = 12.076;
    ASSERT_NEAR(dx(params), 6 * 12.076, ERR_BOUND * ERR_BOUND);


    ASSERT_EQ(dx.variables(), fvariables_t({"x"}));
}
