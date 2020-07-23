#include "gtest/gtest.h"

#include "../../../src/model/transmission/common_differentials.h"
#include "../../../src/model/transmission/common_gearboxes.h"
#include "../../../src/model/transmission/transmission.h"
#include "../../../src/physics/common_units.h"

#include <cmath>

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;



TEST (TransmissionTest, speedTest) {
    auto tyre = make_shared<Tyre>(185, 80, 13);
    auto transmission = make_shared<Transmission>(
            tyre,
            tyre,
            CommonDifferentials::VAZ::VAZ_2103(),
            CommonGearboxes::VAZ::VAZ_2105()
    );

    transmission->gearbox->shiftToGear(5);

    auto v_ptr = transmission->speedF();
    auto& v = * v_ptr;

    fparams_t params;
    params["rotationSpeed"] = make_shared<Value>(4500, CommonUnits::Speed::rpm)->convertToSi()->value;

    ASSERT_DOUBLE_EQ(v(params), ((185.0L/1000.0L) * 0.8L + 13.0L * 0.0254L) * 2 * M_PI * (4500 / (0.801L * 4.1L * 60))); // m/s
}