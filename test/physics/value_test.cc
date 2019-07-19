#include "gtest/gtest.h"

#include "../../src/physics/value.h"
#include "../../src/util/exceptions/illegal_argument_exception.h"

using namespace std;
using namespace engc::physics;
using namespace engc::util;

#define SU SimpleUnit
#define CU CompoundUnit

TEST (ValueTest, conversion) {
    auto km = make_shared<CU>(SU::KiloMeters);
    auto h = make_shared<CU>(SU::Hours);
    auto kmPh = km / h;

    auto m = make_shared<CU>(SU::Meters);
    auto s = make_shared<CU>(SU::Seconds);
    auto min = make_shared<CU>(SU::Minutes);
    auto mPmin = m / min;
    auto mPs = m / s;

    auto kg = make_shared<CU>(SU::Kilograms);
    auto j = kg * m / (s * s);
    auto kj = j->withName("KJ", 1000);

    auto speedMpmin = make_shared<Value>(100 * 60, mPmin);
    auto speedKmph = speedMpmin->convertTo(kmPh);
    auto speedSi = speedKmph->convertToSi();

    auto energyJ = make_shared<Value>(234, j);
    auto energyKJ = energyJ->convertTo(kj);
    auto energySi = energyKJ->convertToSi();

    ASSERT_DOUBLE_EQ(speedKmph->value, 360);
    ASSERT_DOUBLE_EQ(speedSi->value, 100);
    ASSERT_DOUBLE_EQ(energyKJ->value, 0.234);
    ASSERT_DOUBLE_EQ(energySi->value, 234);
}

TEST (ValueTest, impossibleConversion) {
    auto km = make_shared<CU>(SU::KiloMeters);
    auto m = make_shared<CU>(SU::Meters);
    auto h = make_shared<CU>(SU::Hours);
    auto kmPh = km / h;
    auto m2 = m * m;
    auto kmm = km * m;

    auto kg = make_shared<CU>(SU::Kilograms);
    auto min = make_shared<CU>(SU::Minutes);
    auto kgPmin = kg / min;

    auto speed = make_shared<Value>(100, kmPh);
    auto area = make_shared<Value>(20, m2);
    ASSERT_THROW(speed->convertTo(kgPmin), IllegalArgumentException);
    ASSERT_NO_THROW(area->convertTo(kmm));
}

