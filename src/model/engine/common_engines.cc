#include "common_engines.h"

#include "../../../src/model/engine/precalculated_momentum_builder.h"
#include "../../../src/physics/common_units.h"

using namespace std;
using namespace engc::model;
using namespace engc::physics;

#define CE CommonEngines
#define PISTON_MASS make_shared<Value>(315, CommonUnits::Get()->Mass->g)
#define SMALL_CYLINDER_BORE make_shared<Value>(76, CommonUnits::Get()->Length->mm)
#define BIG_CYLINDER_BORE make_shared<Value>(79, CommonUnits::Get()->Length->mm)
#define ROD_LENGTH make_shared<Value>(136, CommonUnits::Get()->Length->mm)
#define SMALL_STROKE make_shared<Value>(66, CommonUnits::Get()->Length->mm)
#define BIG_STROKE make_shared<Value>(80, CommonUnits::Get()->Length->mm)

shared_ptr<Engine> CE::VAZ::VAZ_2101() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(PISTON_MASS)
            ->setCylinderBore(SMALL_CYLINDER_BORE)
            ->setStrokeLength(SMALL_STROKE)
            ->setRodLength(ROD_LENGTH)
            ->setCombustionRatio(8.8);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Get()->Speed->rpm), make_shared<Value>(87.3, CommonUnits::Get()->Torque->Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Get()->Speed->rpm), make_shared<Value>(47.2, CommonUnits::Get()->Power->KW));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_21011() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(PISTON_MASS)
            ->setCylinderBore(BIG_CYLINDER_BORE)
            ->setStrokeLength(SMALL_STROKE)
            ->setRodLength(ROD_LENGTH)
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Get()->Speed->rpm), make_shared<Value>(94.1, CommonUnits::Get()->Torque->Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Get()->Speed->rpm), make_shared<Value>(50.88, CommonUnits::Get()->Power->KW));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_2103() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(PISTON_MASS)
            ->setCylinderBore(SMALL_CYLINDER_BORE)
            ->setStrokeLength(BIG_STROKE)
            ->setRodLength(ROD_LENGTH)
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3400, CommonUnits::Get()->Speed->rpm), make_shared<Value>(110.9, CommonUnits::Get()->Torque->Nm));
    pmb->setMaxPower(make_shared<Value>(5600, CommonUnits::Get()->Speed->rpm), make_shared<Value>(53, CommonUnits::Get()->Power->KW));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_2105() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(PISTON_MASS)
            ->setCylinderBore(BIG_CYLINDER_BORE)
            ->setStrokeLength(SMALL_STROKE)
            ->setRodLength(ROD_LENGTH)
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3500, CommonUnits::Get()->Speed->rpm), make_shared<Value>(94, CommonUnits::Get()->Torque->Nm));
    pmb->setMaxPower(make_shared<Value>(5500, CommonUnits::Get()->Speed->rpm), make_shared<Value>(46.8, CommonUnits::Get()->Power->KW));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}

shared_ptr<Engine> CE::VAZ::VAZ_2106() {
    auto engine = make_shared<Engine>()
            ->setPistonMass(PISTON_MASS)
            ->setCylinderBore(BIG_CYLINDER_BORE)
            ->setStrokeLength(BIG_STROKE)
            ->setRodLength(ROD_LENGTH)
            ->setCombustionRatio(8.5);
    auto pmb = make_shared<PrecalculatedMomentumBuilder>();
    pmb->setMaxMomentum(make_shared<Value>(3500, CommonUnits::Get()->Speed->rpm), make_shared<Value>(120, CommonUnits::Get()->Torque->Nm));
    pmb->setMaxPower(make_shared<Value>(5430, CommonUnits::Get()->Speed->rpm), make_shared<Value>(54.8, CommonUnits::Get()->Power->KW));
    engine->precalculatedMomentumF = pmb->calculateMomentum();
    engine->precalculatedPowerF = pmb->calculatePower();
    return engine;
}
