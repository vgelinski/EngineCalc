#include "differential.h"

#include "../../math/constant.h"
#include "../../math/identity.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;


const string Differential::ROTATING_SPEED = "rotationSpeed";

Differential::Differential(const fret_t& ratio) : ratio(ratio) {}

Differential::~Differential(){}

shared_ptr<Function> Differential::rotationSpeedF() const {
    return make_shared<Identity>(ROTATING_SPEED) / make_shared<Constant>(ratio);
}