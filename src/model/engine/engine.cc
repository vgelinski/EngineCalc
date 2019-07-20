#include "engine.h"

#include <cmath>

#include "../../physics/common_units.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;

Engine::Engine(int pistonCount) : pistonCount(pistonCount) {}

Engine::~Engine() {}

fparams_t Engine::getParams() const {
    fparams_t params;
    params["n"] = pistonCount;
    params["pistonMass"] = pistonMass->convertToSi()->value;
    params["cylinderBore"] = cylinderBore->convertToSi()->value;
    params["strokeLength"] = strokeLength->convertToSi()->value;
    params["rodLength"] = rodLength->convertToSi()->value;
    params["setCombustionChamberVolume"] = combustionChamberVolume->convertToSi()->value;
    return params;
}

shared_ptr<Function> Engine::mechanicalLossF() const {
    return nullptr;
}

shared_ptr<Engine> Engine::setPistonMass(const std::shared_ptr<Value> &pistonMass) {
    this->pistonMass = pistonMass;
    return shared_from_this();
}

shared_ptr<Engine> Engine::setCylinderBore(const std::shared_ptr<Value> &cylinderBore) {
    this->cylinderBore = cylinderBore;
    return shared_from_this();
}

shared_ptr<Engine> Engine::setStrokeLength(const std::shared_ptr<Value> &strokeLength) {
    this->strokeLength = strokeLength;
    return shared_from_this();
}

shared_ptr<Engine> Engine::setRodLength(const std::shared_ptr<Value> &rodLength) {
    this->rodLength = rodLength;
    return shared_from_this();
}

shared_ptr<Engine> Engine::setCombustionChamberVolume(const std::shared_ptr<Value> &combustionChamberVolume) {
    this->combustionChamberVolume = combustionChamberVolume;
    return shared_from_this();
}

shared_ptr<Engine> Engine::setCombustionRatio(const long double &ratio) {
    auto boreSi = cylinderBore->convertToSi()->value;
    auto displacementSi = strokeLength->convertToSi()->value * M_PI * boreSi * boreSi / 4;
    auto combChambVolSi = displacementSi / (ratio - 1.0L);
    combustionChamberVolume = make_shared<Value>(combChambVolSi, CommonUnits::Volume::m3);
    return shared_from_this();
}
