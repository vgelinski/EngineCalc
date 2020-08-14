#include "precalculated_momentum_builder.h"

#include "../../math/function/identity.h"
#include "../../math/function/polynomial/lagrange_polynom_builder.h"

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
    auto Tx = maxMomentumRpm->convertToSi()->value;
    auto Ty = maxMomentum->convertToSi()->value;
    auto Px = maxPowerRpm->convertToSi()->value;
    auto Py = maxPower->convertToSi()->value / maxPowerRpm->convertToSi()->value;
    auto b = (Py - Ty) / (Px - Tx/2 - Px*Px/(2*Tx));
    auto c = Ty - b*Tx/2;
    auto a = -b/(2*Tx);
    auto ret = make_shared<Polynomial>();
    auto x = "rotationSpeed";
    ret->add(make_shared<Monomial>(x, 2, a));
    ret->add(make_shared<Monomial>(x, 1, b));
    ret->add(make_shared<Monomial>(c));
    return ret;
//    return make_shared<LagrangePolynomBuilder>("rotationSpeed")
//            ->addPoint(0, 0)
//            ->addPoint(maxMomentumRpm->convertToSi()->value, maxMomentum->convertToSi()->value)
//            ->addPoint(maxPowerRpm->convertToSi()->value, maxPower->convertToSi()->value / maxPowerRpm->convertToSi()->value)
//            ->build();
}

shared_ptr<Function> PMB::calculatePower() const {
    return calculateMomentum() * make_shared<Identity>("rotationSpeed");
}