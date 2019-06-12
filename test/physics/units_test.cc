#include "gtest/gtest.h"

#include "../../src/physics/units.h"

using namespace std;
using namespace engc::physics;

#define SU SimpleUnit

TEST (UnitsTest, toStringTest) {
    ASSERT_EQ(SU::Meters->toString(), "m");
    ASSERT_EQ(SU::Kilograms->toString(), "kg");
    ASSERT_EQ(SU::Seconds->toString(), "s");
    ASSERT_EQ(SU::Kelvins->toString(), "K°");
}
