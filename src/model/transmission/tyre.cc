#include "tyre.h"

#include "../../math/function/constant.h"
#include "../../math/function/identity.h"
#include "../../physics/common_units.h"

#include <cmath>

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;


const string Tyre::DIAMETER = "D";
const string Tyre::WIDTH = "width";
const string Tyre::HEIGHT = "height";
const string Tyre::ROTATING_SPEED = "rotationSpeed";
const string Tyre::SPEED = "speed";

Tyre::Tyre(const math::fret_t& widthMM, const math::fret_t& heightPerc, const math::fret_t& diameterInch)
        : diameter(make_shared<Value>(diameterInch, CommonUnits::Length::Inch)),
          width(make_shared<Value>(widthMM, CommonUnits::Length::mm)),
          height(make_shared<Value>((heightPerc * widthMM) / 100.0L, CommonUnits::Length::mm))
{}

Tyre::~Tyre(){}

shared_ptr<Function> Tyre::speedF() const {
    auto rotSpeedF = make_shared<Identity>(ROTATING_SPEED); // rad/s
    return radiusF() * rotSpeedF;
}

shared_ptr<Function> Tyre::rotationF() const {
    auto speedF = make_shared<Identity>(SPEED); // m/s
    return speedF / radiusF();
}

shared_ptr<Function> Tyre::radiusF() const {
    return make_shared<Constant>(diameter->convertToSi()->value / 2.0L + height->convertToSi()->value);
}