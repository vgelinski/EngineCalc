#include "gtest/gtest.h"

#include "../../../src/model/transmission/tyre.h"
#include "../../../src/physics/common_units.h"

#include <cmath>

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;

TEST (TyreTest, speed) {
    auto tyre1F = make_shared<Tyre>(185, 80, 13)->speedF();
    auto tyre2F = make_shared<Tyre>(165, 70, 13)->speedF();
    auto tyre3F = make_shared<Tyre>(225, 50, 17)->speedF();

    const auto& v1 = * tyre1F;
    const auto& v2 = * tyre2F;
    const auto& v3 = * tyre3F;

    fparams_t params;
    params["rotationSpeed"] = make_shared<Value>(1200, CommonUnits::Speed::rpm)->convertToSi()->value;
    params["unused"] = 3.0;

    ASSERT_DOUBLE_EQ(v1(params), ((185.0L/1000.0L) * 0.8L + 13.0L * 0.0254L / 2) * 2 * M_PI * 20); // m/s
    ASSERT_DOUBLE_EQ(v2(params), ((165.0L/1000.0L) * 0.7L + 13.0L * 0.0254L / 2) * 2 * M_PI * 20); // m/s
    ASSERT_DOUBLE_EQ(v3(params), ((225.0L/1000.0L) * 0.5L + 17.0L * 0.0254L / 2) * 2 * M_PI * 20); // m/s

    params["rotationSpeed"] = make_shared<Value>(600, CommonUnits::Speed::rpm)->convertToSi()->value;


    ASSERT_DOUBLE_EQ(v1(params), ((185.0L/1000.0L) * 0.8L + 13.0L * 0.0254L / 2) * 2 * M_PI * 10); // m/s
    ASSERT_DOUBLE_EQ(v2(params), ((165.0L/1000.0L) * 0.7L + 13.0L * 0.0254L / 2) * 2 * M_PI * 10); // m/s
    ASSERT_DOUBLE_EQ(v3(params), ((225.0L/1000.0L) * 0.5L + 17.0L * 0.0254L / 2) * 2 * M_PI * 10); // m/s
}

TEST (TyreTest, rotation) {
    auto tyre1F = make_shared<Tyre>(185, 80, 13)->rotationF();
    auto tyre2F = make_shared<Tyre>(165, 70, 13)->rotationF();
    auto tyre3F = make_shared<Tyre>(225, 50, 17)->rotationF();

    const auto& v1 = * tyre1F;
    const auto& v2 = * tyre2F;
    const auto& v3 = * tyre3F;

    fparams_t params;
    params["speed"] = make_shared<Value>(80, CommonUnits::Speed::KmPh)->convertToSi()->value;

    ASSERT_DOUBLE_EQ(v1(params), 80 / (3.6L * ((185.0L/1000.0L) * 0.8L + 13.0L * 0.0254L / 2))); // rad/s
    ASSERT_DOUBLE_EQ(v2(params), 80 / (3.6L * ((165.0L/1000.0L) * 0.7L + 13.0L * 0.0254L / 2))); // rad/s
    ASSERT_DOUBLE_EQ(v3(params), 80 / (3.6L * ((225.0L/1000.0L) * 0.5L + 17.0L * 0.0254L / 2))); // rad/s

    params["speed"] = make_shared<Value>(120, CommonUnits::Speed::KmPh)->convertToSi()->value;


    ASSERT_DOUBLE_EQ(v1(params), 120 / (3.6L * ((185.0L/1000.0L) * 0.8L + 13.0L * 0.0254L / 2))); // rad/s
    ASSERT_DOUBLE_EQ(v2(params), 120 / (3.6L * ((165.0L/1000.0L) * 0.7L + 13.0L * 0.0254L / 2))); // rad/s
    ASSERT_DOUBLE_EQ(v3(params), 120 / (3.6L * ((225.0L/1000.0L) * 0.5L + 17.0L * 0.0254L / 2))); // rad/s
}
