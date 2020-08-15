#include "gtest/gtest.h"

#include "../../src/physics/common_units.h"
#include "../../src/physics/value.h"
#include "../../src/util/exceptions/illegal_argument_exception.h"

using namespace std;
using namespace engc::physics;
using namespace engc::util;

#define SU SimpleUnit
#define CU CompoundUnit

TEST (ValueTest, conversion) {

    auto mPmin = CommonUnits::Get()->Length->m / CommonUnits::Get()->Time->min;

    auto speedMpmin = make_shared<Value>(100 * 60, mPmin);
    auto speedKmph = speedMpmin->convertTo(CommonUnits::Get()->Speed->KmPh);
    auto speedSi = speedKmph->convertToSi();

    auto energyJ = make_shared<Value>(234, CommonUnits::Get()->Energy->J);
    auto energyKJ = energyJ->convertTo(CommonUnits::Get()->Energy->KJ);
    auto energySi = energyKJ->convertToSi();

    ASSERT_DOUBLE_EQ(speedKmph->value, 360);
    ASSERT_DOUBLE_EQ(speedSi->value, 100);
    ASSERT_DOUBLE_EQ(energyKJ->value, 0.234);
    ASSERT_DOUBLE_EQ(energySi->value, 234);
}

TEST (ValueTest, impossibleConversion) {
    auto kmm = CommonUnits::Get()->Length->Km * CommonUnits::Get()->Length->m;

    auto kgPmin = CommonUnits::Get()->Mass->Kg / CommonUnits::Get()->Time->min;

    auto speed = make_shared<Value>(100, CommonUnits::Get()->Speed->KmPh);
    auto area = make_shared<Value>(20, CommonUnits::Get()->Area->m2);
    ASSERT_THROW(speed->convertTo(kgPmin), IllegalArgumentException);
    ASSERT_NO_THROW(area->convertTo(kmm));
}

