#include "gtest/gtest.h"

#include "../../../src/util/plot/data_calculator_2d.h"

#include "../../../src/math/constant.h"
#include "../../../src/math/identity.h"
#include "../../../src/physics/common_units.h"

using namespace std;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::util;

#define SU SimpleUnit
#define CU CompoundUnit

TEST (DataCalculator2DTest, calculate) {
    auto acc = 0.5; // m/s^2
    auto speedF = make_shared<Constant>(acc) * make_shared<Identity>("t");//m/s

    auto mass = 0.1; //kg
    auto massF = make_shared<Identity>("m");

    auto energyF = massF * speedF * speedF / make_shared<Constant>(2);

    auto start = make_shared<Value>(0, CommonUnits::Time::min);
    auto end = make_shared<Value>(2, CommonUnits::Time::min);
    auto step = make_shared<Value>(1, CommonUnits::Time::min);

    vector<line_t> lines = {
        pair(speedF, CommonUnits::Speed::KmPh),
        pair(massF, CommonUnits::Mass::g),
        pair(energyF, CommonUnits::Energy::J)
    };
    fparams_t p;
    p["m"] = mass;
    auto calc = make_shared<DataCalculator2D>(lines, start, end, step, p, "t");

    auto data = calc->calculateData();
    ASSERT_EQ(data.size(), 3);
    auto minutes = 0;
    for (auto row : data) {
        auto seconds = minutes * 60;
        auto speedMps = acc * seconds;
        auto speedKmph = speedMps * 3.6;
        auto energyJ = mass * speedMps * speedMps / 2;
        ASSERT_EQ(row.size(), 4);
        ASSERT_DOUBLE_EQ(row[0]->value, minutes);
        ASSERT_DOUBLE_EQ(row[1]->value, speedKmph) << "minutes: " <<  minutes;
        ASSERT_DOUBLE_EQ(row[2]->value, 100.0);
        ASSERT_DOUBLE_EQ(row[3]->value, energyJ) << "munites: " << minutes;
        minutes++;
    }
}
