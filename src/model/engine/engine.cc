#include "engine.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;

Engine::Engine(int pistonCount) : pistonCount(pistonCount) {}

Engine::~Engine() {}

fparams_t Engine::getParams() const {
    return {};
}

shared_ptr<Function> Engine::mechanicalLossF() const {
    return nullptr;
}

shared_ptr<Engine> Engine::setPistonMass(const std::shared_ptr <Value> &pistonMass) {
    return shared_from_this();
}

shared_ptr<Engine> Engine::setCylinderBore(const std::shared_ptr <Value> &cylinderBore) {
    return shared_from_this();
}

shared_ptr<Engine> Engine::setStrokeLength(const std::shared_ptr <Value> &strokeLength) {
    return shared_from_this();
}

shared_ptr<Engine> Engine::setRodLength(const std::shared_ptr <Value> &rodLength) {
    return shared_from_this();
}

shared_ptr<Engine> Engine::setRotatingSpeed(const std::shared_ptr <Value> &rotatingSpeed) {
    return shared_from_this();
}

shared_ptr<Engine> Engine::setCombustionChamberVolume(const std::shared_ptr <Value> &combustionChamberVolume) {
    return shared_from_this();
}

shared_ptr<Engine> Engine::setCombustionRatio(const long double &ratio) {
    return shared_from_this();
}
