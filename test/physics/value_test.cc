#include "gtest/gtest.h"

#include "../../src/physics/value.h"

using namespace std;
using namespace engc::physics;

#define SU SimpleUnit
#define CU CompoundUnit

TEST (ValueTest, conversion) {
    shared_ptr<CU> km = make_shared<CU>(SU::KiloMeters);
    shared_ptr<CU> h = make_shared<CU>(SU::Hours);
    shared_ptr<CU> kmPh = km / h;

    shared_ptr<CU> m = make_shared<CU>(SU::Meters);
    shared_ptr<CU> s = make_shared<CU>(SU::Seconds);
    shared_ptr<CU> min = make_shared<CU>(SU::Minutes);
    shared_ptr<CU> mPmin = m / min;
    shared_ptr<CU> mPs = m / s;

    auto speedMpmin = make_shared<Value>(100 * 60, mPmin);
    auto speedKmph = speedMpmin->convertTo(kmPh);
    auto speedSi = speedKmph->convertToSi();

    ASSERT_DOUBLE_EQ(speedKmph->value, 360);
    ASSERT_DOUBLE_EQ(speedSi->value, 100);

}
