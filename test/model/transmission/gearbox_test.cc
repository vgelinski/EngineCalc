#include "gtest/gtest.h"

#include "../../../src/model/transmission/common_gearboxes.h"

using namespace std;
using namespace engc::model;

TEST (GearboxTest, common) {
    auto gearbox05 = CommonGearboxes::VAZ::VAZ_2105();
    auto gearbox01 = CommonGearboxes::VAZ::VAZ_2101();

    ASSERT_EQ(gearbox05->gearCount(), 5);
    ASSERT_EQ(gearbox01->gearCount(), 4);
}
