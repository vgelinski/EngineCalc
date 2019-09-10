#include "common_engines.h"

#include "../../../src/physics/common_units.h"

using namespace std;
using namespace engc::model;
using namespace engc::physics;

#define CE CommonEngines

shared_ptr<Engine> CE::VAZ::VAZ_2101() {
    return make_shared<Engine>()
            ->setPistonMass(make_shared<Value>(315, CommonUnits::Mass::g))
            ->setCylinderBore(make_shared<Value>(72, CommonUnits::Length::mm))
            ->setStrokeLength(make_shared<Value>(66, CommonUnits::Length::mm))
            ->setRodLength(make_shared<Value>(136, CommonUnits::Length::mm))
            ->setCombustionRatio(8.8);
}
