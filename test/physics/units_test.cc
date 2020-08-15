#include "gtest/gtest.h"

#include <unordered_map>
#include <utility>

#include "../../src/physics/common_units.h"
#include "../../src/physics/units.h"

using namespace std;
using namespace engc::physics;

#define SUT SimpleUnitType
#define SU SimpleUnit
#define SUV SimpleUnitValues
#define CU CompoundUnit

TEST (UnitsTest, toStringTest) {
    ASSERT_EQ(SUV::Get()->Kelvins->toString(), "K°");
    ASSERT_EQ(SUV::Get()->MilliMeters->toString(), "mm");
    ASSERT_EQ(SUV::Get()->Minutes->toString(), "min");
    ASSERT_EQ(SUV::Get()->Radians->toString(), "rad");
}

TEST (UnitsTest, testUniqueness) {
    struct hasher {
        size_t operator()(const pair<SUT, long double>& p) const {
            return hash<SUT>()(p.first) ^ (hash<long double>()(p.second) << 1);
        }
    };
    unordered_multimap<pair<SUT, long double>, SU const *, hasher> mults;
    unordered_multimap<string, SU const *> names;

    ASSERT_GT(SUV::values().size(), 0);

    for (auto val : SUV::values()) {
        auto t = val->type;
        mults.insert(pair(pair(t, val->multiplier), val));
        names.insert(pair(val->toString(), val));
    }

    for (auto p : mults) {
        ASSERT_EQ(mults.count(p.first), 1) << (int) p.first.first <<
            "\t" << p.first.second << "\t" << p.second->toString() << endl;
    }

    for (auto p : names) {
        ASSERT_EQ(names.count(p.first), 1);
    }
}

TEST (UnitsTest, testSiUnit) {

    for (auto val : SUV::values()) {
        ASSERT_NE(val->siUnit(), nullptr);
    }
}

TEST (UnitsTest, testCompoundUnit) {
    ASSERT_EQ(CommonUnits::Get()->Speed->KmPh->toString(), "km/h");
    ASSERT_EQ(CommonUnits::Get()->Area->m2->toString(), "m^2");

    ASSERT_EQ(CommonUnits::Get()->Mass->Kg->toDebugString(), "kg");
    ASSERT_EQ(CommonUnits::Get()->Acceleration->mps2->toDebugString(), "m/s^2");

    ASSERT_EQ(CommonUnits::Get()->Force->N->toDebugString(), "kg*m/s^2");
    ASSERT_EQ(CommonUnits::Get()->Force->N->toString(), "N");
    ASSERT_EQ(CommonUnits::Get()->Force->KN->toDebugString(), "1000.000000*kg*m/s^2");
}

