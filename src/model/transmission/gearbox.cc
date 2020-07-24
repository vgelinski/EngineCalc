#include "gearbox.h"

#include "../../math/constant.h"
#include "../../math/identity.h"


using namespace std;
using namespace engc::math;
using namespace engc::model;


const string Gearbox::ROTATING_SPEED = "rotationSpeed";

Gearbox::Gearbox(const vector<math::fret_t>& gearRatios) : gearRatios(gearRatios), currentGear(0) {}

Gearbox::~Gearbox(){}

shared_ptr<Function> Gearbox::rotationSpeedF() const {
    return make_shared<Identity>(ROTATING_SPEED) / make_shared<Constant>(gearRatios[currentGear]);
}

shared_ptr<Function> Gearbox::rotationSpeedReverseF() const {
    return make_shared<Identity>(ROTATING_SPEED) * make_shared<Constant>(gearRatios[currentGear]);
}

void Gearbox::shiftToGear(const uint_fast8_t& gear) {
    currentGear = gear;
}

void Gearbox::shiftToReverse() {
    currentGear = 0;
}