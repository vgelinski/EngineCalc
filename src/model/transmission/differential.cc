#include "differential.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;


const string Differential::ROTATING_SPEED = "rotationSpeed"

Differential::Differential(const fret_t& ratio) : ratio(ratio) {}

Differential::~Differential(){}

shared_ptr<Function> Differential::rotationSpeedF() const {
    auto radiusF = make_shared<Constant>(radius->convertToSi()->value + height->convertToSi()->value);
    auto rotSpeedF = make_shared<Identity>(ROTATING_SPEED); // rad/s
    return make_shared<Identity>(ROTATING_SPEED) / make_shared<Constant>(ratio);
}