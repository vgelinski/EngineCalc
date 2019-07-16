#include "gtest/gtest.h"

#include <unordered_map>
#include <utility>

#include "../../src/physics/units.h"

using namespace std;
using namespace engc::physics;

#define SUT SimpleUnitType
#define SU SimpleUnit
#define CU CompoundUnit

TEST (UnitsTest, toStringTest) {
    ASSERT_EQ(SU::Kelvins->toString(), "K°");
    ASSERT_EQ(SU::MilliMeters->toString(), "mm");
    ASSERT_EQ(SU::Minutes->toString(), "min");
    ASSERT_EQ(SU::Radians->toString(), "rad");
}

TEST (UnitsTest, testUniqueness) {
    struct hasher {
        size_t operator()(const pair<SUT, long double> &p) const {
            return hash<SUT>()(p.first) ^ (hash<long double>()(p.second) << 1);
        }
    };
    unordered_multimap<pair<SUT, long double>, SU const *, hasher> mults;
    unordered_multimap<string, SU const *> names;

    ASSERT_GT(SU::values().size(), 0);

    for (auto val : SU::values()) {
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

    for (auto val : SU::values()) {
        ASSERT_NE(val->siUnit(), nullptr);
    }
}

TEST (UnitsTest, testCompoundUnit) {
    shared_ptr<CU> km = make_shared<CU>(SU::KiloMeters);
    shared_ptr<CU> h = make_shared<CU>(SU::Hours);
    shared_ptr<CU> kmPh = km / h;

    shared_ptr<CU> m = make_shared<CU>(SU::Meters);
    shared_ptr<CU> m2 = m * m;

    shared_ptr<CU> s = make_shared<CU>(SU::Seconds);
    shared_ptr<CU> kg = make_shared<CU>(SU::Kilograms);
    shared_ptr<CU> f = kg * m / (s * s);

    ASSERT_EQ(kmPh->toString(), "km/h");
    ASSERT_EQ(m2->toString(), "m^2");
    ASSERT_EQ(f->toString(), "kg*m/s^2");
}

