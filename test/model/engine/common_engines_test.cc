#include "gtest/gtest.h"

#include "../../../../src/model/engine/common_engines.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;

TEST (CommonEnginesTest, parameters) {
    auto vaz2101 = CommonEngines::VAZ::VAZ_2101();
    auto params = vaz2101->getParams();

    ASSERT_DOUBLE_EQ(params["n"], 4.0l);
    ASSERT_DOUBLE_EQ(params["pistonMass"], 0.315l);
    ASSERT_DOUBLE_EQ(params["cylinderBore"], 0.076l);
    ASSERT_DOUBLE_EQ(params["strokeLength"], 0.066);
    ASSERT_DOUBLE_EQ(params["rodLength"], 0.136l);
    ASSERT_DOUBLE_EQ(params["combustionChamberVolume"], 0.000038385429007400208);
}
