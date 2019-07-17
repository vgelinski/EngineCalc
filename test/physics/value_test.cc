#include "gtest/gtest.h"

#include "../../src/physics/value.h"
#include "../../src/util/exceptions/illegal_argument_exception.h"

using namespace std;
using namespace engc::physics;
using namespace engc::util;

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

TEST (ValueTest, impossibleConversion) {
    shared_ptr<CU> km = make_shared<CU>(SU::KiloMeters);
    shared_ptr<CU> m = make_shared<CU>(SU::Meters);
    shared_ptr<CU> h = make_shared<CU>(SU::Hours);
    shared_ptr<CU> kmPh = km / h;
    shared_ptr<CU> m2 = m * m;
    shared_ptr<CU> kmm = km * m;

    shared_ptr<CU> kg = make_shared<CU>(SU::Kilograms);
    shared_ptr<CU> min = make_shared<CU>(SU::Minutes);
    shared_ptr<CU> kgPmin = kg / min;

    auto speed = make_shared<Value>(100, kmPh);
    auto area = make_shared<Value>(20, m2);
    ASSERT_THROW(speed->convertTo(kgPmin), IllegalArgumentException);
    ASSERT_NO_THROW(area->convertTo(kmm));
}

