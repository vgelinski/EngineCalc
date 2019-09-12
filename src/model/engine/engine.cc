#include "engine.h"

#include <cmath>

#include "../../math/constant.h"
#include "../../math/custom_function.h"
#include "../../math/identity.h"
#include "../../physics/common_units.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;

const string Engine::PISTON_COUNT = "n";
const string Engine::PISTON_MASS = "pistonMass";
const string Engine::CYLINDER_BORE = "cylinderBore";
const string Engine::STROKE_LENGTH = "strokeLength";
const string Engine::ROD_LENGTH = "rodLength";
const string Engine::COMBUSTION_CHAMBER_VOLUME = "combustionChamberVolume";
const string Engine::ROTATING_SPEED = "rotationSped";


Engine::Engine(int pistonCount) : pistonCount(pistonCount) {}

Engine::~Engine() {}

fparams_t Engine::getParams() const {
    fparams_t params;
    params[PISTON_COUNT] = pistonCount;
    params[PISTON_MASS] = pistonMass->convertToSi()->value;
    params[CYLINDER_BORE] = cylinderBore->convertToSi()->value;
    params[STROKE_LENGTH] = strokeLength->convertToSi()->value;
    params[ROD_LENGTH] = rodLength->convertToSi()->value;
    params[COMBUSTION_CHAMBER_VOLUME] = combustionChamberVolume->convertToSi()->value;
    return params;
}

shared_ptr<Function> Engine::mechanicalLossF() const {
    auto rotSpeedF = make_shared<Identity>(ROTATING_SPEED);
    auto elapesedTimeF = make_shared<Identity>("t");
    auto phi = rotSpeedF * elapesedTimeF;

    auto cosPhi = make_shared<CustomFunction>([phi](const fparams_t& params){
        return cos((*phi)(params));
        }, phi->variables());

    auto varSinB = phi->variables();
    varSinB.insert(STROKE_LENGTH);
    auto sinB = make_shared<CustomFunction>([phi](const fparams_t& params){
        auto r = params.at(STROKE_LENGTH) / 2;
        auto l = params.at(ROD_LENGTH);
        auto sinPhi = sin((*phi)(params));
        return r * sinPhi / l;
    }, varSinB);

    auto cosB = make_shared<CustomFunction>([sinB](const fparams_t& params){
        auto sinBV = (*sinB)(params);
        auto beta = asin(sinBV);
        return cos(beta);
    }, varSinB);

    auto rF = make_shared<Identity>(STROKE_LENGTH) / make_shared<Constant>(2);
    auto lF = make_shared<Identity>(ROD_LENGTH);
    auto ocF = rF * cosPhi + lF * cosB;

    auto xF = lF + rF - ocF;
    auto velocityF = xF->derive("t", 0.0001);
    auto accF = velocityF->derive("t", 0.0001l);

    auto massF = make_shared<Identity>(PISTON_MASS);
    auto forceF = massF * accF;
    auto fFrF = make_shared<CustomFunction>([forceF, sinB](const fparams_t& params){
        auto f = (*forceF)(params);
        auto sb = (*sinB)(params);
        return abs(f * sb) * 0.1;
        }, forceF->variables());

    auto absVelocityF = make_shared<CustomFunction>([velocityF](const fparams_t& params){
        return abs((*velocityF)(params));
        }, velocityF->variables());
    auto fVF = fFrF * absVelocityF;
    auto lossF = make_shared<CustomFunction>([fVF, rotSpeedF](const fparams_t& params){
        auto rotSpeedRPS = make_shared<Value>((*rotSpeedF)(params), CommonUnits::Speed::radPs)->convertTo(CommonUnits::Angle::round / CommonUnits::Time::s)->value;
        auto roundTimeS = 1 / rotSpeedRPS;
        auto roundWorkF = fVF->integrate(0, roundTimeS, "t", 0.001);
        auto  roundWork = (*roundWorkF)(params);
        return roundWork / roundTimeS;
        }, fVF->variables());
    return lossF;
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

shared_ptr<Value> Engine::getRodLength() const {
    return rodLength;
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
