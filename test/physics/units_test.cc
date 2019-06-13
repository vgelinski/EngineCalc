#include "gtest/gtest.h"

#include "../../src/physics/units.h"

using namespace std;
using namespace engc::physics;

#define SU SimpleUnit
#define MU MultipleUnit
#define CU CompoundUnit

TEST (UnitsTest, toStringTest) {
    ASSERT_EQ(SU::Meters->toString(), "m");
    ASSERT_EQ(SU::Kilograms->toString(), "kg");
    ASSERT_EQ(SU::Seconds->toString(), "s");
    ASSERT_EQ(SU::Kelvins->toString(), "K°");

    ASSERT_EQ(MU::Kelvins->toString(), "K°");
    ASSERT_EQ(MU::MilliMeters->toString(), "mm");
    ASSERT_EQ(MU::Minutes->toString(), "min");
    ASSERT_EQ(MU::Radians->toString(), "rad");
}

TEST (UnitsTest, testCompoundUnit) {
    shared_ptr<CU> km = make_shared<CU>(MU::KiloMeters);
    shared_ptr<CU> h = make_shared<CU>(MU::Hours);
    shared_ptr<CU> kmPh = km / h;

    shared_ptr<CU> m = make_shared<CU>(MU::Meters);
    shared_ptr<CU> m2 = m * m;

    shared_ptr<CU> s = make_shared<CU>(MU::Seconds);
    shared_ptr<CU> kg = make_shared<CU>(MU::Kilograms);
    shared_ptr<CU> f = kg * m / (s * s);

    ASSERT_EQ(kmPh->toString(), "km/h");
    ASSERT_EQ(m2->toString(), "m^2");
    ASSERT_EQ(f->toString(), "kg*m/s^2");
}

