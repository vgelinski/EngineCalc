#include "tyre.h"

#include "../../math/constant.h"
#include "../../math/identity.h"
#include "../../physics/common_units.h"

#include <cmath>

using namespace std;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;


const string Tyre::RADIUS = "R";
const string Tyre::WIDTH = "width";
const string Tyre::HEIGHT = "height";
const string Tyre::ROTATING_SPEED = "rotationSpeed";

Tyre::Tyre(const math::fret_t& widthMM, const math::fret_t& heightPerc, const math::fret_t& radiusInch)
        : radius(make_shared<Value>(radiusInch, CommonUnits::Length::Inch)),
          width(make_shared<Value>(widthMM, CommonUnits::Length::mm)),
          height(make_shared<Value>((heightPerc * widthMM) / 100.0L, CommonUnits::Length::mm))
{}

Tyre::~Tyre(){}

shared_ptr<Function> Tyre::speedF() const {
    auto radiusF = make_shared<Constant>(radius->convertToSi()->value + height->convertToSi()->value);
    auto rotSpeedF = make_shared<Identity>(ROTATING_SPEED); // rad/s
    return radiusF * rotSpeedF;
}