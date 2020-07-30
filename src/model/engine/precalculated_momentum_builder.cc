#include "precalculated_momentum_builder.h"

#include "../../math/identity.h"
#include "../../math/polynomial/lagrange_polynom_builder.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;

#define PMB PrecalculatedMomentumBuilder
#define VAL shared_ptr<physics::Value>

PMB::PMB() {}
PMB::~PMB() {}

void PMB::setMaxMomentum(VAL rpm, VAL momentum) {
    maxMomentumRpm = rpm;
    maxMomentum = momentum;
}

void PMB::setMaxPower(VAL rpm, VAL momentum) {
    maxPowerRpm = rpm;
    maxPower = momentum;
}

shared_ptr<Function> PMB::calculateMomentum() const {
    return make_shared<LagrangePolynomBuilder>("rotationSpeed")
            ->addPoint(0, 0)
            ->addPoint(maxMomentumRpm->convertToSi()->value, maxMomentum->convertToSi()->value)
            ->addPoint(maxPowerRpm->convertToSi()->value, maxPowerRpm->convertToSi()->value / maxPowerRpm->convertToSi()->value)
            ->build();
}

shared_ptr<Function> PMB::calculatePower() const {
    return calculateMomentum() * make_shared<Identity>("rotationSpeed");
}