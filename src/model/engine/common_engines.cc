#include "common_engines.h"

#include "../../../src/model/engine/precalculated_momentum_builder.h"
#include "../../../src/physics/common_units.h"

using namespace std;
using namespace engc::model;
using namespace engc::physics;

#define CE CommonEngines

shared_ptr<Engine> CE::VAZ::VAZ_2101() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(make_shared<Value>(315, CommonUnits::Mass::g))
            ->setCylinderBore(make_shared<Value>(76, CommonUnits::Length::mm))
            ->setStrokeLength(make_shared<Value>(66, CommonUnits::Length::mm))
            ->setRodLength(make_shared<Value>(136, CommonUnits::Length::mm))
            ->setCombustionRatio(8.8);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Speed::rpm), make_shared<Value>(89, CommonUnits::Torque::Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Speed::rpm), make_shared<Value>(64, CommonUnits::Power::HP));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_21011() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(make_shared<Value>(315, CommonUnits::Mass::g))
            ->setCylinderBore(make_shared<Value>(79, CommonUnits::Length::mm))
            ->setStrokeLength(make_shared<Value>(66, CommonUnits::Length::mm))
            ->setRodLength(make_shared<Value>(136, CommonUnits::Length::mm))
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Speed::rpm), make_shared<Value>(96, CommonUnits::Torque::Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Speed::rpm), make_shared<Value>(69, CommonUnits::Power::HP));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_2103() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(make_shared<Value>(315, CommonUnits::Mass::g))
            ->setCylinderBore(make_shared<Value>(76, CommonUnits::Length::mm))
            ->setStrokeLength(make_shared<Value>(80, CommonUnits::Length::mm))
            ->setRodLength(make_shared<Value>(136, CommonUnits::Length::mm))
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Speed::rpm), make_shared<Value>(104, CommonUnits::Torque::Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Speed::rpm), make_shared<Value>(75, CommonUnits::Power::HP));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_2105() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(make_shared<Value>(315, CommonUnits::Mass::g))
            ->setCylinderBore(make_shared<Value>(79, CommonUnits::Length::mm))
            ->setStrokeLength(make_shared<Value>(66, CommonUnits::Length::mm))
            ->setRodLength(make_shared<Value>(136, CommonUnits::Length::mm))
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Speed::rpm), make_shared<Value>(92, CommonUnits::Torque::Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Speed::rpm), make_shared<Value>(63, CommonUnits::Power::HP));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_2106() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(make_shared<Value>(315, CommonUnits::Mass::g))
            ->setCylinderBore(make_shared<Value>(79, CommonUnits::Length::mm))
            ->setStrokeLength(make_shared<Value>(80, CommonUnits::Length::mm))
            ->setRodLength(make_shared<Value>(136, CommonUnits::Length::mm))
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3000, CommonUnits::Speed::rpm), make_shared<Value>(116, CommonUnits::Torque::Nm));
    pmb->setMaxPower(make_shared<Value>(5400, CommonUnits::Speed::rpm), make_shared<Value>(75, CommonUnits::Power::HP));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}
